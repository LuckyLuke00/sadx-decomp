"""The facts that `check.py dossier --facts` lists: what a function's assembly hides from a reader who writes C,
such as a register argument, a callee that pops its arguments, a global that holds a pointer, a type with no
body in the types header and a float constant that the source writes as a literal. A C++ member function
shows only as ecx and a pop. With `idioms`, the facts also name the compiler idioms that the code shows.

check.py passes fact_lines to dossier.show. Needs capstone, so it runs in .venv.
"""

import collections
import math
import re
import struct
from typing import NamedTuple

import floattells
import names
import pe
import x86
from dossier import Function, Global, Namer
from groups import calls, read_first

FACT_LIMIT = 3  # most items that a fact names
REGISTERS = {"eax": x86.EAX, "ecx": x86.ECX, "edx": x86.EDX, "ebx": x86.EBX, "esi": x86.ESI, "edi": x86.EDI}
READ_ONLY = ("cmp", "test", "push", "call", "jmp", "fld", "fild", "fcom", "fcomp", "fadd", "fsub", "fmul", "fdiv")
POINTED_TAG = re.compile(r"\b(struct|union)\s+(\w+)\s*\*")  # a struct or union reached through a pointer
KEYWORD = re.compile(r"\b(__fastcall|__stdcall|__cdecl|__thiscall|WINAPI|CALLBACK|APIENTRY|PASCAL)\b")
STDCALL_NAMES = ("WINAPI", "CALLBACK", "APIENTRY", "PASCAL")
CPP_FILES = (".cpp", ".cc", ".cxx")
INTEGER_TYPE = re.compile(r"(?:extern\s+|static\s+)*(?:const\s+|volatile\s+)*(?:unsigned\s+|signed\s+)?(?:int|long)\s*")
BASE_OFFSETS = range(-0x100, 0x10000)  # a displacement outside this is a table address, not a member offset
OPPOSITE = {"je": "jne", "jne": "je", "jp": "jnp", "jnp": "jp"}
# What `test ah, M` and the jump that skips the block say about the block, from the status bits C0 0x01, C2 0x04
# and C3 0x40. 0x44 comes after fucompp.
COMPARE_ROWS = {(0x41, "jne"): "st0 > other", (0x01, "jne"): "st0 >= other", (0x05, "jp"): "st0 < other",
                (0x41, "jp"): "st0 <= other", (0x44, "jp"): "st0 == other", (0x44, "jnp"): "st0 != other"}
TWO_TO_32 = {4: struct.pack("<f", 4294967296.0), 8: struct.pack("<d", 4294967296.0)}
LEFT_OPERATORS = {"faddp": "+", "fmulp": "*", "fsubrp": "-", "fdivrp": "/"}
CHAIN_STEPS = ("sub", "dec", "add", "inc")  # a switch chain read from its middle has one of these before it
CHAIN_NEUTRAL = ("push", "pop", "mov", "movsx", "movzx", "lea")  # may sit inside a switch chain, as x87 ops may
CHAIN_GAP = 6  # most such instructions between a step and its jump, or a je and the next step
CAST_REACH = 6  # how far before the `jns` of an unsigned cast the `fild` may sit
TABLE_JUMP_REACH = 3  # how many instructions after a switch's range check may hold the table jump
CONVERSION_REACH = 13  # how many instructions after `fnstcw` may hold the rest of a float to unsigned conversion
TRUNCATE_BITS = ("eax, 0xc00", "ah, 0xc")  # the `or` that sets the rounding mode of the control word to truncate
# The unsigned type of a float converted with `fistp`, from the width of the store and of the first read of its slot.
UNSIGNED_TYPES = {("dword", "byte"): "unsigned char", ("dword", "word"): "unsigned short",
                  ("qword", "dword"): "unsigned int"}


class Memory(NamedTuple):
    base: str | None
    index: str | None
    scale: int
    disp: int


def memory_operands(operands: str) -> list[Memory]:
    """The [base + index*scale + disp] operands of an instruction's text."""
    found = []
    for text in re.findall(r"\[([^\]]*)\]", operands):
        base = index = None
        scale, disp = 1, 0
        for term in text.replace(" - ", " + -").split(" + "):
            if "*" in term:
                index, scale = term.split("*")[0], int(term.split("*")[1])
            elif term.isalpha():
                base, index = (term, index) if base is None else (base, term)
            else:
                disp += int(term, 0)
        found.append(Memory(base, index, scale, disp))
    return found


def memory_width(operands: str) -> int:
    """The bytes that a `qword ptr` or `dword ptr` operand reads, or 0 for any other operand."""
    return 8 if "qword ptr" in operands else 4 if "dword ptr" in operands else 0


def pops(function: x86.Function) -> set[int]:
    """The bytes that its rets pop."""
    return {int(i.operands, 0) for i in function.code if i.mnemonic == "ret" and i.operands}


def stack_change(instruction: x86.Instruction, decoder: x86.Decoder, sizes: dict[int, int]) -> int | None:
    """How far an instruction moves esp, or None when it sets esp to a value that isn't known."""
    mnemonic, operands = instruction.mnemonic, instruction.operands
    if operands.startswith("esp,"):
        number = x86.number(operands.split(", ")[1])
        return {"sub": -number, "add": number}.get(mnemonic) if number is not None else None
    if mnemonic == "leave":
        return None
    if mnemonic in ("push", "pushfd", "pushal"):
        return -32 if mnemonic == "pushal" else -4
    if mnemonic in ("pop", "popfd", "popal"):
        return 32 if mnemonic == "popal" else 4
    if mnemonic == "call" and instruction.target in sizes:  # a callee that pops its arguments
        return max(pops(decoder.function(instruction.target, sizes[instruction.target], 0)), default=0)
    return 0


def stack_offsets(function: x86.Function, decoder: x86.Decoder, sizes: dict[int, int]) -> dict[int, int] | None:
    """esp minus its value at the entry, before each instruction. An instruction that only a path through an
    unknown esp change reaches has none. None when two paths reach one instruction with different offsets."""
    by_address = {i.address: i for i in function.code}
    offset = {function.address: 0}
    pending = [function.address]
    while pending:
        address = pending.pop()
        change = stack_change(by_address[address], decoder, sizes)
        if change is None:
            continue
        for following in function.successors[address]:
            if following not in offset:
                offset[following] = offset[address] + change
                pending.append(following)
            elif offset[following] != offset[address] + change:
                return None
    return offset


def may_read_stack_arguments(function: x86.Function, decoder: x86.Decoder, sizes: dict[int, int]) -> bool:
    """Whether the code reads arguments from the stack. True also when a frameless function moves esp in a
    way that this does not follow."""
    if x86.has_frame(function.code):
        return any(m.base == "ebp" and m.disp >= 8 for i in function.code for m in memory_operands(i.operands))
    offset = stack_offsets(function, decoder, sizes)
    if offset is None or len(offset) < len(function.code):
        return True
    if any(i.mnemonic == "ret" and offset[i.address] != 0 for i in function.code):
        return True
    return any(m.base == "esp" and m.disp + offset[i.address] >= 4
               for i in function.code for m in memory_operands(i.operands))


def unknown_jump(function: x86.Function) -> bool:
    """Whether a jmp goes where no address in the code says, such as `jmp edx`. A switch table is known."""
    return any(i.mnemonic == "jmp" and i.target is None and not x86.SWITCH.search(i.operands) for i in function.code)


def exit_pops(function: x86.Function, decoder: x86.Decoder, sizes: dict[int, int], depth: int = 3) -> set[int] | None:
    """The bytes that the function pops when it returns, through a ret of its own or a jump to another
    function. None when a jump goes where this can't follow, such as `jmp edx`. A switch table is no exit."""
    found = pops(function)
    if unknown_jump(function):
        return None
    for jump in (i for i in calls(function) if i.mnemonic != "call"):
        if jump.target not in sizes or not depth:
            return None
        further = exit_pops(decoder.function(jump.target, sizes[jump.target], 0), decoder, sizes, depth - 1)
        if further is None:
            return None
        found |= further
    return found


def printed_keyword(proto: str) -> str | None:
    """The calling convention that a prototype's head names, as __fastcall, __stdcall, __cdecl or __thiscall."""
    found = KEYWORD.search(proto.partition("(")[0])
    return None if not found else "__stdcall" if found.group(1) in STDCALL_NAMES else found.group(1)


def amount(number: int) -> str:
    """A byte count as the disassembly prints it."""
    return f"0x{number:x}" if number > 9 else str(number)


def member_function_fact(function: x86.Function, f: Function, pop: int) -> str:
    """The text for a function that reads ecx and ends with `ret POP`: a C++ member function, whose struct takes
    the class in its name or an address placeholder."""
    struct_name = ("The struct's name is the part of the function's name before the last `::`."
                   if "::" in f.name else
                   f"Name the struct `Unk_{function.address:08x}`, a placeholder until its real name is known.")
    return (f"The function reads ecx and ends with `ret {amount(pop)}`, so it is a C++ member function: ecx "
            f"holds `this`, and the {amount(pop)} bytes on the stack are its parameters. Declare a struct with "
            "the fields it reads through `this` and the function as its member, then define the function as "
            f"that member. {struct_name}")


def convention_fact(function: x86.Function, flags: str, f: Function, decoder: x86.Decoder,
                    sizes: dict[int, int]) -> str | None:
    """What the registers and the ret say about the calling convention. None when the code shows none, when
    it reads a register that no keyword passes (the register-argument cluster), when a jump out hides what
    is popped, or when the compiler may have picked the registers: optimized code in a C file or in a file
    that is not known, and optimized code whose printed prototype names no such keyword. Only a `/Od`
    function gets a keyword against its printed prototype, because that code never picks registers itself. A
    /Od function in a C++ file that reads ecx and ends with `ret N` gets the member function fact instead."""
    first = read_first(function, {})
    registers = first & (x86.ECX | x86.EDX)
    popped = exit_pops(function, decoder, sizes)
    if popped is None or first & ~registers or len(popped) > 1 or not (registers or popped):
        return None
    pop = max(popped, default=0)
    debug = "/Od" in flags
    if debug and registers == x86.ECX and pop:  # /Od keeps `this` in ecx only for a member function
        return member_function_fact(function, f, pop) if f.file.endswith(CPP_FILES) else None
    keyword = "__stdcall" if not registers else "__fastcall"
    printed = printed_keyword(f.proto)
    if not debug and ((registers and not f.file.endswith(CPP_FILES)) or (f.proto and printed != keyword)):
        return None
    if registers and not pop and may_read_stack_arguments(function, decoder, sizes):
        return None  # a register and a stack argument with a plain ret: only a static function does that
    declare = f"Keep `{keyword}`." if printed == keyword else f"Declare the function `{keyword}`."
    change = (" The printed prototype differs, so change it to fit the code and keep its name."
              if f.proto and printed != keyword else "")
    if not registers:
        return (f"The function ends with `ret {amount(pop)}`, so it pops {amount(pop)} bytes of parameters. "
                f"{declare}{change}")
    lead = {x86.ECX: "The first parameter arrives in ecx.",
            x86.EDX: "The first parameter is unused and the second arrives in edx.",
            x86.ECX | x86.EDX: "The first two parameters arrive in ecx and edx."}[registers]
    stack = f" The stack holds the other {amount(pop)} bytes of parameters." if pop else ""
    if registers == x86.ECX and pop:
        stack += " If the first of them is an integer or a pointer, put an unused second parameter before it."
    member = "::" in f.name or f.name.startswith("?")
    this = "" if member or not registers & x86.ECX else " Do not use `__thiscall`: it is only for class members."
    return f"{lead}{stack} {declare}{change}{this}"


def frame_slot(operand: str) -> tuple[str, int] | None:
    """("slot", disp) for an operand at [ebp + disp]."""
    found = memory_operands(operand) if "[ebp" in operand else []
    return ("slot", found[0].disp) if found and found[0].base == "ebp" and found[0].index is None else None


def transfer(instruction: x86.Instruction, before: frozenset, holder) -> frozenset:
    """The (place, global) pairs after an instruction. A place is a register bit or a frame slot. holder
    maps an address to the known global that holds it, and the offset into it."""
    mnemonic = instruction.mnemonic
    written = x86.changes(instruction)
    destination, _, source = instruction.operands.partition(", ")
    slot = frame_slot(destination) if mnemonic not in READ_ONLY else None
    after = {(place, key) for place, key in before
             if not (isinstance(place, int) and place & written)
             and not (slot and isinstance(place, tuple) and abs(place[1] - slot[1]) < 4)}
    if mnemonic != "mov":
        return frozenset(after)
    place = REGISTERS.get(source) or (frame_slot(source) if source.startswith("dword") else None)
    keys = {key for p, key in before if p == place} if place else set()
    if (m := x86.SLOT.fullmatch(source)) and (held := holder(int(m.group(1), 16))):
        keys.add(held)
    target = REGISTERS.get(destination) or (slot if destination.startswith("dword") else None)
    return frozenset(after | {(target, key) for key in keys} if target else after)


def pointer_globals(function: x86.Function, holder) -> dict[tuple[Global, int], set[int]]:
    """For each global that the code loads into a register, or through a frame slot, and then uses as a
    base address: (the global, the offset into it) -> the offsets from the base that the code uses."""
    by_address = {i.address: i for i in function.code}
    state = {function.address: frozenset()}  # the (place, global) pairs that may hold before each instruction
    pending = [function.address]
    found = collections.defaultdict(set)
    while pending:
        address = pending.pop()
        instruction = by_address[address]
        for m in memory_operands(instruction.operands) if instruction.mnemonic != "lea" else []:
            if m.base in REGISTERS and (m.index is None or m.scale > 1) and m.disp in BASE_OFFSETS:
                for place, key in state[address]:
                    if place == REGISTERS[m.base]:
                        found[key].add(m.disp)
        after = transfer(instruction, state[address], holder)
        for following in function.successors[address]:
            merged = state.get(following, frozenset()) | after
            if following not in state or merged != state[following]:
                state[following] = merged
                pending.append(following)
    return found


def listed(items: list[str]) -> str:
    """ITEMS as `a, b and c`, or the first FACT_LIMIT of them and `and more`."""
    if len(items) > FACT_LIMIT:
        return f"{', '.join(items[:FACT_LIMIT])} and more"
    if len(items) == 1:
        return items[0]
    return f"{', '.join(items[:-1])} and {items[-1]}"


def offsets_text(offsets: set[int]) -> str:
    return listed([f"0x{o:x}" if o >= 0 else f"-0x{-o:x}" for o in sorted(offsets)])


def pointer_facts(function: x86.Function, namer: Namer) -> list[str]:
    """One line for each global that the code loads and then uses as a base address, when its declaration
    doesn't say pointer: an integer, or a 4-byte data address that has no name here. The globals with the
    most offsets come first."""
    image = namer.image

    def holder(address: int) -> tuple[Global, int] | None:
        if found := namer.holder(address):
            return found
        if image.contains(address) and not image.is_code(address) and address not in image.import_slots:
            return Global(address, 4, "", ""), 0
        return None

    found = []
    for (g, offset), used in pointer_globals(function, holder).items():
        before_name = g.decl.partition(g.name)[0] if g.name else ""
        if offset or g.size != 4 or g.name and not INTEGER_TYPE.fullmatch(before_name):
            continue  # a struct, an array or a pointer already says what it holds
        shown = f"offset{'s' if len(used) > 1 else ''} {offsets_text(used)}"
        if g.name:
            first = min(used, key=lambda o: (o == 0, o < 0, abs(o)))
            example = f"(char *){g.name}" + (f" {'-' if first < 0 else '+'} 0x{abs(first):x}" if first else "")
            line = (f"{g.name} holds a pointer. The code uses it at {shown}. Keep its declaration and cast its "
                    f"value, as in `{example}`.")
        else:
            line = (f"DAT_{g.address:08x} (address 0x{g.address:x}) holds a pointer. The code uses it at {shown}. "
                    "Declare it as a pointer and add the offsets to its value, not to its address.")
        found.append((-len(used), g.address, line))
    return [line for _, _, line in sorted(found)[:FACT_LIMIT]]


def bodiless_fact(texts: list[str], types: names.Types) -> str | None:
    """The line about the struct and union types that the function reaches through a pointer and the types
    header gives no body."""
    missing = list(dict.fromkeys(f"{kind} {name}" for text in texts for kind, name in POINTED_TAG.findall(text)
                                 if name not in types.blocks))
    if not missing:
        return None
    return (f"{listed(missing)} {'has' if len(missing) == 1 else 'have'} no members and no known size. "
            "Cast a pointer to `char *` before you add to it or index it. "
            "Read a member with a byte offset and its type, as in `*(int *)((char *)p + 0x10)`.")


def float_literal(raw: bytes) -> str | None:
    """The shortest C literal for the 4 bytes of a float or the 8 bytes of a double, or None for an infinity or a
    NaN, which have no literal."""
    double = len(raw) == 8
    value = struct.unpack("<d" if double else "<f", raw)[0]
    if not math.isfinite(value):
        return None
    text = repr(value)
    if not double:
        for digits in range(1, 10):
            shortest = float(f"{value:.{digits}g}")
            if struct.pack("<f", shortest) == raw:
                text = repr(shortest)
                break
    return text if double else text + "f"


def constant_fact(function: x86.Function, namer: Namer, skip: dict[int, int]) -> str | None:
    """The line about the float and double constants that the code loads from read-only data and that have no
    name here. The compiler puts a literal of the source there, so a global at that address breaks the match.
    SKIP holds the constants that a cast makes, which the source does not write."""
    literals = {}
    for instruction in function.code:
        width = memory_width(instruction.operands)
        if not instruction.mnemonic.startswith("f") or instruction.mnemonic.startswith("fi") or not width:
            continue  # fild, fiadd and the like read integers
        for m in memory_operands(instruction.operands):
            if m.base or m.index or m.disp in skip or namer.holder(m.disp) or not namer.image.is_read_only_data(m.disp):
                continue
            literal = float_literal(namer.image.read(m.disp, width))
            if literal:
                literals[m.disp] = literal
    if not literals:
        return None
    shown = listed([f"{text} (at 0x{address:x})" for address, text in sorted(literals.items())])
    return (f"The code loads the constants {shown} from read-only data. Write each one as that literal. "
            "Do not declare a global for its address: that breaks the match.")


def float_compare_fact(code: list[x86.Instruction]) -> str | None:
    """How `fnstsw ax`, `test ah, M` and a jump after a float compare map to a C operator, for the pairs the
    code has. A jump into the block uses the opposite jump of the row that it skips the block with."""
    pairs, zero = set(), False
    for compare, status, test, jump in zip(code, code[1:], code[2:], code[3:]):
        if (compare.mnemonic not in floattells.COMPARES or (status.mnemonic, status.operands) != ("fnstsw", "ax")
                or test.mnemonic != "test" or not test.operands.startswith("ah, ") or jump.mnemonic not in OPPOSITE):
            continue
        mask = x86.number(test.operands.removeprefix("ah, "))
        key = next((k for k in ((mask, jump.mnemonic), (mask, OPPOSITE[jump.mnemonic])) if k in COMPARE_ROWS), None)
        if key:
            pairs.add(key)
            zero = zero or compare.mnemonic == "ftst"
    rows = [f"`test ah, {amount(mask)}` with `{jump}` runs it when {COMPARE_ROWS[mask, jump]}."
            for mask, jump in sorted(pairs)]
    if not rows:
        return None
    return ("A float compare ends in `fnstsw ax`, `test ah, M` and a jump. M and the jump pick the C operator. "
            "st0 is the top of the x87 stack. The other side is the `fcomp` operand, or the value pushed first "
            "before `fcompp`." + (" After `ftst` the other side is 0.0." if zero else "") +
            f" A jump that skips the block means the block runs as follows. {' '.join(rows)} "
            "A jump into the block uses the opposite jump: swap `je` and `jne`, and swap `jp` and `jnp`, then "
            "read the same rows. A constant can be st0 (`fld` of a constant, `fldz`, `fld1`). Then flip the "
            "operator so the variable is on the left.")


def unsigned_float_constants(code: list[x86.Instruction], image: pe.Image) -> dict[int, int]:
    """The 4294967296.0 constants of `fild`, `jns`, `fadd` (an unsigned int to float cast): address: width."""
    found = {}
    for n, add in enumerate(code[1:], 1):
        if add.mnemonic != "fadd" or code[n - 1].mnemonic != "jns":
            continue
        width, memory = memory_width(add.operands), memory_operands(add.operands)
        if not width or len(memory) != 1:
            continue
        m = memory[0]
        if (not m.base and not m.index and image.read(m.disp, width) == TWO_TO_32[width]
                and any(i.mnemonic == "fild" for i in code[max(0, n - CAST_REACH):n - 1])):
            found[m.disp] = width
    return found


def unsigned_float_fact(constants: dict[int, int]) -> str | None:
    """The cast that the `fild`, `jns`, `fadd` constants of unsigned_float_constants stand for."""
    if not constants:
        return None
    casts = {4: "`(float)(unsigned int)x`", 8: "`(double)(unsigned int)x` where the `fadd` reads a qword"}
    shown = ", or ".join(casts[width] for width in sorted(set(constants.values())))
    return ("`fild`, then `jns` over `fadd` of 4294967296.0, converts an unsigned 32-bit value to a float. "
            f"Write {shown}. Do not write the `if (x < 0)` fix-up. The Ghidra draft shows it, and it does not "
            "match.")


def float_argument_fact(code: list[x86.Instruction]) -> str | None:
    """/Od: `fstp [ebp - N]`, `fld [ebp - N]`, `push ecx`, `fstp [esp]` is a computed float argument."""
    slots = [store.operands.removeprefix("dword ptr ")
             for store, load, push, argument in zip(code, code[1:], code[2:], code[3:])
             if (store.mnemonic, load.mnemonic, push.mnemonic, argument.mnemonic) == ("fstp", "fld", "push", "fstp")
             and store.operands == load.operands and store.operands.startswith("dword ptr [ebp - ")
             and push.operands == "ecx" and argument.operands == "dword ptr [esp]"]
    if not slots:
        return None
    slots = list(dict.fromkeys(slots))
    return (f"`fstp`, `fld`, `push ecx` and `fstp [esp]` through {'the slot' if len(slots) == 1 else 'the slots'} "
            f"{listed(slots)} pass a computed float as a call argument. The compiler makes the slot itself. "
            "Write the expression inside the call and declare no local for it. A `(float)` cast of a double "
            "expression gives the same code. A float local that you pass gives `push ecx` before `fld [local]`, "
            "not after it. Each such argument gets its own slot below all your locals. `sub esp` counts these slots.")


def last_write(code: list[x86.Instruction], n: int, bit: int) -> x86.Instruction | None:
    """The last instruction before code[N] that may change the register BIT, in address order."""
    return next((i for i in reversed(code[:n]) if x86.changes(i) & bit), None)


def switch_step(code: list[x86.Instruction], n: int) -> tuple[str, int] | None:
    """(register, amount) when code[N] is `sub R, K`, `dec R`, or `sub R, R2` where `xor R2, R2` last set R2, the
    form that the compiler gives a case 0 when it keeps a zero in a register."""
    instruction = code[n]
    register, _, operand = instruction.operands.partition(", ")
    if register not in REGISTERS:
        return None
    if instruction.mnemonic == "dec" and not operand:
        return register, 1
    if instruction.mnemonic != "sub":
        return None
    if operand in REGISTERS:
        zeroing = last_write(code, n, REGISTERS[operand])
        is_zero = zeroing is not None and (zeroing.mnemonic, zeroing.operands) == ("xor", f"{operand}, {operand}")
        return (register, 0) if is_zero else None
    gap = x86.number(operand)
    return (register, gap) if gap is not None else None


def skip_neutral(code: list[x86.Instruction], n: int, bit: int) -> int | None:
    """The index of the first instruction from N on that is not a move, push, pop or x87 op that leaves the
    register BIT and the flags alone, when at most CHAIN_GAP such instructions come first."""
    for k in range(n, min(n + CHAIN_GAP + 1, len(code))):
        mnemonic = code[k].mnemonic
        keeps_flags = mnemonic in CHAIN_NEUTRAL or (mnemonic.startswith("f") and "comi" not in mnemonic)
        if not keeps_flags or x86.changes(code[k]) & bit:
            return k
    return None


def chain_cases(code: list[x86.Instruction], n: int) -> list[int]:
    """The case values of the switch chain whose first step is code[N]: the running sums of the `sub R, K` and
    `dec R` steps on one register, each with a je or jne. A jne ends the chain. A CHAIN_STEPS instruction must
    not be the last to set R, so a chain is never read from its middle."""
    first = switch_step(code, n)
    if not first:
        return []
    register, bit = first[0], REGISTERS[first[0]]
    before = last_write(code, n, bit)
    if before is not None and before.mnemonic in CHAIN_STEPS:
        return []
    cases = []
    while n is not None and (step := switch_step(code, n)) and step[0] == register:
        jump = skip_neutral(code, n + 1, bit)
        if jump is None or code[jump].mnemonic not in ("je", "jne"):
            break
        cases.append((cases[-1] if cases else 0) + step[1])
        if code[jump].mnemonic == "jne":
            break
        n = skip_neutral(code, jump + 1, bit)
    return cases


def switch_chain_fact(code: list[x86.Instruction]) -> str | None:
    """Optimized code: two or more `sub R, K` or `dec R` steps on one register, each with je or jne, are a switch
    whose case values are the running sums."""
    chains = []
    for n, instruction in enumerate(code):
        cases = chain_cases(code, n)
        if len(cases) >= 2:
            chains.append(f"The chain at 0x{instruction.address:x} is cases {', '.join(map(str, cases))}.")
    if not chains:
        return None
    return ("`sub R, K` and `dec R` steps, each followed by `je` or `jne`, are one `switch`, not an `if` chain. "
            "Each step subtracts the gap from the previous case value, so the case values are the running sums. "
            f"{' '.join(chains[:FACT_LIMIT])} A last `jne` goes past the switch when there is no `default`. A last "
            "`je` means the `default` body follows the chain. A `movsx` or `movzx` before the chain shows the "
            "width and sign of the switched value.")


def slot_cases(code: list[x86.Instruction], n: int, slot: str) -> tuple[list[int], set[int | None], int]:
    """The constants and the jump targets of the `cmp SLOT, K` and `je` pairs from code[N] on, and the index
    after the last pair."""
    cases, targets, k = [], set(), n
    while k + 1 < len(code) and code[k].mnemonic == "cmp" and code[k + 1].mnemonic == "je":
        place, _, immediate = code[k].operands.partition(", ")
        number = x86.number(immediate)
        if place != slot or number is None:
            break
        cases.append(number)
        targets.add(code[k + 1].target)
        k += 2
    return cases, targets, k


def compare_chain_fact(code: list[x86.Instruction]) -> str | None:
    """/Od: a stack slot that one `mov` fills and that only the `cmp [ebp - N], K` and `je` pairs after it read,
    ended by a `jmp`, is the hidden copy of a switch. A dword slot needs two pairs that jump to different places,
    since an `||` test gives pairs that jump to one place. A word slot is never one: a short switch widens to a
    dword."""
    chains, byte = [], False
    for n, store in enumerate(code):
        slot, _, source = store.operands.partition(", ")
        if store.mnemonic != "mov" or "[ebp - " not in slot or source not in x86.REGISTER or slot.startswith("word"):
            continue
        cases, targets, k = slot_cases(code, n + 1, slot)
        is_byte = slot.startswith("byte")
        if not cases or k >= len(code) or code[k].mnemonic != "jmp" or not (is_byte or len(targets) >= 2):
            continue
        bracket = slot[slot.index("["):]
        if sum(bracket in i.operands for i in code) != len(cases) + 1:
            continue  # the slot is read elsewhere too, so it is a real local
        chains.append(f"At 0x{code[n + 1].address:x}, `cmp {slot}` is case{'s' if len(cases) > 1 else ''} "
                      f"{', '.join(map(str, cases))}.")
        byte = byte or is_byte
    if not chains:
        return None
    return ("The `cmp [ebp - N], K` and `je` pairs on one stack slot, ended by a `jmp`, are one `switch`. "
            f"{' '.join(chains[:FACT_LIMIT])} The slot is a hidden copy of the value that the compiler makes. Write "
            "`switch (value)` on the field, call or local itself, and declare no local for the slot. When the "
            "value stored to the slot comes from another slot, that one is a real local: keep it. The `cmp` "
            "constants run in ascending order, and the case bodies follow in source order. Each `je` goes to its "
            "case body. The last `jmp` goes to `default`, or past the switch."
            + (" A `byte ptr` slot holds a one-byte value, and its sign does not show." if byte else ""))


def is_range_check(load: x86.Instruction, step: x86.Instruction, store: x86.Instruction, compare: x86.Instruction,
                   above: x86.Instruction) -> bool:
    """Whether five instructions are `mov R, [slot]`, `sub R, K` or `add R, K`, `mov [slot], R`, `cmp [slot], M`
    and `ja`, on one frame slot."""
    register, _, slot = load.operands.partition(", ")
    name, _, immediate = step.operands.partition(", ")
    return ((load.mnemonic, store.mnemonic, compare.mnemonic, above.mnemonic) == ("mov", "mov", "cmp", "ja")
            and slot.startswith("dword ptr [ebp - ") and register in REGISTERS and step.mnemonic in ("sub", "add")
            and name == register and x86.number(immediate) is not None and store.operands == f"{slot}, {register}"
            and compare.operands.startswith(f"{slot}, "))


def switch_base_fact(code: list[x86.Instruction]) -> str | None:
    """/Od: `mov R, [slot]`, `sub R, K`, `mov [slot], R`, `cmp [slot], M`, `ja` and a table jump is the range
    check of a switch whose cases start at K."""
    for n in range(len(code) - 4):
        load, step, store, compare, above = code[n:n + 5]
        if not is_range_check(load, step, store, compare, above):
            continue
        if not any(i.mnemonic == "jmp" and x86.SWITCH.search(i.operands) for i in code[n + 5:n + 5 + TABLE_JUMP_REACH]):
            continue
        register, _, slot = load.operands.partition(", ")
        immediate = step.operands.partition(", ")[2]
        shown = slot.removeprefix("dword ptr ")
        sign, side = ("-", "plus") if step.mnemonic == "sub" else ("+", "minus")
        return (f"`{step.mnemonic} {register}, {immediate}`, `mov {shown}, {register}` and "
                f"`cmp {shown}, {compare.operands.partition(', ')[2]}` form the range check of a `switch`. The "
                f"compiler adds the `{step.mnemonic}` and the slot {shown} itself. Write `switch (x)` with no "
                f"`{step.mnemonic}` and no local for `x {sign} {immediate}`. The case values are the table index "
                f"{side} {immediate}. Ignore that step in the draft, and draft cases that start at 0. `sub esp` "
                f"counts the slot {shown}.")
    return None


def bit_clear_fact(code: list[x86.Instruction]) -> str | None:
    """/Od: `and R, 0xffff....` after a load into R clears bits, and only a `~` mask gives that immediate."""
    sites = []
    for load, clear in zip(code, code[1:]):
        register, _, immediate = clear.operands.partition(", ")
        value = x86.number(immediate)
        if (clear.mnemonic == "and" and register in REGISTERS and value is not None
                and 0xffff0000 <= value < 0xffffffff and load.mnemonic in ("movsx", "movzx", "mov")
                and load.operands.startswith(f"{register}, ")):
            sites.append((clear.address, register, value))
    if not sites:
        return None
    shown = listed([f"`and {r}, 0x{v:x}` at 0x{a:x} is `& ~0x{~v & 0xffffffff:x}`" for a, r, v in sites])
    _, register, value = sites[0]
    return (f"{shown}. Write the mask with `~`. A 16-bit literal such as `0x{value & 0xffff:x}` gives "
            f"`and {register}, 0x{value & 0xffff:x}`, a different immediate, and does not match.")


def left_constant_fact(code: list[x86.Instruction]) -> str | None:
    """/Od: `fld1` or `fldz` right before a popping `faddp`, `fmulp`, `fsubrp` or `fdivrp` is a left constant."""
    sites = [f"`{'1.0f' if load.mnemonic == 'fld1' else '0.0f'} {LEFT_OPERATORS[use.mnemonic]} x` at "
             f"0x{load.address:x}" for load, use in zip(code, code[1:])
             if load.mnemonic in ("fld1", "fldz") and use.mnemonic in LEFT_OPERATORS and use.operands == "st(1)"]
    if not sites:
        return None
    return ("`fld1` or `fldz` right before `faddp`, `fmulp`, `fsubrp` or `fdivrp` loads a constant that is the "
            f"left operand. Write {listed(sites)}. `x + 1.0f` compiles to `fadd` with a memory constant instead. "
            "The Ghidra draft may show the constant on the right.")


def minus_one_fact(code: list[x86.Instruction]) -> str | None:
    """/Od: `imul R, S, -1` is `x * -1`, which `-x` does not give."""
    sites = [i for i in code if i.mnemonic == "imul" and i.operands.count(", ") == 2 and i.operands.endswith(", -1")]
    if not sites:
        return None
    shown = listed([f"`imul {i.operands}` at 0x{i.address:x}" for i in sites])
    return (f"{shown} {'is' if len(sites) == 1 else 'are'} `x * -1`. "
            "Write the multiply by -1. Do not write `-x`, which gives `neg`.")


def unsigned_conversion(code: list[x86.Instruction], n: int) -> str | None:
    """The unsigned type of the inline float conversion that the `fnstcw` at code[N] starts: `or` of the truncate
    bits, `fldcw`, `fistp`, and a read of the `fistp` slot, all before the next `fnstcw`."""
    window = code[n + 1:n + 1 + CONVERSION_REACH]
    window = window[:next((k for k, i in enumerate(window) if i.mnemonic == "fnstcw"), len(window))]
    steps = [lambda i: i.mnemonic == "or" and i.operands in TRUNCATE_BITS,
             lambda i: i.mnemonic == "fldcw",
             lambda i: i.mnemonic == "fistp" and i.operands.startswith(("dword ptr", "qword ptr"))]
    at = 0
    for step in steps:
        found = next((k for k in range(at, len(window)) if step(window[k])), None)
        if found is None:
            return None
        at = found + 1
    width, _, slot = window[at - 1].operands.partition(" ptr ")
    for read in window[at:]:
        if slot in read.operands:
            _, _, source = read.operands.partition(", ")
            source_width, _, source_slot = source.partition(" ptr ")
            if read.mnemonic in ("mov", "movzx") and source_slot == slot:
                return UNSIGNED_TYPES.get((width, source_width))
            return None
    return None


def float_to_unsigned_fact(code: list[x86.Instruction]) -> str | None:
    """`fnstcw`, `or` of 0xc00, `fldcw`, `fistp`, `fldcw` converts a float to an unsigned type. The width of the
    first read of the `fistp` slot gives the type."""
    sites = [(i.address, unsigned_conversion(code, n)) for n, i in enumerate(code) if i.mnemonic == "fnstcw"]
    sites = [(address, kind) for address, kind in sites if kind]
    if not sites:
        return None
    kinds = list(dict.fromkeys(kind for _, kind in sites))
    chunks = []
    for kind in kinds:
        places = [f"0x{address:x}" for address, found in sites if found == kind]
        chunks.append(f"{listed(places)} {'is a float' if len(places) == 1 else 'are floats'} converted to {kind}")
    casts = " or ".join(f"`({kind})x`" for kind in kinds)
    return (f"`fnstcw`, `or 0xc00`, `fldcw`, `fistp` and `fldcw` at {listed(chunks)} inline. Write {casts} on the "
            "float itself. `(int)x` or a signed cast calls `__ftol2_sse` instead.")


def idiom_lines(code: list[x86.Instruction], flags: str, unsigned: dict[int, int]) -> list[str | None]:
    """The compiler idioms that the code shows, each with the C that gives it. Each one holds only at the
    optimization level that it names."""
    if "/Od" in flags:
        found = [float_argument_fact(code), compare_chain_fact(code), switch_base_fact(code), bit_clear_fact(code),
                 left_constant_fact(code), minus_one_fact(code), float_to_unsigned_fact(code)]
    else:
        found = [unsigned_float_fact(unsigned), switch_chain_fact(code), float_to_unsigned_fact(code)]
    return [float_compare_fact(code)] + found


def fact_lines(function: x86.Function, f: Function, flags: str, cluster: bool, namer: Namer, types: names.Types,
               decoder: x86.Decoder, sizes: dict[int, int], idioms: bool = False) -> list[str]:
    """The facts about a function: what its assembly hides from a reader who writes C. IDIOMS adds the compiler
    idioms that the code shows."""
    lines = [] if cluster else [convention_fact(function, flags, f, decoder, sizes)]
    lines += pointer_facts(function, namer)
    global_decls = [decl for kind, _, decl in namer.used.values() if kind == "global"]
    lines.append(bodiless_fact([f.proto, f.locals] + global_decls, types))
    unsigned = unsigned_float_constants(function.code, namer.image) if idioms and "/Od" not in flags else {}
    lines.append(constant_fact(function, namer, unsigned))
    if idioms:
        lines += idiom_lines(function.code, flags, unsigned)
    return [line for line in lines if line]
