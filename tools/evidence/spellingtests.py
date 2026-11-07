"""Unit tests for spelling.py, on a corpus built in memory: stub sample trees with fixed name values, and one
lineage per relative path.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/spellingtests.py
run() calls every check and returns the failures. All names are made up.
"""

import sys
from fractions import Fraction
from pathlib import Path
from types import SimpleNamespace

sys.path.insert(0, str(Path(__file__).parent))

import ceval  # noqa: E402
import config  # noqa: E402
import corpus  # noqa: E402
import covers  # noqa: E402
import ctokens  # noqa: E402
import profiles  # noqa: E402
import spelling  # noqa: E402

CALLEE, SLOT = "xxCall", 1
PROFILE = profiles.PROFILES["shc-c"]
TERMS = {"XX_A": 1, "XX_AA": 1, "XX_F1": 16, "XX_F2": 32}
VALUES = {**TERMS, "XX_F1 | XX_F2": 48}


class StubTree:
    """A sample tree whose keys have fixed values. LEFT_OUT: the reason the corpus leaves the slot out, if any."""

    def __init__(self, values: dict, left_out: str = ""):
        self.values = values
        self.slots = {} if left_out else {(CALLEE, SLOT): None}
        self.left_out = {(CALLEE, SLOT): left_out} if left_out else {}

    def evaluate(self, source: str, key: tuple) -> ceval.Result:
        if source in self.values:
            return ceval.Result(ceval.OK, self.values[source])
        return ceval.failure(ceval.UNRESOLVED, "unknown identifier", source)


def seen(tree: str, path: str, argument: str, value: int) -> corpus.Observation:
    """An ok observation in file PATH of TREE, with the spelling key and class of ARGUMENT."""
    tokens = ctokens.tokens_of(argument)
    key, names, inverted = corpus.spelling_key(tokens, PROFILE)
    result = ceval.Result(ceval.OK, value, names=tuple(token.text for token in tokens if token.kind == "id"),
                          literal=any(token.kind == "num" for token in tokens))
    return corpus.Observation(tree, f"{tree}/{path}", path, 1, CALLEE, SLOT, ctokens.spelling(tokens), result, key,
                              names, inverted, corpus.kind_of(result))


def sample_corpus(rows: list, trees: dict | None = None, **overrides) -> corpus.Corpus:
    """ROWS: (tree, path, argument, value). Each relative path is one lineage."""
    observations = [seen(*row) for row in rows]
    nodes = {item.node: item.file for item in observations}
    thresholds = {**config.THRESHOLDS, **overrides}
    return corpus.Corpus(observations, trees or {"new": StubTree(VALUES)}, thresholds,
                         {node: {path} for node, path in nodes.items()}, {node: frozenset() for node in nodes})


def files(*counts: tuple) -> list:
    """(argument, count, value) entries: COUNT files in the new tree that write ARGUMENT, one lineage each."""
    rows, index = [], 0
    for argument, count, value in counts:
        for _ in range(count):
            index += 1
            rows.append(("new", f"f{index}.c", argument, value))
    return rows


def candidate(*names: str, inverted: bool = False) -> covers.Candidate:
    """One term per name, each with the aliases of TERMS that share its value."""
    terms = []
    for name in names:
        aliases = tuple(covers.Name(other, TERMS[other], False) for other in sorted(TERMS)
                        if TERMS[other] == TERMS[name])
        terms.append(covers.Node(aliases, TERMS[name]))
    return covers.Candidate(tuple(terms), inverted)


def spell(samples: corpus.Corpus, found: covers.Candidate, manual: dict | None = None) -> spelling.Spelling:
    return spelling.Speller(samples, manual or {}, samples.thresholds).spell(CALLEE, SLOT, found)


def check_a_edges() -> list[str]:
    failures = []
    cases = {
        "five lineages": (files(("XX_A", 5, 1)), spelling.A),
        "four lineages": (files(("XX_A", 4, 1)), spelling.B),
        "share at 0.9": (files(("XX_A", 9, 1), ("XX_AA", 1, 1)), spelling.A),
        "share at 0.8": (files(("XX_A", 8, 1), ("XX_AA", 2, 1)), spelling.B),
        "literal at 0.1": (files(("XX_A", 9, 1), ("1", 1, 1)), spelling.A),
        "literal at 0.2": (files(("XX_A", 8, 1), ("1", 2, 1)), spelling.B),
    }
    for label, (rows, tier) in cases.items():
        got = spell(sample_corpus(rows), candidate("XX_A"))
        if (got.tier, got.key) != (tier, "XX_A"):
            failures.append(f"{label}: got {got.tier} {got.key}, wanted {tier}")
    return failures


def check_b_edges() -> list[str]:
    failures = []
    cases = {
        "three lineages": (files(("XX_A", 3, 1)), spelling.B),
        "two lineages": (files(("XX_A", 2, 1)), spelling.C),
        "share at 0.5": (files(("XX_A", 2, 1), ("XX_AA", 2, 1)), spelling.B),
        "literal at 0.3": (files(("XX_A", 7, 1), ("1", 3, 1)), spelling.B),
        "literal at 0.4": (files(("XX_A", 6, 1), ("1", 4, 1)), spelling.C),
        "no sample": ([], spelling.NONE),
    }
    for label, (rows, tier) in cases.items():
        got = spell(sample_corpus(rows), candidate("XX_A"))
        if got.tier != tier:
            failures.append(f"{label}: got {got.tier}, wanted {tier}")
    tie = spell(sample_corpus(files(("XX_AA", 2, 1), ("XX_A", 2, 1))), candidate("XX_A"))
    if tie.key != "XX_A":
        failures.append(f"a tie in tier and weight goes to the default key: got {tie.key}")
    alias = spell(sample_corpus(files(("XX_AA", 4, 1), ("XX_A", 1, 1))), candidate("XX_A"))
    if (alias.tier, alias.key, alias.weight) != (spelling.B, "XX_AA", 4):
        failures.append(f"the alias the samples write wins: got {alias.tier} {alias.key} {alias.weight}")
    return failures


def check_weights() -> list[str]:
    """A lineage weighs 1, split evenly over its distinct spellings; a mixed spelling counts as literal."""
    failures = []
    rows = files(("XX_A", 2, 1)) + [("new", "split.c", "XX_A", 1), ("new", "split.c", "1", 1),
                                    ("new", "split.c", "XX_A", 1)]
    got = spell(sample_corpus(rows), candidate("XX_A"))
    if (got.clusters, got.weight, got.literal, got.combo) != (3, Fraction(5, 2), Fraction(1, 6), 3):
        failures.append(f"the even split: got {got}")
    mixed = spell(sample_corpus(files(("XX_A", 3, 1), ("XX_A | 0", 1, 1))), candidate("XX_A"))
    if (mixed.literal, mixed.share) != (Fraction(1, 4), 1):
        failures.append(f"a mixed spelling counts as literal: got {mixed}")
    other_value = spell(sample_corpus(files(("XX_A", 3, 1), ("2", 5, 2))), candidate("XX_A"))
    if other_value.clusters != 3 or other_value.literal:
        failures.append(f"only the files that pass the value count: got {other_value}")
    return failures


def check_combination() -> list[str]:
    failures = []
    rows = files(("XX_F2 | XX_F1", 3, 48), ("XX_F1|XX_F2", 2, 48))
    found = candidate("XX_F1", "XX_F2")
    got = spell(sample_corpus(rows), found)
    if (got.tier, got.key, got.hint, got.combo) != (spelling.A, "XX_F1 | XX_F2", "XX_F2 | XX_F1", 5):
        failures.append(f"B | A is A | B, the hint is the most common order: got {got}")
    strict = spell(sample_corpus(rows, spell_combo=6), found)
    if strict.tier != spelling.B:
        failures.append(f"a combination needs spell_combo lineages for A: got {strict.tier}")
    return failures


def check_keys() -> list[str]:
    failures = []
    samples = sample_corpus(files(("XX_AA", 1, 1), ("XX_A | XX_AA", 1, 1), ("~XX_AA", 1, 1), ("XX_ZZ", 1, 1)))
    got = spelling.candidate_keys(candidate("XX_A"), samples.at(CALLEE, SLOT))
    if got != [("XX_A",), ("XX_AA",)]:
        failures.append(f"keys: the default first, one alias per term, the same ~: got {got}")
    inverted = spelling.candidate_keys(candidate("XX_A", inverted=True), samples.at(CALLEE, SLOT))
    if inverted != [("XX_A",), ("XX_AA",)]:
        failures.append(f"keys of an inverted candidate: got {inverted}")
    return failures


def check_trees() -> list[str]:
    """Each tree evaluates the key with its own values; a tree where it does not evaluate is left out."""
    failures = []
    trees = {"old": StubTree({**VALUES, "XX_A": 5}), "new": StubTree(VALUES), "bare": StubTree({}),
             "gone": StubTree(VALUES, "arity differs")}
    rows = (files(("XX_A", 2, 1)) + [("old", "o1.c", "XX_A", 5), ("old", "o2.c", "1", 1),
                                     ("bare", "b1.c", "1", 1), ("bare", "b2.c", "1", 1)])
    got = spell(sample_corpus(rows, trees), candidate("XX_A"))
    if (got.tier, got.clusters, got.literal) != (spelling.B, 3, 0):
        failures.append(f"a value that differs between trees: got {got}")
    wanted = (("bare", "does not evaluate: unknown identifier"), ("gone", "arity differs"))
    if got.left_out != wanted:
        failures.append(f"left-out trees: got {got.left_out}")
    return failures


def check_manual() -> list[str]:
    failures = []
    named = spell(sample_corpus([]), candidate("XX_A"), {CALLEE: (frozenset({"XX_A", "XX_Q"}),)})
    if (named.tier, named.manual) != (spelling.C, True):
        failures.append(f"a name in the callee's manual section gives C: got {named}")
    partly = spell(sample_corpus([]), candidate("XX_F1", "XX_F2"),
                   {CALLEE: (frozenset({"XX_F1"}), frozenset({"XX_F2"}))})
    if partly.tier != spelling.NONE:
        failures.append(f"one section must name every name of the key: got {partly}")
    return failures


def check_text_and_assign() -> list[str]:
    failures = []
    samples = sample_corpus(files(("XX_A", 3, 1)))
    if spelling.NO_SPELLING.text != "no sample passes the value":
        failures.append(f"text with no sample: got {spelling.NO_SPELLING.text}")
    speller = spelling.Speller(samples, {}, samples.thresholds)
    found = candidate("XX_A")
    if speller.spell(CALLEE, SLOT, found).text != "XX_A: 3 clusters, share 1.000, literal 0.000, combo 3":
        failures.append(f"text: got {speller.spell(CALLEE, SLOT, found).text}")
    hinted = spell(sample_corpus(files(("XX_F2 | XX_F1", 1, 48))), candidate("XX_F1", "XX_F2"))
    if not hinted.text.endswith(", written XX_F2 | XX_F1"):
        failures.append(f"text: a key written in another order names the hint: got {hinted.text}")
    if not speller.reads(CALLEE, SLOT) or speller.reads(CALLEE, SLOT + 1):
        failures.append("reads: only the slot that a sample tree reads")
    record = SimpleNamespace(covered=True, callee=CALLEE, row=SimpleNamespace(slot=SLOT), spellings=(), sampled=False,
                             search=covers.Search([found, candidate("XX_F1", "XX_F2")]))
    unread = SimpleNamespace(covered=True, callee=CALLEE, row=SimpleNamespace(slot=SLOT + 1), spellings=(),
                             sampled=False, search=None)
    spelling.assign([record, unread], speller)
    if [item.tier for item in record.spellings] != [spelling.B, spelling.NONE]:
        failures.append(f"assign: one spelling per candidate, in rank order: got {record.spellings}")
    if not record.sampled or unread.sampled or unread.spellings:
        failures.append("assign: a site is sampled only when a sample tree reads its slot")
    return failures


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_a_edges, check_b_edges, check_weights, check_combination, check_keys, check_trees,
                  check_manual, check_text_and_assign):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    print("\n".join(found) or "spellingtests: all passed")
    sys.exit(1 if found else 0)
