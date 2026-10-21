"""Recount the evidence for data/codegen-groups.csv from the game's exe.

`check.py groups` runs it. For each row it counts the tells that docs/PORTING.md
section 6 lists, and names each function whose tells contradict the row's flags.
It also follows register arguments. One passed into a later row proves /GL. Those
passed inside one row tie functions to one source file, unless /GL or the linker's
folding of identical static functions joins two files: it writes these clusters
to data/file-clusters.csv.

It reads each function's code by following the paths from its entry, so it never
decodes jump tables or padding. Only game rows are read; a library row gets its
function count.

Needs capstone, so it runs in .venv.
"""

import collections
import functools
import operator
from collections.abc import Callable, Iterable
from pathlib import Path
from typing import NamedTuple

import codegen
import codetells
import pe
import progress
import x86

FILE_CLUSTERS = progress.ROOT / "data" / "file-clusters.csv"
MAX_ADDRESSES = 6  # addresses shown per line

PROOF = x86.EAX | x86.EBX | x86.ESI | x86.EDI  # thiscall and __fastcall pass ecx and edx without /GL


class Reading(NamedTuple):
    """What the evidence of each game row is counted from."""
    functions: dict[int, x86.Function]
    cookie: int | None
    strings: codetells.StringFinder
    callers: dict[int, list[tuple[int, int]]]  # calls_in()


def report(game: Path, names: dict[int, str]) -> int:
    """Print the evidence of each game row and write data/file-clusters.csv.
    names: the library function at each address, from src/library.csv.
    Returns 1 if a function contradicts its row's flags."""
    image = pe.Image(game)
    rows = progress.load_codegen_groups()
    functions = read_functions(image, game_functions(rows), names)
    sites = register_argument_sites(functions, names)
    reading = Reading(functions, codetells.security_cookie(image, names), codetells.StringFinder(image),
                      calls_in(functions))
    addresses = [entry["address"] for entry in progress.load_functions()]
    contradictions = 0
    for index, row in enumerate(rows):
        if row["kind"] == "game":
            contradictions += print_game_row(index, row, reading)
        else:
            print(f"{label(row)}  library: {sum(row['start'] <= address < row['end'] for address in addresses)} functions")
    for line in cross_row_lines(sites, functions, rows):
        print(f"/GL  {line}")
    report_clusters(sites, functions)
    return 1 if contradictions else 0


def print_game_row(index: int, row: dict, reading: Reading) -> int:
    """Print the evidence of one game row. Returns how many of its rules a function contradicts."""
    tells = [codetells.Tells.of(function, reading.cookie, reading.strings)
             for function in reading.functions.values() if function.row == index]
    callers = reading.callers[index]
    print(f"{label(row)}  {row['flags']}")
    for line in describe(tells):
        print(f"     {line}")
    print(f"     called from other game rows: {len({caller for caller, _ in callers})} functions, "
          f"{len(callers)} calls and jumps")
    found = contradicting(row["flags"].split(), tells, reading.cookie)
    for rule, addresses in found:
        print(f"FAIL {label(row)}: {rule}: {len(addresses)}: {show(addresses)}")
    return len(found)


def report_clusters(sites: list["Site"], functions: dict[int, x86.Function]) -> None:
    """Write data/file-clusters.csv and print how many clusters it holds."""
    clusters = file_clusters(sites, functions)
    write_clusters(clusters, sites, functions)
    print(f"     {len(clusters)} file clusters, {sum(map(len, clusters))} functions: "
          f"{FILE_CLUSTERS.relative_to(progress.ROOT).as_posix()}")


# ---------------------------------------------------------------- decoding

def game_functions(rows: list[dict]) -> list[tuple[int, int, int]]:
    """(address, size, row) of every function of data/functions.csv that starts in a game row."""
    starts = [(row["start"], row["end"], index) for index, row in enumerate(rows) if row["kind"] == "game"]
    found = []
    for entry in progress.load_functions():
        index = next((index for start, end, index in starts if start <= entry["address"] < end), None)
        if index is not None:
            found.append((entry["address"], entry["size"], index))
    return found


def read_functions(image: pe.Image, entries: list[tuple[int, int, int]], names: dict[int, str]) -> dict[int, x86.Function]:
    """Decode each (address, size, row)."""
    decoder = x86.Decoder(image, names)
    return {address: decoder.function(address, size, row) for address, size, row in entries}


# ---------------------------------------------------------------- register arguments

def calls(function: x86.Function) -> list[x86.Instruction]:
    """Its direct calls and its jumps out of the function."""
    end = function.address + function.size
    return [instruction for instruction in function.code if instruction.target is not None
            and (instruction.mnemonic == "call" or not function.address <= instruction.target < end)]


def effect(instruction: x86.Instruction) -> tuple[int, int]:
    """Reads and writes. A call may change eax, ecx and edx."""
    return instruction.reads, instruction.writes | (x86.CALL_CHANGES if instruction.mnemonic == "call" else 0)


def effect_with_arguments(instruction: x86.Instruction, arguments: dict[int, int]) -> tuple[int, int]:
    """effect(), where a call or a jump out of the function also reads its target's register arguments."""
    reads, writes = effect(instruction)
    return reads | arguments.get(instruction.target, 0), writes


def any_of(masks: Iterable[int]) -> int:
    """The bits that are set in any of the masks."""
    return functools.reduce(operator.or_, masks, 0)


def settle(update: Callable[[x86.Instruction], bool], instructions: list[x86.Instruction]) -> None:
    """Call update on each instruction, pass after pass, until a whole pass changes nothing.
    update returns whether it changed anything."""
    changed = True
    while changed:
        changed = any([update(instruction) for instruction in instructions])  # a list, so every instruction updates


def read_first(function: x86.Function, arguments: dict[int, int]) -> int:
    """The registers the function reads before it writes them, on some path from its entry."""
    leaving = {instruction.address for instruction in calls(function)}
    live = {}

    def update(instruction: x86.Instruction) -> bool:
        reads, writes = (effect_with_arguments(instruction, arguments) if instruction.address in leaving
                         else effect(instruction))
        after = any_of(live.get(following, 0) for following in function.successors[instruction.address])
        value = reads | after & ~writes
        changed = live.get(instruction.address) != value
        live[instruction.address] = value
        return changed

    settle(update, function.code[::-1])
    return live.get(function.address, 0)


def direct_callers(functions: dict[int, x86.Function]) -> dict[int, set[int]]:
    """For each function: the functions that call it or jump to it."""
    callers = collections.defaultdict(set)
    for function in functions.values():
        for target in {instruction.target for instruction in calls(function) if instruction.target in functions}:
            callers[target].add(function.address)
    return callers


def register_arguments(functions: dict[int, x86.Function]) -> dict[int, int]:
    """read_first() of every function, solved over the calls between them."""
    callers = direct_callers(functions)
    arguments = {}
    pending = set(functions)
    while pending:
        address = pending.pop()
        value = read_first(functions[address], arguments)
        if value != arguments.get(address, 0):
            arguments[address] = value
            pending |= callers[address]
    return arguments


def incoming(function: x86.Function) -> dict[int, int]:
    """At each instruction: the registers that may still hold the value they had at the entry."""
    state = {function.address: x86.ALL_REGISTERS}

    def pass_on(instruction: x86.Instruction) -> bool:
        """Join what the instruction keeps into the instructions after it. Returns whether any changed."""
        if instruction.address not in state:
            return False
        kept = state[instruction.address] & ~(x86.CALL_CHANGES if instruction.mnemonic == "call" else instruction.writes)
        changed = False
        for following in function.successors[instruction.address]:
            value = state.get(following, 0) | kept
            if state.get(following) != value:
                state[following] = value
                changed = True
        return changed

    settle(pass_on, function.code)
    return state


class Site(NamedTuple):
    caller: int
    callee: int
    address: int


def register_argument_sites(functions: dict[int, x86.Function], names: dict[int, str]) -> list[Site]:
    """Calls and jumps that pass an argument in eax, ebx, esi or edi: the callee reads one
    before it writes it, and the caller writes it on every path to the call."""
    arguments = register_arguments(functions)
    sites = []
    for function in functions.values():
        passing = [instruction for instruction in calls(function)
                   if instruction.target in functions and instruction.target not in names
                   and arguments.get(instruction.target, 0) & PROOF]
        if passing:
            state = incoming(function)
            sites += [Site(function.address, instruction.target, instruction.address) for instruction in passing
                      if arguments[instruction.target] & PROOF & ~state[instruction.address]]
    return sites


def cross_row_lines(sites: list[Site], functions: dict[int, x86.Function], rows: list[dict]) -> list[str]:
    """One line for each pair of rows that register arguments cross into a later row.

    A call back to an earlier row proves nothing: /OPT:ICF folds identical static functions
    into the first object's copy, so a static's caller can land in an earlier object."""
    pairs = collections.defaultdict(list)
    for site in sites:
        caller, callee = functions[site.caller].row, functions[site.callee].row
        if caller != callee and site.callee > site.caller:
            pairs[caller, callee].append(site)
    lines = []
    for (caller, callee), found in sorted(pairs.items()):
        callers = sorted({site.caller for site in found})
        callees = sorted({site.callee for site in found})
        lines.append(f"{label(rows[caller])} -> {label(rows[callee])}: {len(callers)} callers ({show(callers)}), "
                     f"{len(callees)} callees ({show(callees)})")
    return lines


def file_clusters(sites: list[Site], functions: dict[int, x86.Function]) -> list[list[int]]:
    """Functions that register arguments tie together inside one row, each list sorted."""
    parent = {}

    def root(address: int) -> int:
        while parent.get(address, address) != address:
            address = parent[address]
        return address

    for site in in_one_row(sites, functions):
        first, second = sorted((root(site.caller), root(site.callee)))
        parent[second] = first
    clusters = collections.defaultdict(list)
    for address in parent.keys() | {root(address) for address in parent}:
        clusters[root(address)].append(address)
    return sorted(sorted(members) for members in clusters.values())


def in_one_row(sites: list[Site], functions: dict[int, x86.Function]) -> list[Site]:
    """The sites whose caller and callee are two functions of one row."""
    return [site for site in sites
            if functions[site.caller].row == functions[site.callee].row and site.caller != site.callee]


def write_clusters(clusters: list[list[int]], sites: list[Site], functions: dict[int, x86.Function]) -> None:
    """One line per member: its cluster, its address, and the members it passes register arguments to."""
    callees = collections.defaultdict(set)
    for site in in_one_row(sites, functions):
        callees[site.caller].add(site.callee)
    lines = ["cluster,address,callees"]
    for members in clusters:
        for address in members:
            passes = " ".join(f"0x{callee:08x}" for callee in sorted(callees[address]))
            lines.append(f"0x{members[0]:08x},0x{address:08x},{passes}")
    FILE_CLUSTERS.write_text("\n".join(lines) + "\n", encoding="utf-8", newline="\n")


def calls_in(functions: dict[int, x86.Function]) -> dict[int, list[tuple[int, int]]]:
    """For each row: (caller, target) for each call or jump into it from another game row."""
    links = [(function, functions[instruction.target]) for function in functions.values()
             for instruction in calls(function) if instruction.target in functions]
    found = collections.defaultdict(list)
    for caller, callee in links:
        if callee.row != caller.row:
            found[callee.row].append((caller.address, callee.address))
    return found


# ---------------------------------------------------------------- tells

def count(tells: list[codetells.Tells], test: Callable[[codetells.Tells], bool]) -> int:
    return sum(1 for t in tells if test(t))


def describe(tells: list[codetells.Tells]) -> list[str]:
    """The row's counts: functions, unless a line says otherwise."""
    return [
        f"{len(tells)} functions, {count(tells, lambda t: not t.aligned)} not 16-byte aligned",
        f"frame {count(tells, lambda t: t.frame)}, "
        f"with no EH or and esp {count(tells, lambda t: t.bare_frame)}, "
        f"none but reads an argument {count(tells, lambda t: t.argument_without_frame)}",
        f"EH {count(tells, lambda t: t.eh)}, cookie {count(tells, lambda t: t.cookie)}, "
        f"EH without cookie {count(tells, lambda t: t.eh_without_cookie)}",
        f"slot read twice {count(tells, lambda t: t.slot_reread)}, push and pop {count(tells, lambda t: t.push_pop)}",
        f"literals: {shared_literals(tells)} shared, {len(copied_literals(tells))} copied",
        *float_lines(tells),
    ]


def shared_literals(tells: list[codetells.Tells]) -> int:
    """The texts that one address holds for several functions."""
    texts = collections.defaultdict(set)  # text: the addresses the row uses it at
    users = collections.defaultdict(set)  # (text, address): the functions that use it
    for t in tells:
        for text, address in t.strings:
            texts[text].add(address)
            users[text, address].add(t.address)
    return sum(1 for text, addresses in texts.items() if len(addresses) == 1 and len(users[text, min(addresses)]) > 1)


def float_lines(tells: list[codetells.Tells]) -> list[str]:
    """The x87 and xmm lines of describe()."""
    x87 = [t for t in tells if t.floats.x87]
    x87_tells = [t for t in tells if t.floats.x87_tells]
    first = {}
    for t in x87_tells:
        for name in t.floats.x87_tells:
            first.setdefault(name, t.address)
    x87_line = f"x87 {len(x87)}, with a tell /arch:SSE2 never makes {len(x87_tells)}"
    if first:
        x87_line += f" ({', '.join(f'{name} 0x{address:x}' for name, address in first.items())})"
    sse = [t.address for t in tells if t.floats.sse]
    fast = [t.address for t in tells if t.floats.fast]
    xmm_line = (f"xmm {count(tells, lambda t: t.floats.xmm)}, SSE tell {len(sse)}, "
                f"/arch:SSE2 tell {count(tells, lambda t: t.floats.sse2)}, /fp:fast tell {len(fast)}")
    for kind, addresses in (("sse", sse), ("fast", fast)):
        if addresses:
            xmm_line += f", {kind} {show(addresses)}"
    return [x87_line, xmm_line]


def contradicting(flags: list[str], tells: list[codetells.Tells], cookie: int | None) -> list[tuple[str, list[int]]]:
    """(rule, functions) for each tell that the row's flags could not have made."""
    rules = code_rules(flags, cookie) + float_rules(flags)
    found = [(rule, [t.address for t in tells if test(t)]) for rule, test in rules]
    if codegen.pools_strings(flags):
        found.append(("a copied literal under /GF", copied_literals(tells)))
    return [(rule, addresses) for rule, addresses in found if addresses]


def code_rules(flags: list[str], cookie: int | None) -> list[tuple[str, Callable[[codetells.Tells], bool]]]:
    """(rule, test) for the frame, cookie and stack tells that the flags forbid."""
    optimized = bool({"/O1", "/O2", "/Ox"} & set(flags))
    rules = []
    if optimized and "/Oy-" not in flags:
        rules.append(("a frame with no EH or and esp under /Oy", lambda t: t.bare_frame))
    if optimized and "/Oy-" in flags:
        rules.append(("an argument read with no frame under /Oy-", lambda t: t.argument_without_frame))
    if cookie is not None and "/GS-" in flags:
        rules.append(("a cookie under /GS-", lambda t: t.cookie))
    if cookie is not None and "/GS-" not in flags:
        rules.append(("EH without a cookie under /GS", lambda t: t.eh_without_cookie))
    if optimized:
        rules.append(("a frame slot read twice in a row, which only /Od does", lambda t: t.slot_reread))
    return rules


def float_rules(flags: list[str]) -> list[tuple[str, Callable[[codetells.Tells], bool]]]:
    """(rule, test) for the float tells that the flags forbid."""
    if "/arch:SSE2" in flags:
        rules = [("x87 code that /arch:SSE2 never makes", lambda t: t.floats.x87_tells)]
    elif "/arch:SSE" in flags:
        rules = [("code that only /arch:SSE2 makes", lambda t: t.floats.sse2)]
    else:
        rules = [("code that only /arch:SSE or /arch:SSE2 makes", lambda t: t.floats.sse)]
    if "/fp:fast" not in flags:
        rules.append(("float code that only /fp:fast makes", lambda t: t.floats.fast))
    return rules


def copied_literals(tells: list[codetells.Tells]) -> list[int]:
    """For each text that the row holds at more than one address: the lowest function that uses it, sorted."""
    texts = collections.defaultdict(dict)
    for t in tells:
        for text, address in t.strings:
            texts[text].setdefault(address, t.address)
    return sorted(min(users.values()) for users in texts.values() if len(users) > 1)


# ---------------------------------------------------------------- output

def label(row: dict) -> str:
    return f"{row['group']} {row['start']:#010x}"


def show(addresses: list[int]) -> str:
    shown = " ".join(f"0x{address:x}" for address in addresses[:MAX_ADDRESSES])
    return shown + (f" and {len(addresses) - MAX_ADDRESSES} more" if len(addresses) > MAX_ADDRESSES else "")
