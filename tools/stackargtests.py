"""Unit tests for tools/stackargs.py: the bytes that each call passes on the stack and the bytes that a function
reads, as `check.py args` uses them.

run() calls every check and returns the failures. The code under test is built by hand with the fixtures of
facttests.py: build() makes an x86.Function from lines of assembly, and callees() places the callees.
"""

import collections
import tempfile
from pathlib import Path

import dossier
import names
import stackargs
import x86
from facttests import CALLEE, CODE, DATA, build, callees, described, namer_of

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
    does not pass: ecx for __thiscall, ecx and edx for __fastcall as far as it has parameters in them, none for the
    rest. A method passes its this in ecx unless it declares __fastcall or the like. /GL passes the others."""
    cases = [
        (x86.ECX, "void __thiscall f(struct a *p)", False, 0),
        (x86.ECX | x86.EDX, "void __fastcall f(int a, int b)", False, 0),
        (x86.ECX, "void f(struct taskwk *twp)", False, x86.ECX),
        (x86.ESI | x86.EDX, "void __thiscall f(struct a *p, int b)", False, x86.ESI | x86.EDX),
        (0, "void f(void)", False, 0),
        (x86.ECX | x86.EDX, "void __fastcall f(int a)", False, x86.EDX),
        (x86.ECX, "void __fastcall f(void)", False, x86.ECX),
        (x86.ECX | x86.EDX, "void __fastcall f(float a, int b)", False, x86.EDX),
        (x86.ECX, "int A::f()", True, 0),
        (x86.ECX | x86.EDX, "int A::f(int a)", True, x86.EDX),
        (x86.ECX, "int __thiscall A::f()", True, 0),
        (x86.ECX | x86.EDX, "int __fastcall A::f(int a)", True, x86.EDX),
    ]
    types = names.Types(Path("no-such-types.h"))
    return [f"unexplained_registers gives {found} for {registers}, {proto} and method {method}, not {wanted}"
            for registers, proto, method, wanted in cases
            if (found := stackargs.unexplained_registers(registers, proto, types, method)) != wanted]


def check_members_of() -> list[str]:
    """members_of gives the classes and structs that the sources define with a body, through a base class too, and
    the names of the static functions that they declare. A forward declaration and a template parameter are none."""
    sources = {"a.h": "class File;\ntemplate<class T> class Singleton\n{\n};\nclass A : public Base\n{\n"
                      "\ttemplate<class T> static T Uniform(T param_1);\n\tint f();\n};\nstruct b {\n};\n",
               "a.c": "static void FUN_00401000(void)\n{\n\tstatic int count = f(1);\n}\n"}
    found = stackargs.members_of(sources)
    wanted = ({"Singleton", "A", "b"}, {"Uniform", "FUN_00401000"})
    return [] if found == wanted else [f"members_of gives {found}, not {wanted}"]


def check_is_method() -> list[str]:
    """is_method says whether a prototype defines a member function of a known class that takes a this: a
    constructor, a destructor and one that returns a qualified type count, a static member and a function of a
    namespace do not, and neither does a free function with a qualified parameter type."""
    classes, statics = {"A", "Timer"}, {"Uniform"}
    cases = [("int A::f()", True), ("A::A()", True), ("A::~A()", True), ("double Magic::Base::Timer::f()", True),
             ("float A::Uniform(float a)", False), ("int Magic::f()", False), ("int f(const std::string& a)", False),
             ("int f(void)", False)]
    return [f"is_method gives {found} for {proto}, not {wanted}" for proto, wanted in cases
            if (found := stackargs.is_method(proto, classes, statics)) != wanted]


def check_returned_type() -> list[str]:
    """returned_type gives the type that a prototype returns, without name and convention, or None without a
    parameter list."""
    cases = [("float f(int a)", "float"), ("double __cdecl f(void)", "double"), ("struct task *f()", "struct task *"),
             ("void __fastcall Foo::f(int a)", "void"), ("int x", None)]
    return [f"returned_type gives {found!r} for `{proto}`, not {wanted!r}" for proto, wanted in cases
            if (found := stackargs.returned_type(proto)) != wanted and (found or "").strip() != wanted]


def check_register_parameters() -> list[str]:
    """register_parameters gives the indexes of the parameters that travel in registers."""
    cases = [(["int"], [4], "__thiscall", [0]), ([], [], "__thiscall", []), (["int"], [4], None, []),
             (["int", "int", "int"], [4, 4, 4], "__fastcall", [0, 1]), (["float", "int"], [4, 4], "__fastcall", [1]),
             (["double", "int", "int"], [8, 4, 4], "__fastcall", [1, 2]), (["int"], [4], "__fastcall", [0]),
             (["struct a"], [None], "__fastcall", [0]), (["struct a"], [12], "__fastcall", [])]
    return [f"register_parameters gives {found} for {kinds}, {sizes} and {convention}, not {wanted}"
            for kinds, sizes, convention, wanted in cases
            if (found := stackargs.register_parameters(kinds, sizes, convention)) != wanted]


def check_x87_change() -> list[str]:
    """x87_change gives how far an x87 instruction moves the top of the stack: a load up one, a store that pops or
    an operation that pops down one or two, the rest none. An instruction it does not know gives None."""
    cases = [("fld", 1), ("fldz", 1), ("fild", 1), ("fstp", -1), ("fist", 0), ("fadd", 0), ("faddp", -1),
             ("fcomp", -1), ("fcompp", -2), ("fucompp", -2), ("fxch", 0), ("fchs", 0), ("fnstsw", 0), ("fldcw", 0),
             ("fscale", None), ("fprem", None)]
    return [f"x87_change gives {found} for {mnemonic}, not {wanted}" for mnemonic, wanted in cases
            if (found := stackargs.x87_change(mnemonic)) != wanted]


def check_library_change() -> list[str]:
    """library_change gives how far a library call moves the top of the x87 stack."""
    cases = [("_ftol2", -1), ("_ftol2_sse", -1), ("_CIpow", -1), ("_CIatan2", -1), ("_CIsin", 0), ("floor", 1),
             ("atan2", 1), ("memcpy", 0)]
    return [f"library_change gives {found} for {name}, not {wanted}" for name, wanted in cases
            if (found := stackargs.library_change(name)) != wanted]


def check_x87_exits() -> list[str]:
    """x87_exits gives the x87 depth before each instruction and the Exit at each ret and each jump out: the depth
    there and the open result, the game function whose float may still sit in st0 (None for none, UNKNOWN for a
    call to something else). A library call takes its effect from the library table, the cookie check leaves st0 as
    it was, and a callee that the answers name adds the float it leaves. An x87 instruction that is no load uses an
    open result on an empty stack, and a control instruction keeps it. A path ends in UNCLEAR at a load or a
    non-empty stack that meets an open result and at an unknown x87 instruction, and the other paths go on. It
    gives None for two depths at one instruction and a function with no exit."""
    load, store = "fld dword ptr [0x500000]", "fstp dword ptr [0x500000]"
    cookie, ftol, unknown = {0x409000: "__security_check_cookie"}, {0x409000: "_ftol2"}, stackargs.UNKNOWN
    leaves, leaves_none = {CALLEE: True}, {CALLEE: False}
    exit_, unclear = stackargs.Exit, stackargs.UNCLEAR
    cases = [
        ([load, "ret"], {}, {}, {exit_(1, None)}),
        (["ret"], {}, {}, {exit_(0, None)}),
        ([load, store, "ret"], {}, {}, {exit_(0, None)}),
        ([F, "ret"], {}, {}, {exit_(0, CALLEE)}),
        ([F, store, "ret"], {}, {}, {exit_(0, None)}),
        ([F, "fchs", "ret"], {}, {}, {exit_(1, None)}),
        ([F, "mov eax, 1", "ret"], {}, {}, {exit_(0, CALLEE)}),
        ([F, "fnstsw ax", "ret"], {}, {}, {exit_(0, CALLEE)}),
        (["jmp 0x402000"], {}, {}, {exit_(0, CALLEE)}),
        ([load, "call 0x409000", "ret"], ftol, {}, {exit_(0, None)}),
        (["call 0x409000", "ret"], {}, {}, {exit_(0, unknown)}),
        ([F, "call 0x409000", "ret"], cookie, {}, {exit_(0, CALLEE)}),
        (["test eax, eax", "je @4", F, "ret", "ret"], {}, {}, {exit_(0, CALLEE), exit_(0, None)}),
        ([F, "ret"], {}, leaves, {exit_(1, None)}),
        ([F, load, "faddp st(1), st0", "ret"], {}, leaves, {exit_(1, None)}),
        ([F, load, store, "ret"], {}, leaves_none, {exit_(0, None)}),
        (["jmp 0x402000"], {}, leaves, {exit_(1, None)}),
        ([F, load, store, "ret"], {}, {}, {unclear}),
        ([load, F, "fchs", "ret"], {}, {}, {unclear}),
        (["test eax, eax", "je @4", F, load, "ret"], {}, {}, {unclear, exit_(0, None)}),
        (["fscale", "ret"], {}, {}, {unclear}),
        (["test eax, eax", "je @4", load, "nop", "ret"], {}, {}, None),
        (["jmp @0"], {}, {}, None),
    ]
    failures = []
    for lines, library, found_before, wanted in cases:
        decoder, _ = callees(f=["ret"])
        function = build(lines)
        found = stackargs.x87_exits(function, {CODE: function, **decoder.functions}, library, found_before)
        if (found and found[1]) != wanted and not (found is None and wanted is None):
            failures.append(f"x87_exits gives {found} for {described(lines)} with {library} and {found_before}, "
                            f"not {wanted}")
    function = build([load, "nop", store, "ret"])
    depths = stackargs.x87_exits(function, {CODE: function}, {}, {})
    if depths is None or depths[0] != {CODE: 0, CODE + 1: 1, CODE + 2: 1, CODE + 3: 0}:
        failures.append(f"x87_exits gives {depths} for a load and a store, not the depths 0, 1, 1, 0")
    decoder, _ = callees(f=["ret"])
    function = build([load, store, F, load, "ret"])
    depths = stackargs.x87_exits(function, {CODE: function, **decoder.functions}, {}, {})
    if depths is None or depths[0] != {CODE: 0, CODE + 1: 1, CODE + 2: 0, CODE + 3: 0}:
        failures.append(f"x87_exits gives {depths} for a load after a call, not the depths 0, 1, 0, 0 up to it")
    return failures


def check_settle() -> list[str]:
    """settle says per function whether every exit leaves a float in st0 (True) or none does (False). An open result
    adds what its callee leaves. A function with exits that disagree, two values, a result of something unknown, a
    callee left out, an open float over a value, an UNCLEAR exit, or no flow is left out."""
    exit_, unknown = stackargs.Exit, stackargs.UNKNOWN
    flows = {1: ({}, {exit_(1, None)}), 2: ({}, {exit_(0, None)}), 3: ({}, {exit_(0, 1)}), 4: ({}, {exit_(0, 5)}),
             5: None, 6: ({}, {exit_(1, None), exit_(0, None)}), 7: ({}, {exit_(2, None)}),
             8: ({}, {exit_(0, unknown)}), 9: ({}, {exit_(0, 10)}), 10: ({}, {exit_(0, 9)}),
             11: ({}, {exit_(0, 3)}), 12: ({}, {exit_(0, 2)}), 13: ({}, {exit_(1, 2)}), 14: ({}, {exit_(1, 1)}),
             15: ({}, {exit_(0, None), stackargs.UNCLEAR})}
    found = {}
    stackargs.settle(flows, found)
    wanted = {1: True, 2: False, 3: True, 11: True, 12: False, 13: True}
    return [] if found == wanted else [f"settle gives {found}, not {wanted}"]


def check_leaves_float() -> list[str]:
    """leaves_float follows again the functions without an answer once a round answers more, so a load after a call
    to a callee that leaves a float or none is cleared. It gives the flow of each function too."""
    load, store = "fld dword ptr [0x500000]", "fstp dword ptr [0x500000]"
    cases = [([load, "ret"], [F, load, "faddp st(1), st0", "ret"], True),
             (["ret"], [F, load, "ret"], True), (["ret"], [F, load, store, "ret"], False)]
    failures = []
    for callee_lines, lines, wanted in cases:
        decoder, _ = callees(f=callee_lines)
        function = build(lines)
        found, flows = stackargs.leaves_float({CODE: function, **decoder.functions}, {})
        if found.get(CODE) != wanted or flows.get(CODE) is None:
            failures.append(f"leaves_float gives {found} and {flows} for {described(lines)} after a callee "
                            f"{described(callee_lines)}, not {wanted} for the function")
    return failures


def check_reads_float_result() -> list[str]:
    """reads_float_result says whether the first x87 instruction after a call uses st0: any that is no load. A call,
    a ret and a load end a path, a control instruction does not, and one path is enough."""
    load, store = "fld dword ptr [0x500000]", "fstp dword ptr [0x500000]"
    cases = [([F, store, "ret"], True), ([F, load, store, "ret"], False), ([F, "ret"], False),
             ([F, "mov eax, 1", "fadd dword ptr [0x500000]", "ret"], True), ([F, F, store, "ret"], False),
             ([F, "fnstsw ax", "fchs", "ret"], True), ([F, "test eax, eax", "je @4", "fchs", "ret"], True),
             ([F, "test eax, eax", "je @4", load, "ret"], False)]
    return [f"reads_float_result gives {found} for {described(lines)}, not {wanted}" for lines, wanted in cases
            if (found := stackargs.reads_float_result(function := build(lines), function.code[0])) != wanted]


def check_float_callers() -> list[str]:
    """float_callers counts, per game function that a call reaches, the calls that use st0 right after it returns
    and all the calls. A call with a value on the x87 stack already, or in a function whose x87 stack is unclear,
    does not count as using st0."""
    store = "fstp dword ptr [0x500000]"
    callee = build(["ret"], CALLEE)
    lines = [F, store, F, store, "ret"]
    function = build(lines)
    functions = {CODE: function, CALLEE: callee}
    exits = {stackargs.Exit(0, None)}
    cases = [({CODE: ({CODE: 0, CODE + 2: 0}, exits), CALLEE: None}, (2, 2)),
             ({CODE: ({CODE: 0, CODE + 2: 1}, exits), CALLEE: None}, (1, 2)),
             ({CODE: None, CALLEE: None}, (0, 2))]
    return [f"float_callers gives {found} for {described(lines)} with {flows}, not {{{CALLEE}: {wanted}}}"
            for flows, wanted in cases if (found := stackargs.float_callers(functions, flows)) != {CALLEE: wanted}]


def check_float_verdict() -> list[str]:
    """float_verdict says float-return when the declaration returns no float and a call uses st0, and
    no-float-return when it returns a float, no call uses st0 and the function leaves none."""
    cases = [(False, True, 2, "float-return"), (False, None, 1, "float-return"), (False, False, 0, None),
             (False, True, 0, None), (True, False, 0, "no-float-return"), (True, None, 0, None),
             (True, False, 1, None), (True, True, 0, None)]
    return [f"float_verdict gives {found} for {args}, not {wanted}" for *args, wanted in cases
            if (found := stackargs.float_verdict(*args)) != wanted]


def check_first_read() -> list[str]:
    """first_read gives the lowest address that reads a register before any write to it, and None when nothing
    does. A call may change ecx, so a read after it is no read of the argument."""
    cases = [(["mov eax, ecx", "ret"], x86.ECX, 0), (["mov ecx, 1", "mov eax, ecx", "ret"], x86.ECX, None),
             (["test eax, eax", "je @4", "mov ecx, 1", "nop", "mov eax, ecx", "ret"], x86.ECX, 4),
             (["mov edx, 1", "mov eax, ecx", "mov ebx, edx", "ret"], x86.EDX, None),
             ([F, "mov eax, ecx", "ret"], x86.ECX, None), (["ret"], x86.ECX, None),
             (["mov eax, dword ptr [edx + 8]", "ret"], x86.EDX, 0)]
    return [f"first_read gives {found} for {described(lines)} and {register}, not {wanted}"
            for lines, register, wanted in cases
            if (found := stackargs.first_read(build(lines), register)) != (None if wanted is None else CODE + wanted)]


def check_declared_scalar() -> list[str]:
    """declared_scalar gives the bytes, the kind and whether it is an array for a scalar declaration, and None for
    a struct. The type can hold the name too, as the c of `unsigned char c`."""
    cases = [("int DAT_1", (4, "int", False)), ("float DAT_1[4]", (4, "float", True)),
             ("unsigned char DAT_1", (1, "int", False)), ("struct task *DAT_1", (4, "int", False)),
             ("double DAT_1", (8, "float", False)), ("static const int DAT_1", (4, "int", False)),
             ("short DAT_1[2][3]", (2, "int", True)), ("struct Foo DAT_1", None), ("struct Foo DAT_1[2]", None)]
    named = [("unsigned char c", "c", (1, "int", False)), ("long g", "g", (4, "int", False)),
             ("int i[4]", "i", (4, "int", True)), ("struct x *x", "x", (4, "int", False))]
    return [f"declared_scalar gives {found} for `{decl}`, not {wanted}"
            for decl, name, wanted in [(decl, "DAT_1", wanted) for decl, wanted in cases] + named
            if (found := stackargs.declared_scalar(decl, name)) != wanted]


def check_use_fits() -> list[str]:
    """use_fits says whether an access can be to a scalar of a size and kind: the same width and kind, an int move
    of a float, or a dword int move of half a double."""
    use = stackargs.Use
    cases = [(use(0, 4, "float", False), 4, "float", True), (use(0, 4, "int", False), 4, "float", True),
             (use(0, 4, "float", False), 4, "int", False), (use(0, 1, "int", False), 4, "int", False),
             (use(0, 4, "int", False), 8, "float", True), (use(0, 4, "float", False), 8, "float", False),
             (use(0, 8, "float", False), 8, "float", True), (use(0, 8, "float", False), 4, "float", False)]
    return [f"use_fits gives {found} for {a_use}, {size} and {value}, not {wanted}"
            for a_use, size, value, wanted in cases if (found := stackargs.use_fits(a_use, size, value)) != wanted]


def check_width_conflict() -> list[str]:
    """width_conflict says a global is declared wrong when it has reads and none fits its width and kind. Writes do
    not count, and neither do the dword reads of an array of bytes or words."""
    use = stackargs.Use
    cases = [((4, "int", False), {use(0, 1, "int", False): [1]}, True),
             ((4, "int", False), {use(0, 1, "int", True): [1]}, False),
             ((4, "int", False), {use(0, 1, "int", False): [1], use(0, 4, "int", False): [2]}, False),
             ((1, "int", True), {use(0, 4, "int", False): [1]}, False),
             ((1, "int", False), {use(0, 4, "int", False): [1]}, True),
             ((4, "int", False), {use(0, 4, "float", False): [1]}, True),
             ((4, "float", False), {use(0, 2, "int", False): [1]}, True), ((4, "int", False), {}, False)]
    return [f"width_conflict gives {found} for {declared} and {uses}, not {wanted}"
            for declared, uses, wanted in cases if (found := stackargs.width_conflict(declared, uses)) != wanted]


def check_uses_text() -> list[str]:
    """uses_text names the kinds of access once each, in order."""
    use = stackargs.Use
    found = stackargs.uses_text({use(0, 4, "float", True): [1], use(0, 1, "int", False): [1],
                                 use(2, 1, "int", False): [2]})
    return [] if found == "byte int read, dword float written" else [f"uses_text gives {found!r}"]


def check_global_uses() -> list[str]:
    """global_uses gives, per known global, each kind of access to its bytes by an absolute address with the
    functions that make it: the offset, the width, int or float and whether it is only a write. A lea is no access."""
    namer = namer_of([dossier.Global(DATA, 4, "Foo", "int Foo")])
    use = stackargs.Use
    first = build(["mov eax, dword ptr [0x501000]", "mov byte ptr [0x501002], 1", "lea eax, [0x501000]",
                   "mov eax, dword ptr [0x509000]", "ret"])
    second = build(["fld dword ptr [0x501000]", "mov eax, dword ptr [0x501000]", "ret"], CALLEE)
    found = stackargs.global_uses({CODE: first, CALLEE: second}, namer)
    wanted = {DATA: {use(0, 4, "int", False): [CODE, CALLEE], use(2, 1, "int", True): [CODE],
                     use(0, 4, "float", False): [CALLEE]}}
    return [] if found == wanted else [f"global_uses gives {found}, not {wanted}"]


TASK_TYPES = """struct task {
    struct task *next;
    void (*exec)(struct task *);
    struct taskwk *twp;
};
static_assert(sizeof(task) == 0xc, "sizeof task");
static_assert(offsetof(task, next) == 0x0, "task::next");
static_assert(offsetof(task, exec) == 0x4, "task::exec");
static_assert(offsetof(task, twp) == 0x8, "task::twp");

struct taskwk {
    signed char mode;
    signed char smode;
    short flag;
    union {
        unsigned char b[4];
        float f;
    } counter;
};
static_assert(sizeof(taskwk) == 0x8, "sizeof taskwk");
static_assert(offsetof(taskwk, mode) == 0x0, "taskwk::mode");
static_assert(offsetof(taskwk, smode) == 0x1, "taskwk::smode");
static_assert(offsetof(taskwk, flag) == 0x2, "taskwk::flag");
static_assert(offsetof(taskwk, counter) == 0x4, "taskwk::counter");

struct Bits {
    int a : 3;
};
static_assert(sizeof(Bits) == 0x4, "sizeof Bits");
static_assert(offsetof(Bits, a) == 0x0, "Bits::a");

struct Hole {
    struct Missing m;
};
static_assert(sizeof(Hole) == 0x4, "sizeof Hole");
static_assert(offsetof(Hole, m) == 0x0, "Hole::m");

struct Unplaced {
    int a;
};
static_assert(sizeof(Unplaced) == 0x4, "sizeof Unplaced");
"""


def with_task_types(check) -> list[str]:
    """The failures of CHECK, which takes a names.Types of TASK_TYPES."""
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder) / "types.h"
        path.write_text(TASK_TYPES, encoding="utf-8")
        return check(names.Types(path))


def check_struct_leaves() -> list[str]:
    """struct_leaves gives the scalars of a struct with their offsets: a pointer for a pointer or function pointer,
    each member of a union from the union's start, and None for a bit field, a member of unknown layout, a member
    without an offsetof assert and a struct that is not there."""
    leaf = stackargs.Leaf
    cases = [("task", [leaf(0, 4, "pointer"), leaf(4, 4, "pointer"), leaf(8, 4, "pointer")]),
             ("taskwk", [leaf(0, 1, "int"), leaf(1, 1, "int"), leaf(2, 2, "int"), leaf(4, 1, "int"),
                         leaf(5, 1, "int"), leaf(6, 1, "int"), leaf(7, 1, "int"), leaf(4, 4, "float")]),
             ("Bits", None), ("Hole", None), ("Unplaced", None), ("Nothing", None)]

    def check(types):
        return [f"struct_leaves gives {found} for {name}, not {wanted}" for name, wanted in cases
                if (found := stackargs.struct_leaves(types, name)) != wanted]
    return with_task_types(check)


def check_fits_struct() -> list[str]:
    """fits_struct says an access can be to a struct when a float access meets a float scalar of the same offset
    and width, an int access lies over scalars, and a byte or a word lies over no pointer."""
    use = stackargs.Use
    cases = [(use(4, 4, "float", False), False, True), (use(0, 1, "int", False), False, True),
             (use(0, 4, "int", False), True, True), (use(8, 4, "int", False), True, False),
             (use(1, 4, "int", False), True, True), (use(0xc, 4, "int", False), False, False),
             (use(4, 2, "int", False), False, True), (use(8, 2, "int", False), False, False),
             (use(6, 4, "float", False), False, False)]

    def check(types):
        failures = []
        for a_use, on_task, on_taskwk in cases:
            for name, wanted in (("task", on_task), ("taskwk", on_taskwk)):
                found = stackargs.fits_struct(stackargs.struct_leaves(types, name), a_use)
                if found != wanted:
                    failures.append(f"fits_struct gives {found} for {a_use} on {name}, not {wanted}")
        return failures
    return with_task_types(check)


def check_struct_confusion() -> list[str]:
    """struct_confusion gives the other struct of the task and taskwk pair when every access fits it and one does
    not fit the declared one. It gives None when the accesses fit both or neither, when there are none and when a
    layout is unknown."""
    use = stackargs.Use
    cases = [("task", {use(4, 4, "float", False)}, "taskwk"), ("task", {use(0, 1, "int", False)}, "taskwk"),
             ("task", {use(0, 4, "int", False)}, None), ("task", {use(0x10, 4, "int", False)}, None),
             ("task", set(), None), ("taskwk", {use(8, 4, "int", False)}, "task"),
             ("taskwk", {use(4, 4, "float", False)}, None), ("taskwk", {use(0xc, 4, "int", False)}, None),
             ("taskwk", {use(8, 4, "int", False), use(4, 4, "float", False)}, None)]

    def check(types):
        failures = []
        for declared, uses, wanted in cases:
            if (found := stackargs.struct_confusion(declared, uses, types)) != wanted:
                failures.append(f"struct_confusion gives {found} for {declared} and {uses}, not {wanted}")
        return failures
    return with_task_types(check)


def check_pointer_uses() -> list[str]:
    """pointer_uses gives the accesses through the pointer that a function takes at a stack slot: the offset from
    the pointer, the width and int or float. It follows a copy of the pointer in a register, reads the slot at
    [ebp + n] with a frame and at [esp + n - 4] without, and ignores the other parameters. It gives None without a
    frame when ebp is used for something else, and when two paths reach one instruction with different esp."""
    use = stackargs.Use
    frame = ["push ebp", "mov ebp, esp"]
    cases = [
        (frame + ["mov eax, dword ptr [ebp + 8]", "fld dword ptr [eax + 4]", "movzx ecx, byte ptr [eax + 1]",
                  "mov edx, dword ptr [ebp + 0xc]", "mov ecx, dword ptr [edx]", "pop ebp", "ret"], 8,
         {use(4, 4, "float", False), use(1, 1, "int", False)}),
        (frame + ["mov eax, dword ptr [ebp + 0xc]", "mov esi, eax", "mov ecx, dword ptr [esi + 0x10]", "pop ebp",
                  "ret"], 0xc, {use(0x10, 4, "int", False)}),
        (frame + ["mov eax, dword ptr [ebp + 8]", "pop ebp", "ret"], 8, set()),
        (["mov eax, dword ptr [esp + 4]", "fld dword ptr [eax + 8]", "ret"], 8, {use(8, 4, "float", False)}),
        (["mov eax, dword ptr [esp + 8]", "mov ecx, dword ptr [eax]", "ret"], 0xc, {use(0, 4, "int", False)}),
        (["mov eax, dword ptr [ebp + 8]", "ret"], 8, None),
        (["test eax, eax", "je @3", "push eax", "ret"], 8, None),
    ]
    failures = []
    for lines, slot, wanted in cases:
        decoder, sizes = callees()
        found = stackargs.pointer_uses(build(lines), decoder, sizes, slot)
        if found != wanted:
            failures.append(f"pointer_uses gives {found} for {described(lines)} at {slot}, not {wanted}")
    return failures


def check_pointer_slots() -> list[str]:
    """pointer_slots gives the struct and the [ebp + n] slot of each parameter declared as a pointer to a task or a
    taskwk, with the sizes of the parameters before it counted. It is empty for a convention that passes registers
    and stops at a parameter of unknown size."""
    cases = [("void f(struct task *tp, int a, struct taskwk *twp)", [("task", 8), ("taskwk", 16)]),
             ("void f(struct taskwk *twp)", [("taskwk", 8)]), ("void __fastcall f(struct task *tp)", []),
             ("void __thiscall f(struct task *tp)", []), ("void f(double d, struct task *tp)", [("task", 16)]),
             ("void f(struct Unknown u, struct task *tp)", []), ("void f(const struct task *tp)", [("task", 8)]),
             ("void f(struct task **tpp)", []), ("void f(void)", []), ("int x", [])]

    def check(types):
        return [f"pointer_slots gives {found} for `{proto}`, not {wanted}" for proto, wanted in cases
                if (found := stackargs.pointer_slots(proto, types)) != wanted]
    return with_task_types(check)


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_saved_offset, check_arguments_passed, check_arguments_read, check_parameter_bytes,
                  check_verdict, check_unexplained_registers, check_members_of, check_is_method,
                  check_returned_type, check_register_parameters, check_x87_change, check_library_change,
                  check_x87_exits, check_settle, check_leaves_float,
                  check_reads_float_result, check_float_callers, check_float_verdict, check_first_read,
                  check_declared_scalar, check_use_fits, check_width_conflict, check_uses_text, check_global_uses,
                  check_struct_leaves, check_fits_struct, check_struct_confusion, check_pointer_uses,
                  check_pointer_slots):
        failures += check()
    return failures
