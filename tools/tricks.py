"""The functions that match only through a trick, not plain C.

A trick is one of these:
- inline assembly, `__emit`, `__declspec(naked)`, `#pragma` or `__pragma` in the function: forbidden(), the words
  the local model's harness refuses;
- `volatile`, `__restrict`, `__declspec(safebuffers)` or `__declspec(noinline)` in the function;
- a global declared `volatile` at file level in any source, used in the function;
- a place after a file-level pragma that changes the code, such as `#pragma auto_inline(off)`, and before the pragma
  that resets it;
- a fake-match line (tools/fakematch.py), when the scan gets FAKES.

Such a function keeps the score reccmp gives it, but it does not count as matched until it is plain C.

  python tools/tricks.py      list each function with a trick and why

Standard library only.
"""

import re
import sys
from collections.abc import Callable
from pathlib import Path

import fakematch
import names
import project

FORBIDDEN = re.compile(r"\b(?:__asm|_asm|asm|__emit|__pragma)\b|__declspec\s*\(\s*naked\s*\)|#\s*pragma\b")  # not C
KEYWORDS = re.compile(r"\bvolatile\b|\b__restrict\b|__declspec\s*\(\s*(?:safebuffers|noinline)\s*\)")
VOLATILE = re.compile(r"\bvolatile\b")
PRAGMA = re.compile(r"^\s*(?:#\s*pragma\s+|__pragma\s*\(\s*)(\w+)\s*(?:\((.*?)\))?")
HARMLESS_PRAGMAS = {"once", "warning", "push_macro", "pop_macro", "pack"}  # they change no function's code
RESETS = {"", "on", '"",on'}  # the arguments that put a pragma back to the command line's setting


def words(pattern: re.Pattern, blanked: str) -> list[str]:
    """The matches of PATTERN in BLANKED, text from names.blank_literals, without their blanks."""
    return [re.sub(r"\s+", "", m[0]) for m in pattern.finditer(blanked)]


def forbidden(lines: list[str]) -> list[str]:
    """The words in LINES that put machine code or compiler settings where C should be: inline assembly, `__emit`,
    `__declspec(naked)`, `#pragma` and `__pragma`, without their blanks. A word in a string, a character or a
    comment does not count."""
    return words(FORBIDDEN, names.blank_literals("\n".join(lines)))


def declarator_start(lines: list[str], blank: list[str], annotation: int) -> int:
    """The first line of the definition whose annotation is at line ANNOTATION. A line such as
    `__declspec(safebuffers)` right above the annotation is part of the declarator: the compiler reads past the
    comment. A blank line, a preprocessor line or a line that ends a statement or block ends the walk up."""
    start = annotation
    while start > 0:
        above = blank[start - 1].strip()
        if not lines[start - 1].strip() or above.startswith("#") or above.endswith((";", "}", "{")):
            break
        start -= 1
    return start


def set_pragma(opened: dict[str, str], line: str, blank: str) -> None:
    """Put a file-level pragma on LINE that changes the code into OPENED (pragma name: its normalized text), or take
    it out when LINE resets it. BLANK is LINE from names.blank_literals."""
    pragma = PRAGMA.match(blank)
    if not pragma or pragma[1] in HARMLESS_PRAGMAS:
        return
    # the blank line has the same columns, and only the real line still has the strings, as in optimize("", on)
    argument = re.sub(r"\s+", "", line[pragma.start(2):pragma.end(2)]) if pragma[2] is not None else ""
    if argument in RESETS:
        opened.pop(pragma[1], None)
    else:
        opened[pragma[1]] = f"#pragma {pragma[1]}({argument})"


def volatile_globals(text: str) -> set[str]:
    """The names TEXT declares `volatile` at file level: a declaration line that starts at its first column, as in
    `extern volatile int g;`. A line inside a function or a struct is indented."""
    lines = names.blank_literals(text).split("\n")
    return {names.declared_name(line.rstrip()[:-1]) for line in lines
            if line[:1].strip() and line.rstrip().endswith(";") and VOLATILE.search(line)} - {None}


def is_definition(annotation: re.Match | None) -> bool:
    """True for the annotation of a function definition that is not a stub."""
    return bool(annotation) and annotation[1] in names.FUNCTION_KINDS and annotation[1] != "STUB"


def file_tricks(text: str, volatiles: set[str] = frozenset(),
                fakes: Callable[[list[str]], list[str]] | None = None) -> dict[int, str]:
    """address: the tricks of each function definition in TEXT that has one, in the order they appear. A definition
    runs from its declarator_start to the first line that is exactly "}". A stub is left out: it counts as nothing
    anyway. VOLATILES: the globals declared `volatile` in any source, from volatile_globals. FAKES gives the kinds of
    the fake-match lines in a definition's lines from its annotation on (fakematch.checker)."""
    lines = text.split("\n")
    blank = names.blank_literals(text).split("\n")
    opened = {}  # pragma name: its normalized text, while it is set
    found = {}
    for i, line in enumerate(lines):
        set_pragma(opened, line, blank[i])
        annotation = names.annotation().match(line)
        if not is_definition(annotation):
            continue
        end = names.definition_end(lines, i)
        if end is None:
            continue  # check.py's annotation lint reports a definition with no end
        body = "\n".join(blank[declarator_start(lines, blank, i):end + 1])
        reasons = list(dict.fromkeys(words(FORBIDDEN, body) + words(KEYWORDS, body)))
        reasons += [f"volatile global {name}" for name in sorted(volatiles & set(re.findall(r"\w+", body)))]
        reasons += [f"after {setting}" for setting in opened.values()]
        if fakes:
            reasons += [f"fake match {kind}" for kind in dict.fromkeys(fakes(lines[i:end + 1]))]
        if reasons:
            found[int(annotation[2], 16)] = ", ".join(reasons)
    return found


def scan(root: Path, fakes: Callable[[list[str]], list[str]] | None = None) -> dict[int, tuple[str, str]]:
    """address: (file, tricks) of each function in root/src that has a trick. FAKES: as in file_tricks."""
    sources = names.read_sources(root)
    volatiles = set().union(*map(volatile_globals, sources.values()))
    return {address: (rel, reasons) for rel, text in sources.items()
            for address, reasons in file_tricks(text, volatiles, fakes).items()}


def main() -> int:
    found = scan(names.ROOT, fakematch.checker(names.ROOT, project.require_game()))
    for address, (rel, reasons) in sorted(found.items()):
        print(f"0x{address:08x} {rel}: {reasons}")
    print(f"{len(found)} functions with a trick")
    return 0


if __name__ == "__main__":
    sys.exit(main())
