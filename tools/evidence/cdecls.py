"""C and C++ declarations on a token stream: the declarator reader that the source reader and the header reader share.

A Declarations object holds one token stream and its bracket pairs. It reads declarators (`type *a, b[n]`, function
pointers, prototypes, qualified C++ names) without a grammar: the declared name is the last identifier that is not a
keyword, a type word or the base type, before the first ( that follows it. A declaration whose type it does not know
still gives the name, with the type as spelled.

Standard library only.
"""

from ctokens import CLOSERS, OPENERS, Token, Unsupported, spelling

KEYWORDS = frozenset("""
    auto break case char const continue default do double else enum extern float for goto if inline int long
    register restrict return short signed sizeof static struct switch typedef union unsigned void volatile while
    __try __finally __leave __asm _asm __alignof __uuidof __if_exists __if_not_exists
    asm bool catch class const_cast delete dynamic_cast explicit export false friend mutable namespace new operator
    private protected public reinterpret_cast static_cast template this throw true try typeid typename using virtual
    nullptr and and_eq bitand bitor compl not not_eq or or_eq xor xor_eq
""".split())
STORAGE = frozenset({"static", "extern", "register", "auto", "inline", "typedef", "mutable", "virtual", "explicit",
                     "friend"})
QUALIFIERS = frozenset({"const", "volatile"})
TAG_WORDS = frozenset({"struct", "union", "enum", "class"})
POINTER_TOKENS = frozenset({"*", "&"})


def pairs(tokens: list[Token]) -> dict[int, int]:
    """The index of the matching bracket for each bracket token. Raises Unsupported when they do not balance."""
    found, stack = {}, []
    for index, token in enumerate(tokens):
        if token.kind != "punct":
            continue
        if token.text in OPENERS:
            stack.append(index)
        elif token.text in CLOSERS:
            if not stack or OPENERS[tokens[stack[-1]].text] != token.text:
                raise Unsupported("unbalanced brackets")
            opener = stack.pop()
            found[opener], found[index] = index, opener
    if stack:
        raise Unsupported("unbalanced brackets")
    return found


def without_extern_c(tokens: list[Token]) -> list[int]:
    """The indices of TOKENS without `extern "C"` and `extern "C++"`: a block keeps its contents."""
    bracket, dropped = pairs(tokens), set()
    for index, token in enumerate(tokens[:-1]):
        following = tokens[index + 1]
        if token.text == "extern" and following.kind == "str" and following.text in ('"C"', '"C++"'):
            dropped |= {index, index + 1}
            if index + 2 < len(tokens) and tokens[index + 2].text == "{":
                dropped |= {index + 2, bracket[index + 2]}
    return [index for index in range(len(tokens)) if index not in dropped]


class Declarations:
    """TOKENS with their bracket pairs. TYPES and TAGS are the type names and tags known so far; readers add to
    them. In C++, a tag is a type name."""

    def __init__(self, tokens: list[Token], profile, types: set, tags: set):
        self.tokens, self.profile, self.types, self.tags = tokens, profile, types, tags
        self.pairs = pairs(tokens)

    def is_name(self, token: Token) -> bool:
        return token.kind == "id" and token.text not in KEYWORDS and token.text not in self.profile.type_words

    def is_type(self, text: str) -> bool:
        if text in self.types or text.rsplit("::", 1)[-1] in self.types:
            return True
        return self.profile.language == "cpp" and text in self.tags

    def qualified(self, index: int) -> tuple[str, int]:
        """The qualified name that starts at INDEX (A::B, X::~X) and the index after it."""
        tokens, end = self.tokens, index
        if tokens[end].text == "~":
            end += 1
        end += 1
        while end + 1 < len(tokens) and tokens[end].text == "::":
            step = 2 if tokens[end + 1].text == "~" else 1
            if end + step >= len(tokens) or tokens[end + step].kind != "id":
                break
            end += step + 1
        return "".join(token.text for token in tokens[index:end]), end

    def skip(self, index: int) -> int:
        """The index after the token at INDEX, or after its bracket group."""
        return self.pairs[index] + 1 if self.tokens[index].text in OPENERS else index + 1

    def split(self, low: int, high: int, separator: str = ",") -> list[tuple[int, int]]:
        """The ranges between the depth-0 SEPARATORs of LOW..HIGH."""
        parts, start, index = [], low, low
        while index < high:
            if self.tokens[index].text == separator:
                parts.append((start, index))
                start = index + 1
            index = self.skip(index)
        parts.append((start, high))
        return parts

    def first(self, low: int, high: int, text: str) -> int:
        """The index of the first depth-0 TEXT in LOW..HIGH, or HIGH."""
        index = low
        while index < high:
            if self.tokens[index].text == text:
                return index
            index = self.skip(index)
        return high

    def has_tag(self, low: int, high: int) -> bool:
        """Whether LOW..HIGH holds a depth-0 struct, union, enum or class word."""
        return any(self.tokens[index].text in TAG_WORDS for index in self.depth_zero(low, high))

    def depth_zero(self, low: int, high: int):
        index = low
        while index < high:
            yield index
            index = self.skip(index)

    def note_tags(self, low: int, high: int):
        for index in range(low, high - 1):
            if self.tokens[index].text in TAG_WORDS and self.tokens[index + 1].kind == "id":
                self.note_tag(self.tokens[index].text, self.qualified(index + 1)[0])

    def note_tag(self, kind: str, name: str):
        self.tags.add(name)

    def function_head(self, start: int, brace: int) -> int | None:
        """The parameter group of the function definition whose body opens at BRACE, or None. A const member
        function (`) const {`) counts."""
        end = brace
        while end > start and self.tokens[end - 1].text in QUALIFIERS:
            end -= 1
        if end == start or self.tokens[end - 1].text != ")" or self.first(start, end, "=") < end:
            return None
        for index in self.depth_zero(start, end):
            if self.tokens[index].text == "(" and index > start and self.is_name(self.tokens[index - 1]):
                return index
        return None

    def name_before(self, start: int, group: int) -> tuple[str, int]:
        """The qualified name that ends just before GROUP, and its first index."""
        tokens, first = self.tokens, group - 1
        while first > start and (tokens[first - 1].text in ("::", "~")
                                 or tokens[first].text in ("::", "~") and tokens[first - 1].kind == "id"):
            first -= 1
        return "".join(token.text for token in tokens[first:group]), first

    def spelled(self, tokens: list[Token]) -> str:
        return spelling([token for token in tokens if token.text not in STORAGE])

    def declarator(self, low: int, high: int, typed: bool, parameter: bool):
        """The declared name of LOW..HIGH as (text, start, end), the index of its parameter group if it declares a
        function (else None), and the end of the declarator before any initializer. TYPED says that a base type was
        already read, as for the second declarator of `int a, b`."""
        tokens = self.tokens
        cut = self.first(low, high, "=")
        name, unknown, index = None, None, low
        while index < cut:
            token = tokens[index]
            if token.text == "(":
                if name:
                    return name, index, cut
                inner = index + 1
                while inner < self.pairs[index] and tokens[inner].text in POINTER_TOKENS | QUALIFIERS:
                    inner += 1
                if inner > index + 1 and inner < self.pairs[index] and self.is_name(tokens[inner]):
                    text, end = self.qualified(inner)
                    return (text, inner, end), None, cut
                index = self.pairs[index] + 1
                continue
            if token.text in OPENERS:
                index = self.pairs[index] + 1
                continue
            if token.kind != "id" and token.text != "~":
                index += 1
                continue
            if token.text in TAG_WORDS:
                typed = True
                tagged = index + 1 < cut and tokens[index + 1].kind == "id"
                index = self.qualified(index + 1)[1] if tagged else index + 1
                continue
            if token.text in self.profile.type_words and token.text not in QUALIFIERS:
                typed = True
                index += 1
                continue
            if token.text in KEYWORDS or token.text in QUALIFIERS:
                index += 1
                continue
            text, end = self.qualified(index)
            if typed:
                name = (text, index, end)
            else:
                typed = True
                if not self.is_type(text):
                    unknown = (text, index, end)
            index = end
        if name is None and unknown and not parameter:
            name = unknown
        return name, None, cut

    def declarators(self, low: int, high: int, parameter: bool = False):
        """Each declarator of LOW..HIGH as (name or None, spelled type, parameter group or None, (start, end, cut)).
        The spelled type leaves out the name, storage words and any { } body: `struct A { int x; } a` spells
        `struct A`. A function's spelled type is its return type."""
        found, base = [], []
        for number, (start, end) in enumerate(self.split(low, high)):
            name, group, cut = self.declarator(start, end, number > 0, parameter)
            stop = cut if group is None else group
            skipped = set(range(name[1], name[2])) if name else set()
            for index in self.depth_zero(start, stop):
                if self.tokens[index].text == "{":
                    skipped |= set(range(index, self.pairs[index] + 1))
            if number == 0:
                base_stop = name[1] if name else stop
                for index in range(start, base_stop):
                    if self.tokens[index].text in POINTER_TOKENS | {"(", "["}:
                        base_stop = index
                        break
                base = [self.tokens[index] for index in range(start, base_stop) if index not in skipped]
            own = [self.tokens[index] for index in range(start, stop) if index not in skipped]
            found.append((name, self.spelled(own if number == 0 else base + own), group, (start, end, cut)))
        return found

    def parameters(self, group: int, names: dict | None = None) -> tuple[tuple, bool]:
        """The spelled parameter types of the group at GROUP and whether it ends with ...; puts each named
        parameter's spelled type in NAMES."""
        types, variadic = [], False
        close = self.pairs[group]
        self.note_tags(group + 1, close)
        for start, end in self.split(group + 1, close):
            words = [token.text for token in self.tokens[start:end]]
            if words == ["..."]:
                variadic = True
                continue
            if not words or words == ["void"]:
                continue
            [(name, spelled, _, _)] = self.declarators(start, end, parameter=True)
            types.append(spelled)
            if names is not None and name:
                names[name[0]] = spelled
        return tuple(types), variadic
