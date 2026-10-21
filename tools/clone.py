"""Write the copies of matched functions: `check.py clone`.

  python tools/check.py clone 0x00401000 [...] [--tables DIR]
  python tools/check.py clone --all [--tables DIR]

A copy is a game function whose instructions equal those of a function at 100%, its template,
apart from the addresses in them: the functions it calls and the globals, strings and constants
it uses. clone writes the template's code under the copy's name, with each name the template uses
swapped for the name at the same place in the copy. Names come from the same places as for
`check.py dossier`. The copy's prototype gives its parameter names, else they are param_N. A copy
goes in the file the tables give it, else in src/unplaced. A copy that the tree defines stays as
it is, but a STUB is replaced. With --all, every FUNCTION at 100% is a template.

The template's types are its own guesses, so a copy takes only the types its own sources give it: its
prototype, and the declarations the tree already has. Where the copy needs a type that nothing gives it
(its signature without a prototype, a global or a function the tree does not declare), it gets a neutral
one: the signed integer of the same size for an integer or an enum, void * for a pointer; float, double
and void stay. A pointer type stays only where the copy passes the name straight to a function whose
prototype in the tables takes that type. The copy gets none of the template file's pragmas or includes.

Several static functions can share a name, one in each file. decls stops when two of them are used or
defined and one of them has no static definition. So for each such name that a kept copy uses or
defines, clone writes a static STUB in its file for each one that the tree uses but does not define.

Then clone runs `check.py decls`, builds and scores. It takes out each copy that stops decls or
the build, and keeps only the copies at 100%. It also takes out the copies that need a STUB in a
file where a function that was at 100% no longer is. One line per copy and per STUB says what
happened.

A copy is skipped, with the reason, when:
- one name in the template has two names in the copy, or an offset into a global differs;
- a string, a constant, an import or a library function differs;
- an address in the copy has no name, or a name is not a plain C name;
- the copy's prototype, or the type of a name the copy uses, differs from the template's;
- the template uses a named local that the copy's locals entry in the tables lacks;
- a type it needs has no neutral one (a struct or union by value, an array);
- it uses or defines a shared name that a global function has too, or that the tree defines without static;
- it uses a global whose name several globals have: decls wants each one static in its own file, with a GLOBAL
  annotation, and clone has no layout for it.
Needs capstone, so it runs in .venv.
"""

import collections
import contextlib
import io
import re
import sys
from pathlib import Path
from typing import Iterable, NamedTuple

import capstone

import check
import declgen
import dossier
import llm
import names
import pe
import progress
import project
import runner

ROOT = project.ROOT
NAME = re.compile(r"[A-Za-z_]\w*")
CALL = re.compile(r"\b([A-Za-z_]\w*)\s*\(")
NEUTRAL_INTEGERS = {1: "char", 2: "short", 4: "int", 8: "__int64"}  # by size
DECLS_SUMMARY = re.compile(r"^decls: \d+ functions")
ERROR_LINE = re.compile(r"\berror\b")


class Skip(Exception):
    """Why a copy cannot be written: a short kind, for the totals, and the details."""

    def __init__(self, kind: str, detail: str):
        super().__init__(f"{kind}: {detail}")
        self.kind = kind


class Slot(NamedTuple):
    kind: str  # "code" (a call or jump target), "imm" (an immediate) or "data" (a memory operand's address)
    value: int
    width: int  # the operand's bytes


class Shape(NamedTuple):
    tokens: tuple  # the instructions, each without its addresses
    slots: tuple[Slot, ...]  # those addresses, in order


class Target(NamedTuple):
    kind: str  # "function", "global", "library", "import" or "string"
    name: str
    offset: int = 0  # into a global


class Pair(NamedTuple):
    new: str  # the copy's name for a name in the template
    kind: str  # "function" or "global"
    template: int  # the address the template's name stands for
    copy: int


class Copy(NamedTuple):
    address: int
    name: str
    template: int
    file: str
    lines: list[str]  # the definition
    decls: list[str]  # the top-of-file declarations it needs
    names: frozenset[str]  # its own name, the names it uses that the template does not, and its shared names
    shared: frozenset[str]  # the names it uses or defines that several static functions have


class Stub(NamedTuple):
    address: int
    name: str
    file: str
    lines: list[str]  # the definition
    decls: list[str]  # none: llm.apply_function declares a static function itself


def stub(address: int, file: str, proto: str) -> Stub:
    """A static STUB with an empty body, as decls writes one, for the function at ADDRESS in FILE."""
    sig = "static " + re.sub(r"^static\s+", "", proto.rstrip(";").strip())
    lines = [f"// STUB: {project.game_config().target} {llm.hexa(address)}", sig] + declgen.stub_body(sig).split("\n")
    return Stub(address, names.declared_name(sig), file, lines, [])


def stubs_needed(kept: list[Copy], siblings: dict[str, list[int]], defined: set[int], planned: dict[int, Stub],
                 uses: dict[str, set[str]]) -> list[Stub]:
    """The PLANNED STUBs that the KEPT copies need. A shared name that a kept copy uses or defines needs a static
    definition for each of its functions when two or more of them are defined or used. A static function is used
    only where its file uses the name: USES gives the names the tree uses for each file."""
    defined = defined | {copy.address for copy in kept}
    needed = []
    for name in sorted({name for copy in kept for name in copy.shared}):
        used = [planned[a] for a in siblings[name] if a not in defined and a in planned
                and (name in uses.get(planned[a].file, ()) or any(copy.file == planned[a].file and name in copy.shared
                                                                  for copy in kept))]
        if len(used) + sum(a in defined for a in siblings[name]) > 1:
            needed += used
    return needed


def shape(md: capstone.Cs, image: pe.Image, address: int, size: int) -> Shape:
    """The function's instructions, with each address in the image taken out as a slot. A jump inside the
    function stays, as its offset from the start."""
    end = address + size
    tokens, slots, decoded = [], [], 0
    for ins in md.disasm(image.read(address, size), address):
        branch = ins.group(capstone.CS_GRP_CALL) or ins.group(capstone.CS_GRP_JUMP)
        ops = []
        for op in ins.operands:
            if op.type == capstone.x86.X86_OP_IMM:
                value = op.imm & 0xFFFFFFFF
                if address <= value < end:
                    ops.append(f"L{value - address}")
                elif branch or image.contains(value):
                    slots.append(Slot("code" if branch else "imm", value, op.size))
                    ops.append("A")
                else:
                    ops.append(value)
            elif op.type == capstone.x86.X86_OP_MEM:
                m = op.mem
                disp = m.disp & 0xFFFFFFFF
                if address <= disp < end:
                    disp = f"L{disp - address}"
                elif image.contains(disp):
                    slots.append(Slot("data", disp, op.size))
                    disp = "A"
                ops.append((m.segment, m.base, m.index, m.scale, disp, op.size))
            else:
                ops.append(op.reg)
        tokens.append((ins.mnemonic, ins.size, *ops))
        decoded += ins.size
    tokens.append(image.read(address + decoded, size - decoded))  # bytes that are no instructions, such as a table
    return Shape(tuple(tokens), tuple(slots))


def target(namer: dossier.Namer, slot: Slot) -> Target | None:
    """What a slot's address is, by name."""
    if slot.kind != "data":
        name = namer.function(slot.value)
        if name and name.endswith(" (library)"):
            return Target("library", name.removesuffix(" (library)"))
        if name:
            return Target("function", name)
        if slot.kind == "code":
            return None
    name = namer.data(slot.value)
    if name is None:
        return None
    if name.startswith("[import] "):
        return Target("import", name.removeprefix("[import] "))
    if name.startswith('"'):
        return Target("string", name)
    base, _, offset = name.partition("+")
    return Target("global", base, int(offset, 16) if offset else 0)


def placeholder(kind: str, address: int) -> str:
    """The name the tree gives a function or global at ADDRESS that has no name."""
    return f"{'FUN' if kind == 'function' else 'DAT'}_{address:08x}"


def name_map(namer: dossier.Namer, image: pe.Image, template: Shape, copy: Shape) -> dict[str, Pair]:
    """Each function and global name the template uses: the copy's name at the same slot."""
    pairs = {}
    for t, c in zip(template.slots, copy.slots):
        old, new = target(namer, t), target(namer, c)
        if old and old.kind == "global" and old.offset == 0 and new is None and c.kind != "code":
            new = Target("global", placeholder("global", c.value))
        if old is None and new is None:
            if t.value == c.value or t.kind == "data" and image.read(t.value, t.width) == image.read(c.value, c.width):
                continue
            raise Skip("constant differs", f"0x{t.value:08x} against 0x{c.value:08x}")
        if old is None or new is None:
            raise Skip("no name", f"0x{(t if old is None else c).value:08x}")
        if old.kind != new.kind:
            raise Skip("kind differs", f"{old.kind} {old.name} against {new.kind} {new.name}")
        if old.kind in ("library", "import", "string"):
            if old.name != new.name:
                raise Skip(f"{old.kind} differs", f"{old.name} against {new.name}")
            continue
        if old.offset != new.offset:
            raise Skip("offset differs", f"{old.name}+0x{old.offset:x} against {new.name}+0x{new.offset:x}")
        for name in (old.name, new.name):
            if not NAME.fullmatch(name):
                raise Skip("not a C name", name)
        pair = pairs.setdefault(old.name, Pair(new.name, old.kind, t.value - old.offset, c.value - new.offset))
        if pair.new != new.name:
            raise Skip("two names", f"{old.name} is {pair.new} and {new.name}")
    return pairs


def renamed(sig: str, name: str) -> str:
    """SIG declaring NAME instead."""
    old = names.declared_name(sig)
    return re.sub(rf"\b{re.escape(old)}\b(?=\s*\()", name, sig, count=1)


def parameter_name(param: str) -> str | None:
    """The name a parameter declares: None for an unnamed one, `void` and `...`."""
    if param in ("void", "...") or names.without_parameter_name(param) == " ".join(param.split()):
        return None
    return names.declared_name(param)


def with_name(param: str, name: str) -> str:
    """An unnamed parameter, named."""
    if re.search(r"\(\s*\*\s*\)", param):
        return re.sub(r"\(\s*\*\s*\)", f"(*{name})", param, count=1)
    return param + name if param.endswith("*") else f"{param} {name}"


def copy_signature(template_sig: str, name: str, proto: str, static: bool) -> tuple[str, dict[str, str]]:
    """The copy's signature and the new name of each template parameter. The copy's prototype gives its types
    and the names it has; with no prototype, the template's types. Every other parameter is param_N."""
    template_sig = re.sub(r"^static\s+", "", template_sig)
    sig = proto.rstrip(";").strip() if proto else renamed(template_sig, name)
    t_span, c_span = names.parameter_span(template_sig), names.parameter_span(sig)
    if t_span is None or c_span is None:
        raise Skip("layout", f"no parameter list in `{template_sig}` or `{sig}`")
    t_params = [p for p in t_span[2] if p != "void"]
    c_params = [p for p in c_span[2] if p != "void"]
    if len(t_params) != len(c_params):
        raise Skip("prototype", f"`{sig}` has {len(c_params)} parameters, the template {len(t_params)}")
    if not same_type(sig, renamed(template_sig, name)):
        raise Skip("type differs", f"`{sig}` against the template's `{template_sig}`")
    params, renames = [], {}
    for number, (t, c) in enumerate(zip(t_params, c_params), 1):
        old, new = parameter_name(t), parameter_name(c) if proto else None
        if old is None or new is not None:
            params.append(c)
            new = new or old
        else:
            new = f"param_{number}"
            params.append(with_name(names.without_parameter_name(c), new))
        if old and old != new:
            renames[old] = new
    if c_params:
        start, end, _ = c_span
        sig = sig[:start] + ", ".join(params) + sig[end:]
    return ("static " if static else "") + sig, renames


def copy_body(definition: list[str], renames: dict[str, str]) -> list[str]:
    """The definition's lines from its opening brace on, with each name in RENAMES swapped. Members keep theirs."""
    brace = next((i for i, line in enumerate(definition) if line == "{"), None)
    if brace is None:
        raise Skip("layout", "no line that is just {")
    renames = {old: new for old, new in renames.items() if old != new}
    if not renames:
        return definition[brace:]
    words = "|".join(re.escape(old) for old in sorted(renames, key=len, reverse=True))
    pattern = re.compile(rf"(?<!\.)(?<!->)\b({words})\b")
    return [pattern.sub(lambda m: renames[m.group(1)], line) for line in definition[brace:]]


def neutral_type(type_: str) -> str:
    """TYPE as the tree writes one that nothing confirms: the signed integer of its size for an integer or an enum,
    void * for a pointer. void, float and double stay."""
    type_ = " ".join(re.sub(r"\b(?:const|volatile)\b", "", type_).split())
    if type_.endswith("*") or "(*" in type_:
        return "void *"
    if type_ in ("void", "float", "double"):
        return type_
    if type_.startswith("enum "):
        return "int"
    if type_ in names.SCALAR_SIZES:
        return NEUTRAL_INTEGERS[names.SCALAR_SIZES[type_]]
    raise Skip("no neutral type", f"`{type_}`")


def neutral_function(sig: str, uses: dict[str, list[str]]) -> str:
    """SIG with a neutral type for each type it spells. A pointer parameter keeps its type when USES, the types that a
    prototype gives each name, has it."""
    static, sig = re.fullmatch(r"(static\s+)?(.*)", sig, re.S).groups()
    at = re.search(rf"\b{re.escape(names.declared_name(sig))}\s*\(", sig)
    start, end, params = names.parameter_span(sig)
    types = []
    for param in params:
        name = parameter_name(param)
        type_ = names.without_parameter_name(param)
        if param != "..." and not any(same_type(type_, given) for given in uses.get(name, ())):
            type_ = neutral_type(type_)
        types.append(type_ if name is None else with_name(type_, name))
    result = neutral_type(sig[:at.start()])
    return (static or "") + result + ("" if result.endswith("*") else " ") + sig[at.start():start] \
        + ", ".join(types) + sig[end:]


def neutral_extern(decl: str, name: str, uses: list[str]) -> str:
    """The extern line DECL with a neutral type, unless USES, the types that a prototype gives NAME, has its type."""
    body = decl.removeprefix("extern ").removesuffix(";")
    if "[" in body:
        raise Skip("no neutral type", f"`{body}`")
    type_ = "void *" if "(*" in body else body.rpartition(name)[0].strip()
    if not any(same_type(type_, given) for given in uses):
        type_ = neutral_type(type_)
    return f"extern {type_}{'' if type_.endswith('*') else ' '}{name};"


def call_arguments(text: str, start: int) -> list[str]:
    """The arguments of the call whose opening parenthesis is just before TEXT[start]."""
    depth, args, cur = 0, [], ""
    for ch in text[start:]:
        if ch in ")]" and depth == 0:
            break
        depth += (ch in "([") - (ch in ")]")
        if ch == "," and depth == 0:
            args.append(cur)
            cur = ""
        else:
            cur += ch
    return [arg.strip() for arg in args + [cur] if arg.strip()]


def pointer_uses(body: list[str], protos: dict[str, str]) -> dict[str, list[str]]:
    """Each name that BODY passes straight to a function whose prototype in PROTOS takes a pointer there: the pointer
    types it takes."""
    text = names.strip_code("\n".join(body))
    found = collections.defaultdict(list)
    for call in CALL.finditer(text):
        span = names.parameter_span(protos[call.group(1)]) if call.group(1) in protos else None
        for arg, param in zip(call_arguments(text, call.end()), span[2] if span else ()):
            type_ = names.without_parameter_name(param)
            if NAME.fullmatch(arg) and type_.endswith("*"):
                found[arg].append(type_)
    return found


def check_locals(template_locals: str, copy_locals: str, definition: list[str]) -> None:
    """Each named local the template uses must be in the copy's locals entry too."""
    used = set(NAME.findall(names.strip_code("\n".join(definition))))
    have = {d.strip() for d in copy_locals.split(";")}
    for decl in (d.strip() for d in template_locals.split(";")):
        if decl and names.declared_name(decl) in used and decl not in have:
            raise Skip("locals differ", f"the copy's locals lack `{decl}`")


def check_globals(pairs: dict[str, Pair], shared: set[str]) -> None:
    """The copy must not use a global whose name is in SHARED, the names that several globals have."""
    for pair in pairs.values():
        if pair.kind == "global" and pair.new in shared:
            raise Skip("shared name", f"{pair.new} 0x{pair.copy:08x} is a global with the name of others")


class Tree:
    """What the tree and the tables know about the functions, globals and files."""

    def __init__(self, game: Path, tables: Path | None):
        sources = names.read_sources(ROOT)
        before = names.previous(ROOT)
        types = names.Types(tables / "types.h" if tables else ROOT / names.TYPES_H)
        self.functions = dossier.known_functions(tables, sources, before)
        globals_ = dossier.known_globals(tables, sources, before, types)
        count = collections.Counter(g.name for g in globals_)
        self.shared_globals = {name for name, number in count.items() if number > 1}
        rows = progress.load_functions()
        self.sizes = {f["address"]: f["size"] for f in rows}
        library = {row.address: row.name for row in project.library_rows()}
        self.game = progress.game_addresses(rows) - library.keys()
        self.image = pe.Image(game)
        self.namer = dossier.Namer(self.image, self.functions, self.sizes, library, globals_)
        self.md = dossier.disassembler()
        self.shapes = {}
        self.sources = sources
        self.defined = {}  # address: (file, annotation kind)
        self.nonstatic = set()  # the addresses the tree defines without static
        self.local_functions, self.local_globals = {}, {}  # file: {name: its top-of-file declaration}
        self.signatures = {}  # name: a top-of-file declaration of it, from any file
        self.declared = {f.name for f in self.functions.values() if f.proto} | {g.name for g in globals_}
        for rel, text in sources.items():
            for kind, address, sig in names.parse_annotations(text):
                if kind in names.FUNCTION_KINDS:
                    self.defined[address] = (rel, kind)
                    if not re.match(r"static\b", sig):
                        self.nonstatic.add(address)
            funcs, vars_ = names.local_declarations(text)
            self.local_functions[rel], self.local_globals[rel] = dict(funcs), dict(vars_)
            self.declared |= self.local_functions[rel].keys() | self.local_globals[rel].keys()
            for name, sig in funcs:
                self.signatures.setdefault(name, sig)
        by_name = collections.defaultdict(set)  # the prototypes that a tables row gives each name
        for row in names.table_rows(tables / "functions.tsv") if tables else ():
            if row["proto"]:
                by_name[row["name"]].add(row["proto"])
        self.protos = {name: next(iter(protos)) for name, protos in by_name.items() if len(protos) == 1}
        self.claimed = {}  # name: the type this run's copies give it, as claim() writes it
        # Names as decls reads them: several functions share one, a library name or an address name never.
        self.siblings = collections.defaultdict(list)  # name: the addresses that have it
        library_names = set(library.values())
        for address, f in sorted(self.functions.items()):
            if f.name not in library_names and not f.name.startswith(("FUN_", "?")) and "::" not in f.name:
                self.siblings[f.name].append(address)
        self.homes = collections.defaultdict(set)  # a tables file: the tree's files that hold its functions
        for address, (rel, _) in self.defined.items():
            if address in self.functions and self.functions[address].file:
                self.homes[self.functions[address].file].add(rel)
        self.stubs = {}  # address: the STUB a copy with a shared name can need there

    def kind(self, address: int) -> str | None:
        return self.defined[address][1] if address in self.defined else None

    def name(self, address: int) -> str:
        return self.functions[address].name if address in self.functions else placeholder("function", address)

    def shape(self, address: int) -> Shape:
        if address not in self.shapes:
            self.shapes[address] = shape(self.md, self.image, address, self.sizes[address])
        return self.shapes[address]

    def copies_of(self, templates: list[int]) -> dict[int, list[int]]:
        """Each game function without a definition that has a template's shape: those templates, lowest first."""
        wanted = {self.sizes[t] for t in templates}
        by_shape = collections.defaultdict(list)
        for address in sorted(self.game):
            if self.sizes[address] in wanted and self.kind(address) in (None, "STUB"):
                by_shape[self.shape(address).tokens].append(address)
        found = collections.defaultdict(list)
        for t in sorted(templates):
            for address in by_shape.get(self.shape(t).tokens, ()):
                found[address].append(t)
        return found

    def definition(self, address: int) -> list[str]:
        lines = self.sources[self.defined[address][0]].split("\n")
        span = llm.definition_span(lines, address)
        if span is None:
            raise Skip("layout", f"the template 0x{address:08x} has no line that is just }}")
        return lines[span[0]:span[1] + 1]

    def plan(self, address: int, template: int) -> Copy:
        """The copy at ADDRESS, written from TEMPLATE."""
        pairs = name_map(self.namer, self.image, self.shape(template), self.shape(address))
        check_globals(pairs, self.shared_globals)
        template_file = self.defined[template][0]
        definition = self.definition(template)
        template_sig = names.parse_annotations("\n".join(definition))[0][2]
        own = self.functions.get(address)
        name = self.name(address)
        if not NAME.fullmatch(name):
            raise Skip("not a C name", name)
        functions = {name} | {pair.new for pair in pairs.values() if pair.kind == "function"}
        shared = frozenset(n for n in functions if self.shared(n, address))
        check_locals(self.functions[template].locals if template in self.functions else "",
                     own.locals if own else "", definition)
        proto = own.proto if own and own.proto else self.signatures.get(name, "")
        sig, renames = copy_signature(template_sig, name, proto, own.static if own else False)
        renames |= {old: pair.new for old, pair in pairs.items()}
        # The template may spell a name by its address, as the tree does before a name is known.
        renames |= {placeholder(pair.kind, pair.template): pair.new for pair in pairs.values()}
        renames[names.declared_name(template_sig)] = name
        body = copy_body(definition, renames)
        uses = pointer_uses(body, self.protos)
        if not proto:
            sig = neutral_function(sig, uses)
        decls = self.declarations(pairs, template_file, uses)
        lines = [llm.function_line(address), sig] + body
        self.claim([sig] + decls)
        if address in self.defined:
            file = self.defined[address][0]
        elif own and own.file:
            file = own.file
        else:
            file = f"src/unplaced/FUN_{address:08x}{Path(template_file).suffix}"
        new_names = frozenset({name} | {pair.new for old, pair in pairs.items() if pair.new != old})
        return Copy(address, name, template, file, lines, decls, new_names | shared, shared)

    def shared(self, name: str, own: int) -> bool:
        """Whether several static functions have NAME. Each must then be static where the tree defines it, and each
        that the tree does not define gets a planned STUB. OWN is the copy's address: it replaces the tree's STUB."""
        siblings = self.siblings.get(name, [])
        if len(siblings) < 2 or not any(self.functions[a].static for a in siblings):
            return False  # one function, or global overloads
        for a in siblings:
            if not self.functions[a].static:
                raise Skip("shared name", f"{name} 0x{a:08x} is global")
            if a != own and a in self.nonstatic:
                raise Skip("shared name", f"{name} 0x{a:08x} in {self.defined[a][0]} is not static")
        for a in siblings:
            if a not in self.defined and self.functions[a].file:
                self.stubs[a] = stub(a, self.functions[a].file, self.functions[a].proto)
        return True

    def needed_stubs(self, kept: list[Copy]) -> list[Stub]:
        """The planned STUBs that the KEPT copies need."""
        uses = {}  # file: the names the tree uses there and in its other files that hold the file's functions
        for file in {s.file for s in self.stubs.values()}:
            uses[file] = {name for rel in {file} | self.homes[file] if rel in self.sources
                          for name in NAME.findall(names.strip_code(self.sources[rel]))}
        return stubs_needed(kept, self.siblings, set(self.defined), self.stubs, uses)

    def claim(self, decls: list[str]) -> None:
        """Keep the type each declaration gives its name, so that a later copy cannot give it another."""
        claims = {names.declared_name(decl): claim(decl) for decl in decls}
        for name, text in claims.items():
            if self.claimed.get(name, text) != text:
                raise Skip("two types", f"{name} is `{self.claimed[name]}` and `{text}`")
        self.claimed |= claims

    def declarations(self, pairs: dict[str, Pair], template_file: str, uses: dict[str, list[str]]) -> list[str]:
        """The template's declaration of each name, renamed and with neutral types, for the copy's names that the tree
        does not declare. USES gives the pointer types that the prototypes keep. Where the tree declares the copy's
        name, its type must be the template's."""
        decls = []
        for old, pair in pairs.items():
            if pair.new == old:
                continue
            wanted, known = self.declaration(old, pair, template_file), self.own_declaration(pair)
            if wanted and known and not same_type(wanted, known):
                raise Skip("type differs", f"{pair.new} is `{known}`, the template's {old} `{wanted}`")
            if pair.new in self.declared:
                continue
            if not wanted:
                raise Skip("no prototype" if pair.kind == "function" else "no type", f"{old}, to declare {pair.new}")
            decls.append(neutral_function(wanted, uses) if pair.kind == "function"
                         else neutral_extern(wanted, pair.new, uses.get(pair.new, [])))
        return decls

    def declaration(self, old: str, pair: Pair, template_file: str) -> str | None:
        """The declaration of the copy's name PAIR.new: the one the template compiles with for OLD, renamed.
        That is its file's, else the tree's. None when the tree has none."""
        if pair.kind == "function":
            f = self.functions.get(pair.template)
            sig = self.local_functions[template_file].get(old) or (f.proto.rstrip(";") if f and f.proto else None)
            return names.without_parameter_names(renamed(sig, pair.new)) + ";" if sig else None
        held = self.namer.holder(pair.template)
        decl = self.local_globals[template_file].get(old) or (held[0].decl if held else None)
        return extern_of(decl, old, pair.new) if decl else None

    def own_declaration(self, pair: Pair) -> str | None:
        """The declaration the tree gives the copy's name PAIR.new, if it gives one."""
        if pair.kind == "function":
            f = self.functions.get(pair.copy)
            return f.proto if f and f.proto else self.signatures.get(pair.new)
        held = self.namer.holder(pair.copy)
        return extern_of(held[0].decl, held[0].name, pair.new) if held else None


def extern_of(decl: str, old: str, new: str) -> str:
    """The extern line that gives NEW the type DECL gives OLD. The definition gives an array's size."""
    decl = re.sub(r"\b(?:static|extern)\s+", "", decl)
    decl = re.sub(rf"\b{re.escape(old)}\b", new, decl, count=1)
    return "extern " + re.sub(r"\[[\w?]*\]", "[]", decl, count=1) + ";"


def same_type(a: str, b: str) -> bool:
    """Whether two declarations of one name give it one type, apart from spaces and struct keywords."""
    def text(decl: str) -> str:
        return re.sub(r"\s", "", re.sub(r"\b(?:struct|union|enum)\s+", "", claim(decl)))
    return text(a) == text(b)


def claim(decl: str) -> str:
    """A declaration or signature, in the form two copies must agree on: no linkage or parameter names."""
    decl = re.sub(r"^(?:static|extern)\s+", "", decl.rstrip(";"))
    return " ".join(names.without_parameter_names(decl).split()).replace("(void)", "()")


def as_defined(decl: str, definitions: dict[str, str]) -> str:
    """DECL, or when another copy defines its name, that copy's signature: decls wants the two to agree."""
    name = None if decl.startswith("#") else names.declared_name(decl)
    return names.without_parameter_names(definitions[name]) + ";" if name in definitions else decl


def is_match(entry: dict | None) -> bool:
    return entry is not None and not entry.get("stub") and entry["matching"] == 1.0


def declare(tables: Path | None) -> tuple[int, list[str]]:
    """Run `check.py decls` quietly: its exit code and its lines but the summary."""
    out = io.StringIO()
    with contextlib.redirect_stdout(out):
        code = declgen.write(None, tables)
    return code, [line for line in out.getvalue().splitlines() if not DECLS_SUMMARY.match(line)]


def build_errors() -> list[str] | None:
    """Build quietly: None, or the lines that say why it failed."""
    try:
        with contextlib.redirect_stdout(io.StringIO()):
            check.build()
    except SystemExit as error:
        lines = str(error.code).replace("\\", "/").splitlines()
        return [with_generated_line(line) for line in lines if ERROR_LINE.search(line)] or lines
    return None


def with_generated_line(line: str) -> str:
    """LINE, plus the line of a generated file that it points at: the name there leads to the copy that brought it."""
    for rel in names.GENERATED:
        m = re.search(re.escape(rel) + r"\((\d+)\)", line)
        if m:
            text = (ROOT / rel).read_text(encoding="utf-8").split("\n")
            return f"{line} [{text[int(m.group(1)) - 1].strip()}]"
    return line


def put_back(rel: str, original: bytes | None) -> None:
    path = ROOT / rel
    if original is None:
        path.unlink(missing_ok=True)
    else:
        path.write_bytes(original)


def write_file(rel: str, parts: list[Copy | Stub], original: bytes | None) -> None:
    """The file as it was, with PARTS in it: copies and STUBs."""
    put_back(rel, original)
    text, crlf = llm.read_source(ROOT / rel)
    for part in sorted(parts):
        text = llm.apply_function(text, part.address, part.decls, part.lines)
    llm.write_source(ROOT / rel, text, crlf)


def culprits(lines: list[str], kept: dict[str, list[Copy]]) -> dict[int, str]:
    """The copies in KEPT that the lines blame, each with the first line that blames it. A line that names a copy's
    file blames the copies there it points at. A line that names no such file blames the copies that use a name in it."""
    found = {}
    for line in lines:
        lower = line.lower()  # the compiler writes paths in lower case
        words = set(NAME.findall(line))
        blamed = []
        for rel, copies in kept.items():
            at = re.search(re.escape(rel.lower()) + r"(?:\((\d+)\))?(?!\w)", lower)
            if at or f"{Path(rel).name.lower()}.obj" in lower:
                blamed += pointed_at(rel, copies, int(at.group(1)) if at and at.group(1) else None, words)
        if not blamed:
            blamed = [copy for copies in kept.values() for copy in copies if copy.names & words]
        for copy in blamed:
            found.setdefault(copy.address, line)
    return found


def pointed_at(rel: str, copies: list[Copy], number: int | None, words: set[str]) -> list[Copy]:
    """The copy in REL whose definition holds line NUMBER, else those that use one of WORDS, else all of them."""
    if number:
        lines = (ROOT / rel).read_text(encoding="utf-8").split("\n")
        for copy in copies:
            span = llm.definition_span(lines, copy.address)
            if span and span[0] < number <= span[1] + 1:  # the compiler counts lines from 1
                return [copy]
    return [copy for copy in copies if copy.names & words] or copies


def rewrite(rel: str, parts: list[Copy | Stub], original: bytes | None) -> None:
    """The file with only PARTS in it: as it was when there are none."""
    if parts:
        write_file(rel, parts, original)
    else:
        put_back(rel, original)


def take_out(kept: dict[str, list[Copy]], gone: dict[int, str]) -> list[str]:
    """Take the copies at the addresses in GONE out of KEPT. Returns the files they were in."""
    files = [rel for rel, copies in kept.items() if any(copy.address in gone for copy in copies)]
    for rel in files:
        kept[rel] = [copy for copy in kept[rel] if copy.address not in gone]
        if not kept[rel]:
            del kept[rel]
    return files


def place(tree: Tree, kept: dict[str, list[Copy]], stubs: dict[str, list[Stub]], originals: dict[str, bytes | None],
          changed: Iterable[str]) -> dict[str, list[Stub]]:
    """Rewrite each file whose copies CHANGED, or whose STUBs the KEPT copies now need otherwise, with only its kept
    copies and needed STUBs in it. STUBS are the ones in place before. Returns those in place now, by file."""
    now = collections.defaultdict(list)
    for s in tree.needed_stubs([copy for copies in kept.values() for copy in copies]):
        now[s.file].append(s)
    for rel in set(changed) | {rel for rel in set(stubs) | set(now) if stubs.get(rel) != now.get(rel)}:
        rewrite(rel, kept.get(rel, []) + now.get(rel, []), originals[rel])
    return now


def stub_harm(tree: Tree, matched: set[int], scores: dict[int, dict], kept: dict[str, list[Copy]],
              stubs: dict[str, list[Stub]]) -> dict[int, str]:
    """The kept copies that need a STUB that the build leaves out, or a STUB in a file where a function that was at
    100% (MATCHED) no longer is: each with why."""
    harm = {}  # a STUB's name: why
    for s in (s for in_file in stubs.values() for s in in_file if s.address not in scores):
        harm.setdefault(s.name, f"its STUB for {s.name} in {s.file} is not in the build")
    for address in sorted(matched):
        rel = tree.defined[address][0] if address in tree.defined else None
        if rel in stubs and not is_match(scores.get(address)):
            for s in stubs[rel]:
                harm.setdefault(s.name, f"a STUB it needs in {rel} takes 0x{address:08x} below 100%")
    found = {}
    for copy in (copy for copies in kept.values() for copy in copies):
        for name in sorted(copy.shared & harm.keys()):
            found.setdefault(copy.address, harm[name])
    return found


def run(game: Path, addresses: list[int], every: bool, tables: Path | None) -> int:
    runner.require_our_game()
    matched = {a for a, entry in runner.score_target(runner.game_build(), game).items() if is_match(entry)}
    tree = Tree(game, tables)
    if every:
        templates = sorted(a for a in matched if tree.kind(a) == "FUNCTION")
    else:
        below = [a for a in addresses if a not in matched or tree.kind(a) != "FUNCTION"]
        if below:
            sys.exit("clone: a template must be a FUNCTION at 100%: " + ", ".join(f"0x{a:08x}" for a in below))
        templates = addresses
    found = tree.copies_of(templates)

    plans, skipped = {}, {}
    for address, candidates in sorted(found.items()):
        reasons = []
        for template in candidates:
            try:
                plans[address] = tree.plan(address, template)
                break
            except Skip as skip:
                reasons.append(skip)
        else:
            skipped[address] = reasons[0]
    definitions = {copy.name: copy.lines[1] for copy in plans.values()}
    for address, copy in plans.items():
        plans[address] = copy._replace(decls=[as_defined(decl, definitions) for decl in copy.decls])
    if not plans:
        report(tree, found, plans, skipped, {}, {})
        return 0

    code, baseline = declare(tables)
    if code:
        sys.exit("clone: decls fails before any copy is written:\n" + "\n".join(baseline))
    kept = collections.defaultdict(list)
    for copy in plans.values():
        kept[copy.file].append(copy)
    files = set(kept) | {s.file for s in tree.stubs.values()}
    originals = {rel: (ROOT / rel).read_bytes() if (ROOT / rel).exists() else None for rel in files}
    stubs = place(tree, kept, {}, originals, kept)

    failed = {}  # address: why
    while True:
        code, lines = declare(tables)
        errors, stage = lines[-1:], "decls"  # decls prints its fatal lines last, and the baseline has none
        if not code:  # the new lines are warnings
            errors, stage = build_errors() or [], "the build"
            if not errors:
                break
        hit = culprits(errors, kept)
        if not hit:
            for rel, original in originals.items():
                put_back(rel, original)
            declare(tables)
            sys.exit(f"clone: {stage} fails in a file clone did not write. Every file is back as it was.\n"
                     + "\n".join(errors[:20]))
        for address, line in hit.items():
            failed[address] = f"{stage} fails: {line.strip()}"
        stubs = place(tree, kept, stubs, originals, take_out(kept, hit))

    runner.require_our_game()
    scores = runner.score_target(runner.game_build(), game)
    for copies in kept.values():
        for copy in copies:
            entry = scores.get(copy.address)
            if entry is None:
                static = " (static: nothing in the build calls it)" if copy.lines[1].startswith("static ") else ""
                failed[copy.address] = f"not in the build{static}"
            elif not is_match(entry):
                failed[copy.address] = f"{entry['matching'] * 100:.1f}%"
    for address, why in stub_harm(tree, matched, scores, kept, stubs).items():
        failed.setdefault(address, why)
    stubs = place(tree, kept, stubs, originals, take_out(kept, failed))
    code, lines = declare(tables)
    errors = [line for line in lines if line not in baseline] if code else build_errors()
    if errors:
        sys.exit("clone: the tree with only the matched copies fails:\n" + "\n".join(errors[:20]))

    report(tree, found, plans, skipped, failed, stubs)
    return 0


def report(tree: Tree, found: dict[int, list[int]], plans: dict[int, Copy], skipped: dict[int, Skip],
           failed: dict[int, str], stubs: dict[str, list[Stub]]) -> None:
    for address in sorted(found):
        if address in skipped:
            what = f"skipped, {skipped[address]}"
        elif address in failed:
            what = failed[address]
        else:
            copy = plans[address]
            what = f"matched, from {tree.name(copy.template)}, in {copy.file}"
        print(f"0x{address:08x} {tree.name(address)}: {what}")
    written = sorted(s for in_file in stubs.values() for s in in_file)
    for s in written:
        print(f"0x{s.address:08x} {s.name}: static STUB in {s.file}, for the copies that share its name")
    below = sum(1 for why in failed.values() if not why.startswith(("decls fails", "the build fails")))
    print(f"clone: {len(plans) - len(failed)} matched, {below} below 100%, {len(failed) - below} stopped decls or "
          f"the build, {len(skipped)} skipped, of {len(found)} copies; {len(written)} STUBs for shared names")
    for kind, count in collections.Counter(skip.kind for skip in skipped.values()).most_common():
        print(f"  skipped, {kind}: {count}")
