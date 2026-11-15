"""The run state in evidence/: site ids, generations and backups.

  high-water.txt   the number of the highest site id ever minted; it only grows
  state/CURRENT    one line: the number of the live generation (0 before the first commit)
  state/<n>/       generation n: its files and manifest.json, which holds their hashes and the high-water mark

A commit writes generation n + 1 in full, raises the high-water mark, then replaces CURRENT in one rename. A run
stopped before the rename leaves generation n live, and recover() deletes the partial folder. A read goes through
CURRENT and checks every hash in the manifest, so a hand edit or a torn write fails with a clear error. After a commit
only the live and the previous generation stay; the backups keep the history.

A backup snapshot holds the live state's files and the hand-owned files, which no run can make again. A snapshot is
built under a temporary name and renamed when whole. No snapshot is made when the hashes equal the latest one's, and
the newest BACKUPS_KEPT stay. A snapshot's manifest holds the high-water mark of its time. A restore checks the whole
snapshot before it writes anything, writes the hand-owned files back, then commits the state files as a new generation.
Its mark is the highest of high-water.txt, the restored snapshot and the newest snapshot. Each run backs up after its
commit, so a restored older state reuses no id, even when high-water.txt was lost.

sites.csv: the line `# evidence-sites schema=1`, then a CSV header and one row per site, each owner's sites in order.
The ordinal column counts a site's place in its owner, from 1; it is for reading only.

Standard library only.
"""

import hashlib
import json
import os
import sys
from collections import Counter
from dataclasses import dataclass
from datetime import datetime, timezone
from pathlib import Path

sys.path.append(str(Path(__file__).resolve().parents[1]))  # tools/, after the standard library
import osutil  # noqa: E402
import outputs  # noqa: E402
from remap import Site  # noqa: E402

SCHEMA = 1
STATE, CURRENT, MANIFEST, HIGH_WATER = "state", "CURRENT", "manifest.json", "high-water.txt"
SITES = "sites.csv"
SITE_COLUMNS = ("id", "owner", "ordinal", "kind", "target", "slot", "expression", "value", "file", "line", "column",
                "context")
BACKUPS_KEPT = 10
SNAPSHOT_DIGITS = 6
PARTIAL = ".new"  # the suffix of a snapshot folder still being written
MANIFEST_TYPES = {"generation": int, "high_water": int, "files": dict}


class StateError(Exception):
    """The state cannot be read or written as it is."""


@dataclass(frozen=True)
class State:
    generation: int
    files: dict  # name -> bytes
    high_water: int  # the mark the commit recorded


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def format_sites(sites: list[Site]) -> bytes:
    ordinals = Counter()
    rows = []
    for site in sites:
        ordinals[site.owner] += 1
        rows.append((site.id, site.owner, ordinals[site.owner], site.kind, site.target, site.slot, site.expression,
                     site.value, site.file, site.line, site.column, site.context))
    return outputs.schema_text(SITES, SCHEMA, SITE_COLUMNS, rows).encode("utf-8")


def parse_sites(data: bytes) -> list[Site]:
    return [Site(row["owner"], row["kind"], row["target"], row["slot"], row["expression"], row["value"],
                 row["context"], row["id"], row["file"], int(row["line"]), int(row["column"]))
            for _, row in outputs.schema_rows(data.decode("utf-8"), SITES, SCHEMA, SITE_COLUMNS, StateError)]


def _number(path: Path) -> int:
    """The number in a one-line file."""
    text = path.read_text(encoding="utf-8").strip()
    if not text.isdecimal():
        raise StateError(f"{path} holds {text[:40]!r}, not a number")
    return int(text)


def read_high_water(folder: Path) -> int:
    path = folder / HIGH_WATER
    return _number(path) if path.is_file() else 0


def raise_high_water(folder: Path, number: int) -> int:
    """Raise the mark to NUMBER when it is lower. Returns the mark."""
    current = read_high_water(folder)
    if number > current:
        osutil.write_whole(folder / HIGH_WATER, f"{number}\n")
    return max(number, current)


def highest_minted(folder: Path, state: State | None) -> int:
    """The number to mint above: the mark, or the live commit's mark when high-water.txt was lost."""
    return max(read_high_water(folder), state.high_water if state else 0)


def _numbered(folder: Path) -> list[int]:
    if not folder.is_dir():
        return []
    return sorted(int(path.name) for path in folder.iterdir() if path.is_dir() and path.name.isdigit())


def live_generation(folder: Path) -> int:
    state = folder / STATE
    if not state.is_dir():
        return 0
    if not (state / CURRENT).is_file():
        raise StateError(f"{state} has no {CURRENT}: restore a backup, or delete {state} to start with new ids")
    return _number(state / CURRENT)


def _manifest(where: Path, keys: tuple, advice: str = "") -> dict:
    """WHERE's manifest, checked for the schema and for the KEYS the caller reads."""
    path = where / MANIFEST
    if not path.is_file():
        raise StateError(f"{where} has no {MANIFEST}{advice}")
    try:
        manifest = json.loads(path.read_text(encoding="utf-8"))
    except ValueError as error:  # not UTF-8, or not JSON
        raise StateError(f"{path} is not JSON ({error}){advice}") from None
    if not isinstance(manifest, dict) or manifest.get("schema") != SCHEMA:
        raise StateError(f"{path} is not a schema {SCHEMA} manifest{advice}")
    wrong = [key for key in keys if not isinstance(manifest.get(key), MANIFEST_TYPES[key])]
    if wrong:
        raise StateError(f"{path} lacks a valid {', '.join(wrong)}{advice}")
    return manifest


def _checked_files(where: Path, manifest: dict, advice: str = "") -> dict:
    """The files the manifest lists, each checked against its hash."""
    files = {}
    for name, wanted in manifest["files"].items():
        path = where / name
        if not path.is_file():
            raise StateError(f"{path} is missing: {where / MANIFEST} lists it{advice}")
        data = path.read_bytes()
        if digest(data) != wanted:
            raise StateError(f"{path} does not match {where / MANIFEST}: it changed outside a run{advice}")
        files[name] = data
    return files


def read_state(folder: Path) -> State | None:
    """The live state, None before the first commit."""
    generation = live_generation(folder)
    if generation == 0:
        return None
    where, advice = folder / STATE / str(generation), ": restore a backup"
    manifest = _manifest(where, ("generation", "high_water", "files"), advice)
    if manifest["generation"] != generation:
        raise StateError(f"{where / MANIFEST} names generation {manifest['generation']}{advice}")
    return State(generation, _checked_files(where, manifest, advice), manifest["high_water"])


def recover(folder: Path) -> list[str]:
    """Delete what a stopped run left in state/. Returns one line per deleted folder."""
    live, notes = live_generation(folder), []
    for number in _numbered(folder / STATE):
        if number > live:
            notes.append(f"deleted {STATE}/{number}: a run stopped before its commit")
        elif number < live - 1:
            notes.append(f"deleted {STATE}/{number}: a run stopped before it cleared the old generations")
        else:
            continue
        osutil.remove(folder / STATE / str(number))
    return notes


def _write_folder(where: Path, files: dict, manifest: dict) -> None:
    """FILES into WHERE, then the manifest with their hashes."""
    for name, data in files.items():
        (where / name).parent.mkdir(parents=True, exist_ok=True)
        (where / name).write_bytes(data)
    whole = {**manifest, "files": {name: digest(data) for name, data in sorted(files.items())}}
    (where / MANIFEST).write_bytes((json.dumps(whole, indent=1, sort_keys=True) + "\n").encode("utf-8"))


def commit(folder: Path, files: dict, high_water: int) -> int:
    """Write FILES (name -> bytes) as the next generation and make it live. HIGH_WATER must be at least the number of
    every id in FILES. Run recover() first. Returns the new generation."""
    state = folder / STATE
    if not state.is_dir():
        state.mkdir(parents=True)
        osutil.write_whole(state / CURRENT, "0\n")
    generation = live_generation(folder) + 1
    where = state / str(generation)
    if where.exists():
        raise StateError(f"{where} exists: another run writes the state, or recover() did not run")
    where.mkdir()
    _write_folder(where, files, {"schema": SCHEMA, "generation": generation, "high_water": high_water})
    raise_high_water(folder, high_water)
    osutil.write_whole(state / CURRENT, f"{generation}\n")
    for number in _numbered(state):
        if number < generation - 1:
            osutil.remove(state / str(number))
    return generation


def backup(folder: Path, destination: Path, kept: list[str]) -> Path | None:
    """Snapshot the live state's files and the KEPT files (paths relative to FOLDER) into DESTINATION. Returns the
    snapshot folder, None when nothing changed since the latest snapshot."""
    state = read_state(folder)
    files = {f"{STATE}/{name}": data for name, data in (state.files.items() if state else [])}
    for name in kept:
        path = folder / name
        if not path.is_file():
            raise StateError(f"missing hand-owned file {path}")
        files[name] = path.read_bytes()
    numbers = _numbered(destination)
    hashes = {name: digest(data) for name, data in sorted(files.items())}
    if numbers and _manifest(_snapshot(destination, numbers[-1]), ("files",))["files"] == hashes:
        return None
    destination.mkdir(parents=True, exist_ok=True)
    for path in destination.glob(f"*{PARTIAL}"):  # a backup stopped while it wrote
        osutil.remove(path)
    snapshot = _snapshot(destination, (numbers[-1] if numbers else 0) + 1)
    temp = destination / (snapshot.name + PARTIAL)
    temp.mkdir()
    created = datetime.now(timezone.utc).isoformat(timespec="seconds")
    _write_folder(temp, files, {"schema": SCHEMA, "generation": state.generation if state else 0, "created": created,
                                "high_water": highest_minted(folder, state)})
    os.replace(temp, snapshot)
    for number in _numbered(destination)[:-BACKUPS_KEPT]:
        osutil.remove(_snapshot(destination, number))
    return snapshot


def _snapshot(destination: Path, number: int) -> Path:
    return destination / f"{number:0{SNAPSHOT_DIGITS}d}"


def restore(folder: Path, destination: Path, number: int | None = None) -> int:
    """Put snapshot NUMBER (the latest when None) back: first the hand-owned files, then the state files as a new
    generation, with the highest mark of high-water.txt, this snapshot and the newest one. Returns the new
    generation."""
    numbers = _numbered(destination)
    if not numbers:
        raise StateError(f"no snapshots in {destination}")
    chosen = numbers[-1] if number is None else number
    if chosen not in numbers:
        raise StateError(f"no snapshot {chosen} in {destination}: there are {numbers}")
    where = _snapshot(destination, chosen)
    manifest = _manifest(where, ("high_water", "files"))
    files = _checked_files(where, manifest)
    newest = _manifest(_snapshot(destination, numbers[-1]), ("high_water",))
    mark = max(read_high_water(folder), manifest["high_water"], newest["high_water"])
    prefix = f"{STATE}/"
    for name, data in files.items():
        if not name.startswith(prefix):
            (folder / name).parent.mkdir(parents=True, exist_ok=True)
            osutil.write_whole(folder / name, data)
    state = folder / STATE
    if state.is_dir() and not (state / CURRENT).is_file():  # CURRENT was lost: the newest folder stands in for it
        osutil.write_whole(state / CURRENT, f"{max(_numbered(state), default=0)}\n")
    recover(folder)
    state_files = {name.removeprefix(prefix): data for name, data in files.items() if name.startswith(prefix)}
    return commit(folder, state_files, mark)
