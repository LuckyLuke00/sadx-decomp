"""Unit tests for evidence.py, the command layer: main sends each command to its function, and each command's fault
reaches the error output as one line with exit code 1.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/evidencetests.py
run() calls every check and returns the failures. All paths are made up.
"""

import contextlib
import io
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import evidence  # noqa: E402
import osutil  # noqa: E402  (the modules put tools/ on the path)


def console(arguments: list[str], root: Path) -> tuple[int, str, str]:
    """main's exit code, standard output and error output for ARGUMENTS, with the repository at ROOT."""
    saved = evidence.ROOT, evidence.FOLDER, sys.argv
    evidence.ROOT, evidence.FOLDER, sys.argv = root, root / "evidence", ["evidence.py", *arguments]
    out, err = io.StringIO(), io.StringIO()
    try:
        with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
            code = evidence.main()
    finally:
        evidence.ROOT, evidence.FOLDER, sys.argv = saved
    return code, out.getvalue(), err.getvalue()


def check_faults() -> list[str]:
    """Each command reaches its own function, whose fault prints one line to the error output and returns 1."""
    failures = []
    with osutil.foreign_repository(), tempfile.TemporaryDirectory() as temp:
        root = Path(temp)
        (root / "evidence").mkdir()
        cases = (
            (["audit"], "audit: missing deny-list "),
            (["run"], "evidence run: "),
            (["import-baseline", str(root / "old.csv")], "evidence import-baseline: missing hand-owned file "),
            (["decide", "S000001", "confirm"], "evidence decide: no ledger yet: run the tool first"),
            (["pdbimport", str(root / "none.pdb")], "evidence pdbimport: "),
        )
        for arguments, wanted in cases:
            code, out, err = console(arguments, root)
            if (code, out) != (1, "") or not err.startswith(wanted) or err.count("\n") != 1:
                failures.append(f"{arguments[0]}: got {(code, out, err)!r}, want 1 and {wanted!r}")
    return failures


def run() -> list[str]:
    failures = []
    for check in (check_faults,):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    print("\n".join(found) or "evidencetests: all passed")
    sys.exit(1 if found else 0)
