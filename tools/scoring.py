"""Scores and totals of a progress summary.

The score of a function, the totals over the game, and what changed between two
summaries. progress.py draws them. check.py and ci.py gate on them.
Standard library only.
"""

from typing import NamedTuple


class Totals(NamedTuple):
    decompiled: int
    matched: int  # functions at 100% in plain C
    accuracy: float | None  # average score of the decompiled functions
    game_total: int
    library: int  # runtime library functions identified
    effective: int  # functions below 100% that reccmp calls an effective match
    tricks: int  # functions at 100% only through a trick (tools/tricks.py), which do not count as matched


def score(entry: dict) -> float:
    """The share of instructions that match. Stubs count as zero.

    An effective match keeps its own score: reccmp's check for one is loose. It allows
    other registers and instruction orders without checking that the behavior stays the same.
    """
    if entry["stub"]:
        return 0.0
    return entry["accuracy"]


def is_trick(entry: dict) -> bool:
    """At 100% only through a trick. Only a function with a trick has the "trick" key, so older summaries read the
    same. Below 100% a trick does not change how the function counts."""
    return score(entry) == 1.0 and bool(entry.get("trick"))


def is_matched(entry: dict) -> bool:
    """At 100% in plain C. A function with a trick keeps its score, but it does not count as matched."""
    return score(entry) == 1.0 and not is_trick(entry)


def state(entry: dict) -> str:
    if entry["stub"]:
        return "stub"
    if score(entry) < 1.0:
        return f"{score(entry):.1%}"
    return "100%" if is_matched(entry) else "100%, through a trick"


def state_text(entry: dict | None) -> str:
    """The state of a function, or "none" for one with no entry."""
    return "none" if entry is None else state(entry)


def find_regressions(baseline: dict, current: dict, accepted: set[tuple[str, str, str]] = frozenset()) -> list[str]:
    """Every function whose score dropped, and every global that matched and no longer does. A removed annotation
    scores zero, so a removed stub drops nothing. A summary from before data scoring has no data list. ACCEPTED holds
    the drops that count as none: (address, old score, new score), the scores as this function prints them."""
    now = {entry["address"]: entry for entry in current["functions"]}
    problems = []
    for old in baseline["functions"]:
        new = now.get(old["address"])
        if new is None and score(old) > 0:
            problems.append(f"{old['address']} {old['name']}: annotation removed")
        elif (new is not None and score(new) < score(old)
              and (old["address"], f"{score(old):.2%}", f"{score(new):.2%}") not in accepted):
            problems.append(f"{old['address']} {old['name']}: {score(old):.2%} -> {score(new):.2%}")
    data_now = {entry["address"]: entry for entry in current.get("data", [])}
    for old in baseline.get("data", []):
        new = data_now.get(old["address"])
        if old["match"] and not (new and new["match"]):
            problems.append(f"{old['address']} {old['name']}: data matched -> {'gone' if new is None else 'differs'}")
    return problems


def moved_scores(baseline: dict, current: dict) -> list[int]:
    """The addresses of the functions whose score moved, in order. A missing function scores zero, like a stub."""
    old = {int(entry["address"], 16): score(entry) for entry in baseline["functions"]}
    new = {int(entry["address"], 16): score(entry) for entry in current["functions"]}
    return sorted(address for address in old.keys() | new.keys() if old.get(address, 0.0) != new.get(address, 0.0))


def library_addresses(summary: dict) -> set[int]:
    return {int(entry["address"], 16) for entry in summary["functions"] if entry["library"]}


def game_functions(summary: dict, game: set[int]) -> set[int]:
    """The game addresses that are not library entries. A library entry in a game range, such as a header function
    that the linker kept in game code, is not a game function."""
    return game - library_addresses(summary)


def entries_by_address(summary: dict) -> dict[int, dict]:
    return {int(entry["address"], 16): entry for entry in summary["functions"]}


def totals(summary: dict, game: set[int]) -> Totals:
    """Library entries are runtime code we link, not decompile, so they count apart."""
    ours = [entry for entry in summary["functions"] if not entry["library"]]
    library = library_addresses(summary)
    implemented = [entry for entry in ours if not entry["stub"]]
    matched = sum(1 for entry in implemented if is_matched(entry))
    tricks = sum(1 for entry in implemented if is_trick(entry))
    effective = sum(1 for entry in implemented if entry["effective"] and score(entry) < 1.0)
    accuracy = sum(score(entry) for entry in implemented) / len(implemented) if implemented else None
    return Totals(len(implemented), matched, accuracy, len(game_functions(summary, game)), len(library), effective,
                  tricks)


class Bytes(NamedTuple):
    """Code bytes of game functions, from each function's size."""
    decompiled: int  # functions with a body: stubs do not count
    matched: int  # functions at 100% in plain C
    game: int  # all game functions


def code_bytes(summary: dict, game: set[int], sizes: dict[int, int]) -> Bytes:
    """The code bytes of the game functions in GAME, from each function's size in SIZES. A library entry counts in
    none of them."""
    entries = entries_by_address(summary)
    functions = game_functions(summary, game)
    scored = {address: entries[address] for address in functions if address in entries}
    decompiled = sum(sizes[address] for address, entry in scored.items() if not entry["stub"])
    matched = sum(sizes[address] for address, entry in scored.items() if is_matched(entry))
    return Bytes(decompiled, matched, sum(sizes[address] for address in functions))


class Emblem(NamedTuple):
    """A goal in code bytes. It is earned once the matched bytes reach the needed ones."""
    name: str
    matched: int
    needed: int

    @property
    def earned(self) -> bool:
        return self.matched >= self.needed


def emblems(areas: list[tuple[str, Bytes]]) -> list[Emblem]:
    """One emblem for each (name, code bytes) area, for all of its code. They come from the current summary only, so
    they carry no date."""
    return [Emblem(name, area.matched, area.game) for name, area in areas]


def earned_count(found: list[Emblem]) -> int:
    return sum(1 for emblem in found if emblem.earned)


def data_share(summary: dict) -> tuple[int, int]:
    """(bytes of the matching game globals, bytes of the original's initialized data). Runtime library globals count
    in neither part, as library functions don't count in the code share. The whole holds middleware data, strings and
    floats too. A summary from before data scoring has neither."""
    data = summary.get("data", [])
    matched = sum(entry["size"] for entry in data if entry["match"] and not entry["library"])
    library = sum(entry["size"] for entry in data if entry["library"])
    return matched, summary.get("data_bytes", 0) - library


def ratio(part: float, whole: float) -> float:
    """part / whole. An empty whole counts as 1, so 0 of 0 gives 0."""
    return part / max(whole, 1)


def percent(part: int, whole: int) -> str:
    """The percent rounded down to two decimals, so only a whole that is all done shows 100.00%. Integers, as in
    whole_percent."""
    hundredths = 10000 * part // max(whole, 1)
    return f"{hundredths // 100}.{hundredths % 100:02d}%"


def count_text(part: int, whole: int, unit: str) -> str:
    return f"{part:,} of {whole:,} {unit} ({percent(part, whole)})"


def whole_percent(part: int, whole: int) -> str:
    """The percent rounded down, so only a whole that is all done shows 100%. Integers, so no float error rounds it
    down a step."""
    return f"{100 * part // max(whole, 1)}%"


def accuracy_text(stats: Totals) -> str:
    return f"{stats.accuracy:.2%}" if stats.accuracy is not None else "n/a"


def stats_line(stats: Totals) -> str:
    return (f"{stats.decompiled:,} / {stats.game_total:,} game functions decompiled "
            f"({percent(stats.decompiled, stats.game_total)}) | {stats.matched:,} matched | "
            f"{stats.tricks:,} at 100% only through a trick | "
            f"{stats.effective:,} effective | accuracy {accuracy_text(stats)} "
            f"| library functions identified: {stats.library:,}")
