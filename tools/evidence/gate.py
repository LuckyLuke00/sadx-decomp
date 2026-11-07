"""The gate report, evidence/gate.md: the counts that decide whether the phase-1 model is good enough to build on.

The brake, one per site kind: when unresolved plus unevaluated sites are over the gate_brake share of the coverage
sites of a kind, the model needs fixing before anything is built on it. The first run of a kind is its baseline. The
share is a process brake, not a measured value. Incomplete searches with a cover are not in it, and the budget is
never raised to make A appear.

The other sections: the coverage split per kind (each split sums to its total), the counts out of coverage, the field
spots by what became of them (inventory step 7), the reference symbols (inventory step 8: the rows of each symbol
file, the sites per kind and their flags), the reference calls (pairs.py: per build the paired functions by what
became of them, the sites by the reference value, the verdict, and the sites whose value differs across builds), the
top unresolved identifiers of the sites and of the #if lines, per
umbrella the header reading counts and the expected names that do not resolve (evidence/expected-names.csv,
hand-owned: set,umbrella,name), the and-mask slots, the spelling section, the skipped modules, the baseline diff
causes, and the times.

The skipped modules: the yield probes that a run does not repeat, from evidence/probes.csv (hand-owned, optional:
module,sites,floor,verdict,date,method,note). A module whose probe found fewer than yield_floor sites is not built.

The spelling section: the top spelling per meaning tier, the eligibility per kind and per callee, per sample tree
the files, distinct files, files with calls, observations, failures and slots read and left out (corpus.py), the
lineage
histograms with the cut, and per manual the markers, index entries, kept and dropped sections and the top unknown
functions (manual.py).

Standard library only.
"""

import csv
import sys
import time
from collections import Counter
from dataclasses import dataclass
from pathlib import Path

import audit
import ceval
import inventory
import pairs
import score
import symbols

sys.path.append(str(Path(__file__).resolve().parents[1]))  # tools/, after the standard library
import osutil  # noqa: E402

GATE, EXPECTED, PROBES = "gate.md", "expected-names.csv", "probes.csv"
EXPECTED_COLUMNS = ("set", "umbrella", "name")
PROBE_COLUMNS = ("module", "sites", "floor", "verdict", "date", "method", "note")
TOP = 20


class GateError(Exception):
    """A hand-owned input of the gate is missing or malformed."""


def read_expected(path: Path) -> list[tuple]:
    """(header set, umbrella, name) rows of expected-names.csv."""
    if not path.is_file():
        raise GateError(f"missing hand-owned file {path}")
    with path.open(encoding="utf-8", newline="") as data:
        reader = csv.DictReader(data)
        if tuple(reader.fieldnames or ()) != EXPECTED_COLUMNS:
            raise GateError(f"{path}: the columns must be {','.join(EXPECTED_COLUMNS)}")
        return [(fields["set"], fields["umbrella"], fields["name"]) for fields in reader]


def read_probes(path: Path) -> list[dict]:
    """The rows of probes.csv, or [] when the file does not exist."""
    if not path.is_file():
        return []
    with path.open(encoding="utf-8", newline="") as data:
        reader = csv.DictReader(data)
        if tuple(reader.fieldnames or ()) != PROBE_COLUMNS:
            raise GateError(f"{path}: the columns must be {','.join(PROBE_COLUMNS)}")
        return list(reader)


def resolves(closure, name: str) -> bool:
    """NAME is a macro defined in every branch, a constant with a value, or a type, tag, function or variable, in
    CLOSURE."""
    if closure.is_defined(name) is True:
        return True
    if name in closure.constants:
        return closure.resolve(name).ok
    return any(name in table for table in (closure.typedefs, closure.functions, closure.variables, closure.tags,
                                           closure.type_names))


def matches(umbrella: str, wanted: str) -> bool:
    """The umbrella as config.json gives it (a name, or a path when the file exists), against an expected-names row:
    equal, or ending in the row's path."""
    umbrella, wanted = umbrella.replace("\\", "/"), wanted.replace("\\", "/")
    return umbrella == wanted or umbrella.endswith("/" + wanted)


def write(loaded, rows: list, found, generation: int, expected: list, probes: list, entries, samples,
          readings: list, ranked: list) -> list:
    """Runs the audit, then writes gate.md. FOUND: the inventory of this run. EXPECTED: the expected-names.csv rows.
    PROBES: the probes.csv rows. ENTRIES: the baseline diff, or None. SAMPLES: the corpus.Corpus. READINGS: the
    manual.Reading records. RANKED: the sites in review order (score.write). Returns the brakes."""
    start = time.perf_counter()
    hits = audit.audit(loaded.root)
    seconds = time.perf_counter() - start
    text, stop = report(found, generation, loaded.thresholds, expected, probes, {row.callee for row in rows},
                        entries, samples, readings, ranked, (hits, seconds))
    osutil.write_whole(loaded.folder / GATE, text)
    return stop


@dataclass(frozen=True)
class Brake:
    kind: str  # a site kind of inventory.KINDS
    coverage: int
    stopped: int  # unresolved plus unevaluated
    share: float
    limit: float

    @property
    def fired(self) -> bool:
        return self.coverage > 0 and self.share > self.limit


def covered_of(records: list, kind: str) -> list:
    """The coverage sites of one site kind."""
    return [record for record in records if record.covered and record.kind == kind]


def brakes(records: list, limit: float) -> list[Brake]:
    """One brake per site kind, in inventory.KINDS order, each on the sites of its kind only."""
    stops = []
    for kind in inventory.KINDS:
        covered = covered_of(records, kind)
        stopped = sum(1 for record in covered if record.result.status in (ceval.UNRESOLVED, ceval.UNSUPPORTED))
        stops.append(Brake(kind, len(covered), stopped, stopped / len(covered) if covered else 0.0, limit))
    return stops


def report(found, generation: int, thresholds: dict, expected: list, probes: list, mapped: set, entries: list,
           samples, readings: list, ranked: list, audit: tuple) -> tuple[str, list]:
    """FOUND: the inventory of this run. THRESHOLDS: the threshold table. MAPPED: the argmap callees. ENTRIES: the
    baseline diff, or None. EXPECTED, PROBES, SAMPLES, READINGS, RANKED: as write() takes them. AUDIT: (hits,
    seconds). Returns the text of gate.md and the brakes."""
    records = found.records
    stops = brakes(records, thresholds["gate_brake"])
    lines = [f"# Evidence gate, generation {generation}", "", score.NOTE, ""]
    lines += _brake(stops, found.previous)
    lines += _split(records)
    lines += _outside(found)
    lines += _fields(found)
    lines += _symbols(found)
    lines += _references(found)
    lines += _unresolved(found)
    lines += _umbrellas(found, expected)
    lines += _masks(records)
    lines += _spelling(ranked)
    lines += _trees(samples, mapped)
    lines += _lineage(samples, thresholds["lineage_cut"])
    lines += _manuals(readings)
    lines += _probes(probes)
    if entries is not None:
        lines += ["## Baseline diff", ""] + [f"- {side} {cause}: {count}" for (side, cause), count in
                                              sorted(Counter((entry.side, entry.cause) for entry in entries).items())]
        lines.append("")
    lines += _times(found, samples, audit)
    return "\n".join(lines), stops


def _brake(stops: list, previous) -> list:
    """A row per kind with coverage sites in this run or in the previous one. PREVIOUS: the coverage sites per kind
    of the previous run, or None on a first run. A kind that PREVIOUS lacks has its first run now."""
    lines = ["## Brake", "", f"- brake at {stops[0].limit:.0%} of the coverage sites of each kind: unresolved plus "
             "unevaluated", "", "| kind | coverage sites | change | unresolved plus unevaluated | verdict |",
             "|---|---|---|---|---|"]
    for stop in stops:
        known = previous is not None and stop.kind in previous
        if not stop.coverage and not known:
            continue
        change = f"previous run {previous[stop.kind]}, change {stop.coverage - previous[stop.kind]:+d}" if known \
            else "first run"
        verdict = "FIRED: fix the model before anything else" if stop.fired else "not fired"
        lines.append(f"| {stop.kind} | {stop.coverage} | {change} | {stop.stopped} ({stop.share:.1%}) | {verdict} |")
    return lines + [""]


def _split(records: list) -> list:
    """Per kind with coverage sites: its resolved sites by tier, then its unresolved and unevaluated sites by
    cause."""
    lines = ["## Coverage split", ""]
    for kind in inventory.KINDS:
        covered = covered_of(records, kind)
        if covered:
            lines += [f"### {kind}", "", *_kind_split(covered), ""]
    return lines


def _kind_split(covered: list) -> list:
    tiers = score.tier_counts(covered)
    resolved = [record for record in covered if record.result.ok]
    lines = [f"- coverage sites: {len(covered)}", f"- resolved: {len(resolved)}"]
    for tier in score.ORDER:
        if tier not in tiers or tier in (score.UNRESOLVED, score.UNEVALUATED):
            continue
        lines.append(f"  - {tier}: {tiers[tier]}")
        lines += [f"    - {key}: {count}" for key, count in sorted(tiers.items()) if key.startswith(tier + " ")
                  and tier in (score.A, score.B)]
    incomplete = sum(1 for record in resolved if record.search and record.search.incomplete)
    lines.append(f"  - searches that ran out of budget: {incomplete}")
    for status, label in ((ceval.UNRESOLVED, "unresolved"), (ceval.UNSUPPORTED, "unevaluated")):
        causes = Counter(record.result.cause for record in covered if record.result.status == status)
        lines.append(f"- {label}: {sum(causes.values())}")
        lines += [f"  - {cause}: {count}" for cause, count in sorted(causes.items(), key=lambda item: (-item[1],
                                                                                                    item[0]))]
    return lines


def _outside(found) -> list:
    nonconstant = Counter(record.result.cause for record in found.records
                          if not record.covered and record.kind == inventory.CALL)
    lines = ["## Out of coverage", "", f"- unmapped calls: {found.unmapped}",
             f"- function-like macro callees: {found.macro_calls}",
             f"- nonconstant arguments: {sum(nonconstant.values())}"]
    lines += [f"  - {cause}: {count}" for cause, count in sorted(nonconstant.items(), key=lambda item: (-item[1],
                                                                                                         item[0]))]
    lines.append(f"- unsupported files: {len(found.unsupported_files)}")
    lines += [f"  - {file}: {reason}" for file, reason in found.unsupported_files]
    return lines + [""]


def _fields(found) -> list:
    """The field spots: those that became field sites, in coverage or not, the scope sites, and those that became
    neither, by why."""
    counts = found.field_counts
    sites = [record for record in found.records
             if record.kind == inventory.FIELD and record.row.status not in symbols.STATUSES]
    covered = sum(1 for record in sites if record.covered)
    rows = f"- fieldmap rows: {len(found.field_rows)}" if found.field_rows else "- no fieldmap: no spot is a field site"
    return ["## Field spots", "", rows, f"- field spots: {counts['spots']}",
            f"  - field sites: {len(sites)} (in coverage {covered}, nonconstant value {len(sites) - covered})",
            f"  - scope sites (no fieldmap row, in a function with scope constants): {counts['scope sites']}",
            f"  - member with no fieldmap row: {counts['unmapped']}",
            f"  - base type unknown: {counts['untyped']}", f"  - bitfield: {counts['bitfields']}",
            f"- case labels: {counts['case labels']} (sites only in a function with scope constants), raw-offset "
            f"accesses: {counts['raw offsets']} (counted only)", ""]


def _symbols(found) -> list:
    """The reference symbols: what each symbol file holds, the sites of their rows per kind, and the flags."""
    lines = ["## Reference symbols", ""]
    if found.symbols is None:
        return lines + ["- no symbol files: no reference sites", ""]
    held = [record for record in found.records if record.row.status in symbols.STATUSES]
    kinds = Counter(record.kind for record in held)
    flags = Counter(flag for record in held for flag in record.flags)
    covered = sum(1 for record in held if record.covered)
    enums, scopes = found.symbols.enums, found.symbols.scopes
    lines += [f"- {symbols.PROTOTYPES}: functions {len(found.symbols.prototypes)}",
              f"- {symbols.ENUMS}: enums {len(enums)}, enumerators {sum(len(names) for names in enums.values())}",
              f"- {symbols.SCOPES}: constants {sum(len(constants) for constants in scopes.values())}, functions "
              f"{len(scopes)}",
              f"- sites: {len(held)} (in coverage {covered}, nonconstant value {len(held) - covered})"]
    lines += [f"  - {kind}: {kinds[kind]}" for kind in inventory.KINDS if kinds[kind]]
    lines.append(f"- flags: {symbols.ONE_ENUMERATOR} {flags[symbols.ONE_ENUMERATOR]}, {symbols.LVALUE_CHECK} "
                 f"{flags[symbols.LVALUE_CHECK]}")
    return lines + [""]


def _references(found) -> list:
    """The reference calls (pairs.py): per build its pairs, its paired functions by what became of them, the slots
    of the live functions, the coverage sites by the reference value, and whether the build gives evidence; then the
    sites whose value another build passes otherwise."""
    lines = ["## Reference calls", ""]
    if not found.references:
        return lines + ["- no reference call files: no reference evidence", ""]
    lines += ["| build | floats | pairs | dropped | unpaired | compared | no calls | no shared | killed few/low | "
              "live | slots agree/known | sites same/differ/unknown | verdict |",
              "|---|---|---|---|---|---|---|---|---|---|---|---|---|"]
    for report in found.references:
        verdict = "under the floor: no evidence" if report.under_floor else "used"
        lines.append(f"| {report.build} | {report.floats} | {report.pairs} | {report.dropped} | {report.unpaired} | "
                     f"{report.compared} | {report.no_calls} | {report.no_shared} | {report.few}/{report.low} | "
                     f"{report.live} | {report.agree}/{report.slots} | {report.same}/{report.differs}/{report.unknown} "
                     f"| {verdict} |")
    differ = [record for record in found.records if pairs.DIFFERS in record.flags]
    lines += ["", f"- sites with the flag {pairs.DIFFERS}: {len(differ)}"]
    for record in differ[:TOP]:
        builds = ", ".join(f"{build} same" if same else f"{build} {text}" for build, text, same in record.references)
        lines.append(f"  - {record.id} {record.file}:{record.line} {record.callee} slot {record.slot}: "
                     f"{record.value} ({builds})")
    return lines + [""]


def _unresolved(found) -> list:
    sites = Counter(record.result.detail for record in found.records
                    if record.result.status == ceval.UNRESOLVED and record.result.detail)
    conditions = Counter()
    for _, closure in found.closures:
        conditions.update(closure.diagnostics.unresolved_if)
    lines = ["## Top unresolved identifiers", ""]
    for label, counts in (("sites", sites), ("#if lines of all closures", conditions)):
        top = sorted(counts.items(), key=lambda item: (-item[1], item[0]))[:TOP]
        lines.append(f"- {label}: " + (", ".join(f"{name} {count}" for name, count in top) if top else "none"))
    return lines + [""]


def _umbrellas(found, expected: list) -> list:
    lines = ["## Umbrellas", "", "| set | umbrella | files | skipped declarations | unresolved #if identifiers | "
             "live #error | missing includes | expected names not resolved |", "|---|---|---|---|---|---|---|---|"]
    unknown = {f"{wanted_set} {umbrella}" for wanted_set, umbrella, _ in expected
               if not any(set_name == wanted_set and matches(closure.name, umbrella)
                          for set_name, closure in found.closures)}
    for set_name, closure in found.closures:
        notes = closure.diagnostics
        missed = [name for wanted_set, umbrella, name in expected if wanted_set == set_name
                  and matches(closure.name, umbrella) and not resolves(closure, name)]
        live = sum(1 for _, _, _, is_live in notes.errors if is_live)
        lines.append(f"| {set_name} | {Path(closure.name).name} | {len(closure.files)} | {len(notes.skipped)} | "
                     f"{len(notes.unresolved_if)} | {live} | {len(notes.missing)} | {' '.join(missed) or 'none'} |")
    if unknown:
        lines += ["", f"expected-names.csv names umbrellas that config.json lacks: {', '.join(sorted(unknown))}"]
    return lines + [""]


def _masks(records: list) -> list:
    masks = [record for record in records if record.covered and record.row.mode == "and-mask"]
    inverted = sum(1 for record in masks if record.search and any(item.inverted for item in record.search.candidates))
    none = sum(1 for record in masks if not (record.search and record.search.candidates))
    return ["## And-mask slots", "", f"- sites {len(masks)}, with an inverted candidate {inverted}, "
                                     f"with no candidate {none}", ""]


def _spelling(ranked: list) -> list:
    return ["## Spelling", "", "### Top candidates", "", *score.spelling_table(ranked), "", "### Eligibility", "",
            *score.eligibility_lines(ranked), ""]


def _trees(samples, mapped: set) -> list:
    """Per sample tree: the reading counts, the slots left out by reason and the failed files."""
    if not samples.trees:
        return ["### Sample trees", "", "- none configured", ""]
    observed = Counter(item.tree for item in samples.observations)
    lines = ["### Sample trees", "", "| tree | files | distinct | with calls | observations | failed | slots read | "
             "slots left out |", "|---|---|---|---|---|---|---|---|"]
    for name, tree in samples.trees.items():
        lines.append(f"| {name} | {tree.files} | {len(tree.nodes)} | {len(tree.call_nodes)} | {observed[name]} | "
                     f"{len(tree.failures)} | {len(tree.slots)} | {len(tree.left_out)} |")
    used = {item.callee for item in samples.observations}
    lines += ["", f"- argmap callees with an observation: {len(used & mapped)} of {len(mapped)}"]
    for name, tree in samples.trees.items():
        reasons = {}
        for (callee, slot), reason in sorted(tree.left_out.items()):
            reasons.setdefault(reason, []).append(f"{callee}#{slot}")
        lines += [f"- {name} left out, {reason}: {len(slots)} ({_capped(slots)})"
                  for reason, slots in sorted(reasons.items())]
        if tree.failures:
            lines.append(f"- {name} failed: {_capped([f'{file}: {reason}' for file, reason in tree.failures])}")
    return lines + [""]


def _capped(texts: list) -> str:
    return ", ".join(texts[:TOP]) + (", ..." if len(texts) > TOP else "")


def _lineage(samples, cut: float) -> list:
    """The two similarity histograms of corpus.Corpus.histograms, with the bin of the lineage cut marked."""
    same, other = samples.histograms()
    bins = len(same)
    edges = [f"{index / bins:.1f}" for index in range(bins)]
    edges[min(int(cut * bins), bins - 1)] += " (cut)"
    return ["### Lineage", "", f"Pairs of sample files that share an observation slot, by the lower edge of their "
            f"similarity bin. Files at or above the cut ({cut}) can share a lineage.", "",
            "| pairs | " + " | ".join(edges) + " |", "|---|" + "---|" * bins,
            "| same path | " + " | ".join(str(count) for count in same) + " |",
            "| other path | " + " | ".join(str(count) for count in other) + " |", ""]


def _manuals(readings: list) -> list:
    if not readings:
        return ["### Manuals", "", "- none configured", ""]
    lines = ["### Manuals", "", "| manual | markers | index entries | sections kept | dropped | top unknown |",
             "|---|---|---|---|---|---|"]
    for reading in readings:
        dropped = ", ".join(f"{reason} {count}" for reason, count in sorted(reading.dropped.items())) or "none"
        unknown = ", ".join(f"{name} {count}" for name, count in reading.unknown.most_common(5)) or "none"
        lines.append(f"| {'/'.join(Path(reading.path).parts[-2:])} | {reading.markers} | {reading.index} | "
                     f"{len(reading.sections)} | {dropped} | {unknown} |")
    return lines + [""]


def _probes(probes: list) -> list:
    if not probes:
        return ["## Skipped modules", "", "- none recorded", ""]
    return ["## Skipped modules", "", "| " + " | ".join(PROBE_COLUMNS) + " |", "|---" * len(PROBE_COLUMNS) + "|",
            *("| " + " | ".join(row[column] for column in PROBE_COLUMNS) + " |" for row in probes), ""]


def _times(found, samples, audit: tuple) -> list:
    hits, seconds = audit
    times = ", ".join(f"{name} {value:.1f} s" for name, value in found.seconds.items())
    return ["## Times", "", f"- inventory: {times}", "- closure cache: none in phase 1",
            f"- sample corpus: {samples.seconds:.1f} s", f"- audit: {seconds:.1f} s, {len(hits)} hits"
            + (f" ({', '.join(hits[:5])})" if hits else ""), ""]
