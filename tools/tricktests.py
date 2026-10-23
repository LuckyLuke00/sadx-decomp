"""Checks for tools/tricks.py: which function definitions match only through a trick, not plain C."""

import names
import project
import tricks

TARGET = project.game_config().target


def annotated(kind, address, *body):
    return [f"// {kind}: {TARGET} 0x{address:08x}", *body]


def function(address, *statements, kind="FUNCTION", head=()):
    return [*head, *annotated(kind, address, f"void FUN_{address:08x}(void)", "{", *statements, "}"), ""]


def check_file_tricks() -> list[str]:
    """Each trick counts in its own definition. A file-level pragma that changes the code counts in every definition
    after it until a reset, and a harmless pragma counts nowhere. A trick word in a comment or a string, or in a stub,
    counts nowhere, and a definition with no closing line is left out. A word counts once per definition."""
    cases = [(function(0x401000, "\tx = 1;"), {}),
             (function(0x401000, "\t__asm mov eax, ecx"), {0x401000: "__asm"}),
             (function(0x401000, "\t__asm { nop }", kind="STUB"), {}),
             (annotated("FUNCTION", 0x401000, "__declspec( naked ) void FUN_00401000(void)", "{", "\t__emit 0x90",
                        "}"), {0x401000: "__declspec(naked), __emit"}),
             (function(0x401000, "\tv = ((volatile struct task *)tp)->fwp;"), {0x401000: "volatile"}),
             (function(0x401000, "\tx = 1;", head=["__declspec(safebuffers)"]),
              {0x401000: "__declspec(safebuffers)"}),
             (["int g;", *function(0x401000, "\tx = 1;")], {}),
             (function(0x401000, '\tputs("__asm volatile");', "\tx = 1; // __asm", "\t/* #pragma once */"), {}),
             (["#pragma auto_inline(off)", *function(0x401000), *function(0x401010), "#pragma auto_inline()",
               *function(0x401020)],
              {0x401000: "after #pragma auto_inline(off)", 0x401010: "after #pragma auto_inline(off)"}),
             ([*function(0x401000), "#pragma inline_depth(0)", *function(0x401010), "#pragma inline_depth()"],
              {0x401010: "after #pragma inline_depth(0)"}),
             (['#pragma optimize("", off)', *function(0x401000), '#pragma optimize("", on)', *function(0x401010)],
              {0x401000: 'after #pragma optimize("",off)'}),
             (["#pragma once", "#pragma warning(disable: 4244)", "#pragma pack(push, 1)", *function(0x401000)], {}),
             (["/*", "#pragma auto_inline(off)", "*/", *function(0x401000)], {}),
             (function(0x401000, "\t#pragma warning(disable: 4244)"), {0x401000: "#pragma"}),
             (["#pragma auto_inline(off)", *function(0x401000), "#pragma auto_inline(on)", *function(0x401010)],
              {0x401000: "after #pragma auto_inline(off)"}),
             (['__pragma(optimize("", off))', "", *function(0x401000), '__pragma(optimize("", on))', "",
               *function(0x401010)], {0x401000: 'after #pragma optimize("",off)'}),
             (annotated("FUNCTION", 0x401000, "void FUN_00401000(void)", "{", "\t__asm nop"), {}),
             (function(0x401000, "\t__asm nop", "\t__asm nop"), {0x401000: "__asm"})]
    failures = []
    for lines, wanted in cases:
        found = tricks.file_tricks("\n".join(lines))
        if found != wanted:
            failures.append(f"file_tricks gives {found} for {lines}, not {wanted}")
    return failures


def check_declarator_start() -> list[str]:
    """A declarator line right above an annotation belongs to the definition below it. A blank line, a statement end,
    a block end or a preprocessor line ends the walk up."""
    cases = [(["}", "__declspec(safebuffers)", "// FUNCTION: x"], 2, 1),
             (["}", "", "// FUNCTION: x"], 2, 2),
             (["int g;", "// FUNCTION: x"], 1, 1),
             (["#include \"a.h\"", "static", "// FUNCTION: x"], 2, 1),
             (["static", "__declspec(safebuffers)", "// FUNCTION: x"], 2, 0)]
    failures = []
    for lines, annotation, wanted in cases:
        blank = names.blank_literals("\n".join(lines)).split("\n")
        found = tricks.declarator_start(lines, blank, annotation)
        if found != wanted:
            failures.append(f"declarator_start gives {found} for {lines}, not {wanted}")
    return failures


def check_forbidden() -> list[str]:
    """Inline assembly, `__emit`, `__declspec(naked)`, `#pragma` and `__pragma` count, in each spelling, without their
    blanks. The same words in a string, a comment over several lines or a longer name do not."""
    cases = [(["__asm mov eax, ecx"], ["__asm"]),
             (["void Foo(void)", "{", "\t__asm {", "\t\tmov eax, 1", "\t}", "}"], ["__asm"]),
             (["_asm int 3"], ["_asm"]),
             (['asm("nop");'], ["asm"]),
             (["__emit 0x90"], ["__emit"]),
             (["__declspec( naked ) void Foo(void)"], ["__declspec(naked)"]),
             (['#pragma optimize("", off)', "# pragma pack(1)"], ["#pragma", "#pragma"]),
             (['__pragma(optimize("", off))'], ["__pragma"]),
             (['puts("__asm");', "c = '#';", "x = 1; // __asm"], []),
             (["/* the", "__asm block is gone", "*/ x = 1;"], []),
             (["int basm_count = asm_size;", "__declspec(dllexport) void Foo(void)"], []),
             (["/* a */ x = 1;", "__asm nop", "y = 2; /* b */"], ["__asm"])]
    failures = []
    for lines, wanted in cases:
        found = tricks.forbidden(lines)
        if found != wanted:
            failures.append(f"forbidden gives {found} for {lines}, not {wanted}")
    return failures


def run() -> list[str]:
    """Every check of this module, in order."""
    failures = []
    for check in (check_forbidden, check_file_tricks, check_declarator_start):
        failures += check()
    return failures
