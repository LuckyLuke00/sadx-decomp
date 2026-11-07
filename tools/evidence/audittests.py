"""Unit tests for audit.py, the leak guard. Each check builds a git repository in a temp folder.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/audittests.py
run() calls every check and returns the failures. All words are made up.
"""

import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import audit  # noqa: E402
import osutil  # noqa: E402  (audit puts tools/ on the path)

DENYLIST = "# made-up words\nLeakword\nxy\nword: pinned\nsubstring: ab\n"


def repository(root: Path, files: dict, add: list[str]) -> None:
    """A git repository at root with FILES written and the ADD paths staged."""
    osutil.git(root, "init", "-q")
    for name, content in files.items():
        path = root / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(content if isinstance(content, bytes) else content.encode())
    if add:
        osutil.git(root, "add", "-f", "--", *add)


def fault(files: dict, add: list[str]) -> str:
    """The AuditError text for a repository, or "" when the audit runs."""
    with osutil.foreign_repository(), tempfile.TemporaryDirectory() as folder:
        repository(Path(folder), files, add)
        try:
            audit.audit(Path(folder))
        except audit.AuditError as error:
            return str(error)
    return ""


def check_hits() -> list[str]:
    files = {
        ".gitignore": "evidence/\n*.log\n",
        "evidence/denylist.txt": DENYLIST,
        "src/tracked.c": "int x;\r\nint LEAKWORD_count;\r\n",
        "src/ident.c": "int pinned_suffix;\nint xyz;\n",
        "src/partial.c": "int pinned;\n",
        "notes/leakword-notes.md": "clean\n",
        "data.bin": b"leakword\0",
        "untracked.txt": "see xy here\ncab\n",
        "ignored.log": "leakword\n",
    }
    with osutil.foreign_repository(), tempfile.TemporaryDirectory() as folder:
        root = Path(folder)
        repository(root, files, [".gitignore", "src", "notes", "data.bin"])
        (root / "src" / "partial.c").write_text("int clean;\n")  # the staged version keeps the word
        found = audit.audit(root)
    wanted = ["notes/leakword-notes.md:0:Leakword", "src/partial.c (staged):1:pinned", "src/tracked.c:2:Leakword",
              "untracked.txt:1:xy", "untracked.txt:2:ab"]
    return [] if sorted(found) == wanted else [f"hits {sorted(found)}, want {wanted}"]


def check_faults() -> list[str]:
    failures = []
    ignore = {".gitignore": "evidence/\n"}
    cases = (
        ("missing deny-list", dict(ignore), []),
        ("empty deny-list", {**ignore, "evidence/denylist.txt": "# nothing yet\n\n"}, []),
        ("an entry with no text", {**ignore, "evidence/denylist.txt": "word:\n"}, []),
        ("git does not ignore evidence/", {"evidence/denylist.txt": DENYLIST}, []),
        ("git tracks files in evidence/", {**ignore, "evidence/denylist.txt": DENYLIST}, ["evidence/denylist.txt"]),
        ("", {**ignore, "evidence/denylist.txt": DENYLIST}, []),
    )
    for wanted, files, add in cases:
        got = fault(files, add)
        if (wanted == "" and got) or wanted not in got:
            failures.append(f"fault {got!r}, want {wanted!r}")
    return failures


def run() -> list[str]:
    failures = []
    for check in (check_hits, check_faults):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    for failure in found:
        print(failure)
    if not found:
        print("audittests: all passed")
    sys.exit(1 if found else 0)
