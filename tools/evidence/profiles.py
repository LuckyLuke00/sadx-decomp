"""Compiler profiles: what one compiler does with one language, for the evaluator and the header reader.

A profile names one compiler, target and language, such as msvc-vc10-x86-cpp. It gives the type sizes, the literal
typing, what folding does at the edges (signed overflow, narrowing, signed right shifts, multi-character constants),
the #if width, the compiler's own predefines, the boolean type names and the tokens that header reading drops. A case
with no rule, such as a shift count out of range or a float to int conversion out of range, gives "unsupported": the
evaluator never guesses.

Each profile says where its values come from. The msvc-vc10-x86 values come from a probe compiled with the VC10
compiler (tools/evidence/probe.py); the probe's output is kept as test fixtures in tools/evidence/probe/, and
cevaltests.py checks the evaluator and the predefines against them. The shc values are not probed and not yet checked against the SHC manual.

Standard library only.
"""

from dataclasses import dataclass, field
from functools import cached_property

UNSUPPORTED, WRAP, ARITHMETIC, BIG_ENDIAN = "unsupported", "wrap", "arithmetic", "big-endian"


@dataclass(frozen=True)
class CType:
    """A type as the evaluator sees it. KIND is int, bool, float, pointer, void, record or array. RANK orders the
    integer types for the usual arithmetic conversions: bool 0, char 1, short and wchar_t 2, int 3, long 4,
    long long 5, the #if types 6. A record, an array or an enum whose size is not known has 0 bits."""
    kind: str
    bits: int = 0
    signed: bool = False
    rank: int = 0
    name: str = ""

    def lowest(self) -> int:
        return -(1 << (self.bits - 1)) if self.signed else 0

    def highest(self) -> int:
        return (1 << (self.bits - 1)) - 1 if self.signed else (1 << self.bits) - 1

    def shape(self) -> tuple:
        """What the machine sees: kind, width and sign; the rank and the spelling do not count."""
        return self.kind, self.bits, self.signed


@dataclass(frozen=True)
class Profile:
    name: str
    version: int
    language: str  # c or cpp
    provenance: str
    char_signed: bool
    short_bits: int
    int_bits: int
    long_bits: int
    long_long_bits: int
    pointer_bits: int
    wchar_bits: int
    long_double_bits: int
    size_type: str  # the type of sizeof
    decimal_types: tuple  # the types a decimal literal with no suffix may take, in order
    extra_suffixes: tuple  # integer suffixes beyond u, l, ul and lu, such as i64
    wide_types: tuple  # tried, in order, by a literal with no suffix or u, l, ul, lu that fits none of its types
    signed_overflow: str  # wrap or unsupported
    narrowing: str  # a conversion to a signed type that is out of range: wrap or unsupported
    signed_right_shift: str  # >> on a negative value: arithmetic or unsupported
    multichar: str  # 'ABCD': big-endian (the first character highest) or unsupported
    pp_bits: int  # the #if width
    predefines: dict = field(default_factory=dict)
    boolean_names: tuple = ("BOOL", "Bool", "bool")
    ignored_words: tuple = ()  # dropped, with a (...) group that follows: calling conventions, __declspec, SAL
    ignored_prefixes: tuple = ()  # dropped words that start with one of these, such as _In_

    def builtin(self, words: tuple) -> CType | None:
        """The type that a run of type keywords spells, or None if it spells none."""
        key = tuple(sorted(word for word in words if word not in ("const", "volatile")))
        return self.builtins.get(key)

    def int_type(self, name: str) -> CType:
        return self.builtin(tuple(name.split()))

    def pointer(self, name: str = "void *") -> CType:
        return CType("pointer", self.pointer_bits, False, 0, name)

    def wchar(self) -> CType:
        return CType("int", self.wchar_bits, False, 2, "wchar_t")

    @cached_property
    def type_words(self) -> frozenset:
        """Every keyword that can start a type name."""
        return frozenset(word for key in self.builtins for word in key) | {"const", "volatile"}

    @cached_property
    def builtins(self) -> dict:
        """The built-in types, keyed by their sorted keywords."""
        table = {
            ("char",): CType("int", 8, self.char_signed, 1, "char"),
            ("char", "signed"): CType("int", 8, True, 1, "signed char"),
            ("char", "unsigned"): CType("int", 8, False, 1, "unsigned char"),
            ("void",): CType("void", 0, False, 0, "void"),
            ("float",): CType("float", 32, True, 0, "float"),
            ("double",): CType("float", 64, True, 0, "double"),
            ("double", "long"): CType("float", self.long_double_bits, True, 0, "long double"),
        }
        for words, bits, rank, name in ((("short",), self.short_bits, 2, "short"),
                                        (("int",), self.int_bits, 3, "int"),
                                        (("long",), self.long_bits, 4, "long"),
                                        (("long", "long"), self.long_long_bits, 5, "long long")):
            signed = CType("int", bits, True, rank, name)
            unsigned = CType("int", bits, False, rank, "unsigned " + name)
            variants = [words, words + ("signed",)]
            if words != ("int",):
                variants += [words + ("int",), words + ("int", "signed")]
            for variant in variants:
                table[tuple(sorted(variant))] = signed
            for variant in (words + ("unsigned",), words + ("int", "unsigned")):
                table[tuple(sorted(variant))] = unsigned
        table[("signed",)] = table[("int",)]
        table[("unsigned",)] = table[("int", "unsigned")]
        if self.language == "cpp":
            table[("bool",)] = CType("bool", 8, False, 0, "bool")
            table[("wchar_t",)] = self.wchar()
        if self.name.startswith("msvc"):
            for word, base in (("__int8", ("char",)), ("__int16", ("short",)), ("__int32", ("int",)),
                               ("__int64", ("long", "long"))):
                table[(word,)] = table[tuple(sorted(base))]
                table[tuple(sorted((word, "signed")))] = table[tuple(sorted(base))]
                table[tuple(sorted((word, "unsigned")))] = table[tuple(sorted(base + ("unsigned",)))]
        return table


# Only what the compiler defines whatever the flags; flag-dependent ones such as _MT belong to the target
# configuration. cevaltests.py checks each value against the probe fixtures.
MSVC_PREDEFINES = {"_MSC_VER": "1600", "_MSC_FULL_VER": "160040219", "_MSC_BUILD": "1", "_M_IX86": "600",
                   "_WIN32": "1", "_INTEGRAL_MAX_BITS": "64", "_MSC_EXTENSIONS": "1"}
MSVC_WORDS = ("__cdecl", "__stdcall", "__fastcall", "__thiscall", "_cdecl", "_stdcall", "__inline", "__forceinline",
              "__restrict", "__ptr32", "__ptr64", "__unaligned", "__w64", "WINAPI", "APIENTRY", "CALLBACK",
              "WINAPIV", "NTAPI", "__RPC_FAR", "__RPC_API", "__RPC_USER", "__CRTDECL", "__CLRCALL_OR_CDECL",
              "_CRTIMP", "_CRTIMP2", "_CRTNOALIAS", "_CRTRESTRICT", "WINBASEAPI", "WINUSERAPI", "WINGDIAPI",
              "WINADVAPI", "NTSYSAPI", "DECLSPEC_IMPORT", "DECLSPEC_NORETURN", "FORCEINLINE", "__checkReturn",
              "__declspec", "_declspec", "__pragma", "DECLSPEC_ALIGN", "_CRT_INSECURE_DEPRECATE",
              "_CRT_DEPRECATE_TEXT", "__in", "__out", "__inout", "__deref", "__reserved", "__nullterminated",
              "__success", "__opt", "__callback", "__nullnullterminated", "__possibly_notnullterminated",
              "__exceptthat", "__maybenull", "__notnull", "__readonly", "__valid", "__format_string", "__typefix",
              "__override", "__range", "__control_entrypoint", "__data_entrypoint", "__gdi_entry", "__allocator")
SAL_PREFIXES = ("_In_", "_Out_", "_Inout_", "_Deref_", "_Pre_", "_Post_", "_Ret_", "_Check_return_", "_Printf_format",
                "_Reserved_", "_Field_", "_Struct_", "_When_", "_Success_", "_Null_", "_Notnull_", "_Maybenull_",
                "_Outptr_", "_Frees_", "_Use_decl_", "_Always_", "_Analysis_", "_Must_inspect_", "_Translates_",
                "__in_", "__out_", "__inout_", "__deref_", "__drv_", "__bcount", "__ecount", "__field_", "__struct_")
VC10_PROVENANCE = ("probe: VC10 SP1 cl.exe, C and C++ mode; fixtures in tools/evidence/probe/vc10-*.json "
                   "(values checked by cevaltests.py)")


def _vc10(language: str) -> Profile:
    predefines = dict(MSVC_PREDEFINES)
    if language == "cpp":
        predefines["__cplusplus"] = "199711L"
    return Profile(name=f"msvc-vc10-x86-{language}", version=1, language=language, provenance=VC10_PROVENANCE,
                   char_signed=True, short_bits=16, int_bits=32, long_bits=32, long_long_bits=64, pointer_bits=32,
                   wchar_bits=16, long_double_bits=64, size_type="unsigned int",
                   decimal_types=("int", "long", "unsigned long"),
                   extra_suffixes=("ll", "ull", "llu", "i64", "ui64"),
                   wide_types=("long long", "unsigned long long"), signed_overflow=WRAP, narrowing=WRAP,
                   signed_right_shift=ARITHMETIC, multichar=BIG_ENDIAN, pp_bits=64, predefines=predefines,
                   ignored_words=MSVC_WORDS, ignored_prefixes=SAL_PREFIXES)


SHC = Profile(name="shc-c", version=1, language="c",
              provenance="unchecked: not probed and not yet checked against the SHC manual",
              char_signed=True, short_bits=16, int_bits=32, long_bits=32, long_long_bits=64, pointer_bits=32,
              wchar_bits=16, long_double_bits=64, size_type="unsigned int",
              decimal_types=("int", "long", "unsigned long"), extra_suffixes=(), wide_types=(),
              signed_overflow=UNSUPPORTED,
              narrowing=UNSUPPORTED, signed_right_shift=UNSUPPORTED, multichar=UNSUPPORTED, pp_bits=32,
              predefines={"__SHC__": "1"})

PROFILES = {profile.name: profile for profile in (_vc10("cpp"), _vc10("c"), SHC)}


def get(name: str) -> Profile:
    if name not in PROFILES:
        raise SystemExit(f"unknown compiler profile {name!r}; known: {', '.join(sorted(PROFILES))}")
    return PROFILES[name]
