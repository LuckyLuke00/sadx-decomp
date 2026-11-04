"""Tests of tools/immediates.py: which immediates the compare keeps as numbers.

run() returns the failures as "<case> gives <found>, not <wanted>". Each check builds a small reccmp database by hand,
with the code of one function on each side, and compares it with reccmp's FunctionComparator.
"""

import struct
from unittest import mock

from reccmp.compare.db import EntityDb
from reccmp.compare.functions import FunctionComparator
from reccmp.types import EntityType, ImageId

import endrefs
import immediates
from endrefstests import FakeTypes, NoLines, cmp, immediate, load

ORIG_CODE, RECOMP_CODE = 0x00401000, 0x00501000  # the function on each side
TABLE, OURS = 0x00600000, 0x00700000  # a matched global of 0x100 bytes, in the game and in our build
OTHER_CODE = 0x00402000  # another function of the game, 0x100 bytes
FLAG = TABLE + 0x10  # a number inside TABLE


class FakeImage:
    """One side's image: the code at its address, and the addresses its relocations point at. Each place in the code
    that holds one of those addresses has a relocation."""

    def __init__(self, start: int, code: bytes, relocated: set[int]):
        self.start, self.code, self.relocated = start, code, relocated
        self.imagebase = 0x400000
        self.relocations = {start + at for at in range(len(code) - 3)
                            if struct.unpack_from("<I", code, at)[0] in relocated}

    def read(self, address: int, size: int) -> bytes:
        return self.code[address - self.start:][:size]

    def is_relocated_addr(self, address: int) -> bool:
        return address in self.relocated


def push(value: int) -> bytes:
    """push VALUE"""
    return b"\x68" + struct.pack("<I", value)


def comparator(orig: bytes, recomp: bytes, relocated: set[int] = frozenset()) -> tuple[FunctionComparator, object]:
    """A comparator and the function to compare: ORIG at ORIG_CODE and RECOMP at RECOMP_CODE, each then a ret. The game
    has TABLE and OTHER_CODE, our build TABLE at OURS. RELOCATED: the addresses our build's relocations point at."""
    orig, recomp = orig + b"\xc3", recomp + b"\xc3"
    db = EntityDb()
    db.bulk_insert(ImageId.ORIG, [(ORIG_CODE, {"type": EntityType.FUNCTION, "name": "Draw", "orig_size": len(orig)}),
                                  (OTHER_CODE, {"type": EntityType.FUNCTION, "name": "Other", "orig_size": 0x100}),
                                  (TABLE, {"type": EntityType.DATA, "name": "table", "orig_size": 0x100})])
    db.bulk_insert(ImageId.RECOMP, [(RECOMP_CODE, {"type": EntityType.FUNCTION, "name": "Draw",
                                                   "recomp_size": len(recomp)}),
                                    (OURS, {"type": EntityType.DATA, "name": "table", "recomp_size": 0x100})])
    db.bulk_match([(ORIG_CODE, RECOMP_CODE), (TABLE, OURS)])
    compare = FunctionComparator(db=db, lines_db=NoLines(), orig_bin=FakeImage(ORIG_CODE, orig, set()),
                                 recomp_bin=FakeImage(RECOMP_CODE, recomp, set(relocated)),
                                 report=lambda *args: None, types=FakeTypes())
    return compare, db.get(ImageId.ORIG, ORIG_CODE)


def compared(orig: bytes, recomp: bytes, relocated: set[int] = frozenset()):
    """The result of reccmp's compare with immediates, and without."""
    compare, match = comparator(orig, recomp, relocated)
    return immediates.as_numbers(FunctionComparator.compare_function)(compare, match), compare.compare_function(match)


def check_flags() -> list[str]:
    """A number inside a global or inside another function of the game stays a number, in a mov, a push or a cmp."""
    failures = []
    for case, code in (("a mov inside a global", immediate(FLAG)), ("a push inside a global", push(FLAG)),
                       ("a cmp inside a global", cmp(FLAG)), ("a push inside a function", push(OTHER_CODE + 0x10))):
        result, before = compared(code + load(TABLE), code + load(OURS))
        found = (before.match_ratio < 1.0, result.match_ratio)
        if found != (True, 1.0):
            failures.append(f"{case} gives {found}, not (True, 1.0)")
    return failures


def check_addresses() -> list[str]:
    """A real address keeps its name: the game's TABLE against ours, and our relocated number against the game's."""
    failures = []
    result, _ = compared(immediate(TABLE), immediate(OURS), {OURS})
    if result.diff.orig_inst[0][1] != "mov eax, table (DATA)" or result.match_ratio != 1.0:
        failures.append(f"the address of a global gives {result.diff.orig_inst[0][1]}, {result.match_ratio}")
    result, before = compared(immediate(FLAG) + load(TABLE), immediate(FLAG) + load(OURS), {FLAG})
    if result.match_ratio != before.match_ratio:
        failures.append(f"a number our build relocates gives {result.match_ratio}, not {before.match_ratio}")
    return failures


def check_our_layout() -> list[str]:
    """A number that falls inside our global and not the game's stays a number, unless our build relocates it."""
    failures = []
    for case, code in (("a mov", immediate(OURS + 0x10)), ("an or", b"\x0d" + struct.pack("<I", OURS + 0x10))):
        result, before = compared(code + load(TABLE), code + load(OURS))
        found = (before.match_ratio < 1.0, result.match_ratio)
        if found != (True, 1.0):
            failures.append(f"{case} inside our global gives {found}, not (True, 1.0)")
    result, before = compared(immediate(OURS + 0x10) + load(TABLE), immediate(OURS + 0x10) + load(OURS), {OURS + 0x10})
    if result.match_ratio != before.match_ratio:
        failures.append(f"an address our build relocates gives {result.match_ratio}, not {before.match_ratio}")
    return failures


def check_numbers() -> list[str]:
    """numbers() takes only the values on both sides that one side reads as an address and no relocation of our
    function holds."""
    compare, _ = comparator(b"", b"")
    found = immediates.numbers(compare.orig_sanitize, compare.recomp_sanitize, {FLAG, 5, TABLE + 0x20, OURS + 0x10},
                               {FLAG, 5, OURS + 0x10, OURS + 0x20}, set())
    if found != {FLAG, OURS + 0x10}:
        return [f"numbers gives {found}, not {{FLAG, OURS + 0x10}}"]
    found = immediates.numbers(compare.orig_sanitize, compare.recomp_sanitize, {FLAG}, {FLAG}, {FLAG})
    return [] if found == set() else [f"numbers with FLAG relocated gives {found}, not set()"]


def check_perfect() -> list[str]:
    """A function that matches is not scanned again."""
    scans = []

    def operands(code: bytes, start: int) -> endrefs.Operands:
        scans.append(start)
        return endrefs.Operands(set(), set())

    with mock.patch.object(endrefs, "operands", operands):
        result, _ = compared(load(TABLE), load(OURS))
    found = (result.match_ratio, scans)
    return [] if found == (1.0, []) else [f"a matching function gives {found}, not (1.0, [])"]


def run() -> list[str]:
    """Every check of the number rule, in order: the failures of all."""
    failures = []
    for check in (check_flags, check_addresses, check_our_layout, check_numbers, check_perfect):
        failures += check()
    return failures
