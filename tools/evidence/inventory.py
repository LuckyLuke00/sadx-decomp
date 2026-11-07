"""Inventory: one site per mapped call argument and mapped field spot in the game source, with its value and the
names that may spell it.

build() does the work in memory:
1. It reads one closure per umbrella of the target header set and of each reference set.
2. It parses every source file under the source root.
3. It names each owner by its annotation address, or file:name (file#name at file scope) when it has none or when
   the address is not unique. A callee's role id is the address of the one annotated definition with that name,
   else its spelling ("ambiguous target" when two definitions share the name).
4. For each call whose callee has argmap rows, and is not a function-like macro, it makes one site per mapped
   argument. The prototype comes from the row's vendor header, else a target closure, else the source file; a call
   whose arity differs is unsupported, and a call with no prototype gets the flag "no prototype". The argument is
   evaluated under the target profile: a name the source declares is nonconstant, a name the target closures define
   is evaluated, anything else is unresolved. An ok value is converted to the parameter type, and the cover search
   (covers.py) looks for it among the names that the row takes, in every closure, each evaluated under the target
   profile.
5. Callees that a vendor header declares and that argmap.csv does not map get their literal arguments counted, for
   argmap-proposed.csv.
6. Each use of a placeholder macro (config "placeholders") is a placeholder site: the macro is its target, it has no
   slot and no value, and its prototype text holds the hash of the macro's definition. A literal inside a no-code
   macro gets the flag "literal inside a no-code macro".
7. Each field spot (cparse.py) whose member a fieldmap row maps (fields.py) is a field site: its target is the type
   id and the member, its slot the operator, its prototype text the member's spelled type. The base expression
   types through the declaration subset. When it does not, a member name whose every body has a row, with rows
   that take the same names and one spelling of the member, gives the target ?.member and the flag "member name
   only". The value converts to the member type. The operator sets the mode: &= masks, |= and & take flags. The
   counts: field spots, and the spots that are no site (bitfields, unmapped, untyped), case labels and raw-offset
   accesses. A body in the row's header that gives the member another type gives the flag "target member differs".
8. With reference symbols (symbols.py) in the evidence folder:
   - a call whose callee has no argmap row and whose role id has a reference prototype gets one site per enum slot,
     with that prototype (an enum converts as int);
   - a return with a value, in a function whose reference return type is an enum, is a return site: its target is
     the owner, its slot "return";
   - in a function with scope constants, a field spot with no fieldmap row and a value spot (cparse.py) that is a
     variable write or compare or a case label is a scope site. A variable site needs a nonconstant variable. Its
     target is the variable or the switch expression, its slot the operator or "case". The lvalue check runs over
     the function's values first (symbols.lvalue_check), keyed by the lvalue as written: field spots, variables and
     the switch expressions of case labels. Each value converts to its lvalue's type, when that resolves.
   A site of a reference-prototype row whose top candidate is one enumerator alone, under a C++ profile, gets the
   flag "one enumerator". Call arguments are no scope sites.
9. Each call in a function, other than a placeholder, a function-like macro and __except, is an owned call for
   pairs.py: its callee's role id, its position and each argument's numeric value, converted to the parameter type
   when a target closure or the source file declares the callee with a fitting arity.

A site is in coverage when its expression is constant: its status is ok, unresolved or unsupported. Only coverage
sites get ids: ledger.commit() gives them and commits the state, then write() puts inventory.csv and
argmap-proposed.csv in the evidence folder.

The target closures act as one: a name is answered by the first closure, in umbrella order, that knows it. When
another closure gives it a different answer, the site gets the flag "closures disagree". A name that no header the
file reaches through its own #include lines defines gets the flag "include".

Standard library only.
"""

import hashlib
import os
import sys
import time
from collections import Counter
from dataclasses import dataclass, field
from pathlib import Path

import argmap
import ceval
import cheaders
import covers
import cparse
import ctokens
import fields
import outputs
import symbols

sys.path.append(str(Path(__file__).resolve().parents[1]))  # tools/, after the standard library
import osutil  # noqa: E402

INVENTORY, PROPOSED = "inventory.csv", "argmap-proposed.csv"
COLUMNS = ("id", "kind", "file", "line", "column", "owner", "target", "slot", "callee", "argument", "expression", "status",
           "cause", "detail", "value", "type", "state", "mode", "row", "check", "flags", "candidates", "incomplete")
PROPOSED_COLUMNS = ("callee", "slot", "sites", "values", "header", "spelled_type", "sample_clusters",
                    "sample_spellings")
LITERAL_SUFFIXES = {"int": "", "unsigned int": "u", "long": "l", "unsigned long": "ul", "long long": "ll",
                    "unsigned long long": "ull"}
COVERED = (ceval.OK, ceval.UNRESOLVED, ceval.UNSUPPORTED)
APPLIED, OPEN = "applied", "open"
CALL, FIELD, PLACEHOLDER = "call", "field", "placeholder"  # site kinds; a placeholder row's status is PLACEHOLDER
CASE, VARIABLE, RETURN = ctokens.CASE, ctokens.VARIABLE, ctokens.RETURN  # the site kinds of value spots
KINDS = (CALL, FIELD, CASE, VARIABLE, RETURN, PLACEHOLDER)  # the site kinds, in report order
MEMBER_NAME_ONLY = "member name only"  # the flag of a field site that its member name alone types
PLACEHOLDER_NOTES = {"no-code": "the binary cannot tell this apart from no statement",
                     "code": "stands for code that has no name yet"}
VENDOR_ORIGINS_EXCLUDED = ("game", "")  # origins whose functions are not proposed for argmap rows
EXCEPT = "__except"  # an exception filter, which cparse reads as a call: no owned call


class InventoryError(Exception):
    """A source file that does not decode, or another input fault that stops the run."""


@dataclass
class Record:
    """One site: a mapped call argument, a mapped field spot, or a placeholder use."""
    file: str
    line: int
    column: int
    owner: str
    target: str
    slot: str  # the slot path: the outer calls as role#index, then this argument's index; a field spot's operator
    callee: str
    argument: str  # the argument as written, tokens joined by single spaces
    expression: str  # the normalized expression
    result: ceval.Result  # converted to the parameter type when it has one
    row: argmap.Row
    check: argmap.Check
    context: str
    flags: list = field(default_factory=list)
    search: covers.Search | None = None
    pool: object = None  # the Pool the search used
    cover_slot: covers.Slot | None = None  # the slot the search used
    accepted: tuple = ()  # the origins whose names the slot accepts; empty: any
    prototype: str = ""  # where the prototype comes from and its spelled parameters; "" when there is none
    spellings: tuple = ()  # spelling.Spelling per candidate, in rank order
    sampled: bool = False  # some sample tree reads the slot (spelling.Speller.reads)
    kind: str = CALL
    id: str = ""
    references: tuple = ()  # (build, reference value text, same) per reference build that compares it (pairs.py)

    @property
    def covered(self) -> bool:
        return self.result.status in COVERED

    @property
    def state(self) -> str:
        return APPLIED if self.result.ok and self.result.names and not self.result.literal else OPEN

    @property
    def value(self) -> str:
        return value_text(self.result)


@dataclass
class Pool:
    """The names one row takes at one parameter type."""
    names: list  # covers.Name records
    uncertain: set  # names whose definition sits in an unresolved branch
    disputed: dict  # name -> why its value is in doubt
    failed: Counter  # cause -> names that did not evaluate


@dataclass(frozen=True)
class OwnedCall:
    """A call in a function, as pairs.py compares it with the calls of other builds."""
    target: str  # the callee's role id
    file: str
    line: int
    column: int
    values: tuple  # per argument: (value, CType) when it evaluates to a number, else None
    floats: bool  # a parameter or a value is a float


@dataclass
class Inventory:
    records: list
    files: int = 0
    unsupported_files: list = field(default_factory=list)  # (file, reason)
    calls: int = 0
    unmapped: int = 0  # calls whose callee has no argmap row
    macro_calls: int = 0  # mapped callees that are function-like macros
    proposed: list = field(default_factory=list)  # rows of argmap-proposed.csv
    field_rows: list = field(default_factory=list)  # the fieldmap rows; [] without a fieldmap
    field_counts: Counter = field(default_factory=Counter)  # see step 7
    prototypes: dict = field(default_factory=dict)  # (callee, slot) -> (spelled parameters, variadic) from a header
    warnings: list = field(default_factory=list)
    closures: list = field(default_factory=list)  # (set name, closure)
    headers: object = None  # the Headers of the target closures
    seconds: dict = field(default_factory=dict)
    previous: Counter | None = None  # the coverage sites per kind of the generation before ledger.commit(); None on
    # a first run
    symbols: object = None  # the symbols.Symbols of the evidence folder; None without symbol files
    owned_calls: dict = field(default_factory=dict)  # owner id -> [OwnedCall] in callee order (step 9)
    references: list = field(default_factory=list)  # pairs.Report per reference build; set by the pipeline


def value_text(result: ceval.Result) -> str:
    if not result.ok or result.value is None:
        return ""
    return repr(result.value) if isinstance(result.value, float) else str(result.value)


class Headers:
    """The target closures as one, with the evaluator callbacks under the target profile."""

    def __init__(self, closures: list, profile):
        self.closures, self.profile = closures, profile
        self._owner, self._disagree = {}, {}

    @staticmethod
    def knows(closure, name: str) -> bool:
        return (name in closure.macros.table or name in closure.constants or name in closure.variables
                or name in closure.functions)

    def owner(self, name: str):
        """The first closure that knows NAME, or None."""
        if name not in self._owner:
            self._owner[name] = next((closure for closure in self.closures if self.knows(closure, name)), None)
        return self._owner[name]

    def answer(self, closure, name: str):
        alternatives = closure.macros.alternatives(name) if name in closure.macros.table else []
        if alternatives:
            return tuple(item.key() for item in alternatives)
        result = closure.resolve(name, self.profile)
        return (result.status, result.value, result.ctype) if result else None

    def disagree(self, name: str) -> bool:
        if name not in self._disagree:
            answers = {self.answer(closure, name) for closure in self.closures if self.knows(closure, name)}
            self._disagree[name] = len(answers) > 1
        return self._disagree[name]

    def origin_file(self, name: str) -> str:
        """The header that defines NAME in its first closure, "" when none does."""
        closure = self.owner(name)
        if closure is None:
            return ""
        definition = closure.macros.definition(name)
        if definition is not None:
            return definition.origin.file
        records = closure.constants.get(name) or closure.variables.get(name) or closure.functions.get(name)
        return records[0].origin.file if records else ""

    def expand(self, name: str):
        closure = self.owner(name)
        return closure.expand(name) if closure else None

    def resolve(self, name: str):
        closure = self.owner(name)
        return closure.resolve(name, self.profile) if closure else None

    def resolve_type(self, spelling: str):
        return next((found for found in (closure.resolve_type(spelling, self.profile) for closure in self.closures)
                     if found is not None), None)

    def is_function_macro(self, name: str) -> bool:
        closure = self.owner(name)
        return closure is not None and closure.macros.is_function(name)


@dataclass(frozen=True)
class Parameter:
    spelled: str  # "" for a variadic argument
    ctype: object  # CType or None


@dataclass(frozen=True)
class Prototype:
    parameters: tuple  # spelled types
    variadic: bool
    source: str  # header, target or source
    resolve_type: object  # spelled type -> CType
    file: str  # the file that declares it


def build(loaded, rows: list) -> Inventory:
    """LOADED: a config.Config. ROWS: the argmap rows. The fieldmap comes from the evidence folder."""
    seconds = {}
    start = time.perf_counter()
    target_closures = [cheaders.read(umbrella, loaded.target.config) for umbrella in loaded.target.umbrellas]
    references = [(header_set, cheaders.read(umbrella, header_set.config))
                  for header_set in loaded.references for umbrella in header_set.umbrellas]
    seconds["closures"] = time.perf_counter() - start
    profile = loaded.target.config.profile
    headers = Headers(target_closures, profile)
    every = [(loaded.target.name, closure) for closure in target_closures]
    every += [(header_set.name, closure) for header_set, closure in references]

    start = time.perf_counter()
    parsed = _parse_sources(loaded, target_closures, profile)
    seconds["parse"] = time.perf_counter() - start

    start = time.perf_counter()
    field_rows = fields.read_fieldmap(loaded.folder / fields.FIELDMAP)
    keyed, field_warnings = fields.index_rows(field_rows, target_closures)
    found_symbols = symbols.load(loaded.folder)
    reader = _Reader(loaded, rows, headers, every, parsed, keyed, found_symbols)
    inventory = reader.read()
    inventory.closures, inventory.headers, inventory.field_rows = every, headers, field_rows
    inventory.symbols = found_symbols
    inventory.seconds = {**seconds, "sites": time.perf_counter() - start}
    owners = {owner.name for source in parsed.values() for owner in source.owners if owner.kind == "function"}
    declared = {name for _, closure in every for name in closure.functions}
    inventory.warnings = argmap.hygiene(rows, owners, declared) + field_warnings
    return inventory


def _parse_sources(loaded, closures: list, profile) -> dict:
    """Relative path -> cparse.SourceFile, in path order."""
    sources = loaded.sources
    type_names = frozenset().union(*(closure.type_names for closure in closures))
    paths = sorted(path for path in sources.root.rglob("*") if path.suffix in sources.suffixes and path.is_file())
    parsed = {}
    for path in paths:
        relative = path.relative_to(loaded.root).as_posix()
        try:
            text = path.read_bytes().decode(sources.encoding)
        except UnicodeDecodeError as error:
            raise InventoryError(f"{relative} does not decode as {sources.encoding}: {error}") from None
        parsed[relative] = cparse.parse(text, relative, profile, sources.annotation, type_names)
    return parsed


class _Reader:
    def __init__(self, loaded, rows, headers: Headers, every: list, parsed: dict, field_rows: dict, found_symbols):
        self.loaded, self.headers, self.every, self.parsed = loaded, headers, every, parsed
        self.symbols = found_symbols  # symbols.Symbols or None
        self.field_rows = field_rows  # (type id, member) -> fieldmap row
        self.mapped_members = {member for _, member in field_rows}
        self.member_owners = fields.member_owners(headers.closures)
        self.profile = headers.profile
        self.rows = {}
        for row in rows:
            self.rows.setdefault(row.callee, {})[row.slot] = row
        self.source_names = {name for source in parsed.values() for name in source.names}
        self.addresses = Counter()
        self.definitions = {}  # function name -> set of addresses
        for source in parsed.values():
            for owner in source.owners:
                found = {note.address.lower() for note in owner.annotations}
                self.addresses.update(found)
                if owner.kind == "function" and len(found) == 1:
                    self.definitions.setdefault(owner.name, set()).update(found)
        self.edges = {}
        for _, closure in every:
            for start, _, end in closure.edges:
                self.edges.setdefault(cheaders.canonical(start), set()).add(cheaders.canonical(end))
        self.pools, self.checks, self.proposals, self.origins, self.prototypes = {}, {}, {}, {}, {}

    def read(self) -> Inventory:
        inventory = Inventory([])
        for relative, source in self.parsed.items():
            inventory.files += 1
            if source.unsupported:
                inventory.unsupported_files.append((relative, source.unsupported))
                continue
            reachable = self.reachable(relative, source)
            owner_ids = [self.owner_id(relative, owner) for owner in source.owners]
            for call in source.calls:
                inventory.calls += 1
                if self.is_owned(call, source):
                    owned = self.owned_call(call, source)
                    inventory.owned_calls.setdefault(owner_ids[call.owner][0], []).append(owned)
                kind = self.loaded.placeholders.get(call.callee)
                if kind is not None:
                    inventory.records.append(self.placeholder(call, kind, source, owner_ids[call.owner]))
                    continue
                rows = self.rows.get(call.callee) or self.reference_rows(call.callee)
                if not rows:
                    inventory.unmapped += 1
                    self.propose(call, source)
                    continue
                if self.headers.is_function_macro(call.callee):
                    inventory.macro_calls += 1
                    continue
                inventory.records += self.sites(call, rows, source, owner_ids[call.owner], reachable)
            scoped = self.scoped(source, owner_ids)
            for spot in source.spots:
                record = self.field_site(spot, source, owner_ids[spot.owner], reachable, inventory.field_counts,
                                         scoped.get(spot.owner))
                if record is not None:
                    inventory.records.append(record)
            for spot in source.values:
                record = self.value_site(spot, source, owner_ids[spot.owner], reachable, scoped.get(spot.owner))
                if record is not None:
                    inventory.records.append(record)
            inventory.field_counts["case labels"] += source.case_labels
            inventory.field_counts["raw offsets"] += source.raw_offsets
        inventory.proposed = self.proposed_rows()
        inventory.prototypes = self.prototypes
        return inventory

    # Owners, targets and includes

    def owner_id(self, relative: str, owner: cparse.Owner) -> tuple[str, str]:
        found = sorted({note.address.lower() for note in owner.annotations})
        if len(found) == 1 and self.addresses[found[0]] == 1:
            return found[0], ""
        fallback = f"{relative}:{owner.name}" if owner.kind == "function" else f"{relative}#{owner.name}"
        return fallback, "ambiguous owner" if found else ""

    def role(self, name: str) -> tuple[str, str]:
        found = self.definitions.get(name, set())
        if len(found) == 1:
            return next(iter(found)), ""
        return name, "ambiguous target" if found else ""

    def reachable(self, relative: str, source: cparse.SourceFile) -> set:
        """The canonical paths of the headers that the file's own #include lines reach."""
        folder = str((self.loaded.root / relative).parent)
        search = self.loaded.target.config.search_path
        found, stack = set(), []
        for include in source.includes:
            folders = search if include.angle else (folder,) + search
            path = next((os.path.join(item, include.name) for item in folders
                         if os.path.isfile(os.path.join(item, include.name))), None)
            if path:
                stack.append(cheaders.canonical(path))
        while stack:
            path = stack.pop()
            if path not in found:
                found.add(path)
                stack.extend(self.edges.get(path, ()))
        return found

    # Sites

    def sites(self, call: cparse.Call, rows: dict, source, owner: tuple, reachable: set) -> list:
        owner_id, owner_flag = owner
        target, target_flag = self.role(call.callee)
        prefix = "".join(f"{self.role(callee)[0]}#{index}/" for callee, index in call.outer)
        context = _context(call)
        locals_ = source.owners[call.owner].names
        records = []
        for index, row in sorted(rows.items()):
            if index > len(call.arguments):
                continue
            tokens = call.arguments[index - 1]
            prototype = self.prototype(row, call.callee, source)
            if prototype is not None and prototype.source in ("header", "target"):
                self.prototypes.setdefault((call.callee, index), (prototype.parameters, prototype.variadic))
            flags = [flag for flag in (owner_flag, target_flag) if flag]
            result = self.evaluate(tokens, locals_, source)
            parameter = None
            if prototype is None:
                flags.append("no prototype")
            elif not arity_fits(len(call.arguments), prototype):
                if result.status != ceval.NONCONSTANT:
                    result = ceval.failure(ceval.UNSUPPORTED, "arity",
                                           f"{len(call.arguments)} arguments, the prototype has "
                                           f"{len(prototype.parameters)}")
            else:
                parameter = _parameter(prototype, index)
                if parameter.ctype is not None and not parameter.spelled == "" and result.ok:
                    result = ceval.convert(result, parameter.ctype, self.profile)
            flags += self.name_flags(result, reachable)
            flags += self.prototype_flags(row, call.callee, prototype, source)
            record = Record(source.path, call.line, call.column, owner_id, target, f"{prefix}{index}", call.callee,
                            ctokens.spelling(list(tokens)), normalized(tokens, self.profile), result, row,
                            self.check(row), context, flags,
                            accepted=self.accepted(row, prototype.file if prototype else None),
                            prototype=_prototype_text(prototype))
            if record.covered and result.ok:
                record.search, record.pool, record.cover_slot = self.search(result, row, parameter)
                if symbols.one_enumerator(record.search, row, self.profile):
                    record.flags.append(symbols.ONE_ENUMERATOR)
            records.append(record)
        return records

    def is_owned(self, call: cparse.Call, source: cparse.SourceFile) -> bool:
        """Whether CALL is an owned call (step 9)."""
        return (source.owners[call.owner].kind == "function" and call.callee not in self.loaded.placeholders
                and call.callee != EXCEPT and not self.headers.is_function_macro(call.callee))

    def owned_call(self, call: cparse.Call, source: cparse.SourceFile) -> OwnedCall:
        prototype = self.declared_prototype(call.callee, source)
        if prototype is not None and not arity_fits(len(call.arguments), prototype):
            prototype = None
        locals_ = source.owners[call.owner].names
        values, floats = [], False
        for index, tokens in enumerate(call.arguments, 1):
            parameter = _parameter(prototype, index) if prototype is not None else None
            ctype = parameter.ctype if parameter is not None and parameter.spelled else None
            floats = floats or (ctype is not None and ctype.kind == "float")
            result = self.evaluate(tokens, locals_, source)
            if result.ok and ctype is not None:
                result = ceval.convert(result, ctype, self.profile)
            if not result.ok or not isinstance(result.value, (int, float)):
                values.append(None)
                continue
            floats = floats or isinstance(result.value, float)
            values.append((result.value, result.ctype))
        return OwnedCall(self.role(call.callee)[0], source.path, call.line, call.column, tuple(values), floats)

    def placeholder(self, call: cparse.Call, kind: str, source, owner: tuple) -> Record:
        """One use of a placeholder macro of KIND, no-code or code."""
        owner_id, owner_flag = owner
        flags = [owner_flag] if owner_flag else []
        if kind == "no-code" and any(token.kind in ("num", "char") for tokens in call.arguments for token in tokens):
            flags.append("literal inside a no-code macro")
        texts = [ctokens.spelling(list(tokens)) for tokens in call.arguments]
        row = argmap.Row(call.callee, 0, "", (), PLACEHOLDER, "", "", (), kind, 0)
        return Record(source.path, call.line, call.column, owner_id, call.callee, "", call.callee,
                      f"{call.callee}({', '.join(texts)})",
                      " , ".join(normalized(tokens, self.profile) for tokens in call.arguments), ceval.Result(ceval.OK),
                      row, argmap.Check(True, ""), _context(call), flags, prototype=self.definition_text(call.callee),
                      kind=PLACEHOLDER)

    def field_site(self, spot: cparse.Spot, source, owner: tuple, reachable: set, counts: Counter,
                   scoped: tuple | None = None) -> Record | None:
        """The site of one field spot, or None when no fieldmap row maps it and SCOPED (the owner's entry of
        scoped()) makes it no scope site; COUNTS gets the reason."""
        counts["spots"] += 1
        locals_ = source.owners[spot.owner].names
        scope = fields.Scope(self.headers.closures, source, locals_)
        typed = scope.member(fields.base_type(spot.base, scope), spot.arrow, spot.member)
        by_name = typed is None
        row, reason = None, "unmapped"
        if not by_name:
            row = self.field_rows.get((typed[0], spot.member))
        elif spot.member in self.mapped_members:
            fallback = self.member_name_only(spot.member)
            if fallback is None:
                reason = "untyped"
            else:
                typed, row = fallback
        if typed is not None and ":" in typed[1].split():
            counts["bitfields"] += 1
            return None
        if row is None and scoped is not None and spot.operator in symbols.SCOPE_OPERATORS:
            counts["scope sites"] += 1
            target = f"{typed[0]}.{spot.member}" if typed else f"?.{spot.member}"
            key = _lvalue_key([token.text for token in spot.base] + ["->" if spot.arrow else ".", spot.member])
            return self.scope_site(spot, FIELD, target, key, source, owner, reachable, scoped,
                                   typed[1] if typed else None)
        if row is None:
            counts[reason] += 1
            return None
        type_id, spelled = typed
        owner_id, owner_flag = owner
        flags = [flag for flag in (owner_flag, MEMBER_NAME_ONLY if by_name else "") if flag]
        row = fields.operator_row(row, spot.operator)
        result = self.evaluate(spot.value, locals_, source)
        ctype = self.resolve_type(spelled, source)
        if ctype is not None and result.ok:
            result = ceval.convert(result, ctype, self.profile)
        flags += self.name_flags(result, reachable) + self.member_flags(row, ctype)
        target = f"?.{spot.member}" if by_name else f"{type_id}.{spot.member}"
        record = Record(source.path, spot.line, spot.column, owner_id, target, spot.operator, row.callee,
                        ctokens.spelling(list(spot.value)), normalized(spot.value, self.profile), result, row,
                        self.member_check(row), _context(spot), flags,
                        accepted=self.accepted(row, self.body_file(row, type_id)), prototype=f"member {spelled}",
                        kind=FIELD)
        if record.covered and result.ok:
            record.search, record.pool, record.cover_slot = self.search(result, row, Parameter(spelled, ctype))
        return record

    def reference_rows(self, callee: str) -> dict:
        """Slot -> Row for the enum slots of the reference prototype of CALLEE's role id; {} without one."""
        if self.symbols is None:
            return {}
        return self.symbols.call_rows(self.role(callee)[0], callee)

    def scoped(self, source: cparse.SourceFile, owner_ids: list) -> dict:
        """Owner index -> (address, {lvalue: the scopes that pass the lvalue check}) for each function of SOURCE
        whose owner id has scope constants. The lvalue check takes the ok integer values of the function's field
        spots with a scope operator, its variable spots and its case labels."""
        if self.symbols is None:
            return {}
        spots = {index: [] for index, (owner_id, _) in enumerate(owner_ids)
                 if owner_id in self.symbols.scopes and source.owners[index].kind == "function"}
        for spot in source.spots:
            if spot.owner in spots and spot.operator in symbols.SCOPE_OPERATORS:
                texts = [token.text for token in spot.base] + ["->" if spot.arrow else ".", spot.member]
                spots[spot.owner].append((_lvalue_key(texts), spot.value))
        for spot in source.values:
            if spot.owner in spots and spot.kind != RETURN:
                spots[spot.owner].append((_lvalue_key([token.text for token in spot.lvalue]), spot.value))
        minimum = self.loaded.thresholds["scope_min_values"]
        found = {}
        for index, entries in spots.items():
            locals_ = source.owners[index].names
            results = [(key, self.evaluate(tokens, locals_, source)) for key, tokens in entries]
            pairs = [(key, result.value) for key, result in results if result.ok and isinstance(result.value, int)]
            address = owner_ids[index][0]
            found[index] = (address, symbols.lvalue_check(pairs, self.symbols.scopes[address], minimum))
        return found

    def value_site(self, spot: cparse.ValueSpot, source, owner: tuple, reachable: set,
                   scoped: tuple | None) -> Record | None:
        """The site of one value spot: a return in a function whose reference return type is an enum, or a scope
        site (a nonconstant variable or a case label, in a function with scope constants). None for other spots."""
        if spot.kind == RETURN:
            row = self.symbols.return_row(owner[0], source.owners[spot.owner].name) if self.symbols else None
            if row is None:
                return None
            return self.symbol_site(spot, RETURN, owner[0], "return", source, owner, reachable, row,
                                    row.spelled_type, [])
        if scoped is None:
            return None
        if spot.kind == VARIABLE:
            locals_ = source.owners[spot.owner].names
            if self.evaluate(spot.lvalue, locals_, source).status != ceval.NONCONSTANT:
                return None
            spelled = fields.Scope(self.headers.closures, source, locals_).name_type(spot.lvalue[0].text)
        else:
            scope = fields.Scope(self.headers.closures, source, source.owners[spot.owner].names)
            spelled = fields.base_type(spot.lvalue, scope)
        key = _lvalue_key([token.text for token in spot.lvalue])
        return self.scope_site(spot, spot.kind, key, key, source, owner, reachable, scoped, spelled)

    def scope_site(self, spot, kind: str, target: str, key: str, source, owner: tuple, reachable: set,
                   scoped: tuple, spelled: str | None) -> Record:
        """A scope site of SPOT, whose lvalue is KEY: it takes the constants of the scopes that pass the lvalue check
        for KEY, with the flag "lvalue check", else every scope constant of the function."""
        address, passed = scoped
        flags = [symbols.LVALUE_CHECK] if key in passed else []
        row = self.symbols.scope_row(address, passed.get(key, ()))
        return self.symbol_site(spot, kind, target, spot.operator, source, owner, reachable, row, spelled, flags)

    def symbol_site(self, spot, kind: str, target: str, slot: str, source, owner: tuple, reachable: set,
                    row: argmap.Row, spelled: str | None, flags: list) -> Record:
        """A site whose row comes from the reference symbols: SPOT's value, converted to SPELLED's type when it
        resolves, searched among the row's names."""
        owner_id, owner_flag = owner
        locals_ = source.owners[spot.owner].names
        ctype = self.reference_type(spelled, source) if spelled is not None else None
        result = self.evaluate(spot.value, locals_, source)
        if ctype is not None and result.ok:
            result = ceval.convert(result, ctype, self.profile)
        flags = ([owner_flag] if owner_flag else []) + flags + self.name_flags(result, reachable)
        record = Record(source.path, spot.line, spot.column, owner_id, target, slot, source.owners[spot.owner].name,
                        ctokens.spelling(list(spot.value)), normalized(spot.value, self.profile), result, row,
                        self.check(row), _context(spot), flags, accepted=row.origins,
                        prototype=f"{kind} {spelled if spelled is not None else '?'}", kind=kind)
        if record.covered and result.ok:
            parameter = Parameter(spelled, ctype) if ctype is not None else None
            record.search, record.pool, record.cover_slot = self.search(result, row, parameter)
            if symbols.one_enumerator(record.search, row, self.profile):
                record.flags.append(symbols.ONE_ENUMERATOR)
        return record

    def reference_type(self, spelled: str, source: cparse.SourceFile | None = None):
        """The type of SPELLED: int for an enum of the reference symbols, else as the target headers (and SOURCE)
        resolve it."""
        if symbols.enum_slot(spelled):
            return self.profile.int_type("int")
        return self.resolve_type(spelled, source) if source is not None else self.headers.resolve_type(spelled)

    def member_name_only(self, member: str):
        """((type id, spelled type), row) for MEMBER when its base does not type: every body that holds a member of
        that name has a fieldmap row for it, the rows take the same names, and the member has one spelling. The
        type id is the first in order. None otherwise."""
        owners = self.member_owners.get(member, {})
        rows = [self.field_rows.get((type_id, member)) for type_id in sorted(owners)]
        spellings = set(owners.values())
        if not rows or None in rows or None in spellings or len(spellings) > 1:
            return None
        if len({(row.mode, row.groups, row.origins) for row in rows}) > 1:
            return None
        type_id = min(owners)
        return (type_id, owners[type_id]), rows[0]

    def evaluate(self, tokens, locals_: dict, source: cparse.SourceFile) -> ceval.Result:
        """TOKENS under the target profile; the names that LOCALS_ and SOURCE declare are nonconstant."""
        return ceval.evaluate(list(tokens), self.profile, expand=self.headers.expand,
                              resolve=lambda name: self.resolve(name, locals_, source),
                              resolve_type=lambda spelling: self.resolve_type(spelling, source))

    def definition_text(self, name: str) -> str:
        """"definition" and the hash of NAME's alternatives in the first target closure that knows it."""
        closure = self.headers.owner(name)
        if closure is None:
            return "no definition"
        answer = repr(self.headers.answer(closure, name))
        return "definition " + hashlib.sha256(answer.encode("utf-8")).hexdigest()[:16]

    def resolve(self, name: str, locals_: dict, source: cparse.SourceFile):
        if name in locals_:
            return ceval.failure(ceval.NONCONSTANT, "variable", name)
        declared = source.names.get(name)
        if declared is not None:
            return ceval.failure(ceval.NONCONSTANT, declared.kind, name)
        if name in self.source_names:
            return ceval.failure(ceval.NONCONSTANT, "source declaration", name)
        return self.headers.resolve(name)

    def resolve_type(self, spelling: str, source: cparse.SourceFile):
        return self.headers.resolve_type(source.typedefs.get(spelling, spelling))

    def name_flags(self, result: ceval.Result, reachable: set) -> list:
        if not result.ok:
            return []
        flags = []
        if any(self.headers.disagree(name) for name in result.names):
            flags.append("closures disagree")
        files = [self.headers.origin_file(name) for name in result.names]
        if any(file and file != "<predefined>" and cheaders.canonical(file) not in reachable for file in files):
            flags.append("include")
        if result.names and result.literal:
            flags.append("partial")
        return flags

    # Prototypes

    def prototype(self, row: argmap.Row, callee: str, source: cparse.SourceFile) -> Prototype | None:
        if row.status == symbols.REFERENCE_PROTOTYPE:
            parameters, variadic = self.symbols.parameters(self.role(callee)[0])
            return Prototype(parameters, variadic, "reference", self.reference_type, "")
        found = self.header_functions(row)
        if found:
            closure, record = found[0]
            return Prototype(record.parameters, record.variadic, "header",
                             lambda spelling: closure.resolve_type(spelling, self.profile), record.origin.file)
        return self.declared_prototype(callee, source)

    def declared_prototype(self, callee: str, source: cparse.SourceFile) -> Prototype | None:
        """CALLEE's prototype in the first target closure that declares it, else in SOURCE."""
        closure = self.headers.owner(callee)
        if closure is not None and callee in closure.functions:
            record = closure.functions[callee][0]
            return Prototype(record.parameters, record.variadic, "target", self.headers.resolve_type,
                             record.origin.file)
        declared = source.prototypes.get(callee)
        if declared is not None:
            return Prototype(declared.parameters, declared.variadic, "source",
                             lambda spelling: self.resolve_type(spelling, source), str(self.loaded.root / source.path))
        return None

    def accepted(self, row: argmap.Row, file: str | None) -> tuple:
        """The origins whose names the slot accepts: the row's, else the origin of FILE, the file that declares the
        callee or defines the member's body. Empty when neither is known; then no origin is counterevidence."""
        if row.origins or file is None:
            return row.origins
        found = self.origin(file)
        return (found,) if found else ()

    def prototype_flags(self, row: argmap.Row, callee: str, prototype: Prototype | None, source) -> list:
        """Counterevidence: a target or source prototype that spells the row's argument otherwise."""
        if prototype is None or prototype.source != "header":
            return []
        others = [(record.parameters, record.variadic) for record in self.target_functions(callee)]
        declared = source.prototypes.get(callee)
        if declared is not None:
            others.append((declared.parameters, declared.variadic))
        own = _spelled(prototype.parameters, row.slot)
        if any(_spelled(parameters, row.slot) not in (own, None) for parameters, _ in others):
            return ["target prototype differs"]
        return []

    def target_functions(self, callee: str) -> list:
        return [record for closure in self.headers.closures for record in closure.functions.get(callee, ())]

    def header_functions(self, row: argmap.Row) -> list:
        """(closure, record) per prototype of the row's callee in the row's header, as the game sees that header. The
        row's origins are the origins of the names it accepts, not of its header, so they do not filter here."""
        if not row.header:
            return []
        return self.in_targets_first(lambda closures: [
            (closure, record) for closure in closures for record in closure.functions.get(row.callee, ())
            if argmap.in_header(record.origin.file, row.header)])

    def header_bodies(self, row: argmap.Row) -> list:
        """(closure, (file, members)) per body that the row's type names in the row's header, as the game sees that
        header."""
        if not row.header:
            return []
        type_name, _ = fields.type_and_member(row)
        return self.in_targets_first(lambda closures: fields.named_bodies(closures, type_name, row.header))

    def body_file(self, row: argmap.Row, type_id: str) -> str | None:
        """The file that defines the member's body: the row's header, as the game sees it, else the first target
        closure that defines TYPE_ID."""
        bodies = self.header_bodies(row)
        if bodies:
            _, (file, _) = bodies[0]
            return file
        return next((closure.bodies[type_id].file for closure in self.headers.closures if type_id in closure.bodies),
                    None)

    def in_targets_first(self, find) -> list:
        """FIND(closures) on the target closures; on the reference closures when the targets give nothing."""
        targets = self.headers.closures
        return find(targets) or find([closure for _, closure in self.every[len(targets):]])

    def member_flags(self, row: argmap.Row, ctype) -> list:
        """Counterevidence: a body in the row's header gives the member another type than the target headers do."""
        _, member = fields.type_and_member(row)
        theirs = [closure.resolve_type(entry.spelled, self.profile) for closure, (_, members) in self.header_bodies(row)
                  for entry in members if entry.name == member]
        if ctype is not None and any(other is not None and other.shape() != ctype.shape() for other in theirs):
            return ["target member differs"]
        return []

    def origin(self, file: str) -> str:
        if file not in self.origins:
            self.origins[file] = self.loaded.origin(file)
        return self.origins[file]

    def check(self, row: argmap.Row) -> argmap.Check:
        if row.status in symbols.STATUSES:
            return self.symbols.check(row)
        key = (row.callee, row.slot)
        if key not in self.checks:
            functions = [record for _, record in self.header_functions(row)]
            self.checks[key] = argmap.check_prototype(row, functions)
        return self.checks[key]

    def member_check(self, row: argmap.Row) -> argmap.Check:
        key = (row.callee, row.slot)
        if key not in self.checks:
            self.checks[key] = fields.check_member(row, [body for _, body in self.header_bodies(row)])
        return self.checks[key]

    # Candidates

    def search(self, result: ceval.Result, row: argmap.Row, parameter: Parameter | None):
        ctype = parameter.ctype if parameter is not None and parameter.ctype is not None else result.ctype
        variadic = parameter is not None and parameter.spelled == ""
        kind = covers.slot_kind(parameter.spelled if parameter else "", ctype, self.profile.boolean_names)
        if kind is None or not isinstance(result.value, int):
            return None, None, None
        pool = self.pool(row, ctype)
        slot = covers.Slot(kind, row.mode, ctype.bits, variadic)
        thresholds = self.loaded.thresholds
        found = covers.search(result.value, slot, pool.names, thresholds["cover_budget"], thresholds["composite_terms"])
        return found, pool, slot

    def pool(self, row: argmap.Row, ctype) -> Pool:
        key = (row.callee, row.slot, row.status, row.groups, ctype)
        if key in self.pools:
            return self.pools[key]
        if row.status in symbols.STATUSES:
            self.pools[key] = self.reference_pool(row, ctype)
            return self.pools[key]
        values, uncertain, disputed, failed = {}, set(), {}, Counter()
        for set_name, closure in self.every:
            for name in sorted(set(closure.macros.table) | set(closure.constants)):
                if not row.takes(name) or closure.macros.is_function(name):
                    continue
                raw = ceval.evaluate(name, self.profile, **closure.callbacks(self.profile))
                result = ceval.convert(raw, ctype, self.profile)
                if not result.ok:
                    failed[result.cause] += 1
                    continue
                if closure.profile is not self.profile:
                    own = ceval.evaluate(name, closure.profile, **closure.callbacks())
                    if own.ok and own.value != raw.value:
                        disputed[name] = f"{closure.profile.name} gives {own.value}"
                origin_file, certain = _definition(closure, name)
                if not certain:
                    uncertain.add(name)
                entry = values.setdefault((name, result.value), [raw.ctype.kind == "pointer", set()])
                entry[1].add(self.origin(origin_file) or set_name)
        names = []
        for (name, value), (pointer, origins) in sorted(values.items()):
            names.append(covers.Name(name, value, pointer, tuple(sorted(origins))))
        for name, count in Counter(name for name, _ in values).items():
            if count > 1:
                disputed[name] = "closures give different values"
        self.pools[key] = Pool(names, uncertain, disputed, failed)
        return self.pools[key]

    def reference_pool(self, row: argmap.Row, ctype) -> Pool:
        """The names of a reference-symbol row, converted to CTYPE. A name that the target headers define with
        another value is disputed."""
        names, disputed, failed = [], {}, Counter()
        for name in self.symbols.names(row):
            result = ceval.convert(ceval.Result(ceval.OK, name.value, self.profile.int_type("int")), ctype, self.profile)
            if not result.ok:
                failed[result.cause] += 1
                continue
            names.append(covers.Name(name.name, result.value, False, name.origins))
            known = ceval.evaluate(name.name, self.profile, expand=self.headers.expand, resolve=self.headers.resolve,
                                   resolve_type=self.headers.resolve_type)
            if known.ok and known.value != name.value:
                disputed[name.name] = f"target headers give {known.value}"
        return Pool(names, set(), disputed, failed)

    # Proposals

    def propose(self, call: cparse.Call, source: cparse.SourceFile):
        record = next((record for _, closure in self.every for record in closure.functions.get(call.callee, ())
                       if self.origin(record.origin.file) not in VENDOR_ORIGINS_EXCLUDED), None)
        if record is None:
            return
        for index, tokens in enumerate(call.arguments, 1):
            if not tokens or any(token.kind not in ("num", "char", "punct") for token in tokens):
                continue
            result = ceval.evaluate(list(tokens), self.profile)
            if result.ok and isinstance(result.value, int):
                entry = self.proposals.setdefault((call.callee, index), [Counter(), record])
                entry[0][result.value] += 1
                self.prototypes.setdefault((call.callee, index), (record.parameters, record.variadic))

    def proposed_rows(self) -> list:
        rows = []
        for (callee, index), (values, record) in self.proposals.items():
            spelled = record.parameters[index - 1] if index <= len(record.parameters) else ""
            rows.append((callee, index, sum(values.values()),
                         " ".join(str(value) for value, _ in values.most_common(5)),
                         os.path.basename(record.origin.file), spelled, "", ""))  # the sample columns: corpus.py
        return sorted(rows, key=lambda row: (-row[2], row[0], row[1]))


def _context(found) -> str:
    """The hash of the statement that holds FOUND, a call or a field spot, and the statement before it: for
    suggestions only."""
    return hashlib.sha256(f"{found.statement}\n{found.previous}".encode("utf-8")).hexdigest()[:16]


def _lvalue_key(texts: list) -> str:
    """An lvalue as the lvalue check keys it: its tokens, outer parentheses dropped."""
    return " ".join(ctokens.unwrapped(texts))


def _prototype_text(prototype: Prototype | None) -> str:
    if prototype is None:
        return ""
    parameters = prototype.parameters + (("...",) if prototype.variadic else ())
    return f"{prototype.source}: ({', '.join(parameters)})"


def arity_fits(count: int, prototype: Prototype) -> bool:
    fixed = len(prototype.parameters)
    return count == fixed or (prototype.variadic and count >= fixed)


def _parameter(prototype: Prototype, index: int) -> Parameter:
    if index > len(prototype.parameters):
        return Parameter("", None)
    spelled = argmap.normalized(prototype.parameters[index - 1])
    return Parameter(spelled, prototype.resolve_type(spelled))


def _spelled(parameters: tuple, slot: int) -> str | None:
    return argmap.normalized(parameters[slot - 1]) if slot <= len(parameters) else None


def _definition(closure, name: str) -> tuple[str, bool]:
    """The file and certainty of NAME's one definition. A name with several alternatives counts as uncertain."""
    definition = closure.macros.definition(name)
    if definition is not None:
        return definition.origin.file, definition.origin.certain
    records = closure.constants.get(name)
    if records and name not in closure.macros.table:
        return records[0].origin.file, all(record.origin.certain for record in records)
    return "", False


def normalized(tokens, profile) -> str:
    """The expression as identity sees it: outer parentheses dropped, each integer literal as its value with the
    suffix that names its type (0x10 -> 16, 0x80000000 -> 2147483648u). Other tokens keep their spelling."""
    texts = ctokens.unwrapped([token.text for token in tokens])
    for index, token in enumerate(texts):
        if token[:1].isdigit():
            result = ceval.evaluate(token, profile)
            if result.ok and result.ctype.kind == "int" and result.ctype.name in LITERAL_SUFFIXES:
                texts[index] = f"{result.value}{LITERAL_SUFFIXES[result.ctype.name]}"
    return " ".join(texts)


# Writing


def write(folder: Path, inventory: Inventory, generation: int):
    """inventory.csv and argmap-proposed.csv in FOLDER, for state generation GENERATION."""
    osutil.write_whole(folder / INVENTORY, format_inventory(inventory, generation))
    osutil.write_whole(folder / PROPOSED, outputs.csv_text("argmap-proposed", generation, PROPOSED_COLUMNS,
                                                           inventory.proposed))


def format_inventory(inventory: Inventory, generation: int) -> str:
    rows = []
    for record in inventory.records:
        result, search = record.result, record.search
        rows.append((record.id, record.kind, record.file, record.line, record.column, record.owner, record.target, record.slot,
                     record.callee, record.argument, record.expression, result.status, result.cause, result.detail,
                     record.value, result.ctype.name if result.ok and result.ctype else "", record.state,
                     record.row.mode, record.row.status, "pass" if record.check.passed else record.check.reason,
                     " ".join(record.flags),
                     "; ".join(candidate.text for candidate in search.candidates) if search else "",
                     "yes" if search and search.incomplete else ""))
    return outputs.csv_text("evidence-inventory", generation, COLUMNS, rows)


def summary(inventory: Inventory) -> list[str]:
    """The counts for the console."""
    records = inventory.records
    statuses = Counter(record.result.status for record in records)
    kinds = Counter(record.kind for record in records)
    causes = Counter((record.result.status, record.result.cause) for record in records if not record.result.ok)
    found = sum(1 for record in records if record.search and record.search.candidates)
    lines = [f"files {inventory.files} ({len(inventory.unsupported_files)} unsupported), calls {inventory.calls}, "
             f"unmapped {inventory.unmapped}, macro callees {inventory.macro_calls}",
             f"sites {len(records)} (" + ", ".join(f"{kind} {count}" for kind, count in sorted(kinds.items()))
             + "): " + ", ".join(f"{status} {count}" for status, count in statuses.most_common()),
             f"with a candidate {found}, proposals {len(inventory.proposed)}",
             "seconds: " + ", ".join(f"{name} {value:.1f}" for name, value in inventory.seconds.items())]
    lines += [f"  {status} {cause}: {count}" for (status, cause), count in causes.most_common(12)]
    lines += [f"  unsupported file {file}: {reason}" for file, reason in inventory.unsupported_files[:5]]
    lines += [f"  warning: {warning}" for warning in inventory.warnings]
    return lines
