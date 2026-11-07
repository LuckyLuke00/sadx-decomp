"""Unit tests for ceval.py, the typed evaluator, and profiles.py, the compiler profiles.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/cevaltests.py
run() calls every check and returns the failures. All names are made up.
"""

import json
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import ceval  # noqa: E402
import ctokens  # noqa: E402
import probe  # noqa: E402
import profiles  # noqa: E402
from ceval import NONCONSTANT, OK, UNRESOLVED, UNSUPPORTED, Macro, Result  # noqa: E402

CPP = profiles.get("msvc-vc10-x86-cpp")
C = profiles.get("msvc-vc10-x86-c")
SHC = profiles.get("shc-c")
U32 = CPP.int_type("unsigned int")
S16 = CPP.int_type("short")
VARIABLES = {"var", "p", "a", "g", "x"}
MACROS = {
    "NULL": "0",
    "SUM": "1+2",
    "FLAG": "0x10",
    "LOOP": "LOOP + 1",
    "PASTE": "a ## b",
    "ERRNO": "(*get_errno())",
    "ALIAS": "FLAG",
}
FUNCTION_MACROS = {"LOCATION"}
# Function-like macros with parameters and bodies, for #if mode: name -> (parameters, body).
FUNCTIONS = {
    "CAT": (("a", "b"), "a ## b"),
    "VER2": (("v",), "v ## 0000"),
    "VER": (("v",), "VER2(v)"),
    "TWICE": (("x",), "((x) * 2)"),
    "ADD": (("a", "b"), "a + b"),
    "PICK": (("a", "..."), "a"),
    "ARGS": (("...",), "__VA_ARGS__"),
    "STR": (("x",), "#x"),
    "SELF": (("x",), "SELF(x)"),
}
MACROS["HIGH"] = "0x0600"
MACROS["JOIN"] = "MAY ## BE"
TYPES = {"U32": U32, "S16": S16, "struct VEC": profiles.CType("record", 96, name="struct VEC")}
CONSTANTS = {"RED": Result(OK, 2, CPP.int_type("int"))}


def expand(name):
    if name in FUNCTION_MACROS:
        return Macro(True)
    if name in FUNCTIONS:
        parameters, body = FUNCTIONS[name]
        return Macro(True, tuple(ctokens.tokens_of(body)), parameters)
    if name in MACROS:
        return Macro(False, tuple(ctokens.tokens_of(MACROS[name])))
    return None


def resolve(name):
    if name in VARIABLES:
        return ceval.failure(NONCONSTANT, "variable", name)
    return CONSTANTS.get(name)


def value_of(text, profile=CPP, **options):
    return ceval.evaluate(text, profile, expand=expand, resolve=resolve, resolve_type=TYPES.get, **options)


def expect(failures, text, status, value=None, ctype=None, profile=CPP, cause=None, **options):
    result = value_of(text, profile, **options)
    wrong = result.status != status or (value is not None and result.value != value)
    wrong = wrong or (ctype is not None and result.ctype.name != ctype)
    wrong = wrong or (cause is not None and result.cause != cause)
    if wrong:
        failures.append(f"{profile.name} {options.get('mode', 'expr')} {text!r}: got {result}, want {status} "
                        f"{value!r} {ctype or ''} {cause or ''}")


# ---------------------------------------------------------------- checks

def check_integer_operations() -> list[str]:
    failures = []
    expect(failures, "~0x2000", OK, -0x2001, "int")
    expect(failures, "~0", OK, -1, "int")
    expect(failures, "~0u", OK, 0xFFFFFFFF, "unsigned int")
    expect(failures, "(U32)~0x2000", OK, 0xFFFFDFFF, "unsigned int")
    expect(failures, "1 << 31", OK, -0x80000000, "int")
    expect(failures, "1 << 31", UNSUPPORTED, profile=SHC, cause="signed overflow")
    expect(failures, "-8 >> 1", OK, -4, "int")
    expect(failures, "-8 >> 1", UNSUPPORTED, profile=SHC, cause="signed right shift")
    expect(failures, "0x7FFFFFFF + 1", OK, -0x80000000, "int")
    expect(failures, "0x7FFFFFFF + 1", UNSUPPORTED, profile=SHC, cause="signed overflow")
    expect(failures, "1 << 32", UNSUPPORTED, cause="shift count")
    expect(failures, "1 << -1", UNSUPPORTED, cause="shift count")
    expect(failures, "1 / 0", UNSUPPORTED, cause="division by zero")
    expect(failures, "1 % 0", UNSUPPORTED, cause="division by zero")
    expect(failures, "(-2147483647 - 1) / -1", OK, -0x80000000, "int")
    expect(failures, "(-2147483647 - 1) / -1", UNSUPPORTED, profile=SHC, cause="division overflow")
    expect(failures, "-7 / 2", OK, -3)
    expect(failures, "-7 % 2", OK, -1)
    expect(failures, "-1 < 0u", OK, 0, "bool")
    expect(failures, "-1 < 0u", OK, 0, "int", profile=C)
    expect(failures, "1 ? 2 : 3u", OK, 2, "unsigned int")
    expect(failures, "true + 1", OK, 2, "int")
    expect(failures, "0 && 1 / 0", OK, 0)
    expect(failures, "1 || UNKNOWN", OK, 1)
    expect(failures, "0 && var", NONCONSTANT)
    expect(failures, "RED | 1", OK, 3)
    return failures


def check_literal_types() -> list[str]:
    failures = []
    for text, ctype in (("0x7FFFFFFF", "int"), ("0x80000000", "unsigned int"), ("2147483647", "int"),
                        ("2147483648", "unsigned long"), ("4294967295", "unsigned long"),
                        ("037777777777", "unsigned int"), ("1u", "unsigned int"), ("1l", "long"),
                        ("1ul", "unsigned long"), ("1i64", "long long"),
                        ("0xFFFFFFFFFFFFFFFFui64", "unsigned long long"), ("1e3f", "float"), ("1.0", "double"),
                        ("'A'", "char")):
        expect(failures, text, OK, ctype=ctype)
    expect(failures, "'A'", OK, 65, "int", profile=C)
    expect(failures, "4294967296", OK, 4294967296, "long long")
    expect(failures, "4294967296u", OK, 4294967296, "unsigned long long")
    expect(failures, "4294967296", UNSUPPORTED, profile=SHC, cause="literal")
    expect(failures, "18446744073709551616", UNSUPPORTED, cause="literal")
    expect(failures, "1i64", UNSUPPORTED, profile=SHC, cause="literal")
    expect(failures, "08", UNSUPPORTED, cause="literal")
    expect(failures, "0x", UNSUPPORTED, cause="literal")
    return failures


def check_floats() -> list[str]:
    failures = []
    third = struct.unpack("<f", struct.pack("<f", 1 / 3))[0]
    expect(failures, "1.0f / 3.0f", OK, third, "float")
    expect(failures, "1.0 / 3.0", OK, 1 / 3, "double")
    expect(failures, "1e3f", OK, 1000.0)
    expect(failures, "(float)16777217", OK, 16777216.0)
    # Just above the halfway point between 1.0f and the next float: rounding through a double would give 1.0f.
    expect(failures, "1.00000005960464477550f", OK, struct.unpack("<f", struct.pack("<I", 0x3F800001))[0])
    expect(failures, "(int)3e9f", UNSUPPORTED, cause="float range")
    expect(failures, "(int)2.9", OK, 2)
    expect(failures, "(int)-2.9", OK, -2)
    expect(failures, "1e39f", UNSUPPORTED, cause="float range")
    expect(failures, "1.0 / 0.0", UNSUPPORTED, cause="division by zero")
    expect(failures, "1.0 % 2", UNSUPPORTED, cause="operand type")
    return failures


def check_casts_and_sizes() -> list[str]:
    failures = []
    expect(failures, "(S16)0x18000", OK, -0x8000, "short")
    expect(failures, "(S16)0x18000", UNSUPPORTED, profile=SHC, cause="narrowing")
    expect(failures, "(unsigned char)300", OK, 44)
    expect(failures, "(void *)0", OK, 0, "void *")
    expect(failures, "(char *)-1", OK, 0xFFFFFFFF)
    expect(failures, "(MYSTERY)0", UNRESOLVED, cause="unknown identifier")
    expect(failures, "(void (*)(int))0", UNSUPPORTED, cause="type name")
    expect(failures, "sizeof(int)", OK, 4, "unsigned int")
    expect(failures, "sizeof(U32)", OK, 4)
    expect(failures, "sizeof(struct VEC)", OK, 12)
    expect(failures, "sizeof(struct UNKNOWN)", UNSUPPORTED, cause="sizeof")
    expect(failures, "sizeof(char *)", OK, 4)
    expect(failures, "sizeof('a')", OK, 1)
    expect(failures, "sizeof('a')", OK, 4, profile=C)
    expect(failures, "sizeof(var)", UNSUPPORTED, cause="sizeof of an expression")
    expect(failures, "sizeof(UNKNOWN)", UNRESOLVED, cause="unknown identifier")
    result = ceval.convert(value_of("-1"), U32, CPP)
    if result.value != 0xFFFFFFFF:
        failures.append(f"-1 at an unsigned slot: got {result}")
    return failures


def check_characters() -> list[str]:
    failures = []
    expect(failures, "'ABCD'", OK, 0x41424344, "int")
    expect(failures, "'ABCD'", UNSUPPORTED, profile=SHC, cause="character constant")
    expect(failures, "'ABCDE'", UNSUPPORTED, cause="character constant")
    expect(failures, "L'A'", OK, 65, "wchar_t")
    expect(failures, "'\\xff'", OK, -1, "char")
    expect(failures, "'\\\\'", OK, 92)
    expect(failures, "'\\''", OK, 39)
    expect(failures, "'/'", OK, 47)
    expect(failures, "'\\101'", OK, 65)
    expect(failures, "'\\q'", UNSUPPORTED, cause="character constant")
    return failures


def check_preprocessor_mode() -> list[str]:
    failures = []

    def is_defined(name):
        return {"ON": True, "OFF": False}.get(name)

    pp = {"mode": "pp", "is_defined": is_defined}
    expect(failures, "1 << 31", OK, 0x80000000, "intmax_t", **pp)
    expect(failures, "1 << 31", UNSUPPORTED, profile=SHC, cause="signed overflow", **pp)
    expect(failures, "0xFFFFFFFF + 1", OK, 0x100000000, **pp)
    expect(failures, "0xFFFFFFFF + 1", OK, 0, "uintmax_t", profile=SHC, **pp)
    expect(failures, "defined ON && !defined(OFF)", OK, 1, **pp)
    expect(failures, "defined(MAYBE)", UNRESOLVED, cause="unknown identifier", **pp)
    expect(failures, "defined(OFF) && MAYBE", OK, 0, **pp)
    expect(failures, "MAYBE >= 2 && !defined(ON)", OK, 0, **pp)
    expect(failures, "MAYBE || defined(ON)", OK, 1, **pp)
    expect(failures, "MAYBE && defined(ON)", UNRESOLVED, **pp)
    expect(failures, "MAYBE || defined(OFF)", UNRESOLVED, **pp)
    expect(failures, "sizeof(int) && 0", UNSUPPORTED, **pp)
    expect(failures, "MAYBE && 0", UNRESOLVED, cause="unknown identifier")
    expect(failures, "defined(ON) ? 5 : MAYBE", OK, 5, **pp)
    expect(failures, "MAYBE > 1", UNRESOLVED, **pp)
    expect(failures, "'A' == 65", OK, 1, **pp)
    expect(failures, "sizeof(int)", UNSUPPORTED, cause="not a #if expression", **pp)
    expect(failures, "(int)1", UNSUPPORTED, cause="not a #if expression", **pp)
    expect(failures, "1.0", UNSUPPORTED, cause="not a #if expression", **pp)
    expect(failures, "0xFFFFFFFFFFFFFFFF", OK, 0xFFFFFFFFFFFFFFFF, "uintmax_t", **pp)
    expect(failures, "-1 < 0u", OK, 0, **pp)
    expect(failures, "defined(SUM) || SUM", OK, 1, **pp)
    expect(failures, "defined(SUM) && SUM", UNRESOLVED, **pp)
    return failures


def check_function_macros_in_if() -> list[str]:
    failures = []
    pp = {"mode": "pp", "is_defined": lambda name: None}
    expect(failures, "CAT(0x06, 00) == 0x0600", OK, 1, **pp)
    expect(failures, "VER(HIGH) == 0x06000000", OK, 1, **pp)
    expect(failures, "TWICE(TWICE(1)) == 4", OK, 1, **pp)
    expect(failures, "CAT(, 5)", OK, 5, **pp)
    expect(failures, "PICK(1, 2, 3)", OK, 1, **pp)
    expect(failures, "PICK(7)", OK, 7, **pp)
    expect(failures, "ARGS(1)", OK, 1, **pp)
    expect(failures, "ADD(1)", UNSUPPORTED, cause="macro arguments", **pp)
    expect(failures, "STR(1)", UNSUPPORTED, **pp)
    expect(failures, "SELF(1)", UNSUPPORTED, cause="macro cycle", **pp)
    expect(failures, "CAT(+, -)", UNSUPPORTED, cause="token pasting", **pp)
    expect(failures, "CAT(MAYBE, 1)", UNRESOLVED, **pp)
    expect(failures, "CAT(x, 1)", UNSUPPORTED, cause="not a #if expression", **pp)
    expect(failures, "JOIN", UNRESOLVED, cause="unknown identifier", **pp)
    expect(failures, "CAT(1, 2)", UNSUPPORTED, cause="function-like macro")
    return failures


def check_macros_and_names() -> list[str]:
    failures = []
    expect(failures, "SUM * 3", OK, 7)
    expect(failures, "LOOP", UNSUPPORTED, cause="macro cycle")
    expect(failures, "PASTE", UNSUPPORTED, cause="token pasting")
    expect(failures, "ERRNO", UNSUPPORTED, cause="macro expands to a call")
    expect(failures, "LOCATION(0, 0)", UNSUPPORTED, cause="function-like macro")
    expect(failures, "LOCATION(x, 0)", NONCONSTANT)
    expect(failures, "LOCATION", UNRESOLVED, cause="unknown identifier")
    for text, names, literal in (("NULL", ("NULL",), False), ("0", (), True), ("FLAG | 0x80", ("FLAG",), True),
                                 ("ALIAS", ("ALIAS",), False), ("RED", ("RED",), False),
                                 ("(void *)NULL", ("NULL",), False)):
        result = value_of(text)
        if result.names != names or result.literal != literal:
            failures.append(f"{text!r}: names {result.names} literal {result.literal}, want {names} {literal}")
    return failures


def check_nonconstant_and_unsupported() -> list[str]:
    failures = []
    for text in ("p->f", "a[1]", "&g", "*p", "x = 1", "call(0)", '"text"', "x++", "var", "UNKNOWN + var",
                 "s.f"):
        expect(failures, text, NONCONSTANT)
    expect(failures, "UNKNOWN", UNRESOLVED, cause="unknown identifier")
    expect(failures, "(1, 2)", UNSUPPORTED, cause="comma")
    expect(failures, "nullptr", UNSUPPORTED, cause="C++ construct")
    expect(failures, "1 2", UNSUPPORTED, cause="syntax")
    expect(failures, "??/", UNSUPPORTED, cause="syntax")
    expect(failures, "", UNSUPPORTED, cause="syntax")
    expect(failures, "(1", UNSUPPORTED, cause="syntax")
    expect(failures, "UNKNOWN + 1 / 0", UNRESOLVED)
    return failures


def check_profiles_differ() -> list[str]:
    """One token with different values under two profiles: the scorer reports such a pair as counterevidence."""
    cpp, shc = value_of("'\\xff' < 0"), value_of("(S16)0x18000", SHC)
    failures = []
    if not (cpp.ok and cpp.value == 1 and shc.status == UNSUPPORTED):
        failures.append(f"profiles: got {cpp} and {shc}")
    if CPP.predefines.get("__cplusplus") is None or "__cplusplus" in C.predefines:
        failures.append("__cplusplus must be predefined in C++ mode only")
    return failures


# Clean compiler values that ceval refuses on purpose, each with its reason. Any other refusal of a clean case fails.
REFUSED = {
    "(1, 2)": "a comma in a constant is unsupported (plan)",
    "'\\x41\\x42'": "a multi-character constant that starts with a numeric escape has no known rule",
    "'\\101\\102'": "a multi-character constant that starts with a numeric escape has no known rule",
    "'\\x41\\x42\\x43'": "a multi-character constant that starts with a numeric escape has no known rule",
    "'\\xff\\x01'": "a multi-character constant that starts with a numeric escape has no known rule",
    "'\\x41\\x42\\x43\\x44'": "a multi-character constant that starts with a numeric escape has no known rule",
    "(__int64)1e19": "a float to integer conversion out of range has no rule",
    "1e308 * 10.0": "a float overflow to infinity is unsupported",
    "(float)1e39": "a float overflow to infinity is unsupported",
    "UNDEFINED_NAME == 0": "an unknown #if name is unresolved, never 0 (plan)",
    "UNDEFINED_NAME": "an unknown #if name is unresolved, never 0 (plan)",
    "1 << 64": "a shift count out of range is unsupported",
    "1 << -1": "a shift count out of range is unsupported",
}


def check_probe_fixtures() -> list[str]:
    """ceval against what cl.exe gave in the VC10 probe (tools/evidence/probe.py writes the fixtures)."""
    failures = []
    for language, profile in (("c", C), ("cpp", CPP)):
        path = probe.FIXTURES / f"vc10-{language}.json"
        fixture = json.loads(path.read_text(encoding="utf-8"))
        for case in fixture["cases"]:
            if any(name in case["text"] for name in probe.ENUM_NAMES + ("probe_enum",)):
                continue  # enum values need a header; cheaderstests.py checks them
            result = probe.evaluate(case, profile)
            problem = probe.disagreement(case, result, language)
            if problem and not (case["text"] in REFUSED and not result.ok):
                failures.append(f"probe {language} {case['kind']} {case['text']!r}: {problem}")
        for name, value in profile.predefines.items():
            if fixture["predefines"].get(name) != value:
                failures.append(f"probe {language}: profile {name}={value!r}, compiler "
                                f"{fixture['predefines'].get(name)!r}")
    return failures


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_integer_operations, check_literal_types, check_floats, check_casts_and_sizes,
                  check_characters, check_preprocessor_mode, check_function_macros_in_if, check_macros_and_names,
                  check_nonconstant_and_unsupported, check_profiles_differ, check_probe_fixtures):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    print("\n".join(found) or "cevaltests: all passed")
    sys.exit(1 if found else 0)
