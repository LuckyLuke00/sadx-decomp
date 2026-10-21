"""The self-test of check.py: prove the toolchain and reccmp on the known program in tests/selftest.

run() builds nothing: CMake already built the original and our twin. It checks the
original's hash, the scores reccmp gives, the regression gate, the register-argument
search and the totals against what tests/selftest pins. It also checks the history
rules of progress.py on changed copies of the pinned scores, its git reader on a
throwaway repository, and where the annotation lint lets a function annotation sit.
"""

import contextlib
import copy
import io
import json
import re
import tempfile
from pathlib import Path

import declgen
import names
import osutil
import pe
import progress
import project
import runner
import scoring

ROOT = project.ROOT
BUILD = project.BUILD
# The self-test is its own reccmp project, so reccmp-project.yml holds only the game.
SELFTEST = ROOT / "tests" / "selftest"
SELFTEST_EXPECTED = SELFTEST / "expected.json"
SELFTEST_ORIGINAL = BUILD / "selftest-original" / "SELFTEST.exe"
SELFTEST_MAP = SELFTEST_ORIGINAL.with_suffix(".map")
SELFTEST_OURS = BUILD / "SELFTEST.exe"
SELFTEST_BUILD = BUILD / "selftest-reccmp"  # reccmp runs here for the self-test


def run() -> int:
    """Prove the toolchain and reccmp on the known program in tests/selftest."""
    expected = json.loads(SELFTEST_EXPECTED.read_text(encoding="utf-8"))
    original_hash, failures = check_original_hash()
    spans = map_functions(SELFTEST_MAP)
    current = score_selftest(spans)
    failures += check_scores(expected, current)
    failures += check_regression_gate(expected, current)
    failures += check_register_arguments(current, spans)
    failures += check_totals(expected, current)
    failures += check_whole_percent()
    failures += check_moved_scores(expected)
    failures += check_history_rows(expected)
    failures += check_empty_map()
    failures += check_block_names()
    failures += check_gem_colors()
    failures += check_read_blobs()
    failures += check_misplaced_annotations()
    failures += check_local_declarations()
    failures += check_tree_conflicts()
    failures += check_declaration_keys()
    failures += check_decls_trees()
    failures += check_nested_globals()

    if failures:
        print("FAIL self-test")
        for line in failures:
            print(f"     {line}")
        return 1
    print(f"ok   self-test: build hash {original_hash[:12]}..., exact scores, regression gate, /GL call, totals, history, "
          "annotation lint")
    return 0


def check_original_hash() -> tuple[str, list[str]]:
    """The toolchain is deterministic and identical to the one that pinned the hash."""
    project_yml = SELFTEST / "reccmp-project.yml"
    pinned = project.read_yml(project_yml)["targets"]["SELFTEST"]["hash"]["sha256"]
    original_hash = osutil.sha256(SELFTEST_ORIGINAL)
    if original_hash == pinned:
        return original_hash, []
    return original_hash, [f"original build hash {original_hash} != {pinned} in "
                           f"{project_yml.relative_to(ROOT).as_posix()}: the compiler, libraries or flags differ"]


def score_selftest(spans: list[tuple[int, int]]) -> dict:
    """Score the self-test with reccmp, with its function sizes and the constants of an original
    that has no relocations."""
    import constants

    build = runner.Build("SELFTEST", SELFTEST, SELFTEST_OURS, SELFTEST_BUILD)
    runner.write_user_yml(SELFTEST / "reccmp-user.yml", "SELFTEST", SELFTEST_ORIGINAL)
    runner.write_build_yml(build)
    # SELFTEST_FLAGS in CMakeLists.txt have /O2, which pools strings.
    runner.write_constants_csv(SELFTEST_BUILD / "constants.csv", SELFTEST_ORIGINAL,
                               [constants.Function(address, size, True) for address, size in spans])
    runner.write_sizes_csv(SELFTEST_BUILD / "sizes.csv", spans)
    return runner.summarize("SELFTEST", runner.score_target(build, SELFTEST_ORIGINAL))


def check_scores(expected: dict, current: dict) -> list[str]:
    """reccmp scores every outcome exactly as pinned: match, near miss, stub, /GL, and the
    constants of an original without relocations."""
    if current["functions"] == expected["functions"]:
        return []
    return ["scores differ from expected.json:\n"
            f"    expected {json.dumps(expected['functions'])}\n"
            f"    actual   {json.dumps(current['functions'])}"]


def check_regression_gate(expected: dict, current: dict) -> list[str]:
    """The regression gate passes on the pinned baseline and a removed stub, and fires on a drop."""
    failures = []
    false_alarms = scoring.find_regressions(expected, current)
    if false_alarms:
        failures.append(f"gate flagged a regression on identical scores: {false_alarms}")
    if len(scoring.find_regressions(current, with_first_accuracy(current, 0.5))) != 1:
        failures.append("gate missed a deliberate score drop")
    if scoring.find_regressions(current, without_stubs(current)):
        failures.append("gate flagged a removed stub, which scores zero")
    return failures


def check_moved_scores(expected: dict) -> list[str]:
    """A stub added or removed moves no score. A new accuracy moves one, and so does a removed
    match: a missing function scores zero."""
    unstubbed = without_stubs(expected)
    unmatched = dict(expected, functions=expected["functions"][1:])
    first = [int(expected["functions"][0]["address"], 16)]
    cases = [("a removed stub", expected, unstubbed, []),
             ("an added stub", unstubbed, expected, []),
             ("a new accuracy", expected, with_first_accuracy(expected, 0.5), first),
             ("a removed match", expected, unmatched, first)]
    failures = []
    for name, baseline, current, wanted in cases:
        moved = scoring.moved_scores(baseline, current)
        if moved != wanted:
            failures.append(f"moved_scores gives {moved} for {name}, not {wanted}")
    return failures


def check_history_rows(expected: dict) -> list[str]:
    """The history gets a row for the first commit and for each commit that changed the totals, two commits of one
    day included, and none for a commit that only removes or adds a stub. A commit that undoes the one before gets
    a row too. The working tree gets a row only when it changed the totals."""
    game = {int(entry["address"], 16) for entry in expected["functions"]}
    dropped = with_first_accuracy(expected, 0.5)
    later = with_first_accuracy(expected, 0.25)
    commits = [progress.Snapshot("2026-01-01", expected, game),
               progress.Snapshot("2026-01-02", without_stubs(expected), game),
               progress.Snapshot("2026-01-03", expected, game),
               progress.Snapshot("2026-01-04", dropped, game),
               progress.Snapshot("2026-01-04", later, game)]
    rows_of_commits = [("2026-01-01", expected), ("2026-01-04", dropped), ("2026-01-04", later)]
    # (case, the snapshots after the commits, the day and scores of each row)
    cases = [("an unchanged working tree", [("2026-01-05", later)], rows_of_commits),
             ("a working tree that changed the totals", [("2026-01-05", expected)],
              rows_of_commits + [("2026-01-05", expected)]),
             ("a commit that undoes the one before", [("2026-01-05", dropped), ("2026-01-05", later)],
              rows_of_commits + [("2026-01-05", dropped), ("2026-01-05", later)])]
    failures = []
    for name, more, wanted in cases:
        snapshots = commits + [progress.Snapshot(day, summary, game) for day, summary in more]
        rows = progress.history_rows(snapshots)
        if rows != [progress.history_row(day, scoring.totals(summary, game)) for day, summary in wanted]:
            failures.append(f"history rows {[row['date'] for row in rows]} for {name}, not the "
                            f"{len(wanted)} rows of {[day for day, _ in wanted]}")
    return failures


def check_empty_map() -> list[str]:
    """A game with no game functions yet, such as a new port, gets a map of just its header and colour key."""
    summary = {"exe": "GAME.EXE", "functions": []}
    sections = progress.map_sections({}, [("Stages", None, {"stage": "Stages"})])
    svg = progress.render_map(summary, scoring.totals(summary, set()), sections, progress.LIGHT)
    height = progress.HEADER + progress.FOOTER
    if f'viewBox="0 0 {progress.WIDTH} {height}"' in svg:
        return []
    return [f"the map of a game with no game functions is not {height} px high"]


def check_block_names() -> list[str]:
    """A block shows its name unless its section has only one area in the map list, whose title names it. A section
    of two areas names its block also when only one of them has functions."""
    sections = [("Two areas", None, {"a": "Area A", "b": "Area B"}), ("One area", None, {"c": "Area C"})]
    found = progress.map_sections({0x401000: "a", 0x402000: "c"}, sections)
    labelled = [(block.name, block.labelled) for section in found for block in section.blocks]
    wanted = [("Area A", True), ("Area C", False)]
    return [] if labelled == wanted else [f"map blocks (name, labelled) {labelled}, not {wanted}"]


def check_gem_colors() -> list[str]:
    """A section's gem colour in data/areas.yml is a quoted #rrggbb string. Unquoted, the # starts a YAML comment, so
    the colour reads as null, and a number is no colour either: the map stops on both."""
    import areas  # here, not at the top: it needs .venv's packages, and check.py imports this module before .venv

    cases = [('"#2f6bff"', []), ("#2f6bff", ["Stages"]), ("123456", ["Stages"])]
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder) / "areas.yml"
        for color, wanted in cases:
            path.write_text(f"map:\n- section: Stages\n  color: {color}\n  areas: {{stage: Stages}}\n",
                            encoding="utf-8")
            found = areas.miscolored(project.read_yml(path))
            if found != wanted:
                failures.append(f"miscolored gives {found} for `color: {color}`, not {wanted}")
    return failures


def check_read_blobs() -> list[str]:
    """read_blobs gives the text of each spec from git's batch output, also when two specs share one blob."""
    files = {"a.txt": "same text\n", "b.txt": "same text\n", "c.txt": "other\ntext\n"}
    with tempfile.TemporaryDirectory() as folder:
        root = Path(folder)
        osutil.git(root, "init", "--quiet")
        for name, text in files.items():
            (root / name).write_text(text, encoding="utf-8", newline="\n")
        osutil.git(root, "add", *files)
        # A tree needs no commit, so no user name, hooks or signing.
        tree = osutil.git(root, "write-tree").decode().strip()
        texts = progress.read_blobs(root, [f"{tree}:{name}" for name in files])
    wanted = {f"{tree}:{name}": text for name, text in files.items()}
    if texts == wanted:
        return []
    return [f"read_blobs gave {texts}, not {wanted}"]


def check_misplaced_annotations() -> list[str]:
    """A STUB may start any function, such as a library function that game code calls. Any other function annotation
    must start a game function."""
    game, library = 0x401000, 0x402000
    annotations = [(game, "FUNCTION at a game function", False), (library, "STUB at a library function", True),
                   (library, "FUNCTION at a library function", False), (library + 1, "STUB inside a function", True)]
    found = [where for _, where, _ in runner.misplaced(annotations, {game, library}, {game})]
    expected = ["FUNCTION at a library function", "STUB inside a function"]
    return [] if found == expected else [f"annotation lint flags {found}, not {expected}"]


def check_local_declarations() -> list[str]:
    """A label at column 0 is no declaration, also when a call follows it. A return type on its own line is one."""
    text = "end:\n\tFoo();\nlocal_20:\n\tFUN_004afe30();\nint Bar(int a);\nint\nBaz(int);\n"
    found = [name for name, _ in names.local_declarations(text)[0]]
    wanted = ["Bar", "Baz"]
    return [] if found == wanted else [f"local_declarations finds {found}, not {wanted}"]


def check_tree_conflicts() -> list[str]:
    """Each kind of clash line drops the model's own declaration of that name, and only that one. A declaration over
    two lines stays: dropping one of its lines would break the file. A global inside another global stays too:
    without the declaration, the code that uses the name has no type for it."""
    import llm  # here, not at the top: it needs .venv's packages, and check.py imports this module before .venv
    decls = ["extern int DAT_05baf368; // eight slots", "extern int DAT_05cda1b0[1];",
             "void FUN_004b66c0(void **param_1);", "extern short DAT_05b42998;", "extern unsigned char DAT_05b3e04c;",
             "void FUN_004f8070(void *param_1,", "    int param_2);"]
    lines = ["decls: DAT_05baf368: sources declare it in 2 ways: int DAT_05baf368 | short *DAT_05baf368",
             "decls: DAT_05cda1b0: src/CameraStageTable.c declares it `unsigned long DAT_05cda1b0` in the context "
             "tree. Declare it that way too.",
             "decls: FUN_004b66c0: the tree declares it `void __fastcall FUN_004b66c0(void **param_1)`, a file here "
             "declares it `void FUN_004b66c0(void **)`. Remove that declaration: a second signature is a C++ overload "
             "that never links.",
             "decls: FUN_004f8070: the tree declares it `void FUN_004f8070(void *param_1)`, a file here declares it "
             "`void FUN_004f8070(void *, int)`. Remove that declaration: a second signature is a C++ overload that "
             "never links.",
             "decls: DAT_05b932f0: sources declare it in 2 ways: char DAT_05b932f0[1024] | long DAT_05b932f0[16]",
             "decls: DAT_05b3e04c: inside DAT_05b3e040 (struct NJS_ARGB) at +12. Remove that declaration and reach it "
             "through DAT_05b3e040."]
    wanted = (["extern short DAT_05b42998;", "extern unsigned char DAT_05b3e04c;", "void FUN_004f8070(void *param_1,",
               "    int param_2);"],
              {"DAT_05baf368": ["short *DAT_05baf368"], "DAT_05cda1b0": ["unsigned long DAT_05cda1b0"],
               "FUN_004b66c0": ["void __fastcall FUN_004b66c0(void **param_1)"]})
    found = llm.tree_conflicts(decls, lines)
    return [] if found == wanted else [f"tree_conflicts gives {found}, not {wanted}"]


def check_declaration_keys() -> list[str]:
    """Two declarations of one function read the same in C++ with or without `extern`, `struct` before a type name,
    parameter names, and `void` for no parameters. A different parameter type is a different function."""
    cases = [("void Foo()", "extern void Foo(void)", True),
             ("void Foo(struct NJS_ARGB *)", "void Foo(NJS_ARGB *argb)", True),
             ("void Foo(void (*)())", "void Foo(void (*func)(void))", True),
             ("void Foo(NJS_ARGB *)", "void Foo(int *)", False),
             ("void Foo(int)", "void Foo(void)", False),
             ("void Foo(void *)", "void Foo()", False)]
    return [f"declaration_key reads `{a}` and `{b}` {'different' if same else 'the same'}"
            for a, b, same in cases if (names.declaration_key(a) == names.declaration_key(b)) != same]


def check_decls_trees() -> list[str]:
    """decls on throwaway trees. A static function here and a global one of the same name in the context share a
    name once the context holds both, also when no file here uses the context's. A global name that two objects
    share means the one in the object that the using file defines functions of, and a second file that uses the
    other one fails."""
    target = project.game_config().target
    exec_here = f"// FUNCTION: {target} 0x00401000\nstatic void Exec(struct task *tp)\n{{\n}}\n"
    exec_there = f"// FUNCTION: {target} 0x00402000\nvoid Exec(struct task *tp)\n{{\n}}\n"
    functions = [("0x00401000", "Exec", "L", "src/x.c", "o_x.obj"),
                 ("0x00402000", "Exec", "G", "src/emblem.c", "o_e.obj"),
                 ("0x00403000", "DispX", "L", "src/x.c", "o_x.obj"),
                 ("0x00404000", "DispY", "L", "src/y.c", "o_y.obj")]
    globals_ = [("0x00501000", "obj_c_info", "o_x.obj"), ("0x00502000", "obj_c_info", "o_y.obj")]

    def disp(address, name):
        return f"// FUNCTION: {target} {address}\nstatic void {name}(struct task *tp)\n{{\n\tobj_c_info[0] = 1;\n}}\n"

    # (case, files, the context's files, exit code, text of the output, addresses of the generated globals)
    cases = [("a static function against the context's global one", {"src/x.c": exec_here},
              {"src/emblem.c": exec_there}, 1, "share the name", []),
             ("a static function with no context", {"src/x.c": exec_here}, {}, 0, "", []),
             ("a global name that two objects share", {"src/x.c": disp("0x00403000", "DispX")}, {}, 0, "",
              ["0x00501000"]),
             ("a global name that two files use", {"src/x.c": disp("0x00403000", "DispX"),
                                                   "src/y.c": disp("0x00404000", "DispY")}, {}, 1,
              "0x00501000, 0x00502000 share the name", None)]
    failures = []
    for case, files, context_files, code, line, addresses in cases:
        found, output, generated = run_decls(files, context_files, functions, globals_)
        defined = re.findall(r"GLOBAL: \w+ (0x\w+)", generated.get(names.GLOBALS_CPP, ""))
        if found != code or line not in output or (addresses is not None and defined != addresses):
            failures.append(f"decls for {case} gives exit {found}, not {code}, globals {defined}, not {addresses}, "
                            f"and prints {output!r}, not {line!r}")
    return failures


def check_nested_globals() -> list[str]:
    """A global at an address inside another global's span splits it: decls fails on the new one, as the model's
    `extern unsigned char DAT_05b3e04c;` did inside `struct NJS_ARGB DAT_05b3e040`. A global behind the span is fine,
    and so is a pair that the context's last layout already had."""
    target = project.game_config().target
    argb = ("struct NJS_ARGB {\n    float a;\n    float r;\n    float g;\n    float b;\n};\n"
            'static_assert(sizeof(NJS_ARGB) == 0x10, "sizeof NJS_ARGB");\n')

    def fog(name):
        return {"src/fog.c": f"extern unsigned char {name};\nint Fog(void)\n{{\n\treturn {name};\n}}\n"}

    holder = {"src/rd.c": "extern struct NJS_ARGB DAT_05b3e040;\nvoid Rd(void)\n{\n\tDAT_05b3e040.a = 1;\n}\n"}
    layout = "".join(f"// GLOBAL: {target} {a}\n{decl};\n\n" for a, decl in
                     [("0x05b3e040", "struct NJS_ARGB DAT_05b3e040"), ("0x05b3e04c", "unsigned char DAT_05b3e04c")])
    # (case, own files, the context's files, exit code, text of the output)
    cases = [("a global inside a struct global", fog("DAT_05b3e04c"), holder, 1,
              "decls: DAT_05b3e04c: inside DAT_05b3e040 (struct NJS_ARGB) at +12."),
             ("a global behind a struct global", fog("DAT_05b3e050"), holder, 0, "decls: 0 functions"),
             ("a pair that the context's layout had", fog("DAT_05b3e04c"),
              holder | {"src/unplaced/globals.cpp": layout}, 0,
              "decls: DAT_05b3e040 (struct NJS_ARGB) holds 1 other globals, as in the last layout: DAT_05b3e04c at +12")]
    failures = []
    for case, files, context_files, code, line in cases:
        found, output, _ = run_decls(files, context_files, [], [], argb)
        if found != code or line not in output or (code == 0 and "inside" in output):
            failures.append(f"decls for {case} gives exit {found}, not {code}, and prints {output!r}, not {line!r}")
    return failures


def run_decls(files: dict, context_files: dict, functions: list, globals_: list,
              types: str = "") -> tuple[int, str, dict]:
    """(exit code, output, generated files) of decls in a throwaway tree of FILES, with a throwaway context tree and
    the given rows of the tables: functions (address, name, scope, file, object) and globals (address, name, object),
    and the TYPES header."""
    def tsv(header, rows):
        return "\n".join("\t".join(row) for row in [header, *rows]) + "\n"

    with tempfile.TemporaryDirectory() as folder:
        root, context, tables = (Path(folder) / name for name in ("tree", "context", "tables"))
        for tree, texts in ((root, files), (context, context_files)):
            for rel, text in texts.items():
                (tree / rel).parent.mkdir(parents=True, exist_ok=True)
                (tree / rel).write_text(text, encoding="utf-8")
        tables.mkdir()
        (tables / "functions.tsv").write_text(
            tsv(["address", "name", "proto", "scope", "file", "object"],
                [(a, n, f"void {n}(struct task *tp);", s, f, o) for a, n, s, f, o in functions]), encoding="utf-8")
        (tables / "globals.tsv").write_text(
            tsv(["address", "name", "decl", "base", "dims", "size", "object"],
                [(a, n, "int {}[?]", "int", "?", "8", o) for a, n, o in globals_]), encoding="utf-8")
        if types:
            (tables / "types.h").write_text(types, encoding="utf-8")
        saved, declgen.ROOT = declgen.ROOT, root
        output = io.StringIO()
        try:
            with contextlib.redirect_stdout(output):
                code = declgen.write(context if context_files else None, tables)
        finally:
            declgen.ROOT = saved
        generated = {rel: (root / rel).read_text(encoding="utf-8") for rel in names.GENERATED if (root / rel).exists()}
    return code, output.getvalue(), generated


def without_stubs(summary: dict) -> dict:
    return dict(summary, functions=[entry for entry in summary["functions"] if not entry["stub"]])


def with_first_accuracy(summary: dict, accuracy: float) -> dict:
    changed = copy.deepcopy(summary)
    changed["functions"][0]["accuracy"] = accuracy
    return changed


def check_register_arguments(current: dict, spans: list[tuple[int, int]]) -> list[str]:
    """The register-argument search of `check.py groups` finds the one call that /GL made, from Total to Mix."""
    import groups

    names = {entry["name"]: int(entry["address"], 16) for entry in current["functions"]}
    functions = groups.read_functions(pe.Image(SELFTEST_ORIGINAL), [(address, size, 0) for address, size in spans], {})
    sites = groups.register_argument_sites(functions, {})
    found = sorted((site.caller, site.callee) for site in sites)
    if found == [(names.get("Total"), names.get("Mix"))]:
        return []
    return [f"register-argument calls (caller, callee) {[(hex(a), hex(b)) for a, b in found]} "
            "are not the one from Total to Mix"]


def check_totals(expected: dict, current: dict) -> list[str]:
    """The totals leave a stub out of the decompiled count, and a library function out of the game total."""
    with_library = copy.deepcopy(current)
    with_library["functions"][0]["library"] = True
    totals = scoring.totals(with_library, {int(entry["address"], 16) for entry in current["functions"]})
    if totals._asdict() == expected["totals"]:
        return []
    return [f"totals {json.dumps(totals._asdict())} != {json.dumps(expected['totals'])} in expected.json"]


def check_whole_percent() -> list[str]:
    """A whole percent rounds down, so only a whole that is all done shows 100%. It counts in integers: 29 of 100 is
    29%, though 100 * 0.29 in floats is just under 29."""
    cases = [(0, 0, "0%"), (29, 100, "29%"), (199, 200, "99%"), (1, 1, "100%")]
    return [f"whole_percent({part}, {whole}) gives {scoring.whole_percent(part, whole)}, not {wanted}"
            for part, whole, wanted in cases if scoring.whole_percent(part, whole) != wanted]


def map_functions(path: Path) -> list[tuple[int, int]]:
    """(address, size) of each function from the self-test's own objects in a link map.
    Each runs to the next symbol in the code section."""
    symbols = []
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        parts = line.split()
        if len(parts) >= 4 and parts[0].startswith("0001:") and re.fullmatch(r"[0-9a-f]{8}", parts[2]):
            symbols.append((int(parts[2], 16), parts[-1]))
    symbols.sort()
    # A library member shows as library:object.
    return [(address, following - address) for (address, source), (following, _) in zip(symbols, symbols[1:])
            if ":" not in source]
