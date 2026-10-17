"""Run reccmp on a build and read back its scores, for check.py.

reccmp runs in a folder that holds a reccmp-build.yml (our binary and its PDB), a
constants.csv and a sizes.csv. write_build_yml() and write_constants() make them. write_user_yml() writes
the reccmp-user.yml that says where the original binary is. score_target() runs reccmp
there and returns the score of each function.
"""

import json
import re
import sys
from pathlib import Path
from typing import NamedTuple

import codegen
import library
import osutil
import pe
import progress
import project

CONSTANTS_CSV = project.BUILD / "constants.csv"  # the game's constants, which reccmp() adds
SIZES_CSV = project.BUILD / "sizes.csv"  # the size of each game function, which reccmp() sets
FUNCTION_TYPE = 1  # reccmp EntityType.FUNCTION


class Build(NamedTuple):
    """A reccmp target that was built: where reccmp runs, and what it compares."""
    target: str
    project: Path  # the folder with the target's reccmp-project.yml
    ours: Path  # our binary
    folder: Path  # where reccmp runs: its reccmp-build.yml, constants.csv and sizes.csv are here


def game_build() -> Build:
    return Build(project.game_config().target, project.ROOT, project.OUR_GAME, project.BUILD)


def write_user_yml(path: Path, target: str, original: Path) -> None:
    """reccmp's per-machine path to an original binary."""
    lines = ["# Written by tools/check.py: where the original binary is on this machine.", "targets:",
             f"  {target}:", f"    path: {json.dumps(original.as_posix())}"]
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def write_build_yml(build: Build) -> None:
    """reccmp's pointer from the folder it runs in to its project, our binary and its PDB."""
    lines = [f"project: {json.dumps(build.project.as_posix())}", "targets:", f"  {build.target}:",
             f"    path: {json.dumps(build.ours.as_posix())}",
             f"    pdb: {json.dumps(build.ours.with_suffix('.pdb').as_posix())}"]
    build.folder.mkdir(exist_ok=True)
    (build.folder / "reccmp-build.yml").write_text("\n".join(lines) + "\n", encoding="utf-8")


def write_constants(game: Path) -> None:
    """Write build/constants.csv, the floats and strings the game's code uses, and build/sizes.csv,
    the size of each game function. tools/constants.py says why."""
    # Only .venv has reccmp and capstone, like ruamel.
    import constants

    groups = progress.load_codegen_groups()
    rows = progress.load_functions()
    functions = []
    for function in rows:
        group = progress.codegen_group(groups, function["address"])
        pools = group is not None and codegen.pools_strings(group["flags"].split())
        functions.append(constants.Function(function["address"], function["size"], pools))
    write_constants_csv(CONSTANTS_CSV, game, functions)
    game_code = progress.game_addresses(rows)
    write_sizes_csv(SIZES_CSV, [(row["address"], row["size"]) for row in rows if row["address"] in game_code])


def write_sizes_csv(path: Path, spans: list[tuple[int, int]]) -> None:
    """Write the size of each function, for reccmp() to set."""
    lines = ["address|size"] + [f"0x{address:08x}|{size}" for address, size in spans]
    osutil.write_if_changed(path, "\n".join(lines) + "\n")


def write_constants_csv(path: Path, exe: Path, functions: list) -> None:
    """Write the constants that the functions' code uses, for reccmp() to add."""
    import constants

    lines = ["address|type|size"] + [f"0x{found.address:08x}|{found.kind}|{found.size}"
                                     for found in constants.find(exe, functions)]
    osutil.write_if_changed(path, "\n".join(lines) + "\n")


def require_our_game() -> None:
    """Some antivirus tools quarantine a new exe a few seconds after the link, so check before reading it."""
    if not project.OUR_GAME.exists():
        sys.exit(f"{project.OUR_GAME.relative_to(project.ROOT)} is gone after the build. "
                 "An antivirus may have quarantined it: see docs/FRAMEWORK.md#antivirus-false-positives.")


def reccmp(*args: str, cwd: Path) -> tuple[str, list[str]]:
    """Run reccmp in a folder that has a reccmp-build.yml, with the constants.csv and sizes.csv there.
    Return its stdout and its log from stderr, one entry per message, without the [INFO] ones."""
    result = project.run([project.VENV_PYTHON, project.ROOT / "tools" / "constants.py", *args], cwd=cwd)
    # A message's lines after its first don't start with "[".
    messages = re.split(r"\n(?=\[)", result.stderr.strip())
    return result.stdout, [message for message in messages if message and not message.startswith("[INFO]")]


def score_target(build: Build, original: Path, *extra: str) -> dict[int, dict]:
    """Score a target, print reccmp's log and return the function entries keyed by original address.

    reccmp's stdout summary is dropped: callers print their own, shorter one.
    Only entries at code addresses count: reccmp types a symbol with "@" and no leading "?" as a function,
    so throw info such as __TI2?AVbad_exception@std@@ also gets a score.
    """
    report = build.folder / f"{build.target}.json"
    _, log = reccmp("--target", build.target, "--json", str(report), "--json-diet", "--silent", *extra,
                    cwd=build.folder)
    data = json.loads(report.read_text(encoding="utf-8"))
    image = pe.Image(original)
    functions = {int(entry["address"], 16): entry for entry in data["data"]
                 if entry.get("type") in (None, FUNCTION_TYPE) and image.is_code(int(entry["address"], 16))}
    for message in log:
        if not harmless_ambiguity(message, functions):
            print(message)
    return functions


def harmless_ambiguity(message: str, functions: dict[int, dict]) -> bool:
    """reccmp warns "Ambiguous match" when a name fits two symbols.
    A 100% score shows that it took the right one."""
    ambiguous = re.search(r"Ambiguous match 0x([0-9a-f]+) ", message)
    return ambiguous is not None and functions.get(int(ambiguous[1], 16), {}).get("matching") == 1.0


def unmatched_library_rows(functions: dict[int, dict], game: Path) -> dict[int, str]:
    """The function rows of src/library.csv that reccmp found nothing for in our build, as address: name.

    Function rows only: reccmp's report holds no globals, so a wrong global name
    shows only in the score of a function that uses it. Import stubs don't count either:
    reccmp needs their rows to name the calls to them, but reports no stubs.
    """
    missing = {row.address: row.name for row in project.library_rows()
               if row.kind == "library" and row.address not in functions}
    if not missing:
        return {}
    original = pe.Image(game)
    return {address: name for address, name in missing.items() if original.read(address, 2) != library.IMPORT_JUMP}


def function_annotations() -> list[tuple[int, str]]:
    """The FUNCTION, STUB, LIBRARY, TEMPLATE and SYNTHETIC annotations in src/, as (address, where)."""
    # reccmp is in .venv, which the first run of this script makes after this module loads.
    from reccmp.dir import source_code_search
    from reccmp.formats import TextFile
    from reccmp.parser import DecompCodebase

    codebase = DecompCodebase(TextFile.from_files(source_code_search(project.ROOT / "src")),
                              project.game_config().target)
    annotated = [*codebase.iter_line_functions(), *codebase.iter_name_functions()]
    return [(symbol.offset, f"0x{symbol.offset:08x}: {Path(symbol.filename).relative_to(project.ROOT).as_posix()} "
                            f"line {symbol.line_number}") for symbol in annotated]


def unmatched_annotations(functions: dict[int, dict]) -> list[str]:
    """The function annotations in src/ that reccmp found no symbol for in our build.

    reccmp drops them quietly: a LIBRARY name that is no symbol, or a FUNCTION line it can't find.
    """
    return [where for address, where in function_annotations() if address not in functions]


def misplaced_annotations() -> list[str]:
    """The function annotations in src/ whose address starts no game function in data/functions.csv.

    reccmp scores such a function on whatever bytes are there, and the totals count it as game code.
    """
    game_code = progress.game_addresses(progress.load_functions())
    return [f"{where}: not the start of a game function in data/functions.csv"
            for address, where in function_annotations() if address not in game_code]


def unmatched_library_note(address: int, name: str) -> str:
    return f"0x{address:08x} {name}: this src/library.csv name is not a symbol in our build"


def summarize(target: str, scored: dict[int, dict]) -> dict:
    functions = [
        {
            "address": f"0x{address:08x}",
            "name": entry["name"],
            "accuracy": entry["matching"],
            "effective": bool(entry.get("effective")),
            "stub": bool(entry.get("stub")),
            "library": bool(entry.get("library")),
        }
        for address, entry in sorted(scored.items())
    ]
    return {"target": target, "functions": functions}
