"""Unit tests for pipeline.py: one run end to end in a temp git repository, the faults that stop it before it writes,
the baseline diff when a baseline exists, and the out-of-date outputs.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/pipelinetests.py
run() calls every check and returns the failures. All names are made up.
"""

import contextlib
import dataclasses
import re
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import baseline  # noqa: E402
import baselinetests  # noqa: E402
import gate  # noqa: E402
import gatetests  # noqa: E402
import inventorytests  # noqa: E402
import outputs  # noqa: E402
import pipeline  # noqa: E402
import state  # noqa: E402
import osutil  # noqa: E402  (the modules put tools/ on the path)

DAY = "2026-01-01"


@contextlib.contextmanager
def workspace(fixture):
    """A temp git repository that the audit accepts, filled by FIXTURE (a tests module's repository function), with
    expected-names.csv. Yields the configuration and the argmap rows."""
    with osutil.foreign_repository(), tempfile.TemporaryDirectory() as temp:
        loaded, rows = fixture(temp)
        osutil.git(Path(temp), "init", "-q")
        (Path(temp) / ".gitignore").write_text("evidence/\n", encoding="utf-8")
        (loaded.folder / "denylist.txt").write_text("Leakword\n", encoding="utf-8")
        (loaded.folder / gate.EXPECTED).write_text(gatetests.EXPECTED, encoding="utf-8")
        yield loaded, rows


def check_missing_expected() -> list[str]:
    """A missing expected-names.csv stops the run before anything is written."""
    with workspace(inventorytests.repository) as (loaded, rows):
        (loaded.folder / gate.EXPECTED).unlink()
        try:
            pipeline.run(loaded, rows, DAY)
        except gate.GateError:
            written = (loaded.folder / "state").exists() or (loaded.folder / gate.GATE).exists()
            return ["the fault comes before anything is written"] if written else []
    return ["a missing expected-names.csv fails"]


def check_run() -> list[str]:
    """Two runs give generations 1 and 2, and every output carries the live generation."""
    failures = []
    with workspace(inventorytests.repository) as (loaded, rows):
        first = pipeline.run(loaded, rows, DAY)
        second = pipeline.run(loaded, rows, DAY)
        text = (loaded.folder / gate.GATE).read_text(encoding="utf-8")
        written = {Path(name).as_posix(): outputs.generation_of(loaded.folder / name) for name in pipeline.OUTPUTS}
    if (first.generation, second.generation) != (1, 2) or any(stop.fired for stop in first.stops):
        failures.append(f"runs {first.generation} and {second.generation}, brakes {first.stops}")
    if any(note.startswith("out of date") for note in second.notes):
        failures.append(f"nothing is out of date after a run: {second.notes}")
    if written != {name: None if name == baseline.DIFF.as_posix() else 2 for name in written}:
        failures.append(f"every output but the baseline diff carries generation 2: {written}")
    if "| call | 10 | previous run 10, change +0 |" not in text or "## Baseline diff" in text:
        failures.append("the second run shows the change; no baseline, no diff section")
    if not re.match(r"# Evidence gate, generation 2\n", text):
        failures.append("gate.md carries the generation")
    if "- audit: " not in text or "0 hits" not in text or "- none configured" not in text:
        failures.append("the audit time and hits, and no sample trees")
    return failures


def check_baseline() -> list[str]:
    """With a baseline, the run writes the diff and the confidence report lists its causes. Without it, the old diff
    is out of date."""
    failures = []
    with workspace(baselinetests.repository) as (loaded, rows):
        first = pipeline.run(loaded, rows, DAY)
        diff = (loaded.folder / baseline.DIFF).read_text(encoding="utf-8")
        confidence = (loaded.folder / "confidence.md").read_text(encoding="utf-8")
        ids = [line.rsplit(",", 1)[-1] for line in diff.split("\n")[2:] if line.startswith("new,")]
        (loaded.folder / baseline.BASELINE).unlink()
        later = pipeline.run(loaded, rows, DAY).notes
        live = state.read_state(loaded.folder).generation
    if first.generation != 1 or not diff.startswith("# evidence-baseline-diff generation=1\n"):
        failures.append(f"the diff carries the generation: {diff[:40]!r}")
    if "## Baseline diff causes" not in confidence:
        failures.append("confidence.md lists the diff causes")
    if not any(ids):
        failures.append("the new rows of the diff carry their ids")
    if any(note.startswith("out of date") for note in first.notes):
        failures.append(f"with a baseline nothing is out of date: {first.notes}")
    if f"baseline: 1 old rows unexplained, see {baseline.DIFF.as_posix()}" not in first.notes:
        failures.append(f"the unexplained old rows reach the notes: {first.notes}")
    if f"out of date: {baseline.DIFF.as_posix()}" not in later or live != 2:
        failures.append(f"a diff from an earlier generation is out of date: {later}")
    return failures


def check_warnings() -> list[str]:
    """An argmap callee that matches no function and no declaration reaches the console notes."""
    with workspace(inventorytests.repository) as (loaded, rows):
        stray = dataclasses.replace(rows[0], callee="xxStray", line=99)
        notes = pipeline.run(loaded, rows + [stray], DAY).notes
    wanted = "warning: argmap callee xxStray matches no function in the sources and no header declaration"
    return [] if wanted in notes else [f"argmap warnings reach the notes: {notes}"]


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_missing_expected, check_run, check_baseline, check_warnings):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    print("\n".join(found) or "pipelinetests: all passed")
    sys.exit(1 if found else 0)
