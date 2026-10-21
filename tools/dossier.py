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

Names come from the tree's annotations, the files `check.py decls` wrote last,
src/library.csv and the --tables folder (tools/declgen.py says what it holds). --context
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


def known_functions(tables: Path | None, sources: dict[str, str], before: names.Previous) -> dict[int, Function]:
    """The functions with a name or a signature: the tree, then the last stubs. A tables row wins, but
    the tree's signature fills one the row lacks."""
    found = {}
    for rel, text in sources.items():
        for kind, address, sig in names.parse_annotations(text):
            if kind in names.FUNCTION_KINDS and names.declared_name(sig):
                proto = re.sub(r"^static\s+", "", sig)
                found.setdefault(address, Function(names.declared_name(sig), proto, proto != sig, rel, ""))
    for address, sig in before.stubs.items():
        found.setdefault(address, Function(names.declared_name(sig), sig, False, "", ""))
    if tables:
        for r in names.table_rows(tables / "functions.tsv"):
            a = int(r["address"], 16)
            proto = r["proto"] or (found[a].proto if a in found else "")
            found[a] = Function(r["name"], proto, r["scope"] == "L", r["file"], r["note"], r.get("locals", ""))
    return found


def known_globals(tables: Path | None, sources: dict[str, str], before: names.Previous,
                  types: names.Types) -> list[Global]:
    """The globals with a name, by address: the tables first, then the tree, then the last generated ones."""
    found = {}
    if tables:
        for r in names.table_rows(tables / "globals.tsv"):
            a = int(r["address"], 16)
            found[a] = Global(a, int(r["size"] or 0), r["name"], r["decl"].replace("{}", r["name"]))
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
    head, _, tail = definition.partition(name)
    element = names.element_size(re.sub(r"\b(?:static|extern)\b", "", head).strip(), types)
    counts = re.findall(r"\[\s*(\w*)\s*\]", tail)
    if element is None or not all(count.isdigit() for count in counts):
        return 0
    return element * math.prod(int(count) for count in counts)


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


def disassemble(image: pe.Image, namer: Namer, address: int, size: int) -> list[str]:
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
                    name = namer.data(target)
                    if name is None and ins.mnemonic.startswith("f") and op.size in (4, 8):
                        name = namer.constant(target, op.size)
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


def ghidra_c(address: int, drafts: Path, functions: dict[int, Function], globals_: list[Global]) -> str:
    path = drafts / f"{address:08x}.c"
    if not path.exists():
        return f"(no Ghidra draft: {path} is missing)"
    text = path.read_text(encoding="utf-8")
    global_names = {g.address: g.name for g in globals_}

    def fun(m):
        f = functions.get(int(m.group(1), 16))
        return f.name if f else m.group(0)

    def dat(m):
        return global_names.get(int(m.group(1), 16), m.group(0))

    text = re.sub(r"\bFUN_([0-9a-f]{8})\b", fun, text)
    text = re.sub(r"\b(?:DAT|PTR_DAT|PTR)_([0-9a-f]{8})\b", dat, text)
    return text.strip()


def show(game: Path, addresses: list[int], draft: bool, callers: bool, tables: Path | None,
         drafts: Path | None, access: bool = False, facts: Callable[..., list[str]] | None = None,
         context: Path | None = None) -> int:
    sources = names.read_sources(ROOT)
    added = names.context_sources(context, sources)  # a lane holds only its item's files
    sources |= added
    before = names.previous(ROOT)
    if added:
        theirs = names.previous(context)
        before = names.Previous(theirs.stubs | before.stubs, theirs.globals | before.globals,
                                theirs.externs | before.externs)
    types = names.Types(tables / "types.h" if tables else ROOT / names.TYPES_H)
    functions = known_functions(tables, sources, before)
    globals_ = known_globals(tables, sources, before, types)
    sizes = {f["address"]: f["size"] for f in progress.load_functions()}
    library = {row.address: row.name for row in project.library_rows()}
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
        code = disassemble(image, namer, address, size)
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
            print(ghidra_c(address, drafts or DRAFTS, functions, globals_))
        print()
    return 1 if missing else 0
