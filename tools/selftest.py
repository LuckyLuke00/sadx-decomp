"""The self-test of check.py: prove the toolchain and reccmp on the known program in tests/selftest.

run() builds nothing: CMake already built the original and our twin. It checks the
original's hash, the scores reccmp gives, the regression gate, the register-argument
search and the totals against what tests/selftest pins.
"""

import copy
import json
import re
from pathlib import Path

import osutil
import pe
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

    if failures:
        print("FAIL self-test")
        for line in failures:
            print(f"     {line}")
        return 1
    print(f"ok   self-test: build hash {original_hash[:12]}..., exact scores, regression gate, /GL call, totals")
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
    """The regression gate passes on the pinned baseline and fires on a drop."""
    failures = []
    false_alarms = scoring.find_regressions(expected, current)
    if false_alarms:
        failures.append(f"gate flagged a regression on identical scores: {false_alarms}")
    dropped = copy.deepcopy(current)
    dropped["functions"][0]["accuracy"] = 0.5
    if len(scoring.find_regressions(current, dropped)) != 1:
        failures.append("gate missed a deliberate score drop")
    return failures


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
