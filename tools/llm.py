"""Let a language model decompile functions, with the build's score as its feedback.

  python tools/llm.py init [--url URL] [--key-env VAR] [--model NAME] [--start "COMMAND"]
      find the chat server, see what it takes and write llm.json
  python tools/llm.py solve FILE 0x00401000 [0x...]
      the loop for each function, in this checkout: the best attempt stays in FILE
  python tools/llm.py bench [--set SET.tsv | --ladder N]
      solve matched functions again, each from a start without it, then put the files back
  python tools/llm.py report [--tag T]
      the summary of each results file, or of T's

Any server with an OpenAI-style /chat/completions works: llama.cpp, Ollama, LM Studio,
vLLM or a hosted API. docs/FRAMEWORK.md, section "LLM agents", says how to set one up.
tools/llmclient.py says what llm.json holds.

solve and bench take --prompt NAME (the system prompt tools/prompts/NAME.txt, plus
data/llm-hints.txt when the game has one), --tries N, --seed S (try N asks with seed
S+N), --structs (the first prompt lists the members of the structs the dossier names,
and a build error about a missing member lists the members of that struct), --accesses
(each dossier adds how the whole exe reads and writes each global it names), --top-k K,
--top-p P and --min-p M (sent with every request, else the server picks), --tree-wins
(a try that fails on a declaration the tree has in another way is built once more without
the model's declaration of that name), --think-max N (the run ends when it would think after
N thinking tries, or after a thinking try that repeated), --give-up (the run ends after
GIVE_UP_STALE tries without a new best, or after STUCK_TRIES when the best is below
GIVE_UP_BELOW%), --stale-built-only (a try that does not build does not count toward
STUCK_TRIES, nor toward --give-up) and --tag T (default: the prompt's name). Every command
takes --config PATH.
Results go to build/llm/T/: results.tsv with a row per function and transcripts/ADDRESS.jsonl
with every exchange.

bench solves each function of its set from the same start: the function's file with the
function and the file's unmatched functions as stubs, without the declarations only they
used. Then it puts the file and the generated files back. Git must hold each file as it
is, staged or committed, to restore it after a hard kill. Matched means 100% in
docs/progress/summary.json. It saves the set
as build/llm/T/set.tsv and runs that one again for T. A new tag without --set gets
--ladder N: N matched functions of each size bucket, spread over the exe.

The loop: the first prompt holds the function's dossier and up to EXAMPLES matched
functions of the same code group, its own file first, then the nearest in size. Each
attempt goes into the file as it was before the function, and `check.py decls` and
`check.py fn` score it. Then the model sees its best attempt so far with that attempt's
diff, and one line on its latest try when that was another. When the instructions differ
only in the names of globals or functions, the feedback lists the exe's name next to the
model's for each one. An attempt it already sent
is not built again, and the temperature rises until it sends something new. After
STUCK_TRIES tries without a new best, the tries think until the best moves again.
When the file already holds the function, that code is the first best: a solve only
replaces it with a try that scores higher.
"""

import argparse
import collections
import csv
import functools
import json
import re
import subprocess
import sys
import time
from pathlib import Path

import check
import ci
import declgen
import llmclient
import names
import progress
import project

ROOT = project.ROOT
PROMPTS = ROOT / "tools" / "prompts"  # NAME.txt: the system prompt that --prompt NAME picks
HINTS = ROOT / "data" / "llm-hints.txt"  # the game's own facts, added to the system prompt when present
CONFIG = ROOT / "llm.json"
OUT = project.BUILD / "llm"
SERVER_LOG = OUT / "server.log"
BUCKETS = (("<=32", 32), ("33-64", 64), ("65-128", 128), ("129-256", 256), ("257-512", 512), (">512", float("inf")))
LADDER = 5  # functions per size bucket
FEEDBACK_LINES = 150
ERROR_LINES = 40
STUCK_TRIES = 3  # tries without a new best before the model thinks
GIVE_UP_STALE, GIVE_UP_BELOW = 4, 60  # --give-up ends a run at this many stale tries, or at STUCK_TRIES below this %
TEMPERATURE_STEP, TEMPERATURE_MAX = 0.3, 1.2  # added after each repeated attempt
EXAMPLES = 2
STRUCT_LINES = 120  # member lines in the first prompt's Structs section
STRUCT_DEPTH = 2  # levels of member types below the types the dossier names
STRUCTS_RULE = ("The Structs section lists members with their offsets: "
                "use the member names, not casts, when an offset matches.")
RESULT_FIELDS = ["file", "address", "size", "tries", "best", "wall_s", "prompt_tokens", "completion_tokens", "model",
                 "think_tries", "repeats"]
SET_FIELDS = ["file", "address", "size", "name"]
BLOCK = re.compile(r"```[a-zA-Z+]*[ \t]*\n(.*?)```", re.S)
SCORE = re.compile(r"^(0x[0-9a-f]{8}) \S.*?: (?:(\d+(?:\.\d+)?)% match|(stub))", re.M)
DECLARED = re.compile(r"^(?:prototype:|locals:|  \w+ 0x[0-9a-f]{8} ).*", re.M)  # a dossier's typed lines
TAG = re.compile(r"\b(?:struct|union|enum)\s+(\w+)")
OFFSET = re.compile(r"static_assert\(offsetof\(\w+, (\w+)\) == (0x[0-9a-f]+)")
MISSING_MEMBER = re.compile(r"C2039: '\w+' : is not a member of '(\w+)'")
DIFF_LINE = re.compile(r"^(?:0x[0-9a-f]+)?\s*: ([-+])(.*)$", re.M)  # a changed line of reccmp's diff: sign, text
SOURCE_LINE = re.compile(r"\s+\([^()\s]+:\d+\)$")  # such as "	(ef_flash.c:128)" after a line of our build
# decls lines that say the tree declares a name in another way: name, then the tree's way(s)
CLASH_CONTEXT = re.compile(r"^decls: (\w+): (.+) in the context tree\. Declare it that way too\.$")
CLASH_TREE = re.compile(r"^decls: (\w+): the tree declares it `([^`]*)`, a file here declares it `([^`]*)`")
CLASH_WAYS = re.compile(r"^decls: (\w+): sources declare it in \d+ ways: (.+)$")
SYMBOL = re.compile(r"[^\s,\[\]]+(?:\[[^\]]*\])*(?:\+0x[0-9a-f]+)? \([A-Z]+\)")  # a name reccmp put in, with its kind
Best = collections.namedtuple("Best", "percent reply note text")  # text: the source file with that attempt in it


def hexa(address):
    return f"0x{address:08x}"


def bucket(size):
    return next(name for name, top in BUCKETS if size <= top)


@functools.cache
def marker() -> re.Pattern:
    """The line above a definition: FUNCTION or STUB."""
    return re.compile(rf"//\s*(?:FUNCTION|STUB):\s*{project.game_config().target}\s+(0x[0-9a-fA-F]+)")


def function_line(address):
    return f"// FUNCTION: {project.game_config().target} {hexa(address)}"


def annotation_address(line):
    m = marker().match(line)
    return int(m.group(1), 16) if m else None


def definition_end(lines, start):
    """Index of the first line that is exactly "}" from START on, or None."""
    return next((i for i in range(start, len(lines)) if lines[i] == "}"), None)


def definition_span(lines, address):
    """(first, last) line index of the definition at ADDRESS, or None when it has none or no closing line."""
    start = next((i for i, line in enumerate(lines) if annotation_address(line) == address), None)
    end = None if start is None else definition_end(lines, start)
    return None if end is None else (start, end)


def first_function_line(lines):
    """Index of the first annotated line: the top-of-file declarations end there."""
    return next((i for i, line in enumerate(lines) if annotation_address(line) is not None), len(lines))


def parse_reply(reply, address):
    """(declarations, function lines) from the first fenced block that holds the function's annotation."""
    for m in BLOCK.finditer(reply.replace("\r\n", "\n")):
        lines = [line.rstrip() for line in m.group(1).split("\n")]
        span = definition_span(lines, address)
        if span is not None:
            return [d for d in lines[:span[0]] if d and not d.startswith("//")], lines[span[0]:span[1] + 1]
    return None


def apply_function(text, address, decls, func):
    """TEXT with the function in address order (replacing its old definition) and the new declarations after the includes."""
    lines = text.split("\n")
    if lines[-1] == "":
        lines.pop()
    annotated = [(i, annotation_address(line)) for i, line in enumerate(lines) if annotation_address(line) is not None]
    same = next((i for i, a in annotated if a == address), None)
    later = next((i for i, a in annotated if a > address), None)
    if same is not None:
        end = definition_end(lines, same)
        if end is None:
            sys.exit(f"the definition at {hexa(address)} has no closing brace line")
        lines[same:end + 1] = func
    elif later is not None:
        lines[later:later] = func + [""]
    else:
        if lines:
            lines.append("")
        lines += func
    sig = names.parse_annotations("\n".join(func))[0][2]
    if re.match(r"static\b", sig):
        decls = decls + [sig + ";"]  # callers above it need a prototype, and decls never declares a static function
    includes = [i for i, line in enumerate(lines[:first_function_line(lines)]) if line.startswith("#include")]
    seen = {line.strip() for line in lines}
    new = [d for d in dict.fromkeys(decls) if d.strip() not in seen]
    at = includes[-1] + 1 if includes else 0
    lines[at:at] = new
    return "\n".join(lines) + "\n"


def stub_functions(text, addresses):
    """TEXT with the definitions at ADDRESSES as stubs, and without the top-of-file declarations only they used."""
    lines = text.split("\n")
    for address in addresses:
        span = definition_span(lines, address)
        if span is not None:
            sig = names.parse_annotations("\n".join(lines[span[0]:span[1] + 1]))[0][2]
            stub = [f"// STUB: {project.game_config().target} {hexa(address)}", sig, declgen.stub_body(sig)]
            lines[span[0]:span[1] + 1] = "\n".join(stub).split("\n")
    top = first_function_line(lines)
    declared = [names.declared_name(line[:-1]) if i < top and line.endswith(";") else None for i, line in enumerate(lines)]
    used = collections.Counter()
    for line, name in zip(lines, declared):
        used.update(set(re.findall(r"\w+", line)) - {name})
    return "\n".join(line for line, name in zip(lines, declared) if name is None or used[name])


def read_source(path):
    """The file's text with LF line ends, and whether the file has CRLF ones."""
    if not path.exists():
        return '#include "decls.h"\n', False
    text = path.read_bytes().decode("utf-8")
    return text.replace("\r\n", "\n"), "\r\n" in text


def write_source(path, text, crlf):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes((text.replace("\n", "\r\n") if crlf else text).encode("utf-8"))


def snapshot(paths):
    """The bytes of each of PATHS that exists, for restore."""
    return {p: p.read_bytes() for p in paths if p.exists()}


def restore(saved):
    for p, data in saved.items():
        p.write_bytes(data)


def generated_files():
    return [ROOT / rel for rel in names.GENERATED]


def run_check(*args):
    """(output, exit code) of tools/check.py with ARGS."""
    out = subprocess.run([sys.executable, str(ROOT / "tools" / "check.py"), *args], cwd=ROOT, capture_output=True,
                         text=True, errors="replace")
    return out.stdout + out.stderr, out.returncode


def folder_flags(config, *keys):
    """--tables T and the like, for the folders llm.json sets."""
    return [arg for key in keys if config[key] for arg in (f"--{key}", config[key])]


def decls(config):
    """(output, exit code) of check.py decls with the folders llm.json sets."""
    return run_check("decls", *folder_flags(config, "tables", "context"))


def score(config, address):
    """(percent, or None when nothing built or decls failed, the output of decls and the scoring)."""
    declared, failed = decls(config)
    text, _ = run_check("fn", hexa(address))
    scores = {int(m.group(1), 16): 0.0 if m.group(3) else float(m.group(2)) for m in SCORE.finditer(text)}
    return (None if failed else scores.get(address)), declared + text


def dossier(config, address, *flags):
    return run_check("dossier", hexa(address), *flags, *folder_flags(config, "tables", "drafts"))[0].strip()


def tree_warnings(config):
    """The decls lines of the tree before the first try, when decls passes: they are not about the function."""
    text, failed = decls(config)
    return set() if failed else {line for line in text.splitlines() if line.startswith("decls:")}


def tool_lines(text, known):
    """The scoring output without decls' summary line of the functions it declared and the KNOWN decls lines."""
    return [line for line in text.splitlines()
            if not (line.startswith("decls:") and ("functions (" in line or line in known))]


def build_errors(text, known):
    """The lines that say why decls or the build failed."""
    lines = tool_lines(text, known)
    errors = [line for line in lines if " error " in line or "fatal" in line or line.startswith("decls:")]
    shown = (errors or lines[-ERROR_LINES:])[:ERROR_LINES]
    if any("Failed to find function symbol" in line for line in lines):
        shown.append("If the function is `static`, drop the `static`: the compiler leaves out a static function "
                     "that nothing in the build calls, so there is nothing to score.")
    return shown


def tree_conflicts(decls, lines):
    """(DECLS without the model's declarations that decls' LINES say clash with the tree, name: the tree's ways)."""
    mine = {}
    for d in decls:
        for name, decl in line_declarations(d):
            mine.setdefault(name, set()).add(decl)
    gone = {}
    for line in lines:
        m = CLASH_CONTEXT.match(line)
        if m and m.group(1) in mine:
            gone[m.group(1)] = re.findall(r"declares it `([^`]*)`", m.group(2))
        m = CLASH_TREE.match(line)
        if m and m.group(3) in mine.get(m.group(1), ()):
            gone[m.group(1)] = [m.group(2)]
        m = CLASH_WAYS.match(line)
        if m:
            ways = m.group(2).split(" | ")
            theirs = [w for w in ways if w not in mine.get(m.group(1), ())]
            if theirs and len(theirs) < len(ways):
                gone[m.group(1)] = theirs
    return without_declarations(decls, gone), gone


def line_declarations(line):
    """(name, declaration) of each declaration that LINE holds whole: a declaration over two lines has none."""
    funcs, vars_ = names.local_declarations(line)
    return funcs + vars_


def without_declarations(decls, dropped):
    """DECLS without the lines that declare a name in DROPPED, such as a --tree-wins try's "dropped" names."""
    return [d for d in decls if not any(name in dropped for name, _ in line_declarations(d))]


def load_types(config):
    return names.Types(Path(config["tables"]) / "types.h" if config["tables"] else ROOT / names.TYPES_H)


def render_type(types, name):
    """(the type's block as C with a /* +0xN */ comment on each member that has an offset, its member line count)."""
    offsets = dict(OFFSET.findall(types.blocks[name]))
    lines = types.blocks[name].splitlines()
    start, end = next(i for i, line in enumerate(lines) if line.endswith("{")), lines.index("};")
    for i in range(start + 1, end):
        offset = re.match(r" {4}\S.*;$", lines[i]) and offsets.get(names.declared_name(lines[i].strip()[:-1]))
        if offset:
            lines[i] += f"  /* +{offset} */"
    return "\n".join(lines[:end + 1]), end - start - 1


def member_types(types, name):
    """The defined types that the members of NAME mention, in order."""
    found = TAG.findall(types.blocks[name].split("};", 1)[0])
    return [t for t in dict.fromkeys(found) if t != name and t in types.blocks]


def struct_section(types, dossier_text):
    """The Structs section: the types that the dossier's prototype, locals and names used lines mention, then their
    member types down to STRUCT_DEPTH, until STRUCT_LINES member lines are shown. "" when the dossier names no
    defined type."""
    level = [t for t in dict.fromkeys(TAG.findall("\n".join(DECLARED.findall(dossier_text)))) if t in types.blocks]
    seen, shown, left, count = set(level), [], 0, 0
    for _ in range(STRUCT_DEPTH + 1):
        below = []
        for name in level:
            text, members = render_type(types, name)
            if count + members > STRUCT_LINES:
                left += 1
                continue
            shown.append(text)
            count += members
            below += [t for t in member_types(types, name) if t not in seen]
            seen.update(below)
        level = below
    if not shown:
        return ""
    more = f"{left} more types do not fit and are left out.\n" if left else ""
    return "Structs (a `/* +0xN */` comment is the member's offset):\n```cpp\n" + "\n\n".join(shown) + "\n```\n" + more


def missing_members(types, errors):
    """The members of each type that a C2039 error in ERRORS names, once per type. "" when there is none."""
    if types is None:
        return ""
    found = [t for t in dict.fromkeys(MISSING_MEMBER.findall("\n".join(errors))) if t in types.blocks]
    if not found:
        return ""
    return ("\nThe compiler named these types; these are all their members (`/* +0xN */` is the offset):\n```cpp\n"
            + "\n\n".join(render_type(types, t)[0] for t in found) + "\n```")


def masked(line):
    """A diff line without the source line reccmp adds to ours, and with each name it put in replaced by SYMBOL."""
    return SYMBOL.sub("SYMBOL", SOURCE_LINE.sub("", line)).strip()


def names_only(diff):
    """Whether the instructions that differ are the same apart from the names of globals and functions."""
    sides = {"-": [], "+": []}
    for sign, text in DIFF_LINE.findall(diff):
        sides[sign].append(masked(text))
    return bool(sides["-"]) and sorted(sides["-"]) == sorted(sides["+"])


def name_pairs(diff):
    """(the exe's name, ours) for each name that differs between a changed line of the exe and the same line in our
    build, once each. Lines that are the same apart from names pair up in order."""
    ours = [text for sign, text in DIFF_LINE.findall(diff) if sign == "+"]
    pairs = []
    for sign, text in DIFF_LINE.findall(diff):
        twin = next((o for o in ours if masked(o) == masked(text)), None) if sign == "-" else None
        if twin is None:
            continue
        ours.remove(twin)
        pairs += [(exe, own) for exe, own in zip(SYMBOL.findall(text), SYMBOL.findall(twin)) if exe != own]
    return list(dict.fromkeys(pairs))


def names_note(diff):
    """The names to change when the instructions differ only in names, else ""."""
    if not names_only(diff):
        return ""
    rows = [f"- the exe has `{exe.rsplit(' (', 1)[0]}` where yours has `{own.rsplit(' (', 1)[0]}`"
            for exe, own in name_pairs(diff)]
    return ("Only names differ: each instruction is the exe's apart from them. The score names an address after the "
            "nearest global at or below it, so one address can have two names. Use the exe's name in each place. "
            "A `[0][5]` or `+8` after a name is the fixed part of the address: keep your own index.\n"
            + "\n".join(rows) + "\n")


def feedback(percent, text, address, known, types=None):
    if percent is None:
        errors = build_errors(text, known)
        return ("Nothing was scored: decls or the compiler failed. They said:\n```\n"
                + "\n".join(errors) + "\n```" + missing_members(types, errors) + "\n"
                f"Fix the function (all of it) and reply with one cpp block again, with the `{function_line(address)}` line.")
    lines = tool_lines(text, known)
    return (f"Score {percent:.2f}%. The scoring tool printed (`decls:` lines are declaration problems: fix them first; "
            "`-` is the exe, `+` is your build):\n```\n" + "\n".join(lines[:FEEDBACK_LINES]) + "\n```\n"
            + names_note(text)
            + "Reply with one cpp block again: the declarations and the whole function with the changes.")


def matched_functions():
    """address: name of each function at 100% in docs/progress/summary.json."""
    summary = json.loads(progress.SUMMARY_JSON.read_text(encoding="utf-8"))
    return {int(f["address"], 16): f["name"] for f in summary["functions"]
            if f["accuracy"] == 1.0 and not f["stub"] and not f["library"]}


def definitions(roots):
    """address: (root, file) of each FUNCTION definition. The first root that has one wins."""
    found = {}
    for root in roots:
        for rel, text in names.read_sources(root).items():
            for kind, address, _ in names.parse_annotations(text):
                if kind == "FUNCTION":
                    found.setdefault(address, (root, rel))
    return found


def matched_source(path, address):
    """The C of the definition at ADDRESS in PATH, or None when it has none."""
    lines = path.read_text(encoding="utf-8").split("\n")
    span = definition_span(lines, address)
    return None if span is None else "\n".join(lines[span[0]:span[1] + 1])


def examples(config, file, address, count, extra=()):
    """Up to COUNT matched functions of the same code group, its own file first, then the nearest in size."""
    sizes = {f["address"]: f["size"] for f in progress.load_functions()}
    groups = progress.load_codegen_groups()
    group = progress.codegen_group(groups, address)
    where = definitions([ROOT] + ([Path(config["context"])] if config["context"] else []))
    done = matched_functions()
    pool = sorted((a for a in done if a != address and a in where and progress.codegen_group(groups, a) == group),
                  key=lambda a: (where[a][1] != file, abs(sizes.get(a, 0) - sizes[address]), a))
    shown = []
    for a in pool:
        if len(shown) == count:
            break
        root, rel = where[a]
        source = matched_source(root / rel, a)
        if source is None:
            continue
        shown.append(f"Example: {done[a]}, which matches 100%. Its dossier:\n```\n{dossier(config, a, *extra)}\n```\n"
                     f"Its C:\n```cpp\n{source}\n```")
    return shown


def first_prompt(config, file, address, types=None, count=EXAMPLES, extra=()):
    facts = dossier(config, address, '--c', '--callers', *extra)
    structs = "" if types is None else struct_section(types, facts)
    task = (f"Function {hexa(address)}, to go in {file}. Dossier:\n```\n{facts}\n```\n{structs}"
            f"Write the function. Reply with one cpp block with the `{function_line(address)}` line.")
    shown = examples(config, file, address, count, extra)
    return "\n\n".join(shown + ["Now your function. " + task]) if shown else task


def attempt_key(parsed):
    """An attempt with its whitespace folded, so a resend with other spacing counts as the same."""
    decls, func = parsed
    return " ".join(" ".join(decls + func).split())


def next_turn(best, improved, reply, note, latest):
    """The model's best attempt and that attempt's feedback, plus a line on the latest try when it was another."""
    if best is None or improved:
        return [{"role": "assistant", "content": reply}, {"role": "user", "content": note}]
    return [{"role": "assistant", "content": best.reply},
            {"role": "user", "content": f"{best.note}\n\nYour latest try {latest}. The reply above is your best so far "
                                        f"({best.percent:.2f}%): start again from it and change something else."}]


def file_best(config, text, address, known, types):
    """The function's definition in the file as a Best, when it has one that builds, else None."""
    lines = text.split("\n")
    span = definition_span(lines, address)
    if span is None or lines[span[0]].lstrip().startswith("// STUB"):
        return None
    percent, output = score(config, address)
    if percent is None:
        return None
    code = "\n".join(lines[span[0]:span[1] + 1])
    return Best(percent, f"```cpp\n{code}\n```", feedback(percent, output, address, known, types), text)


def thinks(stale, config):
    """Whether a try thinks: after STUCK_TRIES tries without a new best, when the server can."""
    return stale >= STUCK_TRIES and bool(config["think_on"])


def solve_function(args, file, address, transcript):
    """Run the loop for one function. Returns tries, best, wall_s, prompt_tokens, completion_tokens, think_tries, repeats."""
    config = args.settings
    started = time.time()
    path = ROOT / file
    before, crlf = read_source(path)
    # decls forgets a name once no file uses it, so each decls run starts from these files.
    generated = snapshot(generated_files())
    known = tree_warnings(config)
    restore(generated)
    types = load_types(config) if args.structs else None
    extra = ('--accesses',) if args.accesses else ()
    count = EXAMPLES
    first = first_prompt(config, file, address, types, count, extra)
    base = [{"role": "system", "content": args.system}, {"role": "user", "content": first}]
    best = file_best(config, before, address, known, types)  # the code already in the file is the floor
    restore(generated)
    messages, seen = base, {}  # seen: key -> (try, note)
    stale, temperature, totals = 0, config["temperature"], collections.Counter()
    transcript.parent.mkdir(parents=True, exist_ok=True)
    with open(transcript, "w", encoding="utf-8") as log:
        log.write(json.dumps({"prompt": first}) + "\n")
        if best is not None:
            log.write(json.dumps({"file_best": best.percent}) + "\n")
            print(f"{hexa(address)}: the file's code scores {best.percent:.2f}%", flush=True)
        for tries in range(1, args.tries + 1):
            thinking = thinks(stale, config)
            asked = time.time()
            seed = None if args.seed is None else args.seed + tries
            try:
                reply = llmclient.chat(config, messages, temperature, thinking, seed)
            except llmclient.ServerError as e:
                if e.status != 400 or "context" not in str(e).lower():
                    raise
                # Too long for the server: drop the history, else an example, else give up on the function.
                if messages is not base:
                    messages = base
                elif count > 0:
                    count -= 1
                    first = first_prompt(config, file, address, types, count, extra)
                    messages = base = [base[0], {"role": "user", "content": first}]
                    log.write(json.dumps({"prompt": first}) + "\n")
                else:
                    print(f"{hexa(address)} try {tries}: even the first prompt is too long for the server", flush=True)
                    break
                print(f"{hexa(address)} try {tries}: too long for the server, retrying shorter", flush=True)
                continue
            totals["prompt_tokens"] += reply.usage["prompt_tokens"]
            totals["completion_tokens"] += reply.usage["completion_tokens"]
            totals["think_tries"] += thinking
            parsed = parse_reply(reply.text, address)
            percent, repeat, dropped = None, None, {}
            if parsed is None:
                result = latest = "had no function in the reply"
                note = (f"Your reply had no fenced cpp block with the `{function_line(address)}` line and a function "
                        "that ends with a line holding only `}`. Reply with one cpp block.")
            elif attempt_key(parsed) in seen:
                repeat, earlier = seen[attempt_key(parsed)]
                result = latest = f"repeated try {repeat}"
                note = f"That is the same code as your try {repeat}, which got this answer:\n\n{earlier}"
            else:
                attempt = apply_function(before, address, *parsed)
                write_source(path, attempt, crlf)
                restore(generated)
                percent, text = score(config, address)
                kept, gone = parsed[0], {}
                if args.tree_wins and percent is None:
                    kept, gone = tree_conflicts(parsed[0], tool_lines(text, known))
                if gone:
                    trimmed = apply_function(before, address, kept, parsed[1])
                    write_source(path, trimmed, crlf)
                    restore(generated)
                    retry_percent, retry_text = score(config, address)
                    left = tool_lines(retry_text, known)
                    dropped = {name: ways for name, ways in gone.items()
                               if not any(line.startswith(f"decls: {name}: ") for line in left)}
                    if dropped:  # else the clash was not the model's declaration: the first build's answer stands
                        attempt, percent, text = trimmed, retry_percent, retry_text
                tree_ways = {name: " or ".join(f"`{way}`" for way in ways) for name, ways in dropped.items()}
                note = "".join(f"Your declaration of {name} was dropped: the tree declares it as {ways}.\n"
                               for name, ways in tree_ways.items())
                note += feedback(percent, text, address, known, types)
                seen[attempt_key(parsed)] = (tries, note)
                if dropped:
                    seen[attempt_key((kept, parsed[1]))] = (tries, note)
                result = "build failed" if percent is None else f"{percent:.2f}%"
                errors = build_errors(text, known)[:10]
                latest = ("did not build:\n```\n" + "\n".join(errors) + "\n```" + missing_members(types, errors)
                          if percent is None else f"scored {percent:.2f}%")
                if dropped:  # next_turn shows only this line when the try is no new best
                    latest = ("was built without your declaration of "
                              + ", ".join(f"{name} (the tree declares it as {ways})" for name, ways in tree_ways.items())
                              + " and " + latest)
            improved = percent is not None and (best is None or percent > best.percent)
            if improved:
                best = Best(percent, reply.text, note, attempt)
            failed_build = parsed is not None and repeat is None and percent is None
            stale = 0 if improved else stale + (0 if args.stale_built_only and failed_build else 1)
            totals["repeats"] += repeat is not None
            temperature = (round(min(temperature + TEMPERATURE_STEP, TEMPERATURE_MAX), 2) if repeat is not None
                           else config["temperature"])
            log.write(json.dumps({"try": tries, "thinking": thinking, "result": result,
                                  "seconds": round(time.time() - asked, 1), "usage": reply.usage,
                                  "finish": reply.finish, "reasoning": reply.reasoning, "reply": reply.text,
                                  "note": note, **({"dropped": dropped} if dropped else {})}) + "\n")
            log.flush()
            cut = " (the reply hit max_tokens)" if reply.finish == "length" else ""
            trim = f" (without its declaration of {', '.join(dropped)})" if dropped else ""
            print(f"{hexa(address)} try {tries}{' (thinking)' if thinking else ''}: {result}{trim}{cut}", flush=True)
            if percent == 100:
                break
            best_percent = best.percent if best else 0.0
            if args.give_up and (stale >= GIVE_UP_STALE or (stale >= STUCK_TRIES and best_percent < GIVE_UP_BELOW)):
                break
            if args.think_max is not None and thinks(stale, config) and (totals["think_tries"] >= args.think_max
                                                                         or (thinking and repeat is not None)):
                break
            messages = base + next_turn(best, improved, reply.text, note, latest)
    write_source(path, best.text if best else before, crlf)
    restore(generated)
    decls(config)
    return {"tries": tries, "best": best.percent if best else 0.0, "wall_s": time.time() - started, **totals}


def log_result(path, file, address, size, result, model):
    new = not path.exists()
    with open(path, "a", encoding="utf-8", newline="") as out:
        writer = csv.writer(out, delimiter="\t")
        if new:
            writer.writerow(RESULT_FIELDS)
        writer.writerow([file, hexa(address), size, result["tries"], f"{result['best']:.2f}",
                         f"{result['wall_s']:.1f}", result["prompt_tokens"], result["completion_tokens"], model,
                         result["think_tries"], result["repeats"]])


def solve_and_log(args, file, address, size):
    folder = OUT / args.tag
    results = folder / "results.tsv"
    if results.exists() and results.read_text(encoding="utf-8").splitlines()[0].split("\t") != RESULT_FIELDS:
        sys.exit(f"{results} has other columns than {RESULT_FIELDS}: log to another tag")
    result = solve_function(args, file, address, folder / "transcripts" / f"{address:08x}.jsonl")
    log_result(results, file, address, size, result, args.settings["model"])
    print(f"{hexa(address)}: best {result['best']:.2f}% in {result['tries']} tries "
          f"({result['think_tries']} thinking), {result['wall_s']:.0f}s", flush=True)


def solve(args):
    file = (ROOT / args.file).resolve().relative_to(ROOT.resolve()).as_posix()
    sizes = {f["address"]: f["size"] for f in progress.load_functions()}
    unknown = [hexa(a) for a in args.addresses if a not in sizes]
    if unknown:
        sys.exit(f"not a function in data/functions.csv: {' '.join(unknown)}")
    llmclient.ensure_server(args.settings, SERVER_LOG)
    for address in sorted(args.addresses):
        solve_and_log(args, file, address, sizes[address])
    return 0


def ladder(per_bucket):
    """PER_BUCKET matched functions of each size bucket, spread evenly over the bucket in address order."""
    sizes = {f["address"]: f["size"] for f in progress.load_functions()}
    where = definitions([ROOT])
    done = matched_functions()
    pool = sorted(a for a in done if a in where and a in sizes)
    chosen = []
    for name, _ in BUCKETS:
        in_bucket = [a for a in pool if bucket(sizes[a]) == name]
        count = min(per_bucket, len(in_bucket))
        chosen += [in_bucket[i * len(in_bucket) // count] for i in range(count)]
    return [{"file": where[a][1], "address": hexa(a), "size": str(sizes[a]), "name": done[a]} for a in chosen]


def write_set(path, rows):
    path.parent.mkdir(parents=True, exist_ok=True)
    with open(path, "w", encoding="utf-8", newline="") as out:
        writer = csv.DictWriter(out, SET_FIELDS, delimiter="\t", extrasaction="ignore")
        writer.writeheader()
        writer.writerows(rows)


def bench(args):
    folder = OUT / args.tag
    saved_set = folder / "set.tsv"
    if args.set:
        rows, source = names.table_rows(args.set), args.set
    elif saved_set.exists():
        rows, source = names.table_rows(saved_set), saved_set
    else:
        rows, source = ladder(args.ladder), f"--ladder {args.ladder}"
    files = sorted({r["file"] for r in rows})
    # The second column of a status line is what git does not hold: an unstaged change or an untracked file.
    dirty = [line for line in ci.git("status", "--porcelain", "--", *files).splitlines() if line[1] != " "]
    if dirty:
        sys.exit("bench puts each file back from a copy, and git restores it after a hard kill, "
                 "so stage (git add) or commit these first:\n" + "\n".join(dirty))
    if not args.set or Path(args.set).resolve() != saved_set.resolve():
        write_set(saved_set, rows)
    print(f"bench: {len(rows)} functions from {source}, tag {args.tag}", flush=True)
    llmclient.ensure_server(args.settings, SERVER_LOG)
    results = folder / "results.tsv"
    done = {int(r["address"], 16) for r in names.table_rows(results)} if results.exists() else set()
    matched = matched_functions()
    for row in rows:
        address = int(row["address"], 16)
        if address in done:
            continue
        path = ROOT / row["file"]
        saved = snapshot([path, *generated_files()])
        try:
            text, crlf = read_source(path)
            unmatched = [a for kind, a, _ in names.parse_annotations(text) if kind == "FUNCTION" and a not in matched]
            write_source(path, stub_functions(text, [address, *unmatched]), crlf)
            solve_and_log(args, row["file"], address, row["size"])
        finally:
            restore(saved)
    return report(args.tag)


def report(tag):
    tags = [tag] if tag else sorted(p.name for p in OUT.glob("*") if (p / "results.tsv").exists())
    if not tags or not (OUT / tags[0] / "results.tsv").exists():
        sys.exit("no results yet")
    for t in tags:
        rows = list({r["address"]: r for r in names.table_rows(OUT / t / "results.tsv")}.values())
        best = [float(r["best"]) for r in rows]
        tokens = sum(int(r["prompt_tokens"]) + int(r["completion_tokens"]) for r in rows)
        print(f"{t}: functions tried {len(rows)}, matched at 100% {sum(1 for b in best if b == 100)}, "
              f"mean best score {sum(best) / len(rows):.2f}%, mean tries {sum(int(r['tries']) for r in rows) / len(rows):.2f}, "
              f"total tokens {tokens}, wall time {sum(float(r['wall_s']) for r in rows):.0f}s, "
              f"thinking tries {sum(int(r['think_tries']) for r in rows)}, repeats {sum(int(r['repeats']) for r in rows)}")
    return 0


def system_prompt(name):
    game = project.game_config()
    text = (PROMPTS / f"{name}.txt").read_text(encoding="utf-8").strip()
    text = text.replace("{target}", game.target).replace("{exe}", game.filename)
    if HINTS.exists():
        text += "\n\n" + HINTS.read_text(encoding="utf-8").strip()
    return text


def parse_args():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    common = argparse.ArgumentParser(add_help=False)
    common.add_argument("--config", type=Path, default=CONFIG, help="the config file (default: llm.json)")
    runs = argparse.ArgumentParser(add_help=False, parents=[common])
    runs.add_argument("--prompt", default="v2", choices=sorted(p.stem for p in PROMPTS.glob("*.txt")))
    runs.add_argument("--tries", type=int, default=10)
    runs.add_argument("--seed", type=int, help="try N asks with seed S+N, so a rerun repeats")
    runs.add_argument("--structs", action="store_true", help="show the members of the structs the dossier names")
    runs.add_argument("--accesses", action="store_true", help="show how the whole exe reads and writes each global")
    for sampler, kind in (("--top-k", int), ("--top-p", float), ("--min-p", float)):
        runs.add_argument(sampler, type=kind, help="sent with every request (default: the server's own)")
    runs.add_argument("--tree-wins", action="store_true",
                      help="build a try once more without the declarations that clash with the tree")
    runs.add_argument("--think-max", type=int, help="end a run when it would think after N thinking tries")
    runs.add_argument("--give-up", action="store_true", help="end a run that stopped getting better")
    runs.add_argument("--stale-built-only", action="store_true",
                      help="a try that does not build does not count toward thinking")
    runs.add_argument("--tag", help="results go to build/llm/TAG (default: the prompt's name)")
    commands = parser.add_subparsers(dest="command", required=True)
    init = commands.add_parser("init", parents=[common])
    init.add_argument("--url", help="the URL before /chat/completions, such as http://127.0.0.1:8080/v1")
    init.add_argument("--key-env", help="the environment variable that holds the API key")
    init.add_argument("--model", help="the model name, when the server lists several")
    init.add_argument("--start", help="the command that starts the server, when nothing answers")
    solve_command = commands.add_parser("solve", parents=[runs])
    solve_command.add_argument("file", help="the source file, such as src/main.c")
    solve_command.add_argument("addresses", nargs="+", type=lambda value: int(value, 16), help="e.g. 0x00401000")
    bench_command = commands.add_parser("bench", parents=[runs])
    bench_command.set_defaults(seed=1)
    chosen = bench_command.add_mutually_exclusive_group()
    chosen.add_argument("--set", type=Path, help="a tab-separated file with file, address and size columns")
    chosen.add_argument("--ladder", type=int, default=LADDER, help="matched functions per size bucket")
    commands.add_parser("report").add_argument("--tag")
    return parser.parse_args()


def main():
    args = parse_args()
    if args.command == "report":
        return report(args.tag)
    if args.command == "init":
        return llmclient.init(args.config, args.url, args.key_env, args.model, args.start, SERVER_LOG)
    args.settings = llmclient.load(args.config)
    samplers = {"top_k": args.top_k, "top_p": args.top_p, "min_p": args.min_p}
    args.settings["extra_body"] = {**args.settings["extra_body"], **{k: v for k, v in samplers.items() if v is not None}}
    args.tag = args.tag or args.prompt
    args.system = system_prompt(args.prompt)  # once, so an edit mid-run changes nothing
    if args.structs:
        args.system += "\n\n" + STRUCTS_RULE
    if args.seed is not None and not args.settings["seed"]:
        print(f"{args.config} says the server does not repeat a reply for a seed: this run will not repeat.")
    try:
        return solve(args) if args.command == "solve" else bench(args)
    except llmclient.ServerError as e:
        sys.exit(str(e))


if __name__ == "__main__":
    check.rerun_in_venv(__file__)
    sys.exit(main())
