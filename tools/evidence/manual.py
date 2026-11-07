"""Manual sections: the names that a vendor manual writes in each function's section, for spelling C (spelling.py).

A manual is a text dump of a vendor reference manual, one entry of the configuration's "manuals" list. The dump has
lost the layout: a page can be one long line, and a table cell can run into the next one. So the reader works on the
text, not on its lines:
1. Index entries are dropped: a name, an optional space and a run of at least four dots, as in a table of contents
   ("xxFoo..........Does foo."). The name and the dots go; the description stays.
2. The text splits at each FORMAT marker (the word FORMAT). A section runs from one marker to the next, so the next
   section's title counts for the section before it. The text before the first marker is in no section.
3. The section's head runs from its marker to its first PARAMETERS heading, or to its end when it has none. The
   section's functions are the identifiers in the head that a "(" follows and that the manual's reference set
   declares as a function or a function-like macro.
4. A section with no such function is dropped: "no prototype" when no identifier in its head has a "(", else
   "unknown function".

The names of a section are its identifier words (a word that starts with a digit is none). A word of capitals,
digits and underscores that runs into a lowercase letter also gives the run before it, because the dump glued the
next word to it: NAMEtext gives NAME. When the run ends in a capital, the run without that capital counts too, for a
glued word with a capital: NAMEText gives NAME (and NAMET). So a name of capitals is found in glued text, and a name
with a lowercase letter only as a whole word.

Standard library only.
"""

import re
from collections import Counter
from dataclasses import dataclass, field

import config

MARKER = re.compile(r"(?<![A-Za-z0-9_])FORMAT(?![A-Za-z0-9_])")
HEAD_END = re.compile(r"(?<![A-Za-z0-9_])PARAMETERS(?![A-Za-z0-9_])")
INDEX = re.compile(r"(?<![A-Za-z0-9_])[A-Za-z_][A-Za-z0-9_]*\s?\.{4,}")
CALL = re.compile(r"(?<![A-Za-z0-9_])([A-Za-z_][A-Za-z0-9_]*)\s*\(")
WORD = re.compile(r"[A-Za-z0-9_]+")
CAPITALS = re.compile(r"[A-Z0-9_]+")
NO_PROTOTYPE, UNKNOWN = "no prototype", "unknown function"


@dataclass(frozen=True)
class Section:
    functions: tuple  # the functions of its prototype, in text order
    names: frozenset  # the names it writes


@dataclass
class Reading:
    """One manual, read."""

    path: str
    markers: int = 0  # FORMAT markers
    index: int = 0  # index entries dropped
    sections: list = field(default_factory=list)  # the kept Section records
    dropped: Counter = field(default_factory=Counter)  # reason -> sections
    unknown: Counter = field(default_factory=Counter)  # the unknown functions -> sections


def names_of(text: str) -> frozenset:
    """The names that TEXT writes, with the runs of capitals of glued words."""
    names = set()
    for word in WORD.findall(text):
        if word[0].isdigit():
            continue
        names.add(word)
        run = CAPITALS.match(word)
        if run is None or run.end() == len(word) or not word[run.end()].islower():
            continue
        names.add(run.group())
        if len(run.group()) >= 2 and run.group()[-1].isupper():
            names.add(run.group()[:-1])
    return frozenset(names)


def parse(path: str, text: str, is_function) -> Reading:
    """The sections of manual TEXT. IS_FUNCTION: name -> whether the reference set declares it as a function."""
    reading = Reading(path)
    reading.index = len(INDEX.findall(text))
    text = INDEX.sub(" ", text)
    starts = [match.start() for match in MARKER.finditer(text)]
    reading.markers = len(starts)
    for start, end in zip(starts, starts[1:] + [len(text)]):
        body = text[start:end]
        stop = HEAD_END.search(body)
        called = CALL.findall(body[:stop.start()] if stop else body)
        functions = tuple(dict.fromkeys(name for name in called if is_function(name)))
        if functions:
            reading.sections.append(Section(functions, names_of(body)))
        elif called:
            reading.dropped[UNKNOWN] += 1
            reading.unknown.update(dict.fromkeys(called, 1))
        else:
            reading.dropped[NO_PROTOTYPE] += 1
    return reading


def read(loaded, found) -> list:
    """The Reading of each manual of LOADED (a config.Config). FOUND: the inventory, for the reference closures."""
    readings = []
    for manual in loaded.manuals:
        closures = [closure for name, closure in found.closures if name == manual.reference]

        def is_function(name: str, closures=closures) -> bool:
            return any(name in closure.functions or closure.macros.is_function(name) for closure in closures)

        try:
            text = manual.path.read_text(encoding=manual.encoding)
        except FileNotFoundError as error:
            raise config.ConfigError(f"missing manual {manual.path}") from error
        except UnicodeDecodeError as error:
            raise config.ConfigError(f"{manual.path}: does not decode as {manual.encoding}: {error}") from error
        readings.append(parse(str(manual.path), text, is_function))
    return readings


def by_function(readings: list) -> dict:
    """Function -> the names of each of its sections, over every manual (spelling.Speller's MANUAL)."""
    sections = {}
    for reading in readings:
        for section in reading.sections:
            for function in section.functions:
                sections.setdefault(function, []).append(section.names)
    return {function: tuple(items) for function, items in sections.items()}
