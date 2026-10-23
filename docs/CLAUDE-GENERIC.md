# Decomp framework: working rules for Claude

This is a matching decompilation of one 32-bit Windows exe. It uses a generic framework. Root `CLAUDE.md` imports this file (framework rules) and adds game facts.

- docs/FRAMEWORK.md: explains the framework and lists the framework files and the game files.
- docs/PORTING.md: playbook for a new game. Follow it when the user asks for a port.
- `<TARGET>`: the one target name in `reccmp-project.yml`.

## Commands

Run each command from the repo root. Each command first sets up what it needs (`.venv`, `.toolchain` compiler, game path). Then it runs inside `.venv`. It shows tool output on failure only. It also shows compiler and reccmp warnings.

- `python tools/check.py setup [--game PATH]`: run once per clone. It finds the game in a Steam library or takes `--game`. It enables the pre-commit and pre-push hooks.
- `python tools/check.py fn 0x<addr> [0x<addr> ...]`: builds once and prints one line per function. Exit 0 means every function matches 100%. A miss prints a diff: `-` shows the original, `+` shows ours. reccmp calls some misses an effective match, but its check is loose. Read the diff.
- `python tools/check.py decls`: writes `src/include/types.h`, `functions.h`, `globals.h`, `src/unplaced/stubs.cpp` and `globals.cpp` from the names the sources use. Run it after a source starts to use a new name. Exit 1 shows one of two faults. Either a used name has no declaration the command can make, or two functions get the same name.
- `python tools/check.py dossier 0x<addr> [--c] [--callers] [--accesses]`: shows what you need to write a function. That is the prototype, code group, assembly with names, and declarations of the names the function uses. `--c` adds Ghidra's draft C from `build/decomp` (docs/FRAMEWORK.md, Function list). `--accesses` shows how the whole exe reads and writes each global that the function names.
- `python tools/check.py access 0x<addr> [--size N]`: lists every read and write of a global in the exe, by offset, size, int or float. Use it to check the type or name of a global. For example, a 4-byte float read does not fit a `char`.
- `python tools/check.py clone 0x<addr> [...] [--all] [--tables DIR]`: writes the copies of a 100% function: same instructions, other calls and globals. Each copy gets the template's code and the copy's names. Then the command keeps only the copies at 100%. It prints one line per copy. The line for a skipped copy says why. With `--all`, every 100% function is a template.
- `python tools/check.py ci`: runs the checks that need no game: annotation lint, self-test in `tests/selftest`, `tools/ci.py`. CI runs it. Lint fails any function annotation that is not at the start of a game function in `data/functions.csv`. A `STUB` can start any function there. Lint also fails a `FUNCTION` or `STUB` definition with no line holding only `}` before the next one. It exits 1, as `areas` does, when a file in a new folder under `src/` has no tree line.
- `python tools/check.py gate`: runs `ci` plus the Rich header check, every game score, and a check that `data/functions.csv` covers all code. Exit 1 means a check fails or a function scores lower than its score in `docs/progress/summary.json`. The pre-push hook runs it.
- `python tools/check.py save`: it first saves a new baseline, rebuilds `docs/progress/history.csv` from the commits, and redraws SVGs in light and dark. Then it runs `gate`. The history file has one row per commit that changed the totals. The commit being made counts as today's. The pre-commit hook runs it. It saves nothing unless annotation lint, self-test, Rich header check and annotation check pass and no score drops. It exits 1, as `areas` does, when a file in a new folder under `src/` has no tree line.
- `python tools/check.py link [FILE ...]`: links the game's exe from its own bytes with each FILE's object swapped in. Exit 0 means the result is the game's exe, byte for byte. A file with data of its own, other than a float or string literal, can't be swapped in yet.
- `python tools/check.py library`: finds runtime library code in the game, writes `src/library.csv` and scores the code. Run it after a change to `data/functions.csv` or to the `library` ranges in `data/codegen-groups.csv`.
- `python tools/check.py sources`: uses exe paths and class names to tie functions to source files (`data/source-files.csv`) and classes (`data/classes.csv`). Run it after `data/functions.csv` changes.
- `python tools/check.py groups`: prints evidence for each row of `data/codegen-groups.csv` and writes `data/file-clusters.csv`. Exit 1 means a function has a tell that its row's flags cannot produce. Run it after a change to `data/functions.csv`, to `src/library.csv` or to a row.
- `python tools/check.py areas`: sorts game functions into areas (`data/areas.yml`) and writes the exe's guess to `data/areas.csv`. Exit 1 means a file in a new folder under `src/` has no tree line. Add one in `data/areas.yml`.
- `python tools/check.py probe <exe>`: reads the exe headers and suggests its game files. It needs no game setup.

## Loop for one function

1. Read the original with REA tools. First use `open_binary` on the exe path in `reccmp-user.yml`. Then use `analyze_function` or `procedure_assembly` at the address. A big exe opens slowly, so keep one session open.
2. Write the source under `src/`. Name and place it as docs/STYLE.md says. Until you know the real file, use `src/unplaced/FUN_<address>` with the extension that docs/STYLE.md sets. Put the annotation on the line directly above the function:
   ```cpp
   // FUNCTION: <TARGET> 0x00401000
   ```
   - Unwritten callee: put `// STUB: <TARGET> 0x...` above an empty-body function in its own file. In the caller's file, the compiler drops the call to an empty function, even with inlining off (`/Ob0`).
   - Global: put `// GLOBAL: <TARGET> 0x...` above its definition.
   - String literal or float constant: add no annotation. `check.py` finds the game's literal or constant in the game's code. Exception: add `// STRING: <TARGET> 0x...` for a wide literal (`L"..."`) of one character or with a character outside Latin-1. Put the annotation on the line above a line that holds the literal.
   - Runtime library code from `.toolchain` (such as the CRT): add no annotation. `check.py library` writes the rows for it. Never edit `src/library.csv`. The build links no other prebuilt library, so middleware stays a `library` range in `data/codegen-groups.csv`.
   - Header function with one kept copy in game code: its callers on the game's side show an address placeholder. Annotate it by hand in a header under `src/`, such as `src/header-functions.h`. Write `// LIBRARY: <TARGET> 0x...`, then `// <name>` on the next line. The Traps section in docs/PORTING.md says which name to use.
3. Run `check.py fn 0x...` until it exits 0. Change the source, not the compiler flags. If a function cannot match, keep the closest version and say why in a comment above it.
4. Run `check.py save`. It must exit 0 before you finish.

## Rules

- Never add game files to the repo (`.exe`, `.dll`, game data, disassembly dumps, HTML reports). The repo ignores `build/` for this.
- Compiler flags come from `data/codegen-groups.csv`, one set per code group. A file gets the flags of the group that its `FUNCTION`, `TEMPLATE` and `SYNTHETIC` annotations belong to. They must all belong to one group. `STUB`, `GLOBAL` and `LIBRARY` annotations do not count. Change the flags of a group only with evidence from functions in that group. Then run `gate`.
- Never hand-edit `summary.json`, `history.csv`, or SVGs in `docs/progress`. CI catches an edited SVG or history line and any score drop. CI has no game, so it can't catch a raised score. Only `gate` checks the scores.
- Write annotation addresses as `0x` plus 8 lower-case hex digits, for example `0x0040a1f0`.
- Put game facts in the game files that docs/FRAMEWORK.md lists, never in framework files.
- Never fetch tcrf.net or other bot-walled fan wikis.
- Known limit: reccmp's README (pinned version) names no supported compilers. Only the self-test shows that reccmp works with VC++ 2010 SP1.
