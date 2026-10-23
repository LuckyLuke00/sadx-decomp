#!/usr/bin/env python3
"""Draw the README progress visuals and the progress history.

  python tools/progress.py

Reads docs/progress/summary.json, data/functions.csv and data/codegen-groups.csv,
and the same three files in each commit that changed summary.json. The map sorts
the game functions into the areas tools/areas.py gives them.
Writes history.csv, and card.svg, history.svg and map.svg in docs/progress, each
in a light version and a dark one with -dark in its name. The history has a row
for the first first-parent commit that changed summary.json, and one for each
later one that changed the totals. The working tree, the commit being made,
counts as a commit of today when its totals differ from the last row's. The
output depends only on committed files, so CI can check that it is current.
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
from scoring import (Totals, accuracy_text, game_functions, is_matched, is_trick, percent, ratio, score, state,
                     stats_line, totals, whole_percent)

ROOT = Path(__file__).resolve().parent.parent
PROGRESS = ROOT / "docs" / "progress"
SUMMARY_JSON = PROGRESS / "summary.json"
HISTORY_CSV = PROGRESS / "history.csv"
FUNCTIONS_CSV = ROOT / "data" / "functions.csv"
CODEGEN_GROUPS = ROOT / "data" / "codegen-groups.csv"

HISTORY_FIELDS = ["date", "decompiled", "matched", "accuracy", "game_total"]


class Theme(NamedTuple):
    background: str
    border: str  # around the drawing and each block
    block: str
    text: str
    muted: str
    grid: str
    not_started: str
    done: str
    decompiled: str
    accuracy: str
    # Partial scores in 10% steps, from 0% to the done colour at 100%, on a straight line in OKLab, where equal steps
    # look equal. The lightness moves away from the block colour the whole way, so the order holds for every kind of
    # colour vision.
    partial: list[str]


# Both themes use GitHub's neutral greys, so the drawings sit well on its light and dark pages. In the dark theme
# the partial scores rise from blue to gold. In the light theme they fall from blue to a darker gold, which keeps its
# contrast on white.
DARK = Theme(background="#161b22", border="#30363d", block="#21262d", text="#e6edf3", muted="#8b949e",
             grid="#30363d", not_started="#0d1117", done="#ffd700", decompiled="#4493f8", accuracy="#e6edf3",
             partial=["#2753d8", "#3a66d0", "#4e77c7", "#6386bd", "#7893b2", "#8ea0a6", "#a4ac97", "#bab786",
                      "#d1c270", "#e8cd51", "#ffd700"])
LIGHT = Theme(background="#f6f8fa", border="#d0d7de", block="#ffffff", text="#1f2328", muted="#59636e",
              grid="#d0d7de", not_started="#e6eaef", done="#b07d00", decompiled="#0969da", accuracy="#1f2328",
              partial=["#6f9ff0", "#779dde", "#7f9bcc", "#8699b9", "#8d96a7", "#939394", "#9a8f80", "#a08c6b",
                       "#a58754", "#ab8239", "#b07d00"])
THEMES = {"": LIGHT, "-dark": DARK}  # each theme's suffix to the file names

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
    """The scores of each first-parent commit that changed summary.json, oldest first."""
    if subprocess.run(["git", "rev-parse", "--verify", "--quiet", "HEAD"], cwd=ROOT, capture_output=True).returncode:
        return []  # no commit yet
    paths = [path.relative_to(ROOT).as_posix() for path in (SUMMARY_JSON, FUNCTIONS_CSV, CODEGEN_GROUPS)]
    log = osutil.git(ROOT, "log", "--first-parent", "--reverse", "--format=%H %as", "--", paths[0]).decode()
    commits = [line.split() for line in log.splitlines()]
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


def history_rows(snapshots: list[Snapshot]) -> list[dict]:
    """The history rows of the snapshots, oldest first: the first snapshot, then each one that changed the totals.
    Stubs score zero, so a commit that only adds or removes stubs gets no row."""
    rows = []
    for snapshot in snapshots:
        row = history_row(snapshot.day, totals(snapshot.summary, snapshot.game))
        if not rows or not same_totals(row, rows[-1]):
            rows.append(row)
    return rows


def history_row(day: str, stats: Totals) -> dict:
    return {
        "date": day,
        "decompiled": str(stats.decompiled),
        "matched": str(stats.matched),
        "accuracy": f"{stats.accuracy * 100:.2f}" if stats.accuracy is not None else "",
        "game_total": str(stats.game_total),
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


def partial_color(value: float, theme: Theme) -> str:
    """The colour of a score from 0 to 1, between the two steps of theme.partial around it."""
    steps = len(theme.partial) - 1
    low = min(int(value * steps), steps - 1)
    t = value * steps - low
    low_rgb, high_rgb = bytes.fromhex(theme.partial[low][1:]), bytes.fromhex(theme.partial[low + 1][1:])
    return "#" + "".join(f"{round(a + (b - a) * t):02x}" for a, b in zip(low_rgb, high_rgb))


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
    return sum(1 for address in cells if address in entries and is_matched(entries[address]))


def map_header(summary: dict, stats: Totals, height: int, theme: Theme) -> list[str]:
    """The map's opening tags: title, background and the three text lines."""
    stats_text = (f"{stats.matched:,} of {stats.game_total:,} game functions done "
                  f"({percent(stats.matched, stats.game_total)}), accuracy {accuracy_text(stats)}")
    return [
        f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {WIDTH} {height}" width="{WIDTH}" height="{height}">',
        f'<title>{escape(summary["exe"])} decompilation progress</title>',
        backdrop(WIDTH, height, theme),
        f'<text x="{MARGIN}" y="28" font-family="{FONT}" font-size="18" font-weight="600" fill="{theme.text}">'
        f'{escape(summary["exe"])}</text>',
        f'<text x="{WIDTH - MARGIN}" y="28" text-anchor="end" font-family="{FONT}" font-size="12" '
        f'fill="{theme.muted}">one square per function</text>',
        f'<text x="{MARGIN}" y="50" font-family="{FONT}" font-size="13" fill="{theme.muted}">{escape(stats_text)}</text>',
    ]


def backdrop(width: int, height: int, theme: Theme) -> str:
    """The background of a drawing: a rounded rectangle with a thin border, like GitHub's boxes."""
    return (f'<rect x="0.5" y="0.5" width="{width - 1}" height="{height - 1}" rx="6" fill="{theme.background}" '
            f'stroke="{theme.border}"/>')


def ring(x: float, y: float, theme: Theme) -> str:
    """A gold ring centred on (x, y)."""
    return f'<circle cx="{x:g}" cy="{y:g}" r="5" fill="none" stroke="{theme.done}" stroke-width="2.5"/>'


def gem(x: float, y: float, color: str, theme: Theme) -> list[str]:
    """A cut gem 12 px wide centred on (x, y), with a light top facet and a thin edge, so a pale gem shows on a light
    background too."""
    outline = [(x - 3, y - 5), (x + 3, y - 5), (x + 6, y - 1.5), (x, y + 5.5), (x - 6, y - 1.5)]
    facet = [(x - 3, y - 5), (x + 3, y - 5), (x + 1.5, y - 1.5), (x - 1.5, y - 1.5)]
    return [f'<polygon points="{svg_points(outline)}" fill="{color}" stroke="{theme.muted}" stroke-width="0.75" '
            'stroke-linejoin="round"/>',
            f'<polygon points="{svg_points(facet)}" fill="#ffffff" fill-opacity="0.45"/>']


def section_title(section: Section, outer: Rect, entries: dict[int, dict], theme: Theme) -> list[str]:
    """The section's gem, name and done share."""
    cells = [address for block in section.blocks for address in block.cells]
    share = whole_percent(done_count(cells, entries), len(cells))
    x, baseline = outer.x + SECTION_GAP, outer.y + TITLE - 7
    parts = gem(x + GEM_WIDTH / 2, baseline - 4.5, section.color, theme) if section.color else []
    parts.append(f'<text x="{x + title_indent(section)}" y="{baseline}" font-family="{FONT}" '
                 f'font-size="{TITLE_SIZE}" font-weight="600" fill="{theme.text}">{escape(section.name)} '
                 f'<tspan font-weight="400" fill="{theme.muted}">{share}</tspan></text>')
    return parts


def name_text(lines: list[list[str]], share: str, rect: Rect, theme: Theme) -> list[str]:
    """The block's name in its lines, with the done share in place of the SHARE_SAMPLE that ends the last one."""
    parts = []
    for row, words in enumerate(lines):
        name, tail = words, ""
        if row == len(lines) - 1:
            name = words[:-1]
            share_text = f'<tspan font-weight="400" fill="{theme.muted}">{share}</tspan>'
            tail = f" {share_text}" if name else share_text
        y = rect.y + PAD + (row + 1) * NAME_LINE_HEIGHT - 4
        parts.append(f'<text x="{rect.x + PAD}" y="{y}" font-family="{FONT}" font-size="{NAME_SIZE}" '
                     f'font-weight="600" fill="{theme.text}">{escape(" ".join(name))}{tail}</text>')
    return parts


def todo_pattern(theme: Theme) -> str:
    """The pattern of not-started cells that todo_rect fills with."""
    return (f'<defs><pattern id="todo" width="{PITCH}" height="{PITCH}" patternUnits="userSpaceOnUse">'
            f'<rect width="{CELL}" height="{CELL}" fill="{theme.not_started}"/></pattern></defs>')


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


def scored_cells(cells: list[int], entries: dict[int, dict], columns: int, theme: Theme) -> list[str]:
    """One colored cell with a tooltip for each function with a score, from the block's first cell. A stub has
    none: it is not started. A function at 100% through a trick gets the highest step below full, as it is not done."""
    rects = []
    for index, address in enumerate(cells):
        entry = entries.get(address)
        if entry is None or entry["stub"]:
            continue
        color = theme.partial[-2] if is_trick(entry) else partial_color(score(entry), theme)
        rects.append(f'<rect x="{index % columns * PITCH}" y="{index // columns * PITCH}" width="{CELL}" '
                     f'height="{CELL}" fill="{color}">'
                     f'<title>{cell_label(address, entry)}</title></rect>')
    return rects


def block_border(done: bool, theme: Theme) -> str:
    """The border of a block or its key swatch: gold for a finished area."""
    return f' stroke="{theme.done}" stroke-width="1.5"' if done else f' stroke="{theme.border}"'


def block_parts(block: Block, rect: Rect, entries: dict[int, dict], theme: Theme) -> list[str]:
    """A block's background with its tooltip, its name and its cells."""
    done = done_count(block.cells, entries)
    tip = escape(f"{block.name}: {done:,} of {len(block.cells):,} done")
    parts = [f'<rect x="{rect.x + 1}" y="{rect.y + 1}" width="{rect.width - 2}" height="{rect.height - 2}" rx="3" '
             f'fill="{theme.block}"{block_border(done == len(block.cells), theme)}><title>{tip}</title></rect>']
    lines, columns = block_grid(block, rect)
    parts += name_text(lines, whole_percent(done, len(block.cells)), rect, theme)
    parts.append(f'<g transform="translate({rect.x + PAD},{rect.y + PAD + len(lines) * NAME_LINE_HEIGHT})">')
    parts += todo_cells(len(block.cells), columns)
    parts += scored_cells(block.cells, entries, columns, theme)
    parts.append("</g>")
    return parts


def map_legend(height: int, theme: Theme) -> list[str]:
    """The colour key on a strip of block colour, as the cells sit on their block. Under it, a line on the code the
    map leaves out."""
    y = height - FOOTER + 22
    keys = [([theme.not_started], "", "not started"),
            ([partial_color(step / 10, theme) for step in range(10)], "", "partly matching, 0% to 99%"),
            ([theme.done], "", "done"), ([theme.block], block_border(True, theme), "area done")]
    swatches = []
    x = MARGIN
    for colors, border, label in keys:
        for color in colors:
            swatches.append(f'<rect x="{x}" y="{y - 9}" width="10" height="10" rx="2" fill="{color}"{border}/>')
            x += 12
        swatches.append(f'<text x="{x + 3}" y="{y}" font-family="{FONT}" font-size="12" fill="{theme.muted}">'
                        f'{label}</text>')
        x += 3 + round(text_width(label, 12)) + KEY_GAP
    strip_end = x - KEY_GAP + STRIP_PAD
    return [f'<rect x="{MARGIN - STRIP_PAD}" y="{y - 15}" width="{strip_end - MARGIN + STRIP_PAD}" height="22" rx="4" '
            f'fill="{theme.block}"{block_border(False, theme)}/>',
            *swatches,
            f'<text x="{MARGIN}" y="{y + 22}" font-family="{FONT}" font-size="12" fill="{theme.muted}">'
            "Library code is left out: it needs no decompiling.</text>"]


def render_map(summary: dict, stats: Totals, sections: list[Section], theme: Theme) -> str:
    entries = {int(entry["address"], 16): entry for entry in summary["functions"]}
    placed = map_layout(sections)
    height = max((outer.y + outer.height for outer, _ in placed), default=HEADER) + FOOTER
    parts = map_header(summary, stats, height, theme)
    parts.append(todo_pattern(theme))
    for section, (outer, rects) in zip(sections, placed):
        parts += section_title(section, outer, entries, theme)
        for block, rect in zip(section.blocks, rects):
            parts += block_parts(block, rect, entries, theme)
    parts += map_legend(height, theme)
    parts.append("</svg>")
    return "\n".join(parts) + "\n"


def card_bar(stats: Totals, theme: Theme) -> list[str]:
    """The progress bar across the card: a track, then the decompiled and done shares over it."""
    bar_y, bar_width = 96, WIDTH - 2 * MARGIN
    parts = [f'<rect x="{MARGIN}" y="{bar_y}" width="{bar_width}" height="8" rx="4" fill="{theme.not_started}"/>']
    decompiled = ratio(stats.decompiled, stats.game_total)
    matched = ratio(stats.matched, stats.game_total)
    # At least 2 px wide once there is anything, so the first functions show.
    for fraction, color in ((decompiled, theme.decompiled), (matched, theme.done)):
        if fraction > 0:
            parts.append(f'<rect x="{MARGIN}" y="{bar_y}" width="{max(2.0, bar_width * fraction):.1f}" height="8" '
                         f'rx="4" fill="{color}"/>')
    return parts


def card_figures(stats: Totals, theme: Theme) -> list[str]:
    """The three figures under the bar, one in each third of the card."""
    figures = [(f"{stats.matched:,}", "done"), (accuracy_text(stats), "accuracy"),
               (f"{stats.game_total:,}", "game functions")]
    parts = []
    column = (WIDTH - 2 * MARGIN) / len(figures)
    for index, (value, label) in enumerate(figures):
        x = MARGIN + index * column
        parts.append(f'<text x="{x:.0f}" y="134" font-family="{FONT}" font-size="18" font-weight="600" '
                     f'fill="{theme.text}">{escape(value)}</text>')
        parts.append(f'<text x="{x:.0f}" y="152" font-family="{FONT}" font-size="12" fill="{theme.muted}">'
                     f'{label}</text>')
    return parts


def done_this_week(history: list[dict]) -> int:
    """The functions done since the last history row a week or more before the newest. It counts from the newest
    row's date, not from today, so the card depends only on the history."""
    newest = date.fromisoformat(history[-1]["date"])
    before = [row for row in history if date.fromisoformat(row["date"]) <= newest - timedelta(days=7)]
    return int(history[-1]["matched"]) - (int(before[-1]["matched"]) if before else 0)


def render_card(stats: Totals, history: list[dict], exe: str, theme: Theme) -> str:
    """The summary card at the top of the README, as wide as the map."""
    height = 168
    parts = [
        f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {WIDTH} {height}" width="{WIDTH}" height="{height}">',
        f'<title>{escape(stats_line(stats))}</title>',
        backdrop(WIDTH, height, theme),
        f'<text x="{MARGIN}" y="30" font-family="{FONT}" font-size="13" fill="{theme.muted}">{escape(exe)}</text>',
        f'<text x="{WIDTH - MARGIN}" y="30" text-anchor="end" font-family="{FONT}" font-size="12" '
        f'fill="{theme.muted}">updated {escape(history[-1]["date"])}</text>',
        f'<text x="{MARGIN}" y="76" font-family="{FONT}" font-size="40" font-weight="600" fill="{theme.text}">'
        f'{percent(stats.matched, stats.game_total)}<tspan dx="10" font-size="13" font-weight="400" '
        f'fill="{theme.muted}">of the game done</tspan></text>',
        f'<text x="{WIDTH - MARGIN - 17}" y="76" text-anchor="end" font-family="{FONT}" font-size="13" '
        f'font-weight="600" fill="{theme.text}">{done_this_week(history):+,} this week</text>',
        ring(WIDTH - MARGIN - 6, 71.5, theme),  # its right edge lines up with the text above
    ]
    parts += card_bar(stats, theme)
    parts += card_figures(stats, theme)
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


def history_legend(theme: Theme) -> list[str]:
    parts = []
    x = HISTORY_RIGHT
    for label, color in reversed([("decompiled", theme.decompiled), ("done", theme.done),
                                  ("accuracy", theme.accuracy)]):
        x -= round(text_width(label, 12)) + 15
        parts.append(f'<rect x="{x}" y="19" width="10" height="10" rx="2" fill="{color}"/>')
        parts.append(f'<text x="{x + 15}" y="28" font-family="{FONT}" font-size="12" fill="{theme.muted}">'
                     f'{label}</text>')
        x -= 18
    return parts


def panel_grid(panel: Panel, theme: Theme) -> list[str]:
    """The three horizontal grid lines of a panel, each with its percent label."""
    parts = []
    for fraction in (0.0, 0.5, 1.0):
        y = panel.bottom - (panel.bottom - panel.top) * fraction
        parts.append(f'<line x1="{HISTORY_LEFT}" y1="{y:.1f}" x2="{HISTORY_RIGHT}" y2="{y:.1f}" '
                     f'stroke="{theme.grid}" stroke-width="1"/>')
        parts.append(f'<text x="{HISTORY_LEFT - 8}" y="{y + 4:.1f}" text-anchor="end" font-family="{FONT}" '
                     f'font-size="11" fill="{theme.muted}">{panel.top_value * fraction * 100:g}%</text>')
    return parts


def day_starts(dates: list[str]) -> list[int]:
    """The index of the first row of each day."""
    return [index for index, day in enumerate(dates) if index == 0 or day != dates[index - 1]]


def day_lines(dates: list[str], panel: Panel, theme: Theme) -> list[str]:
    """A vertical grid line across the panel before the first dot of each day but the first. The rows sit an even
    step apart, not by time, so these lines show where the days change."""
    parts = []
    for index in day_starts(dates)[1:]:
        x = (history_x(index - 1, len(dates)) + history_x(index, len(dates))) / 2
        parts.append(f'<line x1="{x:.1f}" y1="{panel.top}" x2="{x:.1f}" y2="{panel.bottom}" stroke="{theme.grid}" '
                     'stroke-width="1"/>')
    return parts


def dot_radius(count: int) -> float:
    """3 px, or a third of the step between dots when they sit closer than 9 px, but at least 1 px."""
    if count < 2:
        return 3.0
    return max(1.0, min(3.0, (HISTORY_RIGHT - HISTORY_LEFT) / (count - 1) / 3))


def plot_line(line: Line, panel: Panel, dates: list[str]) -> list[str]:
    """A polyline through the line's values, and a dot with a tooltip at each one."""
    height = panel.bottom - panel.top
    points = [(history_x(index, len(dates)), panel.bottom - height * value / panel.top_value, index, value)
              for index, value in enumerate(line.values) if value is not None]
    radius = dot_radius(len(dates))
    parts = []
    if len(points) > 1:
        path = " ".join(f"{px:.1f},{py:.1f}" for px, py, _, _ in points)
        parts.append(f'<polyline points="{path}" fill="none" stroke="{line.color}" stroke-width="2"/>')
    for px, py, index, value in points:
        tip = escape(f"{dates[index]}: {line.label} {value:.2%}")
        parts.append(f'<circle cx="{px:.1f}" cy="{py:.1f}" r="{radius:.1f}" fill="{line.color}">'
                     f'<title>{tip}</title></circle>')
    return parts


def date_labels(dates: list[str], y: int, theme: Theme) -> list[str]:
    """The date of each day, centred under its dots and kept inside the drawing. A label that would come within
    8 px of the one before is left out."""
    parts, last_end = [], -math.inf
    starts = day_starts(dates)
    for start, end in zip(starts, starts[1:] + [len(dates)]):
        width = text_width(dates[start], 11)
        middle = (history_x(start, len(dates)) + history_x(end - 1, len(dates))) / 2
        x = min(max(middle, MARGIN + width / 2), WIDTH - MARGIN - width / 2)
        if x - width / 2 < last_end + 8:
            continue
        parts.append(f'<text x="{x:.1f}" y="{y}" text-anchor="middle" font-family="{FONT}" font-size="11" '
                     f'fill="{theme.muted}">{escape(dates[start])}</text>')
        last_end = x + width / 2
    return parts


def history_heading(theme: Theme) -> list[str]:
    """The history chart's opening tags: background and the two panel titles."""
    return [
        f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {WIDTH} {HISTORY_HEIGHT}" '
        f'width="{WIDTH}" height="{HISTORY_HEIGHT}">',
        "<title>Decompilation progress over time</title>",
        backdrop(WIDTH, HISTORY_HEIGHT, theme),
        f'<text x="{MARGIN}" y="28" font-family="{FONT}" font-size="15" font-weight="600" fill="{theme.text}">'
        "Share of game functions decompiled and done</text>",
        f'<text x="{MARGIN}" y="176" font-family="{FONT}" font-size="15" font-weight="600" fill="{theme.text}">'
        "Accuracy of the decompiled functions</text>",
    ]


def render_history(history: list[dict], theme: Theme) -> str:
    """Two panels over the history rows, one dot a row: completeness on an auto scale, accuracy on 0 to 100%."""
    decompiled = [ratio(int(row["decompiled"]), int(row["game_total"])) for row in history]
    matched = [ratio(int(row["matched"]), int(row["game_total"])) for row in history]
    accuracy = [float(row["accuracy"]) / 100 if row["accuracy"] else None for row in history]
    panels = [
        Panel(48, 140, axis_top(max(decompiled + matched)),
              [Line("decompiled", decompiled, theme.decompiled), Line("done", matched, theme.done)]),
        Panel(196, 288, 1.0, [Line("accuracy", accuracy, theme.accuracy)]),
    ]
    parts = history_heading(theme)
    parts += history_legend(theme)
    dates = [row["date"] for row in history]
    for panel in panels:
        parts += panel_grid(panel, theme)
        parts += day_lines(dates, panel, theme)
        for line in panel.lines:
            parts += plot_line(line, panel, dates)
    parts += date_labels(dates, panels[-1].bottom + 22, theme)  # below the lower panel
    parts.append("</svg>")
    return "\n".join(parts) + "\n"


def load_areas(summary: dict, game: set[int]) -> list[Section]:
    """The map's sections."""
    import areas  # here, not at the top: it needs .venv's packages, and check.py imports this module before .venv

    area_of, sections = areas.load(game_functions(summary, game))
    return map_sections(area_of, sections)


def render_all() -> dict[Path, str]:
    """Every generated file and its expected text, from the committed inputs only."""
    summary = load_summary()
    game = game_addresses(load_functions())
    sections = load_areas(summary, game)
    history = history_rows(committed_snapshots() + [Snapshot(date.today().isoformat(), summary, game)])
    stats = totals(summary, game)
    files = {HISTORY_CSV: render_history_csv(history)}
    for suffix, theme in THEMES.items():
        files[PROGRESS / f"map{suffix}.svg"] = render_map(summary, stats, sections, theme)
        files[PROGRESS / f"card{suffix}.svg"] = render_card(stats, history, summary["exe"], theme)
        files[PROGRESS / f"history{suffix}.svg"] = render_history(history, theme)
    return files


def write_visuals() -> None:
    for path, text in render_all().items():
        path.write_text(text, encoding="utf-8", newline="\n")


if __name__ == "__main__":
    import check  # here, not at the top: check.py imports this module

    check.rerun_in_venv(__file__)
    write_visuals()
