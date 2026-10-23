"""Checks for tools/pages.py: the changelog, the badge colours and the page building blocks. Also the measures of
tools/objdiffreport.py."""

import json
import tempfile
from pathlib import Path
from types import SimpleNamespace
from unittest import mock

import objdiffreport
import pages
import progress
import scoring


def check_changelog_rows() -> list[str]:
    """A change of the game total gives a row, no change gives none, and the rows come sorted by date."""
    def history(*pairs):
        return [{"date": day, "game_total": str(total)} for day, total in pairs]

    fixed = pages.RULE_CHANGES
    changed = pages.changelog_rows(history(("2026-10-01", 100), ("2026-10-03", 120)))
    same = pages.changelog_rows(history(("2026-10-01", 100), ("2026-10-03", 100)))
    early = pages.changelog_rows(history(("2026-01-01", 100), ("2026-01-02", 90)))
    failures = []
    if changed != sorted(fixed + [("2026-10-03", "The game total changed from 100 to 120 functions.")]):
        failures.append(f"changelog_rows gives {changed} for a changed game total")
    if same != sorted(fixed):
        failures.append(f"changelog_rows gives {same} for an unchanged game total")
    if [day for day, _ in early] != sorted(day for day, _ in early) or early[0][0] != "2026-01-02":
        failures.append(f"changelog_rows gives {early}, not sorted by date")
    return failures


def check_share_color() -> list[str]:
    """A share gets the map's colour for it, without the #, and a whole of 0 counts as 0%."""
    cases = [(0, 10, progress.LIGHT.partial[0]), (10, 10, progress.LIGHT.partial[10]),
             (5, 10, progress.partial_color(0.5, progress.LIGHT)), (0, 0, progress.LIGHT.partial[0])]
    return [f"share_color({part}, {whole}) gives {pages.share_color(part, whole)}, not {wanted[1:]}"
            for part, whole, wanted in cases if pages.share_color(part, whole) != wanted[1:]]


def check_badge() -> list[str]:
    """A badge is JSON for shields.io with the share as its message, after the prefix if it has one, and the share's
    colour."""
    failures = []
    for prefix, message in (("", "25.00%"), ("D", "D 25.00%")):
        data = json.loads(pages.badge("matched", 1, 4, prefix))
        wanted = {"schemaVersion": 1, "label": "matched", "message": message, "color": pages.share_color(1, 4)}
        if data != wanted:
            failures.append(f"badge gives {data}, not {wanted}")
    return failures


def check_table() -> list[str]:
    """A table escapes its cells and its headings."""
    text = pages.table(["a<b"], [["<script>", 5]])
    if "<script>" in text or "a<b" in text or "&lt;script&gt;" not in text or "<td>5</td>" not in text:
        return [f"table gives {text!r}, which does not escape its cells"]
    return []


def check_area_page() -> list[str]:
    """A trick below 100% is not matched yet. Only a trick at 100% shows under the trick heading."""
    def entry(accuracy, trick):
        data = {"name": "f", "accuracy": accuracy, "stub": False, "library": False}
        return dict(data, trick=True) if trick else data

    entries = {0x401000: entry(0.85, True), 0x401010: entry(1.0, True), 0x401020: entry(1.0, False)}
    fake = SimpleNamespace(entries=entries, sizes={address: 4 for address in entries}, groups=[], sources={},
                           section_of={"a": "Section"}, area_title=lambda area: "Area",
                           area_code=lambda addresses: scoring.Bytes(12, 4, 12))
    text = pages.area_page(fake, "a", list(entries))
    open_part, trick_part = text.split("These match only through a trick")
    failures = []
    if "0x00401000" not in open_part or "0x00401010" in open_part or "0x00401020" in open_part:
        failures.append("area_page does not list exactly the function below 100% as not matched yet")
    if "0x00401010" not in trick_part or "0x00401000" in trick_part or "0x00401020" in trick_part:
        failures.append("area_page does not list exactly the trick at 100% under the trick heading")
    if "1 of 3 game functions matched" not in text:
        failures.append("area_page does not count one matched function of three")
    if ">D</span> 4 of 12 code bytes matched" not in text:
        failures.append("area_page does not show rank D for 4 of 12 code bytes")
    return failures


def check_hard_tail_page() -> list[str]:
    """The hard tail leaves out the rows the tree matches now, and says how many."""
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder) / "hard-tail.csv"
        path.write_text("address,size,best,tries,area,group\n0x00401000,8,96.9,26,a,F\n0x00401010,8,100.0,3,a,F\n",
                        encoding="utf-8")
        fake = SimpleNamespace(is_matched=lambda address: address == 0x401010)
        with mock.patch.object(pages, "HARD_TAIL_CSV", path):
            text = pages.hard_tail_page(fake)
    if "0x00401000" not in text or "0x00401010" in text or "the tree matches them now: 1." not in text:
        return [f"hard_tail_page does not leave out exactly the matched row: {text!r}"]
    return []


def check_rank() -> list[str]:
    """Each fifth of the whole gets the next rank, and only all of it gets the emblem."""
    cases = [(0, 100, "E"), (19, 100, "E"), (20, 100, "D"), (99, 100, "A"), (100, 100, "Emblem"), (0, 0, "E")]
    return [f"rank({part}, {whole}) gives {pages.rank(part, whole)}, not {wanted}"
            for part, whole, wanted in cases if pages.rank(part, whole) != wanted]


def check_near_misses() -> list[str]:
    """Only game functions from 90% up to below 100% count: the highest score first, then the smallest."""
    def entry(accuracy, stub=False, trick=False):
        return {"name": "f", "accuracy": accuracy, "stub": stub, "library": False, "trick": trick}

    entries = {0x401000: entry(0.95), 0x401010: entry(0.95), 0x401020: entry(0.99), 0x401030: entry(0.89),
               0x401040: entry(1.0, trick=True), 0x401050: entry(0.99, stub=True), 0x401060: entry(0.92)}
    sizes = {0x401000: 40, 0x401010: 8, 0x401020: 100, 0x401030: 4, 0x401040: 4, 0x401050: 4, 0x401060: 4}
    fake = SimpleNamespace(game=set(entries) - {0x401060} | {0x401070}, entries=entries, sizes=sizes)
    found = pages.near_misses(fake)
    wanted = [0x401020, 0x401010, 0x401000]
    return [] if found == wanted else [f"near_misses gives {[hex(a) for a in found]}, not {[hex(a) for a in wanted]}"]


def check_objdiff_measures() -> list[str]:
    """objdiff's measures write 64-bit counts as strings and weigh the fuzzy share by size."""
    entries = {0x401000: {"name": "f", "accuracy": 1.0, "stub": False, "library": False},
               0x401010: {"name": "g", "accuracy": 0.5, "stub": False, "library": False}}
    fake = SimpleNamespace(sizes={0x401000: 30, 0x401010: 10, 0x401020: 40, 0x401030: 20}, entries=entries,
                           area_code=lambda addresses: scoring.Bytes(40, 30, 100),
                           is_matched=lambda address: address == 0x401000)
    found = objdiffreport.measures(fake, [0x401000, 0x401010, 0x401020, 0x401030], (5, 50))
    wanted = {"fuzzy_match_percent": 35.0, "total_code": "100", "matched_code": "30", "matched_code_percent": 30.0,
              "total_data": "50", "matched_data": "5", "matched_data_percent": 10.0, "total_functions": 4,
              "matched_functions": 1, "matched_functions_percent": 25.0}
    return [] if found == wanted else [f"measures gives {found}, not {wanted}"]


def run() -> list[str]:
    """Every check of this module, in order."""
    failures = []
    for check in (check_changelog_rows, check_share_color, check_badge, check_table, check_area_page,
                  check_hard_tail_page, check_rank, check_near_misses, check_objdiff_measures):
        failures += check()
    return failures
