"""What an agent needs to decompile one function: `check.py dossier`.

Prints the function's name, signature, code group and flags, file, register-argument
cluster and note. Then its assembly with call targets, globals, strings and float
constants named, and the declaration of each name it uses. --callers adds the
functions that call it, jump to it or take its address. --accesses adds, under each
global, how the whole exe reads and writes it (tools/accesses.py). --c adds Ghidra's draft C
with the same names, from <drafts>/<address>.c: tools/ghidra/DumpDecomp.java writes
those, and docs/FRAMEWORK.md says how. --facts adds a "facts:" list after the header
(tools/facts.py): what the assembly hides, such as a register argument, a callee that pops
its arguments, a global that holds a pointer and a type with no body in the types header.
--hide-own leaves out the prototype that a shown function's own definition gives, as before it was
decompiled: a tables row's prototype still shows.

Names come from the tree's annotations, the files `check.py decls` wrote last,
src/library.csv and the --tables folder (tools/declgen.py says what it holds). A LIBRARY annotation's
name wins over a tables row: the build checks it. --context
adds another checkout's annotations and last decls files, as decls does: this tree's own win.
Needs capstone, so it runs in .venv.
"""

import bisect
import collections
import math
import re
import struct
from collections.abc import Callable
from pathlib import Path
from typing import NamedTuple

import capstone
from reccmp.cvdump.demangler import msvc_demangle

import accesses
import names
import pe
import progress
import project
import x86

ROOT = project.ROOT
ACCESS_GROUPS = 6  # most-used kinds of access shown per global
CALLERS = project.BUILD / "callers.tsv"
DRAFTS = project.BUILD / "decomp"
STRING = "basic_string<char, struct std::char_traits<char>, class std::allocator<char>>"  # as the demangler spells it
SPECIFIERS = re.compile(r"^(?:public|protected|private): |\b__(?:thiscall|cdecl|stdcall|fastcall) ")


class Function(NamedTuple):
    name: str
    proto: str
    static: bool
    file: str
    note: str
    locals: str = ""  # local declarations, from a tables row


class Global(NamedTuple):
    address: int
    size: int
    name: str
    decl: str


def known_functions(tables: Path | None, sources: dict[str, str], before: names.Previous,
                    hidden: frozenset[int] = frozenset()) -> dict[int, Function]:
    """The functions with a name or a signature: the tree, then the last stubs. A tables row wins, but
    the tree's signature fills one the row lacks. A HIDDEN address's definition gives no prototype, as before
    it was decompiled."""
    found = {}
    for rel, text in sources.items():
        for kind, address, sig in names.parse_annotations(text):
            if kind in names.FUNCTION_KINDS and names.declared_name(sig):
                proto = re.sub(r"^static\s+", "", sig)
                shown = "" if address in hidden else proto
                found.setdefault(address, Function(names.declared_name(sig), shown, proto != sig, rel, ""))
    for address, sig in before.stubs.items():
        found.setdefault(address, Function(names.declared_name(sig), sig, False, "", ""))
    if tables:
        for r in names.table_rows(tables / "functions.tsv"):
            a = int(r["address"], 16)
            proto = r["proto"] or (found[a].proto if a in found else "")
            found[a] = Function(r["name"], proto, r["scope"] == "L", r["file"], r["note"], r.get("locals", ""))
    return found


def library_annotations(sources: dict[str, str]) -> dict[int, str]:
    """The name on the comment line under each LIBRARY annotation, demangled when it is a decorated name."""
    found = {}
    for text in sources.values():
        for m in names.annotation().finditer(text):
            if m.group(1) != "LIBRARY":
                continue
            line = text[m.end():].split("\n", 2)[1].strip()
            if line.startswith("//"):
                name = line[2:].strip()
                plain = SPECIFIERS.sub("", msvc_demangle(name) or name).replace("std::" + STRING, "std::string")
                found[int(m.group(2), 16)] = plain.replace(STRING, "basic_string")
    return found


def known_globals(tables: Path | None, sources: dict[str, str], before: names.Previous,
                  types: names.Types) -> list[Global]:
    """The globals with a name, by address: the tables first, then the tree, then the last generated ones. A name
    that several rows share stays DAT_: a file means only one of them by it, and decls gives the name where it does."""
    found = {}
    if tables:
        rows = names.table_rows(tables / "globals.tsv")
        counts = collections.Counter(r["name"] for r in rows)
        for r in rows:
            a = int(r["address"], 16)
            r = dict(r, name=f"DAT_{a:08x}") if counts[r["name"]] > 1 else r
            found[a] = Global(a, int(r["size"] or 0), r["name"], names.row_declaration(r))
    definitions = [(address, sig) for text in sources.values()
                   for kind, address, sig in names.parse_annotations(text) if kind == "GLOBAL"]
    for address, sig in definitions + list(before.globals.items()):
        definition = sig.split("=")[0].strip()
        name = names.declared_name(definition)
        if name:
            found.setdefault(address, Global(address, global_size(definition, name, types), name, definition))
    return sorted(found.values())


def global_size(definition: str, name: str, types: names.Types) -> int:
    """The bytes a definition takes, or 0 when a type's size is unknown."""
    _, element, counts = element_layout(definition, name, types)
    if element is None or None in counts:
        return 0
    return element * math.prod(counts)


def element_layout(definition: str, name: str, types: names.Types) -> tuple[str, int | None, list[int | None]]:
    """(the element type of a definition, its size or None when unknown, the count in each of its array brackets:
    decimal or hex, else None)."""
    head, _, tail = definition.partition(name)
    base = re.sub(r"\b(?:static|extern)\b", "", head).strip()
    counts = [int(count, 0) if re.fullmatch(r"[1-9]\d*|0[xX][0-9a-fA-F]+", count) else None
              for count in re.findall(r"\[\s*(\w*)\s*\]", tail)]
    return base, names.element_size(base, types), counts


def member_path(g: Global, offset: int, types: names.Types) -> str | None:
    """The element and member of G that OFFSET falls in, such as name[2].speed or name[0].pos+0x4, or None when G is
    no array and its type has no known layout."""
    base, element, counts = element_layout(g.decl, g.name, types)
    if element is None or None in counts[1:]:
        return None
    path, rest = g.name, offset
    for i in range(len(counts)):
        stride = element * math.prod(counts[i + 1:])
        path, rest = f"{path}[{rest // stride}]", rest % stride
    tag = re.fullmatch(r"(?:const\s+)?struct\s+(\w+)", base)  # a union's members all start at 0
    at = {offset: member for member, offset in types.offsets(tag.group(1)).items()} if tag else {}
    start = max((o for o in at if o <= rest), default=None)
    if start is not None:
        path, rest = f"{path}.{at[start]}", rest - start
    if path == g.name:
        return None
    return path if rest == 0 else f"{path}+0x{rest:x}"


class Namer:
    def __init__(self, image: pe.Image, functions: dict[int, Function], sizes: dict[int, int],
                 library: dict[int, str], globals_: list[Global]):
        self.image, self.functions, self.sizes, self.library = image, functions, sizes, library
        self.globals = globals_
        self.starts = [g.address for g in globals_]
        self.used = {}

    def function(self, address: int) -> str | None:
        if address in self.functions:
            f = self.functions[address]
            self.used[address] = ("function", f.name, f.proto or "(no known prototype)")
            return f.name
        if address in self.library:
            return self.library[address] + " (library)"
        if address in self.sizes:
            name = f"FUN_{address:08x}"
            self.used[address] = ("function", name, "(no known prototype)")
            return name
        return None

    def data(self, address: int) -> str | None:
        if address in self.image.import_slots:
            return "[import] " + self.image.import_slots[address]
        held = self.holder(address)
        if held:
            g, offset = held
            self.used[g.address] = ("global", g.name, g.decl)
            return g.name if offset == 0 else f"{g.name}+0x{offset:x}"
        return self.string(address)

    def holder(self, address: int) -> tuple[Global, int] | None:
        """The known global that holds ADDRESS, and the offset into it."""
        i = bisect.bisect_right(self.starts, address) - 1
        if i >= 0:
            g = self.globals[i]
            if g.address == address or g.address < address < g.address + max(g.size, 1):
                return g, address - g.address
        return None

    def string(self, address: int) -> str | None:
        raw = self.image.read(address, 256)
        end = raw.find(b"\0")
        if end < 2:
            return None
        body = raw[:end]
        if all(32 <= b < 127 or b in (9, 10, 13) for b in body):
            return '"' + body.decode("ascii").encode("unicode_escape").decode("ascii").replace('"', '\\"') + '"'
        return None

    def constant(self, address: int, width: int) -> str | None:
        raw = self.image.read(address, width)
        if len(raw) != width:
            return None
        if width == 4:
            return f"float {struct.unpack('<f', raw)[0]!r}"
        if width == 8:
            return f"double {struct.unpack('<d', raw)[0]!r}"
        return None


def disassembler() -> capstone.Cs:
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    return md


def data_note(namer: Namer, address: int, types: names.Types) -> str | None:
    """The name of the data at ADDRESS for a note: the element and member it falls in when its holder's layout is
    known, else namer.data's name."""
    name = namer.data(address)  # it also lists the holder under the names used
    held = namer.holder(address)
    path = member_path(*held, types) if held and held[1] else None
    return path or name


def disassemble(image: pe.Image, namer: Namer, address: int, size: int, types: names.Types) -> list[str]:
    """The lines of the function's assembly, each with a note that names its call target, global, string or float
    constant. A memory operand with a base register and a data address, as in [esi + 0x5b93488], names it too."""
    lines = []
    for ins in disassembler().disasm(image.read(address, size), address):
        note = []
        if ins.group(capstone.CS_GRP_CALL) or ins.group(capstone.CS_GRP_JUMP):
            for op in ins.operands:
                if op.type == capstone.x86.X86_OP_IMM:
                    target = op.imm
                    if not (address <= target < address + size):
                        name = namer.function(target)
                        note.append(name or f"0x{target:08x}")
                elif op.type == capstone.x86.X86_OP_MEM and op.mem.base == 0 and op.mem.index == 0:
                    name = namer.data(op.mem.disp & 0xFFFFFFFF)
                    if name:
                        note.append(name)
        else:
            for op in ins.operands:
                if op.type == capstone.x86.X86_OP_MEM and op.mem.base == 0 and op.mem.disp:
                    target = op.mem.disp & 0xFFFFFFFF
                    name = data_note(namer, target, types)
                    if name is None and ins.mnemonic.startswith("f") and op.size in (4, 8):
                        name = namer.constant(target, op.size)
                    if name:
                        note.append(name)
                elif (op.type == capstone.x86.X86_OP_MEM and image.contains(op.mem.disp)
                      and not image.is_code(op.mem.disp)):
                    name = data_note(namer, op.mem.disp, types)
                    if name:
                        note.append(name)
                elif op.type == capstone.x86.X86_OP_IMM and op.imm > 0x400000:
                    target = op.imm & 0xFFFFFFFF
                    name = namer.function(target) or namer.data(target)
                    if name:
                        note.append(name)
        text = f"{ins.address:08x}  {ins.bytes.hex():<20} {ins.mnemonic} {ins.op_str}"
        if note:
            text = f"{text:<70} ; {', '.join(note)}"
        lines.append(text)
    return lines


def write_callers(image: pe.Image, sizes: dict[int, int]) -> None:
    """build/callers.tsv: for each function, the functions that call it, jump to it or take its address."""
    md = disassembler()
    refs = collections.defaultdict(set)
    for a, size in sizes.items():
        for ins in md.disasm(image.read(a, size), a):
            for op in ins.operands:
                if op.type == capstone.x86.X86_OP_IMM and op.imm in sizes and op.imm != a:
                    kind = "call" if ins.mnemonic == "call" else ("jmp" if ins.mnemonic.startswith("j") else "ref")
                    refs[op.imm].add((a, kind))
    CALLERS.parent.mkdir(parents=True, exist_ok=True)
    with open(CALLERS, "w", encoding="utf-8", newline="\n") as f:
        for target in sorted(refs):
            listed = ", ".join(f"0x{c:08x}" + ("" if k == "call" else f" ({k})") for c, k in sorted(refs[target]))
            f.write(f"0x{target:08x}\t{listed}\n")


def fresh_callers(image: pe.Image, sizes: dict[int, int]) -> None:
    """Write build/callers.tsv again when data/functions.csv is newer."""
    if not CALLERS.exists() or CALLERS.stat().st_mtime < progress.FUNCTIONS_CSV.stat().st_mtime:
        write_callers(image, sizes)


def read_callers(image: pe.Image, sizes: dict[int, int]) -> dict[int, list[tuple[int, str]]]:
    """build/callers.tsv as target -> (caller, kind), with kind "call", "jmp" or "ref"."""
    fresh_callers(image, sizes)
    found = {}
    with open(CALLERS, encoding="utf-8") as f:
        for line in f:
            target, listed = line.rstrip("\n").split("\t", 1)
            items = [item.split() for item in listed.split(", ")]
            found[int(target, 16)] = [(int(item[0], 16), item[1].strip("()") if len(item) > 1 else "call")
                                      for item in items]
    return found


def callers_of(image: pe.Image, sizes: dict[int, int], target: int) -> str:
    fresh_callers(image, sizes)
    key = f"0x{target:08x}\t"
    with open(CALLERS, encoding="utf-8") as f:
        found = [line.rstrip("\n").split("\t", 1)[1] for line in f if line.startswith(key)]
    return ", ".join(found) or "none"


def ghidra_c(address: int, drafts: Path, functions: dict[int, Function], namer: Namer, types: names.Types) -> str:
    """Ghidra's draft with the known names. An address inside a known global becomes its element and member, else
    keeps Ghidra's name with a comment that names the holder."""
    path = drafts / f"{address:08x}.c"
    if not path.exists():
        return f"(no Ghidra draft: {path} is missing)"
    text = path.read_text(encoding="utf-8")

    def fun(m):
        f = functions.get(int(m.group(1), 16))
        return f.name if f else m.group(0)

    def dat(m):
        held = namer.holder(int(m.group(1), 16))
        if held is None:
            return m.group(0)
        g, offset = held
        if offset == 0:
            return g.name
        member = member_path(g, offset, types)  # a member path with a +0xN rest is no C
        return member if member and "+" not in member else f"{m.group(0)} /* {g.name}+0x{offset:x} */"

    text = re.sub(r"\bFUN_([0-9a-f]{8})\b", fun, text)
    text = re.sub(r"\b(?:DAT|PTR_DAT|PTR)_([0-9a-f]{8})\b", dat, text)
    return text.strip()


def show(game: Path, addresses: list[int], draft: bool, callers: bool, tables: Path | None,
         drafts: Path | None, access: bool = False, facts: Callable[..., list[str]] | None = None,
         context: Path | None = None, hide_own: bool = False) -> int:
    sources = names.read_sources(ROOT)
    added = names.context_sources(context, sources)  # a lane holds only its item's files
    sources |= added
    before = names.previous(ROOT)
    if added:
        theirs = names.previous(context)
        before = names.Previous(theirs.stubs | before.stubs, theirs.globals | before.globals,
                                theirs.externs | before.externs)
    types = names.Types(tables / "types.h" if tables else ROOT / names.TYPES_H)
    functions = known_functions(tables, sources, before, frozenset(addresses) if hide_own else frozenset())
    globals_ = known_globals(tables, sources, before, types)
    sizes = {f["address"]: f["size"] for f in progress.load_functions()}
    annotated = library_annotations(sources)
    library = {row.address: row.name for row in project.library_rows()} | annotated
    functions = {address: f for address, f in functions.items() if address not in annotated}
    groups = progress.load_codegen_groups()
    cluster_rows = progress.read_csv(ROOT / "data" / "file-clusters.csv")
    clusters = {int(r["address"], 16): r["cluster"] for r in cluster_rows}
    passes = {int(r["address"], 16): r["callees"].split() for r in cluster_rows}
    takes = {int(callee, 16) for callees in passes.values() for callee in callees}
    image = pe.Image(game)
    namer = Namer(image, functions, sizes, library, globals_)
    decoder = x86.Decoder(image, library)
    access_rows = accesses.load(image) if access else None
    global_sizes = {g.address: g.size for g in globals_}
    missing = 0
    for address in addresses:
        size = sizes.get(address)
        if size is None:
            print(f"0x{address:08x}: not a function in {progress.FUNCTIONS_CSV.relative_to(ROOT).as_posix()}")
            missing += 1
            continue
        f = functions.get(address, Function(library.get(address, f"FUN_{address:08x}"), "", False, "", ""))
        group = progress.codegen_group(groups, address)
        code = disassemble(image, namer, address, size, types)
        print(f"== 0x{address:08x} {f.name}  ({size} bytes)")
        print(f"prototype: {f.proto or '(none known: choose the types from the code)'}")
        if f.locals:
            print(f"locals: {f.locals}")
        if f.static:
            print("linkage: static (local to its file)")
        elif address in takes:
            print("linkage: static (its callers in this file pass it arguments in registers)")
        if group:
            print(f"group: {group['group']}  flags: {group['flags']}")
        if f.file:
            print(f"file: {f.file}")
        if address in clusters:
            print(f"register-argument cluster: {clusters[address]} (these functions share one file)")
        if passes.get(address):
            print(f"register-argument calls: to {', '.join(passes[address])}. They match only once those functions "
                  "are static in this file. Until then the build pushes their arguments.")
        if f.note:
            print(f"note: {f.note}")
        if facts:
            lines = facts(decoder.function(address, size, 0), f, group["flags"] if group else "",
                          address in clusters, namer, types, decoder, sizes)
            if lines:
                print("facts:")
                print("\n".join(f"  - {line}" for line in lines))
        print()
        print("\n".join(code))
        if namer.used:
            print("\nnames used:")
            for a, (kind, name, decl) in sorted(namer.used.items()):
                if a != address:
                    print(f"  {kind} 0x{a:08x} {decl}")
                    if access_rows is not None and kind == "global":
                        print("    exe-wide:", accesses.summary(access_rows, a, global_sizes[a], ACCESS_GROUPS))
        namer.used = {}
        if callers:
            print("\ncallers:", callers_of(image, sizes, address))
        if draft:
            print("\nGhidra draft (types and names are guesses; the assembly is the truth):")
            print(ghidra_c(address, drafts or DRAFTS, functions, namer, types))
        print()
    return 1 if missing else 0
