"""Unit tests for state.py: sites.csv, the high-water mark, generations and backups. Each check works in a temp folder.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/statetests.py
run() calls every check and returns the failures. All names are made up.
"""

import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import remap  # noqa: E402
import state  # noqa: E402
from remap import Site  # noqa: E402
from state import STATE, StateError  # noqa: E402

SITES = [
    Site("0x00401000", "call", "f", "1", "0", "0", "c1", "S000001", "a.c", 10, 5),
    Site("0x00401000", "call", "g", "outer#2/g#1", 'A | "x,y"', "48", "c2", "S000002", "a.c", 11, 9),
    Site("b.c#table", "call", "h", "1", "é", "", "", "S000003", "b.c", 3, 1),
]


def fault(action) -> str:
    """The StateError text ACTION raises, or "" when it raises none."""
    try:
        action()
    except StateError as error:
        return str(error)
    return ""


def check_sites_file() -> list[str]:
    failures = []
    data = state.format_sites(SITES)
    lines = data.decode("utf-8").split("\n")
    if lines[0] != "# evidence-sites schema=1" or lines[1] != ",".join(state.SITE_COLUMNS):
        failures.append(f"sites header {lines[:2]}")
    if [line.split(",")[2] for line in lines[2:5]] != ["1", "2", "1"]:
        failures.append(f"ordinals in {lines[2:5]}")
    if state.parse_sites(data) != SITES:
        failures.append(f"round trip gave {state.parse_sites(data)}")
    if state.parse_sites(state.format_sites([])) != []:
        failures.append("an empty sites file")
    for text, wanted in ((b"id,owner\n", "not a sites file"), (b"# evidence-sites schema=2\n", "sites schema 2")):
        if wanted not in fault(lambda: state.parse_sites(text)):
            failures.append(f"parse_sites({text!r}) did not fail with {wanted!r}")
    return failures


def check_generations() -> list[str]:
    failures = []
    with tempfile.TemporaryDirectory() as temp:
        folder = Path(temp)
        if state.read_state(folder) is not None or state.recover(folder):
            failures.append("a new folder has a state")
        for number in (1, 2, 3):
            if state.commit(folder, {"sites.csv": f"run {number}\n".encode()}, number * 10) != number:
                failures.append(f"commit {number}")
        live = state.read_state(folder)
        if live != state.State(3, {"sites.csv": b"run 3\n"}, 30):
            failures.append(f"live state {live}")
        if state._numbered(folder / STATE) != [2, 3]:
            failures.append(f"generations kept {state._numbered(folder / STATE)}")
        if state.read_high_water(folder) != 30:
            failures.append(f"high water {state.read_high_water(folder)}")
        (folder / STATE / "4").mkdir()  # a run stopped before its commit
        (folder / STATE / "4" / "sites.csv").write_bytes(b"half")
        (folder / STATE / "1").mkdir()  # a run stopped before it cleared the old generations
        notes = state.recover(folder)
        if len(notes) != 2 or state._numbered(folder / STATE) != [2, 3] or state.read_state(folder) != live:
            failures.append(f"recover gave {notes}, kept {state._numbered(folder / STATE)}")
        (folder / STATE / "4").mkdir()
        if "another run" not in fault(lambda: state.commit(folder, {}, 30)):
            failures.append("commit over a partial folder")
    return failures


def check_faults() -> list[str]:
    failures = []
    with tempfile.TemporaryDirectory() as temp:
        folder = Path(temp)
        state.commit(folder, {"sites.csv": b"one\n", "ledger.csv": b"two\n"}, 2)
        (folder / STATE / "1" / "ledger.csv").write_bytes(b"edited\n")
        if "ledger.csv does not match" not in fault(lambda: state.read_state(folder)):
            failures.append("a hand edit was not caught")
        (folder / STATE / "1" / "ledger.csv").unlink()
        if "ledger.csv is missing" not in fault(lambda: state.read_state(folder)):
            failures.append("a lost file was not caught")
        (folder / STATE / "1" / state.MANIFEST).write_text("{")
        if "is not JSON" not in fault(lambda: state.read_state(folder)):
            failures.append("a torn manifest was not caught")
        (folder / STATE / state.CURRENT).write_text("x\n")
        if "not a number" not in fault(lambda: state.read_state(folder)):
            failures.append("a bad CURRENT was not caught")
        (folder / STATE / state.CURRENT).unlink()
        if "has no CURRENT" not in fault(lambda: state.read_state(folder)):
            failures.append("a lost CURRENT was not caught")
        (folder / state.HIGH_WATER).write_text("7\n")
        if state.raise_high_water(folder, 3) != 7 or state.raise_high_water(folder, 9) != 9:
            failures.append("the high-water mark went down")
    return failures


def check_backups() -> list[str]:
    failures = []
    with tempfile.TemporaryDirectory() as temp:
        folder, destination = Path(temp) / "evidence", Path(temp) / "backups"
        folder.mkdir()
        (folder / "argmap.csv").write_text("callee\n")
        kept = ["argmap.csv"]
        state.commit(folder, {"sites.csv": b"one\n"}, 1)
        first = state.backup(folder, destination, kept)
        if first is None or state.backup(folder, destination, kept) is not None:
            failures.append("an unchanged run made a snapshot")
        if first and (first / "argmap.csv").read_text() != "callee\n":
            failures.append("the hand-owned file is not in the snapshot")
        (folder / "notes.csv").unlink(missing_ok=True)
        if "missing hand-owned file" not in fault(lambda: state.backup(folder, destination, ["notes.csv"])):
            failures.append("a missing hand-owned file did not fail")
        (destination / "000099.new").mkdir()  # a backup stopped while it wrote
        for number in range(2, 13):
            state.commit(folder, {"sites.csv": f"run {number}\n".encode()}, number)
            state.backup(folder, destination, kept)
        if state._numbered(destination) != list(range(3, 13)) or (destination / "000099.new").exists():
            failures.append(f"snapshots kept {state._numbered(destination)}")
    return failures


def check_restore() -> list[str]:
    failures = []
    with tempfile.TemporaryDirectory() as temp:
        folder, destination = Path(temp) / "evidence", Path(temp) / "backups"
        folder.mkdir()
        (folder / "argmap.csv").write_text("old\n")
        state.commit(folder, {"sites.csv": b"old ids\n"}, 2)
        state.backup(folder, destination, ["argmap.csv"])
        (folder / "argmap.csv").write_text("new\n")
        state.commit(folder, {"sites.csv": b"new ids\n"}, 5)
        state.backup(folder, destination, ["argmap.csv"])
        snapshot = destination / "000002" / "argmap.csv"
        snapshot.write_text("broken\n")
        if "does not match" not in fault(lambda: state.restore(folder, destination)):
            failures.append("a broken snapshot was restored")
        if (folder / "argmap.csv").read_text() != "new\n":
            failures.append("a failed restore wrote a file")
        generation = state.restore(folder, destination, 1)
        live = state.read_state(folder)
        if live.files != {"sites.csv": b"old ids\n"} or (folder / "argmap.csv").read_text() != "old\n":
            failures.append(f"restore gave {live}")
        minted = remap.mint(1, state.highest_minted(folder, live))
        if generation != 3 or state.read_high_water(folder) != 5 or minted != (["S000006"], 6):
            failures.append(f"after the restore: generation {generation}, minted {minted}")
        (folder / STATE / state.CURRENT).unlink()
        if state.restore(folder, destination, 1) != 4 or state.read_state(folder).files != live.files:
            failures.append("restore with CURRENT lost")
        (folder / state.HIGH_WATER).unlink()
        if state.highest_minted(folder, state.read_state(folder)) != 5:
            failures.append("the commit's mark did not stand in for a lost high-water.txt")
    return failures


def run() -> list[str]:
    failures = []
    for check in (check_sites_file, check_generations, check_faults, check_backups, check_restore):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    for failure in found:
        print(failure)
    if not found:
        print("statetests: all passed")
    sys.exit(1 if found else 0)
