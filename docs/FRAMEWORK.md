# The decomp framework

The framework builds a matching decompilation of one 32-bit Windows exe. It compiles the source with the exe's own compiler and scores every function against the original. Nothing in it is game-specific: each game's facts live in a few game files. This repo's game is in [README.md](../README.md). To start a new game, follow [PORTING.md](PORTING.md).

## What it supports

- One 32-bit x86 Windows exe with a GUI or console subsystem. DLLs are not supported.
- Code built with Visual C++ 2010 SP1 (`cl.exe` 16.00.40219.01). `check.py probe` says whether an exe qualifies. PORTING.md says what another compiler takes.
- An exe with a Rich header, which Microsoft's linker writes. `probe` and `gate` stop without one.
- A static or DLL C runtime (`MSVCR100.dll`). The DLL runtime is tested on three small test exes only.
- The headers and libraries in `.toolchain`, which hold no D3DX, MFC or ATL. PORTING.md says what a game that uses them takes.
- Windows 10 build 17063 or newer (has `tar.exe`), Python 3.10 or newer and git. Every command is tested on Windows 11 with Python 3.13. CI is set to run `ci` with Python 3.12 on GitHub's latest Windows image, but has not run yet.

## Framework files and game files

| Framework: the same in every game | Game: written for each game |
| --- | --- |
| `tools/`, `tests/`, `.github/`, `.githooks/` | `CLAUDE.md`, `README.md` |
| `CMakeLists.txt`, `requirements.txt` | `reccmp-project.yml`, `game.cmake` |
| `.gitignore`, `.gitattributes` | `src/`, `data/` |
| `docs/CLAUDE-GENERIC.md`, `docs/FRAMEWORK.md`, `docs/PORTING.md` | `docs/STYLE.md`, `docs/progress/` |

To update a game's copy of the framework, run the copy command in [PORTING.md](PORTING.md#3-make-the-repo) step 3 without its `mkdir`, `git init` and `git add` lines. It only copies, so delete by hand any file the framework dropped. Rerun the [Ghidra command](#function-list) if the copy changed `tools/ghidra`. Rerun `check.py library` if it changed `tools/library.py` or `tools/libobjects.py`, or if the function list changed. Then run `check.py gate`, which fails after the copy changed a build input such as `CMakeLists.txt` or `tools/check.py` until `check.py save` records the scores again. Framework files quote SADX only as worked examples.

The game files:

| File | What it holds |
| --- | --- |
| `reccmp-project.yml` | reccmp's target: the target name, the exe's filename and SHA-256, the source folder and the data sources. It must hold exactly one target. The name goes in every annotation, and reccmp's lint accepts capitals and digits only. |
| `game.cmake` | Build settings for the `game` target, which `CMakeLists.txt` adds with the framework's flags before including this file: PE header link flags, the subsystem, and any include folders, defines or runtime choice. |
| `data/functions.csv` | Every function Ghidra finds in the exe's code, except imported functions and their jmp stubs. |
| `data/codegen-groups.csv` | Code groups: address ranges with their compiler flags and the evidence for them. |
| `data/file-clusters.csv` | Functions in one row of `data/codegen-groups.csv` that pass each other register arguments. Without `/GL` such a call stays inside one source file, so a cluster mostly shares a file. Two things join files: `/GL`, and the linker folding identical `static` functions, which sends a call to another file's copy. |
| `data/source-files.csv`, `data/classes.csv` | Functions that use each source path in the exe, and each class's vtable, methods and users. `check.py sources` writes them. |
| `src/library.csv` | Runtime library functions and their globals, matched by name. |
| `src/header-functions.h` | `LIBRARY` annotations for header functions the linker kept in game code, such as `swprintf`. Written by hand in a header, since the lint rejects them in a `.cpp`. |
| `CLAUDE.md` | Imports `docs/CLAUDE-GENERIC.md`, then adds the game's facts for Claude. |
| `README.md` | The game's page. It needs the `<!-- history:start -->` and `<!-- history:end -->` markers for the recent-changes table. |
| `docs/STYLE.md` | Naming, file layout and language, with the evidence. |
| `docs/progress/` | Scores, history and visuals. |

## How accuracy is measured

Each decompiled function has a comment with its address in the original exe. `<TARGET>` is the target name in `reccmp-project.yml`:

```cpp
// FUNCTION: <TARGET> 0x00401000
void FUN_00401000(int value)
{
	// ...
}
```

`tools/check.py` compiles the source with the game's own compiler. Then [reccmp](https://github.com/isledecomp/reccmp), the scoring tool from the [LEGO Island decompilation](https://github.com/isledecomp/isle), disassembles both copies of every annotated function and compares the instructions.

| Figure | Meaning |
| --- | --- |
| Score | The share of instructions the same in both copies. The game's copy runs to the end of its row in `data/functions.csv`, so code ours lacks at the end counts as a miss. Calls and globals compare by name, so a function can match at another address in our exe. |
| Matched | A score of 100%. reccmp also calls some misses an *effective* match (other registers or another instruction order), but its check is loose and can pass code that behaves differently. So an effective match keeps its score and the totals count it apart as *effective*. |
| Decompiled | The share of game functions that have a body. Stubs do not count. |
| Accuracy | The average score of the decompiled functions. |

Constants compare by value. reccmp finds a float or string literal only where a relocation marks the operand as an address. Our exe keeps relocations (`/FIXED:NO`) and the game's has none, so after each build `check.py` reads the game's code and writes the floats and strings it uses to `build/constants.csv`. reccmp adds these rows after matching, along with the constants it finds itself, so a variable's name still wins. A row with no name covers an address our PDB doesn't name either, such as a compiler-made exception handler stub. [tools/constants.py](../tools/constants.py) has the rules. Literals and floats need no annotation, except a wide literal of one character or with a character outside Latin-1: docs/CLAUDE-GENERIC.md says how.

**Game functions** are the functions in `data/functions.csv` in a `game` range of `data/codegen-groups.csv`. Functions in `library` ranges do not count, nor does compiler-made code such as the `Unwind@` funclets, which gets a `library` range of its own. A function's catch blocks and the filters and handlers of its SEH `__try` blocks are part of it. Runtime functions listed in `src/library.csv` and game functions with a `LIBRARY` annotation show apart. Every function annotation must be at the start of a game function, or the annotation lint fails.

The same source always gives the same score. `docs/progress/summary.json` keeps the last accepted score of every function, and `check.py gate` fails if any score drops.

Three checks show that the toolchain is the game's own:

1. **Rich header.** Every tool build that made our exe is also in the game's Rich header (`check.py gate`). Only build numbers compare, since product ids depend on each game's mix of C, C++ and `/GL` objects. If an import library fails it, [PORTING.md](PORTING.md#import-libraries) has the fix.
2. **Runtime library.** A CRT function from `src/library.csv` that scores 100% shows our copy of the library is the game's.
3. **Self-test.** A small known program in `tests/selftest` builds to the same SHA-256 every time, and reccmp scores it exactly as pinned (`check.py ci`).

## Commands

`tools/check.py` is the single entry point. Only `python tools/progress.py` runs on its own: it redraws the SVGs in `docs/progress` and the README table from the saved files, as `save` does. Every command first sets up what it needs, then runs itself inside `.venv`. It prints only what matters: tool output shows on failure, and compiler and reccmp warnings always show.

| Command | What it does | Exit code |
| --- | --- | --- |
| `setup [--game PATH]` | Gets the Python packages, the compiler and the game ready, and turns on the pre-push hook | 1 if something is missing |
| `fn 0x00401000 0x00401020` | Builds and scores each function: one line each, plus the instruction diff for misses | 0 only if all match |
| `ci [--base COMMIT]` | Builds and runs every check that needs no game: the annotation lint (reccmp's linter plus a check that every function annotation is at the start of a game function), the self-test and `tools/ci.py` | 1 if any fails |
| `gate` | `ci`, plus the Rich header check, every game function's score with `build/report.html`, and checks that every code byte is in a function of `data/functions.csv`, padding or an import stub, and that every `FUNCTION`, `STUB` and `LIBRARY` annotation names a symbol in our build. The pre-push hook runs it | 1 if any fails or a score dropped |
| `save` | `gate`, then saves the scores, adds a history row if anything changed and redraws the visuals. It saves nothing if the lint, the self-test, the Rich header check or the annotation check fails, or a score dropped | 1 if any fails or a score dropped |
| `library` | Finds the runtime library code, mostly in the `library` ranges of `data/codegen-groups.csv`, writes `src/library.csv` and names the game function the runtime calls, such as `WinMain`. Then it builds and scores those functions | 1 if a function misses |
| `sources` | Writes `data/source-files.csv` and `data/classes.csv` from the source paths and class names in the exe | 0 |
| `groups` | Recounts the tells behind each row of `data/codegen-groups.csv` from the exe, names each function whose tells contradict its row's flags, and writes `data/file-clusters.csv`. Needs `src/library.csv` | 1 if a function contradicts its row |
| `probe EXE` | Reads an exe's PE and Rich headers, and suggests its `game.cmake` and reccmp target. Needs no game setup | 1 if the exe is a DLL, is not 32-bit x86 with a GUI or console subsystem, has no Rich header, or the framework's compiler did not build it |

`setup` finds the game in any Steam library on the machine by the SHA-256 in `reccmp-project.yml`. For a copy from elsewhere, pass `--game`. The path goes in `reccmp-user.yml`, which stays on your machine.

## What setup downloads

Nothing is installed outside the repo: setup unpacks the Microsoft downloads with Windows' own tools and runs none of their installers. pip installs the Python packages from PyPI into `.venv`, and `check.py` runs cmake, ninja and reccmp from there. Setup keeps its files in these folders, which git ignores:

| Folder | Contents |
| --- | --- |
| `.venv` | the Python packages pinned in `requirements.txt` |
| `.toolchain` | the VC++ 2010 SP1 compiler, linker, headers and libraries |
| `build` | the build and `report.html` |

[tools/toolchain.py](../tools/toolchain.py) makes `.toolchain` once. It downloads the Windows SDK 7.1 ISO and the VC++ 2010 SP1 compiler update from Microsoft (722 MB), checks their SHA-256 and unpacks them with `tar.exe`, a read-only mount of the ISO and `msiexec /a`. Then it copies the files the build uses into `.toolchain` and checks the `cl.exe` and `link.exe` versions. The script holds the URLs, file lists and steps.

The downloads wait in `%TEMP%\decomp-toolchain` until this succeeds, so a failed run does not download them again. That path is short on purpose: `msiexec` failed with error 1304 under a long one. A `.toolchain` folder copied from another clone works too, since `toolchain.py` checks it before use.

## Antivirus false positives

Every build links a new, unsigned exe, and an antivirus can flag it. In one port test, Malwarebytes quarantined the bare placeholder `build/game.exe` as `Adware.InstallCore` soon after each link. Later builds of the same placeholder passed.

When `build/game.exe` is gone, `check.py` stops and says it "is gone after the build". During `fn`, reccmp can say it first: "Recompiled binary ... does not exist".

1. Look for `build/game.exe` in the antivirus's detection log.
2. Report the false positive to the vendor. Only the vendor can fix it for every user.
3. Until then, allow the repo's `build` folder in the antivirus. You need not restore the file: the next build links it again.

Do not change the code to get past a detection. The next definitions update can flag it again.

## The self-test

`tests/selftest` is a small known program with its own reccmp project. CMake builds `original.cpp` as `build/selftest-original/SELFTEST.exe`, with no PDB and no relocations, to stand in for a retail exe. `decomp.cpp` is its annotated twin. Both builds also hold `gl-caller.cpp` and `gl-callee.cpp`, compiled with `/GL`. `check.py ci` checks five things:

- The original builds to the SHA-256 pinned in `tests/selftest/reccmp-project.yml`. A change of compiler, libraries or flags breaks it.
- reccmp scores every function exactly as `tests/selftest/expected.json` says: six matches, one near miss, one effective match and one stub. `Scale` and `Name` use a float and a string from the original's data. It has no relocations, so they match only with the constants `check.py` adds. `Total` and `Mix` are the `/GL` pair. `Combine` is the same inline assembly with two registers swapped. reccmp scores it 50% and flags it as an effective match.
- The regression gate passes on equal scores and fires on a deliberate drop.
- The register-argument search of `check.py groups` finds the call from `Total` to `Mix`, which only `/GL` makes, and no other call.
- The totals leave the stub out of the decompiled count, and a library function out of the game total.

A new compiler needs a new pinned hash and new expected scores.

## Continuous integration

GitHub Actions runs [.github/workflows/ci.yml](../.github/workflows/ci.yml) on every pull request and every push to `main` or `master`. Its one job, **CI**, runs `check.py ci` on Windows and caches the compiler download between runs.

CI never sees the game exe, so it can't score game functions itself. `tools/ci.py` covers the gap:

- **Fresh scores.** `summary.json` stores a hash of the build inputs that `tools/ci.py` lists. After any source change, CI fails until a new `summary.json` from `check.py save` is committed, and only a machine with the game can make one.
- **No drops.** No score may fall below the base commit's, and no function may disappear. After a force push, CI has no base commit, but the pre-push hook compared with the old tip.
- **Honest history.** `history.csv` may only gain rows, its last row must equal the totals in `summary.json`, and the SVGs and the README table must equal a fresh render.
- **One group each.** Every function in `data/functions.csv` is in exactly one code group and ends inside it.
- **No game files.** No file with a binary suffix (`.exe`, `.dll`, `.pdb`, `.lib`, `.obj`, `.ilk`, `.iso`, `.msi`) and no file over 10 MB. Other game files, such as a small data file, pass this check.

<details>
<summary>Limits while a repo is private, and settings for later</summary>

- Branch protection on a private repo needs a paid GitHub plan, so until then a failed run shows a red X but does not block a merge.
- `git push --no-verify` skips the pre-push hook.
- Windows minutes cost more than Linux minutes on a private repo. So a push to another branch runs nothing until it has a pull request.
- Once the repo is public (or on a paid plan), add a branch rule for the default branch: require a pull request, require the status check **CI**, and allow no bypass.

</details>

## Function list

Ghidra makes `data/functions.csv` with three scripts in `tools/ghidra`. With Ghidra 12.1 and a 64-bit JDK 21, run this in Git Bash from the repo root:

```bash
JAVA_HOME="<JDK 21 folder>" "<Ghidra folder>/support/analyzeHeadless.bat" "<empty temp folder>" decomp -import "<path to the exe>" -scriptPath tools/ghidra -preScript AnalysisOptions.java -postScript PaddedFunctions.java -postScript ExportFunctions.java data/functions.csv -deleteProject < /dev/null > ghidra.log 2>&1
```

- `AnalysisOptions.java` turns off three guesses of Ghidra's analysis that go wrong in VC++ code: which functions never return, which runs of data are tables of code addresses, and that a function's code is all in one piece. Each wrong guess cuts functions short or makes code of data.
- `PaddedFunctions.java` adds the functions analysis misses and gives functions back the code it cut off. VC++ starts each function at a 16-byte boundary after `int3` padding, except under `/O1`, so such a boundary starts one. Nothing calls an entry of the runtime's tables of initializers and terminators (`__xc_a` to `__xc_z`), so each entry starts one too, and so does an uncalled import stub. A function only an address reaches starts where a code address is pushed, stored, or listed in a table of read-only data. An SEH scope table names the filter and handler of each `__try` block, which are code of the function that pushes the table, so no function starts there. The script repeats its passes until nothing changes. Its header comment has every rule.
- `ExportFunctions.java` writes the list. A row runs from a function's entry up to the padding before the next one, so it holds the function's switch tables. A catch block gets no row.

Headless Ghidra exits 0 even when a script fails, so check `ghidra.log` for `SCRIPT ERROR`. A good run ends its `PaddedFunctions.java` lines with `Created ...`, and `ExportFunctions.java` prints `Exported <N> functions`. Use forward slashes, as Git Bash drops backslashes. Give each run a new empty folder, since a folder another Ghidra still holds fails with `Unable to lock project!`. A failed run waits for a key press, and `< /dev/null` stops that wait. Ghidra's default heap is 2 GB, enough for a 90 MB exe. If Ghidra runs out of memory, set `GHIDRA_HEADLESS_MAXMEM` higher, for example `12G`.
