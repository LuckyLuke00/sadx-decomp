"""The VC10 probe: what cl.exe makes of constant expressions, kept as test fixtures for the evaluator.

  python -I tools/evidence/probe.py fixtures
      compile the cases below in C and in C++ mode, run them, and write probe/vc10-c.json and probe/vc10-cpp.json
  python -I tools/evidence/probe.py differential [--count N] [--seed S] [--language c|cpp]
      compare ceval with cl.exe on N seeded random integer expressions and print each disagreement; writes nothing

Both need the repo's toolchain in .toolchain (tools/check.py setup) and build in build/probe. The tests read only
the fixtures, so they run without cl.exe.

Every value comes from a file-scope initializer, so the compiler folds it; the program only prints it. A case
that does not compile gets the error code, and a case that compiles with a warning keeps the warning codes. A
#if case keeps its truth value. The predefines are read before any #include.

Standard library only.
"""

import argparse
import json
import random
import re
import struct
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))

import ceval  # noqa: E402
import profiles  # noqa: E402

ROOT = HERE.parents[1]
FIXTURES = HERE / "probe"
BUILD = ROOT / "build" / "probe"
TOOLCHAIN = ROOT / ".toolchain"
FLAGS = ("/nologo", "/DWIN32", "/D_WINDOWS", "/EHsc", "/fp:precise", "/DNDEBUG", "/MT", "/O2", "/W4")
PROFILE_NAMES = {"c": "msvc-vc10-x86-c", "cpp": "msvc-vc10-x86-cpp"}
LANGUAGE_FLAGS = {"c": "/TC", "cpp": "/TP"}
MAX_ROUNDS = 40
TYPE_NAMES = {"__int64": "long long", "unsigned __int64": "unsigned long long"}  # typeid spelling: ceval spelling
DIAGNOSTIC = re.compile(r"\((\d+)\) : (?:fatal )?(error|warning) (C\d{4})")

INT, F32, F64, PP = "int", "f32", "f64", "pp"
BOTH, C_ONLY, CPP_ONLY = ("c", "cpp"), ("c",), ("cpp",)
ENUM_DECLARATION = "enum probe_enum { PROBE_HIGH = 0x80000000, PROBE_NEXT, PROBE_ALL = 0xFFFFFFFF };"
ENUM_NAMES = ("PROBE_HIGH", "PROBE_NEXT", "PROBE_ALL")

# (kind, expression, languages). Grouped as the plan lists them: shifts, operators, literal typing, characters,
# sizes, conversions, floats, enums, #if.
CASES = (
    (INT, "1 << 31", BOTH), (INT, "1 << 30", BOTH), (INT, "1u << 31", BOTH), (INT, "1 << 32", BOTH),
    (INT, "1 << 33", BOTH), (INT, "1u << 32", BOTH), (INT, "1 << -1", BOTH), (INT, "1 >> 32", BOTH),
    (INT, "1i64 << 32", BOTH), (INT, "1i64 << 63", BOTH), (INT, "1i64 << 64", BOTH),
    (INT, "-1 >> 1", BOTH), (INT, "-8 >> 1", BOTH), (INT, "-1 >> 31", BOTH), (INT, "0x80000000 >> 31", BOTH),
    (INT, "(-2147483647 - 1) >> 4", BOTH), (INT, "-1 << 1", BOTH), (INT, "-1i64 >> 40", BOTH),
    (INT, "~0x2000", BOTH), (INT, "~0", BOTH), (INT, "~0u", BOTH), (INT, "~0x2000u", BOTH),
    (INT, "(unsigned int)~0x2000", BOTH), (INT, "-0x80000000", BOTH), (INT, "-2147483648", BOTH),
    (INT, "0x7FFFFFFF + 1", BOTH), (INT, "2147483647 + 1", BOTH), (INT, "-2147483647 - 2", BOTH),
    (INT, "65536 * 65536", BOTH), (INT, "46341 * 46341", BOTH), (INT, "0xFFFF * 0xFFFF", BOTH),
    (INT, "0u - 1", BOTH), (INT, "5 / -2", BOTH), (INT, "-5 / 2", BOTH), (INT, "-5 % 3", BOTH),
    (INT, "5 % -3", BOTH), (INT, "-7u / 2", BOTH), (INT, "1 / 0", BOTH), (INT, "1 % 0", BOTH),
    (INT, "(-2147483647 - 1) / -1", BOTH), (INT, "(-2147483647 - 1) % -1", BOTH),
    (INT, "0x7FFFFFFFFFFFFFFFi64 + 1", BOTH),
    (INT, "-1 < 0u", BOTH), (INT, "-1 < 0ul", BOTH), (INT, "-1L < 1u", BOTH), (INT, "-1 < 1i64", BOTH),
    (INT, "-1 < 1ui64", BOTH), (INT, "1 ? -1 : 0u", BOTH), (INT, "0 ? 1 : 2L", BOTH), (INT, "!5", BOTH),
    (INT, "3 && 0", BOTH), (INT, "(1, 2)", BOTH), (INT, "-(unsigned short)1", BOTH),
    (INT, "0x7FFFFFFF", BOTH), (INT, "0x80000000", BOTH), (INT, "0xFFFFFFFF", BOTH), (INT, "0x100000000", BOTH),
    (INT, "2147483647", BOTH), (INT, "2147483648", BOTH), (INT, "4294967295", BOTH), (INT, "4294967296", BOTH),
    (INT, "017", BOTH), (INT, "037777777777", BOTH), (INT, "040000000000", BOTH), (INT, "0", BOTH),
    (INT, "0x0", BOTH), (INT, "1u", BOTH), (INT, "1l", BOTH), (INT, "1ul", BOTH), (INT, "1lu", BOTH),
    (INT, "1ll", BOTH), (INT, "1ull", BOTH), (INT, "1i64", BOTH), (INT, "1ui64", BOTH),
    (INT, "0xFFFFFFFFi64", BOTH), (INT, "2147483648u", BOTH), (INT, "4294967296u", BOTH),
    (INT, "9223372036854775807", BOTH), (INT, "9223372036854775808", BOTH),
    (INT, "4294967296l", BOTH), (INT, "4294967296ul", BOTH), (INT, "0x100000000L", BOTH),
    (INT, "0x100000000u", BOTH), (INT, "0x8000000000000000", BOTH), (INT, "0xFFFFFFFFFFFFFFFF", BOTH),
    (INT, "18446744073709551615", BOTH), (INT, "18446744073709551616", BOTH), (INT, "0x10000000000000000", BOTH),
    (INT, "'A'", BOTH), (INT, "'AB'", BOTH), (INT, "'ABCD'", BOTH), (INT, "'ABCDE'", BOTH),
    (INT, "'\\xff'", BOTH), (INT, "'\\377'", BOTH), (INT, "'\\0'", BOTH), (INT, "'\\n'", BOTH),
    (INT, "L'A'", BOTH), (INT, "L'\\xffff'", BOTH), (INT, "L'AB'", BOTH), (INT, "'\\x41\\x42'", BOTH),
    (INT, "'\\x41B'", BOTH), (INT, "'A\\x42'", BOTH), (INT, "'\\101\\102'", BOTH), (INT, "'\\nA'", BOTH),
    (INT, "'A\\n'", BOTH), (INT, "'\\x41\\x42\\x43'", BOTH), (INT, "'AB\\x43'", BOTH), (INT, "'\\xff\\x01'", BOTH),
    (INT, "'\\x41\\x42\\x43\\x44'", BOTH), (INT, "'A\\x42CD'", BOTH),
    (INT, "sizeof('a')", BOTH), (INT, "sizeof(L'a')", BOTH), (INT, "sizeof(1 ? 'a' : 'b')", BOTH),
    (INT, "sizeof(char)", BOTH), (INT, "sizeof(short)", BOTH), (INT, "sizeof(int)", BOTH),
    (INT, "sizeof(long)", BOTH), (INT, "sizeof(__int64)", BOTH), (INT, "sizeof(long long)", BOTH),
    (INT, "sizeof(float)", BOTH), (INT, "sizeof(double)", BOTH), (INT, "sizeof(long double)", BOTH),
    (INT, "sizeof(void *)", BOTH), (INT, "sizeof(1.0f)", BOTH), (INT, "sizeof(1.0)", BOTH),
    (INT, "sizeof(1.0L)", BOTH), (INT, "sizeof(0x80000000)", BOTH), (INT, "sizeof(1i64)", BOTH),
    (INT, "sizeof(wchar_t)", CPP_ONLY), (INT, "sizeof(bool)", CPP_ONLY), (INT, "true + 1", CPP_ONLY),
    (INT, "true", CPP_ONLY), (INT, "(bool)5", CPP_ONLY),
    (INT, "(short)0x18000", BOTH), (INT, "(signed char)0x80", BOTH), (INT, "(unsigned char)-1", BOTH),
    (INT, "(char)200", BOTH), (INT, "(short)-32769", BOTH), (INT, "(unsigned short)70000", BOTH),
    (INT, "(int)0x80000000", BOTH), (INT, "(int)4294967295", BOTH), (INT, "(long)0xFFFFFFFFi64", BOTH),
    (INT, "(unsigned int)-1", BOTH), (INT, "(unsigned __int64)-1", BOTH), (INT, "(__int64)0xFFFFFFFF", BOTH),
    (INT, "(int)2.9", BOTH), (INT, "(int)-2.9", BOTH), (INT, "(int)3e9f", BOTH), (INT, "(int)3e9", BOTH),
    (INT, "(int)-3e9", BOTH), (INT, "(unsigned int)3e9", BOTH), (INT, "(unsigned int)-1.0", BOTH),
    (INT, "(unsigned int)5e9", BOTH), (INT, "(short)1e5", BOTH), (INT, "(unsigned char)300.0", BOTH),
    (INT, "(__int64)1e19", BOTH), (INT, "(int)1e10f", BOTH), (INT, "(char)-129", BOTH),
    (F32, "1.0f / 3.0f", BOTH), (F64, "1.0 / 3.0", BOTH), (F64, "1.0f / 3.0", BOTH), (F32, "1e3f", BOTH),
    (F32, "0.1f + 0.2f", BOTH), (F32, "(float)0.1", BOTH), (F32, "16777217.0f", BOTH),
    (F32, "(float)16777217", BOTH), (F64, "(double)(1.0f / 3.0f)", BOTH), (F32, "0x7FFFFFFF * 1.0f", BOTH),
    (F32, "3.0e38f * 10.0f", BOTH), (F64, "1e308 * 10.0", BOTH), (F32, "(float)1e39", BOTH),
    (F32, "1.0f / 0.0f", BOTH), (F64, "0.0 / 0.0", BOTH), (F32, "-0.0f", BOTH), (F64, "1.0L / 3.0", BOTH),
    (F32, "1.17549435e-38f / 2.0f", BOTH), (F32, "1.40129846e-45f", BOTH), (F32, "0.5f * 3", BOTH),
    (F64, "1e-320", BOTH), (F32, "(float)(1 << 24) + 1.0f", BOTH), (F32, "3.14159265358979f", BOTH),
    (F32, "1.0f + 1e-8f", BOTH), (F64, "2.5e-1", BOTH), (F64, ".5", BOTH), (F64, "5.", BOTH),
    (INT, "PROBE_HIGH", BOTH), (INT, "PROBE_NEXT", BOTH), (INT, "PROBE_ALL", BOTH),
    (INT, "sizeof(enum probe_enum)", BOTH),
    (PP, "0xFFFFFFFF + 1 == 0", BOTH), (PP, "0xFFFFFFFFFFFFFFFF + 1 == 0", BOTH), (PP, "(1 << 31) < 0", BOTH),
    (PP, "(1 << 63) < 0", BOTH), (PP, "-1 < 0u", BOTH), (PP, "-1 < 0", BOTH), (PP, "~0 == -1", BOTH),
    (PP, "~0u == 0xFFFFFFFF", BOTH), (PP, "-1 >> 1 == -1", BOTH), (PP, "-1 >> 63 == -1", BOTH),
    (PP, "0x7FFFFFFFFFFFFFFF + 1 < 0", BOTH), (PP, "2147483648 < 0", BOTH), (PP, "4294967295 == -1", BOTH),
    (PP, "18446744073709551615 == -1", BOTH), (PP, "'A' == 65", BOTH), (PP, "'AB' == 0x4142", BOTH),
    (PP, "'ABCD' == 0x41424344", BOTH), (PP, "'\\xff' < 0", BOTH), (PP, "L'A' == 65", BOTH),
    (PP, "L'\\xffff' < 0", BOTH), (PP, "1 ? 2 : 0", BOTH), (PP, "0 ? 1 : 0", BOTH), (PP, "1 / 0", BOTH),
    (PP, "1 % 0", BOTH), (PP, "1 || 1 / 0", BOTH), (PP, "0 && 1 / 0", BOTH), (PP, "UNDEFINED_NAME == 0", BOTH),
    (PP, "UNDEFINED_NAME", BOTH), (PP, "defined(_MSC_VER)", BOTH), (PP, "defined UNDEFINED_NAME", BOTH),
    (PP, "(-2147483647 - 1) / -1 > 0", BOTH), (PP, "1 << 64", BOTH), (PP, "1 << -1", BOTH),
    (PP, "-1 % 0u", BOTH), (PP, "5 / -2 == -2", BOTH), (PP, "-5 % 3 == -2", BOTH),
    (PP, "1i64 == 1", BOTH), (PP, "0x80000000 > 0", BOTH), (PP, "true", CPP_ONLY), (PP, "true == 1", CPP_ONLY),
)

PREDEFINES = ("_MSC_VER", "_MSC_FULL_VER", "_MSC_BUILD", "_MSC_EXTENSIONS", "_M_IX86", "_M_IX86_FP", "_M_X64",
              "_M_AMD64", "_M_ARM", "_WIN32", "_WIN64", "_INTEGRAL_MAX_BITS", "__cplusplus", "__STDC__",
              "__STDC_VERSION__", "__STDC_HOSTED__", "_CHAR_UNSIGNED", "_CPPRTTI", "_CPPUNWIND",
              "_NATIVE_WCHAR_T_DEFINED", "_WCHAR_T_DEFINED", "_MT", "_DLL", "_DEBUG", "NDEBUG", "WIN32",
              "_WINDOWS", "_MANAGED", "__CLR_VER", "__cplusplus_cli", "_M_CEE", "_OPENMP", "_Wp64", "_ATL_VER",
              "_MFC_VER", "_VC_NODEFAULTLIB", "_PREFAST_", "__midl", "_WIN32_WCE", "_WIN32_WINNT", "WINVER",
              "NTDDI_VERSION", "_POSIX_", "DBG", "WINXP")


class ProbeError(Exception):
    """The probe could not compile or run."""


def cases_for(language: str) -> list[tuple]:
    return [(kind, text) for kind, text, languages in CASES if language in languages]


# The probe program


class _Source:
    """The text of one probe program, with the case that each line belongs to."""

    def __init__(self):
        self.lines: list[str] = []
        self.owner: dict[int, int] = {}  # line number (1-based): case index

    def add(self, text: str, case: int | None = None):
        self.lines.append(text)
        if case is not None:
            self.owner[len(self.lines)] = case

    def text(self) -> str:
        return "\n".join(self.lines) + "\n"


def program(cases: list[tuple], skipped: set[int]) -> _Source:
    """The probe program for CASES, without the cases in SKIPPED. Each case's own code is on lines of its own."""
    source = _Source()
    source.add("#define PROBE_STR2(x) #x")
    source.add("#define PROBE_STR(x) PROBE_STR2(x)")
    for index, name in enumerate(PREDEFINES):
        source.add(f"#ifdef {name}")
        source.add(f"static const char *probe_define_{index} = PROBE_STR({name});")
        source.add("#else")
        source.add(f"static const char *probe_define_{index} = 0;")
        source.add("#endif")
    source.add("#include <stdio.h>")
    source.add("#include <string.h>")
    source.add("#ifdef __cplusplus")
    source.add("#include <typeinfo>")
    source.add("#define PROBE_TYPE(e) typeid(e).name()")
    source.add("#else")
    source.add('#define PROBE_TYPE(e) ""')
    source.add("#endif")
    source.add(ENUM_DECLARATION)
    for index, (kind, text) in enumerate(cases):
        if index in skipped:
            continue
        if kind == INT:
            source.add(f"static const unsigned __int64 probe_bits_{index} = (unsigned __int64)({text});", index)
            source.add(f"static const unsigned int probe_size_{index} = sizeof({text});", index)
            # A type narrower than int promotes, so its sign cannot be read this way: 2 marks it unknown.
            source.add(f"static const int probe_signed_{index} = sizeof({text}) < sizeof(int) ? 2 "
                       f": ({text}) * 0 - 1 < 0;", index)
        elif kind in (F32, F64):
            ctype = "float" if kind == F32 else "double"
            source.add(f"static const {ctype} probe_float_{index} = {text};", index)
        else:
            source.add(f"#if {text}", index)
            source.add(f"static const int probe_truth_{index} = 1;")
            source.add("#else")
            source.add(f"static const int probe_truth_{index} = 0;")
            source.add("#endif")
    source.add("int main(void)")
    source.add("{")
    for index, name in enumerate(PREDEFINES):
        source.add(f'    printf("define {name} %s\\n", probe_define_{index} ? probe_define_{index} : "<undefined>");')
    for index, (kind, text) in enumerate(cases):
        if index in skipped:
            continue
        if kind == INT:
            source.add(f'    printf("{index} %u %d %I64u %s\\n", probe_size_{index}, probe_signed_{index}, '
                       f"probe_bits_{index}, PROBE_TYPE({text}));", index)
        elif kind == F32:
            source.add(f"    {{ unsigned int b; memcpy(&b, &probe_float_{index}, 4); "
                       f'printf("{index} %08x\\n", b); }}')
        elif kind == F64:
            source.add(f"    {{ unsigned __int64 b; memcpy(&b, &probe_float_{index}, 8); "
                       f'printf("{index} %016I64x\\n", b); }}')
        else:
            source.add(f'    printf("{index} %d\\n", probe_truth_{index});')
    source.add("    return 0;")
    source.add("}")
    return source


def compile_and_run(cases: list[tuple], language: str) -> tuple[dict, dict, dict, str]:
    """Compile CASES as LANGUAGE until the program builds, then run it. Returns the errors (case: code), the
    warnings (case: codes), the output lines (case: text, and "define NAME": value) and the compiler banner."""
    sys.path.insert(0, str(ROOT / "tools"))
    import toolchain
    env = toolchain.env(TOOLCHAIN)
    BUILD.mkdir(parents=True, exist_ok=True)
    stem = BUILD / f"probe-{language}"
    errors: dict[int, str] = {}
    for _ in range(MAX_ROUNDS):
        source = program(cases, set(errors))
        stem.with_suffix(".c").write_text(source.text(), encoding="ascii")
        command = [str(TOOLCHAIN / "bin" / "cl.exe"), *FLAGS, LANGUAGE_FLAGS[language], stem.with_suffix(".c").name,
                   f"/Fe{stem.name}.exe", f"/Fo{stem.name}.obj"]
        built = subprocess.run(command, cwd=BUILD, env=env, capture_output=True, text=True)
        warnings: dict[int, list[str]] = {}
        new_errors = {}
        unowned = []
        for match in DIAGNOSTIC.finditer(built.stdout + built.stderr):
            line, severity, code = int(match[1]), match[2], match[3]
            case = source.owner.get(line)
            if case is None:
                if severity == "error":
                    unowned.append(match[0])
                continue
            if severity == "error":
                new_errors.setdefault(case, code)
            else:
                warnings.setdefault(case, [])
                if code not in warnings[case]:
                    warnings[case].append(code)
        if unowned:
            raise ProbeError(f"errors outside every case: {unowned[:5]}\n{built.stdout[-2000:]}")
        if not new_errors:
            if built.returncode != 0:
                raise ProbeError(f"cl.exe failed with no case error:\n{built.stdout[-2000:]}")
            break
        errors.update(new_errors)
    else:
        raise ProbeError(f"the program still does not build after {MAX_ROUNDS} rounds")
    ran = subprocess.run([str(stem.with_suffix(".exe"))], capture_output=True, text=True, check=True)
    output = {}
    for line in ran.stdout.splitlines():
        head, _, rest = line.partition(" ")
        if head == "define":
            name, _, value = rest.partition(" ")
            output[f"define {name}"] = None if value == "<undefined>" else value
        else:
            output[int(head)] = rest
    banner = subprocess.run([str(TOOLCHAIN / "bin" / "cl.exe")], env=env, capture_output=True, text=True)
    versions = [line.strip() for line in (banner.stderr + banner.stdout).splitlines() if "Version" in line]
    if not versions:
        raise ProbeError(f"cl.exe printed no version line:\n{banner.stderr}{banner.stdout}")
    return errors, warnings, output, versions[0]


def results(cases: list[tuple], language: str) -> dict:
    """The fixture for LANGUAGE: the compiler, the flags, each case's outcome and the predefines."""
    errors, warnings, output, banner = compile_and_run(cases, language)
    found = []
    for index, (kind, text) in enumerate(cases):
        case = {"kind": kind, "text": text}
        if index in errors:
            case["error"] = errors[index]
            found.append(case)
            continue
        case["warnings"] = warnings.get(index, [])
        line = output[index]
        if kind == INT:
            size, signed, bits, type_name = (line.split(" ", 3) + [""])[:4]
            bits, signed = int(bits), {"0": False, "1": True, "2": None}[signed]
            case["value"] = bits - (1 << 64) if bits >= 1 << 63 and signed is not False else bits
            case["bits"] = int(size) * 8
            case["signed"] = signed
            if language == "cpp":
                case["type"] = TYPE_NAMES.get(type_name, type_name)
        elif kind in (F32, F64):
            case["pattern"] = line
        else:
            case["value"] = int(line)
        found.append(case)
    predefines = {name: output[f"define {name}"] for name in PREDEFINES}
    return {"compiler": banner, "flags": list(FLAGS) + [LANGUAGE_FLAGS[language]], "language": language,
            "cases": found, "predefines": predefines}


# Comparing ceval with a fixture


def float_pattern(value: float, kind: str) -> str:
    if kind == F32:
        return f"{struct.unpack('<I', struct.pack('<f', value))[0]:08x}"
    return f"{struct.unpack('<Q', struct.pack('<d', value))[0]:016x}"


def disagreement(case: dict, result: ceval.Result, language: str) -> str | None:
    """Why ceval's RESULT for one fixture CASE disagrees with the compiler, or None when it agrees.

    A compiler error must not give a value. A case the compiler took with a warning may be unsupported; a clean
    case must give the compiler's value and type. A #if case compares truth values only."""
    kind = case["kind"]
    if "error" in case:
        return f"compiler error {case['error']}, ceval gives {result.value!r}" if result.ok else None
    if not result.ok:
        if case["warnings"]:
            return None
        return f"compiler gives {case.get('value', case.get('pattern'))!r}, ceval {result.status}: {result.cause} " \
               f"{result.detail}".rstrip()
    if kind == PP:
        return None if bool(result.value) == bool(case["value"]) else \
            f"compiler truth {case['value']}, ceval {result.value!r}"
    if kind in (F32, F64):
        bits = 32 if kind == F32 else 64
        if result.ctype.kind != "float" or result.ctype.bits != bits:
            return f"compiler type {kind}, ceval {result.ctype.name}"
        found = float_pattern(result.value, kind)
        return None if found == case["pattern"] else f"compiler {case['pattern']}, ceval {found} ({result.value!r})"
    value = int(result.value)
    if value != case["value"]:
        return f"compiler {case['value']}, ceval {value}"
    signed_differs = case["signed"] is not None and result.ctype.signed != case["signed"]
    if result.ctype.bits != case["bits"] or signed_differs:
        if not (result.ctype.kind == "bool" and case.get("type") == "bool"):
            return f"compiler {case['bits']} bits signed={case['signed']}, ceval {result.ctype.name}"
    if language == "cpp" and result.ctype.name != case["type"]:
        return f"compiler type {case['type']}, ceval {result.ctype.name}"
    return None


def evaluate(case: dict, profile: profiles.Profile) -> ceval.Result:
    """CASE evaluated by ceval under PROFILE: #if cases in preprocessor mode, with only _MSC_VER defined."""
    if case["kind"] == PP:
        return ceval.evaluate(case["text"], profile, mode="pp", is_defined=lambda name: name in profile.predefines)
    return ceval.evaluate(case["text"], profile)


# Seeded random expressions


LEAVES = ("0", "1", "2", "3", "7", "15", "31", "100", "255", "256", "1000", "65535", "65536", "0x7F", "0x80",
          "0xFF", "0xFFFF", "0x7FFFFFFF", "0x80000000", "0xFFFFFFFF", "2147483647", "2147483648", "4294967295",
          "1u", "5u", "0x10u", "3L", "7UL", "1i64", "0xFFFFFFFFi64", "5ui64", "017", "0777", "'A'", "'\\xff'",
          "L'A'")
CASTS = ("(char)", "(signed char)", "(unsigned char)", "(short)", "(unsigned short)", "(int)", "(unsigned int)",
         "(long)", "(unsigned long)", "(__int64)", "(unsigned __int64)")
UNARY = ("-", "~", "!")
BINARY = ("+", "-", "*", "/", "%", "<<", ">>", "&", "|", "^", "<", ">", "<=", ">=", "==", "!=", "&&", "||")


def random_expression(rng: random.Random, depth: int, language: str) -> str:
    """One random integer expression. Divisors are nonzero literals; most shift counts are 0 to 31."""
    if depth == 0 or rng.random() < 0.25:
        return rng.choice(LEAVES)
    roll = rng.random()
    if roll < 0.15:
        return f"{rng.choice(UNARY)}({random_expression(rng, depth - 1, language)})"
    if roll < 0.30:
        casts = CASTS + (("(bool)",) if language == "cpp" else ())
        return f"{rng.choice(casts)}({random_expression(rng, depth - 1, language)})"
    if roll < 0.37:
        parts = [random_expression(rng, depth - 1, language) for _ in range(3)]
        return f"({parts[0]} ? {parts[1]} : {parts[2]})"
    operation = rng.choice(BINARY)
    left = random_expression(rng, depth - 1, language)
    if operation in ("/", "%"):
        right = rng.choice([leaf for leaf in LEAVES if leaf != "0"])
    elif operation in ("<<", ">>"):
        right = str(rng.randrange(32)) if rng.random() < 0.9 else rng.choice(("32", "33", "40", "63", "-1"))
    else:
        right = random_expression(rng, depth - 1, language)
    return f"({left} {operation} {right})"


def differential(count: int, seed: int, language: str) -> int:
    """Compare ceval with cl.exe on COUNT random expressions; print the disagreements and return their number."""
    rng = random.Random(seed)
    cases = [(INT, random_expression(rng, 4, language)) for _ in range(count)]
    profile = profiles.get(PROFILE_NAMES[language])
    found = results(cases, language)["cases"]
    tally = {"agree": 0, "disagree": 0, "compiler error": 0, "ceval unsupported, compiler warned": 0,
             "ceval value, compiler warned": 0}
    for case in found:
        result = evaluate(case, profile)
        problem = disagreement(case, result, language)
        if problem:
            tally["disagree"] += 1
            print(f"{case['text']}\n    {problem}")
        elif "error" in case:
            tally["compiler error"] += 1
        elif case["warnings"]:
            tally["ceval value, compiler warned" if result.ok else "ceval unsupported, compiler warned"] += 1
        else:
            tally["agree"] += 1
    print(", ".join(f"{name} {number}" for name, number in tally.items()))
    return tally["disagree"]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    commands = parser.add_subparsers(dest="command", required=True)
    commands.add_parser("fixtures", help="write probe/vc10-c.json and probe/vc10-cpp.json")
    random_run = commands.add_parser("differential", help="compare ceval with cl.exe on random expressions")
    random_run.add_argument("--count", type=int, default=2000)
    random_run.add_argument("--seed", type=int, default=1)
    random_run.add_argument("--language", choices=sorted(PROFILE_NAMES), default="cpp")
    arguments = parser.parse_args()
    try:
        if arguments.command == "differential":
            return 1 if differential(arguments.count, arguments.seed, arguments.language) else 0
        FIXTURES.mkdir(exist_ok=True)
        for language in PROFILE_NAMES:
            fixture = results(cases_for(language), language)
            path = FIXTURES / f"vc10-{language}.json"
            path.write_text(json.dumps(fixture, indent=1) + "\n", encoding="utf-8", newline="\n")
            print(f"{path.relative_to(ROOT)}: {len(fixture['cases'])} cases, {fixture['compiler']}")
    except ProbeError as error:
        print(f"probe: {error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
