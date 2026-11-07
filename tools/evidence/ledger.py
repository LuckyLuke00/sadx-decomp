"""The ledger: ledger.csv in each state generation, one row per site id ever seen. No row is ever deleted.

ledger.csv: the line `# evidence-ledger schema=2`, then a CSV header and one row per id, in id order.
- kind: placeholder for a placeholder site, value for any other.
- status: open or applied for a live site (applied: every value-giving leaf of the expression is a header name);
  gone when the remap found no pair for the id; ambiguous when it could not tell which of several identical sites
  the id is. A row whose id is not live keeps its last status. A live site's latest decision (decisions.py) wins
  over open and applied: confirmed or rejected while the row's review hash equals the decision's, else stale. A
  reopen leaves open or applied.
- spelling: the argument as written. candidates: every candidate, ranked, "; " between them; the first is the top
  candidate. tier: the top candidate's meaning tier (score.py). spelling_tier: its spelling tier (spelling.py).
  evidence: the argmap row and its prototype check (a field site: the fieldmap row and its member check), the top
  candidate's origins, the reference builds that pass the same value and those that pass another (pairs.py), and its
  spelling evidence. counter: the counterevidence.
- fingerprint: the hash of the inputs that feed the row: the names its row takes, with their values, origins and
  doubts; the row; the prototype; the expression and its value; the cited evidence, with the spelling
  evidence of every candidate and the reference values; and the configuration hash (config.Config.fingerprint).
  Canonical JSON.
- first_seen: the date the ledger first held the id. last_checked: the date its fingerprint last changed.
- file, line: where the site was last seen.

The changes of a run go to ledger-changes.md: new ids, ids kept through a pair that is not exact, moved meaning and
spelling tiers, added and removed candidates, rows that went gone or ambiguous (with the suggested new sites), the
stale decisions, the orphaned decisions (a confirm or reject on a gone or ambiguous id), and the count of rows whose
fingerprint changed while their tiers and candidates did not.

commit() is the write of one run: it remaps the coverage sites against the live state (remap.py), gives them ids,
builds the ledger with the latest decisions of notes.csv, commits sites.csv and ledger.csv as one state generation
(state.py), writes ledger-changes.md, inventory.csv and argmap-proposed.csv, and makes a backup, with notes.csv when
it exists.

Standard library only.
"""

import csv
import hashlib
import io
import json
import re
import sys
from collections import Counter
from dataclasses import dataclass, replace
from pathlib import Path

import ceval
import decisions
import inventory
import remap
import score
import spelling
import state
import symbols

sys.path.append(str(Path(__file__).resolve().parents[1]))  # tools/, after the standard library
import osutil  # noqa: E402

LEDGER, CHANGES = "ledger.csv", "ledger-changes.md"
SCHEMA = 2
HEADER = re.compile(r"# evidence-ledger schema=(\d+)")
COLUMNS = ("id", "kind", "status", "spelling", "candidates", "tier", "spelling_tier", "evidence", "counter",
           "fingerprint", "first_seen", "last_checked", "file", "line")
VALUE, PLACEHOLDER = "value", "placeholder"
CHECKS = {inventory.CALL: ("argmap", "prototype check"), inventory.FIELD: ("fieldmap", "member check")}  # per kind
SYMBOL_CHECK = ("symbols", "symbol check")  # the source and check of a row from the reference symbols, of any kind
GONE, AMBIGUOUS = decisions.ORPHAN_STATUSES
NEW, ADDED, REMAPPED, TIER, CANDIDATES, RECHECKED = ("new id", "added to the ledger", "kept through a remap",
                                                     "tier moved", "candidates changed", "rechecked")
STALE_DECISION, ORPHANED = "stale decision", "orphaned decision"
CHANGE_ORDER = (NEW, REMAPPED, TIER, CANDIDATES, GONE, AMBIGUOUS, STALE_DECISION, ORPHANED, ADDED, RECHECKED)
COUNT_ONLY = (ADDED, RECHECKED)


class LedgerError(Exception):
    """ledger.csv cannot be read."""


@dataclass(frozen=True)
class Row:
    id: str
    kind: str
    status: str
    spelling: str
    candidates: str
    tier: str
    spelling_tier: str
    evidence: str
    counter: str
    fingerprint: str
    first_seen: str
    last_checked: str
    file: str
    line: int


@dataclass(frozen=True)
class Change:
    kind: str
    id: str
    text: str = ""


def format_ledger(rows: dict) -> bytes:
    out = io.StringIO()
    out.write(f"# evidence-ledger schema={SCHEMA}\n")
    writer = csv.writer(out, lineterminator="\n")
    writer.writerow(COLUMNS)
    for key in sorted(rows, key=remap.id_number):
        row = rows[key]
        writer.writerow([getattr(row, column) for column in COLUMNS])
    return out.getvalue().encode("utf-8")


def parse_ledger(data: bytes) -> dict:
    """The rows by id."""
    first, _, rest = data.decode("utf-8").partition("\n")
    match = HEADER.fullmatch(first)
    if match is None:
        raise LedgerError(f"not a ledger file: its first line is {first[:60]!r}")
    if int(match[1]) != SCHEMA:
        raise LedgerError(f"ledger schema {match[1]}: this tool reads schema {SCHEMA}")
    reader = csv.DictReader(io.StringIO(rest))
    if tuple(reader.fieldnames or ()) != COLUMNS:
        raise LedgerError(f"the ledger columns must be {','.join(COLUMNS)}")
    return {fields["id"]: Row(**{**fields, "line": int(fields["line"])}) for fields in reader}


def kind_of(site_kind: str) -> str:
    """The ledger kind of a site kind."""
    return PLACEHOLDER if site_kind == inventory.PLACEHOLDER else VALUE


def evidence(record, grade: score.Grade, top: spelling.Spelling) -> str:
    row = record.row
    if record.kind == inventory.PLACEHOLDER:
        return f"placeholder {row.note}: {inventory.PLACEHOLDER_NOTES[row.note]}; {record.prototype}"
    if row.status in symbols.STATUSES:
        source, check = SYMBOL_CHECK
        parts = [f"{source} {row.status} {', '.join(row.groups)}"]
    else:
        source, check = CHECKS[record.kind]
        parts = [f"{source} {row.status}" + (f" {row.header}" if row.header else "")]
    parts.append(f"{check} passed" if record.check.passed else f"{check} failed: {record.check.reason}")
    if grade.origins:
        parts.append(f"origins {' '.join(grade.origins)}")
    same = [build for build, _, agrees in record.references if agrees]
    if same:
        parts.append(f"same value in build {', '.join(same)}")
    parts += [f"other value in build {build}: {text}" for build, text, agrees in record.references if not agrees]
    parts.append(f"spelling {top.text}")
    return "; ".join(parts)


def live_status(site_state: str, decision, current: str) -> str:
    """The status of a live site in state SITE_STATE (open or applied) with its latest DECISION (or None), where
    CURRENT is the row's review hash now."""
    if decision is None or decision.decision == decisions.REOPEN:
        return site_state
    if decision.hash != current:
        return decisions.STALE
    return decisions.CONFIRMED if decision.decision == decisions.CONFIRM else decisions.REJECTED


def fingerprint(record, grade: score.Grade, texts: list, configuration: str) -> str:
    pool, row = record.pool, record.row
    data = {
        "names": sorted([name.name, name.value, name.pointer, sorted(name.origins)] for name in pool.names)
        if pool else [],
        "uncertain": sorted(pool.uncertain) if pool else [],
        "disputed": sorted(pool.disputed.items()) if pool else [],
        "row": [row.callee, row.slot, row.mode, list(row.groups), row.status, row.header, row.spelled_type,
                list(row.origins)],
        "prototype": record.prototype,
        "site": [record.expression, record.value, record.result.status, record.result.cause],
        "evidence": [grade.tier, list(grade.counter), grade.reason, list(grade.origins), texts, record.flags,
                     list(record.accepted), record.check.passed, record.check.reason],
        "spellings": [[item.tier, item.text] for item in record.spellings],
        "references": [list(item) for item in record.references],
        "configuration": configuration,
    }
    return hashlib.sha256(json.dumps(data, sort_keys=True).encode("utf-8")).hexdigest()[:16]


def build(records: list, mapping: remap.Remap, old_sites: list, old: dict, configuration: str, today: str,
          decided: dict) -> tuple[dict, list]:
    """RECORDS: the coverage sites with their ids, in the order the remap saw them. MAPPING: that remap. OLD_SITES:
    the live sites before the run. OLD: the live ledger by id. DECIDED: id -> its latest decision. Returns the new
    ledger by id and the changes."""
    rows, changes = dict(old), []
    for index, record in enumerate(records):
        grade = score.grade_site(record)
        top = spelling.top_of(record.spellings)
        texts = [candidate.text for candidate in record.search.candidates] if record.search else []
        stamp = fingerprint(record, grade, texts, configuration)
        before = old.get(record.id)
        current = decisions.review_hash("; ".join(texts), grade.tier, top.tier)
        row = Row(record.id, kind_of(record.kind), live_status(record.state, decided.get(record.id), current), record.argument,
                  "; ".join(texts), grade.tier, top.tier, evidence(record, grade, top), "; ".join(grade.counter),
                  stamp, before.first_seen if before else today,
                  before.last_checked if before and before.fingerprint == stamp else today, record.file, record.line)
        rows[record.id] = row
        changes += _moved(before, row, mapping.ids[index], mapping.kinds[index])
    sites = {site.id: site for site in old_sites}
    suggested = {}
    for old_id, new_index in mapping.suggestions:
        suggested.setdefault(old_id, []).append(records[new_index].id)
    for status, ids in ((GONE, mapping.gone), (AMBIGUOUS, mapping.ambiguous)):
        for old_id in ids:
            site = sites[old_id]
            known = old.get(old_id) or Row(old_id, kind_of(site.kind), status, site.expression, "", "", "", "", "", "", today,
                                           today, site.file, site.line)
            rows[old_id] = replace(known, status=status)
            note = f", suggested: {' '.join(suggested[old_id])}" if old_id in suggested else ""
            changes.append(Change(status, old_id, f"{site.file}:{site.line} {site.expression}{note}"))
    return rows, changes + _decision_changes(rows, decided)


def _decision_changes(rows: dict, decided: dict) -> list:
    """The stale decisions, and the confirm and reject decisions on an id that is gone or ambiguous."""
    changes = []
    for site_id in sorted(decided, key=remap.id_number):
        row, decision = rows.get(site_id), decided[site_id]
        made = decisions.describe(decision)
        if row is not None and row.status == decisions.STALE:
            changes.append(Change(STALE_DECISION, site_id, f"{row.file}:{row.line} {row.spelling}: {made}, now "
                                                           f"{row.candidates or 'no candidate'} (meaning {row.tier}, "
                                                           f"spelling {row.spelling_tier})"))
        elif row is not None and row.status in decisions.ORPHAN_STATUSES and decision.decision != decisions.REOPEN:
            changes.append(Change(ORPHANED, site_id, f"{row.status}: {made}"))
    return changes


def _moved(before: Row | None, row: Row, kept: str, kind: str) -> list:
    where = f"{row.file}:{row.line} {row.spelling}"
    if not kept:
        return [Change(NEW, row.id, where)]
    if before is None:
        return [Change(ADDED, row.id)]
    changes = []
    if kind != remap.EXACT:
        changes.append(Change(REMAPPED, row.id, f"{where}: {kind} pair, was {before.spelling}"))
    moved = [f"{label} {old_tier} to {new_tier}" for label, old_tier, new_tier in
             (("meaning", before.tier, row.tier), ("spelling", before.spelling_tier, row.spelling_tier))
             if old_tier != new_tier]
    if moved:
        changes.append(Change(TIER, row.id, f"{where}: {', '.join(moved)}"))
    old_texts, new_texts = _texts(before.candidates), _texts(row.candidates)
    if old_texts != new_texts:
        added = [text for text in new_texts if text not in old_texts]
        removed = [text for text in old_texts if text not in new_texts]
        changes.append(Change(CANDIDATES, row.id, f"{where}: added {'; '.join(added) or 'none'}, removed "
                                                  f"{'; '.join(removed) or 'none'}" + ("" if added or removed
                                                                                       else ", order changed")))
    if before.fingerprint != row.fingerprint and not changes:
        changes.append(Change(RECHECKED, row.id))
    return changes


def _texts(candidates: str) -> list:
    return candidates.split("; ") if candidates else []


@dataclass(frozen=True)
class Commit:
    """One committed run."""
    generation: int
    rows: dict  # the new ledger by id
    decided: dict  # id -> its latest decision
    notes: list  # for the console


def commit(loaded, found, today: str) -> Commit:
    """Remap the coverage sites of FOUND (an inventory.Inventory) against the live state, give them ids, update the
    ledger and commit sites.csv with ledger.csv. Then write ledger-changes.md, inventory.csv and argmap-proposed.csv,
    and make a backup. LOADED: the configuration. TODAY: the date for the ledger."""
    folder = loaded.folder
    notes = state.recover(folder)
    live = state.read_state(folder)
    old = state.parse_sites(live.files[state.SITES]) if live and state.SITES in live.files else []
    old_ledger = parse_ledger(live.files[LEDGER]) if live and LEDGER in live.files else {}
    decided = decisions.latest(decisions.read_notes(folder / decisions.NOTES))
    found.previous = Counter(site.kind for site in old) if live else None
    covered = [record for record in found.records if record.covered]
    new = [remap.Site(record.owner, record.kind, record.target, record.slot, record.expression, record.value,
                      record.context, "", record.file, record.line, record.column) for record in covered]
    mapping = remap.remap(old, new, _revaluer(found, loaded.target.config.profile), loaded.scores())
    fresh, high_water = remap.mint(mapping.ids.count(""), state.highest_minted(folder, live))
    fresh = iter(fresh)
    for record, kept in zip(covered, mapping.ids):
        record.id = kept or next(fresh)
    sites = [remap.Site(site.owner, site.kind, site.target, site.slot, site.expression, site.value, site.context,
                        record.id, site.file, site.line, site.column) for site, record in zip(new, covered)]
    rows, changes = build(covered, mapping, old, old_ledger, loaded.fingerprint(), today, decided)
    generation = state.commit(folder, {state.SITES: state.format_sites(sites), LEDGER: format_ledger(rows)},
                              high_water)
    osutil.write_whole(folder / CHANGES, format_changes(changes, generation))
    inventory.write(folder, found, generation)
    kept = list(loaded.kept) + ([decisions.NOTES] if (folder / decisions.NOTES).is_file() else [])
    snapshot = state.backup(folder, loaded.backups, kept)
    notes.append(f"remap: {len(mapping.gone)} gone, {len(mapping.ambiguous)} ambiguous, "
                 f"{mapping.ids.count('')} new, {len(mapping.ids) - mapping.ids.count('')} kept")
    notes.append(f"backup: {snapshot}" if snapshot else "backup: unchanged since the latest snapshot")
    return Commit(generation, rows, decided, notes)


def _revaluer(found, profile):
    """An old site's value under the current rules: its expression evaluated with the target closures and converted
    like this run's sites at the same target and slot. "" when that is not possible."""
    headers = found.headers
    types = {(record.target, record.slot): record.result.ctype for record in found.records if record.result.ok}

    def revalue(site: remap.Site) -> str:
        ctype = types.get((site.target, site.slot))
        if ctype is None:
            return ""
        result = ceval.evaluate(site.expression, profile, expand=headers.expand, resolve=headers.resolve,
                                resolve_type=headers.resolve_type)
        return inventory.value_text(ceval.convert(result, ctype, profile)) if result.ok else ""

    return revalue


def format_changes(changes: list, generation: int) -> str:
    counts = Counter(change.kind for change in changes)
    lines = [f"# Ledger changes, generation {generation}", ""]
    lines += [f"- {kind}: {counts[kind]}" for kind in CHANGE_ORDER]
    for kind in CHANGE_ORDER:
        if kind in COUNT_ONLY or not counts[kind]:
            continue
        lines += ["", f"## {kind}", ""]
        lines += [f"- {change.id} {change.text}" for change in changes if change.kind == kind]
    return "\n".join(lines) + "\n"
