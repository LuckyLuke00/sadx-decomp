#!/usr/bin/env python3
"""Build the static progress site for GitHub Pages.

  python tools/pages.py [--out DIR]

Reads only committed files: docs/progress/summary.json, history.csv and the
SVGs, data/areas.yml and areas.csv, data/functions.csv and
data/codegen-groups.csv, the sources under src, and an optional export,
docs/progress/hard-tail.csv. Writes plain HTML pages and shields.io endpoint
badges to DIR (default _site). The areas come
from tools/areas.py, as on the progress map, so run as a script it reruns
itself in .venv.
"""

import argparse
import collections
import html
import json
import re
import shutil
from pathlib import Path

import names
import progress
import scoring

SVG_NAMES = ["card", "map", "history"]
HARD_TAIL_CSV = progress.PROGRESS / "hard-tail.csv"
PLACEHOLDER = re.compile(r"FUN_[0-9a-fA-F]{8}")
RULE_CHANGES = [("2026-10-22", "Functions that match only through a trick, such as inline assembly, no longer count as "
                               "matched.")]  # (date, text) of each change to the scoring rules
RANKS = ["E", "D", "C", "B", "A", "Emblem"]  # the game's mission ranks for each fifth of an area's code, then all of it
NEAR_MISS = 0.9  # the lowest score the near misses page lists
FUNCTION_COLUMNS = ["Address", "Size", "Score", "Code group", "Source file"]
ICON_THEME = progress.LIGHT._replace(done="currentColor", muted="currentColor")  # the CSS colours the site's icons

STYLE = """
:root { --bg: #ffffff; --text: #1f2328; --muted: #59636e; --border: #d0d7de; --head: #f6f8fa; --link: #0969da;
  --accent: #b07d00; }
@media (prefers-color-scheme: dark) {
  :root { --bg: #0d1117; --text: #e6edf3; --muted: #8b949e; --border: #30363d; --head: #161b22; --link: #4493f8;
    --accent: #ffd700; }
}
* { box-sizing: border-box; }
body { margin: 0; background: var(--bg); color: var(--text); font: 16px/1.5 system-ui, "Segoe UI", sans-serif; }
main { max-width: 60rem; margin: 0 auto; padding: 16px; }
a { color: var(--link); }
h1 { font-size: 1.6rem; margin: 0.5rem 0; }
h2 { font-size: 1.2rem; margin: 1.5rem 0 0.5rem; }
.big { font-size: 1.5rem; font-weight: 600; color: var(--accent); margin: 0.25rem 0; }
picture, img { display: block; max-width: 100%; height: auto; margin: 0.75rem 0; }
.wrap { overflow-x: auto; border: 1px solid var(--border); }
table { border-collapse: collapse; width: 100%; }
th, td { text-align: left; padding: 4px 8px; border-bottom: 1px solid var(--border); white-space: nowrap; }
th { background: var(--head); }
h3 { font-size: 1rem; margin: 1rem 0 0.25rem; }
.banner { background: linear-gradient(#2a5ee8, #102f8c); border-bottom: 3px solid #ffd700; }
.banner a { display: block; max-width: 60rem; margin: 0 auto; padding: 10px 16px; color: #ffffff; font-weight: 700;
  text-decoration: none; }
.banner .icon { color: #ffd700; margin-right: 6px; }
.icon { vertical-align: -3px; }
.earned { color: var(--accent); }
.locked { color: var(--muted); }
.rank { display: inline-block; min-width: 1.6em; padding: 0 0.3em; border: 1px solid var(--accent); border-radius: 4px;
  color: var(--accent); font-weight: 700; text-align: center; }
.emblems { list-style: none; padding: 0; }
"""


def e(value: object) -> str:
    return html.escape(str(value))


def write(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8", newline="\n")


def hex_address(address: int) -> str:
    return f"0x{address:08x}"


def icon(shape: str, kind: str) -> str:
    """A 16 px inline icon of one shape drawn around (8, 8) in ICON_THEME. The CSS class KIND gives its colour."""
    return f'<svg class="icon {kind}" viewBox="0 0 16 16" width="16" height="16" aria-hidden="true">{shape}</svg>'


def emblem_icon(earned: bool) -> str:
    return icon(progress.emblem(8, 8, earned, ICON_THEME), "earned" if earned else "locked")


def page(title: str, body: str, root: str = "") -> str:
    """A page under the site's banner, which links home."""
    return (f'<!doctype html>\n<html lang="en">\n<head>\n<meta charset="utf-8">\n'
            f'<meta name="viewport" content="width=device-width, initial-scale=1">\n'
            f"<title>{e(title)}</title>\n<style>{STYLE}</style>\n</head>\n<body>\n"
            f'<header class="banner"><a href="{root}index.html">{icon(progress.ring(8, 8, ICON_THEME), "ring")}'
            f"Decompilation progress</a></header>\n<main>\n{body}</main>\n</body>\n</html>\n")


def table(columns: list[str], rows: list[list[object]]) -> str:
    """A table in a wrapper that scrolls by itself. It escapes the cells."""
    head = "".join(f"<th>{e(column)}</th>" for column in columns)
    lines = ["".join(f"<td>{e(cell)}</td>" for cell in row) for row in rows]
    body = "".join(f"<tr>{line}</tr>\n" for line in lines)
    return f'<div class="wrap"><table>\n<tr>{head}</tr>\n{body}</table></div>\n'


def picture(name: str, alt: str) -> str:
    return (f'<picture>\n  <source media="(prefers-color-scheme: dark)" srcset="{name}-dark.svg">\n'
            f'  <img src="{name}.svg" alt="{e(alt)}">\n</picture>\n')


def source_files() -> dict[int, list[str]]:
    """The sources under src, as paths relative to the repo, that annotate each function."""
    found = collections.defaultdict(list)
    for rel, text in names.read_sources(progress.ROOT).items():
        for kind, address, _ in names.parse_annotations(text):
            if kind in names.FUNCTION_KINDS:
                found[address].append(rel)
    return found


class Site:
    """Everything the pages show, read once."""

    def __init__(self) -> None:
        self.summary = progress.load_summary()
        functions = progress.load_functions()
        self.groups = progress.load_codegen_groups()
        self.sizes = progress.function_sizes(functions)
        game = progress.game_addresses(functions, self.groups)
        self.game = scoring.game_functions(self.summary, game)
        self.entries = scoring.entries_by_address(self.summary)
        self.stats = scoring.totals(self.summary, game)
        self.code = scoring.code_bytes(self.summary, game, self.sizes)
        self.history = progress.read_csv(progress.HISTORY_CSV)
        self.area_of, sections = progress.load_areas(self.summary, game)
        self.area_names = {area: name for _, _, named in sections for area, name in named.items()}
        self.section_of = {area: section for section, _, named in sections for area in named}
        self.sources = source_files()
        self.emblems = progress.area_emblems(self.summary, self.code, self.area_of, sections, self.sizes)

    def is_matched(self, address: int) -> bool:
        entry = self.entries.get(address)
        return entry is not None and scoring.is_matched(entry)

    def named_total(self) -> int:
        return sum(1 for entry in self.entries.values()
                   if not entry["library"] and scoring.is_matched(entry) and not PLACEHOLDER.fullmatch(entry["name"]))

    def areas(self) -> dict[str, list[int]]:
        """The game functions of each area that has any, in the progress map's order."""
        found = collections.defaultdict(list)
        for address in sorted(self.game):
            found[self.area_of[address]].append(address)
        return {area: found[area] for area in self.area_names if area in found}

    def area_title(self, area: str) -> str:
        return self.area_names[area]

    def area_code(self, addresses: list[int]) -> scoring.Bytes:
        return scoring.code_bytes(self.summary, set(addresses), self.sizes)

    def headline(self) -> str:
        return (f"{scoring.count_text(self.code.matched, self.code.game, 'code bytes matched')}, "
                f"{scoring.count_text(self.stats.matched, self.stats.game_total, 'game functions')}")


def share_color(part: int, whole: int) -> str:
    """The colour the progress map gives a share, without the #."""
    return progress.partial_color(scoring.ratio(part, whole), progress.LIGHT).lstrip("#")


def badge(label: str, part: int, whole: int, prefix: str = "") -> str:
    """A shields.io endpoint badge that shows a share, after the prefix if it has one."""
    data = {"schemaVersion": 1, "label": label, "message": f"{prefix} {scoring.percent(part, whole)}".lstrip(),
            "color": share_color(part, whole)}
    return json.dumps(data, indent=1) + "\n"


def rank(part: int, whole: int) -> str:
    """E below 20% of the whole, D below 40%, and so on up to A below 100%. All of it earns the emblem."""
    return RANKS[(len(RANKS) - 1) * part // max(whole, 1)]


def rank_chip(code: scoring.Bytes) -> str:
    """The rank of an area's code bytes matched, with the emblem icon once it has all of them."""
    found = rank(code.matched, code.game)
    shown = f"{emblem_icon(True)} {found}" if found == RANKS[-1] else found
    return f'<span class="rank" title="Rank by code bytes matched">{shown}</span>'


def steps_table(site: Site) -> str:
    total = site.stats.game_total
    steps = [("Decompiled", site.stats.decompiled), ("Matched in plain C", site.stats.matched),
             ("Named in the tree", site.named_total())]
    return table(["Step", "Functions", "Share of game functions"],
                 [[name, f"{count:,}", scoring.percent(count, total)] for name, count in steps])


def area_links(site: Site) -> str:
    """The links to the area pages, one list for each section of the map."""
    by_section = collections.defaultdict(list)
    for area, addresses in site.areas().items():
        link = (f'<li><a href="areas/{e(area)}.html">{e(site.area_title(area))}</a> '
                f'{rank_chip(site.area_code(addresses))}</li>')
        by_section[site.section_of[area]].append(link)
    return "".join(f"<h3>{e(section)}</h3>\n<ul>\n" + "\n".join(items) + "\n</ul>\n"
                   for section, items in by_section.items())


def index_page(site: Site) -> str:
    data = scoring.count_text(*scoring.data_share(site.summary), "bytes of initialized data match")
    emblems = f"{scoring.earned_count(site.emblems)} of {len(site.emblems)}"
    body = (f"<h1>{e(site.summary['target'])} decompilation progress</h1>\n"
            f'<p class="big">{scoring.count_text(site.code.matched, site.code.game, "code bytes matched")}</p>\n'
            f"<p>{scoring.count_text(site.stats.matched, site.stats.game_total, 'game functions matched')}</p>\n"
            "<p>A function is matched when our plain C compiles to the same instructions as the original. "
            "The code share counts the size of those functions, so a large function weighs more than a small one.</p>\n"
            f"<h2>Steps</h2>\n{steps_table(site)}"
            f"<h2>Data</h2>\n<p>{data}.</p>\n"
            "<p>A global matches when its value in our exe is the same as in the original. The whole is the original's "
            ".data and .rdata as stored in the file. Zero-filled data (.bss) is left out, because a "
            "placeholder matches it for free. Runtime library globals count in neither part, as with code. The whole "
            "still holds middleware data, strings and floats, which this count does not credit yet, so it can't "
            "reach 100%.</p>\n"
            f"<h2>Card</h2>\n{picture('card', 'Progress summary')}"
            f"<h2>Map</h2>\n{picture('map', 'Progress map by area')}"
            f"<h2>History</h2>\n{picture('history', 'Progress history')}"
            '<h2>Pages</h2>\n<ul>\n'
            f'<li><a href="emblems.html">Emblems</a>: {emblems}</li>\n'
            '<li><a href="near-misses.html">Near misses</a></li>\n<li><a href="changelog.html">Changelog</a></li>\n'
            '<li><a href="hard-tail.html">Hard tail</a></li>\n</ul>\n'
            "<h2>Areas</h2>\n<p>An area's rank comes from its code bytes matched: E below 20%, D below 40%, C below "
            "60%, B below 80% and A below 100%. All of it earns the area's emblem.</p>\n"
            f"{area_links(site)}")
    return page("Progress", body)


def function_row(site: Site, address: int) -> list[object]:
    entry = site.entries.get(address)
    group = progress.codegen_group(site.groups, address)
    return [hex_address(address), site.sizes[address], scoring.state_text(entry),group["group"] if group else "",
            ", ".join(site.sources.get(address, []))]


def area_page(site: Site, area: str, addresses: list[int]) -> str:
    entries = site.entries
    done = progress.done_count(addresses, entries)
    code = site.area_code(addresses)
    code_text = scoring.count_text(code.matched, code.game, "code bytes matched")
    open_rows = [function_row(site, a) for a in addresses if a not in entries or scoring.score(entries[a]) < 1.0]
    trick_rows = [function_row(site, a) for a in addresses if a in entries and scoring.is_trick(entries[a])]
    trick = table(FUNCTION_COLUMNS, trick_rows) if trick_rows else "<p>No function is flagged yet.</p>\n"
    body = (f"<p>{e(site.section_of[area])}</p>\n<h1>{e(site.area_title(area))}</h1>\n"
            f'<p class="big">{rank_chip(code)} {code_text}</p>\n'
            f"<p>{scoring.count_text(done, len(addresses), 'game functions matched')}</p>\n"
            f"<h2>Functions not matched yet</h2>\n{table(FUNCTION_COLUMNS, open_rows)}"
            "<h2>Functions that need a plain-C rewrite</h2>\n"
            f"<p>These match only through a trick. They count as not matched.</p>\n{trick}")
    return page(site.area_title(area), body, "../")


def emblem_state(emblem: scoring.Emblem) -> str:
    return "earned" if emblem.earned else f"{emblem.needed - emblem.matched:,} code bytes to go"


def emblems_page(site: Site) -> str:
    items = "".join(f"<li>{emblem_icon(emblem.earned)} {e(emblem.name)}: {emblem_state(emblem)}</li>\n"
                    for emblem in site.emblems)
    body = ("<h1>Emblems</h1>\n"
            f'<p class="big">{scoring.earned_count(site.emblems)} of {len(site.emblems)} emblems earned</p>\n'
            f"<p>The game's code earns an emblem for each {scoring.EMBLEM_STEP}% of its bytes matched. Each area earns "
            "one when all of its code matches. Only matches in plain C count.</p>\n"
            f'<ul class="emblems">\n{items}</ul>\n')
    return page("Emblems", body)


def near_misses(site: Site) -> list[int]:
    """The game functions at NEAR_MISS or more that are not at 100% yet, highest score first, then smallest."""
    found = [address for address in site.game
             if address in site.entries and NEAR_MISS <= scoring.score(site.entries[address]) < 1.0]
    return sorted(found, key=lambda address: (-scoring.score(site.entries[address]), site.sizes[address]))


def near_misses_page(site: Site) -> str:
    rows = [function_row(site, address) + [site.area_title(site.area_of[address])] for address in near_misses(site)]
    body = ("<h1>Near misses</h1>\n"
            f"<p>The game functions at {NEAR_MISS:.0%} or more that are not at 100% yet, closest first, then smallest. "
            "A good place to start.</p>\n"
            f"{table(FUNCTION_COLUMNS + ['Area'], rows)}")
    return page("Near misses", body)


def changelog_rows(history: list[dict]) -> list[tuple[str, str]]:
    rows = list(RULE_CHANGES)
    for before, now in zip(history, history[1:]):
        if before["game_total"] != now["game_total"]:
            text = f"The game total changed from {int(before['game_total']):,} to {int(now['game_total']):,} functions."
            rows.append((now["date"], text))
    return sorted(rows, key=lambda row: row[0])


def changelog_page(site: Site) -> str:
    rows = changelog_rows(site.history)
    return page("Changelog", f"<h1>Changelog</h1>\n{table(['Date', 'Change'], rows)}")


def read_export(path: Path) -> list[dict]:
    """The rows of an optional exported CSV file: none when it is missing."""
    return progress.read_csv(path) if path.exists() else []


def csv_page(title: str, rows: list[dict], intro: str) -> str:
    """A page for the rows of an exported CSV file, with the columns of its header."""
    if not rows:
        return page(title, f"<h1>{e(title)}</h1>\n<p>No rows yet.</p>\n")
    columns = list(rows[0])
    return page(title, f"<h1>{e(title)}</h1>\n<p>{e(intro)}</p>\n"
                       f"{table(columns, [[row[column] for column in columns] for row in rows])}")


def hard_tail_page(site: Site) -> str:
    """The hard tail export without the functions the tree matches now: the export is made by hand, so it goes
    stale."""
    rows = read_export(HARD_TAIL_CSV)
    open_rows = [row for row in rows if not site.is_matched(int(row["address"], 16))]
    intro = ("The functions that were tried and are not matched yet, most tries first. Best is the highest score any "
             "try reached. A best of 100.0 means a try matched, but that code is not in the tree.")
    left_out = len(rows) - len(open_rows)
    if left_out:
        intro += f" Left out because the tree matches them now: {left_out:,}."
    return csv_page("Hard tail", open_rows, intro)


def badge_files(site: Site) -> dict[str, str]:
    files = {"badges/matched.json": badge("functions matched", site.stats.matched, site.stats.game_total),
             "badges/bytes.json": badge("code matched", site.code.matched, site.code.game)}
    for area, addresses in site.areas().items():
        code = site.area_code(addresses)
        files[f"badges/{area}.json"] = badge(site.area_title(area), code.matched, code.game,
                                             rank(code.matched, code.game))
    return files


def render_all(site: Site) -> dict[str, str]:
    files = {"index.html": index_page(site), "emblems.html": emblems_page(site),
             "near-misses.html": near_misses_page(site), "changelog.html": changelog_page(site),
             "hard-tail.html": hard_tail_page(site)}
    for area, addresses in site.areas().items():
        files[f"areas/{area}.html"] = area_page(site, area, addresses)
    files.update(badge_files(site))
    return files


def build(out: Path) -> None:
    site = Site()
    for rel, text in render_all(site).items():
        write(out / rel, text)
    for name in SVG_NAMES:
        for suffix in progress.THEMES:
            shutil.copyfile(progress.PROGRESS / f"{name}{suffix}.svg", out / f"{name}{suffix}.svg")
    print(site.headline())


def main() -> None:
    parser = argparse.ArgumentParser(description="Build the static progress site.")
    parser.add_argument("--out", type=Path, default=progress.ROOT / "_site", help="output folder (default: _site)")
    build(parser.parse_args().out)


if __name__ == "__main__":
    import check  # here, not at the top: only the script run needs it, not the tests that import this module

    check.rerun_in_venv(__file__)
    main()
