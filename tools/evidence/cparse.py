"""Game source reader: the owners, declarations and call sites of one C or C++ file, read without a preprocessor.

parse() takes decoded text. It records #include lines and drops #pragma lines. Any other directive (#if, #define and
the like) makes the whole file unsupported, because the file is not preprocessed. So does a trigraph, an unterminated
block comment, an unbalanced bracket or a function body inside a type. The reason is in SourceFile.unsupported, and
nothing else is read.

It then drops `extern "C"` (a block keeps its contents) and the profile's ignored words, such as calling conventions,
__declspec(...) and SAL annotations. On the token stream that is left (so line breaks and comments do not matter), it
finds:
- owners: function definitions (an identifier, a balanced (...), then {), and file-scope declarations whose
  initializer holds a call. Each owner gets the annotation comments directly above its first token: only blank lines
  and other annotation lines may sit between.
- declarations: parameters, locals, file-scope variables and functions, prototypes, typedefs and tags. A declaration
  whose type is not known still records its name, with the spelled type.
- calls: each identifier followed by ( that is not a keyword, a type word or a known type and does not follow `.`,
  `->` or `::`. The arguments split at depth-1 commas. A nested call records the calls around it, outermost first.
- field spots, in function bodies only: a member after `.` or `->` that is written (=, |=, &=) or compared (==, !=,
  &), with its base expression and value (ctokens.find_fields). The case labels and the raw-offset accesses of the
  bodies are counted.
- value spots, in function bodies only (ctokens.find_values): a plain variable written or compared with =, == or !=,
  a local's initializer (as =, unless it is a { } list), a case label with its switch expression, and a return with a
  value.

A file-scope block that is not a function body, a type body or an initializer makes the file unsupported, so no code
is skipped without notice. Annotations on function-local statics are not read: their names are locals already.

Standard library only.
"""

import bisect
from dataclasses import dataclass, field

import ctokens
from cdecls import KEYWORDS, QUALIFIERS, STORAGE, TAG_WORDS, Declarations, without_extern_c
from ctokens import OPENERS, Token, Unsupported

STATEMENT_ENDS = frozenset({";", "{", "}"})
SKIPPED_HEADS = frozenset({"template", "using", "namespace"})


@dataclass(frozen=True)
class Annotation:
    kind: str
    address: str
    line: int


@dataclass(frozen=True)
class Include:
    name: str
    angle: bool  # <name> rather than "name"
    line: int


@dataclass(frozen=True)
class Declared:
    name: str
    kind: str  # variable or function
    type: str  # the spelled type, storage words dropped; for a function, its return type
    line: int
    annotations: tuple = ()


@dataclass(frozen=True)
class Prototype:
    name: str
    parameters: tuple  # the spelled parameter types
    variadic: bool
    line: int


@dataclass
class Owner:
    kind: str  # function or global
    name: str
    line: int
    annotations: tuple
    names: dict = field(default_factory=dict)  # parameter and local name -> spelled type


@dataclass(frozen=True)
class Call:
    callee: str
    outer: tuple  # ((callee, 1-based argument index), ...) of the calls around this one, outermost first
    arguments: tuple  # one tuple of tokens per argument; () for f()
    line: int
    column: int
    owner: int  # index into SourceFile.owners
    statement: str  # the spelling of the statement that holds the call
    previous: str  # the spelling of the statement before it


@dataclass(frozen=True)
class Spot:
    base: tuple  # the tokens of the expression before the . or ->
    arrow: bool  # -> rather than .
    member: str
    operator: str  # =, |=, &=, ==, != or &; x.f = x.f | K reads as x.f |= K
    value: tuple  # the tokens of the value
    line: int  # the line and column of the member
    column: int
    owner: int  # index into SourceFile.owners
    statement: str  # the spelling of the statement that holds the spot
    previous: str  # the spelling of the statement before it


@dataclass(frozen=True)
class ValueSpot:
    kind: str  # ctokens.VARIABLE, CASE or RETURN
    lvalue: tuple  # the tokens of the variable or of the switch expression; () for a return
    operator: str  # =, == or != for a variable; case; return
    value: tuple  # the tokens of the value
    line: int  # the line and column of the variable, of case or of return
    column: int
    owner: int  # index into SourceFile.owners
    statement: str  # the spelling of the statement that holds the spot
    previous: str  # the spelling of the statement before it


@dataclass
class SourceFile:
    path: str
    unsupported: str = ""
    includes: list = field(default_factory=list)
    owners: list = field(default_factory=list)
    calls: list = field(default_factory=list)
    spots: list = field(default_factory=list)
    values: list = field(default_factory=list)  # ValueSpot records, in function bodies
    case_labels: int = 0  # in function bodies
    raw_offsets: int = 0  # accesses such as *(T *)((char *)p + 8), in function bodies
    names: dict = field(default_factory=dict)  # file-scope name -> Declared
    prototypes: dict = field(default_factory=dict)  # function name -> Prototype, the last one read
    typedefs: dict = field(default_factory=dict)  # name -> spelled type
    tags: set = field(default_factory=set)


def parse(text: str, path: str, profile, annotation=None, type_names=frozenset()) -> SourceFile:
    """Read TEXT. ANNOTATION is a compiled regex with the groups kind and address, matched against each // comment;
    None reads no annotations. TYPE_NAMES are the type names the file can see from headers."""
    result = SourceFile(path)
    try:
        tokens, comments = ctokens.tokenize(text)
        _Reader(tokens, comments, result, profile, annotation, type_names).read()
    except Unsupported as error:
        return SourceFile(path, unsupported=str(error))
    return result


class _Reader(Declarations):
    def __init__(self, tokens, comments, result, profile, annotation, type_names):
        self.result, self.annotation = result, annotation
        self.token_lines = {token.line for token in tokens}
        self.comment_lines = {}
        for comment in comments:
            for line in range(comment.line, comment.end_line + 1):
                self.comment_lines.setdefault(line, []).append(comment)
        tokens = ctokens.drop_directives(tokens, self.directive)
        tokens = [tokens[index] for index in without_extern_c(tokens)]
        tokens = ctokens.drop_words(tokens, profile.ignored_words, profile.ignored_prefixes)
        super().__init__(tokens, profile, set(type_names), result.tags)

    # Preparation

    def directive(self, words: list[Token], line: int):
        name = words[0].text if words else ""
        if name in ("", "pragma"):
            return
        if name != "include":
            raise Unsupported(f"#{name}")
        rest = words[1:]
        if len(rest) == 1 and rest[0].kind == "str":
            self.result.includes.append(Include(rest[0].text[1:-1], False, line))
        elif len(rest) >= 3 and rest[0].text == "<" and rest[-1].text == ">":
            self.result.includes.append(Include("".join(token.text for token in rest[1:-1]), True, line))
        else:
            raise Unsupported("#include of a macro")

    def annotations(self, line: int) -> tuple:
        found, line = [], line - 1
        while line >= 1 and line not in self.token_lines:
            comments = self.comment_lines.get(line)
            if comments:
                comment = comments[0]
                single = len(comments) == 1 and comment.line == comment.end_line and comment.text.startswith("//")
                match = self.annotation.match(comment.text) if single and self.annotation else None
                if not match:
                    break
                found.append(Annotation(match["kind"], match["address"], line))
            line -= 1
        return tuple(reversed(found))

    # File scope

    def read(self):
        index = 0
        while index < len(self.tokens):
            index = self.external(index)

    def external(self, start: int) -> int:
        """Read the declaration or definition at START; return the index after it."""
        tokens, index = self.tokens, start
        while index < len(tokens):
            text = tokens[index].text
            if text in ("(", "["):
                index = self.pairs[index] + 1
            elif text == "{":
                group = self.function_head(start, index)
                if group is not None:
                    self.function(start, group, index)
                    return self.pairs[index] + 1
                if tokens[start].text == "namespace":
                    raise Unsupported("namespace")
                if tokens[index - 1].text != "=" and not self.has_tag(start, index):
                    raise Unsupported(f"a file-scope block the reader does not model (line {tokens[index].line})")
                self.check_type_body(index)
                index = self.pairs[index] + 1
            elif text == ";":
                self.declaration(start, index)
                return index + 1
            else:
                index += 1
        self.declaration(start, index)
        return index

    def check_type_body(self, brace: int):
        for index in range(brace + 1, self.pairs[brace]):
            if self.tokens[index].text == "{" and self.tokens[index - 1].text == ")":
                raise Unsupported("function body inside a type")

    def function(self, start: int, group: int, brace: int):
        tokens = self.tokens
        name, name_start = self.name_before(start, group)
        line = tokens[start].line
        annotations = self.annotations(line)
        self.note_tags(start, group)
        owner = Owner("function", name, line, annotations)
        parameters, variadic = self.parameters(group, owner.names)
        self.result.prototypes[name] = Prototype(name, parameters, variadic, line)
        self.result.names[name] = Declared(name, "function", self.spelled(tokens[start:name_start]), line, annotations)
        self.result.owners.append(owner)
        declarations, initializers = self.locals(brace, self.pairs[brace], owner)
        bounds = self.bounds(brace, self.pairs[brace])
        self.calls(bounds, len(self.result.owners) - 1)
        self.spots(bounds, len(self.result.owners) - 1)
        self.values(bounds, len(self.result.owners) - 1, declarations, initializers)

    def declaration(self, start: int, end: int):
        if start == end or self.tokens[start].text in SKIPPED_HEADS:
            return
        typedef = self.tokens[start].text == "typedef"
        low = start + 1 if typedef else start
        self.note_tags(low, end)
        annotations = self.annotations(self.tokens[start].line)
        for name, spelled, group, (part_start, part_end, cut) in self.declarators(low, end):
            if not name:
                continue
            text = name[0]
            if typedef:
                self.result.typedefs[text] = spelled
                self.types.add(text)
                continue
            line = self.tokens[name[1]].line
            kind = "variable" if group is None else "function"
            self.result.names[text] = Declared(text, kind, spelled, line, annotations)
            if group is not None:
                parameters, variadic = self.parameters(group)
                self.result.prototypes[text] = Prototype(text, parameters, variadic, line)
            if cut < part_end and self.holds_call(cut + 1, part_end):
                self.result.owners.append(Owner("global", text, self.tokens[start].line, annotations))
                self.calls(self.bounds(cut, part_end), len(self.result.owners) - 1)

    # Function bodies

    def locals(self, low: int, high: int, owner: Owner) -> tuple[list, list]:
        """Put each local's spelled type in OWNER.names. Returns the (start, end) of each declaration, and the (name,
        cut, end) indices of each initialized declarator."""
        tokens, declarations, initializers = self.tokens, [], []
        for index in range(low + 1, high):
            before = tokens[index - 1].text
            start = before in STATEMENT_ENDS or before == "(" and tokens[index - 2].text == "for"
            if start and self.starts_declaration(index, high):
                end = self.statement_end(index, high)
                self.note_tags(index, end)
                declarations.append((index, end))
                for name, spelled, _, (_, part_end, cut) in self.declarators(index, end):
                    if name:
                        owner.names[name[0]] = spelled
                        if cut < part_end:
                            initializers.append((name[1], cut, part_end))
        return declarations, initializers

    def starts_declaration(self, index: int, high: int) -> bool:
        tokens, start = self.tokens, index
        while index < high and tokens[index].text in STORAGE | QUALIFIERS:
            index += 1
        if index >= high or tokens[index].kind != "id":
            return False
        word = tokens[index].text
        if word in self.profile.type_words or word in TAG_WORDS:
            return True
        if word in KEYWORDS:
            return False
        text, end = self.qualified(index)
        if self.is_type(text) or index > start:
            return True
        if end < high and self.is_name(tokens[end]):
            return True
        after = end
        while after < high and tokens[after].text == "*":
            after += 1
        return (after > end and after + 1 < high and self.is_name(tokens[after])
                and tokens[after + 1].text in (";", "=", ",", "[", ")"))

    def statement_end(self, index: int, high: int) -> int:
        while index < high:
            text = self.tokens[index].text
            if text in OPENERS:
                index = self.pairs[index] + 1
                continue
            if text in (";", ")", "}"):
                return index
            index += 1
        return high

    def is_callee(self, index: int) -> bool:
        token = self.tokens[index]
        if not self.is_name(token) or self.is_type(token.text):
            return False
        return index == 0 or self.tokens[index - 1].text not in (".", "->", "::")

    def holds_call(self, low: int, high: int) -> bool:
        return any(self.tokens[index].text == "(" and self.is_callee(index - 1) for index in range(low + 1, high))

    def bounds(self, low: int, high: int) -> list[int]:
        """LOW, the indices of the statement ends strictly between LOW and HIGH, and HIGH."""
        tokens = self.tokens
        return [low] + [index for index in range(low + 1, high) if tokens[index].kind == "punct"
                        and tokens[index].text in STATEMENT_ENDS] + [high]

    def context(self, position: int, bounds: list[int]) -> tuple[str, str]:
        """The spellings of the statement that holds POSITION and of the statement before it."""
        bound = bisect.bisect_left(bounds, position)
        statement = ctokens.spelling(self.tokens[bounds[bound - 1] + 1:bounds[bound]])
        previous = ctokens.spelling(self.tokens[bounds[bound - 2] + 1:bounds[bound - 1]]) if bound >= 2 else ""
        return statement, previous

    def calls(self, bounds: list[int], owner: int):
        """Record the calls strictly between the first and the last of BOUNDS."""
        for found in ctokens.find_calls(self.tokens, self.is_callee, bounds[0], bounds[-1]):
            self.result.calls.append(self.call(found, bounds, owner))

    def call(self, found: ctokens.FoundCall, bounds: list[int], owner: int) -> Call:
        token = self.tokens[found.position]
        return Call(token.text, found.outer, found.arguments(self.tokens), token.line, token.column, owner,
                    *self.context(found.position, bounds))

    def spots(self, bounds: list[int], owner: int):
        """Record the field spots strictly between the first and the last of BOUNDS, and count the case labels and
        raw-offset accesses there."""
        tokens, low, high = self.tokens, bounds[0], bounds[-1]
        for found in ctokens.find_fields(tokens, self.is_callee, low, high):
            member = tokens[found.member]
            self.result.spots.append(Spot(tuple(tokens[found.base:found.member - 1]),
                                          tokens[found.member - 1].text == "->", member.text, found.operator,
                                          tuple(tokens[found.value:found.end]), member.line, member.column, owner,
                                          *self.context(found.member, bounds)))
        self.result.case_labels += sum(1 for index in range(low + 1, high) if tokens[index].text == "case")
        self.result.raw_offsets += ctokens.raw_offsets(tokens, low, high)

    def values(self, bounds: list[int], owner: int, declarations: list, initializers: list):
        """Record the value spots strictly between the first and the last of BOUNDS, in position order. A variable
        spot inside a declaration is left out: the declaration's initializers stand for it."""
        tokens, found = self.tokens, []
        for spot in ctokens.find_values(tokens, self.is_callee, bounds[0], bounds[-1]):
            if spot.kind == ctokens.VARIABLE and any(start <= spot.position < end for start, end in declarations):
                continue
            lvalue = tuple(tokens[spot.lvalue[0]:spot.lvalue[1]]) if spot.lvalue else ()
            found.append((spot.position, spot.kind, lvalue, spot.operator, spot.value, spot.end))
        for name, cut, end in initializers:
            if cut + 1 < end and tokens[cut + 1].text != "{":
                found.append((name, ctokens.VARIABLE, (tokens[name],), "=", cut + 1, end))
        for position, kind, lvalue, operator, value, end in sorted(found, key=lambda entry: entry[0]):
            token = tokens[position]
            self.result.values.append(ValueSpot(kind, lvalue, operator, tuple(tokens[value:end]), token.line,
                                                token.column, owner, *self.context(position, bounds)))
