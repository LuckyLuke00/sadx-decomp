"""C text for the repairs in tools/llm.py: the types and declarations on a line of C, the bounds of its brackets,
operands and arguments, and the line with a cast or a byte offset.

Each helper works on text: a line, an expression, a type name or a function's lines. None of them builds, reads the
build output or finds a function in its file. llm.py does that and calls these.
"""

import collections
import functools
import re

import names

LITERAL = re.compile(r"\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'|//.*|/\*.*?\*/")  # a string, a character or a comment
ASSIGN = re.compile(r"(?<![=!<>+\-*/%&|^])=(?!=)")
SIMPLE = re.compile(r"[-&*!~]*[\w.]+(?:->\w+|\.\w+|\[[^\]]*\]|\([^()]*\))*")  # an operand: a cast needs no brackets
TAG_NAME = re.compile(r"(?<!struct )(?<!union )(?<!enum )\b\w+\b")
INTEGER_TYPES = names.SCALAR_SIZES.keys() - {"bool", "float", "double"}
CAST = re.compile(r"\s*(?:[A-Za-z_]\w*\s+)*[A-Za-z_]\w*\s*(?:\*\s*)*")  # the text of a type in parentheses
# A declaration at the start of a statement or parameter: type, `*`s, name, array dimensions.
DECLARATION = re.compile(r"\s*(?:(?:extern|static|register)\s+)*"
                         r"((?:(?:const|volatile|struct|union|enum)\s+)*[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*?)"
                         r"\s*((?:\*\s*(?:const\s+)?)*)\s*([A-Za-z_]\w*)\s*((?:\[[^\]]*\])*)\s*(?:[;,=)]|$)")
NOT_TYPES = {"return", "else", "goto", "case", "delete", "new", "typedef"}  # words that DECLARATION also matches
CALL_WORDS = {"return", "if", "while", "for", "switch", "else", "case"}  # a word before `(` that is not a function name
Pointee = collections.namedtuple("Pointee", "base stars dims")  # a C type: its name, pointer levels, array dimensions


def plain_type(text):
    """The type name in TEXT without `const`, `volatile`, `struct`, `union`, `enum` and `*`."""
    return " ".join(w for w in re.findall(r"\w+", text) if w not in ("const", "volatile", "struct", "union", "enum"))


def is_cast(group):
    """Whether GROUP, the text between parentheses, is a type: a pointer, or a name that starts with a C type word."""
    return bool(CAST.fullmatch(group)) and ("*" in group or group.split()[0] in names.TYPE_WORDS)


def declared_type(statement):
    """(name, Pointee) of the declaration that STATEMENT starts with, or None."""
    m = DECLARATION.match(statement)
    if not m or m.group(1).split()[0] in NOT_TYPES:
        return None
    return m.group(3), Pointee(plain_type(m.group(1)), m.group(2).count("*"), m.group(4).count("["))


def bracket_start(line, close):
    """Index of the bracket that the one at CLOSE closes, or None."""
    depth = 0
    for i in range(close, -1, -1):
        depth += (line[i] in ")]") - (line[i] in "([")
        if depth == 0:
            return i
    return None


def bracket_end(line, start):
    """Index of the bracket that closes the one at START, or None."""
    depth = 0
    for i in range(start, len(line)):
        depth += (line[i] in "([") - (line[i] in ")]")
        if depth == 0:
            return i
    return None


def group_at_end(text):
    """(index of its `(`, the text inside) of the parenthesized group that TEXT ends with, or None."""
    start = bracket_start(text, len(text) - 1) if text.endswith(")") else None
    return None if start is None else (start, text[start + 1:-1])


@functools.cache
def struct_members(types, name):
    """The members of the struct NAME as {owner: {member: Pointee}}: the owner is NAME, or "NAME.#N" for a union or
    struct inside it. A member that is one has that owner as the name of its type."""
    owners, stack = {name: {}}, [name]
    for line in types.blocks[name].split("};", 1)[0].splitlines()[1:]:
        close = re.match(r"\s*\}\s*(\w*)\s*((?:\[[^\]]*\])*);", line)
        if re.match(r"\s*(?:struct|union)\s*\w*\s*\{$", line):
            stack.append(f"{name}.#{len(owners)}")
            owners[stack[-1]] = {}
        elif close:
            inner = stack.pop()
            if close.group(1):
                owners[stack[-1]][close.group(1)] = Pointee(inner, 0, close.group(2).count("["))
            else:
                owners[stack[-1]].update(owners[inner])
        elif declared := declared_type(line):
            member, pointee = declared
            owners[stack[-1]][member] = pointee
    return owners


def member_type(types, owner, member, arrow):
    """The Pointee of OWNER's MEMBER (OWNER is a struct pointer when ARROW, else a struct), or None."""
    top = owner.base.split(".")[0]
    if owner.dims or owner.stars != (1 if arrow else 0) or top not in types.blocks:
        return None
    return struct_members(types, top).get(owner.base, {}).get(member)


def element_type(found):
    """The Pointee of an element of an array or of what a pointer points to, or None."""
    if found.dims:
        return found._replace(dims=found.dims - 1)
    return found._replace(stars=found.stars - 1) if found.stars else None


def follow(found, rest, types):
    """FOUND, a Pointee, after the index and member steps in REST; None when a step does not apply."""
    while found is not None and rest.strip():
        step = re.match(r"\s*(\[|->|\.)\s*", rest)
        end = bracket_end(rest, step.start(1)) if step and step.group(1) == "[" else None
        if not step or step.group(1) == "[" and end is None:
            return None
        if step.group(1) == "[":
            found, rest = element_type(found), rest[end + 1:]
        else:
            m = re.match(r"[A-Za-z_]\w*", rest[step.end():])
            found = m and member_type(types, found, m.group(), step.group(1) == "->")
            rest = rest[step.end() + (m.end() if m else 0):]
    return found


def expression_type(text, scope, types):
    """The Pointee of the C expression TEXT, or None when TEXT is not a cast, a name or a chain of `*`, `&`, `[]`, `.`
    and `->` on one, or the name has no type in SCOPE ({name: Pointee})."""
    text = text.strip()
    if text.startswith("("):
        end = bracket_end(text, 0)
        if end is None:
            return None
        if is_cast(text[1:end]):
            return Pointee(plain_type(text[1:end]), text[1:end].count("*"), 0)
        found, rest = expression_type(text[1:end], scope, types), text[end + 1:]
    elif text[:1] in ("*", "&"):
        inner = expression_type(text[1:], scope, types)
        if inner is None or text[0] == "&" and inner.dims:
            return None
        return element_type(inner) if text[0] == "*" else inner._replace(stars=inner.stars + 1)
    else:
        m = re.match(r"[A-Za-z_]\w*", text)
        found, rest = (scope.get(m.group()), text[m.end():]) if m else (None, "")
    return follow(found, rest, types)


def binary_operand(before):
    """Whether the text BEFORE an operator ends in an operand: the operator then has a left side. A cast ends none."""
    before = before.rstrip()
    group = group_at_end(before)
    return (bool(before) and (before[-1].isalnum() or before[-1] in "_)]") and not before.endswith("return")
            and not (group and is_cast(group[1])))


def opens_call(before):
    """Whether a `(` after the text BEFORE opens the arguments of a call, not a group."""
    before = before.rstrip()
    if before.endswith(")"):
        group = group_at_end(before)
        return group is not None and not is_cast(group[1])
    word = re.search(r"\w+$", before)
    return before.endswith("]") or bool(word) and word.group() not in CALL_WORDS


def operand_start(line, end, prefix=True):
    """Index in LINE where the operand that ends at END starts: a name, call, index or member chain, with its casts and
    `*` and `&` when PREFIX. None when it does not read as one."""
    i = len(line[:end].rstrip())
    while i:
        if line[i - 1] in ")]":
            open_at = bracket_start(line, i - 1)
            if open_at is None:
                return None
            i = open_at
            if line[i] == "(" and not opens_call(line[:i]):
                break
        elif line[i - 1].isalnum() or line[i - 1] == "_":
            while i and (line[i - 1].isalnum() or line[i - 1] == "_"):
                i -= 1
            before = line[:i].rstrip()
            if not before.endswith(("->", ".")):
                break
            i = len(before[:-2 if before.endswith("->") else -1].rstrip())
        else:
            return None
    while prefix:
        before = line[:i].rstrip()
        group = group_at_end(before)
        if before[-1:] in ("*", "&", "!", "~") and not binary_operand(before[:-1]):
            i = len(before) - 1
        elif group and is_cast(group[1]) and not binary_operand(before[:group[0]]):
            i = group[0]
        else:
            break
    return i


def binary_sign(line, i):
    """Whether the `+` or `-` at I adds or subtracts: not `++`, `--`, `+=`, `-=`, `->` or a sign."""
    after = line[i + 1:i + 2]
    if after in ("=", line[i]) or (line[i] == "-" and after == ">") or line[i - 1:i] == line[i]:
        return False
    return binary_operand(line[:i])


def chain_end(line, i):
    """Index where the `+` and `-` terms that go on from the operator at I end: at the first `)`, `,` or operator that
    binds weaker than `+` outside brackets."""
    depth = 0
    for j in range(i, len(line)):
        c = line[j]
        if c in "([":
            depth += 1
        elif c in ")]":
            if depth == 0:
                return len(line[:j].rstrip())
            depth -= 1
        elif depth == 0 and c in ",;?:{}<>=!&|^" and not (c == ">" and line[j - 1] == "-"):
            return len(line[:j].rstrip())
    return len(line.rstrip())


def under_cast(line, start, end):
    """Whether the text from START to END is all that a cast `(type)(...)` holds."""
    before, after = line[:start].rstrip(), line[end:].lstrip()
    group = group_at_end(before[:-1].rstrip()) if before.endswith("(") else None
    return group is not None and after.startswith(")") and is_cast(group[1])


def pointer_kind(operand, spellings, scope, types):
    """The spelling in SPELLINGS ({type name: the type as the compiler wrote it}) of the type that OPERAND points to,
    when it is a pointer to one of them, else None."""
    found = expression_type(operand, scope, types)
    return None if found is None or found.stars != 1 or found.dims else spellings.get(found.base)


def next_byte_fix(line, spellings, scope, types):
    """LINE with `(char *)` on the first pointer to a type in SPELLINGS that a `+`, `-` or `[]` uses, or None. Under a
    cast the offset keeps its type: `*(int *)(p + 4)` becomes `*(int *)((char *)p + 4)`; else the sum is cast back."""
    for i, c in enumerate(line):
        if c in "+-" and binary_sign(line, i):
            start = operand_start(line, i)
            kind = None if start is None else pointer_kind(line[start:i], spellings, scope, types)
            if kind:
                end = chain_end(line, i)
                operand = line[start:i].rstrip()
                cast = f"(char *)({operand})" if operand[0] in "*&(" else f"(char *){operand}"
                terms = cast + line[start + len(operand):end]
                if not under_cast(line, start, end):
                    terms = f"({kind} *)({terms})"
                return line[:start] + terms + line[end:]
        elif c == "[" and binary_operand(line[:i]):
            start = operand_start(line, i, prefix=False)
            kind = None if start is None else pointer_kind(line[start:i], spellings, scope, types)
            end = bracket_end(line, i)
            if kind and end is not None and not line[end + 1:].lstrip().startswith((".", "->")):
                return f"{line[:start]}((char *){line[start:i]}){line[i:]}"
    return None


def type_kind(name):
    """"pointer", "array", "integer" or "other" for a type as the compiler prints it."""
    bare = " ".join(re.sub(r"\b(?:const|volatile)\b", "", name).split())
    if "::*" in bare.replace(" ", "") or bare.endswith("&"):
        return "other"  # a member pointer or a reference: a C-style cast would not be the conversion C makes
    if "*" in bare:
        return "pointer"
    if re.search(r"\[\d*\]$", bare):
        return "array"
    return "integer" if bare in INTEGER_TYPES else "other"


def blank_literals(line):
    """LINE with each string, character and comment as filler of the same length, so a bracket, comma or = in
    them does not count."""
    return LITERAL.sub(lambda m: ("_" if m[0][0] in "\"'" else " ") * len(m[0]), line)


def expression_end(blanked, start):
    """The index in BLANKED, a line from blank_literals, where the expression that starts at START ends: a `,`
    or `;` outside brackets, or the bracket that closes the one around it. None when the line ends first."""
    depth = 0
    for i in range(start, len(blanked)):
        depth += (blanked[i] in "([{") - (blanked[i] in ")]}")
        if depth < 0 or (depth == 0 and blanked[i] in ",;"):
            return i
    return None


def trimmed(blanked, start, end):
    """(START, END) without the blanks at both ends."""
    text = blanked[start:end]
    return start + len(text) - len(text.lstrip()), start + len(text.rstrip())


def value_span(blanked, name):
    """(start, end) of the expression that a C2440 on NAME ('=', 'initializing' or 'return') converts in BLANKED,
    a line from blank_literals. None when the line holds more than one = or return, or the expression goes on in
    the next line."""
    marks = [m.end() for m in (re.finditer(r"\breturn\b", blanked) if name == "return" else ASSIGN.finditer(blanked))]
    end = expression_end(blanked, marks[0]) if len(marks) == 1 else None
    if end is None:
        return None
    start, end = trimmed(blanked, marks[0], end)
    return None if start == end or blanked[start] == "{" else (start, end)


def argument_spans(blanked, start):
    """(start, end) of each argument of the call whose bracket opens just before START in BLANKED, a line from
    blank_literals. None when the call goes on in the next line."""
    spans = []
    while (end := expression_end(blanked, start)) is not None:
        spans.append(trimmed(blanked, start, end))
        if blanked[end] == ")":
            return spans
        if blanked[end] != ",":
            return None
        start = end + 1
    return None


def argument_span(blanked, name, param):
    """(start, end) of argument PARAM (from 1) of the one call to NAME in BLANKED, a line from blank_literals, else
    None."""
    calls = list(re.finditer(rf"\b{re.escape(name)}\s*\(", blanked))
    spans = argument_spans(blanked, calls[0].end()) if len(calls) == 1 else None
    return spans[param - 1] if spans and param <= len(spans) and all(a < b for a, b in spans) else None


def tagged(name, kinds):
    """NAME, a type as the compiler prints it, with struct, union or enum before each tag that KINDS (name: kind)
    holds. A bare tag can be hidden by a function or a variable of its name, and the tag is always right."""
    return TAG_NAME.sub(lambda m: f"{kinds[m[0]]} {m[0]}" if m[0] in kinds else m[0], name)


def cast_text(expression, target):
    """EXPRESSION cast to TARGET, in brackets when it is more than one operand."""
    return f"({target})" + (expression if SIMPLE.fullmatch(expression) else f"({expression})")


def cast_line(line, conversion, kinds):
    """LINE with the cast that CONVERSION names, or None when the spot is more than one place in the line."""
    blanked = blank_literals(line)
    span = (value_span(blanked, conversion.name) if conversion.param is None
            else argument_span(blanked, conversion.name, conversion.param))
    if span is None:
        return None
    return line[:span[0]] + cast_text(line[span[0]:span[1]], tagged(conversion.target.strip(), kinds)) + line[span[1]:]


def continued_lines(func):
    """The indexes of FUNC's lines that continue a statement from the line before, or from an open bracket. The
    compiler names the last line of a statement, so the callee or the = it means can be in an earlier line."""
    continued, depth, ended = set(), 0, True
    for i, line in enumerate(func):
        blanked = blank_literals(line).strip()
        if not blanked or blanked.startswith("#"):
            continue
        if depth > 0 or not ended:
            continued.add(i)
        depth += sum(c in "([" for c in blanked) - sum(c in ")]" for c in blanked)
        ended = blanked[-1] in ";{}:)" or blanked.endswith(("else", "do"))
    return continued
