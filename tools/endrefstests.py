"""Tests of tools/endrefs.py: which operands just past an array's end, or one element before its start, the compare
names after the array on both sides.

run() returns the failures as "<case> gives <found>, not <wanted>". Each check builds a small reccmp database by hand,
with the code of one function on each side, and compares it with reccmp's FunctionComparator.
"""

import struct
from unittest import mock

from reccmp.compare.db import EntityDb
from reccmp.compare.functions import FunctionComparator
from reccmp.cvdump.cvinfo import CvdumpTypeKey
from reccmp.cvdump.types import TypeInfo
from reccmp.types import EntityType, ImageId

import endrefs

ORIG_CODE, RECOMP_CODE = 0x00401000, 0x00501000  # the function on each side
LIST, OTHER = 0x00600000, 0x00600100  # two int[6] arrays in the game
OURS = 0x00700000  # where our build puts the arrays: LIST at OURS, OTHER at OURS + 0x100
INT6, INT = CvdumpTypeKey(0x1000), CvdumpTypeKey(0x74)
TYPES = {INT6: TypeInfo(INT6, 24, array_type=INT, array_length=6, array_element_size=4), INT: TypeInfo(INT, 4)}


class FakeTypes:
    """reccmp's type lookup, with TYPES as the types our PDB gives."""

    def get(self, key: CvdumpTypeKey) -> TypeInfo:
        return TYPES[key]

    def get_name_for_offset(self, key: CvdumpTypeKey, offset: int) -> str:
        return f"+{offset}"


class FakeImage:
    """One side's image: the code at its address. Our build has relocations, so on our side every address the code
    holds is one."""

    def __init__(self, start: int, code: bytes, relocated: bool):
        self.start, self.code, self.relocated = start, code, relocated
        self.imagebase = 0x400000

    def read(self, address: int, size: int) -> bytes:
        return self.code[address - self.start:][:size]

    def is_relocated_addr(self, address: int) -> bool:
        return self.relocated


class NoLines:
    def find_line_of_recomp_address(self, address: int) -> None:
        return None


def cmp(value: int) -> bytes:
    """cmp eax, VALUE"""
    return b"\x3d" + struct.pack("<I", value)


def lea(value: int, scale: int = 4) -> bytes:
    """lea ecx, [eax*SCALE + VALUE]"""
    return b"\x8d\x0c" + bytes([{1: 0x05, 2: 0x45, 4: 0x85, 8: 0xc5}[scale]]) + struct.pack("<I", value)


def load(value: int) -> bytes:
    """mov eax, [VALUE]"""
    return b"\xa1" + struct.pack("<I", value)


def immediate(value: int) -> bytes:
    """mov eax, VALUE"""
    return b"\xb8" + struct.pack("<I", value)


def comparator(globals_: list[tuple[int | None, int | None, str, dict]], orig: bytes,
               recomp: bytes) -> tuple[FunctionComparator, object]:
    """A comparator and the function to compare: ORIG at ORIG_CODE and RECOMP at RECOMP_CODE, each then a ret. Each
    of GLOBALS_ is (game address, our address, name, values): a global on both sides is matched."""
    orig, recomp = orig + b"\xc3", recomp + b"\xc3"
    db = EntityDb()
    db.bulk_insert(ImageId.ORIG, [(ORIG_CODE, {"type": EntityType.FUNCTION, "name": "Loop", "orig_size": len(orig)})]
                   + [(game, {"type": EntityType.DATA, "name": name, **values})
                      for game, _, name, values in globals_ if game is not None])
    db.bulk_insert(ImageId.RECOMP, [(RECOMP_CODE, {"type": EntityType.FUNCTION, "name": "Loop",
                                                   "recomp_size": len(recomp)})]
                   + [(ours, {"type": EntityType.DATA, "name": name, **values})
                      for _, ours, name, values in globals_ if ours is not None])
    db.bulk_match([(ORIG_CODE, RECOMP_CODE)] + [(game, ours) for game, ours, _, _ in globals_
                                                if game is not None and ours is not None])
    compare = FunctionComparator(db=db, lines_db=NoLines(), orig_bin=FakeImage(ORIG_CODE, orig, False),
                                 recomp_bin=FakeImage(RECOMP_CODE, recomp, True), report=lambda *args: None,
                                 types=FakeTypes())
    return compare, db.get(ImageId.ORIG, ORIG_CODE)


def compared(globals_, orig: bytes, recomp: bytes):
    """The result of reccmp's compare with endrefs, and without."""
    compare, match = comparator(globals_, orig, recomp)
    return endrefs.renaming(FunctionComparator.compare_function)(compare, match), compare.compare_function(match)


def first_lines(result) -> tuple[str, str]:
    """The first instruction of each side, as the diff shows it."""
    return result.diff.orig_inst[0][1], result.diff.recomp_inst[0][1]


def arrays(orig_size: int | None = None, key: CvdumpTypeKey = INT6) -> list[tuple[int, int, str, dict]]:
    """LIST and OTHER on both sides, and in our build a global right after each of them."""
    values = {"recomp_size": 24, "data_type": key, "orig_size": orig_size}
    return [(LIST, OURS, "list", values), (OTHER, OURS + 0x100, "other", values),
            (None, OURS + 24, "next", {"recomp_size": 4}), (None, OURS + 0x118, "after", {"recomp_size": 4})]


def check_past_end() -> list[str]:
    """A compare with the address just past the list, where the game has nothing and our build has another global,
    shows the same name on both sides."""
    result, before = compared(arrays(), cmp(LIST + 24), cmp(OURS + 24))
    found = (before.match_ratio, result.match_ratio, first_lines(result))
    wanted = (0.5, 1.0, ("cmp eax, list+24 (OFFSET)", "cmp eax, list+24 (OFFSET)"))
    return [] if found == wanted else [f"a compare past the end gives {found}, not {wanted}"]


def check_real_neighbour() -> list[str]:
    """The global that the game has right after the list, which our build puts elsewhere, keeps its name: our side
    does not point past the list."""
    neighbour = [(LIST + 24, OURS + 0x200, "count", {"recomp_size": 4})]
    globals_ = arrays()[:1] + neighbour
    compare, _ = comparator(globals_, b"", b"")
    found = endrefs.renames(compare.db, compare.types, endrefs.operands(immediate(LIST + 24), ORIG_CODE),
                            endrefs.operands(immediate(OURS + 0x200), RECOMP_CODE))
    result, _ = compared(globals_, immediate(LIST + 24) + cmp(1), immediate(OURS + 0x200) + cmp(2))
    lines = first_lines(result)
    failures = [] if found == ({}, {}) else [f"renames gives {found} for a real neighbour, not ({{}}, {{}})"]
    return failures + ([] if lines == ("mov eax, count (DATA)",) * 2 else [f"a real neighbour gives {lines}"])


def check_other_array() -> list[str]:
    """The end of the list on one side and another address on the other differ: the end of another array, or an
    address next to the end of the list."""
    failures = []
    for game, ours in ((LIST + 24, OURS + 0x118), (LIST + 24, OURS + 20), (LIST + 24, OURS + 28),
                       (LIST + 20, OURS + 24), (LIST + 28, OURS + 24)):
        result, _ = compared(arrays(), cmp(game), cmp(ours))
        if result.match_ratio == 1.0:
            failures.append(f"0x{game:08x} against 0x{ours:08x} gives {first_lines(result)}, not a mismatch")
    return failures


def check_before_start() -> list[str]:
    """An index scaled by the element size from one element before the list shows the same name on both sides,
    though the game has a short global there and our build the end of a struct. A plain read there, an index of
    another scale, and an index from our build's own short keep their names."""
    globals_ = arrays() + [(LIST - 4, OURS + 0x300, "flag", {"recomp_size": 2}),
                           (None, OURS - 16, "block", {"recomp_size": 16})]
    result, before = compared(globals_, lea(LIST - 4), lea(OURS - 4))
    found = (before.match_ratio < 1.0, result.match_ratio, first_lines(result))
    wanted = (True, 1.0, ("lea ecx, [eax*4 + list-4 (OFFSET)]", "lea ecx, [eax*4 + list-4 (OFFSET)]"))
    failures = [] if found == wanted else [f"an index before the start gives {found}, not {wanted}"]
    compare, _ = comparator(globals_, b"", b"")
    for case, orig, recomp in (("a plain read", load(LIST - 4), load(OURS - 4)),
                               ("scale 1", lea(LIST - 4, 1), lea(OURS - 4, 1)),
                               ("scale 2", lea(LIST - 4, 2), lea(OURS - 4, 2)),
                               ("scale 8 from 8 before", lea(LIST - 8, 8), lea(OURS - 8, 8)),
                               ("our own short", lea(LIST - 4), lea(OURS + 0x300))):
        renamed = endrefs.renames(compare.db, compare.types, endrefs.operands(orig, ORIG_CODE),
                                  endrefs.operands(recomp, RECOMP_CODE))
        if renamed != ({}, {}):
            failures.append(f"renames gives {renamed} for {case}, not ({{}}, {{}})")
    return failures


def check_guards() -> list[str]:
    """No rename past a global that is not an array, or past an array whose two sides have other sizes."""
    failures = []
    for case, globals_ in (("an int", arrays(key=INT)), ("sizes 24 and 28", arrays(orig_size=28))):
        compare, _ = comparator(globals_, b"", b"")
        renamed = endrefs.renames(compare.db, compare.types, endrefs.operands(cmp(LIST + 24), ORIG_CODE),
                                  endrefs.operands(cmp(OURS + 24), RECOMP_CODE))
        if renamed != ({}, {}):
            failures.append(f"renames gives {renamed} for {case}, not ({{}}, {{}})")
    return failures


def check_worse() -> list[str]:
    """The names count only when they raise the score. Here our build puts right after the list a global that the
    function also reads, so the names fix the compare but break both reads."""
    globals_ = arrays()[:1] + [(LIST + 0x80, OURS + 24, "count", {"recomp_size": 4})]
    result, before = compared(globals_, cmp(LIST + 24) + load(LIST + 0x80) * 2, cmp(OURS + 24) + load(OURS + 24) * 2)
    found = (before.match_ratio, result.match_ratio)
    return [] if found == (0.75, 0.75) else [f"names that break more than they fix give {found}, not (0.75, 0.75)"]


def check_perfect() -> list[str]:
    """A function that matches is not scanned again."""
    scans = []

    def operands(code: bytes, start: int) -> endrefs.Operands:
        scans.append(start)
        return endrefs.Operands(set(), set())

    with mock.patch.object(endrefs, "operands", operands):
        result, _ = compared(arrays(), load(LIST), load(OURS))
    found = (result.match_ratio, scans)
    return [] if found == (1.0, []) else [f"a matching function gives {found}, not (1.0, [])"]


def run() -> list[str]:
    """Every check of the rename rule, in order: the failures of all."""
    failures = []
    for check in (check_past_end, check_real_neighbour, check_other_array, check_before_start, check_guards,
                  check_worse, check_perfect):
        failures += check()
    return failures
