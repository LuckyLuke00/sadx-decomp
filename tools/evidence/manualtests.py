"""Unit tests for manual.py, on made-up manual text.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/manualtests.py
run() calls every check and returns the failures. All names are made up.
"""

import sys
import tempfile
from collections import Counter
from pathlib import Path
from types import SimpleNamespace

sys.path.insert(0, str(Path(__file__).parent))

import config  # noqa: E402
import manual  # noqa: E402

FUNCTIONS = {"xxFoo", "xxBar", "xxBaz", "xxMac"}
TEXT = ("XX Library Contents xxFoo..........Does foo. xxBar ....Does bar. XX_ONLY_BEFORE "
        "xxFoo Does foo. FORMAT #include <xx.h> void xxFoo( mode ) Int mode PARAMETERS mode XX_MODE_Asource mode "
        "EXAMPLE xxBaz( XX_IN_EXAMPLE ); RELATED TOPICS xxBar "
        "xxBar Does bar. FORMAT #include <xx.h> void xxBar( a ); void xxBaz( b ) PARAMETERS XX_SHARED_FLAGText "
        "Contents xxQux............Does qux. "
        "xxUnknown Does nothing. FORMAT #include <xx.h> void xxUnknown( void ) PARAMETERS None "
        "xxGone (Unsupported) FORMAT PARAMETERS RETURN VALUE FUNCTION EXAMPLE NOTES "
        "FORMATTED text is no marker. FORMAT #define xxMac( a ) PARAMETERS a")


def parse(text: str = TEXT) -> manual.Reading:
    return manual.parse("xx.txt", text, FUNCTIONS.__contains__)


def check_names() -> list[str]:
    failures = []
    names = manual.names_of("XX_SOURCE_COLORsource color, XX_ASource xxFoo( x ) 16bit xxGluedtext Mixed_case")
    for wanted in ("XX_SOURCE_COLOR", "XX_A", "xxFoo", "xxGluedtext", "Mixed_case", "color"):
        if wanted not in names:
            failures.append(f"names: {wanted} missing from {sorted(names)}")
    for unwanted in ("16bit", "xxGlued", "XX_SOURCE_COLORsourc"):
        if unwanted in names:
            failures.append(f"names: {unwanted} found")
    return failures


def check_index() -> list[str]:
    failures = []
    reading = parse()
    if reading.index != 3:
        failures.append(f"index entries: got {reading.index}, wanted 3")
    named = set().union(*(section.names for section in reading.sections))
    if "xxQux" in named or "Does" not in named:
        failures.append("an index entry loses its name and keeps its description")
    return failures


def check_sections() -> list[str]:
    failures = []
    reading = parse()
    if reading.markers != 5:
        failures.append(f"markers: got {reading.markers}, wanted 5 (FORMATTED is no marker)")
    functions = [section.functions for section in reading.sections]
    if functions != [("xxFoo",), ("xxBar", "xxBaz"), ("xxMac",)]:
        failures.append(f"functions: the calls in the head only, a macro counts: got {functions}")
    first = reading.sections[0].names
    if "XX_MODE_A" not in first or "XX_IN_EXAMPLE" not in first or "XX_ONLY_BEFORE" in first:
        failures.append(f"the section runs from its marker to the next: got {sorted(first)}")
    if "XX_SHARED_FLAG" not in reading.sections[1].names:
        failures.append("a glued capital word gives the name before it")
    if reading.dropped != Counter({manual.UNKNOWN: 1, manual.NO_PROTOTYPE: 1}):
        failures.append(f"dropped: got {reading.dropped}")
    if reading.unknown != Counter({"xxUnknown": 1}):
        failures.append(f"unknown: got {reading.unknown}")
    return failures


def check_read() -> list[str]:
    failures = []
    closure = SimpleNamespace(functions={"xxFoo": [None]}, macros=SimpleNamespace(is_function="xxMac".__eq__))
    other = SimpleNamespace(functions={"xxBar": [None]}, macros=SimpleNamespace(is_function=lambda name: False))
    found = SimpleNamespace(closures=[("ref", closure), ("other", other)])
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder) / "xx.txt"
        path.write_bytes(TEXT.encode("latin-1"))
        loaded = SimpleNamespace(manuals=(config.Manual(path, "ref", "latin-1"),))
        functions = [section.functions for section in manual.read(loaded, found)[0].sections]
        if functions != [("xxFoo",), ("xxMac",)]:
            failures.append(f"read: only the functions of the manual's reference set: got {functions}")
        path.write_bytes(b"\xff")
        loaded = SimpleNamespace(manuals=(config.Manual(path, "ref", "utf-8"),))
        failures += _fails(lambda: manual.read(loaded, found), "does not decode as utf-8")
        loaded = SimpleNamespace(manuals=(config.Manual(Path(folder) / "gone.txt", "ref", "latin-1"),))
        failures += _fails(lambda: manual.read(loaded, found), "missing manual")
    return failures


def _fails(call, wanted: str) -> list[str]:
    try:
        call()
    except config.ConfigError as error:
        return [] if wanted in str(error) else [f"error text: got {error}"]
    return [f"no error, wanted {wanted!r}"]


def check_by_function() -> list[str]:
    one = manual.Reading("a", sections=[manual.Section(("xxFoo", "xxBar"), frozenset({"XX_A"}))])
    two = manual.Reading("b", sections=[manual.Section(("xxFoo",), frozenset({"XX_B"}))])
    got = manual.by_function([one, two])
    wanted = {"xxFoo": (frozenset({"XX_A"}), frozenset({"XX_B"})), "xxBar": (frozenset({"XX_A"}),)}
    return [] if got == wanted else [f"by_function: got {got}"]


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_names, check_index, check_sections, check_read, check_by_function):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    print("\n".join(found) or "manualtests: all passed")
    sys.exit(1 if found else 0)
