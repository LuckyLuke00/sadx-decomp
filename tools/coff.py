"""Read and write i386 COFF object files: the sections with their relocations, and the symbol table.

The writer lays a file out as cl.exe does: the header, the section table, each section's bytes followed by its
relocations, then the symbols and the string table. So writing what was read gives back the same bytes.
Standard library only.
"""

import struct
from pathlib import Path
from typing import NamedTuple

import pe

# Section flags (IMAGE_SCN_*)
CODE = 0x20
INITIALIZED = 0x40
UNINITIALIZED = 0x80
REMOVE = 0x800  # the linker leaves the section out of the image
COMDAT = 0x1000
ALIGN_SHIFT = 20  # the alignment is 2 ** (the 4 bits from here, minus 1). 0 means the default, 16 bytes.
ALIGN_1 = 1 << ALIGN_SHIFT
ALIGN_MASK = 0xF << ALIGN_SHIFT
DEFAULT_ALIGNMENT = 16
NRELOC_OVERFLOW = 0x01000000  # more than 65,535 relocations: not written by cl.exe for game code
FUNCTION = 0x20  # a symbol's type: a function
# Storage classes
EXTERNAL = 2
STATIC = 3
# Section numbers that name no section
UNDEFINED = 0
ABSOLUTE = -1
# Relocation types (IMAGE_REL_I386_*)
DIR32 = 6  # the target's address
DIR32NB = 7  # the target's address minus the image base
REL32 = 0x14  # the target's address minus the address after the field

HEADER = struct.Struct("<HHIIIHH")
SECTION_HEADER = struct.Struct("<8sIIIIIIHHI")
RELOCATION = struct.Struct("<IIH")
SYMBOL = struct.Struct("<8sIhHBB")
SECTION_AUX = struct.Struct("<IHHIHB3x")  # the auxiliary record of a section symbol
AUX_SIZE = 18


class Relocation(NamedTuple):
    offset: int  # where the field is in the section's bytes
    symbol: int  # the index of its symbol in the symbol table, aux records counted
    kind: int  # DIR32, REL32, ...


class Section(NamedTuple):
    name: str
    flags: int
    data: bytes | int  # an int is the size of uninitialized data, which the file does not hold
    relocations: list[Relocation]

    @property
    def size(self) -> int:
        return self.data if isinstance(self.data, int) else len(self.data)

    @property
    def alignment(self) -> int:
        bits = (self.flags & ALIGN_MASK) >> ALIGN_SHIFT
        return 1 << (bits - 1) if bits else DEFAULT_ALIGNMENT


class Symbol(NamedTuple):
    name: str
    value: int
    section: int  # a 1-based section number, UNDEFINED or ABSOLUTE
    type: int
    storage: int  # EXTERNAL, STATIC, ...
    aux: bytes = b""  # its auxiliary records, AUX_SIZE bytes each


class Object(NamedTuple):
    sections: list[Section]
    symbols: dict[int, Symbol]  # by index in the symbol table, which counts the aux records
    timestamp: int = 0


def section_symbol(number: int, section: Section, selection: int = 0) -> Symbol:
    """The static symbol that names a section, with the aux record that gives its size."""
    aux = SECTION_AUX.pack(section.size, len(section.relocations), 0, 0, 0, selection)
    return Symbol(section.name, 0, number, 0, STATIC, aux)


def numbered(symbols: list[Symbol]) -> dict[int, Symbol]:
    """The symbols by their index in the symbol table, where each aux record takes one index."""
    table, index = {}, 0
    for symbol in symbols:
        table[index] = symbol
        index += 1 + len(symbol.aux) // AUX_SIZE
    return table


def read(path: Path) -> Object:
    data = path.read_bytes()
    machine, count, timestamp, symbol_table, symbol_count, optional_size, _ = HEADER.unpack_from(data)
    if machine != pe.MACHINE_I386:
        raise ValueError(f"{path} is no i386 COFF object (machine 0x{machine:x})")
    strings = symbol_table + SYMBOL.size * symbol_count

    def name_at(raw: bytes) -> str:
        if raw[:4] == bytes(4):  # a long name: its offset in the string table
            start = strings + struct.unpack_from("<I", raw, 4)[0]
            return data[start:data.index(b"\0", start)].decode("latin-1")
        return raw.rstrip(b"\0").decode("latin-1")

    sections = []
    for offset in range(HEADER.size + optional_size, HEADER.size + optional_size + SECTION_HEADER.size * count,
                        SECTION_HEADER.size):
        raw_name, _, _, size, raw_at, relocations_at, _, relocation_count, _, flags = SECTION_HEADER.unpack_from(
            data, offset)
        if flags & NRELOC_OVERFLOW:
            raise ValueError(f"{path} has a section with over 65,535 relocations")
        name = raw_name.rstrip(b"\0").decode("latin-1")
        if name.startswith("/"):
            start = strings + int(name[1:])
            name = data[start:data.index(b"\0", start)].decode("latin-1")
        relocations = [Relocation(*RELOCATION.unpack_from(data, relocations_at + RELOCATION.size * i))
                       for i in range(relocation_count)]
        body = size if flags & UNINITIALIZED else data[raw_at:raw_at + size]
        sections.append(Section(name, flags, body, relocations))

    symbols, index = {}, 0
    while index < symbol_count:
        at = symbol_table + SYMBOL.size * index
        raw_name, value, section, kind, storage, aux_count = SYMBOL.unpack_from(data, at)
        aux = data[at + SYMBOL.size:at + SYMBOL.size + AUX_SIZE * aux_count]
        symbols[index] = Symbol(name_at(raw_name), value, section, kind, storage, aux)
        index += 1 + aux_count
    return Object(sections, symbols, timestamp)


def write(obj: Object) -> bytes:
    strings = bytearray()

    def name_field(name: str, long_prefix: bytes) -> bytes:
        encoded = name.encode("latin-1")
        if len(encoded) <= 8:
            return encoded.ljust(8, b"\0")
        offset = 4 + len(strings)
        strings.extend(encoded + b"\0")
        return long_prefix(offset)

    table_end = HEADER.size + SECTION_HEADER.size * len(obj.sections)
    headers, bodies, at = [], [], table_end
    for section in obj.sections:
        name = name_field(section.name, lambda offset: f"/{offset}".encode().ljust(8, b"\0"))
        raw_at = 0 if isinstance(section.data, int) or not section.data else at
        if raw_at:
            bodies.append(section.data)
            at += len(section.data)
        relocations_at = at if section.relocations else 0
        for relocation in section.relocations:
            bodies.append(RELOCATION.pack(*relocation))
            at += RELOCATION.size
        headers.append(SECTION_HEADER.pack(name, 0, 0, section.size, raw_at, relocations_at, 0,
                                           len(section.relocations), 0, section.flags))

    records, count = [], 0
    for index, symbol in obj.symbols.items():
        if index != count:
            raise ValueError(f"symbol {symbol.name} has index {index}, but the table is at {count}")
        name = name_field(symbol.name, lambda offset: struct.pack("<II", 0, offset))
        records.append(SYMBOL.pack(name, symbol.value, symbol.section, symbol.type, symbol.storage,
                                   len(symbol.aux) // AUX_SIZE) + symbol.aux)
        count += 1 + len(symbol.aux) // AUX_SIZE
    header = HEADER.pack(pe.MACHINE_I386, len(obj.sections), obj.timestamp, at, count, 0, 0)
    return b"".join([header, *headers, *bodies, *records, struct.pack("<I", 4 + len(strings)), bytes(strings)])
