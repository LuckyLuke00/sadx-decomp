"""Baseline diff: an earlier inventory joined with this one. Every old row is kept or explained by a fixed cause, and
every new row the old inventory lacks is listed.

The baseline is evidence/baseline-inventory.csv, hand-owned once imported, in the columns of the first scanner:
file (relative to the sources root), line, callee (as written), arg (1-based), literal, value, candidates
("NAME (header); NAME (header)" or "A | B (bit flags)"). `evidence.py import-baseline PATH` copies it in once; each
`evidence.py run` then writes the diff while the file exists.

The join key is the file, the line, the callee with leading underscores dropped, and the argument index; never the
argument text. Rows with the same key pair in order.

An old row that pairs gets one cause:
- same: the same value and the same first candidate;
- converted to the slot type: the same argument text, and the new value is the old one converted to the parameter
  type (`-1` at an unsigned slot); the old scanner evaluated with unbounded integers and never converted;
- cast: the same argument text with a cast the old scanner dropped, and another value (`(short)0x18000`);
- type gate: an old candidate is a truth or null name that the slot's type does not take;
- old definition differs: an old exact candidate has another value, or none, among the slot's names under the new
  header reader; the old scanner kept the first definition of each name and ignored #if;
- new cover rank: the old first candidate is among the new candidates, not first;
- new search: the old scanner found no candidate and the new search finds one.
An old row that does not pair gets one cause:
- file not read: its suffix is not a source suffix (the old scanner also read headers);
- unsupported file: the new reader does not read the file (it has preprocessor lines);
- callee name stripped: argmap.csv maps the callee only without its leading underscores;
- macro callee: the callee is a function-like macro of the target closures;
- inside a string: on that line the callee is only inside a string or character literal, where the old call pattern
  also matched.
Anything else is "unexplained", and the report counts it.

A new row the old inventory lacks gets one cause: spelled with names, nonconstant, old comment stripping (the old
scanner's comment pattern blanks the call, because it ignored strings), not a plain literal, or not in the baseline.

Standard library only.
"""

import csv
import re
import shutil
import sys
from collections import Counter
from dataclasses import dataclass
from pathlib import Path

import covers
import ctokens
import inventory
import outputs

sys.path.append(str(Path(__file__).resolve().parents[1]))  # tools/, after the standard library
import osutil  # noqa: E402

BASELINE = "baseline-inventory.csv"
DIFF = Path("diagnostics") / "baseline-diff.csv"
OLD_COLUMNS = ("file", "line", "callee", "arg", "literal", "value", "candidates")
DIFF_COLUMNS = ("side", "cause", "file", "line", "callee", "arg", "old_literal", "old_value", "new_expression",
                "new_value", "old_candidates", "new_candidates", "id")

SAME, CONVERTED, CAST, TYPE_GATE = "same", "converted to the slot type", "cast", "type gate"
DEFINITION, RANK, SEARCH = "old definition differs", "new cover rank", "new search"
NOT_READ, UNSUPPORTED_FILE, STRIPPED = "file not read", "unsupported file", "callee name stripped"
MACRO, IN_STRING, UNEXPLAINED = "macro callee", "inside a string", "unexplained"
NAMES, NONCONSTANT, COMMENT_CUT = "spelled with names", "nonconstant", "old comment stripping"
NOT_PLAIN, NOT_IN_BASELINE = "not a plain literal", "not in the baseline"

# The first scanner's patterns: comments, blind to strings; the casts it dropped before it evaluated.
OLD_COMMENT = re.compile(r"//[^\n]*|/\*.*?\*/", re.S)
OLD_CAST = re.compile(r"\(\s*(?:unsigned\s+|signed\s+)?(?:int|long|short|char|Uint32|Sint32|Int|DWORD|UINT|LONG)\s*\)")
GATED_NAMES = covers.NULL_NAMES | covers.TRUTH_NAMES


class BaselineError(Exception):
    """The baseline file is missing or malformed."""


@dataclass(frozen=True)
class Old:
    file: str  # relative to the repository, like the inventory's
    line: int
    callee: str
    arg: int
    literal: str
    value: str
    candidates: tuple  # the candidate texts, without their header notes

    @property
    def key(self) -> tuple:
        return self.file, self.line, self.callee.lstrip("_"), self.arg


@dataclass(frozen=True)
class Entry:
    side: str  # old or new
    cause: str
    old: Old | None
    new: inventory.Record | None


def import_baseline(source: Path, folder: Path) -> Path:
    """Copies SOURCE in as the baseline, once. Returns the copy."""
    target = folder / BASELINE
    if target.exists():
        raise BaselineError(f"{target} exists; the baseline is imported once")
    read_baseline(source, "")
    shutil.copyfile(source, target)
    return target


def read_baseline(path: Path, prefix: str) -> list[Old]:
    """PREFIX: the sources root relative to the repository, with a trailing slash ("" keeps the paths)."""
    if not path.is_file():
        raise BaselineError(f"missing hand-owned file {path}")
    with path.open(encoding="utf-8", newline="") as data:
        reader = csv.DictReader(data)
        if tuple(reader.fieldnames or ()) != OLD_COLUMNS:
            raise BaselineError(f"{path}: the columns must be {','.join(OLD_COLUMNS)}")
        rows = []
        for line, fields in enumerate(reader, 2):
            try:
                rows.append(Old(prefix + fields["file"], int(fields["line"]), fields["callee"], int(fields["arg"]),
                                fields["literal"], str(int(fields["value"])), _texts(fields["candidates"])))
            except ValueError as error:
                raise BaselineError(f"{path}:{line}: {error}") from None
    return rows


def prefix(loaded) -> str:
    """The sources root relative to the repository, with a trailing slash: the old file paths start there."""
    return loaded.sources.root.relative_to(loaded.root).as_posix() + "/"


def _bare(text: str) -> str:
    return "".join(text.split())


def _texts(candidates: str) -> tuple:
    return tuple(part.rsplit(" (", 1)[0] for part in candidates.split("; ") if part)


def explain(found: inventory.Inventory, old_rows: list[Old], loaded, rows: list, generation: int) -> list[Entry]:
    """The diff of FOUND against OLD_ROWS, written to diagnostics/baseline-diff.csv."""
    entries = diff(found, old_rows, loaded, rows)
    target = loaded.folder / DIFF
    target.parent.mkdir(exist_ok=True)
    osutil.write_whole(target, format_diff(entries, generation))
    return entries


def unexplained(entries: list[Entry]) -> int:
    return sum(1 for entry in entries if entry.side == "old" and entry.cause == UNEXPLAINED)


def diff(found: inventory.Inventory, old_rows: list[Old], loaded, rows: list) -> list[Entry]:
    """FOUND: an inventory built from the same tree. ROWS: the argmap rows it used. The old inventory holds call
    sites only, so only call records join it."""
    new = {}
    for record in found.records:
        if record.kind != inventory.CALL:
            continue
        new.setdefault((record.file, record.line, record.callee.lstrip("_"), int(record.slot.split("/")[-1])),
                       []).append(record)
    olds = {}
    for row in old_rows:
        olds.setdefault(row.key, []).append(row)
    sources = _Sources(loaded, found, {row.callee for row in rows})
    entries = []
    for key, items in olds.items():
        records = new.get(key, [])
        entries += [Entry("old", kept(row, record), row, record) for row, record in zip(items, records)]
        entries += [Entry("old", sources.missing(row), row, None) for row in items[len(records):]]
    for key, records in new.items():
        entries += [Entry("new", sources.extra(record), None, record) for record in records[len(olds.get(key, [])):]]
    return entries


def kept(old: Old, record: inventory.Record) -> str:
    result = record.result
    if old.value != record.value:
        if not result.ok or not isinstance(result.value, int) or _bare(old.literal) != _bare(record.argument):
            return UNEXPLAINED
        modulus = 1 << result.ctype.bits
        if int(old.value) % modulus == result.value % modulus:
            return CONVERTED
        return CAST if OLD_CAST.search(old.literal) else UNEXPLAINED
    texts = [candidate.text for candidate in record.search.candidates] if record.search else []
    if old.candidates[:1] == tuple(texts[:1]):
        return SAME
    names = {name.strip("~() ") for text in old.candidates for name in text.split("|")}
    if record.cover_slot and any(not covers.passes_gate(covers.Name(name, result.value, False), record.cover_slot)
                                 for name in names & GATED_NAMES):
        return TYPE_GATE
    values = {}
    for name in record.pool.names if record.pool else ():
        values.setdefault(name.name, set()).add(name.value)
    exact = [text for text in old.candidates if text.isidentifier()]
    if any(result.value not in values.get(name, ()) for name in exact):
        return DEFINITION
    if old.candidates and old.candidates[0] in texts:
        return RANK
    if not old.candidates and texts:
        return SEARCH
    return UNEXPLAINED


class _Sources:
    """The source text the missing and extra rows need, read once per file."""

    def __init__(self, loaded, found: inventory.Inventory, mapped: set):
        self.loaded, self.mapped = loaded, mapped
        self.unsupported = {file for file, _ in found.unsupported_files}
        self.headers = found.headers
        self.texts, self.tokens, self.blanked = {}, {}, {}

    def text(self, file: str) -> str:
        if file not in self.texts:
            path = self.loaded.root / file
            self.texts[file] = path.read_bytes().decode(self.loaded.sources.encoding) if path.is_file() else ""
        return self.texts[file]

    def line_tokens(self, file: str, line: int) -> list:
        if file not in self.tokens:
            try:
                tokens, _ = ctokens.tokenize(self.text(file))
            except ctokens.Unsupported:
                tokens = []
            self.tokens[file] = tokens
        return [token for token in self.tokens[file] if token.line == line]

    def missing(self, old: Old) -> str:
        if Path(old.file).suffix not in self.loaded.sources.suffixes:
            return NOT_READ
        if old.file in self.unsupported:
            return UNSUPPORTED_FILE
        if old.callee not in self.mapped and old.callee.lstrip("_") in self.mapped:
            return STRIPPED
        if self.headers.is_function_macro(old.callee):
            return MACRO
        tokens = self.line_tokens(old.file, old.line)
        named = any(token.kind == "id" and token.text == old.callee for token in tokens)
        quoted = any(token.kind in ("str", "char") and old.callee in token.text for token in tokens)
        return IN_STRING if quoted and not named else UNEXPLAINED

    def extra(self, record: inventory.Record) -> str:
        result = record.result
        if result.status == "nonconstant":
            return NONCONSTANT
        if result.names:
            return NAMES
        if self.cut(record):
            return COMMENT_CUT
        plain = record.expression.lstrip("- ").rstrip("ulUL")
        return NOT_IN_BASELINE if plain.isdigit() else NOT_PLAIN

    def cut(self, record: inventory.Record) -> bool:
        """The old comment pattern blanks the callee of RECORD."""
        if record.file not in self.blanked:
            self.blanked[record.file] = OLD_COMMENT.sub(lambda match: re.sub(r"[^\n]", " ", match.group(0)),
                                                        self.text(record.file)).split("\n")
        lines = self.blanked[record.file]
        if record.line > len(lines):
            return False
        start = record.column - 1
        return lines[record.line - 1][start:start + len(record.callee)] != record.callee


def format_diff(entries: list[Entry], generation: int) -> str:
    rows = []
    for entry in sorted(entries, key=_order):
        old, new = entry.old, entry.new
        where = old or new
        rows.append((entry.side, entry.cause, where.file, where.line, where.callee,
                     old.arg if old else new.slot, old.literal if old else "", old.value if old else "",
                     new.expression if new else "", new.value if new else "",
                     "; ".join(old.candidates) if old else "",
                     "; ".join(candidate.text for candidate in new.search.candidates)
                     if new and new.search else "", new.id if new else ""))
    return outputs.csv_text("evidence-baseline-diff", generation, DIFF_COLUMNS, rows)


def _order(entry: Entry) -> tuple:
    where = entry.old or entry.new
    return entry.side, entry.cause, where.file, where.line, where.callee


def summary(entries: list[Entry]) -> list[str]:
    counts = Counter((entry.side, entry.cause) for entry in entries)
    lines = [f"old rows {sum(1 for entry in entries if entry.side == 'old')}, "
             f"new rows not in the baseline {sum(1 for entry in entries if entry.side == 'new')}"]
    lines += [f"  {side} {cause}: {count}" for (side, cause), count in sorted(counts.items())]
    missing = unexplained(entries)
    lines.append(f"unexplained old rows: {missing}" if missing else "every old row is kept or explained")
    return lines
