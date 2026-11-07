"""Unit tests for gate.py: the brake, each report section on the inventory, corpus and manual fixtures, and the
hand-owned file faults. A whole run is in pipelinetests.py.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/gatetests.py
run() calls every check and returns the failures. All names are made up.
"""

import sys
import tempfile
from collections import Counter
from dataclasses import replace
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import baseline  # noqa: E402
import ceval  # noqa: E402
import config  # noqa: E402
import corpus  # noqa: E402
import corpustests  # noqa: E402
import gate  # noqa: E402
import inventory  # noqa: E402
import inventorytests  # noqa: E402
import manualtests  # noqa: E402
import pairs  # noqa: E402
import score  # noqa: E402
import scoretests  # noqa: E402

EXPECTED = ("set,umbrella,name\ngame,vendor.h,XXF_A\ngame,vendor.h,xxPush\ngame,vendor.h,XX_T\ngame,vendor.h,xxMacro\n"
            "game,vendor.h,XX_MISSING\ngame,other.h,XX_ELSE\nref,vendor.h,XX_REF\n")
EMPTY = corpus.Corpus([], {}, config.THRESHOLDS)  # no sample tree
PROBES = "module,sites,floor,verdict,date,method,note\nxxmod,3,20,under the floor: skipped,2026-01-01,a count,\n"


def probe_rows(folder: str, text: str | None = PROBES):
    """The probes.csv rows of TEXT, or the fault, as a str; None: no file."""
    path = Path(folder) / gate.PROBES
    if text is not None:
        path.write_text(text, encoding="utf-8")
    try:
        return gate.read_probes(path)
    except gate.GateError as error:
        return str(error)


def expected_rows() -> list:
    return [tuple(line.split(",")) for line in EXPECTED.splitlines()[1:]]


def section(text: str, title: str) -> list:
    """The lines of one ## section of TEXT."""
    lines = text.split("\n")
    start = lines.index(f"## {title}") + 1
    end = next((index for index in range(start, len(lines)) if lines[index].startswith("## ")), len(lines))
    return [line for line in lines[start:end] if line]


def check_brake() -> list[str]:
    """One brake per kind, on the sites of that kind only: over the limit fires, at it does not, no coverage never."""
    failures = []
    unresolved = ceval.failure(ceval.UNRESOLVED, "unknown identifier", "XX_X")
    nonconstant = ceval.failure(ceval.NONCONSTANT, "variable", "m")
    held = replace(scoretests.site(), kind=inventory.PLACEHOLDER)
    for records, limit, given in (
            ([scoretests.site(result=unresolved)] + [scoretests.site()] * 2 + [held] * 3, 0.30,
             {inventory.CALL: (3, 1, True), inventory.PLACEHOLDER: (3, 0, False)}),
            ([scoretests.site(result=unresolved)] + [scoretests.site()] * 3, 0.25, {inventory.CALL: (4, 1, False)}),
            ([scoretests.site(result=nonconstant)], 0.30, {})):
        wanted = [(kind, *given.get(kind, (0, 0, False))) for kind in inventory.KINDS]
        found = [(stop.kind, stop.coverage, stop.stopped, stop.fired) for stop in gate.brakes(records, limit)]
        if found != wanted:
            failures.append(f"brakes {found}, wanted {wanted}")
    return failures


def brake_rows(text: str) -> list:
    """The kind rows of the brake table in TEXT."""
    return [line for line in section(text, "Brake") if line.startswith("| ") and not line.startswith("| kind ")]


def check_report() -> list[str]:
    """Each section on the inventory fixture, with the corpus and manual fixtures; the coverage split sums to its
    totals."""
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        loaded, rows = inventorytests.repository(folder)
        found, made = inventorytests.committed(loaded, rows)
    with tempfile.TemporaryDirectory() as folder:
        samples = corpustests.read_fixture(folder)
        probes = probe_rows(folder)
    ranked = score.review_order(found.records, made.rows)
    mapped = {"xxPush", "xxFlags", "xxMode", "xxCount", "xxMacro"}
    entries = [baseline.Entry("old", baseline.SAME, None, None)] * 2
    text, stop = gate.report(found, 7, config.THRESHOLDS, expected_rows(), probes, mapped, entries, samples,
                             [manualtests.parse()], ranked, (["x.txt:1:word"], 0.5))
    if not text.startswith("# Evidence gate, generation 7\n\n" + score.NOTE):
        failures.append("the title and the phase-1 note come first")
    if section(text, "Brake") != ["- brake at 30% of the coverage sites of each kind: unresolved plus unevaluated",
                                  "| kind | coverage sites | change | unresolved plus unevaluated | verdict |",
                                  "|---|---|---|---|---|", "| call | 10 | first run | 2 (20.0%) | not fired |"]:
        failures.append(f"brake section {section(text, 'Brake')}")
    split = section(text, "Coverage split")
    wanted = ["### call", "- coverage sites: 10", "- resolved: 8", "  - A: 7", "    - A vendor: 7", "  - B: 1",
              "    - B prototype check failed: 1", "  - searches that ran out of budget: 0", "- unresolved: 1",
              "  - unknown identifier: 1", "- unevaluated: 1", "  - arity: 1"]
    if split != wanted:
        failures.append(f"coverage split {split}")
    numbers = {line: int(line.rsplit(": ", 1)[1]) for line in split[1:]}
    tiers = sum(value for line, value in numbers.items() if line.startswith("  - ") and "budget" not in line
                and line.split(":")[0][4:] in score.ORDER)
    if tiers != numbers["- resolved: 8"] or numbers["- resolved: 8"] + 2 != numbers["- coverage sites: 10"]:
        failures.append("the tiers sum to the resolved sites, and resolved, unresolved and unevaluated to coverage")
    outside = section(text, "Out of coverage")
    for line in (f"- unmapped calls: {found.unmapped}", "- function-like macro callees: 1", "- nonconstant arguments: 1",
                 "  - variable: 1", "- unsupported files: 1"):
        if line not in outside:
            failures.append(f"out of coverage lacks {line!r}: {outside}")
    if section(text, "Field spots")[0] != "- no fieldmap: no spot is a field site":
        failures.append(f"field spots {section(text, 'Field spots')}")
    if section(text, "Skipped modules") != ["| module | sites | floor | verdict | date | method | note |",
                                            "|---|---|---|---|---|---|---|",
                                            "| xxmod | 3 | 20 | under the floor: skipped | 2026-01-01 | a count |  |"]:
        failures.append(f"skipped modules {section(text, 'Skipped modules')}")
    if section(text, "Top unresolved identifiers")[0] != "- sites: XX_UNKNOWN 1":
        failures.append(f"top unresolved {section(text, 'Top unresolved identifiers')}")
    umbrellas = section(text, "Umbrellas")
    if not umbrellas[2].startswith("| game | vendor.h | 1 | 0 | 0 | 0 | 0 | XX_MISSING |"):
        failures.append(f"umbrella row: only the name that is not defined is listed: {umbrellas[2]}")
    if umbrellas[-1] != "expected-names.csv names umbrellas that config.json lacks: game other.h, ref vendor.h":
        failures.append(f"unknown umbrella {umbrellas[-1]}")
    if section(text, "And-mask slots") != ["- sites 0, with an inverted candidate 0, with no candidate 0"]:
        failures.append(f"and-mask {section(text, 'And-mask slots')}")
    spelled = section(text, "Spelling")
    if spelled[:4] != ["### Top candidates", "| meaning | A | B | C | none |", "|---|---|---|---|---|",
                       "### Eligibility"]:
        failures.append(f"the top spelling table has no row with no spelling: {spelled[:4]}")
    for line in ("- call: yes 0, no 0, no sample 10", "| xxPush | 0 | 0 | 2 |", "| old | 6 | 6 | 3 | 13 | 2 | 3 | 4 |",
                 "| new | 4 | 4 | 4 | 19 | 0 | 7 | 0 |", "- argmap callees with an observation: 4 of 5",
                 "- old left out, arity differs: 1 (xxWide#1)", "- old left out, no prototype: 1 (xxGone#1)",
                 "| pairs | 0.0 | 0.1 | 0.2 | 0.3 | 0.4 | 0.5 (cut) | 0.6 | 0.7 | 0.8 | 0.9 |",
                 "| same path | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |",
                 "| other path | 2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |",
                 "| xx.txt | 5 | 3 | 3 | no prototype 1, unknown function 1 | xxUnknown 1 |"):
        if line not in spelled:
            failures.append(f"the spelling section lacks {line!r}")
    failed = next((line for line in spelled if line.startswith("- old failed: ")), "")
    if not failed.startswith("- old failed: f/bad.c: does not decode as cp932") or "g/tri.c: trigraph" not in failed:
        failures.append(f"failed sample files {failed!r}")
    if section(text, "Baseline diff") != ["- old same: 2"]:
        failures.append(f"baseline diff {section(text, 'Baseline diff')}")
    times = section(text, "Times")
    if not times[0].startswith("- inventory: closures") or not times[-2].startswith("- sample corpus: ") or (
            times[-1] != "- audit: 0.5 s, 1 hits (x.txt:1:word)"):
        failures.append(f"times {times}")
    found.previous = Counter({inventory.CALL: 12, inventory.PLACEHOLDER: 5})
    bare, fired = gate.report(found, 7, dict(config.THRESHOLDS, gate_brake=0.1), [], [], mapped, None, EMPTY, [],
                              ranked, ([], 0.0))
    if any(item.fired for item in stop) or not any(item.fired for item in fired):
        failures.append("the brake fires only over the limit")
    if brake_rows(bare) != ["| call | 10 | previous run 12, change -2 | 2 (20.0%) | FIRED: fix the model before "
                            "anything else |", "| placeholder | 0 | previous run 5, change -5 | 0 (0.0%) | not fired |"]:
        failures.append(f"a kind of the previous run stays in the table: {brake_rows(bare)}")
    if bare.count("- none configured") != 2 or section(bare, "Skipped modules") != ["- none recorded"]:
        failures.append("with no sample tree, no manual and no probe, the three tables say so")
    return failures


def check_fields() -> list[str]:
    """The field spots by what became of them sum to the spots; a field site with a nonconstant value counts there,
    not as a nonconstant argument; the field kind has its brake row."""
    failures = []
    files = dict(inventorytests.FIELD_FILES, **{"src/e.c": inventorytests.E_C.replace(
        "    op->other = 1;\n", "    op->other = 1;\n    op->flags = op->child->flags;\n")})
    with tempfile.TemporaryDirectory() as folder:
        found = inventorytests.fielded(folder, files, inventorytests.FIELDMAP)
    text, _ = gate.report(found, 1, config.THRESHOLDS, [], [], set(), None, EMPTY, [], [], ([], 0.0))
    wanted = ["- fieldmap rows: 4", "- field spots: 11", "  - field sites: 9 (in coverage 8, nonconstant value 1)",
              "  - scope sites (no fieldmap row, in a function with scope constants): 0",
              "  - member with no fieldmap row: 1", "  - base type unknown: 0", "  - bitfield: 1",
              "- case labels: 1 (sites only in a function with scope constants), raw-offset accesses: 1 (counted only)"]
    if section(text, "Field spots") != wanted:
        failures.append(f"field spots {section(text, 'Field spots')}")
    calls = sum(1 for record in found.records if record.kind == inventory.CALL and not record.covered)
    if f"- nonconstant arguments: {calls}" not in section(text, "Out of coverage"):
        failures.append(f"nonconstant arguments, wanted {calls}: {section(text, 'Out of coverage')}")
    if "| field | 8 | first run | 0 (0.0%) | not fired |" not in brake_rows(text):
        failures.append(f"brake rows {brake_rows(text)}")
    return failures


def check_symbols() -> list[str]:
    """The reference symbols section: the rows per symbol file, the sites per kind and the flags; a scope field site
    counts apart from the field sites; each new kind has its brake row. With no symbol files, the section says so."""
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        found = inventory.build(*inventorytests.referenced(folder))
    text, _ = gate.report(found, 1, config.THRESHOLDS, [], [], set(), None, EMPTY, [], [], ([], 0.0))
    wanted = ["- prototypes.csv: functions 2", "- enums.csv: enums 1, enumerators 3",
              "- scope-constants.csv: constants 4, functions 1", "- sites: 9 (in coverage 9, nonconstant value 0)",
              "  - call: 1", "  - field: 1", "  - case: 1", "  - variable: 5", "  - return: 1",
              "- flags: one enumerator 2, lvalue check 4"]
    if section(text, "Reference symbols") != wanted:
        failures.append(f"reference symbols {section(text, 'Reference symbols')}")
    spots = section(text, "Field spots")
    if spots[:4] != ["- no fieldmap: no spot is a field site", "- field spots: 12",
                     "  - field sites: 0 (in coverage 0, nonconstant value 0)",
                     "  - scope sites (no fieldmap row, in a function with scope constants): 1"]:
        failures.append(f"field spots {spots}")
    for row in ("| case | 1 | first run | 0 (0.0%) | not fired |", "| variable | 5 | first run | 0 (0.0%) | not fired |",
                "| return | 1 | first run | 0 (0.0%) | not fired |"):
        if row not in brake_rows(text):
            failures.append(f"brake rows lack {row!r}: {brake_rows(text)}")
    with tempfile.TemporaryDirectory() as folder:
        plain = inventorytests.fielded(folder, inventorytests.FIELD_FILES, inventorytests.FIELDMAP)
    text, _ = gate.report(plain, 1, config.THRESHOLDS, [], [], set(), None, EMPTY, [], [], ([], 0.0))
    if section(text, "Reference symbols") != ["- no symbol files: no reference sites"]:
        failures.append(f"no symbol files {section(text, 'Reference symbols')}")
    return failures


def check_references() -> list[str]:
    """The reference calls section: a table row per build with its verdict, then the sites whose value another build
    passes otherwise, with each build's value. With no reference call files, the section says so."""
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        found = inventory.build(*inventorytests.referenced(folder))
    text, _ = gate.report(found, 1, config.THRESHOLDS, [], [], set(), None, EMPTY, [], [], ([], 0.0))
    if section(text, "Reference calls") != ["- no reference call files: no reference evidence"]:
        failures.append(f"no reference call files {section(text, 'Reference calls')}")
    site = next(record for record in found.records if record.kind == inventory.CALL and record.covered)
    site.id, site.references = "S000001", (("xx", "5", False), ("yy", "0x1", True))
    site.flags.append(pairs.DIFFERS)
    found.references = [pairs.Report("xx", pairs.IN_ORDER, 4, 1, 2, 3, 1, 0, 1, 0, 2, 8, 7, 3, 1, 2),
                        pairs.Report("yy", pairs.APART, 2, 0, 0, 1, 0, 0, 0, 0, 1, 3, 3, 1, 0, 0),
                        pairs.Report("zz", pairs.APART, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, True)]
    text, _ = gate.report(found, 1, config.THRESHOLDS, [], [], set(), None, EMPTY, [], [], ([], 0.0))
    rows = section(text, "Reference calls")
    wanted = ["| xx | in-order | 4 | 1 | 2 | 3 | 1 | 0 | 1/0 | 2 | 7/8 | 3/1/2 | used |",
              "| yy | apart | 2 | 0 | 0 | 1 | 0 | 0 | 0/0 | 1 | 3/3 | 1/0/0 | used |",
              "| zz | apart | 1 | 0 | 0 | 1 | 0 | 1 | 0/0 | 0 | 0/0 | 0/0/0 | under the floor: no evidence |",
              "- sites with the flag value differs across builds: 1",
              f"  - S000001 {site.file}:{site.line} {site.callee} slot {site.slot}: {site.value} (xx 5, yy same)"]
    if rows[2:] != wanted:
        failures.append(f"reference calls {rows}")
    return failures


def check_kinds() -> list[str]:
    """A kind new in this run has its first run now; each kind has its own coverage split and eligibility counts."""
    failures = []
    settings = dict(inventorytests.CONFIG, placeholders={"XX_ASSERT": "no-code", "XX_GUESS": "code"})
    files = dict(inventorytests.FILES, **{"src/d.c": inventorytests.D_C})
    with tempfile.TemporaryDirectory() as folder:
        loaded, rows = inventorytests.repository(folder, files, settings)
        found, made = inventorytests.committed(loaded, rows)
    found.previous = Counter({inventory.CALL: 8})
    ranked = score.review_order(found.records, made.rows)
    text, _ = gate.report(found, 7, config.THRESHOLDS, [], [], set(), None, EMPTY, [], ranked, ([], 0.0))
    if brake_rows(text) != ["| call | 10 | previous run 8, change +2 | 2 (20.0%) | not fired |",
                            "| placeholder | 3 | first run | 0 (0.0%) | not fired |"]:
        failures.append(f"brake rows {brake_rows(text)}")
    split = section(text, "Coverage split")
    held = split[split.index("### placeholder"):]
    if held != ["### placeholder", "- coverage sites: 3", "- resolved: 3", "  - placeholder: 3",
                "  - searches that ran out of budget: 0", "- unresolved: 0", "- unevaluated: 0"]:
        failures.append(f"placeholder split {held}")
    for line in ("- call: yes 0, no 0, no sample 10", "- placeholder: yes 0, no 3, no sample 0"):
        if line not in section(text, "Spelling"):
            failures.append(f"the eligibility per kind lacks {line!r}")
    return failures


def check_inputs() -> list[str]:
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder) / gate.EXPECTED
        for text, wanted in ((None, "missing hand-owned file"),
                             ("umbrella,name\nx.h,XX\n", "the columns must be set,umbrella,name")):
            if text is not None:
                path.write_text(text, encoding="utf-8")
            try:
                gate.read_expected(path)
                failures.append(f"no fault for {text!r}")
            except gate.GateError as error:
                if wanted not in str(error):
                    failures.append(f"fault {error}, wanted {wanted!r}")
        if probe_rows(folder, None) != []:
            failures.append("a missing probes.csv gives no rows")
        if [row["module"] for row in probe_rows(folder)] != ["xxmod"]:
            failures.append(f"probes.csv rows {probe_rows(folder)}")
        bad = probe_rows(folder, "module\nx\n")
        if "the columns must be module,sites,floor,verdict,date,method,note" not in bad:
            failures.append(f"probes.csv columns: {bad}")
    for umbrella, wanted, result in (("D:/xx/inc/vendor.h", "vendor.h", True), ("D:\\xx\\inc\\vendor.h", "inc/vendor.h",
                                                                               True), ("myvendor.h", "vendor.h", False)):
        if gate.matches(umbrella, wanted) != result:
            failures.append(f"matches({umbrella!r}, {wanted!r}) is not {result}")
    return failures


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_brake, check_report, check_fields, check_symbols, check_references, check_kinds,
                  check_inputs):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    print("\n".join(found) or "gatetests: all passed")
    sys.exit(1 if found else 0)
