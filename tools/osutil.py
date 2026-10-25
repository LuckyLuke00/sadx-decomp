"""Helpers that know nothing about the decomp: run a command, catch a step's output, hash a file, copy and delete
folders, read counts from the command line, tell how alike two counts are, count differing bytes, escape a
Markdown table cell, tell whether a process runs, lock a file.

Standard library only.
"""

import argparse
import collections
import contextlib
import ctypes
import hashlib
import html
import io
import msvcrt
import shutil
import stat
import subprocess
import sys
import time
from pathlib import Path

POWERSHELL = ["powershell", "-NoProfile", "-NonInteractive", "-Command"]
PROCESS_QUERY_LIMITED_INFORMATION, STILL_ACTIVE = 0x1000, 259
LOCK_POLL_SECONDS = 0.1


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


def write_if_changed(path: Path, text: str) -> None:
    """Write a build input only when its text changes, so the build tools see no change otherwise."""
    if not path.exists() or path.read_text(encoding="utf-8") != text:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")


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


def table_cell(text: str) -> str:
    """TEXT for a cell of a GitHub Markdown table: a `<` would start an HTML tag and a `|` would end the cell."""
    return html.escape(text, quote=False).replace("|", "\\|")


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
