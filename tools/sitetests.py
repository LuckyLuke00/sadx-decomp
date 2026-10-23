"""Checks for tools/pages.py: the changelog, the badge colours and the page building blocks."""

import json
from types import SimpleNamespace

import pages
import progress


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
    """A badge is JSON for shields.io with the share as its message and the share's colour."""
    data = json.loads(pages.badge("matched", 1, 4))
    wanted = {"schemaVersion": 1, "label": "matched", "message": "25.00%", "color": pages.share_color(1, 4)}
    return [] if data == wanted else [f"badge gives {data}, not {wanted}"]


def check_table() -> list[str]:
    """A table escapes its cells and its headings."""
    text = pages.table(["a<b"], [["<script>", 5]])
    if "<script>" in text or "a<b" in text or "&lt;script&gt;" not in text or "<td>5</td>" not in text:
        return [f"table gives {text!r}, which does not escape its cells"]
    return []


def check_count_text() -> list[str]:
    """The count text shows the thousands and the percent, and 0 of 0 shows 0%."""
    cases = [((1234, 5000, "bytes"), "1,234 of 5,000 bytes (24.68%)"), ((0, 0, "bytes"), "0 of 0 bytes (0.00%)")]
    return [f"count_text{args} gives {pages.count_text(*args)}, not {wanted}"
            for args, wanted in cases if pages.count_text(*args) != wanted]


def check_area_page() -> list[str]:
    """A trick below 100% is not matched yet. Only a trick at 100% shows under the trick heading."""
    def entry(accuracy, trick):
        data = {"name": "f", "accuracy": accuracy, "stub": False, "library": False}
        return dict(data, trick=True) if trick else data

    entries = {0x401000: entry(0.85, True), 0x401010: entry(1.0, True), 0x401020: entry(1.0, False)}
    fake = SimpleNamespace(entries=entries, sizes={address: 4 for address in entries}, groups=[], sources={},
                           section_of={"a": "Section"}, area_title=lambda area: "Area")
    text = pages.area_page(fake, "a", list(entries))
    open_part, trick_part = text.split("These match only through a trick")
    failures = []
    if "0x00401000" not in open_part or "0x00401010" in open_part or "0x00401020" in open_part:
        failures.append("area_page does not list exactly the function below 100% as not matched yet")
    if "0x00401010" not in trick_part or "0x00401000" in trick_part or "0x00401020" in trick_part:
        failures.append("area_page does not list exactly the trick at 100% under the trick heading")
    if "1 of 3 game functions matched" not in text:
        failures.append("area_page does not count one matched function of three")
    return failures


def run() -> list[str]:
    """Every check of this module, in order."""
    failures = []
    for check in (check_changelog_rows, check_share_color, check_badge, check_table, check_count_text, check_area_page):
        failures += check()
    return failures
