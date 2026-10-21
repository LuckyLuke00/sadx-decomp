"""Tests of the repairs in tools/llm.py that build a try again: the Bench and its Repairs record.

The Bench gets a fake rebuild: the build of a code is the (percent, output) of the first rule whose text the code
holds, else a failed build with no output. run() returns the failures as "<method> gives <found> for <case>, not
<wanted>".
"""

import tempfile
from pathlib import Path

import llm
import names

ADDRESS = 0x00401000
PATH = Path("src/foo.c")
SIGNATURE = "void Run(void)"
OTHER = "src/foo.c(4) : error C2065: 'x' : undeclared identifier"  # an error that no repair reads
MEMSET = 'extern "C" void *memset(void *dst, int value, unsigned int size);'
CLASH = ("decls: FUN_00402000: the tree declares it `void __fastcall FUN_00402000(void **param_1)`, a file here "
         "declares it `void FUN_00402000(void **)`. Remove that declaration: a second signature is a C++ overload "
         "that never links.")


def fake_bench(rules, tree_wins=False, earlier=None, tables=None):
    """(a Bench whose rebuild follows RULES, the list of the codes that it built)."""
    built = []

    def rebuild(decls, func):
        code = "\n".join(decls + func)
        built.append(code)
        return code, *next(((percent, output) for text, percent, output in rules if text in code), (None, ""))

    config = {"tables": tables, "context": None}
    types = names.Types(Path("no types.h"))
    return llm.Bench(rebuild, config, PATH, ADDRESS, set(), tree_wins, types, earlier or {}), built


def failed(body, output, decls=(), signature=SIGNATURE):
    """The first build of a try with DECLS and a function of BODY, which failed with OUTPUT."""
    func = [llm.function_line(ADDRESS), signature, "{", *body, "}"]
    return llm.Build(list(decls), func, "\n".join([*decls, *func]), None, output)


def line_of(build, text):
    """The line number of the line TEXT in the source of BUILD, as the compiler prints it."""
    return build.source.split("\n").index(text) + 1


def judged(method, case, found, built, wanted):
    """The failures of a repair that gave FOUND after the builds in BUILT, against WANTED: (the code that it goes on
    with, the change, the number of builds)."""
    build, change = found
    code = "\n".join(build.decls + build.func)
    if (code, change, len(built)) == wanted:
        return []
    return [f"{method} gives {change!r} and {len(built)} builds for {case}, not {wanted[1]!r} and {wanted[2]}"
            + ("" if code == wanted[0] else f", and goes on with {code!r}, not {wanted[0]!r}")]


def code_of(build, old=None, new=None):
    """The code of BUILD as text, with the line OLD written as NEW."""
    return "\n".join(new if line == old else line for line in build.decls + build.func)


def check_guard() -> list[str]:
    """A try that builds gets no repair: each method gives the build back with an empty change and builds nothing,
    although its output asks for every repair. The same try with no score makes each method build."""
    body = ["\ty = sqrtf(x);", "\tmemset(p, 0, 4);", "\tFUN_00402000(1, 2);", "\tx = DAT_00501000[1];", "\tFoo();",
            "\tg = tp + 4;", "\tp = q;"]
    start = failed(body, "", ["void FUN_00402000(void **param_1);"], "static void Run(struct Foo *tp)")
    errors = ["error C3861: 'sqrtf': identifier not found", "error C3861: 'memset': identifier not found",
              "error C2660: 'FUN_00402000' : function does not take 2 arguments", None,
              "error C3861: 'Foo': identifier not found", "error C2036: 'struct Foo *' : unknown size",
              "error C2440: '=' : cannot convert from 'int *' to 'char *'"]
    output = [f"src/foo.c({line_of(start, line)}) : {error}" for line, error in zip(body, errors) if error]
    start = start._replace(output="\n".join(output + [CLASH, f"{llm.NOT_BUILT}: Run"]))
    model = ["void FUN_00402000(int a, int b);", "extern int DAT_00501000[4];"]
    dropped = {"FUN_00402000": ["void FUN_00402000(void)"], "DAT_00501000": ["int DAT_00501000"]}
    methods = [("repair_names", [""]), ("repair_clashes", []), ("repair_calls", [model, dropped]),
               ("repair_globals", [model, dropped]), ("repair_runtime", []), ("repair_earlier", []),
               ("repair_offsets", []), ("repair_pointers", []), ("repair_static", [])]
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        (Path(folder) / "functions.tsv").write_text("address\tname\n0x00401000\tRun\n", encoding="utf-8")
        for method, extra in methods:
            for percent in (None, 90.0):
                bench, built = fake_bench([], True, {"Foo": "int Foo(void);"}, folder)
                attempt = start._replace(percent=percent)
                build, change = getattr(bench, method)(attempt, *extra)
                if percent is None and not built:
                    failures.append(f"{method} builds nothing for a try with no score")
                elif percent is not None and (build != attempt or change or built):
                    failures.append(f"{method} gives {change!r} and {len(built)} builds for a try that builds")
    return failures


def check_repair_names() -> list[str]:
    """A flagged name that the runtime writes another way gets that way. The retry is kept when its output no longer
    names the old name, also when it still fails. No rename, no build."""
    start = failed(["\ty = sqrtf(x);"], "src/foo.c(4) : error C3861: 'sqrtf': identifier not found")
    renamed = code_of(start, "\ty = sqrtf(x);", "\ty = sqrt(x);")
    cases = [("a rename that clears the old name", start, [("sqrt(x)", None, OTHER)],
              (renamed, {"sqrtf": "sqrt"}, 1)),
             ("a rename that builds", start, [("sqrt(x)", 100.0, "")], (renamed, {"sqrtf": "sqrt"}, 1)),
             ("a retry that still names the old name", start,
              [("sqrt(x)", None, "src/foo.c(4) : error C2065: 'sqrtf' : undeclared identifier")],
              (code_of(start), {}, 1)),
             ("no name to change", start._replace(output=OTHER), [], (code_of(start), {}, 0))]
    failures = []
    for case, build, rules, wanted in cases:
        bench, built = fake_bench(rules)
        failures += judged("repair_names", case, bench.repair_names(build, ""), built, wanted)
    return failures


def check_repair_clashes() -> list[str]:
    """With tree_wins, a declaration that clashes with the tree goes. The names whose clash line is gone from the
    retry count as dropped, with the tree's ways. When every clash stays, the first build stands. Without tree_wins
    or a clash line, nothing is built."""
    decls = ["void FUN_00402000(void **param_1);", "extern int DAT_00501000;"]
    start = failed(["\tFUN_00402000(0);"], CLASH, decls)
    trimmed = "\n".join(decls[1:] + start.func)
    ways = {"FUN_00402000": ["void __fastcall FUN_00402000(void **param_1)"]}
    cases = [("a clash that the retry clears", start, True, [("", None, OTHER)], (trimmed, ways, 1)),
             ("a clash that stays", start, True, [("", None, CLASH)], (code_of(start), {}, 1)),
             ("no tree_wins", start, False, [], (code_of(start), {}, 0)),
             ("no clash line", start._replace(output=OTHER), True, [], (code_of(start), {}, 0))]
    failures = []
    for case, build, tree_wins, rules, wanted in cases:
        bench, built = fake_bench(rules, tree_wins)
        failures += judged("repair_clashes", case, bench.repair_clashes(build), built, wanted)
    return failures


def check_repair_calls() -> list[str]:
    """A call that the tree's declaration of a dropped callee rejects goes through a cast to the model's type. The
    retry is kept when that clash is gone, even when another error remains. A clash on a name that was not dropped
    builds nothing."""
    model = ["void FUN_00402000(int a, int b);"]
    rejected = "src/foo.c(4) : error C2660: 'FUN_00402000' : function does not take 2 arguments"
    start = failed(["\tFUN_00402000(1, 2);"], rejected)
    cast = code_of(start, "\tFUN_00402000(1, 2);", "\t((void (*)(int, int))FUN_00402000)(1, 2);")
    dropped = {"FUN_00402000": ["void FUN_00402000(void)"]}
    cases = [("a clash that the cast clears", dropped, [("(void (*)", None, OTHER)],
              (cast, ["FUN_00402000"], 1)),
             ("a clash that stays", dropped, [("(void (*)", None, rejected)], (code_of(start), [], 1)),
             ("a callee that was not dropped", {"FUN_00403000": ["void FUN_00403000(void)"]}, [],
              (code_of(start), [], 0))]
    failures = []
    for case, gone, rules, wanted in cases:
        bench, built = fake_bench(rules)
        failures += judged("repair_calls", case, bench.repair_calls(start, model, gone), built, wanted)
    return failures


def check_repair_globals() -> list[str]:
    """A use of a dropped variable goes through a cast to the model's type. The retry is kept when it builds or has
    fewer errors. No dropped name, no build."""
    model = ["extern int DAT_00501000[4];"]
    two = OTHER + "\nsrc/foo.c(5) : error C2109: subscript requires array or pointer type"
    start = failed(["\tx = DAT_00501000[1];"], two)
    cast = code_of(start, "\tx = DAT_00501000[1];", "\tx = (*(int (*)[4])&DAT_00501000)[1];")
    dropped = {"DAT_00501000": ["int DAT_00501000"]}
    cases = [("a retry that builds", dropped, [("(int (*)[4])", 99.0, "")], (cast, ["DAT_00501000"], 1)),
             ("a retry with fewer errors", dropped, [("(int (*)[4])", None, OTHER)],
              (cast, ["DAT_00501000"], 1)),
             ("a retry with as many errors", dropped, [("(int (*)[4])", None, two)], (code_of(start), [], 1)),
             ("no dropped name", {}, [], (code_of(start), [], 0))]
    failures = []
    for case, gone, rules, wanted in cases:
        bench, built = fake_bench(rules)
        failures += judged("repair_globals", case, bench.repair_globals(start, model, gone), built, wanted)
    return failures


def check_repair_runtime_and_earlier() -> list[str]:
    """A runtime function that the code calls undeclared gets its declaration, and a name that an earlier try
    declared gets that try's line. Each retry is kept when the name is no longer missing."""
    undeclared = "src/foo.c(4) : error C3861: '{}': identifier not found"
    start = failed(["\tmemset(p, 0, 4); Foo();"], undeclared.format("memset"))
    earlier = start._replace(output=undeclared.format("Foo"))
    line = "int Foo(void);"
    cases = [("repair_runtime", "a declaration that clears the error", start, [(MEMSET, None, OTHER)],
              (MEMSET + "\n" + code_of(start), [MEMSET], 1)),
             ("repair_runtime", "a name that stays missing", start, [(MEMSET, None, start.output)],
              (code_of(start), [], 1)),
             ("repair_earlier", "a line that clears the error", earlier, [(line, None, OTHER)],
              (line + "\n" + code_of(start), [line], 1)),
             ("repair_earlier", "a name that stays missing", earlier, [(line, None, earlier.output)],
              (code_of(start), [], 1)),
             ("repair_earlier", "a name that no earlier try declared", earlier._replace(output=OTHER), [],
              (code_of(start), [], 0))]
    failures = []
    for method, case, build, rules, wanted in cases:
        bench, built = fake_bench(rules, earlier={"Foo": line})
        failures += judged(method, case, getattr(bench, method)(build), built, wanted)
    return failures


def check_repair_offsets() -> list[str]:
    """A sum on a pointer to a type of unknown size gets `(char *)` and a cast back. The retry is kept when it has
    fewer of those errors and no new error code, even when another error remains."""
    sum = "\tg = tp + 4;"
    start = failed([sum], "", signature="void Run(struct Foo *tp)")
    unknown = f"src/foo.c({line_of(start, sum)}) : error C2036: 'struct Foo *' : unknown size"
    start = start._replace(output=unknown + "\n" + OTHER)
    bytes = "g = (struct Foo *)((char *)tp + 4);"
    sized = code_of(start, sum, "\t" + bytes)
    syntax = "src/foo.c(4) : error C2143: syntax error : missing ';'"
    cases = [("a retry with fewer of those errors", [("(char *)tp", None, OTHER)],
              (sized, [bytes], 1)),
             ("a retry with as many", [("(char *)tp", None, start.output)], (code_of(start), [], 1)),
             ("a retry with a new error code", [("(char *)tp", None, syntax)], (code_of(start), [], 1))]
    failures = []
    for case, rules, wanted in cases:
        bench, built = fake_bench(rules)
        failures += judged("repair_offsets", case, bench.repair_offsets(start), built, wanted)
    return failures


def check_repair_pointers() -> list[str]:
    """A pointer conversion that the compiler refuses gets a cast, and the change lists each line before and after.
    When no round keeps a cast, the first build stands."""
    assignment = "\tp = q;"
    start = failed([assignment], "")
    refused = f"src/foo.c({line_of(start, assignment)}) : error C2440: '=' : cannot convert from 'int *' to 'char *'"
    start = start._replace(output=refused)
    cast = code_of(start, assignment, "\tp = (char *)q;")
    cases = [("a cast that builds", [("(char *)q", 100.0, "")],
              (cast, [{"before": "p = q;", "after": "p = (char *)q;"}], 1)),
             ("a cast that does not help", [("(char *)q", None, refused)], (code_of(start), [], 1))]
    failures = []
    for case, rules, wanted in cases:
        bench, built = fake_bench(rules)
        failures += judged("repair_pointers", case, bench.repair_pointers(start), built, wanted)
    return failures


def check_repair_static() -> list[str]:
    """When the build holds no code for a static function, `static` goes. The retry is kept when it builds. A name
    that the tables give several functions keeps its `static`, and so does one without tables."""
    start = failed(["\tx = 1;"], f"{llm.NOT_BUILT}: Run", signature="static " + SIGNATURE)
    plain = code_of(start, "static " + SIGNATURE, SIGNATURE)
    cases = [("a retry that builds", "Run", [("\n" + SIGNATURE, 80.0, "")], (plain, True, 1)),
             ("a retry that still fails", "Run", [("\n" + SIGNATURE, None, start.output)],
              (code_of(start), False, 1)),
             ("a name that several functions have", "Run\n0x00403000\tRun", [], (code_of(start), False, 0)),
             ("no tables", None, [], (code_of(start), False, 0))]
    failures = []
    for case, rows, rules, wanted in cases:
        with tempfile.TemporaryDirectory() as folder:
            (Path(folder) / "functions.tsv").write_text(f"address\tname\n0x00401000\t{rows}\n", encoding="utf-8")
            bench, built = fake_bench(rules, tables=folder if rows else None)
            failures += judged("repair_static", case, bench.repair_static(start), built, wanted)
    return failures


def check_repair() -> list[str]:
    """repair runs the repairs in turn on what the one before kept, and gives (the model's code with its names
    fixed, that code without the tree's clashes, the last build, the Repairs)."""
    output = "\n".join(["src/foo.c(4) : error C3861: 'sqrtf': identifier not found",
                        "src/foo.c(4) : error C3861: 'memset': identifier not found"])
    start = failed(["\ty = sqrtf(x); memset(p, 0, 4);"], output)
    bench, built = fake_bench([(MEMSET, 100.0, ""), ("sqrt(x)", None, output.split("\n")[1])])
    model, trimmed, build, repairs = bench.repair(start, "")
    renamed = code_of(start, "\ty = sqrtf(x); memset(p, 0, 4);", "\ty = sqrt(x); memset(p, 0, 4);")
    found = (code_of(model), code_of(trimmed), code_of(build), build.percent, repairs.logged(), len(built))
    logged = {"runtime": [MEMSET], "renamed": {"sqrtf": "sqrt"}}
    wanted = (renamed, renamed, MEMSET + "\n" + renamed, 100.0, logged, 2)
    return [] if found == wanted else [f"repair gives {found}, not {wanted}"]


def check_repairs_text() -> list[str]:
    """No repair gives no note, no console text and no transcript keys, and the latest line is the outcome alone.
    Each repair puts its words in front of the outcome: the dropped declarations first, the pointer casts last."""
    empty = llm.Repairs()
    failures = []
    if (empty.note(), empty.trim(), empty.logged(), empty.latest("scored 9%")) != ("", "", {}, "scored 9%"):
        failures.append("an empty Repairs gives text")
    every = llm.Repairs()
    every.renamed, every.dropped, every.casts, every.gcasts = {"a": "b"}, {"F": ["int F"]}, ["G"], ["H"]
    every.runtime, every.carried, every.offsets = ["int r;"], ["int c;"], ["x = (char *)p + 1;"]
    every.pointer_casts, every.unstatic = [{"before": "p = q;", "after": "p = (char *)q;"}], True
    latest = every.latest("scored 9%")
    if not latest.startswith("was built without your declaration of F (the tree declares it as `int F`) and was "
                             "built with casts on the calls to G and ") or not latest.endswith(
            "was built with casts on the pointer conversions and scored 9%"):
        failures.append(f"the latest line with every repair is {latest!r}")
    keys = ["dropped", "unstatic", "casts", "pointer_casts", "gcasts", "runtime", "carried", "renamed", "bytes"]
    if list(every.logged()) != keys:
        failures.append(f"the transcript keys with every repair are {list(every.logged())}, not {keys}")
    return failures


def run() -> list[str]:
    """Every check of this module, in order."""
    failures = []
    for check in (check_guard, check_repair_names, check_repair_clashes, check_repair_calls, check_repair_globals,
                  check_repair_runtime_and_earlier, check_repair_offsets, check_repair_pointers, check_repair_static,
                  check_repair, check_repairs_text):
        failures += check()
    return failures
