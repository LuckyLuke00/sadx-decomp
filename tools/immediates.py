"""The immediates that the game reads as addresses and our build reads as numbers, for reccmp.

reccmp takes an immediate for an address when a relocation points at it or when it falls inside an entity it
knows: a flag such as 0x2000000 inside a global array, or 0x800000 inside a function. The game's exe has no
relocations, so only the second test works there, and it also fires on our side when our layout puts a global over
the flag. The line then differs though both sides have the same bytes.

Our build has relocations, so they tell which immediates of our function are addresses. numbers() finds the values
that both sides have as an immediate, that one side reads as an address, and that no relocation in our function
holds. A function that matches stays as it is. Any other function is compared again with those values as numbers on
both sides, and the better result counts. A source that writes an address as a bare number gets the same bytes;
fakematch.py marks that as raw_address.

install() makes reccmp compare each function through as_numbers(). Needs reccmp and capstone, so it runs in .venv.
"""

import bisect
import copy
import struct

from reccmp.compare import functions
from reccmp.compare.asm.parse import ParseAsm

import endrefs


def reads_address(parser: ParseAsm, value: int) -> bool:
    """Whether PARSER gives VALUE a name or a placeholder where it is an immediate."""
    return parser.is_addr(value) or parser.lookup(value) is not None


_sites: dict[int, list[int]] = {}  # id of an image: the sorted addresses of its relocations


def relocated(image, start: int, code: bytes) -> set[int]:
    """The values that IMAGE's relocations hold inside CODE, the bytes of IMAGE at START."""
    if id(image) not in _sites:
        _sites[id(image)] = sorted(image.relocations)
    sites = _sites[id(image)]
    first, last = bisect.bisect_left(sites, start), bisect.bisect_right(sites, start + len(code) - 4)
    return {struct.unpack_from("<I", code, site - start)[0] for site in sites[first:last]}


def numbers(orig: ParseAsm, recomp: ParseAsm, orig_values: set[int], recomp_values: set[int],
            recomp_relocated: set[int]) -> set[int]:
    """The immediates in both ORIG_VALUES and RECOMP_VALUES that ORIG or RECOMP reads as an address, though no
    relocation of our function holds them: RECOMP_RELOCATED."""
    return {value for value in orig_values & recomp_values
            if value not in recomp_relocated and (reads_address(orig, value) or reads_address(recomp, value))}


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
    on both sides, for a function that does not match. The second result counts only when it scores higher."""

    def compare_function(self, match):
        result = compare(self, match)
        if result.match_ratio == 1.0:
            return result
        orig_code, recomp_code = endrefs.code(self, match)
        values = numbers(self.orig_sanitize, self.recomp_sanitize,
                         endrefs.operands(orig_code, match.orig_addr).immediates,
                         endrefs.operands(recomp_code, match.recomp_addr).immediates,
                         relocated(self.recomp_bin, match.recomp_addr, recomp_code))
        if not values:
            return result
        renamed = copy.copy(self)
        renamed.orig_sanitize = with_numbers(self.orig_sanitize, values)
        renamed.recomp_sanitize = with_numbers(self.recomp_sanitize, values)
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
