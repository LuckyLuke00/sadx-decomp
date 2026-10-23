"""Unit tests for the dossier facts in tools/facts.py: the stack and register readers, the text helpers and the lines.

run() calls every check and returns the failures. The code under test is built by hand: build() makes an
x86.Function from lines of assembly, and FakeDecoder hands out the callees by address.
"""

import math
import re
import struct
import tempfile
from pathlib import Path

import dossier
import facts
import names
import project
import x86

CODE = 0x401000  # where the function under test starts
CALLEE = 0x402000  # where a callee starts
READ_ONLY = 0x580000  # where read-only data starts
DATA = 0x501000  # an address in the data section


# ---------------------------------------------------------------- fixtures

def registers_in(text: str) -> int:
    """The register bits that a piece of operand text names."""
    bits = 0
    for word in re.findall(r"[a-z]+", text):
        bits |= x86.REGISTER.get(word, 0)
    return bits


def effects(mnemonic: str, operands: str) -> tuple[int, int]:
    """The register bits that an instruction reads and writes, as the decoder would give them."""
    destination, _, source = operands.partition(", ")
    if mnemonic in ("mov", "lea", "movzx") and destination in x86.REGISTER:
        return registers_in(source), x86.REGISTER[destination]
    if mnemonic == "pop":
        return 0, registers_in(operands)
    if mnemonic in ("cmp", "test", "push", "call", "jmp", "ret", "nop") or mnemonic.startswith("j"):
        return registers_in(operands), 0
    return registers_in(operands), registers_in(destination) if destination in x86.REGISTER else 0


def build(lines: list[str], start: int = CODE) -> x86.Function:
    """A function of one-byte instructions. @N in an operand is the address of line N."""
    span = range(start, start + len(lines))
    code, successors = [], {}
    for index, text in enumerate(lines):
        address = start + index
        mnemonic, _, operands = text.partition(" ")
        operands = re.sub(r"@(\d+)", lambda m: hex(start + int(m.group(1))), operands)
        branch = mnemonic == "call" or mnemonic.startswith("j")
        target = x86.number(operands) if branch else None
        reads, writes = effects(mnemonic, operands)
        code.append(x86.Instruction(address, 1, mnemonic, operands, reads, writes, target, None))
        after = [address + 1] if address + 1 in span else []
        if mnemonic in x86.STOPS:
            successors[address] = []
        elif mnemonic == "jmp":
            successors[address] = [target] if target in span else []
        elif mnemonic.startswith("j"):
            successors[address] = [t for t in [target] + after if t in span]
        else:
            successors[address] = after
    return x86.Function(start, len(lines), 0, code, successors)


class FakeDecoder:
    """Gives the function at an address: the only method that the facts call."""

    def __init__(self, functions: dict[int, x86.Function]):
        self.functions = functions

    def function(self, address: int, size: int, row: int) -> x86.Function:
        return self.functions[address]


def callees(**by_name: list[str]) -> tuple[FakeDecoder, dict[int, int]]:
    """A decoder and a size table for callees at CALLEE, CALLEE + 0x100 and so on, in the order given."""
    functions = {CALLEE + 0x100 * i: build(lines, CALLEE + 0x100 * i) for i, lines in enumerate(by_name.values())}
    return FakeDecoder(functions), {address: f.size for address, f in functions.items()}


NO_CALLEES = callees()


class FakeImage:
    """The part of pe.Image that the facts read: a code section, a data section with read-only data from
    READ_ONLY, an import slot and the bytes in BYTES."""

    import_slots = {0x503000: "Import"}
    bytes = {0x580000: struct.pack("<f", -65535.0), 0x580008: struct.pack("<d", 0.1),
             0x580010: struct.pack("<f", math.inf), 0x501000: struct.pack("<f", 2.0),
             0x580018: struct.pack("<f", 4294967296.0), 0x580020: struct.pack("<d", 4294967296.0)}

    def contains(self, address: int) -> bool:
        return 0x400000 <= address < 0x600000

    def is_code(self, address: int) -> bool:
        return 0x400000 <= address < 0x500000

    def is_read_only_data(self, address: int) -> bool:
        return READ_ONLY <= address < 0x600000

    def read(self, address: int, size: int) -> bytes:
        return self.bytes.get(address, bytes(size))[:size]


def namer_of(globals_: list[dossier.Global]) -> dossier.Namer:
    return dossier.Namer(FakeImage(), {}, {}, {}, sorted(globals_))


def info(name: str = "Foo", proto: str = "", file: str = "", locals_: str = "") -> dossier.Function:
    return dossier.Function(name, proto, False, file, "", locals_)


def described(lines: list[str]) -> str:
    return "; ".join(lines)


# ---------------------------------------------------------------- operands and stack

def check_memory_operands() -> list[str]:
    """memory_operands reads each [base + index*scale + disp] in the text. A scale is the number after the star
    and one when there is none. A minus sign makes a negative displacement. Text with no brackets gives none."""
    cases = [("", []),
             ("eax, ebx", []),
             ("eax, dword ptr [ebp + 8]", [facts.Memory("ebp", None, 1, 8)]),
             ("dword ptr [ebp - 0x14], eax", [facts.Memory("ebp", None, 1, -0x14)]),
             ("dword ptr [eax + ecx*4 + 0x10]", [facts.Memory("eax", "ecx", 4, 0x10)]),
             ("eax, dword ptr [ecx*8 + 0x501000]", [facts.Memory(None, "ecx", 8, 0x501000)]),
             ("eax, [eax*2 + ebx]", [facts.Memory("ebx", "eax", 2, 0)]),
             ("eax, dword ptr [eax + ecx]", [facts.Memory("eax", "ecx", 1, 0)]),
             ("eax, dword ptr [esp]", [facts.Memory("esp", None, 1, 0)]),
             ("eax, dword ptr [0x501000]", [facts.Memory(None, None, 1, 0x501000)]),
             ("eax, dword ptr fs:[0]", [facts.Memory(None, None, 1, 0)]),
             ("dword ptr [esi + 4], dword ptr [edi - 4]",
              [facts.Memory("esi", None, 1, 4), facts.Memory("edi", None, 1, -4)])]
    return [f"memory_operands gives {found} for `{text}`, not {wanted}"
            for text, wanted in cases if (found := facts.memory_operands(text)) != wanted]


def check_pops() -> list[str]:
    """pops gives the byte counts that the rets of a function pop, as a set. A plain ret pops nothing. A count
    in hex is read as hex. Two rets with one count give it once."""
    cases = [([], set()),
             (["ret"], set()),
             (["ret 8"], {8}),
             (["ret 0xc"], {12}),
             (["add esp, 8", "ret"], set()),
             (["test ecx, ecx", "je @4", "ret 4", "nop", "ret 0xc"], {4, 12}),
             (["test ecx, ecx", "je @4", "ret 8", "nop", "ret 8"], {8})]
    return [f"pops gives {found} for {described(lines)}, not {wanted}"
            for lines, wanted in cases if (found := facts.pops(build(lines))) != wanted]


def check_stack_change() -> list[str]:
    """stack_change gives how many bytes an instruction adds to esp: sub and add with a number, a push or pop of
    one dword or of the flags, 32 for pushal and popal, and the bytes that a called function pops. It gives None
    when esp gets a value that is not known: from a register, with and, from leave. Other instructions give 0.
    A call to a function with no known size moves nothing."""
    decoder, sizes = callees(pops8=["ret 8"], plain=["ret"], two=["test ecx, ecx", "je @4", "ret 4", "nop", "ret 0xc"])
    pops8, plain, two = sorted(sizes)
    cases = [("sub esp, 0x10", -16), ("sub esp, 4", -4), ("add esp, 8", 8), ("add esp, 0x20", 32),
             ("sub esp, eax", None), ("and esp, 0xfffffff0", None), ("mov esp, ebp", None), ("mov esp, 0x10", None),
             ("leave", None),
             ("push eax", -4), ("push 0", -4), ("pushfd", -4), ("pushal", -32),
             ("pop ecx", 4), ("popfd", 4), ("popal", 32),
             ("mov eax, ebx", 0), ("mov eax, esp", 0), ("ret", 0), ("ret 8", 0),
             (f"call {hex(pops8)}", 8), (f"call {hex(plain)}", 0), (f"call {hex(two)}", 12),
             ("call 0x409000", 0), ("call eax", 0)]
    failures = []
    for text, wanted in cases:
        mnemonic, _, operands = text.partition(" ")
        target = x86.number(operands) if mnemonic == "call" else None
        instruction = x86.Instruction(CODE, 1, mnemonic, operands, 0, 0, target, None)
        found = facts.stack_change(instruction, decoder, sizes)
        if found != wanted:
            failures.append(f"stack_change gives {found} for `{text}`, not {wanted}")
    return failures


def check_may_read_stack_arguments() -> list[str]:
    """may_read_stack_arguments is True when a frame function reads [ebp + 8] or higher, and when a frameless one
    reads [esp + n] at or above the return address, counting its pushes, subs and the pops of its callees. It is
    also True when a frameless function moves esp in a way that it cannot follow, returns with esp moved, or
    reaches one instruction with two esp offsets. It is False when no stack argument is read. A frame function
    ignores how esp moves."""
    frame = ["push ebp", "mov ebp, esp"]
    cases = [
        (frame + ["mov eax, dword ptr [ebp + 8]", "pop ebp", "ret"], True, {}),
        (["mov edi, edi"] + frame + ["mov eax, dword ptr [ebp + 0xc]", "pop ebp", "ret"], True, {}),
        (frame + ["sub esp, 4", "mov eax, dword ptr [ebp - 4]", "mov ecx, dword ptr [ebp + 4]", "mov esp, ebp",
                  "pop ebp", "ret"], False, {}),
        (["mov eax, dword ptr [esp + 4]", "ret"], True, {}),
        (["mov eax, dword ptr [esp]", "ret"], False, {}),
        (["mov eax, ecx", "ret"], False, {}),
        (["push ecx", "mov eax, dword ptr [esp + 4]", "pop ecx", "ret"], False, {}),
        (["push ecx", "mov eax, dword ptr [esp + 8]", "pop ecx", "ret"], True, {}),
        (["sub esp, 8", "mov eax, dword ptr [esp + 8]", "add esp, 8", "ret"], False, {}),
        (["sub esp, 8", "mov eax, dword ptr [esp + 0xc]", "add esp, 8", "ret"], True, {}),
        (["mov esp, eax", "ret"], True, {}),
        (["push eax", "ret"], True, {}),
        (["test ecx, ecx", "je @4", "push eax", "nop", "pop eax", "ret"], True, {}),
        (["push ecx", "pop ecx", "sub edx, 1", "jne @0", "ret"], False, {}),
        (["push eax", "call 0x402000", "ret"], False, {"pop": ["ret 4"]}),
        (["push eax", "call 0x402000", "ret"], True, {}),
        (["push eax", "call 0x402000", "mov ecx, dword ptr [esp + 4]", "ret"], True, {"pop": ["ret 4"]}),
        (["push eax", "call 0x402000", "mov ecx, dword ptr [esp + 4]", "pop eax", "ret"], False, {"pop": ["ret"]}),
    ]
    failures = []
    for lines, wanted, callee in cases:
        decoder, sizes = callees(**callee)
        found = facts.may_read_stack_arguments(build(lines), decoder, sizes)
        if found != wanted:
            failures.append(f"may_read_stack_arguments gives {found} for {described(lines)}"
                            f"{' with a callee ' + str(callee) if callee else ''}, not {wanted}")
    return failures


def check_exit_pops() -> list[str]:
    """exit_pops gives the bytes that a function pops on return: its own rets, plus those of each function that
    it jumps to, also by a conditional jump. A call is no exit. A jump inside the function is no exit. It gives
    None for a jump that it cannot follow (jmp edx, an unknown target, or a chain deeper than depth). A switch
    table jump is no exit."""
    cases = [
        (["ret 8"], {}, 3, {8}),
        (["ret"], {}, 3, set()),
        (["test ecx, ecx", "je @4", "ret 4", "nop", "ret 8"], {}, 3, {4, 8}),
        (["jmp dword ptr [esp + 4]"], {}, 3, None),
        (["jmp dword ptr [eax*4 + 0x501000]", "ret 4"], {}, 3, {4}),
        (["call 0x409000", "ret 4"], {}, 3, {4}),
        (["sub edx, 1", "jne @0", "ret 4"], {}, 3, {4}),
        (["jmp 0x402000"], {"x": ["ret 8"]}, 3, {8}),
        (["jmp 0x409000"], {}, 3, None),
        (["test ecx, ecx", "jne 0x402000", "ret 4"], {"x": ["ret 0xc"]}, 3, {4, 12}),
        (["jmp 0x402000"], {"x": ["jmp 0x402100"], "y": ["ret 4"]}, 1, None),
        (["jmp 0x402000"], {"x": ["jmp 0x402100"], "y": ["ret 4"]}, 2, {4}),
        (["jmp 0x402000"], {"x": ["ret 4"]}, 0, None),
        (["jmp 0x402000"], {"x": ["jmp 0x402100"], "y": ["jmp 0x402200"], "z": ["ret 8"]}, 3, {8}),
        (["jmp 0x402000"], {"x": ["jmp 0x402100"], "y": ["jmp 0x402200"], "z": ["jmp 0x402300"], "w": ["ret 8"]}, 3,
         None),
    ]
    failures = []
    for lines, by_name, depth, wanted in cases:
        decoder, sizes = callees(**by_name)
        found = facts.exit_pops(build(lines), decoder, sizes, depth)
        if found != wanted:
            failures.append(f"exit_pops gives {found} for {described(lines)} with {by_name} at depth {depth}, "
                            f"not {wanted}")
    return failures


# ---------------------------------------------------------------- text

def check_printed_keyword() -> list[str]:
    """printed_keyword gives the calling convention that the head of a prototype names. WINAPI, CALLBACK,
    APIENTRY and PASCAL mean __stdcall. A keyword inside the parameter list is no part of the head."""
    cases = [("void __fastcall Foo(int a)", "__fastcall"), ("int __stdcall Foo()", "__stdcall"),
             ("int __cdecl Foo(void)", "__cdecl"), ("void __thiscall Foo::Run(int)", "__thiscall"),
             ("BOOL WINAPI Foo(void)", "__stdcall"), ("LRESULT CALLBACK Foo(int)", "__stdcall"),
             ("void APIENTRY Foo(void)", "__stdcall"), ("int PASCAL Foo(int)", "__stdcall"),
             ("void Foo(int a)", None), ("", None),
             ("void Foo(void (__cdecl *callback)(int))", None)]
    return [f"printed_keyword gives {found!r} for `{proto}`, not {wanted!r}"
            for proto, wanted in cases if (found := facts.printed_keyword(proto)) != wanted]


def check_amount() -> list[str]:
    """amount writes a byte count as the disassembly does: decimal up to 9, hex with 0x from 10."""
    cases = [(0, "0"), (4, "4"), (9, "9"), (10, "0xa"), (12, "0xc"), (16, "0x10"), (0x24, "0x24")]
    return [f"amount gives {found!r} for {number}, not {wanted!r}"
            for number, wanted in cases if (found := facts.amount(number)) != wanted]


def check_listed() -> list[str]:
    """listed joins items as `a`, `a and b`, `a, b and c`. Past FACT_LIMIT (3) items it keeps the first three and
    adds `and more`."""
    cases = [(["a"], "a"), (["a", "b"], "a and b"), (["a", "b", "c"], "a, b and c"),
             (["a", "b", "c", "d"], "a, b, c and more"), (list("abcdefg"), "a, b, c and more")]
    return [f"listed gives {found!r} for {items}, not {wanted!r}"
            for items, wanted in cases if (found := facts.listed(items)) != wanted]


def check_offsets_text() -> list[str]:
    """offsets_text writes a set of offsets in hex, smallest first and by value, a negative one with a minus sign
    before the 0x, in the form that listed gives."""
    cases = [({0}, "0x0"), ({8}, "0x8"), ({-4}, "-0x4"), ({0x10, 8}, "0x8 and 0x10"),
             ({4, -8, 0}, "-0x8, 0x0 and 0x4"), ({1, 2, 3, 4}, "0x1, 0x2, 0x3 and more"),
             ({-1, -2, -3, 4}, "-0x3, -0x2, -0x1 and more")]
    return [f"offsets_text gives {found!r} for {sorted(offsets)}, not {wanted!r}"
            for offsets, wanted in cases if (found := facts.offsets_text(offsets)) != wanted]


# ---------------------------------------------------------------- calling convention

def check_convention_fact() -> list[str]:
    """convention_fact tells which keyword the registers and the ret show. It gives None when the code shows no
    convention, when a register other than ecx and edx is read first, when the rets pop two different counts or a
    jump hides the pop, and in optimized code when the registers may be the compiler's choice (a C file or an
    unknown file) or the printed keyword differs. A /Od function gets its fact against any prototype: ecx with a
    pop is a C++ member function in a C++ file (None in a C file or an unknown file, which has no members),
    whose struct takes the class in its name or an address placeholder, other registers are __fastcall. A
    register with a plain ret gives None when the code reads a stack argument. Member names get no __thiscall
    warning."""
    ret8 = ["mov eax, dword ptr [esp + 4]", "ret 8"]
    ecx = ["mov eax, ecx", "ret"]
    thunk = ["jmp 0x402000"]
    stack = " The stack holds the other {} bytes of parameters."
    second = " If the first of them is an integer or a pointer, put an unused second parameter before it."
    no_this = " Do not use `__thiscall`: it is only for class members."
    change = " The printed prototype differs, so change it to fit the code and keep its name."
    member = ("The function reads ecx and ends with `ret 8`, so it is a C++ member function: ecx holds `this`, and "
              "the 8 bytes on the stack are its parameters. Declare a struct with the fields it reads through `this` "
              "and the function as its member, then define the function as that member. ")
    placeholder = member + "Name the struct `Unk_00401000`, a placeholder until its real name is known."
    named = member + "The struct's name is the part of the function's name before the last `::`."
    pop8 = "The function ends with `ret 8`, so it pops 8 bytes of parameters."
    cases = [
        # (code, flags, name, proto, file, callee, wanted)
        (ret8, "/O2", "Foo", "int __stdcall Foo(int, int)", "a.c", None, f"{pop8} Keep `__stdcall`."),
        (["mov eax, dword ptr [esp + 4]", "ret 0xc"], "/O2", "Foo", "", "a.c", None,
         "The function ends with `ret 0xc`, so it pops 0xc bytes of parameters. Declare the function `__stdcall`."),
        (ret8, "/O2", "Foo", "int Foo(int, int)", "a.c", None, None),
        (ret8, "/Od", "Foo", "int Foo(int, int)", "a.c", None, f"{pop8} Declare the function `__stdcall`.{change}"),
        (["mov eax, 1", "ret"], "/Od", "Foo", "int Foo(void)", "a.c", None, None),
        (["cmp dword ptr [esp + 4], 0", "je @4", "ret 4", "nop", "ret 8"], "/O2", "Foo", "", "a.c", None, None),
        (["jmp dword ptr [esp + 4]"], "/O2", "Foo", "", "a.c", None, None),
        (["mov ecx, eax", "ret 4"], "/Od", "Foo", "", "a.cpp", None, None),
        (thunk, "/O2", "Foo", "int __stdcall Foo(int)", "a.c", ["ret 4"],
         "The function ends with `ret 4`, so it pops 4 bytes of parameters. Keep `__stdcall`."),
        (ecx, "/O2", "Foo", "", "a.c", None, None),
        (ecx, "/O2", "Foo", "", "", None, None),
        (ecx, "/O2", "Foo", "", "a.cpp", None,
         f"The first parameter arrives in ecx. Declare the function `__fastcall`.{no_this}"),
        (ecx, "/O2", "Foo::Run", "void __fastcall Foo::Run(void)", "a.cpp", None,
         "The first parameter arrives in ecx. Keep `__fastcall`."),
        (ecx, "/O2", "?Run@Foo@@QAEXXZ", "", "a.cpp", None,
         "The first parameter arrives in ecx. Declare the function `__fastcall`."),
        (ecx, "/O2", "Foo", "void __stdcall Foo(void)", "a.cpp", None, None),
        (["mov eax, edx", "ret"], "/O2", "Foo", "", "a.cpp", None,
         "The first parameter is unused and the second arrives in edx. Declare the function `__fastcall`."),
        (["mov eax, ecx", "add eax, edx", "ret 8"], "/O2", "Foo", "", "a.cpp", None,
         "The first two parameters arrive in ecx and edx." + stack.format(8) + " Declare the function `__fastcall`."
         + no_this),
        (["mov eax, ecx", "ret 4"], "/O2", "Foo", "", "a.cpp", None,
         "The first parameter arrives in ecx." + stack.format(4) + second + " Declare the function `__fastcall`."
         + no_this),
        (["mov eax, ecx", "add eax, dword ptr [esp + 4]", "ret 4"], "/O2", "Foo", "", "a.cpp", None,
         "The first parameter arrives in ecx." + stack.format(4) + second + " Declare the function `__fastcall`."
         + no_this),
        (["mov eax, ecx", "add eax, dword ptr [esp + 4]", "ret"], "/O2", "Foo", "", "a.cpp", None, None),
        (["push ebp", "mov ebp, esp", "mov eax, ecx", "add eax, dword ptr [ebp + 8]", "pop ebp", "ret"],
         "/O2", "Foo", "", "a.cpp", None, None),
        (["mov ecx, eax", "ret 4"], "/O2", "Foo", "int __stdcall Foo(int)", "a.cpp", None, None),
        (["mov eax, ecx", "ret 8"], "/Od", "Foo", "", "a.cpp", None, placeholder),
        (["mov eax, ecx", "ret 8"], "/Gy /Od", "Foo", "void Foo(int, int)", "a.cpp", None, placeholder),
        (["mov eax, ecx", "ret 8"], "/Od", "Foo", "void __stdcall Foo(int, int)", "a.cpp", None, placeholder),
        (["mov eax, ecx", "ret 8"], "/Od", "Foo::Run", "", "a.cpp", None, named),
        (["mov eax, ecx", "ret 8"], "/Od", "Foo", "", "a.c", None, None),
        (["mov eax, ecx", "ret 8"], "/Od", "Foo", "", "", None, None),
        (ecx, "/Od", "Foo", "", "a.c", None,
         f"The first parameter arrives in ecx. Declare the function `__fastcall`.{no_this}"),
        (ecx, "/Od", "Foo", "void __stdcall Foo(void)", "a.c", None,
         f"The first parameter arrives in ecx. Declare the function `__fastcall`.{change}{no_this}"),
        (["mov eax, edx", "ret 8"], "/Od", "Foo", "", "a.c", None,
         "The first parameter is unused and the second arrives in edx." + stack.format(8)
         + " Declare the function `__fastcall`."),
    ]
    failures = []
    for lines, flags, name, proto, file, callee, wanted in cases:
        decoder, sizes = callees(x=callee) if callee else NO_CALLEES
        found = facts.convention_fact(build(lines), flags, info(name, proto, file), decoder, sizes)
        if found != wanted:
            failures.append(f"convention_fact gives {found!r} for {described(lines)} with flags {flags}, "
                            f"name {name}, proto `{proto}`, file {file!r}, not {wanted!r}")
    return failures


# ---------------------------------------------------------------- pointer globals

def check_frame_slot() -> list[str]:
    """frame_slot gives ("slot", disp) for an operand that is one plain [ebp + disp], and None for a register,
    a memory operand on another base, or one with an index."""
    cases = [("dword ptr [ebp - 8]", ("slot", -8)), ("dword ptr [ebp + 8]", ("slot", 8)), ("[ebp - 8]", ("slot", -8)),
             ("dword ptr [ebp]", ("slot", 0)), ("eax", None), ("", None), ("dword ptr [eax + 4]", None),
             ("dword ptr [esp + 4]", None), ("dword ptr [ebp + eax*4 - 8]", None), ("dword ptr [ebp + eax]", None)]
    return [f"frame_slot gives {found} for `{operand}`, not {wanted}"
            for operand, wanted in cases if (found := facts.frame_slot(operand)) != wanted]


def check_transfer() -> list[str]:
    """transfer gives the (place, global) pairs after one instruction. A mov of a known global's address word
    puts the global in the register. A mov between registers or to or from a frame slot copies the pairs. Every
    write drops the old pairs of its place, a call drops eax, ecx and edx, and a write to a slot drops the slots
    within four bytes. A compare reads and drops nothing."""
    g, h = (dossier.Global(DATA, 4, "Foo", "int Foo"), 0), (dossier.Global(DATA + 8, 4, "Bar", "int Bar"), 0)
    slot = lambda disp: ("slot", disp)
    known = {DATA: g, DATA + 8: h}
    cases = [
        ("mov eax, dword ptr [0x501000]", frozenset(), {(x86.EAX, g)}),
        ("mov eax, dword ptr [0x509999]", frozenset(), set()),
        ("mov eax, dword ptr [0x509999]", {(x86.EAX, g)}, set()),
        ("mov ecx, eax", {(x86.EAX, g)}, {(x86.EAX, g), (x86.ECX, g)}),
        ("mov eax, ecx", {(x86.EAX, g), (x86.ECX, h)}, {(x86.EAX, h), (x86.ECX, h)}),
        ("mov eax, ebx", {(x86.EAX, g)}, set()),
        ("mov ecx, eax", {(x86.EAX, g), (x86.EAX, h), (x86.ECX, h)}, {(x86.EAX, g), (x86.EAX, h), (x86.ECX, g),
                                                                       (x86.ECX, h)}),
        ("mov al, cl", {(x86.EAX, g)}, set()),
        ("add eax, 4", {(x86.EAX, g), (x86.EBX, h)}, {(x86.EBX, h)}),
        ("call 0x402000", {(x86.EAX, g), (x86.ECX, g), (x86.EDX, g), (x86.EBX, h), (x86.ESI, h), (x86.EDI, h)},
         {(x86.EBX, h), (x86.ESI, h), (x86.EDI, h)}),
        ("mov dword ptr [ebp - 8], eax", {(x86.EAX, g)}, {(x86.EAX, g), (slot(-8), g)}),
        ("mov ecx, dword ptr [ebp - 8]", {(slot(-8), g)}, {(slot(-8), g), (x86.ECX, g)}),
        ("mov ecx, dword ptr [ebp - 12]", {(slot(-8), g)}, {(slot(-8), g)}),
        ("mov dword ptr [ebp - 8], ecx", {(slot(-8), g)}, set()),
        ("mov dword ptr [ebp - 8], 5", {(slot(-8), g), (slot(-16), h)}, {(slot(-16), h)}),
        ("mov dword ptr [ebp - 8], ecx", {(slot(-5), g), (slot(-12), h)}, {(slot(-12), h)}),
        ("mov dword ptr [ebp - 8], ecx", {(slot(-4), g), (slot(-13), h)}, {(slot(-4), g), (slot(-13), h)}),
        ("add dword ptr [ebp - 8], 1", {(slot(-8), g)}, set()),
        ("cmp dword ptr [ebp - 8], 0", {(slot(-8), g)}, {(slot(-8), g)}),
        ("push dword ptr [ebp - 8]", {(slot(-8), g)}, {(slot(-8), g)}),
        ("mov ecx, dword ptr [eax + 4]", {(x86.EAX, g)}, {(x86.EAX, g)}),
    ]
    failures = []
    for text, before, wanted in cases:
        mnemonic, _, operands = text.partition(" ")
        branch = mnemonic == "call"
        reads, writes = effects(mnemonic, operands)
        target = x86.number(operands) if branch else None
        instruction = x86.Instruction(CODE, 1, mnemonic, operands, reads, writes, target, None)
        found = facts.transfer(instruction, frozenset(before), known.get)
        if found != frozenset(wanted):
            failures.append(f"transfer gives {sorted(found, key=repr)} for `{text}` after {sorted(before, key=repr)}, "
                            f"not {sorted(wanted, key=repr)}")
    return failures


def check_pointer_globals() -> list[str]:
    """pointer_globals maps (global, offset into it) to the offsets used from the loaded value as a base. A use
    counts for a base register with no index, or a scaled one, and a displacement from -0x100 to 0xffff. A lea,
    a base of esp or ebp, an overwritten register, a call that drops the register and a use before the load do
    not count. A value kept in a frame slot counts, and so does one that reaches a use by only one of two paths.
    One global read at two offsets gives a key for each."""
    holder_at = lambda base: (lambda address: (dossier.Global(base, 16, "Foo", "int Foo[4]"), address - base)
                              if base <= address < base + 16 else None)
    load = "mov eax, dword ptr [0x501000]"
    cases = [
        ([load, "mov ecx, dword ptr [eax + 8]", "mov edx, dword ptr [eax + 0x10]", "ret"], {(0, 0): {8, 0x10}}),
        (["mov eax, dword ptr [0x501000]", "mov ebx, dword ptr [0x501004]", "mov edx, dword ptr [eax + 8]",
          "mov ecx, dword ptr [ebx + 0xc]", "ret"], {(0, 0): {8}, (0, 4): {0xc}}),
        ([load, "mov ecx, dword ptr [eax]", "mov edx, dword ptr [eax - 4]", "ret"], {(0, 0): {0, -4}}),
        ([load, "lea edx, [eax + 8]", "ret"], {}),
        ([load, "mov ecx, dword ptr [eax + ebx]", "ret"], {}),
        ([load, "mov ecx, dword ptr [eax + ebx*4 + 8]", "ret"], {(0, 0): {8}}),
        ([load, "mov ecx, dword ptr [eax + 0xffff]", "mov edx, dword ptr [eax - 0x100]", "ret"],
         {(0, 0): {0xffff, -0x100}}),
        ([load, "mov ecx, dword ptr [eax + 0x10000]", "mov edx, dword ptr [eax - 0x101]", "ret"], {}),
        ([load, "mov ecx, dword ptr [esp + 4]", "mov edx, dword ptr [ebp + 8]", "ret"], {}),
        (["mov ecx, dword ptr [eax + 4]", load, "ret"], {}),
        ([load, "mov eax, 5", "mov ecx, dword ptr [eax + 4]", "ret"], {}),
        ([load, "mov ecx, ebx", "mov edx, dword ptr [ecx + 4]", "ret"], {}),
        ([load, "mov ecx, eax", "mov edx, dword ptr [ecx + 4]", "ret"], {(0, 0): {4}}),
        (["mov ebx, dword ptr [0x501000]", "call 0x402000", "mov ecx, dword ptr [ebx + 4]", "ret"], {(0, 0): {4}}),
        ([load, "call 0x402000", "mov ecx, dword ptr [eax + 4]", "ret"], {}),
        ([load, "mov dword ptr [ebp - 4], eax", "mov eax, 0", "mov ecx, dword ptr [ebp - 4]",
          "mov edx, dword ptr [ecx + 4]", "ret"], {(0, 0): {4}}),
        ([load, "mov dword ptr [ebp - 4], eax", "mov dword ptr [ebp - 4], 0", "mov ecx, dword ptr [ebp - 4]",
          "mov edx, dword ptr [ecx + 4]", "ret"], {}),
        (["test ecx, ecx", "je @4", load, "nop", "mov edx, dword ptr [eax + 4]", "ret"], {(0, 0): {4}}),
        ([load, "mov ecx, dword ptr [eax + 4]", "sub edx, 1", "jne @1", "ret"], {(0, 0): {4}}),
    ]
    failures = []
    for lines, wanted in cases:
        found = facts.pointer_globals(build(lines), holder_at(DATA))
        simple = {(g.address - DATA, offset): used for (g, offset), used in found.items()}
        if simple != wanted:
            failures.append(f"pointer_globals gives {simple} for {described(lines)}, not {wanted}")
    return failures


def check_pointer_facts() -> list[str]:
    """pointer_facts gives one line for each global that the code loads and uses as a base, when its declaration
    is an integer of 4 bytes, or the data address has no name. Named ones say to keep the declaration and cast.
    Unnamed ones say to declare a pointer. A pointer, a float, an array or a global in code or an import slot
    gets none. A global that is only loaded gets none. The globals with the most offsets come first, ties by
    address, and only FACT_LIMIT lines are kept."""
    foo = lambda decl, size=4: dossier.Global(DATA, size, "Foo", decl)
    named = "Foo holds a pointer. The code uses it at {}. Keep its declaration and cast its value, as in `{}`."
    unnamed = ("DAT_{:08x} (address 0x{:x}) holds a pointer. The code uses it at {}. Declare it as a pointer and "
               "add the offsets to its value, not to its address.")
    load = "mov eax, dword ptr [0x501000]"
    use = lambda *offsets: [f"mov esi, dword ptr [eax {'-' if o < 0 else '+'} {abs(o)}]" for o in offsets] + ["ret"]
    many = ["mov eax, dword ptr [0x501000]", "mov ecx, dword ptr [0x501010]", "mov edx, dword ptr [0x501008]",
            "mov ebx, dword ptr [0x501020]", "mov esi, dword ptr [eax + 4]", "mov esi, dword ptr [ecx + 4]",
            "mov esi, dword ptr [ecx + 8]", "mov esi, dword ptr [edx + 4]", "mov esi, dword ptr [edx + 8]",
            "mov esi, dword ptr [ebx + 4]", "mov esi, dword ptr [ebx + 8]", "mov esi, dword ptr [ebx + 0xc]",
            "mov esi, dword ptr [ebx + 0x10]", "ret"]
    cases = [
        ([load] + use(8, 0x10), [foo("int Foo")],
         [named.format("offsets 0x8 and 0x10", "(char *)Foo + 0x8")]),
        ([load] + use(0), [foo("int Foo")], [named.format("offset 0x0", "(char *)Foo")]),
        ([load] + use(0, 4), [foo("int Foo")], [named.format("offsets 0x0 and 0x4", "(char *)Foo + 0x4")]),
        ([load] + use(-4), [foo("int Foo")], [named.format("offset -0x4", "(char *)Foo - 0x4")]),
        ([load] + use(-4, 8), [foo("int Foo")], [named.format("offsets -0x4 and 0x8", "(char *)Foo + 0x8")]),
        ([load] + use(4), [foo("extern unsigned long Foo")], [named.format("offset 0x4", "(char *)Foo + 0x4")]),
        ([load] + use(4), [foo("int *Foo")], []),
        ([load] + use(4), [foo("float Foo")], []),
        ([load] + use(4), [foo("struct Bar Foo")], []),
        ([load] + use(4), [foo("int Foo[4]", 16)], []),
        (["mov eax, dword ptr [0x501004]"] + use(4), [foo("int Foo[4]", 16)], []),
        ([load, "ret"], [foo("int Foo")], []),
        ([load] + use(4), [], [unnamed.format(DATA, DATA, "offset 0x4")]),
        (["mov eax, dword ptr [0x401234]", "mov ecx, dword ptr [0x503000]", "mov edx, dword ptr [0x700000]",
          "mov esi, dword ptr [eax + 4]", "mov esi, dword ptr [ecx + 4]", "mov esi, dword ptr [edx + 4]", "ret"],
         [], []),
        (many, [], [unnamed.format(0x501020, 0x501020, "offsets 0x4, 0x8, 0xc and more"),
                    unnamed.format(0x501008, 0x501008, "offsets 0x4 and 0x8"),
                    unnamed.format(0x501010, 0x501010, "offsets 0x4 and 0x8")]),
    ]
    failures = []
    for lines, globals_, wanted in cases:
        found = facts.pointer_facts(build(lines), namer_of(globals_))
        if found != wanted:
            failures.append(f"pointer_facts gives {found} for {described(lines)} with globals "
                            f"{[g.decl for g in globals_]}, not {wanted}")
    return failures


# ---------------------------------------------------------------- types and the whole list

HEADER = "struct Foo {\n    int a;\n};\n\nunion Bar {\n    int b;\n};\n\nstruct Fwd;\n"


def check_bodiless_fact() -> list[str]:
    """bodiless_fact names the struct and union types that the texts reach through a pointer and the types header
    gives no body, each once and in the order first seen. It says has for one and have for more, with at most
    FACT_LIMIT names and `and more`. A type used by value, an enum, a type with a body and text with no such type
    give None. A forward declaration is no body."""
    tail = (" no members and no known size. Cast a pointer to `char *` before you add to it or index it. "
            "Read a member with a byte offset and its type, as in `*(int *)((char *)p + 0x10)`.")
    cases = [
        (["void Run(struct Baz *p)"], "struct Baz has" + tail),
        (["void Run(union Baz *p)"], "union Baz has" + tail),
        (["void Run(struct Baz *p)", "", "struct Baz *q;"], "struct Baz has" + tail),
        (["void Run(struct Baz *p, union Qux *q)"], "struct Baz and union Qux have" + tail),
        (["void Run(struct Qux *q)", "struct Baz *p;"], "struct Qux and struct Baz have" + tail),
        (["struct A *a; struct B *b; struct C *c;"], "struct A, struct B and struct C have" + tail),
        (["struct A *a; struct B *b; struct C *c; struct D *d;"], "struct A, struct B, struct C and more have" + tail),
        (["void Run(struct Fwd *p)"], "struct Fwd has" + tail),
        (["void Run(struct Baz **pp)"], "struct Baz has" + tail),
        (["void Run(struct Foo *p, union Bar *q)"], None),
        (["void Run(struct Baz b)"], None),
        (["void Run(enum Baz *p)"], None),
        (["void Run(int *p)", ""], None),
        ([], None),
    ]
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder) / "types.h"
        path.write_text(HEADER, encoding="utf-8")
        types = names.Types(path)
        for texts, wanted in cases:
            found = facts.bodiless_fact(texts, types)
            if found != wanted:
                failures.append(f"bodiless_fact gives {found!r} for {texts}, not {wanted!r}")
    return failures


def check_float_literal() -> list[str]:
    """float_literal gives the shortest text that gives the same float back, with `f`, and a double's repr. A
    whole number gets `.0`. An infinity and a NaN give None."""
    cases = [(struct.pack("<f", -65535.0), "-65535.0f"), (struct.pack("<f", 0.1), "0.1f"),
             (struct.pack("<f", 320.0), "320.0f"),
             (struct.pack("<f", 1e-05), "1e-05f"), (struct.pack("<f", 3.0e38), "3e+38f"),
             (struct.pack("<d", 0.1), "0.1"), (struct.pack("<d", 2.0), "2.0"),
             (struct.pack("<f", math.inf), None), (struct.pack("<d", math.nan), None)]
    return [f"float_literal gives {facts.float_literal(raw)!r} for {raw.hex()}, not {wanted!r}"
            for raw, wanted in cases if facts.float_literal(raw) != wanted]


def check_constant_fact() -> list[str]:
    """constant_fact names the floats and doubles that x87 code loads from read-only data with no name here.
    It skips a named global, writable data, an integer load, a register base, an infinity and an address in its
    skip table."""
    float_load = "fld dword ptr [0x580000]"
    double_load = "fmul qword ptr [0x580008]"
    cases = [([float_load, "ret"], [], "The code loads the constants -65535.0f (at 0x580000) from"),
             ([float_load, double_load, "ret"], [], "The code loads the constants -65535.0f (at 0x580000) and 0.1 "),
             ([float_load, "ret"], [dossier.Global(0x580000, 4, "Speed", "float Speed")], None),
             (["fld dword ptr [0x501000]", "ret"], [], None),
             (["fild dword ptr [0x580000]", "ret"], [], None),
             (["fld dword ptr [eax + 0x580000]", "ret"], [], None),
             (["fld dword ptr [0x580010]", "ret"], [], None),
             (["mov eax, dword ptr [0x580000]", "ret"], [], None)]
    failures = []
    for code, globals_, wanted in cases:
        found = facts.constant_fact(build(code), namer_of(globals_), {})
        if (found or "")[:len(wanted or "")] != (wanted or "") or (found is None) != (wanted is None):
            failures.append(f"constant_fact gives {found!r} for {described(code)}, not one that starts {wanted!r}")
    found = facts.constant_fact(build([float_load, "ret"]), namer_of([]), {0x580000: 4})
    if found is not None:
        failures.append(f"constant_fact gives {found!r} for a constant in its skip table, not None")
    return failures


UNSIGNED = ["fild dword ptr [esp + 4]", "test eax, eax", "jns @4", "fadd dword ptr [0x580018]", "ret"]
SWITCH_BASE = ["mov ecx, dword ptr [ebp - 8]", "sub ecx, 1", "mov dword ptr [ebp - 8], ecx",
               "cmp dword ptr [ebp - 8], 5", "ja @7", "mov edx, dword ptr [ebp - 8]",
               "jmp dword ptr [edx*4 + 0x401100]", "ret"]


def check_text_cases(fact, cases: list[tuple[list[str], str | None]]) -> list[str]:
    """The failures of a fact function over (code, wanted) cases: None when wanted is None, else a text that
    holds wanted."""
    failures = []
    for code, wanted in cases:
        found = fact(build(code).code)
        if (found is None) != (wanted is None) or (wanted and wanted not in found):
            failures.append(f"{fact.__name__} gives {found!r} for {described(code)}, not one that holds {wanted!r}")
    return failures


def check_float_compare_fact() -> list[str]:
    """float_compare_fact names the C operator of each `fnstsw ax`, `test ah, M` and jump after a float compare
    (fcom, fcomp, fcompp, fucom, fucomp, fucompp or ftst), for every row of COMPARE_ROWS. A jump into the block
    reads the swapped row, a mask that no row holds says nothing, and `fnstsw` with no compare before it says
    nothing. After `ftst` the other side is 0.0."""
    compare = ["fcomp dword ptr [0x580000]", "fnstsw ax"]
    return check_text_cases(facts.float_compare_fact, [
        (compare + ["test ah, 0x41", "jne @5", "ret"], "`test ah, 0x41` with `jne` runs it when st0 > other."),
        (compare + ["test ah, 0x41", "je @5", "ret"], "`test ah, 0x41` with `jne` runs it when st0 > other."),
        (compare + ["test ah, 1", "jne @5", "ret"], "`test ah, 1` with `jne` runs it when st0 >= other."),
        (compare + ["test ah, 5", "jp @5", "ret"], "`test ah, 5` with `jp` runs it when st0 <"),
        (compare + ["test ah, 0x41", "jp @5", "ret"], "`test ah, 0x41` with `jp` runs it when st0 <= other."),
        (["fucompp", "fnstsw ax", "test ah, 0x44", "jp @5", "ret"], "st0 == other"),
        (["fucompp", "fnstsw ax", "test ah, 0x44", "jnp @5", "ret"], "st0 != other"),
        (["fucomp dword ptr [0x580000]", "fnstsw ax", "test ah, 5", "jp @5", "ret"], "st0 < other"),
        (["ftst", "fnstsw ax", "test ah, 0x41", "jne @5", "ret"], "After `ftst` the other side is 0.0."),
        (compare + ["test ah, 0x40", "jne @5", "ret"], None),
        (["fnstsw ax", "test ah, 5", "jp @4", "ret"], None),
    ])


def check_float_argument_fact() -> list[str]:
    """float_argument_fact names the slot of `fstp`, `fld`, `push ecx`, `fstp [esp]` on one slot. A float local
    passed to a call has `push ecx` first, and a `fld` of another slot is no such argument."""
    return check_text_cases(facts.float_argument_fact, [
        (["fstp dword ptr [ebp - 4]", "fld dword ptr [ebp - 4]", "push ecx", "fstp dword ptr [esp]", "call @5",
          "ret"], "through the slot [ebp - 4] pass"),
        (["fstp dword ptr [ebp - 4]", "push ecx", "fld dword ptr [ebp - 4]", "fstp dword ptr [esp]", "ret"], None),
        (["fstp dword ptr [ebp - 4]", "fld dword ptr [ebp - 8]", "push ecx", "fstp dword ptr [esp]", "ret"], None),
    ])


def check_switch_chain_fact() -> list[str]:
    """switch_chain_fact gives the case values of two or more `sub R, K` or `dec R` steps on one register, each
    with je or jne, as running sums. A neutral instruction may sit inside the chain, at most CHAIN_GAP of them
    between a step and its jump. A chain after an `add` or a `jne` is read from its middle, `sub R, R2` is case
    0 only when `xor R2, R2` set R2, and a step on another register ends the chain."""
    gap = lambda count: ["mov eax, esi", "sub eax, 1"] + ["push edi"] * count + ["je @1", "dec eax", "je @1", "ret"]
    return check_text_cases(facts.switch_chain_fact, [
        (["mov eax, dword ptr [ecx + 4]", "sub eax, 0", "je @7", "sub eax, 2", "je @7", "sub eax, 4", "jne @8", "nop",
          "ret"], "The chain at 0x401001 is cases 0, 2, 6."),
        (["mov eax, ebp", "sub eax, 2", "push edi", "je @8", "dec eax", "je @8", "sub eax, 6", "jne @9", "nop", "ret"],
         "The chain at 0x401001 is cases 2, 3, 9."),
        (gap(facts.CHAIN_GAP), "The chain at 0x401001 is cases 1, 2."),
        (gap(facts.CHAIN_GAP + 1), None),
        (["xor ebx, ebx", "mov eax, dword ptr [ecx + 4]", "sub eax, ebx", "je @8", "dec eax", "je @8", "dec eax",
          "jne @8", "ret"], "The chain at 0x401002 is cases 0, 1, 2."),
        (["mov ebx, esi", "mov eax, dword ptr [ecx + 4]", "sub eax, ebx", "je @8", "dec eax", "je @8", "dec eax",
          "jne @8", "ret"], None),
        (["mov eax, esi", "sub eax, 1", "je @5", "sub ecx, 1", "je @5", "ret"], None),
        (["add eax, 3", "sub eax, 1", "je @5", "dec eax", "je @5", "ret"], None),
        (["mov eax, esi", "sub eax, 4", "jne @5", "dec eax", "je @5", "ret"], None),
    ])


def check_compare_chain_fact() -> list[str]:
    """compare_chain_fact names the `cmp [ebp - N], K` and `je` pairs on a slot that one `mov` fills and a `jmp`
    ends. A dword slot needs two pairs that jump to different places, a byte slot one. A slot read elsewhere is
    a real local, a word slot is never a switch copy, and a chain with no `mov` before it is no copy."""
    return check_text_cases(facts.compare_chain_fact, [
        (["mov dword ptr [ebp - 8], eax", "cmp dword ptr [ebp - 8], 1", "je @6", "cmp dword ptr [ebp - 8], 3",
          "je @7", "jmp @8", "nop", "nop", "ret"], "At 0x401001, `cmp dword ptr [ebp - 8]` is cases 1, 3. The slot"),
        (["mov byte ptr [ebp - 4], al", "cmp byte ptr [ebp - 4], 0", "je @4", "jmp @5", "nop", "ret"],
         "is case 0. The slot"),
        (["mov dword ptr [ebp - 8], eax", "cmp dword ptr [ebp - 8], 1", "je @4", "jmp @5", "nop", "ret"], None),
        (["mov dword ptr [ebp - 8], eax", "cmp dword ptr [ebp - 8], 1", "je @6", "cmp dword ptr [ebp - 8], 3",
          "je @6", "jmp @7", "nop", "ret"], None),
        (["mov dword ptr [ebp - 8], eax", "cmp dword ptr [ebp - 8], 1", "je @6", "cmp dword ptr [ebp - 8], 3",
          "je @7", "jmp @8", "mov ecx, dword ptr [ebp - 8]", "nop", "ret"], None),
        (["cmp dword ptr [ebp - 8], 1", "je @5", "cmp dword ptr [ebp - 8], 3", "je @6", "jmp @7", "nop", "nop",
          "ret"], None),
        (["mov word ptr [ebp - 4], ax", "cmp word ptr [ebp - 4], 1", "je @6", "cmp word ptr [ebp - 4], 3", "je @7",
          "jmp @8", "nop", "nop", "ret"], None),
    ])


def check_switch_base_fact() -> list[str]:
    """switch_base_fact names the `sub` or `add` of a switch whose cases do not start at 0, from the `mov`, step,
    `mov`, `cmp`, `ja` and table jump. The table jump may come up to TABLE_JUMP_REACH instructions after the
    `ja`. Without the table jump, or when the source shifts a value that the slot did not load, it says nothing."""
    base_add = [line.replace("sub ecx", "add ecx") for line in SWITCH_BASE]
    source_shift = ["mov ecx, dword ptr [ebp - 4]"] + SWITCH_BASE[1:]
    reach = lambda count: SWITCH_BASE[:5] + ["nop"] * count + SWITCH_BASE[5:]  # COUNT nops after the `ja`
    return check_text_cases(facts.switch_base_fact, [
        (SWITCH_BASE, "The case values are the table index plus 1."),
        (base_add, "The case values are the table index minus 1."),
        (reach(facts.TABLE_JUMP_REACH - 2), "The case values are the table index plus 1."),
        (reach(facts.TABLE_JUMP_REACH - 1), None),
        (SWITCH_BASE[:6] + ["ret"], None),
        (source_shift, None),
    ])


def check_bit_clear_fact() -> list[str]:
    """bit_clear_fact names the `and R, 0xffff....` after a load into R. A mask that no `~` of a 16-bit value
    gives, a 16-bit immediate and an `and` after `sbb` say nothing."""
    return check_text_cases(facts.bit_clear_fact, [
        (["movsx edx, word ptr [eax + 4]", "and edx, 0xfffffeff", "mov word ptr [ecx + 4], dx", "ret"],
         "`and edx, 0xfffffeff` at 0x401001 is `& ~0x100`. Write the mask with `~`. A 16-bit literal such as "
         "`0xfeff` gives `and edx, 0xfeff`"),
        (["sbb edx, edx", "and edx, 0xffffff92", "ret"], None),
        (["movsx edx, word ptr [eax + 4]", "and edx, 0xfeff", "ret"], None),
    ])


def check_left_constant_fact() -> list[str]:
    """left_constant_fact names the `fld1` or `fldz` right before a popping `faddp`, `fmulp`, `fsubrp` or `fdivrp`
    as the left operand. A `fld1` before `fstp` is no operand."""
    return check_text_cases(facts.left_constant_fact, [
        (["fld dword ptr [ebp - 4]", "fld1", "faddp st(1)", "ret"], "Write `1.0f + x` at 0x401001."),
        (["fld dword ptr [ebp - 4]", "fldz", "fsubrp st(1)", "ret"], "`0.0f - x`"),
        (["fld1", "fstp dword ptr [ebp - 4]", "ret"], None),
    ])


def check_minus_one_fact() -> list[str]:
    """minus_one_fact quotes the operands of each `imul R, S, -1` and lists their addresses. Another constant
    says nothing."""
    return check_text_cases(facts.minus_one_fact, [
        (["imul eax, eax, -1", "ret"], "`imul eax, eax, -1` at 0x401000 is `x * -1`."),
        (["imul eax, ecx, -1", "ret"], "`imul eax, ecx, -1` at 0x401000 is `x * -1`."),
        (["imul eax, eax, -1", "imul ecx, edx, -1", "ret"],
         "`imul eax, eax, -1` at 0x401000 and `imul ecx, edx, -1` at 0x401001 are `x * -1`."),
        (["imul eax, eax, -2", "ret"], None),
    ])


def check_unsigned_float() -> list[str]:
    """unsigned_float_constants finds the 4294967296.0 that `fadd` adds right after `jns`, with a `fild` before
    it, as a float or a double. unsigned_float_fact names the cast for each width. A `fld` before it, or another
    constant, is no cast."""
    qword = UNSIGNED[:3] + ["fadd qword ptr [0x580020]", "ret"]
    cases = [(UNSIGNED, {0x580018: 4}, "Write `(float)(unsigned int)x`."),
             (qword, {0x580020: 8}, "Write `(double)(unsigned int)x` where the `fadd` reads a qword."),
             (["fld dword ptr [esp + 4]"] + UNSIGNED[1:], {}, None),
             (UNSIGNED[:3] + ["fadd dword ptr [0x580000]", "ret"], {}, None)]
    failures = []
    for code, wanted, text in cases:
        found = facts.unsigned_float_constants(build(code).code, FakeImage())
        line = facts.unsigned_float_fact(found)
        if found != wanted or (line is None) != (text is None) or (text and text not in line):
            failures.append(f"unsigned float gives {found} and {line!r} for {described(code)}, not {wanted} and "
                            f"{text!r}")
    return failures


def check_idiom_lines() -> list[str]:
    """idiom_lines gives the /Od idioms only for /Od code, and the optimized ones only for other code."""
    code = build(["imul eax, eax, -1", "mov ecx, esi", "sub ecx, 1", "je @6", "dec ecx", "je @6", "ret"]).code
    minus_one, chain = facts.minus_one_fact(code), facts.switch_chain_fact(code)
    if minus_one is None or chain is None:
        return [f"the idiom_lines fixture gives {minus_one!r} and {chain!r}, not both facts"]
    cases = [("/Od /GS", minus_one, chain), ("/O2 /GS", chain, minus_one)]
    failures = []
    for flags, kept, dropped in cases:
        lines = facts.idiom_lines(code, flags, {})
        if kept not in lines or dropped in lines:
            failures.append(f"idiom_lines for {flags} gives {[line[:30] for line in lines if line]}, not "
                            f"{kept[:30]!r} without {dropped[:30]!r}")
    return failures


def check_fact_lines() -> list[str]:
    """fact_lines gives the convention fact, then the pointer facts, then the bodiless fact, with no empty
    line. A register-argument cluster has no convention fact. The bodiless fact reads the prototype, the locals
    and the declarations of the globals that the namer used, and not those of functions."""
    lines = ["mov eax, dword ptr [0x501100]", "mov ecx, dword ptr [eax + 4]", "ret 8"]
    plain = ["mov eax, 1", "ret"]
    convention = "The function ends with `ret 8`"
    pointer = "DAT_00501100 (address 0x501100) holds a pointer."
    bodiless = "struct Baz has no members"
    cases = [
        (lines, "void __stdcall Foo(struct Baz *p)", "", False, {}, [convention, pointer, bodiless]),
        (lines, "void __stdcall Foo(struct Baz *p)", "", True, {}, [pointer, bodiless]),
        (lines, "void __stdcall Foo(int a)", "", False, {}, [convention, pointer]),
        (lines, "void __stdcall Foo(int a)", "struct Baz *p;", False, {}, [convention, pointer, bodiless]),
        (lines, "void __stdcall Foo(int a)", "", False, {0x501200: ("global", "Foo", "struct Baz *Foo")},
         [convention, pointer, bodiless]),
        (lines, "void __stdcall Foo(int a)", "", False, {0x402000: ("function", "Bar", "void Bar(struct Baz *p)")},
         [convention, pointer]),
        (plain, "void Foo(void)", "", False, {}, []),
    ]
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder) / "types.h"
        path.write_text(HEADER, encoding="utf-8")
        types = names.Types(path)
        for code, proto, locals_, cluster, used, wanted in cases:
            namer = namer_of([])
            namer.used = used
            found = facts.fact_lines(build(code), info("Foo", proto, "a.c", locals_), "/O2", cluster, namer, types,
                                       *NO_CALLEES)
            starts = [line[:len(want)] for line, want in zip(found, wanted)]
            if len(found) != len(wanted) or starts != wanted:
                failures.append(f"fact_lines gives {[line[:40] for line in found]} for {described(code)} with proto "
                                f"`{proto}`, locals `{locals_}`, cluster {cluster}, used {list(used.values())}, "
                                f"not {wanted}")
    return failures


def check_fact_lines_idioms() -> list[str]:
    """With idioms, fact_lines leaves the cast's 4294967296.0 out of the constant line and puts the cast's line
    last. Without them, the constant line keeps it."""
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder) / "types.h"
        path.write_text(HEADER, encoding="utf-8")
        types = names.Types(path)
        for idioms in (False, True):
            found = facts.fact_lines(build(UNSIGNED), info("Foo", "void Foo(void)", "a.c"), "/O2", False,
                                     namer_of([]), types, *NO_CALLEES, idioms=idioms)
            constant = any("4294967300.0f" in line for line in found)
            cast = bool(found) and found[-1].startswith("`fild`, then `jns`")
            if (constant, cast) != (not idioms, idioms):
                failures.append(f"fact_lines with idioms {idioms} gives {[line[:40] for line in found]}")
    return failures


# ---------------------------------------------------------------- callee names

def check_library_annotations() -> list[str]:
    """library_annotations maps each LIBRARY address to the name on the comment line under it. A decorated name
    comes back demangled, with no access or calling-convention words and with std::string for the long string
    type. A plain name stays as it is, an indented annotation counts, and a FUNCTION or STUB annotation gives
    nothing."""
    target = project.game_config().target
    text = (f"// LIBRARY: {target} 0x00402f90\n"
            "// ??0?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAE@PBD@Z\n"
            f"\t// LIBRARY: {target} 0x00403000\n"
            "\t// _strlen\n"
            f"// FUNCTION: {target} 0x00403100\n"
            "void Foo(void) {}\n"
            f"// STUB: {target} 0x00403200\n"
            "// Bar\n")
    wanted = {0x402f90: "std::string::basic_string(char const *)", 0x403000: "_strlen"}
    found = dossier.library_annotations({"a.cpp": text})
    if found != wanted:
        return [f"library_annotations gives {found}, not {wanted}"]
    return []


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_memory_operands, check_pops, check_stack_change, check_may_read_stack_arguments,
                  check_exit_pops, check_printed_keyword, check_amount, check_listed, check_offsets_text,
                  check_convention_fact, check_frame_slot, check_transfer, check_pointer_globals,
                  check_pointer_facts, check_bodiless_fact, check_float_literal, check_constant_fact,
                  check_float_compare_fact, check_float_argument_fact, check_switch_chain_fact,
                  check_compare_chain_fact, check_switch_base_fact, check_bit_clear_fact, check_left_constant_fact,
                  check_minus_one_fact, check_unsigned_float, check_idiom_lines, check_fact_lines,
                  check_fact_lines_idioms, check_library_annotations):
        failures += check()
    return failures
