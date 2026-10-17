"""Tie the game's functions to source files and classes, from what the exe itself says.

- Source paths. A function that uses a string such as "..\\src\\task.c" holds
  __FILE__, as asserts and log calls do. It sits in that file, or in a file that
  includes it when the path is a header.
- RTTI. Each class with virtual methods has a vtable, and the word before the
  vtable points at a locator that names the class. The vtable lists the class's
  virtual methods. The functions that use the vtable's address are its
  constructors and destructors.

`check.py sources` writes these to data/source-files.csv and data/classes.csv.
Standard library only.
"""

import bisect
import itertools
import re
import struct
from collections.abc import Iterator
from pathlib import Path
from typing import NamedTuple

import pe

# The end of a NUL-terminated path, from a folder on, to a C or C++ file.
SOURCE_PATH = re.compile(rb"[\\/][ -~]*?\.(?:c|cc|cpp|cxx|h|hpp|inl)\x00", re.IGNORECASE)
# The decorated class name in an RTTI type descriptor, which starts 8 bytes before it.
TYPE_NAME = re.compile(rb"\.\?A[UV][!-~]+?@@\x00")


class Use(NamedTuple):
    site: int  # where the code holds the address
    function: int | None  # the function in data/functions.csv around the site, if any


class Vtable(NamedTuple):
    address: int
    type: str  # the decorated class name, such as .?AVTObject@@
    offset: int  # where the class's part with this vtable sits in the object: not 0 only with multiple bases
    methods: list[int]
    uses: list[Use]


def find(exe: Path, functions: list[tuple[int, int]]) -> tuple[dict[str, list[Use]], list[Vtable]]:
    """The uses of each source path, and every vtable. functions holds (address, size) pairs."""
    image = pe.Image(exe)
    paths = source_paths(image)
    tables = vtables(image)
    found = uses(image, functions, set(paths) | {table.address for table in tables})
    by_path = {}
    for address, text in paths.items():
        if found.get(address):
            by_path.setdefault(text, []).extend(found[address])
    return by_path, [table._replace(uses=found.get(table.address, [])) for table in tables]


def data_sections(image: pe.Image) -> Iterator[tuple[int, bytes]]:
    """The address and bytes of each section that holds no code."""
    for start, _, section in image.sections:
        if not section.flags & pe.CODE:
            yield start, image.contents(section)


def code_sections(image: pe.Image) -> Iterator[tuple[int, bytes]]:
    """The address and bytes of each section that holds code."""
    for start, _, section in image.sections:
        if section.flags & pe.CODE:
            yield start, image.contents(section)


def strings(image: pe.Image, pattern: re.Pattern) -> dict[int, str]:
    """The address and text of each match of pattern in the sections that hold no code."""
    found = {}
    for start, data in data_sections(image):
        for match in pattern.finditer(data):
            found[start + match.start()] = match.group()[:-1].decode("ascii")
    return found


def source_paths(image: pe.Image) -> dict[int, str]:
    """Each address the code can hold to use a source path, and the path.

    Code holds the start of a string, and a path can end a longer string, such as an
    error message that forgot a comma before __FILE__. Data can also sit right before a
    string, with no NUL between. So every place from the last NUL to the path's last
    folder counts, and only the one the code uses shows. The path is the string's last
    part with no whitespace, so a path with a space in it would lose its start.
    """
    found = {}
    for start, data in data_sections(image):
        for match in SOURCE_PATH.finditer(data):
            found.update(path_addresses(start, data, match))
    return found


def path_addresses(start: int, data: bytes, match: re.Match) -> dict[int, str]:
    """Each address that can hold the source path of match, and the path. data starts at start."""
    first = data.rfind(b"\0", 0, match.start()) + 1
    end = match.end() - 1  # the NUL
    last_folder = max(data.rfind(b"\\", 0, end), data.rfind(b"/", 0, end))
    return {start + offset: data[offset:end].decode("latin1").split()[-1] for offset in range(first, last_folder + 1)}


def vtables(image: pe.Image) -> list[Vtable]:
    """Every vtable that has a locator. Locators and vtables sit in read-only data."""
    types = {address - 8: name for address, name in strings(image, TYPE_NAME).items()}
    sections = read_only_words(image)
    locators = {start + 4 * index: (types[words[index + 3]], words[index + 1])  # address: (class name, offset)
                for start, words in sections for index in range(len(words) - 4)
                if words[index] == 0 and words[index + 3] in types}
    return [table for section in sections for table in section_vtables(image, section, locators)]


def read_only_words(image: pe.Image) -> list[tuple[int, tuple[int, ...]]]:
    """The address and 4-byte words of each read-only data section."""
    sections = []
    for start, _, section in image.sections:
        if not section.flags & (pe.CODE | pe.WRITABLE):
            data = image.contents(section)
            sections.append((start, struct.unpack_from(f"<{len(data) // 4}I", data)))
    return sections


def section_vtables(image: pe.Image, section: tuple[int, tuple[int, ...]], locators: dict) -> list[Vtable]:
    """The vtables in one section, given as its address and words."""
    start, words = section
    tables = []
    for index, word in enumerate(words):
        if word in locators:
            methods = list(itertools.takewhile(image.is_code, itertools.islice(words, index + 1, None)))
            tables.append(Vtable(start + 4 * index + 4, *locators[word], methods, []))
    return tables


def uses(image: pe.Image, functions: list[tuple[int, int]], targets: set[int]) -> dict[int, list[Use]]:
    """For each target address that the code holds as a 4-byte value: where, and in which function.

    Every 4 bytes of code count, so instruction bytes can spell a target by chance. The
    compiler aligns string literals and vtables to 4 bytes, so only aligned targets count.
    """
    targets = {target for target in targets if target % 4 == 0}
    starts = [address for address, _ in functions]
    found = {}
    for start, data in code_sections(image):
        for offset, value in held_targets(data, targets):
            site = start + offset
            index = bisect.bisect_right(starts, site) - 1
            inside = index >= 0 and site < functions[index][0] + functions[index][1]
            found.setdefault(value, []).append(Use(site, functions[index][0] if inside else None))
    return found


def held_targets(data: bytes, targets: set[int]) -> Iterator[tuple[int, int]]:
    """The offset and value of each 4-byte value in data that is a target."""
    for offset in range(len(data) - 3):
        value = struct.unpack_from("<I", data, offset)[0]
        if value in targets:
            yield offset, value
