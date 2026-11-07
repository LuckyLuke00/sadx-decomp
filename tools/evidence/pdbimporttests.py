"""Unit tests for pdbimport.py: the program database reader. Each test builds a small file byte by byte, as the
public format descriptions that pdbimport.py names lay it out. The self-test program database (build/SELFTEST.pdb)
is read too when it exists; without it that check prints "skipped".

Run on its own: .venv/Scripts/python.exe -I tools/evidence/pdbimporttests.py
run() calls every check and returns the failures. All names are made up.
"""

import csv
import struct
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import pdbimport  # noqa: E402
import symbols  # noqa: E402

SELFTEST = Path(__file__).resolve().parents[2] / "build" / "SELFTEST.pdb"
MAGIC = b"Microsoft C/C++ MSF 7.00\r\n\x1aDS\0\0\0"
NIL, NO_STREAM = 0xFFFFFFFF, 0xFFFF
T_NOTYPE, T_VOID, T_LONG, T_ULONG, T_REAL32, T_RCHAR, T_INT4 = 0x00, 0x03, 0x12, 0x22, 0x40, 0x70, 0x74
LF_MODIFIER, LF_POINTER, LF_PROCEDURE, LF_MFUNCTION, LF_ARGLIST = 0x1001, 0x1002, 0x1008, 0x1009, 0x1201
LF_FIELDLIST, LF_BITFIELD, LF_INDEX, LF_ENUMERATE, LF_MEMBER = 0x1203, 0x1205, 0x1404, 0x1502, 0x150d
LF_ARRAY, LF_CLASS, LF_STRUCTURE, LF_UNION, LF_ENUM = 0x1503, 0x1504, 0x1505, 0x1506, 0x1507
S_END, S_BLOCK32, S_CONSTANT, S_LPROC32, S_GPROC32, S_GPROC32_ID = 0x0006, 0x1103, 0x1107, 0x110f, 0x1110, 0x1147
S_INLINESITE, S_INLINESITE_END = 0x114d, 0x114e
CONST, VOLATILE = 1, 2  # modifier bits
REFERENCE, DATA_MEMBER, METHOD, RVALUE = 1, 2, 3, 4  # pointer modes
SELFTEST_SLOTS = {"Clamp": ("int", "int", "int", "int"),
                  "Dot": ("float", "const struct Vec3 &", "const struct Vec3 &"),
                  "CountAbove": ("int", "const int *", "int", "int"),
                  "Name": ("const char *", "int"),
                  "main": ("int", "int", "char **")}


# Building a program database


def pads(data: bytes, base: int = 0) -> bytes:
    """DATA and the pad bytes (F3 F2 F1) that make BASE plus its length a multiple of 4."""
    count = -(base + len(data)) % 4
    return data + bytes(0xF0 + count - position for position in range(count))


def name(text: str) -> bytes:
    return text.encode("utf-8") + b"\0"


def numeric(value: int) -> bytes:
    """VALUE as a numeric leaf: the value itself below 0x8000, else an LF_LONG."""
    return struct.pack("<H", value) if 0 <= value < 0x8000 else struct.pack("<Hi", 0x8003, value)


def records(bodies: list) -> bytes:
    """Each record body (kind and data) after its 2-byte length, padded to a multiple of 4 bytes."""
    padded = [pads(body, 2) for body in bodies]
    return b"".join(struct.pack("<H", len(body)) + body for body in padded)


def msf(streams: list, block_size: int = 512) -> bytes:
    """An MSF 7.00 file of STREAMS (bytes each, None for a nil stream). Blocks 0 to 2 hold the superblock and the
    free block maps; the stream blocks follow, then the directory, then the block map in as many blocks as it needs."""
    blocks = [b"", bytes(block_size), bytes(block_size)]

    def place(data: bytes) -> list:
        first = len(blocks)
        blocks.extend(data[start:start + block_size].ljust(block_size, b"\0")
                      for start in range(0, len(data), block_size))
        return list(range(first, len(blocks)))

    sizes = [NIL if stream is None else len(stream) for stream in streams]
    indices = [index for stream in streams for index in place(stream or b"")]
    directory = struct.pack(f"<{1 + len(sizes) + len(indices)}I", len(sizes), *sizes, *indices)
    directory_blocks = place(directory)
    map_blocks = place(struct.pack(f"<{len(directory_blocks)}I", *directory_blocks))
    superblock = MAGIC + struct.pack(f"<{5 + len(map_blocks)}I", block_size, 1, len(blocks), len(directory), 0,
                                     *map_blocks)
    blocks[0] = superblock.ljust(block_size, b"\0")
    return b"".join(blocks)


def module_record(stream: int, size: int, path: str) -> bytes:
    """A module record of the DBI stream: the 64-byte header, the module and object names, zeros to 4 bytes."""
    data = struct.pack("<I28sHHIIIH2xIII", 0, bytes(28), 0, stream, size, 0, 0, 0, 0, 0, 0) + name(path) * 2
    return data + bytes(-len(data) % 4)


class Pdb:
    """A program database under construction: type records, the symbols of one module and the section addresses."""

    def __init__(self):
        self.types = []  # record bodies, kind first
        self.symbols = []  # record bodies, kind first
        self.sections = [0x1000, 0x8000]  # virtual addresses
        self.versions = {"info": 20000404, "tpi": 20040203, "dbi": 19990903, "module": 4}
        self.debug = [NO_STREAM] * 5 + [5] + [NO_STREAM] * 5  # the section headers are stream 5

    def type(self, kind: int, data: bytes) -> int:
        """Adds a type record and returns its index."""
        self.types.append(struct.pack("<H", kind) + data)
        return 0x1000 + len(self.types) - 1

    def symbol(self, kind: int, data: bytes = b"") -> None:
        self.symbols.append(struct.pack("<H", kind) + data)

    def streams(self) -> list:
        """The old directory, info, TPI, DBI, IPI (nil), section header and module streams."""
        types = records(self.types)
        tpi = struct.pack("<5I2H8I", self.versions["tpi"], 56, 0x1000, 0x1000 + len(self.types), len(types),
                          NO_STREAM, NO_STREAM, 4, *[0] * 7) + types
        module = struct.pack("<I", self.versions["module"]) + records(self.symbols)
        modules = module_record(NO_STREAM, 0, "ab.obj") + module_record(6, len(module), "xx.obj")
        debug = struct.pack(f"<{len(self.debug)}H", *self.debug)
        dbi = struct.pack("<iII6H5iI2i2HI", -1, self.versions["dbi"], 1, NO_STREAM, 0, NO_STREAM, 0, NO_STREAM, 0,
                          len(modules), 0, 0, 0, 0, 0, len(debug), 0, 0, 0x14c, 0) + modules + debug
        sections = b"".join(struct.pack("<8s6I2HI", b".text", 0x100, address, 0, 0, 0, 0, 0, 0, 0)
                            for address in self.sections)
        info = struct.pack("<3I16s", self.versions["info"], 0, 1, bytes(16))
        return [b"", info, tpi, dbi, None, sections, module]

    def build(self) -> bytes:
        return msf(self.streams())


def pointer(pdb: Pdb, target: int, mode: int = 0, qualifiers: int = 0, owner: int | None = None) -> int:
    attributes = 0x0a | mode << 5 | (qualifiers & VOLATILE) << 8 | (qualifiers & CONST) << 10 | 4 << 13
    member = struct.pack("<IH", owner, 0) if owner is not None else b""
    return pdb.type(LF_POINTER, struct.pack("<II", target, attributes) + member)


def modifier(pdb: Pdb, target: int, qualifiers: int) -> int:
    return pdb.type(LF_MODIFIER, struct.pack("<IH", target, qualifiers))


def arglist(pdb: Pdb, arguments: tuple) -> int:
    return pdb.type(LF_ARGLIST, struct.pack(f"<{1 + len(arguments)}I", len(arguments), *arguments))


def procedure(pdb: Pdb, returned: int, *arguments: int) -> int:
    listed = arglist(pdb, arguments)
    return pdb.type(LF_PROCEDURE, struct.pack("<IBBHI", returned, 0, 0, len(arguments), listed))


def method(pdb: Pdb, returned: int, owner: int, *arguments: int) -> int:
    listed = arglist(pdb, arguments)
    return pdb.type(LF_MFUNCTION, struct.pack("<IIIBBHIi", returned, owner, 0, 0, 0, len(arguments), listed, 0))


def enumerate_member(text: str, value: int) -> bytes:
    return pads(struct.pack("<HH", LF_ENUMERATE, 3) + numeric(value) + name(text))


def index_member(target: int) -> bytes:
    return struct.pack("<HHI", LF_INDEX, 0, target)


def fieldlist(pdb: Pdb, *members: bytes) -> int:
    return pdb.type(LF_FIELDLIST, b"".join(members))


def enum_of(pdb: Pdb, text: str, fields: int, count: int = 0, forward: bool = False) -> int:
    return pdb.type(LF_ENUM, struct.pack("<HHII", count, 0x80 if forward else 0, T_INT4, fields) + name(text))


def enum(pdb: Pdb, text: str, enumerators: tuple = (), forward: bool = False) -> int:
    fields = 0 if forward else fieldlist(pdb, *(enumerate_member(*pair) for pair in enumerators))
    return enum_of(pdb, text, fields, len(enumerators), forward)


def udt(pdb: Pdb, kind: int, text: str, size: int, forward: bool = False) -> int:
    head = struct.pack("<HHI", 0, 0x80 if forward else 0, 0) + (b"" if kind == LF_UNION else bytes(8))
    return pdb.type(kind, head + numeric(size) + name(text))


def array(pdb: Pdb, element: int, size: int) -> int:
    return pdb.type(LF_ARRAY, struct.pack("<II", element, T_ULONG) + numeric(size) + name(""))


def proc(type_index: int, offset: int, segment: int, text: str) -> bytes:
    return struct.pack("<8IHB", 0, 0, 0, 16, 0, 0, type_index, offset, segment, 0) + name(text)


def constant(type_index: int, value: int, text: str) -> bytes:
    return struct.pack("<I", type_index) + numeric(value) + name(text)


def block() -> bytes:
    return struct.pack("<4IH", 0, 0, 0, 0, 1) + name("")


# Running the reader


def expect_error(action, message: str) -> list[str]:
    try:
        action()
    except pdbimport.PdbError as error:
        return [] if message in str(error) else [f"error {str(error)!r}, want {message!r}"]
    return [f"no error, want {message!r}"]


def types_of(pdb: Pdb) -> pdbimport.Types:
    return pdbimport.Types(pdbimport.Reader(pdb.streams()[2], "x.pdb: TPI stream"))


def imported(pdb: Pdb, mapping: str | None = None):
    """(counts without zeros, {file: text}, the loaded symbols) after importing PDB; the error text on a failure."""
    with tempfile.TemporaryDirectory() as temp:
        folder = Path(temp)
        source = folder / "x.pdb"
        source.write_bytes(pdb.build())
        map_path = None
        if mapping is not None:
            map_path = folder / "map.csv"
            map_path.write_bytes(mapping.encode("utf-8"))
        out = folder / "out"
        out.mkdir()
        try:
            counts = pdbimport.import_file(source, map_path, out)
        except pdbimport.PdbError as error:
            return str(error)
        texts = {file: (out / file).read_bytes().decode("utf-8") for file in symbols.FILES}
        return {key: value for key, value in counts.items() if value}, texts, symbols.load(out)


# Checks


def check_numeric() -> list[str]:
    failures = []
    cases = [(struct.pack("<H", 0x1234), 0x1234, 2),
             (struct.pack("<Hb", 0x8000, -2), -2, 3),
             (struct.pack("<Hh", 0x8001, -300), -300, 4),
             (struct.pack("<HH", 0x8002, 0xFFFF), 0xFFFF, 4),
             (struct.pack("<Hi", 0x8003, -70000), -70000, 6),
             (struct.pack("<HI", 0x8004, 0xFFFFFFFF), 0xFFFFFFFF, 6),
             (struct.pack("<Hq", 0x8009, -2 ** 40), -2 ** 40, 10),
             (struct.pack("<HQ", 0x800a, 2 ** 63), 2 ** 63, 10),
             (struct.pack("<H", 0x8017) + (-5).to_bytes(16, "little", signed=True), -5, 18),
             (struct.pack("<H", 0x8018) + (2 ** 100).to_bytes(16, "little"), 2 ** 100, 18),
             (struct.pack("<Hf", 0x8005, 1.5), None, 6),
             (struct.pack("<Hd", 0x8006, 1.5), None, 10),
             (struct.pack("<H", 0x8007) + bytes(10), None, 12),
             (struct.pack("<H", 0x8008) + bytes(16), None, 18),
             (struct.pack("<H", 0x800b) + bytes(6), None, 8),
             (struct.pack("<H", 0x800c) + bytes(8), None, 10),
             (struct.pack("<H", 0x800d) + bytes(16), None, 18),
             (struct.pack("<H", 0x800e) + bytes(20), None, 22),
             (struct.pack("<H", 0x800f) + bytes(32), None, 34),
             (struct.pack("<H", 0x801c) + bytes(2), None, 4),
             (struct.pack("<HH", 0x8010, 3) + b"abc", None, 7)]
    for data, value, end in cases:
        got = pdbimport.Reader(data + b"\0", "n").numeric(0)
        if got != (value, end):
            failures.append(f"numeric {data.hex()}: {got}, want {(value, end)}")
    failures += expect_error(lambda: pdbimport.Reader(struct.pack("<H", 0x8011), "n").numeric(0),
                             "n: unknown numeric leaf 0x8011 at offset 0x0")
    failures += expect_error(lambda: pdbimport.Reader(struct.pack("<HH", 0x8003, 1), "n").numeric(0),
                             "n: 4 bytes at offset 0x2 run past the end (0x4)")
    failures += expect_error(lambda: pdbimport.Reader(struct.pack("<Hf", 0x8005, 1.5), "n").integer(0),
                             "n: the value at offset 0x0 is not an integer")
    return failures


def check_reader() -> list[str]:
    failures = []
    reader = pdbimport.Reader(b"ab\0\xff\0\x01\x02\x03\x04", "r")
    if reader.string(0) != ("ab", 3) or reader.end_of_string(3) != 5:
        failures.append(f"string {reader.string(0)}")
    if (reader.u16(5), reader.u32(5)) != (0x0201, 0x04030201):
        failures.append(f"fields {reader.u16(5):#x} {reader.u32(5):#x}")
    failures += expect_error(lambda: reader.string(3), "r: the name at offset 0x3 is not UTF-8")
    failures += expect_error(lambda: pdbimport.Reader(b"ab", "r").string(0), "r: the name at offset 0x0 has no end")
    failures += expect_error(lambda: reader.u32(6), "r: 4 bytes at offset 0x6 run past the end (0x9)")
    return failures


def check_msf() -> list[str]:
    failures = []
    long = bytes(range(256)) * 5 + b"tail"  # three blocks of 512 bytes
    data = msf([long, None, b"abc"])
    found = pdbimport.Msf(data, "m")
    if found.stream(0, "long stream").data != long or found.stream(2, "short stream").data != b"abc":
        failures.append("the streams must read back whole")
    if len(found.stream(1, "nil stream")) != 0:
        failures.append("a nil stream must read as empty")
    if pdbimport.Msf(msf([long], block_size=4096), "m").stream(0, "long stream").data != long:
        failures.append("a stream in 4096-byte blocks must read back whole")
    many = msf([b"abc"] + [b""] * 16400)  # a directory of 129 blocks, so a block map of 2 blocks
    if struct.unpack_from("<I", many, 56)[0] == 0 or pdbimport.Msf(many, "m").stream(0, "first stream").data != b"abc":
        failures.append("a block map of two blocks must read")
    huge = data[:44] + struct.pack("<I", 512 * 128 * 116) + data[48:]
    failures += expect_error(lambda: pdbimport.Msf(huge, "m"),
                             "m: the block map needs 116 blocks, more than the superblock can name")
    failures += expect_error(lambda: found.stream(9, "module stream 9"),
                             "m: no stream 9 for the module stream 9: the file has 3 streams")
    failures += expect_error(lambda: pdbimport.Msf(b"Microsoft C/C++ program database 2.00\r\n" + bytes(600), "m"),
                             "m: not an MSF 7.00 file")
    odd = data[:32] + struct.pack("<I", 1000) + data[36:]
    failures += expect_error(lambda: pdbimport.Msf(odd, "m"),
                             "m: block size 1000 is not one of 512, 1024, 2048, 4096")
    map_block = struct.unpack_from("<I", data, 52)[0]
    short = data[:40] + struct.pack("<I", map_block) + data[44:]
    failures += expect_error(lambda: pdbimport.Msf(short, "m"),
                             f"m: block {map_block} is outside the file ({map_block} blocks)")
    failures += expect_error(lambda: pdbimport.Msf(data[:-512], "m"),
                             f"m: the header names {map_block + 1} blocks of 512 bytes, but the file holds "
                             f"{len(data) - 512} bytes")
    return failures


def check_versions() -> list[str]:
    failures = []
    for key, value, message in (
            ("info", 20030901, "x.pdb: info stream: version 20030901 is not supported: only VC70 (20000404)"),
            ("tpi", 19990903, "x.pdb: TPI stream: version 19990903 is not supported: only V80 (20040203)"),
            ("dbi", 19970606, "x.pdb: DBI stream: version 19970606 is not supported: only V70 (19990903)"),
            ("module", 1, "x.pdb: module stream 6: signature 1 is not supported: only C13 (4)")):
        pdb = Pdb()
        pdb.versions[key] = value
        got = imported(pdb)
        if not isinstance(got, str) or message not in got:
            failures.append(f"{key} version {value}: {got!r}, want {message!r}")
    return failures


def check_types() -> list[str]:
    failures = []
    one = records([struct.pack("<HIH", LF_MODIFIER, T_INT4, CONST)])

    def tpi(declared: int, data: bytes, count: int) -> pdbimport.Reader:
        header = struct.pack("<5I2H8I", 20040203, 56, 0x1000, 0x1000 + count, declared, NO_STREAM, NO_STREAM, 4,
                             *[0] * 7)
        return pdbimport.Reader(header + data, "t")

    types = pdbimport.Types(tpi(len(one), one, 1))
    if types.spell(0x1000) != "const int":
        failures.append(f"one record spells {types.spell(0x1000)!r}")
    failures += expect_error(lambda: pdbimport.Types(tpi(12, one[:9], 1)),
                             "t: 12 bytes at offset 0x38 run past the end (0x41)")
    failures += expect_error(lambda: pdbimport.Types(tpi(len(one), struct.pack("<H", 20) + one[2:], 1)),
                             "t: the record at offset 0x38 runs past the end of the records")
    failures += expect_error(lambda: pdbimport.Types(tpi(len(one), one, 2)),
                             "t: the header says 2 records, the stream holds 1")
    failures += expect_error(lambda: types.record(0x1005), "t: type 0x1005 is outside the type records (0x1000 to 0x1000)")
    return failures


def check_spellings() -> list[str]:
    failures = []
    pdb = Pdb()
    vector = udt(pdb, LF_STRUCTURE, "xx_vec", 0, forward=True)
    udt(pdb, LF_STRUCTURE, "xx_vec", 12)
    task = udt(pdb, LF_STRUCTURE, "xx_task", 0, forward=True)
    box = udt(pdb, LF_CLASS, "xx_box", 8)
    cell = udt(pdb, LF_UNION, "xx_cell", 4)
    mode = enum(pdb, "XX_MODE", (("XX_OFF", 0), ("XX_ON", 1)))
    text = pointer(pdb, T_RCHAR)
    const_text = pointer(pdb, modifier(pdb, T_RCHAR, CONST))
    const_mode = modifier(pdb, mode, CONST)
    mode_pointer = pointer(pdb, mode)
    cases = [(pointer(pdb, T_INT4, REFERENCE), "int &"),
             (pointer(pdb, T_INT4, RVALUE), "int &&"),
             (pointer(pdb, array(pdb, T_REAL32, 64)), "float (*)[16]"),
             (pointer(pdb, procedure(pdb, T_VOID, pointer(pdb, task))), "void (*)(struct xx_task *)"),
             (pointer(pdb, text), "char **"),
             (modifier(pdb, T_LONG, CONST), "const long"),
             (modifier(pdb, T_INT4, VOLATILE), "volatile int"),
             (const_text, "const char *"),
             (pointer(pdb, T_RCHAR, qualifiers=CONST), "char *const"),
             (pointer(pdb, pointer(pdb, T_RCHAR, qualifiers=CONST)), "char *const *"),
             (modifier(pdb, text, CONST), "char *const"),
             (modifier(pdb, modifier(pdb, text, VOLATILE), CONST), "char *volatile const"),
             (const_mode, "const enum XX_MODE"),
             (mode_pointer, "enum XX_MODE *"),
             (pointer(pdb, T_INT4, DATA_MEMBER, owner=box), "int xx_box::*"),
             (pointer(pdb, method(pdb, T_VOID, box, T_INT4), METHOD, owner=box), "void (xx_box::*)(int)"),
             (pointer(pdb, procedure(pdb, T_INT4, T_VOID)), "int (*)(void)"),
             (pointer(pdb, procedure(pdb, T_INT4)), "int (*)()"),
             (pointer(pdb, procedure(pdb, T_INT4, const_text, T_NOTYPE)), "int (*)(const char *, ...)"),
             (procedure(pdb, pointer(pdb, procedure(pdb, T_VOID, T_INT4)), T_RCHAR), "void (*(char))(int)"),
             (pointer(pdb, pointer(pdb, procedure(pdb, T_VOID, T_INT4))), "void (**)(int)"),
             (array(pdb, vector, 48), "struct xx_vec[4]"),
             (array(pdb, task, 48), "struct xx_task[?]"),
             (array(pdb, pointer(pdb, T_INT4), 16), "int *[4]"),
             (cell, "union xx_cell"),
             (box, "class xx_box"),
             (0x0423, "unsigned __int64 *"),
             (0x0031, "<simple 0x0031>"),
             (pdb.type(LF_BITFIELD, struct.pack("<IBB", T_INT4, 3, 0)), "<leaf 0x1205>")]
    deep = T_INT4
    for _ in range(70):
        deep = pointer(pdb, deep)
    types = types_of(pdb)
    for index, spelled in cases:
        if types.spell(index) != spelled:
            failures.append(f"type {index:#x} spells {types.spell(index)!r}, want {spelled!r}")
    slots = [types.slot(const_mode), types.slot(mode_pointer), types.slot(T_INT4)]
    if slots != ["enum XX_MODE", "enum XX_MODE *", "int"]:
        failures.append(f"slots {slots}")
    failures += expect_error(lambda: types.spell(deep), "nests deeper than 64 levels")
    return failures


def check_enums() -> list[str]:
    failures = []
    pdb = Pdb()
    tail = fieldlist(pdb, enumerate_member("XX_C", -5))
    head = fieldlist(pdb, enumerate_member("XX_A", 0), enumerate_member("XX_B", 0x9000), index_member(tail))
    enum_of(pdb, "XX_LIST", head, 3)
    first = enum(pdb, "XX_TWO", (("XX_X", 0),))
    enum(pdb, "XX_TWO", (("XX_Y", 0),))
    enum(pdb, "XX_SAME", (("XX_S", 1),))
    enum(pdb, "XX_SAME", (("XX_S", 1),))
    forward = enum(pdb, "XX_SAME", forward=True)
    member = fieldlist(pdb, struct.pack("<HHI", LF_MEMBER, 3, T_INT4) + numeric(0) + name("x"))
    enum_of(pdb, "XX_MEMBER", member, 1)
    pad = fieldlist(pdb, enumerate_member("XX_P", 0) + b"\xf0\0\0\0")
    enum_of(pdb, "XX_PAD", pad, 1)
    looping = 0x1000 + len(pdb.types)
    fieldlist(pdb, enumerate_member("XX_L", 0), index_member(looping))
    enum_of(pdb, "XX_LOOP", looping, 1)
    types = types_of(pdb)
    if types.enumerators("XX_LIST") != [(("XX_A", 0), ("XX_B", 0x9000), ("XX_C", -5))]:
        failures.append(f"a continued field list gives {types.enumerators('XX_LIST')}")
    if len(types.enumerators("XX_TWO")) != 2 or types.enumerators("XX_NONE") != []:
        failures.append("two different definitions must give two lists, none no list")
    if types.enumerators("XX_SAME") != [(("XX_S", 1),)] or types.enumerators_at(forward) != (("XX_S", 1),):
        failures.append(f"identical definitions give {types.enumerators('XX_SAME')}")
    if types.enumerators_at(first) != (("XX_X", 0),):
        failures.append(f"a definition's own enumerators {types.enumerators_at(first)}")
    failures += expect_error(lambda: types.enumerators("XX_MEMBER"),
                             f"type {member:#x}: leaf 0x150d at offset 0x2 in the field list of enum XX_MEMBER")
    failures += expect_error(lambda: types.enumerators("XX_PAD"), f"type {pad:#x}: pad byte 0xf0 at offset 0xe")
    failures += expect_error(lambda: types.enumerators("XX_LOOP"),
                             f"the field list of enum XX_LOOP loops at type {looping:#x}")
    return failures


def symbol_fixture() -> Pdb:
    """Two functions with prototypes, one with scope constants in two enums of one name; constants outside a function
    and inside an inline site, an enum-typed constant that is no enumerator and a constant of another type; a
    procedure outside every section and one with no function type."""
    pdb = Pdb()
    mode = enum(pdb, "XX_MODE", (("XX_OFF", 0), ("XX_ON", 1)))
    forward = enum(pdb, "XX_MODE", forward=True)
    step = enum(pdb, "XX_STEP", (("XX_INIT", 0), ("XX_RUN", 1)))
    other_step = modifier(pdb, enum(pdb, "XX_STEP", (("XX_WAIT", 5),)), CONST)
    update = procedure(pdb, T_INT4, modifier(pdb, forward, CONST), pointer(pdb, mode), T_NOTYPE)
    reset = procedure(pdb, T_VOID, T_VOID)
    pdb.symbol(S_CONSTANT, constant(step, 1, "XX_RUN"))
    pdb.symbol(S_GPROC32, proc(update, 0x10, 1, "xxUpdate"))
    pdb.symbol(S_CONSTANT, constant(step, 0, "XX_INIT"))
    pdb.symbol(S_BLOCK32, block())
    pdb.symbol(S_CONSTANT, constant(step, 1, "XX_RUN"))
    pdb.symbol(S_CONSTANT, constant(other_step, 5, "XX_WAIT"))
    pdb.symbol(S_CONSTANT, constant(step, 7, "xxLimit"))
    pdb.symbol(S_CONSTANT, constant(T_INT4, 3, "XX_COUNT"))
    pdb.symbol(S_CONSTANT, constant(step, 0, "XX_INIT"))
    pdb.symbol(S_INLINESITE, struct.pack("<3I", 0, 0, 0x1000))
    pdb.symbol(S_CONSTANT, constant(mode, 1, "XX_ON"))
    pdb.symbol(S_INLINESITE_END)
    pdb.symbol(S_END)
    pdb.symbol(S_END)
    pdb.symbol(S_LPROC32, proc(reset, 0x20, 2, "xxReset"))
    pdb.symbol(S_END)
    pdb.symbol(S_GPROC32, proc(reset, 0x30, 3, "xxOutside"))
    pdb.symbol(S_CONSTANT, constant(step, 0, "XX_INIT"))
    pdb.symbol(S_END)
    pdb.symbol(S_GPROC32, proc(T_NOTYPE, 0x40, 1, "xxUntyped"))
    pdb.symbol(S_END)
    return pdb


def check_symbols() -> list[str]:
    failures = []
    got = imported(symbol_fixture())
    if isinstance(got, str):
        return [f"the symbol fixture fails: {got}"]
    counts, texts, loaded = got
    want = {symbols.PROTOTYPES: "address,name,slot,type\n"
                                "0x00001010,xxUpdate,0,int\n"
                                "0x00001010,xxUpdate,1,enum XX_MODE\n"
                                "0x00001010,xxUpdate,2,enum XX_MODE *\n"
                                "0x00001010,xxUpdate,3,...\n"
                                "0x00008020,xxReset,0,void\n",
            symbols.ENUMS: "enum,name,value\nenum XX_MODE,XX_OFF,0\nenum XX_MODE,XX_ON,1\n",
            symbols.SCOPES: "address,scope,name,value\n"
                            "0x00001010,enum XX_STEP,XX_INIT,0\n"
                            "0x00001010,enum XX_STEP,XX_RUN,1\n"
                            "0x00001010,enum XX_STEP #2,XX_WAIT,5\n"}
    for file, text in want.items():
        if texts[file] != text:
            failures.append(f"{file}: {texts[file]!r}, want {text!r}")
    wanted = {pdbimport.FUNCTIONS: 2, pdbimport.SLOTS: 5, pdbimport.ENUM_COUNT: 1, pdbimport.ENUMERATORS: 2,
              pdbimport.SCOPE_CONSTANTS: 3, pdbimport.OUTSIDE: 1, pdbimport.UNTYPED: 1, pdbimport.NOT_ENUMERATOR: 1}
    if counts != wanted:
        failures.append(f"counts {counts}")
    described = pdbimport.describe(counts)
    if described != ("2 functions, 5 prototype slots, 1 enums, 2 enumerators, 3 scope constants; left out: "
                     "1 procedures outside every section, 1 procedures with no function type, "
                     "1 constants that are no enumerator of their enum"):
        failures.append(f"described {described!r}")
    if list(loaded.call_rows("0x00001010", "xxUpdate")) != [1]:
        failures.append(f"call rows {loaded.call_rows('0x00001010', 'xxUpdate')}")
    if loaded.parameters("0x00001010") != (("enum XX_MODE", "enum XX_MODE *"), True):
        failures.append(f"parameters {loaded.parameters('0x00001010')}")
    return failures


def check_balance() -> list[str]:
    failures = []
    extra, open_scope, ids = Pdb(), Pdb(), Pdb()
    extra.symbol(S_END)
    open_scope.symbol(S_GPROC32, proc(T_NOTYPE, 0, 1, "xxOpen"))
    ids.symbol(S_GPROC32_ID, proc(0x1000, 0, 1, "xxId"))
    for pdb, message in ((extra, "module stream 6: the end record at offset 0x4 closes no scope"),
                         (open_scope, "module stream 6: the symbols end inside an open scope (1 deep)"),
                         (ids, "the procedure at offset 0x4 keeps its type in the IPI stream (kind 0x1147), which "
                               "this reader does not support")):
        got = imported(pdb)
        if not isinstance(got, str) or message not in got:
            failures.append(f"symbols {got!r}, want {message!r}")
    return failures


def check_map() -> list[str]:
    failures = []
    got = imported(symbol_fixture(), "reference,target\n0x1010,0x00401000\n")
    if isinstance(got, str):
        return [f"the mapped fixture fails: {got}"]
    counts, texts, _ = got
    if not texts[symbols.PROTOTYPES].startswith("address,name,slot,type\n0x00401000,xxUpdate,0,int\n"):
        failures.append(f"mapped prototypes {texts[symbols.PROTOTYPES]!r}")
    if "xxReset" in texts[symbols.PROTOTYPES] or counts.get(pdbimport.UNMAPPED) != 1:
        failures.append(f"an RVA outside the map must be left out and counted: {counts}")
    if not texts[symbols.SCOPES].endswith("0x00401000,enum XX_STEP #2,XX_WAIT,5\n"):
        failures.append(f"mapped scope constants {texts[symbols.SCOPES]!r}")
    for mapping, message in (("reference,target\n0x1010,0x00401000\n0x1010,0x00402000\n",
                              "map.csv:3: reference 0x00001010 is also at"),
                             ("reference,target\n0x1010,0x00401000\n0x8020,0x00401000\n",
                              "map.csv:3: target 0x00401000 is also at"),
                             ("ref,target\n", "map.csv: the columns must be reference,target"),
                             ("reference,target\nzz,0x1\n", "map.csv:2: 'zz' is not a hex address")):
        got = imported(symbol_fixture(), mapping)
        if not isinstance(got, str) or message not in got:
            failures.append(f"map {mapping!r}: {got!r}, want {message!r}")
    with tempfile.TemporaryDirectory() as temp:
        failures += expect_error(lambda: pdbimport.read_map(Path(temp) / "none.csv"), "none.csv")
        failures += expect_error(lambda: pdbimport.import_file(Path(temp) / "x.pdb", None, Path(temp) / "missing"),
                                 "missing does not exist")
        failures += expect_error(lambda: pdbimport.import_file(Path(temp) / "x.pdb", None, Path(temp)), "x.pdb")
    return failures


def check_addresses() -> list[str]:
    pdb = Pdb()
    reset = procedure(pdb, T_VOID, T_VOID)
    for offset, text in ((0x10, "xxOne"), (0x10, "xxTwo"), (0x20, "xxSame"), (0x20, "xxSame")):
        pdb.symbol(S_GPROC32, proc(reset, offset, 1, text))
        pdb.symbol(S_END)
    got = imported(pdb)
    if isinstance(got, str):
        return [f"the address fixture fails: {got}"]
    counts, texts, _ = got
    failures = []
    if texts[symbols.PROTOTYPES] != "address,name,slot,type\n0x00001020,xxSame,0,void\n":
        failures.append(f"shared addresses give {texts[symbols.PROTOTYPES]!r}")
    if counts.get(pdbimport.DIFFERENT) != 1 or counts.get(pdbimport.FUNCTIONS) != 1:
        failures.append(f"shared address counts {counts}")
    return failures


def check_dbi() -> list[str]:
    failures = []
    omap, bare, unnamed = Pdb(), Pdb(), Pdb()
    omap.debug[4] = 7
    bare.debug = [NO_STREAM] * 5
    unnamed.debug[5] = NO_STREAM
    for pdb, message in ((omap, "x.pdb: DBI stream: the file holds an address map (OMAP), which this reader does "
                                "not support"),
                         (bare, "x.pdb: DBI stream: the optional debug header names no section header stream"),
                         (unnamed, "x.pdb: DBI stream: the optional debug header names no section header stream")):
        got = imported(pdb)
        if not isinstance(got, str) or message not in got:
            failures.append(f"debug header {pdb.debug}: {got!r}, want {message!r}")
    return failures


def check_selftest() -> list[str]:
    """The prototypes of the self-test program, when build/SELFTEST.pdb exists. The runtime library that it links
    gives enum slots and scope constants too."""
    if not SELFTEST.is_file():
        return []
    with tempfile.TemporaryDirectory() as temp:
        out = Path(temp)
        try:
            counts = pdbimport.import_file(SELFTEST, None, out)
        except pdbimport.PdbError as error:
            return [f"{SELFTEST.name}: {error}"]
        symbols.load(out)
        found = {}
        with (out / symbols.PROTOTYPES).open(encoding="utf-8", newline="") as data:
            for row in csv.DictReader(data):
                found.setdefault((row["address"], row["name"]), []).append(row["type"])
    slots = {}
    for (_, function), types in found.items():
        slots.setdefault(function, set()).add(tuple(types))
    failures = [f"{SELFTEST.name}: {function} has {sorted(slots.get(function, ()))}, want {wanted}"
                for function, wanted in SELFTEST_SLOTS.items() if wanted not in slots.get(function, ())]
    if not counts[pdbimport.ENUM_COUNT] or not counts[pdbimport.SCOPE_CONSTANTS]:
        failures.append(f"{SELFTEST.name}: no enums or no scope constants: {pdbimport.describe(counts)}")
    return failures


def run() -> list[str]:
    failures = []
    for check in (check_numeric, check_reader, check_msf, check_versions, check_types, check_spellings, check_enums,
                  check_symbols, check_balance, check_map, check_addresses, check_dbi, check_selftest):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    for failure in found:
        print(failure)
    if not SELFTEST.is_file():
        print(f"pdbimporttests: {SELFTEST.name} is missing, so its check is skipped")
    if not found:
        print("pdbimporttests: all passed")
    sys.exit(1 if found else 0)
