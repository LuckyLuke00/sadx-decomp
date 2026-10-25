"""Type search: `check.py retype SPEC`. It builds and scores each candidate type of a global or a field, and keeps the
one that proves itself.

SPEC is a JSON file:
  name        the report's name: build/retype/NAME.tsv
  files       the source files the candidates edit, relative to the tree's root. A retyped global's extern lines must
              all be in them: decls refuses a type that only some files declare.
  watch       the addresses of the functions whose address_pun lines the type must remove
  prefer      optional: the candidate that wins when several survive
  candidates  [{"name": ..., "edits": [...]}], each edit one of
                {"kind": "replace", "file": F, "old": TEXT, "new": TEXT, "count": N}  N times in F, else the run stops
                {"kind": "extern", "symbol": S, "decl": "int S"}    every column-0 extern line of S in FILES
                {"kind": "uncast", "symbol": S, "type": "int"}      *(T *)&S and (T)S become S in FILES

Each candidate runs decls, the build and one reccmp run on the tree as it is plus its edits, then the files go back.
The baseline is the same run with no edits. A candidate survives when it builds, no function scores lower than in
the baseline, the watched functions have no address_pun line left and no new fake line of another kind. Among the
survivors, the only one wins; else `prefer` wins when it survives; else the one with the fewest casts left on the
symbols wins when no other has that few; else it is a tie, and nothing changes. --apply writes the winner's edits
and runs decls.

Run it in a lane that holds FILES: a declaration change in the whole tree rebuilds every file.
"""

import csv
import json
import re
import sys
import time
from pathlib import Path
from typing import NamedTuple

import check
import declgen
import fakematch
import llm
import names
import osutil
import project
import runner

OUT = project.BUILD / "retype"
KINDS = ("replace", "extern", "uncast")
ERROR_LINE = re.compile(r"\b(error|fatal)\b", re.I)  # a compiler, linker or CMake error
CAST = r"\(\s*((?:[^()]|\(\s*\*\s*\))+)\)"  # a cast: no parentheses inside but a `(*)`, as in `(struct taskwk *(*))`
NOT_A_CALL = r"(?<![\w)\]])"  # before a `(`: no name, `)` or `]`, so the parenthesis is not a call's
NO_MEMBER = r"\b(?!\s*(?:\.|->))"  # after the symbol: no member of it, whose type is another


class Result(NamedTuple):
    candidate: str
    error: str | None  # the decls or build failure, None when it builds
    scores: dict[int, float]  # address: reccmp's matching share
    puns: int  # address_pun lines in the watched functions
    other_fakes: int  # fake lines of the other kinds in the watched functions
    casts: int  # casts left on the spec's symbols in its files
    seconds: float


# The edits, on text.


def replace_text(text: str, old: str, new: str, count: int, where: str) -> str:
    found = text.count(old)
    if found != count:
        sys.exit(f"{where}: {old!r} is there {found} times, not {count}: the spec no longer fits the file")
    return text.replace(old, new)


def retype_externs(text: str, symbol: str, decl: str) -> tuple[str, int]:
    """TEXT with every column-0 `extern ...;` line that declares SYMBOL declaring DECL instead, and how many."""
    count = 0

    def swap(m: re.Match) -> str:
        nonlocal count
        if names.declared_name(" ".join(m[1].split())) != symbol:
            return m[0]
        count += 1
        return f"extern {decl};"

    text = re.sub(rf"^extern\s+([^;{{}}]*\b{re.escape(symbol)}\b[^;{{}}]*);", swap, text, flags=re.M)
    return text, count


def plain_type(text: str) -> str:
    """A type's text without spaces, with a pointer written `(*)` as `*`: `struct taskwk *(*)` is `structtaskwk**`."""
    return re.sub(r"\(\*\)", "*", re.sub(r"\s+", "", text))


def uncast(text: str, symbol: str, ctype: str) -> str:
    """TEXT with each `*(CTYPE *)&SYMBOL` and `(CTYPE)SYMBOL` as SYMBOL, and the parentheses around it dropped when
    they are not a call's. A member of SYMBOL keeps its cast."""
    sym = re.escape(symbol)
    read = re.compile(rf"\*\s*{CAST}\s*&\s*{sym}{NO_MEMBER}")
    converted = re.compile(rf"{NOT_A_CALL}{CAST}\s*{sym}{NO_MEMBER}")
    text = read.sub(lambda m: symbol if plain_type(m[1]) == plain_type(ctype) + "*" else m[0], text)
    text = converted.sub(lambda m: symbol if plain_type(m[1]) == plain_type(ctype) else m[0], text)
    # `((T)S)` or `(*(T *)&S)` is now `(S)`.
    return re.sub(rf"{NOT_A_CALL}\(\s*{sym}\s*\)", symbol, text)


def count_casts(text: str, symbol: str) -> int:
    """The casts in TEXT that stand right before SYMBOL or its address."""
    return len(re.findall(rf"{CAST}\s*&?\s*{re.escape(symbol)}\b", names.strip_code(text)))


def apply_edits(texts: dict[str, str], edits: list[dict]) -> dict[str, str]:
    """TEXTS, file: text, with EDITS made. An extern edit that finds no line stops the run: the spec is wrong."""
    texts = dict(texts)
    for edit in edits:
        if edit["kind"] == "replace":
            texts[edit["file"]] = replace_text(texts[edit["file"]], edit["old"], edit["new"], edit["count"],
                                               edit["file"])
        elif edit["kind"] == "extern":
            found = 0
            for rel, text in texts.items():
                texts[rel], count = retype_externs(text, edit["symbol"], edit["decl"])
                found += count
            if not found:
                sys.exit(f"no file of the spec has a column-0 extern line of {edit['symbol']}")
        else:
            texts = {rel: uncast(text, edit["symbol"], edit["type"]) for rel, text in texts.items()}
    return texts


def write_edits(files: list[str], edits: list[dict]) -> dict[str, str]:
    """Make EDITS in FILES, relative to the root, and give their new texts. Nothing is written when an edit stops."""
    sources = {rel: llm.read_source(project.ROOT / rel) for rel in files}
    texts = apply_edits({rel: text for rel, (text, _) in sources.items()}, edits)
    for rel, (_, crlf) in sources.items():
        llm.write_source(project.ROOT / rel, texts[rel], crlf)
    return texts


# The verdict.


def worse(base: Result, result: Result) -> list[str]:
    """The functions that score lower in RESULT than in BASE, as `0x...: old -> new`."""
    return [f"0x{a:08x}: {old:.2%} -> {result.scores.get(a, 0.0):.2%}" for a, old in sorted(base.scores.items())
            if result.scores.get(a, 0.0) < old]


def better(base: Result, result: Result) -> list[str]:
    return [f"0x{a:08x}: {base.scores.get(a, 0.0):.2%} -> {new:.2%}" for a, new in sorted(result.scores.items())
            if new > base.scores.get(a, 0.0)]


def survives(base: Result, result: Result) -> bool:
    return (result.error is None and not worse(base, result) and result.puns == 0
            and result.other_fakes <= base.other_fakes)


def winner(base: Result, results: list[Result], prefer: str | None) -> tuple[str | None, str]:
    """(the winning candidate or None, why)."""
    alive = [r for r in results if survives(base, r)]
    if not alive:
        return None, "no candidate survives"
    if len(alive) == 1:
        return alive[0].candidate, "the only survivor"
    if prefer in {r.candidate for r in alive}:
        return prefer, "the preferred survivor"
    fewest = min(r.casts for r in alive)
    least = [r for r in alive if r.casts == fewest]
    if len(least) == 1:
        return least[0].candidate, f"the only survivor with {fewest} casts left"
    return None, "a tie between " + ", ".join(r.candidate for r in least)


# The runs.


def load_spec(path: Path) -> dict:
    spec = json.loads(path.read_text(encoding="utf-8"))
    for key in ("name", "files", "watch", "candidates"):
        if key not in spec:
            sys.exit(f"{path}: no {key!r}")
    for candidate in spec["candidates"]:
        for edit in candidate["edits"]:
            if edit.get("kind") not in KINDS:
                sys.exit(f"{path}: {candidate['name']} has an edit of kind {edit.get('kind')!r}, not one of {KINDS}")
            if edit["kind"] == "replace" and edit["file"] not in spec["files"]:
                sys.exit(f"{path}: {candidate['name']} edits {edit['file']}, which is not in files")
    if spec.get("prefer") not in (None, *(c["name"] for c in spec["candidates"])):
        sys.exit(f"{path}: prefer names no candidate")
    return spec


def symbols(spec: dict) -> set[str]:
    return {edit["symbol"] for c in spec["candidates"] for edit in c["edits"] if "symbol" in edit}


def definition(texts: dict[str, str], address: int) -> list[str]:
    """The lines of the definition at ADDRESS, from its annotation on, in one of TEXTS."""
    for text in texts.values():
        lines = text.split("\n")
        span = llm.definition_span(lines, address)
        if span is not None:
            return lines[span[0]:span[1] + 1]
    sys.exit(f"no file of the spec defines 0x{address:08x}")


def watched(texts: dict[str, str], addresses: list[int], in_image) -> tuple[int, int]:
    """(address_pun lines, other fake lines) in the functions at ADDRESSES, which must all be in TEXTS."""
    puns = others = 0
    for address in addresses:
        func = definition(texts, address)
        kinds = [kind for kind, _ in fakematch.found(func, llm.signature_index(func), in_image)]
        puns += kinds.count("address_pun")
        others += len(kinds) - kinds.count("address_pun")
    return puns, others


def failure(spec: dict, context: Path | None, tables: Path | None) -> str | None:
    """None when decls and the build work, else the lines that say why: decls' lines that name the spec's symbols, or
    the build's error lines."""
    worked, lines = osutil.caught(lambda: declgen.write(context, tables))
    if not worked:
        named = [line for line in lines if line.startswith("decls:") and any(s in line for s in symbols(spec))]
        return "\n".join((named or lines[-2:])[:5])
    worked, lines = osutil.caught(check.build)
    if not worked:
        return "\n".join(([line.strip() for line in lines if ERROR_LINE.search(line)] or lines[-1:])[:5])
    return None


def evaluate(name: str, spec: dict, edits: list[dict], game: Path, context: Path | None, tables: Path | None,
             in_image) -> Result:
    """Build and score the tree with EDITS, then put the files back."""
    started = time.time()
    saved = llm.snapshot([project.ROOT / rel for rel in spec["files"]] + llm.generated_files())
    try:
        texts = write_edits(spec["files"], edits)
        puns, others = watched(texts, [int(a, 16) for a in spec["watch"]], in_image)
        casts = sum(count_casts(text, s) for text in texts.values() for s in symbols(spec))
        error = failure(spec, context, tables)
        scores = {} if error else {a: e["matching"] for a, e in runner.score_target(runner.game_build(), game).items()}
    finally:
        llm.restore(saved)
    return Result(name, error, scores, puns, others, casts, time.time() - started)


def report(spec: dict, base: Result, results: list[Result], pick: str | None, why: str) -> Path:
    OUT.mkdir(parents=True, exist_ok=True)
    path = OUT / f"{spec['name']}.tsv"
    with open(path, "w", encoding="utf-8", newline="") as f:
        out = csv.writer(f, delimiter="\t", lineterminator="\n")
        out.writerow(["candidate", "builds", "error", "worse", "better", "puns", "other_fakes", "casts", "seconds",
                      "verdict"])
        for r in [base, *results]:
            verdict = ("baseline" if r is base else "wins" if r.candidate == pick
                       else "survives" if survives(base, r) else "out")
            out.writerow([r.candidate, r.error is None, (r.error or "").replace("\n", " | ")[:300],
                          " ".join(worse(base, r)), " ".join(better(base, r)), r.puns, r.other_fakes, r.casts,
                          f"{r.seconds:.1f}", verdict])
    for r in results:
        state = ("does not build: " + r.error.splitlines()[0] if r.error else
                 f"{len(worse(base, r))} worse, {len(better(base, r))} better, {r.puns} puns, {r.casts} casts")
        print(f"{r.candidate}: {state} ({r.seconds:.1f} s)" + (" <- wins" if r.candidate == pick else ""))
    print(f"{spec['name']}: {pick or 'no winner'}, {why}. Report: {path}")
    return path


def run(game: Path, spec_path: Path, context: Path | None, tables: Path | None, apply: bool) -> int:
    """Search, report, and with APPLY write the winner. 0 when a candidate wins."""
    spec = load_spec(spec_path)
    in_image = llm.exe_contains()
    base = evaluate("baseline", spec, [], game, context, tables, in_image)
    if base.error:
        sys.exit(f"the tree does not build without the edits:\n{base.error}")
    results = [evaluate(c["name"], spec, c["edits"], game, context, tables, in_image) for c in spec["candidates"]]
    pick, why = winner(base, results, spec.get("prefer"))
    report(spec, base, results, pick, why)
    if pick is None:
        return 1
    if apply:
        write_edits(spec["files"], next(c["edits"] for c in spec["candidates"] if c["name"] == pick))
        print(f"wrote {pick} into the spec's files")
        return declgen.write(context, tables)
    return 0
