"""Unit tests for remap.py, site identity across runs.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/remaptests.py
run() calls every check and returns the failures. All names are made up.
"""

import math
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import remap  # noqa: E402
from remap import EXACT, REWRITE, TARGET, TARGET_AND_REWRITE, Site  # noqa: E402

OWNER = "0x00401000"


def site(expression: str, value: str = "0", target: str = "f", slot: str = "1", owner: str = OWNER,
         context: str = "", **extra) -> Site:
    return Site(owner, "call", target, slot, expression, value, context, **extra)


def numbered(sites: list) -> list:
    """The sites with ids S000001, S000002 and on, as a last run gives them."""
    return [Site(**{**vars(item), "id": remap.format_id(number)}) for number, item in enumerate(sites, 1)]


def expect(failures: list, name: str, result: remap.Remap, ids: list, kinds: list | None = None,
           gone: list | None = None, ambiguous: list | None = None) -> None:
    got = (result.ids, result.kinds if kinds is not None else None, sorted(result.gone) if gone is not None else None,
           sorted(result.ambiguous) if ambiguous is not None else None)
    want = (ids, kinds, sorted(gone) if gone is not None else None, sorted(ambiguous) if ambiguous is not None else None)
    if got != want:
        failures.append(f"{name}: got {got}, want {want}")


def check_kept_ids() -> list[str]:
    failures = []
    old = numbered([site("0"), site("1", "1", target="g")])
    moved = [site("0", file="b.c", line=90), site("1", "1", target="g", file="b.c", line=91)]
    expect(failures, "a moved owner", remap.remap(old, moved), ["S000001", "S000002"], [EXACT, EXACT], [], [])
    old = numbered([site("0", target="FUN_00401234")])
    expect(failures, "a target change", remap.remap(old, [site("0", target="njPushMatrix")]), ["S000001"], [TARGET])
    expect(failures, "a literal to a name", remap.remap(numbered([site("0")]), [site("NULL")]), ["S000001"],
           [REWRITE])
    expect(failures, "a literal to two flags", remap.remap(numbered([site("0x30", "48")]), [site("A | B", "48")]),
           ["S000001"], [REWRITE])
    old = numbered([site("1 << 31", "-2147483648")])
    expect(failures, "a value fix", remap.remap(old, [site("1 << 31", "2147483648")]), ["S000001"], [EXACT])
    old = numbered([site("0"), site("0")])
    expect(failures, "twins in order", remap.remap(old, [site("0"), site("0")]), ["S000001", "S000002"])
    old = numbered([site("OLD_NAME", "5")])
    expect(failures, "the stored value when the old text no longer evaluates",
           remap.remap(old, [site("5", "5")], revalue=lambda item: ""), ["S000001"], [REWRITE])
    expect(failures, "the current value wins over the stored one",
           remap.remap(old, [site("5", "5")], revalue=lambda item: "6"), [""], gone=["S000001"])
    return failures


def check_new_ids() -> list[str]:
    failures = []
    expect(failures, "a value edit", remap.remap(numbered([site("1", "1")]), [site("0")]), [""], gone=["S000001"])
    old = numbered([site("0", owner="a.c:foo")])
    expect(failures, "an unannotated move", remap.remap(old, [site("0", owner="b.c:foo")]), [""], gone=["S000001"])
    old = numbered([site("1", "1"), site("2", "2", target="g")])
    expect(failures, "no pair is better than a bad pair",
           remap.remap(old, [site("3", "3"), site("4", "4", target="g")]), ["", ""], gone=["S000001", "S000002"])
    old = numbered([site("1", "1", target="a"), site("2", "2", target="b"), site("3", "3", target="c")])
    new = [site("7", "7", target="x"), site("1", "1", target="a"), site("8", "8", target="y"),
           site("3", "3", target="c")]
    expect(failures, "alternating inserts and deletes", remap.remap(old, new), ["", "S000001", "", "S000003"],
           gone=["S000002"], ambiguous=[])
    old = numbered([site("0", target="FUN_00401234"), site("0", target="FUN_00401234")])
    expect(failures, "a target change that is not unique",
           remap.remap(old, [site("0", target="njPushMatrix"), site("0", target="njPushMatrix")]), ["", ""],
           gone=["S000001", "S000002"])
    # A reverted edit: the last run holds only f(1), so f(0) is new again.
    expect(failures, "a reverted edit", remap.remap(numbered([site("1", "1")]), [site("0")]), [""], gone=["S000001"])
    return failures


def check_ties() -> list[str]:
    failures = []
    old = numbered([site("0"), site("0")])
    expect(failures, "a value edit among twins", remap.remap(old, [site("1", "1"), site("0")]), ["", ""], gone=[],
           ambiguous=["S000001", "S000002"])
    old = numbered([site("0"), site("0"), site("0")])
    expect(failures, "a deletion among twins", remap.remap(old, [site("0"), site("0")]), ["", ""], gone=[],
           ambiguous=["S000001", "S000002", "S000003"])
    old = numbered([site("0"), site("0", target="a"), site("0")])
    new = [site("0"), site("0"), site("0", target="a"), site("0")]
    expect(failures, "an insert next to one twin", remap.remap(old, new), ["", "", "S000002", "S000003"],
           ambiguous=["S000001"])
    old = numbered([site("0")])
    expect(failures, "a tie with different payloads", remap.remap(old, [site("A"), site("B")]), ["", ""],
           ambiguous=["S000001"])
    old = numbered([site("0"), site("FOO")])
    swapped = remap.remap(old, [site("FOO"), site("0")])
    if sum(1 for kept in swapped.ids if kept) > 1:
        failures.append(f"a swap kept more than one id: {swapped.ids}")
    # The regression: `setup(); f(0);`, then a new f(0) before the old one. The inserted call inherits the old
    # context key, so the context ranks it first, but it never gets the old id.
    old = numbered([site("", "", target="setup", slot="", context="c0"), site("0", context="c1")])
    new = [site("", "", target="setup", slot="", context="c0"), site("0", context="c1"), site("0", context="c2")]
    result = remap.remap(old, new)
    expect(failures, "an insert before the old call", result, ["S000001", "", ""], ambiguous=["S000002"])
    if result.suggestions != [("S000002", 1), ("S000002", 2)]:
        failures.append(f"suggestions {result.suggestions}")
    return failures


def check_second_pass() -> list[str]:
    failures = []
    old = numbered([site("0", target="FUN_00401234")])
    expect(failures, "a target and rewrite", remap.remap(old, [site("NULL", target="njPushMatrix")]), ["S000001"],
           [TARGET_AND_REWRITE])
    old = numbered([site("0", target="FUN_00401234"), site("0", target="FUN_00405678")])
    new = [site("NULL", target="njPushMatrix"), site("NULL", target="njPopMatrix")]
    expect(failures, "two rows with one slot and value", remap.remap(old, new), ["", ""],
           gone=["S000001", "S000002"])
    return failures


def check_counts() -> list[str]:
    """The shared-pairing check counts the optimal paths with exact integers."""
    failures = []
    old, new = [site("0")] * 200, [site("0")] * 400
    found = remap.align(old, new, lambda i, j: 10)
    if found.count != math.comb(400, 200) or found.shared or len(found.disputed_old) != 200:
        failures.append(f"200 twins against 400: count {found.count}, shared {len(found.shared)}")
    found = remap.align(old, old, lambda i, j: 10)
    if found.count != 1 or found.shared != {i: i for i in range(200)}:
        failures.append(f"200 twins against themselves: count {found.count}, shared {len(found.shared)}")
    return failures


def check_ids() -> list[str]:
    failures = []
    if remap.mint(2, 7) != (["S000008", "S000009"], 9):
        failures.append(f"mint gave {remap.mint(2, 7)}")
    if remap.id_number("S000042") != 42:
        failures.append("id_number")
    for bad in ("X000001", "S00001a", "S"):
        try:
            remap.id_number(bad)
            failures.append(f"id_number took {bad!r}")
        except ValueError:
            pass
    return failures


def run() -> list[str]:
    failures = []
    for check in (check_kept_ids, check_new_ids, check_ties, check_second_pass, check_counts, check_ids):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    for failure in found:
        print(failure)
    if not found:
        print("remaptests: all passed")
    sys.exit(1 if found else 0)
