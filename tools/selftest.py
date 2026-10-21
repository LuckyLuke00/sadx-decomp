"""The self-test of check.py: prove the toolchain and reccmp on the known program in tests/selftest.

run() builds nothing: CMake already built the original and our twin. It checks the
original's hash, the scores reccmp gives, the regression gate, the register-argument
search and the totals against what tests/selftest pins. It also checks the history
rules of progress.py on changed copies of the pinned scores, its git reader on a
throwaway repository, and where the annotation lint lets a function annotation sit.
"""

import copy
import json
import re
import tempfile
from pathlib import Path

import osutil
import pe
import progress
import project
import runner
import scoring

ROOT = project.ROOT
BUILD = project.BUILD
# The self-test is its own reccmp project, so reccmp-project.yml holds only the game.
SELFTEST = ROOT / "tests" / "selftest"
SELFTEST_EXPECTED = SELFTEST / "expected.json"
SELFTEST_ORIGINAL = BUILD / "selftest-original" / "SELFTEST.exe"
SELFTEST_MAP = SELFTEST_ORIGINAL.with_suffix(".map")
SELFTEST_OURS = BUILD / "SELFTEST.exe"
SELFTEST_BUILD = BUILD / "selftest-reccmp"  # reccmp runs here for the self-test


def run() -> int:
    """Prove the toolchain and reccmp on the known program in tests/selftest."""
    expected = json.loads(SELFTEST_EXPECTED.read_text(encoding="utf-8"))
    original_hash, failures = check_original_hash()
    spans = map_functions(SELFTEST_MAP)
    current = score_selftest(spans)
    failures += check_scores(expected, current)
    failures += check_regression_gate(expected, current)
    failures += check_register_arguments(current, spans)
    failures += check_totals(expected, current)
    failures += check_whole_percent()
    failures += check_moved_scores(expected)
    failures += check_history_rows(expected)
    failures += check_empty_map()
    failures += check_block_names()
    failures += check_gem_colors()
    failures += check_read_blobs()
    failures += check_misplaced_annotations()

    if failures:
        print("FAIL self-test")
        for line in failures:
            print(f"     {line}")
        return 1
    print(f"ok   self-test: build hash {original_hash[:12]}..., exact scores, regression gate, /GL call, totals, history, "
          "annotation lint")
    return 0


def check_original_hash() -> tuple[str, list[str]]:
    """The toolchain is deterministic and identical to the one that pinned the hash."""
    project_yml = SELFTEST / "reccmp-project.yml"
    pinned = project.read_yml(project_yml)["targets"]["SELFTEST"]["hash"]["sha256"]
    original_hash = osutil.sha256(SELFTEST_ORIGINAL)
    if original_hash == pinned:
        return original_hash, []
    return original_hash, [f"original build hash {original_hash} != {pinned} in "
                           f"{project_yml.relative_to(ROOT).as_posix()}: the compiler, libraries or flags differ"]


def score_selftest(spans: list[tuple[int, int]]) -> dict:
    """Score the self-test with reccmp, with its function sizes and the constants of an original
    that has no relocations."""
    import constants

    build = runner.Build("SELFTEST", SELFTEST, SELFTEST_OURS, SELFTEST_BUILD)
    runner.write_user_yml(SELFTEST / "reccmp-user.yml", "SELFTEST", SELFTEST_ORIGINAL)
    runner.write_build_yml(build)
    # SELFTEST_FLAGS in CMakeLists.txt have /O2, which pools strings.
    runner.write_constants_csv(SELFTEST_BUILD / "constants.csv", SELFTEST_ORIGINAL,
                               [constants.Function(address, size, True) for address, size in spans])
    runner.write_sizes_csv(SELFTEST_BUILD / "sizes.csv", spans)
    return runner.summarize("SELFTEST", runner.score_target(build, SELFTEST_ORIGINAL))


def check_scores(expected: dict, current: dict) -> list[str]:
    """reccmp scores every outcome exactly as pinned: match, near miss, stub, /GL, and the
    constants of an original without relocations."""
    if current["functions"] == expected["functions"]:
        return []
    return ["scores differ from expected.json:\n"
            f"    expected {json.dumps(expected['functions'])}\n"
            f"    actual   {json.dumps(current['functions'])}"]


def check_regression_gate(expected: dict, current: dict) -> list[str]:
    """The regression gate passes on the pinned baseline and a removed stub, and fires on a drop."""
    failures = []
    false_alarms = scoring.find_regressions(expected, current)
    if false_alarms:
        failures.append(f"gate flagged a regression on identical scores: {false_alarms}")
    if len(scoring.find_regressions(current, with_first_accuracy(current, 0.5))) != 1:
        failures.append("gate missed a deliberate score drop")
    if scoring.find_regressions(current, without_stubs(current)):
        failures.append("gate flagged a removed stub, which scores zero")
    return failures


def check_moved_scores(expected: dict) -> list[str]:
    """A stub added or removed moves no score. A new accuracy moves one, and so does a removed
    match: a missing function scores zero."""
    unstubbed = without_stubs(expected)
    unmatched = dict(expected, functions=expected["functions"][1:])
    first = [int(expected["functions"][0]["address"], 16)]
    cases = [("a removed stub", expected, unstubbed, []),
             ("an added stub", unstubbed, expected, []),
             ("a new accuracy", expected, with_first_accuracy(expected, 0.5), first),
             ("a removed match", expected, unmatched, first)]
    failures = []
    for name, baseline, current, wanted in cases:
        moved = scoring.moved_scores(baseline, current)
        if moved != wanted:
            failures.append(f"moved_scores gives {moved} for {name}, not {wanted}")
    return failures


def check_history_rows(expected: dict) -> list[str]:
    """The history gets a row for the first commit and for each commit that changed the totals, two commits of one
    day included, and none for a commit that only removes or adds a stub. A commit that undoes the one before gets
    a row too. The working tree gets a row only when it changed the totals."""
    game = {int(entry["address"], 16) for entry in expected["functions"]}
    dropped = with_first_accuracy(expected, 0.5)
    later = with_first_accuracy(expected, 0.25)
    commits = [progress.Snapshot("2026-01-01", expected, game),
               progress.Snapshot("2026-01-02", without_stubs(expected), game),
               progress.Snapshot("2026-01-03", expected, game),
               progress.Snapshot("2026-01-04", dropped, game),
               progress.Snapshot("2026-01-04", later, game)]
    rows_of_commits = [("2026-01-01", expected), ("2026-01-04", dropped), ("2026-01-04", later)]
    # (case, the snapshots after the commits, the day and scores of each row)
    cases = [("an unchanged working tree", [("2026-01-05", later)], rows_of_commits),
             ("a working tree that changed the totals", [("2026-01-05", expected)],
              rows_of_commits + [("2026-01-05", expected)]),
             ("a commit that undoes the one before", [("2026-01-05", dropped), ("2026-01-05", later)],
              rows_of_commits + [("2026-01-05", dropped), ("2026-01-05", later)])]
    failures = []
    for name, more, wanted in cases:
        snapshots = commits + [progress.Snapshot(day, summary, game) for day, summary in more]
        rows = progress.history_rows(snapshots)
        if rows != [progress.history_row(day, scoring.totals(summary, game)) for day, summary in wanted]:
            failures.append(f"history rows {[row['date'] for row in rows]} for {name}, not the "
                            f"{len(wanted)} rows of {[day for day, _ in wanted]}")
    return failures


def check_empty_map() -> list[str]:
    """A game with no game functions yet, such as a new port, gets a map of just its header and colour key."""
    summary = {"exe": "GAME.EXE", "functions": []}
    sections = progress.map_sections({}, [("Stages", None, {"stage": "Stages"})])
    svg = progress.render_map(summary, scoring.totals(summary, set()), sections, progress.LIGHT)
    height = progress.HEADER + progress.FOOTER
    if f'viewBox="0 0 {progress.WIDTH} {height}"' in svg:
        return []
    return [f"the map of a game with no game functions is not {height} px high"]


def check_block_names() -> list[str]:
    """A block shows its name unless its section has only one area in the map list, whose title names it. A section
    of two areas names its block also when only one of them has functions."""
    sections = [("Two areas", None, {"a": "Area A", "b": "Area B"}), ("One area", None, {"c": "Area C"})]
    found = progress.map_sections({0x401000: "a", 0x402000: "c"}, sections)
    labelled = [(block.name, block.labelled) for section in found for block in section.blocks]
    wanted = [("Area A", True), ("Area C", False)]
    return [] if labelled == wanted else [f"map blocks (name, labelled) {labelled}, not {wanted}"]


def check_gem_colors() -> list[str]:
    """A section's gem colour in data/areas.yml is a quoted #rrggbb string. Unquoted, the # starts a YAML comment, so
    the colour reads as null, and a number is no colour either: the map stops on both."""
    import areas  # here, not at the top: it needs .venv's packages, and check.py imports this module before .venv

    cases = [('"#2f6bff"', []), ("#2f6bff", ["Stages"]), ("123456", ["Stages"])]
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder) / "areas.yml"
        for color, wanted in cases:
            path.write_text(f"map:\n- section: Stages\n  color: {color}\n  areas: {{stage: Stages}}\n",
                            encoding="utf-8")
            found = areas.miscolored(project.read_yml(path))
            if found != wanted:
                failures.append(f"miscolored gives {found} for `color: {color}`, not {wanted}")
    return failures


def check_read_blobs() -> list[str]:
    """read_blobs gives the text of each spec from git's batch output, also when two specs share one blob."""
    files = {"a.txt": "same text\n", "b.txt": "same text\n", "c.txt": "other\ntext\n"}
    with tempfile.TemporaryDirectory() as folder:
        root = Path(folder)
        osutil.git(root, "init", "--quiet")
        for name, text in files.items():
            (root / name).write_text(text, encoding="utf-8", newline="\n")
        osutil.git(root, "add", *files)
        # A tree needs no commit, so no user name, hooks or signing.
        tree = osutil.git(root, "write-tree").decode().strip()
        texts = progress.read_blobs(root, [f"{tree}:{name}" for name in files])
    wanted = {f"{tree}:{name}": text for name, text in files.items()}
    if texts == wanted:
        return []
    return [f"read_blobs gave {texts}, not {wanted}"]


def check_misplaced_annotations() -> list[str]:
    """A STUB may start any function, such as a library function that game code calls. Any other function annotation
    must start a game function."""
    game, library = 0x401000, 0x402000
    annotations = [(game, "FUNCTION at a game function", False), (library, "STUB at a library function", True),
                   (library, "FUNCTION at a library function", False), (library + 1, "STUB inside a function", True)]
    found = [where for _, where, _ in runner.misplaced(annotations, {game, library}, {game})]
    expected = ["FUNCTION at a library function", "STUB inside a function"]
    return [] if found == expected else [f"annotation lint flags {found}, not {expected}"]


def without_stubs(summary: dict) -> dict:
    return dict(summary, functions=[entry for entry in summary["functions"] if not entry["stub"]])


def with_first_accuracy(summary: dict, accuracy: float) -> dict:
    changed = copy.deepcopy(summary)
    changed["functions"][0]["accuracy"] = accuracy
    return changed


def check_register_arguments(current: dict, spans: list[tuple[int, int]]) -> list[str]:
    """The register-argument search of `check.py groups` finds the one call that /GL made, from Total to Mix."""
    import groups

    names = {entry["name"]: int(entry["address"], 16) for entry in current["functions"]}
    functions = groups.read_functions(pe.Image(SELFTEST_ORIGINAL), [(address, size, 0) for address, size in spans], {})
    sites = groups.register_argument_sites(functions, {})
    found = sorted((site.caller, site.callee) for site in sites)
    if found == [(names.get("Total"), names.get("Mix"))]:
        return []
    return [f"register-argument calls (caller, callee) {[(hex(a), hex(b)) for a, b in found]} "
            "are not the one from Total to Mix"]


def check_totals(expected: dict, current: dict) -> list[str]:
    """The totals leave a stub out of the decompiled count, and a library function out of the game total."""
    with_library = copy.deepcopy(current)
    with_library["functions"][0]["library"] = True
    totals = scoring.totals(with_library, {int(entry["address"], 16) for entry in current["functions"]})
    if totals._asdict() == expected["totals"]:
        return []
    return [f"totals {json.dumps(totals._asdict())} != {json.dumps(expected['totals'])} in expected.json"]


def check_whole_percent() -> list[str]:
    """A whole percent rounds down, so only a whole that is all done shows 100%. It counts in integers: 29 of 100 is
    29%, though 100 * 0.29 in floats is just under 29."""
    cases = [(0, 0, "0%"), (29, 100, "29%"), (199, 200, "99%"), (1, 1, "100%")]
    return [f"whole_percent({part}, {whole}) gives {scoring.whole_percent(part, whole)}, not {wanted}"
            for part, whole, wanted in cases if scoring.whole_percent(part, whole) != wanted]


def map_functions(path: Path) -> list[tuple[int, int]]:
    """(address, size) of each function from the self-test's own objects in a link map.
    Each runs to the next symbol in the code section."""
    symbols = []
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        parts = line.split()
        if len(parts) >= 4 and parts[0].startswith("0001:") and re.fullmatch(r"[0-9a-f]{8}", parts[2]):
            symbols.append((int(parts[2], 16), parts[-1]))
    symbols.sort()
    # A library member shows as library:object.
    return [(address, following - address) for (address, source), (following, _) in zip(symbols, symbols[1:])
            if ":" not in source]
