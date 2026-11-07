"""Spelling tiers: how the vendor's sample code writes a candidate at one call slot, from the sample corpus (corpus.py).

A key is one way to write a candidate: each term by one of its aliases, joined with | under an optional ~, in the
canonical form of corpus.canonical. A candidate's keys are its default key (each term's first alias) and each key
that the samples write at the slot with exactly one alias per term.

For a key K, each sample tree that reads the slot gives:
1. K's value: K evaluated with the tree's own headers and profile, converted to the tree's slot type. A tree where K
   does not evaluate is left out for K, with the cause, like a tree that the corpus leaves out for the slot.
2. The nodes: the sample files with an ok observation at the slot whose value is K's value.
The nodes of all trees fall into lineages (corpus.lineage). Each lineage weighs 1, split evenly over the distinct
spellings of its observations at K's value. A mixed spelling (names and literals) counts as literal. Then:
- clusters: the number of lineages;
- share: K's weight over the weight of every named spelling (0 when there is none);
- literal: the literal weight over the clusters;
- combo: the lineages that write K.

Tiers, with the thresholds of config.THRESHOLDS:
- A: at least spell_a_clusters clusters, share at least spell_a_share, literal at most spell_a_literal, and for a
  combination of names at least spell_combo combo;
- B: at least spell_b_clusters clusters, share at least spell_b_share and literal at most spell_b_literal. For a
  combination of names, the rule that each name appears named holds by construction: a key with weight is written
  with each of its names;
- C: some lineage writes K, or one manual section of the callee (manual.py) names every name of K;
- none: anything else.
A candidate's spelling is its best key: the best tier, then the most weight, then the default key, then the text. The
hint is the most common way the samples write that key, as written. The weights are exact fractions, so a share at a
threshold meets it.

A coverage site is sampled when some sample tree reads its slot. A site that is not sampled can never get sample
support, so it is not eligible for review by construction (score.py).

Spelling in the game's own source is not evidence. Standard library only.
"""

from collections import Counter
from dataclasses import dataclass
from fractions import Fraction

import corpus

A, B, C, NONE = "A", "B", "C", "none"
ORDER = (A, B, C, NONE)
DIGITS = 3  # decimals of the shares in the outputs


@dataclass(frozen=True)
class Spelling:
    tier: str
    key: str = ""
    hint: str = ""  # the most common way the samples write the key; "" when no sample writes it
    clusters: int = 0
    weight: Fraction = Fraction(0)  # the key's weight
    share: Fraction = Fraction(0)
    literal: Fraction = Fraction(0)
    combo: int = 0
    manual: bool = False  # the manual section of the callee names every name of the key
    left_out: tuple = ()  # (tree, reason) for each tree that gives no evidence for the key

    @property
    def text(self) -> str:
        """The evidence in one line, for the ledger and the outputs."""
        if self.tier == NONE and not self.clusters:
            return "no sample passes the value"
        parts = [f"{self.clusters} clusters", f"share {float(self.share):.{DIGITS}f}",
                 f"literal {float(self.literal):.{DIGITS}f}", f"combo {self.combo}"]
        if self.manual:
            parts.append("named in the manual")
        if self.hint and self.hint != self.key:
            parts.append(f"written {self.hint}")
        return f"{self.key}: " + ", ".join(parts)


NO_SPELLING = Spelling(NONE)


def top_of(spellings: tuple) -> Spelling:
    """The top candidate's spelling: the first, else NO_SPELLING."""
    return spellings[0] if spellings else NO_SPELLING


class Speller:
    """The spellings of the candidates at the call slots, cached per slot and candidate."""

    def __init__(self, samples: corpus.Corpus, manual: dict, thresholds: dict):
        """MANUAL: callee -> the names of each of its manual sections (manual.by_function). THRESHOLDS: the
        threshold table."""
        self.samples, self.manual = samples, manual
        self.limits = {name: Fraction(str(value)) for name, value in thresholds.items() if name.startswith("spell_")}
        self._cache = {}

    def reads(self, callee: str, slot: int) -> bool:
        """Some sample tree reads slot SLOT of CALLEE."""
        return any((callee, slot) in tree.slots for tree in self.samples.trees.values())

    def spell(self, callee: str, slot: int, candidate) -> Spelling:
        """The spelling of CANDIDATE (covers.Candidate) at slot SLOT of CALLEE."""
        cache_key = (callee, slot, candidate)
        if cache_key not in self._cache:
            observations = self.samples.at(callee, slot)
            keys = candidate_keys(candidate, observations)
            found = [self._spell_key(callee, slot, names, candidate.inverted, observations) for names in keys]
            default = found[0].key
            self._cache[cache_key] = min(found, key=lambda item: (ORDER.index(item.tier), -item.weight,
                                                                  item.key != default, item.key))
        return self._cache[cache_key]

    def _spell_key(self, callee: str, slot: int, names: tuple, inverted: bool, observations: list) -> Spelling:
        key = corpus.canonical(names, inverted)
        values, left_out = {}, []
        for name, tree in self.samples.trees.items():
            if (callee, slot) in tree.left_out:
                left_out.append((name, tree.left_out[callee, slot]))
            elif (callee, slot) in tree.slots:
                result = tree.evaluate(key, (callee, slot))
                if result.ok:
                    values[name] = result.value
                else:
                    left_out.append((name, f"does not evaluate: {result.cause}"))
        counted = [item for item in observations
                   if item.result.ok and item.tree in values and item.value == values[item.tree]]
        lineages = self.samples.lineage({item.node for item in counted})
        lineage_of = {node: index for index, cluster in enumerate(lineages) for node in cluster}
        spellings = {}
        for item in counted:
            spellings.setdefault(lineage_of[item.node], set()).add((item.key, item.kind == corpus.NAMED))
        weight = named = literal = Fraction(0)
        combo = 0
        for found in spellings.values():
            part = Fraction(1, len(found))
            for text, is_named in found:
                if not is_named:
                    literal += part
                    continue
                named += part
                if text == key:
                    weight += part
            combo += (key, True) in found
        clusters = len(lineages)
        share = weight / named if named else Fraction(0)
        literal_share = literal / clusters if clusters else Fraction(0)
        manual = any(set(names) <= section for section in self.manual.get(callee, ()))
        written = Counter(item.argument for item in counted if item.key == key and item.kind == corpus.NAMED)
        hint = min(written, key=lambda text: (-written[text], text)) if written else ""
        tier = self._tier(clusters, share, literal_share, combo, len(names) >= 2, weight > 0 or manual)
        return Spelling(tier, key, hint, clusters, weight, share, literal_share, combo, manual, tuple(left_out))

    def _tier(self, clusters: int, share: Fraction, literal: Fraction, combo: int, combination: bool,
              any_support: bool) -> str:
        limits = self.limits
        if (clusters >= limits["spell_a_clusters"] and share >= limits["spell_a_share"]
                and literal <= limits["spell_a_literal"] and (not combination or combo >= limits["spell_combo"])):
            return A
        if (clusters >= limits["spell_b_clusters"] and share >= limits["spell_b_share"]
                and literal <= limits["spell_b_literal"]):
            return B
        return C if any_support else NONE


def candidate_keys(candidate, observations: list) -> list[tuple]:
    """The sorted names of each key of CANDIDATE: the default key first, then each key that OBSERVATIONS write with
    one alias per term and the candidate's ~, in text order."""
    term_of = {alias.name: index for index, node in enumerate(candidate.terms) for alias in node.aliases}
    every_term = list(range(len(candidate.terms)))
    default = tuple(sorted(node.name for node in candidate.terms))
    keys = set()
    for observation in observations:
        names = observation.names
        if not names or observation.inverted != candidate.inverted:
            continue
        terms = [term_of.get(name) for name in names]
        if None not in terms and sorted(terms) == every_term:
            keys.add(names)
    return [default] + sorted(keys - {default})


def assign(records: list, speller: Speller):
    """Into each coverage record: record.sampled, and record.spellings, one per candidate in rank order."""
    for record in records:
        if not record.covered:
            continue
        record.sampled = speller.reads(record.callee, record.row.slot)
        if record.search is not None:
            record.spellings = tuple(speller.spell(record.callee, record.row.slot, candidate)
                                     for candidate in record.search.candidates)
