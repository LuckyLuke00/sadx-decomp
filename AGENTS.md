# Agents

This file is for AI coding agents.

Read [docs/CLAUDE-GENERIC.md](docs/CLAUDE-GENERIC.md) first. It has the
commands, the loop for one function and the rules. It applies to every agent,
not only Claude. Then read [CONTRIBUTING.md](CONTRIBUTING.md).

On top of those:

- A function counts only when it matches in plain C. Don't use inline
  assembly, `__emit`, `__declspec(naked)`, `volatile`,
  `__declspec(safebuffers)` or a `#pragma` to force a match. Such a function
  does not count. `python tools/tricks.py` lists them.
- Don't pick names. Keep the placeholder unless
  [docs/STYLE.md](docs/STYLE.md) gives the name.
- Never fetch tcrf.net or other bot-walled fan wikis. Never read leaked source
  code.
