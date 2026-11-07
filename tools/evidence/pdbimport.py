"""Reads a program database (a PDB file) and writes the three neutral symbol files of symbols.py: prototypes.csv,
enums.csv and scope-constants.csv.

Written from the public format descriptions only (all fields little-endian):
- the PDB pages of the LLVM project, https://llvm.org/docs/PDB/ (MsfFile, PdbStream, TpiStream, DbiStream,
  ModiStream, CodeViewTypes, CodeViewSymbols);
- cvinfo.h in https://github.com/microsoft/microsoft-pdb (include/cvinfo.h): the record kinds and their fields;
- msf.cpp in the same repository (PDB/msf/msf.cpp, BIGMSF_HDR): a block map of more than one block;
- the PE format, https://learn.microsoft.com/windows/win32/debug/pe-format: the section headers.

What it reads:
- the MSF 7.00 container: the superblock, the block map (one or more blocks) and the stream directory;
- the info stream, version VC70 only;
- the type stream (TPI), version V80 only: function types, argument lists, pointers, modifiers, arrays, classes,
  structs, unions, enums and the enumerators of their field lists;
- the DBI stream, version V70 only: the module list, and the section headers that its optional debug header names;
- the symbols of each module, signature C13 only: procedures, constants and the scopes that nest them. A constant
  inside an inline site belongs to the inlined function, so it does not count for the procedure around it.

A function's address is its RVA: the virtual address of its section plus its offset. A map with the columns
reference,target (hex) turns each RVA into a target address. Left out, and counted (describe() prints the counts):
- a procedure outside every section, or with no function type;
- an RVA outside the map;
- an address of several different procedures (identical code that the linker folded into one);
- a constant of an enum type that is no enumerator of that enum, or whose enum has no single definition.
An enum with several different definitions, or with none, gives no enums.csv rows.

Anything else that this reader does not support fails with a clear error: other versions, an address map (OMAP), and
procedures that keep their type in the IPI stream (the _ID records).

Standard library only.
"""

import struct
import sys
from collections import Counter
from dataclasses import dataclass
from pathlib import Path

import outputs
import symbols

sys.path.append(str(Path(__file__).resolve().parents[1]))  # tools/, after the standard library
import osutil  # noqa: E402

MAGIC = b"Microsoft C/C++ MSF 7.00\r\n\x1aDS\0\0\0"
BLOCK_SIZES = (512, 1024, 2048, 4096)
BLOCK_MAP = 52  # the superblock offset of the block numbers of the block map, which lists the directory blocks
NIL = 0xFFFFFFFF  # the size of a nil stream
NO_STREAM = 0xFFFF
INFO, TPI, DBI = 1, 2, 3  # fixed stream indices
VC70, TPI_V80, DBI_V70, C13 = 20000404, 20040203, 19990903, 4
DBI_HEADER = 64  # bytes
MODULE_HEADER = 64  # bytes before the names of a module record
SECTION_HEADER = 40  # bytes
DBI_SUBSTREAMS = (24, 28, 32, 36, 40, 52)  # the offsets of the sizes of the substreams before the optional debug header
OMAP_TO_SOURCE, OMAP_FROM_SOURCE, SECTION_HEADERS = 3, 4, 5  # entries of the optional debug header
MAX_DEPTH = 64  # type nesting
MAP_COLUMNS = ("reference", "target")

T_NOTYPE, T_VOID = 0x0000, 0x0003
SIMPLE = {0x03: ("void", None), 0x08: ("HRESULT", 4), 0x10: ("signed char", 1), 0x20: ("unsigned char", 1),
          0x70: ("char", 1), 0x71: ("wchar_t", 2), 0x11: ("short", 2), 0x21: ("unsigned short", 2),
          0x12: ("long", 4), 0x22: ("unsigned long", 4), 0x74: ("int", 4), 0x75: ("unsigned int", 4),
          0x13: ("__int64", 8), 0x23: ("unsigned __int64", 8), 0x40: ("float", 4), 0x41: ("double", 8),
          0x30: ("bool", 1)}  # simple type kind -> (spelling, size)
SIMPLE_POINTERS = {4: 4, 6: 8}  # simple type mode -> pointer size: near 32-bit, near 64-bit

LF_MODIFIER, LF_POINTER, LF_PROCEDURE, LF_MFUNCTION = 0x1001, 0x1002, 0x1008, 0x1009
LF_ARGLIST, LF_FIELDLIST, LF_INDEX, LF_ENUMERATE = 0x1201, 0x1203, 0x1404, 0x1502
LF_ARRAY, LF_CLASS, LF_STRUCTURE, LF_UNION, LF_ENUM = 0x1503, 0x1504, 0x1505, 0x1506, 0x1507
TAGS = {LF_CLASS: "class", LF_STRUCTURE: "struct", LF_UNION: "union", LF_ENUM: "enum"}
SIZE_AT = {LF_CLASS: 18, LF_STRUCTURE: 18, LF_UNION: 10}  # the offset of the size of a class, struct or union
ARGUMENT_LISTS = {LF_PROCEDURE: 10, LF_MFUNCTION: 18}  # the offset of the argument list of a function type
FORWARD = 0x80  # the property bit of a forward reference
POINTER_MARKS = {0: "*", 1: "&", 4: "&&"}  # pointer mode -> mark
MEMBER_MODES = (2, 3)  # pointer to data member, pointer to member function
POINTER_QUALIFIERS = ((1 << 10, "const"), (1 << 9, "volatile"))
MODIFIER_QUALIFIERS = ((1, "const"), (2, "volatile"))
PAD = 0xF0  # field list pad bytes are 0xF1 to 0xFF: the low 4 bits count the bytes to skip

INTEGER_LEAVES = {0x8000: (1, True), 0x8001: (2, True), 0x8002: (2, False), 0x8003: (4, True), 0x8004: (4, False),
                  0x8009: (8, True), 0x800a: (8, False), 0x8017: (16, True),
                  0x8018: (16, False)}  # numeric leaf -> (width, signed)
OTHER_LEAVES = {0x8005: 4, 0x8006: 8, 0x8007: 10, 0x8008: 16, 0x800b: 6, 0x800c: 8, 0x800d: 16, 0x800e: 20,
                0x800f: 32, 0x801c: 2}  # real and complex numeric leaves -> width
LF_VARSTRING = 0x8010

S_END, S_CONSTANT = 0x0006, 0x1107
PROCEDURES = (0x110f, 0x1110)  # S_LPROC32, S_GPROC32
ID_PROCEDURES = (0x1146, 0x1147)  # S_LPROC32_ID, S_GPROC32_ID
INLINE_SITES = (0x114d, 0x115d)  # S_INLINESITE, S_INLINESITE2: the code of another function, inlined here
OPENERS = PROCEDURES + (0x1102, 0x1103, 0x1104, 0x1132) + INLINE_SITES  # thunk, block, with, separated code
CLOSERS = (S_END, 0x114f, 0x114e)  # S_END, S_PROC_ID_END, S_INLINESITE_END
U16, U32 = struct.Struct("<H"), struct.Struct("<I")

FUNCTIONS, SLOTS, ENUM_COUNT = "functions", "prototype slots", "enums"
ENUMERATORS, SCOPE_CONSTANTS = "enumerators", "scope constants"
OUTSIDE = "procedures outside every section"
UNTYPED = "procedures with no function type"
UNMAPPED = "addresses outside the map"
DIFFERENT = "addresses with different procedures"
NOT_ENUMERATOR = "constants that are no enumerator of their enum"
UNKNOWN_ENUM = "constants of an enum with no single definition"
AMBIGUOUS_ENUM = "enums with different definitions"
UNDEFINED_ENUM = "enums with no definition"
WRITTEN = (FUNCTIONS, SLOTS, ENUM_COUNT, ENUMERATORS, SCOPE_CONSTANTS)
LEFT_OUT = (OUTSIDE, UNTYPED, UNMAPPED, DIFFERENT, NOT_ENUMERATOR, UNKNOWN_ENUM, AMBIGUOUS_ENUM, UNDEFINED_ENUM)


class PdbError(Exception):
    """The file is malformed, or holds something that this reader does not support."""


class Reader:
    """The little-endian fields of one byte string. A field past its end fails with the name and the offset."""

    def __init__(self, data: bytes, name: str):
        self.data = data
        self.name = name

    def __len__(self) -> int:
        return len(self.data)

    def check(self, offset: int, size: int) -> None:
        if offset + size > len(self.data):
            raise PdbError(f"{self.name}: {size} bytes at offset {offset:#x} run past the end ({len(self.data):#x})")

    def u16(self, offset: int) -> int:
        self.check(offset, 2)
        return U16.unpack_from(self.data, offset)[0]

    def u32(self, offset: int) -> int:
        self.check(offset, 4)
        return U32.unpack_from(self.data, offset)[0]

    def take(self, offset: int, size: int) -> bytes:
        self.check(offset, size)
        return self.data[offset:offset + size]

    def end_of_string(self, offset: int) -> int:
        """The offset after the NUL byte that ends the string at OFFSET."""
        stop = self.data.find(b"\0", offset)
        if stop < 0:
            raise PdbError(f"{self.name}: the name at offset {offset:#x} has no end")
        return stop + 1

    def string(self, offset: int) -> tuple[str, int]:
        """The UTF-8 string at OFFSET, and the offset after it."""
        end = self.end_of_string(offset)
        try:
            return self.data[offset:end - 1].decode("utf-8"), end
        except UnicodeDecodeError:
            raise PdbError(f"{self.name}: the name at offset {offset:#x} is not UTF-8") from None

    def numeric(self, offset: int) -> tuple[int | None, int]:
        """The value of the numeric leaf at OFFSET, and the offset after it. None for a real, complex or string
        leaf."""
        leaf = self.u16(offset)
        if leaf < 0x8000:
            return leaf, offset + 2
        if leaf in INTEGER_LEAVES:
            width, signed = INTEGER_LEAVES[leaf]
            return int.from_bytes(self.take(offset + 2, width), "little", signed=signed), offset + 2 + width
        if leaf in OTHER_LEAVES:
            self.check(offset + 2, OTHER_LEAVES[leaf])
            return None, offset + 2 + OTHER_LEAVES[leaf]
        if leaf == LF_VARSTRING:
            length = self.u16(offset + 2)
            self.check(offset + 4, length)
            return None, offset + 4 + length
        raise PdbError(f"{self.name}: unknown numeric leaf {leaf:#06x} at offset {offset:#x}")

    def integer(self, offset: int) -> tuple[int, int]:
        """The integer value of the numeric leaf at OFFSET, and the offset after it."""
        value, end = self.numeric(offset)
        if value is None:
            raise PdbError(f"{self.name}: the value at offset {offset:#x} is not an integer")
        return value, end


class Msf:
    """The streams of an MSF 7.00 file."""

    def __init__(self, data: bytes, name: str):
        if data[:len(MAGIC)] != MAGIC:
            raise PdbError(f"{name}: not an MSF 7.00 file")
        self.data = data
        self.name = name
        header = Reader(data, name)
        self.block_size = header.u32(32)
        self.blocks = header.u32(40)
        if self.block_size not in BLOCK_SIZES:
            raise PdbError(f"{name}: block size {self.block_size} is not one of {', '.join(map(str, BLOCK_SIZES))}")
        if self.blocks * self.block_size > len(data):
            raise PdbError(f"{name}: the header names {self.blocks} blocks of {self.block_size} bytes, but the file "
                           f"holds {len(data)} bytes")
        directory_size = header.u32(44)
        directory_count = self._block_count(directory_size)
        map_count = self._block_count(4 * directory_count)
        if BLOCK_MAP + 4 * map_count > self.block_size:
            raise PdbError(f"{name}: the block map needs {map_count} blocks, more than the superblock can name")
        map_blocks = [header.u32(BLOCK_MAP + 4 * position) for position in range(map_count)]
        block_map = Reader(self._join(map_blocks, 4 * directory_count), f"{name}: block map")
        directory_blocks = [block_map.u32(4 * position) for position in range(directory_count)]
        directory = Reader(self._join(directory_blocks, directory_size), f"{name}: stream directory")
        sizes = [directory.u32(4 + 4 * position) for position in range(directory.u32(0))]
        self.streams = []  # (blocks, size) per stream
        offset = 4 + 4 * len(sizes)
        for size in sizes:
            size = 0 if size == NIL else size
            count = self._block_count(size)
            self.streams.append(([directory.u32(offset + 4 * position) for position in range(count)], size))
            offset += 4 * count

    def stream(self, index: int, what: str) -> Reader:
        """Stream INDEX, named WHAT in errors."""
        if index >= len(self.streams):
            raise PdbError(f"{self.name}: no stream {index} for the {what}: the file has {len(self.streams)} streams")
        blocks, size = self.streams[index]
        return Reader(self._join(blocks, size), f"{self.name}: {what}")

    def _block_count(self, size: int) -> int:
        return (size + self.block_size - 1) // self.block_size

    def _block_offset(self, block: int) -> int:
        if block >= self.blocks:
            raise PdbError(f"{self.name}: block {block} is outside the file ({self.blocks} blocks)")
        return block * self.block_size

    def _join(self, blocks: list, size: int) -> bytes:
        """The first SIZE bytes of BLOCKS, joined."""
        view = memoryview(self.data)
        starts = [self._block_offset(block) for block in blocks]
        return b"".join(view[start:start + self.block_size] for start in starts)[:size]


class Types:
    """The type records of a TPI stream, and how C spells them."""

    def __init__(self, tpi: Reader):
        self.name = tpi.name
        version = tpi.u32(0)
        if version != TPI_V80:
            raise PdbError(f"{tpi.name}: version {version} is not supported: only V80 ({TPI_V80})")
        header_size = tpi.u32(4)
        self.begin = tpi.u32(8)
        self.end = tpi.u32(12)
        record_bytes = tpi.u32(16)
        tpi.check(header_size, record_bytes)
        self.records = list(_type_records(tpi, header_size, header_size + record_bytes))
        if len(self.records) != self.end - self.begin:
            raise PdbError(f"{tpi.name}: the header says {self.end - self.begin} records, the stream holds "
                           f"{len(self.records)}")
        self.enum_fields = {}  # enum name -> the field list of each definition
        self.sizes = {}  # class, struct or union name -> the sizes of its definitions
        for index in range(self.begin, self.end):
            record = self.record(index)
            kind = record.u16(0)
            if kind not in TAGS or record.u16(4) & FORWARD:
                continue
            if kind == LF_ENUM:
                self.enum_fields.setdefault(_tag_name(record), []).append(record.u32(10))
            else:
                self.sizes.setdefault(_tag_name(record), set()).add(record.integer(SIZE_AT[kind])[0])

    def record(self, index: int) -> Reader:
        """The kind and data of type record INDEX."""
        if not self.begin <= index < self.end:
            raise PdbError(f"{self.name}: type {index:#x} is outside the type records ({self.begin:#x} to "
                           f"{self.end - 1:#x})")
        return Reader(self.records[index - self.begin], f"{self.name}: type {index:#x}")

    def kind(self, index: int) -> int | None:
        """The leaf kind of type INDEX; None for a simple type."""
        return None if index < self.begin else self.record(index).u16(0)

    def unmodified(self, index: int) -> int:
        """Type INDEX without its modifiers (const, volatile)."""
        for _ in range(MAX_DEPTH):
            if self.kind(index) != LF_MODIFIER:
                return index
            index = self.record(index).u32(2)
        raise PdbError(f"{self.name}: type {index:#x} nests deeper than {MAX_DEPTH} levels")

    def enum_name(self, index: int) -> str:
        """`enum NAME` for the enum record INDEX."""
        return symbols.ENUM_PREFIX + _tag_name(self.record(index))

    def enumerators(self, name: str) -> list:
        """The enumerators ((name, value) pairs) of each distinct definition of enum NAME."""
        return list(dict.fromkeys(self._fields(field, f"enum {name}") for field in self.enum_fields.get(name, ())))

    def enumerators_at(self, index: int) -> tuple | None:
        """The enumerators of the enum record INDEX. A forward reference takes those of the enum's one definition;
        None when the enum has no single definition."""
        record = self.record(index)
        name = _tag_name(record)
        if not record.u16(4) & FORWARD:
            return self._fields(record.u32(10), f"enum {name}")
        definitions = self.enumerators(name)
        return definitions[0] if len(definitions) == 1 else None

    def slot(self, index: int) -> str:
        """Type INDEX as a prototype slot spells it: `enum NAME` for an enum, also under modifiers; else spell()."""
        base = self.unmodified(index)
        return self.enum_name(base) if self.kind(base) == LF_ENUM else self.spell(index)

    def spell(self, index: int, depth: int = 0) -> str:
        """Type INDEX as C spells it in a cast: `int *`, `const struct Vec3 &`, `void (*)(int)`."""
        left, right = self._parts(index, depth)
        return left + right

    def signature(self, index: int) -> tuple | None:
        """The slot spellings of function type INDEX, the return first and `...` last for a variadic function; None
        for a type that is no function."""
        kind = self.kind(index)
        if kind not in ARGUMENT_LISTS:
            return None
        record = self.record(index)
        arguments = self._arguments(record.u32(ARGUMENT_LISTS[kind]))
        parameters, variadic = _split_variadic([] if arguments == [T_VOID] else arguments)
        slots = [self.slot(record.u32(2))] + [self.slot(parameter) for parameter in parameters]
        return tuple(slots + [symbols.VARIADIC] if variadic else slots)

    def size(self, index: int) -> int | None:
        """The size of type INDEX in bytes; None when unknown."""
        index = self.unmodified(index)
        if index < self.begin:
            return _simple_size(index)
        record = self.record(index)
        kind = record.u16(0)
        if kind == LF_POINTER:
            return (record.u32(6) >> 13) & 0x3F
        if kind == LF_ARRAY:
            return record.integer(10)[0]
        if kind == LF_ENUM:
            return self.size(record.u32(6))
        if kind not in SIZE_AT:
            return None
        if not record.u16(4) & FORWARD:
            return record.integer(SIZE_AT[kind])[0]
        sizes = self.sizes.get(_tag_name(record), set())
        return next(iter(sizes)) if len(sizes) == 1 else None

    def _parts(self, index: int, depth: int) -> tuple[str, str]:
        """The spelling of type INDEX split where a declarator would go: `float (*` and `)[16]`."""
        if depth > MAX_DEPTH:
            raise PdbError(f"{self.name}: type {index:#x} nests deeper than {MAX_DEPTH} levels")
        if index < self.begin:
            return _simple(index), ""
        record = self.record(index)
        kind = record.u16(0)
        if kind == LF_MODIFIER:
            return self._modified(record, depth)
        if kind == LF_POINTER:
            return self._pointer(record, depth)
        if kind == LF_ARRAY:
            left, right = self._parts(record.u32(2), depth + 1)
            return left, f"[{self._count(record)}]{right}"
        if kind in ARGUMENT_LISTS:
            left, right = self._parts(record.u32(2), depth + 1)
            return left, f"({self._argument_text(record.u32(ARGUMENT_LISTS[kind]), depth)}){right}"
        if kind in TAGS:
            return f"{TAGS[kind]} {_tag_name(record)}", ""
        return f"<leaf {kind:#06x}>", ""

    def _modified(self, record: Reader, depth: int) -> tuple[str, str]:
        """A modifier: before its type (`const int`), or after the mark of a pointer (`char *const`)."""
        target = record.u32(2)
        qualifiers = _qualifiers(record.u16(6), MODIFIER_QUALIFIERS)
        left, right = self._parts(target, depth + 1)
        if not qualifiers:
            return left, right
        if self._is_pointer(target):
            return f"{left}{_joint(left)}{qualifiers}", right
        return f"{qualifiers} {left}", right

    def _is_pointer(self, index: int) -> bool:
        index = self.unmodified(index)
        if index < self.begin:
            return index >> 8 != 0
        return self.kind(index) == LF_POINTER

    def _pointer(self, record: Reader, depth: int) -> tuple[str, str]:
        """A pointer or reference: its mark and qualifiers after its type, in parentheses before an array or
        function part."""
        attributes = record.u32(6)
        mode = (attributes >> 5) & 7
        if mode in MEMBER_MODES:
            mark = self._class_name(record.u32(10)) + "::*"
        elif mode in POINTER_MARKS:
            mark = POINTER_MARKS[mode]
        else:
            raise PdbError(f"{record.name}: pointer mode {mode} is not supported")
        mark += _qualifiers(attributes, POINTER_QUALIFIERS)
        left, right = self._parts(record.u32(2), depth + 1)
        if right.startswith(("(", "[")):
            return f"{left}{_joint(left)}({mark}", f"){right}"
        return f"{left}{_joint(left)}{mark}", right

    def _class_name(self, index: int) -> str:
        """The name of the class that a member pointer belongs to."""
        index = self.unmodified(index)
        if self.kind(index) in SIZE_AT:
            return _tag_name(self.record(index))
        return self.spell(index)

    def _count(self, record: Reader) -> int | str:
        """The element count of an array record; `?` when the element size is unknown."""
        total = record.integer(10)[0]
        element = self.size(record.u32(2))
        if not element or total % element:
            return "?"
        return total // element

    def _argument_text(self, index: int, depth: int) -> str:
        arguments = self._arguments(index)
        if arguments == [T_VOID]:
            return "void"
        parameters, variadic = _split_variadic(arguments)
        spelled = [self.spell(parameter, depth + 1) for parameter in parameters]
        return ", ".join(spelled + [symbols.VARIADIC] if variadic else spelled)

    def _arguments(self, index: int) -> list:
        """The type indices of argument list INDEX."""
        record = self.record(index)
        if record.u16(0) != LF_ARGLIST:
            raise PdbError(f"{record.name}: not an argument list")
        return [record.u32(6 + 4 * position) for position in range(record.u32(2))]

    def _fields(self, index: int, owner: str) -> tuple:
        """The enumerators of field list INDEX and the lists that it continues in, as (name, value) pairs."""
        members, seen = [], set()
        while index is not None:
            if index in seen:
                raise PdbError(f"{self.name}: the field list of {owner} loops at type {index:#x}")
            seen.add(index)
            record = self.record(index)
            if record.u16(0) != LF_FIELDLIST:
                raise PdbError(f"{record.name}: not a field list")
            index, offset = None, 2
            while offset < len(record):
                pad = record.data[offset]
                if pad == PAD:
                    raise PdbError(f"{record.name}: pad byte {pad:#04x} at offset {offset:#x}")
                if pad > PAD:
                    offset += pad & 0x0F
                    continue
                leaf = record.u16(offset)
                if leaf == LF_ENUMERATE:
                    value, name_at = record.integer(offset + 4)
                    name, offset = record.string(name_at)
                    members.append((name, value))
                elif leaf == LF_INDEX:
                    index = record.u32(offset + 4)
                    offset += 8
                else:
                    raise PdbError(f"{record.name}: leaf {leaf:#06x} at offset {offset:#x} in the field list of "
                                   f"{owner}")
        return tuple(members)


def _type_records(tpi: Reader, offset: int, stop: int):
    """The kind and data of each type record from OFFSET to STOP."""
    while offset < stop:
        length = tpi.u16(offset) if offset + 4 <= stop else 0
        if length < 2 or offset + 2 + length > stop:
            raise PdbError(f"{tpi.name}: the record at offset {offset:#x} runs past the end of the records")
        yield tpi.data[offset + 2:offset + 2 + length]
        offset += 2 + length


def _tag_name(record: Reader) -> str:
    """The name of a class, struct, union or enum record."""
    kind = record.u16(0)
    name_at = 14 if kind == LF_ENUM else record.numeric(SIZE_AT[kind])[1]
    return record.string(name_at)[0]


def _simple(index: int) -> str:
    entry = SIMPLE.get(index & 0xFF)
    mode = index >> 8
    if entry is None or mode and mode not in SIMPLE_POINTERS:
        return f"<simple {index:#06x}>"
    return entry[0] + " *" if mode else entry[0]


def _simple_size(index: int) -> int | None:
    mode = index >> 8
    if mode:
        return SIMPLE_POINTERS.get(mode)
    return SIMPLE.get(index, (None, None))[1]


def _split_variadic(arguments: list) -> tuple[list, bool]:
    """ARGUMENTS without the no-type entry that ends a variadic list, and whether it was there."""
    if arguments[-1:] == [T_NOTYPE]:
        return arguments[:-1], True
    return arguments, False


def _joint(left: str) -> str:
    """What goes between LEFT and a pointer mark or qualifier: nothing after another mark, else a space."""
    return "" if left.endswith(("*", "&")) else " "


def _qualifiers(bits: int, table: tuple) -> str:
    return " ".join(word for bit, word in table if bits & bit)


# Symbols


@dataclass(frozen=True)
class Function:
    """One procedure: its name, its prototype slots and the enum constants declared inside it."""
    name: str
    slots: tuple
    constants: tuple  # (scope, name, value) per constant


def read_functions(msf: Msf, types: Types, counts: Counter) -> dict:
    """RVA -> [Function] for the procedures of every module."""
    modules, sections = _read_dbi(msf)
    found = {}
    for index, size in modules:
        stream = msf.stream(index, f"module stream {index}")
        for rva, function in _module_functions(stream, size, types, sections, counts):
            found.setdefault(rva, []).append(function)
    return found


def _read_dbi(msf: Msf) -> tuple[list, list]:
    """The (stream, symbol bytes) of each module with symbols, and the virtual address of each section."""
    dbi = msf.stream(DBI, "DBI stream")
    version = dbi.u32(4)
    if version != DBI_V70:
        raise PdbError(f"{dbi.name}: version {version} is not supported: only V70 ({DBI_V70})")
    modules = []
    offset, stop = DBI_HEADER, DBI_HEADER + dbi.u32(24)
    while offset < stop:
        stream, size = dbi.u16(offset + 34), dbi.u32(offset + 36)
        if stream != NO_STREAM and size:
            modules.append((stream, size))
        names_end = dbi.end_of_string(dbi.end_of_string(offset + MODULE_HEADER))  # the module and object names
        offset = (names_end + 3) & ~3  # the records align to 4 bytes
    debug_at = DBI_HEADER + sum(dbi.u32(at) for at in DBI_SUBSTREAMS)
    debug_size = dbi.u32(48)
    dbi.check(debug_at, debug_size)
    debug = [dbi.u16(debug_at + 2 * entry) for entry in range(debug_size // 2)]
    if any(stream != NO_STREAM for stream in debug[OMAP_TO_SOURCE:OMAP_FROM_SOURCE + 1]):
        raise PdbError(f"{dbi.name}: the file holds an address map (OMAP), which this reader does not support")
    if len(debug) <= SECTION_HEADERS or debug[SECTION_HEADERS] == NO_STREAM:
        raise PdbError(f"{dbi.name}: the optional debug header names no section header stream")
    headers = msf.stream(debug[SECTION_HEADERS], "section header stream")
    sections = [headers.u32(SECTION_HEADER * position + 12) for position in range(len(headers) // SECTION_HEADER)]
    return modules, sections


def _module_functions(stream: Reader, size: int, types: Types, sections: list, counts: Counter):
    """(RVA, Function) per top-level procedure in the symbols of one module, which take its first SIZE bytes."""
    signature = stream.u32(0)
    if signature != C13:
        raise PdbError(f"{stream.name}: signature {signature} is not supported: only C13 ({C13})")
    stream.check(0, size)
    scopes, current, constants = [], None, []  # the kind of each open scope, innermost last
    offset = 4
    while offset < size:
        length = stream.u16(offset) if offset + 4 <= size else 0
        end = offset + 2 + length
        if length < 2 or end > size:
            raise PdbError(f"{stream.name}: the record at offset {offset:#x} runs past the end of the symbols")
        kind = stream.u16(offset + 2)
        if kind in ID_PROCEDURES:
            raise PdbError(f"{stream.name}: the procedure at offset {offset:#x} keeps its type in the IPI stream "
                           f"(kind {kind:#06x}), which this reader does not support")
        if kind in CLOSERS:
            if not scopes:
                raise PdbError(f"{stream.name}: the end record at offset {offset:#x} closes no scope")
            scopes.pop()
            if not scopes and current is not None:
                rva, name, slots = current
                yield rva, Function(name, slots, _scoped(constants))
                current = None
        elif kind in OPENERS:
            if not scopes and kind in PROCEDURES:
                current, constants = _procedure(_record(stream, offset, end), types, sections, counts), []
            scopes.append(kind)
        elif kind == S_CONSTANT and current is not None and not any(scope in INLINE_SITES for scope in scopes):
            constant = _constant(_record(stream, offset, end), types, counts)
            if constant is not None:
                constants.append(constant)
        offset = end
    if scopes:
        raise PdbError(f"{stream.name}: the symbols end inside an open scope ({len(scopes)} deep)")


def _record(stream: Reader, offset: int, end: int) -> Reader:
    """The data of the symbol record at OFFSET, after its length and kind."""
    return Reader(stream.data[offset + 4:end], f"{stream.name}: the record at offset {offset:#x}")


def _procedure(record: Reader, types: Types, sections: list, counts: Counter) -> tuple | None:
    """(RVA, name, slots) of a procedure record. None, and counted, when it is outside every section or has no
    function type."""
    type_index, offset, segment = record.u32(24), record.u32(28), record.u16(32)
    name = record.string(35)[0]
    if not 1 <= segment <= len(sections):
        counts[OUTSIDE] += 1
        return None
    slots = types.signature(type_index)
    if slots is None:
        counts[UNTYPED] += 1
        return None
    return sections[segment - 1] + offset, name, slots


def _constant(record: Reader, types: Types, counts: Counter) -> tuple | None:
    """(enum, enumerators, name, value) of a constant record of an enum type. None for another type; None, and
    counted, when it is no enumerator of its enum or the enum has no single definition."""
    value, name_at = record.numeric(4)
    name = record.string(name_at)[0]
    base = types.unmodified(record.u32(0))
    if types.kind(base) != LF_ENUM:
        return None
    enumerators = types.enumerators_at(base)
    if enumerators is None:
        counts[UNKNOWN_ENUM] += 1
        return None
    if (name, value) not in enumerators:
        counts[NOT_ENUMERATOR] += 1
        return None
    return types.enum_name(base), enumerators, name, value


def _scoped(constants: list) -> tuple:
    """(scope, name, value) per distinct constant of one function. The scope is `enum NAME`, then `enum NAME #2` and
    so on for other enums of that name in the function."""
    scopes = {}  # (enum, enumerators) -> scope
    for enum, enumerators, _, _ in constants:
        if (enum, enumerators) not in scopes:
            same = sum(1 for other, _ in scopes if other == enum)
            scopes[enum, enumerators] = f"{enum} #{same + 1}" if same else enum
    return tuple(dict.fromkeys((scopes[enum, enumerators], name, value)
                               for enum, enumerators, name, value in constants))


# Import


def read_map(path: Path) -> dict:
    """Reference RVA -> target address, from a map file with the columns reference,target in hex."""
    targets, reference_at, target_at = {}, {}, {}
    try:
        for where, values in outputs.read_rows(path, MAP_COLUMNS, PdbError):
            reference = _address(values["reference"], where)
            target = _address(values["target"], where)
            if reference in reference_at:
                raise PdbError(f"{where}: reference 0x{reference:08x} is also at {reference_at[reference]}")
            if target in target_at:
                raise PdbError(f"{where}: target 0x{target:08x} is also at {target_at[target]}")
            reference_at[reference] = target_at[target] = where
            targets[reference] = target
    except OSError as error:
        raise PdbError(f"{path}: {error.strerror}") from error
    return targets


def _address(text: str, where: str) -> int:
    lowered = text.lower()
    if not symbols.ADDRESS.match(lowered):
        raise PdbError(f"{where}: {text!r} is not a hex address")
    return int(lowered, 16)


def import_file(source: Path, mapping: Path | None, folder: Path) -> Counter:
    """Writes the three symbol files of the program database SOURCE into FOLDER, at the target addresses that MAPPING
    gives, or at the RVAs without one. Returns the counts that describe() prints."""
    if not folder.is_dir():
        raise PdbError(f"{folder} does not exist")
    targets = read_map(mapping) if mapping is not None else None
    try:
        data = source.read_bytes()
    except OSError as error:
        raise PdbError(f"{source}: {error.strerror}") from error
    msf = Msf(data, source.name)
    info = msf.stream(INFO, "info stream")
    version = info.u32(0)
    if version != VC70:
        raise PdbError(f"{info.name}: version {version} is not supported: only VC70 ({VC70})")
    types = Types(msf.stream(TPI, "TPI stream"))
    counts = Counter()
    kept = {}  # address -> Function
    for rva, found in read_functions(msf, types, counts).items():
        address = rva if targets is None else targets.get(rva)
        if address is None:
            counts[UNMAPPED] += 1
        elif len(set(found)) > 1:
            counts[DIFFERENT] += 1
        else:
            kept[address] = found[0]
    _write(kept, types, folder, counts)
    return counts


def _write(kept: dict, types: Types, folder: Path, counts: Counter) -> None:
    prototypes, scopes = [], []
    for address in sorted(kept):
        function, text = kept[address], f"0x{address:08x}"
        prototypes += [(text, function.name, slot, spelled) for slot, spelled in enumerate(function.slots)]
        scopes += [(text, scope, name, value) for scope, name, value in function.constants]
    enums = []
    named = {spelled for function in kept.values() for spelled in function.slots if symbols.enum_slot(spelled)}
    for spelled in sorted(named):
        definitions = types.enumerators(spelled[len(symbols.ENUM_PREFIX):])
        if len(definitions) == 1:
            enums += [(spelled, name, value) for name, value in definitions[0]]
            counts[ENUM_COUNT] += 1
        else:
            counts[AMBIGUOUS_ENUM if definitions else UNDEFINED_ENUM] += 1
    counts[FUNCTIONS] = len(kept)
    counts[SLOTS] = len(prototypes)
    counts[ENUMERATORS] = len(enums)
    counts[SCOPE_CONSTANTS] = len(scopes)
    for name, columns, rows in ((symbols.PROTOTYPES, symbols.PROTOTYPE_COLUMNS, prototypes),
                                (symbols.ENUMS, symbols.ENUM_COLUMNS, enums),
                                (symbols.SCOPES, symbols.SCOPE_COLUMNS, scopes)):
        osutil.write_whole(folder / name, outputs.table_text(columns, rows))


def describe(counts: dict) -> str:
    """The counts in one line: what was written, then what was left out."""
    written = ", ".join(f"{counts.get(key, 0)} {key}" for key in WRITTEN)
    left_out = [f"{counts[key]} {key}" for key in LEFT_OUT if counts.get(key)]
    return written + (f"; left out: {', '.join(left_out)}" if left_out else "")
