"""Sample corpus: the calls that vendor sample code makes to the wanted callees, each argument evaluated under its own
SDK version, and the lineage of the sample files.

The wanted slots are the slots that the inventory found a vendor prototype for (Inventory.prototypes): the argmap
slots and the proposed ones, with variadic arguments left out. read() takes each sample tree in turn:
1. It lists the files under the tree's folders with a source suffix, case ignored. A node is one file content, by
   SHA-256, so exact copies are one node. A node keeps every path it has in every tree, relative to the tree folder,
   in lower case with forward slashes. Each node is read once per tree.
2. It decodes a node with the tree's encoding and tokenizes it. A file that fails is listed with the reason and
   skipped.
3. It drops the directive lines and keeps every #if branch. It finds the calls to the wanted callees that do not
   follow `.`, `->` or `::`. A call whose arguments hold `;`, `{` or `}` joins text from two branches and is dropped.
4. It evaluates each wanted argument with the tree's own header set and profile, and converts an ok value to the
   tree's slot type. A call whose argument count does not fit the tree's prototype is unsupported (cause "arity").

A tree is left out for a slot, with the reason, when its headers do not declare the callee ("no prototype"), define it
as a function-like macro, or give it another arity ("arity differs") or another spelled slot type ("slot type
differs") than the target prototype.

Each observation has a spelling key. A combination of names with | and an optional ~ has one canonical text, with the
names sorted: "A | B", "~A", "~(A | B)". Any other expression keeps its normalized text. Its class is named (names
only), literal (no names) or mixed.

lineage() clusters a node set with complete linkage at lineage_cut (clusters.py). The similarity of two nodes is the
Jaccard index of their shingle sets: each run of shingle_size tokens, directives dropped. When either node has fewer
than lineage_min_shingles shingles, the similarity is 1 when they share a path and 0 when not.

sampled_proposals() fills the two sample columns of argmap-proposed.csv: the lineages of the nodes with an ok
observation at the slot, and the named spellings there, each with its lineages.

Standard library only.
"""

import hashlib
import re
import sys
import time
from collections import Counter
from dataclasses import dataclass, field
from pathlib import Path

import argmap
import ceval
import clusters
import ctokens
import outputs
from inventory import Headers, arity_fits, normalized, value_text

sys.path.append(str(Path(__file__).resolve().parents[1]))  # tools/, after the standard library
import osutil  # noqa: E402

NAMED, LITERAL, MIXED = "named", "literal", "mixed"
SAMPLE_CALLS = Path("diagnostics") / "sample-calls.csv"
SAMPLE_CALL_COLUMNS = ("tree", "file", "line", "callee", "slot", "argument", "status", "cause", "value", "key", "kind",
                       "node", "lineage")
NODE_DIGITS = 12  # hex digits of a node hash in the diagnostic
BRANCH_JOINS = frozenset({";", "{", "}"})
MEMBER_ACCESS = frozenset({".", "->", "::"})
NAME = re.compile(r"[A-Za-z_$][0-9A-Za-z_$]*\Z")
HISTOGRAM_BINS = 10
PROPOSAL_SPELLINGS = 5  # the named spellings that one argmap-proposed.csv row shows, most lineages first


@dataclass(frozen=True)
class Observation:
    tree: str
    node: str  # the SHA-256 of the file
    file: str  # the node's first path in the tree, as written
    line: int
    callee: str
    slot: int
    argument: str  # as written, tokens joined by single spaces
    result: ceval.Result  # converted to the tree's slot type when it has one
    key: str  # the spelling key
    names: tuple  # the sorted names of a name combination; () for any other expression
    inverted: bool  # the name combination is under ~
    kind: str  # named, literal or mixed; "" when the result is not ok

    @property
    def value(self):
        return self.result.value if self.result.ok else None


@dataclass
class Tree:
    """One sample tree with its own header set."""
    name: str
    headers: Headers
    profile: object
    slots: dict = field(default_factory=dict)  # (callee, slot) -> CType or None, for the slots the tree reads
    left_out: dict = field(default_factory=dict)  # (callee, slot) -> reason
    prototypes: dict = field(default_factory=dict)  # callee -> the tree's cheaders.Function
    files: int = 0  # paths with a source suffix
    nodes: set = field(default_factory=set)
    call_nodes: set = field(default_factory=set)  # nodes with at least one observation
    failures: list = field(default_factory=list)  # (file, reason)

    def evaluate(self, source, key: tuple) -> ceval.Result:
        """SOURCE (text or tokens) under this tree's headers and profile, converted to the type of slot KEY."""
        result = ceval.evaluate(source, self.profile, expand=self.headers.expand, resolve=self.headers.resolve,
                                resolve_type=self.headers.resolve_type)
        ctype = self.slots.get(key)
        return ceval.convert(result, ctype, self.profile) if result.ok and ctype is not None else result


@dataclass
class Corpus:
    observations: list  # in tree, file and line order
    trees: dict  # name -> Tree, in configuration order
    thresholds: dict
    paths: dict = field(default_factory=dict)  # node -> set of lower-case paths, over every tree
    shingles: dict = field(default_factory=dict)  # node -> frozenset, for the nodes with an ok observation
    seconds: float = 0.0
    _at: dict = field(default_factory=dict)
    _similar: dict = field(default_factory=dict)
    _lineages: dict = field(default_factory=dict)

    def at(self, callee: str, slot: int) -> list:
        """The observations at one slot."""
        if not self._at and self.observations:
            for observation in self.observations:
                self._at.setdefault((observation.callee, observation.slot), []).append(observation)
        return self._at.get((callee, slot), [])

    def dense(self, node: str) -> bool:
        return len(self.shingles[node]) >= self.thresholds["lineage_min_shingles"]

    def similarity(self, first: str, second: str) -> float:
        if first == second:
            return 1.0
        pair = (first, second) if first < second else (second, first)
        if pair not in self._similar:
            if self.dense(first) and self.dense(second):
                self._similar[pair] = clusters.jaccard(self.shingles[first], self.shingles[second])
            else:
                self._similar[pair] = 1.0 if self.paths[first] & self.paths[second] else 0.0
        return self._similar[pair]

    def lineage(self, nodes) -> list[frozenset]:
        """The lineages of NODES (nodes with an ok observation), in order of their smallest node."""
        key = frozenset(nodes)
        if key not in self._lineages:
            found = clusters.complete_linkage(sorted(key), self.similarity, self.thresholds["lineage_cut"])
            self._lineages[key] = [frozenset(cluster) for cluster in found]
        return self._lineages[key]

    def histograms(self) -> tuple[list, list]:
        """The similarity counts of the dense node pairs that share an ok observation slot, in HISTOGRAM_BINS bins:
        the pairs that share a path, then the pairs that do not."""
        nodes = {}
        for observation in self.observations:
            if observation.result.ok and self.dense(observation.node):
                nodes.setdefault((observation.callee, observation.slot), set()).add(observation.node)
        pairs = set()
        for group in nodes.values():
            ordered = sorted(group)
            pairs.update((first, second) for index, first in enumerate(ordered) for second in ordered[index + 1:])
        same = [self.similarity(*pair) for pair in sorted(pairs) if self.paths[pair[0]] & self.paths[pair[1]]]
        other = [self.similarity(*pair) for pair in sorted(pairs) if not self.paths[pair[0]] & self.paths[pair[1]]]
        return clusters.histogram(same, HISTOGRAM_BINS), clusters.histogram(other, HISTOGRAM_BINS)


def wanted_slots(prototypes: dict) -> dict:
    """(callee, slot) -> (spelled parameters, variadic) of the target prototype, variadic arguments left out."""
    return {key: prototype for key, prototype in sorted(prototypes.items()) if key[1] <= len(prototype[0])}


def read(loaded, found) -> Corpus:
    """LOADED: a config.Config. FOUND: the inventory, for its closures and prototypes."""
    start = time.perf_counter()
    wanted = wanted_slots(found.prototypes)
    corpus = Corpus([], {}, loaded.thresholds)
    suffixes = tuple(suffix.lower() for suffix in loaded.sources.suffixes)
    for sample in loaded.samples:
        profile = loaded.reference(sample.reference).config.profile
        closures = [closure for name, closure in found.closures if name == sample.reference]
        tree = Tree(sample.name, Headers(closures, profile), profile)
        _choose_slots(tree, wanted)
        corpus.trees[sample.name] = tree
        if tree.slots:
            _read_tree(corpus, tree, sample, suffixes)
    corpus.seconds = time.perf_counter() - start
    return corpus


def _choose_slots(tree: Tree, wanted: dict):
    for key, (parameters, variadic) in wanted.items():
        callee, slot = key
        closure = tree.headers.owner(callee)
        records = closure.functions.get(callee) if closure is not None else None
        if tree.headers.is_function_macro(callee):
            tree.left_out[key] = "function-like macro"
        elif not records:
            tree.left_out[key] = "no prototype"
        elif len(records[0].parameters) != len(parameters) or records[0].variadic != variadic:
            tree.left_out[key] = "arity differs"
        elif argmap.normalized(records[0].parameters[slot - 1]) != argmap.normalized(parameters[slot - 1]):
            tree.left_out[key] = "slot type differs"
        else:
            tree.slots[key] = tree.headers.resolve_type(argmap.normalized(parameters[slot - 1]))
            tree.prototypes[callee] = records[0]


def _read_tree(corpus: Corpus, tree: Tree, sample, suffixes: tuple):
    callees = sorted(tree.prototypes)
    slots = {}
    for callee, slot in tree.slots:
        slots.setdefault(callee, []).append(slot)
    for folder in sample.folders:
        for path in sorted(folder.rglob("*")):
            if path.suffix.lower() not in suffixes or not path.is_file():
                continue
            tree.files += 1
            data = path.read_bytes()
            node = hashlib.sha256(data).hexdigest()
            relative = path.relative_to(folder).as_posix()
            corpus.paths.setdefault(node, set()).add(relative.lower())
            if node not in tree.nodes:
                tree.nodes.add(node)
                _read_node(corpus, tree, node, relative, data, sample.encoding, callees, slots)


def _read_node(corpus: Corpus, tree: Tree, node: str, relative: str, data: bytes, encoding: str, callees: list,
               slots: dict):
    try:
        text = data.decode(encoding)
    except UnicodeDecodeError as error:
        tree.failures.append((relative, f"does not decode as {encoding}: {error.reason}"))
        return
    if not any(callee in text for callee in callees):  # a plain search is three times faster than a regex
        return
    try:
        tokens = ctokens.drop_directives(ctokens.tokenize(text)[0])
    except ctokens.Unsupported as error:
        tree.failures.append((relative, str(error)))
        return
    found = _observations(tree, node, relative, tokens, slots)
    corpus.observations += found
    if found:
        tree.call_nodes.add(node)
    if node not in corpus.shingles and any(observation.result.ok for observation in found):
        corpus.shingles[node] = clusters.shingles([token.text for token in tokens], corpus.thresholds["shingle_size"])


def _observations(tree: Tree, node: str, relative: str, tokens: list, slots: dict) -> list:
    def is_callee(index: int) -> bool:
        token = tokens[index]
        return (token.kind == "id" and token.text in tree.prototypes
                and (index == 0 or tokens[index - 1].text not in MEMBER_ACCESS))

    found = []
    for call in ctokens.find_calls(tokens, is_callee):
        callee = tokens[call.position].text
        arguments = call.arguments(tokens)
        if any(token.text in BRANCH_JOINS for argument in arguments for token in argument):
            continue
        fits = arity_fits(len(arguments), tree.prototypes[callee])
        for slot in slots[callee]:
            if slot > len(arguments):
                continue
            argument = list(arguments[slot - 1])
            if fits:
                result = tree.evaluate(argument, (callee, slot))
            else:
                result = ceval.failure(ceval.UNSUPPORTED, "arity", f"{len(arguments)} arguments")
            key, names, inverted = spelling_key(argument, tree.profile)
            found.append(Observation(tree.name, node, relative, tokens[call.position].line, callee, slot,
                                     ctokens.spelling(argument), result, key, names, inverted, kind_of(result)))
    return found


def spelling_key(tokens: list, profile) -> tuple[str, tuple, bool]:
    """The spelling key of an argument, its sorted names when it is a combination of names with | and an optional ~,
    and whether that combination is under ~."""
    texts = ctokens.unwrapped([token.text for token in tokens])
    inverted = bool(texts) and texts[0] == "~"
    body = texts[1:] if inverted else texts
    if inverted and len(body) > 1:
        inner = ctokens.unwrapped(body)
        if len(inner) == len(body):  # ~A | B is (~A) | B: the ~ does not cover the rest
            return normalized(tokens, profile), (), False
        body = inner
    parts = _or_parts(body)
    if parts and all(len(part) == 1 and NAME.match(part[0]) for part in parts):
        names = tuple(sorted(part[0] for part in parts))
        return canonical(names, inverted), names, inverted
    return normalized(tokens, profile), (), False


def canonical(names: tuple, inverted: bool) -> str:
    """The spelling key of the combination of NAMES with |, under ~ when INVERTED."""
    text = " | ".join(sorted(names))
    if not inverted:
        return text
    return f"~{text}" if len(names) == 1 else f"~({text})"


def _or_parts(texts: list) -> list[list]:
    """TEXTS split at the | that sit outside brackets."""
    parts, current, depth = [], [], 0
    for text in texts:
        if text in ctokens.OPENERS:
            depth += 1
        elif text in ctokens.CLOSERS:
            depth -= 1
        elif text == "|" and depth == 0:
            parts.append(current)
            current = []
            continue
        current.append(text)
    return parts + [current] if current or parts else []


def kind_of(result: ceval.Result) -> str:
    if not result.ok:
        return ""
    if not result.names:
        return LITERAL
    return MIXED if result.literal else NAMED


def lineage_ids(corpus: Corpus) -> dict:
    """(callee, slot, value, node) -> the short hash of the smallest node of its lineage, for the ok observations."""
    groups = {}
    for observation in corpus.observations:
        if observation.result.ok:
            key = (observation.callee, observation.slot, observation.value)
            groups.setdefault(key, set()).add(observation.node)
    found = {}
    for (callee, slot, value), nodes in groups.items():
        for cluster in corpus.lineage(nodes):
            label = min(cluster)[:NODE_DIGITS]
            found.update(((callee, slot, value, node), label) for node in cluster)
    return found


def sample_calls_text(corpus: Corpus, generation: int) -> str:
    """diagnostics/sample-calls.csv: one row per observation."""
    labels = lineage_ids(corpus)
    rows = []
    for item in corpus.observations:
        result = item.result
        label = labels.get((item.callee, item.slot, item.value, item.node), "") if result.ok else ""
        rows.append((item.tree, item.file, item.line, item.callee, item.slot, item.argument, result.status,
                     result.cause, value_text(result), item.key, item.kind, item.node[:NODE_DIGITS], label))
    return outputs.csv_text("evidence-sample-calls", generation, SAMPLE_CALL_COLUMNS, rows)


def sampled_proposals(corpus: Corpus, rows: list) -> list:
    """ROWS (inventory.proposed) with their two sample columns: the lineages of the sample files with an ok observation
    at the slot, and the named spellings there, each with its lineages, most first. Both stay empty when no sample
    tree reads the slot."""
    filled = []
    for row in rows:
        key = row[:2]
        if not any(key in tree.slots for tree in corpus.trees.values()):
            filled.append(row)
            continue
        ok = [item for item in corpus.at(*key) if item.result.ok]
        named = {}
        for item in ok:
            if item.kind == NAMED:
                named.setdefault(item.key, set()).add(item.node)
        counts = sorted((-len(corpus.lineage(nodes)), text) for text, nodes in named.items())
        spellings = "; ".join(f"{text} {-count}" for count, text in counts[:PROPOSAL_SPELLINGS])
        filled.append(row[:-2] + (len(corpus.lineage({item.node for item in ok})), spellings))
    return filled


def write(folder: Path, corpus: Corpus, generation: int):
    """diagnostics/sample-calls.csv in FOLDER, for state generation GENERATION."""
    path = folder / SAMPLE_CALLS
    path.parent.mkdir(exist_ok=True)
    osutil.write_whole(path, sample_calls_text(corpus, generation))


def summary(corpus: Corpus) -> list[str]:
    """Console lines: per tree, the files, nodes, call nodes, observations and failures."""
    counts = Counter(observation.tree for observation in corpus.observations)
    return [f"{name}: {tree.files} files, {len(tree.nodes)} distinct, {len(tree.call_nodes)} with calls, "
            f"{counts[name]} observations, {len(tree.failures)} failed" for name, tree in corpus.trees.items()]
