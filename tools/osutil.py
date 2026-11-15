"""Helpers that know nothing about the decomp: run a command, catch a step's output, read git blobs, run git in another
repository than a hook's, link a git remote, hash a file, copy and delete folders, read counts from the command line,
tell how alike two counts are, count differing bytes, escape a Markdown table cell, tell whether a process runs, lock a
file, write a file whole.

Standard library only.
"""

import argparse
import collections
import contextlib
import ctypes
import dataclasses
import hashlib
import html
import io
import msvcrt
import os
import shutil
import stat
import subprocess
import sys
import time
from pathlib import Path

POWERSHELL = ["powershell", "-NoProfile", "-NonInteractive", "-Command"]
PROCESS_QUERY_LIMITED_INFORMATION, STILL_ACTIVE = 0x1000, 259
LOCK_POLL_SECONDS = 0.1
REPLACE_TRIES = 50  # a reader holds a file open for milliseconds


def run(command: list, cwd: Path | None = None, env: dict | None = None) -> subprocess.CompletedProcess:
    """Run a tool with its output captured. On failure, print the output and stop."""
    result = subprocess.run([str(part) for part in command], cwd=cwd, env=env, capture_output=True, text=True,
                            errors="replace")
    if result.returncode != 0:
        sys.exit(f"{result.stdout}{result.stderr}\nfailed ({result.returncode}): {' '.join(map(str, command))}")
    return result


def caught(step) -> tuple[bool, list[str]]:
    """Run STEP with its printed output caught: (whether it worked, the output's lines). It fails when it exits, with
    the exit's message as the last line, or when it returns a nonzero code."""
    out = io.StringIO()
    try:
        with contextlib.redirect_stdout(out):
            worked = not step()
    except SystemExit as failure:
        out.write(f"\n{failure.code}")
        worked = False
    return worked, out.getvalue().strip().splitlines()


def git(root: Path, *args: str, stdin: bytes = b"") -> bytes:
    """Run git in root and return its output. On failure, stop with git's message."""
    result = subprocess.run(["git", *args], cwd=root, input=stdin, capture_output=True)
    if result.returncode != 0:
        sys.exit(f"git {' '.join(args)} failed: {result.stderr.decode(errors='replace').strip()}")
    return result.stdout


def git_blobs(root: Path, ids: list[str]) -> dict[str, bytes]:
    """The bytes of each blob id in the repository at root, read by one `git cat-file --batch` process."""
    unique = sorted(set(ids))
    data = git(root, "cat-file", "--batch", stdin="".join(f"{blob}\n" for blob in unique).encode())
    blobs, position = {}, 0
    for blob in unique:
        header_end = data.index(b"\n", position)
        size = int(data[position:header_end].split()[2])
        blobs[blob] = data[header_end + 1:header_end + 1 + size]
        position = header_end + 1 + size + 1  # the content ends with a newline of its own
    return blobs


@contextlib.contextmanager
def foreign_repository():
    """Clear the variables that tie git to one repository, as `git rev-parse --local-env-vars` lists them, while git
    runs in another one. A hook gets them for its own repository: in a linked worktree's commit hook, `git init` in
    another folder marks that repository bare, and `git add` there stages into the worktree's index."""
    names = run(["git", "rev-parse", "--local-env-vars"]).stdout.split()
    saved = {name: os.environ.pop(name) for name in names if name in os.environ}
    try:
        yield
    finally:
        os.environ.update(saved)


def web_url(remote: str) -> str:
    """The web page of a git remote, https://host/path or git@host:path, without a .git at the end."""
    if remote.startswith("git@") and ":" in remote:
        host, path = remote.removeprefix("git@").split(":", 1)
        remote = f"https://{host}/{path}"
    if not remote.startswith("https://"):
        sys.exit(f"can't make a web link from the git remote {remote}")
    return remote.removesuffix(".git")


def write_if_changed(path: Path, text: str) -> None:
    """Write a build input only when its text changes, so the build tools see no change otherwise."""
    if not path.exists() or path.read_text(encoding="utf-8") != text:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")


def write_files(root: Path, files: dict) -> None:
    """Write FILES (relative path -> text) under ROOT as UTF-8 with their line ends unchanged, making the folders."""
    for name, text in files.items():
        path = root / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8", newline="")


def write_whole(path: Path, data: str | bytes) -> None:
    """Write DATA to PATH through a rename, so another process reads the old data or the new, never a part. Text goes
    out as UTF-8 with its line ends unchanged."""
    temp = path.with_name(path.name + ".new")
    temp.write_bytes(data.encode("utf-8") if isinstance(data, str) else data)
    for _ in range(REPLACE_TRIES - 1):
        try:
            os.replace(temp, path)
            return
        except PermissionError:  # Windows refuses the rename while a reader has PATH open
            time.sleep(LOCK_POLL_SECONDS)
    os.replace(temp, path)


def powershell(script: str) -> str:
    return run([*POWERSHELL, script]).stdout


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as data:
        for chunk in iter(lambda: data.read(1 << 20), b""):
            digest.update(chunk)
    return digest.hexdigest()


def copy_tree(source: Path, target: Path) -> None:
    """copyfile copies no attributes, so a read-only flag in source does not carry over."""
    shutil.copytree(source, target, copy_function=shutil.copyfile)


def copy_files(source: Path, target: Path, names: list[str] | None = None) -> None:
    """Copy the files directly inside source (all of them, or just names) into target, without attributes."""
    target.mkdir(parents=True, exist_ok=True)
    for name in names or sorted(path.name for path in source.iterdir() if path.is_file()):
        if not (source / name).is_file():
            sys.exit(f"missing: {source / name}")
        shutil.copyfile(source / name, target / name)


def positive_int(value: str) -> int:
    """argparse type: VALUE as an int of 1 or more."""
    number = int(value)
    if number < 1:
        raise argparse.ArgumentTypeError(f"{value} is less than 1")
    return number


def positive_ints(value: str) -> list[int]:
    """argparse type: VALUE as comma-separated ints of 1 or more, such as 600,600,1000."""
    return [positive_int(part) for part in value.split(",")]


def likeness(a: collections.Counter, b: collections.Counter) -> float:
    """How alike two counts are: the weighted Jaccard index, 1.0 for the same counts, 0.0 when both are empty."""
    union = sum((a | b).values())
    return sum((a & b).values()) / union if union else 0.0


def byte_differences(a: bytes, b: bytes, block: int = 1 << 16) -> tuple[int, int | None]:
    """How many bytes differ between a and b, the longer one's tail included, and the first offset that does. Equal
    blocks are skipped whole, so two big, mostly equal files compare fast."""
    count, first, common = abs(len(a) - len(b)), None, min(len(a), len(b))
    for start in range(0, common, block):
        end = min(start + block, common)
        ours, theirs = a[start:end], b[start:end]
        if ours != theirs:
            offsets = [start + index for index, (x, y) in enumerate(zip(ours, theirs)) if x != y]
            count += len(offsets)
            first = offsets[0] if first is None else first
    if first is None and len(a) != len(b):
        first = common
    return count, first


def whole_word(pattern: str) -> str:
    """PATTERN as a regular expression that matches only where no letter, digit or underscore touches either end."""
    return f"(?<![A-Za-z0-9_]){pattern}(?![A-Za-z0-9_])"


def table_cell(text: str) -> str:
    """TEXT for a cell of a GitHub Markdown table: a `<` would start an HTML tag and a `|` would end the cell."""
    return html.escape(text, quote=False).replace("|", "\\|")


def markdown_table(head: tuple, rows) -> list[str]:
    """The lines of a GitHub Markdown table: the column names HEAD, then ROWS, each cell through table_cell."""
    lines = ["| " + " | ".join(table_cell(str(cell)) for cell in row) + " |" for row in (head, *rows)]
    return lines[:1] + ["|---" * len(head) + "|"] + lines[1:]


def group_by(items, key) -> dict:
    """KEY(item) -> the ITEMS with that key, the keys and the items in first-seen order."""
    groups = {}
    for item in items:
        groups.setdefault(key(item), []).append(item)
    return groups


def most_first(counts: dict) -> list[tuple]:
    """The (key, count) pairs of COUNTS, the highest count first, then by key."""
    return sorted(counts.items(), key=lambda pair: (-pair[1], pair[0]))


@dataclasses.dataclass
class Alignment:
    shared: dict  # old index -> new index, for the pairs every optimal alignment makes
    disputed_old: set  # old indices on an optimal pair that is not shared
    disputed_new: set
    candidates: list  # (old index, new index) of every optimal pair that is not shared
    count: int  # the number of optimal paths


def align(old: list, new: list, score) -> Alignment:
    """The pairs of a scored global alignment (Needleman-Wunsch) of OLD against NEW. SCORE(i, j) gives a pair's
    score, or None when the two cannot pair. Gaps score 0. A pair is shared when every optimal alignment makes it,
    and disputed when only some do."""
    rows, columns = len(old), len(new)
    pairs = [[score(i, j) for j in range(columns)] for i in range(rows)]
    head, head_ways = _best_paths(pairs, rows, columns)
    # The same tables over the mirrored pairs: tail[a][b] is the best score of the last a old and the last b new items.
    tail, tail_ways = _best_paths([row[::-1] for row in pairs[::-1]], rows, columns)
    total, count = head[rows][columns], head_ways[rows][columns]
    found = Alignment({}, set(), set(), [], count)
    for i in range(rows):
        for j in range(columns):
            after = rows - 1 - i, columns - 1 - j  # the items after the pair (i, j)
            if pairs[i][j] is None or head[i][j] + pairs[i][j] + tail[after[0]][after[1]] != total:
                continue
            if head_ways[i][j] * tail_ways[after[0]][after[1]] == count:
                found.shared[i] = j
            else:
                found.disputed_old.add(i)
                found.disputed_new.add(j)
                found.candidates.append((i, j))
    return found


def _best_paths(pairs: list, rows: int, columns: int) -> tuple[list, list]:
    """best[i][j], the best score of the first i rows against the first j columns of PAIRS (gaps score 0), and
    ways[i][j], the number of paths with that score."""
    best = [[0] * (columns + 1) for _ in range(rows + 1)]
    ways = [[1] * (columns + 1) for _ in range(rows + 1)]
    for i in range(1, rows + 1):
        for j in range(1, columns + 1):
            steps = [(best[i - 1][j], ways[i - 1][j]), (best[i][j - 1], ways[i][j - 1])]
            if pairs[i - 1][j - 1] is not None:
                steps.append((best[i - 1][j - 1] + pairs[i - 1][j - 1], ways[i - 1][j - 1]))
            best[i][j] = max(value for value, _ in steps)
            ways[i][j] = sum(count for value, count in steps if value == best[i][j])
    return best, ways


def remove(path: Path) -> None:
    """Delete a folder, read-only files included."""
    if not path.exists():
        return
    for item in path.rglob("*"):
        item.chmod(stat.S_IWRITE)
    shutil.rmtree(path)


def alive(pid: int) -> bool:
    """Whether the Windows process PID runs: os.kill(pid, 0) would end it."""
    kernel = ctypes.windll.kernel32
    handle = kernel.OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, False, pid)
    if not handle:
        return False
    code = ctypes.c_ulong()
    ok = kernel.GetExitCodeProcess(handle, ctypes.byref(code))
    kernel.CloseHandle(handle)
    return bool(ok) and code.value == STILL_ACTIVE


@contextlib.contextmanager
def locked(path: Path):
    """Hold the lock of the file PATH while the block runs: wait while another process holds it."""
    path.parent.mkdir(parents=True, exist_ok=True)
    with open(path, "a+") as handle:
        while True:
            try:
                msvcrt.locking(handle.fileno(), msvcrt.LK_NBLCK, 1)
                break
            except OSError:  # another process holds it
                time.sleep(LOCK_POLL_SECONDS)
        try:
            yield
        finally:
            msvcrt.locking(handle.fileno(), msvcrt.LK_UNLCK, 1)
