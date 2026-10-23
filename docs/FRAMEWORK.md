# The decomp framework

The framework builds a matching decompilation of one 32-bit Windows exe. It compiles the source with the exe's own compiler and scores every function against the original. Nothing in it is game-specific. Each game's facts are in a few game files. [README.md](../README.md) describes this repo's game. To start a new game, follow [PORTING.md](PORTING.md).

## What it supports

- One 32-bit x86 Windows exe with a GUI or console subsystem. DLLs are not supported.
- Code built with Visual C++ 2010 SP1 (`cl.exe` 16.00.40219.01). `check.py probe` shows whether an exe qualifies. PORTING.md says what another compiler needs.
- An exe with a Rich header. Microsoft's linker writes it. `probe` and `gate` stop without one.
- A static or DLL C runtime (`MSVCR100.dll`). Only three small test exes test the DLL runtime.
- The headers and libraries in `.toolchain`. They hold no D3DX, MFC or ATL. PORTING.md says what a game that uses them needs.
- Windows 10 build 17063 or newer (it has `tar.exe`), Python 3.10 or newer and git. Testing covers every command on Windows 11 with Python 3.13. The CI workflow runs `ci` with Python 3.12 on GitHub's latest Windows image.

## Framework files and game files

| Framework: the same in every game | Game: written for each game |
| --- | --- |
| `tools/`, `tests/`, `.github/`, `.githooks/` | `CLAUDE.md`, `README.md` |
| `CMakeLists.txt`, `requirements.txt` | `reccmp-project.yml`, `game.cmake` |
| `.gitignore`, `.gitattributes` | `src/`, `data/` |
| `docs/CLAUDE-GENERIC.md`, `docs/FRAMEWORK.md`, `docs/PORTING.md` | `docs/STYLE.md`, `docs/FIRST-FUNCTION.md`, `docs/progress/` |

To update a game's copy of the framework, run the copy command in [PORTING.md](PORTING.md#3-make-the-repo) step 3. Leave out its `mkdir`, `git init` and `git add` lines, because the command only copies. Delete by hand any file the framework dropped. Rerun the [Ghidra command](#function-list) if the copy changed `tools/ghidra`. Rerun `check.py library` in two cases. The first is a copy that changed `tools/library.py` or `tools/libobjects.py`. The second is a changed function list. Then run `check.py gate`. After a copy changes a build input such as `CMakeLists.txt` or `tools/check.py`, `gate` fails until `check.py save` records the scores again. Framework files quote SADX only as worked examples.

The game files:

| File | What it holds |
| --- | --- |
| `reccmp-project.yml` | reccmp's target: the target name, the exe's filename and SHA-256, the source folder and the data sources. It must hold exactly one target. The name goes in every annotation. reccmp's lint accepts capitals and digits only. |
| `game.cmake` | Build settings for the `game` target. `CMakeLists.txt` adds the target with the framework's flags before it includes this file. The settings are PE header link flags, the subsystem, and any include folders, defines or runtime choice. |
| `data/functions.csv` | Every function Ghidra finds in the exe's code, except imported functions and their jmp stubs. |
| `data/codegen-groups.csv` | Code groups: address ranges with their compiler flags and the evidence for them. The build links the files with `FUNCTION` annotations first, by lowest address. The linker keeps the first copy of a header function, so that copy comes from the earliest file, as in the game. |
| `data/file-clusters.csv` | Functions in one row of `data/codegen-groups.csv` that pass each other register arguments. Without `/GL` such a call stays inside one source file, so a cluster mostly shares a file. Two things join files: `/GL`, and the linker folding identical `static` functions. Folding sends a call to another file's copy. Its `callees` column lists the members each function passes register arguments to. |
| `data/source-files.csv`, `data/classes.csv` | Functions that use each source path in the exe, and each class's vtable, methods and users. `check.py sources` writes them. |
| `data/areas.yml`, `data/areas.csv` | The game's areas, such as its stages and characters. `areas.yml` holds the rules: the `tree` lines for source folders, and the exe's tables and strings behind the guess. Its `map` list holds the sections of the progress map and the name the map shows for each area. A `map` section can have a `color`, a quoted `"#rrggbb"`, for the gem before its title. `check.py areas` writes the guess to `areas.csv`. |
| `src/library.csv` | Runtime library functions and their globals, matched by name. |
| `data/llm-hints.txt` | Optional. The game's facts for the system prompt of `tools/llm.py`, such as which release the exe is. |
| `src/header-functions.h` | `LIBRARY` annotations for header functions the linker kept in game code, such as `swprintf`. Written by hand in a header. The lint rejects them in a `.cpp`. |
| `CLAUDE.md` | Imports `docs/CLAUDE-GENERIC.md`, then adds the game's facts for Claude. |
| `README.md` | The game's page. It shows the visuals in `docs/progress`. |
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

`tools/check.py` compiles the source with the game's own compiler. Then [reccmp](https://github.com/isledecomp/reccmp) disassembles both copies of every annotated function and compares the instructions. reccmp is the scoring tool from the [LEGO Island decompilation](https://github.com/isledecomp/isle).

| Figure | Meaning |
| --- | --- |
| Score | The share of instructions that are the same in both copies. The game's copy runs to the end of its row in `data/functions.csv`. Code that our copy lacks at the end counts as a miss. Calls and globals compare by name. A function can match at another address in our exe. |
| Matched | A score of 100% in plain C. A function at 100% only through a trick, such as inline assembly or `#pragma auto_inline(off)`, keeps its score but does not count as matched. `python tools/tricks.py` lists those functions and says why. reccmp also calls some misses an *effective* match (other registers or another instruction order). Its check is loose and can pass code that behaves differently. An effective match keeps its score. The totals count it apart as *effective*. |
| Decompiled | The share of game functions that have a body. Stubs do not count. |
| Accuracy | The average score of the decompiled functions. |

Constants compare by value. reccmp finds a float or string literal only where a relocation marks the operand as an address. Our exe keeps relocations (`/FIXED:NO`). The game's exe has none. So after each build `check.py` reads the game's code and writes its floats and strings to `build/constants.csv`. reccmp adds these rows after matching, with the constants it finds itself. A variable's name still wins. A nameless row covers an address that our PDB does not name, such as a compiler-made exception handler stub. [tools/constants.py](../tools/constants.py) has the rules. Literals and floats need no annotation. The exception is a wide literal of one character or with a character outside Latin-1. docs/CLAUDE-GENERIC.md says how.

**Game functions** are the functions in `data/functions.csv` in a `game` range of `data/codegen-groups.csv`. Functions in `library` ranges do not count. Compiler-made code, such as the `Unwind@` funclets, does not count either. It gets a `library` range of its own. A function's catch blocks and the filters and handlers of its SEH `__try` blocks are part of it. Runtime functions listed in `src/library.csv` show apart. Game functions with a `LIBRARY` annotation also show apart. Every function annotation must be at the start of a game function, or the annotation lint fails. A `STUB` is the one exception. It can start any function in `data/functions.csv`, such as a library function that game code calls. The totals skip stubs.

The same source always gives the same score. `docs/progress/summary.json` keeps the last accepted score of every function. `check.py gate` fails if any score drops.

Three checks show that the toolchain is the game's own:

1. **Rich header.** Every tool build that made our exe is also in the game's Rich header (`check.py gate`). Only build numbers compare. Product ids depend on each game's mix of C, C++ and `/GL` objects. If an import library fails the check, [PORTING.md](PORTING.md#import-libraries) has the fix.
2. **Runtime library.** A CRT function from `src/library.csv` that scores 100% shows our copy of the library is the game's.
3. **Self-test.** A small known program in `tests/selftest` builds to the same SHA-256 every time. reccmp scores it exactly as pinned (`check.py ci`).

## Commands

`tools/check.py` is the single entry point. These tools also run on their own. `python tools/progress.py` rewrites `history.csv` from the commits and redraws the SVGs in `docs/progress`, as `save` does. `python tools/pages.py [--out DIR]` builds the static progress site from committed files. `python tools/objdiffreport.py [--out PATH]` writes the progress as an objdiff report, which decomp.dev and decomp.fun read. CI uploads it as the `<target>_report` artifact, such as `SADX_report`, on pushes to the default branch. `python tools/tricks.py` lists the functions that match only through a trick. `tools/llm.py` runs on its own too, as [LLM agents](#llm-agents) says. Every command first sets up what it needs, then runs itself inside `.venv`. `progress.py`, `pages.py`, `objdiffreport.py` and `llm.py` also run themselves inside `.venv`. Output shows only what matters. Tool output shows on failure. Compiler and reccmp warnings always show.

| Command | What it does | Exit code |
| --- | --- | --- |
| `setup [--game PATH]` | Prepares the Python packages, the compiler and the game. Turns on the git hooks | 1 if something is missing |
| `fn 0x00401000 0x00401020` | Builds and scores each function: one line each, plus the instruction diff for misses | 0 only if all match |
| `decls [--tables DIR] [--context DIR]` | Writes the declarations that every source file includes, from the names the source files use. It writes `src/include/types.h`, `functions.h` and `globals.h`. It writes a `STUB` in `src/unplaced/stubs.cpp` for each called function with no source yet. It writes a definition in `src/unplaced/globals.cpp` for each used global that no file defines. Run it after a source starts to use a new name. [tools/declgen.py](../tools/declgen.py) says where the names come from | 1 if a used name has no declaration it can make, or two functions would share a name |
| `dossier 0x00401000 [--c] [--callers] [--accesses]` | Prints what is needed to write a function. It shows its name, prototype, locals when a tables row gives them, and code group and file. It shows its assembly with the calls, globals, strings and floats named. It also shows the declaration of each name it uses. `--callers` adds the functions that call it. `--accesses` adds the `access` summary under each global. `--c` adds Ghidra's draft C from `build/decomp` (see [Function list](#function-list)). It takes `--tables DIR` too | 1 if an address is not a function in `data/functions.csv` |
| `access 0x00800000 [--size N]` | Lists every instruction in the exe that reads or writes the N bytes from the address (default 1). It groups them by offset, size, int or float, and form. The forms are direct, indexed by a register, or the address taken. Each line names the functions behind it. The sizes and kinds are evidence for the global's type. The first run scans every function in `data/functions.csv` in about 13 s. It caches the result in `build/accesses.tsv` until that file changes | 0 |
| `permute FILE 0x00401000 [--tries N] [--minutes M] [--seed S] [--rank score\|class]` | Tries rewrites of a near match that keep its meaning, such as swapped statements, flipped conditions and other loop forms. It scores each one. With `--rank class`, at the same score the try with fewer structural diff lines wins. It writes the best try to `build/permute`. It writes to FILE only when the try scores higher. It restores FILE on a failure or Ctrl+C. It stops at once when only the names of globals or functions differ, because no rewrite can fix that | 0 only if the function matches exactly |
| `clone 0x00401000 [...] [--all] [--tables DIR]` | Writes the copies of a function at 100%. A copy is a game function with the same instructions apart from the functions, globals, strings and constants it uses. Each copy gets the template's code with the copy's names and its own prototype's parameter names or `param_N`. It goes in the file the tables give it or in `src/unplaced`. It skips a copy whose names do not pair one to one, and says why. Then it runs `decls`, builds and scores. It keeps only the copies at 100%. `--all` takes every function at 100% as a template. Docstring: [tools/clone.py](../tools/clone.py) | 0 when it ran, whatever it matched |
| `ci [--base COMMIT]` | Builds and runs every check that needs no game. The checks are the annotation lint, the self-test and `tools/ci.py`. The lint is reccmp's linter plus two checks: every function annotation is at the start of a game function, or of any function for a `STUB`, and every `FUNCTION` or `STUB` definition ends in a line holding only `}` before the next one | 1 if any fails |
| `gate` | Runs `ci`, then the Rich header check and every game function's score with `build/report.html`. It also checks that every code byte is in a function of `data/functions.csv`, padding or an import stub. It checks that every `FUNCTION`, `STUB` and `LIBRARY` annotation names a symbol in our build. The pre-push hook runs it | 1 if any fails or a score dropped |
| `save` | Runs `gate`, then saves the scores and redraws the history and visuals. The pre-commit hook runs it. It saves nothing if the lint, the self-test, the Rich header check or the annotation check fails. It also saves nothing if a score dropped | 1 if any fails or a score dropped |
| `link [FILE ...]` | Links the game's exe from its own bytes with link.exe 10.0, with each FILE's object in place of its functions. mt.exe then embeds the manifest, and a last step copies the Rich header, timestamp and signature and sets the checksum. A name the object uses gets its address from the original's bytes where the object uses it. Each pooled float or string folds into the original's copy. Any other data in the object stops the file | 1 if a file can't take its place or the result differs from the game's exe |
| `library` | Finds the runtime library code, mostly in the `library` ranges of `data/codegen-groups.csv`. It writes `src/library.csv`. It names the game function that the runtime calls, such as `WinMain`. Then it builds and scores those functions | 1 if a function misses |
| `sources` | Writes `data/source-files.csv` and `data/classes.csv` from the source paths and class names in the exe | 0 |
| `groups` | Recounts the tells behind each row of `data/codegen-groups.csv` from the exe. It names each function whose tells contradict its row's flags. It writes `data/file-clusters.csv`. Needs `src/library.csv` | 1 if a function contradicts its row |
| `areas` | Sorts the game functions into the areas of `data/areas.yml`. A function in a file under `src/` takes its folder's area. The others take a guess from the exe, written to `data/areas.csv` with its evidence | 1 if a file under `src/` matches no tree line, or `shared`, `direct` or a `tables` entry in `data/areas.yml` doesn't fit the `map` list |
| `probe EXE` | Reads an exe's PE and Rich headers. It suggests its `game.cmake` and reccmp target. Needs no game setup | 1 if the exe is a DLL, is not 32-bit x86 with a GUI or console subsystem, has no Rich header, or the framework's compiler did not build it |

`setup` finds the game in any Steam library on the machine by the SHA-256 in `reccmp-project.yml`. For a copy from elsewhere, pass `--game`. The path goes in `reccmp-user.yml`, which stays on the machine.

## What setup downloads

Setup installs nothing outside the repo. It unpacks the Microsoft downloads with Windows' own tools and runs none of their installers. pip installs the Python packages from PyPI into `.venv`. `check.py` runs cmake, ninja and reccmp from there. Setup keeps its files in these folders, which git ignores:

| Folder | Contents |
| --- | --- |
| `.venv` | the Python packages pinned in `requirements.txt` |
| `.toolchain` | the VC++ 2010 SP1 compiler, linker, headers and libraries |
| `build` | the build and `report.html` |

[tools/toolchain.py](../tools/toolchain.py) makes `.toolchain` once. It downloads the Windows SDK 7.1 ISO and the VC++ 2010 SP1 compiler update from Microsoft (722 MB). It checks their SHA-256. It unpacks them with `tar.exe`, a read-only mount of the ISO and `msiexec /a`. Then it copies the files that the build uses into `.toolchain`. It checks the `cl.exe` and `link.exe` versions. The script holds the URLs, file lists and steps.

The downloads stay in `%TEMP%\decomp-toolchain` until this succeeds. A failed run does not download them again. The path is short on purpose. `msiexec` failed with error 1304 under a long path. A `.toolchain` folder copied from another clone works too. `toolchain.py` checks it before use.

## Antivirus false positives

Every build links a new, unsigned exe. An antivirus can flag it. In one port test, Malwarebytes quarantined the bare placeholder `build/game.exe` as `Adware.InstallCore` soon after each link. Later builds of the same placeholder passed.

When `build/game.exe` is gone, `check.py` stops and says it "is gone after the build". During `fn`, reccmp can say it first: "Recompiled binary ... does not exist".

1. Look for `build/game.exe` in the antivirus's detection log.
2. Report the false positive to the vendor. Only the vendor can fix it for every user.
3. Until then, allow the repo's `build` folder in the antivirus. Do not restore the file. The next build links it again.

Do not change the code to get past a detection. The next definitions update can flag it again.

## The self-test

`tests/selftest` is a small known program with its own reccmp project. CMake builds `original.cpp` as `build/selftest-original/SELFTEST.exe`, with no PDB and no relocations, to stand in for a retail exe. `decomp.cpp` is its annotated twin. Both builds also hold `gl-caller.cpp` and `gl-callee.cpp`, compiled with `/GL`. `check.py ci` checks eight things:

- The original builds to the SHA-256 pinned in `tests/selftest/reccmp-project.yml`. A change of compiler, libraries or flags breaks it.
- reccmp scores every function exactly as `tests/selftest/expected.json` says: six matches, one near miss, one effective match and one stub. `Scale` and `Name` use a float and a string from the original's data. The original has no relocations, so they match only with the constants `check.py` adds. `Total` and `Mix` are the `/GL` pair. `Combine` is the same inline assembly with two registers swapped. reccmp scores it 50% and flags it as an effective match.
- The regression gate passes on equal scores and a removed stub, and fires on a deliberate drop.
- The register-argument search of `check.py groups` finds the call from `Total` to `Mix`, which only `/GL` makes, and no other call.
- The totals leave the stub out of the decompiled count, and a library function out of the game total.
- The history skips stubs. On copies of the expected scores, an added or removed stub changes no score and adds no history row. Each commit that changes the totals adds one, also two commits on one day. A commit that undoes the one before adds one too. The working tree adds one only when it changed the totals. The git reader of `progress.py` reads each file of a throwaway repository, including when two files share one blob.
- The annotation lint lets a `STUB` start a library function. It flags a `FUNCTION` there, and a `STUB` inside a function. It flags a definition with no line holding only `}` before the next `FUNCTION` or `STUB`.
- `tools/link.py` links `SELFTEST.exe` back from its own bytes, and again with `original.cpp`'s object in place of its functions. Both match the original byte for byte.

A new compiler needs a new pinned hash and new expected scores.

## Continuous integration

GitHub Actions runs [.github/workflows/ci.yml](../.github/workflows/ci.yml) on every pull request and every push to `main` or `master`. It has one job, **CI**. The job runs `check.py ci` on Windows and caches the compiler download between runs.

CI never sees the game exe, so it cannot score game functions itself. `tools/ci.py` covers the gap:

- **Fresh scores.** `summary.json` stores a hash of the build inputs that `tools/ci.py` lists. After any source change, CI fails until someone commits a new `summary.json` from `check.py save`. Only a machine with the game can make one.
- **No drops.** No score may fall below the base commit's, and no global that matched may stop matching. A removed function counts as a drop unless it was a stub. After a force push, CI has no base commit. The pre-push hook compared with the old tip.
- **Honest history.** `history.csv` and the SVGs must equal a fresh render. The render reads each first-parent commit's `summary.json`. So the history has one row for each commit that changed the totals. After a `git commit --amend` that changes a score, the amended commit still holds the old commit's row. Run `git commit --amend --no-edit` once more. Pull requests merge by rebase, after the branch is up to date with the default branch. A squash or a merge commit leaves the branch's commits off the first-parent line. CI checks a pull request on its own last commit for the same reason.
- **One group each.** Every function in `data/functions.csv` is in exactly one code group and ends inside it.
- **No game files.** The check rejects any file over 10 MB. It also rejects a file with a binary suffix (`.exe`, `.dll`, `.pdb`, `.lib`, `.obj`, `.ilk`, `.iso`, `.msi`). Other game files, such as a small data file, pass this check.

With a base commit, CI also writes the score changes to the job's summary page: the totals before and after, and up to 50 functions whose score moved. A reviewer reads them there. On a push to the default branch, CI uploads the objdiff report as the `SADX_report` artifact.

<details>
<summary>Limits while a repo is private, and the branch rule</summary>

- Branch protection on a private repo needs a paid GitHub plan. Until then a failed run shows a red X but does not block a merge.
- `git push --no-verify` skips the pre-push hook, and `git commit --no-verify` skips the pre-commit hook.
- Windows minutes cost more than Linux minutes on a private repo. So a push to another branch runs nothing until it has a pull request.
- Once the repo is public (or on a paid plan), add a branch rule for the default branch. The rule requires a pull request and the status check **CI**. This repo has that rule. Admins can still bypass it.

</details>

## Function list

Ghidra makes `data/functions.csv` with three scripts in `tools/ghidra`. With Ghidra 12.1 and a 64-bit JDK 21, run this in Git Bash from the repo root:

```bash
JAVA_HOME="<JDK 21 folder>" "<Ghidra folder>/support/analyzeHeadless.bat" "<empty temp folder>" decomp -import "<path to the exe>" -scriptPath tools/ghidra -preScript AnalysisOptions.java -postScript PaddedFunctions.java -postScript ExportFunctions.java data/functions.csv -deleteProject < /dev/null > ghidra.log 2>&1
```

- `AnalysisOptions.java` turns off three guesses of Ghidra's analysis that go wrong in VC++ code. Each wrong guess cuts functions short or makes code of data. The guesses:
  - Which functions never return.
  - Which runs of data are tables of code addresses.
  - That a function's code is all in one piece.
- `PaddedFunctions.java` adds the functions analysis misses and gives functions back the code it cut off. VC++ starts each function at a 16-byte boundary after `int3` padding, except under `/O1`. So such a boundary starts one. Nothing calls an entry of the runtime's tables of initializers and terminators (`__xc_a` to `__xc_z`). So each entry starts one too. An uncalled import stub also starts one. A function only an address reaches starts at a code address that the code pushes or stores. It also starts at one that a table of read-only data lists. An SEH scope table names the filter and handler of each `__try` block. They are code of the function that pushes the table, so no function starts there. The script repeats its passes until nothing changes. Its header comment has every rule.
- `ExportFunctions.java` writes the list. A row runs from a function's entry up to the padding before the next one. So it holds the function's switch tables. A catch block gets no row.

Headless Ghidra exits 0 even when a script fails. Check `ghidra.log` for `SCRIPT ERROR`. A good run ends its `PaddedFunctions.java` lines with `Created ...`. `ExportFunctions.java` prints `Exported <N> functions`. Use forward slashes, because Git Bash drops backslashes. Give each run a new empty folder. A folder that another Ghidra still holds fails with `Unable to lock project!`. A failed run waits for a key press. `< /dev/null` stops that wait. Ghidra's default heap is 2 GB, enough for a 90 MB exe. If Ghidra runs out of memory, set `GHIDRA_HEADLESS_MAXMEM` higher, for example `12G`.

`check.py dossier --c` reads Ghidra's draft C of each function from `build/decomp`. A second run writes the drafts, with `DumpDecomp.java` in place of `ExportFunctions.java`:

```bash
JAVA_HOME="<JDK 21 folder>" "<Ghidra folder>/support/analyzeHeadless.bat" "<empty temp folder>" decomp -import "<path to the exe>" -scriptPath tools/ghidra -preScript AnalysisOptions.java -postScript PaddedFunctions.java -postScript DumpDecomp.java build/decomp -deleteProject < /dev/null > ghidra.log 2>&1
```

It skips the drafts that exist, so a run that stopped goes on where it was. A file of hex addresses after the folder name, one on each line, limits it to those functions.

## LLM agents

[tools/llm.py](../tools/llm.py) lets a language model decompile functions, with the build's score as its feedback. Any server with an OpenAI-style `/chat/completions` works: llama.cpp, Ollama, LM Studio, vLLM or a hosted API. Set up the game first, as for `fn`.

```bash
python tools/llm.py init
python tools/llm.py bench
python tools/llm.py report
python tools/llm.py solve src/unplaced/FUN_00401000.c 0x00401000
```

- `init` finds the server, picks its model and tests what the server takes. It tests a seed, and a switch that turns thinking on and off. It writes the settings to `llm.json`, which git ignores. [tools/llmclient.py](../tools/llmclient.py) lists the keys. `--start "COMMAND"` saves the command that starts the server. The other commands then start it when nothing answers, and stop it when they exit. `--key-env VAR` names the environment variable that holds an API key, so the key stays out of the file. When no server answers and there is no start command, `init` prints the GPU and its memory.
- `bench` solves functions that already match, each from a start without the function. It puts the files back after. Its first run picks 5 matched functions of each size bucket and saves the set. It uses seed 1. A rerun gives the same results when `init` found that the server repeats a reply for a seed. Use it to compare models, prompts and settings. Results go to `build/llm/<tag>`. `--tag` names the run, by default after the prompt.
- `report` sums up each run: functions matched, mean score, tries, tokens and time.
- `solve FILE ADDRESS...` works on new functions in this checkout. The best attempt stays in the file. Check it with `check.py fn`.

`--prompt NAME` picks the system prompt `tools/prompts/NAME.txt`. `data/llm-hints.txt` adds the game's facts to it. When `init` found a thinking switch, the tries think after 3 tries without a better score. They think until the score moves again.

### Model and memory

The prompts need a context of at least 32k tokens. 48k leaves room. The biggest first prompt of the default bench is about 12,500 tokens. A thinking try can write up to 12,000. Pick a model file that leaves GPU memory for the context too.

### Servers

| Server | How to start it | URL for `init` |
| --- | --- | --- |
| llama.cpp | `winget install llama.cpp`, then `llama-server -hf <model> -ngl all -c 49152 -fa on -ctk q8_0 -ctv q8_0`. `-hf` downloads the model on the first start | `http://127.0.0.1:8080/v1` |
| Ollama | `ollama pull <model>`, and set `OLLAMA_CONTEXT_LENGTH=49152` before `ollama serve`. The default context is too small | `http://127.0.0.1:11434/v1` |
| LM Studio | Load a model with a context of 48k or more, and start the local server | `http://127.0.0.1:1234/v1` |
| vLLM | `vllm serve <model>` | `http://127.0.0.1:8000/v1` |
| Hosted API | Nothing to start: pass `--key-env` | The API's URL before `/chat/completions` |

To let the harness start llama.cpp itself:

```bash
python tools/llm.py init --url http://127.0.0.1:8080/v1 --start "llama-server -hf <model> -ngl all -c 49152 -fa on -ctk q8_0 -ctv q8_0"
```

The server's output goes to `build/llm/server.log`. The first start downloads the model. If that takes longer than `start_timeout` (900 seconds), raise it in `llm.json`. If the server refuses a field, `init` names it. `extra_body` in `llm.json` adds fields to every request. A null value removes one.

### Name tables and other folders

`decls`, `dossier` and the `tables` key of `llm.json` take a folder of name tables. The tables give names that the tree does not know yet. The folder holds tab-separated `functions.tsv` and `globals.tsv`, and `types.h`. [tools/declgen.py](../tools/declgen.py) lists their columns. The `context` key names another checkout. Its source files serve as examples, and `decls` reads its signatures. The `drafts` key names a folder of Ghidra drafts in place of `build/decomp`.

[tests/llm/mock_server.py](../tests/llm/mock_server.py) is a fake server, to test the harness without a model.
