#!/usr/bin/env python3
"""Build the static progress site for GitHub Pages.

  python tools/pages.py [--out DIR]

Reads only committed files: docs/progress/summary.json and history.csv,
data/areas.yml and areas.csv, data/functions.csv and
data/codegen-groups.csv, and the sources under src. The GitHub link comes
from git's origin remote. Writes the home page, a page for each area, the
Help out page and shields.io endpoint badges to DIR (default _site). The
areas come from tools/areas.py, as on the progress map, so run as a script
it reruns itself in .venv.
"""

import argparse
import collections
import html
import json
import random
from collections.abc import Iterable
from pathlib import Path

import areas
import layout
import names
import osutil
import progress
import scoring

NEAR_MISS = 0.9  # the lowest score the Help out page lists
STAR = ", ".join(f"{x:g}% {y:g}%" for x, y in layout.star_points(50, 50, 50, 21))  # the emblem's star as a CSS polygon
WATER_TILE = (600, 450)  # the size of one tile of the water pattern, in px
WATER_BLEED = 20  # how far a blurred cell may lie outside its tile and still show in it, in px
TAB_CURVE = ("<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 34 40' preserveAspectRatio='none'>"
             "<path d='M0 0 C18 0 16 40 34 40 L0 40 Z' fill='{}'/></svg>")  # the S-curve edge of a file tab


def caustics(seed: int, opacity: float, inset: tuple[float, float], blur: float) -> str:
    """A tile of water caustics as SVG: the light lines between rounded cells, softly blurred. The cells sit on a
    jittered grid, so they stay about the same size, and wrap at the tile's edges, so the tiles join. A seed gives the
    same tile on every build."""
    width, height = WATER_TILE
    rng = random.Random(seed)
    sites = []
    for row in range(4):
        for column in range(4):
            x = (column + 0.5 + rng.uniform(-0.38, 0.38)) * width / 4 + (row % 2) * width / 8
            y = (row + 0.5 + rng.uniform(-0.38, 0.38)) * height / 4
            sites.append((x % width, y))
    shifts = [(dx, dy) for dx in (-width, 0, width) for dy in (-height, 0, height)]
    copies = [(x + dx, y + dy) for x, y in sites for dx, dy in shifts]
    paths = []
    for site in sites:
        cell = layout.voronoi_cell(site, copies, rng.uniform(*inset), max(width, height))
        for dx, dy in shifts:
            moved = [(x + dx, y + dy) for x, y in cell]
            xs, ys = [x for x, _ in moved], [y for _, y in moved]
            if (max(xs) >= -WATER_BLEED and min(xs) <= width + WATER_BLEED
                    and max(ys) >= -WATER_BLEED and min(ys) <= height + WATER_BLEED):
                paths.append(layout.rounded_path(moved))
    return (f"<svg xmlns='http://www.w3.org/2000/svg' width='{width}' height='{height}' "
            f"viewBox='0 0 {width} {height}'>"
            f"<filter id='b' x='-10%' y='-10%' width='120%' height='120%'>"
            f"<feGaussianBlur stdDeviation='{blur}'/></filter>"
            f"<mask id='m'><rect x='-50' y='-50' width='{width + 100}' height='{height + 100}' fill='white'/>"
            f"<path filter='url(#b)' fill='black' d='{''.join(paths)}'/></mask>"
            f"<rect width='{width}' height='{height}' fill='#e8fcff' fill-opacity='{opacity}' mask='url(#m)'/></svg>")


STYLE = """
:root { color-scheme: dark; --royal: #0c14e8; --violet: #3a1490; --sky: #1a8cf6; --sky-light: #7cc4fa;
  --ink: #001062; --yellow: #ffff00; --gold: #ffb408; --emblem-light: #f8c048; --emblem: #f8b800;
  --emblem-dark: #f88800; --ring-light: #f0e070; --ring: #ccaa33; --ring-dark: #554411; --window: rgba(0, 0, 0, 0.74);
  --tab-blue: #0a50ff; --tab-yellow: #ffb000; --orange: #ff6a00; --cyan: #66dde0;
  --heavy: italic 900 1rem/1.2 "Arial Black", "Segoe UI", system-ui, sans-serif; }
* { box-sizing: border-box; }
html { background: var(--sky); }
body { margin: 0; min-height: 100vh; display: flex; flex-direction: column; color: #ffffff;
  font: 16px/1.5 "Segoe UI", system-ui, sans-serif; }
.sky { position: fixed; inset: 0; z-index: -1; overflow: hidden; background:
    repeating-linear-gradient(180deg, rgba(255, 255, 255, 0.16) 0 2px, transparent 2px 4px),
    radial-gradient(34vw 9vw at 12% 30%, rgba(255, 255, 255, 0.9), transparent 70%),
    radial-gradient(28vw 7vw at 24% 36%, rgba(255, 255, 255, 0.7), transparent 70%),
    radial-gradient(40vw 10vw at 86% 62%, rgba(255, 255, 255, 0.85), transparent 70%),
    radial-gradient(26vw 8vw at 70% 70%, rgba(255, 255, 255, 0.6), transparent 70%),
    NEAR_WATER 0 0 / 600px 450px, FAR_WATER 230px 140px / 1000px 750px,
    linear-gradient(180deg, #0a6cf0, var(--sky) 45%, var(--sky-light)); }
.arc { position: absolute; border-radius: 50%; border: solid rgba(255, 255, 255, 0.6); }
.arc.one { width: 150vmax; height: 150vmax; right: -95vmax; top: -40vmax; border-width: 9px; }
.arc.two { width: 120vmax; height: 120vmax; left: -88vmax; bottom: -70vmax; border-width: 4px; }
.band { background:
    repeating-linear-gradient(180deg, rgba(0, 0, 30, 0.45) 0 1px, transparent 1px 3px),
    linear-gradient(90deg, var(--royal), #1010d0 55%, var(--violet)); }
.band.top { border-bottom: 6px solid #ffffff; box-shadow: 0 4px 0 rgba(0, 0, 60, 0.35); }
.band.bottom { margin-top: auto; border-top: 6px solid #ffffff; box-shadow: 0 -4px 0 rgba(0, 0, 60, 0.35); }
.inner, main { width: calc(100% - 32px); max-width: 60rem; margin: 0 auto; }
.band.top .inner { padding: 12px 0 16px; }
.band.bottom .inner { padding: 14px 0 18px; }
main { padding-bottom: 48px; }
.topline { display: flex; flex-wrap: wrap; align-items: center; justify-content: space-between; gap: 10px 24px; }
.game { display: inline-flex; align-items: center; gap: 0.4em; color: #ffffff; text-decoration: none;
  font-weight: 700; text-shadow: 0 1px 0 #000000, 0 0 3px #000000; }
.game:hover, .game:focus-visible { color: var(--yellow); }
.ring { display: inline-block; width: 1.1em; height: 1.1em; border-radius: 50%; animation: spin 1.8s linear infinite;
  background: radial-gradient(circle, transparent 40%, #000000 41%, var(--ring-dark) 46%, var(--ring) 54%,
    var(--ring-light) 63%, var(--ring) 72%, var(--ring-dark) 80%, #000000 86%, transparent 87%); }
@keyframes spin { to { transform: rotateY(360deg); } }
@media (prefers-reduced-motion: reduce) { .ring { animation: none; } }
.kicker { margin: 10px 0 0; color: var(--yellow); font: var(--heavy); font-size: 0.95rem;
  -webkit-text-stroke: 0.14em #000000; paint-order: stroke fill; }
h1 { margin: 2px 0 0; font: var(--heavy); font-size: clamp(1.9rem, 6.4vw, 3.4rem); letter-spacing: 0.01em;
  -webkit-text-stroke: 0.14em #000000; paint-order: stroke fill; text-shadow: 0.05em 0.07em 0 rgba(0, 0, 40, 0.6); }
.window { margin-top: 28px; padding: 18px 24px 20px; border-radius: 24px; background: var(--window);
  box-shadow: 0 0 12px var(--window); }
.window p { margin: 0 0 14px; max-width: 44rem; }
.hudrow { display: grid; grid-template-columns: max-content auto; gap: 0 18px; align-items: baseline;
  margin: 6px 0 12px; }
.hudrow dt, .hudrow dd, .pct { font: var(--heavy); -webkit-text-stroke: 0.16em #000000; paint-order: stroke fill; }
.hudrow dt { color: var(--yellow); font-size: 1.1rem; text-transform: uppercase; }
.hudrow dd { margin: 0; font-size: 1.8rem; }
.hudrow .emblem { display: inline-block; vertical-align: middle; }
.hudrow small { font-size: 1.1rem; }
.gauge { display: block; height: 18px; border: 2px solid #ffffff; border-radius: 9px; background: #0a0040;
  overflow: hidden; }
.gauge span { display: block; height: 100%; min-width: 6px; border-radius: inherit;
  background: linear-gradient(180deg, var(--emblem-light), var(--emblem) 50%, var(--emblem-dark)); }
.gain { margin: 10px 0 0 !important; color: var(--yellow); font: var(--heavy); -webkit-text-stroke: 0.14em #000000;
  paint-order: stroke fill; }
h2 { position: relative; display: flex; margin: 40px 0 0; border-bottom: 5px solid var(--tab);
  font: var(--heavy); font-size: 1.15rem; filter: drop-shadow(3px 3px 0 rgba(0, 0, 0, 0.5)); }
h2 .label { position: relative; display: flex; align-items: center; gap: 8px; padding: 6px 12px 3px 14px;
  border-radius: 14px 0 0 0; background: var(--tab); -webkit-text-stroke: 0.14em #000000; paint-order: stroke fill; }
h2 .label::after { content: ""; position: absolute; left: 100%; bottom: 0; width: 34px; height: 100%;
  background: var(--curve) center / 100% 100%; }
h2.blue { --tab: var(--tab-blue); --curve: BLUE_CURVE; }
h2.yellow { --tab: var(--tab-yellow); --curve: YELLOW_CURVE; }
h2 + p, .lead { margin: 12px 0 0; font-weight: 600; text-shadow: 0 1px 0 #000000, 0 0 4px #000000, 0 0 8px #000000; }
.gem { flex: none; width: 1.1em; filter: drop-shadow(1px 1px 0 rgba(0, 0, 0, 0.6)); }
.bars { display: grid; grid-template-columns: repeat(auto-fill, minmax(min(100%, 18rem), 1fr)); gap: 8px 18px;
  margin: 14px 0 0; padding: 0; list-style: none; }
.bars.wide { grid-template-columns: repeat(auto-fill, minmax(min(100%, 22rem), 1fr)); }
.bar { --fill: linear-gradient(180deg, #5a5e6c 0 2px, #33363f 3px, #1e2028 55%, #121318); --step: 92px;
  position: relative; isolation: isolate; display: flex; align-items: center; gap: 10px; height: 56px;
  padding: 12px calc(var(--step) + 16px) 0 34px; color: #ffffff; text-decoration: none; }
.shape { position: absolute; inset: 0; z-index: -1; filter: drop-shadow(4px 4px 0 rgba(0, 0, 0, 0.55)); }
.shape::before, .shape::after { content: ""; position: absolute; background: var(--fill) 0 0 / 100% 56px no-repeat; }
.shape::before { inset: 12px 0 0; border-radius: 22px 0 0 22px; background-position: 0 -12px;
  box-shadow: inset 0 2px 0 rgba(255, 255, 255, 0.2); }
.shape::after { top: 0; right: 0; bottom: 0; width: calc(var(--step) + 12px);
  background-image: var(--step-fill, var(--fill)); clip-path: polygon(0 100%, 0 12px, 12px 0, 100% 0, 100% 100%); }
.bar::before { content: ""; position: absolute; left: -6px; top: 17px; width: 34px; height: 34px;
  border: 4px solid #ffffff; border-radius: 50%; opacity: 0; box-shadow: 0 0 0 2px rgba(0, 0, 0, 0.5);
  mask: conic-gradient(#000 0 170deg, transparent 170deg 190deg, #000 190deg 350deg, transparent 350deg); }
a.bar:hover, a.bar:focus-visible { --fill: linear-gradient(180deg, #ffffff 0 55%, #dfe6f6); color: var(--ink);
  outline: none; }
a.bar:hover::before, a.bar:focus-visible::before { opacity: 1; }
.bar.done { --fill: linear-gradient(180deg, #fff4b0 0 2px, #ffe080 3px, var(--gold) 55%, var(--emblem-dark));
  color: var(--ink); }
.name { flex: 1 1 auto; min-width: 0; overflow: hidden; text-overflow: ellipsis; white-space: nowrap;
  font-weight: 700; }
.bar:not(:hover):not(:focus-visible):not(.done) .name { text-shadow: 0 1px 0 #000000; }
.name code { margin-right: 10px; font: 600 0.9rem Consolas, "Cascadia Mono", monospace; }
.step { position: absolute; top: 0; right: 0; bottom: 0; display: flex; align-items: center; justify-content: flex-end;
  gap: 8px; width: var(--step); padding: 12px 8px 0 0; }
.pct { font-size: 1rem; -webkit-text-stroke: 0; }
.bar.near { --step: 74px;
  --step-fill: linear-gradient(180deg, #ffc070 0 2px, #ff9a30 3px, var(--orange) 55%, #c84400); }
.bar.near .pct { color: #ffffff; -webkit-text-stroke: 0.16em #000000; }
.emblem { position: relative; flex: none; width: 30px; height: 30px; border-radius: 3px; }
.emblem.earned { background: linear-gradient(180deg, var(--emblem-dark), var(--emblem) 50%, var(--emblem-light));
  box-shadow: 0 0 0 2px var(--window), inset 0 0 0 3px var(--gold), inset 5px 5px 0 0 #c85800; }
.emblem.locked { background: rgba(0, 0, 0, 0.8); box-shadow: inset 0 0 0 2px rgba(255, 255, 255, 0.25); }
.emblem::after { content: ""; position: absolute; inset: 7px; clip-path: polygon(STAR); }
.emblem.earned::after { background: rgba(255, 244, 190, 0.85); }
.emblem.locked::after { background: rgba(255, 255, 255, 0.2); }
.files { columns: 2 22rem; column-gap: 12px; margin: 14px 0 0; padding: 0; list-style: none; }
.file { position: relative; break-inside: avoid; margin-bottom: 12px; padding: 10px 14px 12px 34px;
  border: 3px solid #ffffff; border-radius: 16px; background: var(--window);
  box-shadow: 4px 4px 0 rgba(0, 0, 0, 0.45); }
.file::before { content: ""; position: absolute; left: 12px; top: 16px; width: 12px; height: 12px; border-radius: 50%;
  background: var(--cyan); }
.file a { color: var(--yellow); font-weight: 700; word-break: break-all; text-decoration: none; }
.file a:hover, .file a:focus-visible { text-decoration: underline; }
.file ul { margin: 4px 0 0; padding: 0; list-style: none; font: 0.9rem/1.5 Consolas, "Cascadia Mono", monospace; }
.file .unnamed { color: #c8d0e8; font-family: "Segoe UI", system-ui, sans-serif; }
.hints { display: flex; flex-wrap: wrap; gap: 10px 22px; margin: 0; }
.band.bottom .hints { margin-bottom: 10px; }
.hint { display: inline-flex; align-items: center; gap: 8px; color: #ffffff; text-decoration: none; font: var(--heavy);
  -webkit-text-stroke: 0.14em #000000; paint-order: stroke fill; }
.hint:hover, .hint:focus-visible { color: var(--yellow); outline: none; }
.icon { display: inline-grid; place-items: center; width: 28px; height: 28px; border: 2px solid #ffffff;
  border-radius: 50%; background: radial-gradient(circle at 35% 30%, rgba(255, 255, 255, 0.55), transparent 45%),
  var(--key); box-shadow: 2px 2px 0 rgba(0, 0, 0, 0.5); }
.hint:hover .icon, .hint:focus-visible .icon { border-color: var(--yellow); }
.icon svg { width: 16px; height: 16px; fill: none; stroke: #ffffff; stroke-width: 2.6; stroke-linecap: round;
  stroke-linejoin: round; filter: drop-shadow(0 1px 0 rgba(0, 0, 0, 0.55)); }
.icon.back { --key: #1e5af0; } .icon.help { --key: #f07800; } .icon.code { --key: #18a040; }
.nowrap { white-space: nowrap; }
.small { margin: 0; font-size: 0.85rem; color: #d8dcff; }
a { color: var(--yellow); }
@media (max-width: 40rem) { .window { padding: 14px 16px 16px; } .hudrow dd { font-size: 1.45rem; } }
"""
STYLE = (STYLE.replace("NEAR_WATER", layout.svg_url(caustics(seed=7, opacity=0.34, inset=(2.5, 5.5), blur=2.4)))
         .replace("FAR_WATER", layout.svg_url(caustics(seed=11, opacity=0.16, inset=(3, 6), blur=3.5)))
         .replace("BLUE_CURVE", layout.svg_url(TAB_CURVE.format("#0a50ff")))
         .replace("YELLOW_CURVE", layout.svg_url(TAB_CURVE.format("#ffb000")))
         .replace("STAR", STAR))

# the button icons, on a 16 px grid; the wrench is filled, the rest are lines
ICONS = {"back": "<path d='M10 3 L5 8 L10 13'/>",
         "help": "<path fill='#ffffff' stroke='none' transform='rotate(-45 8 8)' "
                 "d='M2 6.6 H7.56 A3.9 3.9 0 0 1 14.8 6.5 H11.6 V9.5 H14.8 A3.9 3.9 0 0 1 7.56 9.4 H2 "
                 "A1.4 1.4 0 0 1 2 6.6 Z'/>",
         "code": "<path d='M5.5 4.5 L2 8 L5.5 11.5'/><path d='M10.5 4.5 L14 8 L10.5 11.5'/>"}
SHAPE = '<span class="shape" aria-hidden="true"></span>'  # a bar's body and raised step, drawn behind its text


def e(value: object) -> str:
    return html.escape(str(value))


def write(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8", newline="\n")


def hex_address(address: int) -> str:
    return f"0x{address:08x}"


def read_annotations() -> tuple[dict[int, list[str]], dict[int, str | None]]:
    """The sources under src that annotate each function, as paths relative to the repo, and the name the function's
    first annotation declares, None when it declares none."""
    sources, declared = collections.defaultdict(list), {}
    for rel, text in names.read_sources(progress.ROOT).items():
        for kind, address, sig in names.parse_annotations(text):
            if kind in names.FUNCTION_KINDS:
                sources[address].append(rel)
                declared.setdefault(address, names.declared_name(sig))
    return sources, declared


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
        self.section_colors = {section: color for section, color, _ in sections}
        self.sources, self.names = read_annotations()
        self.emblems = progress.area_emblems(self.summary, self.area_of, sections, self.sizes)
        self.earned = {emblem.name: emblem.earned for emblem in self.emblems}  # the unsorted area has none
        self.about = areas.about()

    def is_matched(self, address: int) -> bool:
        entry = self.entries.get(address)
        return entry is not None and scoring.is_matched(entry)

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


def frame(site: Site, title: str, kicker: str, body: str, hints: str) -> str:
    """A page in the frame of the game's menus: the sky, a top band with the game's name, the HINTS and the TITLE,
    then the body, and a bottom band with the HINTS again. The name comes from the exe and links home. KICKER, BODY
    and HINTS are HTML."""
    game = Path(site.summary["exe"]).stem
    return (f'<!doctype html>\n<html lang="en">\n<head>\n<meta charset="utf-8">\n'
            f'<meta name="viewport" content="width=device-width, initial-scale=1">\n'
            f"<title>{e(game)} decomp: {e(title)}</title>\n<style>{STYLE}</style>\n</head>\n<body>\n"
            '<div class="sky" aria-hidden="true"><span class="arc one"></span><span class="arc two"></span></div>\n'
            f'<header class="band top"><div class="inner">\n<div class="topline"><a class="game" href="index.html">'
            f'<span class="ring" aria-hidden="true"></span>{e(game)} decomp</a>\n'
            f'<nav class="hints" aria-label="Pages">{hints}</nav></div>\n'
            f'<p class="kicker">{kicker}</p>\n<h1>{e(title)}</h1>\n</div></header>\n'
            f"<main>\n{body}</main>\n"
            f'<footer class="band bottom"><div class="inner">\n'
            f'<nav class="hints" aria-label="Pages, at the end">{hints}</nav>\n'
            f"<p class=\"small\">Updated {e(site.history[-1]['date'])}. "
            "A fan project, not affiliated with the game's publisher.</p>\n"
            "</div></footer>\n</body>\n</html>\n")


def hint(icon: str, label: str, href: str) -> str:
    """A link as one of the game's round buttons with an icon, then its label."""
    return (f'<a class="hint" href="{e(href)}"><span class="icon {icon}" aria-hidden="true">'
            f'<svg viewBox="0 0 16 16">{ICONS[icon]}</svg></span>{e(label)}</a>')


def hud(rows: list[tuple[str, str]]) -> str:
    """Counters as in the game's HUD: a yellow label, then its value. The values are HTML."""
    items = "".join(f"<dt>{e(label)}</dt><dd>{value}</dd>\n" for label, value in rows)
    return f'<dl class="hudrow">\n{items}</dl>\n'


def heading(kind: str, label: str, gem_svg: str = "") -> str:
    """A heading as a file tab, blue or yellow, with an optional gem before its label."""
    return f'<h2 class="{kind}"><span class="label">{gem_svg}{e(label)}</span></h2>\n'


def gauge(part: int, whole: int) -> str:
    """A gold gauge filled to part of whole. The fill shows only once there is anything."""
    fill = f'<span style="width: {scoring.ratio(part, whole):.2%}"></span>' if part else ""
    return f'<span class="gauge" aria-hidden="true">{fill}</span>'


def gain_html(history: list[dict]) -> str:
    """The gain text with its last word, the date, kept on one line."""
    head, last = progress.gain_text(history).rsplit(" ", 1)
    return f'{e(head)} <span class="nowrap">{e(last)}</span>'


def emblem_slot(earned: bool) -> str:
    kind, label = ("earned", "Emblem earned") if earned else ("locked", "No emblem yet")
    return f'<span class="emblem {kind}" role="img" aria-label="{label}" title="{label}"></span>'


def gem(color: str | None) -> str:
    """A section's gem: the progress map's, in its colour with a black edge. The unsorted section has no colour, so it
    gets none."""
    if not color:
        return ""
    width, height = progress.GEM_WIDTH + 2, progress.GEM_HEIGHT + 2
    parts = "".join(progress.gem(width / 2, height / 2, e(color), "#000000"))
    return f'<svg class="gem" viewBox="0 0 {width:g} {height:g}" aria-hidden="true">{parts}</svg>'


def area_bar(site: Site, area: str, addresses: list[int]) -> str:
    """An area as a bar of the trial stage select that links to its page: its name, then its share and emblem slot
    on the bar's raised step. The unsorted area has no slot."""
    code = site.area_code(addresses)
    earned = site.earned.get(area)
    slot = "" if earned is None else emblem_slot(earned)
    done = " done" if earned else ""
    return (f'<li><a class="bar{done}" href="area-{e(area)}.html">{SHAPE}'
            f'<span class="name">{e(site.area_title(area))}</span><span class="step"><span class="pct">'
            f"{scoring.whole_percent(code.matched, code.game)}</span>{slot}</span></a></li>")


def area_bars(site: Site) -> str:
    """The area bars under a blue tab with its gem for each section of the map."""
    by_section = collections.defaultdict(list)
    for area, addresses in site.areas().items():
        by_section[site.section_of[area]].append(area_bar(site, area, addresses))
    return "".join(heading("blue", section, gem(site.section_colors[section]))
                   + '<ul class="bars">\n' + "\n".join(bars) + "\n</ul>\n" for section, bars in by_section.items())


def index_page(site: Site, repo: str) -> str:
    code, stats = site.code, site.stats
    body = ('<section class="window">\n'
            + hud([("Code", scoring.percent(code.matched, code.game)),
                   ("Functions", f"{stats.matched:,} <small>/ {stats.game_total:,}</small>"),
                   ("Emblems", f"{scoring.earned_count(site.emblems)} <small>/ {len(site.emblems)}</small>")])
            + f'{gauge(code.matched, code.game)}\n<p class="gain">{gain_html(site.history)}</p>\n'
            "</section>\n" + area_bars(site))
    hints = hint("help", "Help out", "near-misses.html") + hint("code", "GitHub", repo)
    return frame(site, "Area Select", "Decompilation progress", body, hints)


def near_misses(site: Site, addresses: Iterable[int]) -> list[int]:
    """The functions among addresses at NEAR_MISS or more that are not at 100% yet, highest score first, then
    smallest."""
    found = [address for address in addresses
             if address in site.entries and NEAR_MISS <= scoring.score(site.entries[address]) < 1.0]
    return sorted(found, key=lambda address: (-scoring.score(site.entries[address]), site.sizes[address]))


def near_bar(site: Site, repo: str, address: int) -> str:
    """A near miss as a bar with an orange step: its address and size, then its score on the step. It links to its
    source file when it has one."""
    files = site.sources.get(address, [])
    inner = (f'{SHAPE}<span class="name"><code>{hex_address(address)}</code>{site.sizes[address]:,} bytes</span>'
             f'<span class="step"><span class="pct">{scoring.state_text(site.entries[address])}</span></span>')
    if files:
        return (f'<li><a class="bar near" href="{e(repo)}/blob/HEAD/{e(files[0])}" title="{e(files[0])}">'
                f"{inner}</a></li>\n")
    return f'<li><span class="bar near">{inner}</span></li>\n'


def near_bars(site: Site, repo: str, near: list[int]) -> str:
    return '<ul class="bars wide">\n' + "".join(near_bar(site, repo, address) for address in near) + "</ul>\n"


def guide_link(repo: str) -> str:
    return f'<a href="{e(repo)}/blob/HEAD/docs/FIRST-FUNCTION.md">The guide</a>'


def file_card(repo: str, rel: str, declared: list[str | None]) -> str:
    """A source file as a card that links to it, with the names its functions declare. A placeholder name counts as
    none yet, and so does None: a TEMPLATE annotation declares no name, since its name is a comment."""
    named = [name for name in declared if name and not name.startswith("FUN_")]
    items = "".join(f"<li>{e(name)}</li>" for name in named)
    unnamed = len(declared) - len(named)
    if unnamed:
        items += f'<li class="unnamed">{unnamed:,} without a name yet</li>'
    return f'<li class="file"><a href="{e(repo)}/blob/HEAD/{e(rel)}">{e(Path(rel).name)}</a><ul>{items}</ul></li>'


def area_page(site: Site, repo: str, area: str, addresses: list[int]) -> str:
    """An area's page: its text, its counters, its matched functions by file, its near misses and how many are left."""
    code = site.area_code(addresses)
    matched = [address for address in addresses if site.is_matched(address)]
    near = near_misses(site, addresses)
    by_file = collections.defaultdict(list)
    for address in matched:
        by_file[site.sources[address][0]].append(site.names[address])
    rows = [("Code", scoring.percent(code.matched, code.game)),
            ("Functions", f"{len(matched):,} <small>/ {len(addresses):,}</small>")]
    earned = site.earned.get(area)
    if earned is not None:
        rows.append(("Emblem", emblem_slot(earned)))
    about = "".join(f"<p>{e(paragraph)}</p>\n" for paragraph in site.about.get(area, "").splitlines())
    body = ('<section class="window">\n' + about
            + hud(rows) + f"{gauge(code.matched, code.game)}\n</section>\n" + heading("blue", "Cleared"))
    if matched:
        cards = "\n".join(file_card(repo, rel, by_file[rel]) for rel in sorted(by_file))
        body += (f"<p>Matched: {layout.counted(len(matched), 'function')} in "
                 f"{layout.counted(len(by_file), 'file')}.</p>\n" + f'<ul class="files">\n{cards}\n</ul>\n')
    else:
        body += "<p>Nothing matches here yet.</p>\n"
    body += heading("yellow", "Almost there")
    if near:
        body += (f"<p>These are {NEAR_MISS:.0%} done or more. {guide_link(repo)} shows you how to finish one.</p>\n"
                 + near_bars(site, repo, near))
    else:
        body += f"<p>Nothing here is at {NEAR_MISS:.0%} yet.</p>\n"
    rest = len(addresses) - len(matched) - len(near)
    if rest:
        body += f'<p class="lead">{layout.counted(rest, "more function")} to go.</p>\n'
    hints = (hint("back", "Back", "index.html") + hint("help", "Help out", "near-misses.html")
             + hint("code", "GitHub", repo))
    section = site.section_of[area]
    return frame(site, site.area_title(area), f"{gem(site.section_colors[section])} {e(section)}", body, hints)


def near_misses_page(site: Site, repo: str) -> str:
    """The near misses of every area, under a yellow tab for each area that has any."""
    groups = ""
    for area, addresses in site.areas().items():
        near = near_misses(site, addresses)
        if near:
            groups += heading("yellow", site.area_title(area)) + near_bars(site, repo, near)
    body = ('<section class="window">\n'
            f"<p>These functions are {NEAR_MISS:.0%} done or more. Pick a small one and finish it. "
            f"{guide_link(repo)} shows you how.</p>\n</section>\n" + groups)
    hints = hint("back", "Back", "index.html") + hint("code", "GitHub", repo)
    return frame(site, "Help out", "Decompilation progress", body, hints)


def share_color(part: int, whole: int) -> str:
    """The colour the progress map gives a share, without the #."""
    return progress.partial_color(scoring.ratio(part, whole), progress.LIGHT).lstrip("#")


def badge(label: str, part: int, whole: int) -> str:
    """A shields.io endpoint badge that shows a share."""
    data = {"schemaVersion": 1, "label": label, "message": scoring.percent(part, whole),
            "color": share_color(part, whole)}
    return json.dumps(data, indent=1) + "\n"


def badge_files(site: Site) -> dict[str, str]:
    files = {"badges/matched.json": badge("functions matched", site.stats.matched, site.stats.game_total),
             "badges/bytes.json": badge("code matched", site.code.matched, site.code.game)}
    for area, addresses in site.areas().items():
        code = site.area_code(addresses)
        files[f"badges/{area}.json"] = badge(site.area_title(area), code.matched, code.game)
    return files


def render_all(site: Site, repo: str) -> dict[str, str]:
    files = {"index.html": index_page(site, repo), "near-misses.html": near_misses_page(site, repo)}
    for area, addresses in site.areas().items():
        files[f"area-{area}.html"] = area_page(site, repo, area, addresses)
    files.update(badge_files(site))
    return files


def build(out: Path) -> None:
    site = Site()
    repo = osutil.web_url(osutil.git(progress.ROOT, "remote", "get-url", "origin").decode().strip())
    for rel, text in render_all(site, repo).items():
        write(out / rel, text)
    print(site.headline())


def main() -> None:
    parser = argparse.ArgumentParser(description="Build the static progress site.")
    parser.add_argument("--out", type=Path, default=progress.ROOT / "_site", help="output folder (default: _site)")
    build(parser.parse_args().out)


if __name__ == "__main__":
    import check  # here, not at the top: only the script run needs it, not the tests that import this module

    check.rerun_in_venv(__file__)
    main()
