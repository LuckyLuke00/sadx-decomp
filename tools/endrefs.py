"""The operands just past the end of a global array, or one element before its start, for reccmp.

A loop over a global array can end on a compare with the address just past the array. An index with count - 1
can fold the - 1 into the address, one element before the array. reccmp names an address after the global that
holds it, and the game and our build put other globals next to the array. So the same operand gets another name
on each side, or none, and the function can't match.

renaming() gives such an operand the array's name with its offset, on both sides. An operand counts only when
both sides have it at the same place next to the same matched array: past the end as an immediate, before the
start as an index scaled by the element size. A function that matches stays as it is. Any other function is
compared again with the names, and the better result counts.

install() makes reccmp compare each function through renaming(). Needs reccmp and capstone, so it runs in .venv.
"""

import copy
from typing import NamedTuple

import capstone
from reccmp.compare import functions
from reccmp.compare.asm.parse import ParseAsm
from reccmp.cvdump.cvinfo import CvdumpTypeKey
from reccmp.types import EntityType, ImageId


class Operands(NamedTuple):
    immediates: set[int]
    indexed: set[tuple[int, int]]  # (address, scale) of each memory operand with an index register


class Layout(NamedTuple):
    size: int
    element: int | None  # the size of one element


def operands(code: bytes, start: int) -> Operands:
    """The immediates and scaled indexes in CODE at START, without the targets of calls and jumps."""
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    found = Operands(set(), set())
    for ins in md.disasm(code, start):
        if ins.group(capstone.CS_GRP_CALL) or ins.group(capstone.CS_GRP_JUMP):
            continue
        for op in ins.operands:
            if op.type == capstone.x86.X86_OP_IMM:
                found.immediates.add(op.imm & 0xFFFFFFFF)
            elif op.type == capstone.x86.X86_OP_MEM and op.mem.index:
                found.indexed.add((op.mem.disp & 0xFFFFFFFF, op.mem.scale))
    return found


def array_layout(entity, types) -> Layout | None:
    """The layout of ENTITY if it is a matched global array whose size both sides agree on, else None."""
    if entity is None or not entity.matched or entity.entity_type != EntityType.DATA or not entity.get("data_type"):
        return None
    size = entity.size(ImageId.RECOMP)
    if not size or entity.size(ImageId.ORIG) not in (None, size):
        return None
    info = types.get(CvdumpTypeKey(entity.get("data_type")))
    return Layout(size, info.array_element_size) if info.is_array() else None


def renames(db, types, orig: Operands, recomp: Operands) -> tuple[dict[int, str], dict[int, str]]:
    """The names of the operands just past the end or one element before the start of a matched array, on each side:
    ({game address: name}, {our address: name}). ORIG and RECOMP are the operands of the function on each side."""
    orig_names, recomp_names = {}, {}
    for value in orig.immediates:
        array = db.get(ImageId.ORIG, value - 1, exact=False)
        layout = array_layout(array, types)
        if layout and array.orig_addr + layout.size == value and array.recomp_addr + layout.size in recomp.immediates:
            orig_names[value] = recomp_names[array.recomp_addr + layout.size] = array.match_name(f"+{layout.size}")
    for value, scale in orig.indexed:
        array = db.get(ImageId.ORIG, value + scale)
        layout = array_layout(array, types)
        if layout and layout.element == scale and (array.recomp_addr - scale, scale) in recomp.indexed:
            orig_names[value] = recomp_names[array.recomp_addr - scale] = array.match_name(f"-{scale}")
    return orig_names, recomp_names


def code(compare, match) -> tuple[bytes, bytes]:
    """The bytes of MATCH on each side, as reccmp's compare_function reads them."""
    recomp_size = match.size(ImageId.RECOMP)
    orig_size = match.size(ImageId.ORIG)
    if orig_size is None:
        orig_max = match.max_size(ImageId.ORIG)
        orig_size = recomp_size if orig_max is None else min(orig_max, recomp_size)
    return compare.orig_bin.read(match.orig_addr, orig_size), compare.recomp_bin.read(match.recomp_addr, recomp_size)


def with_names(parser: ParseAsm, names: dict[int, str]) -> ParseAsm:
    """A copy of PARSER that takes each address of NAMES for an address and gives it its name there."""
    renamed = copy.copy(parser)
    is_address, lookup = parser.addr_test, parser.name_lookup

    def name_lookup(address: int, exact: bool = False, indirect: bool = False) -> str | None:
        if address in names:
            return names[address]
        return lookup(address, exact=exact, indirect=indirect)

    renamed.addr_test = lambda address: address in names or is_address(address)
    renamed.name_lookup = name_lookup
    return renamed


def renaming(compare):
    """COMPARE, reccmp's FunctionComparator.compare_function, compared again with the names of renames() for a
    function that does not match. The second result counts only when it scores higher."""

    def compare_function(self, match):
        result = compare(self, match)
        if result.match_ratio == 1.0:
            return result
        orig_code, recomp_code = code(self, match)
        orig_names, recomp_names = renames(self.db, self.types, operands(orig_code, match.orig_addr),
                                           operands(recomp_code, match.recomp_addr))
        if not orig_names:
            return result
        renamed = copy.copy(self)
        renamed.orig_sanitize = with_names(self.orig_sanitize, orig_names)
        renamed.recomp_sanitize = with_names(self.recomp_sanitize, recomp_names)
        renamed.report = lambda *args: None  # the first compare reported all of it already
        retry = compare(renamed, match)
        return retry if retry.match_ratio > result.match_ratio else result

    compare_function.endrefs = True
    return compare_function


def install() -> None:
    """Make reccmp compare each function through renaming(). Installing it again changes nothing."""
    compare = functions.FunctionComparator.compare_function
    if getattr(compare, "endrefs", False):
        return
    functions.FunctionComparator.compare_function = renaming(compare)
