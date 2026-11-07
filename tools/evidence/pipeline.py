"""One run of the evidence tool, in order:

1. read the hand-owned inputs that the run needs: expected-names.csv, and probes.csv and baseline-inventory.csv when
   they exist;
2. in memory: the inventory of the game source (inventory.py), the reference calls of other builds (pairs.py), the
   sample corpus with the sample columns of the proposals (corpus.py), the manuals (manual.py), and the spelling of
   each candidate (spelling.py);
3. the commit: sites, ids and the ledger as one state generation, then ledger-changes.md, inventory.csv and
   argmap-proposed.csv (ledger.py); then diagnostics/sample-calls.csv (corpus.py);
4. the baseline diff, when a baseline exists (baseline.py);
5. the tiers and the eligibility in review order: confidence.csv, candidates.csv, confidence.md (score.py);
6. the audit and the gate report, gate.md (gate.py);
7. the check for out-of-date outputs: an output whose first line names another generation than the live one.

A fault in steps 1 and 2 stops the run before anything is written.

Standard library only.
"""

import baseline
import corpus
import gate
import inventory
import ledger
import manual
import outputs
import pairs
import score
import spelling

OUTPUTS = (inventory.INVENTORY, inventory.PROPOSED, ledger.CHANGES, score.CONFIDENCE, score.CANDIDATES,
           score.CONFIDENCE_MD, gate.GATE, baseline.DIFF, corpus.SAMPLE_CALLS)


def run(loaded, rows: list, today: str) -> tuple:
    """LOADED: the configuration. ROWS: the argmap rows. TODAY: the date for the ledger. Returns the brakes, the
    generation and the notes for the console."""
    folder = loaded.folder
    expected = gate.read_expected(folder / gate.EXPECTED)
    probes = gate.read_probes(folder / gate.PROBES)
    has_baseline = (folder / baseline.BASELINE).is_file()
    old_rows = baseline.read_baseline(folder / baseline.BASELINE, baseline.prefix(loaded)) if has_baseline else None
    found = inventory.build(loaded, rows)
    found.references = pairs.apply(pairs.load(folder), found, loaded.thresholds)
    samples = corpus.read(loaded, found)
    found.proposed = corpus.sampled_proposals(samples, found.proposed)
    readings = manual.read(loaded, found)
    spelling.assign(found.records, spelling.Speller(samples, manual.by_function(readings), loaded.thresholds))
    made = ledger.commit(loaded, found, today)
    generation = made.generation
    corpus.write(folder, samples, generation)
    entries = baseline.explain(found, old_rows, loaded, rows, generation) if has_baseline else None
    ranked = score.write(folder, found.records, generation, entries, made.rows, made.decided)
    stops = gate.write(loaded, rows, found, generation, expected, probes, entries, samples, readings, ranked)
    notes = made.notes + corpus.summary(samples)
    notes += [f"out of date: {name}" for name in outputs.stale(folder, OUTPUTS, generation)]
    if entries is not None and baseline.unexplained(entries):
        notes.append(f"baseline: {baseline.unexplained(entries)} old rows unexplained, see {baseline.DIFF.as_posix()}")
    return stops, generation, notes
