"""Tests of scopes.py: a static of a function that returns a struct pointer keeps its own name, and a static of a
method keeps its class.

  .venv/Scripts/python.exe tools/scopestests.py
"""

import sys

from reccmp.parser import DecompParser

import scopes

SOURCE = """\
struct task;

// FUNCTION: SADX 0x005d5780
struct task *AmyBirdStart()
{
	// GLOBAL: SADX 0x009979a8
	static const unsigned short DAT_009979a8[6] = { 0x0301, 0x0302, 0x0a00, 0x0c00, 0x0c01, 0x7fff };
	return 0;
}

class Texture : public Resource
{
public:
	// FUNCTION: SADX 0x00401000
	void Load()
	{
		// GLOBAL: SADX 0x00900000
		static int count;
	}
};

namespace Magic {
// GLOBAL: SADX 0x00900010
int total;
}
"""


def check_names() -> list[str]:
    """The variables of SOURCE get their names with the scopes that hold them, and no others."""
    scopes.install()
    parsed = DecompParser()
    parsed.read(SOURCE)
    found = {variable.offset: variable.name for variable in parsed.variables}
    wanted = {0x009979a8: "DAT_009979a8", 0x00900000: "Texture::count", 0x00900010: "Magic::total"}
    return [f"0x{offset:08x} gets the name {found.get(offset)}, not {name}"
            for offset, name in wanted.items() if found.get(offset) != name]


def run() -> list[str]:
    """Every check of scopes.py: the failures of all."""
    return check_names()


if __name__ == "__main__":
    failures = run()
    print("\n".join(failures) or "scopes: all checks passed")
    sys.exit(1 if failures else 0)
