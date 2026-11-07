"""Unit tests for decisions.py: notes.csv read and written back, its faults, the latest decision per id, the one-line
description, the review hash, and decide() and spelled_candidate() on a hand-built ledger.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/decisionstests.py
run() calls every check and returns the failures. All names are made up.
"""

import sys
import tempfile
from dataclasses import replace
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import decisions  # noqa: E402
import ledger  # noqa: E402

TIME = "2026-01-01T00:00:00+00:00"
ROW = ledger.Row("S000001", ledger.VALUE, "open", "3", "XX_A | XX_B; XX_C", "A", "B", "", "", "f00", "2026-01-01",
                 "2026-01-01", "src/a.c", 4)
ROWS = {"S000001": ROW, "S000002": replace(ROW, id="S000002", candidates=""),
        "S000003": replace(ROW, id="S000003", status=ledger.GONE)}
DECISION = decisions.Decision("S000001", decisions.CONFIRM, "XX_A | XX_B", "h", "f00", TIME, "a note, with a comma")
ALIASES = {"XX_A | XX_B": (("XX_A", "XX_AA"), ("XX_B",)), "XX_C": (("XX_C",),)}  # S000001's candidates


def check_file() -> list[str]:
    """The round trip, a missing file, and each fault with the text it gives."""
    failures = []
    with tempfile.TemporaryDirectory() as temp:
        path = Path(temp) / decisions.NOTES
        if decisions.read_notes(path) != []:
            failures.append("a missing notes file holds no decision")
        made = [DECISION, replace(DECISION, decision=decisions.REOPEN, candidate="", note="")]
        path.write_bytes(decisions.format_notes(made))
        if decisions.read_notes(path) != made:
            failures.append("notes.csv round-trips, a comma in a note included")
        data = path.read_bytes()
        lines = data.split(b"\n")
        for broken, wanted in ((b"id,decision\n", "not a notes file"),
                               (data.replace(b"schema=1", b"schema=2"), "notes schema 2"),
                               (b"\n".join([lines[0], b"id,decision"] + lines[2:]), "the columns must be"),
                               (data.replace(b",confirm,", b",approve,"), ":3: unknown decision 'approve'")):
            path.write_bytes(broken)
            try:
                decisions.read_notes(path)
                failures.append(f"no fault for {wanted!r}")
            except decisions.DecisionError as error:
                if wanted not in str(error):
                    failures.append(f"fault {error}, wanted {wanted!r}")
    return failures


def check_latest_and_describe() -> list[str]:
    """The latest decision per id wins; describe() gives one line, with the note when there is one; the review hash
    changes with the candidates and with each tier, and the field bounds count."""
    failures = []
    later, other = replace(DECISION, decision=decisions.REJECT), replace(DECISION, id="S000002")
    if decisions.latest([DECISION, other, later]) != {"S000001": later, "S000002": other}:
        failures.append("the latest decision per id wins")
    if decisions.describe(DECISION) != f"confirm XX_A | XX_B at {TIME}: a note, with a comma":
        failures.append(f"describe {decisions.describe(DECISION)!r}")
    reopened = replace(DECISION, decision=decisions.REOPEN, candidate="", note="")
    if decisions.describe(reopened) != f"reopen - at {TIME}":
        failures.append(f"describe {decisions.describe(reopened)!r}")
    inputs = (("XX_A", "A", "B"), ("XX_B", "A", "B"), ("XX_A", "B", "B"), ("XX_A", "A", "C"), ("XX_AA", "", "B"),
              ("XX_A", "A", "B "))
    if len({decisions.review_hash(*items) for items in inputs}) != len(inputs):
        failures.append("the review hash changes with the candidates and with each tier")
    return failures


def check_decide() -> list[str]:
    """The top candidate by default, a named candidate, a candidate with other aliases, the orphan warning, each
    fault, and a failed decide writes nothing."""
    failures = []
    with tempfile.TemporaryDirectory() as temp:
        folder = Path(temp)
        made, warnings = decisions.decide(folder, ROWS, "S000001", decisions.CONFIRM, "", "", TIME, ALIASES)
        if (made.candidate, made.fingerprint, made.time, warnings) != ("XX_A | XX_B", "f00", TIME, []):
            failures.append(f"confirm takes the top candidate: {made}, {warnings}")
        if made.hash != decisions.review_hash(ROW.candidates, ROW.tier, ROW.spelling_tier):
            failures.append("the decision stores the row's review hash")
        made, _ = decisions.decide(folder, ROWS, "S000001", decisions.REJECT, "XX_C", "not this one", TIME, ALIASES)
        if (made.candidate, made.note) != ("XX_C", "not this one"):
            failures.append(f"a named candidate: {made}")
        made, _ = decisions.decide(folder, ROWS, "S000001", decisions.CONFIRM, "XX_B | XX_AA", "", TIME, ALIASES)
        if made.candidate != "XX_B | XX_AA":
            failures.append(f"a candidate with another alias, in another order, keeps its spelling: {made}")
        _, warnings = decisions.decide(folder, ROWS, "S000003", decisions.REJECT, "", "", TIME, {})
        if warnings != ["S000003 is gone: the decision is orphaned"]:
            failures.append(f"a gone id warns: {warnings}")
        if [item.decision for item in decisions.read_notes(folder / decisions.NOTES)] != ["confirm", "reject",
                                                                                          "confirm", "reject"]:
            failures.append("each decision is appended")
        not_a_candidate = "is not a candidate of S000001"
        for site_id, decision, candidate, wanted in (
                ("S000009", decisions.CONFIRM, "", "S000009: no such id in the ledger"),
                ("S000001", decisions.CONFIRM, "XX_D", "'XX_D' " + not_a_candidate),
                ("S000001", decisions.CONFIRM, "XX_AA | XX_D", not_a_candidate),
                ("S000001", decisions.CONFIRM, "XX_A | XX_AA", not_a_candidate),
                ("S000001", decisions.CONFIRM, "XX_AA", not_a_candidate),
                ("S000001", decisions.CONFIRM, "~(XX_AA | XX_B)", not_a_candidate),
                ("S000001", decisions.REOPEN, "XX_C", "reopen takes no candidate"),
                ("S000002", decisions.CONFIRM, "", "S000002 has no candidate to confirm")):
            try:
                decisions.decide(folder, ROWS, site_id, decision, candidate, "", TIME, ALIASES)
                failures.append(f"no fault for {candidate or site_id}, wanted {wanted!r}")
            except decisions.DecisionError as error:
                if wanted not in str(error):
                    failures.append(f"fault {error}, wanted {wanted!r}")
        if len(decisions.read_notes(folder / decisions.NOTES)) != 4:
            failures.append("a failed decide writes nothing")
        made, _ = decisions.decide(folder, ROWS, "S000002", decisions.REOPEN, "", "", TIME, {})
        if made.candidate:
            failures.append(f"reopen takes no candidate, also on a row with none: {made}")
    return failures


def check_spelled_candidate() -> list[str]:
    """One alias per term, in any order, under the same ~, with or without spaces and brackets."""
    failures = []
    aliases = {"~(XX_A | XX_B)": (("XX_A", "XX_AA"), ("XX_B", "XX_BB")), "~XX_C": (("XX_C", "XX_CC"),),
               "XX_A | XX_B": (("XX_A", "XX_AA"), ("XX_B", "XX_BB"))}
    for text, wanted in (("~(XX_BB|XX_AA)", "~(XX_A | XX_B)"), ("~( XX_AA | XX_B )", "~(XX_A | XX_B)"),
                         ("~XX_CC", "~XX_C"), ("~(XX_CC)", "~XX_C"), ("XX_BB | XX_A", "XX_A | XX_B"),
                         ("~(XX_AA | XX_BB | XX_A)", None), ("XX_CC", None), ("~(XX_AA)", None), ("", None)):
        got = decisions.spelled_candidate(text, aliases)
        if got != wanted:
            failures.append(f"spelled_candidate({text!r}) is {got!r}, wanted {wanted!r}")
    return failures


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_file, check_latest_and_describe, check_decide, check_spelled_candidate):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    print("\n".join(found) or "decisionstests: all passed")
    sys.exit(1 if found else 0)
