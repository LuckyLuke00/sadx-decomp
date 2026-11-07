"""Unit tests for covers.py: the cover search, with its multi-bit composites.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/coverstests.py
run() calls every check and returns the failures. All names are made up, apart from the generic NULL, TRUE and BOOL.
"""

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import covers  # noqa: E402
import profiles  # noqa: E402
from covers import BOOLEAN, INTEGER, POINTER, Name, Slot  # noqa: E402

FLAGS = [Name(f"XX_F{bit}", 1 << bit, False, ("vendor",)) for bit in range(8)]
GROUP = FLAGS + [Name("XX_NONE", 0, False), Name("XX_LOW", 0x3, False), Name("XX_ALSO_F1", 0x2, False, ("other",)),
                 Name("XX_SIGN", -0x80000000, False)]
WIDE = FLAGS + [Name("XX_NONE", 0, False), Name("XX_LOW", 0x3, False), Name("XX_MID", 0xC, False),
                Name("XX_WIDE", 0x6, False)]
MASKS = [Name("XX_HI_MASK", 0xE0000000, False), Name("XX_MD_MASK", 0x1C000000, False)]


def texts(value: int, slot: Slot, names=GROUP, budget: int = 100, terms: int = 4) -> list[str]:
    return [candidate.text for candidate in covers.search(value, slot, names, budget, terms).candidates]


def check_search() -> list[str]:
    failures = []
    flags, mask, plain = Slot(INTEGER, "flags", 32), Slot(INTEGER, "and-mask", 32), Slot(INTEGER, "value", 32)
    cases = (
        ("an uncapped 6-flag split", 0x3F, flags, ["XX_F0 | XX_ALSO_F1 | XX_F2 | XX_F3 | XX_F4 | XX_F5"]),
        ("exact before a split", 0x3, flags, ["XX_LOW", "XX_F0 | XX_ALSO_F1"]),
        ("a value slot takes no split", 0x5, plain, []),
        ("a bit with no name", 0x101, flags, []),
        ("a zero name", 0, flags, ["XX_NONE"]),
        ("no zero name", 0, flags, []),
        ("an inverted mask", ~0x5 & 0xFFFFFFFF, mask, ["~(XX_F0 | XX_F2)"]),
        ("one inverted name before the split", ~0x3 & 0xFFFFFFFF, mask, ["~XX_LOW", "~(XX_F0 | XX_ALSO_F1)"]),
        ("five inverted flags are too many", ~0x1F & 0xFFFFFFFF, mask, []),  # FLAGS only: no composite
        ("no inverted mask at a flags slot", ~0x5 & 0xFFFFFFFF, flags, []),
        ("a signed slot value and a signed name", -0x80000000, flags, ["XX_SIGN"]),
    )
    for name, value, slot, wanted in cases:
        names = {"no zero name": [entry for entry in GROUP if entry.name != "XX_NONE"],
                 "five inverted flags are too many": FLAGS}.get(name, GROUP)
        got = texts(value, slot, names)
        if got != wanted:
            failures.append(f"{name}: got {got}, want {wanted}")
    node = covers.search(0x2, flags, GROUP, 100, 4).candidates[0].terms[0]
    if [(alias.name, alias.origins) for alias in node.aliases] != [("XX_ALSO_F1", ("other",)), ("XX_F1", ("vendor",))]:
        failures.append(f"an alias node keeps every alias with its origins: {node}")
    if texts(0x3, flags, list(reversed(GROUP))) != texts(0x3, flags):
        failures.append("the rank depends on the input order")
    return failures


def check_budget() -> list[str]:
    failures = []
    flags = Slot(INTEGER, "flags", 32)
    found = covers.search(0x3, flags, GROUP, 0, 4)
    if found.candidates or not found.incomplete:
        failures.append(f"a budget of 0: {found}")
    found = covers.search(0x3, flags, GROUP, 2, 4)
    if [candidate.text for candidate in found.candidates] != ["XX_LOW"] or not found.incomplete:
        failures.append(f"incomplete with cover: {found}")
    found = covers.search(0x3, flags, FLAGS, 3, 4)  # no multi-bit name: the composite walk costs no step
    if len(found.candidates) != 1 or found.incomplete or found.steps != 3:
        failures.append(f"a budget that fits: {found}")
    found = covers.search(0x7, flags, WIDE, 10, 4)  # exact 1, composite walk 7, split 3
    if [candidate.text for candidate in found.candidates] != ["XX_F0 | XX_WIDE", "XX_LOW | XX_F2"] \
            or not found.incomplete:
        failures.append(f"the composites stay when the budget ends in the split: {found}")
    found = covers.search(0x7, flags, WIDE, 11, 4)
    if len(found.candidates) != 3 or found.incomplete or found.steps != 11:
        failures.append(f"a budget that fits the composite walk: {found}")
    if covers.search(0x3, Slot(INTEGER, "flags", 32, variadic=True), GROUP, 100, 4).candidates:
        failures.append("a variadic argument got candidates")
    return failures


def check_gates() -> list[str]:
    failures = []
    names = [Name("NULL", 0, False), Name("FALSE", 0, False), Name("TRUE", 1, False), Name("XX_ONE", 1, False),
             Name("XX_PTR", 0, True)]
    cases = (
        (POINTER, 0, ["NULL"]),  # XX_PTR shares the node; NULL sorts first
        (BOOLEAN, 0, ["FALSE"]),
        (BOOLEAN, 1, ["TRUE"]),  # TRUE and XX_ONE share one node
        (INTEGER, 1, ["XX_ONE"]),
        (INTEGER, 0, []),
    )
    for kind, value, wanted in cases:
        got = texts(value, Slot(kind, "value", 32), names)
        if got != wanted:
            failures.append(f"{kind} slot, value {value}: got {got}, want {wanted}")
    aliases = covers.search(0, Slot(POINTER, "value", 32), names, 10, 4).candidates[0].terms[0].aliases
    if [alias.name for alias in aliases] != ["NULL", "XX_PTR"]:
        failures.append(f"pointer aliases {aliases}")
    profile = profiles.get("msvc-vc10-x86-cpp")
    int_type, pointer = profile.int_type("int"), profile.pointer()
    kinds = [covers.slot_kind("BOOL", int_type, profile.boolean_names), covers.slot_kind("Int", int_type, ()),
             covers.slot_kind("void *", pointer, ()), covers.slot_kind("Float", None, ())]
    if kinds != [BOOLEAN, INTEGER, POINTER, None]:
        failures.append(f"slot kinds {kinds}")
    return failures


def check_composites() -> list[str]:
    """Covers by 2 to TERMS bit-disjoint names, one of them multi-bit: after the exact name, before the split, fewer
    names first, then the names in order. Overlapping names never pair, and a zero name is no term."""
    flags, mask, plain = Slot(INTEGER, "flags", 32), Slot(INTEGER, "and-mask", 32), Slot(INTEGER, "value", 32)
    split = "XX_F0 | XX_F1 | XX_F2 | XX_F3 | XX_F4"
    four = ["XX_LOW | XX_MID | XX_F4", "XX_F0 | XX_F1 | XX_MID | XX_F4", "XX_F0 | XX_WIDE | XX_F3 | XX_F4",
            "XX_LOW | XX_F2 | XX_F3 | XX_F4"]
    cases = (
        ("four names at most", 0x1F, flags, WIDE, 4, four + [split]),
        ("three names at most", 0x1F, flags, WIDE, 3, four[:1] + [split]),
        ("two names at most", 0x1F, flags, WIDE, 2, [split]),
        ("a value slot takes no composite", 0x7, plain, WIDE, 4, []),
        ("two multi-bit names, inverted", 0x03FFFFFF, mask, MASKS, 4, ["~(XX_MD_MASK | XX_HI_MASK)"]),
        ("the inverted cap counts names, not bits", ~0x1F & 0xFFFFFFFF, mask, WIDE, 4,
         [f"~({cover})" for cover in four]),
    )
    failures = []
    for name, value, slot, names, terms, wanted in cases:
        got = texts(value, slot, names, terms=terms)
        if got != wanted:
            failures.append(f"{name}: got {got}, want {wanted}")
    return failures


def run() -> list[str]:
    failures = []
    for check in (check_search, check_budget, check_gates, check_composites):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    for failure in found:
        print(failure)
    if not found:
        print("coverstests: all passed")
    sys.exit(1 if found else 0)
