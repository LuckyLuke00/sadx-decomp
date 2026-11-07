"""Typed evaluation of one C or C++ constant expression, under one compiler profile.

evaluate() takes the text or the tokens of one expression and gives a Result. An "ok" result holds the value and
its C type. Every other result says why there is no value:

- nonconstant: the expression reads memory or calls code (a variable, a call, ., ->, [], unary * or &, a string);
- unresolved: an identifier that nothing defines, or a value that depends on an unresolved #if;
- unsupported: a step the tools do not model, such as a function-like macro, a comma operator, a shift count out of
  range, a division by zero or a signed overflow under a profile with no rule for it.

When parts of one expression fail in different ways, nonconstant wins over unresolved, and unresolved over
unsupported. Both operands of &&, || and ?: are always read; the one that the condition skips does not change the
value, but in expression mode it still makes the whole expression nonconstant. In expression mode a skipped ?:
branch that fails also fails the result, because the result type depends on it.

The caller supplies the names through callbacks, each of which may be left out:

- expand(name) -> Macro or None: an object-like macro is expanded token by token, as a compiler does; a function-like
  macro followed by "(" gives "unsupported" (cause "function-like macro"), or "nonconstant" when its arguments name a
  variable. A cycle, # or ## in a body, or a body that ends in a call gives "unsupported".
- resolve(name) -> Result or None: any other identifier, such as an enum constant, a const variable or a variable
  (a "nonconstant" Result). None means the name is unknown.
- resolve_type(spelling) -> CType or None: a typedef name or "struct TAG", for casts and sizeof.
- is_defined(name) -> True, False, a failed Result or None (unknown), for `defined` in #if mode.

In #if mode (mode "pp") every integer acts as the profile's #if type, `defined` works, and sizeof, casts and floats
give "unsupported".

Each ok Result lists the names, as written in the expression, that gave part of the value, and says whether a literal
did. So `NULL` gives names ("NULL",) and no literal, and `NAME | 0x80` gives both.

Standard library only.
"""

import math
import operator
import re
import struct
from dataclasses import dataclass, replace
from fractions import Fraction

import ctokens
from profiles import BIG_ENDIAN, WRAP, ARITHMETIC, CType, Profile

OK, NONCONSTANT, UNRESOLVED, UNSUPPORTED = "ok", "nonconstant", "unresolved", "unsupported"
SEVERITY = {OK: 0, UNSUPPORTED: 1, UNRESOLVED: 2, NONCONSTANT: 3}

INTEGER = re.compile(r"(0[xX][0-9A-Fa-f]+|0[0-7]*|[1-9][0-9]*)([A-Za-z0-9]*)\Z")
FLOATING = re.compile(r"((?:[0-9]+\.[0-9]*|\.[0-9]+)(?:[eE][+-]?[0-9]+)?|[0-9]+[eE][+-]?[0-9]+)([fFlL]?)\Z")
BASIC_SUFFIXES = ("", "u", "l", "ul", "lu")
HEX_TYPES = ("int", "unsigned int", "long", "unsigned long")
LITERAL_TYPES = {  # suffix: (the types a decimal literal may take, the types a hex or octal literal may take)
    "u": (("unsigned int", "unsigned long"), ("unsigned int", "unsigned long")),
    "l": (("long", "unsigned long"), ("long", "unsigned long")),
    "ul": (("unsigned long",), ("unsigned long",)),
    "lu": (("unsigned long",), ("unsigned long",)),
    "ll": (("long long",), ("long long", "unsigned long long")),
    "i64": (("long long",), ("long long", "unsigned long long")),
    "ull": (("unsigned long long",), ("unsigned long long",)),
    "llu": (("unsigned long long",), ("unsigned long long",)),
    "ui64": (("unsigned long long",), ("unsigned long long",)),
}
SIMPLE_ESCAPES = {"n": 10, "t": 9, "v": 11, "b": 8, "r": 13, "f": 12, "a": 7, "\\": 92, "?": 63, "'": 39, '"': 34}
CPP_UNSUPPORTED = frozenset("""
    nullptr this new delete operator template typename typeid throw static_cast dynamic_cast reinterpret_cast
    const_cast alignof decltype noexcept and and_eq bitand bitor compl not not_eq or or_eq xor xor_eq
""".split())
BINARY_LEVELS = (("||",), ("&&",), ("|",), ("^",), ("&",), ("==", "!="), ("<", ">", "<=", ">="), ("<<", ">>"),
                 ("+", "-"), ("*", "/", "%"))
ASSIGNMENTS = ("=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=")
COMPARISONS = {"==": operator.eq, "!=": operator.ne, "<": operator.lt, ">": operator.gt, "<=": operator.le,
               ">=": operator.ge}
INTEGER_OPERATIONS = {"+": operator.add, "-": operator.sub, "*": operator.mul, "&": operator.and_,
                      "|": operator.or_, "^": operator.xor}
FLOAT_OPERATIONS = {"+": operator.add, "-": operator.sub, "*": operator.mul, "/": operator.truediv}
ARITHMETIC_KINDS = ("int", "bool", "float")
SCALAR_KINDS = ("int", "bool", "float", "pointer")
QUALIFIERS = ("const", "volatile")
TAG_WORDS = ("struct", "union", "enum")


@dataclass(frozen=True)
class Result:
    status: str  # ok, nonconstant, unresolved or unsupported
    value: int | float | None = None
    ctype: CType | None = None
    cause: str = ""  # a fixed key for the reason, such as "unknown identifier"
    detail: str = ""  # what the reason is about, such as the identifier
    names: tuple = ()  # the names as written that gave part of the value
    literal: bool = False  # a literal as written gave part of the value

    @property
    def ok(self) -> bool:
        return self.status == OK


@dataclass(frozen=True)
class Macro:
    function: bool
    body: tuple = ()  # the tokens of the replacement list
    parameters: tuple = ()  # a function-like macro's parameter names, "..." last when it is variadic


def failure(status: str, cause: str, detail: str = "") -> Result:
    return Result(status, cause=cause, detail=detail)


@dataclass(frozen=True)
class _Item:
    """A token after macro expansion. ORIGIN is the macro, as written in the expression, that it came from. Kind
    `defined` holds the name after `defined`, kind `call` a function-like macro use with its argument tokens, and
    kind `bad` a failed expansion."""
    kind: str
    text: str
    origin: str = ""
    args: tuple = ()
    result: Result | None = None


class _Syntax(Exception):
    """Tokens that do not form an expression."""


def _unknown(_name):
    return None


def evaluate(source, profile: Profile, *, mode: str = "expr", expand=_unknown, resolve=_unknown,
             resolve_type=_unknown, is_defined=_unknown, max_depth: int = 64) -> Result:
    """The value and type of SOURCE (text or a list of ctokens.Token) under PROFILE. MODE is expr or pp (#if)."""
    try:
        tokens = ctokens.tokens_of(source) if isinstance(source, str) else list(source)
    except ctokens.Unsupported as error:
        return failure(UNSUPPORTED, "syntax", str(error))
    evaluator = _Evaluator(profile, mode, expand, resolve, resolve_type, is_defined, max_depth)
    try:
        result = evaluator.parse(evaluator.expand_items(tokens, "", frozenset(), 0))
    except _Syntax as error:
        return failure(UNSUPPORTED, "syntax", str(error))
    if mode == "pp" and result.status == NONCONSTANT:
        return failure(UNSUPPORTED, "not a #if expression", result.cause)
    return result


def convert(result: Result, target: CType, profile: Profile) -> Result:
    """RESULT converted to TARGET, as a cast or an assignment does. An unsigned target wraps; a signed target follows
    the profile's narrowing rule; a float to integer conversion out of range is unsupported."""
    if not result.ok:
        return result
    source, value = result.ctype, result.value
    if target.kind not in SCALAR_KINDS or source.kind not in SCALAR_KINDS:
        return failure(UNSUPPORTED, "conversion", f"{source.name} to {target.name}")
    if target.kind == "bool":
        converted = int(value != 0)
    elif target.kind == "float":
        converted = None if source.kind == "pointer" else round_float(value, target.bits)
        if converted is None:
            return failure(UNSUPPORTED, "float range", f"{value} to {target.name}")
    elif source.kind == "float":
        whole = math.trunc(value)
        if target.kind == "pointer" or not target.lowest() <= whole <= target.highest():
            return failure(UNSUPPORTED, "float range", f"{value} to {target.name}")
        converted = whole
    else:
        fitted = _fit(value, target, profile.narrowing, "narrowing")
        if not fitted.ok:
            return fitted
        converted = fitted.value
    return replace(result, value=converted, ctype=target)


def round_float(exact, bits: int) -> float | None:
    """The float of BITS (32 or 64) nearest to EXACT (an int, a float or a Fraction), ties to even; None when it is
    out of range. A float literal rounds straight to 32 bits, never through a double."""
    if isinstance(exact, float) and not math.isfinite(exact):
        return None
    try:
        nearest = float(exact)
    except OverflowError:
        return None
    if bits == 64:
        return nearest
    magnitude = abs(Fraction(exact))
    try:
        pattern = struct.unpack("<I", struct.pack("<f", float(magnitude)))[0]
    except OverflowError:
        return None
    best, best_pattern = None, pattern
    for candidate in (pattern - 1, pattern, pattern + 1):
        if not 0 <= candidate < 0x7F800000:  # below zero, or infinity and NaN
            continue
        distance = abs(Fraction(_float32_of(candidate)) - magnitude)
        if best is None or distance < best or (distance == best and candidate % 2 == 0):
            best, best_pattern = distance, candidate
    value = _float32_of(best_pattern)
    return -value if exact < 0 else value


def _float32_of(pattern: int) -> float:
    return struct.unpack("<f", struct.pack("<I", pattern))[0]


def _wrap(value: int, ctype: CType) -> int:
    value &= (1 << ctype.bits) - 1
    if ctype.signed and value >> (ctype.bits - 1):
        value -= 1 << ctype.bits
    return value


def _fit(exact: int, ctype: CType, rule: str, cause: str) -> Result:
    """EXACT in CTYPE: kept when in range; else wrapped for an unsigned type or under RULE wrap; else unsupported."""
    if ctype.lowest() <= exact <= ctype.highest():
        return Result(OK, exact, ctype)
    if not ctype.signed or rule == WRAP:
        return Result(OK, _wrap(exact, ctype), ctype)
    return failure(UNSUPPORTED, cause, str(exact))


def _first_failure(*results: Result) -> Result | None:
    """The most severe failure among RESULTS, the first one on a tie; None when all are ok."""
    worst = max(results, key=lambda result: SEVERITY[result.status])
    return None if worst.ok else worst


def _with_sources(result: Result, *parts: Result) -> Result:
    """RESULT with the names and the literal flag of PARTS."""
    if not result.ok:
        return result
    names = tuple(dict.fromkeys(name for part in parts for name in part.names))
    return replace(result, names=names, literal=any(part.literal for part in parts))


def _char_units(body: str, limit: int) -> list[int] | None:
    """The code units of a character constant's body; None for an escape the tools do not model, a non-ASCII
    character or a unit above LIMIT."""
    units, index = [], 0
    while index < len(body):
        char = body[index]
        index += 1
        if char != "\\":
            if ord(char) > 0x7F:
                return None
            units.append(ord(char))
            continue
        if index == len(body):
            return None
        escape = body[index]
        index += 1
        if escape in SIMPLE_ESCAPES:
            units.append(SIMPLE_ESCAPES[escape])
        elif escape in "01234567":
            end = index
            while end < len(body) and end - index < 2 and body[end] in "01234567":
                end += 1
            units.append(int(escape + body[index:end], 8))
            index = end
        elif escape == "x":
            end = index
            while end < len(body) and body[end] in "0123456789abcdefABCDEF":
                end += 1
            if end == index:
                return None
            units.append(int(body[index:end], 16))
            index = end
        else:
            return None
        if units[-1] > limit:
            return None
    return units


def _starts_call(tokens: list, index: int) -> bool:
    return index < len(tokens) and tokens[index].kind == "punct" and tokens[index].text == "("


def _split_arguments(tokens: tuple) -> list[tuple]:
    """The arguments of a macro call: TOKENS split at the commas outside parentheses."""
    arguments, current, depth = [], [], 0
    for token in tokens:
        if token.kind == "punct" and token.text in ("(", ")"):
            depth += 1 if token.text == "(" else -1
        if depth == 0 and token.kind == "punct" and token.text == ",":
            arguments.append(tuple(current))
            current = []
        else:
            current.append(token)
    arguments.append(tuple(current))
    return arguments


def _stringized(tokens: tuple) -> list:
    """The # operator: the argument as one string literal token."""
    text = ctokens.spelling(list(tokens)).replace("\\", "\\\\").replace('"', '\\"')
    return ctokens.tokens_of(f'"{text}"')


def _call_arguments(tokens: list, index: int) -> tuple[tuple, int]:
    """The tokens between the "(" at INDEX and its matching ")", and the index after the ")"."""
    depth = 0
    for end in range(index, len(tokens)):
        if tokens[end].kind == "punct" and tokens[end].text in ("(", ")"):
            depth += 1 if tokens[end].text == "(" else -1
            if depth == 0:
                return tuple(tokens[index + 1:end]), end + 1
    raise _Syntax("unbalanced parentheses")


class _Evaluator:
    def __init__(self, profile, mode, expand, resolve, resolve_type, is_defined, max_depth):
        self.profile, self.mode, self.max_depth = profile, mode, max_depth
        self.expand, self.resolve, self.resolve_type, self.is_defined = expand, resolve, resolve_type, is_defined
        self.int = profile.int_type("int")
        self.uint = profile.int_type("unsigned int")
        self.intmax = CType("int", profile.pp_bits, True, 6, "intmax_t")
        self.uintmax = CType("int", profile.pp_bits, False, 6, "uintmax_t")
        if mode == "pp":
            self.truth = self.intmax
        else:
            self.truth = profile.builtin(("bool",)) if profile.language == "cpp" else self.int
        self.items, self.pos = [], 0

    # ------------------------------------------------------------ macro expansion

    def expand_items(self, tokens: list, origin: str, hidden: frozenset, depth: int) -> list:
        items, index = [], 0
        while index < len(tokens):
            token = tokens[index]
            index += 1
            if token.kind != "id":
                # An item from an expanded macro argument keeps what it holds (a call, a failure, a defined name).
                items.append(token if isinstance(token, _Item) else _Item(token.kind, token.text, origin))
                continue
            if self.mode == "pp" and token.text == "defined":
                name, index = self._defined_operand(tokens, index)
                items.append(_Item("defined", name, origin))
                continue
            macro = self.expand(token.text)
            if macro is None or (macro.function and not _starts_call(tokens, index)):
                items.append(_Item("id", token.text, origin))
                continue
            where = origin or token.text
            if macro.function:
                args, index = _call_arguments(tokens, index)
            if macro.function and self.mode != "pp":
                items.append(_Item("call", token.text, where, args))
            elif token.text in hidden:
                items.append(_Item("bad", token.text, where, result=failure(UNSUPPORTED, "macro cycle", token.text)))
            elif depth >= self.max_depth:
                items.append(_Item("bad", token.text, where, result=failure(UNSUPPORTED, "macro depth", token.text)))
            elif macro.function:
                items += self.expand_call(token.text, macro, args, where, hidden, depth)
            elif self.mode != "pp" and any(part.text in ("#", "##") for part in macro.body):
                items.append(_Item("bad", token.text, where,
                                   result=failure(UNSUPPORTED, "token pasting", token.text)))
            elif self._calls(macro.body):
                items.append(_Item("bad", token.text, where,
                                   result=failure(UNSUPPORTED, "macro expands to a call", token.text)))
            else:
                items += self.rescan(list(macro.body), where, hidden | {token.text}, depth + 1)
        return items

    def expand_call(self, name: str, macro: Macro, raw: tuple, where: str, hidden: frozenset, depth: int) -> list:
        """A function-like macro use in #if: each parameter takes its argument (as written next to # and ##,
        else fully expanded), then # and ## apply and the result is rescanned with NAME hidden."""
        names = list(macro.parameters)
        arguments = _split_arguments(raw)
        if not names and arguments == [()]:
            arguments = []
        if names[-1:] == ["..."]:
            names[-1] = "__VA_ARGS__"
            fixed = len(names) - 1
            if len(arguments) == fixed:
                arguments.append(())
            elif len(arguments) > fixed:
                rest = [token for argument in arguments[fixed:-1] for token in (*argument, _Item("punct", ","))]
                arguments = arguments[:fixed] + [tuple(rest) + arguments[-1]]
        if len(arguments) != len(names):
            return [_Item("bad", name, where, result=failure(UNSUPPORTED, "macro arguments", name))]
        given = dict(zip(names, arguments))
        body = list(macro.body)
        parts, index = [], 0
        while index < len(body):
            part = body[index]
            following = body[index + 1] if index + 1 < len(body) else None
            if part.text == "#" and following is not None and following.text in given:
                parts += _stringized(given[following.text])
                index += 2
                continue
            if part.kind == "id" and part.text in given:
                pasted = (index > 0 and body[index - 1].text == "##") or (following is not None and
                                                                           following.text == "##")
                argument = list(given[part.text])
                if pasted:
                    parts += argument or [_Item("placemarker", "")]
                else:
                    parts += self.expand_items(argument, where, hidden, depth + 1)
            else:
                parts.append(part)
            index += 1
        return self.rescan(parts, where, hidden | {name}, depth + 1)

    def rescan(self, parts: list, where: str, hidden: frozenset, depth: int) -> list:
        """PARTS expanded again after the ## operators are applied (in #if mode only)."""
        if self.mode == "pp":
            parts = self.pasted(parts, where)
            if isinstance(parts, _Item):
                return [parts]
        return self.expand_items(parts, where, hidden, depth)

    def pasted(self, parts: list, where: str) -> list | _Item:
        """PARTS with each `a ## b` joined into one token, or a bad item when a join is not one token or an operand
        is a name with no single meaning (such as a macro with unresolved alternatives)."""
        out, index = [], 0
        while index < len(parts):
            part = parts[index]
            if not (part.kind == "punct" and part.text == "##" and out and index + 1 < len(parts)):
                out.append(part)
                index += 1
                continue
            left, right = out.pop(), parts[index + 1]
            for operand in (left, right):
                if operand.kind not in ("id", "num", "char", "str", "punct", "placemarker"):
                    return _Item("bad", where, where, result=failure(UNSUPPORTED, "token pasting", where))
                if operand.kind == "id" and self.expand(operand.text) is None:
                    found = self.resolve(operand.text)
                    if found is not None and not found.ok:
                        return _Item("bad", operand.text, where, result=found)
            text = left.text + right.text
            try:
                made = ctokens.tokens_of(text) if text else [_Item("placemarker", "")]
            except ctokens.Unsupported:
                made = []
            if len(made) != 1:
                return _Item("bad", where, where, result=failure(UNSUPPORTED, "token pasting", text))
            out.append(made[0])
            index += 2
        return [part for part in out if part.kind != "placemarker"]

    def _calls(self, body: tuple) -> bool:
        """BODY calls a function: an identifier other than sizeof, a type word or a function-like macro, before "("."""
        for index, token in enumerate(body[:-1]):
            if token.kind != "id" or not _starts_call(body, index + 1):
                continue
            if token.text == "sizeof" or token.text in self.profile.type_words:
                continue
            macro = self.expand(token.text)
            if macro is None or not macro.function:
                return True
        return False

    @staticmethod
    def _defined_operand(tokens: list, index: int) -> tuple[str, int]:
        parenthesized = _starts_call(tokens, index)
        start = index + 1 if parenthesized else index
        if start >= len(tokens) or tokens[start].kind != "id":
            raise _Syntax("defined without a name")
        if not parenthesized:
            return tokens[start].text, start + 1
        if start + 1 >= len(tokens) or tokens[start + 1].text != ")":
            raise _Syntax("defined( without )")
        return tokens[start].text, start + 2

    # ------------------------------------------------------------ token access

    def peek(self, ahead: int = 0) -> _Item | None:
        index = self.pos + ahead
        return self.items[index] if index < len(self.items) else None

    def at(self, *texts: str) -> bool:
        item = self.peek()
        return item is not None and item.kind == "punct" and item.text in texts

    def take(self) -> _Item:
        item = self.peek()
        if item is None:
            raise _Syntax("unexpected end")
        self.pos += 1
        return item

    def expect(self, text: str) -> None:
        if not self.at(text):
            raise _Syntax(f"expected {text!r}")
        self.pos += 1

    # ------------------------------------------------------------ grammar

    def parse(self, items: list) -> Result:
        self.items, self.pos = items, 0
        if not items:
            raise _Syntax("empty expression")
        result = self.comma()
        if self.pos != len(items):
            raise _Syntax(f"unexpected {items[self.pos].text!r}")
        return result

    def comma(self) -> Result:
        result = self.assignment()
        while self.at(","):
            self.pos += 1
            result = _first_failure(result, self.assignment()) or failure(UNSUPPORTED, "comma")
        return result

    def assignment(self) -> Result:
        result = self.conditional()
        if self.at(*ASSIGNMENTS):
            self.pos += 1
            self.assignment()
            return failure(NONCONSTANT, "assignment")
        return result

    def conditional(self) -> Result:
        condition = self.binary(0)
        if not self.at("?"):
            return condition
        self.pos += 1
        yes = self.comma()
        self.expect(":")
        return self.choose(condition, yes, self.conditional())

    def binary(self, level: int) -> Result:
        if level == len(BINARY_LEVELS):
            return self.cast()
        result = self.binary(level + 1)
        while self.at(*BINARY_LEVELS[level]):
            symbol = self.take().text
            result = self.apply(symbol, result, self.binary(level + 1))
        return result

    def cast(self) -> Result:
        if not self.at("("):
            return self.unary()
        start = self.pos
        self.pos += 1
        target = self.type_name()
        if target is not None:
            self.expect(")")
            return self.apply_cast(target, self.cast())
        self.pos = start
        return self.unknown_cast() or self.unary()

    def unary(self) -> Result:
        item = self.peek()
        if item is None:
            raise _Syntax("unexpected end")
        if item.kind == "punct" and item.text in ("+", "-", "~", "!"):
            self.pos += 1
            return self.unary_operation(item.text, self.cast())
        if item.kind == "punct" and item.text in ("*", "&"):
            self.pos += 1
            self.cast()
            return failure(NONCONSTANT, "address or indirection")
        if item.kind == "punct" and item.text in ("++", "--"):
            self.pos += 1
            self.unary()
            return failure(NONCONSTANT, "increment")
        if item.kind == "id" and item.text == "sizeof":
            self.pos += 1
            return self.size_of()
        return self.postfix()

    def postfix(self) -> Result:
        callee = self.peek()
        result = self.primary()
        while True:
            if self.at("["):
                self.pos += 1
                self.comma()
                self.expect("]")
                result = failure(NONCONSTANT, "subscript")
            elif self.at("("):
                self.pos += 1
                self.arguments()
                result = failure(NONCONSTANT, "call", callee.text)
            elif self.at(".", "->"):
                self.pos += 1
                if self.take().kind != "id":
                    raise _Syntax("member access without a name")
                result = failure(NONCONSTANT, "member access")
            elif self.at("++", "--"):
                self.pos += 1
                result = failure(NONCONSTANT, "increment")
            else:
                return result

    def arguments(self) -> None:
        if self.at(")"):
            self.pos += 1
            return
        self.assignment()
        while self.at(","):
            self.pos += 1
            self.assignment()
        self.expect(")")

    def primary(self) -> Result:
        item = self.take()
        if item.kind == "num":
            return self.number(item)
        if item.kind == "char":
            return self.character(item)
        if item.kind == "str":
            while self.peek() is not None and self.peek().kind == "str":
                self.pos += 1
            return failure(NONCONSTANT, "string literal")
        if item.kind == "bad":
            return item.result
        if item.kind == "defined":
            return self.defined(item)
        if item.kind == "call":
            return self.macro_call(item)
        if item.kind == "id":
            return self.identifier(item)
        if item.kind == "punct" and item.text == "(":
            result = self.comma()
            self.expect(")")
            return result
        if item.kind == "punct" and item.text == "::":
            return failure(UNSUPPORTED, "C++ construct", "::")
        raise _Syntax(f"unexpected {item.text!r}")

    # ------------------------------------------------------------ leaves

    def leaf(self, value, ctype: CType, item: _Item, literal: bool) -> Result:
        """A value that ITEM gives. In #if mode an integer acts as the #if type of its signedness."""
        names = (item.origin,) if item.origin else (() if literal else (item.text,))
        result = Result(OK, value, ctype, names=names, literal=literal and not item.origin)
        if self.mode != "pp":
            return result
        if ctype.kind not in ("int", "bool"):
            return failure(UNSUPPORTED, "not a #if expression", ctype.name)
        target = self.intmax if ctype.signed or ctype.kind == "bool" else self.uintmax
        return _with_sources(_fit(value, target, self.profile.narrowing, "narrowing"), result)

    def number(self, item: _Item) -> Result:
        match = FLOATING.match(item.text)  # first: the integer pattern would take "e3f" in 1e3f as a suffix
        if match is None:
            return self.integer(item)
        if self.mode == "pp":
            return failure(UNSUPPORTED, "not a #if expression", item.text)
        digits, suffix = match.groups()
        ctype = self.profile.builtin(("float",) if suffix in ("f", "F") else ("long", "double") if suffix else
                                     ("double",))
        value = round_float(Fraction(digits), ctype.bits)
        if value is None:
            return failure(UNSUPPORTED, "float range", item.text)
        return self.leaf(value, ctype, item, True)

    def integer(self, item: _Item) -> Result:
        match = INTEGER.match(item.text)
        if match is None:
            return failure(UNSUPPORTED, "literal", item.text)
        digits, suffix = match.groups()
        octal = digits.startswith("0") and len(digits) > 1 and digits[1] not in "xX"
        hexadecimal = digits[1:2] in ("x", "X")
        value = int(digits, 16 if hexadecimal else 8 if octal else 10)
        ctype = self.integer_type(value, octal or hexadecimal, suffix.lower())
        if ctype is None:
            return failure(UNSUPPORTED, "literal", item.text)
        return self.leaf(value, ctype, item, True)

    def integer_type(self, value: int, hex_or_octal: bool, suffix: str) -> CType | None:
        """The type of an integer literal, or None when the suffix or the size is not modelled. In #if mode a literal
        is the signed #if type when it fits and has no u, else the unsigned one."""
        if suffix not in BASIC_SUFFIXES and suffix not in self.profile.extra_suffixes:
            return None
        if self.mode == "pp":
            if "u" not in suffix and value <= self.intmax.highest():
                return self.intmax
            return self.uintmax if value <= self.uintmax.highest() else None
        if suffix:
            candidates = LITERAL_TYPES[suffix][hex_or_octal]
        else:
            candidates = HEX_TYPES if hex_or_octal else self.profile.decimal_types
        if suffix in BASIC_SUFFIXES:
            wide = [name for name in self.profile.wide_types if "u" not in suffix or name.startswith("unsigned")]
            candidates = (*candidates, *wide)
        for name in candidates:
            ctype = self.profile.int_type(name)
            if value <= ctype.highest():
                return ctype
        return None

    def character(self, item: _Item) -> Result:
        wide = item.text.startswith("L")
        body = item.text[2 if wide else 1:-1]
        units = _char_units(body, 0xFFFF if wide else 0xFF)
        if not units or (wide and len(units) > 1):
            return failure(UNSUPPORTED, "character constant", item.text)
        if wide:
            return self.leaf(units[0], self.profile.wchar(), item, True)
        if len(units) == 1:
            char = self.profile.builtin(("char",))
            return self.leaf(_wrap(units[0], char), char if self.profile.language == "cpp" else self.int, item, True)
        # VC10 packs '\x41\x42' as 0x4241 but 'A\x42' as 0x4142; the rule for a leading numeric escape is not known.
        numeric_first = body[:1] == "\\" and body[1:2] in tuple("01234567x")
        if self.profile.multichar != BIG_ENDIAN or len(units) * 8 > self.int.bits or numeric_first:
            return failure(UNSUPPORTED, "character constant", item.text)
        packed = 0
        for unit in units:
            packed = packed << 8 | unit
        return self.leaf(_wrap(packed, self.int), self.int, item, True)

    def identifier(self, item: _Item) -> Result:
        name = item.text
        if self.mode == "pp" and name in ("true", "false"):  # VC10 rejects them in #if (error C1017)
            return failure(UNSUPPORTED, "true or false in #if", name)
        if self.profile.language == "cpp" and name in ("true", "false"):
            return self.leaf(int(name == "true"), self.profile.builtin(("bool",)), item, True)
        if self.profile.language == "cpp" and name in CPP_UNSUPPORTED:
            return failure(UNSUPPORTED, "C++ construct", name)
        if name in self.profile.type_words or name in TAG_WORDS:
            raise _Syntax(f"type word {name!r} in an expression")
        found = self.resolve(name)
        if found is None:
            return failure(UNRESOLVED, "unknown identifier", name)
        if not found.ok:
            return found
        return self.leaf(found.value, found.ctype, item, False)

    def defined(self, item: _Item) -> Result:
        answer = self.is_defined(item.text)
        if isinstance(answer, Result):
            return answer
        if answer is None:
            return failure(UNRESOLVED, "unknown identifier", item.text)
        return self.leaf(int(answer), self.int, item, False)

    def macro_call(self, item: _Item) -> Result:
        """A function-like macro use: nonconstant when an argument names a variable, else unsupported."""
        for token in item.args:
            if token.kind == "id" and self.expand(token.text) is None:
                found = self.resolve(token.text)
                if found is not None and found.status == NONCONSTANT:
                    return found
        return failure(UNSUPPORTED, "function-like macro", item.text)

    # ------------------------------------------------------------ types

    def type_name(self) -> CType | Result | None:
        """At the token after "(": the type that a type name spells, stopping at the ")". None when the tokens do not
        start a type name; a failed Result when they start one that the tools do not model."""
        start, words, base = self.pos, [], None
        while (item := self.peek()) is not None and item.kind == "id":
            if item.text in QUALIFIERS:
                self.pos += 1
            elif item.text in self.profile.type_words and base is None:
                words.append(item.text)
                self.pos += 1
            elif item.text in TAG_WORDS and base is None and not words:
                tag = self.peek(1)
                if tag is None or tag.kind != "id":
                    raise _Syntax(f"{item.text} without a tag")
                self.pos += 2
                spelling = f"{item.text} {tag.text}"
                base = self.resolve_type(spelling) or CType("record", 0, name=spelling)
            elif base is None and not words and (found := self.resolve_type(item.text)) is not None:
                base = found
                self.pos += 1
            else:
                break
        if not words and base is None:
            self.pos = start
            return None
        if words:  # the loop takes no typedef or tag after a keyword, so BASE is still None here
            base = self.profile.builtin(tuple(words))
            if base is None:
                return self.skip_type_name(" ".join(words))
        pointer = False
        while self.at("*"):
            self.pos += 1
            pointer = True
            while (item := self.peek()) is not None and item.kind == "id" and item.text in QUALIFIERS:
                self.pos += 1
        if not self.at(")"):
            return self.skip_type_name(base.name)
        return self.profile.pointer(base.name + " *") if pointer else base

    def skip_type_name(self, spelling: str) -> Result:
        """Skips to the ")" that closes a type name the tools do not model."""
        depth = 0
        while (item := self.peek()) is not None and not (depth == 0 and self.at(")")):
            if item.kind == "punct" and item.text in ("(", ")"):
                depth += 1 if item.text == "(" else -1
            self.pos += 1
        return failure(UNSUPPORTED, "type name", spelling)

    def unknown_cast(self) -> Result | None:
        """`(NAME) operand`, where NAME is unknown: a cast to an unknown type, so unresolved."""
        name, close, after = self.peek(1), self.peek(2), self.peek(3)
        if name is None or name.kind != "id" or close is None or close.kind != "punct" or close.text != ")":
            return None
        starts_operand = after is not None and (after.kind in ("num", "char", "str", "id", "call") or
                                                (after.kind == "punct" and after.text in ("(", "~", "!")))
        if not starts_operand or self.resolve(name.text) is not None or name.text in CPP_UNSUPPORTED:
            return None
        self.pos += 3
        return _first_failure(self.cast(), failure(UNRESOLVED, "unknown identifier", name.text))

    def apply_cast(self, target: CType | Result, operand: Result) -> Result:
        if isinstance(target, Result):
            return _first_failure(operand, target)
        if self.mode == "pp":
            return _first_failure(operand) or failure(UNSUPPORTED, "not a #if expression", "cast")
        return convert(operand, target, self.profile)

    def size_of(self) -> Result:
        """sizeof(type), or sizeof of an expression whose value and so its type are known."""
        if self.at("("):
            start = self.pos
            self.pos += 1
            target = self.type_name()
            if target is not None:
                self.expect(")")
                result = target if isinstance(target, Result) else self.size_result(target)
            else:
                self.pos = start
                result = None
        else:
            result = None
        if result is None:
            operand = self.unary()
            if operand.ok:
                result = self.size_result(operand.ctype)
            elif operand.status == UNRESOLVED:
                result = operand
            else:
                result = failure(UNSUPPORTED, "sizeof of an expression", operand.cause)
        if self.mode == "pp":
            return failure(UNSUPPORTED, "not a #if expression", "sizeof")
        return result

    def size_result(self, ctype: CType) -> Result:
        if ctype.kind == "void" or ctype.bits == 0:
            return failure(UNSUPPORTED, "sizeof", ctype.name)
        return Result(OK, ctype.bits // 8, self.profile.int_type(self.profile.size_type))

    def promote(self, ctype: CType) -> CType:
        if ctype.kind == "bool" or (ctype.kind == "int" and ctype.rank < self.int.rank):
            return self.int if ctype.signed or ctype.bits < self.int.bits else self.uint
        return ctype

    def common(self, left: CType, right: CType) -> CType:
        """The usual arithmetic conversions."""
        if "float" in (left.kind, right.kind):
            bits = max(ctype.bits for ctype in (left, right) if ctype.kind == "float")
            return self.profile.builtin(("float",) if bits == 32 else ("double",))
        left, right = self.promote(left), self.promote(right)
        if left.signed == right.signed:
            return right if right.rank > left.rank else left
        unsigned, signed = (right, left) if left.signed else (left, right)
        if unsigned.rank >= signed.rank:
            return unsigned
        if signed.bits > unsigned.bits:
            return signed
        return CType("int", signed.bits, False, signed.rank, "unsigned " + signed.name)

    # ------------------------------------------------------------ operations

    def unary_operation(self, symbol: str, operand: Result) -> Result:
        if not operand.ok:
            return operand
        if symbol == "!":
            if operand.ctype.kind not in SCALAR_KINDS:
                return failure(UNSUPPORTED, "operand type", symbol)
            return replace(operand, value=int(not operand.value), ctype=self.truth)
        ctype = self.promote(operand.ctype)
        if ctype.kind not in ("int", "float") or (symbol == "~" and ctype.kind == "float"):
            return failure(UNSUPPORTED, "operand type", symbol)
        value = convert(operand, ctype, self.profile).value
        if ctype.kind == "float":
            return replace(operand, value=-value if symbol == "-" else value, ctype=ctype)
        if symbol == "+":
            return replace(operand, value=value, ctype=ctype)
        if symbol == "-":
            return _with_sources(_fit(-value, ctype, self.profile.signed_overflow, "signed overflow"), operand)
        return _with_sources(_fit(~value, ctype, WRAP, ""), operand)

    def apply(self, symbol: str, left: Result, right: Result) -> Result:
        if symbol in ("&&", "||"):
            return self.logical(symbol, left, right)
        bad = _first_failure(left, right)
        if bad is not None:
            return bad
        if symbol in ("<<", ">>"):
            return _with_sources(self.shift(symbol, left, right), left, right)
        return _with_sources(self.arithmetic(symbol, left, right), left, right)

    def arithmetic(self, symbol: str, left: Result, right: Result) -> Result:
        if left.ctype.kind not in ARITHMETIC_KINDS or right.ctype.kind not in ARITHMETIC_KINDS:
            return failure(UNSUPPORTED, "operand type", symbol)
        ctype = self.common(left.ctype, right.ctype)
        a = convert(left, ctype, self.profile)
        b = convert(right, ctype, self.profile)
        bad = _first_failure(a, b)
        if bad is not None:
            return bad
        if symbol in COMPARISONS:
            return Result(OK, int(COMPARISONS[symbol](a.value, b.value)), self.truth)
        if ctype.kind == "float":
            return self.float_operation(symbol, a.value, b.value, ctype)
        return self.integer_operation(symbol, a.value, b.value, ctype)

    def integer_operation(self, symbol: str, a: int, b: int, ctype: CType) -> Result:
        if symbol in ("/", "%"):
            if b == 0:
                return failure(UNSUPPORTED, "division by zero")
            quotient = abs(a) // abs(b) * (1 if (a < 0) == (b < 0) else -1)
            # The lowest value divided by -1: the VC10 probe folds it to the lowest value, remainder 0.
            if quotient > ctype.highest() and self.profile.signed_overflow != WRAP:
                return failure(UNSUPPORTED, "division overflow")
            return Result(OK, _wrap(quotient if symbol == "/" else a - b * quotient, ctype), ctype)
        return _fit(INTEGER_OPERATIONS[symbol](a, b), ctype, self.profile.signed_overflow, "signed overflow")

    @staticmethod
    def float_operation(symbol: str, a: float, b: float, ctype: CType) -> Result:
        if symbol not in FLOAT_OPERATIONS:
            return failure(UNSUPPORTED, "operand type", symbol)
        if symbol == "/" and b == 0:
            return failure(UNSUPPORTED, "division by zero")
        value = round_float(FLOAT_OPERATIONS[symbol](a, b), ctype.bits)
        if value is None:
            return failure(UNSUPPORTED, "float range", symbol)
        return Result(OK, value, ctype)

    def shift(self, symbol: str, left: Result, right: Result) -> Result:
        ctype, count_type = self.promote(left.ctype), self.promote(right.ctype)
        if ctype.kind != "int" or count_type.kind != "int":
            return failure(UNSUPPORTED, "operand type", symbol)
        value = convert(left, ctype, self.profile).value
        count = convert(right, count_type, self.profile).value
        if not 0 <= count < ctype.bits:
            return failure(UNSUPPORTED, "shift count", str(count))
        if symbol == "<<":
            if value < 0 and self.profile.signed_overflow != WRAP:
                return failure(UNSUPPORTED, "signed overflow", "left shift of a negative value")
            return _fit(value << count, ctype, self.profile.signed_overflow, "signed overflow")
        if value < 0 and self.profile.signed_right_shift != ARITHMETIC:
            return failure(UNSUPPORTED, "signed right shift")
        return Result(OK, value >> count, ctype)

    def logical(self, symbol: str, left: Result, right: Result) -> Result:
        for side in (left, right):
            if side.ok and side.ctype.kind not in SCALAR_KINDS:
                return failure(UNSUPPORTED, "operand type", symbol)
        if left.ok and bool(left.value) == (symbol == "||"):
            if self.mode == "pp" or right.status != NONCONSTANT:
                return _with_sources(Result(OK, int(symbol == "||"), self.truth), left)
        # In #if, `x && 0` is 0 and `x || 1` is 1 whatever integer x is, so an unresolved x does not matter.
        # Not in expressions: there an unknown name may be a variable, and the site must stay unresolved.
        if self.mode == "pp" and left.status == UNRESOLVED and right.ok and bool(right.value) == (symbol == "||"):
            return _with_sources(Result(OK, int(symbol == "||"), self.truth), right)
        bad = _first_failure(left, right)
        if bad is not None:
            return bad
        return _with_sources(Result(OK, int(bool(right.value)), self.truth), left, right)

    def choose(self, condition: Result, yes: Result, no: Result) -> Result:
        if not condition.ok:
            return _first_failure(condition, yes, no)
        taken, skipped = (yes, no) if condition.value else (no, yes)
        if self.mode == "pp":
            return _with_sources(taken, condition, taken)
        bad = _first_failure(taken, skipped)
        if bad is not None:
            return bad
        ctype = self.branch_type(yes.ctype, no.ctype)
        if ctype is None:
            return failure(UNSUPPORTED, "operand type", "?:")
        return _with_sources(convert(taken, ctype, self.profile), condition, yes, no)

    def branch_type(self, yes: CType, no: CType) -> CType | None:
        if self.profile.language == "cpp" and yes == no:  # C++ keeps a shared type: sizeof(1 ? 'a' : 'b') is 1
            return yes
        if yes.kind in ARITHMETIC_KINDS and no.kind in ARITHMETIC_KINDS:
            return self.common(yes, no)
        if yes.kind == "pointer" and no.kind in ("pointer", "int"):
            return yes
        if no.kind == "pointer" and yes.kind == "int":
            return no
        return None
