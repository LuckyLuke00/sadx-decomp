"""Tests of the parts of tools/link.py that need no linker, with tools/coff.py and the byte helpers they use: the COFF
writer, the literal fold, the code layout, a name's address from the original's bytes, the names the split defines,
the link order, the PE checksum and the byte count.

run() returns the failures as "<helper> gives <found> for <input>, not <wanted>". selftest.check_link runs the real
link on the self-test's exe.
"""

import struct
import tempfile
from pathlib import Path

import coff
import link
import osutil
import pe

TEXT = 0x60500020  # code, executable, readable, 16-byte aligned
LITERAL = 0x40301040  # read-only initialized data, 4-byte aligned, COMDAT
DATA = 0xC0300040  # read-write initialized data, 4-byte aligned
ANY = 2  # a COMDAT selection: keep any one copy
# A function that loads a float literal, reads _table[2] and calls _f: fld [lit]; mov eax, [_table+8]; call _f; ret
CODE = bytes.fromhex("d90500000000" "a108000000" "e800000000" "c3")
LITERAL_BYTES = bytes.fromhex("0000803f")  # 1.0f
# Where the original has them
FUNCTION_AT, LITERAL_AT, TABLE_AT, CALLEE_AT = 0x00401000, 0x0040A000, 0x00500000, 0x00401100


class Image:
    """What link needs of pe.Image: read, over a few runs of bytes by address."""

    def __init__(self, runs: dict[int, bytes]):
        self.runs = runs

    def read(self, address: int, size: int) -> bytes:
        for start, data in self.runs.items():
            if start <= address < start + len(data):
                return data[address - start:address - start + size]
        return b""


def failure(helper: str, found, given, wanted) -> str:
    return f"{helper} gives {found!r} for {given!r}, not {wanted!r}"


def sample() -> coff.Object:
    """An object as cl.exe writes CODE: the function, its literal as a COMDAT, and the names it uses."""
    text = coff.Section(".text", TEXT, CODE, [coff.Relocation(2, 5, coff.DIR32), coff.Relocation(7, 6, coff.DIR32),
                                              coff.Relocation(12, 7, coff.REL32)])
    literal = coff.Section(".rdata", LITERAL, LITERAL_BYTES, [])
    return coff.Object([text, literal], coff.numbered([
        coff.section_symbol(1, text),
        coff.Symbol("_main", 0, 1, coff.FUNCTION, coff.EXTERNAL),
        coff.section_symbol(2, literal, ANY),
        coff.Symbol("__real@3f800000", 0, 2, 0, coff.EXTERNAL),
        coff.Symbol("_table", 0, coff.UNDEFINED, 0, coff.EXTERNAL),
        coff.Symbol("_f", 0, coff.UNDEFINED, coff.FUNCTION, coff.EXTERNAL),
        coff.Symbol("__fltused", 0, coff.UNDEFINED, 0, coff.EXTERNAL),
    ]))


def original(literal: bytes = LITERAL_BYTES) -> Image:
    """The original's bytes for sample(): CODE with its fields filled in, and the literal."""
    code = bytearray(CODE)
    struct.pack_into("<I", code, 2, LITERAL_AT)
    struct.pack_into("<I", code, 7, TABLE_AT + 8)
    struct.pack_into("<I", code, 12, CALLEE_AT - (FUNCTION_AT + 12 + 4))
    return Image({FUNCTION_AT: bytes(code), LITERAL_AT: literal})


def raises_not_linkable(action) -> bool:
    try:
        action()
    except link.NotLinkable:
        return True
    return False


def check_round_trip() -> list[str]:
    """coff.write lays an object out so that reading it back gives the same sections and symbols, and writing that
    gives the same bytes: long names go to the string table, and uninitialized data has no bytes in the file."""
    bss = coff.Section(".bss", link.BSS_FLAGS, 64, [])
    objects = [sample(), coff.Object([bss], coff.numbered([coff.section_symbol(1, bss)]))]
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder) / "test.obj"
        for obj in objects:
            written = coff.write(obj)
            path.write_bytes(written)
            found = coff.read(path)
            if found.sections != obj.sections or found.symbols != obj.symbols or coff.write(found) != written:
                failures.append(failure("coff.read(coff.write(obj))", found, obj, obj))
    return failures


def check_fold() -> list[str]:
    """fold empties a pooled literal's section, leaves its name undefined and returns its bytes. The code stays.
    Data of the file's own, such as a .data section, stops the file."""
    obj, literals = link.fold(sample())
    failures = []
    if literals != {"__real@3f800000": LITERAL_BYTES}:
        failures.append(failure("fold's literals", literals, "sample()", {"__real@3f800000": LITERAL_BYTES}))
    if obj.sections[0] != sample().sections[0] or obj.sections[1] != coff.Section(link.FOLDED, coff.REMOVE, b"", []):
        failures.append(failure("fold's sections", obj.sections, "sample()", "the code, then an empty REMOVE section"))
    if obj.symbols[5] != coff.Symbol("__real@3f800000", 0, coff.UNDEFINED, 0, coff.EXTERNAL):
        failures.append(failure("fold's literal symbol", obj.symbols[5], "sample()", "undefined"))
    own = sample()
    own.sections[1] = coff.Section(".data", DATA, LITERAL_BYTES, [])
    if not raises_not_linkable(lambda: link.fold(own)):
        failures.append(failure("fold", "no NotLinkable", "an object with .data", "NotLinkable"))
    return failures


def check_place() -> list[str]:
    """place lays code sections out from start, each at its alignment, and skips data."""
    sections = [coff.Section(".text", TEXT, bytes(6), []), coff.Section(".rdata", LITERAL, bytes(4), []),
                coff.Section(".text", TEXT, bytes(3), []),
                coff.Section(".text", (TEXT & ~coff.ALIGN_MASK) | 3 << coff.ALIGN_SHIFT, bytes(5), [])]
    found = link.place(coff.Object(sections, {}), 0x401000)
    wanted = ({1: 0x401000, 3: 0x401010, 4: 0x401014}, 0x401019)
    return [] if found == wanted else [failure("place", found, "sizes 6, data, 3 and 5 aligned to 4", wanted)]


def check_resolve() -> list[str]:
    """resolve reads each name's address from the original's bytes at its use: a DIR32 field less our addend, a REL32
    field from the end of the field. A name only the debug info or nothing uses has None. A name with two addresses
    stops the file."""
    obj = link.fold(sample())[0]
    found = link.resolve(obj, {1: FUNCTION_AT}, original())
    wanted = {"__real@3f800000": LITERAL_AT, "_table": TABLE_AT, "_f": CALLEE_AT, "__fltused": None}
    failures = [] if found == wanted else [failure("resolve", found, "sample()", wanted)]
    image = original()
    code = bytearray(image.runs[FUNCTION_AT])
    struct.pack_into("<I", code, 2, TABLE_AT + 0x40)  # the first use now names _table, at another address
    obj.sections[0].relocations[0] = coff.Relocation(2, 6, coff.DIR32)
    image.runs[FUNCTION_AT] = bytes(code)
    if not raises_not_linkable(lambda: link.resolve(obj, {1: FUNCTION_AT}, image)):
        failures.append(failure("resolve", "no NotLinkable", "_table at two addresses", "NotLinkable"))
    return failures


def check_swap_object() -> list[str]:
    """swap_object places the object at its functions' addresses. A literal whose bytes differ from the original's,
    or functions that would land elsewhere, stop the file."""
    swap = link.swap_object("sample.c", sample(), [FUNCTION_AT], original())
    failures = []
    if (swap.start, swap.end) != (FUNCTION_AT, FUNCTION_AT + len(CODE)):
        failures.append(failure("swap_object's range", (swap.start, swap.end), "sample()",
                                (FUNCTION_AT, FUNCTION_AT + len(CODE))))
    if not raises_not_linkable(lambda: link.swap_object("sample.c", sample(), [FUNCTION_AT], original(bytes(4)))):
        failures.append(failure("swap_object", "no NotLinkable", "a literal of other bytes", "NotLinkable"))
    if not raises_not_linkable(lambda: link.swap_object("sample.c", sample(), [FUNCTION_AT + 4], original())):
        failures.append(failure("swap_object", "no NotLinkable", "an unaligned function", "NotLinkable"))
    return failures


def check_split_names() -> list[str]:
    """split_names keeps the names the swaps use and none defines, with an address if any use gives one. Two
    addresses for one name stop the link."""
    first = link.Swap("a.c", sample(), 0, 0, {"_x": 0x500000, "_main": 0x401000, "__fltused": None})
    second = link.Swap("b.c", sample(), 0, 0, {"_x": None, "__fltused": None, "_y": 0x500010})
    found = link.split_names([first, second])
    wanted = {"_x": 0x500000, "__fltused": None, "_y": 0x500010}  # sample() defines _main
    failures = [] if found == wanted else [failure("split_names", found, "a.c and b.c", wanted)]
    other = second._replace(uses={"_x": 0x500004})
    if not raises_not_linkable(lambda: link.split_names([first, other])):
        failures.append(failure("split_names", "no NotLinkable", "_x at two addresses", "NotLinkable"))
    return failures


def check_link_order() -> list[str]:
    """link_order cuts .text around the swaps in address order, leaves out an empty run of .text between two swaps,
    and stops on swaps that overlap."""
    text, rdata = link.Piece(".text", TEXT, 0x1000, 0x2000), link.Piece(".rdata", LITERAL, 0x2000, 0x2400)
    first, second = (link.Swap(name, sample(), start, end, {}) for name, start, end in
                     (("a.c", 0x1100, 0x1180), ("b.c", 0x1180, 0x1200)))
    found = link.link_order([text, rdata], [second, first])
    wanted = [[text._replace(end=0x1100), rdata], first, second, [text._replace(start=0x1200)]]
    failures = [] if found == wanted else [failure("link_order", found, "a.c then b.c", wanted)]
    overlapping = second._replace(start=0x1170)
    if not raises_not_linkable(lambda: link.link_order([text, rdata], [first, overlapping])):
        failures.append(failure("link_order", "no NotLinkable", "overlapping swaps", "NotLinkable"))
    return failures


def check_checksum() -> list[str]:
    """pe.checksum sums 16-bit words with each carry folded back in, skips the CheckSum field, pads an odd length
    with a zero byte and adds the length. Worked by hand: 0xffff + 0x0002 + 0x0040 (e_lfanew) = 0x10041, folded to
    0x0042, plus 0x100 bytes gives 0x142. A last byte 0x05 adds 5 and one byte: 0x148."""
    data = bytearray(0x100)
    struct.pack_into("<HHI", data, 0, 0xFFFF, 0x0002, 0)
    struct.pack_into("<I", data, 0x3C, 0x40)
    struct.pack_into("<I", data, pe.checksum_offset(data), 0x12345678)
    failures = []
    for given, wanted in ((bytes(data), 0x142), (bytes(data) + b"\x05", 0x148)):
        if pe.checksum(given) != wanted:
            failures.append(failure("pe.checksum", hex(pe.checksum(given)), f"{len(given)} bytes", hex(wanted)))
    return failures


def check_byte_differences() -> list[str]:
    """byte_differences counts differing bytes and a longer tail, and finds the first offset, across blocks too."""
    cases = [((b"abcd", b"abcd"), (0, None)), ((b"abcd", b"abXd"), (1, 2)), ((b"ab", b"abc"), (1, 2)),
             ((b"abcd", b"aXcdEF"), (3, 1)), ((b"a" * 10, b"a" * 9 + b"b", 4), (1, 9))]
    return [failure("byte_differences", osutil.byte_differences(*given), given, wanted)
            for given, wanted in cases if osutil.byte_differences(*given) != wanted]


def run() -> list[str]:
    """Every check of the link helpers, in order: the failures of all."""
    failures = []
    for check in (check_round_trip, check_fold, check_place, check_resolve, check_swap_object, check_split_names,
                  check_link_order, check_checksum, check_byte_differences):
        failures += check()
    return failures
