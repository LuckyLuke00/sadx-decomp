"""The constants that the game's code uses and reccmp does not name there, for reccmp.

Our build has relocations, and each marks an operand as an address. The game has
none. There reccmp takes each 4-byte value in the image that is an address in a
data section for a pointer. It names a float, such as 400.0 in
fld [0x00403000], where an x87 instruction that it checks (fld, fadd, fmul and
the like) reads read-only data through such a pointer. It names a NUL-terminated
text that it takes for Latin-1 where a pointer holds its address. That is a text
whose first byte is a tab, CR, LF or 0x20-0x7f, and whose other bytes are those
or 0xa0-0xff. find() gives a row to what that search leaves out, from each
operand of an instruction in data/functions.csv:

- A float that such an x87 instruction reads from read-only data. reccmp's own
  search skips a few of them.
- An operand address in read-only data that holds no Latin-1 text, if no literal
  before it covers it. An import slot holds a pointer, so it is no literal.

reccmp names no such literal on our side, such as Shift-JIS text or text that
starts with a control code, unless the compiler pooled strings (/GF, which /O1
and /O2 turn on). Then each literal has a symbol, and reccmp names it after its
bytes. So the address gets a string row where its function's group pools
strings, and a row with no name elsewhere, which shows as an address
placeholder, as on our side. Writable data holds variables more than literals,
so there only Latin-1 text counts, as in reccmp, and no address gets a row.

A wide literal, such as L"sum", follows the same rules. Without pooling it has
no symbol, and reccmp reads it as narrow text from our relocation, so "s" is
all of it. The game's side reads it the same way. With pooling its symbol is a
widechar, and reccmp names it after its UTF-16LE text. So an operand address in
read-only data gets a widechar row where its function's group pools strings, if
its bytes are UTF-16LE text of two characters or more that passes the Latin-1
test. A narrow string of two characters or more never passes: it has no NUL
after its first character. One character is too few, as a one-character narrow
string and its padding read the same way. Other wide text needs a STRING
annotation.

One other kind of address has no name on our side, so it gets a row with no
name too: an exception handler that the compiler made for a function. It ends
with mov eax, offset FuncInfo; jmp ___CxxFrameHandler3. reccmp's own search for
these knows only the FuncInfo of Visual C++ 6.

The image base is a number in the game, where no relocation marks it. Our build
has a relocation on it. So run_reccmp() makes reccmp take no number at or below
the image base for an address.

reccmp adds the constants it finds itself after it matches, and skips each
address inside an entity it knows. There both sides name the address after the
variable, such as __lc_category[1]. A data source loads before matching, so a
row of ours there would hide that name on the game's side. So `check.py` writes
the rows to build/constants.csv, and run_reccmp() adds them at the step where
reccmp adds its own.

A wrong row costs nothing as long as it is at data: our side names the variable
there, so the function can't match before a GLOBAL annotation names it on the
game's side too, which drops the row. Only an integer constant that happens to
equal the address would then show as an address on the game's side alone.

reccmp also reads no more of a game function than our function's size, unless
it knows the game function's size. A function of ours that stops short would
then hide the rest of the game's code from the score. So `check.py` also
writes the size of each game function in data/functions.csv to
build/sizes.csv, and run_reccmp() sets it on each function that reccmp knows
by then. Library code gets no sizes: its rows there need not end where the
library's objects do.

Needs capstone and reccmp, so it runs in .venv.
"""

import re
import sys
from collections.abc import Iterator
from pathlib import Path
from typing import NamedTuple

import capstone
from reccmp.analysis.float_const import FLOAT_OPCODES, SINGLE_PRECISION_OPCODES
from reccmp.analysis.string_const import is_likely_latin1
from reccmp.compare import core, functions
from reccmp.compare.csv import csv_parse
from reccmp.formats import detect_image
from reccmp.tools import asmcmp
from reccmp.types import ImageId

import endrefs
import immediates
import folds
import varfiles

HEX = re.compile(r"0x[0-9a-f]+")
HANDLER_START = (b"\xb8", b"\x8b\x54\x24\x08")  # mov eax, offset FuncInfo; or mov edx, [esp + 8] for cookie checks
HANDLER_END = re.compile(rb"\xb8(.{4})\xe9", re.DOTALL)  # mov eax, offset FuncInfo; jmp
HANDLER_LENGTH = 64  # bytes enough for a handler that checks two security cookies
FUNCINFO_MAGIC = (0x19930520, 0x19930521, 0x19930522)  # as reccmp lists them for Visual C++ 6 to 8; 2010 uses the last


class Constant(NamedTuple):
    address: int
    kind: str  # reccmp's type: float, string, widechar, or global for a row with no name
    size: int


class Function(NamedTuple):
    address: int
    size: int
    pools_strings: bool  # whether its code group pools strings: see codegen.pools_strings()


class Regions(NamedTuple):
    const: list[range]
    data: list[range]
    code: list[range]


class Scan:
    """What the code of the functions holds: the floats it reads, and the addresses in its operands."""

    def __init__(self, image, const: list[range]):
        self.image = image
        self.const = const
        self.floats = {}  # address: size
        self.operands = {}  # address: whether a function that pools strings uses it
        self.disassembler = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    def add(self, function: Function) -> None:
        code = self.image.read(function.address, function.size)
        for address, length, _, operand_text in self.disassembler.disasm_lite(code, function.address):
            if self.add_float(code, address - function.address, length):
                continue
            for value in HEX.findall(operand_text):
                operand = int(value, 16)
                self.operands[operand] = self.operands.get(operand, False) or function.pools_strings

    def add_float(self, code: bytes, offset: int, length: int) -> bool:
        """Add the float that the instruction at offset reads, if it reads one from read-only data."""
        if length != 6 or (code[offset], code[offset + 1]) not in FLOAT_OPCODES:
            return False
        pointer = int.from_bytes(code[offset + 2:offset + 6], "little")
        if not inside(pointer, self.const):
            return False
        self.floats[pointer] = 4 if (code[offset], code[offset + 1]) in SINGLE_PRECISION_OPCODES else 8
        return True


def find(exe: Path, functions: list[Function]) -> list[Constant]:
    """The constants that the code of the functions uses."""
    image = detect_image(exe)
    regions = Regions([region.range for region in image.get_const_regions()],
                      [region.range for region in image.get_data_regions()],
                      [region.range for region in image.get_code_regions()])
    scan = Scan(image, regions.const)
    for function in functions:
        scan.add(function)
    found = [Constant(address, "float", size) for address, size in scan.floats.items()]
    return sorted(found + other_constants(image, scan, regions))


def other_constants(image, scan: Scan, regions: Regions) -> list[Constant]:
    """The string and global rows for the operand addresses that scan found."""
    imports = {slot.addr for slot in image.imports}
    covered = set().union(*(range(address, address + size) for address, size in scan.floats.items()))
    found = []
    end = 0  # the end of the last literal
    for address, pooled in sorted(scan.operands.items()):
        if exception_handler(image, address, regions):
            found.append(Constant(address, "global", 1))
            continue
        if address < end or address in covered or address in imports or not inside(address, regions.data):
            continue
        size, kind = literal(image, address, pooled, regions.const)
        if kind is not None:
            found.append(Constant(address, kind, size))
        end = address + size
    return found


def literal(image, address: int, pooled: bool, const: list[range]) -> tuple[int, str | None]:
    """The size of the literal at an operand address in data, and the kind of the row it needs. The kind is None
    where it needs no row: reccmp names Latin-1 text itself. Other bytes in writable data are no literal, so their
    size is 0. POOLED says whether a function that pools strings uses the address."""
    in_const = inside(address, const)
    wide = wide_text(image, address) if pooled and in_const else ""
    if wide:
        return 2 * len(wide) + 2, "widechar"
    text = image.read_string(address)
    if is_likely_latin1(text.decode("latin1")):
        return len(text) + 1, None
    if in_const:
        return len(text) + 1, "string" if pooled else "global"
    return 0, None


def wide_text(image, address: int) -> str:
    """The text of the wide literal at address, or "" if the bytes are no such text. It is
    UTF-16LE text that passes the Latin-1 test, so a NUL byte follows each character. It has
    two characters or more: a one-character narrow string and its padding read as one."""
    raw = image.read_widechar(address)
    if len(raw) < 4 or any(raw[1::2]):
        return ""
    text = raw[::2].decode("latin1")
    return text if is_likely_latin1(text) else ""


def exception_handler(image, address: int, regions: Regions) -> bool:
    """Whether address starts an exception handler that the compiler made: it ends with
    mov eax, offset FuncInfo; jmp ___CxxFrameHandler3, after the security cookie checks."""
    span = next((span for span in regions.code if address in span), None)
    if span is None:
        return False
    handler = image.read(address, min(HANDLER_LENGTH, span.stop - address))
    tail = HANDLER_END.search(handler)
    if not handler.startswith(HANDLER_START) or tail is None:
        return False
    funcinfo = int.from_bytes(tail[1], "little")
    return inside(funcinfo, regions.const) and int.from_bytes(image.read(funcinfo, 4), "little") in FUNCINFO_MAGIC


def inside(address: int, ranges: list[range]) -> bool:
    return any(address in span for span in ranges)


def free_rows(db, image_id, rows: list) -> Iterator[tuple[int, dict]]:
    """The rows whose address no entity of reccmp's database covers yet."""
    for address, values in rows:
        if not db.intersects(image_id, address):
            yield address, values


def add_rows(db, image_id, rows: list) -> None:
    with db.batch() as batch:
        for address, values in free_rows(db, image_id, rows):
            batch.set(image_id, address, **values)


def set_sizes(db, rows: list) -> None:
    """Set the size of each function that reccmp knows. A row at another address adds nothing."""
    with db.batch() as batch:
        for address, values in rows:
            if db.exists(ImageId.ORIG, address):
                batch.set(ImageId.ORIG, address, **values)


def read_rows(path: Path) -> list:
    return list(csv_parse(path.read_text(encoding="utf-8")))


def run_reccmp(args: list[str]) -> int:
    """Run reccmp-reccmp with args in a folder with a reccmp-build.yml. Where reccmp adds the
    constants it finds, set the sizes in the folder's sizes.csv and add the rows of its
    constants.csv. The folder must have both files."""
    sizes = read_rows(Path("sizes.csv"))
    rows = read_rows(Path("constants.csv"))
    find_floats = core.complete_partial_floats  # reccmp's first step on constants

    def add_rows_then_find_floats(db, image_id, binfile):
        if image_id == ImageId.ORIG:
            set_sizes(db, sizes)
            add_rows(db, image_id, rows)
        find_floats(db, image_id, binfile)

    core.complete_partial_floats = add_rows_then_find_floats
    make_lookup = functions.create_valid_addr_lookup

    def make_lookup_above_base(db, image_id, binfile):
        lookup = make_lookup(db, image_id, binfile)
        return lambda address, operand: address > binfile.imagebase and lookup(address, operand)

    functions.create_valid_addr_lookup = make_lookup_above_base
    folds.install()
    endrefs.install()
    immediates.install()
    varfiles.install()
    # reccmp prints a sparkle emoji, which the code page of a pipe on Windows may not have.
    sys.stdout.reconfigure(errors="replace")
    sys.argv = ["reccmp-reccmp", *args]
    return asmcmp.main()


if __name__ == "__main__":
    sys.exit(run_reccmp(sys.argv[1:]))
