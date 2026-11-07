"""Reference symbols: what a symbol dump of a reference build says about the game's own functions. A local adapter
writes three neutral files into the evidence folder. Each is optional; the run reads the ones that exist.

- prototypes.csv: address,name,slot,type. One row per return (slot 0) and parameter (slot 1 and up) of a function.
  The address is the function's target address, as the owner annotations spell it; the name is the reference
  build's; the type is as the dump spells it, "enum NAME" for an enum, "..." for a variadic tail.
- enums.csv: enum,name,value. The enumerators of the enums that prototypes.csv names, each enum spelled as there.
- scope-constants.csv: address,scope,name,value. The enum constants declared inside a function. The scope names the
  enum that each one belongs to, unique within the function.

load() checks every row: a malformed one fails with the file and line.

The inventory makes these sites with them. Each row status is one of STATUSES, and each name has the origin
REFERENCE.
- A call slot of a game function whose reference prototype gives the slot an enum type, and `return K;` in a function
  whose reference return type is an enum: the enum's enumerators are the candidates, at an int slot. The row passes
  its check when enums.csv holds the enum.
- In a function with scope constants: a field spot or a plain variable written or compared with =, == or !=, and a
  case label, when no argmap or fieldmap row maps it. The function's scope constants are the candidates, meaning B.
- The lvalue check (lvalue_check()): an lvalue of the function (its normalized expression; a case label's is its
  switch expression) passes when it takes scope_min_values or more distinct literal values, all of them values of one
  scope. Its sites take that scope's constants only, get the flag "lvalue check" and can reach meaning A.
- Under a C++ profile, an integer converts to an enum only through a cast. So an original that spelled no cast spelled
  an enumerator. An enum site whose value one enumerator alone has gets the flag "one enumerator".

Standard library only.
"""

import re
from dataclasses import dataclass
from pathlib import Path

import argmap
import covers
import outputs

PROTOTYPES, ENUMS, SCOPES = "prototypes.csv", "enums.csv", "scope-constants.csv"
FILES = (PROTOTYPES, ENUMS, SCOPES)
PROTOTYPE_COLUMNS = ("address", "name", "slot", "type")
ENUM_COLUMNS = ("enum", "name", "value")
SCOPE_COLUMNS = ("address", "scope", "name", "value")
REFERENCE = "reference"  # the origin of every name from these files
REFERENCE_PROTOTYPE, REFERENCE_SCOPE = "reference prototype", "reference scope"  # row statuses
STATUSES = (REFERENCE_PROTOTYPE, REFERENCE_SCOPE)
LVALUE_CHECK, ONE_ENUMERATOR = "lvalue check", "one enumerator"  # site flags
SCOPE_OPERATORS = ("=", "==", "!=")
VARIADIC = "..."
ENUM_PREFIX = "enum "
NO_ENUM = "enums.csv has no rows for the enum"
ADDRESS = re.compile(r"(0x)?[0-9a-f]+\Z")
NAME = re.compile(r"[A-Za-z_][A-Za-z0-9_]*\Z")
DECLARATOR = re.compile(r"[*&\[(]")  # a pointer, reference, array or function part of a spelled type


class SymbolsError(Exception):
    """A neutral symbol file is malformed."""


@dataclass(frozen=True)
class Constant:
    scope: str
    name: str
    value: int


@dataclass
class Symbols:
    prototypes: dict  # address -> [type per slot], slot 0 (the return) first
    enums: dict  # enum -> [(name, value)], in file order
    scopes: dict  # address -> [Constant], in file order

    def call_rows(self, address: str, callee: str) -> dict:
        """Slot -> Row for each parameter of the function at ADDRESS that has an enum type."""
        types = self.prototypes.get(address, ())
        return {slot: _enum_row(callee, slot, spelled) for slot, spelled in enumerate(types)
                if slot and enum_slot(spelled)}

    def return_row(self, address: str, owner: str) -> argmap.Row | None:
        """The Row of the return of the function at ADDRESS when its type is an enum, else None."""
        types = self.prototypes.get(address)
        return _enum_row(owner, 0, types[0]) if types and enum_slot(types[0]) else None

    def parameters(self, address: str) -> tuple[tuple, bool]:
        """The parameter types of the function at ADDRESS, and whether it is variadic."""
        types = self.prototypes[address][1:]
        variadic = bool(types) and types[-1] == VARIADIC
        return tuple(types[:-1] if variadic else types), variadic

    def scope_row(self, address: str, scopes: tuple = ()) -> argmap.Row | None:
        """The Row of a scope site in the function at ADDRESS: it takes the constants of SCOPES, or of every scope of
        the function when SCOPES is empty. None when the function has no scope constants."""
        constants = self.scopes.get(address)
        if not constants:
            return None
        groups = scopes or tuple(sorted({constant.scope for constant in constants}))
        return argmap.Row(address, 0, "value", groups, REFERENCE_SCOPE, "", "", (REFERENCE,), "", 0)

    def names(self, row: argmap.Row) -> list:
        """The covers.Name records that ROW takes, one per name and value."""
        if row.status == REFERENCE_PROTOTYPE:
            pairs = self.enums.get(row.groups[0], ())
        else:
            pairs = [(constant.name, constant.value) for constant in self.scopes.get(row.callee, ())
                     if constant.scope in row.groups]
        return [covers.Name(name, value, False, (REFERENCE,)) for name, value in dict.fromkeys(pairs)]

    def check(self, row: argmap.Row) -> argmap.Check:
        if row.status == REFERENCE_PROTOTYPE and not self.enums.get(row.groups[0]):
            return argmap.Check(False, NO_ENUM)
        return argmap.Check(True, "")


def enum_slot(spelled: str) -> bool:
    """Whether a spelled slot type is an enum itself (`enum NAME`), not a pointer, reference, array or function."""
    return spelled.startswith(ENUM_PREFIX) and not DECLARATOR.search(spelled)


def _enum_row(callee: str, slot: int, spelled: str) -> argmap.Row:
    return argmap.Row(callee, slot, "value", (spelled,), REFERENCE_PROTOTYPE, "", spelled, (REFERENCE,), PROTOTYPES, 0)


def one_enumerator(search, row: argmap.Row, profile) -> bool:
    """Under a C++ profile: the top candidate of an enum site is one enumerator alone."""
    if row.status != REFERENCE_PROTOTYPE or profile.language != "cpp":
        return False
    if search is None or search.incomplete or not search.candidates:
        return False
    top = search.candidates[0]
    return len(top.terms) == 1 and len(top.terms[0].aliases) == 1


def lvalue_check(pairs: list, constants: list, minimum: int) -> dict:
    """PAIRS: (lvalue, value) per literal spot of one function. CONSTANTS: its Constant records. The lvalues that take
    MINIMUM or more distinct values, every one of them the value of a constant of one scope -> those scopes."""
    taken = {}
    for lvalue, value in pairs:
        taken.setdefault(lvalue, set()).add(value)
    members = {}
    for constant in constants:
        members.setdefault(constant.scope, set()).add(constant.value)
    passed = {}
    for lvalue, values in taken.items():
        scopes = tuple(sorted(scope for scope, held in members.items() if values <= held))
        if len(values) >= minimum and scopes:
            passed[lvalue] = scopes
    return passed


# Reading


def load(folder: Path) -> Symbols | None:
    """The neutral symbol files in FOLDER; None when none of them exists."""
    if not any((folder / name).is_file() for name in FILES):
        return None
    return Symbols(_read_prototypes(folder / PROTOTYPES), _read_enums(folder / ENUMS), _read_scopes(folder / SCOPES))


def _rows(path: Path, columns: tuple):
    """(where, values) per data row of PATH, whose header must be COLUMNS; no rows when PATH does not exist."""
    if path.is_file():
        yield from outputs.read_rows(path, columns, SymbolsError)


def _address(text: str, where: str) -> str:
    address = text.lower()
    if not ADDRESS.match(address):
        raise SymbolsError(f"{where}: address {text!r} is not a hex number")
    return address


def _integer(text: str, what: str, where: str) -> int:
    try:
        return int(text, 0)
    except ValueError:
        raise SymbolsError(f"{where}: {what} {text!r} is not an integer") from None


def _name(text: str, where: str) -> str:
    if not NAME.match(text):
        raise SymbolsError(f"{where}: name {text!r} is not an identifier")
    return text


def _read_prototypes(path: Path) -> dict:
    slots, seen = {}, {}
    for where, values in _rows(path, PROTOTYPE_COLUMNS):
        address = _address(values["address"], where)
        if not values["name"] or not values["type"]:
            raise SymbolsError(f"{where}: the name and the type must not be empty")
        if not values["slot"].isdigit():
            raise SymbolsError(f"{where}: slot {values['slot']!r} is not a number from 0")
        slot = int(values["slot"])
        if (address, slot) in seen:
            raise SymbolsError(f"{where}: {address} slot {slot} is also at {seen[address, slot]}")
        seen[address, slot] = where
        slots.setdefault(address, {})[slot] = values["type"]
    prototypes = {}
    for address, types in slots.items():
        missing = next((slot for slot in range(len(types)) if slot not in types), None)
        if missing is not None:
            raise SymbolsError(f"{path}: {address} has no slot {missing}")
        ordered = [types[slot] for slot in range(len(types))]
        if VARIADIC in ordered[:-1] or ordered[0] == VARIADIC:
            raise SymbolsError(f"{seen[address, ordered.index(VARIADIC)]}: {VARIADIC} must be the last parameter")
        prototypes[address] = ordered
    return prototypes


def _read_enums(path: Path) -> dict:
    enums, seen = {}, {}
    for where, values in _rows(path, ENUM_COLUMNS):
        enum = values["enum"]
        if not enum.startswith(ENUM_PREFIX) or not enum[len(ENUM_PREFIX):].strip():
            raise SymbolsError(f"{where}: enum {enum!r} must be spelled {ENUM_PREFIX}NAME")
        name = _name(values["name"], where)
        if (enum, name) in seen:
            raise SymbolsError(f"{where}: {enum} {name} is also at {seen[enum, name]}")
        seen[enum, name] = where
        enums.setdefault(enum, []).append((name, _integer(values["value"], "value", where)))
    return enums


def _read_scopes(path: Path) -> dict:
    scopes, seen = {}, {}
    for where, values in _rows(path, SCOPE_COLUMNS):
        address = _address(values["address"], where)
        if not values["scope"]:
            raise SymbolsError(f"{where}: the scope must not be empty")
        constant = Constant(values["scope"], _name(values["name"], where),
                            _integer(values["value"], "value", where))
        key = (address, constant.scope, constant.name)
        if key in seen:
            raise SymbolsError(f"{where}: {constant.name} of {constant.scope} is also at {seen[key]}")
        seen[key] = where
        scopes.setdefault(address, []).append(constant)
    return scopes
