"""The output of `check.py fn` and `check.py library`: what each function scored.

score_functions() prints one line per function and the instruction diff of each miss.
score_library() counts the runtime library functions that match.
"""

from pathlib import Path

import project
import runner
import tricks


def score_functions(addresses: list[int], game: Path) -> int:
    """One line per function, a diff only for misses. Exit 0 only when all match."""
    runner.require_our_game()
    functions = runner.score_target(runner.game_build(), game)
    unmatched = runner.unmatched_library_rows(functions, game)
    tricked = {address: reasons for address, (_, reasons) in tricks.scan(project.ROOT).items()}
    matched = 0
    for address in addresses:
        if report_function(address, functions.get(address), unmatched.get(address), tricked.get(address)):
            matched += 1
    if len(addresses) > 1:
        print(f"{matched} / {len(addresses)} match.")
    return 0 if matched == len(addresses) else 1


def report_function(address: int, entry: dict | None, unmatched_library_name: str | None, trick: str | None) -> bool:
    """True for a match: 100% in plain C. TRICK is why tools/tricks.py finds a trick in the function, or None."""
    if unmatched_library_name is not None:
        print(f"{runner.unmatched_library_note(address, unmatched_library_name)}.")
        return False
    if entry is None:
        print(f"0x{address:08x}: no FUNCTION/STUB annotation, and no LIBRARY annotation or src/library.csv row "
              "whose name is a symbol in our build.")
        return False
    label = f"0x{address:08x} {entry['name']}"
    if entry.get("stub"):
        print(f"{label}: stub. Replace STUB with FUNCTION once it has a body.")
        return False
    if entry["matching"] == 1.0 and trick is not None:
        print(f"{label}: 100%, but only through a trick ({trick}). It does not count as matched until it is plain C.")
        return False
    if entry["matching"] == 1.0:
        print(f"{label}: 100% match.")
        return True
    report_miss(address, entry, label)
    return False


def report_miss(address: int, entry: dict, label: str) -> None:
    """Print the instruction diff of a function that is not at 100%."""
    # The log is the one score_target printed for this build.
    diff, _ = runner.reccmp("--target", project.game_config().target, "--verbose", hex(address), "--print-rec-addr",
                            "--no-color", cwd=project.BUILD)
    print(diff.strip())
    print(f"{label}: {entry['matching']:.2%} match. Diff above (- original, + ours).")
    if entry.get("effective"):
        print(f"{label}: reccmp calls this an effective match. Its check is loose and does not prove "
              "the same behavior, so read the diff.")


def score_library(game: Path) -> int:
    """Score every function in src/library.csv. Exit 0 only when all of them match."""
    runner.require_our_game()
    functions = runner.score_target(runner.game_build(), game)
    unmatched = runner.unmatched_library_rows(functions, game)
    problems = [runner.unmatched_library_note(address, name) for address, name in unmatched.items()]
    scored = [(row, functions[row.address]) for row in project.library_rows()
              if row.kind == "library" and row.address in functions]
    problems += [f"0x{row.address:08x} {row.name}: {entry['matching']:.2%}"
                 for row, entry in scored if entry["matching"] != 1.0]
    for line in problems:
        print(f"     {line}")
    total = len(scored) + len(unmatched)
    print(f"{total - len(problems)} / {total} library functions match.")
    return 1 if problems else 0
