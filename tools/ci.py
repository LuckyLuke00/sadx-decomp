"""Regression checks that need no compiler and no game files. check.py runs them last.

1. summary.json is fresh: it was scored from the build inputs in this checkout.
2. Against the base commit: no score dropped. A removed stub scored zero, so it drops nothing.
3. history.csv and the visuals equal a fresh render. The history comes from the
   commits, so a fresh render proves it matches them.
4. Every function in data/functions.csv is in exactly one code group and ends inside it.
5. No binaries and no file over 10 MB are in the repo.

Before the first `check.py save` there is no summary.json: that fails, and only
checks 4 and 5 run. The base defaults to the branch's upstream. Without a base,
check 2 is skipped, with a note. On GitHub Actions, a run with a base also
writes the score changes against it to the job's summary page. Standard library
only.
"""

import hashlib
import json
import os
import subprocess
import sys
from pathlib import Path

import osutil
import progress
import scoring

ROOT = progress.ROOT
# The repo files and tools that can change a score. summary.json stores their hash.
BUILD_INPUTS = ["src", "CMakeLists.txt", "game.cmake", "data/codegen-groups.csv", "data/functions.csv",
                "reccmp-project.yml", "requirements.txt", "tools/accesses.py", "tools/check.py", "tools/codegen.py",
                "tools/constants.py", "tools/datafiles.py", "tools/fakematch.py", "tools/libobjects.py",
                "tools/library.py", "tools/names.py", "tools/osutil.py", "tools/pe.py", "tools/progress.py",
                "tools/project.py", "tools/report.py", "tools/runner.py", "tools/scoring.py", "tools/selftest.py",
                "tools/toolchain.py", "tools/tricks.py"]
BINARY_SUFFIXES = {".exe", ".dll", ".pdb", ".lib", ".obj", ".ilk", ".iso", ".msi"}
MAX_FILE_BYTES = 10 * 1024 * 1024
MAX_LINES = 10  # problem lines a check prints before it sums up the rest
JOB_SUMMARY_ROWS = 50  # the most moved functions the job summary lists
NO_COMMIT = "0" * 40


def run_git(*args: str) -> subprocess.CompletedProcess:
    return subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True, encoding="utf-8")


def git(*args: str) -> str:
    return osutil.git(ROOT, *args).decode("utf-8")


def repo_files(*paths: str) -> list[Path]:
    """Tracked files plus new ones git would add: what a commit would hold. Ignored files are left out."""
    listed = git("ls-files", "--cached", "--others", "--exclude-standard", "-z", "--", *paths).split("\0")
    return sorted({ROOT / name for name in listed if name and (ROOT / name).is_file()})


def normalized(path: Path) -> bytes:
    """File bytes with LF line ends, so a Windows checkout and a Linux one hash the same."""
    return path.read_bytes().replace(b"\r\n", b"\n")


def inputs_hash() -> str:
    missing = [path for path in BUILD_INPUTS if not (ROOT / path).exists()]
    if missing:
        sys.exit(f"BUILD_INPUTS in tools/ci.py names missing files: {', '.join(missing)}. Update the list.")
    digest = hashlib.sha256()
    for path in repo_files(*BUILD_INPUTS):
        digest.update(path.relative_to(ROOT).as_posix().encode("utf-8") + b"\0")
        digest.update(normalized(path) + b"\0")
    return digest.hexdigest()


def at_base(base: str, path: Path) -> str | None:
    """A file's text at the base commit, or None if it did not exist there."""
    name = path.relative_to(ROOT).as_posix()
    result = run_git("show", f"{base}:{name}")
    return result.stdout if result.returncode == 0 else None


def resolve_base(base: str | None) -> str | None:
    if base is None:
        return run_git("rev-parse", "--verify", "--quiet", "@{upstream}").stdout.strip() or None
    if base in ("", NO_COMMIT):
        return None
    if run_git("cat-file", "-e", f"{base}^{{commit}}").returncode != 0:
        sys.exit(f"base commit {base} is not in this clone. CI needs the full history (fetch-depth: 0).")
    return base


def check_fresh(summary: dict) -> list[str]:
    stored, current = summary.get("inputs_sha256"), inputs_hash()
    if stored == current:
        return []
    return [f"summary.json was scored from other build inputs ({str(stored)[:12]} != {current[:12]}). "
            "Once no score drops, run `python tools/check.py save` and commit the result."]


def check_no_drops(summary: dict, base: str) -> list[str]:
    text = at_base(base, progress.SUMMARY_JSON)
    if text is None:
        return []
    return [f"against {base[:12]}: {line}"
            for line in scoring.find_regressions(json.loads(text), summary, progress.load_accepted_drops())]


def change_word(old: dict | None, new: dict | None) -> str:
    if old is None:
        return "new"
    if new is None:
        return "removed"
    return "raised" if scoring.score(new) > scoring.score(old) else "dropped"


def score_changes(baseline: dict, current: dict, game: set[int], sizes: dict[int, int]) -> str:
    """Markdown for the job summary: the totals before and after, then each function whose score moved, at most
    JOB_SUMMARY_ROWS of them."""
    before, after = scoring.totals(baseline, game), scoring.totals(current, game)
    code_before, code_after = scoring.code_bytes(baseline, game, sizes), scoring.code_bytes(current, game, sizes)
    lines = ["### Scores against the base", "", "| | Before | After |", "| --- | --- | --- |",
             f"| Game functions matched | {before.matched:,} | {after.matched:,} |",
             f"| Code bytes matched | {code_before.matched:,} | {code_after.matched:,} |", ""]
    moved = scoring.moved_scores(baseline, current)
    if not moved:
        return "\n".join(lines + ["No score moved.", ""])
    old, new = scoring.entries_by_address(baseline), scoring.entries_by_address(current)
    lines += ["| Function | Before | After | Change |", "| --- | --- | --- | --- |"]
    for address in moved[:JOB_SUMMARY_ROWS]:
        was, now = old.get(address), new.get(address)
        lines.append(f"| `0x{address:08x}` {osutil.table_cell((now or was)['name'])} | {scoring.state_text(was)} | "
                     f"{scoring.state_text(now)} | {change_word(was, now)} |")
    if len(moved) > JOB_SUMMARY_ROWS:
        lines += ["", f"And {len(moved) - JOB_SUMMARY_ROWS:,} more."]
    return "\n".join(lines) + "\n"


def write_job_summary(summary: dict, base: str) -> None:
    """On GitHub Actions, add the score changes against the base to the job's summary page."""
    path, text = os.environ.get("GITHUB_STEP_SUMMARY"), at_base(base, progress.SUMMARY_JSON)
    if not path or text is None:
        return
    functions = progress.load_functions()
    game = progress.game_addresses(functions)
    with open(path, "a", encoding="utf-8") as out:
        out.write(score_changes(json.loads(text), summary, game, progress.function_sizes(functions)))


def check_visuals() -> list[str]:
    stale = [path for path, text in progress.render_all().items()
             if not path.exists() or path.read_text(encoding="utf-8") != text]
    return [f"{path.relative_to(ROOT).as_posix()} differs from a fresh render. "
            "Run `python tools/progress.py`; never edit generated text by hand." for path in stale]


def check_groups() -> list[str]:
    """Every function in data/functions.csv starts in exactly one code group and ends inside it."""
    groups = progress.load_codegen_groups()
    problems = []
    for function in progress.load_functions():
        group = progress.codegen_group(groups, function["address"])
        if group is None:
            problems.append(f"0x{function['address']:08x} {function['name']}: in no code group")
        elif function["address"] + function["size"] > group["end"]:
            problems.append(f"0x{function['address']:08x} {function['name']}: ends past group {group['group']}")
    if len(problems) > MAX_LINES:
        problems[MAX_LINES:] = [f"and {len(problems) - MAX_LINES} more"]
    return problems


def check_no_binaries() -> list[str]:
    problems = []
    for path in repo_files("."):
        name = path.relative_to(ROOT).as_posix()
        if path.suffix.lower() in BINARY_SUFFIXES:
            problems.append(f"{name}: binaries do not belong in the repo")
        elif path.stat().st_size > MAX_FILE_BYTES:
            problems.append(f"{name}: over {MAX_FILE_BYTES // (1024 * 1024)} MB")
    return problems


def run_checks(base: str | None) -> int:
    """Print one line per check and return the number that failed."""
    if not progress.SUMMARY_JSON.exists():
        print("FAIL no scores yet: run `python tools/check.py save` once")
        return 1 + report([("every function is in one code group", check_groups),
                           ("no binaries or large files", check_no_binaries)])
    summary = progress.load_summary()
    resolved = resolve_base(base)
    checks = [("summary.json matches the build inputs", lambda: check_fresh(summary))]
    if resolved is None:
        print("note no base commit: old scores are not compared")
    else:
        checks += [("no score dropped", lambda: check_no_drops(summary, resolved))]
    checks += [
        ("history and visuals are current", check_visuals),
        ("every function is in one code group", check_groups),
        ("no binaries or large files", check_no_binaries),
    ]
    failed = report(checks)
    if resolved is not None:
        write_job_summary(summary, resolved)
    return failed


def report(checks: list) -> int:
    """Run each (label, check) and print its result. Returns the number that failed."""
    failed = 0
    for label, check in checks:
        problems = check()
        print(f"{'ok  ' if not problems else 'FAIL'} {label}")
        for line in problems:
            print(f"     {line}")
        failed += bool(problems)
    return failed
