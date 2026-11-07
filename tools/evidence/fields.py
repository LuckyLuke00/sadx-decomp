"""The field map and the typing of field spots. evidence/fieldmap.csv is hand-owned and optional.

Columns, as in argmap.csv apart from the first two:
- type, member: the struct or union and its member; the type is any spelling that names the body in the target
  headers, such as a typedef name or `struct tag`;
- mode, groups, origins, note: as in argmap.csv;
- status: "header declaration" when the member type comes from a vendor header, else "unverified";
- header: the vendor header that defines the body;
- spelled_type: the member's type as that header spells it, before typedefs unroll.

The member check reads the body from the row's header. Its member must exist, and its spelled type must equal the
row's. A row that fails the check, or is unverified, gives meaning B at best.

A spot's base expression types through the declaration subset: locals and parameters, then the source file's names
and typedefs, then the target closures. A closure name counts only when every closure that declares it agrees.
Names, calls, casts, unary *, [ ], . and -> type; anything else does not.

Standard library only.
"""

import dataclasses
from pathlib import Path

import argmap
import ctokens
from argmap import ArgmapError, Check, Row
from cdecls import KEYWORDS, QUALIFIERS
from cheaders import MAX_EXPANSION_DEPTH

FIELDMAP = "fieldmap.csv"
COLUMNS = ("type", "member", "mode", "groups", "status", "header", "spelled_type", "origins", "note")
HEADER_DECLARATION = "header declaration"
OPERATOR_MODES = {"&=": "and-mask", "|=": "flags", "&": "flags"}  # the other operators keep the row's mode


def read_fieldmap(path: Path) -> list[Row]:
    """The rows of fieldmap.csv, or [] when the file does not exist. A row's callee is `type.member`, its slot 0."""
    if not path.is_file():
        return []
    return argmap.read_map(path, COLUMNS, _row)


def _row(values: dict, line: int, where: str) -> Row:
    if not values["type"] or not values["member"]:
        raise ArgmapError(f"{where}: a row needs a type and a member")
    callee = f"{argmap.normalized(values['type'])}.{values['member']}"
    return argmap.checked_row(values, callee, 0, HEADER_DECLARATION, line, where)


def type_and_member(row: Row) -> tuple[str, str]:
    type_name, member = row.callee.rsplit(".", 1)
    return type_name, member


def operator_row(row: Row, operator: str) -> Row:
    """ROW with the mode that OPERATOR gives: &= masks, |= and & take flags."""
    return dataclasses.replace(row, mode=OPERATOR_MODES.get(operator, row.mode))


def check_member(row: Row, bodies: list) -> Check:
    """BODIES: (file, members) of the row's type, one per closure that defines it, members as cheaders Member
    records."""
    if row.status != HEADER_DECLARATION:
        return Check(False, "unverified row")
    type_name, member = type_and_member(row)
    found = {tuple(members) for file, members in bodies if argmap.in_header(file, row.header)}
    if not found:
        return Check(False, f"no body of {type_name} in {row.header}")
    if len(found) > 1:
        return Check(False, f"{row.header} defines {type_name} in different ways")
    [members] = found
    spelled = [entry.spelled for entry in members if entry.name == member]
    if not spelled:
        return Check(False, f"{row.header}'s {type_name} has no member {member}")
    if argmap.normalized(spelled[0]) != row.spelled_type:
        return Check(False, f"{row.header} spells {member} {spelled[0]!r}, the row says {row.spelled_type!r}")
    return Check(True, "")


def named_bodies(closures: list, type_name: str, header: str) -> list:
    """(closure, (file, members)) per closure of CLOSURES in which TYPE_NAME names a body that HEADER defines."""
    found = []
    for closure in closures:
        type_id = Scope([closure], None, {}).body(type_name)
        if type_id is not None and argmap.in_header(closure.bodies[type_id].file, header):
            found.append((closure, (closure.bodies[type_id].file, tuple(closure.members[type_id]))))
    return found


def index_rows(rows: list[Row], closures: list) -> tuple[dict, list[str]]:
    """ROWS by (type id, member), with the type id that each row's type names in CLOSURES, and a warning per row
    whose type has no body there. Two rows that name one member fail."""
    scope = Scope(closures, None, {})
    keyed, warnings = {}, []
    for row in rows:
        type_name, member = type_and_member(row)
        type_id = scope.body(type_name)
        if type_id is None:
            warnings.append(f"fieldmap line {row.line}: type {type_name} has no struct or union body in the target "
                            "headers")
            continue
        key = (type_id, member)
        if key in keyed:
            raise ArgmapError(f"fieldmap lines {keyed[key].line} and {row.line} name one member, {type_id}.{member}")
        keyed[key] = row
    return keyed, warnings


def member_owners(closures: list) -> dict:
    """Member name -> {type id: spelled type} over every body in CLOSURES; the spelled type is None when two
    closures spell the member in different ways."""
    found = {}
    for closure in closures:
        for type_id, members in closure.members.items():
            for entry in members:
                owners = found.setdefault(entry.name, {})
                if owners.get(type_id, entry.spelled) != entry.spelled:
                    owners[type_id] = None
                elif type_id not in owners:
                    owners[type_id] = entry.spelled
    return found


class Scope:
    """The names that one function body sees: LOCALS (name -> spelled type), then SOURCE's file-scope names and
    typedefs (a cparse SourceFile, or None), then CLOSURES."""

    def __init__(self, closures: list, source, locals_: dict):
        self.closures, self.source, self.locals = closures, source, locals_

    def name_type(self, name: str) -> str | None:
        if name in self.locals:
            return self.locals[name]
        declared = self.source.names.get(name) if self.source else None
        if declared is not None:
            return declared.type if declared.kind == "variable" else None
        return self._agreed("variables", name, "spelled")

    def returns(self, name: str) -> str | None:
        if name in self.locals:
            return None
        declared = self.source.names.get(name) if self.source else None
        if declared is not None:
            return declared.type if declared.kind == "function" else None
        return self._agreed("functions", name, "returns")

    def typedef(self, name: str) -> str | None:
        if self.source and name in self.source.typedefs:
            return self.source.typedefs[name]
        return self._agreed("typedefs", name, "spelled")

    def _agreed(self, table: str, name: str, attribute: str):
        values = {getattr(record, attribute) for closure in self.closures
                  for record in getattr(closure, table).get(name, ())}
        return values.pop() if len(values) == 1 else None

    def members(self, type_id: str) -> tuple | None:
        """The members of TYPE_ID's body, when the closures that define it agree."""
        found = {tuple(closure.members[type_id]) for closure in self.closures if type_id in closure.members}
        return found.pop() if len(found) == 1 else None

    def body(self, spelling: str, depth: int = 0) -> str | None:
        """The type id of the struct or union body that SPELLING names, through typedefs; None for other types."""
        words = [word for word in spelling.split() if word not in QUALIFIERS]
        if not words or depth > MAX_EXPANSION_DEPTH:
            return None
        text = " ".join(words)
        tried = (text, f"struct {text}", f"union {text}") if len(words) == 1 else (text,)
        for type_id in tried:
            if self.members(type_id) is not None:
                return type_id
        unrolled = self.typedef(text) if len(words) == 1 else None
        return self.body(unrolled, depth + 1) if unrolled is not None and unrolled != text else None

    def dereferenced(self, spelling: str | None, depth: int = 0) -> str | None:
        """The type that a pointer or an array of SPELLING points to, through typedefs, or None."""
        words = spelling.split() if spelling is not None else []
        while words and words[-1] in QUALIFIERS:
            words.pop()
        if not words or "(" in words or depth > MAX_EXPANSION_DEPTH:
            return None
        if words[-1] == "*":
            return " ".join(words[:-1])
        if "[" in words:
            first = words.index("[")
            return " ".join(words[:first] + words[words.index("]", first) + 1:])
        core = [word for word in words if word not in QUALIFIERS]
        unrolled = self.typedef(core[0]) if len(core) == 1 else None
        return self.dereferenced(unrolled, depth + 1) if unrolled is not None and unrolled != core[0] else None

    def is_cast(self, texts: list[str]) -> bool:
        """TEXTS, the contents of a ( ) group, spell a pointer type or a typedef name."""
        words = [text for text in texts if text not in QUALIFIERS]
        if not words:
            return False
        return words[-1] == "*" or len(words) == 1 and self.typedef(words[0]) is not None

    def member(self, spelling: str | None, arrow: bool, name: str) -> tuple[str, str] | None:
        """The type id and the spelled type of member NAME of an object of type SPELLING, or of the object that
        SPELLING points to when ARROW; None when the declarations cannot tell."""
        if spelling is not None and arrow:
            spelling = self.dereferenced(spelling)
        type_id = self.body(spelling) if spelling is not None else None
        if type_id is None:
            return None
        found = [entry.spelled for entry in self.members(type_id) if entry.name == name]
        return (type_id, found[0]) if len(found) == 1 else None


def base_type(tokens, scope: Scope, depth: int = 0) -> str | None:
    """The spelled type of the expression TOKENS, a field spot's base, or None when SCOPE cannot tell."""
    tokens = list(tokens)
    layers = (len(tokens) - len(ctokens.unwrapped([token.text for token in tokens]))) // 2
    tokens = tokens[layers:len(tokens) - layers]
    if not tokens or depth > MAX_EXPANSION_DEPTH:
        return None
    first, last = tokens[0], tokens[-1]
    if len(tokens) == 1:
        return scope.name_type(first.text) if _is_name(first) else None
    if first.text == "*":
        return scope.dereferenced(base_type(tokens[1:], scope, depth + 1))
    if first.text == "(":
        cast = [token.text for token in tokens[1:ctokens.matching_closer(tokens, 0, len(tokens))]]
        if scope.is_cast(cast):
            return " ".join(cast)
    elif not _is_name(first):
        return None
    if tokens[-2].text in (".", "->") and _is_name(last):
        found = scope.member(base_type(tokens[:-2], scope, depth + 1), tokens[-2].text == "->", last.text)
        return found[1] if found else None
    opener = ctokens.matching_opener(tokens, len(tokens) - 1, -1) if last.text in ("]", ")") else None
    if last.text == "]" and opener:
        return scope.dereferenced(base_type(tokens[:opener], scope, depth + 1))
    if last.text == ")" and opener == 1 and _is_name(first):
        return scope.returns(first.text)
    return None


def _is_name(token) -> bool:
    return token.kind == "id" and token.text not in KEYWORDS
