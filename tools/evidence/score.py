"""Meaning tiers for the coverage sites: review priority from the evidence the inventory found. Tiers are not
probabilities and not rename permission.

Each candidate of a site gets a tier, and the site gets the tier of its top candidate:
- A: the row is a header-prototype argmap row that passed the prototype check, a header-declaration fieldmap row
  that passed the member check, or a reference-symbol row (symbols.py) that passed its check; the value is ok, the
  search is complete and no candidate name sits in an unresolved branch. A scope site needs the flag "lvalue check";
  without it, it is B ("scope value only");
- A*: A with counterevidence; shown apart, never eligible;
- B: as A, from an unverified row, a row whose prototype or member check failed, or a field site that its member name
  alone types;
- C: a candidate name whose definition sits in an unresolved branch or has several alternatives.
A site with no tier from a candidate gets one from its status: incomplete with cover (the budget ran out after a
cover was found), no candidate (resolved, nothing found, or a slot type with no search), unresolved, unevaluated.
A placeholder site gets the tier placeholder. It is never eligible and has a list of its own.

Counterevidence for a candidate: another closure or profile gives one of its names another value; a name with no
accepted origin. For the site: the target closures disagree on a name of the expression; a target prototype spells
the slot otherwise; a body of the row's header in another closure gives the member another type; a paired function
of a reference build passes another value at the slot (pairs.py).

Eligible for review: meaning A, top spelling A or B (spelling.py), and the ledger status open or stale. A site with
the flag "one enumerator" and meaning A is eligible in an open or stale status without spelling support: an enum
slot under C++ takes no plain integer, so the original spelled a name or a cast. Any other site whose slot no sample
tree reads can never get sample support, so it is not eligible by construction ("no sample"). Eligible is not
confirmed.

write() puts the coverage sites in review order into confidence.csv (one row per site), candidates.csv (every
candidate, ranked, with its spelling tier and the aliases of its terms) and confidence.md (the tiers, the top spelling per meaning tier, the
eligibility per callee, the rollup by target, slot and value, the placeholders per macro, and the baseline diff
causes). The column "list" names the review list of each site: review, reference or placeholder. The reference list
holds the open or stale sites of meaning A whose top candidate has a reference origin, in this order: one enumerator,
then the lvalue check, then the sites with the same target, slot and value (most first), then id.

Standard library only.
"""

import sys
from collections import Counter
from dataclasses import dataclass
from pathlib import Path

import argmap
import ceval
import decisions
import fields
import inventory
import outputs
import pairs
import remap
import spelling
import symbols

sys.path.append(str(Path(__file__).resolve().parents[1]))  # tools/, after the standard library
import osutil  # noqa: E402

A, A_STAR, B, C = "A", "A*", "B", "C"
INCOMPLETE, NO_CANDIDATE, UNRESOLVED, UNEVALUATED = ("incomplete with cover", "no candidate", "unresolved",
                                                    "unevaluated")
PLACEHOLDER = "placeholder"
ORDER = (A, A_STAR, B, C, INCOMPLETE, UNEVALUATED, UNRESOLVED, NO_CANDIDATE, PLACEHOLDER)  # the review order of tiers
REVIEW_LIST, REFERENCE_LIST, PLACEHOLDER_LIST = "review", "reference", "placeholder"
LISTS = (REVIEW_LIST, REFERENCE_LIST, PLACEHOLDER_LIST)  # the review lists, in review order
SITE_COUNTER_FLAGS = ("closures disagree", "target prototype differs", "target member differs", pairs.DIFFERS)
UNVERIFIED_ROW, CHECK_FAILED, MEMBER_CHECK_FAILED = "unverified row", "prototype check failed", "member check failed"
SCOPE_ONLY = "scope value only"  # why B: a scope site that does not pass the lvalue check
VERIFIED = (argmap.HEADER_PROTOTYPE, fields.HEADER_DECLARATION, *symbols.STATUSES)  # the row statuses that can give A
NOTE = ("Eligible for review: meaning A, top spelling A or B, status open or stale. A site of meaning A whose top "
        "candidate is one enumerator alone (an enum slot under C++, which takes no plain integer) is eligible without "
        "spelling. Eligible is not confirmed. Any other site whose slot no sample tree reads is not eligible by "
        "construction (no sample). A comes from argmap header-prototype rows, fieldmap header-declaration rows and "
        "the reference symbols, so a thin A list is expected. Reference names and placeholder sites have lists of "
        "their own.")


@dataclass(frozen=True)
class Grade:
    tier: str
    counter: tuple = ()  # counterevidence texts
    reason: str = ""  # why B: an unverified row, a failed prototype or member check, or the member name only
    origins: tuple = ()  # the origins of the candidate's names


def grade_site(record) -> Grade:
    """The tier of a coverage site: its top candidate's, else its status's."""
    if record.kind == inventory.PLACEHOLDER:
        return Grade(PLACEHOLDER)
    result, search = record.result, record.search
    if result.status == ceval.UNRESOLVED:
        return Grade(UNRESOLVED)
    if result.status == ceval.UNSUPPORTED:
        return Grade(UNEVALUATED)
    if search is None or not search.candidates:
        return Grade(NO_CANDIDATE)
    if search.incomplete:
        return Grade(INCOMPLETE, origins=_origins(search.candidates[0]))
    return grade_candidate(record, search.candidates[0])


def grade_candidate(record, candidate) -> Grade:
    aliases = [alias for node in candidate.terms for alias in node.aliases]
    counter = [flag for flag in SITE_COUNTER_FLAGS if flag in record.flags]
    pool = record.pool
    counter += [f"{alias.name}: {pool.disputed[alias.name]}" for alias in aliases if alias.name in pool.disputed]
    if record.accepted:
        counter += [f"{alias.name}: origin {' '.join(alias.origins)} not accepted" for alias in aliases
                    if not set(alias.origins) & set(record.accepted)]
    origins = _origins(candidate)
    if any(alias.name in pool.uncertain for alias in aliases):
        return Grade(C, tuple(counter), origins=origins)
    reason = _reason(record)
    if reason:
        return Grade(B, tuple(counter), reason, origins)
    return Grade(A_STAR if counter else A, tuple(counter), origins=origins)


def _reason(record) -> str:
    if record.row.status not in VERIFIED:
        return UNVERIFIED_ROW
    if not record.check.passed:
        return MEMBER_CHECK_FAILED if record.kind == inventory.FIELD else CHECK_FAILED
    if record.row.status == symbols.REFERENCE_SCOPE and symbols.LVALUE_CHECK not in record.flags:
        return SCOPE_ONLY
    return inventory.MEMBER_NAME_ONLY if inventory.MEMBER_NAME_ONLY in record.flags else ""


def _origins(candidate) -> tuple:
    return tuple(sorted({origin for node in candidate.terms for alias in node.aliases for origin in alias.origins}))


def tier_counts(records: list) -> Counter:
    """The tiers of the coverage sites, with B split by reason and A by origin: keys like "B unverified row" and
    "A crt"."""
    counts = Counter()
    for record in records:
        if not record.covered:
            continue
        found = grade_site(record)
        counts[found.tier] += 1
        if found.tier == B:
            counts[f"{B} {found.reason}"] += 1
        if found.tier == A:
            counts[f"{A} {' '.join(found.origins) or 'no origin'}"] += 1
    return counts


# Outputs

CONFIDENCE, CONFIDENCE_MD, CANDIDATES = "confidence.csv", "confidence.md", "candidates.csv"
CONFIDENCE_COLUMNS = ("id", "eligible", "meaning", "spelling", "sites", "target", "slot", "callee", "argument",
                      "value", "status", "top", "reason", "counter", "origins", "samples", "decision", "flags", "file",
                      "line", "list")
CANDIDATE_COLUMNS = ("id", "rank", "name", "meaning", "spelling", "origins", "aliases")
ALIAS_JOIN = "="  # joins the aliases of one term in the aliases column; a space separates the terms
YES, NO, NO_SAMPLE = "yes", "no", "no sample"
ELIGIBILITY = (YES, NO, NO_SAMPLE)
ELIGIBLE_SPELLINGS = (spelling.A, spelling.B)
REVIEW_STATUSES = (inventory.OPEN, decisions.STALE)  # the ledger statuses that come into review


@dataclass(frozen=True)
class Ranked:
    record: object
    grade: Grade
    sites: int  # the coverage sites with the same target, slot and value
    top: spelling.Spelling  # the top candidate's spelling
    status: str  # the ledger status
    eligible: str  # YES, NO or NO_SAMPLE
    review_list: str  # one of LISTS


def group_key(record) -> tuple:
    """Target, slot and value; the expression stands in for a value the site does not have."""
    return record.target, record.slot, record.value or f"expression {record.expression}"


def eligibility(record, grade: Grade, top: spelling.Spelling, status: str) -> str:
    """YES for meaning A in a status that comes into review, with top spelling A or B or with the flag "one
    enumerator"; else NO_SAMPLE when no sample tree reads the slot, else NO. A placeholder site is never eligible."""
    if record.kind == inventory.PLACEHOLDER:
        return NO
    if grade.tier == A and symbols.ONE_ENUMERATOR in record.flags and status in REVIEW_STATUSES:
        return YES
    if not record.sampled:
        return NO_SAMPLE
    if grade.tier == A and top.tier in ELIGIBLE_SPELLINGS and status in REVIEW_STATUSES:
        return YES
    return NO


def review_order(records: list, rows: dict) -> list[Ranked]:
    """The coverage sites in review order: by list (the reference list by its own flags first), eligible first, then
    meaning tier, top spelling tier, sites with the same target, slot and value (most first) and id. ROWS: the ledger
    by id, for the statuses."""
    covered = [record for record in records if record.covered]
    sites = Counter(group_key(record) for record in covered)
    ranked = []
    for record in covered:
        grade, top, status = grade_site(record), spelling.top_of(record.spellings), rows[record.id].status
        ranked.append(Ranked(record, grade, sites[group_key(record)], top, status,
                             eligibility(record, grade, top, status), review_list(record, grade, status)))
    return sorted(ranked, key=lambda item: (LISTS.index(item.review_list), _reference_rank(item),
                                            item.eligible != YES,
                                            ORDER.index(item.grade.tier),
                                            spelling.ORDER.index(item.top.tier), -item.sites,
                                            remap.id_number(item.record.id)))


def review_list(record, grade: Grade, status: str) -> str:
    """PLACEHOLDER_LIST for a placeholder site; REFERENCE_LIST for meaning A from a name of reference origin, in a
    status that comes into review; else REVIEW_LIST."""
    if record.kind == inventory.PLACEHOLDER:
        return PLACEHOLDER_LIST
    if grade.tier == A and symbols.REFERENCE in grade.origins and status in REVIEW_STATUSES:
        return REFERENCE_LIST
    return REVIEW_LIST


def _reference_rank(item: Ranked) -> tuple:
    """Within the reference list: one enumerator first, then the lvalue check. () on the other lists."""
    if item.review_list != REFERENCE_LIST:
        return ()
    return symbols.ONE_ENUMERATOR not in item.record.flags, symbols.LVALUE_CHECK not in item.record.flags


def confidence_rows(ranked: list[Ranked], decided: dict) -> list[tuple]:
    """One row per site. DECIDED: id -> its latest decision."""
    rows = []
    for item in ranked:
        record, grade = item.record, item.grade
        search, decision = record.search, decided.get(record.id)
        rows.append((record.id, item.eligible, grade.tier, item.top.tier, item.sites, record.target, record.slot,
                     record.callee, record.argument, record.value, item.status,
                     search.candidates[0].text if search and search.candidates else "", grade.reason,
                     "; ".join(grade.counter), " ".join(grade.origins), item.top.text if record.spellings else "",
                     decisions.describe(decision) if decision else "", " ".join(record.flags), record.file,
                     record.line, item.review_list))
    return rows


def candidate_rows(ranked: list[Ranked]) -> list[tuple]:
    """Every candidate of every site, in review order, then rank, with its own spelling tier. An incomplete search
    gives its candidates the meaning tier incomplete with cover."""
    rows = []
    for item in ranked:
        record = item.record
        search = record.search
        for rank, candidate in enumerate(search.candidates if search else (), start=1):
            tier = INCOMPLETE if search.incomplete else grade_candidate(record, candidate).tier
            spelled = record.spellings[rank - 1].tier if record.spellings else spelling.NONE
            rows.append((record.id, rank, candidate.text, tier, spelled, " ".join(_origins(candidate)),
                         alias_column(candidate)))
    return rows


def alias_column(candidate) -> str:
    """The aliases column of CANDIDATE: its terms in the order of its text, each as its aliases joined by ALIAS_JOIN."""
    return " ".join(ALIAS_JOIN.join(alias.name for alias in node.aliases) for node in candidate.terms)


def read_aliases(folder: Path, generation: int, site_id: str) -> dict:
    """Candidate text -> its alias groups, one tuple of names per term, of each candidate of SITE_ID in FOLDER's
    candidates.csv, which GENERATION must have written."""
    path = folder / CANDIDATES
    if outputs.generation_of(path) != generation:
        raise decisions.DecisionError(f"{path} is not from generation {generation}: run the tool first")
    return {values["name"]: tuple(tuple(group.split(ALIAS_JOIN)) for group in values["aliases"].split())
            for _, values in outputs.read_rows(path, CANDIDATE_COLUMNS, decisions.DecisionError, skip=1)
            if values["id"] == site_id}


def spelling_table(ranked: list[Ranked]) -> list[str]:
    """A table of the sites with a candidate: meaning tier against the top candidate's spelling tier."""
    counts = Counter((item.grade.tier, item.top.tier) for item in ranked if item.record.spellings)
    lines = ["| meaning | " + " | ".join(spelling.ORDER) + " |", "|---|" + "---|" * len(spelling.ORDER)]
    for tier in ORDER:
        if any(counts[tier, spelled] for spelled in spelling.ORDER):
            lines.append(f"| {tier} | " + " | ".join(str(counts[tier, spelled]) for spelled in spelling.ORDER) + " |")
    return lines


def eligibility_lines(ranked: list[Ranked]) -> list[str]:
    """The eligibility counts per site kind, then a table of them per callee."""
    per_kind, per_callee = {}, {}
    for item in ranked:
        per_kind.setdefault(item.record.kind, Counter())[item.eligible] += 1
        per_callee.setdefault(item.record.callee, Counter())[item.eligible] += 1
    lines = [f"- {kind}: " + ", ".join(f"{label} {per_kind[kind][label]}" for label in ELIGIBILITY)
             for kind in inventory.KINDS if kind in per_kind]
    lines += ["", "| callee | " + " | ".join(ELIGIBILITY) + " |", "|---|" + "---|" * len(ELIGIBILITY)]
    lines += [f"| {callee} | " + " | ".join(str(counts[label]) for label in ELIGIBILITY) + " |"
              for callee, counts in sorted(per_callee.items())]
    return lines


def reference_lines(items: list[Ranked]) -> list[str]:
    """The reference list: its sites per flag, then a table per target, slot and value in list order."""
    one = sum(symbols.ONE_ENUMERATOR in item.record.flags for item in items)
    passed = sum(symbols.LVALUE_CHECK in item.record.flags for item in items)
    lines = [f"- sites: {len(items)}; {symbols.ONE_ENUMERATOR} {one}; {symbols.LVALUE_CHECK} {passed}", "",
             "| kind | callee | slot | value | sites | flags | top candidate |", "|---|---|---|---|---|---|---|"]
    groups = {}
    for item in items:
        groups.setdefault(group_key(item.record), []).append(item)
    for held in groups.values():
        first = held[0].record
        flags = " ".join(flag for flag in (symbols.ONE_ENUMERATOR, symbols.LVALUE_CHECK) if flag in first.flags)
        lines.append(f"| {first.kind} | {first.callee} | {first.slot} | {group_key(first)[2]} | {len(held)} | "
                     f"{flags} | {first.search.candidates[0].text} |")
    return lines


def placeholder_lines(items: list[Ranked]) -> list[str]:
    """The placeholder kinds, then a table per macro: its kind, its sites, their ledger statuses and their flags."""
    lines = [f"- {kind}: {note}" for kind, note in inventory.PLACEHOLDER_NOTES.items()]
    lines += ["", "| macro | kind | sites | statuses | flags |", "|---|---|---|---|---|"]
    macros = {}
    for item in items:
        macros.setdefault(item.record.target, []).append(item)
    for macro, held in sorted(macros.items()):
        statuses = Counter(item.status for item in held)
        flags = Counter(flag for item in held for flag in item.record.flags)
        lines.append(f"| {macro} | {held[0].record.row.note} | {len(held)} | "
                     + ", ".join(f"{status} {count}" for status, count in sorted(statuses.items())) + " | "
                     + ", ".join(f"{flag} {count}" for flag, count in sorted(flags.items())) + " |")
    return lines


def summary_text(records: list, ranked: list[Ranked], generation: int, entries) -> str:
    """confidence.md: the tiers, the rollup by target, slot and value, the placeholders, and the baseline diff causes
    when ENTRIES is not None."""
    placeholders = [item for item in ranked if item.review_list == PLACEHOLDER_LIST]
    references = [item for item in ranked if item.review_list == REFERENCE_LIST]
    graded = [item for item in ranked if item.review_list != PLACEHOLDER_LIST]
    ranked = [item for item in ranked if item.review_list == REVIEW_LIST]
    lines = [f"# Confidence, generation {generation}", "", NOTE, "", "## Tiers", ""]
    tiers = tier_counts(records)
    by_origin = Counter(" ".join(item.grade.origins) or "no origin" for item in graded if item.grade.tier == B)
    for tier in ORDER:
        if tier not in tiers:
            continue
        lines.append(f"- {tier}: {tiers[tier]}")
        if tier in (A, B):
            lines += [f"  - {key[len(tier) + 1:]}: {count}" for key, count in sorted(tiers.items())
                      if key.startswith(tier + " ")]
        if tier == B:
            lines += [f"  - origins {origins}: {count}" for origins, count in sorted(by_origin.items())]
    lines += ["", "## Spelling of the top candidates", "", *spelling_table(graded), "", "## Eligibility", "",
              *eligibility_lines(graded)]
    lines += ["", "## By target, slot and value", "",
              "| callee | slot | value | sites | tiers | spelling | top candidate |", "|---|---|---|---|---|---|---|"]
    groups = {}
    for item in ranked:
        groups.setdefault(group_key(item.record), []).append(item)
    for items in groups.values():
        first = items[0].record
        counts = Counter(item.grade.tier for item in items)
        top = first.search.candidates[0].text if first.search and first.search.candidates else ""
        lines.append(f"| {first.callee} | {first.slot} | {group_key(first)[2]} | {len(items)} | "
                     + ", ".join(f"{tier} {counts[tier]}" for tier in ORDER if counts[tier])
                     + f" | {items[0].top.tier} | {top} |")
    if references:
        lines += ["", "## Reference names", "", *reference_lines(references)]
    if placeholders:
        lines += ["", "## Placeholders", "", *placeholder_lines(placeholders)]
    if entries is not None:
        lines += ["", "## Baseline diff causes", ""]
        lines += [f"- {side} {cause}: {count}" for (side, cause), count in
                  sorted(Counter((entry.side, entry.cause) for entry in entries).items())]
    return "\n".join(lines) + "\n"


def write(folder, records: list, generation: int, entries, rows: dict, decided: dict) -> list[Ranked]:
    """confidence.csv, candidates.csv and confidence.md in FOLDER. ENTRIES: the baseline diff, or None. ROWS: the
    ledger by id. DECIDED: id -> its latest decision. Returns the sites in review order."""
    ranked = review_order(records, rows)
    osutil.write_whole(folder / CONFIDENCE, outputs.csv_text("evidence-confidence", generation, CONFIDENCE_COLUMNS,
                                                             confidence_rows(ranked, decided)))
    osutil.write_whole(folder / CANDIDATES, outputs.csv_text("evidence-candidates", generation, CANDIDATE_COLUMNS,
                                                             candidate_rows(ranked)))
    osutil.write_whole(folder / CONFIDENCE_MD, summary_text(records, ranked, generation, entries))
    return ranked
