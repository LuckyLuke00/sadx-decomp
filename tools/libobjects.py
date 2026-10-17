"""The runtime libraries' functions and data, read from their .lib files, for library.py.

A .lib file is an archive of COFF objects. library_functions() cuts each object into the
functions and data sections that the linker can place, with the bytes a relocation fills
masked, and gives each the names that our build will give it. It also reads the symbols of
an import library.
Standard library only.
"""

import collections
import struct
from pathlib import Path
from typing import Iterator, NamedTuple

import pe

SECREL = 0x0B  # COFF relocation type
SECTION_RELOCATION = 0x0A  # the one relocation type that fills 2 bytes, not 4
EXTERNAL, STATIC, LABEL, WEAK_EXTERNAL = 2, 3, 6, 105  # COFF storage classes
FUNCTION = 0x20  # COFF symbol type of a function
INITIALIZED_DATA, UNINITIALIZED_DATA, COMDAT = 0x40, 0x80, 0x1000  # COFF section flags, as pe.CODE
NOT_LINKED = 0x800 | 0x02000000  # COFF section flags of .drectve and .debug$S: the exe holds neither
# CodeView records that name an address, as record type: (offset of the address, offset of the name).
# These are S_LPROC32, S_GPROC32, S_LABEL32, S_LDATA32 and S_GDATA32.
NAMED_RECORDS = {0x110F: (32, 39), 0x1110: (32, 39), 0x1105: (4, 11), 0x110C: (8, 14), 0x110D: (8, 14)}
PROCEDURES = (0x110F, 0x1110)  # their length is at offset 16
DEBUG_SYMBOLS = 0xF1  # the .debug$S subsection that holds symbol records
IMPORT_ENTRY = b"\x00\x00\xff\xff"  # the start of an import library entry, which has no COFF object


class Reference(NamedTuple):
    """A relocation in a library function."""
    offset: int  # in the function
    kind: int  # COFF relocation type
    key: str  # the symbol, or library:object!symbol for a static one; "" for a section
    name: str  # the name our PDB gives it; "" if it has none or no library defines it
    symbol: str  # the linker symbol, or "" when it is static


class Label(NamedTuple):
    """A symbol inside a function, such as a second entry point into asm code."""
    offset: int
    key: str
    name: str
    symbol: str
    table: bool  # data in code, such as the TrailUpVec jump table in memcpy.asm


class Function(NamedTuple):
    """A function, or a whole data section, which the search matches the same way."""
    member: str  # library:object, e.g. libcmt.lib:crt0.obj
    place: tuple[int, int]  # section number and offset in the object
    name: str  # the name our PDB gives it; "" if it has none
    symbol: str  # its linker symbol, or "" when it is static
    keys: frozenset[str]  # the key of every symbol at its address
    code: bytes
    mask: bytes  # 1 for each byte a relocation fills
    references: tuple[Reference, ...]
    labels: tuple[Label, ...]
    flags: int  # its section's COFF flags

    @property
    def fixed(self) -> int:
        return self.mask.count(0)

    @property
    def data(self) -> bool:
        return not self.flags & pe.CODE

    @property
    def foldable(self) -> bool:
        """Whether identical code folding may merge it: the linker folds only packaged
        functions and read-only data, which the compiler puts in COMDAT sections."""
        return bool(self.flags & COMDAT) and not self.flags & pe.WRITABLE

    def spots(self) -> dict[int, set[str]]:
        """The keys at each offset that a symbol names: the start, then each label."""
        spots = {0: set(self.keys)}
        for label in self.labels:
            spots.setdefault(label.offset, set()).add(label.key)
        return spots


class Part(NamedTuple):
    """The symbols of one section of an object."""
    number: int  # 1-based
    defined: list["Symbol"]  # its functions and data
    marks: list["Symbol"]  # its asm labels, such as fFATN2, which a jump table names, and tables


def library_functions(paths: list[Path]) -> Iterator[Function]:
    """Every function in the .lib files, with the names our PDB will give it."""
    objects = [(f"{path.name}:{member.rsplit(chr(92), 1)[-1]}", parsed)
               for path in paths for member, body in archive_members(path)
               if (parsed := read_object(body)) is not None]
    names = external_symbol_names(objects)
    for member, coff in objects:
        yield from LibraryObject(member, coff, names).functions()


def external_symbol_names(objects: list[tuple[str, "Object"]]) -> dict[str, str]:
    """The name of each external symbol, from the object that defines it. Imports and
    symbols the linker makes, such as ___ImageBase, have no such object. An uninitialized
    C global is a common symbol: section 0, with its size as its value."""
    names = {}
    for _, coff in objects:
        names.update({symbol.name: coff.names.get(symbol.name, plain_name(symbol.name))
                      for symbol in coff.symbols.values()
                      if symbol.storage == EXTERNAL and (symbol.section > 0 or symbol.value > 0)})
    return names


class LibraryObject:
    """One object of a library, and the functions in it."""

    def __init__(self, member: str, coff: "Object", external_names: dict[str, str]):
        self.member = member
        self.coff = coff
        self.external_names = external_names
        # A static name can repeat in one object, such as the jnedef label in two asm procedures.
        self.statics = collections.Counter(s.name for s in set(coff.symbols.values()) if s.storage != EXTERNAL)

    def describe(self, symbol: "Symbol") -> tuple[str, str, str]:
        """A symbol's key, the name our PDB gives it, and its linker symbol."""
        if symbol.storage == EXTERNAL:
            return symbol.name, self.external_names.get(symbol.name, ""), symbol.name
        key = f"{self.member}!{symbol.name}"
        if self.statics[symbol.name] > 1:
            key += f"@{symbol.section}+{symbol.value}"
        return key, self.coff.names.get(symbol.name, ""), ""

    def reference(self, offset: int, kind: int, index: int) -> Reference:
        symbol = self.coff.symbols[index]
        if symbol.name.startswith((".", "$")):  # a section or a compiler label
            return Reference(offset, kind, "", "", "")
        return Reference(offset, kind, *self.describe(symbol))

    def functions(self) -> Iterator[Function]:
        for part in self.parts():
            for start, end in self.bounds(part):
                yield self.function_at(part, start, end)
        # A common symbol has no bytes, so any data address can hold it.
        for index, symbol in self.coff.symbols.items():
            if symbol.storage == EXTERNAL and symbol.section == 0 and symbol.value > 0:
                yield Function(self.member, (0, index), self.external_names[symbol.name], symbol.name,
                               frozenset({symbol.name}), b"", b"", (), (), UNINITIALIZED_DATA | pe.WRITABLE)

    def parts(self) -> list[Part]:
        """The symbols of each section that holds functions or data."""
        by_section = collections.defaultdict(list)
        marks = collections.defaultdict(list)
        for symbol in self.coff.symbols.values():
            if symbol.section <= 0 or symbol.name.startswith((".", "$")):
                continue
            flags = self.coff.sections[symbol.section - 1].flags
            if symbol.storage == LABEL or flags & pe.CODE and data_in_code(symbol):
                marks[symbol.section].append(symbol)
            elif is_wanted(symbol, flags):
                by_section[symbol.section].append(symbol)
        return [Part(number, defined, marks[number]) for number, defined in by_section.items()]

    def bounds(self, part: Part) -> list[tuple[int, int]]:
        """The start and end of each function in a section."""
        section = self.coff.sections[part.number - 1]
        data = not section.flags & pe.CODE
        defined = part.defined
        # A symbol inside another's procedure is a label in it, not a function of its own. Code before
        # a section's first symbol, such as found_bx in strchr.asm, is a function with no symbol.
        # A data section stays whole, so a vtable keeps the RTTI pointer before its symbol.
        procedures = [(s.value, s.value + self.coff.lengths[s.name]) for s in defined if s.name in self.coff.lengths]
        offsets = [0] if data else sorted({0} | {s.value for s in defined} - {
            s.value for s in defined for start, end in procedures if start < s.value < end})
        return list(zip(offsets, offsets[1:] + [len(section.data)]))

    def function_at(self, part: Part, start: int, end: int) -> Function:
        """The function in a section from start up to end."""
        section = self.coff.sections[part.number - 1]
        data = not section.flags & pe.CODE
        mask, references = self.masked(section, start, end)
        named = part.defined + part.marks
        labels = tuple(Label(s.value - start, *self.describe(s), not data and data_in_code(s))
                       for s in named if start < s.value < end)
        symbol, name = self.symbol_and_name([s for s in part.defined if s.value == start])
        keys = frozenset(self.describe(s)[0] for s in named if s.value == start)
        return Function(self.member, (part.number, start), name, symbol, keys,
                        section.data[start:end], mask, references, labels, section.flags)

    def masked(self, section: "Section", start: int, end: int) -> tuple[bytes, tuple[Reference, ...]]:
        """The mask of the bytes that relocations fill between start and end, and those relocations."""
        mask = bytearray(end - start)
        references = []
        for offset, index, kind in section.relocations:
            if start <= offset < end:
                size = 2 if kind == SECTION_RELOCATION else 4
                mask[offset - start:offset - start + size] = b"\1" * size
                references.append(self.reference(offset - start, kind, index))
        return bytes(mask[:end - start]), tuple(references)

    def symbol_and_name(self, here: list["Symbol"]) -> tuple[str, str]:
        """The linker symbol and the name our PDB gives the function that the symbols in here start."""
        externals = sorted(s.name for s in here if s.storage == EXTERNAL)
        cv_name = next((self.coff.names[s.name] for s in here if s.name in self.coff.names), None)
        # Our PDB lists one symbol per address. Pick the one its name comes from.
        symbol = next((s for s in externals if plain_name(s) == cv_name), externals[0] if externals else "")
        if symbol:
            return symbol, cv_name or plain_name(symbol)
        # Without a procedure record, such as for an exception funclet, our PDB
        # holds a label, and reccmp matches only functions by name.
        return symbol, cv_name if any(s.name in self.coff.lengths for s in here) else ""


def is_wanted(symbol: "Symbol", flags: int) -> bool:
    """Whether a symbol in a section with these flags names a function, or data that the exe holds."""
    if flags & pe.CODE:
        return symbol.storage == EXTERNAL or (symbol.storage == STATIC and symbol.type == FUNCTION)
    return bool(flags & INITIALIZED_DATA) and not flags & NOT_LINKED and symbol.storage in (EXTERNAL, STATIC)


def data_in_code(symbol: "Symbol") -> bool:
    """Whether a symbol in a code section names data, such as an asm jump table: a static
    symbol that is no function. An asm code label has storage class LABEL instead."""
    return symbol.storage == STATIC and symbol.type != FUNCTION


def plain_name(symbol: str) -> str:
    """A C symbol without its leading underscore and stdcall suffix. C++ symbols stay as they are."""
    if symbol.startswith("?"):
        return symbol
    if symbol.startswith("@"):  # fastcall: @name@8
        return symbol[1:].rsplit("@", 1)[0]
    symbol = symbol.removeprefix("_")
    head, _, tail = symbol.rpartition("@")
    return head if head and tail.isdigit() else symbol


def archive_members(path: Path) -> Iterator[tuple[str, bytes]]:
    """The members of a .lib archive, by name."""
    data = path.read_bytes()
    position, long_names = 8, b""
    while position + 60 <= len(data):
        name = data[position:position + 16].decode("latin1").rstrip()
        size = int(data[position + 48:position + 58])
        body = data[position + 60:position + 60 + size]
        if name == "//":
            long_names = body
        elif name.startswith("/") and name[1:].isdigit():
            yield c_string(long_names, int(name[1:])), body
        elif name != "/":
            yield name.rstrip("/"), body
        position += 60 + size + (size & 1)


def import_symbols(path: Path) -> dict[str, str]:
    """The symbols that an import library defines, by the name the DLL exports: GetSystemMetrics: _GetSystemMetrics@4."""
    return {plain_name(symbol): symbol for _, body in archive_members(path) if body[:4] == IMPORT_ENTRY
            for symbol in [c_string(body, 20)]}  # the 20-byte header is followed by the symbol, then the DLL's name


class Section(NamedTuple):
    name: str
    data: bytes
    flags: int
    relocations: list[tuple[int, int, int]]  # offset, symbol index, type


class Symbol(NamedTuple):
    name: str
    value: int
    section: int  # 1-based; 0 or less for none
    type: int
    storage: int


class Object(NamedTuple):
    sections: list[Section]
    symbols: dict[int, Symbol]  # by index
    names: dict[str, str]  # symbol: the name its CodeView record gives it, which is what our PDB will hold
    lengths: dict[str, int]  # symbol: its procedure's length, from the same records


def read_object(body: bytes) -> Object | None:
    """A COFF object, or None for an import library entry."""
    machine, count, _, table, symbol_count, optional, _ = struct.unpack_from("<HHIIIHH", body)
    if machine != pe.MACHINE_I386:
        return None
    strings = string_table(table, symbol_count)
    sections = [read_section(body, header, strings)
                for header in range(20 + optional, 20 + optional + 40 * count, 40)]
    symbols = read_symbols(body, table, symbol_count)
    return Object(sections, symbols, *codeview(sections, symbols))


def string_table(table: int, symbol_count: int) -> int:
    """The offset of an object's string table, which follows its symbol table."""
    return table + 18 * symbol_count


def read_section(body: bytes, header: int, strings: int) -> Section:
    """The section whose header is at this offset."""
    name = body[header:header + 8].rstrip(b"\0").decode("latin1")
    if name.startswith("/"):
        name = c_string(body, strings + int(name[1:]))
    size, pointer, relocation_table, _, relocation_count, _, flags = struct.unpack_from("<IIIIHHI", body, header + 16)
    relocations = [struct.unpack_from("<IIH", body, relocation_table + 10 * i) for i in range(relocation_count)]
    return Section(name, body[pointer:pointer + size] if pointer else bytes(size), flags, relocations)


def read_symbols(body: bytes, table: int, symbol_count: int) -> dict[int, Symbol]:
    """The symbols of an object, by index."""
    strings = string_table(table, symbol_count)

    def long_name(raw: bytes) -> str:
        if raw[:4] == bytes(4):
            return c_string(body, strings + struct.unpack_from("<I", raw, 4)[0])
        return raw.rstrip(b"\0").decode("latin1")

    symbols, defaults = {}, {}
    index = 0
    while index < symbol_count:
        entry = table + 18 * index
        value, section, kind, storage, aux = struct.unpack_from("<IhHBB", body, entry + 8)
        symbols[index] = Symbol(long_name(body[entry:entry + 8]), value, section, kind, storage)
        if storage == WEAK_EXTERNAL:
            defaults[index] = struct.unpack_from("<I", body, entry + 18)[0]  # its aux record starts with it
        index += 1 + aux
    # A weak external, such as a vtable's ??_E destructor, is its default symbol
    # unless an object defines it, and no object in the runtime libraries does.
    symbols.update({weak: symbols[default] for weak, default in defaults.items()})
    return symbols


def codeview(sections: list[Section], symbols: dict[int, Symbol]) -> tuple[dict[str, str], dict[str, int]]:
    """The names and procedure lengths that an object's CodeView records give its symbols."""
    names, lengths = {}, {}
    for symbol, name, length in named_symbols(sections, symbols):
        names.setdefault(symbol, name)
        if length is not None:
            lengths.setdefault(symbol, length)
    return names, lengths


def named_symbols(sections: list[Section], symbols: dict[int, Symbol]) -> Iterator[tuple[str, str, int | None]]:
    """Each symbol that the .debug$S sections name: its linker symbol, its CodeView name and its
    procedure's length, which is None for a symbol that is no procedure."""
    for section in sections:
        if section.name == ".debug$S":
            yield from section_symbols(section, symbols)


def section_symbols(section: Section, symbols: dict[int, Symbol]) -> Iterator[tuple[str, str, int | None]]:
    """Each symbol that the records of a .debug$S section name, as named_symbols gives them."""
    data = section.data
    targets = {offset: index for offset, index, kind in section.relocations if kind == SECREL}
    for record_type, record in named_records(data):
        address, name = (record + offset for offset in NAMED_RECORDS[record_type])
        if address in targets:
            length = struct.unpack_from("<I", data, record + 16)[0] if record_type in PROCEDURES else None
            yield symbols[targets[address]].name, c_string(data, name), length


def named_records(data: bytes) -> Iterator[tuple[int, int]]:
    """The records in .debug$S data that name an address: their type and their offset."""
    position = 4  # after the CodeView signature
    while position + 8 <= len(data):
        kind, length = struct.unpack_from("<II", data, position)
        start, position = position + 8, position + 8 + length + (-length & 3)
        if kind == DEBUG_SYMBOLS:
            yield from subsection_records(data, start, length)


def subsection_records(data: bytes, start: int, length: int) -> Iterator[tuple[int, int]]:
    """The records in a symbols subsection that name an address: their type and their offset."""
    record = start
    while record + 4 <= start + length:
        size, record_type = struct.unpack_from("<HH", data, record)
        if record_type in NAMED_RECORDS:
            yield record_type, record
        record += 2 + size


def c_string(data: bytes, offset: int) -> str:
    return data[offset:data.index(b"\0", offset)].decode("latin1")
