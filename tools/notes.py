"""The notes about the original in src (docs/STYLE.md, Notes): one line each, in one exact form, in its place.

Tools write FRAME_NOTE (work/tools/inlinefit.py) and FOLD_NOTE (llm.py); a hand writes the DIFF code and type notes
and the PLACEHOLDER notes. tagged_problems and untagged_problems check a file's text; namecheck.py runs them at each
commit.
"""
import re

import names

FRAME_NOTE = "// DIFF: frame: the original frame has {} more bytes; their source is unknown."
FOLD_NOTE = "// FOLD: the game's link folded this copy into the one of {} ({})."
TAG = re.compile(r"^\s*// (?:DIFF|FOLD|PLACEHOLDER):")
DIFF_FORM = re.compile(r"// DIFF: (?:code|type): [a-z0-9_][^\n]*\.")
PLACEHOLDER_FORM = re.compile(r"// PLACEHOLDER: ([A-Za-z_]\w*): [a-z0-9_][^\n]*\.")
ANNOTATION = re.compile(r"^// (?:FUNCTION|STUB|LIBRARY|TEMPLATE|SYNTHETIC|GLOBAL|VTABLE|STRING|LINE): ")
FUNCTION_ANNOTATION = re.compile(r"^// (?:FUNCTION|STUB): \w+ (0x[0-9a-fA-F]+)\s*$")
STATIC = re.compile(r"static\s")
DECORATED = re.compile(r"^//\s*\?")  # a decorated-name line, such as `// ?name@@YAXXZ`
TRIGGER = re.compile(r"\b(?:original\w*|differ\w*|unmatched|unknown|likely|placeholder\w*|folded|reserves)\b", re.I)
PLACEHOLDER_REACH = 5  # lines below a PLACEHOLDER note that may name its placeholder


def form(note, *patterns):
    """The regex of the tool-written NOTE with each {} in turn replaced by one of PATTERNS."""
    parts = [re.escape(part) for part in note.split("{}")]
    return re.compile("".join(part + pattern for part, pattern in zip(parts, [*patterns, ""])))


FRAME_FORM = form(FRAME_NOTE, r"([1-9]\d*)")
FOLD_FORM = form(FOLD_NOTE, r"[\w.]+", r"0x[0-9a-f]{8}")
PLACES = ((FRAME_FORM, FUNCTION_ANNOTATION, "a frame note must sit above a FUNCTION or STUB annotation"),
          (DIFF_FORM, ANNOTATION, "a DIFF note must sit above an annotation"),
          (FOLD_FORM, STATIC, "a FOLD note must sit right above the copy's static definition"))


def note_target(lines, k):
    """The first line after line K that is not a note."""
    k += 1
    while k < len(lines) and TAG.match(lines[k]):
        k += 1
    return lines[k] if k < len(lines) else ""


def tagged_problems(text):
    """(line number, why) for each note in TEXT that is not in its exact form and place."""
    lines = text.split("\n")
    for k, line in enumerate(lines):
        if TAG.match(line):
            why = tagged_problem(line, note_target(lines, k), "\n".join(lines[k + 1:k + 1 + PLACEHOLDER_REACH]))
            if why:
                yield k + 1, why


def tagged_problem(line, target, below):
    """Why the note LINE, above the line TARGET and the lines BELOW, is not in its exact form and place, or None."""
    for note_form, place, why in PLACES:
        if note_form.fullmatch(line):
            return None if place.match(target) else why
    placeholder = PLACEHOLDER_FORM.fullmatch(line)
    if not placeholder:
        return "a note not in one of the exact forms"
    name = placeholder.group(1)
    defines_it = re.match(rf"#define {name}\b", target)
    annotates_it = ANNOTATION.match(target) and re.search(rf"\b{name}\b", below)
    if defines_it or annotates_it:
        return None
    return f"a PLACEHOLDER note must sit above the #define or the annotation of {name}"


def untagged_problems(text):
    """(line number, why) for each untagged prose comment in TEXT that talks about the original."""
    for literal in names.LITERAL.finditer(text):
        comment = literal.group(0)
        if not comment.startswith(("//", "/*")) or is_marker(comment) or not is_prose(comment):
            continue
        word = TRIGGER.search(comment)
        if word:
            line = text.count("\n", 0, literal.start()) + 1
            yield line, f"an untagged comment says `{word.group(0)}`: use a note tag"


def is_marker(comment):
    """Whether COMMENT is a note, an annotation or a decorated name, which the other checks cover."""
    return bool(TAG.match(comment) or ANNOTATION.match(comment) or DECORATED.match(comment))


def is_prose(comment):
    """Whether COMMENT holds more than one word."""
    return " " in comment.strip("/* ")
