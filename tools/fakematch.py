"""The lines of a function definition that are not the plain C a programmer writes, though they can build the same
code: a fake match.

The kinds:
  raw_address      a cast applied to an address in the exe, such as *(T *)0x5edd884 or *(T *)(i * 4 + 0x5edd884), an
                   address in the exe plus a scaled index, such as 0x5baf6a0 + i * 0xc, or a bare number that is the
                   address of a function or a global the tree knows. A number added to a pointer is an offset.
  index_game       an index then an offset, such as *(&p[1] - 1)
  neighbor_address a variable's address moved by a number, such as *(&p + 1) or (&p)[1], or a tree global's address
                   cast and moved out of its bytes, such as (char *)&p + i * 4 with p an int: it reaches what the build
                   stores next to the variable. A move inside the bytes, such as (char *)&p + 2, reads a part of p.
  address_pun      a variable read through a pointer of another type, such as *(int *)&x, *(int *)(void *)&x or
                   reinterpret_cast<int *>(&x)
  cast_call        a call through a cast function type, such as ((void (*)(int))f)(a) or (*(void (*)(int))f)(a)
  constant_test    if (0), if (1) or while (0); while (1) is a plain loop
  empty_statement  a lone ;, or an if, for or while (not the end of a do) with an empty body
  empty_block      { then } inside a function body
  lone_conditional a ?: that is a whole statement, such as p ? f(p) : 0;: plain C writes an if, and the form copies
                   the code a delete compiles to
  unused_local     a local that is declared and never used again: it only fills the frame
  self_assignment  a variable set to itself, such as x = x;: it does nothing
  unused_label     a label that no goto names
  address_number   the address of a DAT_ that is not a multiple of 4 cast to an integer, such as (int)&DAT_04000002:
                   such a number is nearly always a flag or a count, not the address of a global
  constant_global  a float or double DAT_ declared at an address of read-only data (constant_globals): the compiler
                   puts the source's literals there, so the source wrote a literal

In a function that builds with /Od (Tree.is_debug), unused_local and self_assignment are plain C: every local gets a
stack slot there, and x = x; loads and stores. A float literal in arithmetic or a comparison compiles to a qword
operand there, so a float DAT_ that the code uses so is a float object (constant_globals).

llm.py --refuse-fakematch refuses a 100% try with one of them. A function at 100% with one counts as matched only
through a trick: checker gives tools/tricks.py the kinds. Standard library only.
"""

import math
import re
from collections.abc import Callable
from pathlib import Path
from typing import NamedTuple

import names
import pe
import progress

KEYWORDS = {"return", "goto", "else", "case", "default", "break", "continue", "do", "if", "while", "for", "switch",
            "sizeof", "delete", "new", "throw"}
QUALIFIER = r"(?:(?:const|unsigned|signed|struct|union|enum|volatile|register)\s+)*"
DECLARATOR = re.compile(r"\s*((?:\*\s*)*)([A-Za-z_]\w*)\s*((?:\[[^\]]*\]\s*)*)(?:=.*)?$", re.S)
DECLARATION = re.compile(rf"^\s*({QUALIFIER}[A-Za-z_]\w*)\s*(\*?[\s*]*[A-Za-z_].*);\s*$")
PATTERNS = {
    # A cast right before the address, a pointer cast on a sum in parentheses that holds it, a pointer cast on a value
    # that the address is added to, or the address plus a scaled index, either way round.
    "raw_address": re.compile(r"\)\s*\(?\s*(0x[0-9a-fA-F]{6,8})\b"
                              r"|\*\s*\)\s*\((?:[^()]|\([^()]*\))*?\b(0x[0-9a-fA-F]{6,8})\b"
                              r"|\*\s*\)\s*(?:\((?:[^()]|\([^()]*\))*\)|[A-Za-z_]\w*(?:\[[^\]]*\]|\.\w+|->\w+)*)"
                              r"\s*[-+]\s*(0x[0-9a-fA-F]{6,8})\b"
                              r"|\b(0x[0-9a-fA-F]{6,8})\s*\+\s*(?:\(\s*\w+\s*\)\s*)?[A-Za-z_][\w.>\[\]-]*\s*\*\s*"
                              r"(?:0x[0-9a-fA-F]+|\d+)\b"
                              r"|\b[A-Za-z_][\w.>\[\]-]*\s*\*\s*(?:0x[0-9a-fA-F]+|\d+)\s*\+\s*(0x[0-9a-fA-F]{6,8})\b"),
    "index_game": re.compile(r"(?<!&)&(?!&)\s*[\w.>-]+\s*\[[^\]]+\]\s*[-+]\s*(?:0x[0-9a-fA-F]+|\d+)"),
    # The & follows an operator, so it takes an address: a bitwise and follows a value. reinterpret_cast<T>(&x) is an
    # address_pun. A cast before the &, as in (char *)&x + i, is CAST_ADDRESS.
    "neighbor_address": re.compile(r"(?:^|(?<!>)\(|[=,?:]|\breturn)\s*&\s*[A-Za-z_]\w*\s*"
                                   r"(?:\)\s*\[|[-+]\s*(?:0x[0-9a-fA-F]+|\d+)\b)"),
    # A pointer type, maybe to an array or a function, then maybe casts to void * or char *, then maybe a (, then &.
    "address_pun": re.compile(r"\*\s*\(\s*[\w\s]+[\s*]*(?:\(\s*\*+\s*\)\s*(?:\[[^\]]*\]|\([^()]*\))?)?\s*\)"
                              r"\s*(?:\(\s*(?:void|(?:unsigned\s+)?char)\s*\*\s*\)\s*)*\(?\s*&\s*\w"
                              r"|reinterpret_cast\s*<(?:[^<>]|<[^<>]*>)*\*\s*>\s*\(\s*&\s*\w"),
    # In C, ((T)x)(a) is only ever a call through a cast, whether T is spelled out or a typedef. A field is left out:
    # the struct fixes its type, so a callback in a void * field needs the cast.
    "cast_call": re.compile(r"\(\s*\*?\s*\(\s*[\w\s*]+(?:\(\s*(?:__\w+\s*)?\*\s*\)\s*\([^()]*\))?\s*\)"
                            r"\s*&?\s*(?:\w+|\(\s*\w+\s*\))\s*\)\s*\("
                            r"|reinterpret_cast\s*<[^<>]*\(\s*(?:__\w+\s*)?\*\s*\)[^<>]*>\s*\(\s*&?\s*\w+\s*\)\s*\("),
    "constant_test": re.compile(r"\b(?:if\s*\(\s*[01]\s*\)|while\s*\(\s*0\s*\))"),
    "self_assignment": re.compile(r"^\s*((?:\*\s*)*[A-Za-z_](?:\w|\.|->|\[[^\]]*\])*)\s*=\s*\1\s*;\s*$"),
    "address_number": re.compile(r"\(\s*(?:unsigned\s+)?(?:int|long)\s*\)\s*&\s*DAT_[0-9a-fA-F]{7}[^\W048cC]\b"),
}
# A cast on the address of a variable or of a member of one, then + or -, as in (char *)&x + i or (char *)&x.y.z + i:
# group 1 is the cast's type words, 2 its stars, 3 the variable, 4 the members and 5 the sign. An element, as in
# (char *)&x[1] + i, is left out.
CAST_ADDRESS = re.compile(r"\(\s*((?:[A-Za-z_]\w*\s+)*[A-Za-z_]\w*)\s*((?:\*\s*)*)\)\s*&\s*([A-Za-z_]\w*)"
                          r"((?:\s*\.\s*[A-Za-z_]\w*)*)\s*([-+])(?![-+=>])")
INTEGER_CASTS = (set(names.SCALAR_SIZES) - {"float", "double", "bool"}) | {"unsigned", "signed"}
OFFSET_END = set(")]},;?:=<>&|^!")  # what ends an offset: a closing bracket, or an operator that binds less than +
ADDED_TO = re.compile(r"(?<![\w.])([A-Za-z_]\w*)\s*\)?\s*[-+]\s*$")  # a name, maybe in parentheses, then + or -
NUMBER = re.compile(r"(?<![\w.])(0[xX][0-9a-fA-F]+|[1-9]\d*|0)[uUlL]*(?![\w.])")  # an integer, not part of a float
LABEL = re.compile(r"^\s*([A-Za-z_]\w*)\s*:\s*;?\s*$")
HEAD = re.compile(r"\s*(?:if|for|while)\s*\(")
DEBUG_PLAIN = {"unused_local", "self_assignment"}  # the kinds that are plain C at /Od
DAT_NAME = re.compile(r"DAT_([0-9a-f]{8})")  # a global's placeholder name, which holds its address
FLOAT_GLOBAL = re.compile(r"^\s*(?:extern\s+)?(?:const\s+)?(float|double)\s+(?:const\s+)?DAT_([0-9a-fA-F]{8})\s*;\s*$")
ARITHMETIC_BEFORE = re.compile(r"(?:[-+*/%<>]|[-+*/%<>=!]=)$")  # an operator or a compound assignment
ARITHMETIC_AFTER = re.compile(r"[-+*/%<>]|[=!]=")
CAST_BEFORE = re.compile(r"\(\s*[A-Za-z_][\w\s]*\**\s*\)$")  # such as (float) or (struct task *)
CALL_PAREN = re.compile(r"[\w)\]]\s*\($")  # the ( of a call, an if or a while: no grouping


class Tree(NamedTuple):
    """What found knows of the tree: whether a number is the address of a function or a global it knows
    (address_test), the definition of each global by name without its initializer, the types header that sizes
    them, and whether the function at an address builds with /Od (debug_test)."""
    is_address: Callable[[int], bool]
    definitions: dict[str, str]
    types: names.Types
    is_debug: Callable[[int], bool]

    def is_debug_function(self, func: list[str]) -> bool:
        """Whether FUNC, a definition's lines from its annotation on, builds with /Od."""
        head = names.annotation().match(func[0])
        return bool(head) and self.is_debug(int(head[2], 16))

    def with_addresses(self, addresses: set[int]) -> "Tree":
        """This tree, with ADDRESSES as addresses it knows too."""
        return self._replace(is_address=lambda address: address in addresses or self.is_address(address))

    def with_decls(self, decls: list[str]) -> "Tree":
        """This tree, with the globals that DECLS, a try's declaration lines, declare as extern: their definitions,
        and the bytes of each DAT_ among them as addresses it knows, since its name holds its address."""
        declared = dict(names.local_declarations("\n".join(decls))[1])
        placed = [(int(m[1], 16), names.global_size(definition, name, self.types))
                  for name, definition in declared.items() if (m := DAT_NAME.fullmatch(name))]
        known = address_test(set(), placed)
        return self._replace(is_address=lambda address: known(address) or self.is_address(address),
                             definitions={**self.definitions, **declared})

    def size(self, name: str, members: list[str] = ()) -> int:
        """The bytes of the global NAME, or of its member at the path MEMBERS, as ["pos", "x"] for NAME.pos.x. 0 when
        the tree has no such global or does not know the size."""
        definition = self.definitions.get(name)
        for member in members:
            if not definition:
                return 0
            base = names.element_layout(definition, name, self.types)[0]
            definition, name = self.types.member(base, member), member
        return names.global_size(definition, name, self.types) if definition else 0

    def is_pointer(self, name: str) -> bool:
        """Whether the global NAME is a pointer or an array: a number added to it is an offset."""
        definition = self.definitions.get(name)
        if not definition:
            return False
        base, _, counts = names.element_layout(definition, name, self.types)
        return base.endswith("*") or bool(counts)


def empty_head(line: str) -> bool:
    """Whether LINE is an if, for or while whose body is the ; right after its closing parenthesis."""
    m = HEAD.match(line)
    if not m:
        return False
    depth = 1
    for i in range(m.end(), len(line)):
        depth += (line[i] == "(") - (line[i] == ")")
        if depth == 0:
            return line[i + 1:].strip() == ";"
    return False


def lone_conditional(line: str) -> bool:
    """Whether LINE, a blanked line, is a statement that is a ?: as a whole: a ? outside brackets with no assignment
    before it, in a line that does not return it."""
    statement = line.strip()
    if not statement.endswith(";") or re.match(r"(?:return|case)\b", statement):
        return False
    depth, outside = 0, []
    for c in statement:
        depth += (c in "([{") - (c in ")]}")
        outside.append(" " if depth else c)
    # <<= and >>= assign; ==, !=, <= and >= compare
    top = re.sub(r"[=!<>]=", "  ", "".join(outside).replace("<<=", "=").replace(">>=", "="))
    return "?" in top and "=" not in top[:top.index("?")] and bool(top[:top.index("?")].strip())


def split_top(text: str, sep: str = ",") -> list[str]:
    """TEXT split at each SEP outside brackets and parentheses."""
    parts, depth, start = [], 0, 0
    for i, c in enumerate(text):
        depth += c in "([{"
        depth -= c in ")]}"
        if c == sep and depth == 0:
            parts.append(text[start:i])
            start = i + 1
    return parts + [text[start:]]


def declared(line: str) -> list[tuple[str, str]]:
    """[(name, type)] of a declaration LINE such as `struct task *tp, *other;`, else []. The type keeps the stars of
    each declarator and drops arrays: `struct task *`."""
    m = DECLARATION.match(line)
    if not m or m.group(1).split()[0] in KEYWORDS:
        return []
    base = " ".join(m.group(1).split())
    found = []
    for part in split_top(m.group(2)):
        d = DECLARATOR.match(part)
        if not d:
            return []
        stars = d.group(1).replace(" ", "")
        found.append((d.group(2), f"{base} {stars}".strip() if stars else base))
    return found


def float_global(line: str) -> tuple[int, int] | None:
    """(address, width) of the float or double DAT_ that the declaration LINE declares, else None."""
    m = FLOAT_GLOBAL.match(line)
    return (int(m.group(2), 16), 4 if m.group(1) == "float" else 8) if m else None


def in_arithmetic(text: str, name: str) -> bool:
    """Whether TEXT, code, uses NAME as an operand of arithmetic or a comparison, such as x * NAME, (float)NAME < y or
    x += NAME. Casts and parentheses around NAME do not hide it, and the parentheses of a call end it."""
    text = names.blank_literals(text)
    for m in re.finditer(rf"\b{re.escape(name)}\b", text):
        before, after = text[:m.start()].rstrip(), text[m.end():].lstrip()
        while True:
            if cast := CAST_BEFORE.search(before):
                before = before[:cast.start()].rstrip()
            elif before.endswith("(") and after.startswith(")") and not CALL_PAREN.search(before):
                before, after = before[:-1].rstrip(), after[1:].lstrip()
            else:
                break
        if ARITHMETIC_BEFORE.search(before) or ARITHMETIC_AFTER.match(after):
            return True
    return False


def constant_globals(decls: list[str], literal_at: Callable[[int, int], str | None], text: str = "",
                     debug: bool = False) -> list[tuple[str, str]]:
    """[("constant_global", line)] of the declarations in DECLS of a float or double DAT_ that LITERAL_AT, given
    its address and width, finds a literal at: it gives None for an address that is not read-only data. In a /Od
    function (DEBUG), a float that TEXT, its code, uses in arithmetic or a comparison does not count: a float literal
    there compiles to a qword operand, so the exe's dword operand is a float object."""
    return [("constant_global", line.strip()) for line in decls if (at := float_global(line)) and literal_at(*at)
            and not (debug and at[1] == 4 and in_arithmetic(text, re.search(r"DAT_\w+", line)[0]))]


def statements(lines: list[str], start: int) -> list[tuple[str, int]]:
    """(text, index of its first line) of each statement in LINES from START on, split at each `;` outside brackets.
    A statement runs on over lines up to one that ends in `;`, `{`, `}` or `:`. A blank line or a preprocessor line
    ends the one before it and holds none."""
    found, pending, first = [], [], start
    for i, line in enumerate([*lines[start:], ""], start):  # the blank line at the end ends the last statement
        line = line.strip()
        if line and not line.startswith("#"):
            if not pending:
                first = i
            pending.append(line)
        if pending and (not line or line.startswith("#") or line.endswith((";", "{", "}", ":"))):
            found += [(text, first) for text in split_top(" ".join(pending), ";")]
            pending = []
    return found


def variable_types(func_lines: list[str], at: int) -> tuple[dict[str, str], list[tuple[str, int]]]:
    """name: type of each parameter and local of the function whose signature is FUNC_LINES[AT], and the locals as
    (name, index of the line its statement starts on). A line can declare several, as in `int x; int y;`, and a
    declaration can run over lines."""
    sig = func_lines[at]
    params = sig[sig.index("(") + 1:sig.rindex(")")]
    types = {}
    for p in split_top(params):
        for name, kind in declared(p.strip() + ";"):
            types[name] = kind
    locals_ = []
    for statement, i in statements(func_lines, at + 1):
        for name, kind in declared(statement + ";"):
            types[name] = kind
            locals_.append((name, i))
    return types, locals_


def number_value(text: str) -> int | None:
    """The value of TEXT when it is one integer literal, as in 0x1c or 4u, else None."""
    m = NUMBER.fullmatch(text.strip())
    return int(m[1], 0) if m else None


def offset_text(line: str, start: int) -> str:
    """The offset that LINE adds from START on: its text up to a closing bracket or an operator of OFFSET_END outside
    brackets, or to the line's end. The > of a -> belongs to a member."""
    depth = 0
    for i in range(start, len(line)):
        if line[i] in "([{":
            depth += 1
        elif depth == 0 and line[i] in OFFSET_END and line[i - 1:i + 1] != "->":
            return line[start:i]
        elif line[i] in ")]}":
            depth -= 1
    return line[start:]


def term_bytes(term: str, unit: int) -> int:
    """The bytes that TERM, a term of an offset in steps of UNIT bytes, moves for one step of its index: UNIT times
    its value for a number, times the product of its numbers for a product such as i * 4, else UNIT."""
    numbers = [value for factor in split_top(term, "*") if (value := number_value(factor)) is not None]
    return math.prod(numbers) * unit if numbers else unit


def cast_unit(words: str, stars: str, types: names.Types) -> int | None:
    """The bytes that one step moves after a cast to WORDS STARS, such as `unsigned char` and `*`: the size of what a
    pointer points to, 1 for an integer, or None when TYPES does not know it."""
    base, stars = " ".join(words.split()), stars.replace(" ", "")
    if stars:
        return names.element_size(f"{base} {stars[1:]}".rstrip(), types)
    return 1 if base in INTEGER_CASTS else None


def past_bytes(m: re.Match, line: str, tree: Tree) -> bool:
    """Whether the CAST_ADDRESS match M on LINE moves the address of a tree global, or of a member of one, out of its
    bytes: back, or on by its size or more, at once or for one step of an index. A global, a member or a cast step of
    unknown size is not judged."""
    size, unit = tree.size(m[3], re.findall(r"\w+", m[4])), cast_unit(m[1], m[2], tree.types)
    if not size or unit is None:
        return False
    return m[5] == "-" or any(term_bytes(term, unit) >= size for term in split_top(offset_text(line, m.end()), "+"))


def added_to_pointer(before: str, variables: dict[str, str], tree: Tree) -> bool:
    """Whether the number after BEFORE, the text of a line up to it, is added to a pointer or an array: then it is an
    offset, not an address. A name is a parameter or local of VARIABLES (variable_types), else a tree global."""
    m = ADDED_TO.search(before)
    if not m:
        return False
    return variables[m[1]].endswith("*") if m[1] in variables else tree.is_pointer(m[1])


def found(func: list[str], at: int, in_image: Callable[[int], bool], tree: Tree) -> list[tuple[str, str]]:
    """[(kind, line)] of the fake match lines in FUNC, a definition's lines from its annotation to the line that closes
    its body (names.definition_end), whose signature is FUNC[AT], each once. A kind of DEBUG_PLAIN does not count in a
    /Od function. IN_IMAGE says whether an address is in the exe, TREE what the tree knows (read_tree). The line of an
    unused_local is the local's name."""
    plain = DEBUG_PLAIN if tree.is_debug_function(func) else set()
    clean = names.blank_literals("\n".join(func)).split("\n")
    body = range(at + 1, len(clean))
    text = "\n".join(clean[at + 1:])
    variables, locals_ = variable_types(clean, at)
    hits = []
    for i in body:
        line, source = clean[i], func[i].strip()
        for kind, pattern in PATTERNS.items():
            for m in pattern.finditer(line):
                if kind != "raw_address" or (in_image(int(m[m.lastindex], 16))
                                             and not added_to_pointer(line[:m.start(m.lastindex)], variables, tree)):
                    hits.append((kind, source))
        if any(m[3] not in variables and past_bytes(m, line, tree) for m in CAST_ADDRESS.finditer(line)):
            hits.append(("neighbor_address", source))
        if any(tree.is_address(int(m[1], 0)) for m in NUMBER.finditer(line)):
            hits.append(("raw_address", source))
    for i in body:
        line, source = clean[i], func[i].strip()
        prior = next((clean[j].strip() for j in range(i - 1, at, -1) if clean[j].strip()), "")
        if line.strip() == ";" or (empty_head(line) and not (line.lstrip().startswith("while") and prior == "}")):
            hits.append(("empty_statement", source))
        if line.strip() == "{" and i > at + 1 and i + 1 < len(clean) and clean[i + 1].strip() == "}":
            hits.append(("empty_block", source))
        if lone_conditional(line):
            hits.append(("lone_conditional", source))
        label = LABEL.match(line)
        if label and label[1] != "default" and not re.search(rf"\bgoto\s+{label[1]}\b", text):
            hits.append(("unused_label", source))
    for name, _ in locals_:
        if len(re.findall(rf"(?<!\.)(?<!->)\b{name}\b", text)) == 1:  # p->name and p.name are members, not uses
            hits.append(("unused_local", name))
    return [hit for hit in dict.fromkeys(hits) if hit[0] not in plain]


def address_test(function_starts: set[int], globals_: list[tuple[int, int]]) -> Callable[[int], bool]:
    """Whether a number is an address the tree knows: one of FUNCTION_STARTS, or the start, a byte or the end of one of
    GLOBALS_, (address, size) pairs that do not overlap. A global of size 0, whose size is unknown, counts at its start
    alone."""
    ranges = sorted([(address, address + 1) for address in function_starts]
                    + [(address, address + size + 1) for address, size in globals_])
    return lambda address: pe.in_ranges(ranges, address)


def debug_test(groups: list[dict]) -> Callable[[int], bool]:
    """Whether the function at an address builds with /Od: the flags of its codegen group in GROUPS have it."""
    def is_debug(address: int) -> bool:
        group = progress.codegen_group(groups, address)
        return group is not None and "/Od" in group["flags"].split()

    return is_debug


def direct_targets(rows) -> set[int]:
    """The addresses that the exe reads or writes as such, from tools/accesses.py's ROWS: a bare number that is one is
    the address of a global, though the tree may not declare it yet. A taken address, as in push 0x2000000, is left
    out: the same number can be a flag."""
    return {row.target for row in rows if row.form == "direct" and row.size}


def read_tree(root: Path) -> Tree:
    """The Tree at ROOT: the functions of data/functions.csv, the globals of its sources and of the files declgen
    wrote, sized with its types header, and the /Od functions of data/codegen-groups.csv."""
    types = names.Types(root / names.TYPES_H)
    named = [(address, name, definition)
             for address, definition in names.global_definitions(names.read_sources(root), names.previous(root))
             if (name := names.declared_name(definition))]
    is_address = address_test({function["address"] for function in progress.load_functions()},
                              [(address, names.global_size(definition, name, types))
                               for address, name, definition in named])
    return Tree(is_address, {name: definition for _, name, definition in named}, types,
                debug_test(progress.load_codegen_groups()))


def checker(root: Path, game: Path) -> Callable[[list[str]], list[str]]:
    """The fake-match kinds of a definition, given its lines from its annotation on, in the tree at ROOT against the
    exe GAME: those of found, with the addresses the exe reads or writes as such (direct_targets), and those of
    constant_globals for the float or double DAT_ at read-only data that its body names."""
    import accesses  # loads capstone, so only here

    image = pe.Image(game)
    tree = read_tree(root).with_addresses(direct_targets(accesses.load(image)))
    floats = {name: definition + ";" for name, definition in tree.definitions.items()
              if float_global(definition + ";")}

    def kinds(func: list[str]) -> list[str]:
        at = names.signature_index(func)
        text = "\n".join(func)
        words = set(re.findall(r"\w+", text))
        hits = found(func, at, image.contains, tree)
        named = [line for name, line in floats.items() if name in words]
        return [kind for kind, _ in hits] + [kind for kind, _ in constant_globals(
            named, lambda address, width: image.is_read_only_data(address), text, tree.is_debug_function(func))]

    return kinds
