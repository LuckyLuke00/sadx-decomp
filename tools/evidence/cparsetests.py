"""Unit tests for cparse.py, the game source reader.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/cparsetests.py
run() calls every check and returns the failures. All names are made up.
"""

import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import cparse  # noqa: E402
import ctokens  # noqa: E402
import profiles  # noqa: E402

CPP = profiles.get("msvc-vc10-x86-cpp")
C = profiles.get("msvc-vc10-x86-c")
ANNOTATION = re.compile(r"//\s*(?P<kind>FUNCTION|STUB|GLOBAL):\s*GAME\s+(?P<address>0x[0-9a-fA-F]+)\s*$")


def read(text: str, profile=CPP, type_names=frozenset()) -> cparse.SourceFile:
    return cparse.parse(text, "game/file.c", profile, ANNOTATION, type_names)


def arguments(call: cparse.Call) -> list[str]:
    return [ctokens.spelling(list(argument)) for argument in call.arguments]


def calls(source: cparse.SourceFile) -> list[tuple]:
    return [(call.callee, call.outer, arguments(call)) for call in source.calls]


def check_arguments() -> list[str]:
    source = read('void g(void)\n{\n\tf(cond ? 1 : 2, 0);\n\tf(")", 0);\n\tf(\')\', 0);\n\tf(M(a, b), c);\n'
                  '\tf((a, b), c);\n\tf(a[1, 2], c);\n\th();\n}\n')
    expected = [("f", (), ["cond ? 1 : 2", "0"]), ("f", (), ['")"', "0"]), ("f", (), ["')'", "0"]),
                ("f", (), ["M ( a , b )", "c"]), ("M", (("f", 1),), ["a", "b"]), ("f", (), ["( a , b )", "c"]),
                ("f", (), ["a [ 1 , 2 ]", "c"]), ("h", (), [])]
    if calls(source) != expected:
        return [f"arguments: got {calls(source)}"]
    return []


def check_nested_and_multiline() -> list[str]:
    failures = []
    source = read("void g(void)\n{\n\touter(1, inner(0));\n\tf(1,\n\t  2);\n}\n")
    if calls(source)[:2] != [("outer", (), ["1", "inner ( 0 )"]), ("inner", (("outer", 2),), ["0"])]:
        failures.append(f"nested call path: got {calls(source)}")
    multi = source.calls[2]
    if (multi.line, multi.column, arguments(multi)) != (4, 2, ["1", "2"]):
        failures.append(f"multi-line call: got {multi}")
    source = read("void g(void)\n{\n\tsetup();\n\tf(0);\n}\n")
    if (source.calls[1].statement, source.calls[1].previous) != ("f ( 0 )", "setup ( )"):
        failures.append(f"statement context: got {source.calls[1]}")
    return failures


def check_not_calls() -> list[str]:
    source = read("void g(struct S *s)\n{\n\ts->exec(s);\n\ts.f(1);\n\tA::b(2);\n\tx = sizeof(int);\n"
                  "\tif (x) { }\n\twhile (y) { }\n\treturn (z);\n\t(void)0;\n\tx = int(3);\n}\n")
    if source.calls:
        return [f"not calls: got {calls(source)}"]
    return []


def check_except() -> list[str]:
    source = read("void g(void)\n{\n\t__try\n\t{\n\t\tf();\n\t}\n\t__except (1)\n\t{\n\t\th();\n\t}\n}\n")
    if calls(source) != [("f", (), []), ("__except", (), ["1"]), ("h", (), [])]:
        return [f"__except: got {calls(source)}"]
    return []


def check_annotations() -> list[str]:
    failures = []
    source = read("// FUNCTION: GAME 0x00401000\n\n// STUB: GAME 0x00401010\nstatic void\nfoo(int a) /* note */\n"
                  "{\n\tbar(a);\n}\n")
    owner = source.owners[0]
    got = (owner.kind, owner.name, owner.line, [(note.kind, note.address, note.line) for note in owner.annotations])
    if got != ("function", "foo", 4, [("FUNCTION", "0x00401000", 1), ("STUB", "0x00401010", 3)]):
        failures.append(f"annotations above a split head: got {got}")
    if owner.names != {"a": "int"} or source.calls[0].owner != 0:
        failures.append(f"owner names and call owner: got {owner.names}, {source.calls}")
    for text, why in (("// FUNCTION: GAME 0x1\n// plain\nvoid foo(void) { }\n", "a plain comment"),
                      ("// FUNCTION: GAME 0x1\n/* block */\nvoid foo(void) { }\n", "a block comment"),
                      ("// FUNCTION: GAME 0x1\nint x;\nvoid foo(void) { }\n", "a code line")):
        owner = read(text).owners[0]
        if owner.annotations:
            failures.append(f"{why} stops the walk: got {owner.annotations}")
    source = read("// GLOBAL: GAME 0x2\nint table = f(1);\nint plain = 2;\n")
    if [(owner.kind, owner.name, len(owner.annotations)) for owner in source.owners] != [("global", "table", 1)]:
        failures.append(f"a global with a call in its initializer is an owner: got {source.owners}")
    if calls(source) != [("f", (), ["1"])] or source.names["plain"].kind != "variable":
        failures.append(f"global initializer calls: got {calls(source)}")
    if source.names["table"].annotations[0].kind != "GLOBAL":
        failures.append(f"a global keeps its annotation: got {source.names['table']}")
    source = cparse.parse("// FUNCTION: GAME 0x1\nvoid foo(void) { }\n", "f.c", CPP)
    if source.owners[0].annotations:
        failures.append("no annotation pattern reads no annotations")
    return failures


def check_qualified_owners() -> list[str]:
    failures = []
    source = read("void Audio::Play(float p)\n{\n\tStop();\n}\nX::~X() { }\nX::X() : y(0) { }\n"
                  "bool C::f(int a) const\n{\n\treturn g(a);\n}\n// STUB: GAME 0x3\nint h(void) { return 0; }\n")
    names = [(owner.name, len(owner.annotations)) for owner in source.owners]
    if names != [("Audio::Play", 0), ("X::~X", 0), ("X::X", 0), ("C::f", 0), ("h", 1)]:
        failures.append(f"qualified and const owners: got {names}")
    source = read("int x;\nfoo bar { }\nvoid g(void) { f(); }\n")
    if not source.unsupported.startswith("a file-scope block the reader does not model") or source.calls:
        failures.append(f"an unknown file-scope block: got {source.unsupported!r}")
    return failures


def check_extern_c() -> list[str]:
    failures = []
    text = 'extern "C" {\nint rand(void);\n}\nextern "C" double fabs(double v);\nvoid g(void) { rand(); }\n'
    for profile in (CPP, C):
        source = read(text, profile)
        got = {name: (declared.kind, declared.type) for name, declared in source.names.items()}
        if got != {"rand": ("function", "int"), "fabs": ("function", "double"), "g": ("function", "void")}:
            failures.append(f"{profile.name}: extern \"C\" names: got {got}")
        if source.prototypes["fabs"].parameters != ("double",) or calls(source) != [("rand", (), [])]:
            failures.append(f"{profile.name}: extern \"C\" prototypes and calls: got {source.prototypes}")
    return failures


def check_directives() -> list[str]:
    failures = []
    for text, reason in (("#if 1\nint x;\n#endif\n", "#if"), ("#define A 1\n", "#define"),
                         ("#ifdef A\n#endif\n", "#ifdef"), ("void g(void) { f(1; }\n", "unbalanced brackets"),
                         ("int x ??/\n;\n", "trigraph"), ("struct A { void f() { g(); } };\n",
                                                          "function body inside a type"),
                         ("namespace n { int x; }\n", "namespace")):
        source = read(text)
        if source.unsupported != reason or source.names or source.calls:
            failures.append(f"{text!r}: got {source.unsupported!r}, {source.names}")
    source = read('#include "decls.h"\n#include <sys/types.h>\n#pragma optimize("", off)\nint x;\n')
    includes = [(include.name, include.angle, include.line) for include in source.includes]
    if source.unsupported or includes != [("decls.h", False, 1), ("sys/types.h", True, 2)]:
        failures.append(f"includes and pragma: got {source.unsupported!r}, {includes}")
    return failures


def check_declarations() -> list[str]:
    failures = []
    source = read("struct taskwk;\ntypedef int MyInt;\nextern int DAT_1;\nstatic struct VEC table[4], *ptr;\n"
                  "void (*handler)(int);\nUnknown thing;\nlong Diff(long a, long b);\n"
                  "void g(struct taskwk *tp, MyInt n, float (*cb)(int), ...)\n{\n\tint i, j[3];\n"
                  "\tstruct taskwk *t2 = tp;\n\tNJS_VECTOR v;\n\tMystery m;\n\tOther *op;\n"
                  "\tfor (int k = 0; k < 2; k++) { use(k); }\n\tstruct taskwk *taskwk;\n}\n",
                  type_names={"NJS_VECTOR"})
    got = {name: (declared.kind, declared.type) for name, declared in source.names.items()}
    expected = {"DAT_1": ("variable", "int"), "table": ("variable", "struct VEC [ 4 ]"),
                "ptr": ("variable", "struct VEC *"), "handler": ("variable", "void ( * ) ( int )"),
                "thing": ("variable", "Unknown"), "Diff": ("function", "long"), "g": ("function", "void")}
    if got != expected:
        failures.append(f"file-scope names: got {got}")
    if source.typedefs != {"MyInt": "int"} or source.tags != {"taskwk", "VEC"}:
        failures.append(f"typedefs and tags: got {source.typedefs}, {source.tags}")
    prototype = source.prototypes["g"]
    if (prototype.parameters, prototype.variadic) != (("struct taskwk *", "MyInt", "float ( * ) ( int )"), True):
        failures.append(f"parameters: got {prototype}")
    if source.prototypes["Diff"].parameters != ("long", "long"):
        failures.append(f"prototype: got {source.prototypes['Diff']}")
    expected = {"tp": "struct taskwk *", "n": "MyInt", "cb": "float ( * ) ( int )", "i": "int", "j": "int [ 3 ]",
                "t2": "struct taskwk *", "v": "NJS_VECTOR", "m": "Mystery", "op": "Other *", "k": "int",
                "taskwk": "struct taskwk *"}
    if source.owners[0].names != expected:
        failures.append(f"parameters and locals: got {source.owners[0].names}")
    return failures


def check_ignored_words() -> list[str]:
    source = read("__declspec(dllimport) unsigned __int64 __cdecl f(_In_ int a, __in int b);\n")
    declared, prototype = source.names.get("f"), source.prototypes.get("f")
    if declared is None or declared.type != "unsigned __int64" or prototype.parameters != ("int", "int"):
        return [f"ignored words and __int64: got {declared}, {prototype}"]
    return []


def check_spots() -> list[str]:
    """Field spots per owner, also inside call arguments, in function bodies only, with their context; case labels
    and raw offsets are counted there."""
    failures = []
    source = read("int g_z = make(g_s.f == 1);\nvoid g(struct taskwk *tp)\n{\n\tstruct VEC v;\n\tv.x = 0;\n"
                  "\ttp->mode = 1;\n\tset(tp->flag & 8);\n"
                  "\tswitch (tp->mode) { case 1: tp->wtimer |= 0x10; break; case 2: break; }\n"
                  "\t*(int *)((char *)tp + 4) = 0;\n}\nvoid h(void)\n{\n\tg_tp->mode = 2;\n}\n")
    got = [(ctokens.spelling(list(spot.base)), spot.arrow, spot.member, spot.operator,
            ctokens.spelling(list(spot.value)), spot.line, spot.owner) for spot in source.spots]
    expected = [("v", False, "x", "=", "0", 5, 1), ("tp", True, "mode", "=", "1", 6, 1),
                ("tp", True, "flag", "&", "8", 7, 1), ("tp", True, "wtimer", "|=", "0x10", 8, 1),
                ("g_tp", True, "mode", "=", "2", 13, 2)]
    if got != expected:
        failures.append(f"spots: got {got}")
    elif (source.spots[0].column, source.spots[2].statement, source.spots[2].previous) != (
            4, "set ( tp -> flag & 8 )", "tp -> mode = 1"):
        failures.append(f"spot column and context: got {source.spots[0]}, {source.spots[2]}")
    if (source.case_labels, source.raw_offsets) != (2, 1):
        failures.append(f"case labels and raw offsets: got {source.case_labels}, {source.raw_offsets}")
    return failures


def check_values() -> list[str]:
    """Value spots in function bodies only, in position order: assignments and compares of plain variables, local
    initializers (not { } lists, and not the declaration itself as an assignment), case labels with the switch
    expression, and returns with a value."""
    failures = []
    source = read("int g_mode = 3;\nint g(int mode)\n{\n\tint a, b = 2;\n\tint list[2] = { 1, 2 };\n"
                  "\tfor (int i = 0; i != 4; ++i) mode = 5;\n\tif (mode == 6) return 7;\n"
                  "\tswitch (g_mode) { case 8: break; }\n\treturn mode != 9;\n}\n")
    got = [(spot.kind, ctokens.spelling(list(spot.lvalue)), spot.operator, ctokens.spelling(list(spot.value)),
            spot.line, spot.owner) for spot in source.values]
    expected = [("variable", "b", "=", "2", 4, 0), ("variable", "i", "=", "0", 6, 0),
                ("variable", "i", "!=", "4", 6, 0), ("variable", "mode", "=", "5", 6, 0),
                ("variable", "mode", "==", "6", 7, 0), ("return", "", "return", "7", 7, 0),
                ("case", "g_mode", "case", "8", 8, 0), ("return", "", "return", "mode != 9", 9, 0),
                ("variable", "mode", "!=", "9", 9, 0)]
    if got != expected:
        failures.append(f"values: got {got}")
    elif (source.values[0].column, source.values[4].statement, source.values[4].previous) != (
            9, "if ( mode == 6 ) return 7", "++ i ) mode = 5"):
        failures.append(f"value column and context: got {source.values[0]}, {source.values[4]}")
    return failures


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_arguments, check_nested_and_multiline, check_not_calls, check_except, check_annotations,
                  check_qualified_owners, check_extern_c, check_directives, check_declarations,
                  check_ignored_words, check_spots, check_values):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    print("\n".join(found) or "cparsetests: all passed")
    sys.exit(1 if found else 0)
