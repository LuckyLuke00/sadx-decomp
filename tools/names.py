"""The names, signatures and types that the source tree knows, for declgen.py and dossier.py.

A name's address comes from an annotation in a source file or in a file that
declgen.py wrote before. A tables folder can add more: declgen.py says what it holds.
Standard library only.
"""

import csv
import functools
import re
from pathlib import Path
from typing import NamedTuple

import project

ROOT = project.ROOT
GENERATED = ("src/include/types.h", "src/include/functions.h", "src/include/globals.h",
             "src/unplaced/stubs.cpp", "src/unplaced/globals.cpp")
TYPES_H, FUNCTIONS_H, GLOBALS_H, STUBS_CPP, GLOBALS_CPP = GENERATED
SOURCE_SUFFIXES = (".c", ".cpp", ".h", ".inc")
FUNCTION_KINDS = ("FUNCTION", "STUB", "TEMPLATE", "SYNTHETIC")
SCALAR_SIZES = {"char": 1, "signed char": 1, "unsigned char": 1, "bool": 1, "short": 2, "unsigned short": 2,
                "int": 4, "unsigned int": 4, "long": 4, "unsigned long": 4, "float": 4, "double": 8,
                "__int64": 8, "unsigned __int64": 8, "long long": 8, "unsigned long long": 8}
TYPE_WORDS = {"void", "char", "short", "int", "long", "float", "double", "signed", "unsigned", "bool", "__int64",
              "struct", "union", "enum", "class", "const", "volatile"}


class Previous(NamedTuple):
    """What declgen.py wrote last time: the public table of the names it knew."""
    stubs: dict[int, str]  # address: signature
    globals: dict[int, str]  # address: definition, without its initializer
    externs: dict[str, str]  # name: the extern line, without its semicolon


@functools.cache
def annotation() -> re.Pattern:
    target = project.game_config().target
    return re.compile(rf"^\s*//\s*(FUNCTION|STUB|GLOBAL|LIBRARY|TEMPLATE|SYNTHETIC|STRING):\s*{target}\s+(0x[0-9a-fA-F]+)",
                      re.M)


def strip_code(text: str) -> str:
    """Text without comments, string and char literals: what is left are code tokens."""
    return re.sub(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', " ", text, flags=re.S)


def read_sources(root: Path) -> dict[str, str]:
    """The hand-written source files under root/src: path relative to root: text."""
    sources = {}
    for path in sorted((root / "src").rglob("*")):
        rel = path.relative_to(root).as_posix()
        if rel in GENERATED or path.suffix not in SOURCE_SUFFIXES:
            continue
        sources[rel] = path.read_text(encoding="utf-8")
    return sources


def signature_after(text: str, pos: int) -> str:
    """The declarator text from pos up to the body's `{` or a `;`, on one line."""
    end = len(text)
    for ch in "{;":
        i = text.find(ch, pos)
        if i != -1:
            end = min(end, i)
    return " ".join(text[pos:end].split())


def declared_name(sig: str) -> str | None:
    """The name a declaration or definition declares."""
    m = re.search(r"\(\s*\*\s*(\w+)", sig)
    if m and re.match(r"[^(]*\(\s*\*", sig):
        return m.group(1)
    head = sig.split("=")[0]
    head = re.sub(r"\[[^\]]*\]", "", head)
    if "(" in head:
        head = head[:head.index("(")]
    ids = re.findall(r"[A-Za-z_][\w:]*", head)
    return ids[-1] if ids else None


def without_parameter_name(param: str) -> str:
    """One parameter's type: `struct task *tp` gives `struct task *`, `void (*f)(int)` gives `void (*)(int)`."""
    param = " ".join(param.split())
    if re.search(r"\(\s*\*\s*\w+\s*\)", param):
        return re.sub(r"\(\s*\*\s*\w+\s*\)", "(*)", param, count=1)
    m = re.fullmatch(r"(.*?[\s*&])\s*([A-Za-z_]\w*)\s*((?:\[[^\]]*\])*)", param)
    if not m or m.group(2) in TYPE_WORDS:
        return param
    type_words = [w for w in re.findall(r"\w+", m.group(1)) if w not in ("const", "volatile")]
    if not type_words or type_words[-1] in ("struct", "union", "enum", "class"):
        return param  # `const Angle` or `struct task`: the last word is the type, not a name
    return (m.group(1).rstrip() + m.group(3)).strip()


def without_parameter_names(sig: str) -> str:
    """SIG with its parameters' names dropped: two declarations of one function then compare equal."""
    span = parameter_span(sig)
    if span is None:
        return sig
    start, end, params = span
    types = [without_parameter_name(p) for p in params]
    return " ".join((sig[:start] + ", ".join(types) + sig[end:]).split())


def declaration_key(decl: str) -> str:
    """DECL as C++ reads it, to tell whether two declarations of one name are the same: without parameter names, a
    leading `extern`, and `struct`, `union`, `enum` or `class` before a type name, with `(void)` as `()`. Not for
    writing: a C file needs the `struct`."""
    decl = without_parameter_names(decl)
    decl = re.sub(r"^\s*extern\b", "", decl)
    decl = re.sub(r"\b(?:struct|union|enum|class)\s+(?=\w)", "", decl)
    decl = re.sub(r"\(\s*void\s*\)", "()", decl)
    return re.sub(r"\s", "", decl)


def parameter_span(sig: str) -> tuple[int, int, list[str]] | None:
    """(start, end, parameters) of SIG's parameter list, where sig[start:end] is the text between its parentheses.
    None when SIG declares no function."""
    name = declared_name(sig)
    m = re.search(re.escape(name) + r"\s*\(", sig) if name else None
    if not m:
        return None
    depth, parts, cur = 0, [], ""
    for i in range(m.end(), len(sig)):
        ch = sig[i]
        depth += (ch in "([") - (ch in ")]")
        if depth < 0:
            parts.append(cur)
            return m.end(), i, [p.strip() for p in parts if p.strip()]
        if ch == "," and depth == 0:
            parts.append(cur)
            cur = ""
        else:
            cur += ch
    return None


def parse_annotations(text: str) -> list[tuple[str, int, str]]:
    """(kind, address, signature) of each annotation: the signature is the first code line after it."""
    found = []
    for m in annotation().finditer(text):
        kind, address = m.group(1), int(m.group(2), 16)
        nl = text.find("\n", m.end())
        rest = text[nl + 1:] if nl != -1 else ""
        # skip further annotation and blank lines
        while True:
            line_end = rest.find("\n")
            line = rest if line_end == -1 else rest[:line_end]
            if line.strip().startswith("//") or not line.strip():
                if line_end == -1:
                    rest = ""
                    break
                rest = rest[line_end + 1:]
                continue
            break
        sig = signature_after(rest, 0)
        found.append((kind, address, sig))
    return found


def local_declarations(text: str) -> tuple[list[tuple[str, str]], list[tuple[str, str]]]:
    """File-scope declarations: `ret name(args);` and `extern type name...;`."""
    funcs, vars_ = [], []
    # The lookahead also skips a label such as `end:`, which a call on the next line would turn into a declaration.
    for m in re.finditer(r"^(?!static\b|typedef\b|return\b|#|[A-Za-z_]\w*\s*:(?!:))"
                         r"([A-Za-z_][^;{}()=#]*?\b([A-Za-z_]\w*)\s*\([^;{}]*\))\s*;",
                         strip_code(text), re.M):
        funcs.append((m.group(2), without_parameter_names(" ".join(m.group(1).split()))))
    for m in re.finditer(r"^extern\s+([^;{}]+);", strip_code(text), re.M):
        decl = " ".join(m.group(1).split())
        if "(" in decl and not re.search(r"\(\s*\*", decl):
            continue
        vars_.append((declared_name(decl), decl))
    return funcs, vars_


def previous(root: Path) -> Previous:
    """The stubs, global definitions and externs in the files declgen.py wrote last time."""
    def text(rel: str) -> str:
        path = root / rel
        return path.read_text(encoding="utf-8") if path.exists() else ""

    stubs = {address: sig for kind, address, sig in parse_annotations(text(STUBS_CPP)) if kind == "STUB"}
    definitions = {}
    for kind, address, sig in parse_annotations(text(GLOBALS_CPP)):
        if kind == "GLOBAL":
            definitions[address] = re.sub(r"\s*=\s*(?:0|\{\})?$", "", sig)
    externs = {}
    for line in text(GLOBALS_H).splitlines():
        if line.startswith("extern ") and line.endswith(";"):
            externs[declared_name(line[len("extern "):-1])] = line[:-1]
    return Previous(stubs, definitions, externs)


def table_rows(path: Path) -> list[dict]:
    with open(path, encoding="utf-8", newline="") as f:
        return list(csv.DictReader(f, delimiter="\t"))


class Types:
    """Blocks of a types header: each struct, union or enum with its static_asserts."""

    def __init__(self, path: Path):
        text = path.read_text(encoding="utf-8") if path.exists() else ""  # a new game has none yet
        self.order, self.blocks, self.kind, self.deps, self.size = [], {}, {}, {}, {}
        self.forward = set()
        for block in re.split(r"\n\s*\n", text):
            block = block.strip()
            m = re.search(r"^(struct|union|enum)\s+(\w+)\s*(?::\s*\w+\s*)?\{", block, re.M)
            if not m:
                for kind, name in re.findall(r"^(struct|union)\s+(\w+);", block, re.M):
                    self.forward.add(name)
                    self.kind.setdefault(name, kind)
                continue
            kind, name = m.group(1), m.group(2)
            self.order.append(name)
            self.blocks[name] = block
            self.kind[name] = kind
            body = block.split("};", 1)[0]
            self.deps[name] = {n for k, n, ptr in re.findall(r"\b(struct|union|enum)\s+(\w+)\s*(\**)", body[m.end():])
                               if not ptr}
            s = re.search(r"sizeof\(\w+\) == (0x[0-9a-f]+)", block)
            self.size[name] = int(s.group(1), 16) if s else None


def element_size(base: str, types: Types) -> int | None:
    t = re.sub(r"\bconst\b|\bvolatile\b", "", base).strip()
    if t.endswith("*") or "(*" in t:
        return 4
    if t in SCALAR_SIZES:
        return SCALAR_SIZES[t]
    m = re.fullmatch(r"(?:struct|union)\s+(\w+)", t)
    if m:
        return types.size.get(m.group(1))
    if t.startswith("enum "):
        return 4
    return None
