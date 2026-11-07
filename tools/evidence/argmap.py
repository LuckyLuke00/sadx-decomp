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

Standard library only.
"""

import csv
from dataclasses import dataclass
from pathlib import Path

import ctokens

COLUMNS = ("callee", "slot", "mode", "groups", "status", "header", "spelled_type", "origins", "note")
MODES = ("value", "flags", "and-mask")
HEADER_PROTOTYPE, UNVERIFIED = "header prototype", "unverified"
PSEUDO_CALLEES = frozenset({"__except"})  # cparse reports these as calls; no owner or prototype declares them


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


def normalized(spelled: str) -> str:
    return ctokens.spelling(ctokens.tokens_of(spelled))


def read_argmap(path: Path) -> list[Row]:
    if not path.is_file():
        raise ArgmapError(f"missing hand-owned file {path}")
    return read_map(path, COLUMNS, _row)


def read_map(path: Path, columns: tuple, make) -> list[Row]:
    """The rows of the map at PATH, whose header must be COLUMNS. MAKE(values, line, where) gives the Row of one line's
    stripped values. Two rows with one callee and slot fail."""
    with path.open(encoding="utf-8", newline="") as data:
        reader = csv.DictReader(data)
        if tuple(reader.fieldnames or ()) != columns:
            raise ArgmapError(f"{path}: the columns must be {','.join(columns)}")
        rows, seen = [], {}
        for line, fields in enumerate(reader, 2):
            row = make({name: (fields[name] or "").strip() for name in columns}, line, f"{path}:{line}")
            key = (row.callee, row.slot)
            if key in seen:
                what = f"{row.callee} argument {row.slot}" if row.slot else row.callee
                raise ArgmapError(f"{path}:{line}: {what} is also on line {seen[key]}")
            seen[key] = line
            rows.append(row)
    return rows


def _row(values: dict, line: int, where: str) -> Row:
    if not values["callee"]:
        raise ArgmapError(f"{where}: no callee")
    if not values["slot"].isdigit() or int(values["slot"]) < 1:
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
    return Row(callee, slot, values["mode"], tuple(values["groups"].split()), values["status"], values["header"],
               normalized(values["spelled_type"]) if values["spelled_type"] else "", tuple(values["origins"].split()),
               values["note"], line)


def in_header(file: str, header: str) -> bool:
    """FILE is HEADER: the same name, or a path that ends with HEADER's parts. Case does not matter (Windows)."""
    path, wanted = file.replace("\\", "/").lower(), header.replace("\\", "/").lower()
    return path == wanted or path.endswith("/" + wanted)


def check_prototype(row: Row, functions: list) -> Check:
    """FUNCTIONS: the callee's prototypes in the closures, as cheaders Function records."""
    if row.status != HEADER_PROTOTYPE:
        return Check(False, "unverified row")
    found = {(function.parameters, function.variadic) for function in functions
             if in_header(function.origin.file, row.header)}
    if not found:
        return Check(False, f"no prototype of {row.callee} in {row.header}")
    if len(found) > 1:
        return Check(False, f"{row.header} declares {row.callee} with different parameters")
    [(parameters, variadic)] = found
    if row.slot > len(parameters):
        reason = "a variadic argument" if variadic else f"argument {row.slot} of {len(parameters)}"
        return Check(False, reason)
    spelled = normalized(parameters[row.slot - 1])
    if spelled != row.spelled_type:
        return Check(False, f"{row.header} spells argument {row.slot} {spelled!r}, the row says {row.spelled_type!r}")
    return Check(True, "")


def hygiene(rows: list[Row], owners: set, declared: set) -> list[str]:
    """A warning per callee that matches no annotated owner (OWNERS) and no closure declaration (DECLARED)."""
    callees = sorted({row.callee for row in rows} - owners - declared - PSEUDO_CALLEES)
    return [f"argmap callee {callee} matches no annotated function and no header declaration" for callee in callees]
