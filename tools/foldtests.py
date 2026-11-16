"""Tests of tools/folds.py: which copies of a function alias_folds() names after the copy the game kept.

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


LIST_A = ("std::list<A,std::allocator<A> >::clear", "?clear@?$list@UA@@V?$allocator@UA@@@std@@@std@@QAEXXZ")
LIST_B = ("std::list<B,std::allocator<B> >::clear", "?clear@?$list@UB@@V?$allocator@UB@@@std@@@std@@QAEXXZ")
LIST_C = ("std::list<C,std::allocator<C> >::clear", "?clear@?$list@UC@@V?$allocator@UC@@@std@@@std@@QAEXXZ")
VECTOR_B = ("std::vector<B,std::allocator<B> >::clear", "?clear@?$vector@UB@@V?$allocator@UB@@@std@@@std@@QAEXXZ")


def check_template() -> list[str]:
    """An instance of a template folds into the matched instance of that template with its code."""
    given = [(0x401000, LIST_A[0], calls(0x401000, CALLEE), True, LIST_A[1]),
             (0x401100, LIST_C[0], reads(DATA), True, LIST_C[1]),
             (0x402000, LIST_B[0], calls(0x402000, CALLEE), False, LIST_B[1])]
    db, image = database(given)
    found = (folds.alias_folds(db, image), names(db)[0x402000])
    wanted = ({0x402000: 0x401000}, f"{LIST_A[0]}(1)")
    return [] if found == wanted else [failure("alias_folds", found, given, wanted)]


def check_not_folded() -> list[str]:
    """No copy folds that reads another global, is a global function, has another name or is the same code as two
    matched functions of its name. No instance of a template folds into another template, into other code or into
    one of two matched instances with its code."""
    cases = {
        "another template": [(0x401000, LIST_A[0], calls(0x401000, CALLEE), True, LIST_A[1]),
                             (0x402000, VECTOR_B[0], calls(0x402000, CALLEE), False, VECTOR_B[1])],
        "a template with other code": [(0x401000, LIST_A[0], reads(DATA), True, LIST_A[1]),
                                       (0x402000, LIST_B[0], reads(DATA + 4), False, LIST_B[1])],
        "two matched instances": [(0x401000, LIST_A[0], calls(0x401000, CALLEE), True, LIST_A[1]),
                                  (0x401100, LIST_C[0], calls(0x401100, CALLEE), True, LIST_C[1]),
                                  (0x402000, LIST_B[0], calls(0x402000, CALLEE), False, LIST_B[1])],
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


EMPTY_HELPER = ("std::_Destroy<A>", "??$_Destroy@UA@@@std@@YAXPAUA@@@Z")


def check_listed() -> list[str]:
    """A listed copy folds into the function at its row's game address, though the names differ and another matched
    function has the same code. A listed copy with other code does not fold, and not_folded() names it. A row whose
    copy the image lacks is no problem."""
    listed = {EMPTY_HELPER[1]: ORIGINAL + 0x401100, "?Gone@@YAXXZ": ORIGINAL + 0x401000}
    failures = []
    for case, copy_code, wanted in (("the same code", reads(DATA), ({0x402000: 0x401100}, "FUN_00401100(1)", [])),
                                    ("other code", reads(DATA + 4), ({}, EMPTY_HELPER[0], [EMPTY_HELPER[1]]))):
        db, image = database([(0x401000, "FUN_00401000", reads(DATA), True, "?FUN_00401000@@YAXXZ"),
                              (0x401100, "FUN_00401100", reads(DATA), True, "?FUN_00401100@@YAXXZ"),
                              (0x402000, EMPTY_HELPER[0], copy_code, False, EMPTY_HELPER[1])])
        folded = folds.alias_folds(db, image, listed)
        found = (folded, names(db)[0x402000], folds.not_folded(db, listed, folded))
        if found != wanted:
            failures.append(failure("alias_folds", found, f"a listed copy with {case}", wanted))
    return failures


def check_listed_static() -> list[str]:
    """A static copy is listed by its name. With the same code it folds into its row's function, though the names
    differ and a matched function of its own name has the same code. With other code it does not fold, and
    not_folded() names it. A global function whose name is a listed name does not fold."""
    listed = {"KasyaDestruct": ORIGINAL + 0x401100}
    kept = [(0x401000, "KasyaDestruct", reads(DATA), True, None),
            (0x401100, "DeadJumpdai", reads(DATA), True, None)]
    cases = (("a static copy with the same code", reads(DATA), None,
              ({0x402000: 0x401100}, "DeadJumpdai(1)", [])),
             ("a static copy with other code", reads(DATA + 4), None, ({}, "KasyaDestruct", ["KasyaDestruct"])),
             ("a global copy", reads(DATA), "?KasyaDestruct@@YAXPAUtask@@@Z", ({}, "KasyaDestruct", [])))
    failures = []
    for case, copy_code, symbol, wanted in cases:
        db, image = database([*kept, (0x402000, "KasyaDestruct", copy_code, False, symbol)])
        folded = folds.alias_folds(db, image, listed)
        found = (folded, names(db)[0x402000], folds.not_folded(db, listed, folded))
        if found != wanted:
            failures.append(failure("alias_folds", found, case, wanted))
    return failures


def run() -> list[str]:
    """Every check of the fold rule, in order: the failures of all."""
    failures = []
    for check in (check_copy, check_same_code, check_template, check_not_folded, check_chain, check_listed,
                  check_listed_static):
        failures += check()
    return failures
