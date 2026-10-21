"""Helpers that know nothing about the decomp: run a command, hash a file, copy and delete folders, read a count
from the command line.

Standard library only.
"""

import argparse
import hashlib
import shutil
import stat
import subprocess
import sys
from pathlib import Path

POWERSHELL = ["powershell", "-NoProfile", "-NonInteractive", "-Command"]


def run(command: list, cwd: Path | None = None, env: dict | None = None) -> subprocess.CompletedProcess:
    """Run a tool with its output captured. On failure, print the output and stop."""
    result = subprocess.run([str(part) for part in command], cwd=cwd, env=env, capture_output=True, text=True,
                            errors="replace")
    if result.returncode != 0:
        sys.exit(f"{result.stdout}{result.stderr}\nfailed ({result.returncode}): {' '.join(map(str, command))}")
    return result


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


def remove(path: Path) -> None:
    """Delete a folder, read-only files included."""
    if not path.exists():
        return
    for item in path.rglob("*"):
        item.chmod(stat.S_IWRITE)
    shutil.rmtree(path)
