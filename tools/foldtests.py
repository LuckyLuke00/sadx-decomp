"""Tests of tools/folds.py: which copies of a static function alias_folds() names after the copy the game kept.

run() returns the failures as "<helper> gives <found> for <input>, not <wanted>". Each check builds a small reccmp
database by hand, with the code of each function at its address in a FakeImage.
"""

import collections
import struct

from reccmp.compare.db import EntityDb
from reccmp.types import EntityType, ImageId

import folds

ORIGINAL = 0x10000000  # the game's addresses only need to differ from ours
DATA = 0x404000  # a global that the code reads
CALLEE = 0x405000  # a function that the code calls


class FakeImage:
    """Our image: the code of each function at its address."""

    def __init__(self, code: dict[int, bytes]):
        self.code = code

    def read(self, address: int, size: int) -> bytes:
        return self.code[address][:size]


def failure(helper: str, found, given, wanted) -> str:
    return f"{helper} gives {found!r} for {given!r}, not {wanted!r}"


def call(at: int, target: int) -> bytes:
    """call TARGET, at address AT."""
    return b"\xe8" + struct.pack("<i", target - (at + 5))


def calls(start: int, target: int) -> bytes:
    """A function at START that loads its own address, calls TARGET and returns."""
    return b"\xb8" + struct.pack("<I", start) + call(start + 5, target) + b"\xc3"


def reads(address: int) -> bytes:
    """A function that loads the global at ADDRESS and returns."""
    return b"\xa1" + struct.pack("<I", address) + b"\xc3"


def database(functions: list[tuple[int, str, bytes, bool, str | None]]) -> tuple[EntityDb, FakeImage]:
    """A database and our image with each function of FUNCTIONS: (our address, name, code, matched, symbol).
    A matched function gets the computed name that reccmp numbers the functions of a name with, in their order."""
    db = EntityDb()
    db.bulk_insert(ImageId.RECOMP, [(address, {"type": EntityType.FUNCTION, "name": name, "recomp_size": len(code),
                                               "symbol": symbol}) for address, name, code, _, symbol in functions])
    matched = [address for address, _, _, is_matched, _ in functions if is_matched]
    db.bulk_insert(ImageId.ORIG, [(ORIGINAL + address, {"type": EntityType.FUNCTION}) for address in matched])
    db.bulk_match([(ORIGINAL + address, address) for address in matched])
    numbers = collections.Counter()
    with db.batch() as batch:
        for address, name, _, is_matched, _ in functions:
            if is_matched:
                numbers[name] += 1
                batch.set(ImageId.RECOMP, address, computed_name=f"{name}({numbers[name]})")
    return db, FakeImage({address: code for address, _, code, _, _ in functions})


def names(db: EntityDb) -> dict[int, str]:
    return {entity.recomp_addr: entity.best_name() for entity in db.all(ImageId.RECOMP)}


def check_copy() -> list[str]:
    """A static copy with the same name and code folds, though its own address and its call's displacement differ."""
    given = [(0x401000, "Scroll", calls(0x401000, CALLEE), True, None),
             (0x402000, "Scroll", calls(0x402000, CALLEE), False, None)]
    db, image = database(given)
    found = (folds.alias_folds(db, image), names(db)[0x402000])
    wanted = ({0x402000: 0x401000}, "Scroll(1)")
    return [] if found == wanted else [failure("alias_folds", found, given, wanted)]


def check_same_code() -> list[str]:
    """Of two matched functions of its name, a copy folds into the one with its code."""
    given = [(0x401000, "Read", reads(DATA), True, None),
             (0x401100, "Read", reads(DATA + 4), True, None),
             (0x402000, "Read", reads(DATA + 4), False, None)]
    db, image = database(given)
    found = (folds.alias_folds(db, image), names(db)[0x402000])
    wanted = ({0x402000: 0x401100}, "Read(2)")
    return [] if found == wanted else [failure("alias_folds", found, given, wanted)]


def check_not_folded() -> list[str]:
    """No copy folds that reads another global, is a global function, has another name or is the same code as two
    matched functions of its name."""
    cases = {
        "another global": [(0x401000, "Read", reads(DATA), True, None),
                           (0x402000, "Read", reads(DATA + 4), False, None)],
        "a global function": [(0x401000, "Scroll", calls(0x401000, CALLEE), True, None),
                              (0x402000, "Scroll", calls(0x402000, CALLEE), False, "?Scroll@@YAXXZ")],
        "another name": [(0x401000, "Scroll", calls(0x401000, CALLEE), True, None),
                         (0x402000, "Other", calls(0x402000, CALLEE), False, None)],
        "two matched": [(0x401000, "Scroll", calls(0x401000, CALLEE), True, None),
                        (0x401100, "Scroll", calls(0x401100, CALLEE), True, None),
                        (0x402000, "Scroll", calls(0x402000, CALLEE), False, None)],
    }
    failures = []
    for case, given in cases.items():
        db, image = database(given)
        found = folds.alias_folds(db, image)
        if found:
            failures.append(failure("alias_folds", found, case, {}))
    return failures


def check_chain() -> list[str]:
    """A copy that calls a copy folds once the copy it calls folds, though it comes first."""
    given = [(0x401000, "Outer", calls(0x401000, 0x401100), True, None),
             (0x401100, "Inner", calls(0x401100, CALLEE), True, None),
             (0x402000, "Outer", calls(0x402000, 0x402100), False, None),
             (0x402100, "Inner", calls(0x402100, CALLEE), False, None)]
    db, image = database(given)
    found = folds.alias_folds(db, image)
    wanted = {0x402000: 0x401000, 0x402100: 0x401100}
    return [] if found == wanted else [failure("alias_folds", found, "a copy of Outer that calls a copy of Inner",
                                               wanted)]


def run() -> list[str]:
    """Every check of the fold rule, in order: the failures of all."""
    failures = []
    for check in (check_copy, check_same_code, check_not_folded, check_chain):
        failures += check()
    return failures
