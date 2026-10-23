# Contributing

Pull requests are welcome. This page says what a pull request needs.

## Set up

Follow [Building](README.md#building) in the README. Then read two guides:

- [docs/CLAUDE-GENERIC.md](docs/CLAUDE-GENERIC.md) has the commands and the
  loop for one function. It is written for agents, but people use the same
  loop.
- [docs/STYLE.md](docs/STYLE.md) says how to name and place code.

## What counts

A function counts as matched only under the rules in
[How it works](README.md#how-it-works). Its C compiles to the same
instructions as the exe, and it is plain C. A function that matches only
through a trick, such as inline assembly or `#pragma auto_inline(off)`, can
stay in the tree. It does not count as matched. `python tools/tricks.py` lists
those functions.

A partial match is welcome too. No score may drop below the score on the
default branch. CI checks this.

## Names

Name a function, global or type only as [docs/STYLE.md](docs/STYLE.md) says.
Everything else keeps its placeholder, such as `FUN_00401000` or `param_1`.
Never let a model pick a name.

## AI use

AI-assisted pull requests are fine. You answer for everything in your pull
request, AI or not.

## Pull requests

- Keep the pull request small: one source file or a few functions.
- Check every function yourself with `python tools/check.py fn`.
- Run `python tools/check.py setup` once. Then `git commit` runs `save` and
  stages the new scores, and `git push` runs `gate`.
- Never edit `summary.json`, `history.csv` or the SVGs in `docs/progress` by
  hand. CI rejects the edit.
- Never add game files: no exe, no dll, no game data, no disassembly dumps.
- Never read or use leaked source code.
- Pull requests merge by rebase, after the branch is up to date with the
  default branch.

Report a security problem as [SECURITY.md](SECURITY.md) says, not in an issue.
