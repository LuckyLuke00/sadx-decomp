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
`...` are left out unless named.

Four more checks find a wrong prototype by other evidence, each with a verdict of its own:
  float-return     the declaration returns no float or double, but a caller uses st0 right after the call
  no-float-return  the declaration returns a float or double, but no caller uses st0 and the function leaves
                   no value on the x87 stack at any ret
  register         a function that is not static reads ecx or edx before it writes it, and its declared
                   convention does not pass that register
  width            a global that the tree declares as a scalar, but no read in the exe uses its width or kind
  task-taskwk      a pointer parameter declared `struct task *` or `struct taskwk *`, but every access through
                   it fits the other struct and some access does not fit the declared one
Needs capstone, so it runs in .venv.
"""

import collections
import functools
import re
from pathlib import Path
from typing import NamedTuple

import accesses
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


def returned_type(proto: str) -> str | None:
    """The type that a prototype returns, without its name and calling convention. None without a parameter list."""
    span = names.parameter_span(proto)
    return None if span is None else re.sub(r"[\w:~]+\s*$", "", facts.KEYWORD.sub("", proto[:span[0] - 1]))


def register_parameters(kinds: list[str], sizes: list[int | None], convention: str | None) -> list[int]:
    """The indexes of the parameters that travel in registers: the first of a __thiscall, and the first two of a
    __fastcall that take a dword or less and are no float. A parameter of unknown size counts as a dword."""
    if convention == "__thiscall":
        return [0][:len(kinds)]
    if convention == "__fastcall":
        return [n for n, kind in enumerate(kinds) if sizes[n] in (4, None) and kind != "float"][:2]
    return []


def parameter_bytes(proto: str, types: names.Types) -> int | None:
    """The stack bytes that a prototype's parameters take. None for a variadic, a parameter of unknown size and a
    struct returned by value, which may add a hidden pointer."""
    span = names.parameter_span(proto)
    if span is None:
        return None
    params = span[2]
    if is_struct(returned_type(proto), types):
        return None
    kinds = [kind for kind in map(names.without_parameter_name, params) if kind != "void"]
    if "..." in kinds:
        return None
    sizes = [stack_size(kind, types) for kind in kinds]
    if None in sizes:
        return None
    in_registers = register_parameters(kinds, sizes, facts.printed_keyword(proto))
    return sum(size for n, size in enumerate(sizes) if n not in in_registers)


QUALIFIED = re.compile(r"(\w+)::(~?\w+)\s*\(")  # the class and the name in a member function's definition
CLASS = re.compile(r"\b(?:class|struct)\s+(\w+)\s*(?::[^;{]*)?\{")  # a class or struct with a body
STATIC_CALL = re.compile(r"\bstatic\b[^;{}=]*?(~?\b\w+)\s*\(")  # the name in a static function's declaration


def members_of(sources: dict[str, str]) -> tuple[set[str], set[str]]:
    """The classes that the sources define, and the names that they declare static functions under."""
    return ({name for text in sources.values() for name in CLASS.findall(text)},
            {name for text in sources.values() for name in STATIC_CALL.findall(text)})


def is_method(proto: str, classes: set[str], statics: set[str]) -> bool:
    """Whether PROTO defines a member function of one of CLASSES that takes a this: one whose name no static
    declaration uses. A function of a namespace is no member."""
    found = QUALIFIED.search(proto)
    return found is not None and found.group(1) in classes and found.group(2) not in statics


def unexplained_registers(registers: int, proto: str, types: names.Types, method: bool) -> int:
    """The REGISTERS that a function reads at its entry that its declared parameters do not pass: ecx for the first
    parameter of a __thiscall, ecx and edx for the first two of a __fastcall (see register_parameters). A METHOD
    without another convention passes its this in ecx, which no declared parameter is."""
    if method and facts.printed_keyword(proto) in (None, "__thiscall"):
        return registers & ~x86.ECX
    span = names.parameter_span(proto)
    kinds = [] if span is None else [kind for kind in map(names.without_parameter_name, span[2]) if kind != "void"]
    count = len(register_parameters(kinds, [stack_size(kind, types) for kind in kinds], facts.printed_keyword(proto)))
    return registers & ~(x86.ECX * (count > 0) | x86.EDX * (count > 1))


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


# ---------------------------------------------------------------- float return values

# The x87 instructions by what they do to the stack of values.
X87_PUSHES = ("fld", "fld1", "fldz", "fldpi", "fldl2e", "fldl2t", "fldlg2", "fldln2", "fild", "fbld")
X87_KEEPS = ("fadd", "fsub", "fsubr", "fmul", "fdiv", "fdivr", "fiadd", "fisub", "fisubr", "fimul", "fidiv", "fidivr",
             "fst", "fist", "fxch", "fcom", "fucom", "ficom", "ftst", "fxam", "fchs", "fabs", "frndint", "fsqrt",
             "fsin", "fcos")
X87_CONTROL = ("fnstsw", "fstsw", "fnstcw", "fstcw", "fldcw", "fnclex", "fnop", "fwait", "wait")  # touch no value
# The library math functions that take their arguments on the stack and return a float.
FLOAT_LIBRARY = ("fabs", "atan2", "floor", "ceil", "asin", "acos", "atan", "sqrt", "sin", "cos", "tan", "exp", "log",
                 "log10", "pow", "fmod", "atof")
TWO_OPERANDS = ("_CIpow", "_CIatan2", "_CIfmod")  # the _CI helpers that take two values from the x87 stack
KEEPS_RESULT = ("__security_check_cookie",)  # the library functions that leave st0 as it was
UNKNOWN = -1  # the result of a call to something that is no game or library function


class Exit(NamedTuple):
    depth: int  # values on the x87 stack at the exit, -1 for the end of a path that this cannot follow
    result: int | None  # the game function whose float result may still sit in st0, UNKNOWN, or None for none


UNCLEAR = Exit(-1, None)


def is_x87(mnemonic: str) -> bool:
    return mnemonic.startswith("f") or mnemonic in X87_CONTROL


def x87_change(mnemonic: str) -> int | None:
    """How far an x87 instruction moves the top of the stack: up for a load, down for a store or an operation
    that pops. None for an instruction that this does not know."""
    if mnemonic in X87_PUSHES:
        return 1
    if mnemonic in X87_KEEPS or mnemonic in X87_CONTROL:
        return 0
    if mnemonic.endswith("pp"):
        return -2
    return -1 if mnemonic.endswith("p") else None


def library_change(name: str) -> int:
    """How far a call to the library function NAME moves the top of the x87 stack: _ftol2 takes the value, the
    two-operand _CI helpers take two and leave one, the other _CI helpers replace the top one, and a math function
    with its arguments on the stack returns a float."""
    if name.startswith("_ftol") or name in TWO_OPERANDS:
        return -1
    return 1 if name in FLOAT_LIBRARY else 0


def x87_exits(function: x86.Function, functions: dict[int, x86.Function], library: dict[int, str],
              found: dict[int, bool]) -> tuple[dict[int, int], set[Exit]] | None:
    """How many values the x87 stack holds before each instruction, and the Exit at each ret and each jump out of
    the function. FOUND says of game functions whether they leave a float in st0. A call to a game function that
    FOUND leaves out keeps its result open until an x87 instruction uses the stack: one that is no load and finds
    it empty uses the callee's float, since compiled code never reads an empty stack. A path ends in UNCLEAR at an
    x87 instruction that this does not know, and where a load or a non-empty stack meets an open result: the
    depths before it still hold. None when two paths reach one instruction with different depths, or no exit is
    reachable."""
    end = function.address + function.size
    by_address = {i.address: i for i in function.code}
    state = {function.address: (0, frozenset([None]))}  # per instruction: the depth and the open results
    pending = [function.address]
    exits = set()
    while pending:
        address = pending.pop()
        instruction = by_address[address]
        depth, results = state[address]
        mnemonic, target = instruction.mnemonic, instruction.target
        leaves = mnemonic == "call" or mnemonic == "jmp" and (
            target is not None and not function.address <= target < end or not function.successors[address])
        change = 0
        if is_x87(mnemonic) and mnemonic not in X87_CONTROL:
            change = x87_change(mnemonic)
            if change is None or results != {None} and (mnemonic in X87_PUSHES or depth):
                exits.add(UNCLEAR)
                continue
            if results != {None}:
                depth = 1
            results = frozenset([None])
        elif leaves and library.get(target) not in KEEPS_RESULT:
            result = None
            if target in library:
                change = library_change(library[target])
            elif target in found:
                change = int(found[target])
            else:
                result = target if target in functions else UNKNOWN
            results = frozenset([result])
        depth = max(depth + change, 0)
        if mnemonic == "ret" or leaves and mnemonic == "jmp":
            exits.update(Exit(depth, result) for result in results)
            continue
        for following in function.successors[address]:
            if following not in state:
                state[following] = (depth, results)
                pending.append(following)
            elif state[following][0] != depth:
                return None
            elif not results <= state[following][1]:
                state[following] = (depth, state[following][1] | results)
                pending.append(following)
    return ({address: depth for address, (depth, _) in state.items()}, exits) if exits else None


def exit_leaves(row: Exit, found: dict[int, bool]) -> bool | None:
    """Whether one exit leaves a float in st0: one value does, none does not, more is unclear. An open result adds
    the value that FOUND says its callee leaves, and is unclear when FOUND leaves the callee out. UNCLEAR is
    unclear."""
    if row == UNCLEAR or row.result is not None and row.result not in found:
        return None
    depth = row.depth + (row.result is not None and found[row.result])
    return depth == 1 if depth < 2 else None


def settle(flows: dict[int, tuple[dict[int, int], set[Exit]] | None], found: dict[int, bool]) -> None:
    """Add to FOUND each function of FLOWS whose exits all leave a float in st0 (True) or none do (False), until no
    more are added. A function stays out when its exits disagree or are unclear, or when its flow is None."""
    changed = True
    while changed:
        changed = False
        for address, flow in flows.items():
            if address in found or flow is None:
                continue
            answers = {exit_leaves(row, found) for row in flow[1]}
            if len(answers) == 1 and None not in answers:
                found[address] = answers.pop()
                changed = True


def leaves_float(functions: dict[int, x86.Function], library: dict[int, str]
                 ) -> tuple[dict[int, bool], dict[int, tuple[dict[int, int], set[Exit]] | None]]:
    """Whether each function leaves a float in st0 at every exit (True) or at none (False), and the x87_exits flow
    of each. Each round follows again the functions without an answer, with the answers so far, until a round adds
    none: an answer for a callee can clear a load after the call to it."""
    found, flows = {}, {}
    while True:
        for address, function in functions.items():
            if address not in found:
                flows[address] = x87_exits(function, functions, library, found)
        before = len(found)
        settle(flows, found)
        if len(found) == before:
            return found, flows


def reads_float_result(function: x86.Function, call: x86.Instruction) -> bool:
    """Whether the first x87 instruction after CALL uses st0 on some path from it: any that is no load. A call or a
    ret ends a path, and so does a load, which leaves the old st0 where it was."""
    by_address = {i.address: i for i in function.code}
    pending, seen = list(function.successors[call.address]), set()
    while pending:
        address = pending.pop()
        if address in seen:
            continue
        seen.add(address)
        mnemonic = by_address[address].mnemonic
        if is_x87(mnemonic) and mnemonic not in X87_CONTROL:
            if mnemonic not in X87_PUSHES:
                return True
        elif mnemonic not in ("call", "ret"):
            pending.extend(function.successors[address])
    return False


def float_callers(functions: dict[int, x86.Function],
                  flows: dict[int, tuple[dict[int, int], set[Exit]] | None]) -> dict[int, tuple[int, int]]:
    """For each game function that a call reaches: how many of the direct calls use st0 right after it returns,
    and how many calls there are. A call with a value on the x87 stack already, or in a function whose x87 stack
    this cannot follow, does not count as one that uses st0: the value may be the old one."""
    found = collections.defaultdict(lambda: [0, 0])
    for function in functions.values():
        flow = flows[function.address]
        for call in function.code:
            if call.mnemonic == "call" and call.target in functions:
                found[call.target][0] += (flow is not None and flow[0].get(call.address) == 0
                                          and reads_float_result(function, call))
                found[call.target][1] += 1
    return {address: tuple(counts) for address, counts in found.items()}


def float_verdict(returns_float: bool, leaves: bool | None, readers: int) -> str | None:
    """float-return, no-float-return or None, from whether the declaration returns a float or double, whether
    the function leaves a float in st0 (None when that is unclear) and how many calls use st0 after it. A
    declaration without a float is wrong when a call uses st0. One with a float is wrong when no call does and the
    function leaves nothing in st0."""
    if not returns_float and readers:
        return "float-return"
    if returns_float and leaves is False and not readers:
        return "no-float-return"
    return None


# ---------------------------------------------------------------- registers at the entry

def first_read(function: x86.Function, register: int) -> int | None:
    """The lowest address of an instruction that reads REGISTER before any write to it on some path from the entry.
    None when no instruction does, as when the function only passes the register on to a callee."""
    by_address = {i.address: i for i in function.code}
    pending, seen, found = [function.address], set(), []
    while pending:
        address = pending.pop()
        if address in seen:
            continue
        seen.add(address)
        instruction = by_address[address]
        if instruction.reads & register:
            found.append(address)
        elif not x86.changes(instruction) & register:
            pending.extend(function.successors[address])
    return min(found, default=None)


# ---------------------------------------------------------------- global widths

WIDTHS = {"byte": 1, "word": 2, "dword": 4, "qword": 8}
MEMORY_WIDTH = re.compile(r"\b(byte|word|dword|qword) ptr (?:\w+:)?\[")
STORES = ("mov", "fst", "fstp", "fist", "fistp", "fisttp")  # with a memory destination, they only write it


class Use(NamedTuple):
    offset: int  # from the start of the global, or of the struct that a pointer points to
    width: int  # bytes
    value: str  # "int" or "float", as accesses.value_kind says
    written: bool  # only written, not read


def global_uses(functions: dict[int, x86.Function], namer: dossier.Namer) -> dict[int, dict[Use, list[int]]]:
    """For each global that the namer knows: the kinds of access that the code makes to its bytes by an absolute
    or a table address, and the functions that make each, by address."""
    found = collections.defaultdict(lambda: collections.defaultdict(set))
    for function in functions.values():
        for instruction in function.code:
            operands = instruction.operands
            width = MEMORY_WIDTH.search(operands)
            if width is None or instruction.mnemonic == "lea":
                continue
            store = operands.startswith(width.group(0)) and (instruction.mnemonic in STORES
                                                             or instruction.mnemonic.startswith("set"))
            for operand in facts.memory_operands(operands):
                if operand.disp >= 0x400000 and (held := namer.holder(operand.disp)):
                    use = Use(operand.disp - held[0].address, WIDTHS[width.group(1)],
                              accesses.value_kind(instruction.mnemonic), store)
                    found[held[0].address][use].add(function.address)
    return {address: {use: sorted(users) for use, users in uses.items()} for address, uses in found.items()}


def declared_scalar(decl: str, name: str) -> tuple[int, str, bool] | None:
    """(bytes, "int" or "float", whether it is an array) of the scalar, or array of a scalar, that a declaration
    declares, a pointer counting as an int. None for any other type."""
    head, _, tail = decl.partition(name)
    head = re.sub(r"\b(?:static|extern|const|volatile)\b", "", head).strip()
    size = 4 if "*" in head else names.SCALAR_SIZES.get(head)
    return None if size is None else (size, "float" if head in ("float", "double") else "int", "[" in tail)


def use_fits(use: Use, size: int, value: str) -> bool:
    """Whether an access can be one to a scalar of SIZE bytes and kind VALUE: the same width and kind, an int move
    of a float, or a dword move of half a double or of a 64-bit int, which copies the bytes."""
    if use.width == size:
        return use.value == value or use.value == "int" and value == "float"
    return use.width == 4 and use.value == "int" and size == 8


def width_conflict(declared: tuple[int, str, bool], uses: dict[Use, list[int]]) -> bool:
    """Whether a global declared as DECLARED has reads, and none fits its width and kind. Writes do not count. A
    byte test of an int is a read at a narrower width, but an int that the code only ever reads that way is more
    likely a byte. Arrays of bytes and words are left out, as copies read them in dwords."""
    size, value, array = declared
    reads = [use for use in uses if not use.written]
    return bool(reads) and not (array and size < 4) and not any(use_fits(use, size, value) for use in reads)


def uses_text(uses: dict[Use, list[int]]) -> str:
    """The kinds of access, such as `byte int read, dword int written`."""
    words = {1: "byte", 2: "word", 4: "dword", 8: "qword"}
    return ", ".join(sorted({f"{words[use.width]} {use.value} {'written' if use.written else 'read'}" for use in uses}))


# ---------------------------------------------------------------- task against taskwk

STRUCT_PAIR = {"task": "taskwk", "taskwk": "task"}


class Leaf(NamedTuple):
    offset: int
    size: int
    value: str  # "int", "float" or "pointer"


def type_leaves(types: names.Types, kind: str, dims: list[int]) -> list[Leaf] | None:
    """The scalars of an array of KIND with the dimensions DIMS, from offset 0. None when the type's layout is
    unknown."""
    kind = re.sub(r"\b(?:const|volatile)\b", "", kind).strip()
    if "*" in kind or "(*" in kind:
        size, found = 4, [Leaf(0, 4, "pointer")]
    elif kind in names.SCALAR_SIZES:
        size = names.SCALAR_SIZES[kind]
        found = [Leaf(0, size, "float" if kind in ("float", "double") else "int")]
    elif kind.startswith("enum "):
        size, found = 4, [Leaf(0, 4, "int")]
    elif match := re.fullmatch(r"(?:struct|union)\s+(\w+)", kind):
        size, found = types.size.get(match.group(1)), struct_leaves(types, match.group(1))
    else:
        return None
    if size is None or found is None:
        return None
    count = 1
    for dim in dims:
        count *= dim
    return [leaf._replace(offset=n * size + leaf.offset) for n in range(count) for leaf in found]


@functools.cache
def struct_leaves(types: names.Types, name: str) -> list[Leaf] | None:
    """The scalars of a struct, with their offsets, from its member lines and the offsetof asserts of the types
    header. A union may sit inside it, but no struct. None for a bit field, a member that has no offset or a type
    of unknown layout."""
    block = types.blocks.get(name)
    if block is None:
        return None
    offsets = types.offsets(name)
    open_groups = [[]]  # the scalars of the struct and of each union that is open in it, from the group's start
    for line in (raw.strip() for raw in block.split("};", 1)[0].splitlines()[1:]):
        if re.fullmatch(r"union\s*\w*\s*\{", line):
            open_groups.append([])
            continue
        if close := re.fullmatch(r"\}\s*(\w+)\s*;", line):
            member, found = close.group(1), open_groups.pop()
        elif match := re.fullmatch(r"(.*?)(\w+)\s*((?:\[\w+\])*)\s*;|(.*)\(\*\s*(\w+)\)(.*);", line):
            member = match.group(2) or match.group(5)
            dims = [int(dim) if dim.isdigit() else None for dim in re.findall(r"\[(\w+)\]", match.group(3) or "")]
            found = None if None in dims else type_leaves(types, match.group(1) or "void *", dims)
        else:
            return None
        if found is None or len(open_groups) == 1 and member not in offsets:
            return None
        base = offsets[member] if len(open_groups) == 1 else 0
        open_groups[-1] += [leaf._replace(offset=base + leaf.offset) for leaf in found]
    return open_groups[0] if len(open_groups) == 1 else None


def fits_struct(leaves: list[Leaf], use: Use) -> bool:
    """Whether an access can be to a struct with these scalars. A float access must match a float scalar. An int
    access must lie over scalars, and a byte or a word must lie over no pointer: the compiler does not read part of
    a pointer."""
    if use.value == "float":
        return any(leaf.value == "float" and (leaf.offset, leaf.size) == (use.offset, use.width) for leaf in leaves)
    over = [leaf for leaf in leaves if leaf.offset < use.offset + use.width and use.offset < leaf.offset + leaf.size]
    covered = {at for leaf in over for at in range(leaf.offset, leaf.offset + leaf.size)}
    return all(at in covered for at in range(use.offset, use.offset + use.width)) \
        and (use.width >= 4 or not any(leaf.value == "pointer" for leaf in over))


def struct_confusion(declared: str, uses: set[Use], types: names.Types) -> str | None:
    """The other struct of the task and taskwk pair, when every access fits it and some access does not fit the
    declared one. None when the accesses fit both, or neither, or a layout is unknown."""
    mine, other = struct_leaves(types, declared), struct_leaves(types, STRUCT_PAIR[declared])
    if mine is None or other is None or not uses or all(fits_struct(mine, use) for use in uses):
        return None
    return STRUCT_PAIR[declared] if all(fits_struct(other, use) for use in uses) else None


def pointer_uses(function: x86.Function, decoder: x86.Decoder, sizes: dict[int, int], slot: int) -> set[Use] | None:
    """The accesses through the pointer that the function takes at [ebp + SLOT], or without a frame at the same
    place from the entry's esp: the offsets from the pointer with their width and kind. A copy of the pointer in
    a register or a frame slot counts. None when two paths reach an instruction with different esp, or when ebp
    is no frame."""
    framed = x86.has_frame(function.code)
    offset = {} if framed else facts.stack_offsets(function, decoder, sizes)
    if offset is None or not framed and any("ebp" in (m.base, m.index) for i in function.code
                                            for m in facts.memory_operands(i.operands)):
        return None
    by_address = {i.address: i for i in function.code}
    state = {function.address: frozenset([(("slot", slot), "pointer")])}
    pending = [function.address]
    found = set()
    while pending:
        address = pending.pop()
        instruction = by_address[address]
        if address in offset:  # write each [esp + n] as the [ebp + m] that the same slot has in a frame
            instruction = instruction._replace(operands=re.sub(
                r"\[esp(?: \+ (0x[0-9a-f]+|\d+))?\]",
                lambda m: f"[ebp + {offset[address] + int(m.group(1) or '0', 0) + 4}]", instruction.operands))
        width = MEMORY_WIDTH.search(instruction.operands)
        if width and instruction.mnemonic != "lea":
            for operand in facts.memory_operands(instruction.operands):
                if operand.index is None and operand.disp >= 0 \
                        and (x86.REGISTER.get(operand.base), "pointer") in state[address]:
                    found.add(Use(operand.disp, WIDTHS[width.group(1)], accesses.value_kind(instruction.mnemonic),
                                  False))
        after = facts.transfer(instruction, state[address], lambda _: None)
        for following in function.successors[address]:
            merged = state.get(following, frozenset()) | after
            if following not in state or merged != state[following]:
                state[following] = merged
                pending.append(following)
    return found


def pointer_slots(proto: str, types: names.Types) -> list[tuple[str, int]]:
    """For each parameter declared `struct task *` or `struct taskwk *`: the struct and the [ebp + n] slot of the
    parameter. Empty for a convention that passes parameters in registers. The list ends at a parameter of unknown
    size."""
    span = names.parameter_span(proto)
    if span is None or facts.printed_keyword(proto) in ("__fastcall", "__thiscall"):
        return []
    found, slot = [], 8
    for kind in (kind for kind in map(names.without_parameter_name, span[2]) if kind != "void"):
        if match := re.fullmatch(r"(?:const\s+)?struct\s+(task|taskwk)\s*\*\s*(?:const)?", kind.strip()):
            found.append((match.group(1), slot))
        size = stack_size(kind, types)
        if size is None:
            break
        slot += size
    return found


FLOAT_RETURN = re.compile(r"(?:(?:static|inline|__inline|extern|const|volatile)\s+)*(?:float|double)")
VERDICT_WIDTH = len("no-float-return")


def other_findings(address: int, function: x86.Function, proto: str, static: bool, method: bool,
                   leaves: dict[int, bool], readers: dict[int, tuple[int, int]], registers: int, types: names.Types,
                   decoder: x86.Decoder, sizes: dict[int, int]) -> list[tuple[str, str]]:
    """(verdict, text) for each of the float, register and task checks that finds this function's prototype wrong."""
    returned = returned_type(proto)
    if returned is None:
        return []
    found = []
    read, calls = readers.get(address, (0, 0))
    answer = {True: "yes", False: "no", None: "?"}[leaves.get(address)]
    kind = float_verdict(FLOAT_RETURN.fullmatch(returned.strip()) is not None, leaves.get(address), read)
    if kind:
        found.append((kind, f"st0 is used after {read} of {calls} calls, the function leaves a value in st0: {answer}"))
    lost = unexplained_registers(registers, proto, types, method) & (x86.ECX | x86.EDX)
    if lost and not static:
        reads = [f"{name} " + (f"at 0x{at:08x}" if (at := first_read(function, bit)) else "through a call")
                 for name, bit in facts.REGISTERS.items() if lost & bit]
        convention = facts.printed_keyword(proto) or "no convention"
        found.append(("register", f"reads {' and '.join(reads)}, but declares {convention}"))
    for declared, slot in pointer_slots(proto, types):
        uses = pointer_uses(function, decoder, sizes, slot)
        if uses and (other := struct_confusion(declared, uses, types)):
            odd = sorted(use for use in uses if not fits_struct(struct_leaves(types, declared), use))
            shown = ", ".join(f"+0x{use.offset:x} {use.width}-byte {use.value}" for use in odd[:3])
            found.append(("task-taskwk", f"parameter at [ebp + {slot}] is struct {declared}, but {shown} fit struct "
                                         f"{other} only"))
    return found


def width_findings(globals_: list[dossier.Global], uses: dict[int, dict[Use, list[int]]]) -> list[tuple[int, str]]:
    """(address, text) for each global that the tree declares as a scalar, and no read fits."""
    found = []
    for g in globals_:
        declared = declared_scalar(g.decl, g.name)
        if declared and g.address in uses and width_conflict(declared, uses[g.address]):
            users = sorted({user for found_by in uses[g.address].values() for user in found_by})
            size, value, array = declared
            found.append((g.address, f"declares {size}-byte {value}{' array' if array else ''}, reads and writes are "
                                     f"{uses_text(uses[g.address])}, in {' '.join(f'0x{u:08x}' for u in users[:3])}: "
                                     f"{g.decl}"))
    return found


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
    sources, before = names.read_sources(project.ROOT), names.previous(project.ROOT)
    tree = dossier.known_functions(None, sources, before)
    types = names.Types(project.ROOT / names.TYPES_H)
    classes, statics = members_of(sources)
    leaves, flows = leaves_float(functions, library)
    readers = float_callers(functions, flows)
    for address in addresses or sorted(functions.keys() - library.keys()):
        function = functions.get(address)
        if function is None or address in library:
            print(f"0x{address:08x} not a game function")
            continue
        proto = tree[address].proto if address in tree else ""
        method = is_method(proto, classes, statics)
        if (address in passed or addresses) and ("..." not in proto or addresses):
            sure = collections.Counter(size for size in passed[address] if size is not None)
            reads = arguments_read(function, decoder, sizes)
            pops = facts.exit_pops(function, decoder, sizes)
            unexplained = unexplained_registers(registers.get(address, 0), proto, types, method)
            declared = parameter_bytes(proto, types) if proto and not unexplained else None
            found = verdict(sure, reads, pops, declared)
            if found or addresses:
                read = "?" if reads is None else f"{reads.size}{' and an address' if reads.address else ''}"
                popped = "?" if pops is None else max(pops, default=0)
                in_registers = " ".join(name for name, bit in facts.REGISTERS.items() if unexplained & bit) or "none"
                print(f"0x{address:08x} {found or '-':<{VERDICT_WIDTH}} reads {read}, pops {popped}, "
                      f"sure {counts_text(sure)}, unsure {passed[address].count(None)}, registers {in_registers}, "
                      f"declares {'?' if declared is None else declared}: {proto or '(no prototype)'}")
        static = tree[address].static if address in tree else False
        for found, text in other_findings(address, function, proto, static, method, leaves, readers,
                                          registers.get(address, 0), types, decoder, sizes):
            print(f"0x{address:08x} {found:<{VERDICT_WIDTH}} {text}: {proto}")
    globals_ = dossier.known_globals(None, sources, before, types)
    uses = global_uses(functions, dossier.Namer(image, {}, sizes, library, globals_))
    for address, text in width_findings(globals_, uses):
        if not addresses or set(addresses) & {user for found_by in uses[address].values() for user in found_by}:
            print(f"0x{address:08x} {'width':<{VERDICT_WIDTH}} {text}")
    return 0
