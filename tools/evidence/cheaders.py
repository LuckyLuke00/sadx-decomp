"""Header reader: the macros and declarations of one include closure, read with a three-valued preprocessor.

read() starts at one header (an umbrella) and follows its #include lines. A quoted name searches the including
file's folder, then the search path; an angle name searches the search path only. Each file is read once per closure,
by its canonical path, which models include guards and #pragma once. A missing file is reported, and so is an
#include of a macro; reading goes on without them.

Conditions are three-valued: true, false or unresolved. An identifier in #if that is not defined and not in the
configuration's known-undefined list makes the condition unresolved, never 0. That differs from a real preprocessor on
purpose, so that a guess is never taken for a fact. `defined X` of a name that was never defined is false in a closed
world (an umbrella closure) and unresolved in an open world (a header read alone), unless the name is known to be
undefined. Nothing in a false branch is read. An unresolved branch is read with every definition and declaration in
it marked uncertain.

Each macro name keeps a list of alternatives: a definition, "undefined" (after #undef or for a known-undefined name),
"never defined" or "unknown" (open world). A definition in a live region replaces the list. One in an unresolved
region adds an alternative; equal alternatives merge. A name with more alternatives than the branch cap becomes
"truncated". A name with more than one alternative is unresolved wherever it is used.

An include guard counts as live: the first directive is `#ifndef G` (or `#if !defined(G)`), the next is `#define G`
with an empty body, the matching #endif is the last directive, and only comments sit before or after. If G is
already defined, the file is skipped, as a compiler does. Any other #ifndef is an ordinary condition.

The tokens outside directives and false branches are kept per file, with object-like macros expanded (function-like
names stay as written). Each file's tokens are then read for declarations, the included files first: typedefs (a
struct, union or enum tag and its typedefs share one type id; an anonymous body takes its first typedef name),
enumerators (an implicit value is the previous one plus 1), struct and union members, function prototypes, global
variables and, in C++, const integral constants. `extern "C"` and the profile's ignored words are dropped first.
DECLARE_HANDLE(N) is built in. A declaration that uses another function-like macro, a namespace, template or using
block, a C++ class body or an unknown block is skipped and listed; the closure stays alive.

The finished Closure answers the evaluator's callbacks (expand, resolve, resolve_type, is_defined) with the state at
the end of the closure. Under a C++ profile, a tag is a type name: a bare tag resolves as its tag type, also when only
a prototype names it, unless a function, variable or constant of the same name hides it.

Standard library only.
"""

import os
from collections import Counter
from dataclasses import dataclass, field, replace

import ceval
import ctokens
from cdecls import QUALIFIERS, TAG_WORDS, Declarations, without_extern_c
from ctokens import Token, Unsupported

MAX_EXPANSION_DEPTH = 64
CONDITIONALS = ("if", "ifdef", "ifndef")
SKIPPED_HEADS = ("namespace", "template", "using")
CLASS_WORDS = frozenset({"public", "private", "protected", "virtual", "operator", "friend", "template"})


class HeaderError(Exception):
    """A configuration or input fault that stops the run: a missing umbrella or a file that does not decode."""


@dataclass(frozen=True)
class Config:
    profile: object  # a profiles.Profile
    search_path: tuple = ()  # folders, in search order
    predefines: dict = field(default_factory=dict)  # name -> body text, on top of the profile's own
    known_undefined: frozenset = frozenset()  # names that count as undefined (0 in #if)
    branch_cap: int = 8  # the most alternatives one macro name keeps
    encoding: str = "utf-8"


@dataclass(frozen=True)
class Origin:
    file: str
    line: int
    certain: bool  # False when it comes from an unresolved branch


@dataclass(frozen=True)
class Definition:
    name: str
    function: bool
    parameters: tuple
    body: tuple  # tokens
    origin: Origin

    def key(self):
        return (self.function, self.parameters, ctokens.spelling(list(self.body)))


class _Sentinel:
    def __init__(self, name: str):
        self.name = name

    def __repr__(self):
        return self.name

    def key(self):
        return self.name


UNDEFINED = _Sentinel("undefined")  # after #undef, or a known-undefined name
NEVER = _Sentinel("never defined")  # closed world: no file of the closure defines it
UNKNOWN = _Sentinel("unknown")  # open world: some file outside may define it
TRUNCATED = _Sentinel("truncated")  # more alternatives than the branch cap


@dataclass(frozen=True)
class Function:
    name: str
    returns: str  # the spelled return type
    parameters: tuple  # the spelled parameter types
    variadic: bool
    origin: Origin


@dataclass(frozen=True)
class Typedef:
    name: str
    spelled: str
    type_id: str  # the id of an anonymous body it names, else ""
    origin: Origin


@dataclass(frozen=True)
class Constant:
    name: str
    expression: tuple  # tokens
    type: str  # the enum's type id, or the spelled type of a const
    enumerator: bool
    origin: Origin


@dataclass(frozen=True)
class Variable:
    name: str
    spelled: str
    origin: Origin


@dataclass(frozen=True)
class Member:
    name: str
    spelled: str


@dataclass
class Diagnostics:
    missing: list = field(default_factory=list)  # (file, line, include name)
    macro_includes: list = field(default_factory=list)  # (file, line, text): #include of a macro
    errors: list = field(default_factory=list)  # (file, line, text, live): #error and #warning
    skipped: list = field(default_factory=list)  # (file, line, reason): declarations not read
    unsupported_files: list = field(default_factory=list)  # (file, reason)
    uncertain_files: list = field(default_factory=list)  # files included from an unresolved branch
    unterminated: list = field(default_factory=list)  # (file, line, problem): #if without #endif and the like
    unresolved_if: Counter = field(default_factory=Counter)  # identifier -> unresolved conditions
    unsupported_if: Counter = field(default_factory=Counter)  # cause -> unsupported conditions
    truncated: Counter = field(default_factory=Counter)  # name -> truncations
    unknown_directives: Counter = field(default_factory=Counter)


def _and(*values):
    if False in values:
        return False
    return None if None in values else True


def _or(*values):
    if True in values:
        return True
    return None if None in values else False


def _not(value):
    return None if value is None else not value


def canonical(path: str) -> str:
    return os.path.normcase(os.path.realpath(path))


class _Macros:
    """The macro table: name -> list of alternatives."""

    def __init__(self, profile, closed_world: bool, known_undefined: frozenset, cap: int, truncated: Counter):
        self.profile, self.closed_world, self.known_undefined, self.cap = profile, closed_world, known_undefined, cap
        self.table, self.truncated = {}, truncated

    def alternatives(self, name: str) -> list:
        if name in self.table:
            return self.table[name]
        if name in self.known_undefined:
            return [UNDEFINED]
        return [NEVER] if self.closed_world else [UNKNOWN]

    def set(self, name: str, alternative, certain: bool):
        if certain:
            self.table[name] = [alternative]
            return
        old = self.alternatives(name)
        if old == [TRUNCATED]:
            return
        merged, keys = [], set()
        for item in old + [alternative]:
            if item.key() not in keys:
                keys.add(item.key())
                merged.append(item)
        if len(merged) > self.cap:
            self.table[name] = [TRUNCATED]
            self.truncated[name] += 1
            return
        self.table[name] = merged

    def definition(self, name: str) -> Definition | None:
        """The one definition of NAME, or None when it has none or several alternatives."""
        alternatives = self.alternatives(name)
        return alternatives[0] if len(alternatives) == 1 and isinstance(alternatives[0], Definition) else None

    def is_function(self, name: str) -> bool:
        return any(isinstance(item, Definition) and item.function for item in self.alternatives(name))

    def expand(self, name: str) -> ceval.Macro | None:
        definition = self.definition(name)
        return ceval.Macro(definition.function, definition.body, definition.parameters) if definition else None

    def failure(self, name: str) -> ceval.Result | None:
        """Why NAME has no value of its own as a macro: truncated, several alternatives or a function-like macro
        that is not called. None when it is not a macro at all."""
        alternatives = self.alternatives(name)
        if TRUNCATED in alternatives:
            return ceval.failure(ceval.UNRESOLVED, "truncated branches", name)
        if len(alternatives) > 1:
            return ceval.failure(ceval.UNRESOLVED, "unresolved #if", name)
        if isinstance(alternatives[0], Definition):
            return ceval.failure(ceval.UNSUPPORTED, "function-like macro", name)
        return None

    def is_defined(self, name: str):
        alternatives = self.alternatives(name)
        if TRUNCATED in alternatives:
            return ceval.failure(ceval.UNRESOLVED, "truncated branches", name)
        answers = {None if item is UNKNOWN else isinstance(item, Definition) for item in alternatives}
        if len(answers) > 1:
            return ceval.failure(ceval.UNRESOLVED, "unresolved #if", name)
        return answers.pop()

    def resolve_pp(self, name: str) -> ceval.Result | None:
        """A bare identifier in #if that is not an expandable macro: 0 when it is undefined for sure."""
        found = self.failure(name)
        if found:
            return found
        if self.alternatives(name) == [UNDEFINED]:
            return ceval.Result(ceval.OK, 0, self.profile.int_type("int"))
        return None


@dataclass
class _Stream:
    """The tokens of one file after preprocessing, with a certain flag and a function-like-macro flag each."""
    path: str
    tokens: list = field(default_factory=list)
    certain: list = field(default_factory=list)
    function_macro: list = field(default_factory=list)


@dataclass
class _Frame:
    parent: object  # the region state around the #if: True or None (a false parent makes the frame dead)
    taken: object  # some earlier branch was taken: True, False or None
    current: object  # this branch: True, False or None
    dead: bool = False

    @property
    def state(self):
        return False if self.dead else _and(self.parent, self.current)


class Closure:
    """The macros and declarations of one closure, with the evaluator callbacks."""

    def __init__(self, name: str, config: Config, closed_world: bool):
        self.name, self.config, self.closed_world = name, config, closed_world
        self.profile = config.profile
        self.diagnostics = Diagnostics()
        known = set(config.known_undefined)
        if self.profile.language == "c":
            known.add("__cplusplus")
        self.macros = _Macros(self.profile, closed_world, frozenset(known), config.branch_cap,
                              self.diagnostics.truncated)
        self.functions, self.typedefs, self.constants, self.variables = {}, {}, {}, {}  # name -> list
        self.members = {}  # type id -> list of Member
        self.bodies = {}  # type id -> the Origin of the struct or union body that gave its members
        self.tag_ids = set()  # the type id of each tag the headers name, with or without a body: "enum X"
        self.tags, self.type_names = set(), set()
        self.files, self.edges = [], []  # read order; (from file, line, to file)
        self._values, self._evaluating = {}, set()

    def add(self, table: dict, record):
        table.setdefault(record.name, []).append(record)

    # Evaluator callbacks, with the state at the end of the closure. PROFILE (default: the closure's own) evaluates
    # the constants and gives the built-in types, so a reference header's names can be read under the target's rules.

    def callbacks(self, profile=None) -> dict:
        """The evaluator callbacks as keyword arguments for ceval.evaluate, with constants under PROFILE."""
        profile = profile or self.profile
        return {"expand": self.expand, "resolve": lambda name: self.resolve(name, profile),
                "resolve_type": lambda spelling: self.resolve_type(spelling, profile)}

    def expand(self, name: str) -> ceval.Macro | None:
        return self.macros.expand(name)

    def is_defined(self, name: str):
        return self.macros.is_defined(name)

    def resolve(self, name: str, profile=None) -> ceval.Result | None:
        found = self.macros.failure(name)
        if found:
            return found
        if name in self.constants:
            return self.constant_value(name, profile)
        if name in self.variables:
            return ceval.failure(ceval.NONCONSTANT, "variable", name)
        if name in self.functions:
            return ceval.failure(ceval.NONCONSTANT, "function", name)
        return None

    def constant_value(self, name: str, profile=None) -> ceval.Result:
        profile = profile or self.profile
        key = (name, profile.name)
        if key in self._values:
            return self._values[key]
        records = self.constants[name]
        if len({(ctokens.spelling(list(record.expression)), record.type) for record in records}) > 1:
            return ceval.failure(ceval.UNRESOLVED, "unresolved #if", name)
        if key in self._evaluating:
            return ceval.failure(ceval.UNSUPPORTED, "constant cycle", name)
        record = records[0]
        self._evaluating.add(key)
        result = ceval.evaluate(list(record.expression), profile, **self.callbacks(profile))
        self._evaluating.discard(key)
        target = profile.int_type("int") if record.enumerator else self.resolve_type(record.type, profile)
        if result.ok and target is not None:
            result = ceval.convert(result, target, profile)
        self._values[key] = result
        return result

    def resolve_type(self, spelling: str, profile=None, depth: int = 0):
        profile = profile or self.profile
        words = [word for word in spelling.split() if word not in QUALIFIERS]
        if not words or depth > MAX_EXPANSION_DEPTH:
            return None
        if words[-1] == "]":
            return self.array_type(words, profile, depth)
        if "*" in words:
            return profile.pointer(spelling)
        builtin = profile.builtin(tuple(words))
        if builtin is not None:
            return builtin
        if words[0] == "enum":
            return profile.int_type("int")
        if words[0] in TAG_WORDS:
            return ceval.CType("record", 0, name=" ".join(words))
        records = self.typedefs.get(words[0]) if len(words) == 1 else None
        if records and len({record.spelled for record in records}) == 1:
            return self.resolve_type(records[0].spelled, profile, depth + 1)
        if len(words) == 1 and profile.language == "cpp" and not self.hides_tag(words[0]):
            known = [f"{kind} {words[0]}" for kind in sorted(TAG_WORDS) if f"{kind} {words[0]}" in self.tag_ids]
            if known:
                return self.resolve_type(known[0], profile, depth + 1)
        return None

    def hides_tag(self, name: str) -> bool:
        """Whether a function, variable or constant named NAME hides the tag NAME (C++)."""
        return any(name in table for table in (self.functions, self.variables, self.constants))

    def array_type(self, words: list, profile, depth: int):
        """The array type that WORDS spell (`Float [ 16 ]`): its bits are the element's times every dimension, or 0
        when a dimension is missing or does not evaluate. None when the element type is not known."""
        first = words.index("[")
        element = self.resolve_type(" ".join(words[:first]), profile, depth + 1)
        if element is None:
            return None
        bits, dimension = element.bits, []
        for word in words[first:]:
            if word not in ("[", "]"):
                dimension.append(word)
            elif word == "]":
                count = ceval.evaluate(" ".join(dimension), profile, **self.callbacks(profile)) if dimension else None
                bits = bits * count.value if count and count.ok and isinstance(count.value, int) else 0
                dimension = []
        return ceval.CType("array", bits, name=" ".join(words))

    def type_id(self, spelling: str, depth: int = 0) -> str:
        """The type id that SPELLING names: typedef chains unroll; `struct T` and its typedefs share one id."""
        records = self.typedefs.get(spelling)
        if not records or len({record.spelled for record in records}) > 1 or depth > MAX_EXPANSION_DEPTH:
            return spelling
        return records[0].type_id or self.type_id(records[0].spelled, depth + 1)


def read(start: str, config: Config, closed_world: bool = True) -> Closure:
    """The closure of START: a header path, or a name found on the search path. An umbrella closure is a closed
    world; a header read alone (closed_world False) is an open one."""
    path = start if os.path.isfile(start) else _search(start, config.search_path)
    if path is None:
        raise HeaderError(f"umbrella {start!r} not found on the search path")
    closure = Closure(start, config, closed_world)
    reader = _Preprocessor(closure)
    for name, body in {**config.profile.predefines, **config.predefines}.items():
        if name in closure.macros.known_undefined:
            raise HeaderError(f"{name} is both predefined and known to be undefined")
        definition = Definition(name, False, (), tuple(ctokens.tokens_of(body)), Origin("<predefined>", 0, True))
        closure.macros.set(name, definition, True)
    reader.read_file(path, True)
    for stream in reader.streams:
        _read_declarations(stream, closure)
    return closure


def _search(name: str, folders) -> str | None:
    for folder in folders:
        candidate = os.path.join(folder, name)
        if os.path.isfile(candidate):
            return candidate
    return None


def _directives(tokens: list[Token]) -> list[tuple[int, int]]:
    """The (start, end) token range of each directive line, the # included."""
    found, index = [], 0
    while index < len(tokens):
        if tokens[index].bol and tokens[index].text == "#":
            end = index + 1
            while end < len(tokens) and not tokens[end].bol:
                end += 1
            found.append((index, end))
            index = end
        else:
            index += 1
    return found


def _guard(tokens: list[Token], directives: list[tuple[int, int]]) -> str | None:
    """The guard macro of a guarded file, or None."""
    if len(directives) < 3 or directives[0][0] != 0 or directives[-1][1] != len(tokens):
        return None
    words = [[token.text for token in tokens[start + 1:end]] for start, end in directives]
    first = words[0]
    if len(first) == 2 and first[0] == "ifndef":
        name = first[1]
    elif first[:3] == ["if", "!", "defined"] and first[3:4] != ["("] and len(first) == 4:
        name = first[3]
    elif first[:4] == ["if", "!", "defined", "("] and len(first) == 6 and first[5] == ")":
        name = first[4]
    else:
        return None
    if words[1] != ["define", name] or words[-1] != ["endif"]:
        return None
    depth = 0
    for number, line in enumerate(words):
        if line and line[0] in CONDITIONALS:
            depth += 1
        elif line and line[0] == "endif":
            depth -= 1
            if depth == 0 and number != len(words) - 1:
                return None
    return name if depth == 0 else None


class _Preprocessor:
    def __init__(self, closure: Closure):
        self.closure, self.macros, self.diagnostics = closure, closure.macros, closure.diagnostics
        self.config = closure.config
        self.seen, self.streams = set(), []

    def read_file(self, path: str, region):
        key = canonical(path)
        if key in self.seen:
            return
        self.seen.add(key)
        self.closure.files.append(path)
        if region is None:
            self.diagnostics.uncertain_files.append(path)
        try:
            with open(path, encoding=self.config.encoding, newline="") as handle:
                text = handle.read()
        except UnicodeDecodeError as error:
            raise HeaderError(f"{path}: does not decode as {self.config.encoding}: {error}") from error
        try:
            tokens = ctokens.tokenize(text)[0]
        except Unsupported as error:
            self.diagnostics.unsupported_files.append((path, str(error)))
            return
        directives = _directives(tokens)
        guard = _guard(tokens, directives)
        if guard and self.macros.definition(guard):
            return
        stream, frames = _Stream(path), []
        guard_start = directives[0][0] if guard else None
        index = 0
        while index < len(tokens):
            token = tokens[index]
            state = frames[-1].state if frames else region
            if token.bol and token.text == "#":
                end = index + 1
                while end < len(tokens) and not tokens[end].bol:
                    end += 1
                words = tokens[index + 1:end]
                if index == guard_start:
                    frames.append(_Frame(region, True, True))
                else:
                    self.directive(path, words, token.line, frames, region, state)
                index = end
                continue
            if state is not False:
                self.emit(stream, token, state is True)
            index += 1
        if frames:
            self.diagnostics.unterminated.append((path, tokens[-1].line, "#if without #endif"))
        self.streams.append(stream)

    # Directives

    def directive(self, path: str, words: list[Token], line: int, frames: list, region, state):
        name = words[0].text if words else ""
        if name in CONDITIONALS:
            if state is False:
                frames.append(_Frame(None, True, False, dead=True))
                return
            value = self.condition(name, words[1:], path, line)
            frames.append(_Frame(state, value, value))
        elif name in ("elif", "else", "endif"):
            if not frames:
                self.diagnostics.unterminated.append((path, line, f"#{name} without #if"))
                return
            frame = frames[-1]
            if name == "endif":
                frames.pop()
            elif frame.dead:
                return
            elif name == "else":
                frame.current = _not(frame.taken)
                frame.taken = True
            elif frame.taken is True:
                frame.current = False
            else:
                value = self.condition("if", words[1:], path, line)
                frame.current = False if value is False else (None if frame.taken is None else value)
                frame.taken = _or(frame.taken, value)
        elif state is False:
            return
        elif name == "define":
            self.define(path, words, line, state is True)
        elif name == "undef":
            if len(words) > 1 and words[1].kind == "id":
                self.macros.set(words[1].text, UNDEFINED, state is True)
        elif name == "include":
            self.include(path, words[1:], line, state)
        elif name in ("error", "warning"):
            text = ctokens.spelling(words[1:])
            self.diagnostics.errors.append((path, line, f"#{name} {text}", state is True))
        elif name not in ("", "pragma", "line"):
            self.diagnostics.unknown_directives[name] += 1

    def condition(self, kind: str, words: list[Token], path: str, line: int):
        """True, False or None (unresolved) for #if, #ifdef or #ifndef WORDS."""
        if kind in ("ifdef", "ifndef"):
            if not words or words[0].kind != "id":
                self.diagnostics.unsupported_if["malformed"] += 1
                return None
            answer = self.macros.is_defined(words[0].text)
            if answer is None or isinstance(answer, ceval.Result):
                self.diagnostics.unresolved_if[words[0].text] += 1
                return None
            return answer if kind == "ifdef" else not answer
        result = ceval.evaluate(words, self.closure.profile, mode="pp", expand=self.macros.expand,
                                resolve=self.macros.resolve_pp, is_defined=self.macros.is_defined)
        if result.ok:
            return result.value != 0
        if result.status == ceval.UNRESOLVED:
            self.diagnostics.unresolved_if[result.detail] += 1
        else:
            self.diagnostics.unsupported_if[result.cause] += 1
        return None

    def define(self, path: str, words: list[Token], line: int, certain: bool):
        if len(words) < 2 or words[1].kind != "id":
            self.diagnostics.unknown_directives["malformed define"] += 1
            return
        name = words[1]
        after = words[2] if len(words) > 2 else None
        function = (after is not None and after.text == "(" and after.line == name.line
                    and after.column == name.column + len(name.text))
        parameters, body = (), tuple(words[2:])
        if function:
            close = next((index for index in range(3, len(words)) if words[index].text == ")"), None)
            if close is None:
                self.diagnostics.unknown_directives["malformed define"] += 1
                return
            parameters = tuple(token.text for token in words[3:close] if token.text != ",")
            body = tuple(words[close + 1:])
        definition = Definition(name.text, function, parameters, body, Origin(path, line, certain))
        self.macros.set(name.text, definition, certain)

    def include(self, path: str, words: list[Token], line: int, state):
        if len(words) == 1 and words[0].kind == "str":
            name, folders = words[0].text[1:-1], (os.path.dirname(path),) + tuple(self.config.search_path)
        elif len(words) >= 3 and words[0].text == "<" and words[-1].text == ">":
            name, folders = "".join(token.text for token in words[1:-1]), tuple(self.config.search_path)
        else:
            self.diagnostics.macro_includes.append((path, line, ctokens.spelling(words)))
            return
        found = _search(name, folders)
        if found is None:
            self.diagnostics.missing.append((path, line, name))
            return
        self.closure.edges.append((path, line, found))
        self.read_file(found, state)

    # Emission

    def emit(self, stream: _Stream, token: Token, certain: bool):
        for item, item_certain in self.expansion(token, frozenset(), 0):
            stream.tokens.append(item)
            stream.certain.append(certain and item_certain)
            stream.function_macro.append(item.kind == "id" and self.macros.is_function(item.text))

    def expansion(self, token: Token, hidden: frozenset, depth: int) -> list[tuple[Token, bool]]:
        """TOKEN with its object-like macros expanded, each token with a certain flag. The profile's ignored words
        stay as written, so that declaration reading drops them whole."""
        profile = self.closure.profile
        if (token.kind != "id" or token.text in hidden or token.text in profile.ignored_words
                or token.text.startswith(tuple(profile.ignored_prefixes))):
            return [(token, True)]
        alternatives = self.macros.alternatives(token.text)
        if any(isinstance(item, Definition) for item in alternatives) and len(alternatives) > 1:
            return [(token, False)]
        definition = self.macros.definition(token.text)
        if definition is None or definition.function:
            return [(token, TRUNCATED not in alternatives)]
        if depth >= MAX_EXPANSION_DEPTH:
            return [(token, False)]
        found = []
        for part in definition.body:
            moved = replace(part, line=token.line, column=token.column, bol=False)
            found += self.expansion(moved, hidden | {token.text}, depth + 1)
        return found


def _read_declarations(stream: _Stream, closure: Closure):
    try:
        _Header(stream, closure).read()
    except Unsupported as error:
        closure.diagnostics.skipped.append((stream.path, 0, str(error)))


class _Header(Declarations):
    def __init__(self, stream: _Stream, closure: Closure):
        self.closure, self.path = closure, stream.path
        profile = closure.profile
        kept = without_extern_c(stream.tokens)
        tokens = [stream.tokens[index] for index in kept]
        certain = [stream.certain[index] for index in kept]
        function_macro = [stream.function_macro[index] for index in kept]
        kept = ctokens.kept_indices(tokens, profile.ignored_words, profile.ignored_prefixes)
        self.certain = [certain[index] for index in kept]
        self.function_macro = [function_macro[index] for index in kept]
        super().__init__([tokens[index] for index in kept], profile, closure.type_names, closure.tags)

    def note_skip(self, index: int, reason: str):
        self.closure.diagnostics.skipped.append((self.path, self.tokens[index].line, reason))

    def note_tag(self, kind: str, name: str):
        super().note_tag(kind, name)
        self.closure.tag_ids.add(f"{kind} {name}")

    def origin(self, start: int, end: int) -> Origin:
        return Origin(self.path, self.tokens[start].line, all(self.certain[start:end]))

    def read(self):
        index = 0
        while index < len(self.tokens):
            index = self.statement(index)

    def skip_statement(self, start: int) -> int:
        """The index after the statement or block at START."""
        tokens, index = self.tokens, start
        while index < len(tokens):
            text = tokens[index].text
            if text == ";":
                return index + 1
            if text == "{":
                end = self.pairs[index] + 1
                return end + 1 if end < len(tokens) and tokens[end].text == ";" else end
            index = self.skip(index)
        return index

    def statement(self, start: int) -> int:
        tokens = self.tokens
        head = tokens[start].text
        if head == ";":
            return start + 1
        if head in SKIPPED_HEADS:
            self.note_skip(start, f"{head} block")
            return self.skip_statement(start)
        if head == "DECLARE_HANDLE" and self.declare_handle(start):
            return self.skip_statement(start)
        bodies, index = [], start
        while index < len(tokens):
            text = tokens[index].text
            if text == ";":
                self.declaration(start, index, bodies)
                return index + 1
            if text != "{":
                index = self.skip(index)
                continue
            close = self.pairs[index]
            if self.function_head(start, index) is not None:
                self.declaration(start, index, [])
                return close + 1
            if index > start and tokens[index - 1].text == "=":
                index = close + 1
                continue
            if index > start and self.has_tag(start, index) and not self.is_class_body(index):
                bodies.append(index)
                index = close + 1
                continue
            self.note_tags(start, index)
            self.note_skip(start, self.block_reason(start, index))
            return self.skip_statement(start)
        self.declaration(start, len(tokens), bodies)
        return len(tokens)

    def macro_use(self, start: int, end: int) -> str | None:
        """The first depth-0 use of a function-like macro in START..END, or None."""
        for index in self.depth_zero(start, end):
            if self.function_macro[index] and index + 1 < end and self.tokens[index + 1].text == "(":
                return self.tokens[index].text
        return None

    def block_reason(self, start: int, brace: int) -> str:
        """Why the block that opens at BRACE is skipped: a function-like macro in its head, a C++ class body, or an
        unknown block."""
        macro = self.macro_use(start, brace)
        if macro:
            return f"function-like macro {macro}"
        return "class body" if self.has_tag(start, brace) else "block"

    def declare_handle(self, start: int) -> bool:
        tokens = self.tokens
        if start + 3 >= len(tokens) or tokens[start + 1].text != "(" or tokens[start + 3].text != ")":
            return False
        name = tokens[start + 2].text
        self.tags.add(f"{name}__")
        self.types.add(name)
        self.closure.add(self.closure.typedefs, Typedef(name, f"struct {name}__ *", "", self.origin(start,
                                                                                                    start + 4)))
        return True

    def is_class_body(self, brace: int) -> bool:
        """A C++ class body: member functions, access words and the like, which the reader does not model."""
        tokens = self.tokens
        for index in range(brace + 1, self.pairs[brace]):
            if tokens[index].text in CLASS_WORDS or tokens[index].text == "{" and tokens[index - 1].text in (")",
                                                                                                         "const"):
                return True
        return False

    def declaration(self, start: int, end: int, bodies: list):
        if start >= end:
            return
        tokens = self.tokens
        macro = self.macro_use(start, end)
        if macro:
            self.note_skip(start, f"function-like macro {macro}")
            return
        origin = self.origin(start, end)
        typedef = tokens[start].text == "typedef"
        low = start + 1 if typedef else start
        self.note_tags(low, end)
        declared = self.declarators(low, end)
        body_id, anonymous = (self.define_type(low, bodies[0], declared if typedef else None, origin)
                              if bodies else (None, False))
        for name, spelled, group, (part_start, part_end, cut) in declared:
            if not name:
                continue
            if anonymous:
                spelled = _respell(spelled, tokens[bodies[0] - 1].text, body_id)
            text = name[0]
            if typedef:
                plain = anonymous and spelled == body_id
                self.closure.add(self.closure.typedefs, Typedef(text, spelled, body_id if plain else "", origin))
                self.types.add(text)
            elif group is not None:
                parameters, variadic = self.parameters(group)
                self.closure.add(self.closure.functions, Function(text, spelled, parameters, variadic, origin))
            else:
                self.closure.add(self.closure.variables, Variable(text, spelled, origin))
                if self.is_constant(spelled, cut, part_end):
                    constant = Constant(text, tuple(tokens[cut + 1:part_end]), spelled, False, origin)
                    self.closure.add(self.closure.constants, constant)

    def is_constant(self, spelled: str, cut: int, end: int) -> bool:
        """A C++ const integral variable with an initializer."""
        words = spelled.split()
        return (self.profile.language == "cpp" and cut < end and "const" in words
                and not any(word in ("*", "&", "[") for word in words))

    def define_type(self, low: int, brace: int, typedefs, origin: Origin) -> tuple[str, bool]:
        """Read the type body that opens at BRACE; return its type id and whether it is anonymous. TYPEDEFS are the
        declarators of a typedef, whose first plain name names an anonymous body."""
        tokens = self.tokens
        tag_at = [index for index in self.depth_zero(low, brace) if tokens[index].text in TAG_WORDS][-1]
        kind = tokens[tag_at].text
        anonymous = tag_at + 1 == brace or tokens[tag_at + 1].kind != "id"
        if not anonymous:
            type_id = f"{kind} {self.qualified(tag_at + 1)[0]}"
        else:
            plain = [name[0] for name, spelled, _, _ in typedefs or () if name and spelled == kind]
            type_id = plain[0] if plain else f"{kind}@{origin.file}:{tokens[brace].line}"
        if kind == "enum":
            self.enumerators(brace, type_id, origin)
        else:
            self.closure.members[type_id] = self.member_list(brace, origin)
            self.closure.bodies[type_id] = origin
        return type_id, anonymous

    def enumerators(self, brace: int, type_id: str, origin: Origin):
        previous = None
        for low, high in self.split(brace + 1, self.pairs[brace]):
            if low == high or self.tokens[low].kind != "id":
                if low != high:
                    self.note_skip(low, "enumerator")
                continue
            name = self.tokens[low]
            if high > low + 1 and self.tokens[low + 1].text == "=":
                expression = tuple(self.tokens[low + 2:high])
            else:
                expression = tuple(ctokens.tokens_of("0" if previous is None else f"( {previous} ) + 1"))
            certain = origin.certain and all(self.certain[low:high])
            self.closure.add(self.closure.constants,
                             Constant(name.text, expression, type_id, True, Origin(self.path, name.line, certain)))
            previous = name.text

    def member_list(self, brace: int, origin: Origin) -> list:
        found = []
        for low, high in self.split(brace + 1, self.pairs[brace], ";"):
            if low == high:
                continue
            nested = [index for index in self.depth_zero(low, high) if self.tokens[index].text == "{"]
            declared = self.declarators(low, high)
            nested_id, anonymous = self.define_type(low, nested[0], None, origin) if nested else (None, False)
            names = [entry for entry in declared if entry[0]]
            if anonymous and not names:
                found += self.closure.members.get(nested_id, [])
                continue
            for name, spelled, _, _ in names:
                if anonymous:
                    spelled = _respell(spelled, self.tokens[nested[0] - 1].text, nested_id)
                found.append(Member(name[0], spelled))
        return found


def _respell(spelled: str, kind: str, type_id: str) -> str:
    """SPELLED with the bare tag word of an anonymous body replaced by the body's type id."""
    words = spelled.split(" ")
    if kind in words:
        words[words.index(kind)] = type_id
    return " ".join(words)
