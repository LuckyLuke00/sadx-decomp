"""Unit tests for pairs.py: reading the neutral pair and call files, the value compare, the call alignment, the kill
switch, the site evidence, the floor, and the calls the inventory exports for it.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/pairstests.py
run() calls every check and returns the failures. All names are made up.
"""

import sys
import tempfile
from dataclasses import replace
from pathlib import Path
from types import SimpleNamespace

sys.path.insert(0, str(Path(__file__).parent))

import config  # noqa: E402
import inventory  # noqa: E402
import inventorytests  # noqa: E402
import ledger  # noqa: E402
import pairs  # noqa: E402
import score  # noqa: E402
import scoretests  # noqa: E402
import spelling  # noqa: E402
from pairs import Call, PairsError, Value  # noqa: E402

CPP = inventorytests.CPP
INT, UINT8, FLOAT, DOUBLE = (CPP.int_type("int"), CPP.builtin(("unsigned", "char")), CPP.builtin(("float",)),
                             CPP.builtin(("double",)))
PAIRS = ("target,reference\n"
         "0x00401000,0x10\n"
         "0x00402000,0x20\n"
         "0x00403000,0x30\n"
         "0x00403000,0x31\n"
         "0x00404000,0x40\n"
         "0x00405000,0x40\n")
CALLS = ("# evidence-refcalls schema=1 floats=apart\n"
         "owner,order,callee,values\n"
         "0x10,2,xxName,-1 0xff:8 1.5\n"
         "0x10,1,0x20,1 0x2 ?\n"
         "0x10,3,?,\n"
         "0x20,1,0x30,\n"
         "0x99,1,0x10,4\n")
OWNER = "0x00401000"


def load(files: dict):
    with tempfile.TemporaryDirectory() as folder:
        for name, text in files.items():
            (Path(folder) / name).write_text(text, encoding="utf-8", newline="")
        try:
            return pairs.load(Path(folder))
        except PairsError as error:
            return str(error)


def error_of(files: dict, wanted: str) -> list[str]:
    """A failure unless loading FILES fails with a message that holds WANTED."""
    found = load(files)
    if not isinstance(found, str) or wanted not in found:
        return [f"expected an error with {wanted!r}, got {found!r}"]
    return []


def check_load() -> list[str]:
    failures = []
    if load({}) != []:
        failures.append("no files must give no builds")
    found = load({"pairs-xx.csv": PAIRS, "refcalls-xx.csv": CALLS})
    if isinstance(found, str):
        return failures + [f"good files failed: {found}"]
    build = found[0]
    if (build.name, build.floats, build.pairs, build.dropped, build.unpaired) != ("xx", pairs.APART, 2, 4, 1):
        failures.append(f"build: {(build.name, build.floats, build.pairs, build.dropped, build.unpaired)}")
    calls = build.owners.get(0x00401000)
    wanted = (Call(0x00402000, (Value(1, 0, "1"), Value(2, 0, "0x2"), None)),
              Call("xxName", (Value(-1, 0, "-1"), Value(0xff, 8, "0xff:8"), Value(1.5, 0, "1.5"))),
              Call(None, ()))
    if calls != wanted:
        failures.append(f"calls of 0x00401000: {calls}")
    if build.owners.get(0x00402000) != (Call(None, ()),):
        failures.append(f"an unpaired callee must map to None: {build.owners.get(0x00402000)}")
    good = {"pairs-xx.csv": PAIRS, "refcalls-xx.csv": CALLS}
    failures += error_of({"refcalls-xx.csv": CALLS}, "pairs-xx.csv")
    failures += error_of({"pairs-xx.csv": PAIRS}, "refcalls-xx.csv")
    failures += error_of(dict(good, **{"refcalls-xx.csv": CALLS.replace("floats=apart", "floats=mixed")}),
                         "refcalls-xx.csv:1")
    failures += error_of(dict(good, **{"refcalls-xx.csv": CALLS.replace("owner,order", "owner,rank")}),
                         "refcalls-xx.csv: the columns")
    failures += error_of(dict(good, **{"pairs-xx.csv": PAIRS.replace("0x00402000", "402000")}), "pairs-xx.csv:3")
    for bad, line in (("0x10,2,", "zz,2,"), ("0x10,2,", "0x10,x,"), ("0x10,2,", "0x10,0,"), ("0x10,2,", "0x10,1,"),
                      ("xxName", "1xx"), ("-1 0xff:8", "-1 0xff:12"), ("1.5", "1.5:32"), ("1.5", "x1")):
        failures += error_of(dict(good, **{"refcalls-xx.csv": CALLS.replace(bad, line, 1)}), "refcalls-xx.csv:3")
    failures += error_of(dict(good, **{"refcalls-xx.csv": CALLS.replace("0x10,3,", "0x10,4,")}),
                         "0x10 has no call 3")
    return failures


def check_values() -> list[str]:
    failures = []
    if pairs.parse_value("?", "here") is not None:
        failures.append("? must give None")
    if pairs.parse_value("-0x10:16", "here") != Value(-16, 16, "-0x10:16"):
        failures.append(f"-0x10:16: {pairs.parse_value('-0x10:16', 'here')}")
    if pairs.parse_value("1e+06", "here") != Value(1e6, 0, "1e+06"):
        failures.append(f"1e+06: {pairs.parse_value('1e+06', 'here')}")
    cases = [(16, INT, "0x10", True), (-1, INT, "0xffffffff", True), (-1, INT, "0xff:8", True),
             (0xff, UINT8, "0x1ff", True), (2, INT, "3", False), (1.0, FLOAT, "1.0", True),
             (0.1, DOUBLE, "0.1", True), (0.5, FLOAT, "0.25", False), (1.0, FLOAT, "0x3f800000", True),
             (0.5, DOUBLE, "0x3f000000", True), (1.0, DOUBLE, "0x3ff0000000000000", True),
             (1.0, FLOAT, "0x3f800001", False), (1, INT, "1.0", True), (0, INT, "0.0", True), (2, INT, "1.5", False),
             (1e300, DOUBLE, "1e300", True), (1e300, DOUBLE, "1e299", False), (3, None, "3", True)]
    for value, ctype, text, wanted in cases:
        if pairs.same_value(value, ctype, pairs.parse_value(text, "here")) != wanted:
            failures.append(f"same_value({value!r}, {ctype.name if ctype else None}, {text}) must be {wanted}")
    return failures


def check_alignment() -> list[str]:
    failures = []
    cases = [(["a", "b", "c", "d"], ["a", "c", "b", "d"], {0: 0, 3: 3}, "a reordered call is a gap"),
             (["x", "x", "a"], ["x", "a"], {2: 1}, "a callee twice on one side does not anchor"),
             (["a", None], [None, "a"], {0: 1}, "None never pairs"),
             (["x", "x"], ["x", "x"], {0: 0, 1: 1}, "no anchor: the plain alignment"),
             (["a", "x", "b"], ["a", "y", "b"], {0: 0, 2: 2}, "an unmatched callee is a gap")]
    for source, reference, wanted, label in cases:
        found = pairs.align_calls(source, reference)
        if found != wanted:
            failures.append(f"{label}: {found}")
    return failures


def owned(target: str, line: int, values: tuple, floats: bool = False) -> inventory.OwnedCall:
    return inventory.OwnedCall(target, "src/a.c", line, 5, values, floats)


def record(line: int, value, ctype, flags=()) -> inventory.Record:
    """A coverage call site of meaning A at slot 1 of the call on LINE."""
    result = replace(scoretests.OK, value=value, ctype=ctype)
    return replace(scoretests.site(flags=flags, result=result), line=line, column=5, slot="1", owner=OWNER)


def build(calls: tuple, floats: str = pairs.IN_ORDER) -> pairs.Build:
    return pairs.Build("xx", floats, 1, 0, {0x00401000: calls}, 0)


def apply(builds: list, records: list, owned_calls: list, **thresholds) -> list:
    found = SimpleNamespace(records=records, owned_calls={OWNER: owned_calls})
    return pairs.apply(builds, found, {**config.THRESHOLDS, "yield_floor": 1, **thresholds})


def check_sites() -> list[str]:
    failures = []
    calls = (Call("xxA", (Value(1, 0, "1"), Value(2, 0, "2"))), Call("xxB", (Value(3, 0, "3"),)),
             Call("xxC", (Value(0x3f800000, 0, "0x3f800000"),)), Call("xxD", (Value(5, 0, "5"),)),
             Call("xxE", (None,)), Call("xxF", (Value(7, 0, "7"), Value(8, 0, "8"))))
    owned_calls = [owned("xxA", 1, ((1, INT), (2, INT))), owned("xxB", 2, ((3, INT),)),
                   owned("xxC", 3, ((1.0, FLOAT),), floats=True), owned("xxD", 4, ((6, INT),)),
                   owned("xxE", 5, ((9, INT),)), owned("xxF", 6, ((7, INT),))]
    records = [record(line, value, ctype) for line, value, ctype in
               ((2, 3, INT), (3, 1.0, FLOAT), (4, 6, INT), (5, 9, INT), (6, 7, INT))]
    reports = apply([build(calls)], records, owned_calls)
    found = [record.references for record in records]
    if found != [(("xx", "3", True),), (("xx", "0x3f800000", True),), (("xx", "5", False),), (), ()]:
        failures.append(f"in order, the references: {found}")
    if pairs.DIFFERS not in records[2].flags or any(pairs.DIFFERS in item.flags for item in records[:2]):
        failures.append("only the site whose value differs must get the flag")
    grade = score.grade_site(records[2])
    if grade.tier != score.A_STAR or pairs.DIFFERS not in grade.counter:
        failures.append(f"a value that differs must give A*: {grade}")
    if score.grade_site(records[0]).tier != score.A:
        failures.append("the same value must keep A")
    report = reports[0]
    if (report.live, report.slots, report.agree, report.same, report.differs, report.unknown) != (1, 5, 4, 2, 1, 2):
        failures.append(f"in order, the report: {report}")
    text = ledger.evidence(records[0], score.grade_site(records[0]), spelling.top_of(records[0].spellings))
    if "same value in build xx" not in text:
        failures.append(f"the ledger evidence must cite the build: {text}")
    text = ledger.evidence(records[2], grade, spelling.top_of(records[2].spellings))
    if "other value in build xx: 5" not in text:
        failures.append(f"the ledger evidence must cite the other value: {text}")

    records = [record(line, value, ctype) for line, value, ctype in ((2, 3, INT), (3, 1.0, FLOAT))]
    reports = apply([build(calls + (Call("xxG", (Value(1.5, 0, "1.5"),)),), pairs.APART)], records,
                    owned_calls + [owned("xxG", 7, ((1, INT),))])
    if [record.references for record in records] != [(("xx", "3", True),), ()]:
        failures.append(f"apart, a call with a float must not compare: {[r.references for r in records]}")
    if (reports[0].slots, reports[0].agree) != (4, 3):
        failures.append(f"apart, the slots: {reports[0]}")
    return failures


def check_kill_switch() -> list[str]:
    """One owner with AGREE calls that pass the same value and DIFFER calls that pass another, one argument each; the
    coverage site sits on the first call."""
    failures = []
    for agree, differ, live in ((2, 0, False), (3, 0, True), (1, 3, False), (2, 2, True), (1, 2, False)):
        calls, owned_calls = [], []
        for index in range(agree + differ):
            callee = f"xx{index}"
            calls.append(Call(callee, (Value(index, 0, str(index)),)))
            owned_calls.append(owned(callee, index + 1, ((index if index < agree else index + 100, INT),)))
        records = [record(1, 0, INT)]
        reports = apply([build(tuple(calls))], records, owned_calls)
        if bool(records[0].references) != live or reports[0].live != int(live):
            failures.append(f"{agree} same and {differ} other: live must be {live}, {reports[0]}")
        killed = reports[0].few + reports[0].low
        if killed != int(not live):
            failures.append(f"{agree} same and {differ} other: killed {killed}")
    return failures


def check_floor() -> list[str]:
    calls = tuple(Call(f"xx{index}", (Value(index, 0, str(index)),)) for index in range(3))
    owned_calls = [owned(f"xx{index}", index + 1, ((index, INT),)) for index in range(3)]
    records = [record(1, 0, INT)]
    reports = apply([build(calls)], records, owned_calls, yield_floor=2)
    if records[0].references or not reports[0].under_floor:
        return [f"a build under the floor must give no evidence: {reports[0]}"]
    return []


def check_unpaired() -> list[str]:
    """Owners that do not pair: a game owner with no reference calls, and an owner id that is no address."""
    found = SimpleNamespace(records=[], owned_calls={OWNER: [owned("xxA", 1, ((1, INT),))],
                                                     "src/c.c:other": [owned("xxA", 1, ((1, INT),))]})
    reports = pairs.apply([pairs.Build("xx", pairs.IN_ORDER, 1, 0, {0x00402000: (Call("xxA", (None,)),)}, 0)],
                          found, dict(config.THRESHOLDS))
    if (reports[0].compared, reports[0].no_calls) != (0, 1):
        return [f"a reference owner with no game calls: {reports[0]}"]
    return []


def check_inventory() -> list[str]:
    """The calls that the inventory exports for the fixture's annotated owner, then one build through the files."""
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        loaded, rows = inventorytests.repository(folder)
        found = inventory.build(loaded, rows)
        calls = found.owned_calls.get(OWNER, [])
        targets = [call.target for call in calls]
        wanted = ["xxPush"] * 3 + ["xxFlags"] * 3 + ["xxMode"] * 3 + ["xxUnmapped", "xxUnmapped", "xxCount"]
        if targets != wanted:
            return [f"owned calls: {targets}"]
        values = [tuple(None if item is None else item[0] for item in call.values) for call in calls]
        if values[:7] != [(0,), (0,), (None,), (5,), (3,), (0,), (1, None)] or values[9] != (5,):
            failures.append(f"owned values: {values}")
        if any(call.floats for call in calls):
            failures.append("no fixture call has a float")
        if [call.target for call in found.owned_calls.get("src/c.c:other", [])] != ["xxFlags"]:
            failures.append(f"an unannotated owner keeps its fallback id: {sorted(found.owned_calls)}")
        evidence = Path(folder) / "evidence"
        (evidence / "pairs-xx.csv").write_text("target,reference\n0x00401000,0x10\n", encoding="utf-8")
        (evidence / "refcalls-xx.csv").write_text(
            "# evidence-refcalls schema=1 floats=in-order\nowner,order,callee,values\n"
            "0x10,1,xxPush,0\n0x10,2,xxPush,0\n0x10,3,xxPush,?\n0x10,4,xxFlags,5\n0x10,5,xxFlags,3\n"
            "0x10,6,xxFlags,0\n", encoding="utf-8")
        reports = pairs.apply(pairs.load(evidence), found, dict(loaded.thresholds, yield_floor=1))
        held = {(record.line, record.slot): record.references for record in found.records if record.references}
        if held.get((10, "1")) != (("xx", "3", True),) or reports[0].live != 1:
            failures.append(f"through the files: {held}, {reports[0]}")
    return failures


def run() -> list[str]:
    failures = []
    for check in (check_load, check_values, check_alignment, check_sites, check_kill_switch, check_floor,
                  check_unpaired, check_inventory):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    for failure in found:
        print(failure)
    if not found:
        print("pairstests: all passed")
    sys.exit(1 if found else 0)
