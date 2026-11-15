"""The argument map: which argument of which callee takes names from which groups. evidence/argmap.csv is hand-owned.

Columns:
- callee, slot: the function and its 1-based argument index;
- mode: value (one name), flags (one name, or single-bit names or'ed together) or and-mask (also ~ of them);
- groups: space-separated; an entry that ends with _ is a name prefix, any other entry is one name;
- status: "header prototype" when the slot type comes from a vendor header, else "unverified";
- header: the vendor header that declares the callee, such as ninjaapi.h;
- spelled_type: the slot's parameter type as that header spells it, before typedefs unroll, such as Angle;
- origins: space-separated sources whose names the slot accepts; empty means the source of the header;
- note: free text.

The prototype check reads the callee's prototype from the row's header, also when other headers declare it too. The
slot's spelled type must equal the row's, with spacing normalized. A row that fails the check, or is unverified, gives
meaning B at best.

read_map, checked_row and in_header also read fieldmap.csv (fields.py). Standard library only.
"""

from dataclasses import dataclass
from pathlib import Path

import ctokens
import outputs

COLUMNS = ("callee", "slot", "mode", "groups", "status", "header", "spelled_type", "origins", "note")
VALUE, FLAGS, AND_MASK = "value", "flags", "and-mask"  # the slot modes
MODES = (VALUE, FLAGS, AND_MASK)
HEADER_PROTOTYPE, UNVERIFIED = "header prototype", "unverified"


class ArgmapError(Exception):
    """argmap.csv is missing or malformed, or fieldmap.csv is malformed."""


@dataclass(frozen=True)
class Row:
    callee: str
    slot: int
    mode: str
    groups: tuple
    status: str
    header: str
    spelled_type: str
    origins: tuple
    note: str
    line: int  # in argmap.csv

    def takes(self, name: str) -> bool:
        return any(name.startswith(entry) if entry.endswith("_") else name == entry for entry in self.groups)


@dataclass(frozen=True)
class Check:
    passed: bool
    reason: str  # why it failed, "" when it passed


def normalized_type(spelled: str) -> str:
    return ctokens.spelling(ctokens.tokens_of(spelled))


def read_argmap(path: Path) -> list[Row]:
    if not path.is_file():
        raise ArgmapError(f"missing hand-owned file {path}")
    return read_map(path, COLUMNS, _row)


def read_map(path: Path, columns: tuple, make) -> list[Row]:
    """The rows of the map at PATH, whose header must be COLUMNS. MAKE(values, line, where) gives the Row of one line's
    stripped values. A row with the wrong number of values, a type that does not tokenize, and two rows with one
    callee and slot fail."""
    rows, seen = [], {}
    for where, values in outputs.read_rows(path, columns, ArgmapError):
        line = outputs.line_of(where)
        try:
            row = make(values, line, where)
        except ctokens.Unsupported as error:
            raise ArgmapError(f"{where}: {error}") from None
        key = (row.callee, row.slot)
        if key in seen:
            what = f"{row.callee} argument {row.slot}" if row.slot else row.callee
            raise ArgmapError(f"{where}: {what} is also on line {seen[key]}")
        seen[key] = line
        rows.append(row)
    return rows


def _row(values: dict, line: int, where: str) -> Row:
    if not values["callee"]:
        raise ArgmapError(f"{where}: no callee")
    if not values["slot"].isdecimal() or int(values["slot"]) < 1:
        raise ArgmapError(f"{where}: slot {values['slot']!r} is not an argument number from 1")
    return checked_row(values, values["callee"], int(values["slot"]), HEADER_PROTOTYPE, line, where)


def checked_row(values: dict, callee: str, slot: int, verified: str, line: int, where: str) -> Row:
    """The Row of CALLEE and SLOT from VALUES (mode, groups, status, header, spelled_type, origins and note). VERIFIED
    is the status that needs a header and a spelled type; the only other status is UNVERIFIED."""
    if values["mode"] not in MODES:
        raise ArgmapError(f"{where}: mode {values['mode']!r} is not one of {', '.join(MODES)}")
    if values["status"] not in (verified, UNVERIFIED):
        raise ArgmapError(f"{where}: status {values['status']!r} is not {verified!r} or {UNVERIFIED!r}")
    if not values["groups"].split():
        raise ArgmapError(f"{where}: no groups")
    if values["status"] == verified and not (values["header"] and values["spelled_type"]):
        raise ArgmapError(f"{where}: a {verified} row needs a header and a spelled type")
    spelled = normalized_type(values["spelled_type"]) if values["spelled_type"] else ""
    return Row(callee, slot, values["mode"], tuple(values["groups"].split()), values["status"], values["header"],
               spelled, tuple(values["origins"].split()), values["note"], line)


def in_header(file: str, header: str) -> bool:
    """FILE is HEADER: the same name, or a path that ends with HEADER's parts. Case does not matter (Windows)."""
    path, wanted = file.replace("\\", "/").lower(), header.replace("\\", "/").lower()
    return path == wanted or path.endswith("/" + wanted)


def check_prototype(row: Row, functions: list) -> Check:
    """FUNCTIONS: the callee's prototypes in the closures, as cheaders Function records. A prototype read in an
    unresolved #if branch fails the check."""
    if row.status != HEADER_PROTOTYPE:
        return Check(False, "unverified row")
    declared = [function for function in functions if in_header(function.origin.file, row.header)]
    if not declared:
        return Check(False, f"no prototype of {row.callee} in {row.header}")
    if not all(function.origin.certain for function in declared):
        return Check(False, f"{row.header} declares {row.callee} in an unresolved #if branch")
    found = {(function.parameters, function.variadic) for function in declared}
    if len(found) > 1:
        return Check(False, f"{row.header} declares {row.callee} with different parameters")
    [(parameters, variadic)] = found
    if row.slot > len(parameters):
        reason = "a variadic argument" if variadic else f"argument {row.slot} of {len(parameters)}"
        return Check(False, reason)
    spelled = normalized_type(parameters[row.slot - 1])
    if spelled != row.spelled_type:
        return Check(False, f"{row.header} spells argument {row.slot} {spelled!r}, the row says {row.spelled_type!r}")
    return Check(True, "")


def hygiene(rows: list[Row], owners: set, declared: set) -> list[str]:
    """A warning per callee that matches no function the sources define (OWNERS) and no closure declaration
    (DECLARED)."""
    callees = sorted({row.callee for row in rows} - owners - declared)
    return [f"argmap callee {callee} matches no function in the sources and no header declaration"
            for callee in callees]
