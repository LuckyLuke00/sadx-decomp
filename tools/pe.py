"""Read and patch the parts of a 32-bit PE file that the tools need. Standard library only."""

import struct
import sys
from pathlib import Path
from typing import NamedTuple

PE32_MAGIC = 0x10B
MACHINE_I386 = 0x14C
CODEVIEW = 2  # debug directory type
CODE = 0x20  # section flag: IMAGE_SCN_CNT_CODE
WRITABLE = 0x80000000  # section flag: IMAGE_SCN_MEM_WRITE
IMPORT_BY_ORDINAL = 0x80000000  # an import table entry with this bit holds an ordinal, not a name


class Section(NamedTuple):
    name: str
    rva: int
    virtual_size: int
    raw_offset: int
    raw_size: int
    flags: int  # IMAGE_SCN_* characteristics


class DelayImport(NamedTuple):
    dll: str
    descriptor: int  # the address of its import descriptor
    slots: dict[int, str]  # the address of each delay import address table slot: the function it imports, or #ordinal


class Header(NamedTuple):
    machine: int
    characteristics: int
    linker: tuple[int, int]
    image_base: int
    subsystem: int
    dll_characteristics: int
    sections: list[Section]
    imports: list[str]  # DLL names
    import_slots: dict[int, str]  # the address of each import address table slot: the function it imports, or #ordinal
    delay_imports: list[DelayImport]  # the DLLs that the exe loads when it first calls them
    pdb: str | None  # the PDB path in the CodeView record, if the exe has one


class Layout(NamedTuple):
    image_base: int
    sections: list[Section]
    directories: int  # the file offset of the data directory table


class Reader:
    """Finds addresses and strings in the bytes of one PE file."""

    def __init__(self, path: Path, data: bytes, layout: Layout):
        self.path = path
        self.data = data
        self.image_base = layout.image_base
        self.sections = layout.sections
        self.directories = layout.directories

    def directory_rva(self, index: int) -> int:
        return struct.unpack_from("<I", self.data, self.directories + index * 8)[0]

    def file_offset(self, rva: int) -> int:
        section = next((s for s in self.sections if s.rva <= rva < s.rva + max(s.virtual_size, s.raw_size)), None)
        if section is None:
            sys.exit(f"{self.path}: address 0x{rva:08x} is in no section, so the exe is packed or damaged.")
        return section.raw_offset + rva - section.rva

    def c_string(self, offset: int) -> str:
        return self.data[offset:self.data.index(b"\0", offset)].decode("ascii", "replace")

    def read_slots(self, names_rva: int, slots_rva: int) -> dict[int, str]:
        # Before loading, each slot holds what its name table entry holds: a hint and name, or an ordinal.
        slots, entries, index = {}, self.file_offset(names_rva), 0
        while entry := struct.unpack_from("<I", self.data, entries + 4 * index)[0]:  # a zero entry ends the list
            slot = self.image_base + slots_rva + 4 * index
            if entry & IMPORT_BY_ORDINAL:
                slots[slot] = f"#{entry & 0xFFFF}"
            else:
                slots[slot] = self.c_string(self.file_offset(entry) + 2)
            index += 1
        return slots

    def read_imports(self) -> tuple[list[str], dict[int, str]]:
        import_rva = self.directory_rva(1)
        imports, import_slots = [], {}
        descriptor = self.file_offset(import_rva) if import_rva else None
        while descriptor is not None:
            names_rva, _, _, name_rva, slots_rva = struct.unpack_from("<5I", self.data, descriptor)
            if not name_rva:  # an all-zero descriptor ends the table
                break
            imports.append(self.c_string(self.file_offset(name_rva)))
            import_slots.update(self.read_slots(names_rva or slots_rva, slots_rva))
            descriptor += 20
        return imports, import_slots

    def read_delay_imports(self) -> list[DelayImport]:
        # The delay import table has its own descriptors, with the same kind of name table and slots.
        delay_imports, delay_at = [], self.directory_rva(13)
        while delay_at:
            attributes, name_rva, _, slots_rva, names_rva = struct.unpack_from("<5I", self.data, self.file_offset(delay_at))
            if not name_rva:  # an all-zero descriptor ends the table
                break
            if not attributes & 1:
                sys.exit(f"{self.path}: a delay import descriptor with addresses, not RVAs: not built by VC++ 2010.")
            delay_imports.append(DelayImport(self.c_string(self.file_offset(name_rva)), self.image_base + delay_at,
                                             self.read_slots(names_rva, slots_rva)))
            delay_at += 32
        return delay_imports

    def read_pdb(self) -> str | None:
        debug_rva, debug_size = struct.unpack_from("<II", self.data, self.directories + 6 * 8)
        pdb = None
        for entry in range(debug_size // 28) if debug_rva else []:
            record = self.file_offset(debug_rva) + entry * 28
            kind = struct.unpack_from("<I", self.data, record + 12)[0]
            raw = struct.unpack_from("<I", self.data, record + 24)[0]
            if kind == CODEVIEW and self.data[raw:raw + 4] == b"RSDS":
                pdb = self.c_string(raw + 24)
        return pdb


def read_sections(data: bytes, table: int, count: int) -> list[Section]:
    sections = []
    for offset in range(table, table + 40 * count, 40):
        virtual_size, rva, raw_size, raw_offset = struct.unpack_from("<IIII", data, offset + 8)
        flags = struct.unpack_from("<I", data, offset + 36)[0]
        sections.append(Section(data[offset:offset + 8].rstrip(b"\0").decode("ascii", "replace"),
                                rva, virtual_size, raw_offset, raw_size, flags))
    return sections


def read_header(path: Path) -> Header:
    data = path.read_bytes()
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    if data[pe:pe + 4] != b"PE\0\0":
        sys.exit(f"{path} is not a PE file.")
    machine, count, _, _, _, optional_size, characteristics = struct.unpack_from("<HHIIIHH", data, pe + 4)
    optional = pe + 24
    if struct.unpack_from("<H", data, optional)[0] != PE32_MAGIC:
        sys.exit(f"{path} is not a 32-bit PE file.")
    image_base = struct.unpack_from("<I", data, optional + 28)[0]
    subsystem, dll_characteristics = struct.unpack_from("<HH", data, optional + 68)
    sections = read_sections(data, optional + optional_size, count)
    reader = Reader(path, data, Layout(image_base, sections, optional + 96))
    imports, import_slots = reader.read_imports()
    delay_imports = reader.read_delay_imports()
    pdb = reader.read_pdb()
    return Header(machine, characteristics, (data[optional + 2], data[optional + 3]), image_base,
                  subsystem, dll_characteristics, sections, imports, import_slots, delay_imports, pdb)


class Image:
    """A PE file's bytes, by address."""

    def __init__(self, path: Path):
        header = read_header(path)
        self.data = path.read_bytes()
        self.sections = [(header.image_base + s.rva, max(s.virtual_size, s.raw_size), s) for s in header.sections]
        self.import_slots = header.import_slots

    def contents(self, section: Section) -> bytes:
        """A section's bytes in the file."""
        return self.data[section.raw_offset:section.raw_offset + section.raw_size]

    def read(self, address: int, size: int) -> bytes:
        for start, length, section in self.sections:
            if start <= address < start + length:
                offset = address - start
                return self.data[section.raw_offset + offset:section.raw_offset + min(offset + size, section.raw_size)]
        return b""

    def is_code(self, address: int) -> bool:
        return any(start <= address < start + length and section.flags & CODE
                   for start, length, section in self.sections)


def rich_entries(path: Path) -> dict[tuple[int, int], int]:
    """A PE's Rich header: the object count per (product id, build), that is, which tools made its objects."""
    with path.open("rb") as exe:
        data = exe.read(0x1000)
    end = data.find(b"Rich")
    if end < 0:
        sys.exit(f"{path} has no Rich header, so the tools that built it are unknown.")
    key = struct.unpack_from("<I", data, end + 4)[0]
    start = next((offset for offset in range(0x80, end, 4)
                  if struct.unpack_from("<I", data, offset)[0] ^ key == 0x536E6144), None)  # "DanS"
    if start is None:
        sys.exit(f"{path} has a damaged Rich header, so the tools that built it are unknown.")
    entries = {}
    for offset in range(start + 16, end, 8):
        comp_id, count = (value ^ key for value in struct.unpack_from("<II", data, offset))
        entries[comp_id >> 16, comp_id & 0xFFFF] = count
    return entries


def clear_timestamp(path: Path) -> None:
    """Zero the link timestamp, and the checksum that covers it, so the same
    sources always give the same bytes."""
    data = bytearray(path.read_bytes())
    pe_header = struct.unpack_from("<I", data, 0x3C)[0]
    timestamp = pe_header + 8
    checksum = pe_header + 24 + 0x40
    if data[timestamp:timestamp + 4] != bytes(4) or data[checksum:checksum + 4] != bytes(4):
        struct.pack_into("<I", data, timestamp, 0)
        struct.pack_into("<I", data, checksum, 0)
        path.write_bytes(data)
