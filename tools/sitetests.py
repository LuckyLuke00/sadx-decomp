"""Checks for tools/pages.py: the badge colours, the near misses, the home page and an area page. Also the layout
helpers its art uses, the remote's web link from tools/osutil.py and the measures of tools/objdiffreport.py."""

import json
from types import SimpleNamespace

import layout
import objdiffreport
import osutil
import pages
import progress
import scoring


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


def entry(accuracy: float, stub: bool = False, trick: bool = False) -> dict:
    return {"name": "f", "accuracy": accuracy, "stub": stub, "library": False, "trick": trick}


def check_near_misses() -> list[str]:
    """Only the given functions from 90% up to below 100% count: the highest score first, then the smallest."""
    entries = {0x401000: entry(0.95), 0x401010: entry(0.95), 0x401020: entry(0.99), 0x401030: entry(0.89),
               0x401040: entry(1.0, trick=True), 0x401050: entry(0.99, stub=True), 0x401060: entry(0.92)}
    sizes = {0x401000: 40, 0x401010: 8, 0x401020: 100, 0x401030: 4, 0x401040: 4, 0x401050: 4, 0x401060: 4}
    fake = SimpleNamespace(entries=entries, sizes=sizes)
    found = pages.near_misses(fake, set(entries) - {0x401060} | {0x401070})
    wanted = [0x401020, 0x401010, 0x401000]
    return [] if found == wanted else [f"near_misses gives {[hex(a) for a in found]}, not {[hex(a) for a in wanted]}"]


def check_index_page() -> list[str]:
    """The HUD shows the code share, the functions, the emblems and the gain. Each area links to its page. A complete
    area gets a gold emblem, an area below 100% an empty slot, and the unsorted area none. Only a section with a colour
    gets a gem. The page escapes the names."""
    codes = {"done": scoring.Bytes(8, 8, 8), "open": scoring.Bytes(8, 2, 8), "unsorted": scoring.Bytes(4, 1, 4)}
    fake = SimpleNamespace(
        summary={"exe": "Game.exe"}, code=scoring.Bytes(20, 11, 20), stats=SimpleNamespace(matched=3, game_total=7),
        emblems=[scoring.Emblem("done", 8, 8), scoring.Emblem("open", 2, 8)], earned={"done": True, "open": False},
        history=[{"date": "2026-10-01", "matched_bytes": "0", "game_bytes": "20"},
                 {"date": "2026-10-02", "matched_bytes": "11", "game_bytes": "20"}],
        areas=lambda: {area: [index] for index, area in enumerate(codes)},
        section_of={"done": "S<1>", "open": "S<1>", "unsorted": "Not sorted"},
        section_colors={"S<1>": "#ff0000", "Not sorted": None},
        area_title=lambda area: f"{area} <b>", area_code=lambda addresses: list(codes.values())[addresses[0]])
    text = pages.index_page(fake, "https://example.com/r")
    failures = [f"index_page does not show {wanted!r}"
                for wanted in ("<dd>55.00%</dd>", "<dd>3 <small>/ 7</small></dd>", "<dd>1 <small>/ 2</small></dd>",
                               '+55.00% of the code since <span class="nowrap">2026-10-01</span>', "done &lt;b&gt;",
                               "S&lt;1&gt;",
                               'href="area-done.html"', 'href="area-unsorted.html"')
                if wanted not in text]
    if text.count('class="emblem earned"') != 1 or text.count('class="emblem locked"') != 1:
        failures.append("index_page does not give one gold emblem, one empty slot and none for the unsorted area")
    if text.count('class="gem"') != 1:
        failures.append("index_page does not give exactly the section with a colour a gem")
    if "<b>" in text:
        failures.append("index_page does not escape the area names")
    return failures


def check_area_page() -> list[str]:
    """An area page shows its text, escaped, with a paragraph per line, its matched functions by file with their names
    and a count of those without one, its near misses highest score first, and how many functions are left. The
    unsorted area has no emblem, and an area without a text shows none."""
    entries = {1: entry(1.0), 2: entry(1.0), 3: entry(1.0), 4: entry(0.91), 5: entry(0.97), 6: entry(0.5)}
    fake = SimpleNamespace(
        summary={"exe": "Game.exe"}, history=[{"date": "2026-10-02"}], entries=entries,
        sizes=dict.fromkeys(range(1, 8), 8), sources={1: ["src/a<b>.c"], 2: ["src/a<b>.c"], 3: ["src/c.c"],
                                                      4: ["src/c.c"], 5: ["src/c.c"]},
        names={1: "Foo", 2: "FUN_00000002", 3: "Bar<T>", 4: "Baz", 5: "Qux"}, earned={"area": False},
        about={"area": "Whales & <waves>\nMore"},section_of={"area": "S", "unsorted": "Not sorted"},
        section_colors={"S": "#ff0000", "Not sorted": None}, is_matched=lambda address: address <= 3,
        area_title=lambda area: area.title(), area_code=lambda addresses: scoring.Bytes(56, 24, 56))
    text = pages.area_page(fake, "https://example.com/r", "area", list(range(1, 8)))
    failures = [f"area_page does not show {wanted!r}"
                for wanted in ("<p>Whales &amp; &lt;waves&gt;</p>\n<p>More</p>","a&lt;b&gt;.c</a>", "<li>Foo</li>",
                               "<li>Bar&lt;T&gt;</li>", "1 without a name yet", "Matched: 3 functions in 2 files.",
                               "2 more functions to go.", "<dt>Emblem</dt>")
                if wanted not in text]
    if "FUN_00000002" in text or "<waves>" in text:
        failures.append("area_page shows a placeholder name or an unescaped text")
    if text.find("0x00000005") > text.find("0x00000004"):
        failures.append("area_page does not list the higher near miss first")
    unsorted = pages.area_page(fake, "https://example.com/r", "unsorted", [6, 7])
    failures += [f"area_page of the unsorted area does not show {wanted!r}"
                 for wanted in ("Nothing matches here yet.", "Nothing here is at 90% yet.", "2 more functions to go.")
                 if wanted not in unsorted]
    if "<dt>Emblem</dt>" in unsorted or "Whales" in unsorted:
        failures.append("area_page gives the unsorted area an emblem or another area's text")
    return failures


def check_layout_helpers() -> list[str]:
    """Clipping keeps the part of a polygon on the inner side of a line, a cell ends inset from the halfway line to
    its neighbour, a count names its noun in the plural unless it is 1, and an SVG URL escapes # and double quotes."""
    failures = []
    half = sorted(layout.clip_polygon([(0, 0), (2, 0), (2, 2), (0, 2)], (1, 0), 1))
    if half != [(0, 0), (0, 2), (1.0, 0.0), (1.0, 2.0)]:
        failures.append(f"clip_polygon gives {half}, not the left half of the square")
    cell = layout.voronoi_cell((0, 0), [(0, 0), (4, 0)], 1, 10)
    if max(x for x, _ in cell) != 1:
        failures.append(f"voronoi_cell gives {cell}, which does not end 1 short of x = 2")
    counts = [layout.counted(1, "file"), layout.counted(2, "file"), layout.counted(1234, "file")]
    if counts != ["1 file", "2 files", "1,234 files"]:
        failures.append(f"counted gives {counts}")
    url = layout.svg_url("<svg fill='#fff' id=\"a\"/>")
    if "#" in url or url.count('"') != 2:
        failures.append(f"svg_url gives {url}, which does not escape # and double quotes")
    return failures


def check_web_url() -> list[str]:
    """A remote's web page comes from its https or ssh form, without the .git. Any other form stops."""
    cases = [("https://github.com/o/r.git", "https://github.com/o/r"),
             ("https://github.com/o/r", "https://github.com/o/r"), ("git@github.com:o/r.git", "https://github.com/o/r")]
    failures = [f"web_url({remote!r}) gives {osutil.web_url(remote)!r}, not {wanted!r}"
                for remote, wanted in cases if osutil.web_url(remote) != wanted]
    try:
        osutil.web_url("/srv/repo.git")
        failures.append("web_url gives a link for a local path instead of stopping")
    except SystemExit:
        pass
    return failures


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
    for check in (check_share_color, check_badge, check_near_misses, check_index_page, check_area_page,
                  check_layout_helpers, check_web_url, check_objdiff_measures):
        failures += check()
    return failures
