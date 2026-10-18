"""Scores and totals of a progress summary.

The score of a function, the totals over the game, and what changed between two
summaries. progress.py draws them. check.py and ci.py gate on them.
Standard library only.
"""

from typing import NamedTuple


class Totals(NamedTuple):
    decompiled: int
    matched: int  # functions at 100%
    accuracy: float | None  # average score of the decompiled functions
    game_total: int
    library: int  # runtime library functions identified
    effective: int  # functions below 100% that reccmp calls an effective match


def score(entry: dict) -> float:
    """The share of instructions that match. Stubs count as zero.

    An effective match keeps its own score: reccmp's check for one is loose. It allows
    other registers and instruction orders without checking that the behavior stays the same.
    """
    if entry["stub"]:
        return 0.0
    return entry["accuracy"]


def state(entry: dict) -> str:
    if entry["stub"]:
        return "stub"
    return "100%" if score(entry) == 1.0 else f"{score(entry):.1%}"


def find_regressions(baseline: dict, current: dict) -> list[str]:
    """Every function whose score dropped. A removed annotation scores zero, so a removed stub drops nothing."""
    now = {entry["address"]: entry for entry in current["functions"]}
    problems = []
    for old in baseline["functions"]:
        new = now.get(old["address"])
        if new is None and score(old) > 0:
            problems.append(f"{old['address']} {old['name']}: annotation removed")
        elif new is not None and score(new) < score(old):
            problems.append(f"{old['address']} {old['name']}: {score(old):.2%} -> {score(new):.2%}")
    return problems


def scores_changed(baseline: dict, current: dict) -> bool:
    """True if a function's score moved. A missing function scores zero, like a stub."""
    old = {entry["address"]: score(entry) for entry in baseline["functions"]}
    new = {entry["address"]: score(entry) for entry in current["functions"]}
    return any(old.get(address, 0.0) != new.get(address, 0.0) for address in old.keys() | new.keys())


def describe_changes(baseline: dict, current: dict) -> list[str]:
    """One short line per function that was added, removed or rescored."""
    old = {entry["address"]: entry for entry in baseline["functions"]}
    new = {entry["address"]: entry for entry in current["functions"]}
    changes = []
    for address in sorted(old.keys() | new.keys()):
        before, after = old.get(address), new.get(address)
        if before is None:
            changes.append(f"+{after['name']} {state(after)}")
        elif after is None:
            changes.append(f"-{before['name']}")
        elif state(before) != state(after):
            changes.append(f"{after['name']} {state(before)} -> {state(after)}")
    # Scores first: new stubs are the least interesting news.
    changes.sort(key=lambda line: line.endswith(" stub"))
    return changes


def totals(summary: dict, game: set[int]) -> Totals:
    """Library entries are runtime code we link, not decompile, so they count apart.
    One in a game range, such as a header function that the linker kept in game code, leaves the game total too."""
    ours = [entry for entry in summary["functions"] if not entry["library"]]
    library = {int(entry["address"], 16) for entry in summary["functions"] if entry["library"]}
    implemented = [entry for entry in ours if not entry["stub"]]
    matched = sum(1 for entry in implemented if score(entry) == 1.0)
    effective = sum(1 for entry in implemented if entry["effective"] and score(entry) < 1.0)
    accuracy = sum(score(entry) for entry in implemented) / len(implemented) if implemented else None
    return Totals(len(implemented), matched, accuracy, len(game - library), len(library), effective)


def ratio(part: float, whole: float) -> float:
    """part / whole. An empty whole counts as 1, so 0 of 0 gives 0."""
    return part / max(whole, 1)


def percent(part: int, whole: int) -> str:
    return f"{ratio(part, whole):.2%}"


def accuracy_text(stats: Totals) -> str:
    return f"{stats.accuracy:.2%}" if stats.accuracy is not None else "n/a"


def stats_line(stats: Totals) -> str:
    return (f"{stats.decompiled:,} / {stats.game_total:,} game functions decompiled "
            f"({percent(stats.decompiled, stats.game_total)}) | {stats.matched:,} matched | "
            f"{stats.effective:,} effective | accuracy {accuracy_text(stats)} "
            f"| library functions identified: {stats.library:,}")
