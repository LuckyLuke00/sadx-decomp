"""Tests of the declaration and name repairs in tools/llm.py: the helpers that drop, add, rename or cast a
declaration when the build output flags a name, and the readers of that output.

run() returns the failures as "<helper> gives <found> for <input>, not <wanted>".
"""

import llm
import names

ANN = "// FUNCTION: SADX 0x00401000"


def check_signature_index() -> list[str]:
    """The signature is the first line after the annotation that is not blank and not a `//` comment, also when it
    is indented, and names.parse_annotations reads the same line."""
    cases = [([ANN, "void Foo(void)", "{", "}"], 1),
             ([ANN, "", "// note", "\t// indented note", "   ", "void Foo(void)", "{", "}"], 5),
             ([ANN, "// FUNCTION: SADX 0x00401004", "static void Foo(void)", "{", "}"], 2),
             ([ANN, "// void Bar(void)", "static int Foo(int a)", "{", "// not a signature", "}"], 2)]
    failures = []
    for func, wanted in cases:
        found = llm.signature_index(func)
        if found != wanted:
            failures.append(f"signature_index gives {found} for {func}, not {wanted}")
            continue
        read = names.parse_annotations("\n".join(func))[0][2]
        if read != " ".join(func[wanted].split()):
            failures.append(f"parse_annotations reads `{read}` for {func}, not the line at {wanted}")
    return failures


def check_without_static() -> list[str]:
    """`static` goes from the signature line only, also when a comment or a blank line sits between the annotation
    and the signature. The result is None when the signature has no `static`, when SHARED is None, or when the
    name is in SHARED. A `static` in the body stays."""
    body = ["{", "    static int count;", "}"]
    cases = [([ANN, "static void Foo(void)", *body], set(), [ANN, "void Foo(void)", *body]),
             ([ANN, "// note", "static void Foo(void)", *body], set(), [ANN, "// note", "void Foo(void)", *body]),
             ([ANN, "", "  // note", "static void Foo(void)", *body], {"Bar"},
              [ANN, "", "  // note", "void Foo(void)", *body]),
             ([ANN, "static   char *Foo(int a)", *body], set(), [ANN, "char *Foo(int a)", *body]),
             ([ANN, "static\tvoid Foo(void)", *body], set(), [ANN, "void Foo(void)", *body]),
             ([ANN, "// static void Bar(void)", "void Foo(void)", *body], set(), None),
             ([ANN, "static_type Foo(void)", *body], set(), None),
             ([ANN, "static void Foo(void)", *body], {"Foo", "Bar"}, None),
             ([ANN, "// note", "static void Foo(void)", *body], {"Foo"}, None),
             ([ANN, "static void Foo(void)", *body], None, None)]
    failures = []
    for func, shared, wanted in cases:
        before = list(func)
        found = llm.without_static(func, shared)
        if found != wanted:
            failures.append(f"without_static gives {found} for {func} and {shared}, not {wanted}")
        if func != before:
            failures.append(f"without_static changes its input {before} to {func}")
    return failures


WRAP_BASE = "\n".join(['#include "x.h"', "", "// FUNCTION: SADX 0x00001000", "void Exec(void)", "{", "}", ""])
WRAPPED = [llm.OFF, llm.ON]


def stub_lines(address: int, sig: str) -> list[str]:
    """The lines of a STUB at ADDRESS with the signature SIG."""
    return [f"// STUB: SADX 0x{address:08x}", sig, "{", "}"]


def pragma_lines(text: str) -> list[str]:
    """The #pragma lines of TEXT, in order."""
    return [line for line in text.split("\n") if line.startswith("#pragma")]


def check_wrapped_stubs() -> list[str]:
    """A static STUB that apply_function writes sits between pragma optimize off and on. A function replaces it
    together with the pair, a second stub goes above the pair of a later one, a rewritten stub keeps one pair, and a
    global stub gets none. No definition is left unclosed."""
    one = llm.apply_function(WRAP_BASE, 0x500, [], stub_lines(0x500, "static void Draw(void)"))
    two = llm.apply_function(one, 0x300, [], stub_lines(0x300, "static void Disp(void)"))
    function = ["// FUNCTION: SADX 0x00000500", "static void Draw(void)", "{", "\tmarker();", "}"]
    rewritten = llm.apply_function(two, 0x500, [], stub_lines(0x500, "static void Draw(void)"))
    global_stub = llm.apply_function(WRAP_BASE, 0x500, [], stub_lines(0x500, "void Draw(void)"))
    cases = [("one stub", pragma_lines(one), WRAPPED),
             ("a second stub above the first", pragma_lines(two), WRAPPED * 2),
             ("a function over a stub", pragma_lines(llm.apply_function(two, 0x500, [], function)), WRAPPED),
             ("a stub over a stub", pragma_lines(rewritten), WRAPPED * 2),
             ("a global stub", pragma_lines(global_stub), [])]
    failures = [f"apply_function leaves {found} for {what}, not {wanted}" for what, found, wanted in cases
                if found != wanted]
    if llm.unclosed_definitions(two.split("\n")):
        failures.append(f"apply_function leaves an unclosed definition in {two!r}")
    return failures


def check_definition_block() -> list[str]:
    """definition_block is a wrapped stub's definition_span plus its pair, and the span of a definition without one."""
    lines = llm.apply_function(WRAP_BASE, 0x500, [], stub_lines(0x500, "static void Draw(void)")).split("\n")
    failures = []
    block, span = llm.definition_block(lines, 0x500), llm.definition_span(lines, 0x500)
    if block != (span[0] - 1, span[1] + 1):
        failures.append(f"definition_block gives {block} for a wrapped stub, not the span {span} plus its pair")
    plain = WRAP_BASE.split("\n")
    if llm.definition_block(plain, 0x1000) != llm.definition_span(plain, 0x1000):
        failures.append("definition_block widens a definition that has no pair")
    return failures


def check_stub_functions_wrap() -> list[str]:
    """stub_functions wraps the stub of a static function, and not the stub of a global one."""
    failures = []
    stubbed = llm.stub_functions(WRAP_BASE, [0x1000])
    if pragma_lines(stubbed):
        failures.append(f"stub_functions wraps a global stub in {stubbed!r}")
    static = llm.stub_functions(WRAP_BASE.replace("void Exec", "static void Exec"), [0x1000])
    if pragma_lines(static) != WRAPPED:
        failures.append(f"stub_functions leaves {pragma_lines(static)} for a static function, not a wrapped stub")
    return failures


def check_cast_calls() -> list[str]:
    """Each call to a clashed name goes through a pointer of the type its declaration gives, without `extern`, with
    parameter names dropped. Other names, members, names with a longer name round them, and names not clashed stay.
    The annotation, the comments above the signature and the signature itself stay, also when the function is
    the clashed name. A name that has no declaration stays."""
    body = ["{", "    Foo(a, 2);", "    x = Bar(3) + Foo(1, 2);", "    p->Foo(1); q.Foo(2); MyFoo(3); Foo2(4); Foo;",
            "    Foo (5);", "}"]
    pointer_foo = "((void (*)(int, int))Foo)"
    decls = ["void Foo(int a, int b);", "extern char *Bar(void);", "static int Baz(void);", "int Qux(int);"]
    cases = [([ANN, "static void Run(void)", *body], decls, {"Foo"},
              [ANN, "static void Run(void)", "{", f"    {pointer_foo}(a, 2);", f"    x = Bar(3) + {pointer_foo}(1, 2);",
               f"    p->Foo(1); q.Foo(2); MyFoo(3); Foo2(4); Foo;", f"    {pointer_foo}(5);", "}"]),
             ([ANN, "static void Run(void)", "{", "    x = Bar(3);", "}"], decls, {"Bar"},
              [ANN, "static void Run(void)", "{", "    x = ((char *(*)(void))Bar)(3);", "}"]),
             ([ANN, "static void Run(void)", "{", "    Baz(1); Qux(2); Zed(3);", "}"], decls, {"Baz", "Zed"},
              [ANN, "static void Run(void)", "{", "    Baz(1); Qux(2); Zed(3);", "}"]),
             ([ANN, "static void Run(void)", "{", "    Foo(1, 2); Bar(3);", "}"], decls, set(),
              [ANN, "static void Run(void)", "{", "    Foo(1, 2); Bar(3);", "}"]),
             ([ANN, "// note: Foo(1)", "", "static void Foo(int a, int b)", "{", "    Foo(a, b);", "}"], decls, {"Foo"},
              [ANN, "// note: Foo(1)", "", "static void Foo(int a, int b)", "{", f"    {pointer_foo}(a, b);", "}"])]
    failures = []
    for func, declared, clashed, wanted in cases:
        found = llm.cast_calls(func, declared, clashed)
        if found != wanted:
            failures.append(f"cast_calls gives {found} for {func} and {sorted(clashed)}, not {wanted}")
    return failures


def check_one_edit_apart() -> list[str]:
    """Two strings are one edit apart when they are equal or differ by one character changed, added or left out,
    at the start, in the middle or at the end. Two changes, a swap of two different characters and a length
    difference of two are not one edit."""
    cases = [("00501000", "00501000", True), ("", "", True), ("", "a", True), ("a", "", True), ("", "ab", False),
             ("00501000", "00501001", True), ("00501000", "10501000", True), ("00501000", "00501011", False),
             ("0050100", "00501000", True), ("00501000", "0050100", True), ("0501000", "00501000", True),
             ("0050100", "00510000", False), ("0501000", "0050100", False), ("ab", "ba", False),
             ("00501000", "005010", False), ("00501000", "0501", False)]
    return [f"one_edit_apart gives {found} for {a!r} and {b!r}, not {wanted}"
            for a, b, wanted in cases if (found := llm.one_edit_apart(a, b)) != wanted]


def check_short_globals() -> list[str]:
    """A flagged DAT_ name with fewer than 8 digits maps to the DAT_ name of an address in the prompt: its digits with
    zeros in front, else the only address one edit apart. The prompt names addresses as DAT_ names or as 0x
    numbers of 6 to 8 digits. No fix for two near addresses, for no address, for a name with 8 digits or for a
    name that is not a DAT_ name. The padded address wins over a near one."""
    prompt = "uses DAT_00501000 and DAT_00501001, mov eax, [0x00502010], call 0x4010"
    cases = [(["DAT_501000"], prompt, {"DAT_501000": "DAT_00501000"}),
             (["DAT_0050201"], prompt, {"DAT_0050201": "DAT_00502010"}),
             (["DAT_0501000"], prompt, {"DAT_0501000": "DAT_00501000"}),
             (["DAT_0050100"], prompt, {}),
             (["DAT_00501000"], prompt, {}),
             (["DAT_99999"], prompt, {}),
             (["FUN_501000", "Foo", "DAT_"], prompt, {}),
             (["DAT_501000"], "", {}),
             (["DAT_502010", "DAT_50100"], "x 0x502010 y 0x00502010 DAT_00501000", {"DAT_502010": "DAT_00502010"}),
             ([], prompt, {})]
    failures = []
    for flagged, text, wanted in cases:
        found = llm.short_globals(flagged, text)
        if found != wanted:
            failures.append(f"short_globals gives {found} for {flagged} and {text!r}, not {wanted}")
    return failures


def check_ftol_casts() -> list[str]:
    """Each call of a float to int helper, in any of its five names and with a space before the bracket, becomes
    `((long)(x))`. Brackets inside the argument stay balanced. A call that is not closed on the line, and
    every call after it, stays as it is. A line without a call, a name that only ends in a helper's name and a
    member of that name stay."""
    cases = [("x = _ftol2_sse(a[i] * (b + c)) + _ftol2_sse(d);", "x = ((long)(a[i] * (b + c))) + ((long)(d));"),
             ("_ftol2_sse(a) + _ftol2(b) + __ftol2_sse(c) + __ftol2(d) + _ftol(e)",
              "((long)(a)) + ((long)(b)) + ((long)(c)) + ((long)(d)) + ((long)(e))"),
             ("return _ftol2_sse (a * 2.0f);", "return ((long)(a * 2.0f));"),
             ("x = _ftol2_sse(a +", "x = _ftol2_sse(a +"),
             ("x = _ftol2_sse(a * (b", "x = _ftol2_sse(a * (b"),
             ("_ftol2_sse(a) + _ftol2_sse(b *", "((long)(a)) + _ftol2_sse(b *"),
             ("_ftol2_sse(a * (b +", "_ftol2_sse(a * (b +"),
             ("my_ftol(a); s._ftol(a); p->_ftol(a); _ftol2_sse_x(a); y = _ftol2_sse;",
              "my_ftol(a); s._ftol(a); p->_ftol(a); _ftol2_sse_x(a); y = _ftol2_sse;"),
             ("x = a + b;", "x = a + b;"),
             ("", "")]
    return [f"ftol_casts gives {found!r} for {line!r}, not {wanted!r}"
            for line, wanted in cases if (found := llm.ftol_casts(line)) != wanted]


def check_with_renames_names() -> list[str]:
    """The names that the build output flags are written another way in the declarations and the function: a global
    with digits missing (flagged as undeclared or as an unresolved variable), the name that decls says to use,
    a runtime function under another name and a Ghidra type. Only names that the code uses change, a name that
    is not flagged stays, and a member of that name stays. The renames come back as old: new. The declarations
    that read the same afterwards are one. Without a rename the inputs come back as they are."""
    prompt = "DAT_00501000 and 0x00502010 in the dossier"
    decls = ["extern int DAT_501000;", "extern int DAT_00501000;", "extern int DAT_0050201;", "unsigned short Flag;"]
    func = [ANN, "static void Run(void)", "{", "    DAT_501000 = DAT_0050201 + sqrtf(x) + p->uint + s.sqrtf;",
            "    uint v = ushort_x + ushort;", "    MyFUN_00401000(1); FUN_00401000(FUN_00401000x);", "}"]
    text = "\n".join(["a.c(4) : error C2065: 'DAT_501000' : undeclared identifier",
                      'b.obj : error LNK2001: unresolved external symbol "int DAT_0050201" (?DAT_0050201@@3HA)',
                      "a.c(5) : error C3861: 'sqrtf': identifier not found",
                      "a.c(6) : error C2065: 'uint' : undeclared identifier",
                      "a.c(7) : error C2065: 'unflagged_name' : undeclared identifier",
                      "decls: FUN_00401000 has the name Foo: use that",
                      "decls: FUN_00403000 has the name Bar: use that"])
    wanted_renames = {"DAT_501000": "DAT_00501000", "DAT_0050201": "DAT_00502010", "sqrtf": "sqrt",
                      "uint": "unsigned int", "FUN_00401000": "Foo"}
    wanted_decls = ["extern int DAT_00501000;", "extern int DAT_00502010;", "unsigned short Flag;"]
    wanted_func = [ANN, "static void Run(void)", "{", "    DAT_00501000 = DAT_00502010 + sqrt(x) + p->uint + s.sqrtf;",
                   "    unsigned int v = ushort_x + ushort;", "    MyFUN_00401000(1); Foo(FUN_00401000x);", "}"]
    cases = [(decls, func, text, prompt, (wanted_decls, wanted_func, wanted_renames)),
             (["void sqrtf(int);"], ["sqrtf(1); _CIsin(2); __builtin_memcpy(3); memset(4);"],
              "error C3861: 'sqrtf': x\nerror C3861: '_CIsin': x\nerror C3861: '__builtin_memcpy': x",
              "", (["void sqrt(int);"], ["sqrt(1); sin(2); memcpy(3); memset(4);"],
                   {"sqrtf": "sqrt", "_CIsin": "sin", "__builtin_memcpy": "memcpy"})),
             (["extern int A;", "extern int A;"], ["use A;"], "", prompt,
              (["extern int A;", "extern int A;"], ["use A;"], {})),
             (["extern int A;"], ["use A;"], "error C3861: 'sqrtf': x\nerror C2065: 'DAT_501000': x\n"
              "decls: FUN_00401000 has the name Foo: use that", prompt, (["extern int A;"], ["use A;"], {})),
             (["extern int A;"], ["use DAT_501000;"], "error C2065: 'DAT_501000': x", "no address here",
              (["extern int A;"], ["use DAT_501000;"], {}))]
    failures = []
    for declared, body, build, text_prompt, wanted in cases:
        found = llm.with_renames(declared, body, build, text_prompt)
        if found != wanted:
            failures.append(f"with_renames gives {found} for {declared}, {body}, {build!r}, not {wanted}")
    return failures


def check_with_renames_ftol() -> list[str]:
    """A float to int helper that the build flags and the code uses loses its declaration, and the function calls
    become casts, with the renames of the same try: the renames list it as `(long)`. A helper that the build
    does not flag, or that neither the declarations nor the function use, changes nothing."""
    decls = ["int _ftol2_sse(float x);", "extern int DAT_00501000;", "float sqrtf(float);"]
    head, tail = [ANN, "static void Run(void)", "{"], ["    z = sqrtf(f);", "}"]
    calls = [*head, "    y = _ftol2_sse(a * (b + c)) + _ftol2_sse(d);", *tail]
    casts = [*head, "    y = ((long)(a * (b + c))) + ((long)(d));", *tail]
    no_calls = [*head, "    y = a + d;", *tail]
    flagged_two = "error C3861: '_ftol2_sse': x\nerror C3861: 'sqrtf': x"
    cases = [(decls, calls, "error C3861: '_ftol2_sse': identifier not found",
              (["extern int DAT_00501000;", "float sqrtf(float);"], casts, {"_ftol2_sse": "(long)"})),
             (decls, calls, flagged_two,
              (["extern int DAT_00501000;", "float sqrt(float);"], [*casts[:-2], "    z = sqrt(f);", "}"],
               {"sqrtf": "sqrt", "_ftol2_sse": "(long)"})),
             (decls, calls, "error C3861: '_ftol2': x\nerror C3861: '__ftol2': x",
              (decls, calls, {})),
             (decls[1:], no_calls, "error C3861: '_ftol2_sse': x", (decls[1:], no_calls, {})),
             (decls, calls, "a.c(2) : error C2065: 'e' : undeclared identifier", (decls, calls, {}))]
    failures = []
    for declared, body, build, wanted in cases:
        found = llm.with_renames(declared, body, build, "")
        if found != wanted:
            failures.append(f"with_renames gives {found} for {build!r}, not {wanted}")
    return failures


def check_cast_globals() -> list[str]:
    """Each use of a dropped variable goes through a pointer of the type its extern declaration gives, such as
    `(*(int (*)[4])&v)`. The names that changed come back sorted. A member of that name, a longer name, a call
    of the name, the annotation, the comments above the signature and the signature stay, and so does a dropped
    name that has no declaration or no use. The input lines do not change."""
    decls = ["extern unsigned long DAT_00501000;", "extern int Tab[4];", "extern unsigned char *Ptr;", "void Foo(int);"]
    func = [ANN, "// reads DAT_00501000", "static void Run(void)", "{",
            "    a = DAT_00501000 + Tab[1] + *Ptr; Tab[2] = DAT_00501000;",
            "    p->DAT_00501000 = s.Tab; DAT_00501000x = Tab2; DAT_00501000(1);", "}"]
    wanted_func = [ANN, "// reads DAT_00501000", "static void Run(void)", "{",
                   "    a = (*(unsigned long (*))&DAT_00501000) + (*(int (*)[4])&Tab)[1]"
                   " + *(*(unsigned char *(*))&Ptr); (*(int (*)[4])&Tab)[2] = (*(unsigned long (*))&DAT_00501000);",
                   "    p->DAT_00501000 = s.Tab; DAT_00501000x = Tab2; DAT_00501000(1);", "}"]
    every = {"Tab", "DAT_00501000", "Ptr", "Unused", "Foo"}
    cases = [(func, decls, every, (wanted_func, ["DAT_00501000", "Ptr", "Tab"])),
             (func, decls, ["Tab"], ([*func[:4], func[4].replace("Tab[1]", "(*(int (*)[4])&Tab)[1]")
                                      .replace("Tab[2]", "(*(int (*)[4])&Tab)[2]"), func[5], func[6]], ["Tab"])),
             (func, decls, set(), (func, [])),
             (func, [], {"Tab"}, (func, [])),
             ([ANN, "static void Run(void)", "{", "    Foo(Tab);", "}"], decls, {"Foo", "Unused"},
              ([ANN, "static void Run(void)", "{", "    Foo(Tab);", "}"], []))]
    failures = []
    for lines, declared, dropped, wanted in cases:
        before = list(lines)
        found = llm.cast_globals(lines, declared, dropped)
        if found != wanted:
            failures.append(f"cast_globals gives {found} for {lines} and {sorted(dropped)}, not {wanted}")
        if lines != before:
            failures.append(f"cast_globals changes its input {before} to {lines}")
    return failures


def check_runtime_line() -> list[str]:
    """A macro or a function that takes a FILE is declared by its header include. Any other runtime function is
    declared by its C prototype with C linkage."""
    cases = [("va_start", "#include <stdarg.h>"), ("va_end", "#include <stdarg.h>"), ("fopen", "#include <stdio.h>"),
             ("memset", 'extern "C" void *memset(void *dst, int value, unsigned int size);'),
             ("strlen", 'extern "C" unsigned int strlen(const char *s);'),
             ("printf", 'extern "C" int printf(const char *format, ...);')]
    return [f"runtime_line gives {found!r} for {name}, not {wanted!r}"
            for name, wanted in cases if (found := llm.runtime_line(name)) != wanted]


def check_undeclared() -> list[str]:
    """The names with no declaration are the quoted names of errors C3861 and C2065, and the function names of an
    unresolved external symbol that the linker prints in C++ form. A variable that is unresolved, any other
    error and a text without errors name nothing. A name that comes twice is one."""
    cases = [("a.c(5) : error C3861: 'Foo': identifier not found", {"Foo"}),
             ("a.c(5) : error C2065: 'bar' : undeclared identifier", {"bar"}),
             ('a.obj : error LNK2019: unresolved external symbol "void * __cdecl memset(void *,int,unsigned int)" '
              "(?memset@@YAPAXPAXHI@Z) referenced in function Run", {"memset"}),
             ('a.obj : error LNK2019: unresolved external symbol "int DAT_0050201" (?DAT_0050201@@3HA)', set()),
             ("a.c(5) : error C2440: 'Foo': cannot convert from 'int' to 'char'", set()),
             ("a.c(5) : warning C3861: 'Foo': x\n", set()),
             ("a.c(1) : error C3861: 'Foo': x\na.c(2) : error C3861: 'Foo': x\na.c(3) : error C2065: 'Bar': x",
              {"Foo", "Bar"}),
             ("", set())]
    return [f"undeclared gives {found} for {text!r}, not {wanted}"
            for text, wanted in cases if (found := llm.undeclared(text)) != wanted]


def check_with_runtime() -> list[str]:
    """Each runtime function that the build flags as undeclared gets its declaration after the model's, and the model's
    own declarations of it go. The added lines are sorted and each is once. A flagged name that is not a runtime
    function changes nothing: (DECLS, [])."""
    memset = 'extern "C" void *memset(void *dst, int value, unsigned int size);'
    strlen = 'extern "C" unsigned int strlen(const char *s);'
    decls = ["void *memset(void *p, int v, int n);", "void Bar(int);", "extern int strlen_count;",
             "int strlen(const char *s);", "void va_start(int);"]
    one = "a.c(1) : error C3861: 'memset': identifier not found"
    many = "\n".join(["error C3861: 'strlen': x", "error C3861: 'va_start': x", "error C3861: 'va_end': x",
                      "error C3861: 'memset': x", "error C3861: 'memset': x", "error C3861: 'Bar': x"])
    cases = [(decls, one, (["void Bar(int);", "extern int strlen_count;", "int strlen(const char *s);",
                            "void va_start(int);", memset], [memset])),
             (decls, many, (["void Bar(int);", "extern int strlen_count;", "#include <stdarg.h>", strlen, memset],
                            ["#include <stdarg.h>", strlen, memset])),
             (decls, 'error LNK2019: unresolved external symbol "int __cdecl strlen(char const *)" (?strlen@@YAHPBD@Z)',
              (["void *memset(void *p, int v, int n);", "void Bar(int);", "extern int strlen_count;",
                "void va_start(int);", strlen], [strlen])),
             (decls, "error C3861: 'Bar': x\nerror C3861: 'Unknown': x", (decls, [])),
             (decls, "", (decls, [])),
             ([], one, ([memset], [memset]))]
    failures = []
    for declared, text, wanted in cases:
        before = list(declared)
        found = llm.with_runtime(declared, text)
        if found != wanted:
            failures.append(f"with_runtime gives {found} for {text!r} and {before}, not {wanted}")
        if declared != before:
            failures.append(f"with_runtime changes its input {before} to {declared}")
    return failures


def check_with_earlier() -> list[str]:
    """Each name that the build flags as undeclared and that an earlier try declared, but the declarations now do not,
    gets the earlier try's line, after the others. The added lines are sorted by text and each is once. A name
    that is declared, not flagged or not in the earlier try adds nothing: (DECLS, [])."""
    decls = ["void Bar(int);", "extern int Zed;"]
    earlier = {"Foo": "int Foo(void);", "Bar": "void Bar(int, int);", "Zed": "extern int Zed;",
               "Alpha": "extern int Alpha;", "Never": "extern int Never;"}
    text = "\n".join(["error C3861: 'Foo': x", "error C3861: 'Bar': x", "error C2065: 'Zed': x",
                      "error C3861: 'Baz': x"])
    both = "error C3861: 'Foo': x\nerror C2065: 'Alpha': x\nerror C3861: 'Foo': x"
    cases = [(decls, text, (decls + ["int Foo(void);"], ["int Foo(void);"])),
             (decls, both, (decls + ["extern int Alpha;", "int Foo(void);"], ["extern int Alpha;", "int Foo(void);"])),
             (decls, "error C3861: 'Bar': x\nerror C2065: 'Baz': x", (decls, [])),
             (decls, "", (decls, [])),
             ([], "error C2065: 'Never': x", (["extern int Never;"], ["extern int Never;"])),
             (["int Foo(void);", "void Bar(int);"], "error C3861: 'Foo': x",
              (["int Foo(void);", "void Bar(int);"], []))]
    failures = []
    for declared, build, wanted in cases:
        before = list(declared)
        found = llm.with_earlier(declared, build, earlier)
        if found != wanted:
            failures.append(f"with_earlier gives {found} for {build!r} and {before}, not {wanted}")
        if declared != before:
            failures.append(f"with_earlier changes its input {before} to {declared}")
    return failures


def check_without_declarations() -> list[str]:
    """The lines that declare a dropped name go, a function or a variable, with or without `extern` and a comment
    after it. Every other line stays, in its order: the lines of a declaration over two lines, comments, a
    `static` function and the declarations of other names, also when their name only starts with a dropped one."""
    decls = ["void Foo(int a);", "extern int Bar; // note", "extern int Foo2[4];", "static int Baz(void);",
             "// Foo(int)", "void Qux(void *a,", "    int b);", "char *Zed(void);"]
    cases = [({"Foo"}, ["extern int Bar; // note", "extern int Foo2[4];", "static int Baz(void);", "// Foo(int)",
                        "void Qux(void *a,", "    int b);", "char *Zed(void);"]),
             ({"Bar", "Zed", "Absent"}, ["void Foo(int a);", "extern int Foo2[4];", "static int Baz(void);",
                                         "// Foo(int)", "void Qux(void *a,", "    int b);"]),
             ({"Foo2": ["int Foo2[4]"]}, ["void Foo(int a);", "extern int Bar; // note", "static int Baz(void);",
                                          "// Foo(int)", "void Qux(void *a,", "    int b);", "char *Zed(void);"]),
             ({"Baz", "Qux", "b"}, decls),
             (set(), decls)]
    failures = []
    for dropped, wanted in cases:
        found = llm.without_declarations(decls, dropped)
        if found != wanted:
            failures.append(f"without_declarations gives {found} for {sorted(dropped)}, not {wanted}")
    if llm.without_declarations([], {"Foo"}) != []:
        failures.append("without_declarations gives lines for no lines")
    return failures


def check_tool_lines() -> list[str]:
    """The tool output keeps every line except the decls lines that are a summary (they hold "functions (") and the
    decls lines in KNOWN. A line that only holds "functions (" or equals a known line without the decls prefix
    stays."""
    known = {"decls: Foo: old warning"}
    text = "\n".join(["decls: 12 functions (3 stubs)", "decls: Foo: old warning", "decls: Foo: new warning",
                      "functions (not a decls line)", "Foo: old warning", "a.c(1) : error C2065: 'x' : x", ""])
    cases = [(text, known, ["decls: Foo: new warning", "functions (not a decls line)", "Foo: old warning",
                            "a.c(1) : error C2065: 'x' : x"]),
             (text, set(), ["decls: Foo: old warning", "decls: Foo: new warning", "functions (not a decls line)",
                            "Foo: old warning", "a.c(1) : error C2065: 'x' : x"]),
             ("one\r\ntwo\r\n", known, ["one", "two"]),
             ("", known, [])]
    return [f"tool_lines gives {found} for {text!r} and {sorted(kn)}, not {wanted}"
            for text, kn, wanted in cases if (found := llm.tool_lines(text, kn)) != wanted]


def check_build_errors() -> list[str]:
    """The lines that say why the build failed are the error lines, the fatal lines and the decls lines that are not
    summaries or known, in order, at most ERROR_LINES of them. Without such a line the last ERROR_LINES lines
    come back. When a line says the build holds no code for the function, the hint about `static` ends the list,
    after the cap."""
    cap = llm.ERROR_LINES
    hint = ("If the function is `static`, drop the `static`: the compiler leaves out a static function "
            "that nothing in the build calls, so there is nothing to score.")
    known = {"decls: old"}
    many_errors = [f"a.c({i}) : error C2065: 'x{i}' : x" for i in range(cap + 1)]
    plain = [f"line {i}" for i in range(cap + 10)]
    cases = [("note\na.c(1) : error C2065: 'x' : x\nwarning\nLINK : fatal error LNK1120: 1 unresolved\n"
              "decls: new\ndecls: old\ndecls: 9 functions (1 stubs)\n", ["a.c(1) : error C2065: 'x' : x",
                                                                        "LINK : fatal error LNK1120: 1 unresolved",
                                                                        "decls: new"]),
             ("fatal: no such thing\nplain", ["fatal: no such thing"]),
             ("\n".join(many_errors), many_errors[:cap]),
             ("\n".join(plain), plain[-cap:]),
             ("one\ntwo", ["one", "two"]),
             ("", []),
             (f"a.c(1) : error C2065: 'x' : x\nsomething\n{llm.NOT_BUILT}: Run",
              ["a.c(1) : error C2065: 'x' : x", hint]),
             (f"note\n{llm.NOT_BUILT}: Run", ["note", f"{llm.NOT_BUILT}: Run", hint]),
             ("\n".join(many_errors) + f"\n{llm.NOT_BUILT}", many_errors[:cap] + [hint]),
             ("decls: old\ndecls: 4 functions (0 stubs)\nnote", ["note"])]
    return [f"build_errors gives {found} for {text!r}, not {wanted}"
            for text, wanted in cases if (found := llm.build_errors(text, known)) != wanted]


def check_error_count() -> list[str]:
    """Each line with " error " counts as a compiler error, a fatal error too. Warnings, other lines and known decls
    lines do not count, nor does a decls summary line. An empty text has none."""
    known = {"decls: old error line"}
    cases = [("a.c(1) : error C2065: 'x' : x\nb.c(2) : error C2143: y\nc.c(3) : warning C4244: z", 2),
             ("LINK : fatal error LNK1120: 1 unresolved externals", 1),
             ("decls: old error line\ndecls: 3 functions (0 stubs)\nno problem here\nan error-free line", 0),
             ("a.c(1) : error C2065: 'x' : x\na.c(1) : error C2065: 'x' : x", 2),
             ("", 0)]
    return [f"error_count gives {found} for {text!r}, not {wanted}"
            for text, wanted in cases if (found := llm.error_count(text, known)) != wanted]


def check_names_only() -> list[str]:
    """A diff whose changed lines differ only in reccmp's names is names only. A moved line is not, though both
    sides hold it, and neither is a diff with no changed lines."""
    renamed = ("0x5aa7e8 : -call njSqrt (FUNCTION)\n"
               "         : +call FUN_00788f30 (FUNCTION) \t(npc_sonic.c:174)\n")
    moved = ("         : +push ecx \t(npc_sonic.c:174)\n"
             "0x5aa7e1 : fld dword ptr [ebp - 0xc]\n"
             "0x5aa7e4 : -push ecx\n")
    cases = [(renamed, True), (moved, False), (renamed + moved, False),
             ("0x5aa7e1 : fld dword ptr [ebp - 0xc]\n", False)]
    return [f"names_only gives {found} for {diff!r}, not {wanted}"
            for diff, wanted in cases if (found := llm.names_only(diff)) != wanted]


def run() -> list[str]:
    """Every check of this module, in order."""
    checks = [check_signature_index, check_without_static, check_wrapped_stubs, check_definition_block,
              check_stub_functions_wrap, check_cast_calls, check_one_edit_apart,
              check_short_globals, check_ftol_casts, check_with_renames_names, check_with_renames_ftol,
              check_cast_globals, check_runtime_line, check_undeclared, check_with_runtime, check_with_earlier,
              check_without_declarations, check_tool_lines, check_build_errors, check_error_count, check_names_only]
    return [failure for check in checks for failure in check()]
