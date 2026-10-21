# Sonic Adventure DX Decompilation

A matching decompilation of the 2014 Steam release of Sonic Adventure DX. The
goal is C and C++ source that compiles to the same machine code as the retail
`Sonic Adventure DX.exe`. The work goes one function at a time.

## Progress

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="docs/progress/card-dark.svg">
  <img src="docs/progress/card.svg" alt="Progress summary" width="100%">
</picture>

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="docs/progress/map-dark.svg">
  <img src="docs/progress/map.svg" alt="Progress map by area" width="100%">
</picture>

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="docs/progress/history-dark.svg">
  <img src="docs/progress/history.svg" alt="Progress over time" width="100%">
</picture>

## How it works

The decomp runs on a generic framework.
[docs/FRAMEWORK.md](docs/FRAMEWORK.md) explains scoring, the commands and CI.
[docs/PORTING.md](docs/PORTING.md) explains how to port the framework to
another game.

**Game functions** are the functions that the progress counts. They are the
functions in [data/functions.csv](data/functions.csv) inside a game code range
of [data/codegen-groups.csv](data/codegen-groups.csv), less four header
functions. [src/header-functions.h](src/header-functions.h) names those four as
library code.

Library code does not count, because nobody needs to decompile it. Library code
is:

- The C runtime, which comes with the compiler.
- Code that the compiler adds on its own, such as exception handlers.
- CRI's middleware. The full rebuild will copy it from your own exe.

<details>
<summary>Is our compiler really the game's compiler?</summary>

The exe's Rich header says that Visual C++ 2010 SP1 (compiler 16.00.40219.01)
built it. This project uses that exact compiler. Three checks prove it:

1. **Rich header.** Every tool build that made our exe also appears in the
   game's Rich header (`check.py gate`).
2. **Runtime library.** The game links the C runtime statically.
   [src/library.csv](src/library.csv) lists 685 runtime functions, not counting
   an import stub. Of these, 658 score 100% against ours, so both copies are
   the same build. Each of the other 27 has a known cause outside the library.
   [docs/PORTING.md](docs/PORTING.md#traps) lists them.
3. **Self-test.** A small known program ([tests/selftest](tests/selftest))
   builds to the same SHA-256 every time. reccmp scores it exactly as pinned:
   six matches, one near miss at 95.24%, one effective match and one stub
   (`check.py ci`).

The game's code falls into 15 groups. The groups use 7 different sets of
optimization, frame pointer, security-check, SSE2 and float settings.
[data/codegen-groups.csv](data/codegen-groups.csv) lists the address range,
flags and evidence of each group. The build gives every source file the flags
of its functions' group. So all functions in one file must come from one group.

The end goal is a byte-for-byte rebuild of the whole exe. That needs every
function decompiled first.

</details>

## Which version do I have?

This project supports only the 2014 Steam release (app 71250, build 411939).
Check your copy against these:

| | |
| --- | --- |
| File | `Sonic Adventure DX.exe`, 90,922,000 bytes |
| SHA-256 | `e4330c00d7ee3910ecc1acab789ffd2a2d571c506984b99a8de4d3663e697fd6` |
| MD5 | `d526786ad2e3967d084c0b3e1f92cb47` |
| PE timestamp | 2014-10-16 13:56:18 UTC |

Two independent sources show that it is the retail file:

- **Signature.** The exe has a valid Authenticode signature from SEGA EUROPE
  LIMITED, time-stamped 2014-10-16. Windows shows it under Properties, Digital
  Signatures.
- **Mod Manager** (community).
  [SA Mod Manager](https://github.com/X-Hax/SA-Mod-Manager) lists this MD5 for
  the Steam exe (`SteamSourceData` in `SADXPatchHashes.cs`).

## Building

You need Windows 10 build 17063 or newer, Python 3.10 or newer, git and the
game from Steam. Testing covers only Windows 11 with Python 3.13. Run these
commands in your clone:

```console
python tools/check.py setup
python tools/check.py gate
```

`setup` gets everything ready and turns on the git hooks. `git commit` runs
`save` and stages the new scores. `git push` runs `gate` first.

If the game is not in a Steam library, give its path:
`setup --game "<path to Sonic Adventure DX.exe>"`. The path goes in
`reccmp-user.yml`, which stays on your machine. The first run downloads the
compiler from Microsoft (722 MB).
[docs/FRAMEWORK.md](docs/FRAMEWORK.md#what-setup-downloads) says what it
downloads and where it goes.

## Legal

This project is for research and preservation. It contains no game files or
assets and publishes no built exe. You need your own legally obtained copy of
the game, because building and scoring read it.

The code in `src/` is new C and C++ code. It aims to compile to the same
machine code as the retail exe. It recreates SEGA's game, and `data/` describes
that game. SEGA owns Sonic Adventure DX. This project claims no ownership of it
and gives no license for `src/` or `data/`.

The tools, build files, tests and guides are under the MIT license in
[LICENSE](LICENSE). Sonic Adventure DX is a trademark of SEGA. This project is
not affiliated with or endorsed by SEGA.
