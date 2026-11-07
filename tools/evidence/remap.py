"""Site identity across runs: which new site keeps which old id.

A site's identity is its owner plus its payload: kind, target, slot path and normalized expression. Its value, its
ordinal and its location are not identity. Per owner, a scored global alignment (Needleman-Wunsch) pairs the old list
of the last run with the new one, in order. Three kinds of pair exist:

1. exact: the same payload;
2. rewrite: the same kind, target and slot, another expression, the same value. The old value is re-evaluated under
   the current rules; when the old expression no longer evaluates, its stored value counts;
3. target: the same kind, slot and expression, another target, each unique in its owner's list.

A pairing is kept only when every optimal alignment of the owner makes it: the alignment counts the optimal paths
forward and backward, and a pair is shared when the paths through it equal all optimal paths. An old site on an
optimal pair that is not shared becomes "ambiguous", and its new partners get fresh ids. An old site on no optimal
pair is "gone". A second pass then pairs a gone row and a fresh row with the same kind, slot path and value whose
target and expression both changed, when each is the only unpaired row of its owner with that kind, slot and value
(kind "target and rewrite"). The context key only ranks the suggestions for ambiguous rows; it never assigns an id.

The invariant: an edit at one site never moves another site's id. Where the alignment cannot tell which of several
identical sites changed, those sites become ambiguous instead.

Standard library only.
"""

from collections import Counter
from dataclasses import dataclass, field

ID_PREFIX, ID_DIGITS = "S", 6
EXACT, REWRITE, TARGET, TARGET_AND_REWRITE = "exact", "rewrite", "target", "target and rewrite"


@dataclass(frozen=True)
class Scores:
    """Alignment scores. Exact beats two weaker pairs, so swapping two sites keeps one id at most."""
    exact: int = 10
    rewrite: int = 3
    target: int = 3


@dataclass(frozen=True)
class Site:
    owner: str
    kind: str
    target: str
    slot: str
    expression: str
    value: str = ""  # the converted value as text, "" when it has none
    context: str = ""  # the hash of this statement and the one before: suggestions only
    id: str = ""
    file: str = ""  # location, display only
    line: int = 0
    column: int = 0

    @property
    def payload(self) -> tuple:
        return self.kind, self.target, self.slot, self.expression


@dataclass
class Remap:
    ids: list  # per new site, in input order: the old id it keeps, or "" for a fresh id
    kinds: list  # per new site: the pair kind, or ""
    gone: list = field(default_factory=list)  # old ids on no optimal pair
    ambiguous: list = field(default_factory=list)  # old ids on a disputed pair
    suggestions: list = field(default_factory=list)  # (old id, new index) for ambiguous rows, same context first


@dataclass
class Alignment:
    shared: dict  # old index -> new index, for the pairs every optimal alignment makes
    disputed_old: set  # old indices on an optimal pair that is not shared
    disputed_new: set
    candidates: list  # (old index, new index) of every optimal pair that is not shared
    count: int  # the number of optimal paths


def format_id(number: int) -> str:
    return f"{ID_PREFIX}{number:0{ID_DIGITS}d}"


def id_number(text: str) -> int:
    if not (text.startswith(ID_PREFIX) and text[len(ID_PREFIX):].isdigit()):
        raise ValueError(f"not a site id: {text!r}")
    return int(text[len(ID_PREFIX):])


def mint(count: int, high_water: int) -> tuple[list[str], int]:
    """COUNT fresh ids above HIGH_WATER, and the new high-water mark."""
    return [format_id(high_water + offset) for offset in range(1, count + 1)], high_water + count


def align(old: list, new: list, score) -> Alignment:
    """The shared and disputed pairs of OLD against NEW. SCORE(i, j) gives a pair's score, or None when the two
    cannot pair. Gaps score 0."""
    rows, columns = len(old), len(new)
    pairs = [[score(i, j) for j in range(columns)] for i in range(rows)]
    forward = [[0] * (columns + 1) for _ in range(rows + 1)]  # the best score from the start to (i, j)
    ways = [[0] * (columns + 1) for _ in range(rows + 1)]  # the optimal paths from the start to (i, j)
    for i in range(rows + 1):
        for j in range(columns + 1):
            if i == 0 or j == 0:
                ways[i][j] = 1
                continue
            steps = [(forward[i - 1][j], ways[i - 1][j]), (forward[i][j - 1], ways[i][j - 1])]
            if pairs[i - 1][j - 1] is not None:
                steps.append((forward[i - 1][j - 1] + pairs[i - 1][j - 1], ways[i - 1][j - 1]))
            best = max(value for value, _ in steps)
            forward[i][j] = best
            ways[i][j] = sum(count for value, count in steps if value == best)
    backward = [[0] * (columns + 1) for _ in range(rows + 1)]  # the best score from (i, j) to the end
    back_ways = [[0] * (columns + 1) for _ in range(rows + 1)]
    for i in range(rows, -1, -1):
        for j in range(columns, -1, -1):
            if i == rows or j == columns:
                back_ways[i][j] = 1
                continue
            steps = [(backward[i + 1][j], back_ways[i + 1][j]), (backward[i][j + 1], back_ways[i][j + 1])]
            if pairs[i][j] is not None:
                steps.append((backward[i + 1][j + 1] + pairs[i][j], back_ways[i + 1][j + 1]))
            best = max(value for value, _ in steps)
            backward[i][j] = best
            back_ways[i][j] = sum(count for value, count in steps if value == best)
    total, count = forward[rows][columns], ways[rows][columns]
    found = Alignment({}, set(), set(), [], count)
    for i in range(rows):
        for j in range(columns):
            if pairs[i][j] is None or forward[i][j] + pairs[i][j] + backward[i + 1][j + 1] != total:
                continue
            if ways[i][j] * back_ways[i + 1][j + 1] == count:
                found.shared[i] = j
            else:
                found.disputed_old.add(i)
                found.disputed_new.add(j)
                found.candidates.append((i, j))
    return found


def _pair_kind(old: Site, old_value: str, new: Site, unique_old: Counter, unique_new: Counter) -> str | None:
    if old.kind != new.kind or old.slot != new.slot:
        return None
    if old.payload == new.payload:
        return EXACT
    if old.target == new.target:
        return REWRITE if old_value and old_value == new.value else None
    if old.expression == new.expression:
        key = (old.kind, old.slot, old.expression)
        return TARGET if unique_old[key] == 1 and unique_new[key] == 1 else None
    return None


def _remap_owner(old: list, new: list, revalue, scores: Scores, result: Remap, indices: list) -> None:
    """Remap one owner's sites. INDICES gives the place of each of NEW in the whole new list."""
    values = [revalue(site) or site.value for site in old]
    unique_old = Counter((site.kind, site.slot, site.expression) for site in old)
    unique_new = Counter((site.kind, site.slot, site.expression) for site in new)
    kinds = {}

    def score(i, j):
        kind = _pair_kind(old[i], values[i], new[j], unique_old, unique_new)
        kinds[i, j] = kind
        return None if kind is None else getattr(scores, kind)

    found = align(old, new, score)
    for i, j in found.shared.items():
        result.ids[indices[j]], result.kinds[indices[j]] = old[i].id, kinds[i, j]
    paired_old = set(found.shared) | found.disputed_old
    gone = [i for i in range(len(old)) if i not in paired_old]
    fresh = [j for j in range(len(new)) if j not in found.shared.values()]
    # Second pass: a gone row and a fresh row whose target and expression both changed.
    unpaired_old = Counter((old[i].kind, old[i].slot, values[i]) for i in range(len(old)) if i not in found.shared)
    unpaired_new = Counter((new[j].kind, new[j].slot, new[j].value) for j in fresh)
    for i in list(gone):
        key = (old[i].kind, old[i].slot, values[i])
        if not values[i] or unpaired_old[key] != 1 or unpaired_new[key] != 1:
            continue
        j = next(j for j in fresh if (new[j].kind, new[j].slot, new[j].value) == key)
        if j in found.disputed_new or old[i].target == new[j].target or old[i].expression == new[j].expression:
            continue
        result.ids[indices[j]], result.kinds[indices[j]] = old[i].id, TARGET_AND_REWRITE
        gone.remove(i)
    result.gone += [old[i].id for i in gone]
    result.ambiguous += [old[i].id for i in sorted(found.disputed_old)]
    ranked = sorted(found.candidates, key=lambda pair: (old[pair[0]].context != new[pair[1]].context, pair))
    result.suggestions += [(old[i].id, indices[j]) for i, j in ranked]


def remap(old: list, new: list, revalue=lambda site: "", scores: Scores = Scores()) -> Remap:
    """Pair NEW against OLD, owner by owner. OLD holds the last run's sites with their ids, NEW this run's sites, each
    in owner order. REVALUE(site) gives an old site's value under the current rules, or "" when it no longer
    evaluates."""
    result = Remap([""] * len(new), [""] * len(new))
    old_by_owner, new_by_owner = {}, {}
    for site in old:
        old_by_owner.setdefault(site.owner, []).append(site)
    for index, site in enumerate(new):
        new_by_owner.setdefault(site.owner, []).append(index)
    for owner, indices in new_by_owner.items():
        _remap_owner(old_by_owner.pop(owner, []), [new[index] for index in indices], revalue, scores, result, indices)
    for sites in old_by_owner.values():
        result.gone += [site.id for site in sites]
    return result
