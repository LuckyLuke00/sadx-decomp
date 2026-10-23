"""Checks for the data scores and emblems in tools/scoring.py, the text it shows for a share, and the job summary of
tools/ci.py."""

import ci
import scoring


def summary(*data: tuple[str, int, bool], data_bytes: int = 100) -> dict:
    """A summary with no functions and one game data entry per (address, size, match)."""
    return {"functions": [], "data_bytes": data_bytes,
            "data": [{"address": address, "name": "g", "size": size, "match": match, "library": False}
                     for address, size, match in data]}


def check_count_text() -> list[str]:
    """The count text shows the thousands and the percent, and 0 of 0 shows 0%."""
    cases = [((1234, 5000, "bytes"), "1,234 of 5,000 bytes (24.68%)"), ((0, 0, "bytes"), "0 of 0 bytes (0.00%)")]
    return [f"count_text{args} gives {scoring.count_text(*args)}, not {wanted}"
            for args, wanted in cases if scoring.count_text(*args) != wanted]


def check_data_share() -> list[str]:
    """Only matching game globals count, by size, over the initialized data. A runtime library global counts in
    neither part. A summary from before data scoring gives 0 of 0."""
    with_library = summary(("0x00a00000", 8, True), ("0x00a00008", 4, False), ("0x00a0000c", 16, True))
    with_library["data"][-1]["library"] = True
    cases = [(with_library, (8, 84)), ({"functions": []}, (0, 0))]
    return [f"data_share gives {scoring.data_share(found)}, not {wanted}"
            for found, wanted in cases if scoring.data_share(found) != wanted]


def check_data_regressions() -> list[str]:
    """A matching global that differs or is gone is a drop. A global that never matched, a new one, and a baseline
    from before data scoring drop nothing."""
    old = summary(("0x00a00000", 4, True), ("0x00a00004", 4, False))
    cases = [("a global that differs", summary(("0x00a00000", 4, False), ("0x00a00004", 4, False)), 1),
             ("a global that is gone", summary(("0x00a00004", 4, False)), 1),
             ("an unchanged list", old, 0),
             ("a new global", summary(("0x00a00000", 4, True), ("0x00a00004", 4, True), ("0x00a00008", 4, True)), 0)]
    failures = [f"find_regressions finds {len(scoring.find_regressions(old, current))} drops for {name}, not {wanted}"
                for name, current, wanted in cases if len(scoring.find_regressions(old, current)) != wanted]
    if scoring.find_regressions({"functions": []}, old):
        failures.append("find_regressions finds a drop against a baseline with no data list")
    return failures


def check_emblems() -> list[str]:
    """A code emblem needs its share of the game's bytes, rounded up. An area emblem needs all of its bytes."""
    found = scoring.emblems(scoring.Bytes(900, 50, 999), [("Area", scoring.Bytes(10, 10, 10)),
                                                         ("Other", scoring.Bytes(10, 9, 10))])
    failures = []
    if len(found) != 100 // scoring.EMBLEM_STEP + 2:
        failures.append(f"emblems gives {len(found)} emblems, not one per {scoring.EMBLEM_STEP}% and one per area")
    if found[0] != scoring.Emblem("5% of the game's code", 50, 50) or found[-3].needed != 999:
        failures.append(f"emblems needs {found[0].needed} and {found[-3].needed} bytes, not 50 and 999")
    if [emblem.earned for emblem in found[-2:]] != [True, False] or scoring.earned_count(found) != 2:
        failures.append("emblems does not earn exactly the 5% emblem and the area at 10 of 10 bytes")
    return failures


def check_score_changes() -> list[str]:
    """The job summary shows the totals before and after, and one row for each moved function with its change. A name
    can't break its row."""
    def entry(address, accuracy, name="f"):
        return {"address": address, "name": name, "accuracy": accuracy, "stub": False, "library": False,
                "effective": False}

    old = {"functions": [entry("0x00401000", 0.5), entry("0x00401010", 1.0), entry("0x00401020", 0.7)]}
    new = {"functions": [entry("0x00401000", 1.0), entry("0x00401010", 0.9), entry("0x00401030", 1.0, "a<b>|c")]}
    game = {0x401000, 0x401010, 0x401020, 0x401030}
    text = ci.score_changes(old, new, game, dict.fromkeys(game, 10))
    wanted = ["| Game functions matched | 1 | 2 |", "| Code bytes matched | 10 | 20 |",
              "| `0x00401000` f | 50.0% | 100% | raised |", "| `0x00401010` f | 100% | 90.0% | dropped |",
              "| `0x00401020` f | 70.0% | none | removed |", "| `0x00401030` a&lt;b&gt;\\|c | none | 100% | new |"]
    failures = [f"score_changes has no line {line!r}" for line in wanted if line not in text.splitlines()]
    if "No score moved." not in ci.score_changes(old, old, game, dict.fromkeys(game, 10)):
        failures.append("score_changes does not say that no score moved")
    return failures


def run() -> list[str]:
    """Every check of this module, in order."""
    failures = []
    for check in (check_count_text, check_data_share, check_data_regressions, check_emblems, check_score_changes):
        failures += check()
    return failures
