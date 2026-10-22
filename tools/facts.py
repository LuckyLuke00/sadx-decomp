"""The facts that `check.py dossier --facts` lists: what a function's assembly hides from a reader who writes C,
such as a register argument, a callee that pops its arguments, a global that holds a pointer, a type with no
body in the types header and a float constant that the source writes as a literal.

check.py passes fact_lines to dossier.show. Needs capstone, so it runs in .venv.
"""

import collections
import math
import re
import struct
from typing import NamedTuple

import names
import x86
from dossier import Function, Global, Namer
from groups import calls, read_first

FACT_LIMIT = 3  # most globals, types and offsets that a fact names
REGISTERS = {"eax": x86.EAX, "ecx": x86.ECX, "edx": x86.EDX, "ebx": x86.EBX, "esi": x86.ESI, "edi": x86.EDI}
READ_ONLY = ("cmp", "test", "push", "call", "jmp", "fld", "fild", "fcom", "fcomp", "fadd", "fsub", "fmul", "fdiv")
POINTED_TAG = re.compile(r"\b(struct|union)\s+(\w+)\s*\*")  # a struct or union reached through a pointer
KEYWORD = re.compile(r"\b(__fastcall|__stdcall|__cdecl|__thiscall|WINAPI|CALLBACK|APIENTRY|PASCAL)\b")
STDCALL_NAMES = ("WINAPI", "CALLBACK", "APIENTRY", "PASCAL")
CPP_FILES = (".cpp", ".cc", ".cxx")
INTEGER_TYPE = re.compile(r"(?:extern\s+|static\s+)*(?:const\s+|volatile\s+)*(?:unsigned\s+|signed\s+)?(?:int|long)\s*")
BASE_OFFSETS = range(-0x100, 0x10000)  # a displacement outside this is a table address, not a member offset


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


def may_read_stack_arguments(function: x86.Function, decoder: x86.Decoder, sizes: dict[int, int]) -> bool:
    """Whether the code reads arguments from the stack. True also when a frameless function moves esp in a
    way that this does not follow."""
    if x86.has_frame(function.code):
        return any(m.base == "ebp" and m.disp >= 8 for i in function.code for m in memory_operands(i.operands))
    by_address = {i.address: i for i in function.code}
    offset = {function.address: 0}  # esp minus its value at the entry, before each instruction
    pending = [function.address]
    found = False
    while pending:
        address = pending.pop()
        instruction = by_address[address]
        found = found or any(m.base == "esp" and m.disp + offset[address] >= 4
                             for m in memory_operands(instruction.operands))
        change = stack_change(instruction, decoder, sizes)
        if change is None or (instruction.mnemonic == "ret" and offset[address] != 0):
            return True
        for following in function.successors[address]:
            if following not in offset:
                offset[following] = offset[address] + change
                pending.append(following)
            elif offset[following] != offset[address] + change:
                return True
    return found


def exit_pops(function: x86.Function, decoder: x86.Decoder, sizes: dict[int, int], depth: int = 3) -> set[int] | None:
    """The bytes that the function pops when it returns, through a ret of its own or a jump to another
    function. None when a jump goes where this can't follow, such as `jmp edx`. A switch table is no exit."""
    found = pops(function)
    if any(i.mnemonic == "jmp" and i.target is None and not x86.SWITCH.search(i.operands) for i in function.code):
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


def convention_fact(function: x86.Function, flags: str, f: Function, decoder: x86.Decoder,
                    sizes: dict[int, int]) -> str | None:
    """What the registers and the ret say about the calling convention. None when the code shows none, when
    it reads a register that no keyword passes (the register-argument cluster), when a jump out hides what
    is popped, or when the compiler may have picked the registers: optimized code in a C file or in a file
    that is not known, and optimized code whose printed prototype names no such keyword. Only a `/Od`
    function gets a keyword against its printed prototype, because that code never picks registers itself."""
    first = read_first(function, {})
    registers = first & (x86.ECX | x86.EDX)
    popped = exit_pops(function, decoder, sizes)
    if popped is None or first & ~registers or len(popped) > 1 or not (registers or popped):
        return None
    pop = max(popped, default=0)
    debug = "/Od" in flags
    debug_method = debug and registers == x86.ECX and pop  # the tree matches this with an asm line
    keyword = "__stdcall" if debug_method or not registers else "__fastcall"
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
    if debug_method:
        return (f"The function reads ecx and ends with `ret {amount(pop)}`, so it pops {amount(pop)} bytes of "
                f"parameters. {declare} The parameters are the {amount(pop)} bytes on the stack.{change} "
                "Start the body with `__asm mov <local>, ecx`, where <local> is a new local.")
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
    written = instruction.writes | (x86.CALL_CHANGES if mnemonic == "call" else 0)
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


def constant_fact(function: x86.Function, namer: Namer) -> str | None:
    """The line about the float and double constants that the code loads from read-only data and that have no
    name here. The compiler puts a literal of the source there, so a global at that address breaks the match."""
    literals = {}
    for instruction in function.code:
        width = 8 if "qword ptr" in instruction.operands else 4 if "dword ptr" in instruction.operands else 0
        if not instruction.mnemonic.startswith("f") or instruction.mnemonic.startswith("fi") or not width:
            continue  # fild, fiadd and the like read integers
        for m in memory_operands(instruction.operands):
            if m.base or m.index or namer.holder(m.disp) or not namer.image.is_read_only_data(m.disp):
                continue
            literal = float_literal(namer.image.read(m.disp, width))
            if literal:
                literals[m.disp] = literal
    if not literals:
        return None
    shown = listed([f"{text} (at 0x{address:x})" for address, text in sorted(literals.items())])
    return (f"The code loads the constants {shown} from read-only data. Write each one as that literal. "
            "Do not declare a global for its address: that breaks the match.")


def fact_lines(function: x86.Function, f: Function, flags: str, cluster: bool, namer: Namer, types: names.Types,
               decoder: x86.Decoder, sizes: dict[int, int]) -> list[str]:
    """The facts about a function: what its assembly hides from a reader who writes C."""
    lines = [] if cluster else [convention_fact(function, flags, f, decoder, sizes)]
    lines += pointer_facts(function, namer)
    global_decls = [decl for kind, _, decl in namer.used.values() if kind == "global"]
    lines.append(bodiless_fact([f.proto, f.locals] + global_decls, types))
    lines.append(constant_fact(function, namer))
    return [line for line in lines if line]
