"""The data files that check.py writes from the exe, for the library, sources and groups commands.

write_library() writes src/library.csv, write_sources() writes data/source-files.csv and
data/classes.csv, and check_groups() recounts the evidence for data/codegen-groups.csv.
"""

import collections
import csv
import sys
from pathlib import Path

import library
import pe
import progress
import project
import sources

ROOT = project.ROOT
LIBRARY_FIELDS = ["address", "name", "symbol", "type"]
SOURCE_FILES_CSV = ROOT / "data" / "source-files.csv"
CLASSES_CSV = ROOT / "data" / "classes.csv"


def write_library(game: Path) -> None:
    """Write src/library.csv: the runtime library functions and globals that tools/library.py finds."""
    ranges = [(group["start"], group["end"]) for group in progress.load_codegen_groups() if group["kind"] == "library"]
    starts = [function["address"] for function in progress.load_functions()]
    header = pe.read_header(game)
    runtime = library.DLL_RUNTIME if library.runtime_dlls(header.imports) else library.STATIC_RUNTIME
    libraries = [project.TOOLCHAIN / "lib" / name
                 for name in (*runtime, *([library.DELAY_LOAD] if header.delay_imports else []))]
    found = library.find(game, library.Layout(starts, ranges), libraries)
    found.rows.extend(library.delay_load_rows(game, project.TOOLCHAIN / "sdk" / "lib"))
    with project.LIBRARY_CSV.open("w", encoding="utf-8", newline="\n") as out:
        out.write("# Written by `check.py library`: the runtime library code in the game. Do not edit.\n")
        writer = csv.writer(out, delimiter="|", lineterminator="\n")
        writer.writerow(LIBRARY_FIELDS)
        writer.writerows([f"0x{row.address:08x}", row.name, row.symbol, row.kind] for row in found.rows)
    counts = collections.Counter(row.kind or "label" for row in found.rows)
    print(f"     {project.LIBRARY_CSV.relative_to(ROOT).as_posix()}: "
          + ", ".join(f"{count} {kind}" for kind, count in sorted(counts.items())))
    for address, name in sorted(found.game_calls.items()):
        print(f"     The runtime calls the game's {name} at 0x{address:08x}. Annotate {name} in src/ with that address.")


def check_groups(game: Path) -> int:
    """Recount the tells behind each row of data/codegen-groups.csv. tools/groups.py says how."""
    # Only .venv has capstone.
    import groups

    rows = project.library_rows()
    if not rows:
        sys.exit("src/library.csv is empty: run check.py library first. The count needs its names.")
    names = {row.address: row.symbol for row in rows if row.kind in ("library", "") and row.symbol}
    return groups.report(game, names)


def write_source_files(paths: dict) -> list[tuple[int, str]]:
    """Write data/source-files.csv and return its rows: the functions that use each source path."""
    files = sorted({(use.function, path) for path, uses in paths.items() for use in uses if use.function is not None})
    with SOURCE_FILES_CSV.open("w", encoding="utf-8", newline="") as out:
        writer = csv.writer(out, lineterminator="\n")
        writer.writerow(["function", "file"])
        writer.writerows([f"0x{function:08x}", path] for function, path in files)
    return files


def write_classes(tables: list) -> None:
    """Write data/classes.csv: each class's vtable, methods and users."""
    with CLASSES_CSV.open("w", encoding="utf-8", newline="") as out:
        writer = csv.writer(out, lineterminator="\n")
        writer.writerow(["vtable", "class", "offset", "methods", "users"])
        for table in tables:
            users = sorted({use.function for use in table.uses if use.function is not None})
            writer.writerow([f"0x{table.address:08x}", table.type, table.offset,
                             " ".join(f"0x{method:08x}" for method in table.methods),
                             " ".join(f"0x{user:08x}" for user in users)])


def write_sources(game: Path) -> int:
    """Write data/source-files.csv and data/classes.csv: what tools/sources.py reads from the exe."""
    functions = progress.load_functions()
    paths, tables = sources.find(game, [(function["address"], function["size"]) for function in functions])
    files = write_source_files(paths)
    write_classes(tables)
    print(f"     {SOURCE_FILES_CSV.relative_to(ROOT).as_posix()}: {len(files)} functions, {len(paths)} files")
    print(f"     {CLASSES_CSV.relative_to(ROOT).as_posix()}: {len(tables)} vtables")
    outside = sorted({use.site for uses in [*paths.values(), *(table.uses for table in tables)]
                      for use in uses if use.function is None})
    if outside:
        print(f"note {len(outside)} uses sit in no function of {progress.FUNCTIONS_CSV.relative_to(ROOT).as_posix()}, "
              "so Ghidra missed their functions: " + " ".join(f"0x{site:08x}" for site in outside))
    return 0
