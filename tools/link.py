"""Link the game from the original exe's bytes and our objects, and check that the result is the original.

The original is split into raw-byte COFF objects without relocations, so every byte keeps its address. A swapped
source file's object takes the place of its range of .text. link.exe 10.0 links them all, then mt.exe embeds the
manifest, as the original build did. A last step adds what no linker makes: the Rich header, the timestamp, the
signature and the checksum. The swaps hold when the result is the original, byte for byte.

Our objects keep their relocations. The original's bytes where our code uses a name give that name's address, and a
name with two addresses stops the file. Each pooled literal folds into the original's copy, which must hold the same
bytes. Any other data stops the file: the split can't place it yet. Standard library only.
"""

import hashlib
import struct
import sys
from pathlib import Path
from typing import Iterator, NamedTuple

import coff
import names
import osutil
import pe
import project

OBJECTS = project.BUILD / "CMakeFiles" / "game.dir"  # CMake's objects, by source path
OUT = project.BUILD / "link"
LINK = project.TOOLCHAIN / "bin" / "link.exe"
MT = project.TOOLCHAIN / "bin" / "mt.exe"
CODE_KINDS = {"FUNCTION", "STUB", "LIBRARY", "TEMPLATE", "SYNTHETIC"}  # the annotations of functions
ENTRY = "_entry"  # the split's name for the entry point
FOLDED = ".folded"  # the name of a literal's emptied section
LOAD_CONFIG = 10  # data directory entries
SECURITY = 4
RELOCATIONS_STRIPPED = 0x0001  # a PE characteristic
RT_MANIFEST = 24  # the resource type mt.exe embeds
RES_HEADER = struct.Struct("<IIHHHHIHHII")  # a .res entry: sizes, numbered type and name, flags, language
RES_FLAGS = 0x1030  # moveable, pure, discardable
# The flags an import library gives its .idata pieces: initialized, read-write, 4-byte aligned (2 for names).
IDATA_FLAGS = {".idata$2": 0xC0300040, ".idata$3": 0xC0300040, ".idata$4": 0xC0300040, ".idata$5": 0xC0300040,
               ".idata$6": 0xC0200040}
BSS_FLAGS = 0xC0000000 | coff.UNINITIALIZED | coff.ALIGN_1  # read-write


class NotLinkable(Exception):
    """A file whose object can't take the place of its range, or a name the split can't define."""


class Piece(NamedTuple):
    """A run of the original's bytes that becomes one raw section."""
    name: str  # the section name that link.exe groups it by
    flags: int
    start: int  # addresses
    end: int


class Swap(NamedTuple):
    """A source file's object, ready to take the place of its range of .text."""
    source: str  # from the repo root
    obj: coff.Object  # its literals folded
    start: int  # the addresses it takes
    end: int
    uses: dict[str, int | None]  # each name it uses but does not define: its address, None if its code never uses it


def run(game: Path, sources: list[Path]) -> int:
    """Link the game with the objects of sources swapped in, and compare. Prints the swaps, the bytes mt.exe changed
    and every post-link patch. Returns 1 if a file can't be swapped in or the result is not the original."""
    image, header = pe.Image(game), pe.read_header(game)
    swaps, failures = [], []
    for source in sources:
        try:
            swaps.append(swap_for(source.as_posix(), image))
        except NotLinkable as error:
            failures.append(f"{source.as_posix()}: {error}")
    if failures:
        print(f"FAIL {len(failures)} of the files can't be swapped in:")
        for failure in failures:
            print(f"     {failure}")
        return 1
    try:
        rebuilt, mt_changes, patches = relink(image, header, swaps, OUT)
    except NotLinkable as error:
        print(f"FAIL {error}")
        return 1
    return compare(game, header, rebuilt, swaps, mt_changes, patches)


# The swaps


def swap_for(source: str, image: pe.Image) -> Swap:
    """The swap of a game source file: its object from the build, placed by its function annotations."""
    path = OBJECTS / f"{source}.obj"
    if not path.exists():
        raise NotLinkable("the build has no object for it")
    text = (project.ROOT / source).read_text(encoding="utf-8")
    functions = sorted(address for kind, address, _ in names.parse_annotations(text) if kind in CODE_KINDS)
    if not functions:
        raise NotLinkable("it has no function annotation")
    return swap_object(source, coff.read(path), functions, image)


def swap_object(source: str, obj: coff.Object, functions: list[int], image: pe.Image) -> Swap:
    """obj with its literals folded, placed so that its functions land at FUNCTIONS, the sorted addresses of the
    original's copies, with the addresses of the names it uses."""
    obj, literals = fold(obj)
    placed, end = place(obj, functions[0])
    landed = sorted(placed[symbol.section] + symbol.value for symbol in obj.symbols.values()
                    if symbol.type == coff.FUNCTION and symbol.section in placed)
    if landed != functions:
        raise NotLinkable(f"its functions would land at {hexes(landed)}, but its annotations say {hexes(functions)}")
    uses = resolve(obj, placed, image)
    for name, data in literals.items():
        if uses[name] is not None and image.read(uses[name], len(data)) != data:
            raise NotLinkable(f"its literal {name} differs from the original's at 0x{uses[name]:08x}")
    return Swap(source, obj, functions[0], end, uses)


def fold(obj: coff.Object) -> tuple[coff.Object, dict[str, bytes]]:
    """obj with each pooled literal taken out and its name left undefined, so the original's copy serves, and the
    literals' bytes by name. A pooled literal is a COMDAT of initialized data with no relocations: the original build
    kept one copy of each, wherever its first user put it."""
    sections, symbols, literals, folded = list(obj.sections), dict(obj.symbols), {}, set()
    for number, section in enumerate(obj.sections, 1):
        if section.flags & (coff.CODE | coff.REMOVE) or section.name.startswith(".debug$") or not section.size:
            continue
        if not section.flags & coff.COMDAT or section.flags & coff.UNINITIALIZED or section.relocations:
            raise NotLinkable(f"its section {section.name} holds {section.size} bytes of its own data")
        # A new name: link.exe warns when sections of one name have different flags, and REMOVE differs.
        sections[number - 1] = coff.Section(FOLDED, coff.REMOVE, b"", [])
        folded.add(number)
    for index, symbol in obj.symbols.items():
        if symbol.section not in folded:
            continue
        if symbol.aux:  # the section's own symbol
            symbols[index] = coff.section_symbol(symbol.section, sections[symbol.section - 1])
        elif symbol.storage == coff.EXTERNAL:
            literals[symbol.name] = obj.sections[symbol.section - 1].data
            symbols[index] = coff.Symbol(symbol.name, 0, coff.UNDEFINED, symbol.type, coff.EXTERNAL)
        else:
            raise NotLinkable(f"its literal section holds the local symbol {symbol.name}")
    return coff.Object(sections, symbols, obj.timestamp), literals


def place(obj: coff.Object, start: int) -> tuple[dict[int, int], int]:
    """The address of each code section of obj, by section number, as link.exe lays them out from start: one after
    the other in the object's order, each at its alignment. And the address after the last."""
    placed, at = {}, start
    for number, section in enumerate(obj.sections, 1):
        if section.flags & coff.CODE:
            at += -at % section.alignment
            placed[number] = at
            at += section.size
    return placed, at


def resolve(obj: coff.Object, placed: dict[int, int], image: pe.Image) -> dict[str, int | None]:
    """Each name obj uses but does not define, with its address: the target of the original's bytes where obj's code
    uses it. None for a name its code never uses, such as __fltused."""
    uses = {symbol.name: None for symbol in obj.symbols.values() if symbol.section == coff.UNDEFINED}
    for number, at in placed.items():
        section = obj.sections[number - 1]
        for relocation in section.relocations:
            symbol = obj.symbols[relocation.symbol]
            if symbol.section != coff.UNDEFINED:
                continue
            site = at + relocation.offset
            addend = struct.unpack_from("<I", section.data, relocation.offset)[0]
            original = struct.unpack("<I", image.read(site, 4))[0]
            if relocation.kind == coff.DIR32:
                target = (original - addend) & 0xFFFFFFFF
            elif relocation.kind == coff.REL32:
                target = (original + site + 4 - addend) & 0xFFFFFFFF
            else:
                raise NotLinkable(f"its code has a relocation of type 0x{relocation.kind:x} at 0x{site:08x}")
            if uses[symbol.name] not in (None, target):
                raise NotLinkable(f"{symbol.name} is at both 0x{uses[symbol.name]:08x} and 0x{target:08x}")
            uses[symbol.name] = target
    return uses


def split_names(swaps: list[Swap]) -> dict[str, int | None]:
    """The names the split defines: those the swaps use and none of them defines."""
    defined = {symbol.name for swap in swaps for symbol in swap.obj.symbols.values()
               if symbol.storage == coff.EXTERNAL and symbol.section > 0}
    wanted = {}
    for swap in swaps:
        for name, address in swap.uses.items():
            if name in defined:
                continue
            if None not in (address, wanted.get(name)) and address != wanted[name]:
                raise NotLinkable(f"{swap.source} has {name} at 0x{address:08x}, another file at 0x{wanted[name]:08x}")
            if wanted.get(name) is None:
                wanted[name] = address
    return wanted


def hexes(addresses: list[int]) -> str:
    return " ".join(f"0x{address:08x}" for address in addresses)


# The split


def relink(image: pe.Image, header: pe.Header, swaps: list[Swap], out: Path) -> tuple[Path, int, list[str]]:
    """Split the original around swaps, link, embed the manifest and patch. Returns the rebuilt exe, the bytes
    mt.exe changed and the post-link patches."""
    if not header.characteristics & RELOCATIONS_STRIPPED:
        sys.exit("the exe has relocations: the split can't make them")
    out.mkdir(parents=True, exist_ok=True)
    wanted = split_names(swaps)
    wanted[ENTRY] = header.image_base + struct.unpack_from("<I", image.data, optional_header(image.data) + 16)[0]
    load_config = directory(image.data, LOAD_CONFIG)[0]
    if load_config:
        wanted["__load_config_used"] = header.image_base + load_config
    inputs = write_objects(link_order(pieces(image, header), swaps), image, wanted, out)
    rsrc = next((section for section in header.sections if section.name == ".rsrc"), None)
    manifest = None
    if rsrc:
        manifest = write_resources(image.data, rsrc, out / "resources.res")
        inputs.append(out / "resources.res")
    linked = link_exe(header, image.data, inputs, out / "linked.exe")
    mt_changes = 0
    if manifest:
        (out / "original.manifest").write_bytes(manifest)
        before = linked.read_bytes()
        project.run([MT, "-nologo", "-manifest", out / "original.manifest", f"-outputresource:{linked};#1"])
        mt_changes = osutil.byte_differences(before, linked.read_bytes())[0]
    rebuilt, patches = post_link(image.data, linked, out / "rebuilt.exe")
    return rebuilt, mt_changes, patches


def optional_header(data: bytes) -> int:
    return struct.unpack_from("<I", data, 0x3C)[0] + 24


def directory(data: bytes, index: int) -> tuple[int, int]:
    """The RVA and size of a data directory entry."""
    return struct.unpack_from("<II", data, optional_header(data) + 96 + 8 * index)


def pieces(image: pe.Image, header: pe.Header) -> list[Piece]:
    """The original's sections as raw pieces, .rsrc left out: link.exe groups them back into the same sections. The
    zero tail of a section is uninitialized data, which link.exe merges into .data."""
    found = []
    for section in header.sections:
        if section.name == ".rsrc":
            continue
        start = header.image_base + section.rva
        if section.name == ".rdata":
            cuts = import_cuts(image.data, header.image_base, section)
        else:
            cuts = [(start, section.name), (start + min(section.raw_size, section.virtual_size), None)]
        for (begin, name), (end, _) in zip(cuts, cuts[1:]):
            found.append(Piece(name, IDATA_FLAGS.get(name, (section.flags & ~coff.ALIGN_MASK) | coff.ALIGN_1),
                               begin, end))
        if section.virtual_size > section.raw_size:
            found.append(Piece(".bss", BSS_FLAGS, start + section.raw_size, start + section.virtual_size))
    return found


def import_cuts(data: bytes, base: int, rdata: pe.Section) -> list[tuple[int, str | None]]:
    """Where the import tables sit in .rdata, as (address, section name) starts, then the end. VC++ 2010's linker
    merges .idata into .rdata: the IAT (.idata$5) first, then the descriptors ($2), the null descriptor ($3), the name
    tables ($4) and the names ($6) at the end."""
    import_rva, import_size = directory(data, 1)
    iat_rva, iat_size = directory(data, 12)

    def at(rva: int) -> int:
        return rdata.raw_offset + rva - rdata.rva

    strings, descriptor = [], import_rva
    while struct.unpack_from("<I", data, at(descriptor) + 12)[0]:  # a descriptor with no DLL name ends the table
        lookup, _, _, dll, _ = struct.unpack_from("<5I", data, at(descriptor))
        strings.append(dll)
        while entry := struct.unpack_from("<I", data, at(lookup))[0]:
            if not entry & pe.IMPORT_BY_ORDINAL:
                strings.append(entry)
            lookup += 4
        descriptor += 20
    if iat_rva != rdata.rva or descriptor + 20 != import_rva + import_size:
        sys.exit("the import tables are not where VC++ 2010's linker puts them")
    cuts = [(iat_rva, ".idata$5"), (iat_rva + iat_size, ".rdata"), (import_rva, ".idata$2"), (descriptor, ".idata$3"),
            (descriptor + 20, ".idata$4"), (min(strings), ".idata$6"), (rdata.rva + rdata.virtual_size, None)]
    return [(base + rva, name) for rva, name in cuts]


def link_order(found: list[Piece], swaps: list[Swap]) -> list[list[Piece] | Swap]:
    """The link's inputs in order. The first holds every piece, with .text cut where the first swap starts. Each swap
    comes next, followed by the .text up to the next swap. link.exe keeps that order within .text."""
    text = next(piece for piece in found if piece.name == ".text")
    swaps = sorted(swaps, key=lambda swap: swap.start)
    previous_end = text.start
    for swap in swaps:
        if not previous_end <= swap.start <= swap.end <= text.end:
            raise NotLinkable(f"{swap.source} overlaps the file before it or lies outside .text")
        previous_end = swap.end
    cuts = [text.start, *[at for swap in swaps for at in (swap.start, swap.end)], text.end]
    texts = [Piece(".text", text.flags, start, end) for start, end in zip(cuts[::2], cuts[1::2])]
    order = [[texts[0] if piece is text else piece for piece in found]]
    for swap, after in zip(swaps, texts[1:]):
        order.append(swap)
        if after.end > after.start:
            order.append([after])
    return order


def write_objects(order: list[list[Piece] | Swap], image: pe.Image, wanted: dict[str, int | None],
                  out: Path) -> list[Path]:
    """Write the link's inputs. Each wanted name is defined in the piece that holds its address, or as absolute 0 if
    no code uses it."""
    raw = [piece for part in order if isinstance(part, list) for piece in part]
    homeless = [name for name, address in wanted.items()
                if address is not None and not any(piece.start <= address < piece.end for piece in raw)]
    if homeless:
        raise NotLinkable(f"no raw piece holds these names, so a swapped file has them inside: {' '.join(homeless)}")
    paths = []
    for index, part in enumerate(order):
        if isinstance(part, Swap):
            obj, label = part.obj, Path(part.source).stem
        else:
            obj, label = raw_object(part, image, wanted, absolutes=index == 0), "original"
        paths.append(out / f"{index:02d}-{label}.obj")
        paths[-1].write_bytes(coff.write(obj))
    return paths


def raw_object(found: list[Piece], image: pe.Image, wanted: dict[str, int | None], absolutes: bool) -> coff.Object:
    """found as raw sections, with the wanted names they hold. With absolutes, also the names no code uses."""
    sections = [coff.Section(piece.name, piece.flags, piece.end - piece.start if piece.flags & coff.UNINITIALIZED
                             else image.read(piece.start, piece.end - piece.start), []) for piece in found]
    symbols = [coff.section_symbol(number, section) for number, section in enumerate(sections, 1)]
    for name, address in wanted.items():
        if address is None:
            if absolutes:
                symbols.append(coff.Symbol(name, 0, coff.ABSOLUTE, 0, coff.EXTERNAL))
            continue
        for number, piece in enumerate(found, 1):
            if piece.start <= address < piece.end:
                symbols.append(coff.Symbol(name, address - piece.start, number, 0, coff.EXTERNAL))
    return coff.Object(sections, coff.numbered(symbols))


def resources(data: bytes, rsrc: pe.Section, offset: int = 0, ids: tuple = ()) -> Iterator[tuple]:
    """Each resource in .rsrc as (type, name, language, bytes). Numbered resources only."""
    named, count = struct.unpack_from("<HH", data, rsrc.raw_offset + offset + 12)
    if named:
        sys.exit("the exe has a resource with a string name: the split handles numbered ones only")
    for index in range(count):
        entry, target = struct.unpack_from("<II", data, rsrc.raw_offset + offset + 16 + 8 * index)
        if target & 0x80000000:  # a subdirectory
            yield from resources(data, rsrc, target & 0x7FFFFFFF, (*ids, entry))
        else:
            rva, size = struct.unpack_from("<II", data, rsrc.raw_offset + target)
            start = rsrc.raw_offset + rva - rsrc.rva
            yield *ids, entry, data[start:start + size]


def write_resources(data: bytes, rsrc: pe.Section, path: Path) -> bytes | None:
    """Write the exe's resources as a .res file, all but the manifest, which mt.exe embeds after the link as the
    original build did. Returns the manifest."""
    found = list(resources(data, rsrc))
    res = [RES_HEADER.pack(0, 32, 0xFFFF, 0, 0xFFFF, 0, 0, 0, 0, 0, 0)]  # every .res starts with this empty entry
    for kind, name, language, resource in found:
        if kind != RT_MANIFEST:
            res.append(RES_HEADER.pack(len(resource), 32, 0xFFFF, kind, 0xFFFF, name, 0, RES_FLAGS, language, 0, 0)
                       + resource + bytes(-len(resource) % 4))
    path.write_bytes(b"".join(res))
    return next((resource for kind, _, _, resource in found if kind == RT_MANIFEST), None)


# The link


def link_exe(header: pe.Header, data: bytes, inputs: list[Path], linked: Path) -> Path:
    """link.exe 10.0 on the inputs, with the original's header settings. No default libraries, and no removal or
    folding of unused or identical functions, so every input byte stays."""
    import check  # here, not at the top: check.py imports this module

    optional = optional_header(data)
    os_major, os_minor, _, _, subsystem_major, subsystem_minor = struct.unpack_from("<6H", data, optional + 40)
    stack_reserve, stack_commit, heap_reserve, heap_commit = struct.unpack_from("<4I", data, optional + 72)
    subsystem = {2: "WINDOWS", 3: "CONSOLE"}[header.subsystem]
    arguments = ["/NOLOGO", "/MACHINE:X86", f"/OUT:{linked}", "/FIXED", "/NODEFAULTLIB", "/OPT:NOREF", "/OPT:NOICF",
                 "/INCREMENTAL:NO", "/MANIFEST:NO", "/SAFESEH:NO", f"/ENTRY:{ENTRY[1:]}",
                 f"/SUBSYSTEM:{subsystem},{subsystem_major}.{subsystem_minor:02d}", f"/OSVERSION:{os_major}.{os_minor}",
                 f"/STACK:0x{stack_reserve:x},0x{stack_commit:x}", f"/HEAP:0x{heap_reserve:x},0x{heap_commit:x}",
                 *check.link_flags(header), *map(str, inputs)]
    response = linked.with_suffix(".rsp")
    response.write_text("\n".join(arguments), encoding="utf-8")
    output = project.run([LINK, f"@{response}"]).stdout.strip()
    if output:
        print(f"     link.exe: {output}")
    return linked


def post_link(original: bytes, linked: Path, rebuilt: Path) -> tuple[Path, list[str]]:
    """Add what no linker makes: the original's Rich header (which tools built its objects), its timestamp, its
    Authenticode signature, and the checksum over the result if the original has one. Returns the rebuilt exe and
    each patch it made."""
    ours = bytearray(linked.read_bytes())
    theirs_at, ours_at = optional_header(original) - 24, optional_header(ours) - 24
    if original[:0x3C] != ours[:0x3C] or original[0x40:0x80] != ours[0x40:0x80]:
        sys.exit("the DOS header or stub differs from the original's, not just the Rich header")
    section_count = struct.unpack_from("<H", ours, ours_at + 6)[0]
    optional_size = struct.unpack_from("<H", ours, ours_at + 20)[0]
    table_end = optional_header(ours) + optional_size + 40 * section_count
    headers = ours[ours_at:table_end]
    headers_end = struct.unpack_from("<I", ours, optional_header(ours) + 60)[0]
    if ours[table_end:headers_end].strip(b"\0") or theirs_at + len(headers) > headers_end:
        sys.exit("the headers leave no room to move the PE header")
    ours[0x80:headers_end] = original[0x80:theirs_at] + headers + bytes(headers_end - theirs_at - len(headers))
    struct.pack_into("<I", ours, 0x3C, theirs_at)
    patches = [f"Rich header: copied 0x80-0x{theirs_at:x}, PE header moved from 0x{ours_at:x} to 0x{theirs_at:x}"]
    timestamp = theirs_at + 8
    ours[timestamp:timestamp + 4] = original[timestamp:timestamp + 4]
    patches.append(f"TimeDateStamp: 0x{struct.unpack_from('<I', ours, timestamp)[0]:08x}")
    security = optional_header(ours) + 96 + 8 * SECURITY
    signature_at, signature_size = struct.unpack_from("<II", original, security)
    if signature_size:
        if signature_at != len(ours) or signature_at + signature_size != len(original):
            sys.exit("the original's signature does not start where the rebuilt file ends")
        struct.pack_into("<II", ours, security, signature_at, signature_size)
        ours += original[signature_at:]
        patches.append(f"signature: 0x{signature_size:x} bytes appended at 0x{signature_at:x}, security directory set")
    # 0 means the original has none, though mt.exe writes one.
    has_checksum = struct.unpack_from("<I", original, pe.checksum_offset(original))[0] != 0
    checksum = pe.checksum(bytes(ours)) if has_checksum else 0
    struct.pack_into("<I", ours, pe.checksum_offset(ours), checksum)
    patches.append(f"CheckSum: 0x{checksum:08x}, {'computed' if has_checksum else 'none, as in the original'}")
    rebuilt.write_bytes(ours)
    return rebuilt, patches


def compare(game: Path, header: pe.Header, rebuilt: Path, swaps: list[Swap], mt_changes: int,
            patches: list[str]) -> int:
    original, ours = game.read_bytes(), rebuilt.read_bytes()
    count = osutil.byte_differences(original, ours)[0]
    if count:
        # Any change moves the checksum, which comes before the sections, so point at the first other byte.
        first = osutil.byte_differences(pe.without_checksum(original), pe.without_checksum(ours))[1]
        print(f"FAIL the rebuilt exe differs from the original in {count:,} bytes, the first at "
              f"{'the CheckSum only' if first is None else where(first, header, swaps)}")
    else:
        print(f"ok   the rebuilt exe is the original, byte for byte: sha256 {hashlib.sha256(ours).hexdigest()}")
    for swap in sorted(swaps, key=lambda swap: swap.start):
        print(f"     swapped in {swap.source}: 0x{swap.start:08x}-0x{swap.end:08x}")
    print(f"     mt.exe changed {mt_changes:,} bytes")
    for patch in patches:
        print(f"     post-link: {patch}")
    return 1 if count else 0


def where(offset: int, header: pe.Header, swaps: list[Swap]) -> str:
    """A file offset as an address, with its section and the swapped file that covers it."""
    for section in header.sections:
        if section.raw_offset <= offset < section.raw_offset + section.raw_size:
            address = header.image_base + section.rva + offset - section.raw_offset
            source = next((f", in {swap.source}" for swap in swaps if swap.start <= address < swap.end), "")
            return f"0x{address:08x} ({section.name}{source})"
    return f"file offset 0x{offset:x}"
