"""Reference calls: the calls of paired functions in other builds of the game, compared with the game's own calls.

A local adapter writes two neutral files per reference build NAME into the evidence folder:
- pairs-NAME.csv, columns target,reference: one row per paired function, both addresses hex with 0x. A target or
  reference address on more than one row drops all of its rows, so only 1:1 pairs count.
- refcalls-NAME.csv: first the line "# evidence-refcalls schema=1 floats=in-order" (or floats=apart), then the columns
  owner,order,callee,values. One row per call in a reference function: the owner is its reference address, the order
  runs 1..n per owner with no gap and no duplicate. The callee is a reference address (0x...), a name, or ? when it is
  not known. The values are the arguments, separated by spaces: ? when not known, an integer (-?0x... or -?digits)
  with an optional width :8, :16, :32 or :64, or a float (with a . or an exponent). floats=apart says that the build
  passes floats in registers of their own, so a decompiled call that holds a float need not keep the source order.
load() checks every row: a malformed one fails with the file and line.

apply() compares each paired function that has game calls (inventory.Inventory.owned_calls):
1. The game calls and the reference calls align on callee identity (remap.align). A callee called once on each side
   anchors: it scores more than all other pairs together. Another equal callee scores 1. Only the pairs that every
   optimal alignment makes count. A reference callee address maps through the 1:1 pairs, and an unmapped one never
   aligns. A game callee is its role id, an address only when it reads 0x....
2. An aligned call compares its arguments, slot by slot, when both sides have the same count. On a floats=apart build,
   a call with a float on either side does not compare.
3. The kill switch: a function gives evidence only with at least pair_min_sites compared slots whose value both sides
   know, and with the same value in at least pair_min_rate of them.
4. A coverage call site in a live function whose slot compares gets (build, reference value, same) in
   record.references. Another value adds the flag DIFFERS, counterevidence: A becomes A*. A literal whose value
   differs across builds may stand for a macro.
5. A build with fewer than yield_floor such sites gives no evidence; its report says so.

Standard library only.
"""

import re
import struct
from collections import Counter
from dataclasses import dataclass
from pathlib import Path

import inventory
import outputs
import remap

PAIRS_PREFIX, CALLS_PREFIX = "pairs-", "refcalls-"
PAIR_COLUMNS = ("target", "reference")
CALL_COLUMNS = ("owner", "order", "callee", "values")
IN_ORDER, APART = "in-order", "apart"
CALLS_HEADER = re.compile(r"# evidence-refcalls schema=1 floats=(in-order|apart)")
ADDRESS = re.compile(r"0x[0-9a-f]+")
NAME = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")
INTEGER = re.compile(r"(-?(?:0x[0-9a-f]+|[0-9]+))(?::(8|16|32|64))?")
FLOAT = re.compile(r"-?(?:[0-9]+\.[0-9]*(?:e[-+]?[0-9]+)?|\.[0-9]+(?:e[-+]?[0-9]+)?|[0-9]+e[-+]?[0-9]+)")
UNKNOWN = "?"
DIFFERS = "value differs across builds"  # the site flag of a value that another build passes otherwise


class PairsError(Exception):
    """A reference call file that is malformed or misses its partner file."""


@dataclass(frozen=True)
class Value:
    number: int | float
    bits: int  # the width that the file gives an integer; 0 when it gives none
    text: str  # as the file spells it


@dataclass(frozen=True)
class Call:
    callee: int | str | None  # the target address of a paired callee, a name, or None
    values: tuple  # one Value, or None when not known, per argument


@dataclass(frozen=True)
class Build:
    name: str
    floats: str  # IN_ORDER or APART
    pairs: int  # the 1:1 pairs
    dropped: int  # the pair rows dropped: their target or reference address is on another row too
    owners: dict  # target address -> the paired reference function's calls, in order
    unpaired: int  # reference functions with calls and no 1:1 pair


@dataclass
class Report:
    build: str
    floats: str
    pairs: int
    dropped: int
    unpaired: int
    compared: int = 0  # paired functions with game calls
    no_calls: int = 0  # paired functions with reference calls and no game calls
    no_shared: int = 0  # compared functions with no aligned call
    few: int = 0  # killed: fewer than pair_min_sites known slots
    low: int = 0  # killed: the same value in fewer than pair_min_rate of the known slots
    live: int = 0
    slots: int = 0  # the known slots of the live functions
    agree: int = 0  # the known slots of the live functions with the same value
    same: int = 0  # the coverage sites of the live functions, by the reference value: the same,
    differs: int = 0  # another,
    unknown: int = 0  # or none (an unknown value, an unaligned call, another argument count, a float apart)
    under_floor: bool = False  # same plus differs under yield_floor: the build gives no evidence


def load(folder: Path) -> list[Build]:
    """The reference builds in FOLDER, by name; [] when it holds no reference call files."""
    names = {path.name[len(PAIRS_PREFIX):-len(".csv")] for path in folder.glob(f"{PAIRS_PREFIX}*.csv")}
    calls = {path.name[len(CALLS_PREFIX):-len(".csv")] for path in folder.glob(f"{CALLS_PREFIX}*.csv")}
    for name in sorted(names ^ calls):
        missing = f"{CALLS_PREFIX}{name}.csv" if name in names else f"{PAIRS_PREFIX}{name}.csv"
        raise PairsError(f"{folder / missing} is missing: reference build {name} needs {PAIRS_PREFIX}{name}.csv and "
                         f"{CALLS_PREFIX}{name}.csv")
    return [_read_build(folder, name) for name in sorted(names)]


def _read_build(folder: Path, name: str) -> Build:
    targets, dropped = _read_pairs(folder / f"{PAIRS_PREFIX}{name}.csv")
    floats, functions = _read_calls(folder / f"{CALLS_PREFIX}{name}.csv")
    owners = {}
    for owner, calls in functions.items():
        if owner in targets:
            owners[targets[owner]] = tuple(Call(targets.get(callee) if isinstance(callee, int) else callee, values)
                                           for callee, values in calls)
    return Build(name, floats, len(targets), dropped, owners, len(functions) - len(owners))


def _read_pairs(path: Path) -> tuple[dict, int]:
    """Reference address -> target address for the 1:1 pairs of PATH, and the rows dropped."""
    rows = [(_address(values["target"], "target", where), _address(values["reference"], "reference", where))
            for where, values in outputs.read_rows(path, PAIR_COLUMNS, PairsError)]
    targets = Counter(target for target, _ in rows)
    references = Counter(reference for _, reference in rows)
    kept = {reference: target for target, reference in rows if targets[target] == 1 and references[reference] == 1}
    return kept, len(rows) - len(kept)


def _read_calls(path: Path) -> tuple[str, dict]:
    """The floats mode of PATH, and reference owner -> [(callee, values)] in call order."""
    with path.open(encoding="utf-8") as data:
        first = data.readline().rstrip("\n")
    header = CALLS_HEADER.fullmatch(first)
    if header is None:
        raise PairsError(f"{path}:1: the first line must be '# evidence-refcalls schema=1 floats=in-order' or "
                         f"'... floats=apart', not {first[:60]!r}")
    functions, seen = {}, {}
    for where, values in outputs.read_rows(path, CALL_COLUMNS, PairsError, skip=1):
        owner = _address(values["owner"], "owner", where)
        if not values["order"].isdigit() or int(values["order"]) < 1:
            raise PairsError(f"{where}: order {values['order']!r} is not a number from 1")
        order = int(values["order"])
        if (owner, order) in seen:
            raise PairsError(f"{where}: owner {owner:#x} has call {order} twice, also at {seen[owner, order]}")
        seen[owner, order] = where
        functions.setdefault(owner, {})[order] = (_callee(values["callee"], where),
                                                  tuple(parse_value(text, where) for text in values["values"].split()))
    for owner, calls in functions.items():
        missing = next((order for order in range(1, len(calls) + 1) if order not in calls), None)
        if missing is not None:
            raise PairsError(f"{path}: owner {owner:#x} has no call {missing}")
    return header[1], {owner: [calls[order] for order in sorted(calls)] for owner, calls in functions.items()}


def _address(text: str, what: str, where: str) -> int:
    if not ADDRESS.fullmatch(text):
        raise PairsError(f"{where}: {what} {text!r} is not a lowercase hex address with 0x")
    return int(text, 16)


def _callee(text: str, where: str) -> int | str | None:
    if text == UNKNOWN:
        return None
    if ADDRESS.fullmatch(text):
        return int(text, 16)
    if NAME.fullmatch(text):
        return text
    raise PairsError(f"{where}: callee {text!r} is not ?, a hex address with 0x or a name")


def parse_value(text: str, where: str) -> Value | None:
    """The argument value TEXT; None for ?."""
    if text == UNKNOWN:
        return None
    integer = INTEGER.fullmatch(text)
    if integer:
        return Value(int(integer[1], 16 if "x" in integer[1] else 10), int(integer[2] or 0), text)
    if FLOAT.fullmatch(text):
        return Value(float(text), 0, text)
    raise PairsError(f"{where}: value {text!r} is not ?, an integer with an optional width :8, :16, :32 or :64, "
                     f"or a float")


def same_value(value, ctype, reference: Value) -> bool:
    """Whether the game's VALUE, of type CTYPE (None when not known), is REFERENCE. Two integers compare modulo the
    narrower width, 32 bits when not known. A game float against a 32-bit or 64-bit reference integer compares its
    float or double bit pattern. Any other pair with a float compares at float precision, exactly when a value is too
    large for a float."""
    number = reference.number
    if isinstance(number, int) and not isinstance(value, float):
        bits = min(ctype.bits if ctype is not None and ctype.bits else 32, _width(reference))
        return (value - number) % (1 << bits) == 0
    try:
        if isinstance(number, int) and _width(reference) in (32, 64):
            bits = _width(reference)
            pattern = int.from_bytes(struct.pack("<f" if bits == 32 else "<d", value), "little")
            return (pattern - number) % (1 << bits) == 0
        return struct.pack("<f", value) == struct.pack("<f", number)
    except OverflowError:
        return float(value) == float(number)


def _width(reference: Value) -> int:
    """The width of an integer reference value: the file's, else 32 bits when the value fits them, else 64."""
    if reference.bits:
        return reference.bits
    return 32 if -(1 << 31) <= reference.number < (1 << 32) else 64


def align_calls(source: list, reference: list) -> dict:
    """Game call index -> reference call index, for the pairs that every optimal alignment makes. SOURCE and REFERENCE
    hold the callee of each call; None never pairs."""
    anchor = len(source) + len(reference) + 1
    source_counts, reference_counts = Counter(source), Counter(reference)

    def score(i: int, j: int) -> int | None:
        callee = source[i]
        if callee is None or callee != reference[j]:
            return None
        return anchor if source_counts[callee] == 1 and reference_counts[callee] == 1 else 1

    return remap.align(source, reference, score).shared


def apply(builds: list, found, thresholds: dict) -> list[Report]:
    """Compare each build's paired functions with FOUND's owned calls (an inventory.Inventory), and give its coverage
    call sites their reference evidence. One Report per build."""
    games = {int(owner, 16): calls for owner, calls in found.owned_calls.items() if ADDRESS.fullmatch(owner)}
    sites = {}  # (file, line, column) of a call -> [(slot index, coverage site)]
    for record in found.records:
        if record.kind == inventory.CALL and record.result.ok and isinstance(record.result.value, (int, float)):
            index = int(record.slot.rsplit("/", 1)[-1])
            sites.setdefault((record.file, record.line, record.column), []).append((index, record))
    reports = []
    for build in builds:
        report = Report(build.name, build.floats, build.pairs, build.dropped, build.unpaired)
        evidence = []
        for target, calls in sorted(build.owners.items()):
            evidence += _compare(build, games.get(target, []), calls, sites, thresholds, report)
        report.under_floor = report.same + report.differs < thresholds["yield_floor"]
        if not report.under_floor:
            for record, item in evidence:
                record.references += (item,)
                if not item[2] and DIFFERS not in record.flags:
                    record.flags.append(DIFFERS)
        reports.append(report)
    return reports


def _compare(build: Build, game: list, reference: tuple, sites: dict, thresholds: dict, report: Report) -> list:
    """The (site, (build, reference value, same)) of one paired function, counted in REPORT."""
    if not game:
        report.no_calls += 1
        return []
    report.compared += 1
    shared = align_calls([_role(call.target) for call in game], [call.callee for call in reference])
    if not shared:
        report.no_shared += 1
        return []
    compared = {}  # game call index -> its aligned reference call, for the calls whose slots compare
    known = agree = 0
    for i, j in shared.items():
        if not _compares(game[i], reference[j], build.floats):
            continue
        compared[i] = reference[j]
        for value, other in zip(game[i].values, reference[j].values):
            if value is not None and other is not None:
                known += 1
                agree += same_value(value[0], value[1], other)
    if known < thresholds["pair_min_sites"]:
        report.few += 1
        return []
    if agree < thresholds["pair_min_rate"] * known:
        report.low += 1
        return []
    report.live += 1
    report.slots += known
    report.agree += agree
    evidence = []
    for i, call in enumerate(game):
        for index, record in sites.get((call.file, call.line, call.column), ()):
            other = compared[i].values[index - 1] if i in compared else None
            if other is None:
                report.unknown += 1
                continue
            same = same_value(record.result.value, record.result.ctype, other)
            report.same += same
            report.differs += not same
            evidence.append((record, (build.name, other.text, same)))
    return evidence


def _role(target: str) -> int | str:
    """A game callee's role id as align_calls compares it: an address as a number, a name as it is."""
    return int(target, 16) if ADDRESS.fullmatch(target) else target


def _compares(game, reference: Call, floats: str) -> bool:
    """Whether an aligned call compares its slots: the same argument count, and on a floats=apart build no float on
    either side."""
    if len(game.values) != len(reference.values):
        return False
    if floats == IN_ORDER:
        return True
    return not game.floats and not any(value is not None and isinstance(value.number, float)
                                       for value in reference.values)
