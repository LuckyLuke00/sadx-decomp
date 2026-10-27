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
import os
import re
import tempfile
from pathlib import Path

import coff
import declgen
import library
import link
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
SELFTEST_OBJECT = BUILD / "CMakeFiles" / "selftest_original.dir" / "tests" / "selftest" / "original.cpp.obj"
SELFTEST_LINK = BUILD / "selftest-link"  # check_link links here


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
    failures += check_trick_totals(current)
    failures += check_trick_state(current)
    failures += check_code_bytes(current)
    failures += check_summarize_tricks()
    failures += check_whole_percent()
    failures += check_recent_gain()
    failures += check_moved_scores(expected)
    failures += check_history_rows(expected)
    failures += check_empty_map()
    failures += check_block_names()
    failures += check_gem_colors()
    failures += check_read_blobs()
    failures += check_foreign_repository()
    failures += check_misplaced_annotations()
    failures += check_unclosed_definitions()
    failures += check_local_declarations()
    failures += check_tree_conflicts()
    failures += check_declaration_keys()
    failures += check_decls_trees()
    failures += check_static_users()
    failures += check_nested_globals()
    failures += check_decls_aliases()
    failures += check_extern_of()
    failures += check_reached_types()
    failures += check_clone()
    failures += check_link()
    failures += check_units()

    if failures:
        print("FAIL self-test")
        for line in failures:
            print(f"     {line}")
        return 1
    print(f"ok   self-test: build hash {original_hash[:12]}..., exact scores, regression gate, /GL call, totals, history, "
          "annotation lint, relink, unit tests")
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
    return runner.summarize("SELFTEST", runner.score_target(build, SELFTEST_ORIGINAL), set())


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
    game = addresses(expected)
    sizes = {address: 10 for address in game}
    dropped = with_first_accuracy(expected, 0.5)
    later = with_first_accuracy(expected, 0.25)
    commits = [progress.Snapshot("2026-01-01", expected, game, sizes),
               progress.Snapshot("2026-01-02", without_stubs(expected), game, sizes),
               progress.Snapshot("2026-01-03", expected, game, sizes),
               progress.Snapshot("2026-01-04", dropped, game, sizes),
               progress.Snapshot("2026-01-04", later, game, sizes)]
    rows_of_commits = [("2026-01-01", expected), ("2026-01-04", dropped), ("2026-01-04", later)]
    # (case, the snapshots after the commits, the day and scores of each row)
    cases = [("an unchanged working tree", [("2026-01-05", later)], rows_of_commits),
             ("a working tree that changed the totals", [("2026-01-05", expected)],
              rows_of_commits + [("2026-01-05", expected)]),
             ("a commit that undoes the one before", [("2026-01-05", dropped), ("2026-01-05", later)],
              rows_of_commits + [("2026-01-05", dropped), ("2026-01-05", later)])]
    failures = []
    for name, more, wanted in cases:
        snapshots = commits + [progress.Snapshot(day, summary, game, sizes) for day, summary in more]
        rows = progress.history_rows(snapshots)
        if rows != [progress.history_row(day, scoring.totals(summary, game), scoring.code_bytes(summary, game, sizes))
                    for day, summary in wanted]:
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
    with tempfile.TemporaryDirectory() as folder, osutil.foreign_repository():
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


def check_foreign_repository() -> list[str]:
    """check_read_blobs leaves alone the repository of a commit hook that runs the self-test. A linked worktree's hook
    has GIT_DIR and GIT_INDEX_FILE set for that worktree. The worktree here is made by hand, so it needs no commit."""
    with tempfile.TemporaryDirectory() as folder, osutil.foreign_repository():
        main, worktree = Path(folder) / "main", Path(folder) / "worktree"
        osutil.git(Path(folder), "init", "--quiet", str(main))
        gitdir = main / ".git" / "worktrees" / "worktree"
        gitdir.mkdir(parents=True)
        (gitdir / "commondir").write_text("../..\n", encoding="utf-8")
        (gitdir / "gitdir").write_text(f"{(worktree / '.git').as_posix()}\n", encoding="utf-8")
        (gitdir / "HEAD").write_text("ref: refs/heads/main\n", encoding="utf-8")
        worktree.mkdir()
        (worktree / ".git").write_text(f"gitdir: {gitdir.as_posix()}\n", encoding="utf-8")
        hook = {"GIT_DIR": str(gitdir), "GIT_INDEX_FILE": str(gitdir / "index")}
        os.environ.update(hook)
        try:
            failures = check_read_blobs()
        finally:
            for name in hook:
                del os.environ[name]
        bare = osutil.git(main, "config", "core.bare").decode().strip()
        staged = osutil.git(worktree, "ls-files").decode().split()
    if bare != "false" or staged:
        failures.append(f"git in a scratch folder changed a hook's repository: core.bare {bare}, staged {staged}")
    return failures


def check_misplaced_annotations() -> list[str]:
    """A STUB may start any function, such as a library function that game code calls. Any other function annotation
    must start a game function."""
    game, library = 0x401000, 0x402000
    annotations = [(game, "FUNCTION at a game function", False), (library, "STUB at a library function", True),
                   (library, "FUNCTION at a library function", False), (library + 1, "STUB inside a function", True)]
    found = [where for _, where, _ in runner.misplaced(annotations, {game, library}, {game})]
    expected = ["FUNCTION at a library function", "STUB inside a function"]
    return [] if found == expected else [f"annotation lint flags {found}, not {expected}"]


def check_unclosed_definitions() -> list[str]:
    """A FUNCTION or STUB definition ends in a lone `}` line before the next such annotation: the tools that put a
    function in a file take that line as its end. A brace with a comment after it, or a definition on one line, has
    none. A GLOBAL annotation inside a body is no next annotation."""
    import llm  # here, not at the top: it needs .venv's packages, and check.py imports this module before .venv
    target = project.game_config().target
    lines = [llm.function_line(0x401000), "void A(void)", "{", "}", "",
             f"// STUB: {target} 0x00401010", "void B(void)", "{", "}  // B", "",
             llm.function_line(0x401020), "void C(void)", "{", f"\t// GLOBAL: {target} 0x00501000", "\tstatic int x;",
             "}", "", llm.function_line(0x401030), "void D(void) {}"]
    found = llm.unclosed_definitions(lines)
    wanted = [5, 17]
    return [] if found == wanted else [f"unclosed_definitions flags lines {found}, not {wanted}"]


def check_local_declarations() -> list[str]:
    """A label at column 0 is no declaration, also when a call follows it. A return type on its own line is one."""
    text = ("end:\n\tFoo();\nlocal_20:\n\tFUN_004afe30();\ncase 0x11: Qux(0, 8);\nint Bar(int a);\nint\n"
            "Baz(int);\n")
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
    name once the context holds both, also when no file here uses the context's, and so do a global one here and a
    static one in the context: exit 2, which only a shared function name gives. A name that a file defines means
    that function, also when the file holds a folded copy of another file's function. A global name that two objects
    share means the one in the object that the using file defines functions of, and a second file that uses the
    other one fails, also when that file is in the context, unless it defines its own static. A function here that a
    context file declares another way and calls fails. A global function that the original made static may share its
    name with static ones while only its definition names it, as when its caller is not ported: functions.h then
    leaves it out, also when either file is the context's. Once its own file calls it, they share the name."""
    target = project.game_config().target
    exec_here = f"// FUNCTION: {target} 0x00401000\nstatic void Exec(struct task *tp)\n{{\n}}\n"
    exec_there = f"// FUNCTION: {target} 0x00402000\nvoid Exec(struct task *tp)\n{{\n}}\n"
    folded = f"// FUNCTION: {target} 0x00405000\nstatic void Helper(struct task *tp)\n{{\n}}\n"
    functions = [("0x00401000", "Exec", "L", "src/x.c", "o_x.obj"),
                 ("0x00402000", "Exec", "G", "src/emblem.c", "o_e.obj"),
                 ("0x00403000", "DispX", "L", "src/x.c", "o_x.obj"),
                 ("0x00404000", "DispY", "L", "src/y.c", "o_y.obj"),
                 ("0x00405000", "Helper", "L", "src/z.c", "o_z.obj"),
                 ("0x00406000", "Exec", "L", "src/z.c", "o_z.obj"),
                 ("0x00407000", "Kill", "L", "src/x.c", "o_x.obj"),
                 ("0x00408000", "Kill", "L", "src/y.c", "o_y.obj")]
    globals_ = [("0x00501000", "obj_c_info", "o_x.obj"), ("0x00502000", "obj_c_info", "o_y.obj"),
                ("0x00503000", "DAT_00503000", "o_z.obj")]
    own_static = f"// GLOBAL: {target} 0x00502000\nstatic int obj_c_info[2];\n\n"
    disp_x_int = f"// FUNCTION: {target} 0x00403000\nvoid DispX(int mode)\n{{\n}}\n"
    disp_y_calls = f"\n// FUNCTION: {target} 0x00404000\nstatic void DispY(struct task *tp)\n{{\n\tDispX(0);\n}}\n"

    def disp(address, name):
        return f"// FUNCTION: {target} {address}\nstatic void {name}(struct task *tp)\n{{\n\tobj_c_info[0] = 1;\n}}\n"

    def fill(address, name):
        return f"// FUNCTION: {target} {address}\nstatic void {name}(struct task *tp)\n{{\n\tDAT_00503000[0] = 1;\n}}\n"

    kill_here = (f"// FUNCTION: {target} 0x00407000\nstatic void Kill(struct task *tp)\n{{\n}}\n\n"
                 f"// FUNCTION: {target} 0x00403000\nvoid DispX(struct task *tp)\n{{\n\tKill(tp);\n}}\n")
    kill_there = f"// FUNCTION: {target} 0x00408000\nvoid Kill(struct task *tp)\n{{\n}}\n"
    kill_called = kill_there + f"\n// FUNCTION: {target} 0x00404000\nvoid DispY(struct task *tp)\n{{\n\tKill(tp);\n}}\n"
    sized = "extern char DAT_00503000[8];\n\n"
    unsized = "extern char DAT_00503000[];\n"

    # (case, files, the context's files, exit code, text of the output, addresses of the generated globals)
    cases = [("a static function against the context's global one", {"src/x.c": exec_here},
              {"src/emblem.c": exec_there}, 2, "share the name", []),
             ("a global function against the context's static one", {"src/emblem.c": exec_there},
              {"src/x.c": exec_here}, 2, "share the name", None),
             ("a shared function name and a function a context file declares another way",
              {"src/x.c": exec_here + "\n" + disp_x_int},
              {"src/emblem.c": exec_there, "src/y.c": "void DispX(struct task *tp);\n" + disp_y_calls}, 1,
              "share the name", None),
             ("a static function with no context", {"src/x.c": exec_here}, {}, 0, "", []),
             ("a static function and a file-local global one that only its definition names",
              {"src/x.c": kill_here, "src/y.c": kill_there}, {}, 0, "", []),
             ("a static function and a file-local global one that its own file calls",
              {"src/x.c": kill_here, "src/y.c": kill_called}, {}, 2, "share the name", None),
             ("a static function and a file-local global one in the context", {"src/x.c": kill_here},
              {"src/y.c": kill_there}, 0, "", []),
             ("a static function and a file-local global one that its own file calls in the context",
              {"src/x.c": kill_here}, {"src/y.c": kill_called}, 2, "share the name", None),
             ("a static function and a file-local global one, both in the context", {"src/z.c": folded},
              {"src/x.c": kill_here, "src/y.c": kill_there}, 0, "", []),
             ("a static function beside a folded copy from another file", {"src/x.c": exec_here + "\n" + folded}, {},
              0, "", []),
             ("a global name that two objects share", {"src/x.c": disp("0x00403000", "DispX")}, {}, 0, "",
              ["0x00501000"]),
             ("a global name that two files use", {"src/x.c": disp("0x00403000", "DispX"),
                                                   "src/y.c": disp("0x00404000", "DispY")}, {}, 1,
              "0x00501000, 0x00502000 share the name", None),
             ("a global name that a file here and a context file use", {"src/x.c": disp("0x00403000", "DispX")},
              {"src/y.c": disp("0x00404000", "DispY")}, 1, "0x00501000, 0x00502000 share the name", None),
             ("a global name that a file here uses and a context file defines static",
              {"src/x.c": disp("0x00403000", "DispX")},
              {"src/y.c": own_static + disp("0x00404000", "DispY")}, 0, "", ["0x00501000"]),
             ("a function here that a context file declares another way and calls", {"src/x.c": disp_x_int},
              {"src/y.c": "void DispX(struct task *tp);\n" + disp_y_calls}, 1,
              "src/y.c declares it `void DispX(struct task *)`", None),
             ("a function here that a context file declares the same way and calls", {"src/x.c": disp_x_int},
              {"src/y.c": "void DispX(int mode);\n" + disp_y_calls}, 0, "", []),
             ("an array that a context file declares with and without its size",
              {"src/x.c": sized + fill("0x00403000", "DispX")},
              {"src/y.c": unsized + sized + fill("0x00404000", "DispY")}, 0, "sources declare it in 2 ways", None),
             ("an array that a context file declares only without its size",
              {"src/x.c": sized + fill("0x00403000", "DispX")},
              {"src/y.c": unsized + "\n" + fill("0x00404000", "DispY")}, 1,
              "src/y.c declares it `char DAT_00503000[]` in the context tree", None)]
    failures = []
    for case, files, context_files, code, line, addresses in cases:
        found, output, generated = run_decls(files, context_files, functions, globals_)
        defined = re.findall(r"GLOBAL: \w+ (0x\w+)", generated.get(names.GLOBALS_CPP, ""))
        if found != code or line not in output or (addresses is not None and defined != addresses):
            failures.append(f"decls for {case} gives exit {found}, not {code}, globals {defined}, not {addresses}, "
                            f"and prints {output!r}, not {line!r}")
    return failures


def check_static_users() -> list[str]:
    """decls says to drop the static of a function that another file calls. A file that defines its own copy with no
    annotation, which the game's link folded into the other file's, calls that copy."""
    target = project.game_config().target
    helper = f"// FUNCTION: {target} 0x00405000\nstatic void Helper(struct task *tp)\n{{\n}}\n"
    calls = f"// FUNCTION: {target} 0x00404000\nstatic void DispY(struct task *tp)\n{{\n\tHelper(tp);\n}}\n"
    copy = "static void Helper(struct task *tp)\n{\n}\n\n"
    functions = [("0x00404000", "DispY", "L", "src/y.c", "o_y.obj"), ("0x00405000", "Helper", "L", "src/z.c", "o_z.obj")]
    notice = "Helper is static in src/z.c but src/y.c use it: drop the static"
    failures = []
    for case, caller, wanted in (("another file's static", calls, True), ("a copy of it", copy + calls, False)):
        _, output, _ = run_decls({"src/z.c": helper, "src/y.c": caller}, {}, functions, [])
        if (notice in output) != wanted:
            failures.append(f"decls for a call to {case} prints {output!r}, {'not ' if wanted else ''}{notice!r}")
    return failures


def check_nested_globals() -> list[str]:
    """A global at an address inside another global's span splits it: decls fails on the new one, as the model's
    `extern unsigned char DAT_05b3e04c;` did inside `struct NJS_ARGB DAT_05b3e040`. A global behind the span is fine,
    and so is a pair that the context's last layout already had. The line says to shrink the holder when only a file
    here declares it, and gives both ways when a file here declares both."""
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
              "decls: DAT_05b3e040 (struct NJS_ARGB) holds 1 other globals, as in the last layout: DAT_05b3e04c at +12"),
             ("a struct global here over the context's global", holder, fog("DAT_05b3e04c"), 1,
              "at +12. The tree declares DAT_05b3e04c and a file here declares DAT_05b3e040: declare DAT_05b3e040 "
              "with at most 12 bytes."),
             ("a struct global and a global inside it, both here", holder | fog("DAT_05b3e04c"), {}, 1,
              "at +12. Remove the declaration of DAT_05b3e04c and reach it through DAT_05b3e040, or declare "
              "DAT_05b3e040 with at most 12 bytes.")]
    failures = []
    for case, files, context_files, code, line in cases:
        found, output, _ = run_decls(files, context_files, [], [], argb)
        if found != code or line not in output or (code == 0 and "inside" in output):
            failures.append(f"decls for {case} gives exit {found}, not {code}, and prints {output!r}, not {line!r}")
    return failures


def check_decls_aliases() -> list[str]:
    """decls names the library function at a FUN_ address, as memset for the model's FUN_008e3350. A data name that
    two objects share stays DAT_ in a file that would not mean that address by it: no notice, and the extern keeps
    the DAT_ name. A file that would mean it gets the notice. A placeholder variable as a struct tag fails."""
    target = project.game_config().target
    functions = [("0x00402000", "FUN_00402000", "G", "src/lib.c", "o_lib.obj"),
                 ("0x00403000", "DispX", "L", "src/x.c", "o_x.obj")]
    globals_ = [("0x00501000", "obj_c_info", "o_x.obj"), ("0x00502000", "obj_c_info", "o_y.obj")]
    clears = {"src/w.c": "void *FUN_00402000(void *, int, unsigned int);\nvoid Clear(void)\n{\n"
                         "\tFUN_00402000(0, 0, 4);\n}\n"}
    shared = {"src/w.c": "extern int DAT_00501000[];\nvoid Use(void)\n{\n\tDAT_00501000[0] = 1;\n}\n"}
    meant = {"src/x.c": f"// FUNCTION: {target} 0x00403000\nstatic void DispX(struct task *tp)\n{{\n"
                        "\tDAT_00501000[0] = 1;\n}\n"}
    tag = {"src/w.c": "void Start(struct param_1 const *, float);\n"}
    notice = "DAT_00501000 has the name obj_c_info: use that"
    # (case, files, exit code, a line of the output, a line it must not print)
    cases = [("a library function's address", clears, 0, "FUN_00402000 has the name memset: use that", None),
             ("a shared data name that the file would not mean", shared, 0, "decls:", notice),
             ("a shared data name that the file would mean", meant, None, notice, None),
             ("a placeholder struct tag", tag, 1, "src/w.c: `struct param_1` names a placeholder variable", None)]
    saved = project.library_rows
    project.library_rows = lambda: [library.Row(0x00402000, "memset", "_memset", "library")]
    failures = []
    try:
        for case, files, code, line, absent in cases:
            found, output, generated = run_decls(files, {}, functions, globals_)
            externs = generated.get(names.GLOBALS_H, "")
            if ((code is not None and found != code) or line not in output or (absent and absent in output)
                    or case.endswith("not mean") and "DAT_00501000[]" not in externs):
                failures.append(f"decls for {case} gives exit {found}, not {code}, and prints {output!r}")
    finally:
        project.library_rows = saved
    return failures


def check_extern_of() -> list[str]:
    """A definition's extern in globals.h has one `extern`, also for a C++ `extern const` definition, and leaves an
    array's size to the definition."""
    cases = [("int x", "extern int x"), ("extern const float x", "extern const float x"),
             ("char buf[8]", "extern char buf[]")]
    return [f"extern_of gives {declgen.extern_of(definition)!r} for {definition!r}, not {wanted!r}"
            for definition, wanted in cases if declgen.extern_of(definition) != wanted]


def check_reached_types() -> list[str]:
    """A struct that a file reaches only through a call's result, as in `GetWork(0)->speed`, gets its layout in
    types.h. So does one that the call's arguments reach the same way. A call's result that nothing reaches into
    gets none."""
    target = project.game_config().target
    layouts = ("struct work {\n    float speed;\n};\n\nstruct task {\n    int id;\n};\n\n"
               "struct pad {\n    int on;\n};\n")
    getters = {"src/w.c": f"// FUNCTION: {target} 0x00401000\nstruct work *GetWork(int id)\n{{\n\treturn 0;\n}}\n\n"
                          f"// FUNCTION: {target} 0x00402000\nstruct task *GetTask(void)\n{{\n\treturn 0;\n}}\n\n"
                          f"// FUNCTION: {target} 0x00404000\nstruct pad *GetPad(void)\n{{\n\treturn 0;\n}}\n"}
    user = {"src/x.c": f"// FUNCTION: {target} 0x00403000\nvoid Run(void)\n{{\n"
                       "\tGetWork(GetTask()->id)->speed = 1;\n\tGetPad();\n}\n"}
    functions = [("0x00401000", "GetWork", "G", "src/w.c", "o_w.obj"),
                 ("0x00402000", "GetTask", "G", "src/w.c", "o_w.obj"),
                 ("0x00403000", "Run", "G", "src/x.c", "o_x.obj"),
                 ("0x00404000", "GetPad", "G", "src/w.c", "o_w.obj")]
    code, output, generated = run_decls(user, getters, functions, [], layouts)
    laid_out = [n for n in ("work", "task", "pad") if f"struct {n} {{" in generated.get(names.TYPES_H, "")]
    if code != 0 or laid_out != ["work", "task"]:
        return [f"decls for structs reached through calls' results gives exit {code}, not 0, lays out "
                f"{', '.join(laid_out) or 'none'}, not work and task, and prints {output!r}"]
    return []


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


def check_clone() -> list[str]:
    """A copy gets the template's code with the copy's names. Its own prototype names its parameters and gives
    their types, else the template's types with param_N names. A struct member keeps its name."""
    import clone  # here, not at the top: it needs .venv's packages, and check.py imports this module before .venv

    template = "void Foo(struct task *tp, int count)"
    body = ["{", "	if (DAT_00500000)", "	{", "		Bar(tp, count + DAT_00500000);", "		tp->count = 0;", "	}", "}"]
    names = {"Foo": "FUN_00402000", "Bar": "Baz", "DAT_00500000": "DAT_00600000"}
    wanted_body = ["{", "	if (DAT_00600000)", "	{", "		Baz(param_1, param_2 + DAT_00600000);",
                   "		param_1->count = 0;", "	}", "}"]
    cases = [("FUN_00402000", "", False, "void FUN_00402000(struct task *param_1, int param_2)"),
             ("Qux", "void Qux(struct task *tw, int);", True, "static void Qux(struct task *tw, int param_2)")]
    failures = []
    for name, proto, static, wanted in cases:
        sig, renames = clone.copy_signature(template, name, proto, static)
        if sig != wanted:
            failures.append(f"clone signature `{sig}`, not `{wanted}`")
        if name == "FUN_00402000":
            found = clone.copy_body(["// FUNCTION: X 0x00401000", template] + body, renames | names)
            if found != wanted_body:
                failures.append(f"clone body {found}, not {wanted_body}")
    return failures + check_clone_types(clone) + check_clone_stubs(clone) + check_clone_globals(clone)


def check_clone_types(clone) -> list[str]:
    """A type that only the template gives becomes a neutral one: the signed integer of its size for an integer or an
    enum, void * for a pointer; float stays. A pointer stays where a prototype in the tables takes it at a call that
    passes the name straight on. A struct by value or an array has no neutral type."""
    failures = []
    task = ["struct task *"]
    protos = {"FreeTask": "void FreeTask(struct task *tp);", "Baz": "void Baz(struct task *, int);"}
    body = ["{", "	FreeTask(DAT_00600000);", "	Baz(param_1, count + y);", "	Baz(FreeTask(DAT_00600004), param_3);", "}"]
    found = clone.pointer_uses(body, protos)
    if found != {"DAT_00600000": task, "param_1": task, "DAT_00600004": task}:
        failures.append(f"clone pointer uses {dict(found)}")
    cases = [
        (lambda: clone.neutral_function("static enum eStage Foo(struct task *param_1, unsigned int param_2, float x)", {}),
         "static int Foo(void *param_1, int param_2, float x)"),
        (lambda: clone.neutral_function("void Foo(struct task *param_1, bool param_2, ...)", {"param_1": task}),
         "void Foo(struct task *param_1, char param_2, ...)"),
        (lambda: clone.neutral_function("struct task *Foo(void)", {}), "void *Foo(void)"),
        (lambda: clone.neutral_function("void Bar(struct task *, unsigned short, void (*)(void));", {}),
         "void Bar(void *, short, void *);"),
        (lambda: clone.neutral_extern("extern unsigned int DAT_00600000;", "DAT_00600000", []),
         "extern int DAT_00600000;"),
        (lambda: clone.neutral_extern("extern struct task *DAT_00600000;", "DAT_00600000", task),
         "extern struct task *DAT_00600000;"),
        (lambda: clone.neutral_extern("extern struct task *DAT_00600000;", "DAT_00600000", []),
         "extern void *DAT_00600000;"),
        (lambda: clone.neutral_extern("extern void (*DAT_00600000)(void);", "DAT_00600000", task),
         "extern void *DAT_00600000;"),
        (lambda: clone.neutral_extern("extern double DAT_00600000;", "DAT_00600000", []), "extern double DAT_00600000;"),
        (lambda: clone.neutral_function("void Foo(struct NJS_VECTOR param_1)", {}), None),
        (lambda: clone.neutral_extern("extern int DAT_00600000[];", "DAT_00600000", []), None),
    ]
    for make, wanted in cases:
        try:
            result = make()
        except clone.Skip:
            result = None
        if result != wanted:
            failures.append(f"clone neutral type `{result}`, not `{wanted}`")
    return failures


def check_clone_stubs(clone) -> list[str]:
    """A shared name that a kept copy uses or defines gets a static STUB for each of its functions that the tree uses
    but nothing defines, once two or more are used or defined. Exec: a.c uses it, a kept copy in b.c uses it, a kept
    copy in c.c defines it, the tree defines a fourth, and e.c does not use the fifth. Lone: only a copy in f.c uses
    it."""
    target = project.game_config().target
    wanted = [f"// STUB: {target} 0x00401000", "static float Exec(struct task *tp)", "{", "\treturn (float)0;", "}"]
    found = clone.stub(0x401000, "a.c", "float Exec(struct task *tp);").lines
    failures = [] if found == wanted else [f"clone STUB {found}, not {wanted}"]
    planned = {a: clone.stub(a, file, "void Exec(struct task *tp);") for a, file in
               [(0x401000, "a.c"), (0x402000, "b.c"), (0x403000, "c.c"), (0x405000, "e.c")]}
    planned[0x406000] = clone.stub(0x406000, "f.c", "void Lone(void);")
    siblings = {"Exec": [0x401000, 0x402000, 0x403000, 0x404000, 0x405000], "Lone": [0x406000, 0x407000]}
    uses = {"a.c": {"Exec"}, "b.c": set(), "c.c": set(), "e.c": set(), "f.c": set()}

    def copy(address: int, file: str, shared: str) -> clone.Copy:
        return clone.Copy(address, f"FUN_{address:08x}", 0x400000, file, [], [], frozenset(), frozenset({shared}))

    cases = [([copy(0x408000, "b.c", "Exec"), copy(0x403000, "c.c", "Exec")], [0x401000, 0x402000]),
             ([copy(0x409000, "f.c", "Lone")], [])]
    for kept, addresses in cases:
        found = [s.address for s in clone.stubs_needed(kept, siblings, {0x404000}, planned, uses)]
        if found != addresses:
            failures.append(f"clone STUBs {[hex(a) for a in found]} for copies at {[hex(c.address) for c in kept]}, "
                            f"not {[hex(a) for a in addresses]}")
    return failures


def check_clone_globals(clone) -> list[str]:
    """A copy is skipped when it uses a global whose name several globals have, also when the template's name is the
    same (decls then fails on two copies). A function with such a name, or a global with a name of its own, passes."""
    shared = {"missile_smoke"}
    smoke = clone.Pair("missile_smoke", "global", 0x2C0CAE0, 0x3B76128)
    cases = [({"missile_smoke": smoke}, True), ({"missile_smoke": smoke._replace(kind="function")}, False),
             ({"missile_smoke": smoke._replace(new="DAT_03b76128")}, False), ({}, False)]
    failures = []
    for pairs, skipped in cases:
        try:
            clone.check_globals(pairs, shared)
            found = False
        except clone.Skip as skip:
            found = skip.kind == "shared name"
        if found != skipped:
            failures.append(f"clone global check {'skips' if found else 'passes'} {pairs}")
    return failures


def check_link() -> list[str]:
    """link.py rebuilds the self-test's exe byte for byte from its own bytes, and again with original.cpp's object in
    place of its functions. That object pools five literals, uses __fltused and the security cookie, and calls the
    /GL-built Total."""
    image, header = pe.Image(SELFTEST_ORIGINAL), pe.read_header(SELFTEST_ORIGINAL)
    functions = [address for address, source in map_symbols(SELFTEST_MAP) if source == "original.cpp.obj"]
    original = SELFTEST_ORIGINAL.read_bytes()
    failures = []
    for case, swapped in (("its own bytes", False), ("original.cpp swapped in", True)):
        try:
            swaps = [link.swap_object("original.cpp", coff.read(SELFTEST_OBJECT), functions, image)] if swapped else []
            rebuilt = link.relink(image, header, swaps, SELFTEST_LINK)[0]
        except link.NotLinkable as error:
            failures.append(f"link of SELFTEST.exe from {case}: {error}")
            continue
        count, first = osutil.byte_differences(original, rebuilt.read_bytes())
        if count:
            failures.append(f"link of SELFTEST.exe from {case} differs in {count} bytes, the first at 0x{first:x}")
    return failures


def check_units() -> list[str]:
    """The unit tests of the repairs in llm.py and cfix.py, of the try loop in llm.py, of the dossier facts in
    facts.py, of the trick finder in tricks.py, of the site pages in pages.py, of the data scores in scoring.py, of
    the split in link.py, of the recipe checks in recipes.py, of the type search in retype.py, of the rewrites in
    permute.py, of the stack argument audit in stackargs.py and of the names in dossier.py, one module each."""
    # here, not at the top: they need .venv's packages, and check.py imports this module before .venv
    import benchtests
    import bytetests
    import casttests
    import ctexttests
    import decltests
    import dossiertests
    import facttests
    import linktests
    import permutetests
    import progresstests
    import recipetests
    import retypetests
    import sitetests
    import solvetests
    import stackargtests
    import tricktests
    modules = (ctexttests, bytetests, casttests, decltests, dossiertests, benchtests, solvetests, facttests, tricktests,
               sitetests, progresstests, linktests, recipetests, retypetests, permutetests, stackargtests)
    return [failure for module in modules for failure in module.run()]


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


def addresses(summary: dict) -> set[int]:
    return {int(entry["address"], 16) for entry in summary["functions"]}


def check_totals(expected: dict, current: dict) -> list[str]:
    """The totals leave a stub out of the decompiled count, and a library function out of the game total."""
    with_library = copy.deepcopy(current)
    with_library["functions"][0]["library"] = True
    totals = scoring.totals(with_library, addresses(current))
    if totals._asdict() == expected["totals"]:
        return []
    return [f"totals {json.dumps(totals._asdict())} != {json.dumps(expected['totals'])} in expected.json"]


def check_trick_totals(current: dict) -> list[str]:
    """A function at 100% with a trick keeps its score, but it counts under tricks, not matched."""
    tricked = copy.deepcopy(current)
    first_matched(tricked)["trick"] = True
    game = addresses(current)
    plain, with_trick = scoring.totals(current, game), scoring.totals(tricked, game)
    if (with_trick.matched, with_trick.tricks) == (plain.matched - 1, plain.tricks + 1):
        return []
    return [f"a trick moves matched {plain.matched} to {with_trick.matched} and tricks {plain.tricks} to "
            f"{with_trick.tricks}, not one from matched to tricks"]


def first_matched(summary: dict) -> dict:
    """The first game function of SUMMARY at 100%."""
    return next(entry for entry in summary["functions"] if not entry["library"] and scoring.score(entry) == 1.0)


def check_trick_state(current: dict) -> list[str]:
    """A trick shows in the state and in is_trick only at 100%."""
    failures = []
    tricked = dict(first_matched(current), trick=True)
    partial = dict(tricked, accuracy=0.85)
    if scoring.state(tricked) != "100%, through a trick":
        failures.append(f"state of a trick at 100% gives {scoring.state(tricked)}")
    if scoring.is_trick(partial) or not scoring.is_trick(tricked):
        failures.append("is_trick is true for a trick at 85% or false for a trick at 100%")
    return failures


def check_code_bytes(current: dict) -> list[str]:
    """The code bytes leave a trick function out of the matched bytes, a stub out of the decompiled and matched
    bytes, and a library entry out of all three counts."""
    failures = []
    game = addresses(current)
    sizes = {address: 10 for address in game}
    plain = scoring.code_bytes(current, game, sizes)
    cases = [("a trick", {"trick": True}, plain._replace(matched=plain.matched - 10)),
             ("a stub", {"stub": True}, plain._replace(decompiled=plain.decompiled - 10, matched=plain.matched - 10)),
             ("a library entry", {"library": True}, scoring.Bytes(*(count - 10 for count in plain)))]
    for label, changed, wanted in cases:
        summary = copy.deepcopy(current)
        first_matched(summary).update(changed)
        found = scoring.code_bytes(summary, game, sizes)
        if found != wanted:
            failures.append(f"code_bytes gives {found} with {label}, not {wanted}")
    return failures


def check_summarize_tricks() -> list[str]:
    """The summary gets the trick key for the tricked addresses only."""
    failures = []
    scored = {0x401000: {"name": "a", "matching": 1.0}, 0x401010: {"name": "b", "matching": 1.0}}
    keys = {entry["name"]: "trick" in entry for entry in runner.summarize("t", scored, {0x401000})["functions"]}
    if keys != {"a": True, "b": False}:
        failures.append(f"summarize sets the trick key {keys}, not for the tricked address only")
    return failures


def check_recent_gain() -> list[str]:
    """The card counts the code share from the last row a week or more before the newest. A younger history counts
    from its oldest row and says since when. Eighths of the code keep the floats exact."""
    def rows(*pairs):
        return [{"date": day, "matched_bytes": str(matched), "game_bytes": "8"} for day, matched in pairs]

    cases = [(rows(("2026-10-01", 1), ("2026-10-05", 4), ("2026-10-09", 7)), (0.75, "this week")),
             (rows(("2026-10-17", 0), ("2026-10-22", 2)), (0.25, "since 2026-10-17")),
             (rows(("2026-10-22", 5)), (0.0, "since 2026-10-22")),
             (rows(("2026-10-01", 1), ("2026-10-08", 3)), (0.25, "this week")),
             (rows(("2026-10-02", 2), ("2026-10-08", 3)), (0.125, "since 2026-10-02"))]
    return [f"recent_gain gives {progress.recent_gain(history)} for {history}, not {wanted}"
            for history, wanted in cases if progress.recent_gain(history) != wanted]


def check_whole_percent() -> list[str]:
    """A whole percent rounds down, so only a whole that is all done shows 100%. It counts in integers: 29 of 100 is
    29%, though 100 * 0.29 in floats is just under 29."""
    cases = [(0, 0, "0%"), (29, 100, "29%"), (199, 200, "99%"), (1, 1, "100%")]
    return [f"whole_percent({part}, {whole}) gives {scoring.whole_percent(part, whole)}, not {wanted}"
            for part, whole, wanted in cases if scoring.whole_percent(part, whole) != wanted]


def map_functions(path: Path) -> list[tuple[int, int]]:
    """(address, size) of each function from the self-test's own objects in a link map.
    Each runs to the next symbol in the code section."""
    symbols = map_symbols(path)
    # A library member shows as library:object.
    return [(address, following - address) for (address, source), (following, _) in zip(symbols, symbols[1:])
            if ":" not in source]


def map_symbols(path: Path) -> list[tuple[int, str]]:
    """(address, object) of each symbol in the code section of a link map, by address."""
    symbols = []
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        parts = line.split()
        if len(parts) >= 4 and parts[0].startswith("0001:") and re.fullmatch(r"[0-9a-f]{8}", parts[2]):
            symbols.append((int(parts[2], 16), parts[-1]))
    return sorted(symbols)
