"""Unit tests for audit.py, the leak guard. Each check builds a git repository in a temp folder.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/audittests.py
run() calls every check and returns the failures. All words are made up.
"""

import contextlib
import io
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import audit  # noqa: E402
import osutil  # noqa: E402  (audit puts tools/ on the path)

DENYLIST_TEXT = "# made-up words\nLeakword\nxy\nword: pinned\nsubstring: ab\n"


def repository(root: Path, files: dict, add: list[str]) -> None:
    """A git repository at root with FILES written and the ADD paths staged."""
    osutil.git(root, "init", "-q")
    osutil.git(root, "config", "core.autocrlf", "false")  # the index keeps the bytes as written
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
        "evidence/denylist.txt": DENYLIST_TEXT,
        "src/tracked.c": "int x;\r\nint LEAKWORD_count;\r\n",
        "src/ident.c": "int pinned_suffix;\nint xyz;\nint my_pinned;\n",
        "src/partial.c": "int pinned;\n",
        "src/endings.c": "int pinned;\r\n",
        "src/gone.c": "int pinned;\n",
        "src/latin.c": b"caf\xe9 leakword\n",
        "notes/leakword-notes.md": "clean\n",
        "data.bin": b"leakword\0",
        "untracked.txt": "see xy here\ncab\n",
        "ignored.log": "leakword\n",
    }
    with osutil.foreign_repository(), tempfile.TemporaryDirectory() as folder:
        root = Path(folder)
        repository(root, files, [".gitignore", "src", "notes", "data.bin"])
        (root / "src" / "partial.c").write_text("int clean;\n")  # the staged version keeps the word
        (root / "src" / "endings.c").write_bytes(b"int pinned;\n")  # the staged version differs in line endings
        (root / "src" / "gone.c").unlink()  # only the staged version is left
        osutil.git(root, "update-index", "--add", "--cacheinfo", f"160000,{'1' * 40},vendor/lib")  # a submodule
        found = audit.audit(root)
    wanted = ["notes/leakword-notes.md:0:Leakword", "src/endings.c:1:pinned", "src/gone.c (staged):1:pinned",
              "src/latin.c:1:Leakword", "src/partial.c (staged):1:pinned", "src/tracked.c:2:Leakword",
              "untracked.txt:1:xy", "untracked.txt:2:ab"]
    return [] if sorted(found) == wanted else [f"hits {sorted(found)}, want {wanted}"]


def check_loose_files() -> list[str]:
    """A deny-list with a byte order mark and loosely written prefixes, and a UTF-16 text file, still give hits."""
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder) / audit.DENYLIST
        path.write_bytes(b"\xef\xbb\xbfLeakword\nWord : pinned\nSUBSTRING: xy\nsubstring: a.b\n")
        entries = audit.read_denylist(path)
    found = audit.content_hits("a.c", b"leakword pinned axyz\npinned_x axb\n", entries)  # a.b is no pattern
    found += audit.content_hits("b.txt", "clean\r\nleakword\r\n".encode("utf-16"), entries)
    wanted = ["a.c:1:Leakword", "a.c:1:pinned", "a.c:1:xy", "b.txt:2:Leakword"]
    return [] if found == wanted else [f"loose files: hits {found}, want {wanted}"]


def check_faults() -> list[str]:
    failures = []
    ignore = {".gitignore": "evidence/\n"}
    cases = (
        ("missing deny-list", dict(ignore), []),
        ("empty deny-list", {**ignore, "evidence/denylist.txt": "# nothing yet\n\n"}, []),
        ("an entry with no text", {**ignore, "evidence/denylist.txt": "word:\n"}, []),
        ("git does not ignore evidence/", {"evidence/denylist.txt": DENYLIST_TEXT}, []),
        ("git tracks files in evidence/", {**ignore, "evidence/denylist.txt": DENYLIST_TEXT},
         ["evidence/denylist.txt"]),
        ("", {**ignore, "evidence/denylist.txt": DENYLIST_TEXT}, []),
    )
    for wanted, files, add in cases:
        got = fault(files, add)
        passed = wanted in got if wanted else not got
        if not passed:
            failures.append(f"fault {got!r}, want {wanted!r}")
    which = audit.shutil.which
    audit.shutil.which = lambda name: None  # no git on PATH
    try:
        got = fault(ignore, [])
    finally:
        audit.shutil.which = which
    if got != "the audit needs git on PATH":
        failures.append(f"fault {got!r} without git")
    return failures


def main_result(files: dict) -> tuple[int, str, str]:
    """audit.main's exit code, standard output and error output for a repository of FILES."""
    out, err = io.StringIO(), io.StringIO()
    with osutil.foreign_repository(), tempfile.TemporaryDirectory() as folder:
        repository(Path(folder), files, [])
        with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
            code = audit.main(Path(folder))
    return code, out.getvalue(), err.getvalue()


def check_main() -> list[str]:
    """main prints each hit and returns 1, returns 0 with no hit, and prints a fault as one line and returns 1."""
    failures = []
    kept = {".gitignore": "evidence/\n", "evidence/denylist.txt": DENYLIST_TEXT}
    cases = (
        ("a hit", {**kept, "a.c": "leakword\n"}, 1, "a.c:1:Leakword\naudit: 1 hits\n", ""),
        ("no hit", {**kept, "a.c": "clean\n"}, 0, "audit: no hits\n", ""),
        ("a fault", {".gitignore": "evidence/\n"}, 1, "", "audit: missing deny-list "),
    )
    for name, files, code, out, err in cases:
        got = main_result(files)
        if got[:2] != (code, out) or not got[2].startswith(err) or bool(got[2]) != bool(err):
            failures.append(f"main, {name}: got {got!r}")
    return failures


def run() -> list[str]:
    failures = []
    for check in (check_hits, check_loose_files, check_faults, check_main):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    for failure in found:
        print(failure)
    if not found:
        print("audittests: all passed")
    sys.exit(1 if found else 0)
