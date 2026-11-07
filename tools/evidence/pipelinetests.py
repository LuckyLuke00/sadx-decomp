"""Unit tests for pipeline.py: one run end to end in a temp git repository, the faults that stop it before it writes,
the baseline diff when a baseline exists, and the out-of-date outputs.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/pipelinetests.py
run() calls every check and returns the failures. All names are made up.
"""

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


def audited(root: Path) -> None:
    """Make ROOT a git repository that the audit accepts."""
    osutil.git(root, "init", "-q")
    (root / ".gitignore").write_text("evidence/\n", encoding="utf-8")
    (root / "evidence" / "denylist.txt").write_text("Leakword\n", encoding="utf-8")


def check_run() -> list[str]:
    """A missing expected-names.csv stops the run before anything is written; two runs give generations 1 and 2, and
    every output carries the live generation."""
    failures = []
    with osutil.foreign_repository(), tempfile.TemporaryDirectory() as temp:
        root = Path(temp)
        loaded, rows = inventorytests.repository(temp)
        audited(root)
        try:
            pipeline.run(loaded, rows, DAY)
            failures.append("a missing expected-names.csv fails")
        except gate.GateError:
            if (root / "evidence" / "state").exists() or (root / "evidence" / gate.GATE).exists():
                failures.append("the fault comes before anything is written")
        (root / "evidence" / gate.EXPECTED).write_text(gatetests.EXPECTED, encoding="utf-8")
        first = pipeline.run(loaded, rows, DAY)
        second = pipeline.run(loaded, rows, DAY)
        text = (root / "evidence" / gate.GATE).read_text(encoding="utf-8")
        written = {Path(name).as_posix(): outputs.generation_of(root / "evidence" / name) for name in pipeline.OUTPUTS}
    if (first[1], second[1]) != (1, 2) or any(stop.fired for stop in first[0]):
        failures.append(f"runs {first[:2]} {second[:2]}")
    if any(note.startswith("out of date") for note in second[2]):
        failures.append(f"nothing is out of date after a run: {second[2]}")
    if written != dict({name: 2 for name in written}, **{baseline.DIFF.as_posix(): None}):
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
    with osutil.foreign_repository(), tempfile.TemporaryDirectory() as temp:
        root = Path(temp)
        loaded, rows = baselinetests.repository(temp)
        audited(root)
        (root / "evidence" / gate.EXPECTED).write_text(gatetests.EXPECTED, encoding="utf-8")
        _, generation, notes = pipeline.run(loaded, rows, DAY)
        diff = (loaded.folder / baseline.DIFF).read_text(encoding="utf-8")
        confidence = (loaded.folder / "confidence.md").read_text(encoding="utf-8")
        ids = [line.rsplit(",", 1)[-1] for line in diff.split("\n")[2:] if line.startswith("new,")]
        (loaded.folder / baseline.BASELINE).unlink()
        _, _, later = pipeline.run(loaded, rows, DAY)
        live = state.read_state(loaded.folder).generation
    if generation != 1 or not diff.startswith("# evidence-baseline-diff generation=1\n"):
        failures.append(f"the diff carries the generation: {diff[:40]!r}")
    if "## Baseline diff causes" not in confidence:
        failures.append("confidence.md lists the diff causes")
    if not any(ids):
        failures.append("the new rows of the diff carry their ids")
    if any(note.startswith("out of date") for note in notes):
        failures.append(f"with a baseline nothing is out of date: {notes}")
    if f"out of date: {baseline.DIFF.as_posix()}" not in later or live != 2:
        failures.append(f"a diff from an earlier generation is out of date: {later}")
    return failures


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_run, check_baseline):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    print("\n".join(found) or "pipelinetests: all passed")
    sys.exit(1 if found else 0)
