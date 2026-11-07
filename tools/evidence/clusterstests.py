"""Unit tests for clusters.py.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/clusterstests.py
run() calls every check and returns the failures.
"""

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import clusters  # noqa: E402


def check_shingles() -> list[str]:
    failures = []
    if len(clusters.shingles(list("abcdef"), 3)) != 4:
        failures.append("six texts give four shingles of three")
    if clusters.shingles(list("abab"), 2) != clusters.shingles(list("aba"), 2):
        failures.append("a repeated shingle counts once")
    if len(clusters.shingles(["a"], 3)) != 1 or clusters.shingles([], 3):
        failures.append("a short text gives one shingle, no text none")
    return failures


def check_jaccard() -> list[str]:
    failures = []
    if clusters.jaccard(frozenset({1, 2, 3}), frozenset({2, 3, 4})) != 0.5:
        failures.append("jaccard of {1,2,3} and {2,3,4}")
    if clusters.jaccard(frozenset(), frozenset()) != 1.0 or clusters.jaccard(frozenset({1}), frozenset()) != 0.0:
        failures.append("jaccard with empty sets")
    return failures


def table(pairs: dict):
    """A similarity function over the pairs in PAIRS; other pairs are 0."""
    return lambda first, second: pairs.get((first, second), pairs.get((second, first), 0.0))


def check_complete_linkage() -> list[str]:
    """A is like B and B is like C, but A is not like C: complete linkage keeps C apart, though single linkage
    would chain all three."""
    failures = []
    chain = table({("a", "b"): 0.6, ("b", "c"): 0.6, ("a", "c"): 0.2})
    got = clusters.complete_linkage(["a", "b", "c"], chain, 0.5)
    if got != [["a", "b"], ["c"]]:
        failures.append(f"the chain: got {got}")
    closer = table({("a", "b"): 0.6, ("b", "c"): 0.9, ("a", "c"): 0.2})
    if clusters.complete_linkage(["a", "b", "c"], closer, 0.5) != [["a"], ["b", "c"]]:
        failures.append("the most similar pair merges first")
    at_cut = table({("a", "b"): 0.5})
    if clusters.complete_linkage(["b", "x", "a"], at_cut, 0.5) != [["b", "a"], ["x"]]:
        failures.append("a pair at the cut merges, and clusters keep the item order")
    tight = table({(first, second): 0.8 for first in "abcd" for second in "abcd" if first < second})
    if clusters.complete_linkage(list("dcba"), tight, 0.5) != [list("dcba")]:
        failures.append("four alike items are one cluster")
    if clusters.complete_linkage([], tight, 0.5) != []:
        failures.append("no items, no clusters")
    return failures


def check_histogram() -> list[str]:
    got = clusters.histogram([0.0, 0.09, 0.1, 0.55, 0.99, 1.0], 10)
    if got != [2, 1, 0, 0, 0, 1, 0, 0, 0, 2]:
        return [f"histogram: got {got}"]
    return []


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_shingles, check_jaccard, check_complete_linkage, check_histogram):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    print("\n".join(found) or "clusterstests: all passed")
    sys.exit(1 if found else 0)
