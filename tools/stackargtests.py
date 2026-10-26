"""Unit tests for tools/stackargs.py: the bytes that each call passes on the stack and the bytes that a function
reads, as `check.py args` uses them.

run() calls every check and returns the failures. The code under test is built by hand with the fixtures of
facttests.py: build() makes an x86.Function from lines of assembly, and callees() places the callees.
"""

import collections
import tempfile
from pathlib import Path

import names
import stackargs
import x86
from facttests import CODE, build, callees, described

F = "call 0x402000"  # a call to the first callee


def check_saved_offset() -> list[str]:
    """saved_offset gives where esp stands once the prologue has run: after the frame, the sub esp for the locals
    and the push of each register that a function must keep, ebx, esi, edi and ebp, before it writes it and when
    it pops it somewhere. A register that it never pops came in as an argument. Other instructions may sit between
    those. A sub esp counts only before the first saved register other than ebp. A push ecx counts as a local when
    a saved register follows it, and gives None when none does: it may as well be an argument. The prologue ends
    at the first call, branch or ret, or at a push or esp change that is not one of those."""
    cases = [
        (["push ebp", "mov ebp, esp", "sub esp, 8", "push esi", "push edi", F, "pop edi", "pop esi", "mov esp, ebp",
          "pop ebp", "ret"], -20),
        (["mov edi, edi", "push ebp", "mov ebp, esp", "pop ebp", "ret"], -4),
        (["sub esp, 0x10", "mov eax, dword ptr [esp + 0x14]", "push ebx", "push esi", "mov esi, ecx", "push esi", F,
          "pop esi", "pop ebx"], -24),
        (["push 1", F, "ret"], 0),
        (["push esi", "push esi", F, "pop esi"], -4),
        (["mov esi, ecx", "push esi", F, "pop esi"], 0),
        (["test ecx, ecx", "je @3", "push esi", "pop esi", "ret"], 0),
        (["push esi", "sub esp, 8", "fstp qword ptr [esp]", F, "add esp, 8", "pop esi"], -4),
        (["push esi", "push edi", "pop edi", "pop esi", "ret"], -8),
        (["push edi", F, "add esp, 4", "ret"], 0),
        (["push ecx", "push ebx", F, "pop ebx", "pop ecx", "ret"], -8),
        (["push ecx", "push ecx", "push ebx", F, "pop ebx", "add esp, 8", "ret"], -12),
        (["push ebp", "mov ebp, esp", "push ecx", "push esi", F, "pop esi", "mov esp, ebp", "pop ebp", "ret"], -12),
        (["push ecx", F, "pop ecx", "ret"], None),
        (["push ecx", "push eax", F, "add esp, 8", "ret"], None),
    ]
    return [f"saved_offset gives {found} for {described(lines)}, not {wanted}"
            for lines, wanted in cases if (found := stackargs.saved_offset(build(lines))) != wanted]


def check_arguments_passed() -> list[str]:
    """arguments_passed gives, for each direct call to a function of known size, the bytes it passes on the stack:
    what the callee pops plus the add esp or the pops of ecx or edx right after the call, when that brings esp back
    to where it stands between calls and no other call runs between the first push and the call. That place is where
    the prologue left esp, raised by each pop of a saved register that frees its slot. A call there with nothing to
    clean passes 0, unless a cleanup follows it all the same. Esp above that place, before the pops and the ret that
    end the function, shows that the prologue was read wrong: every call gives None. Anything else gives None: a
    cleanup merged with a later call's, a slot that a later call reuses, a pop of a saved register, an esp that this
    cannot follow, a prologue whose push ecx may be an argument."""
    pop8 = {"f": ["ret 8"]}
    cases = [
        (["push 1", "push 2", "push 3", F, "add esp, 0xc", "ret"], {}, {3: 12}),
        (["push eax", F, "pop ecx", "ret"], {}, {1: 4}),
        (["push 1", "push 2", F, "pop ecx", "pop edx", "ret"], {}, {2: 8}),
        ([F, "ret"], {}, {0: 0}),
        (["push esi", "mov esi, ecx", F, "pop esi", "ret"], {}, {2: 0}),
        (["push 1", "push 2", F, "ret"], pop8, {2: 8}),
        (["push esi", "mov esi, ecx", "sub esp, 8", "fstp qword ptr [esp]", F, "add esp, 8", "pop esi", "ret"], {},
         {4: 8}),
        (["push 1", "test eax, eax", "je @4", "nop", F, "add esp, 4", "ret"], {}, {4: 4}),
        (["push 1", F, "push 2", F, "add esp, 8", "ret"], {}, {1: None, 3: None}),
        (["push 1", F, "mov dword ptr [esp], 2", F, "add esp, 4", "ret"], {}, {1: None, 3: None}),
        (["push 1", F, F, F, "add esp, 4", "ret"], {}, {1: None, 2: None, 3: None}),
        (["push 1", "test eax, eax", "je @4", F, F, "add esp, 4", "ret"], {}, {3: None, 4: None}),
        (["push esi", "push 1", F, "pop esi", "ret"], {}, {2: None}),
        (["push ebp", "mov ebp, esp", "and esp, 0xfffffff8", F, "mov esp, ebp", "pop ebp", "ret"], {}, {3: None}),
        (["test eax, eax", "je @3", "push 1", F, "add esp, 4", "ret"], {}, {3: None}),
        (["push edi", F, "add esp, 4", "ret"], {}, {1: 4}),
        (["push esi", "push edi", F, "add esp, 8", "ret"], {}, {2: 8}),
        (["push ecx", "push ebx", "push 1", F, "add esp, 4", "pop ebx", "pop ecx", "ret"], {}, {3: 4}),
        (["push ecx", "push eax", F, "add esp, 8", "ret"], {}, {2: None}),
        (["push esi", "push edi", F, "pop edi", "push 1", F, "add esp, 4", "pop esi", "ret"], {}, {2: 0, 5: 4}),
        (["sub esp, 8", "fstp dword ptr [esp]", F, "add esp, 8", F, "ret"], {}, {2: None, 4: None}),
        (["sub esp, 8", "fstp dword ptr [esp]", F, "add esp, 8", "ret"], {}, {2: None}),
        (["sub esp, 8", "fstp dword ptr [esp]", F, "mov eax, 1", "add esp, 8", "mov dword ptr [0x500000], eax", "ret"],
         {}, {2: None}),
        (["sub esp, 8", "push esi", "mov dword ptr [esp + 4], eax", F, "pop esi", "add esp, 8", "ret"], {}, {3: 0}),
        (["call 0x409000", "ret"], {}, {}),
        (["call eax", "ret"], {}, {}),
    ]
    failures = []
    for lines, by_name, wanted in cases:
        decoder, sizes = callees(**(by_name or {"f": ["ret"]}))
        sites = stackargs.arguments_passed(build(lines), decoder, sizes)
        found = {site.address - CODE: site.bytes for site in sites}
        if found != wanted:
            failures.append(f"arguments_passed gives {found} for {described(lines)}, not {wanted}")
    return failures


def check_arguments_read() -> list[str]:
    """arguments_read gives how many bytes of stack arguments a function reads, from [ebp + 8] up with a frame and
    from above the return address without one, at least a dword each, and whether it takes an argument's address,
    as va_start does. A jump to another function adds what that one reads. It gives None when a jump goes where
    this cannot follow (jmp eax, an unknown target, a chain deeper than depth) or a frameless esp gets lost."""
    frame = ["push ebp", "mov ebp, esp"]
    cases = [
        (frame + ["mov eax, dword ptr [ebp + 8]", "mov ecx, dword ptr [ebp + 0xc]", "pop ebp", "ret"], {}, 3,
         (8, False)),
        (frame + ["fld qword ptr [ebp + 8]", "pop ebp", "ret"], {}, 3, (8, False)),
        (frame + ["movzx eax, byte ptr [ebp + 0x10]", "pop ebp", "ret"], {}, 3, (12, False)),
        (frame + ["mov eax, dword ptr [ebp - 4]", "mov esp, ebp", "pop ebp", "ret"], {}, 3, (0, False)),
        (["mov edi, edi"] + frame + ["mov eax, dword ptr [ebp + 8]", "pop ebp", "ret"], {}, 3, (4, False)),
        (frame + ["lea eax, [ebp + 0xc]", "pop ebp", "ret"], {}, 3, (0, True)),
        (["push esi", "mov esi, dword ptr [esp + 0xc]", "pop esi", "ret"], {}, 3, (8, False)),
        (["mov eax, dword ptr [esp]", "ret"], {}, 3, (0, False)),
        (["lea eax, [esp + 8]", "push eax", F, "add esp, 4", "ret"], {"f": ["ret"]}, 3, (0, True)),
        (["mov eax, ecx", "ret"], {}, 3, (0, False)),
        (["jmp 0x402000"], {"x": ["mov eax, dword ptr [esp + 8]", "ret"]}, 3, (8, False)),
        (["test ecx, ecx", "jne 0x402000", "mov eax, dword ptr [esp + 4]", "ret"],
         {"x": ["mov eax, dword ptr [esp + 0xc]", "ret"]}, 3, (12, False)),
        (["test eax, eax", "je @3", "jmp dword ptr [eax*4 + 0x501000]", "ret"], {}, 3, (0, False)),
        (["jmp 0x409000"], {}, 3, None),
        (["jmp eax"], {}, 3, None),
        (["mov esp, eax", "ret"], {}, 3, None),
        (["jmp 0x402000"], {"x": ["jmp 0x402100"], "y": ["mov eax, dword ptr [esp + 4]", "ret"]}, 1, None),
        (["jmp 0x402000"], {"x": ["jmp 0x402100"], "y": ["mov eax, dword ptr [esp + 4]", "ret"]}, 2, (4, False)),
    ]
    failures = []
    for lines, by_name, depth, wanted in cases:
        decoder, sizes = callees(**by_name)
        found = stackargs.arguments_read(build(lines), decoder, sizes, depth)
        if found != (wanted and stackargs.Reads(*wanted)):
            failures.append(f"arguments_read gives {found} for {described(lines)} with {by_name} at depth {depth}, "
                            f"not {wanted}")
    return failures


def check_parameter_bytes() -> list[str]:
    """parameter_bytes gives the stack bytes of a prototype's parameters: a dword at least for each, 8 for a double
    or an __int64, a struct by value at its size from the types header, rounded up to dwords. __fastcall keeps the
    first two parameters of a dword or less that are no float in registers, __thiscall the first. It gives None
    for a variadic, a struct whose size is unknown, and a struct returned by value, which may add a hidden
    pointer."""
    cases = [("void f()", 0), ("void f(void)", 0), ("int f(int a, char b)", 8), ("void f(double d)", 8),
             ("void f(struct task *tp, struct ModeSelPrmType *prmp)", 8), ("void f(short a)", 4),
             ("void f(__int64 a)", 8), ("void f(void (*cb)(int))", 4), ("void f(int a[3])", 4),
             ("void f(int &a)", 4), ("struct task *f(int a)", 4),
             ("void __fastcall f(int a, int b, int c)", 4), ("void __fastcall f(float a, int b)", 4),
             ("void __fastcall f(double a, int b, int c)", 8), ("void __thiscall f(struct Foo *p, int a)", 4),
             ("void f(struct Foo s)", 12), ("void f(struct Bar s)", None), ("void f(int a, ...)", None),
             ("struct Foo f(int a)", None)]
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder) / "types.h"
        path.write_text("struct Foo {\n    int a[3];\n};\nstatic_assert(sizeof(Foo) == 0xc);\n", encoding="utf-8")
        types = names.Types(path)
        for proto, wanted in cases:
            found = stackargs.parameter_bytes(proto, types)
            if found != wanted:
                failures.append(f"parameter_bytes gives {found} for `{proto}`, not {wanted}")
    return failures


def check_verdict() -> list[str]:
    """verdict says takes-any when the sure calls pass different byte counts and the function reads fewer than the
    most, pops nothing and takes no argument's address: it ignores what some callers pass. Other disagreeing calls
    give disagree, to check by hand. mismatch is calls that all pass one count that the declaration does not
    take, and unused is such calls that pass what the function reads while the declaration takes more. Calls that
    agree with the declaration, an unknown declaration and no sure call give None."""
    counts = collections.Counter
    reads = stackargs.Reads
    cases = [
        (counts({0: 3, 4: 2}), reads(0, False), set(), 4, "takes-any"),
        (counts({4: 2, 12: 2}), reads(4, False), set(), None, "takes-any"),
        (counts({4: 2, 12: 2}), reads(12, False), set(), 12, "disagree"),
        (counts({4: 1, 8: 1}), reads(4, True), set(), None, "disagree"),
        (counts({4: 1, 8: 1}), reads(4, False), {4}, 4, "disagree"),
        (counts({4: 1, 8: 1}), None, set(), 4, "disagree"),
        (counts({4: 1, 8: 1}), reads(4, False), None, 4, "disagree"),
        (counts({8: 1}), reads(8, False), set(), 4, "mismatch"),
        (counts({4: 2}), None, set(), 0, "mismatch"),
        (counts({4: 2}), reads(8, False), set(), 12, "mismatch"),
        (counts({0: 6}), reads(0, False), set(), 4, "unused"),
        (counts({4: 1}), reads(4, False), set(), 12, "unused"),
        (counts({8: 2}), reads(8, False), set(), 8, None),
        (counts({8: 2}), reads(8, False), set(), None, None),
        (counts(), reads(4, False), set(), 0, None),
    ]
    return [f"verdict gives {found} for {sure}, {read}, pops {pops}, declared {declared}, not {wanted}"
            for sure, read, pops, declared, wanted in cases
            if (found := stackargs.verdict(sure, read, pops, declared)) != wanted]


def check_unexplained_registers() -> list[str]:
    """unexplained_registers gives the registers that a function reads at its entry that its declared convention
    does not pass: ecx for __thiscall, ecx and edx for __fastcall, none for the rest. /GL passes the others."""
    cases = [
        (x86.ECX, "void __thiscall f(struct a *p)", 0),
        (x86.ECX | x86.EDX, "void __fastcall f(int a, int b)", 0),
        (x86.ECX, "void f(struct taskwk *twp)", x86.ECX),
        (x86.ESI | x86.EDX, "void __thiscall f(struct a *p, int b)", x86.ESI | x86.EDX),
        (0, "void f(void)", 0),
    ]
    return [f"unexplained_registers gives {found} for {registers} and {proto}, not {wanted}"
            for registers, proto, wanted in cases
            if (found := stackargs.unexplained_registers(registers, proto)) != wanted]


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_saved_offset, check_arguments_passed, check_arguments_read, check_parameter_bytes,
                  check_verdict, check_unexplained_registers):
        failures += check()
    return failures
