#!/usr/bin/env python3
"""Draw the README progress visuals and keep the progress history.

  python tools/progress.py

Reads docs/progress/summary.json and history.csv, data/functions.csv,
data/codegen-groups.csv and README.md. Writes card.svg, history.svg and map.svg in
docs/progress, and the recent-changes table in README.md. The output depends
only on those committed files, so CI can check that it is current.
`check.py save` calls this after it saves a new summary.json.
Standard library only.
"""

import csv
import json
import math
import sys
from pathlib import Path
from typing import NamedTuple
from xml.sax.saxutils import escape

from scoring import Totals, accuracy_text, percent, ratio, score, state, stats_line, totals

ROOT = Path(__file__).resolve().parent.parent
PROGRESS = ROOT / "docs" / "progress"
SUMMARY_JSON = PROGRESS / "summary.json"
HISTORY_CSV = PROGRESS / "history.csv"
FUNCTIONS_CSV = ROOT / "data" / "functions.csv"
CODEGEN_GROUPS = ROOT / "data" / "codegen-groups.csv"
README = ROOT / "README.md"

HISTORY_FIELDS = ["date", "decompiled", "matched", "accuracy", "game_total", "changes"]
MAX_CHANGES = 5
RECENT_ROWS = 10
TABLE_START = "<!-- history:start -->"
TABLE_END = "<!-- history:end -->"

BACKGROUND = "#0d1117"
TEXT = "#e6edf3"
MUTED = "#8b949e"
GRID = "#30363d"
NOT_STARTED = "#21262d"
NOT_COUNTED = "#172a45"
STUB = "#6e7681"
MATCH = "#56d364"
LIBRARY = "#58a6ff"
ACCURACY = "#d29922"
# Partial matches run from red (0%) through amber to dark green (just under 100%).
PARTIAL_STOPS = [(0.0, (0xDA, 0x36, 0x33)), (0.5, (0xD2, 0x99, 0x22)), (1.0, (0x23, 0x86, 0x36))]

WIDTH = 1000
MARGIN = 16
CELL = 6
PITCH = 7
HEADER = 64
FOOTER = 40
FONT = "Segoe UI,Helvetica,Arial,sans-serif"


HISTORY_HEIGHT = 330
HISTORY_LEFT = 64
HISTORY_RIGHT = WIDTH - MARGIN


class Line(NamedTuple):
    label: str
    values: list[float | None]
    color: str


class Panel(NamedTuple):
    top: int  # pixel rows of the plot area
    bottom: int
    top_value: float  # the value at the top edge
    lines: list[Line]


# Inputs


def read_csv(path: Path) -> list[dict]:
    if not path.exists():
        sys.exit(f"{path.relative_to(ROOT).as_posix()} is missing. docs/PORTING.md says how to make it.")
    with path.open(encoding="utf-8", newline="") as rows:
        return list(csv.DictReader(rows))


def load_functions() -> list[dict]:
    return [{"address": int(row["address"], 16), "size": int(row["size"]), "name": row["ghidra_name"]}
            for row in read_csv(FUNCTIONS_CSV)]


def load_codegen_groups() -> list[dict]:
    return [dict(row, start=int(row["start"], 16), end=int(row["end"], 16)) for row in read_csv(CODEGEN_GROUPS)]


def codegen_group(groups: list[dict], address: int) -> dict | None:
    for group in groups:
        if group["start"] <= address < group["end"]:
            return group
    return None


def load_summary() -> dict:
    return json.loads(SUMMARY_JSON.read_text(encoding="utf-8"))


def game_addresses(functions: list[dict]) -> set[int]:
    """The denominator: functions in game code ranges."""
    groups = load_codegen_groups()
    game = set()
    for function in functions:
        group = codegen_group(groups, function["address"])
        if group and group["kind"] == "game":
            game.add(function["address"])
    return game


# History


def load_history() -> list[dict]:
    """The history rows, oldest first. There are none before the first `check.py save`."""
    return read_csv(HISTORY_CSV) if HISTORY_CSV.exists() else []


def history_row(date: str, stats: Totals, changes: list[str]) -> dict:
    shown = changes[:MAX_CHANGES]
    if len(changes) > MAX_CHANGES:
        shown.append(f"{len(changes) - MAX_CHANGES} more")
    return {
        "date": date,
        "decompiled": str(stats.decompiled),
        "matched": str(stats.matched),
        "accuracy": f"{stats.accuracy * 100:.2f}" if stats.accuracy is not None else "",
        "game_total": str(stats.game_total),
        "changes": "; ".join(shown),
    }


def same_totals(row: dict, other: dict) -> bool:
    return all(row[field] == other[field] for field in ("decompiled", "matched", "accuracy", "game_total"))


def record_history(date: str, stats: Totals, changes: list[str]) -> bool:
    """Append a row when a function changed or the totals moved. The log is append-only."""
    row = history_row(date, stats, changes)
    history = load_history()
    if not changes and history and same_totals(row, history[-1]):
        return False
    new_file = not HISTORY_CSV.exists()
    with HISTORY_CSV.open("a", encoding="utf-8", newline="") as rows:
        writer = csv.DictWriter(rows, HISTORY_FIELDS, lineterminator="\n")
        if new_file:
            writer.writeheader()
        writer.writerow(row)
    return True


# Drawing


def partial_color(value: float) -> str:
    for (low, low_rgb), (high, high_rgb) in zip(PARTIAL_STOPS, PARTIAL_STOPS[1:]):
        if value <= high:
            t = (value - low) / (high - low)
            return "#" + "".join(f"{round(a + (b - a) * t):02x}" for a, b in zip(low_rgb, high_rgb))
    return MATCH


def cell_color(entry: dict) -> str:
    if entry["stub"]:
        return STUB
    if score(entry) == 1.0:
        return LIBRARY if entry["library"] else MATCH
    return partial_color(score(entry))


def cell_label(address: int, entry: dict) -> str:
    kind = " (library)" if entry["library"] else ""
    return escape(f"0x{address:08x} {entry['name']}{kind}: {state(entry)}")


def row_segments(start: int, count: int, columns: int):
    """Split a run of grid cells into one (row, column, length) piece per grid row."""
    index, end = start, start + count
    while index < end:
        row, column = divmod(index, columns)
        length = min(columns - column, end - index)
        yield row, column, length
        index += length


def map_header(summary: dict, stats: Totals, height: int) -> list[str]:
    """The map's opening tags: title, cell patterns, background and the three text lines."""
    parts = [
        f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {WIDTH} {height}" width="{WIDTH}" height="{height}">',
        f'<title>{escape(summary["exe"])} decompilation progress</title>',
        "<defs>",
    ]
    for name, color in (("todo", NOT_STARTED), ("skip", NOT_COUNTED)):
        parts.append(f'<pattern id="{name}" x="{MARGIN}" y="{HEADER}" width="{PITCH}" height="{PITCH}" '
                     f'patternUnits="userSpaceOnUse"><rect width="{CELL}" height="{CELL}" fill="{color}"/></pattern>')
    parts += [
        "</defs>",
        f'<rect width="{WIDTH}" height="{height}" rx="6" fill="{BACKGROUND}"/>',
        f'<text x="{MARGIN}" y="28" font-family="{FONT}" font-size="18" font-weight="600" fill="{TEXT}">{escape(summary["exe"])}</text>',
        f'<text x="{WIDTH - MARGIN}" y="28" text-anchor="end" font-family="{FONT}" font-size="12" fill="{MUTED}">'
        "one cell per function, in address order</text>",
        f'<text x="{MARGIN}" y="50" font-family="{FONT}" font-size="13" fill="{MUTED}">{escape(stats_line(stats))}</text>',
    ]
    return parts


def run_rects(runs: list[tuple[int, int]], pattern: str, columns: int) -> list[str]:
    """One pattern-filled rect per grid row for each (start, count) run of cells."""
    return [f'<rect x="{MARGIN + column * PITCH}" y="{HEADER + row * PITCH}" width="{length * PITCH}" '
            f'height="{PITCH}" fill="url(#{pattern})"/>'
            for start, count in runs
            for row, column, length in row_segments(start, count, columns)]


def skipped_runs(cells: list[int], entries: dict[int, dict], game: set[int]) -> list[tuple[int, int]]:
    """The (start, count) runs of cells that are neither scored nor in game code."""
    runs = []
    run_start = None
    for index, address in enumerate(cells + [None]):
        skipped = address is not None and address not in entries and address not in game
        if skipped and run_start is None:
            run_start = index
        elif not skipped and run_start is not None:
            runs.append((run_start, index - run_start))
            run_start = None
    return runs


def scored_rects(cells: list[int], entries: dict[int, dict], columns: int) -> list[str]:
    """One colored cell with a tooltip for each scored function."""
    rects = []
    for index, address in enumerate(cells):
        entry = entries.get(address)
        if entry is None:
            continue
        x = MARGIN + (index % columns) * PITCH
        y = HEADER + (index // columns) * PITCH
        rects.append(f'<rect x="{x}" y="{y}" width="{CELL}" height="{CELL}" fill="{cell_color(entry)}">'
                     f'<title>{cell_label(address, entry)}</title></rect>')
    return rects


def map_legend(height: int) -> list[str]:
    legend = [(NOT_STARTED, "not started"), (STUB, "stub"), (partial_color(0.0), "0%"),
              (partial_color(0.5), "50%"), (partial_color(0.99), "99%"), (MATCH, "100% match"),
              (LIBRARY, "library, identified"), (NOT_COUNTED, "library, not counted")]
    parts = []
    x = MARGIN
    y = height - FOOTER + 22
    for color, label in legend:
        parts.append(f'<rect x="{x}" y="{y - 9}" width="10" height="10" rx="2" fill="{color}"/>')
        parts.append(f'<text x="{x + 15}" y="{y}" font-family="{FONT}" font-size="12" fill="{MUTED}">{label}</text>')
        x += 15 + round(6.2 * len(label)) + 18
    return parts


def render_map(summary: dict, functions: list[dict], game: set[int]) -> str:
    entries = {int(entry["address"], 16): entry for entry in summary["functions"]}
    cells = sorted({function["address"] for function in functions} | set(entries))
    columns = (WIDTH - 2 * MARGIN) // PITCH
    rows = max(1, math.ceil(len(cells) / columns))
    height = HEADER + rows * PITCH + FOOTER

    parts = map_header(summary, totals(summary, game), height)
    # Every cell starts as not started. Runs of cells outside the game code get
    # the not-counted pattern. Scored functions get their own cell and tooltip.
    parts += run_rects([(0, len(cells))], "todo", columns)
    parts += run_rects(skipped_runs(cells, entries, game), "skip", columns)
    parts += scored_rects(cells, entries, columns)
    parts += map_legend(height)
    parts.append("</svg>")
    return "\n".join(parts) + "\n"


def card_bar(stats: Totals, width: int) -> list[str]:
    """The progress bar: a track, then the decompiled and matched shares over it."""
    bar_x, bar_y, bar_width = 20, 96, width - 40
    parts = [f'<rect x="{bar_x}" y="{bar_y}" width="{bar_width}" height="8" rx="4" fill="{NOT_STARTED}"/>']
    decompiled = ratio(stats.decompiled, stats.game_total)
    matched = ratio(stats.matched, stats.game_total)
    # At least 2 px wide once there is anything, so the first functions show.
    for fraction, color in ((decompiled, LIBRARY), (matched, MATCH)):
        if fraction > 0:
            parts.append(f'<rect x="{bar_x}" y="{bar_y}" width="{max(2.0, bar_width * fraction):.1f}" height="8" '
                         f'rx="4" fill="{color}"/>')
    return parts


def card_figures(stats: Totals, width: int) -> list[str]:
    """The four figures under the bar."""
    figures = [(f"{stats.decompiled:,}", "decompiled"), (f"{stats.matched:,}", "matched"),
               (accuracy_text(stats), "accuracy"), (f"{stats.game_total:,}", "game functions")]
    parts = []
    column = (width - 40) / len(figures)
    for index, (value, label) in enumerate(figures):
        x = 20 + index * column
        parts.append(f'<text x="{x:.0f}" y="134" font-family="{FONT}" font-size="18" font-weight="600" '
                     f'fill="{TEXT}">{escape(value)}</text>')
        parts.append(f'<text x="{x:.0f}" y="152" font-family="{FONT}" font-size="12" fill="{MUTED}">{label}</text>')
    return parts


def render_card(stats: Totals, updated: str, exe: str) -> str:
    """The summary card at the top of the README."""
    width, height = 520, 168
    parts = [
        f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {width} {height}" width="{width}" height="{height}">',
        f'<title>{escape(stats_line(stats))}</title>',
        f'<rect width="{width}" height="{height}" rx="8" fill="{BACKGROUND}"/>',
        f'<text x="20" y="30" font-family="{FONT}" font-size="13" fill="{MUTED}">'
        f'{escape(exe)}</text>',
        f'<text x="{width - 20}" y="30" text-anchor="end" font-family="{FONT}" font-size="12" '
        f'fill="{MUTED}">updated {escape(updated)}</text>',
        f'<text x="20" y="76" font-family="{FONT}" font-size="40" font-weight="600" fill="{TEXT}">'
        f'{percent(stats.decompiled, stats.game_total)}</text>',
        f'<text x="{width - 20}" y="76" text-anchor="end" font-family="{FONT}" font-size="13" fill="{MUTED}">'
        "of game functions decompiled</text>",
    ]
    parts += card_bar(stats, width)
    parts += card_figures(stats, width)
    parts.append("</svg>")
    return "\n".join(parts) + "\n"


def axis_top(value: float) -> float:
    """The smallest 1, 2 or 5 times a power of ten that is at least value, for a 0 to 1 axis."""
    if value <= 0:
        return 0.01
    exponent = math.floor(math.log10(value))
    for step in (1, 2, 5, 10):
        top = step * 10.0 ** exponent
        if top >= value:
            return min(top, 1.0)
    return 1.0


def history_x(index: int, count: int) -> float:
    if count == 1:
        return (HISTORY_LEFT + HISTORY_RIGHT) / 2
    return HISTORY_LEFT + (HISTORY_RIGHT - HISTORY_LEFT) * index / (count - 1)


def history_legend() -> list[str]:
    parts = []
    x = HISTORY_RIGHT
    for label, color in reversed([("decompiled", LIBRARY), ("matched", MATCH), ("accuracy", ACCURACY)]):
        x -= 7 * len(label) + 15
        parts.append(f'<rect x="{x}" y="19" width="10" height="10" rx="2" fill="{color}"/>')
        parts.append(f'<text x="{x + 15}" y="28" font-family="{FONT}" font-size="12" fill="{MUTED}">{label}</text>')
        x -= 18
    return parts


def panel_grid(panel: Panel) -> list[str]:
    """The three horizontal grid lines of a panel, each with its percent label."""
    parts = []
    for fraction in (0.0, 0.5, 1.0):
        y = panel.bottom - (panel.bottom - panel.top) * fraction
        parts.append(f'<line x1="{HISTORY_LEFT}" y1="{y:.1f}" x2="{HISTORY_RIGHT}" y2="{y:.1f}" stroke="{GRID}" stroke-width="1"/>')
        parts.append(f'<text x="{HISTORY_LEFT - 8}" y="{y + 4:.1f}" text-anchor="end" font-family="{FONT}" '
                     f'font-size="11" fill="{MUTED}">{panel.top_value * fraction * 100:g}%</text>')
    return parts


def plot_line(line: Line, panel: Panel, dates: list[str]) -> list[str]:
    """A polyline through the line's values, and a circle with a tooltip at each one."""
    height = panel.bottom - panel.top
    points = [(history_x(index, len(dates)), panel.bottom - height * value / panel.top_value, index, value)
              for index, value in enumerate(line.values) if value is not None]
    parts = []
    if len(points) > 1:
        path = " ".join(f"{px:.1f},{py:.1f}" for px, py, _, _ in points)
        parts.append(f'<polyline points="{path}" fill="none" stroke="{line.color}" stroke-width="2"/>')
    for px, py, index, value in points:
        tip = escape(f"{dates[index]}: {line.label} {value:.2%}")
        parts.append(f'<circle cx="{px:.1f}" cy="{py:.1f}" r="3" fill="{line.color}"><title>{tip}</title></circle>')
    return parts


def date_labels(dates: list[str], y: int) -> list[str]:
    parts = []
    count = len(dates)
    shown = min(count, 8)
    for index in sorted({round(k * (count - 1) / max(shown - 1, 1)) for k in range(shown)}):
        anchor = "end" if count > 1 and index == count - 1 else "middle"  # the last label sits on the right edge
        parts.append(f'<text x="{history_x(index, count):.1f}" y="{y}" text-anchor="{anchor}" '
                     f'font-family="{FONT}" font-size="11" fill="{MUTED}">{escape(dates[index])}</text>')
    return parts


def history_heading() -> list[str]:
    """The history chart's opening tags: background and the two panel titles."""
    return [
        f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {WIDTH} {HISTORY_HEIGHT}" '
        f'width="{WIDTH}" height="{HISTORY_HEIGHT}">',
        "<title>Decompilation progress over time</title>",
        f'<rect width="{WIDTH}" height="{HISTORY_HEIGHT}" rx="6" fill="{BACKGROUND}"/>',
        f'<text x="{MARGIN}" y="28" font-family="{FONT}" font-size="15" font-weight="600" fill="{TEXT}">'
        "Share of game functions decompiled and matched</text>",
        f'<text x="{MARGIN}" y="176" font-family="{FONT}" font-size="15" font-weight="600" fill="{TEXT}">'
        "Accuracy of the decompiled functions</text>",
    ]


def render_history(history: list[dict]) -> str:
    """Two panels over the history rows: completeness on an auto scale, accuracy on 0 to 100%."""
    decompiled = [ratio(int(row["decompiled"]), int(row["game_total"])) for row in history]
    matched = [ratio(int(row["matched"]), int(row["game_total"])) for row in history]
    accuracy = [float(row["accuracy"]) / 100 if row["accuracy"] else None for row in history]
    panels = [
        Panel(48, 140, axis_top(max(decompiled + matched)),
              [Line("decompiled", decompiled, LIBRARY), Line("matched", matched, MATCH)]),
        Panel(196, 288, 1.0, [Line("accuracy", accuracy, ACCURACY)]),
    ]
    parts = history_heading()
    parts += history_legend()
    dates = [row["date"] for row in history]
    for panel in panels:
        parts += panel_grid(panel)
        for line in panel.lines:
            parts += plot_line(line, panel, dates)
    parts += date_labels(dates, panels[-1].bottom + 22)  # below the lower panel
    parts.append("</svg>")
    return "\n".join(parts) + "\n"


def render_recent_changes(history: list[dict]) -> str:
    """The README table, newest row first."""
    lines = ["| Date | Decompiled | Matched | Accuracy | Changes |", "| --- | --- | --- | --- | --- |"]
    for row in reversed(history[-RECENT_ROWS:]):
        decompiled, game_total = int(row["decompiled"]), int(row["game_total"])
        accuracy = f"{row['accuracy']}%" if row["accuracy"] else "n/a"
        changes = row["changes"].replace("|", "\\|")
        lines.append(f"| {row['date']} | {decompiled:,} / {game_total:,} ({percent(decompiled, game_total)}) "
                     f"| {int(row['matched']):,} | {accuracy} | {changes} |")
    return "\n".join(lines)


def history_markers(text: str) -> tuple[int, int]:
    """Where the README's recent-changes table starts and ends."""
    start, end = text.find(TABLE_START), text.find(TABLE_END)
    if start < 0 or end < start:
        sys.exit(f"README.md needs {TABLE_START} and then {TABLE_END} around the table of recent changes.")
    return start + len(TABLE_START), end


def replace_between_markers(text: str, content: str) -> str:
    start, end = history_markers(text)
    return text[:start] + "\n" + content + "\n" + text[end:]


def render_all() -> dict[Path, str]:
    """Every generated file and its expected text, from the committed inputs only."""
    summary = load_summary()
    history = load_history()
    functions = load_functions()
    game = game_addresses(functions)
    stats = totals(summary, game)
    readme = README.read_text(encoding="utf-8")
    return {
        PROGRESS / "map.svg": render_map(summary, functions, game),
        PROGRESS / "card.svg": render_card(stats, history[-1]["date"], summary["exe"]),
        PROGRESS / "history.svg": render_history(history),
        README: replace_between_markers(readme, render_recent_changes(history)),
    }


def write_visuals() -> None:
    for path, text in render_all().items():
        path.write_text(text, encoding="utf-8", newline="\n")


if __name__ == "__main__":
    write_visuals()
