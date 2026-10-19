#!/usr/bin/env python3
"""Build the decomp and score it against the original binary.

  python tools/check.py setup [--game PATH]   get everything ready and turn on the git hooks
  python tools/check.py fn 0x00401000 ...     score functions, exit 0 when all match
  python tools/check.py ci [--base COMMIT]    lint, self-test and repo checks: no game needed
  python tools/check.py gate                  ci plus the game scores: run it before a push
  python tools/check.py save                  gate, and record the new scores, history and visuals
  python tools/check.py library               find the runtime library in the game and score it
  python tools/check.py sources               tie functions to source files and classes, from the exe
  python tools/check.py groups                recount the evidence for data/codegen-groups.csv
  python tools/check.py decls                 write the declarations and stubs that the sources use
  python tools/check.py dossier 0x00401000    what an agent needs to decompile a function
  python tools/check.py access 0x00800000     how the exe reads and writes a global, for its type
  python tools/check.py probe EXE             what a new game's exe needs: see docs/PORTING.md

Every command sets up what it needs: .venv with the pinned packages, the
compiler in .toolchain (a 722 MB download from Microsoft, once) and the path
to the game, found in a Steam library or given with --game. Output is short:
tool output only shows on failure, plus compiler and reccmp warnings.

The game is the one target in reccmp-project.yml. Its build settings are in
game.cmake. docs/FRAMEWORK.md has the details.
"""

import argparse
import json
import re
import shutil
import subprocess
import sys
from pathlib import Path

import ci
import codegen
import datafiles
import declgen
import library
import osutil
import pe
import progress
import project
import report
import runner
import scoring
import selftest
import toolchain

ROOT = project.ROOT
LIBRARY_RSP = project.BUILD / "library.rsp"  # CMakeLists.txt links the game with it


def main() -> int:
    args = parse_args()
    if args.command == "probe":
        return probe(args.exe)
    if args.command == "setup":
        return set_up(args.game)
    if args.command == "sources":
        return datafiles.write_sources(project.require_game())
    if args.command == "groups":
        return datafiles.check_groups(project.require_game())
    if args.command == "decls":
        return declgen.write(args.context, args.tables)
    if args.command == "dossier":
        # Only .venv has capstone.
        import dossier

        return dossier.show(project.require_game(), args.addresses, args.c, args.callers, args.tables, args.drafts,
                            args.accesses)
    if args.command == "access":
        # Only .venv has capstone.
        import accesses

        return accesses.show(project.require_game(), args.addresses, args.size)
    if args.command == "ci":
        toolchain.ensure(project.TOOLCHAIN)
        build()
        return run_ci(args.base)
    return run_with_game(args)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    commands = parser.add_subparsers(dest="command", required=True)
    setup = commands.add_parser("setup")
    setup.add_argument("--game", type=Path, help="the exe, if it is not in a Steam library")
    fn = commands.add_parser("fn")
    fn.add_argument("addresses", nargs="+", type=lambda value: int(value, 16),
                    help="original addresses, e.g. 0x00401000")
    ci_command = commands.add_parser("ci")
    ci_command.add_argument("--base", help="commit to compare scores with (default: the upstream)")
    commands.add_parser("gate")
    commands.add_parser("save")
    commands.add_parser("library")
    commands.add_parser("sources")
    commands.add_parser("groups")
    decls = commands.add_parser("decls")
    decls.add_argument("--context", type=Path, help="another checkout whose files give signatures and globals")
    decls.add_argument("--tables", type=Path, help="a folder of name tables: tools/declgen.py says what it holds")
    dossier = commands.add_parser("dossier")
    dossier.add_argument("addresses", nargs="+", type=lambda value: int(value, 16), help="e.g. 0x00401000")
    dossier.add_argument("--c", action="store_true", help="add Ghidra's draft C")
    dossier.add_argument("--callers", action="store_true", help="add the functions that call it")
    dossier.add_argument("--tables", type=Path, help="a folder of name tables: tools/declgen.py says what it holds")
    dossier.add_argument("--drafts", type=Path, help="the folder of Ghidra drafts (default: build/decomp)")
    dossier.add_argument("--accesses", action="store_true", help="add how the whole exe reads and writes each global")
    access = commands.add_parser("access")
    access.add_argument("addresses", nargs="+", type=lambda value: int(value, 16), help="e.g. 0x00800000")
    access.add_argument("--size", type=int, default=1, help="bytes to cover from each address (default: 1)")
    commands.add_parser("probe").add_argument("exe", type=Path)
    return parser.parse_args()


def run_with_game(args: argparse.Namespace) -> int:
    """The commands that build, then read the original exe."""
    game = project.require_game()
    toolchain.ensure(project.TOOLCHAIN)
    runner.write_user_yml(project.USER_YML, project.game_config().target, game)
    if args.command == "library":
        datafiles.write_library(game)
    build()
    runner.write_constants(game)
    if args.command == "fn":
        return report.score_functions(args.addresses, game)
    if args.command == "library":
        return report.score_library(game)
    if args.command == "save":
        return run_save(game)
    return run_gate(game)


# Setup


def ensure_venv() -> None:
    """Create .venv with the pinned packages, or update it when requirements.txt changed."""
    installed = project.VENV / "requirements.txt"
    if installed.exists() and installed.read_bytes() == project.REQUIREMENTS.read_bytes():
        return
    print("Installing the pinned Python packages into .venv.", flush=True)
    project.run([sys.executable, "-m", "venv", project.VENV])
    project.run([project.VENV_PYTHON, "-m", "pip", "install", "--quiet", "--disable-pip-version-check",
                 "-r", project.REQUIREMENTS])
    shutil.copyfile(project.REQUIREMENTS, installed)


def set_up(game_path: Path | None) -> int:
    if ci.run_git("rev-parse", "--is-inside-work-tree").stdout.strip() != "true":
        sys.exit("Not a git clone. The checks compare against git history: clone the repo with git.")
    # reccmp reads paths in reccmp-user.yml from the repo root, not from where you ran this.
    game = project.require_game(game_path.resolve() if game_path else None)
    toolchain.ensure(project.TOOLCHAIN)
    runner.write_user_yml(project.USER_YML, project.game_config().target, game)
    ci.git("config", "core.hooksPath", ".githooks")
    print(f"Python packages: {project.VENV.relative_to(ROOT)}")
    print(f"Compiler: cl.exe {toolchain.CL_VERSION} in {project.TOOLCHAIN.relative_to(ROOT)}")
    print(f"Game: {game}")
    print("Hooks: pre-commit runs `check.py save`, pre-push runs `check.py gate`")
    if progress.SUMMARY_JSON.exists():
        print("Ready. Next: python tools/check.py gate")
    else:
        print("Ready. A new game has no scores yet: go on with docs/PORTING.md.")
    return 0


# Build


def write_library_includes() -> None:
    """Link every function in src/library.csv into our exe, so reccmp scores each one."""
    symbols = [row.symbol for row in project.library_rows() if row.kind == "library" and row.symbol]
    osutil.write_if_changed(LIBRARY_RSP, "".join(f'"/INCLUDE:{symbol}"\n' for symbol in symbols))


def build() -> None:
    cmake = project.VENV_SCRIPTS / "cmake.exe"
    tools = (project.TOOLCHAIN / "bin").as_posix()
    # A build folder made with another compiler, or in another clone folder, keeps that compiler: start it over.
    cache = project.BUILD / "CMakeCache.txt"
    compiler = f"CMAKE_C_COMPILER:STRING={tools}/cl.exe\n"
    if cache.exists() and compiler not in cache.read_text(encoding="utf-8", errors="replace"):
        osutil.remove(project.BUILD)
    codegen.write_codegen_groups()
    write_library_includes()
    if not (project.BUILD / "build.ninja").exists():
        project.run([cmake, "-S", ROOT, "-B", project.BUILD, "-G", "Ninja", "-DCMAKE_BUILD_TYPE=RelWithDebInfo",
                     f"-DCMAKE_MAKE_PROGRAM={(project.VENV_SCRIPTS / 'ninja.exe').as_posix()}",
                     f"-DCMAKE_C_COMPILER={tools}/cl.exe", f"-DCMAKE_CXX_COMPILER={tools}/cl.exe",
                     f"-DCMAKE_RC_COMPILER={tools}/RC.Exe", f"-DCMAKE_MT={tools}/mt.exe"])
    output = project.run([cmake, "--build", project.BUILD]).stdout
    for line in output.splitlines():
        if ": warning " in line:
            print(line)
    pe.clear_timestamp(selftest.SELFTEST_ORIGINAL)
    runner.write_build_yml(runner.game_build())


# Checks


def run_ci(base: str | None) -> int:
    """The checks that need no game. Each prints its own lines. Returns 1 if any failed."""
    return conclude({"lint": lint(), "selftest": selftest.run(), "repo": ci.run_checks(base)})


def run_gate(game: Path) -> int:
    """The checks of ci, and the game's scores. Returns 1 if any failed."""
    results = checks_on_game(game)
    return finish_game_checks(results, game, score_game(game))


def run_save(game: Path) -> int:
    """run_gate, and it records the scores once the checks before them pass."""
    results = checks_on_game(game)
    trusted = not any(results.values())
    if not trusted:
        print("     not saving: the scores can only be trusted once the checks above pass")
    scores = score_game(game)
    if scores is not None and trusted:
        save_scores(scores)
    return finish_game_checks(results, game, scores)


def checks_on_game(game: Path) -> dict[str, int]:
    """The checks that must pass before the game's scores can be trusted."""
    results = {"lint": lint(), "selftest": selftest.run()}
    runner.require_our_game()
    results["toolchain"] = compare_rich_headers(game)
    return results


def finish_game_checks(results: dict[str, int], game: Path, scores: dict | None) -> int:
    return conclude({**results, "scores": 1 if scores is None else 0, "functions": check_function_map(game),
                     "repo": ci.run_checks(None)})


def conclude(results: dict[str, int]) -> int:
    failed = [name for name, code in results.items() if code]
    print(f"FAILED: {', '.join(failed)}" if failed else "All checks passed.")
    return 1 if failed else 0


def lint() -> int:
    """reccmp's annotation linter: bad addresses, duplicates, misplaced markers.
    Then each function annotation must start a function in data/functions.csv, a game function unless it is a STUB."""
    lint_command = [project.VENV_SCRIPTS / "reccmp-decomplint.exe", "src", "--module", project.game_config().target,
                    "--warnfail"]
    result = subprocess.run(lint_command, cwd=ROOT, capture_output=True, text=True, errors="replace")
    if result.returncode != 0:
        print(f"{result.stdout}{result.stderr}".rstrip())
        print("FAIL annotation lint")
        return 1
    misplaced = runner.misplaced_annotations()
    if misplaced:
        print(f"FAIL {len(misplaced)} function annotations in src/ start no function they may name:")
        for line in misplaced[:ci.MAX_LINES]:
            print(f"     {line}")
        return 1
    print("ok   annotation lint")
    return 0


def scan_gap(image: pe.Image, address: int, first: int) -> tuple[int, int | None]:
    """Walk over padding and import stubs from address up to first.
    Return where the walk ends, and the address of code that is neither, if there is any."""
    while address < first:
        code = image.read(address, 6).ljust(6, b"\0")  # code past the file's bytes is zero
        if code[0] in (0x00, 0xCC):
            address += 1
        elif code[:2] == library.IMPORT_JUMP and int.from_bytes(code[2:], "little") in image.import_slots:
            address += 6  # jmp [slot]: the linker's import stub
        else:
            return first, address
    return address, None


def stray_code(image: pe.Image, section: range, spans: list[tuple[int, int]]) -> list[int]:
    """The addresses in a code section where code sits outside the spans."""
    address, end = section.start, section.stop
    stray = []
    for first, last in spans + [(end, end)]:
        if last <= address or first > end:
            continue
        address, found = scan_gap(image, address, first)
        if found is not None:
            stray.append(found)
        address = max(address, last)
    return stray


def check_function_map(game: Path) -> int:
    """Every byte of the game's code sections is in a function of data/functions.csv, padding
    or an import stub. Anything else is code that Ghidra missed."""
    image = pe.Image(game)
    spans = sorted((function["address"], function["address"] + function["size"]) for function in progress.load_functions())
    stray = []
    for start, _, section in image.sections:
        if section.flags & pe.CODE:
            stray += stray_code(image, range(start, start + section.virtual_size), spans)
    if stray:
        print(f"FAIL {len(stray)} stretches of code are in no function of data/functions.csv:")
        print("     " + " ".join(f"0x{address:08x}" for address in stray[:ci.MAX_LINES]))
        return 1
    print("ok   every code byte is in a function, padding or an import stub")
    return 0


def by_build(rich: dict[tuple[int, int], int]) -> list:
    """The (product, build): count entries of a Rich header, ordered by build, then product id."""
    return sorted(rich.items(), key=lambda item: (item[0][1], item[0][0]))


def compare_rich_headers(game: Path) -> int:
    """Every tool build in our exe, import libraries included, also made the game.

    Builds only: the product ids depend on each game's mix of C, C++ and /GL objects.
    """
    ours, theirs = pe.rich_entries(project.OUR_GAME), pe.rich_entries(game)
    missing = {build for _, build in ours} - {build for _, build in theirs}
    if missing:
        print(f"FAIL our exe has tool builds the game never used: {sorted(missing)}")
        for (product, build), count in [entry for entry in by_build(ours) if entry[0][1] in missing]:
            print(f"     0x{product:02x} {RICH_PRODUCTS.get(product, 'other')} build {build}: {count} objects in our exe")
        print(f"     the game's builds: {sorted({build for _, build in theirs})}. docs/PORTING.md step 8 has the fix.")
        return 1
    print("ok   every tool build in our exe also built the game")
    return 0


def check_annotations(functions: dict[int, dict], game: Path) -> bool:
    """Print the library rows and annotations that name no symbol in our build. False if an annotation does."""
    unmatched = runner.unmatched_library_rows(functions, game)
    if unmatched:
        print(f"note {len(unmatched)} src/library.csv functions are not in our build: `check.py library` lists them")
    lost = runner.unmatched_annotations(functions)
    if lost:
        print(f"FAIL {len(lost)} annotations in src/ name no symbol in our build:")
        for line in lost[:ci.MAX_LINES]:
            print(f"     {line}")
    return not lost


def check_regressions(baseline: dict, current: dict) -> bool:
    """Print each score that dropped below the baseline. False if one did."""
    regressions = scoring.find_regressions(baseline, current)
    if regressions:
        print(f"FAIL {len(regressions)} score(s) dropped against {progress.SUMMARY_JSON.relative_to(ROOT)}:")
        for line in regressions:
            print(f"     {line}")
    return not regressions


def score_game(game: Path) -> dict | None:
    """Score every function, as a new summary.json. None if an annotation names no symbol or a score dropped below summary.json."""
    html = project.BUILD / "report.html"
    build = runner.game_build()
    functions = runner.score_target(build, game, "--html", str(html))
    current = runner.summarize(build.target, functions)
    stats = scoring.totals(current, progress.game_addresses(progress.load_functions()))
    print(f"     {scoring.stats_line(stats)}")
    if not check_annotations(functions, game):
        return None

    # A new game has no scores yet: every function is new.
    baseline = progress.load_summary() if progress.SUMMARY_JSON.exists() else {"functions": []}
    if not check_regressions(baseline, current):
        return None
    print(f"ok   no score dropped (report: {html.relative_to(ROOT)})")
    return current


def save_scores(scores: dict) -> None:
    """Record the scores and redraw the history and visuals."""
    # Check the README before writing anything, so a bad one can't leave half a save.
    progress.history_markers(progress.README.read_text(encoding="utf-8"))
    scores["exe"] = project.game_config().filename
    scores["inputs_sha256"] = ci.inputs_hash()
    progress.PROGRESS.mkdir(parents=True, exist_ok=True)
    progress.SUMMARY_JSON.write_text(json.dumps(scores, indent=1) + "\n", encoding="utf-8", newline="\n")
    progress.write_visuals()
    print(f"     saved {progress.SUMMARY_JSON.parent.relative_to(ROOT)} and README.md")


# Porting

# Rich header product ids of the tools this framework uses. Other ids print as "other".
# The linker counts all /GL objects under one id, picked by the first /GL object it links.
RICH_PRODUCTS = {0x93: "import library", 0x9A: "resources", 0x9C: "import library", 0x9D: "linker", 0x9E: "MASM",
                 0xAA: "C", 0xAB: "C++", 0xAE: "/GL, C first", 0xAF: "/GL, C++ first"}
COMPILER_PRODUCTS = {0xAA, 0xAB, 0xAE, 0xAF}  # the ids of objects that cl.exe compiled
SUBSYSTEMS = {2: "GUI", 3: "console"}


def is_dll(header: pe.Header) -> bool:
    return bool(header.characteristics & 0x2000)


def probe(path: Path) -> int:
    """Print what a new game's exe tells docs/PORTING.md, and the game files it suggests."""
    header = pe.read_header(path)
    rich = pe.rich_entries(path)
    sha256 = osutil.sha256(path)
    our_build = int(toolchain.CL_VERSION.split(".")[2])
    builds = {build for product, build in rich if product in COMPILER_PRODUCTS}

    print_header(path, header, sha256)
    print_rich(rich)
    if our_build not in builds:
        print(f"Compiler:   no C or C++ object of build {our_build}. This framework's compiler did not build this exe.")
        return 1
    print(f"Compiler:   C or C++ objects of build {our_build}: the framework's VC++ 2010 SP1 compiled at least part of it.")
    if header.machine != pe.MACHINE_I386 or header.subsystem not in SUBSYSTEMS or is_dll(header):
        return 1
    print_game_cmake(header)
    print_reccmp_project(path, sha256)
    return 0


def print_header(path: Path, header: pe.Header, sha256: str) -> None:
    crt = library.runtime_dlls(header.imports)
    print(f"Exe:        {path}{', a DLL: DLLs are not supported' if is_dll(header) else ''}")
    print(f"SHA-256:    {sha256}, {path.stat().st_size:,} bytes")
    print(f"Machine:    0x{header.machine:x}{'' if header.machine == pe.MACHINE_I386 else ', not 32-bit x86: not supported'}")
    print(f"Linker:     {header.linker[0]}.{header.linker[1]}")
    print(f"Subsystem:  {header.subsystem} ({SUBSYSTEMS.get(header.subsystem, 'not supported')})")
    print(f"Sections:   {', '.join(section.name for section in header.sections)}")
    print(f"Imports:    {', '.join(header.imports)}")
    if header.delay_imports:
        print(f"Delay load: {', '.join(delay.dll for delay in header.delay_imports)}")
    print(f"C runtime:  {', '.join(crt) + ' (DLL)' if crt else 'static: no MSVCR*.dll import'}")
    print(f"PDB path:   {header.pdb or 'none'}")


def print_rich(rich: dict[tuple[int, int], int]) -> None:
    print("Rich header: product id, build: objects")
    for (product, build), count in by_build(rich):
        print(f"  0x{product:02x} {RICH_PRODUCTS.get(product, 'other'):15} {build:>6}: {count}")


def link_flags(header: pe.Header) -> list[str]:
    """The link flags are the ones the exe's PE header needs beyond the VC++ 2010 defaults:
    ASLR, NX and terminal-server awareness on, large addresses off, image base 0x400000.
    Each delay-loaded DLL adds /DELAYLOAD.
    """
    flags = []
    if header.characteristics & 0x0020:
        flags.append("/LARGEADDRESSAWARE")
    if not header.dll_characteristics & 0x0040:
        flags.append("/DYNAMICBASE:NO")
    if not header.dll_characteristics & 0x0100:
        flags.append("/NXCOMPAT:NO")
    if not header.dll_characteristics & 0x8000:
        flags.append("/TSAWARE:NO")
    if header.image_base != 0x400000:
        flags.append(f"/BASE:0x{header.image_base:x}")
    return flags + [f"/DELAYLOAD:{delay.dll}" for delay in header.delay_imports]


def print_game_cmake(header: pe.Header) -> None:
    """The suggested game.cmake. Each delay-loaded DLL also adds delayimp.lib. Relocations stay on
    whatever the exe has: CMakeLists.txt keeps them for reccmp."""
    flags = link_flags(header)
    crt = library.runtime_dlls(header.imports)
    print("\nSuggested game.cmake:")
    print(f"# From the exe's PE header: characteristics 0x{header.characteristics:x}, "
          f"DLL characteristics 0x{header.dll_characteristics:x}.")
    if header.subsystem == 2:
        print("set_target_properties(game PROPERTIES WIN32_EXECUTABLE TRUE)")
    if crt:
        print("set_target_properties(game PROPERTIES MSVC_RUNTIME_LIBRARY MultiThreadedDLL)")
    if flags:
        print(f"target_link_options(game PRIVATE {' '.join(flags)})")
    if header.delay_imports:
        print(f"target_link_libraries(game PRIVATE {library.DELAY_LOAD})")


def print_reccmp_project(path: Path, sha256: str) -> None:
    target = re.sub(r"[^A-Z0-9]", "", path.stem.upper()) or "GAME"
    print("\nSuggested reccmp-project.yml (a short target name is better: it goes in every annotation):")
    print("targets:")
    print(f"  {target}:")
    print(f"    filename: {path.name}")
    print("    source_root: src")
    print("    hash:")
    print(f"      sha256: {sha256}")
    print("    data_sources:")
    print("    - src/library.csv")


if __name__ == "__main__":
    if Path(sys.executable) != project.VENV_PYTHON:
        ensure_venv()
        sys.exit(subprocess.call([str(project.VENV_PYTHON), __file__, *sys.argv[1:]]))
    sys.exit(main())
