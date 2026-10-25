"""Recipes: a stronger decompiler (the teacher) solves a function the local model misses, blind, and writes the plan
it followed as short steps without code. The local model then tries the function with that plan (llm.py --recipes).
A plan it follows to 100% becomes a training row: the first prompt, the plan as the reasoning, and the matched C.

  python tools/recipes.py brief 0x00401000 [0x...] --out DIR [--prompt NAME] [--structs] [--accesses] [--facts]
                                 [--idioms] [--similar-examples]
  python tools/recipes.py score 0x00401000
  python tools/recipes.py check DIR/0x00401000
  python tools/recipes.py export DIR --run build/llm/TAG [...] --out FILE.jsonl

Run each in the checkout the teacher works in, with its target as a stub or below 100%, so no answer is there to
read. brief writes DIR/ADDRESS/: brief.md for the teacher (tools/prompts/teacher.md, then the local model's system
and first prompt, built with the flags given as llm.py would build them), system.txt and prompt.txt for export, and
sources.json, the hash of every hand-written source. score regenerates the declarations and scores the function, as
llm.py scores a try. check passes when the function is at 100%, tricks.py finds no trick in it, no source but the
function's own file changed since brief, and DIR/ADDRESS/recipe.md is a plan without code: numbered steps, at most
MAX_STEPS, no code block, no line with `;`, `{` or `}`. It writes check.json. export writes one row per checked
function that one of the llm.py runs in RUN matched, with the first such run's matching reply as the completion.
Every command takes --config PATH (default: llm.json).
"""

import argparse
import hashlib
import json
import re
import sys
from pathlib import Path

import check
import llm
import llmclient
import names
import tricks

TEACHER = llm.PROMPTS / "teacher.md"
MAX_STEPS = 12
STEP = re.compile(r"^\s*\d+[.)]\s")
CODE_MARKS = (";", "{", "}")


def source_hashes(root):
    """path: sha256 of each hand-written source under root/src."""
    return {rel: hashlib.sha256(text.encode("utf-8")).hexdigest() for rel, text in names.read_sources(root).items()}


def annotated_file(root, address):
    """The source file under ROOT with an annotation of any kind at ADDRESS, or None."""
    for rel, text in names.read_sources(root).items():
        if any(found == address for _, found, _ in names.parse_annotations(text)):
            return rel
    return None


def recipe_problems(text):
    """Why TEXT is not a plan without code, or [] when it is one."""
    lines = text.split("\n")
    steps = sum(1 for line in lines if STEP.match(line))
    problems = []
    if "```" in text or "~~~" in text:
        problems.append("it has a code block")
    problems += [f"line {i + 1} looks like code: {line.strip()}" for i, line in enumerate(lines)
                 if any(mark in line for mark in CODE_MARKS)]
    if not 1 <= steps <= MAX_STEPS:
        problems.append(f"it has {steps} numbered steps, not 1 to {MAX_STEPS}")
    return problems


def brief(args, config):
    teacher = TEACHER.read_text(encoding="utf-8")
    types = llm.load_types(config) if args.structs else None
    extra = llm.dossier_flags(args)
    system = llm.system_text(args.prompt, args.structs)
    hashes = source_hashes(llm.ROOT)
    for address in args.addresses:
        file = annotated_file(llm.ROOT, address)
        if file is None:
            sys.exit(f"{llm.hexa(address)} has no annotation under {llm.ROOT / 'src'}")
        prompt = llm.first_prompt(config, file, address, types, llm.EXAMPLES, extra, args.similar_examples)
        folder = args.out / llm.hexa(address)
        folder.mkdir(parents=True, exist_ok=True)
        rules = teacher.replace("{address}", llm.hexa(address)).replace("{file}", file).replace(
            "{root}", str(llm.ROOT)).replace("{folder}", str(folder.resolve()))
        text = (f"{rules.strip()}\n\n## The local model's system prompt\n\n~~~~text\n{system}\n~~~~\n\n"
                f"## The local model's first prompt\n\n~~~~text\n{prompt}\n~~~~\n")
        folder.joinpath("brief.md").write_text(text, encoding="utf-8", newline="\n")
        folder.joinpath("system.txt").write_text(system, encoding="utf-8", newline="\n")
        folder.joinpath("prompt.txt").write_text(prompt, encoding="utf-8", newline="\n")
        folder.joinpath("sources.json").write_text(json.dumps({"file": file, "hashes": hashes}, indent=1) + "\n",
                                                   encoding="utf-8", newline="\n")
        print(f"{folder / 'brief.md'}: {file}")
    return 0


def score(args, config):
    percent, output = llm.score(config, args.address)
    print(output.strip())
    print(f"{llm.hexa(args.address)}: " + ("did not build" if percent is None else f"{percent:.2f}%"))
    return 0 if percent == 100 else 1


def check_folder(args, config):
    folder = args.folder
    address = int(folder.name, 16)
    recorded = json.loads(folder.joinpath("sources.json").read_text(encoding="utf-8"))
    percent, _ = llm.score(config, address)
    problems = [] if percent == 100 else [f"it scores {'nothing' if percent is None else f'{percent:.2f}%'}"]
    found = tricks.scan(llm.ROOT).get(address)
    if found:
        problems.append(f"it matches through a trick: {found[1]}")
    now = source_hashes(llm.ROOT)
    changed = sorted(rel for rel in set(now) | set(recorded["hashes"])
                     if rel != recorded["file"] and now.get(rel) != recorded["hashes"].get(rel))
    if changed:
        problems.append(f"sources other than {recorded['file']} changed: {', '.join(changed)}")
    plan = folder / "recipe.md"
    if plan.exists():
        problems += [f"recipe.md: {problem}" for problem in recipe_problems(plan.read_text(encoding="utf-8"))]
    else:
        problems.append("there is no recipe.md")
    folder.joinpath("check.json").write_text(json.dumps({"passed": not problems, "problems": problems}) + "\n",
                                             encoding="utf-8", newline="\n")
    print("\n".join([f"{llm.hexa(address)}: {'passed' if not problems else 'failed'}", *problems]))
    return 0 if not problems else 1


def winning_reply(transcript, address):
    """(the fenced C, the try) of the first try in TRANSCRIPT, an llm.py transcript, that reached 100% with a block
    that holds the function and no tricks.forbidden word, or None."""
    for line in transcript.read_text(encoding="utf-8").splitlines():
        record = json.loads(line)
        result = re.match(r"\d+(?:\.\d+)?", record.get("result", ""))
        if "try" in record and result and float(result.group()) >= 100:
            block = llm.cpp_block(record["reply"], address)
            if block is not None and not tricks.forbidden(block.split("\n")):
                return block, record["try"]
    return None


def first_win(runs, address):
    """(the run, its winning_reply) of the first of RUNS, llm.py run folders, that matched ADDRESS, or None."""
    for run in runs:
        transcript = run / "transcripts" / f"{address:08x}.jsonl"
        won = winning_reply(transcript, address) if transcript.exists() else None
        if won is not None:
            return run, won
    return None


def export(args, config):
    rows = []
    for folder in sorted(path for path in args.folder.iterdir() if path.joinpath("check.json").exists()):
        if not json.loads(folder.joinpath("check.json").read_text(encoding="utf-8"))["passed"]:
            continue
        address = int(folder.name, 16)
        found = first_win(args.run, address)
        if found is None:
            continue
        run, won = found
        recorded = json.loads(folder.joinpath("sources.json").read_text(encoding="utf-8"))
        rows.append({"id": folder.name, "file": recorded["file"], "source": "recipe", "tag": run.name,
                     "win_try": won[1], "system": folder.joinpath("system.txt").read_text(encoding="utf-8"),
                     "prompt": folder.joinpath("prompt.txt").read_text(encoding="utf-8"),
                     "reasoning": folder.joinpath("recipe.md").read_text(encoding="utf-8").strip(),
                     "completion": won[0]})
    with open(args.out, "w", encoding="utf-8", newline="\n") as f:
        f.writelines(json.dumps(row) + "\n" for row in rows)
    print(f"{args.out}: {len(rows)} rows")
    return 0


def parse_args():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--config", type=Path, default=llm.CONFIG, help="the config file (default: llm.json)")
    commands = parser.add_subparsers(dest="command", required=True)
    hexadecimal = lambda value: int(value, 16)  # noqa: E731
    briefs = commands.add_parser("brief")
    briefs.add_argument("addresses", nargs="+", type=hexadecimal, help="e.g. 0x00401000")
    briefs.add_argument("--out", type=Path, required=True)
    briefs.add_argument("--prompt", default="v2", choices=sorted(p.stem for p in llm.PROMPTS.glob("*.txt")))
    for flag in ("--structs", "--accesses", "--facts", "--idioms", "--similar-examples"):
        briefs.add_argument(flag, action="store_true", help="as in llm.py")
    commands.add_parser("score").add_argument("address", type=hexadecimal)
    commands.add_parser("check").add_argument("folder", type=Path, help="DIR/ADDRESS from brief")
    exports = commands.add_parser("export")
    exports.add_argument("folder", type=Path, help="the DIR of brief")
    exports.add_argument("--run", type=Path, nargs="+", required=True,
                         help="the llm.py runs with --recipes, build/llm/TAG; the first that matched counts")
    exports.add_argument("--out", type=Path, required=True)
    return parser.parse_args()


def main():
    args = parse_args()
    config = llmclient.load(args.config)
    return {"brief": brief, "score": score, "check": check_folder, "export": export}[args.command](args, config)


if __name__ == "__main__":
    check.rerun_in_venv(__file__)
    sys.exit(main())
