# Code style for the SADX decompilation

## 1. What this is and is not

No official Sonic Team or Sega style guide exists in the sources read. No interview or talk covers their coding rules. Each naming, file and language rule rests on evidence from the 2014 exe or community symbol headers.

| Tag | Meaning |
| --- | --- |
| official | Read in the shipped exe or launcher, Sega SDK header text, or a developer interview. |
| community | From X-Hax or other fan repos. A good stand-in, not proof. |
| unverified | Not checked. Do not build on it. |

The exe shows how VC++ 2010 SP1 compiled the code, not how the original authors wrote it. Dreamcast, GameCube and PC builds used three different compilers [community].

## 2. Naming tiers

Use the first tier that has a name for the thing.

A parameter, local or label with a guessed name gets a placeholder until the final naming pass:

- parameters: `param_1`, `param_2`, ... by position
- locals: `local_<hex>`, the bytes below the entry stack pointer (`[ebp-0x10]` is `local_14`). Add a letter suffix `g` to `z` when the plain spelling would move the slot (`local_14g`). Use `var1`, `var2`, ... for a local with no stack slot in optimized code
- labels: `LAB_<address>`

Tier 2 names do not apply to parameters and locals.

### Tier 1: official

Keep spelling and case exactly, typos included.

- **Names in exe strings.** Examples: `late_alloca`, `EV_MainThread`, `EV_CreateObjectFunc`, `EV_CanselThread`, `ProcessStatusTable1P`, `LoadPvmMEM2`, `EPJoinVertexes` and the global `playertwp`. Log lines vary: the error text says `EV_CanselThread()`, other lines say `EV_Cansel_Thread`. Use the spelling of the call with `()`, typo included. Other words in log text prove no name.
- **RTTI class names.** Twenty `T` classes: `TObject`, `TMainTask`, `TModeCtrl`, `TAdvertise*`, `TGameGear*`. Also `GGEmu`, `SOCController`, `stControllerManagerGC`, `ConfigManager`, `STEAM::SteamManager`. Keep odd spellings such as `TGameGearInstrusion`. The exe also holds `Adv01Cmodels` and `Adv01models`: keep that case split.
- **Source paths** from `__FILE__` strings (section 3) and the launcher PDB path under `LittlestoneSoftware`.
- **Sega SDK names.** Ninja: `nj*`, `NJS_*`, `NJD_*`, `NJM_*`. Shinobi: `sy*`, `gd*`, `pd*`, `sd*`, `bu*`. Middleware: `mw*`, declared in Sega's `sg_mwply.h`. Types: `Sint8` to `Uint32`, `Float`, `Angle`, `Bool`. The exe's debug strings name `njSetPerspective` and `pdVibMxStop`, and it holds `mwPly*` names such as `mwPlyEntryFname`. Header text: section 8.
- **Not Sega.** `km*` is Kamui, and `kmbase.h` is copyright NEC. The exe shows no `km*` name.
- **Vendor names.** CRI: `ADXT_*`, `ADXPC_*`, `CRICRS_*`, `SFD_*`, `SFLIB_*`. TinyXML in namespace `LSS_TINYXML`. Steamworks: `SteamAPI_*`. Never restyle them.

### Tier 2: community, "based on symbols"

Take names from the X-Hax `sadx-mod-loader` headers `SADXStructsNew.h`, `SADXFunctionsNew.h`, `SADXVariablesNew.h` and `SADXEnumsNew.h`. Line 3 of each says it is based on symbols.

- Structs: `task`, `taskwk`, `motionwk`, `forcewk`, `colliwk`, `eventwk`, `anywk`, `playerwk`.
- Pointers: `task` holds `twp`, `mwp`, `fwp` and `awp`, and `taskwk` holds `cwp` and `ewp`. The headers call a `task *` parameter `tp` and a `playerwk *` parameter `pwp`.
- Copy each name as the header spells it, without normalizing. The symbols mix PascalCase functions, snake_case data and prefixed camel globals.
- A global's prefix gives its type:
  - `ss`: a signed short (`ssGameMode`, `ssStageNumber`)
  - `us`: an unsigned short (`usPlayer`)
  - `ul`: an unsigned long (`ulGlobalTimer`)
  - `gu32`: a global `Uint32` (`gu32GameCnt`)
- Put this comment above the first use: `// community: X-Hax symbols`.
- Only 24 of the 2,034 names in the function and variable headers appear in the exe's strings. Ten are data labels: three `objLandTableGarden02_*`, three `texlist_garden02mr_*` and four `___LANDTABLE*`. Four are words in log and error text: `playertwp`, `EV_CreateObjectFunc`, `EV_MsgClose` and `ProcessStatusTable1P`. The other ten are plain words or character names, such as `Reset` and `Tikal`.
- The headers never name their symbol file. Six comments compare them with another build. Four say `X360`, for example `inlined in SADX X360`. Two say `xbox version`. We read this as the same build [inference].
- Header values can be Xbox 360 values. A comment marks `LANGUAGE` "Different from X360". The comment on the sound queue says "length 20 in xbox version". Check values and array sizes against this exe.
- The headers target the 2004 Direct3D 8 exe. Their addresses and wrapper names do not map one to one onto this exe.

### Tier 3: neutral

Everything else gets an address name, `FUN_xxxxxxxx` for functions and `DAT_xxxxxxxx` for globals, with 8 lower-case hex digits. Never invent a descriptive name.

```cpp
// FUNCTION: SADX 0x0049d410
void FUN_0049d410(void)
{
}

// GLOBAL: SADX 0x00a67000
int DAT_00a67000;
```

### Banned

- The old modder vocabulary: `ObjectMaster`, `EntityData1`, `EntityData2`, `CharObj1`, `CharObj2`, `field_XX`, and the `_Wrapper`, `_Maybe` and `_B` suffixes. Use them only as aliases in notes.
- Direct3D 8 names from the 2004 exe headers. This exe uses Direct3D 9.
- A guessed name for any function.

## 3. File layout

Mirror the `__FILE__` paths in the exe. It holds 32 source-path strings in two trees: game files start with `..\..\src\`, platform files with `..\src\`. Drop the prefix and place each file under `src/`.

```
src/              task.c, enemy.c, eventdraw.c, texture.cpp, l_edit.cpp
src/Advertise/    filesel.cpp
src/shinobi/      sg_maloc.c
src/st/           st_direct3d.cpp, st_file.cpp, st_vertexstream.cpp
src/soc/          SOCAudioSystem.cpp, SOCFileStream.cpp
src/lss/          2014 Littlestone layer (see below)
src/unplaced/     functions whose file is not known yet
src/main.cpp      entry-point placeholder: a STUB named WinMain, the name the CRT calls
src/header-functions.h  LIBRARY annotations for header functions in game code
```

- A function goes in the file whose `__FILE__` string it uses. That proves its file unless `/GL` inlined the string from another file, and its neighbours stay unproven. A test compile showed a function inlined from a header carries the header's name. No SADX `__FILE__` path names a header.
- A function that takes register arguments goes in its callers' file, as `static`. In test compiles without `/GL`, a `static` function took register arguments from callers in its file (often only some). This holds when nothing takes the function's address. It took stack arguments without `static` or when called from another file. Callers in several files mean `/GL` or a fold. `/OPT:ICF` merges identical `static` functions into the first object's copy. For a fold, each caller's file gets its own `static` copy. A caller in an earlier row of `data/codegen-groups.csv` can't come from a fold. Both sides then need `/GL`, when the callee reads `eax`, `ebx`, `esi` or `edi` before it writes it. `ecx` and `edx` prove nothing: `thiscall` and `__fastcall` use them without `/GL`. The CSV notes these calls. `data/file-clusters.csv` lists the functions that register arguments tie together inside one row.
- `src/lss/` is a label from the launcher PDB path, and the exe has no source paths for this layer.
- Until you know a function's file, put it in `src/unplaced/FUN_<address>.cpp`. The address is the lowest function address in that file, as 8 lower-case hex digits. Keep neighbours from the same code group together.
- One file holds functions from one code group only. `data/codegen-groups.csv` lists the groups, their address ranges and their compiler flags. `tools/check.py` gives each file the flags of its group. It takes them from the addresses of its `FUNCTION`s. It stops with an error if a file mixes groups. Groups A to L are game code. `CRI`, `CRT` and `generated` are library code.

## 4. Language: `.c` or `.cpp`

**Rule.** A file the exe names keeps its extension, but the build compiles every file as C++. `game.cmake` sets this.

Evidence: a scratch build put one string literal in `.data` when compiled as C at `/Od` or `/Ox`. It went in `.rdata` when compiled as C++. At `/O2` both put it in `.rdata`. `task.c`, `enemy.c` and `eventdraw.c` sit in an `/Od` group. All their `__FILE__` strings sit in `.rdata`, at 0x00988a58, 0x00997ac8 and 0x0099b4c0 and their copies. So the game compiled these three files as C++. `sg_maloc.c` sits in an `/O2` group, so its string proves nothing.

Method for the table: find every source-path string in the exe. Then scan the code for `push imm32` and `mov` instructions that load each one. All 44 references are `push imm32`. No `mov` loads one. Two of the 11 `filesel.cpp` strings (0x00986ff4 and 0x00987014) have no reference.

| File | Extension | Referenced from | Group |
| --- | --- | --- | --- |
| `..\src\shinobi\sg_maloc.c` | `.c` | 0x0042b3bb-0x0042b40f (3) | B3 |
| `..\src\soc\SOCAudioSystem.cpp` | `.cpp` | 0x00425e5f-0x00426258 (8) | B3 |
| `..\src\st\st_direct3d.cpp` | `.cpp` | 0x004264ac-0x00426553 (2) | B3 |
| `..\src\soc\SOCFileStream.cpp` | `.cpp` | 0x0042b43b-0x0042b505 (3) | B3 |
| `..\src\st\st_vertexstream.cpp` | `.cpp` | 0x00433ef6-0x00433f68 (2) | B3 |
| `..\src\st\st_file.cpp` | `.cpp` | 0x004353c1-0x004356da (2) | B3 |
| `..\..\src\Advertise\filesel.cpp` | `.cpp` | 0x004b6cb1-0x004bab21 (9) | F |
| `..\..\src\task.c` | `.c` | 0x004f4147 (1) | F |
| `..\..\src\texture.cpp` | `.cpp` | 0x005029c4 (1) | F |
| `..\..\src\l_edit.cpp` | `.cpp` | 0x0050308c-0x005036c7 (7) | F |
| `..\..\src\enemy.c` | `.c` | 0x005e3f2e-0x005e41a0 (3) | F |
| `..\..\src\eventdraw.c` | `.c` | 0x0060e2aa-0x0060e9db (3) | F |

The table shows:

- Only groups B3 and F hold any of these files. The other 13 game groups have no source-path string, so this check says nothing about their file names. That includes I, the largest group.
- Group F mixes both extensions, interleaved by address: `.cpp`, `.c`, `.cpp`, `.cpp`, `.c`, `.c`. Group B3 puts `sg_maloc.c` between `.cpp` files.
- This fits the research: gameplay files are `.c`, later additions are `.cpp` [official for the extensions, inference for the layers]. RTTI holds 20 `T` classes. Some name menus (`TAdvertise*`) and game flow (`TMainTask`, `TModeCtrl`). Others name the Game Gear emulator (`TGameGear*`) [official for the names, inference for their role].
- Sega's own SDK headers carry `__cplusplus` guards for C++ callers, for example `sg_maloc.h` (1998) [official]. So C++ was possible on Dreamcast too, which weakens the layer reading above. The PC build compiled all of it as C++ anyway.

The Rich header can't tell C from C++ per file. It counts 265 objects at product id 0x00aa, 2,519 at 0x00ab and 121 at 0x00af, all build 40219. Scratch builds with the repo's compiler show what the ids mean:

- Without `/GL`, a C file counts at 0x00aa and a C++ file at 0x00ab.
- The linker gives all `/GL` objects one id. The id is 0x00ae when the first `/GL` object on the link line is C. The id is 0x00af when it is C++. Two `/GL` C files linked after one `/GL` C++ file count as three 0x00af objects.
- The static CRT adds objects too. An exe with an empty `main` in one C++ file, without `/GL`, counts 55 at 0x00aa and 11 at 0x00ab. With one C file it counts 56 and 10. The CRT's share grows with what the code uses. A `printf` call in C++ gives 84 at 0x00aa.

**Unplaced functions go in `.cpp` files.** Name a file `.c` only where a `__FILE__` string proves it.

## 5. Debug strings

Release code still passes `__FILE__` and `__LINE__` to print and allocator calls. The line numbers show where the code sat in the original files. Reproduce the calls. Keep every format string byte for byte. Use `#line` to set the line and file name.

Two call shapes appear in the exe:

- **Print.** `FUN_00404ef0(fmt, __FILE__, __LINE__, ...)`. The function at 0x00404ef0, in group A, forwards its format and argument list to the CRT `vsprintf` at 0x008e2755. The buffer is a fixed data address.
- **Allocator pair.** `FUN_004337a0(size, __FILE__, __LINE__)` and `FUN_004337c0(ptr, __FILE__, __LINE__)`. Each is a thin wrapper that calls the CRT `malloc` at 0x008e481b or `free` at 0x008e48af with the first argument. It drops file and line, as the disassembly shows. `src/library.csv` names `malloc`, `free` and `vsprintf`. Callers: `sg_maloc.c`, `SOCAudioSystem.cpp`, `SOCFileStream.cpp`, `st_direct3d.cpp`, `st_vertexstream.cpp`, `st_file.cpp`, `filesel.cpp`, `l_edit.cpp` and `task.c`. The exe holds no names for them. Sega's Shinobi header `sg_maloc.h` declares `Void *syMalloc(Uint32 nbytes)`, `void *syCalloc(Uint32 nobj, Uint32 size)` and `Void syFree(Void *ap)`, without file and line [official]. They fit the three `sg_maloc.c` functions that call the pair. 0x0042b3b0 takes a size, 0x0042b3d0 takes a count and a size, and 0x0042b400 takes a pointer. Name those three `syMalloc`, `syCalloc` and `syFree` [official for the names, inference for the match]. The pair takes file and line, so those names do not fit it. Give it no guessed name.

Put `#line` on the line directly above the statement that holds `__LINE__`. Keep that statement on one line.

```cpp
#line 790 "..\\..\\src\\enemy.c"
FUN_00404ef0("%s %d:playertwp=0\n", __FILE__, __LINE__);
```

Known lines:

| File | Lines |
| --- | --- |
| `enemy.c` | 790, 808, 896 (all `"%s %d:playertwp=0\n"`) |
| `task.c` | 945 (allocator call, size 0x1000020) |
| `texture.cpp` | 2908 (`"%s %d : ptlo == 0\n"`) |
| `eventdraw.c` | 63, 199, 257 (glued literals, see below) |
| `l_edit.cpp` | 984, 1512, 1525, 1535, 1538, 1546, 1576 |
| `filesel.cpp` | 1629, 1632, 3091, 3481, 3634, 3637, 3659, 3660, 3663 |
| `sg_maloc.c` | 209, 288, 334 |

Two details to match:

- In `eventdraw.c`, one literal holds the format string and the path at its end, for example `"%s %d : EPJoinVertexes Error\n..\..\src\eventdraw.c"`. The call pushes that literal and the line, with no separate file argument. Write it as `"...\n" __FILE__, __LINE__` so the bytes come out the same.
- In group F every call site has its own copy of the path string. In group B3 all sites share one. This fits `data/codegen-groups.csv`: F is /Od and B3 is /O2. The cause is string pooling (/GF), which /O1 and /O2 turn on. A scratch build of two functions that pass the same literal shows it. /O1 and /O2 share one copy. /Od and /Ox give each function its own.

A scratch build of the two examples shows that the repo's VC++ 2010 SP1 compiler emits both forms above. The string bytes and line constants match (`push 0x316` for line 790).

## 6. Types and formatting

- **Sega typedefs.** Use the Sega types from tier 1 in SDK-facing code once a header defines them. The repo has no such header yet. `Angle` is `Sint32` with 65536 units per turn [official].
- **`long` or `int`.** Sega's `sg_xpt.h` (Shinobi 1.01, 1999) defines `Sint32` as `signed long`, `Uint32` as `unsigned long` and `Bool` as `Sint32` [official]. Whether this PC exe kept `long` stays open, and the exe can't settle it. It changes only C++ name mangling: VC++ writes `long` as `J` and `int` as `H`. A test compile gave the same instructions for both, so a score can't tell them apart. The exe exports nothing and its RTTI names no game template, so it holds no mangled game name [official]. Use `long`, as the SDK does.
- **SDK structs.** Sega uses two forms: `typedef struct { ... } NJS_TEX;` and, with a tag, `typedef struct obj { ... } NJS_OBJECT;`. Copy the form of the header that defines the struct. Align member comments in a column and use `/* */` comments, as Sega's headers do [official].
- **Layout.** Indent with tabs. Put each opening brace on its own line. The existing files do both.
- **Annotations.** Use `//` comments in reccmp format directly above the function (`// FUNCTION: SADX 0x...`). Write addresses as `0x` plus 8 lower-case hex digits.
- **Vendor code.** Do not restyle it. CRT code goes in `src/library.csv`, as `docs/CLAUDE-GENERIC.md` says. The research suggests a `third_party` folder or `library.csv` rows for CRI, TinyXML and Steamworks, but that is not decided.

## 7. Layers of the code base

| Layer | What it holds | Evidence |
| --- | --- | --- |
| Original game logic | `task.c`, `enemy.c`, `eventdraw.c`, `EV_*` event code, `al_*` Chao code, the task-system names | `__FILE__` paths and name strings in the exe, and the copyright string `Copyright(C) SONICTEAM / SEGA, 2003`. The layer label is an inference. |
| GC/DX additions | 20 `T*` classes, Game Gear emulator (`GGEmu`), `Advertise\filesel.cpp`, `texture.cpp`, `l_edit.cpp` | RTTI and `.cpp` paths. Assigning them to the GC/DX layer is an inference. |
| HD-port support layer | `src/soc`, `src/st`, `src/shinobi`, Direct3D 9 renderer (`RenderDevice_DX9`, `PolyBuff_*`), window title `NINJA for PC` | Source paths. The string `SYSTEM_PS3\%s`, which points to a multi-platform port. What `SOC` and `st` stand for is unknown. |
| 2014 Littlestone layer | `ConfigManager`, `STEAM::SteamManager`, `STEAM::StatsAchievementsManager`, `LSS_TINYXML` | RTTI in the exe. The PDB path in `AppLauncher.exe`, the launcher next to the game, is `C:\LittlestoneSoftware\SVN\DreamcastCollection\sega_sonicadv\LSS\Launcher\Build\Bin\x86\Launcher\Release MT\Launcher.pdb`. That Littlestone wrote the exe's config and Steam code is likely, not proven. |
| Third party | CRI ADX and Sofdec, the static VC++ CRT, TinyXML, Steamworks, DirectX | Vendor names in the exe. The string `CRI CFG/PCx86 Ver.1.03 Build:Jul 27 2009`. `README.md` says the CRT links statically. |

The authors of the 2004 PC port and the 2010 HD port are not established. Do not name a studio in the repo until a readable credit turns up.

## 8. Sources

- [official] Local `Sonic Adventure DX.exe`, 2014 Steam build, read only: strings, RTTI, `__FILE__` references, Rich header.
- [official] Local `AppLauncher.exe`, 2014, read only (research scan): the PDB path.
- [community] X-Hax `sadx-mod-loader`: <https://github.com/X-Hax/sadx-mod-loader>. Headers: the four in tier 2. In the same folder, `njdef.h` is Sega header text (banner `Copyright(C)SEGA 1997-1999/SYSTEM R&D DEPT`). `ninja.h` there is a modder rewrite on `stdint` types: do not cite it for Sega's typedefs.
- [official] Katana SDK headers, Sega and NEC text in a community mirror: <https://github.com/Kochise/dreamcast-docs/tree/HEAD/SDK/LIBS/Include>. Read: `sg_xpt.h`, `ninjadef.h`, `ninjastr.h`, `sg_maloc.h`, `sg_mwply.h`, `kmbase.h`.
- The local game folder has no `.pdb`, `.map` or `.sym`, and the exe's debug directory is empty.
- [official] Sonic Channel interview 028, Tetsu Katano: <https://sonic.sega.jp/SonicChannelOld/creators/028/index.html>. Credits only. No coding rules.
- [official] Shmuplations, Dreamcast Magazine developer interviews, 1998-99: <https://shmuplations.com/sonicadventure/>. No coding rules.
- [official] Game Developer, Dreamcast 20th anniversary interviews: <https://www.gamedeveloper.com/business/dreamcast-20th-anniversary-interview-extravaganza-2>. No coding rules.
