# Your first function

This guide takes you from a fresh clone to a pull request with one matched
function. You need Windows, Python 3.10 or newer, git and your own copy of the
game on Steam. You need no disassembler: `dossier` shows the assembly.

## 1. Set up

```
python tools/check.py setup
```

It sets up the Python packages, downloads the compiler and finds the game. It
also turns on the git hooks. [Building](../README.md#building) in the README
has the details.

## 2. Pick a function

Start with a near miss: a function at 90% or more that does not match yet.
Build the progress site and open its near misses page:

```
python tools/pages.py --out _site
```

Then open `_site/near-misses.html`. Small functions are the easiest. Each
area's page also lists the area's functions that are not matched yet, with
their size. A small one with no source file is a good second pick.

## 3. Read it

```
python tools/check.py dossier 0x00401000
```

It prints the function's prototype, code group and file. It shows the
assembly with the calls, globals, strings and floats named, and the
declaration of each name it uses.

## 4. Write the C

A near miss already has a source file. The near misses page names it. Edit
the function there.

A new function goes in `src/unplaced/FUN_<address>.cpp` until its real file is
known. [docs/STYLE.md](STYLE.md) says when to use `.c` instead. Put the
annotation on the line right above it:

```cpp
// FUNCTION: SADX 0x00401000
```

Keep every placeholder name, such as `FUN_00401000` or `param_1`, unless
docs/STYLE.md allows a name. Write plain C. Inline assembly and
`#pragma auto_inline(off)` can make a function match, but it then does not
count as matched.

## 5. Score it

```
python tools/check.py fn 0x00401000
```

Exit code 0 means the function matches. A miss prints a diff: `-` is the
original, `+` is ours. Change the source, never the compiler flags. When you
are close, `python tools/check.py permute FILE 0x00401000` tries rewrites that
keep the meaning.

## 6. Open the pull request

`git commit` runs `save`, which scores everything and stages the new scores.
`git push` runs `gate`. Then open the pull request and fill in its checklist.
CI shows the moved scores on the run's summary page.
[CONTRIBUTING.md](../CONTRIBUTING.md) has the rest of the rules.
