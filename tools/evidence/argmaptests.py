"""Unit tests for argmap.py: reading argmap.csv, the prototype check and the hygiene warnings.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/argmaptests.py
run() calls every check and returns the failures. All names are made up.
"""

import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import argmap  # noqa: E402
from argmap import ArgmapError  # noqa: E402
from cheaders import Function, Origin  # noqa: E402

HEADER = ",".join(argmap.COLUMNS)
GOOD = (f"{HEADER}\n"
        "xxTurn,2,value,XX_ANGLE_ XX_RIGHT,header prototype,xxapi.h,Angle,,turn amount\n"
        "xxDraw,3,flags,XX_SPRITE_,header prototype,sdk/xxapi.h,Uint32  ,vendor other,\n"
        "Wrap,1,and-mask,XX_FLAG_,unverified,,,,game wrapper\n")


def read(text: str):
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder) / "argmap.csv"
        path.write_text(text, encoding="utf-8")
        try:
            return argmap.read_argmap(path)
        except ArgmapError as error:
            return str(error)


def check_read() -> list[str]:
    failures = []
    rows = read(GOOD)
    if isinstance(rows, str):
        return [f"good argmap failed: {rows}"]
    turn, draw, wrap = rows
    if (turn.slot, turn.groups, turn.spelled_type, turn.line) != (2, ("XX_ANGLE_", "XX_RIGHT"), "Angle", 2):
        failures.append(f"row {turn}")
    if (draw.spelled_type, draw.origins, wrap.status) != ("Uint32", ("vendor", "other"), "unverified"):
        failures.append(f"rows {draw}, {wrap}")
    if not turn.takes("XX_ANGLE_90") or not turn.takes("XX_RIGHT") or turn.takes("XX_RIGHTMOST"):
        failures.append("group matching")
    cases = (
        ("callee,slot\n", "the columns must be"),
        (GOOD + "xxTurn,2,value,XX_,unverified,,,,\n", "also on line 2"),
        (f"{HEADER}\nf,0,value,A,unverified,,,,\n", "not an argument number"),
        (f"{HEADER}\nf,1,bits,A,unverified,,,,\n", "mode 'bits'"),
        (f"{HEADER}\nf,1,value,A,maybe,,,,\n", "status 'maybe'"),
        (f"{HEADER}\nf,1,value,,unverified,,,,\n", "no groups"),
        (f"{HEADER}\nf,1,value,A,header prototype,,int,,\n", "needs a header"),
    )
    for text, wanted in cases:
        got = read(text)
        if not isinstance(got, str) or wanted not in got:
            failures.append(f"argmap error {got!r}, want {wanted!r}")
    with tempfile.TemporaryDirectory() as folder:
        try:
            argmap.read_argmap(Path(folder) / "argmap.csv")
            failures.append("a missing argmap.csv was read")
        except ArgmapError as error:
            if "missing hand-owned file" not in str(error):
                failures.append(f"missing argmap: {error}")
    return failures


def function(file: str, *parameters: str, variadic: bool = False) -> Function:
    return Function("xxTurn", "void", parameters, variadic, Origin(file, 1, True))


def check_prototypes() -> list[str]:
    failures = []
    turn, draw, wrap = read(GOOD)
    cases = (
        (turn, [function("D:/sdk/Include/XXAPI.H", "Int", "Angle")], ""),
        (turn, [function("game/xxapi.h", "Int", "Sint32"), function("other.h", "Int", "Angle")], "spells argument 2"),
        (turn, [function("other.h", "Int", "Angle")], "no prototype of xxTurn in xxapi.h"),
        (turn, [function("xxapi.h", "Int")], "argument 2 of 1"),
        (turn, [function("xxapi.h", "Int", variadic=True)], "a variadic argument"),
        (turn, [function("xxapi.h", "Int", "Angle"), function("xxapi.h", "Int", "int")], "different parameters"),
        (draw, [function("x/sdk/xxapi.h", "a *", "Int", "Uint32")], ""),
        (draw, [function("xxapi.h", "a *", "Int", "Uint32")], "no prototype"),
        (wrap, [function("xxapi.h", "Uint32")], "unverified row"),
    )
    for row, functions, wanted in cases:
        check = argmap.check_prototype(row, functions)
        if check.passed != (wanted == "") or wanted not in check.reason:
            failures.append(f"{row.callee} against {functions}: got {check}, want {wanted!r}")
    warnings = argmap.hygiene(read(GOOD) + read(f"{HEADER}\n__except,1,value,A,unverified,,,,\n"), {"xxTurn"},
                              {"xxDraw"})
    if warnings != ["argmap callee Wrap matches no annotated function and no header declaration"]:
        failures.append(f"hygiene {warnings}")
    return failures


def run() -> list[str]:
    failures = []
    for check in (check_read, check_prototypes):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    for failure in found:
        print(failure)
    if not found:
        print("argmaptests: all passed")
    sys.exit(1 if found else 0)
