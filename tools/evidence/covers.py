"""Cover search: the names that may spell one value at one mapped slot.

The caller gives the value and the candidate names, each with its value under the target profile, converted to the
slot type. Names with one value form one alias node. All bit work is on the slot type's unsigned pattern.

The search, in rank order:
1. at an and-mask slot only, the covers of the inverse: ~NAME, then the composites ~(A | B ...), then the split
   ~(A | B ...) of 2 to MAX_INVERTED_FLAGS single-bit names;
2. one name with the value itself;
3. at a flags or and-mask slot: the composites A | B ..., then the split A | B ... of single-bit names.
A composite covers the value with 2 to TERMS bit-disjoint nodes, one of them multi-bit at least. Composites rank by
the number of names, then by the names, lowest bit first. A split takes one single-bit node per set bit, so there is
one at most. It ranks last, because a composite of the same value has fewer names. A value of 0 gets a candidate only
from a name whose value is 0; a zero name never takes part in a composite, a split or a ~.

Type gates: a null name (NULL) only at a pointer slot; a truth name (TRUE, FALSE) only at a boolean slot; any other
name only at a slot of its own kind, pointer or integer, where a boolean slot counts as integer. A variadic argument
gets no candidates.

Each lookup costs one step, and so does each node visit of the composite walk. A value with no multi-bit node inside
it skips the walk. When the steps reach the budget the search stops and is incomplete; a cover found before that
stays ("incomplete with cover").

Standard library only.
"""

from dataclasses import dataclass, field

MAX_INVERTED_FLAGS = 4
NULL_NAMES = frozenset({"NULL"})
TRUTH_NAMES = frozenset({"TRUE", "FALSE", "true", "false"})
POINTER, BOOLEAN, INTEGER = "pointer", "boolean", "integer"


@dataclass(frozen=True)
class Name:
    name: str
    value: int  # under the target profile, converted to the slot type
    pointer: bool  # the name's own type is a pointer type
    origins: tuple = ()  # the sources that define it with this value


@dataclass(frozen=True)
class Node:
    aliases: tuple  # Name records with one value, in name order
    value: int  # the unsigned pattern

    @property
    def name(self) -> str:
        return self.aliases[0].name


@dataclass(frozen=True)
class Candidate:
    terms: tuple  # Node records, lowest bit first
    inverted: bool

    @property
    def text(self) -> str:
        names = " | ".join(node.name for node in self.terms)
        if not self.inverted:
            return names
        return f"~{names}" if len(self.terms) == 1 else f"~({names})"


@dataclass(frozen=True)
class Slot:
    kind: str  # pointer, boolean or integer
    mode: str  # value, flags or and-mask (argmap modes)
    bits: int  # the slot type's width
    variadic: bool = False


@dataclass
class Search:
    candidates: list = field(default_factory=list)  # in rank order
    incomplete: bool = False
    steps: int = 0


def passes_gate(name: Name, slot: Slot) -> bool:
    if name.name in NULL_NAMES:
        return slot.kind == POINTER
    if name.name in TRUTH_NAMES:
        return slot.kind == BOOLEAN
    return slot.kind == POINTER if name.pointer else slot.kind in (INTEGER, BOOLEAN)


def nodes(names: list[Name], bits: int) -> dict[int, Node]:
    """The alias nodes by unsigned pattern."""
    mask = (1 << bits) - 1
    grouped = {}
    for name in names:
        grouped.setdefault(name.value & mask, []).append(name)
    return {value: Node(tuple(sorted(group, key=lambda name: name.name)), value) for value, group in grouped.items()}


def _bits_of(value: int) -> list[int]:
    return [1 << bit for bit in range(value.bit_length()) if value >> bit & 1]


class _Searcher:
    def __init__(self, by_value: dict, budget: int):
        self.by_value, self.budget, self.result = by_value, budget, Search()

    def step(self) -> bool:
        """Count one lookup. False when the budget is spent."""
        if self.result.steps >= self.budget:
            self.result.incomplete = True
            return False
        self.result.steps += 1
        return True

    def exact(self, value: int, inverted: bool) -> bool:
        if not self.step():
            return False
        node = self.by_value.get(value)
        if node is not None:
            self.result.candidates.append(Candidate((node,), inverted))
        return True

    def split(self, value: int, inverted: bool) -> bool:
        terms = []
        for bit in _bits_of(value):
            if not self.step():
                return False
            node = self.by_value.get(bit)
            if node is None:
                return True
            terms.append(node)
        self.result.candidates.append(Candidate(tuple(terms), inverted))
        return True

    def composites(self, value: int, inverted: bool, terms: int) -> bool:
        """Every cover of VALUE by 2 to TERMS bit-disjoint nodes, one of them multi-bit at least, in rank order."""
        parts = sorted(part for part in self.by_value if part and part & value == part)
        if all(len(_bits_of(part)) == 1 for part in parts):
            return True
        found = []

        def walk(rest: int, chosen: list) -> bool:
            if not self.step():
                return False
            if rest == 0:
                if len(chosen) >= 2 and any(len(_bits_of(node.value)) > 1 for node in chosen):
                    found.append(tuple(chosen))
                return True
            if len(chosen) == terms:
                return True
            low = rest & -rest  # the lowest bit left must come from the next node
            for part in parts:
                if part & low and part & rest == part and not walk(rest & ~part, chosen + [self.by_value[part]]):
                    return False
            return True

        complete = walk(value, [])
        found.sort(key=lambda chosen: (len(chosen), [node.name for node in chosen]))
        self.result.candidates += [Candidate(chosen, inverted) for chosen in found]
        return complete

    def covers(self, value: int, inverted: bool, terms: int, split_names: int) -> bool:
        """The exact name, the composites, then the split if it takes 2 to SPLIT_NAMES names. False when the budget
        is spent."""
        if not (self.exact(value, inverted) and self.composites(value, inverted, terms)):
            return False
        if 2 <= len(_bits_of(value)) <= split_names:
            return self.split(value, inverted)
        return True


def search(value: int, slot: Slot, names: list[Name], budget: int, terms: int) -> Search:
    """The candidates for VALUE at SLOT, with composites of at most TERMS names."""
    if slot.variadic:
        return Search()
    mask = (1 << slot.bits) - 1
    pattern = value & mask
    searcher = _Searcher(nodes([name for name in names if passes_gate(name, slot)], slot.bits), budget)
    if slot.mode == "and-mask":
        inverse = ~pattern & mask
        if inverse and not searcher.covers(inverse, True, terms, MAX_INVERTED_FLAGS):
            return searcher.result
    if slot.mode == "value":
        searcher.exact(pattern, False)
    else:
        searcher.covers(pattern, False, terms, slot.bits)
    return searcher.result


def slot_kind(spelled: str, ctype, boolean_names) -> str | None:
    """The class of a parameter with spelled type SPELLED (before typedefs unroll) and type CTYPE. A spelled boolean
    name makes a boolean slot, though it unrolls to int. None for a type no name fits, such as a float."""
    if spelled in boolean_names or (ctype is not None and ctype.kind == "bool"):
        return BOOLEAN
    if ctype is None:
        return None
    return {"pointer": POINTER, "int": INTEGER}.get(ctype.kind)
