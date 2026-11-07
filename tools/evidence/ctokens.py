"""C and C++ tokens: the shared lexer of the evidence tools.

tokenize() reads decoded text, never bytes. It first drops a UTF-8 byte order mark, turns CRLF into LF and joins the
lines that end with a backslash, as a compiler's first phases do. It then splits the text into identifiers, numbers,
character constants, strings and punctuators, and gives each token its line in the file as written. A token whose
line starts a new logical line has `bol` set, so the header reader can find directives. Comments are not tokens;
they come back apart, with their lines, so the source reader can find annotations.

A trigraph (such as ??/) makes the text unsupported: tokenize() raises Unsupported. A quote with no closing quote is
one punctuator token, as in text that a compiler skips, such as `#error don't`.

drop_directives() and find_calls() are the shared scanning steps of the game source reader and the sample reader.
find_fields(), find_values() and raw_offsets() scan function bodies for the game source reader.

Standard library only.
"""

import bisect
import re
from dataclasses import dataclass

PUNCTUATORS = sorted("""
    ... <<= >>= ->* -> ++ -- << >> <= >= == != && || += -= *= /= %= &= ^= |= ## :: .*
    # ( ) [ ] { } . , ; : ? ~ ! + - * / % < > = & ^ | \\ @ $ `
""".split(), key=len, reverse=True)
TRIGRAPH = re.compile(r"\?\?[=/'()!<>\-]")
LEXEME = re.compile(r"""
    (?P<space>[ \t\f\v]+)
  | (?P<newline>\n)
  | (?P<block>/\*.*?\*/)
  | (?P<line>//[^\n]*)
  | (?P<str>L?"(?:[^"\\\n]|\\.)*")
  | (?P<char>L?'(?:[^'\\\n]|\\.)*')
  | (?P<num>\.?[0-9](?:[eEpP][+-]|[0-9A-Za-z_.])*)
  | (?P<id>[A-Za-z_$][0-9A-Za-z_$]*)
  | (?P<punct>""" + "|".join(re.escape(p) for p in PUNCTUATORS) + r""")
  | (?P<other>.)
""", re.VERBOSE | re.DOTALL)
OPENERS = {"(": ")", "[": "]", "{": "}"}
CLOSERS = frozenset(OPENERS.values())
ASSIGNMENT = 2  # the precedence of the assignment operators
BINARY_PRECEDENCE = {"*": 13, "/": 13, "%": 13, "+": 12, "-": 12, "<<": 11, ">>": 11, "<": 10, ">": 10, "<=": 10,
                     ">=": 10, "==": 9, "!=": 9, "&": 8, "^": 7, "|": 6, "&&": 5, "||": 4, "?": 3,
                     **dict.fromkeys(("=", "*=", "/=", "%=", "+=", "-=", "<<=", ">>=", "&=", "^=", "|="), ASSIGNMENT)}
FIELD_OPERATORS = frozenset({"=", "|=", "&=", "==", "!=", "&"})
VALUE_OPERATORS = frozenset({"=", "==", "!="})
VARIABLE, CASE, RETURN = "variable", "case", "return"  # the kinds of value spots
EXPRESSION_KEYWORDS = frozenset({"return", "case", "sizeof", "else", "do"})  # words that an operand follows


class Unsupported(Exception):
    """Text that the tools do not model, with the reason."""


@dataclass(frozen=True)
class Token:
    kind: str  # id, num, char, str or punct
    text: str
    line: int  # 1-based line in the file as written
    bol: bool  # the first token of a logical line
    column: int = 0  # 1-based column in the line as written, a tab counting 1


@dataclass(frozen=True)
class Comment:
    text: str
    line: int  # the line it starts on
    end_line: int  # the line it ends on


def splice(text: str) -> tuple[str, list[int], list[int]]:
    """The text after the first phases, and the splice map: at each offset in SPLICE_AT, the written line number
    jumps by the matching count in SKIPPED."""
    if text.startswith("﻿"):
        text = text[1:]
    text = text.replace("\r\n", "\n")
    parts, offsets, skipped, length = [], [], [], 0
    for piece in re.split(r"(\\\n)", text):
        if piece == "\\\n":
            offsets.append(length)
            skipped.append(1)
            continue
        parts.append(piece)
        length += len(piece)
    return "".join(parts), offsets, skipped


def tokenize(text: str) -> tuple[list[Token], list[Comment]]:
    """The tokens and comments of TEXT. Raises Unsupported on a trigraph or an unterminated block comment."""
    spliced, splice_at, skipped = splice(text)
    if TRIGRAPH.search(spliced):
        raise Unsupported("trigraph")
    extra = [0]
    for count in skipped:
        extra.append(extra[-1] + count)
    newlines = [match.start() for match in re.finditer("\n", spliced)]

    def written_line(offset: int) -> int:
        return bisect.bisect_left(newlines, offset) + 1 + extra[bisect.bisect_right(splice_at, offset)]

    def written_column(offset: int) -> int:
        newline = bisect.bisect_left(newlines, offset)
        line_start = newlines[newline - 1] + 1 if newline else 0
        splice = bisect.bisect_right(splice_at, offset)
        if splice:
            line_start = max(line_start, splice_at[splice - 1])
        return offset - line_start + 1

    tokens, comments, bol = [], [], True
    for match in LEXEME.finditer(spliced):
        kind = match.lastgroup
        if kind == "space":
            continue
        if kind == "newline":
            bol = True
            continue
        if kind in ("block", "line"):
            comments.append(Comment(match.group(), written_line(match.start()), written_line(match.end() - 1)))
            continue
        lexeme = match.group()
        if lexeme == "/" and spliced.startswith("/*", match.start()):  # the block group needs the closing */
            raise Unsupported("unterminated block comment")
        if kind == "other":
            kind = "punct"
        tokens.append(Token(kind, lexeme, written_line(match.start()), bol, written_column(match.start())))
        bol = False
    return tokens, comments


def tokens_of(text: str) -> list[Token]:
    """The tokens of a short text, such as a macro body or an argument."""
    return tokenize(text)[0]


def drop_words(tokens: list[Token], words, prefixes=()) -> list[Token]:
    """TOKENS without the identifiers in WORDS or starting with one of PREFIXES, each with the balanced (...) group
    that follows it, if any. For calling conventions, SAL annotations and __declspec(...)."""
    return [tokens[index] for index in kept_indices(tokens, words, prefixes)]


def kept_indices(tokens: list[Token], words, prefixes=()) -> list[int]:
    """The indices of the tokens that drop_words keeps."""
    kept, index, prefixes = [], 0, tuple(prefixes)
    while index < len(tokens):
        token = tokens[index]
        index += 1
        if token.kind != "id" or not (token.text in words or token.text.startswith(prefixes)):
            kept.append(index - 1)
            continue
        if index < len(tokens) and tokens[index].text == "(":
            depth = 0
            while index < len(tokens):
                if tokens[index].kind == "punct" and tokens[index].text in ("(", ")"):
                    depth += 1 if tokens[index].text == "(" else -1
                index += 1
                if depth == 0:
                    break
    return kept


def spelling(tokens: list[Token]) -> str:
    """The tokens joined with single spaces: one spelling for text that differs only in white space."""
    return " ".join(token.text for token in tokens)


def unwrapped(texts: list[str]) -> list[str]:
    """TEXTS without the parentheses that wrap all of it, as often as they do: ( ( a ) ) gives a, and ( a ) | ( b )
    stays."""
    while len(texts) >= 2 and texts[0] == "(" and texts[-1] == ")" and _wraps(texts):
        texts = texts[1:-1]
    return texts


def _wraps(texts: list[str]) -> bool:
    """The first ( closes at the last text."""
    depth = 0
    for index, text in enumerate(texts):
        depth += {"(": 1, ")": -1}.get(text, 0)
        if depth == 0:
            return index == len(texts) - 1
    return False


def drop_directives(tokens: list[Token], directive=None) -> list[Token]:
    """TOKENS without their directive lines. DIRECTIVE(words, line), when given, gets the tokens after the # of each
    directive and its line, and may raise Unsupported. The tokens between #if, #else and #endif lines stay, so text
    read with no DIRECTIVE keeps every branch."""
    kept, index = [], 0
    while index < len(tokens):
        token = tokens[index]
        if not (token.bol and token.text == "#"):
            kept.append(token)
            index += 1
            continue
        end = index + 1
        while end < len(tokens) and not tokens[end].bol:
            end += 1
        if directive:
            directive(tokens[index + 1:end], token.line)
        index = end
    return kept


@dataclass(frozen=True)
class FoundCall:
    position: int  # the index of the callee token
    outer: tuple  # ((callee, 1-based argument index), ...) of the calls around this one, outermost first
    starts: tuple  # the index of the first token of each argument
    close: int  # the index of the closing )

    def arguments(self, tokens: list[Token]) -> tuple:
        """One tuple of tokens per argument; () for f()."""
        ends = [start - 1 for start in self.starts[1:]] + [self.close]
        arguments = tuple(tuple(tokens[start:end]) for start, end in zip(self.starts, ends))
        return () if arguments == ((),) else arguments


def find_calls(tokens: list[Token], is_callee, low: int = -1, high: int | None = None) -> list[FoundCall]:
    """The calls strictly between LOW and HIGH, in callee order: each ( right after a token whose index IS_CALLEE
    accepts. The arguments split at the call's depth-1 commas, with (), [] and {} balanced. A closer with no opener
    is skipped and a call that never closes is dropped, so text with every #if branch kept still reads."""
    high = len(tokens) if high is None else high
    found, stack = [], []
    for index in range(low + 1, high):
        token = tokens[index]
        if token.kind != "punct":
            continue
        if token.text in OPENERS:
            if token.text == "(" and index - 1 > low and is_callee(index - 1):
                outer = tuple((entry[0], len(entry[2])) for entry in stack if entry)
                stack.append((tokens[index - 1].text, index - 1, [index + 1], outer))
            else:
                stack.append(None)
        elif token.text in CLOSERS:
            entry = stack.pop() if stack else None
            if entry:
                found.append(FoundCall(entry[1], entry[3], tuple(entry[2]), index))
        elif token.text == "," and stack and stack[-1]:
            stack[-1][2].append(index + 1)
    found.sort(key=lambda call: call.position)
    return found


@dataclass(frozen=True)
class FoundField:
    base: int  # the index of the first token of the expression before the . or ->
    member: int  # the index of the member name
    operator: str  # =, |=, &=, ==, != or &; x.f = x.f | K reads as x.f |= K, and & as &=
    value: int  # the index of the first value token
    end: int  # the index after the last value token


def find_fields(tokens: list[Token], is_callee, low: int = -1, high: int | None = None) -> list[FoundField]:
    """The field writes and compares strictly between LOW and HIGH: a member after . or -> with a field operator
    right after it. Its base expression (names, member chains, subscripts, calls whose callee index IS_CALLEE accepts,
    and groups in parentheses) must be the whole left operand. The value is the right operand, as far as C precedence
    takes it."""
    high = len(tokens) if high is None else high
    found, folded = [], set()
    for member in range(low + 3, high - 2):
        operator = tokens[member + 1].text
        if tokens[member].kind != "id" or tokens[member - 1].text not in (".", "->") or operator not in FIELD_OPERATORS:
            continue
        base = _postfix_start(tokens, member - 2, low, is_callee)
        if member in folded or base is None or not _whole_left_operand(tokens, base, operator, low):
            continue
        precedence = BINARY_PRECEDENCE[operator]
        end = operand_end(tokens, member + 2, high, 1 if precedence == ASSIGNMENT else precedence)
        if end <= member + 2:
            continue
        spot = _compound(tokens, FoundField(base, member, operator, member + 2, end))
        if spot.operator != operator:
            folded.add(spot.value - 2)  # in x.f = x.f & K, the second x.f is part of the &=
        found.append(spot)
    return found


@dataclass(frozen=True)
class FoundValue:
    kind: str  # VARIABLE, CASE or RETURN
    lvalue: tuple  # (start, end) of the variable or of the switch expression; empty for a return
    operator: str  # =, == or != for a variable; case; return
    position: int  # the index of the variable, of case or of return
    value: int  # the index of the first value token
    end: int  # the index after the last value token


def find_values(tokens: list[Token], is_name, low: int = -1, high: int | None = None) -> list[FoundValue]:
    """The value spots strictly between LOW and HIGH, in position order:
    - a plain variable (an identifier that IS_NAME accepts) right before =, == or !=, as the whole left operand; a
      declaration such as `int x = 1` is no spot, but `int a, b = 1` is (the caller drops declarations);
    - a case label of the innermost braced switch around it, with that switch's expression;
    - return with a value."""
    high = len(tokens) if high is None else high
    switches = _switches(tokens, low, high)
    found = []
    for index in range(low + 1, high):
        token = tokens[index]
        if token.text == "case" and token.kind == "id":
            end = operand_end(tokens, index + 1, high, 0)
            around = [switch for switch in switches if switch[2] < index < switch[3]]
            if around and end > index + 1 and end < high and tokens[end].text == ":":
                head = max(around)
                found.append(FoundValue(CASE, (head[0], head[1]), "case", index, index + 1, end))
        elif token.text == "return" and token.kind == "id":
            end = operand_end(tokens, index + 1, high, 0)
            if end > index + 1:
                found.append(FoundValue(RETURN, (), "return", index, index + 1, end))
        elif index + 2 < high and tokens[index + 1].text in VALUE_OPERATORS and _is_variable(tokens, index, is_name, low):
            operator = tokens[index + 1].text
            precedence = BINARY_PRECEDENCE[operator]
            end = operand_end(tokens, index + 2, high, 1 if precedence == ASSIGNMENT else precedence)
            if end > index + 2:
                found.append(FoundValue(VARIABLE, (index, index + 1), operator, index, index + 2, end))
    return found


def _is_variable(tokens: list[Token], index: int, is_name, low: int) -> bool:
    """The identifier at INDEX is a whole left operand of the operator after it, and no declaration names it."""
    if tokens[index].kind != "id" or not is_name(index):
        return False
    before = index - 1
    if before > low and tokens[before].kind == "id" and tokens[before].text not in ("return", "else", "do"):
        return False  # a declaration, such as int x = 1
    return _whole_left_operand(tokens, index, tokens[index + 1].text, low)


def _switches(tokens: list[Token], low: int, high: int) -> list[tuple]:
    """(expression start, expression end, body opener, body closer) of each braced switch between LOW and HIGH."""
    found = []
    for index in range(low + 1, high - 1):
        if tokens[index].text != "switch" or tokens[index + 1].text != "(":
            continue
        close = matching_closer(tokens, index + 1, high)
        if close is None or close + 1 >= high or tokens[close + 1].text != "{":
            continue
        body = matching_closer(tokens, close + 1, high)
        if body is not None:
            found.append((index + 2, close, close + 1, body))
    return found


def operand_end(tokens: list[Token], start: int, high: int, limit: int) -> int:
    """The index after the operand that starts at START. It ends at HIGH, or at a ;, a , or a closer at depth 0, a :
    that no ? opened, or a binary operator whose precedence is LIMIT or less."""
    depth = pending = 0
    for index in range(start, high):
        token = tokens[index]
        if token.kind != "punct":
            continue
        text = token.text
        if text in OPENERS:
            depth += 1
        elif text in CLOSERS:
            if depth == 0:
                return index
            depth -= 1
        elif depth:
            continue
        elif text in (";", ","):
            return index
        elif text == ":":
            if not pending:
                return index
            pending -= 1
        elif text in BINARY_PRECEDENCE and ends_operand(tokens, index - 1, start - 1):
            if BINARY_PRECEDENCE[text] <= limit:
                return index
            pending += text == "?"
    return high


def ends_operand(tokens: list[Token], index: int, low: int) -> bool:
    """The token at INDEX, above LOW, ends an operand, so an operator right after it is binary."""
    if index <= low:
        return False
    token = tokens[index]
    if token.kind == "id":
        return token.text not in EXPRESSION_KEYWORDS
    return token.kind in ("num", "char", "str") or token.text in (")", "]")


def _postfix_start(tokens: list[Token], last: int, low: int, is_callee) -> int | None:
    """The index of the first token of the postfix expression that ends at LAST, or None when none ends there."""
    index = last
    while index > low:
        text = tokens[index].text
        if text in (")", "]"):
            opener = matching_opener(tokens, index, low)
            if opener is None:
                return None
            if text == ")" and not (opener - 1 > low and is_callee(opener - 1)):
                return opener
            index = opener - 1
        elif tokens[index].kind != "id":
            return None
        elif index - 1 > low and tokens[index - 1].text in (".", "->"):
            index -= 2
        else:
            return index
    return None


def matching_opener(tokens: list[Token], close: int, low: int) -> int | None:
    """The index of the bracket that the closer at CLOSE matches, searched down to just above LOW, or None."""
    depth = 0
    for index in range(close, low, -1):
        text = tokens[index].text
        if text in CLOSERS:
            depth += 1
        elif text in OPENERS:
            depth -= 1
            if depth == 0:
                return index
    return None


def matching_closer(tokens: list[Token], opener: int, high: int) -> int | None:
    """The index of the bracket that closes the opener at OPENER, searched up to just below HIGH, or None."""
    depth = 0
    for index in range(opener, high):
        text = tokens[index].text
        if text in OPENERS:
            depth += 1
        elif text in CLOSERS:
            depth -= 1
            if depth == 0:
                return index
    return None


def _whole_left_operand(tokens: list[Token], base: int, operator: str, low: int) -> bool:
    """No token before BASE takes part of the left operand of OPERATOR: no unary operator or ::, no cast before a
    compare, and no binary operator that binds tighter."""
    before = base - 1
    if before <= low or tokens[before].kind != "punct":
        return True  # nothing, or a keyword such as return
    text = tokens[before].text
    if text in ("(", "[", "{", "}", ";", ",", ":"):
        return True
    precedence = BINARY_PRECEDENCE[operator]
    if text == ")":
        return precedence == ASSIGNMENT  # the head of an if or while; before a compare, a cast
    if text not in BINARY_PRECEDENCE or not ends_operand(tokens, before - 1, low):
        return False  # a unary operator or ::
    if precedence == ASSIGNMENT:
        return BINARY_PRECEDENCE[text] <= BINARY_PRECEDENCE["?"]  # a = x.f = 1, c ? x.f = 1 : 0
    return BINARY_PRECEDENCE[text] < precedence


def _compound(tokens: list[Token], found: FoundField) -> FoundField:
    """X.F = X.F | K as X.F |= K, and & as &=, when K is the whole right operand of that | or &."""
    joint = found.value + found.member + 1 - found.base
    if found.operator != "=" or joint + 1 >= found.end or tokens[joint].text not in ("|", "&"):
        return found
    if [token.text for token in tokens[found.value:joint]] != [token.text for token in
                                                              tokens[found.base:found.member + 1]]:
        return found
    binary = tokens[joint].text
    if operand_end(tokens, joint + 1, found.end, BINARY_PRECEDENCE[binary] - 1) != found.end:
        return found
    return FoundField(found.base, found.member, binary + "=", joint + 1, found.end)


def raw_offsets(tokens: list[Token], low: int, high: int) -> int:
    """The raw-offset accesses strictly between LOW and HIGH: a unary * on a pointer cast of a group that adds or
    subtracts, as in *(T *)((char *)p + 8)."""
    count = 0
    for index in range(low + 1, high - 1):
        if tokens[index].text != "*" or tokens[index + 1].text != "(" or ends_operand(tokens, index - 1, low):
            continue
        cast = matching_closer(tokens, index + 1, high)
        if cast is None or tokens[cast - 1].text != "*" or cast + 1 >= high or tokens[cast + 1].text != "(":
            continue
        group = matching_closer(tokens, cast + 1, high)
        if group is not None and _depth_one(tokens, cast + 1, group) & {"+", "-"}:
            count += 1
    return count


def _depth_one(tokens: list[Token], opener: int, close: int) -> set:
    """The texts of the tokens directly inside the group from OPENER to CLOSE."""
    texts, depth = set(), 0
    for index in range(opener + 1, close):
        text = tokens[index].text
        if text in CLOSERS:
            depth -= 1
        elif depth == 0:
            texts.add(text)
        if text in OPENERS:
            depth += 1
    return texts
