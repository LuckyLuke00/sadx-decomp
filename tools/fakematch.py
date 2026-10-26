"""The lines of a function definition that are not the plain C a programmer writes, though they can build the same
code: a fake match.

The kinds:
  raw_address      a cast applied to an address in the exe, such as *(T *)0x5edd884
  index_game       an index then an offset, such as *(&p[1] - 1)
  neighbor_address a variable's address moved by a number, such as *(&p + 1) or (&p)[1]: it reaches what the build
                   stores next to the variable
  address_pun      a variable read through a pointer of another type, such as *(int *)&x or reinterpret_cast<int *>(&x)
  cast_call        a call through a cast function type, such as ((void (*)(int))f)(a) or (*(void (*)(int))f)(a)
  constant_test    if (0), if (1) or while (0); while (1) is a plain loop
  empty_statement  a lone ;, or an if, for or while (not the end of a do) with an empty body
  empty_block      { then } inside a function body
  unused_local     a local that is declared and never used again: it only fills the frame

llm.py --refuse-fakematch refuses a 100% try with one of them. Standard library only.
"""

import re
from collections.abc import Callable

import names

KEYWORDS = {"return", "goto", "else", "case", "default", "break", "continue", "do", "if", "while", "for", "switch",
            "sizeof", "delete", "new", "throw"}
QUALIFIER = r"(?:(?:const|unsigned|signed|struct|union|enum|volatile|register)\s+)*"
DECLARATOR = re.compile(r"\s*((?:\*\s*)*)([A-Za-z_]\w*)\s*((?:\[[^\]]*\]\s*)*)(?:=.*)?$", re.S)
DECLARATION = re.compile(rf"^\s*({QUALIFIER}[A-Za-z_]\w*)\s*(\*?[\s*]*[A-Za-z_].*);\s*$")
PATTERNS = {
    "raw_address": re.compile(r"\)\s*\(?\s*(0x[0-9a-fA-F]{6,8})\b"),
    "index_game": re.compile(r"(?<!&)&(?!&)\s*[\w.>-]+\s*\[[^\]]+\]\s*[-+]\s*(?:0x[0-9a-fA-F]+|\d+)"),
    # The & follows an operator, so it takes an address: a bitwise and follows a value. reinterpret_cast<T>(&x) is an
    # address_pun.
    "neighbor_address": re.compile(r"(?:^|(?<!>)\(|[=,?:]|\breturn)\s*&\s*[A-Za-z_]\w*\s*"
                                   r"(?:\)\s*\[|[-+]\s*(?:0x[0-9a-fA-F]+|\d+)\b)"),
    "address_pun": re.compile(r"\*\s*\(\s*[\w\s]+[\s*]*(?:\(\s*\*\s*\)\s*(?:\[[^\]]*\])?)?\s*\)\s*&\s*\w"
                              r"|reinterpret_cast\s*<(?:[^<>]|<[^<>]*>)*\*\s*>\s*\(\s*&\s*\w"),
    # In C, ((T)x)(a) is only ever a call through a cast, whether T is spelled out or a typedef. A field is left out:
    # the struct fixes its type, so a callback in a void * field needs the cast.
    "cast_call": re.compile(r"\(\s*\*?\s*\(\s*[\w\s*]+(?:\(\s*(?:__\w+\s*)?\*\s*\)\s*\([^()]*\))?\s*\)"
                            r"\s*&?\s*(?:\w+|\(\s*\w+\s*\))\s*\)\s*\("
                            r"|reinterpret_cast\s*<[^<>]*\(\s*(?:__\w+\s*)?\*\s*\)[^<>]*>\s*\(\s*&?\s*\w+\s*\)\s*\("),
    "constant_test": re.compile(r"\b(?:if\s*\(\s*[01]\s*\)|while\s*\(\s*0\s*\))"),
}
HEAD = re.compile(r"\s*(?:if|for|while)\s*\(")


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


def variable_types(func_lines: list[str], at: int) -> tuple[dict[str, str], list[tuple[str, int]]]:
    """name: type of each parameter and local of the function whose signature is FUNC_LINES[AT], and the locals as
    (name, index of the declaring line)."""
    sig = func_lines[at]
    params = sig[sig.index("(") + 1:sig.rindex(")")]
    types = {}
    for p in split_top(params):
        for name, kind in declared(p.strip() + ";"):
            types[name] = kind
    locals_ = []
    for i in range(at + 1, len(func_lines)):
        for name, kind in declared(func_lines[i]):
            types[name] = kind
            locals_.append((name, i))
    return types, locals_


def found(func: list[str], at: int, in_image: Callable[[int], bool]) -> list[tuple[str, str]]:
    """[(kind, line)] of the fake match lines in FUNC, a definition's lines from its annotation on, whose signature is
    FUNC[AT]. IN_IMAGE says whether an address is in the exe. The line of an unused_local is the local's name."""
    clean = names.blank_literals("\n".join(func)).split("\n")
    body = range(at + 1, len(clean))
    hits = []
    for i in body:
        for kind, pattern in PATTERNS.items():
            for m in pattern.finditer(clean[i]):
                if kind != "raw_address" or in_image(int(m.group(1), 16)):
                    hits.append((kind, func[i].strip()))
    for i in body:
        line, source = clean[i], func[i].strip()
        prior = next((clean[j].strip() for j in range(i - 1, at, -1) if clean[j].strip()), "")
        if line.strip() == ";" or (empty_head(line) and not (line.lstrip().startswith("while") and prior == "}")):
            hits.append(("empty_statement", source))
        if line.strip() == "{" and i > at + 1 and i + 1 < len(clean) and clean[i + 1].strip() == "}":
            hits.append(("empty_block", source))
    text = "\n".join(clean[at + 1:])
    for name, _ in variable_types(clean, at)[1]:
        if len(re.findall(rf"(?<!\.)(?<!->)\b{name}\b", text)) == 1:  # p->name and p.name are members, not uses
            hits.append(("unused_local", name))
    return hits
