"""The leak guard: no deny-listed word in what git would publish.

`evidence.py audit` scans the paths and the contents of the tracked files, of the untracked files that git does not
ignore, and of each staged version that differs from its working-tree file. It matches each entry of
evidence/denylist.txt, ignoring case. It also checks that git ignores evidence/ and tracks nothing in it. It is a
supplementary check, not a guarantee: it does not read history or ignored files, and it cannot clean history. A file
that holds a NUL byte is binary: only its path is checked.

Each hit is one line `file:line:entry`. Line 0 means the path. A staged version shows as `file (staged)`.

The deny-list holds one entry per line. Blank lines and lines that start with # are skipped. `word: ENTRY` matches
ENTRY only as a whole word: a letter, digit or _ next to it ends the match. `substring: ENTRY` matches it anywhere.
With no prefix, an entry of 4 or more characters is a substring and a shorter one is a word. For a leak guard a false
hit costs less than a miss, so the default is substring.

Standard library only.
"""

import re
import shutil
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path

sys.path.append(str(Path(__file__).resolve().parents[1]))  # tools/, after the standard library
import osutil  # noqa: E402

EVIDENCE = "evidence"
DENYLIST = "denylist.txt"
WORD_MODE_BELOW = 4  # an entry with no prefix and fewer characters matches as a whole word
WORD_CHARACTER = "[A-Za-z0-9_]"
SUBMODULE_MODE = "160000"  # an index entry that holds a commit of another repository, not a blob


class AuditError(Exception):
    """The audit cannot run: no deny-list, no git, or evidence/ not kept out of git."""


@dataclass(frozen=True)
class Entry:
    text: str
    pattern: re.Pattern


def read_denylist(path: Path) -> list[Entry]:
    if not path.is_file():
        raise AuditError(f"missing deny-list {path}")
    entries = []
    for number, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        mode, text = "", line
        for prefix in ("word:", "substring:"):
            if line.startswith(prefix):
                mode, text = prefix[:-1], line[len(prefix):].strip()
        if not text:
            raise AuditError(f"{path}:{number}: an entry with no text")
        if not mode:
            mode = "word" if len(text) < WORD_MODE_BELOW else "substring"
        pattern = re.escape(text)
        if mode == "word":
            pattern = f"(?<!{WORD_CHARACTER}){pattern}(?!{WORD_CHARACTER})"
        entries.append(Entry(text, re.compile(pattern, re.IGNORECASE)))
    if not entries:
        raise AuditError(f"empty deny-list {path}")
    return entries


def path_hits(path: str, entries: list[Entry]) -> list[str]:
    return [f"{path}:0:{entry.text}" for entry in entries if entry.pattern.search(path)]


def content_hits(name: str, data: bytes, entries: list[Entry]) -> list[str]:
    if b"\0" in data:
        return []
    try:
        text = data.decode("utf-8")
    except UnicodeDecodeError:
        text = data.decode("latin-1")
    found = set()
    for entry in entries:
        for match in entry.pattern.finditer(text):
            found.add((text.count("\n", 0, match.start()) + 1, entry.text))
    return [f"{name}:{line}:{text}" for line, text in sorted(found)]


def _paths(root: Path, *args: str) -> list[str]:
    return [path for path in osutil.git(root, *args).decode("utf-8").split("\0") if path]


def _working_bytes(file: Path) -> bytes | None:
    """The file's bytes, None when it is gone or a link (its staged blob holds the link target)."""
    if not file.is_file() or file.is_symlink():
        return None
    return file.read_bytes()


def check_kept_out(root: Path) -> None:
    # Tracked files first: with one inside, git calls the folder not ignored whatever .gitignore says.
    tracked = _paths(root, "ls-files", "-z", "--", EVIDENCE)
    if tracked:
        raise AuditError(f"git tracks files in {EVIDENCE}/ ({', '.join(tracked[:5])}): untrack them with "
                         f"`git rm --cached`")
    ignored = subprocess.run(["git", "check-ignore", "-q", f"{EVIDENCE}/"], cwd=root, capture_output=True)
    if ignored.returncode == 128:
        raise AuditError(f"git check-ignore failed: {ignored.stderr.decode(errors='replace').strip()}")
    if ignored.returncode != 0:
        raise AuditError(f"git does not ignore {EVIDENCE}/: add the line `{EVIDENCE}/` to .gitignore")


def staged_hits(root: Path, entries: list[Entry]) -> list[str]:
    """Hits in each staged version that differs from its working-tree file, line endings aside."""
    changed = set(_paths(root, "diff-files", "--name-only", "-z"))
    rows = []
    for row in _paths(root, "ls-files", "--stage", "-z"):
        info, path = row.split("\t", 1)
        mode, blob, _stage = info.split()
        if path in changed and mode != SUBMODULE_MODE:
            rows.append((path, blob))
    blobs = osutil.git_blobs(root, [blob for _, blob in rows]) if rows else {}
    found = []
    for path, blob in rows:
        working = _working_bytes(root / path)
        if working is not None and working.replace(b"\r\n", b"\n") == blobs[blob].replace(b"\r\n", b"\n"):
            continue
        found += content_hits(f"{path} (staged)", blobs[blob], entries)
    return found


def audit(root: Path) -> list[str]:
    """Every hit in the repository at root. Raises AuditError when the audit cannot run."""
    if shutil.which("git") is None:
        raise AuditError("the audit needs git on PATH")
    entries = read_denylist(root / EVIDENCE / DENYLIST)
    check_kept_out(root)
    paths = set(_paths(root, "ls-files", "-z")) | set(_paths(root, "ls-files", "--others", "--exclude-standard", "-z"))
    found = []
    for path in sorted(paths):
        found += path_hits(path, entries)
        working = _working_bytes(root / path)
        if working is not None:
            found += content_hits(path, working, entries)
    return found + staged_hits(root, entries)


def main(root: Path) -> int:
    try:
        found = audit(root)
    except AuditError as error:
        sys.exit(f"audit: {error}")
    for hit in found:
        print(hit)
    print(f"audit: {len(found)} hits" if found else "audit: no hits")
    return 1 if found else 0
