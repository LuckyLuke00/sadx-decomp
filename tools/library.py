"""Find the runtime library's functions and globals in the original exe, for src/library.csv.

The game linked the static runtime libraries that our toolchain has. So each of
their functions and data sections is in the exe byte for byte, except the bytes
the linker filled with addresses. find() looks for every library function at the
exe's function starts, with those bytes masked. Each match's calls and addresses
then say what sits at their targets, code or data, and the function after it in
its object comes next. The search goes on there. The exe's import table names
each import slot.

A small function can match code it is not, so a match only counts with evidence:
16 or more fixed bytes, a call or reference from a match that counts, a
neighbor from the same object file that counts, or only calls and addresses
that matches which count already use under the same names. Data matches only if
what it points to matches too. `check.py library` then links every function match
into our exe, and reccmp scores each one.
Standard library only.
"""

import collections
import functools
import struct
import sys
from pathlib import Path
from typing import Callable, Iterator, NamedTuple

import libobjects
import pe

# The C and C++ runtime libraries: the static runtime, which CMakeLists.txt links by default, or the
# DLL runtime's import libraries, which also hold the startup code that an exe links statically.
STATIC_RUNTIME = ("libcmt.lib", "libcpmt.lib")
DLL_RUNTIME = ("msvcrt.lib", "msvcprt.lib")
DELAY_LOAD = "delayimp.lib"  # __delayLoadHelper2, which an exe with delay imports links
SURE = 16  # fixed bytes that make a match count without other evidence
STRONG = 32  # fixed bytes that make a match outside the library ranges worth trying
REL32, DIR32 = 0x14, 0x06  # COFF relocation types
IMPORT_JUMP = b"\xff\x25"  # jmp [address]: the linker's thunk for an imported function
IMPORT_PREFIX = "__imp_"  # the symbol of an import address table slot: __imp_ and the function's symbol


class Row(NamedTuple):
    """A row of src/library.csv."""
    address: int
    name: str
    symbol: str
    kind: str  # the reccmp type; "" for a label inside a function


class Found(NamedTuple):
    rows: list[Row]
    game_calls: dict[int, str]  # the game functions that library code calls by name, such as WinMain: address: name


class Layout(NamedTuple):
    """What check.py knows of the exe's code."""
    starts: list[int]  # the exe's known function starts
    ranges: list[tuple[int, int]]  # where library code may sit


def runtime_dlls(imports: list[str]) -> list[str]:
    """The C runtime DLLs among an exe's imports. An empty list means it linked the static runtime."""
    return [name for name in imports if name.upper().startswith("MSVCR")]


def find(exe: Path, layout: Layout, libraries: list[Path]) -> Found:
    """The library functions and globals in exe that reccmp can match to ours."""
    image = Image(exe)
    index = Index(list(libobjects.library_functions(libraries)))
    search = Search(image, index, layout.ranges)
    search.run(layout.starts)
    accepted = Chooser(search).run()
    return Found(RowFinder(image, accepted, index.functions).rows(), find_game_calls(image, accepted, index))


class Index:
    """The library functions, by key, by their first four bytes, by place and by fold class."""

    def __init__(self, functions: list[libobjects.Function]):
        self.functions = functions
        self.by_key = collections.defaultdict(list)  # key: (function, offset of the key in it)
        self.by_prefix = collections.defaultdict(list)
        for function in functions:
            self.add(function)
        self.by_place = {(function.member, function.place): function for function in functions}
        # The original link folded identical functions into one, so a call may name any of them.
        self.classes = fold_classes(functions)
        self.fold = fold_keys(functions, self.classes)

    def add(self, function: libobjects.Function) -> None:
        for key in function.keys:
            self.by_key[key].append((function, 0))
        for label in function.labels:
            self.by_key[label.key].append((function, label.offset))
        if not function.data:
            masked = len(function.code) < 4 or any(function.mask[:4])
            self.by_prefix[None if masked else function.code[:4]].append(function)


def fold_keys(functions: list[libobjects.Function], classes: dict[int, int]) -> dict[str, set[str]]:
    """For each key, the keys at the same spot in every function of its fold class."""
    folded = collections.defaultdict(set)  # (fold class, offset): the keys there
    for function in functions:
        for offset, keys in function.spots().items():
            folded[classes[id(function)], offset] |= keys
    fold = collections.defaultdict(set)
    for keys in folded.values():
        for key in keys:
            fold[key] |= keys
    return fold


def fold_classes(functions: list[libobjects.Function]) -> dict[int, int]:
    """The functions that the linker's identical code folding can merge, as id(function): class.

    Two foldable functions, or two foldable data sections, fold when their bytes match and each
    reference names the same symbol, or the same spot in a static function or section that folds too.
    So two functions with identical exception tables fold. Statics of the same name in two
    objects, such as write_string in output.obj and outputs.obj, fold only when what they
    call folds, so the classes split until they are stable.
    """
    statics = {key: (function, offset)  # a static key: its function and its offset there
               for function in functions for offset, keys in function.spots().items() for key in keys if "!" in key}

    def target(key: str) -> str | tuple[int, int]:
        if key not in statics:
            return key
        function, offset = statics[key]
        return classes[id(function)], offset

    classes = {id(function): 0 for function in functions}
    count = 1
    while True:
        signatures = {id(function): (classes[id(function)], function.code,
                                     tuple((r.offset, r.kind, target(r.key)) for r in function.references))
                      if function.foldable else id(function) for function in functions}
        numbers = {signature: number for number, signature in enumerate(dict.fromkeys(signatures.values()))}
        classes = {identity: numbers[signature] for identity, signature in signatures.items()}
        if len(numbers) == count:
            return classes
        count = len(numbers)


class Search:
    """Where in the exe the library functions may sit: the candidates, as the evidence finds them."""

    def __init__(self, image: "Image", index: Index, ranges: list[tuple[int, int]]):
        self.image = image
        self.index = index
        self.ranges = ranges
        self.fits = functools.cache(lambda target, key: self.fits_below(target, key, set()))
        self.candidates = collections.defaultdict(dict)  # address: {fold class: the functions in it}
        self.tried = set()
        self.masked = {}  # first byte: masked_starting()

    def in_ranges(self, address: int) -> bool:
        return any(start <= address < end for start, end in self.ranges)

    def fits_below(self, target: int, key: str, path: set[tuple[int, int]]) -> bool:
        """Whether the library function, label, data or import that key names can sit at target.
        The exe's import table names each import slot. Code outside the ranges always fits: for an
        inline function from a library header, such as std::locale::facet::_Decref, the linker may
        keep the game's copy, built with the game's flags. Data fits only if what it points to fits
        too, since two exception types' tables differ only in the type name at the end of a chain.
        A chain that comes back to a section on the path fits, as RTTI's class hierarchies do."""
        if key.startswith(IMPORT_PREFIX):
            return self.image.import_slots.get(target) == libobjects.plain_name(key.removeprefix(IMPORT_PREFIX))
        if not self.index.by_key[key] or self.image.is_code(target) and not self.in_ranges(target):
            return True
        for other, offset in self.index.by_key[key]:
            start = target - offset
            if not self.image.matches(start, other):
                continue
            if not other.data or (start, id(other)) in path:
                return True
            path.add((start, id(other)))
            below = all(self.fits_below(inner, reference.key, path) for inner, reference in self.image.targets(start, other))
            path.discard((start, id(other)))
            if below:
                return True
        return False

    def attempt(self, address: int, function: libobjects.Function) -> bool:
        if (address, id(function)) in self.tried:
            return False
        self.tried.add((address, id(function)))
        placed = not self.image.is_code(address) if function.data else self.in_ranges(address) or function.fixed >= STRONG
        if not placed or not self.image.matches(address, function):
            return False
        self.candidates[address].setdefault(self.index.classes[id(function)], []).append(function)
        return True

    def leads(self, address: int, function: libobjects.Function) -> Iterator[tuple[int, libobjects.Function]]:
        """Where a match says other library functions are."""
        for target, reference in self.image.targets(address, function):
            for other, offset in self.index.by_key[reference.key]:
                yield target - offset, other
        section, offset = function.place
        following = self.index.by_place.get((function.member, (section, offset + len(function.code))))
        if following:
            yield address + len(function.code), following

    def run(self, starts: list[int]) -> None:
        """Try every library function at the known function starts, then wherever the matches lead."""
        for address in starts:
            head = self.image.read(address, 4)
            for function in self.index.by_prefix[head] + self.masked_starting(head[0]):
                self.attempt(address, function)
        pending = list(self.candidates)
        while pending:
            pending += self.follow(pending.pop())

    def masked_starting(self, byte: int) -> list[libobjects.Function]:
        """The functions with a masked byte in their first four that can start with byte."""
        if byte not in self.masked:
            self.masked[byte] = [function for function in self.index.by_prefix[None]
                                 if function.mask[:1] != b"\0" or function.code[0] == byte]
        return self.masked[byte]

    def follow(self, address: int) -> list[int]:
        """The new candidate addresses that the matches at address lead to."""
        found = []
        for options in list(self.candidates[address].values()):
            for function in options:
                found += [target for target, other in self.leads(address, function) if self.attempt(target, other)]
        return found


def keys_of(function: libobjects.Function) -> list[str]:
    """Every key that names an address of a function: its start, then each label."""
    return [key for keys in function.spots().values() for key in keys]


class Chooser:
    """One function per address, for each address where the evidence picks one.

    The linker folded identical functions, so an address can fit the same function in several
    objects. The loop picks one at once, from the calls it knows by then. After the loop, each
    pick is redone from the final calls and neighbors, until none moves.
    """

    def __init__(self, search: Search):
        self.image = search.image
        self.candidates = search.candidates
        self.fold = search.index.fold
        self.fits = search.fits
        self.ordered = sorted(self.candidates)
        self.accepted: dict[int, libobjects.Function] = {}
        self.folded: dict[int, list[libobjects.Function]] = {}  # address: the functions the linker may have folded there
        self.refresh()

    def run(self) -> dict[int, libobjects.Function]:
        changed = True
        while changed:
            self.refresh()
            changed = self.sweep(self.accept)

        # Settle the picks with the calls of the last pass. A move raises the total of the calls, or at the
        # same total joins the object beside it, so this ends.
        moved = True
        while moved:
            moved = self.sweep(self.repick)

        # A symbol has one address. Two matches for one symbol mean one of them is wrong.
        counts = collections.Counter(key for function in self.accepted.values() for key in keys_of(function))
        return {address: function for address, function in self.accepted.items()
                if all(counts[key] == 1 for key in keys_of(function))}

    def refresh(self) -> None:
        """Count what the accepted functions place and call. A pass works from these counts."""
        self.placed = collections.defaultdict(set)  # address: the keys that accepted functions and their labels have there
        for address, function in self.accepted.items():
            for offset, keys in function.spots().items():
                self.placed[address + offset] |= keys
        self.calls = collections.defaultdict(collections.Counter)  # address: the keys accepted functions use it as
        for address, function in self.accepted.items():
            for target, reference in self.image.targets(address, function):
                self.calls[target][reference.key] += 1
        self.claims = {target: set().union(*(self.fold.get(key, {key}) for key in keys))
                       for target, keys in self.calls.items()}

    def sweep(self, step: Callable[[int, int], bool]) -> bool:
        """Run step on every address in order. Whether any of them changed a pick."""
        changed = False
        for index, address in enumerate(self.ordered):
            changed |= step(index, address)
        return changed

    def neighbors_of(self, index: int) -> set[str]:
        # The linker keeps an object file's functions together.
        around = self.ordered[max(index - 1, 0):index] + self.ordered[index + 1:index + 2]
        return {self.accepted[other].member for other in around if other in self.accepted}

    def pick(self, address: int, functions: list[libobjects.Function], neighbors: set[str]) -> libobjects.Function:
        # Of functions the linker folded, the one most calls name, then the one beside its object.
        return max(functions, key=lambda f: (
            sum(self.calls[address + offset][key] for offset, keys in f.spots().items() for key in keys),
            f.member in neighbors))

    def consistent(self, address: int, function: libobjects.Function) -> bool:
        for offset, keys in function.spots().items():
            if address + offset in self.claims and not keys & self.claims[address + offset]:
                return False
        for target, reference in self.image.targets(address, function):
            if not self.fits(target, reference.key):
                return False
            known = self.placed.get(target) or self.claims.get(target)
            if known and not self.fold.get(reference.key, {reference.key}) & known:
                return False
        return True

    def anchored(self, address: int, function: libobjects.Function) -> bool:
        """Whether every call and address of a match points at a place that is known by now."""
        targets = [target for target, _ in self.image.targets(address, function)]
        return bool(targets) and all(target in self.placed or target in self.claims or target in self.image.import_slots
                                     for target in targets)

    def has_evidence(self, address: int, functions: list[libobjects.Function], neighbors: set[str]) -> bool:
        near = any(function.member in neighbors for function in functions)
        return address in self.claims or near or self.anchored(address, functions[0]) or functions[0].fixed >= SURE

    def accept(self, index: int, address: int) -> bool:
        """Accept the pick at an address if the evidence has one. Whether it did."""
        if address in self.accepted:
            return False
        neighbors = self.neighbors_of(index)
        options = [functions for functions in self.candidates[address].values()
                   if self.consistent(address, functions[0])]
        beside = [functions for functions in options if any(f.member in neighbors for f in functions)]
        options = beside if len(options) > 1 and address not in self.claims else options
        if len(options) != 1 or not self.has_evidence(address, options[0], neighbors):
            return False
        self.accepted[address] = self.pick(address, options[0], neighbors)
        self.folded[address] = options[0]
        return True

    def repick(self, index: int, address: int) -> bool:
        """Redo the pick at an address from the final calls. Whether it moved."""
        if address not in self.accepted:
            return False
        # The current pick goes first, so a tie keeps it.
        best = self.pick(address, [self.accepted[address], *self.folded[address]], self.neighbors_of(index))
        if best is self.accepted[address]:
            return False
        self.accepted[address] = best
        return True


def find_game_calls(image: "Image", accepted: dict[int, libobjects.Function], index: Index) -> dict[int, str]:
    """The game functions that the library code calls by name, as address: name."""
    # No library defines the function that the startup code calls, such as WinMain: the game does.
    return {target: libobjects.plain_name(reference.symbol)
            for address, function in accepted.items() if not function.data
            for target, reference in image.targets(address, function)
            if reference.symbol and not index.by_key.get(reference.key) and image.is_code(target)
            and image.read(target, 2) != IMPORT_JUMP}


class RowFinder:
    """The rows reccmp can match: by symbol, or by name.

    A static function or global has no symbol, and our PDB names it only if its
    object has a CodeView record for it. Our exe has its object only if some
    function in it has a symbol, which check.py links. Two objects can give a
    static the same name, such as write_char in output.obj and outputs.obj.
    reccmp pairs such rows with our statics of that name in address order, and
    shows each by name. So a global's row always works. A function's row works
    only if our exe has no other static of its name. Our link keeps every
    function of each object it links, so the original exe must hold every
    function of that name in those objects.
    """

    def __init__(self, image: "Image", accepted: dict[int, libobjects.Function], functions: list[libobjects.Function]):
        self.image = image
        self.accepted = accepted
        self.code = {address: function for address, function in accepted.items() if not function.data}
        self.linked = {function.member for function in self.code.values() if function.symbol}
        found_names = collections.Counter(function.name for function in self.code.values())
        library_names = collections.Counter(function.name for function in functions
                                            if function.member in self.linked and not function.data)
        self.whole = {name for name in found_names if found_names[name] == library_names[name]}  # the names whose every function in the linked objects was found
        self.targets = {target for target, _ in self.references()}

    def references(self) -> Iterator[tuple[int, libobjects.Reference]]:
        """Where the calls and addresses of the accepted functions point."""
        for address, function in self.accepted.items():
            yield from self.image.targets(address, function)

    def rows(self) -> list[Row]:
        found = self.import_rows()
        found.update(self.global_rows())
        for address, function in self.code.items():
            found.update(self.code_rows(address, function))
        return sorted(found.values())

    def import_rows(self) -> dict[int, Row]:
        found = {}
        for target, reference in self.references():
            if (self.image.is_code(target) and reference.symbol and not reference.name
                    and self.image.read(target, 2) == IMPORT_JUMP):
                found[target] = Row(target, libobjects.plain_name(reference.symbol), reference.symbol, "library")
        return found

    def global_rows(self) -> dict[int, Row]:
        uses = collections.defaultdict(set)
        for target, reference in self.references():
            if not self.image.is_code(target):
                uses[target].add(reference)
        # A global's address is sure when every use agrees on it and no other address has its symbol.
        sure = {target: next(iter(refs)) for target, refs in uses.items() if len({r.key for r in refs}) == 1}
        addresses = collections.Counter(reference.key for reference in sure.values())
        found = {}
        for target, reference in sure.items():
            # A static's key starts with its object.
            if (addresses[reference.key] == 1 and reference.name
                    and (reference.symbol or reference.key.partition("!")[0] in self.linked)):
                found[target] = Row(target, reference.name, reference.symbol, data_kind(reference.key))
        return found

    def code_rows(self, address: int, function: libobjects.Function) -> dict[int, Row]:
        """The rows of a function and its labels."""
        found = {}
        if function.symbol or (function.member in self.linked and function.name and function.name in self.whole):
            found[address] = Row(address, function.name, function.symbol, "library")
        for label in function.labels:
            row = self.label_row(address, function, label)
            if row is not None:
                found[row.address] = row
        return found

    def label_row(self, address: int, function: libobjects.Function, label: libobjects.Label) -> Row | None:
        at = address + label.offset
        if label.symbol:
            return Row(at, label.name, label.symbol, "")
        if label.table and label.name and function.member in self.linked:
            return Row(at, label.name, "", "global")
        if at in self.targets:
            # reccmp reads no asm label from our PDB, so our side shows an address placeholder at one, such
            # as TrailUp0 in memcpy.asm. A row with no name gives the game's side one too. It has no type
            # either: reccmp ends the game's function at the next variable, but not at a label.
            return Row(at, "", "", "")
        return None


def delay_load_rows(exe: Path, sdk_lib: Path) -> list[Row]:
    """Rows for the code and data that the linker makes for the exe's delay imports: for each DLL its
    import descriptor and __tailMerge_ function, and for each function its slot and __imp_load_ thunk.
    No library object holds them. The linker makes them from the DLL's import library in sdk_lib,
    which also gives the decorated name of each function."""
    image = pe.Image(exe)
    rows = []
    for delay in pe.read_header(exe).delay_imports:
        rows += dll_delay_rows(delay, image, sdk_lib)
    return rows


def dll_delay_rows(delay: pe.DelayImport, image: pe.Image, sdk_lib: Path) -> list[Row]:
    """The rows for the delay imports of one DLL."""
    suffix = delay.dll.replace(".", "_")
    symbols = libobjects.import_symbols(sdk_lib / f"{Path(delay.dll).stem}.lib")
    rows = [Row(delay.descriptor, f"__DELAY_IMPORT_DESCRIPTOR_{suffix}", f"__DELAY_IMPORT_DESCRIPTOR_{suffix}", "global")]
    tail_merges = set()
    for slot, function in delay.slots.items():
        if function not in symbols:
            sys.exit(f"{delay.dll}: {function} is in no import library entry of {Path(delay.dll).stem}.lib.")
        symbol = symbols[function]
        # A slot holds the address of its thunk, mov eax, slot; jmp __tailMerge_.
        thunk = struct.unpack("<I", image.read(slot, 4))[0]
        code = image.read(thunk, 10)
        if code[0] != 0xB8 or code[5] != 0xE9:
            sys.exit(f"{delay.dll}: 0x{thunk:08x} is no delay-load thunk for {function}.")
        tail_merges.add(thunk + 10 + struct.unpack("<i", code[6:])[0])
        rows.append(Row(slot, f"__imp_{symbol}", f"__imp_{symbol}", "global"))
        rows.append(Row(thunk, f"__imp_load_{symbol}", f"__imp_load_{symbol}", "library"))
    return rows + [Row(tail_merge, f"__tailMerge_{suffix}", f"__tailMerge_{suffix}", "library") for tail_merge in tail_merges]


def data_kind(symbol: str) -> str:
    """reccmp's type for a library global, from the compiler's symbol prefixes."""
    for prefix, kind in (("??_C@_0", "string"), ("??_C@_1", "widechar"), ("??_7", "vtable"), ("__real@", "float")):
        if symbol.startswith(prefix):
            return kind
    return "global"


# The exe


class Image(pe.Image):
    """The original exe, where library functions are looked for."""

    def matches(self, address: int, function: libobjects.Function) -> bool:
        data = self.read(address, len(function.code))
        return len(data) == len(function.code) and all(
            masked or ours == theirs for ours, theirs, masked in zip(function.code, data, function.mask))

    def targets(self, address: int, function: libobjects.Function) -> Iterator[tuple[int, libobjects.Reference]]:
        """Where the calls and addresses of a function matched at address point."""
        for reference in function.references:
            field = self.read(address + reference.offset, 4)
            if reference.kind not in (REL32, DIR32) or not reference.key or len(field) < 4:
                continue
            # The object holds an addend where the linker writes the address.
            value = struct.unpack("<I", field)[0] - struct.unpack_from("<I", function.code, reference.offset)[0]
            if reference.kind == REL32:
                value += address + reference.offset + 4
            yield value & 0xFFFFFFFF, reference
