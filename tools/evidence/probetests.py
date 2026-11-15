"""Unit tests for probe.py that need no cl.exe: the probe program, the decode of its output, the comparison with
ceval, the random expressions and the error for a missing toolchain.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/probetests.py
run() calls every check and returns the failures. All expressions are made up.
"""

import random
import re
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import ceval  # noqa: E402
import probe  # noqa: E402
import profiles  # noqa: E402

CPP = profiles.get("msvc-vc10-x86-cpp")
INT, UNSIGNED, LONG_LONG = CPP.int_type("int"), CPP.int_type("unsigned int"), CPP.int_type("long long")
FLOAT, DOUBLE, BOOL = CPP.builtin(("float",)), CPP.builtin(("double",)), CPP.builtin(("bool",))
CASES = [(probe.INT, "-1"), (probe.INT, "0xFFFFFFFF"), (probe.INT, "(char)-1"), (probe.INT, "1i64"),
         (probe.F32, "1.0f"), (probe.PP, "1"), (probe.INT, "1 << 32")]
OUTPUT = {0: "4 1 18446744073709551615 int", 1: "4 0 4294967295 unsigned int", 2: "1 2 18446744073709551615 char",
          3: "8 1 1 __int64", 4: "3f800000", 5: "1"}
ERRORS, WARNINGS = {6: "C2148"}, {0: ["C4146"]}
DECODED = [
    {"kind": probe.INT, "text": "-1", "warnings": ["C4146"], "value": -1, "bits": 32, "signed": True, "type": "int"},
    {"kind": probe.INT, "text": "0xFFFFFFFF", "warnings": [], "value": 4294967295, "bits": 32, "signed": False,
     "type": "unsigned int"},
    {"kind": probe.INT, "text": "(char)-1", "warnings": [], "value": -1, "bits": 8, "signed": None, "type": "char"},
    {"kind": probe.INT, "text": "1i64", "warnings": [], "value": 1, "bits": 64, "signed": True, "type": "long long"},
    {"kind": probe.F32, "text": "1.0f", "warnings": [], "pattern": "3f800000"},
    {"kind": probe.PP, "text": "1", "warnings": [], "value": 1},
    {"kind": probe.INT, "text": "1 << 32", "error": "C2148"},
]


def check_program() -> list[str]:
    """Each case owns the lines with its own code, so a compiler error maps back to its case. A skipped case owns
    none."""
    failures = []
    source = probe.program(CASES, {6})
    owned = {}
    for line, case in source.owner.items():
        owned.setdefault(case, []).append(source.lines[line - 1])
    if sorted(owned) != [0, 1, 2, 3, 4, 5]:
        failures.append(f"cases that own lines: {sorted(owned)}")
    for case, lines in owned.items():
        failures += [f"case {case} owns {line!r}" for line in lines if CASES[case][1] not in line]
    if "1 << 32" in source.text():
        failures.append("the skipped case is in the program")
    return failures


def fake_results(language: str) -> dict:
    """probe.results on CASES, with the compiler run replaced by OUTPUT, ERRORS and WARNINGS."""
    output = {f"define {name}": None for name in probe.PREDEFINES} | {"define _MSC_VER": "1600"} | OUTPUT
    real = probe.compile_and_run
    probe.compile_and_run = lambda cases, language: (ERRORS, WARNINGS, output, "Version 16.00")
    try:
        return probe.results(CASES, language)
    finally:
        probe.compile_and_run = real


def check_results() -> list[str]:
    """The program's output lines decode into fixture cases: sign, width, value and the C++ type name."""
    failures = []
    found = fake_results("cpp")
    if found["cases"] != DECODED:
        failures += [f"case {case['text']!r}: {case}, wanted {wanted}"
                     for case, wanted in zip(found["cases"], DECODED) if case != wanted]
    if found["predefines"]["_MSC_VER"] != "1600" or found["predefines"]["_DEBUG"] is not None:
        failures.append(f"predefines {found['predefines']}")
    if found["flags"][-1] != "/TP" or found["compiler"] != "Version 16.00":
        failures.append(f"flags {found['flags']}, compiler {found['compiler']!r}")
    if any("type" in case for case in fake_results("c")["cases"]):
        failures.append("a C fixture holds a C++ type name")
    return failures


def check_disagreement() -> list[str]:
    """Every branch of probe.disagreement: None when ceval agrees, else a text that names both sides."""
    ok = ceval.OK
    warned = {"kind": probe.INT, "text": "x", "warnings": ["C4293"], "value": 1, "bits": 32, "signed": True}
    clean = dict(warned, warnings=[], type="int")
    truth = {"kind": probe.PP, "text": "x", "warnings": [], "value": 1}
    single = {"kind": probe.F32, "text": "x", "warnings": [], "pattern": "3f800000"}
    unsupported = ceval.Result(ceval.UNSUPPORTED, cause="shift count")
    cases = [
        ({"kind": probe.INT, "text": "x", "error": "C2148"}, ceval.Result(ok, 1, INT), "cpp",
         "compiler error C2148, ceval gives 1"),
        ({"kind": probe.INT, "text": "x", "error": "C2148"}, unsupported, "cpp", None),
        (warned, unsupported, "cpp", None),
        (clean, unsupported, "cpp", "compiler gives 1, ceval unsupported: shift count"),
        (truth, ceval.Result(ok, 5, INT), "cpp", None),
        (truth, ceval.Result(ok, 0, INT), "cpp", "compiler truth 1, ceval 0"),
        (single, ceval.Result(ok, 1.0, FLOAT), "cpp", None),
        (single, ceval.Result(ok, 2.0, FLOAT), "cpp", "compiler 3f800000, ceval 40000000"),
        (single, ceval.Result(ok, 1.0, DOUBLE), "cpp", "compiler type f32, ceval double"),
        (clean, ceval.Result(ok, 1, INT), "cpp", None),
        (clean, ceval.Result(ok, 2, INT), "cpp", "compiler 1, ceval 2"),
        (clean, ceval.Result(ok, 1, LONG_LONG), "cpp", "compiler 32 bits signed=True, ceval long long"),
        (clean, ceval.Result(ok, 1, UNSIGNED), "cpp", "compiler 32 bits signed=True, ceval unsigned int"),
        (dict(clean, type="bool"), ceval.Result(ok, 1, BOOL), "cpp", None),
        (dict(clean, type="long"), ceval.Result(ok, 1, INT), "cpp", "compiler type long, ceval int"),
        (dict(clean, type="long"), ceval.Result(ok, 1, INT), "c", None),
    ]
    failures = []
    for case, result, language, wanted in cases:
        found = probe.disagreement(case, result, language)
        if (found is None) != (wanted is None) or (wanted and wanted not in found):
            failures.append(f"{case} with {result}: {found!r}, wanted {wanted!r}")
    return failures


def check_random() -> list[str]:
    """One seed gives one list. A divisor is never the literal 0, and only C++ casts to bool."""
    failures = []
    first, second = ([probe.random_expression(random.Random(seed), 4, "c") for seed in range(300)] for _ in range(2))
    if first != second:
        failures.append("one seed gave two lists")
    zero_divisors = [text for text in first if re.search(r"[/%] 0\)", text)]
    if zero_divisors:
        failures.append(f"a 0 divisor in {zero_divisors[:3]}")
    if any("(bool)" in text for text in first):
        failures.append("a C expression casts to bool")
    return failures


def probe_error(folder: Path, run=None) -> str:
    """The ProbeError text of compile_and_run with the toolchain in FOLDER and subprocess.run replaced by RUN."""
    real = probe.TOOLCHAIN, probe.BUILD, probe.subprocess.run
    probe.TOOLCHAIN, probe.BUILD = folder / "toolchain", folder / "build"
    probe.subprocess.run = run or real[2]
    try:
        probe.compile_and_run(CASES, "cpp")
        return ""
    except probe.ProbeError as error:
        return str(error)
    finally:
        probe.TOOLCHAIN, probe.BUILD, probe.subprocess.run = real


def crashed_program(command: list[str], **_) -> subprocess.CompletedProcess:
    """A subprocess.run stand-in: cl.exe builds with no diagnostics, and the probe program exits with 3."""
    code = 3 if command[0].endswith("probe-cpp.exe") else 0
    return subprocess.CompletedProcess(command, code, "", "stack overflow")


def check_errors() -> list[str]:
    """A missing toolchain is a ProbeError that names the setup command, raised before anything is written. A probe
    program that exits nonzero is a ProbeError too, not a traceback."""
    failures = []
    with tempfile.TemporaryDirectory() as name:
        folder = Path(name)
        found = probe_error(folder)
        if "tools/check.py setup" not in found or (folder / "build").exists():
            failures.append(f"a missing toolchain gave {found!r}, build folder written: {(folder / 'build').exists()}")
        (folder / "toolchain" / "bin").mkdir(parents=True)
        (folder / "toolchain" / "bin" / "cl.exe").touch()
        found = probe_error(folder, crashed_program)
        if "probe-cpp.exe exited with 3" not in found or "stack overflow" not in found:
            failures.append(f"a crashed probe program gave {found!r}")
    return failures


def check_diagnostics() -> list[str]:
    """Each diagnostic goes to the case that owns its line; a repeated warning counts once, the first error code
    wins, and an error on a line that no case owns is reported apart."""
    text = ("probe-cpp.c(4) : warning C4307: integral constant overflow\n"
            "probe-cpp.c(4) : warning C4307: integral constant overflow\n"
            "probe-cpp.c(5) : error C2124: divide or mod by zero\n"
            "probe-cpp.c(5) : error C2057: expected constant expression\n"
            "probe-cpp.c(9) : fatal error C1004: unexpected end-of-file found\n"
            "probe-cpp.c(9) : warning C4100: unreferenced formal parameter\n")
    got = probe._diagnostics(text, {4: 0, 5: 1})
    wanted = ({1: "C2124"}, {0: ["C4307"]}, ["(9) : fatal error C1004"])
    return [] if got == wanted else [f"diagnostics: got {got}, want {wanted}"]


def run() -> list[str]:
    failures = []
    for check in (check_program, check_results, check_disagreement, check_random, check_errors, check_diagnostics):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    for failure in found:
        print(failure)
    if not found:
        print("probetests: all passed")
    sys.exit(1 if found else 0)
