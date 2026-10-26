"""The bytes that each call in the exe passes on the stack, and the bytes that each function reads: `check.py args`.

The callers of one function in the original exe may pass different counts when the function reads none of the
extra ones, such as an empty function or one that returns a constant, which the linker may fold into one. C++
declares such a function with `...` after the parameters that it reads. The report gives a verdict per function:
  takes-any  the sure calls pass different counts, and the function reads fewer than the most, pops nothing and
             takes no argument's address
  disagree   the sure calls pass different counts for some other reason: check by hand
  mismatch   every sure call passes one count, and the tree's declaration takes another. Left out when the
             function reads a register at its entry that its convention does not pass, as /GL and a static
             function's callers in its file do: then the declaration's stack bytes say nothing
  unused     every sure call passes what the function reads, and the declaration takes more. /O2 drops a static
             function's unused parameters at the calls in its file, so the declaration may be right
A call is sure when the code around it shows all its bytes: the pushes since esp stood where the prologue left it,
with no other call between, and the cleanup that brings esp back there. Functions that the tree declares with
`...` are left out unless named. Needs capstone, so it runs in .venv.
"""

import collections
import re
from pathlib import Path
from typing import NamedTuple

import dossier
import facts
import groups
import names
import pe
import progress
import project
import x86

SAVED = ("ebx", "esi", "edi", "ebp")  # the registers that a function keeps for its caller
CLEANUP_POPS = ("pop ecx", "pop edx")  # the pops that drop a call's arguments: a saved register is no cleanup


class Site(NamedTuple):
    address: int  # of the call
    target: int
    bytes: int | None  # passed on the stack, None when the code does not show them all


class Reads(NamedTuple):
    size: int  # bytes of stack arguments read, from the first argument on
    address: bool  # whether it takes an argument's address, as va_start does


def saved_offset(function: x86.Function) -> int | None:
    """Where esp stands, relative to the entry, once the prologue has run: after the frame, the locals and the push
    of each saved register before the function writes it. A register that the function never pops came in as an
    argument. None when a push ecx may be a local or an argument: only a saved register after it tells."""
    popped = {i.operands for i in function.code if i.mnemonic == "pop"}
    offset, saved, written, locals_, unsure = 0, set(), 0, False, 0  # unsure: the bytes of push ecx so far
    for instruction in function.code:
        mnemonic, operands = instruction.mnemonic, instruction.operands
        if mnemonic in x86.STOPS or mnemonic == "call" or mnemonic.startswith(("j", "loop")):
            break
        if mnemonic == "push" and operands in SAVED and operands in popped and operands not in saved \
                and not written & x86.REGISTER.get(operands, 0):
            saved.add(operands)
            offset -= unsure + 4
            if unsure:
                locals_ = True  # a push ecx before a saved register makes room for a local
            unsure = 0
        elif mnemonic == "sub" and operands.startswith("esp, ") and not locals_ and not unsure and saved <= {"ebp"} \
                and (size := x86.number(operands[len("esp, "):])) is not None:
            locals_ = True
            offset -= size
        elif (mnemonic, operands) == ("push", "ecx") and not locals_ and saved <= {"ebp"}:
            unsure += 4
        elif operands.startswith("esp,") or mnemonic.startswith(("push", "pop")) or mnemonic == "leave":
            break  # esp moves for something else, such as an argument
        written |= instruction.writes
    return None if unsure else offset


def predecessors(function: x86.Function) -> dict[int, list[int]]:
    """The instructions that can run right before each instruction."""
    before = collections.defaultdict(list)
    for address, following in function.successors.items():
        for after in following:
            before[after].append(address)
    return before


def cleanup(instruction: x86.Instruction) -> int:
    """The bytes that an instruction right after a call drops from the stack: an add esp or a pop of ecx or edx."""
    if f"{instruction.mnemonic} {instruction.operands}" in CLEANUP_POPS:
        return 4
    if instruction.mnemonic == "add" and instruction.operands.startswith("esp, "):
        return x86.number(instruction.operands[len("esp, "):]) or 0
    return 0


def no_call_since(address: int, base: int, offset: dict[int, int], before: dict[int, list[int]],
                  by_address: dict[int, x86.Instruction]) -> bool:
    """Whether every path back from ADDRESS reaches an instruction where esp stood at BASE with no call between."""
    pending, seen = list(before[address]), set()
    while pending:
        address = pending.pop()
        if address in seen:
            continue
        seen.add(address)
        if address not in offset or offset[address] < base and by_address[address].mnemonic == "call":
            return False
        if offset[address] < base:
            pending.extend(before[address])
    return True


def resting_levels(function: x86.Function, offset: dict[int, int], base: int) -> dict[int, int] | None:
    """Where esp stands between calls, before each instruction: BASE, where the prologue left it, raised by 4 by each
    pop of a saved register that frees its slot. None when two paths reach one instruction with different levels."""
    by_address = {i.address: i for i in function.code}
    level = {function.address: base}
    pending = [function.address]
    while pending:
        address = pending.pop()
        instruction = by_address[address]
        restores = instruction.mnemonic == "pop" and instruction.operands in SAVED \
            and offset.get(address) == level[address]
        next_level = level[address] + 4 if restores else level[address]
        for following in function.successors[address]:
            if following not in level:
                level[following] = next_level
                pending.append(following)
            elif level[following] != next_level:
                return None
    return level


def above_rest(function: x86.Function, offset: dict[int, int], level: dict[int, int]) -> bool:
    """Whether esp stands above where it rests at an instruction past the prologue, other than the pops, the leave
    and the ret that end the function."""
    settled = False
    for instruction in function.code:
        at = offset.get(instruction.address)
        settled = settled or at == level[instruction.address]
        if settled and at is not None and at > level[instruction.address] \
                and instruction.mnemonic not in ("pop", "leave", "ret"):
            return True
    return False


def arguments_passed(function: x86.Function, decoder: x86.Decoder, sizes: dict[int, int]) -> list[Site]:
    """Each direct call to a function of known size, with the bytes that it passes on the stack."""
    base = saved_offset(function)
    offset = facts.stack_offsets(function, decoder, sizes) or {}
    level = resting_levels(function, offset, base) if base is not None else None
    if level and above_rest(function, offset, level):
        level = None  # the prologue was read wrong, such as a sub esp that makes room for arguments
    by_address = {i.address: i for i in function.code}
    before = predecessors(function)
    sites = []
    for call in function.code:
        if call.mnemonic != "call" or call.target not in sizes:
            continue
        passed = None
        if level is not None and call.address in offset:
            rest = level[call.address]
            after = offset[call.address] + facts.stack_change(call, decoder, sizes)
            following = call.address + call.size
            while after < rest and following in by_address and (dropped := cleanup(by_address[following])):
                after += dropped
                following += by_address[following].size
            more = following in by_address and cleanup(by_address[following])  # the locals may be arguments
            if after == rest and not more and no_call_since(call.address, rest, offset, before, by_address):
                passed = after - offset[call.address]
        sites.append(Site(call.address, call.target, passed))
    return sites


def arguments_read(function: x86.Function, decoder: x86.Decoder, sizes: dict[int, int],
                   depth: int = 3) -> Reads | None:
    """The stack arguments that the function reads, also through the functions that it jumps to. None when a jump
    goes where this cannot follow, or esp gets lost in a function with no frame."""
    if facts.unknown_jump(function):
        return None
    if x86.has_frame(function.code):
        slots = [(m.disp - 8, i) for i in function.code for m in facts.memory_operands(i.operands)
                 if m.base == "ebp" and m.disp >= 8]
    else:
        offset = facts.stack_offsets(function, decoder, sizes)
        if offset is None or len(offset) < len(function.code):
            return None
        slots = [(m.disp + offset[i.address] - 4, i) for i in function.code for m in facts.memory_operands(i.operands)
                 if m.base == "esp" and m.disp + offset[i.address] >= 4]
    size = max((at + max(facts.memory_width(i.operands), 4) for at, i in slots if i.mnemonic != "lea"), default=0)
    reads = Reads(size, any(i.mnemonic == "lea" for _, i in slots))
    for jump in (i for i in groups.calls(function) if i.mnemonic != "call"):
        if jump.target not in sizes or not depth:
            return None
        further = arguments_read(decoder.function(jump.target, sizes[jump.target], 0), decoder, sizes, depth - 1)
        if further is None:
            return None
        reads = Reads(max(reads.size, further.size), reads.address or further.address)
    return reads


def stack_size(kind: str, types: names.Types) -> int | None:
    """The stack bytes of one parameter of type KIND, in whole dwords, or None when its size is unknown."""
    if "[" in kind or kind.endswith("&"):
        return 4  # an array or a reference passes a pointer
    size = names.element_size(kind, types)
    if size is None and kind in types.kind:  # a type named without its keyword, as C++ allows
        size = names.element_size(f"{types.kind[kind]} {kind}", types)
    return None if size is None else (size + 3) // 4 * 4


def is_struct(kind: str, types: names.Types) -> bool:
    """Whether KIND is a struct or union by value."""
    kind = re.sub(r"\b(?:const|volatile)\b", "", kind).strip()
    return "*" not in kind and (re.match(r"(?:struct|union)\s", kind) is not None
                                or types.kind.get(kind) in ("struct", "union"))


def parameter_bytes(proto: str, types: names.Types) -> int | None:
    """The stack bytes that a prototype's parameters take. None for a variadic, a parameter of unknown size and a
    struct returned by value, which may add a hidden pointer."""
    span = names.parameter_span(proto)
    if span is None:
        return None
    start, _, params = span
    returned = re.sub(r"[\w:~]+\s*$", "", facts.KEYWORD.sub("", proto[:start - 1]))
    if is_struct(returned, types):
        return None
    kinds = [kind for kind in map(names.without_parameter_name, params) if kind != "void"]
    if "..." in kinds:
        return None
    sizes = [stack_size(kind, types) for kind in kinds]
    if None in sizes:
        return None
    convention = facts.printed_keyword(proto)
    if convention == "__thiscall":
        sizes = sizes[1:]
    if convention == "__fastcall":  # the first two parameters of a dword or less, but no float, go in ecx and edx
        in_registers = [n for n, kind in enumerate(kinds) if sizes[n] == 4 and kind != "float"][:2]
        sizes = [size for n, size in enumerate(sizes) if n not in in_registers]
    return sum(sizes)


def unexplained_registers(registers: int, proto: str) -> int:
    """The REGISTERS that a function reads at its entry that its declared convention does not pass."""
    passed = {"__thiscall": x86.ECX, "__fastcall": x86.ECX | x86.EDX}.get(facts.printed_keyword(proto), 0)
    return registers & ~passed


def verdict(sure: collections.Counter, reads: Reads | None, pops: set[int] | None, declared: int | None) -> str | None:
    """takes-any, disagree, mismatch or None, from the byte counts of the sure calls, what the function reads, what
    it pops and the bytes that the tree declares."""
    if len(sure) > 1:
        ignores = reads is not None and not reads.address and pops == set() and reads.size < max(sure)
        return "takes-any" if ignores else "disagree"
    if sure and declared is not None and declared not in sure:
        passes_reads = reads is not None and reads.size in sure and declared > reads.size
        return "unused" if passes_reads else "mismatch"
    return None


def counts_text(sure: collections.Counter) -> str:
    return " ".join(f"{size}x{count}" for size, count in sorted(sure.items())) or "none"


def report(game: Path, addresses: list[int]) -> int:
    """Print each game function with a verdict, or each of ADDRESSES with what this finds."""
    image = pe.Image(game)
    library = {row.address: row.name for row in project.library_rows()}
    functions = groups.read_functions(image, groups.game_functions(progress.load_codegen_groups()), library)
    sizes = progress.function_sizes(progress.load_functions())
    decoder = x86.Decoder(image, library)
    registers = groups.register_arguments(functions)
    passed = collections.defaultdict(list)
    for function in functions.values():
        for site in arguments_passed(function, decoder, sizes):
            passed[site.target].append(site.bytes)
    tree = dossier.known_functions(None, names.read_sources(project.ROOT), names.previous(project.ROOT))
    types = names.Types(project.ROOT / names.TYPES_H)
    for address in addresses or sorted(passed.keys() & functions.keys() - library.keys()):
        function = functions.get(address)
        if function is None or address in library:
            print(f"0x{address:08x} not a game function")
            continue
        proto = tree[address].proto if address in tree else ""
        if "..." in proto and not addresses:
            continue
        sure = collections.Counter(size for size in passed[address] if size is not None)
        reads = arguments_read(function, decoder, sizes)
        pops = facts.exit_pops(function, decoder, sizes)
        unexplained = unexplained_registers(registers.get(address, 0), proto)
        declared = parameter_bytes(proto, types) if proto and not unexplained else None
        found = verdict(sure, reads, pops, declared)
        if found or addresses:
            read = "?" if reads is None else f"{reads.size}{' and an address' if reads.address else ''}"
            popped = "?" if pops is None else max(pops, default=0)
            in_registers = " ".join(name for name, bit in facts.REGISTERS.items() if unexplained & bit) or "none"
            print(f"0x{address:08x} {found or '-':<9} reads {read}, pops {popped}, sure {counts_text(sure)}, "
                  f"unsure {passed[address].count(None)}, registers {in_registers}, "
                  f"declares {'?' if declared is None else declared}: {proto or '(no prototype)'}")
    return 0
