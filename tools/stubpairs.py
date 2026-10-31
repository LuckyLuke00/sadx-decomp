"""The #pragma optimize("", off) and on pair around a STUB that its own file calls.

Under /O1 and above the compiler drops a call to an empty function of its own file. A function that it compiles
without optimization keeps its calls, as one of another file does, so the callers keep the game's code. pair_stubs
puts the pair around each STUB that a call needs it for and takes it from every other one. tree_fixes does that for
each file under src: check.py pairs lists or writes the fixes, and ci.py fails while one is left.
"""

import re
from pathlib import Path

import codegen
import names
import progress

OFF, ON = '#pragma optimize("", off)', '#pragma optimize("", on)'


def calls_stub(lines: list[str], span: tuple[int, int], sig: str) -> bool:
    """Whether the code of LINES outside SPAN, a STUB's definition with the signature SIG, calls it: its name with a
    `(` after it. A constructor, destructor or operator also has calls without one, so for those any use of its
    class counts, other than as the scope of a name such as another member's. Taking the stub's address is no
    call."""
    name = names.declared_name(sig)
    code = names.code_outside(lines, name, span)
    *scope, last = name.split("::")
    if scope and (last in (scope[-1], "~" + scope[-1]) or last.startswith("operator")):
        return re.search(rf"\b{re.escape(scope[-1])}\b(?!\s*::)", code) is not None
    return re.search(rf"(?<!\w){re.escape(last)}\s*\(", code) is not None


def pair_stubs(text: str, flags: str | None) -> str:
    """TEXT, a source file's lines, with OFF and ON around each STUB that calls_stub finds called when FLAGS, its
    code group's (None: unknown), optimize, and around no other definition. A file without a FUNCTION, TEMPLATE or
    SYNTHETIC gets none: no caller there has a score."""
    lines = text.split("\n")
    scored = codegen.function_marker().search(text) is not None
    optimized = scored and (flags is None or "/Od" not in flags.split())
    for start in reversed([i for i, line in enumerate(lines) if line.startswith("// STUB")]):
        end = names.definition_end(lines, start)
        if end is None:
            continue
        if start and lines[start - 1] == OFF and end + 1 < len(lines) and lines[end + 1] == ON:
            del lines[end + 1], lines[start - 1]
            start, end = start - 1, end - 1
        func = lines[start:end + 1]
        if optimized and calls_stub(lines, (start, end), func[names.signature_index(func)]):
            lines[start:end + 1] = [OFF, *func, ON]
    return "\n".join(lines)


def paired(text: str) -> set[str]:
    """The STUB annotations of TEXT that sit right below an OFF line."""
    lines = text.split("\n")
    return {line for before, line in zip(lines, lines[1:]) if before == OFF and line.startswith("// STUB")}


def tree_fixes() -> list[tuple[Path, str, int, int]]:
    """(path, fixed text, pairs it adds, pairs it removes) for each source file under src that pair_stubs changes."""
    fixes = []
    for path in sorted((progress.ROOT / "src").rglob("*")):
        if path.suffix not in (".c", ".cpp"):
            continue
        text = codegen.read_source(path)
        fixed = pair_stubs(text, codegen.code_flags(text))
        if fixed != text:
            before, after = paired(text), paired(fixed)
            fixes.append((path, fixed, len(after - before), len(before - after)))
    return fixes
