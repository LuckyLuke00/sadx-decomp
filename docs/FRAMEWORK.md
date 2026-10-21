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
| `data/areas.yml`, `data/areas.csv` | The game's areas, such as its stages and characters. `areas.yml` holds the rules: the `tree` lines for source folders, and the exe's tables and strings behind the guess. Its `map` list holds the progress map's sections and the name the map shows for each area. A `map` section may have a `color`, a quoted `"#rrggbb"`, for the gem before its title. `check.py areas` writes the guess to `areas.csv`. |
| `src/library.csv` | Runtime library functions and their globals, matched by name. |
| `data/llm-hints.txt` | Optional. The game's facts for the system prompt of `tools/llm.py`, such as which release the exe is. |
| `src/header-functions.h` | `LIBRARY` annotations for header functions the linker kept in game code, such as `swprintf`. Written by hand in a header, since the lint rejects them in a `.cpp`. |
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

`tools/check.py` compiles the source with the game's own compiler. Then [reccmp](https://github.com/isledecomp/reccmp), the scoring tool from the [LEGO Island decompilation](https://github.com/isledecomp/isle), disassembles both copies of every annotated function and compares the instructions.

| Figure | Meaning |
| --- | --- |
| Score | The share of instructions the same in both copies. The game's copy runs to the end of its row in `data/functions.csv`, so code ours lacks at the end counts as a miss. Calls and globals compare by name, so a function can match at another address in our exe. |
| Matched | A score of 100%. reccmp also calls some misses an *effective* match (other registers or another instruction order), but its check is loose and can pass code that behaves differently. So an effective match keeps its score and the totals count it apart as *effective*. |
| Decompiled | The share of game functions that have a body. Stubs do not count. |
| Accuracy | The average score of the decompiled functions. |

Constants compare by value. reccmp finds a float or string literal only where a relocation marks the operand as an address. Our exe keeps relocations (`/FIXED:NO`) and the game's has none, so after each build `check.py` reads the game's code and writes the floats and strings it uses to `build/constants.csv`. reccmp adds these rows after matching, along with the constants it finds itself, so a variable's name still wins. A row with no name covers an address our PDB doesn't name either, such as a compiler-made exception handler stub. [tools/constants.py](../tools/constants.py) has the rules. Literals and floats need no annotation, except a wide literal of one character or with a character outside Latin-1: docs/CLAUDE-GENERIC.md says how.

**Game functions** are the functions in `data/functions.csv` in a `game` range of `data/codegen-groups.csv`. Functions in `library` ranges do not count, nor does compiler-made code such as the `Unwind@` funclets, which gets a `library` range of its own. A function's catch blocks and the filters and handlers of its SEH `__try` blocks are part of it. Runtime functions listed in `src/library.csv` and game functions with a `LIBRARY` annotation show apart. Every function annotation must be at the start of a game function, or the annotation lint fails. A `STUB` is the one exception: it may start any function in `data/functions.csv`, such as a library function that game code calls, since the totals skip stubs.

The same source always gives the same score. `docs/progress/summary.json` keeps the last accepted score of every function, and `check.py gate` fails if any score drops.

Three checks show that the toolchain is the game's own:

1. **Rich header.** Every tool build that made our exe is also in the game's Rich header (`check.py gate`). Only build numbers compare, since product ids depend on each game's mix of C, C++ and `/GL` objects. If an import library fails it, [PORTING.md](PORTING.md#import-libraries) has the fix.
2. **Runtime library.** A CRT function from `src/library.csv` that scores 100% shows our copy of the library is the game's.
3. **Self-test.** A small known program in `tests/selftest` builds to the same SHA-256 every time, and reccmp scores it exactly as pinned (`check.py ci`).

## Commands

`tools/check.py` is the single entry point. Only `python tools/progress.py` runs on its own. It rewrites `history.csv` from the commits and redraws the SVGs in `docs/progress`, as `save` does. Every command first sets up what it needs, then runs itself inside `.venv`. `progress.py` also runs itself inside `.venv`. Output shows only what matters. Tool output shows on failure. Compiler and reccmp warnings always show.

| Command | What it does | Exit code |
| --- | --- | --- |
| `setup [--game PATH]` | Gets the Python packages, the compiler and the game ready, and turns on the git hooks | 1 if something is missing |
| `fn 0x00401000 0x00401020` | Builds and scores each function: one line each, plus the instruction diff for misses | 0 only if all match |
| `decls [--tables DIR] [--context DIR]` | Writes the declarations every source file includes, from the names the source files use: `src/include/types.h`, `functions.h` and `globals.h`, a `STUB` in `src/unplaced/stubs.cpp` for each called function with no source yet, and a definition in `src/unplaced/globals.cpp` for each used global no file defines. Run it after a source starts to use a new name. [tools/declgen.py](../tools/declgen.py) says where the names come from | 1 if a used name has no declaration it can make, or two functions would share a name |
| `dossier 0x00401000 [--c] [--callers] [--accesses]` | Prints what it takes to write a function: its name, prototype, locals when a tables row gives them, code group and file, its assembly with the calls, globals, strings and floats named, and the declaration of each name it uses. `--callers` adds the functions that call it, `--accesses` adds the `access` summary under each global, and `--c` adds Ghidra's draft C from `build/decomp` (see [Function list](#function-list)). It takes `--tables DIR` too | 1 if an address is not a function in `data/functions.csv` |
| `access 0x00800000 [--size N]` | Lists every instruction in the exe that reads or writes the N bytes from the address (default 1), grouped by offset, size, int or float, and form: direct, indexed by a register, or the address taken. Each line names the functions behind it. The sizes and kinds are evidence for the global's type. The first run scans every function in `data/functions.csv` in about 13 s and caches the result in `build/accesses.tsv` until that file changes | 0 |
| `permute FILE 0x00401000 [--tries N] [--minutes M] [--seed S]` | Tries rewrites of a near match that keep its meaning, such as swapped statements, flipped conditions and other loop forms. It scores each one. It writes the best try to `build/permute`. It writes to FILE only when the try scores higher. It restores FILE on a failure or Ctrl+C. It stops at once when only the names of globals or functions differ, because no rewrite can fix that | 0 only if the function matches exactly |
| `clone 0x00401000 [...] [--all] [--tables DIR]` | Writes the copies of a function at 100%. A copy is a game function with the same instructions apart from the functions, globals, strings and constants it uses. Each copy gets the template's code with the copy's names and its own prototype's parameter names or `param_N`. It goes in the file the tables give it or in `src/unplaced`. It skips a copy whose names do not pair one to one, and says why. Then it runs `decls`, builds and scores. It keeps only the copies at 100%. `--all` takes every function at 100% as a template. Docstring: [tools/clone.py](../tools/clone.py) | 0 when it ran, whatever it matched |
| `ci [--base COMMIT]` | Builds and runs every check that needs no game: the annotation lint (reccmp's linter plus a check that every function annotation is at the start of a game function, or of any function for a `STUB`), the self-test and `tools/ci.py` | 1 if any fails |
| `gate` | `ci`, plus the Rich header check, every game function's score with `build/report.html`, and checks that every code byte is in a function of `data/functions.csv`, padding or an import stub, and that every `FUNCTION`, `STUB` and `LIBRARY` annotation names a symbol in our build. The pre-push hook runs it | 1 if any fails or a score dropped |
| `save` | `gate`, then saves the scores and redraws the history and visuals. The pre-commit hook runs it. It saves nothing if the lint, the self-test, the Rich header check or the annotation check fails, or a score dropped | 1 if any fails or a score dropped |
| `library` | Finds the runtime library code, mostly in the `library` ranges of `data/codegen-groups.csv`, writes `src/library.csv` and names the game function the runtime calls, such as `WinMain`. Then it builds and scores those functions | 1 if a function misses |
| `sources` | Writes `data/source-files.csv` and `data/classes.csv` from the source paths and class names in the exe | 0 |
| `groups` | Recounts the tells behind each row of `data/codegen-groups.csv` from the exe, names each function whose tells contradict its row's flags, and writes `data/file-clusters.csv`. Needs `src/library.csv` | 1 if a function contradicts its row |
| `areas` | Sorts the game functions into the areas of `data/areas.yml`. A function in a file under `src/` takes its folder's area; the others take a guess from the exe, written to `data/areas.csv` with its evidence | 1 if a file under `src/` matches no tree line, or `shared`, `direct` or a `tables` entry in `data/areas.yml` doesn't fit the `map` list |
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

`tests/selftest` is a small known program with its own reccmp project. CMake builds `original.cpp` as `build/selftest-original/SELFTEST.exe`, with no PDB and no relocations, to stand in for a retail exe. `decomp.cpp` is its annotated twin. Both builds also hold `gl-caller.cpp` and `gl-callee.cpp`, compiled with `/GL`. `check.py ci` checks seven things:

- The original builds to the SHA-256 pinned in `tests/selftest/reccmp-project.yml`. A change of compiler, libraries or flags breaks it.
- reccmp scores every function exactly as `tests/selftest/expected.json` says: six matches, one near miss, one effective match and one stub. `Scale` and `Name` use a float and a string from the original's data. It has no relocations, so they match only with the constants `check.py` adds. `Total` and `Mix` are the `/GL` pair. `Combine` is the same inline assembly with two registers swapped. reccmp scores it 50% and flags it as an effective match.
- The regression gate passes on equal scores and a removed stub, and fires on a deliberate drop.
- The register-argument search of `check.py groups` finds the call from `Total` to `Mix`, which only `/GL` makes, and no other call.
- The totals leave the stub out of the decompiled count, and a library function out of the game total.
- The history skips stubs. On copies of the expected scores, an added or removed stub changes no score and adds no history row. Each commit that changes the totals adds one, also two commits on one day. A commit that undoes the one before adds one too. The working tree adds one only when it changed the totals. The git reader of `progress.py` reads each file of a throwaway repository, including when two files share one blob.
- The annotation lint lets a `STUB` start a library function. It flags a `FUNCTION` there, and a `STUB` inside a function.

A new compiler needs a new pinned hash and new expected scores.

## Continuous integration

GitHub Actions runs [.github/workflows/ci.yml](../.github/workflows/ci.yml) on every pull request and every push to `main` or `master`. Its one job, **CI**, runs `check.py ci` on Windows and caches the compiler download between runs.

CI never sees the game exe, so it can't score game functions itself. `tools/ci.py` covers the gap:

- **Fresh scores.** `summary.json` stores a hash of the build inputs that `tools/ci.py` lists. After any source change, CI fails until a new `summary.json` from `check.py save` is committed, and only a machine with the game can make one.
- **No drops.** No score may fall below the base commit's. A removed function counts as a drop unless it was a stub. After a force push, CI has no base commit, but the pre-push hook compared with the old tip.
- **Honest history.** `history.csv` and the SVGs must equal a fresh render. The render reads each first-parent commit's `summary.json`. So the history has one row for each commit that changed the totals. After a `git commit --amend` that changes a score, the amended commit still holds the old commit's row. Run `git commit --amend --no-edit` once more. Pull requests merge by rebase, after the branch is up to date with the default branch. A squash or a merge commit leaves the branch's commits off the first-parent line. CI checks a pull request on its own last commit for the same reason.
- **One group each.** Every function in `data/functions.csv` is in exactly one code group and ends inside it.
- **No game files.** No file with a binary suffix (`.exe`, `.dll`, `.pdb`, `.lib`, `.obj`, `.ilk`, `.iso`, `.msi`) and no file over 10 MB. Other game files, such as a small data file, pass this check.

<details>
<summary>Limits while a repo is private, and settings for later</summary>

- Branch protection on a private repo needs a paid GitHub plan, so until then a failed run shows a red X but does not block a merge.
- `git push --no-verify` skips the pre-push hook, and `git commit --no-verify` skips the pre-commit hook.
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

`check.py dossier --c` reads Ghidra's draft C of each function from `build/decomp`. A second run writes the drafts, with `DumpDecomp.java` in place of `ExportFunctions.java`:

```bash
JAVA_HOME="<JDK 21 folder>" "<Ghidra folder>/support/analyzeHeadless.bat" "<empty temp folder>" decomp -import "<path to the exe>" -scriptPath tools/ghidra -preScript AnalysisOptions.java -postScript PaddedFunctions.java -postScript DumpDecomp.java build/decomp -deleteProject < /dev/null > ghidra.log 2>&1
```

It skips the drafts that exist, so a run that stopped goes on where it was. A file of hex addresses after the folder name, one a line, limits it to those functions.

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

The prompts need a context of at least 32k tokens. 48k leaves room. The biggest first prompt of the default bench is about 12,500 tokens. A thinking try can write up to 12,000. For Qwen3.8 27B, this table picks a file of `unsloth/Qwen3.8-27B-GGUF` by GPU memory. The context needs memory too, so use the table as a rough guide. The 16 GB row runs with the llama.cpp command below.

| GPU memory | File | File size |
| --- | --- | --- |
| 16 GB | `UD-Q3_K_XL` | 13.1 GB |
| 24 GB | `UD-Q4_K_XL` | 17.6 GB |
| 32 GB | `UD-Q6_K_XL` | 25.3 GB |
| 48 GB or more | `UD-Q8_K_XL` | 31.5 GB |

### Servers

| Server | How to start it | URL for `init` |
| --- | --- | --- |
| llama.cpp | `winget install llama.cpp`, then `llama-server -hf unsloth/Qwen3.8-27B-GGUF:UD-Q3_K_XL -ngl all -c 49152 -fa on -ctk q8_0 -ctv q8_0`. `-hf` downloads the model on the first start | `http://127.0.0.1:8080/v1` |
| Ollama | `ollama pull <model>`, and set `OLLAMA_CONTEXT_LENGTH=49152` before `ollama serve`. The default context is too small | `http://127.0.0.1:11434/v1` |
| LM Studio | Load a model with a context of 48k or more, and start the local server | `http://127.0.0.1:1234/v1` |
| vLLM | `vllm serve <model>` | `http://127.0.0.1:8000/v1` |
| Hosted API | Nothing to start: pass `--key-env` | The API's URL before `/chat/completions` |

To let the harness start llama.cpp itself:

```bash
python tools/llm.py init --url http://127.0.0.1:8080/v1 --start "llama-server -hf unsloth/Qwen3.8-27B-GGUF:UD-Q3_K_XL -ngl all -c 49152 -fa on -ctk q8_0 -ctv q8_0"
```

The server's output goes to `build/llm/server.log`. The first start downloads the model. If that takes longer than `start_timeout` (900 seconds), raise it in `llm.json`. If the server refuses a field, `init` names it. `extra_body` in `llm.json` adds fields to every request. A null value removes one.

### Name tables and other folders

`decls`, `dossier` and the `tables` key of `llm.json` take a folder of name tables. The tables give names that the tree does not know yet. The folder holds tab-separated `functions.tsv` and `globals.tsv`, and `types.h`. [tools/declgen.py](../tools/declgen.py) lists their columns. The `context` key names another checkout. Its source files serve as examples, and `decls` reads its signatures. The `drafts` key names a folder of Ghidra drafts in place of `build/decomp`.

[tests/llm/mock_server.py](../tests/llm/mock_server.py) is a fake server, to test the harness without a model.
