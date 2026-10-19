"""Layout for the SVG drawings: the rectangles of a treemap and lines of wrapped text.

The treemap is the squarified one of Bruls, Huizing and van Wijk (2000): the sizes go largest first, and each strip
along the shorter side takes the next size only while that keeps the strip's worst aspect ratio from growing.
Standard library only.
"""

from typing import NamedTuple

CHAR_WIDTH = 0.6  # a character's width for a font size, a little over the average of a sans-serif font


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


def text_width(text: str, size: float) -> float:
    return len(text) * size * CHAR_WIDTH


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
