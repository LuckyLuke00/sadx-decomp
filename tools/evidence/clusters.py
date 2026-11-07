"""Clustering helpers: token shingles, the Jaccard index, complete-linkage clustering at a cut, and histograms.

complete_linkage() first splits the items into the connected parts of the graph whose edges are the pairs with a
similarity of at least the cut. No cluster can span two parts, because each cross pair is below the cut. It then
merges inside each part.

Standard library only.
"""


def shingles(texts: list, size: int) -> frozenset:
    """The hashes of each run of SIZE texts. Fewer than SIZE texts give one shingle; none give the empty set. The hash
    is Python's own, so the values change from run to run and only their overlap means something."""
    if len(texts) < size:
        return frozenset({hash(tuple(texts))}) if texts else frozenset()
    return frozenset(hash(tuple(texts[index:index + size])) for index in range(len(texts) - size + 1))


def jaccard(first: frozenset, second: frozenset) -> float:
    """The shared share of the union; 1 for two empty sets."""
    if not first and not second:
        return 1.0
    shared = len(first & second)
    return shared / (len(first) + len(second) - shared)


def complete_linkage(items: list, similarity, cut: float) -> list[list]:
    """ITEMS clustered with complete linkage: the two clusters whose least similar cross pair is the most similar
    merge, while that pair's SIMILARITY(a, b) is at least CUT. A tie goes to the clusters that come first. Each
    cluster keeps the order of ITEMS, and the clusters come in the order of their first item."""
    order = {item: index for index, item in enumerate(items)}
    found = []
    for part in _parts(items, similarity, cut):
        found += _merged(part, similarity, cut)
    found = [sorted(cluster, key=order.get) for cluster in found]
    return sorted(found, key=lambda cluster: order[cluster[0]])


def _parts(items: list, similarity, cut: float) -> list[list]:
    parent = list(range(len(items)))

    def root(index: int) -> int:
        while parent[index] != index:
            parent[index] = parent[parent[index]]
            index = parent[index]
        return index

    for first in range(len(items)):
        for second in range(first + 1, len(items)):
            if similarity(items[first], items[second]) >= cut:
                low, high = sorted((root(first), root(second)))
                parent[high] = low
    parts = {}
    for index, item in enumerate(items):
        parts.setdefault(root(index), []).append(item)
    return list(parts.values())


def _merged(items: list, similarity, cut: float) -> list[list]:
    clusters = [[item] for item in items]
    link = {(first, second): similarity(items[first], items[second])
            for first in range(len(items)) for second in range(first + 1, len(items))}
    alive = list(range(len(items)))
    while True:
        best = None
        for position, first in enumerate(alive):
            for second in alive[position + 1:]:
                value = link[first, second]
                if value >= cut and (best is None or value > best[0]):
                    best = (value, first, second)
        if best is None:
            return [clusters[index] for index in alive]
        _, kept, gone = best
        clusters[kept] += clusters[gone]
        alive.remove(gone)
        for other in alive:
            if other != kept:
                pair = (min(kept, other), max(kept, other))
                link[pair] = min(link[pair], link[min(gone, other), max(gone, other)])


def histogram(values, bins: int) -> list[int]:
    """The counts of VALUES (from 0 to 1) in BINS equal bins; 1 counts in the last bin."""
    counts = [0] * bins
    for value in values:
        counts[min(int(value * bins), bins - 1)] += 1
    return counts
