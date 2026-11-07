"""Unit tests for cheaders.py, the header reader.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/cheaderstests.py
run() calls every check and returns the failures. All names are made up. Each check writes its headers into a new
temporary folder.
"""

import json
import os
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import ceval  # noqa: E402
import cheaders  # noqa: E402
import probe  # noqa: E402
import profiles  # noqa: E402

CPP = profiles.get("msvc-vc10-x86-cpp")
C = profiles.get("msvc-vc10-x86-c")


def closure(files: dict, start: str = "top.h", profile=CPP, closed_world=True, **options) -> cheaders.Closure:
    """The closure of START over FILES (relative path -> text), written into a new temporary folder whose "inc"
    subfolder is the search path. A START that begins with @ is a name to find on the search path."""
    with tempfile.TemporaryDirectory() as folder:
        for name, text in files.items():
            path = os.path.join(folder, name)
            os.makedirs(os.path.dirname(path), exist_ok=True)
            with open(path, "w", encoding="utf-8", newline="") as handle:
                handle.write(text)
        config = cheaders.Config(profile, search_path=(os.path.join(folder, "inc"),), **options)
        path = start[1:] if start.startswith("@") else os.path.join(folder, start)
        return cheaders.read(path, config, closed_world)


def value(found: cheaders.Closure, name: str):
    result = ceval.evaluate(name, found.profile, expand=found.expand, resolve=found.resolve,
                            resolve_type=found.resolve_type)
    return result.value if result.ok else (result.status, result.cause)


def names(paths) -> list[str]:
    return [os.path.basename(path) for path in paths]


def check_guards_and_once() -> list[str]:
    failures = []
    found = closure({
        "top.h": '#include "a.h"\n#include "a.h"\n#include "once.h"\n#include "once.h"\n#include "plain.h"\n'
                 '#include "copy/a.h"\n',
        "a.h": "// lead\n#ifndef A_H\n#define A_H\nenum { ONE = 1 };\n#endif /* A_H */\n// trail\n",
        "copy/a.h": "#ifndef A_H\n#define A_H\nenum { TWO = 2 };\n#endif\n",
        "once.h": "#pragma once\nenum { THREE = 3 };\n",
        "plain.h": "#ifndef X\n#define X 1\n#endif\nint after_x;\n",
    })
    if names(found.files) != ["top.h", "a.h", "once.h", "plain.h", "a.h"]:
        failures.append(f"each file once per closure: got {names(found.files)}")
    if [len(found.constants.get(name, [])) for name in ("ONE", "TWO", "THREE")] != [1, 0, 1]:
        failures.append(f"a guard skips a second copy: got {sorted(found.constants)}")
    if value(found, "X") != 1 or "after_x" not in found.variables:
        failures.append(f"a mid-file #ifndef is an ordinary condition: got {value(found, 'X')}")
    alone = closure({"g.h": "#ifndef G_H\n#define G_H\nenum { FOUR = 4 };\n#endif\n"}, "g.h", closed_world=False)
    if value(alone, "FOUR") != 4 or alone.diagnostics.unresolved_if:
        failures.append(f"a guard is live in an open world: got {value(alone, 'FOUR')}, "
                        f"{alone.diagnostics.unresolved_if}")
    return failures


def check_includes() -> list[str]:
    failures = []
    found = closure({
        "top.h": '#include "sub/x.h"\n#include <y.h>\n#include <missing.h>\n#include HEADER_NAME\n',
        "sub/x.h": '#include "y.h"\n#include "../top.h"\n',
        "sub/y.h": "enum { NEAR = 1 };\n",
        "inc/y.h": '#include "z.h"\nenum { FAR = 2 };\n',
        "inc/z.h": '#include <y.h>\nenum { DEEP = 3 };\n',
    })
    if names(found.files) != ["top.h", "x.h", "y.h", "y.h", "z.h"]:
        failures.append(f"include order: got {names(found.files)}")
    if (value(found, "NEAR"), value(found, "FAR"), value(found, "DEEP")) != (1, 2, 3):
        failures.append("quoted names search the including folder first, angle names the path only")
    missing = [(os.path.basename(file), line, name) for file, line, name in found.diagnostics.missing]
    if missing != [("top.h", 3, "missing.h")]:
        failures.append(f"missing include: got {missing}")
    if [text for _, _, text in found.diagnostics.macro_includes] != ["HEADER_NAME"]:
        failures.append(f"an #include of a macro: got {found.diagnostics.macro_includes}")
    return failures


def check_conditions() -> list[str]:
    failures = []
    found = closure({"top.h": (
        "#define A 2\n"
        "#if defined(A) && A == 2\n#define LIVE 1\n#endif\n"
        "#ifdef NEVER_SEEN\n#define DEAD 1\n#endif\n"
        "#if NEVER_SEEN\n#define MAYBE 1\n#endif\n"
        "#if NEVER_SEEN\n#define CHAIN 1\n#elif 1\n#define CHAIN 2\n#else\n#define CHAIN 3\n#endif\n"
        "#if 1\n#define FIRST 1\n#elif NEVER_SEEN\n#define FIRST 2\n#endif\n"
        "#if 0\n#define LATER 1\n#elif 1\n#define LATER 5\n#else\n#define LATER 6\n#endif\n"
        "#if ('A' == 65) && (L'A' == 65) && (1 ? 1 : 0)\n#define CHARS 1\n#endif\n"
        "#if sizeof(int) == 4\n#define SIZE 1\n#endif\n"
        "#if KNOWN_OFF == 0\n#define KNOWN 1\n#endif\n"
        "#define GONE 3\n#undef GONE\n#if GONE == 0\n#define AFTER_UNDEF 1\n#endif\n"
        "#if 0\n#if NEVER_SEEN\n#endif\n#endif\n"
    )}, known_undefined=frozenset({"KNOWN_OFF"}))
    got = {name: value(found, name) for name in ("LIVE", "DEAD", "MAYBE", "CHAIN", "FIRST", "LATER", "CHARS",
                                                 "SIZE", "KNOWN", "AFTER_UNDEF")}
    unresolved = ("unresolved", "unresolved #if")
    expected = {"LIVE": 1, "DEAD": ("unresolved", "unknown identifier"), "MAYBE": unresolved, "CHAIN": unresolved,
                "FIRST": 1, "LATER": 5, "CHARS": 1, "SIZE": unresolved, "KNOWN": 1, "AFTER_UNDEF": 1}
    if got != expected:
        failures.append(f"conditions: got {got}")
    if found.diagnostics.unresolved_if != {"NEVER_SEEN": 2}:
        failures.append(f"unresolved #if identifiers (none inside a dead parent): got "
                        f"{found.diagnostics.unresolved_if}")
    if sum(found.diagnostics.unsupported_if.values()) != 1:
        failures.append(f"sizeof in #if is unsupported: got {found.diagnostics.unsupported_if}")
    return failures


def check_default_definition() -> list[str]:
    failures = []
    header = "#ifndef DEF\n#define DEF 4\n#endif\n"
    found = closure({"top.h": '#define DEF 7\n#include "d.h"\n', "d.h": header})
    if value(found, "DEF") != 7:
        failures.append(f"a default definition follows the closure order: got {value(found, 'DEF')}")
    alone = closure({"d.h": header}, "d.h", closed_world=False)
    if value(alone, "DEF") != ("unresolved", "unresolved #if"):
        failures.append(f"a default definition read alone keeps both alternatives: got {value(alone, 'DEF')}")
    known = closure({"d.h": header}, "d.h", closed_world=False, known_undefined=frozenset({"DEF"}))
    if value(known, "DEF") != 4:
        failures.append(f"a known-undefined name takes the default: got {value(known, 'DEF')}")
    same = closure({"top.h": "#define E 1\n#if NEVER_SEEN\n#define E 1\n#endif\n"})
    if value(same, "E") != 1:
        failures.append(f"equal alternatives merge: got {value(same, 'E')}")
    return failures


def check_macros() -> list[str]:
    failures = []
    found = closure({"top.h": (
        "#define LONG_ONE (1 + \\\n  2)\n#define CAT a##b\n#define CY CY2\n#define CY2 CY\n#define CALL f(1)\n"
        "#define FM(x) ((x) << 16)\n#define OBJ (1)\n#define EMPTY\n"
    )})
    got = {name: value(found, name) for name in ("LONG_ONE", "CAT", "CY", "CALL", "OBJ", "FM")}
    expected = {"LONG_ONE": 3, "CAT": ("unsupported", "token pasting"), "CY": ("unsupported", "macro cycle"),
                "CALL": ("unsupported", "macro expands to a call"), "OBJ": 1,
                "FM": ("unsupported", "function-like macro")}
    if got != expected:
        failures.append(f"macros: got {got}")
    if found.expand("FM").function is not True or found.expand("EMPTY").body != ():
        failures.append("a ( right after the name makes a function-like macro")
    chain = closure({"top.h": (
        "#define WINNT 0x0600\n#define FROM2(ver) ver##0000\n#define FROM(ver) FROM2(ver)\n"
        "#define VERSION FROM(WINNT)\n#if VERSION >= 0x06000000\n#define NEW 1\n#else\n#define NEW 0\n#endif\n"
    )})
    if value(chain, "NEW") != 1:
        failures.append(f"function-like chain in #if: NEW is {value(chain, 'NEW')}, want 1")
    return failures


def check_branch_cap() -> list[str]:
    text = "".join(f"#if NEVER_SEEN\n#define T {number}\n#endif\n" for number in range(3))
    found = closure({"top.h": text}, branch_cap=2)
    if value(found, "T") != ("unresolved", "truncated branches") or found.diagnostics.truncated != {"T": 1}:
        return [f"branch cap: got {value(found, 'T')}, {found.diagnostics.truncated}"]
    return []


def check_declarations() -> list[str]:
    failures = []
    found = closure({"top.h": (
        "DECLARE_HANDLE(HWIDGET);\n"
        "typedef struct _FOO FOO;\nstruct _FOO { int a; FOO *next; };\n"
        "typedef struct { int x; union { int y; float z; }; } ANON, *PANON;\n"
        "enum COLOR { RED, GREEN = 5, BLUE, MIXED = GREEN | 0x10 };\n"
        "static const int K = 3;\n"
        "__declspec(dllimport) int __stdcall Api(_In_ int a, __in_opt void *b);\n"
        "#define FMACRO(x) x\n"
        "FMACRO(1) int bad;\nint after;\n"
        "namespace space { int hidden; }\n"
        "struct Widget { virtual void f(); };\n"
        "__inline int inline_sum(int a) { return a + 1; }\n"
        "int global_table[4];\n"
    )})
    if found.typedefs["HWIDGET"][0].spelled != "struct HWIDGET__ *" or "HWIDGET__" not in found.tags:
        failures.append(f"DECLARE_HANDLE: got {found.typedefs.get('HWIDGET')}")
    if found.type_id("FOO") != "struct _FOO" or [m.name for m in found.members["struct _FOO"]] != ["a", "next"]:
        failures.append(f"a typedef before the body shares the type id: got {found.type_id('FOO')}, "
                        f"{found.members.get('struct _FOO')}")
    if (found.type_id("ANON"), found.typedefs["PANON"][0].spelled) != ("ANON", "ANON *"):
        failures.append(f"an anonymous typedef: got {found.type_id('ANON')}, {found.typedefs['PANON']}")
    if [(m.name, m.spelled) for m in found.members.get("ANON", [])] != [("x", "int"), ("y", "int"), ("z", "float")]:
        failures.append(f"anonymous members lift into their parent: got {found.members.get('ANON')}")
    bodies = {type_id: (os.path.basename(origin.file), origin.line) for type_id, origin in found.bodies.items()
              if not type_id.startswith("union@")}
    if bodies != {"struct _FOO": ("top.h", 3), "ANON": ("top.h", 4)}:
        failures.append(f"struct and union bodies, no enums: got {bodies}")
    got = [value(found, name) for name in ("RED", "GREEN", "BLUE", "MIXED", "K")]
    if got != [0, 5, 6, 0x15, 3]:
        failures.append(f"enumerators and const constants: got {got}")
    api = found.functions["Api"][0]
    if (api.returns, api.parameters) != ("int", ("int", "void *")):
        failures.append(f"SAL and __declspec in a prototype: got {api}")
    reasons = [reason for _, _, reason in found.diagnostics.skipped]
    if reasons != ["function-like macro FMACRO", "namespace block", "class body"]:
        failures.append(f"skipped declarations: got {reasons}")
    if "after" not in found.variables or "hidden" in found.variables or "Widget" not in found.tags:
        failures.append("the closure stays alive after a skipped declaration")
    if "inline_sum" not in found.functions or value(found, "global_table") != ("nonconstant", "variable"):
        failures.append("an inline function gives a prototype; a global is nonconstant")
    in_c = closure({"top.h": "static const int K = 3;\n"}, profile=C)
    if value(in_c, "K") != ("nonconstant", "variable"):
        failures.append(f"a const variable is not a constant in C: got {value(in_c, 'K')}")
    return failures


def check_extern_c() -> list[str]:
    failures = []
    text = ('#ifdef __cplusplus\nextern "C" {\n#endif\nint api(void);\n#ifdef __cplusplus\n}\n#endif\n'
            "#ifdef __cplusplus\n#define LANG 2\n#else\n#define LANG 1\n#endif\n")
    for profile, language in ((CPP, 2), (C, 1)):
        found = closure({"top.h": text}, profile=profile)
        if "api" not in found.functions or value(found, "LANG") != language or found.diagnostics.unresolved_if:
            failures.append(f"{profile.name}: extern \"C\" and __cplusplus: got {sorted(found.functions)}, "
                            f"{value(found, 'LANG')}")
    return failures


def check_directives() -> list[str]:
    failures = []
    found = closure({"top.h": "#pragma pack(push, 1)\n#error stop here\nint after;\n"
                              "#if NEVER_SEEN\n#error maybe\nint maybe;\n#endif\n"})
    errors = [(line, text, live) for _, line, text, live in found.diagnostics.errors]
    if errors != [(2, "#error stop here", True), (5, "#error maybe", False)]:
        failures.append(f"#error is reported, not fatal: got {errors}")
    if "after" not in found.variables or found.diagnostics.unknown_directives:
        failures.append(f"#pragma is ignored: got {found.diagnostics.unknown_directives}")
    if found.variables["after"][0].origin.certain is not True or found.variables["maybe"][0].origin.certain:
        failures.append("a declaration in an unresolved branch is uncertain")
    return failures


def check_faults() -> list[str]:
    failures = []
    try:
        closure({"top.h": "#define A 1\n"}, "@nowhere.h")
        failures.append("a missing umbrella raises")
    except cheaders.HeaderError:
        pass
    with tempfile.TemporaryDirectory() as folder:
        path = os.path.join(folder, "latin.h")
        with open(path, "wb") as handle:
            handle.write(b"// caf\xe9\nint x;\n")
        try:
            cheaders.read(path, cheaders.Config(CPP))
            failures.append("a decode error raises")
        except cheaders.HeaderError as error:
            if "latin.h" not in str(error):
                failures.append(f"a decode error names the file: got {error}")
    found = closure({"top.h": '#include "broken.h"\nint good;\n',
                     "broken.h": "#if NEVER_SEEN\nstruct A {\n#else\nstruct A : B {\n#endif\nint x; };\n"})
    if "good" not in found.variables or [reason for _, _, reason in found.diagnostics.skipped] != [
            "unbalanced brackets"]:
        failures.append(f"an unbalanced file loses only its own declarations: got {found.diagnostics.skipped}")
    return failures


def check_other_profile() -> list[str]:
    """A header read under one profile, its constants evaluated under another; the cache keeps them apart."""
    failures = []
    found = closure({"top.h": "enum { XX_MANY = 'AB' };\n#define XX_SHIFTED (-8 >> 1)\ntypedef long XX_LONG;\n"},
                    profile=profiles.get("shc-c"))
    for name, wanted in (("XX_MANY", 0x4142), ("XX_SHIFTED", -4)):
        target = ceval.evaluate(name, CPP, **found.callbacks(CPP))
        own = ceval.evaluate(name, found.profile, **found.callbacks())
        if (target.value, own.status) != (wanted, ceval.UNSUPPORTED):
            failures.append(f"{name} under the target profile {target}, under its own {own}")
    if found.resolve_type("XX_LONG", CPP) != CPP.int_type("long"):
        failures.append(f"a typedef under the target profile: {found.resolve_type('XX_LONG', CPP)}")
    return failures


def check_array_typedef() -> list[str]:
    """An array typedef is a type: a cast to a pointer to it works, sizeof gives its size, a cast to it does not."""
    failures = []
    found = closure({"top.h": "typedef float XX_F;\ntypedef XX_F XX_M[16];\n#define XX_N 4\n"
                              "typedef int XX_V[XX_N][2];\ntypedef int XX_OPEN[];\n"})
    for text, wanted in (("sizeof(XX_M)", (ceval.OK, 64)), ("sizeof(XX_V)", (ceval.OK, 32)),
                         ("(XX_M *)0", (ceval.OK, 0)), ("(XX_OPEN *)0", (ceval.OK, 0)),
                         ("sizeof(XX_OPEN)", (ceval.UNSUPPORTED, None)), ("(XX_M)0", (ceval.UNSUPPORTED, None))):
        result = ceval.evaluate(text, CPP, **found.callbacks())
        if (result.status, result.value) != wanted:
            failures.append(f"{text}: {result}")
    return failures


def check_probe_enums() -> list[str]:
    """Enumerator values against what cl.exe gave for the probe's enum (tools/evidence/probe.py)."""
    failures = []
    found = closure({"top.h": probe.ENUM_DECLARATION + "\n"})
    for language in probe.PROFILE_NAMES:
        fixture = json.loads((probe.FIXTURES / f"vc10-{language}.json").read_text(encoding="utf-8"))
        wanted = {case["text"]: case["value"] for case in fixture["cases"] if case["text"] in probe.ENUM_NAMES}
        for name, value in wanted.items():
            result = found.constant_value(name)
            if not result.ok or result.value != value:
                failures.append(f"probe {language} enum {name}: compiler {value}, cheaders {result}")
    return failures


def check_tag_types() -> list[str]:
    """In C++, a tag is a type name: a bare enum, struct or union tag resolves as its tag type, also a tag that only a
    prototype names. A variable, function or constant of the same name hides the tag. In C a tag is no type name."""
    failures = []
    found = closure({"top.h": "enum XX_MODE : int { XX_MODE_ON = 1 };\nstruct xxbody { int a; };\n"
                              "union xxboth { int a; };\nvoid xxuse(enum XX_FWD mode);\n"
                              "struct xxhid { int a; };\nextern int xxhid;\nstruct xxfun { int a; };\nvoid xxfun(void);\n"})
    for spelled, wanted in (("XX_MODE", CPP.int_type("int")), ("xxbody", found.resolve_type("struct xxbody")),
                            ("xxboth", found.resolve_type("union xxboth")), ("XX_FWD", CPP.int_type("int")),
                            ("xxhid", None), ("xxfun", None), ("xxnone", None)):
        if found.resolve_type(spelled) != wanted:
            failures.append(f"C++ tag {spelled}: {found.resolve_type(spelled)}, wanted {wanted}")
    for text, wanted in (("(XX_MODE)2", (ceval.OK, 2)), ("(XX_FWD)3", (ceval.OK, 3)),
                         ("(xxnone)2", (ceval.UNRESOLVED, None))):
        result = ceval.evaluate(text, CPP, **found.callbacks())
        if (result.status, result.value) != wanted:
            failures.append(f"C++ {text}: {result}")
    found = closure({"top.h": "enum XX_MODE { XX_MODE_ON = 1 };\n"}, profile=C)
    for text, wanted in (("(XX_MODE)2", ceval.UNRESOLVED), ("(enum XX_MODE)2", ceval.OK)):
        result = ceval.evaluate(text, C, **found.callbacks())
        if result.status != wanted:
            failures.append(f"C {text}: {result}")
    return failures


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_guards_and_once, check_includes, check_conditions, check_default_definition, check_macros,
                  check_branch_cap, check_declarations, check_extern_c, check_directives, check_faults,
                  check_other_profile, check_array_typedef, check_probe_enums, check_tag_types):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    print("\n".join(found) or "cheaderstests: all passed")
    sys.exit(1 if found else 0)
