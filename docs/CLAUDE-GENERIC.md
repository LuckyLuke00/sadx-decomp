# Decomp framework: working rules for Claude

Matching decompilation of one 32-bit Windows exe on a generic framework. Root `CLAUDE.md` imports this file (framework rules) and adds game facts.

- docs/FRAMEWORK.md: explains framework, lists its files and game files.
- docs/PORTING.md: new-game playbook. Follow it when user asks for a port.
- `<TARGET>`: the one target name in `reccmp-project.yml`.

## Commands

Run from repo root. Every command first sets up its needs (`.venv`, `.toolchain` compiler, game path), then runs inside `.venv`. Output: tool output on failure only, plus compiler and reccmp warnings.

- `python tools/check.py setup [--game PATH]`: once per clone. Finds game in a Steam library or takes `--game`, enables the pre-commit and pre-push hooks.
- `python tools/check.py fn 0x<addr> [0x<addr> ...]`: builds once, one line per function. Exit 0: all 100% matches. Miss prints diff: `-` original, `+` ours. reccmp calls some misses an effective match, but its check is loose: read diff.
- `python tools/check.py decls`: writes `src/include/types.h`, `functions.h`, `globals.h`, `src/unplaced/stubs.cpp` and `globals.cpp` from names the sources use. Run after a source starts using a new name. Exit 1: a used name has no declaration it can make, or two functions would share a name.
- `python tools/check.py dossier 0x<addr> [--c] [--callers] [--accesses]`: what writing a function takes: prototype, code group, assembly with names, declarations of names it uses. `--c`: Ghidra's draft C from `build/decomp` (docs/FRAMEWORK.md, Function list). `--accesses`: how the whole exe reads and writes each global it names.
- `python tools/check.py access 0x<addr> [--size N]`: every read and write of a global in the exe, by offset, size, int or float. Use it to check a global's type or name: a 4-byte float read does not fit a `char`.
- `python tools/check.py ci`: no-game checks: annotation lint, self-test in `tests/selftest`, `tools/ci.py`. CI runs it. Lint fails any function annotation not at the start of a game function in `data/functions.csv`.
- `python tools/check.py gate`: `ci`, plus Rich header check, every game score, check that `data/functions.csv` covers all code. Exit 1: a check failed or a function scored lower than in `docs/progress/summary.json`. Pre-push hook runs it.
- `python tools/check.py save`: `gate`, but first saves new baseline, rebuilds `docs/progress/history.csv` from the commits (one row per commit that changed a score, plus the commit being made), redraws SVGs and README table. The pre-commit hook runs it. Saves nothing unless annotation lint, self-test, Rich header check and annotation check pass and no score dropped.
- `python tools/check.py library`: finds runtime library code in game, writes `src/library.csv`, scores it. Run after `data/functions.csv` or `library` ranges in `data/codegen-groups.csv` change.
- `python tools/check.py sources`: ties functions to source files (`data/source-files.csv`) and classes (`data/classes.csv`) from exe paths and class names. Run after `data/functions.csv` changes.
- `python tools/check.py groups`: prints evidence for each row of `data/codegen-groups.csv`, writes `data/file-clusters.csv`. Exit 1: a function has a tell its row's flags could not have made. Run after `data/functions.csv`, `src/library.csv` or a row changes.
- `python tools/check.py probe <exe>`: reads exe headers, suggests its game files. Needs no game setup.

## Loop for one function

1. Read original with REA tools: `open_binary` on exe path in `reccmp-user.yml`, then `analyze_function` or `procedure_assembly` at the address. Big exes open slowly: keep one session open.
2. Write source under `src/`, named and placed per docs/STYLE.md. Until real file is known, use `src/unplaced/FUN_<address>` with the extension docs/STYLE.md sets. Annotate on the line directly above the function:
   ```cpp
   // FUNCTION: <TARGET> 0x00401000
   ```
   - Unwritten callee: `// STUB: <TARGET> 0x...` above an empty-body function in its own file. In the caller's file the compiler drops the call to an empty function, even with inlining off (`/Ob0`).
   - Global: `// GLOBAL: <TARGET> 0x...` above its definition.
   - String literal or float constant: no annotation, `check.py` finds the game's in its code. Exception: a wide literal (`L"..."`) of one character or with a character outside Latin-1 needs `// STRING: <TARGET> 0x...` on the line above a line that holds it.
   - Runtime library code from `.toolchain` (such as the CRT): no annotation, `check.py library` writes its rows. Never edit `src/library.csv`. No other prebuilt library is linked, so middleware stays a `library` range in `data/codegen-groups.csv`.
   - Header function with one kept copy in game code: shows as an address placeholder in its callers on the game's side. Annotate by hand in a header under `src/`, such as `src/header-functions.h`: `// LIBRARY: <TARGET> 0x...`, then `// <name>` on the next line. docs/PORTING.md Traps says which name.
3. Run `check.py fn 0x...` until it exits 0. Change source, not compiler flags. If a function cannot match, keep closest version and say why in a comment above it.
4. Run `check.py save`. It must exit 0 before you finish.

## Rules

- Never add game files to the repo (`.exe`, `.dll`, game data, disassembly dumps, HTML reports). `build/` is ignored for this.
- Compiler flags come from `data/codegen-groups.csv`, one set per code group. A file gets the flags of the group its `FUNCTION`, `TEMPLATE` and `SYNTHETIC` annotations are in, so they must all be from one group. `STUB`, `GLOBAL` and `LIBRARY` don't count. Change a group's flags only with evidence from functions in that group, then run `gate`.
- Never hand-edit `summary.json`, `history.csv`, SVGs in `docs/progress` or the README's recent-changes table. CI rejects it.
- Write annotation addresses as `0x` plus 8 lower-case hex digits, for example `0x0040a1f0`.
- Game facts go in the game files docs/FRAMEWORK.md lists, never in framework files.
- Never fetch tcrf.net or other bot-walled fan wikis.
- Known limit: reccmp's README (pinned version) names no supported compilers. Only the self-test shows it works with VC++ 2010 SP1.
