"""Tests of the fold rule in tools/groups.py: what cross_row_lines() says about a register argument between two rows.

run() returns the failures as "<helper> gives <found> for <input>, not <wanted>". Each check builds a few
functions by hand with facttests.build(), each in one of two rows, and reads the lines for them.
"""

import groups
from facttests import build

COOKIE = 0x700000  # where ___security_cookie would be
FIRST, SECOND = 0x401000, 0x402000  # where the functions of the first and the second row start
PAIR = "A 0x00401000 -> B 0x00402000: 1 callers (0x401000), 1 callees (0x402000)"  # FIRST calls SECOND

PLAIN = ["mov eax, esi", "ret"]  # reads esi before it writes it: a register argument
EH_WITHOUT_COOKIE = ["mov eax, dword ptr fs:[0]", "mov ecx, esi", "ret"]  # /GS-, or no cookie to load, makes it
CALLS_ITSELF = ["mov eax, esi", "mov esi, 0", f"call {SECOND:#x}", "ret"]


class NoStrings:
    """The part of codetells.StringFinder that Tells.of() uses: code with no string literal."""

    def used_by(self, code) -> set:
        return set()


def failure(helper: str, found, given, wanted) -> str:
    return f"{helper} gives {found!r} for {given!r}, not {wanted!r}"


def calls(target: int) -> list[str]:
    """Sets esi, calls TARGET and returns."""
    return ["mov esi, 1", f"call {target:#x}", "ret"]


def lines_for(code: dict[int, tuple[int, list[str]]], first_flags: str, second_flags: str) -> list[str]:
    """cross_row_lines() for the register arguments among CODE: (row, lines of assembly) at each address."""
    rows = [{"group": group, "start": start, "end": start + 0x1000, "kind": "game", "flags": flags}
            for group, start, flags in (("A", FIRST, first_flags), ("B", SECOND, second_flags))]
    functions = {address: build(text, address)._replace(row=row) for address, (row, text) in code.items()}
    reading = groups.Reading(functions, COOKIE, NoStrings(), {})
    return groups.cross_row_lines(groups.register_argument_sites(functions, {}), rows, reading)


def check_fold_fits() -> list[str]:
    """A call into a later row fits a fold of two copies if the callee has a caller in its row. A call back
    into an earlier row fits only a fold of three or more."""
    forward = {FIRST: (0, calls(SECOND)), SECOND: (1, PLAIN), SECOND + 0x100: (1, calls(SECOND))}
    backward = {FIRST: (0, PLAIN), FIRST + 0x100: (0, calls(FIRST)), SECOND: (1, calls(FIRST))}
    cases = [
        ("a call into a later row", forward, f"fold {PAIR}: fits a fold of two copies"),
        ("a call back into an earlier row", backward,
         "fold B 0x00402000 -> A 0x00401000: 1 callers (0x402000), 1 callees (0x401000): "
         "fits only a fold of three or more copies"),
    ]
    return [failure("cross_row_lines", found, case, [wanted]) for case, code, wanted in cases
            if (found := lines_for(code, "/O2 /GS", "/O2 /GS")) != [wanted]]


def check_no_caller_in_its_row() -> list[str]:
    """A callee that no other function of its row calls is /GL: the copy that /OPT:ICF keeps sits in an object
    that calls it. A call from the callee to itself does not count."""
    cases = [
        ("a callee with no caller in its row", {FIRST: (0, calls(SECOND)), SECOND: (1, PLAIN)}),
        ("a callee that only calls itself", {FIRST: (0, calls(SECOND)), SECOND: (1, CALLS_ITSELF)}),
    ]
    wanted = [f"/GL  {PAIR}: no function of its row calls it"]
    return [failure("cross_row_lines", found, case, wanted) for case, code in cases
            if (found := lines_for(code, "/O2 /GS", "/O2 /GS")) != wanted]


def check_flags_cannot_make_callee() -> list[str]:
    """A callee that the caller row's flags could not make is /GL, though it has a caller in its row. Flags that
    could make it leave a fold. A callee with both blockers names both."""
    code = {FIRST: (0, calls(SECOND)), SECOND: (1, EH_WITHOUT_COOKIE), SECOND + 0x100: (1, calls(SECOND))}
    no_caller_in_its_row = {address: entry for address, entry in code.items() if address != SECOND + 0x100}
    cannot = "the caller row's flags can't make its code (EH without a cookie under /GS)"
    cases = [
        ("a callee with EH and no cookie, called under /GS", "/O2 /GS", code, f"/GL  {PAIR}: {cannot}"),
        ("the same callee, called under /GS-", "/O2 /GS-", code, f"fold {PAIR}: fits a fold of two copies"),
        ("the same callee, with no caller in its row", "/O2 /GS", no_caller_in_its_row,
         f"/GL  {PAIR}: no function of its row calls it; {cannot}"),
    ]
    return [failure("cross_row_lines", found, case, [wanted]) for case, flags, functions, wanted in cases
            if (found := lines_for(functions, flags, "/O2 /GS-")) != [wanted]]


def check_one_row() -> list[str]:
    """A register argument between two functions of one row is not a line: those tie functions to a file."""
    found = lines_for({FIRST: (0, calls(FIRST + 0x100)), FIRST + 0x100: (0, PLAIN)}, "/O2 /GS", "/O2 /GS")
    return [] if found == [] else [failure("cross_row_lines", found, "a call inside one row", [])]


def run() -> list[str]:
    """Every check of the fold rule, in order: the failures of all."""
    failures = []
    for check in (check_fold_fits, check_no_caller_in_its_row, check_flags_cannot_make_callee, check_one_row):
        failures += check()
    return failures
