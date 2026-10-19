#!/usr/bin/env python3
"""Draw the README progress visuals and the progress history.

  python tools/progress.py

Reads docs/progress/summary.json, data/functions.csv, data/codegen-groups.csv and
README.md, and the same three files in each commit that changed summary.json.
The map sorts the game functions into the areas tools/areas.py gives them.
Writes history.csv, card.svg, history.svg and map.svg in docs/progress, and the
recent-changes table in README.md. The history has one row for each day whose
first-parent commits changed a score: the last commit of the day. The working
tree, the commit being made, counts as a commit of today when its scores differ
from the last commit's. The output depends only on committed files, so CI can
check that it is current.
`check.py save` calls this after it saves a new summary.json. The areas need
.venv's packages, so run on its own, this runs itself again with .venv's Python.
"""

import collections
import csv
import io
import json
import math
import subprocess
import sys
from datetime import date, timedelta
from pathlib import Path
from typing import NamedTuple
from xml.sax.saxutils import escape

import osutil

from layout import Rect, snap, squarify, svg_points, text_width, wrap
from scoring import (Totals, accuracy_text, game_functions, moved_scores, percent, ratio, score, state, stats_line,
                     totals, whole_percent)

ROOT = Path(__file__).resolve().parent.parent
PROGRESS = ROOT / "docs" / "progress"
SUMMARY_JSON = PROGRESS / "summary.json"
HISTORY_CSV = PROGRESS / "history.csv"
FUNCTIONS_CSV = ROOT / "data" / "functions.csv"
CODEGEN_GROUPS = ROOT / "data" / "codegen-groups.csv"
README = ROOT / "README.md"

HISTORY_FIELDS = ["date", "decompiled", "matched", "accuracy", "game_total", "changes"]
MAX_AREAS = 3  # areas a history row names, the ones with the most changed functions
RECENT_ROWS = 10
TABLE_START = "<!-- history:start -->"
TABLE_END = "<!-- history:end -->"

BACKGROUND = "#07154a"
BACKGROUND_TOP = "#10307e"  # the background fades from this at the top
BLOCK = "#0f2a78"
TEXT = "#ffffff"
MUTED = "#a9bde8"
GRID = "#2a4aa0"
NOT_STARTED = "#06113d"
DONE = "#ffd700"
DONE_BORDER = f' stroke="{DONE}" stroke-width="1.5"'  # around a finished area
DECOMPILED = "#4aa8ff"
ACCURACY = "#ffffff"
# Partial scores run from blue at 0% to the gold of DONE at 100%, in 10% steps of a straight line in OKLab, where
# equal steps look equal. The lightness rises the whole way, so the order holds for every kind of colour vision.
PARTIAL_STOPS = [(0.0, (0x27, 0x53, 0xD8)), (0.1, (0x3A, 0x66, 0xD0)), (0.2, (0x4E, 0x77, 0xC7)),
                 (0.3, (0x63, 0x86, 0xBD)), (0.4, (0x78, 0x93, 0xB2)), (0.5, (0x8E, 0xA0, 0xA6)),
                 (0.6, (0xA4, 0xAC, 0x97)), (0.7, (0xBA, 0xB7, 0x86)), (0.8, (0xD1, 0xC2, 0x70)),
                 (0.9, (0xE8, 0xCD, 0x51)), (1.0, tuple(bytes.fromhex(DONE[1:])))]

WIDTH = 1000
MARGIN = 16
CELL = 6
PITCH = 7
HEADER = 64
FOOTER = 60
FONT = "Segoe UI,Helvetica,Arial,sans-serif"

TITLE = 22  # the strip above a section's blocks that holds its name
TITLE_SIZE = 13
GEM_WIDTH = 12  # gem() draws a gem this wide
GEM = GEM_WIDTH + 4  # the room a section's gem takes before its title
NAME_SIZE = 12
NAME_LINE_HEIGHT = 15
PAD = 4  # from a block's edge to its name and cells
SHARE_SAMPLE = "100%"  # the widest done share: names and titles get room for it, so the layout holds as work lands
KEY_GAP = 18  # after each label of the map's colour key
STRIP_PAD = 6  # from the edge of the colour key's strip to its first swatch and its last label
SECTION_GAP = 3  # around a section's blocks
SECTION_SHARE = 0.85  # the share of a section its blocks start with: the title strip and gaps take the rest
GROW = 1.1  # how much a block grows each round until its name and cells fit
MAX_ROUNDS = 200


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


def parse_functions(rows: list[dict]) -> list[dict]:
    return [{"address": int(row["address"], 16), "size": int(row["size"]), "name": row["ghidra_name"]} for row in rows]


def load_functions() -> list[dict]:
    return parse_functions(read_csv(FUNCTIONS_CSV))


def parse_codegen_groups(rows: list[dict]) -> list[dict]:
    return [dict(row, start=int(row["start"], 16), end=int(row["end"], 16)) for row in rows]


def load_codegen_groups() -> list[dict]:
    return parse_codegen_groups(read_csv(CODEGEN_GROUPS))


def codegen_group(groups: list[dict], address: int) -> dict | None:
    for group in groups:
        if group["start"] <= address < group["end"]:
            return group
    return None


def load_summary() -> dict:
    return json.loads(SUMMARY_JSON.read_text(encoding="utf-8"))


def game_addresses(functions: list[dict], groups: list[dict] | None = None) -> set[int]:
    """The denominator: functions in game code ranges. The groups default to the working tree's."""
    groups = load_codegen_groups() if groups is None else groups
    game = set()
    for function in functions:
        group = codegen_group(groups, function["address"])
        if group and group["kind"] == "game":
            game.add(function["address"])
    return game


# History


class Snapshot(NamedTuple):
    day: str
    summary: dict
    game: set[int]


def read_blobs(root: Path, specs: list[str]) -> dict[str, str]:
    """The text of each `commit:path` spec in the repository at root. Each distinct file version is read once."""
    checks = osutil.git(root, "cat-file", "--batch-check", stdin="".join(f"{spec}\n" for spec in specs).encode())
    ids = []
    for spec, line in zip(specs, checks.decode().splitlines()):
        if line.endswith(" missing"):
            sys.exit(f"git has no {spec}")
        ids.append(line.split()[0])
    unique = sorted(set(ids))
    data = osutil.git(root, "cat-file", "--batch", stdin="".join(f"{blob}\n" for blob in unique).encode())
    texts, position = {}, 0
    for blob in unique:
        header_end = data.index(b"\n", position)
        size = int(data[position:header_end].split()[2])
        texts[blob] = data[header_end + 1:header_end + 1 + size].decode("utf-8")
        position = header_end + 1 + size + 1  # the content ends with a newline of its own
    return {spec: texts[blob] for spec, blob in zip(specs, ids)}


def csv_rows(text: str) -> list[dict]:
    return list(csv.DictReader(io.StringIO(text)))


def committed_snapshots() -> list[Snapshot]:
    """The scores of the last first-parent commit of each day that changed summary.json, oldest first."""
    if subprocess.run(["git", "rev-parse", "--verify", "--quiet", "HEAD"], cwd=ROOT, capture_output=True).returncode:
        return []  # no commit yet
    paths = [path.relative_to(ROOT).as_posix() for path in (SUMMARY_JSON, FUNCTIONS_CSV, CODEGEN_GROUPS)]
    log = osutil.git(ROOT, "log", "--first-parent", "--reverse", "--format=%H %as", "--", paths[0]).decode()
    commits = osutil.last_of_each_day([line.split() for line in log.splitlines()], lambda commit: commit[1])
    texts = read_blobs(ROOT, [f"{commit}:{path}" for commit, _ in commits for path in paths])
    games = {}  # one game set per version of functions.csv and codegen-groups.csv
    snapshots = []
    for commit, day in commits:
        summary, functions, groups = (texts[f"{commit}:{path}"] for path in paths)
        if (functions, groups) not in games:
            games[functions, groups] = game_addresses(parse_functions(csv_rows(functions)),
                                                      parse_codegen_groups(csv_rows(groups)))
        snapshots.append(Snapshot(day, json.loads(summary), games[functions, groups]))
    return snapshots


def history_rows(snapshots: list[Snapshot], area_names: dict[int, str]) -> list[dict]:
    """The history rows of the snapshots, oldest first: the first day, then each day that moved a score.
    Stubs score zero, so a day that only adds or removes stubs gets no row. area_names holds the area
    each game function shows under, for the row's changes."""
    rows, previous = [], {"functions": []}
    for snapshot in osutil.last_of_each_day(snapshots, lambda each: each.day):
        moved = moved_scores(previous, snapshot.summary)
        row = history_row(snapshot.day, totals(snapshot.summary, snapshot.game), area_changes(moved, area_names))
        if not rows or moved or not same_totals(row, rows[-1]):
            rows.append(row)
        previous = snapshot.summary
    return rows


def area_changes(moved: list[int], area_names: dict[int, str]) -> str:
    """The areas with the most of the moved game functions, each with that count."""
    counts = collections.Counter(area_names[address] for address in moved if address in area_names)
    text = ", ".join(f"{name} {count:,}" for name, count in counts.most_common(MAX_AREAS))
    if len(counts) > MAX_AREAS:
        text += f" and {len(counts) - MAX_AREAS} more"
    return text


def history_row(day: str, stats: Totals, changes: str) -> dict:
    return {
        "date": day,
        "decompiled": str(stats.decompiled),
        "matched": str(stats.matched),
        "accuracy": f"{stats.accuracy * 100:.2f}" if stats.accuracy is not None else "",
        "game_total": str(stats.game_total),
        "changes": changes,
    }


def same_totals(row: dict, other: dict) -> bool:
    return all(row[field] == other[field] for field in ("decompiled", "matched", "accuracy", "game_total"))


def render_history_csv(history: list[dict]) -> str:
    text = io.StringIO()
    writer = csv.DictWriter(text, HISTORY_FIELDS, lineterminator="\n")
    writer.writeheader()
    writer.writerows(history)
    return text.getvalue()


# Drawing


def partial_color(value: float) -> str:
    for (low, low_rgb), (high, high_rgb) in zip(PARTIAL_STOPS, PARTIAL_STOPS[1:]):
        if value <= high:
            t = (value - low) / (high - low)
            return "#" + "".join(f"{round(a + (b - a) * t):02x}" for a, b in zip(low_rgb, high_rgb))
    return DONE


def cell_label(address: int, entry: dict) -> str:
    return escape(f"0x{address:08x} {entry['name']}: {state(entry)}")


class Block(NamedTuple):
    name: str
    cells: list[int]  # its game functions, in address order
    labelled: bool  # False in a section of one area, whose title names it


class Section(NamedTuple):
    name: str
    color: str | None  # of the gem before its title, if it has one
    blocks: list[Block]


def map_sections(area_of: dict[int, str], sections: list[tuple[str, str | None, dict[str, str]]]) -> list[Section]:
    """The map's sections and blocks, from each function's area and the (section, gem colour, {area: name}) list,
    without empty blocks or sections."""
    members = collections.defaultdict(list)
    for address in sorted(area_of):
        members[area_of[address]].append(address)
    found = []
    for name, color, names in sections:
        blocks = [(shown, members[area]) for area, shown in names.items() if members[area]]
        if blocks:
            found.append(Section(name, color, [Block(shown, cells, len(names) > 1) for shown, cells in blocks]))
    return found


def name_lines(block: Block, width: float) -> list[list[str]] | None:
    """The words of the block's name and SHARE_SAMPLE in lines that fit the width, or None if a word is too wide."""
    if not block.labelled:
        return []
    return wrap(block.name.split() + [SHARE_SAMPLE], width, NAME_SIZE)


def cell_columns(width: float) -> int:
    return int((width - CELL) // PITCH) + 1 if width >= CELL else 0


def block_grid(block: Block, rect: Rect) -> tuple[list[list[str]] | None, int]:
    """The lines of the block's name and the columns of its cells, inside its padding."""
    inner = rect.width - 2 * PAD
    return name_lines(block, inner), cell_columns(inner)


def block_fits(block: Block, rect: Rect) -> bool:
    lines, columns = block_grid(block, rect)
    if lines is None or columns == 0:
        return False
    return 2 * PAD + len(lines) * NAME_LINE_HEIGHT + math.ceil(len(block.cells) / columns) * PITCH <= rect.height


def title_indent(section: Section) -> int:
    """Where a section's title starts, after its gem if it has one."""
    return GEM if section.color else 0


def section_fits(section: Section, rect: Rect) -> bool:
    title = f"{section.name} {SHARE_SAMPLE}"
    return title_indent(section) + text_width(title, TITLE_SIZE) <= rect.width - 2 * SECTION_GAP


def place(weights: list[list[float]]) -> list[tuple[Rect, list[Rect]]]:
    """Each section's rectangle and its blocks' rectangles, when the blocks get these weights."""
    width = WIDTH - 2 * MARGIN
    sizes = [sum(block_weights) / SECTION_SHARE for block_weights in weights]
    placed = []
    for outer, block_weights in zip(squarify(sizes, Rect(MARGIN, HEADER, width, sum(sizes) / width)), weights):
        inner = Rect(outer.x + SECTION_GAP, outer.y + TITLE, max(outer.width - 2 * SECTION_GAP, 1.0),
                     max(outer.height - TITLE - SECTION_GAP, 1.0))
        placed.append((snap(outer), [snap(rect) for rect in squarify(block_weights, inner)]))
    return placed


def section_misfits(section: Section, outer: Rect, rects: list[Rect]) -> list[int]:
    """The indexes of the section's blocks to grow. A block grows when its name or cells do not fit. Every block
    grows when the section's title does not fit."""
    if not section_fits(section, outer):
        return list(range(len(section.blocks)))
    return [index for index, block in enumerate(section.blocks) if not block_fits(block, rects[index])]


def misfits(sections: list[Section], placed: list[tuple[Rect, list[Rect]]]) -> list[tuple[int, int]]:
    """(section, block) indexes of the blocks to grow."""
    found = []
    for section_index, (section, (outer, rects)) in enumerate(zip(sections, placed)):
        for block_index in section_misfits(section, outer, rects):
            found.append((section_index, block_index))
    return found


def map_layout(sections: list[Section]) -> list[tuple[Rect, list[Rect]]]:
    """Squarified rectangles for the sections and their blocks. A block starts with the room its cells need and
    grows until its name and cells fit, so small blocks end up bigger than their share."""
    weights = [[float(len(block.cells) * PITCH * PITCH) for block in section.blocks] for section in sections]
    for _ in range(MAX_ROUNDS):
        placed = place(weights)
        grow = misfits(sections, placed)
        if not grow:
            return placed
        for section_index, block_index in grow:
            weights[section_index][block_index] *= GROW
    sys.exit(f"The progress map found no layout in {MAX_ROUNDS} rounds where every name and cell fits its block.")


def done_count(cells: list[int], entries: dict[int, dict]) -> int:
    return sum(1 for address in cells if address in entries and score(entries[address]) == 1.0)


def map_header(summary: dict, stats: Totals, height: int) -> list[str]:
    """The map's opening tags: title, background and the three text lines."""
    stats_text = (f"{stats.matched:,} of {stats.game_total:,} game functions done "
                  f"({percent(stats.matched, stats.game_total)}), {stats.decompiled - stats.matched:,} in progress, "
                  f"accuracy {accuracy_text(stats)}")
    return [
        f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {WIDTH} {height}" width="{WIDTH}" height="{height}">',
        f'<title>{escape(summary["exe"])} decompilation progress</title>',
        *backdrop(WIDTH, height, 6),
        f'<text x="{MARGIN}" y="28" font-family="{FONT}" font-size="18" font-weight="600" fill="{TEXT}">{escape(summary["exe"])}</text>',
        f'<text x="{WIDTH - MARGIN}" y="28" text-anchor="end" font-family="{FONT}" font-size="12" fill="{MUTED}">'
        "one square per function</text>",
        f'<text x="{MARGIN}" y="50" font-family="{FONT}" font-size="13" fill="{MUTED}">{escape(stats_text)}</text>',
    ]


def backdrop(width: int, height: int, radius: int) -> list[str]:
    """The background of a drawing: a rounded rectangle that fades from BACKGROUND_TOP to BACKGROUND."""
    return [f'<defs><linearGradient id="backdrop" x1="0" y1="0" x2="0" y2="1">'
            f'<stop offset="0" stop-color="{BACKGROUND_TOP}"/><stop offset="1" stop-color="{BACKGROUND}"/>'
            "</linearGradient></defs>",
            f'<rect width="{width}" height="{height}" rx="{radius}" fill="url(#backdrop)"/>']


def ring(x: float, y: float) -> str:
    """A gold ring centred on (x, y)."""
    return f'<circle cx="{x:g}" cy="{y:g}" r="5" fill="none" stroke="{DONE}" stroke-width="2.5"/>'


def gem(x: float, y: float, color: str) -> list[str]:
    """A cut gem 12 px wide centred on (x, y), with a light top facet."""
    outline = [(x - 3, y - 5), (x + 3, y - 5), (x + 6, y - 1.5), (x, y + 5.5), (x - 6, y - 1.5)]
    facet = [(x - 3, y - 5), (x + 3, y - 5), (x + 1.5, y - 1.5), (x - 1.5, y - 1.5)]
    return [f'<polygon points="{svg_points(outline)}" fill="{color}"/>',
            f'<polygon points="{svg_points(facet)}" fill="#ffffff" fill-opacity="0.45"/>']


def section_title(section: Section, outer: Rect, entries: dict[int, dict]) -> list[str]:
    """The section's gem, name and done share."""
    cells = [address for block in section.blocks for address in block.cells]
    share = whole_percent(done_count(cells, entries), len(cells))
    x, baseline = outer.x + SECTION_GAP, outer.y + TITLE - 7
    parts = gem(x + GEM_WIDTH / 2, baseline - 4.5, section.color) if section.color else []
    parts.append(f'<text x="{x + title_indent(section)}" y="{baseline}" font-family="{FONT}" '
                 f'font-size="{TITLE_SIZE}" font-weight="600" fill="{TEXT}">{escape(section.name)} '
                 f'<tspan font-weight="400" fill="{MUTED}">{share}</tspan></text>')
    return parts


def name_text(lines: list[list[str]], share: str, rect: Rect) -> list[str]:
    """The block's name in its lines, with the done share in place of the SHARE_SAMPLE that ends the last one."""
    parts = []
    for row, words in enumerate(lines):
        name, tail = words, ""
        if row == len(lines) - 1:
            name = words[:-1]
            share_text = f'<tspan font-weight="400" fill="{MUTED}">{share}</tspan>'
            tail = f" {share_text}" if name else share_text
        y = rect.y + PAD + (row + 1) * NAME_LINE_HEIGHT - 4
        parts.append(f'<text x="{rect.x + PAD}" y="{y}" font-family="{FONT}" font-size="{NAME_SIZE}" '
                     f'font-weight="600" fill="{TEXT}">{escape(" ".join(name))}{tail}</text>')
    return parts


def todo_pattern() -> str:
    """The pattern of not-started cells that todo_rect fills with."""
    return (f'<defs><pattern id="todo" width="{PITCH}" height="{PITCH}" patternUnits="userSpaceOnUse">'
            f'<rect width="{CELL}" height="{CELL}" fill="{NOT_STARTED}"/></pattern></defs>')


def todo_rect(top: int, length: int, rows: int) -> str:
    return f'<rect y="{top}" width="{length * PITCH}" height="{rows * PITCH}" fill="url(#todo)"/>'


def todo_cells(count: int, columns: int) -> list[str]:
    """Every cell of a block as not started, from the block's first cell. One rectangle covers the full rows, and
    one the rest of the last row."""
    full, rest = divmod(count, columns)
    parts = []
    if full:
        parts.append(todo_rect(0, columns, full))
    if rest:
        parts.append(todo_rect(full * PITCH, rest, 1))
    return parts


def scored_cells(cells: list[int], entries: dict[int, dict], columns: int) -> list[str]:
    """One colored cell with a tooltip for each function with a score, from the block's first cell. A stub has
    none: it is not started."""
    rects = []
    for index, address in enumerate(cells):
        entry = entries.get(address)
        if entry is None or entry["stub"]:
            continue
        rects.append(f'<rect x="{index % columns * PITCH}" y="{index // columns * PITCH}" width="{CELL}" '
                     f'height="{CELL}" fill="{partial_color(score(entry))}"><title>{cell_label(address, entry)}</title>'
                     "</rect>")
    return rects


def block_parts(block: Block, rect: Rect, entries: dict[int, dict]) -> list[str]:
    """A block's background with its tooltip, its name and its cells. A finished block gets a gold border."""
    done = done_count(block.cells, entries)
    border = DONE_BORDER if done == len(block.cells) else ""
    tip = escape(f"{block.name}: {done:,} of {len(block.cells):,} done")
    parts = [f'<rect x="{rect.x + 1}" y="{rect.y + 1}" width="{rect.width - 2}" height="{rect.height - 2}" rx="3" '
             f'fill="{BLOCK}"{border}><title>{tip}</title></rect>']
    lines, columns = block_grid(block, rect)
    parts += name_text(lines, whole_percent(done, len(block.cells)), rect)
    parts.append(f'<g transform="translate({rect.x + PAD},{rect.y + PAD + len(lines) * NAME_LINE_HEIGHT})">')
    parts += todo_cells(len(block.cells), columns)
    parts += scored_cells(block.cells, entries, columns)
    parts.append("</g>")
    return parts


def map_legend(height: int) -> list[str]:
    """The colour key on a strip of block colour, as the cells sit on their block. Under it, a line on the code the
    map leaves out."""
    y = height - FOOTER + 22
    keys = [([NOT_STARTED], "", "not started"),
            ([partial_color(step / 10) for step in range(10)], "", "in progress, 0% to 99%"),
            ([DONE], "", "done"), ([BLOCK], DONE_BORDER, "area done")]
    swatches = []
    x = MARGIN
    for colors, border, label in keys:
        for color in colors:
            swatches.append(f'<rect x="{x}" y="{y - 9}" width="10" height="10" rx="2" fill="{color}"{border}/>')
            x += 12
        swatches.append(f'<text x="{x + 3}" y="{y}" font-family="{FONT}" font-size="12" fill="{MUTED}">{label}</text>')
        x += 3 + round(text_width(label, 12)) + KEY_GAP
    strip_end = x - KEY_GAP + STRIP_PAD
    return [f'<rect x="{MARGIN - STRIP_PAD}" y="{y - 15}" width="{strip_end - MARGIN + STRIP_PAD}" height="22" rx="4" '
            f'fill="{BLOCK}"/>',
            *swatches,
            f'<text x="{MARGIN}" y="{y + 22}" font-family="{FONT}" font-size="12" fill="{MUTED}">'
            "Library code is left out: it needs no decompiling.</text>"]


def render_map(summary: dict, stats: Totals, sections: list[Section]) -> str:
    entries = {int(entry["address"], 16): entry for entry in summary["functions"]}
    placed = map_layout(sections)
    height = max((outer.y + outer.height for outer, _ in placed), default=HEADER) + FOOTER
    parts = map_header(summary, stats, height)
    parts.append(todo_pattern())
    for section, (outer, rects) in zip(sections, placed):
        parts += section_title(section, outer, entries)
        for block, rect in zip(section.blocks, rects):
            parts += block_parts(block, rect, entries)
    parts += map_legend(height)
    parts.append("</svg>")
    return "\n".join(parts) + "\n"


def card_bar(stats: Totals, width: int) -> list[str]:
    """The progress bar: a track, then the decompiled and done shares over it."""
    bar_x, bar_y, bar_width = 20, 96, width - 40
    parts = [f'<rect x="{bar_x}" y="{bar_y}" width="{bar_width}" height="8" rx="4" fill="{NOT_STARTED}"/>']
    decompiled = ratio(stats.decompiled, stats.game_total)
    matched = ratio(stats.matched, stats.game_total)
    # At least 2 px wide once there is anything, so the first functions show.
    for fraction, color in ((decompiled, DECOMPILED), (matched, DONE)):
        if fraction > 0:
            parts.append(f'<rect x="{bar_x}" y="{bar_y}" width="{max(2.0, bar_width * fraction):.1f}" height="8" '
                         f'rx="4" fill="{color}"/>')
    return parts


def card_figures(stats: Totals, width: int) -> list[str]:
    """The four figures under the bar."""
    figures = [(f"{stats.matched:,}", "done"), (f"{stats.decompiled - stats.matched:,}", "in progress"),
               (accuracy_text(stats), "accuracy"), (f"{stats.game_total:,}", "game functions")]
    parts = []
    column = (width - 40) / len(figures)
    for index, (value, label) in enumerate(figures):
        x = 20 + index * column
        parts.append(f'<text x="{x:.0f}" y="134" font-family="{FONT}" font-size="18" font-weight="600" '
                     f'fill="{TEXT}">{escape(value)}</text>')
        parts.append(f'<text x="{x:.0f}" y="152" font-family="{FONT}" font-size="12" fill="{MUTED}">{label}</text>')
    return parts


def done_this_week(history: list[dict]) -> int:
    """The functions done since the last history row a week or more before the newest. It counts from the newest
    row's date, not from today, so the card depends only on the history."""
    newest = date.fromisoformat(history[-1]["date"])
    before = [row for row in history if date.fromisoformat(row["date"]) <= newest - timedelta(days=7)]
    return int(history[-1]["matched"]) - (int(before[-1]["matched"]) if before else 0)


def render_card(stats: Totals, history: list[dict], exe: str) -> str:
    """The summary card at the top of the README."""
    width, height = 520, 168
    parts = [
        f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {width} {height}" width="{width}" height="{height}">',
        f'<title>{escape(stats_line(stats))}</title>',
        *backdrop(width, height, 8),
        f'<text x="20" y="30" font-family="{FONT}" font-size="13" fill="{MUTED}">'
        f'{escape(exe)}</text>',
        f'<text x="{width - 20}" y="30" text-anchor="end" font-family="{FONT}" font-size="12" '
        f'fill="{MUTED}">updated {escape(history[-1]["date"])}</text>',
        f'<text x="20" y="76" font-family="{FONT}" font-size="40" font-weight="600" fill="{TEXT}">'
        f'{percent(stats.matched, stats.game_total)}</text>',
        f'<text x="{width - 37}" y="56" text-anchor="end" font-family="{FONT}" font-size="13" font-weight="600" '
        f'fill="{DONE}">{done_this_week(history):+,} this week</text>',
        ring(width - 26, 51.5),  # its right edge lines up with the text above and below
        f'<text x="{width - 20}" y="76" text-anchor="end" font-family="{FONT}" font-size="13" fill="{MUTED}">'
        "of the game done</text>",
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
    for label, color in reversed([("decompiled", DECOMPILED), ("done", DONE), ("accuracy", ACCURACY)]):
        x -= round(text_width(label, 12)) + 15
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
        *backdrop(WIDTH, HISTORY_HEIGHT, 6),
        f'<text x="{MARGIN}" y="28" font-family="{FONT}" font-size="15" font-weight="600" fill="{TEXT}">'
        "Share of game functions decompiled and done</text>",
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
              [Line("decompiled", decompiled, DECOMPILED), Line("done", matched, DONE)]),
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
    """The README table, newest row first. Done shows the change since the row before."""
    lines = ["| Date | Done | Decompiled | Accuracy | Areas |", "| --- | --- | --- | --- | --- |"]
    first = max(len(history) - RECENT_ROWS, 0)
    for index in reversed(range(first, len(history))):
        row = history[index]
        matched = int(row["matched"])
        before = int(history[index - 1]["matched"]) if index else 0
        accuracy = f"{row['accuracy']}%" if row["accuracy"] else "n/a"
        changes = row["changes"].replace("|", "\\|")
        lines.append(f"| {row['date']} | {matched:,} ({matched - before:+,}) | {int(row['decompiled']):,} "
                     f"| {accuracy} | {changes} |")
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


def load_areas(summary: dict, game: set[int]) -> tuple[list[Section], dict[int, str]]:
    """The map's sections, and the name of the area each game function shows under."""
    import areas  # here, not at the top: it needs .venv's packages, and check.py imports this module before .venv

    area_of, sections = areas.load(game_functions(summary, game))
    names = {area: shown for _, _, shown_names in sections for area, shown in shown_names.items()}
    return map_sections(area_of, sections), {address: names[area] for address, area in area_of.items()}


def render_all() -> dict[Path, str]:
    """Every generated file and its expected text, from the committed inputs only."""
    summary = load_summary()
    game = game_addresses(load_functions())
    sections, area_names = load_areas(summary, game)
    history = history_rows(committed_snapshots() + [Snapshot(date.today().isoformat(), summary, game)], area_names)
    stats = totals(summary, game)
    readme = README.read_text(encoding="utf-8")
    return {
        HISTORY_CSV: render_history_csv(history),
        PROGRESS / "map.svg": render_map(summary, stats, sections),
        PROGRESS / "card.svg": render_card(stats, history, summary["exe"]),
        PROGRESS / "history.svg": render_history(history),
        README: replace_between_markers(readme, render_recent_changes(history)),
    }


def write_visuals() -> None:
    for path, text in render_all().items():
        path.write_text(text, encoding="utf-8", newline="\n")


if __name__ == "__main__":
    import check  # here, not at the top: check.py imports this module

    check.rerun_in_venv(__file__)
    write_visuals()
