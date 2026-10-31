"""Checks for tools/tricks.py: which function definitions match only through a trick, not plain C. Also how
`check.py fn` reports such a function."""

import contextlib
import io
import tempfile
from pathlib import Path

import names
import project
import report
import tricks

TARGET = project.game_config().target


def annotated(kind, address, *body):
    return [f"// {kind}: {TARGET} 0x{address:08x}", *body]


def function(address, *statements, kind="FUNCTION", head=()):
    return [*head, *annotated(kind, address, f"void FUN_{address:08x}(void)", "{", *statements, "}"), ""]


def check_file_tricks() -> list[str]:
    """Each trick counts in its own definition. A file-level pragma that changes the code counts in every definition
    after it until a reset, and a harmless pragma counts nowhere. A trick word in a comment or a string, or in a stub,
    counts nowhere, and a definition with no closing line is left out. A word counts once per definition. A definition
    ends at the brace that closes its body: in a class, a member function's own, and a `}` at the start of a line inside
    the body is no end."""
    cases = [(function(0x401000, "\tx = 1;"), {}),
             (function(0x401000, "\t__asm mov eax, ecx"), {0x401000: "__asm"}),
             (function(0x401000, "\t__asm { nop }", kind="STUB"), {}),
             (annotated("FUNCTION", 0x401000, "__declspec( naked ) void FUN_00401000(void)", "{", "\t__emit 0x90",
                        "}"), {0x401000: "__declspec(naked), __emit"}),
             (function(0x401000, "\tv = ((volatile struct task *)tp)->fwp;"), {0x401000: "volatile"}),
             (function(0x401000, "\tx = 1;", head=["__declspec(safebuffers)"]),
              {0x401000: "__declspec(safebuffers)"}),
             (annotated("FUNCTION", 0x401000, "static __declspec( noinline ) void FUN_00401000(void)", "{", "\tx = 1;",
                        "}"), {0x401000: "__declspec(noinline)"}),
             (function(0x401000, "\tstruct forcewk *__restrict f;", "\tx = f->x;"), {0x401000: "__restrict"}),
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
             (function(0x401000, "\t__asm nop", "\t__asm nop"), {0x401000: "__asm"}),
             (["class Foo", "{", "public:",
               *annotated("FUNCTION", 0x401000, "\tvoid Bar(void)", "\t{", "\t\tx = 1;", "\t}"), "};", "",
               *function(0x401010, "\tv = ((volatile struct task *)tp)->fwp;")], {0x401010: "volatile"}),
             (function(0x401000, "\tswitch (x)", "\t{", "}", "\tv = ((volatile struct task *)tp)->fwp;"),
              {0x401000: "volatile"})]
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


def check_report_function() -> list[str]:
    """`check.py fn` counts a function at 100% only through a trick as a miss and names the trick. Plain C at 100% is
    a match."""
    entry = {"name": "FUN_00401000", "matching": 1.0}
    cases = [(None, True, "0x00401000 FUN_00401000: 100% match.\n"),
             ("__asm", False, "0x00401000 FUN_00401000: 100%, but only through a trick (__asm). It does not count as "
                              "matched until it is plain C.\n")]
    failures = []
    for trick, wanted, text in cases:
        out = io.StringIO()
        with contextlib.redirect_stdout(out):
            found = report.report_function(0x401000, entry, None, trick)
        if (found, out.getvalue()) != (wanted, text):
            failures.append(f"report_function gives {found} and {out.getvalue()!r} for trick {trick}, "
                            f"not {wanted} and {text!r}")
    return failures


def check_report_miss_without_diff() -> list[str]:
    """`check.py fn --no-diff` gives a miss its score line and runs no reccmp for its diff."""
    entry = {"name": "FUN_00401000", "matching": 0.5}
    calls = []
    reccmp = report.runner.reccmp
    report.runner.reccmp = lambda *args, cwd: calls.append(args) or ("", [])
    out = io.StringIO()
    try:
        with contextlib.redirect_stdout(out):
            found = report.report_function(0x401000, entry, None, None, diffs=False)
    finally:
        report.runner.reccmp = reccmp
    wanted = "0x00401000 FUN_00401000: 50.00% match.\n"
    if (found, out.getvalue(), calls) != (False, wanted, []):
        return [f"report_function without diffs gives {found}, {out.getvalue()!r} and {len(calls)} reccmp runs, "
                f"not False, {wanted!r} and none"]
    return []


def check_volatile_globals() -> list[str]:
    """A file-level declaration with `volatile` gives its name; a volatile local, a volatile member, a comment and a
    string give none. A function that uses such a global has the trick, one that doesn't has none."""
    text = "\n".join(["extern volatile int g_tick;", "volatile float g_rate = 1.0f;", "int plain;",
                      "struct s {", "\tvolatile int member;", "};", "// volatile int g_comment;",
                      'const char *text = "volatile";', *function(0x401000, "\tvolatile int local;"),
                      *function(0x401010, "\tx = g_tick * 2;"), *function(0x401020, "\tx = plain;")])
    failures = []
    found = tricks.volatile_globals(text)
    if found != {"g_tick", "g_rate"}:
        failures.append(f"volatile_globals gives {found}, not g_tick and g_rate")
    tricked = tricks.file_tricks(text, found)
    wanted = {0x401000: "volatile", 0x401010: "volatile global g_tick"}
    if tricked != wanted:
        failures.append(f"file_tricks with the volatile globals gives {tricked}, not {wanted}")
    return failures


def check_fake_tricks() -> list[str]:
    """With FAKES, the kinds of a definition's fake-match lines are tricks too, each once. FAKES gets the lines from the
    annotation to the closing one, and never a stub's."""
    seen = []

    def fakes(func):
        seen.append(func[0])
        return ["unused_local", "raw_address", "unused_local"] if "\tint y;" in func else []

    text = "\n".join([*function(0x401000, "\tint y;", "\tx = 0x450000;", head=["__declspec(safebuffers)"]),
                      *function(0x401010, "\tx = 1;"), *function(0x401020, "\tint y;", kind="STUB")])
    found = tricks.file_tricks(text, fakes=fakes)
    wanted = {0x401000: "__declspec(safebuffers), fake match unused_local, fake match raw_address"}
    failures = [] if found == wanted else [f"file_tricks with fakes gives {found}, not {wanted}"]
    if seen != [f"// FUNCTION: {TARGET} 0x00401000", f"// FUNCTION: {TARGET} 0x00401010"]:
        failures.append(f"fakes got the definitions that start {seen}")
    return failures


def check_scan_needs_src() -> list[str]:
    """A scan of a root with no src folder stops, so a wrong root can't turn every trick function into a match."""
    with tempfile.TemporaryDirectory() as empty:
        try:
            tricks.scan(Path(empty))
        except SystemExit:
            return []
    return ["tricks.scan of a root with no src folder found nothing instead of stopping"]


def run() -> list[str]:
    """Every check of this module, in order."""
    failures = []
    for check in (check_forbidden, check_file_tricks, check_declarator_start, check_report_function,
                  check_report_miss_without_diff, check_volatile_globals, check_fake_tricks, check_scan_needs_src):
        failures += check()
    return failures
