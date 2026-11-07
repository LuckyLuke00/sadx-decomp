"""Review decisions: evidence/notes.csv, written by `evidence.py decide` and read by the ledger (ledger.py).

notes.csv: the line `# evidence-notes schema=1`, then a CSV header and one row per decision, oldest first. The file
is append-only, and the latest row per id wins. Columns: id,decision,candidate,hash,fingerprint,time,note.
- decision: confirm, reject or reopen.
- candidate: the candidate the decision is about: the top candidate, or what decide names: another candidate of the
  row, or a candidate written with other aliases of its names, as written. Empty for reopen.
- hash: review_hash of the ledger row when the decision was made.
- fingerprint: the ledger row's fingerprint then.
- time: the UTC time, ISO 8601, to the second.
- note: free text.

decide() checks the id against the live ledger. An id the ledger does not hold was never minted, so it fails. A gone
or ambiguous id gives a warning: its decision is orphaned. The new file is written whole, atomically.

Standard library only.
"""

import csv
import hashlib
import io
import json
import re
import sys
from dataclasses import dataclass, fields
from pathlib import Path

sys.path.append(str(Path(__file__).resolve().parents[1]))  # tools/, after the standard library
import osutil  # noqa: E402

NOTES = "notes.csv"
SCHEMA = 1
HEADER = re.compile(r"# evidence-notes schema=(\d+)")
CONFIRM, REJECT, REOPEN = "confirm", "reject", "reopen"
DECISIONS = (CONFIRM, REJECT, REOPEN)
ORPHAN_STATUSES = ("gone", "ambiguous")  # ledger statuses of an id that is not live
CONFIRMED, REJECTED, STALE = "confirmed", "rejected", "stale"  # the ledger statuses that a decision gives


class DecisionError(Exception):
    """notes.csv cannot be read, or a decision cannot be made."""


@dataclass(frozen=True)
class Decision:
    id: str
    decision: str
    candidate: str
    hash: str
    fingerprint: str
    time: str
    note: str


COLUMNS = tuple(item.name for item in fields(Decision))


def review_hash(candidates: str, meaning: str, spelling: str) -> str:
    """The SHA-256 of a ledger row's candidates and its two tiers. A decision goes stale when it changes."""
    return hashlib.sha256(json.dumps([candidates, meaning, spelling]).encode("utf-8")).hexdigest()


def read_notes(path: Path) -> list[Decision]:
    """The decisions in file order. A missing file holds none: no decision was made yet."""
    if not path.is_file():
        return []
    first, _, rest = path.read_bytes().decode("utf-8").partition("\n")
    match = HEADER.fullmatch(first)
    if match is None:
        raise DecisionError(f"{path}: not a notes file, its first line is {first[:60]!r}")
    if int(match[1]) != SCHEMA:
        raise DecisionError(f"{path}: notes schema {match[1]}, this tool reads schema {SCHEMA}")
    reader = csv.DictReader(io.StringIO(rest))
    if tuple(reader.fieldnames or ()) != COLUMNS:
        raise DecisionError(f"{path}: the columns must be {','.join(COLUMNS)}")
    found = [Decision(**row) for row in reader]
    for line, item in enumerate(found, start=3):
        if item.decision not in DECISIONS:
            raise DecisionError(f"{path}:{line}: unknown decision {item.decision!r}")
    return found


def latest(decisions: list[Decision]) -> dict:
    """Id -> its latest decision."""
    return {item.id: item for item in decisions}


def describe(decision: Decision) -> str:
    """One decision in one line, for the reports."""
    text = f"{decision.decision} {decision.candidate or '-'} at {decision.time}"
    return f"{text}: {decision.note}" if decision.note else text


def format_notes(decisions: list[Decision]) -> bytes:
    out = io.StringIO()
    out.write(f"# evidence-notes schema={SCHEMA}\n")
    writer = csv.writer(out, lineterminator="\n")
    writer.writerow(COLUMNS)
    for item in decisions:
        writer.writerow([getattr(item, column) for column in COLUMNS])
    return out.getvalue().encode("utf-8")


def spelled_candidate(text: str, aliases: dict) -> str | None:
    """The candidate that TEXT writes with one alias of each of its terms, in any order, under the same ~, or None.
    ALIASES: candidate text -> its alias groups, one tuple of names per term."""
    inverted = text.startswith("~")
    body = text[1:].strip() if inverted else text
    if inverted and body.startswith("(") and body.endswith(")"):
        body = body[1:-1]
    names = [name.strip() for name in body.split("|")]
    for candidate, groups in aliases.items():
        term_of = {name: index for index, group in enumerate(groups) for name in group}
        terms = [term_of.get(name) for name in names]
        if candidate.startswith("~") == inverted and None not in terms and sorted(terms) == list(range(len(groups))):
            return candidate
    return None


def decide(folder: Path, rows: dict, site_id: str, decision: str, candidate: str, note: str, time: str,
           aliases: dict) -> tuple[Decision, list[str]]:
    """Appends one decision to FOLDER/notes.csv. ROWS: the live ledger by id. CANDIDATE: "" for the top candidate.
    TIME: the UTC time. ALIASES: the alias groups of the row's candidates (spelled_candidate). Returns the decision
    and the warnings."""
    row = rows.get(site_id)
    if row is None:
        raise DecisionError(f"{site_id}: no such id in the ledger")
    texts = row.candidates.split("; ") if row.candidates else []
    if decision == REOPEN:
        if candidate:
            raise DecisionError("reopen takes no candidate")
    elif not texts:
        raise DecisionError(f"{site_id} has no candidate to {decision}")
    elif not candidate:
        candidate = texts[0]
    elif candidate not in texts and spelled_candidate(candidate, aliases) not in texts:
        raise DecisionError(f"{candidate!r} is not a candidate of {site_id}, nor one with other aliases of its names: "
                            f"{row.candidates}")
    warnings = [f"{site_id} is {row.status}: the decision is orphaned"] if row.status in ORPHAN_STATUSES else []
    made = Decision(site_id, decision, candidate, review_hash(row.candidates, row.tier, row.spelling_tier),
                    row.fingerprint, time, note)
    path = folder / NOTES
    osutil.write_whole(path, format_notes(read_notes(path) + [made]))
    return made, warnings
