"""Layout for the drawings and pages: the rectangles of a treemap, lines of wrapped text, counted nouns and rounded
polygon cells.

The treemap is the squarified one of Bruls, Huizing and van Wijk (2000): the sizes go largest first, and each strip
along the shorter side takes the next size only while that keeps the strip's worst aspect ratio from growing.
Standard library only.
"""

import html
import math
import urllib.parse
from typing import NamedTuple

CHAR_WIDTH = 0.6  # a character's width for a font size, a little over the average of a sans-serif font

Point = tuple[float, float]


class Rect(NamedTuple):
    x: float
    y: float
    width: float
    height: float


def worst_ratio(areas: list[float], side: float) -> float:
    """The worst aspect ratio of a strip of areas laid along a side."""
    total = sum(areas)
    return max(max(side * side * area / (total * total), total * total / (side * side * area)) for area in areas)


def strip_end(areas: list[float], start: int, side: float) -> int:
    """The end of the strip that starts at areas[start] along a side."""
    end = start + 1
    while end < len(areas) and worst_ratio(areas[start:end + 1], side) <= worst_ratio(areas[start:end], side):
        end += 1
    return end


def squarify(sizes: list[float], bounds: Rect) -> list[Rect]:
    """One rectangle for each size, in the order given, that together fill the bounds. Sizes must be positive."""
    if not sizes:
        return []
    order = sorted(range(len(sizes)), key=lambda index: -sizes[index])
    scale = bounds.width * bounds.height / sum(sizes)
    areas = [sizes[index] * scale for index in order]
    rects = [bounds] * len(sizes)
    x, y, width, height = bounds
    start = 0
    while start < len(areas):
        end = strip_end(areas, start, min(width, height))
        column = width >= height
        thickness = sum(areas[start:end]) / (height if column else width)
        offset = 0.0
        for index, area in zip(order[start:end], areas[start:end]):
            length = area / thickness
            rects[index] = Rect(x, y + offset, thickness, length) if column else Rect(x + offset, y, length, thickness)
            offset += length
        if column:
            x, width = x + thickness, width - thickness
        else:
            y, height = y + thickness, height - thickness
        start = end
    return rects


def snap(rect: Rect) -> Rect:
    """The rectangle with its edges on whole pixels. Rectangles that share an edge still share it."""
    left, top = round(rect.x), round(rect.y)
    return Rect(left, top, round(rect.x + rect.width) - left, round(rect.y + rect.height) - top)


def svg_points(corners: list[tuple[float, float]]) -> str:
    """The corners as the points attribute of an SVG polygon."""
    return " ".join(f"{x:g},{y:g}" for x, y in corners)


def star_points(x: float, y: float, outer: float, inner: float) -> list[tuple[float, float]]:
    """The 10 corners of a five-pointed star centred on (x, y), its top point up, rounded to 0.01 px."""
    corners = []
    for index in range(10):
        radius = outer if index % 2 == 0 else inner
        angle = index * math.pi / 5
        corners.append((round(x + radius * math.sin(angle), 2), round(y - radius * math.cos(angle), 2)))
    return corners


def text_width(text: str, size: float) -> float:
    return len(text) * size * CHAR_WIDTH


def counted(count: int, noun: str) -> str:
    """The count with its noun, the noun plural with an s unless the count is 1."""
    return f"{count:,} {noun}" + ("" if count == 1 else "s")


def wrap(words: list[str], width: float, size: float) -> list[list[str]] | None:
    """The words in lines no wider than width, as many on each line as fit. None if one word alone is wider."""
    lines = []
    for word in words:
        if text_width(word, size) > width:
            return None
        if lines and text_width(" ".join(lines[-1] + [word]), size) <= width:
            lines[-1].append(word)
        else:
            lines.append([word])
    return lines


def clip_polygon(polygon: list[Point], normal: Point, limit: float) -> list[Point]:
    """The part of a convex polygon where point . normal <= limit: one step of Sutherland-Hodgman."""
    kept = []
    for index, current in enumerate(polygon):
        previous = polygon[index - 1]
        before = previous[0] * normal[0] + previous[1] * normal[1] - limit
        now = current[0] * normal[0] + current[1] * normal[1] - limit
        if (before <= 0) != (now <= 0):
            share = before / (before - now)
            kept.append((previous[0] + share * (current[0] - previous[0]),
                         previous[1] + share * (current[1] - previous[1])))
        if now <= 0:
            kept.append(current)
    return kept


def voronoi_cell(site: Point, others: list[Point], inset: float, reach: float) -> list[Point]:
    """The points nearer the site than any of the others, pulled in by inset from each edge, within reach of the site
    on each axis. Others may hold the site itself."""
    x, y = site
    cell = [(x - reach, y - reach), (x + reach, y - reach), (x + reach, y + reach), (x - reach, y + reach)]
    for other in others:
        if other == site:
            continue
        dx, dy = other[0] - x, other[1] - y
        length = math.hypot(dx, dy)
        normal = (dx / length, dy / length)
        middle = ((x + other[0]) / 2, (y + other[1]) / 2)
        cell = clip_polygon(cell, normal, middle[0] * normal[0] + middle[1] * normal[1] - inset)
    return cell


def rounded_path(corners: list[Point]) -> str:
    """An SVG path through the midpoints of a polygon's edges, each corner the control point of the curve past it."""
    middles = [((corners[index - 1][0] + x) / 2, (corners[index - 1][1] + y) / 2)
               for index, (x, y) in enumerate(corners)]
    parts = [f"M{middles[0][0]:.1f} {middles[0][1]:.1f}"]
    for index, (x, y) in enumerate(corners):
        end = middles[(index + 1) % len(corners)]
        parts.append(f"Q{x:.1f} {y:.1f} {end[0]:.1f} {end[1]:.1f}")
    return "".join(parts) + "Z"


def svg_url(svg: str) -> str:
    """An SVG as a CSS url() of a data URI, its whitespace runs cut to one space."""
    return 'url("data:image/svg+xml,' + urllib.parse.quote(" ".join(svg.split()), safe=" =:/'") + '")'


def link_attributes(url: str) -> str:
    """The attributes of an HTML link to URL. A link to another site opens in a new tab, so the page stays open."""
    attributes = f'href="{html.escape(url)}"'
    if urllib.parse.urlsplit(url).scheme:
        attributes += ' target="_blank" rel="noopener"'
    return attributes
