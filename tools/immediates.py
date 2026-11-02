"""The immediates that the game reads as addresses and our build reads as numbers, for reccmp.

The game's exe has no relocations, so reccmp takes an immediate for an address when it falls inside an entity it
knows: a flag such as 0x2000000 inside a global array, or 0x800000 inside a function. Our build has relocations, so
there the same flag stays a number, and the line differs though both sides have the same bytes.

numbers() finds such values: both sides have the immediate, the game's side reads it as an address and ours as a
number. A function that matches stays as it is. Any other function is compared again with those values as numbers on
the game's side, and the better result counts. A source that writes an address as a bare number gets the same bytes;
fakematch.py marks that as raw_address.

install() makes reccmp compare each function through as_numbers(). Needs reccmp and capstone, so it runs in .venv.
"""

import copy

from reccmp.compare import functions
from reccmp.compare.asm.parse import ParseAsm

import endrefs


def reads_address(parser: ParseAsm, value: int) -> bool:
    """Whether PARSER gives VALUE a name or a placeholder where it is an immediate."""
    return parser.is_addr(value) or parser.lookup(value) is not None


def numbers(orig: ParseAsm, recomp: ParseAsm, orig_values: set[int], recomp_values: set[int]) -> set[int]:
    """The immediates in both ORIG_VALUES and RECOMP_VALUES that ORIG reads as an address and RECOMP as a number."""
    return {value for value in orig_values & recomp_values
            if reads_address(orig, value) and not reads_address(recomp, value)}


def with_numbers(parser: ParseAsm, values: set[int]) -> ParseAsm:
    """A copy of PARSER that keeps each of VALUES a number where it is an immediate."""
    renamed = copy.copy(parser)
    is_address, lookup = parser.addr_test, parser.name_lookup

    def name_lookup(address: int, exact: bool = False, indirect: bool = False) -> str | None:
        if address in values and not exact and not indirect:
            return None
        return lookup(address, exact=exact, indirect=indirect)

    renamed.addr_test = lambda address: address not in values and is_address(address)
    renamed.name_lookup = name_lookup
    return renamed


def as_numbers(compare):
    """COMPARE, reccmp's FunctionComparator.compare_function, compared again with the values of numbers() as numbers
    on the game's side, for a function that does not match. The second result counts only when it scores higher."""

    def compare_function(self, match):
        result = compare(self, match)
        if result.match_ratio == 1.0:
            return result
        orig_code, recomp_code = endrefs.code(self, match)
        values = numbers(self.orig_sanitize, self.recomp_sanitize,
                         endrefs.operands(orig_code, match.orig_addr).immediates,
                         endrefs.operands(recomp_code, match.recomp_addr).immediates)
        if not values:
            return result
        renamed = copy.copy(self)
        renamed.orig_sanitize = with_numbers(self.orig_sanitize, values)
        renamed.report = lambda *args: None  # the first compare reported all of it already
        retry = compare(renamed, match)
        return retry if retry.match_ratio > result.match_ratio else result

    compare_function.immediates = True
    return compare_function


def install() -> None:
    """Make reccmp compare each function through as_numbers(). Installing it again changes nothing."""
    compare = functions.FunctionComparator.compare_function
    if getattr(compare, "immediates", False):
        return
    functions.FunctionComparator.compare_function = as_numbers(compare)
