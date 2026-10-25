"""Search for a rewrite of one function that scores higher, with the score as the only judge.

  python tools/check.py permute FILE 0x00401000 [--tries N] [--minutes M] [--seed S] [--rank score|class]

The small changes: swap two statements that do not depend on each other, flip a comparison or the
operands of a commutative operation, write `x == 0` as `!x` or back, move between `x++`, `x += 1`
and `x = x + 1`, invert an if/else or an else-if/else, split an if on `&&` or join two, turn a for
loop into a while loop or back, drop a local that only holds a copy of another, put a local's value
into the next line that reads it once, change the signedness of a local or a cast, turn an if block
that ends a function, or ends it before its last return, into an early return or back, turn an
if/else-if chain on one operand's constants into a switch or back, write a ternary `c ? a : b` as
`!c ? b : a`, turn an if/else that stores or returns one of two values into a ternary or back, give
an if block that ends in a return, break, continue or goto the rest of its block as an else, or the
next if as an else-if, or take them away, put the rest of a block that ends in a jump under the
negated condition of an `if (c) return A;` before it, or call a function through an old-style cast
with its last arguments dropped, for a call the original made with fewer arguments than the function
takes. When the diff shows a local's stack slot (`[ebp - N]`), it also renames placeholder locals
(`local_*`, Ghidra's `iVar1`): at /Od a scope's locals sit in the order of a hash of their names, so
a new name moves a local to another slot. It leaves other local names alone.

Two guesses change what the code does, so a try that one of them makes counts only when it matches
exactly, and they only go in single changes. When the diff shows a jmp on one side only, it drops
the break between two cases or adds one. When it shows an x87 compare whose mask or jump differs, it
tries each of <, <=, > and >= in a comparison, with and without a `!( )`, on the sides in either
order.

Every other try is the next of the best function's single changes, in a random order, so a fix one
change away is always found; the others make one to three changes at random to the current one. A
new best's changes come before the old best's untried ones, which stay, and a try that scores the
same as the best adds its changes after all the others, so a fix two changes away through a change
that alone scores the same is found too. It builds, scores the function with reccmp and keeps the
best try. A try that scores the same as the current one becomes the current one, so a change that
only pays off with a second one can still be found. It stops at 100%, after N tries or after M
minutes.

The best function goes into FILE when its score is higher than at the start; otherwise, and on an
error or Ctrl+C, FILE is left as it was. build/permute/ADDRESS.c keeps the best try either way.
When only the names of globals or functions differ from the original, no shape can help: the
declarations need work, so it says so and stops.
"""

import collections
import random
import re
import sys
import time

import check
import llm
import osutil
import project
import runner

OUT = project.BUILD / "permute"
Score = collections.namedtuple("Score", "percent exact lines structural")
LVALUE = r"\w+(?:(?:\.|->)\w+|\[[^\[\]]*\])*"
OPERAND = rf"-?{LVALUE}(?:\([^()]*\))?"
# An operand pair counts only between these, so that swapping the two cannot change the precedence.
COMPARISON = re.compile(rf"(\(|&& |\|\| )({OPERAND}) (==|!=|<=|>=|<|>) ({OPERAND})(?=\)| &&| \|\|)")
COMMUTATIVE = re.compile(rf"(\(|(?<![=!<>])= |return |, )({OPERAND}) ([+*&|^]) ({OPERAND})(?=\)|;|,)")
FLIP = {"<": ">", ">": "<", "<=": ">=", ">=": "<=", "==": "==", "!=": "!="}
NEGATE = {"<": ">=", ">=": "<", ">": "<=", "<=": ">", "==": "!=", "!=": "=="}
STATEMENT = re.compile(r"^\t+(?!(?:return|break|continue|goto|case|default|if|else|for|while|do|switch)\b)"
                       r"[^\t{}/].*;$")
DECLARATION = re.compile(r"^\t+(?:(?:const|static|struct|union|enum|unsigned|signed|volatile) )*\w+ \**(\w+)"
                         r"(?:\[[^\]]*\])*(?: = .*)?;$")
ASSIGNED = re.compile(r"^\s*([^=]*?)\s*(?:[-+*/%&|^]|<<|>>)?=(?!=)")
CALL = re.compile(r"\w\s*\(")
MEMORY = re.compile(r"->|\[|\*(?=[\w(])|\.(?=[A-Za-z_])")
INCREMENTS = [rf"^(?P<t>\t+)(?P<x>{LVALUE})(?P<o>[+-])(?P=o);$", rf"^(?P<t>\t+)(?P<o>[+-])(?P=o)(?P<x>{LVALUE});$",
              rf"^(?P<t>\t+)(?P<x>{LVALUE}) (?P<o>[+-])= 1;$", rf"^(?P<t>\t+)(?P<x>{LVALUE}) = (?P=x) (?P<o>[+-]) 1;$"]
LONG_ASSIGN = re.compile(rf"^(\t+)({LVALUE}) = (\2) (\+|-|\*|/|%|&|\||\^|<<|>>) ({OPERAND});$")
SHORT_ASSIGN = re.compile(rf"^(\t+)({LVALUE}) (\+|-|\*|/|%|&|\||\^|<<|>>)= (.+);$")
INTEGER_DECLARATION = re.compile(r"^(\t+)(unsigned )?(int|short|char|long)( \**\w+(?:\[[^\]]*\])*(?: = .*)?;)$")
INTEGER_CAST = re.compile(r"\((unsigned )?(int|short|char|long)\)")
IF_LINE = re.compile(r"^(\t*)if \((.*)\)$")
ELSE_IF_LINE = re.compile(r"^(\t*)else if \((.*)\)$")
CONSTANT = r"-?(?:0x[0-9a-fA-F]+|\d+)|[A-Z_][A-Z0-9_]*"
IF_CONSTANT = re.compile(rf"^(\t*)if \(({OPERAND}) == ({CONSTANT})\)$")
SWITCH_LINE = re.compile(rf"^(\t*)switch \(({OPERAND})\)$")
CONDITION_LINE = re.compile(r"^(\t*(?:if|while|\} while) )\((.*)\)(;?)$")
COPY = re.compile(r"^\t+(\w+) = (\w+);$")
FOR_LINE = re.compile(r"^(\t*)for \(([^;]+); ([^;]+); ([^;]+)\)$")
CALL_STATEMENT = re.compile(r"^(\t+)(\w+)\((.+)\);$")
TERNARY_STATEMENT = re.compile(r"^(\t+(?:.*?[^=!<>]= |return ))(.+);$")
WHILE_LINE = re.compile(r"^(\t*)while \((.*)\)$")
TEMP_ASSIGN = re.compile(r"^(\t+)(\w+) = (.+);$")
SIDE_EFFECT = re.compile(r"(?<![=!<>])=(?!=)|\+\+|--")
BLOCK_LINE = re.compile(r"^\t*(?:\{|\}|else\b|for\b|while\b|do\b|case\b|default\b)")
TERNARY_BRANCH = re.compile(rf"^(\t+)({LVALUE} = |return )([^;]+);$")  # a line that if_to_ternary can join
JUMP_LINE = re.compile(r"^\t+(?:return\b[^;]*|break|continue|goto \w+);$")
LABEL_LINE = re.compile(r"^\t*(?:case\b.*|\w+):$")
CASE_LINE = re.compile(r"^\t*(?:case\b.*|default):$")
# VC++ 2010 /Od puts a scope's locals from low to high address by a hash of the name (16 values), then by declaration
# order. One name for each hash value, the lowest first, so that a rename can put a local in any place.
SLOT_NAMES = ["local_8", "local_13c", "local_80", "local_4", "local_5c", "local_40", "local_cc", "local_10", "local_d0",
              "local_4c", "local_9c", "local_a0", "local_dc", "local_128", "local_8c", "local_c"]
PLACEHOLDER = re.compile(r"local_\w+|[a-z]*Var\d+")
SLOT_DIFF = re.compile(r"^(?:0x[0-9a-f]+)?\s*: [-+].*\[ebp - ", re.M)  # a changed line of reccmp's diff with a local
# A changed x87 compare mask in reccmp's diff, or a changed jump right after one.
COMPARE_DIFF = re.compile(r"^(?:0x[0-9a-f]+)?\s*: (?:[-+]test ah|test ah, .*\n(?:0x[0-9a-f]+)?\s*: [-+]j)", re.M)
JMP_DIFF = re.compile(r"^(?:0x[0-9a-f]+)?\s*: [-+]jmp ", re.M)  # a jmp that only one side has
RELATIONAL = ["<", "<=", ">", ">="]


# The changes. Each takes the body's lines and a random source and returns new lines, or None when it finds no place.
# They only call the source's choice(), so that EveryOption can stand in for it.


def swap_statements(body, rng):
    pairs = [i for i in range(len(body) - 1) if starts_statement(body, i) and STATEMENT.match(body[i])
             and STATEMENT.match(body[i + 1]) and indent(body[i]) == indent(body[i + 1])
             and bool(DECLARATION.match(body[i])) == bool(DECLARATION.match(body[i + 1]))
             and independent(body[i], body[i + 1])]
    if not pairs:
        return None
    i = rng.choice(pairs)
    return body[:i] + [body[i + 1], body[i]] + body[i + 2:]


def flip_comparison(body, rng):
    return replace_match(body, rng, COMPARISON, lambda m: f"{m[1]}{m[4]} {FLIP[m[3]]} {m[2]}")


def swap_operands(body, rng):
    return replace_match(body, rng, COMMUTATIVE, lambda m: f"{m[1]}{m[4]} {m[3]} {m[2]}")


def change_increment(body, rng):
    found = [(i, m) for i, line in enumerate(body) for m in [first_match(INCREMENTS, line)] if m]
    if not found:
        return None
    i, m = rng.choice(found)
    x, o = m["x"], m["o"]
    forms = [f"{x}{o}{o};", f"{o}{o}{x};", f"{x} {o}= 1;", f"{x} = {x} {o} 1;"]
    forms.remove(body[i].strip())
    return body[:i] + [m["t"] + rng.choice(forms)] + body[i + 1:]


def change_assignment(body, rng):
    found = [i for i, line in enumerate(body) if LONG_ASSIGN.match(line) or SHORT_ASSIGN.match(line)]
    if not found:
        return None
    i = rng.choice(found)
    long = LONG_ASSIGN.match(body[i])
    if long:
        line = f"{long[1]}{long[2]} {long[4]}= {long[5]};"
    else:
        short = SHORT_ASSIGN.match(body[i])
        value = short[4] if re.fullmatch(OPERAND, short[4]) else f"({short[4]})"
        line = f"{short[1]}{short[2]} = {short[2]} {short[3]} {value};"
    return body[:i] + [line] + body[i + 1:]


def change_signedness(body, rng):
    found = [i for i, line in enumerate(body) if INTEGER_DECLARATION.match(line)]
    if not found:
        return None
    i = rng.choice(found)
    m = INTEGER_DECLARATION.match(body[i])
    return body[:i] + [f"{m[1]}{'' if m[2] else 'unsigned '}{m[3]}{m[4]}"] + body[i + 1:]


def change_cast(body, rng):
    found = [(i, m) for i, line in enumerate(body) for m in INTEGER_CAST.finditer(line)]
    if not found:
        return None
    i, m = rng.choice(found)
    cast = rng.choice(["", f"({'' if m[1] else 'unsigned '}{m[2]})"])
    return body[:i] + [body[i][:m.start()] + cast + body[i][m.end():]] + body[i + 1:]


def invert_if(body, rng):
    """`if (c) {a} else {b}` becomes `if (!c) {b} else {a}`, and the same for an `else if` with an else."""
    found = []
    for i, line in enumerate(body):
        m = IF_LINE.match(line) or ELSE_IF_LINE.match(line)
        if not m or not opens_block(body, i, m[1]):
            continue
        end = block_end(body, i + 1, m[1])
        if end is not None and body[end + 1:end + 2] == [m[1] + "else"] and opens_block(body, end + 1, m[1]):
            other = block_end(body, end + 2, m[1])
            if other is not None:
                found.append((i, end, other, m))
    if not found:
        return None
    i, end, other, m = rng.choice(found)
    t = m[1]
    keyword = "else if" if m.re is ELSE_IF_LINE else "if"
    swapped = [f"{t}{keyword} ({negate(m[2])})", t + "{", *body[end + 3:other], t + "}", t + "else", t + "{",
               *body[i + 2:end], t + "}"]
    return body[:i] + swapped + body[other + 1:]


def for_to_while(body, rng):
    found = []
    for i, line in enumerate(body):
        m = FOR_LINE.match(line)
        if m and opens_block(body, i, m[1]):
            end = block_end(body, i + 1, m[1])
            if end is not None and not has_continue(body[i + 2:end]):
                found.append((i, end, m))
    if not found:
        return None
    i, end, m = rng.choice(found)
    t = m[1]
    loop = [f"{t}{m[2]};", f"{t}while ({m[3]})", t + "{", *body[i + 2:end], f"{t}\t{m[4]};", t + "}"]
    return body[:i] + loop + body[end + 1:]


def while_to_for(body, rng):
    found = []
    for i, line in enumerate(body[1:], 1):
        m = WHILE_LINE.match(line)
        if not m or not opens_block(body, i, m[1]) or not STATEMENT.match(body[i - 1]) \
                or indent(body[i - 1]) != m[1]:
            continue
        end = block_end(body, i + 1, m[1])
        if end is not None and end - 1 > i + 1 and indent(body[end - 1]) == m[1] + "\t" \
                and STATEMENT.match(body[end - 1]) and not has_continue(body[i + 2:end]):
            found.append((i, end, m))
    if not found:
        return None
    i, end, m = rng.choice(found)
    t = m[1]
    loop = [f"{t}for ({body[i - 1].strip()[:-1]}; {m[2]}; {body[end - 1].strip()[:-1]})", t + "{",
            *body[i + 2:end - 1], t + "}"]
    return body[:i - 1] + loop + body[end + 1:]


def change_zero_test(body, rng):
    found = []
    for i, line in enumerate(body):
        m = CONDITION_LINE.match(line)
        if m:
            parts = split_condition(m[2])
            found += [(i, m, parts, j) for j in range(0, len(parts), 2) if zero_test(parts[j])]
    if not found:
        return None
    i, m, parts, j = rng.choice(found)
    parts = parts[:j] + [zero_test(parts[j])] + parts[j + 1:]
    return body[:i] + [f"{m[1]}({''.join(parts)}){m[3]}"] + body[i + 1:]


def split_if(body, rng):
    found = []
    for i, line in enumerate(body):
        m = IF_LINE.match(line)
        if not m or not opens_block(body, i, m[1]):
            continue
        parts = split_condition(m[2])
        end = block_end(body, i + 1, m[1])
        if len(parts) > 1 and set(parts[1::2]) == {" && "} and end is not None \
                and body[end + 1:end + 2] != [m[1] + "else"]:
            found.append((i, end, m, parts))
    if not found:
        return None
    i, end, m, parts = rng.choice(found)
    t = m[1]
    cut = 2 * rng.choice(range(1, (len(parts) + 1) // 2))  # the index in PARTS of the first inner condition
    nested = [f"{t}if ({''.join(parts[:cut - 1])})", t + "{", f"{t}\tif ({''.join(parts[cut:])})", t + "\t{",
              *["\t" + b if b else b for b in body[i + 2:end]], t + "\t}", t + "}"]
    return body[:i] + nested + body[end + 1:]


def join_if(body, rng):
    found = []
    for i, line in enumerate(body):
        m = IF_LINE.match(line)
        if not m or not opens_block(body, i, m[1]):
            continue
        t = m[1]
        inner = IF_LINE.match(body[i + 2]) if i + 2 < len(body) else None
        if not inner or inner[1] != t + "\t" or not opens_block(body, i + 2, inner[1]):
            continue
        inner_end = block_end(body, i + 3, inner[1])
        if inner_end is not None and body[inner_end + 1:inner_end + 2] == [t + "}"] \
                and body[inner_end + 2:inner_end + 3] != [t + "else"]:
            found.append((i, inner_end, m, inner))
    if not found:
        return None
    i, inner_end, m, inner = rng.choice(found)
    t = m[1]
    joined = [f"{t}if ({bracketed(m[2])} && {bracketed(inner[2])})", t + "{",
              *[b[1:] if b.startswith("\t") else b for b in body[i + 4:inner_end]], t + "}"]
    return body[:i] + joined + body[inner_end + 2:]


def inline_copy(body, rng):
    found = []
    for i, line in enumerate(body):
        m = COPY.match(line)
        if not m or m[1] == m[2]:
            continue
        declaration = next((j for j in range(i) if re.fullmatch(rf"\t+[\w ]+ {m[1]};", body[j])), None)
        used_before = any(re.search(rf"\b{m[1]}\b", b) for j, b in enumerate(body[:i]) if j != declaration)
        if declaration is not None and not used_before and not assigned(m[1], body[i + 1:]) \
                and not assigned(m[2], body[i + 1:]):
            found.append((i, declaration, m))
    if not found:
        return None
    i, declaration, m = rng.choice(found)
    rest = [re.sub(rf"\b{m[1]}\b", m[2], b) for b in body[i + 1:]]
    return body[:declaration] + body[declaration + 1:i] + rest


def inline_temp(body, rng):
    """`t = e;` and the next line, which reads the local t once, become that line with e in place of t. At /Od a
    float expression passed straight to a call goes through the compiler's own temporary, which a local cannot
    copy. Only when each call on the line takes t in its brackets, each later read of t comes after a new
    `t = ...` whose block is still open, and, in a loop, nothing reads t before. The declaration goes when nothing
    else uses t."""
    if any(re.search(r"\bgoto\b", line) for line in body):
        return None
    found = []
    for i in range(len(body) - 1):
        m = TEMP_ASSIGN.match(body[i])
        use = body[i + 1]
        if not m or SIDE_EFFECT.search(m[3]) or len(split_arguments(m[3]) or []) != 1 or indent(use) != m[1] \
                or BLOCK_LINE.match(use) or re.search(r"\+\+|--", use):
            continue
        name, value = m[2], m[3]
        declaration = local_declaration(body[:i], name)
        spots = reads(name, use)
        read_before = any(reads(name, line) for k, line in enumerate(body[:i]) if k != declaration)
        if declaration is None or reads(name, value) or len(spots) != 1 or address_taken(name, body) \
                or read_before and in_loop(body, i) or not calls_take(use, spots[0].start()) \
                or not dead_after(name, body[i + 2:]):
            continue
        spot = spots[0]
        if not (re.fullmatch(OPERAND, value) or whole_operand(use, spot.start(), spot.end())):
            value = f"({value})"
        new = body[:i] + [use[:spot.start()] + value + use[spot.end():]] + body[i + 2:]
        if not any(re.search(rf"\b{name}\b", line) for k, line in enumerate(new) if k != declaration) \
                and " = " not in new[declaration]:
            new = new[:declaration] + new[declaration + 1:]
        found.append(new)
    return rng.choice(found) if found else None


def if_to_ternary(body, rng):
    """`if (c) {x = a;} else {x = b;}` becomes `x = c ? a : b;`, and two returns become `return c ? a : b;`."""
    found = []
    for i, line in enumerate(body):
        m = IF_LINE.match(line)
        if not m or " ? " in m[2]:
            continue
        t = m[1]
        shape = [t + "{", None, t + "}", t + "else", t + "{", None, t + "}"]  # None: the one line of a branch
        block = body[i + 1:i + 8]
        if len(block) < len(shape) or any(want not in (None, got) for want, got in zip(shape, block)):
            continue
        first, second = TERNARY_BRANCH.match(block[1]), TERNARY_BRANCH.match(block[5])
        if first and second and first[1] == second[1] == t + "\t" and first[2] == second[2] \
                and not any(" ? " in part or SIDE_EFFECT.search(part) for part in (first[3], second[3])):
            found.append(body[:i] + [f"{t}{first[2]}{m[2]} ? {first[3]} : {second[3]};"] + body[i + 8:])
    return rng.choice(found) if found else None


def ternary_to_if(body, rng):
    """`x = c ? a : b;` becomes `if (c) {x = a;} else {x = b;}`, and `return c ? a : b;` two returns."""
    found = []
    for i, line in enumerate(body):
        m = TERNARY_BRANCH.match(line)
        parts = split_ternary(m[3]) if m else None
        if not parts or any(SIDE_EFFECT.search(part) for part in parts):
            continue
        t, head = m[1], m[2]
        condition, first, second = parts
        found.append(body[:i] + [f"{t}if ({condition})", t + "{", f"{t}\t{head}{first};", t + "}", t + "else",
                                 t + "{", f"{t}\t{head}{second};", t + "}"] + body[i + 1:])
    return rng.choice(found) if found else None


def else_tail(body, rng):
    """An if block with no else that ends in a jump takes the rest of its own block as an else, or the if right after
    it as an else-if. The code does the same: /Od only adds a jump at the end of the block, over the else."""
    found = []
    for i in range(len(body)):
        t, end = jump_block(body, i) or (None, None)
        if end is None or body[end + 1:end + 2] and body[end + 1].startswith(t + "else"):
            continue
        if body[end + 1:end + 2] and body[end + 1].startswith(t + "if ("):
            found.append(body[:end + 1] + [t + "else " + body[end + 1][len(t):]] + body[end + 2:])
        close = next((j for j in range(end + 1, len(body)) if body[j] and len(indent(body[j])) < len(t)), len(body))
        rest = body[end + 1:close]
        if rest and not any(LABEL_LINE.match(x) or declares(x, t) for x in rest):
            found.append(body[:end + 1] + [t + "else", t + "{"] + ["\t" + x if x else x for x in rest] + [t + "}"]
                         + body[close:])
    return rng.choice(found) if found else None


def drop_else(body, rng):
    """The other way of else_tail: an if block that ends in a jump loses the else after it, which lets go of its
    block, or its else-if becomes an if."""
    found = []
    for i in range(len(body)):
        t, end = jump_block(body, i) or (None, None)
        if end is None:
            continue
        after = body[end + 1] if end + 1 < len(body) else ""
        if after.startswith(t + "else if ("):
            found.append(body[:end + 1] + [t + after[len(t) + len("else "):]] + body[end + 2:])
        elif after == t + "else" and opens_block(body, end + 1, t):
            close = block_end(body, end + 2, t)
            inner = body[end + 3:close] if close is not None else []
            if inner and not any(declares(x, t + "\t") for x in inner):
                found.append(body[:end + 1] + [x[1:] if x else x for x in inner] + body[close + 1:])
    return rng.choice(found) if found else None


def nest_return(body, rng):
    """`if (c) {return A;}`, or any other jump, and then the rest of its block, when that rest ends in a jump of its
    own, becomes `if (!c) {the rest} return A;`. The code does the same: /Od jumps over the rest instead of out."""
    found = []
    for i, line in enumerate(body):
        m = IF_LINE.match(line)
        if not m:
            continue
        t = m[1]
        if body[i + 1:i + 2] == [t + "{"] and body[i + 3:i + 4] == [t + "}"]:
            exit_line, after = body[i + 2], i + 4
        elif body[i + 1:i + 2] and indent(body[i + 1]) == t + "\t":
            exit_line, after = body[i + 1], i + 2
        else:
            continue
        if not JUMP_LINE.match(exit_line) or indent(exit_line) != t + "\t" \
                or body[after:after + 1] and body[after].startswith(t + "else"):
            continue
        close = next((j for j in range(after, len(body)) if body[j] and len(indent(body[j])) < len(t)), len(body))
        rest = body[after:close]
        if rest and JUMP_LINE.match(rest[-1]) and indent(rest[-1]) == t \
                and not any(LABEL_LINE.match(x) or declares(x, t) for x in rest):
            found.append(body[:i] + [f"{t}if ({negate(m[2])})", t + "{"] + ["\t" + x if x else x for x in rest]
                         + [t + "}", exit_line[1:]] + body[close:])
    return rng.choice(found) if found else None


def fall_through(body, rng):
    """A case that ends in a break runs on into the next case instead, or the other way. For a function whose diff
    shows a jmp on one side only (JMP_DIFF), since a break is a jmp; it changes what the code does, so only an exact
    match can say which one the original has."""
    found = []
    for i in range(1, len(body)):
        if not CASE_LINE.match(body[i]):
            continue
        t = indent(body[i]) + "\t"
        if body[i - 1] == t + "break;":
            found.append(body[:i - 1] + body[i:])
        elif indent(body[i - 1]) == t and not JUMP_LINE.match(body[i - 1]):
            found.append(body[:i] + [t + "break;"] + body[i:])
    return rng.choice(found) if found else None


def change_comparison(body, rng):
    """A comparison in an if or while takes another of <, <=, >, >=, with or without a `!( )` around it, on the
    sides in either order. For a function whose diff shows an x87 compare that differs (COMPARE_DIFF): there the
    operator, the order of the sides and the `!` pick the loads, the mask and the jump, and only an exact match can
    say which one the original has."""
    found = []
    for i, line in enumerate(body):
        m = CONDITION_LINE.match(line)
        parts = split_condition(m[2]) if m else []
        for j in range(0, len(parts), 2):
            found += [body[:i] + [f"{m[1]}({''.join(parts[:j] + [form] + parts[j + 1:])}){m[3]}"] + body[i + 1:]
                      for form in comparison_forms(parts[j])]
    return rng.choice(found) if found else None


def jump_block(body, i):
    """(the tabs, the closing line) when line I is an if, not an else-if, whose block ends in a return, break, continue
    or goto of its own, so that control never reaches the end of the block; else None."""
    m = IF_LINE.match(body[i])
    if not m or not opens_block(body, i, m[1]):
        return None
    end = block_end(body, i + 1, m[1])
    if end is None or not JUMP_LINE.match(body[end - 1]) or indent(body[end - 1]) != m[1] + "\t":
        return None
    return m[1], end


def declares(line, tabs):
    """Whether LINE declares a local at the depth TABS."""
    return indent(line) == tabs and bool(DECLARATION.match(line)) and not JUMP_LINE.match(line)


def early_return(body, rng):
    """An if block that ends a function, or ends it before its last `return V;`, becomes `if (!c) return;` or
    `if (!c) return V;` and the block's lines, or the other way."""
    tail = [line for line in body[-1:] if re.fullmatch(r"\treturn [^;]+;", line)]
    if not tail and any(re.match(r"\t+return [^;]", line) for line in body):
        return None
    exit_line = "\t" + (tail[0] if tail else "\treturn;")
    end = len(body) - len(tail)
    found = []
    for i, line in enumerate(body[:end]):
        m = IF_LINE.match(line)
        if not m or m[1] != "\t":
            continue
        if opens_block(body, i, "\t") and block_end(body, i + 1, "\t") == end - 1:
            found.append(body[:i] + [f"\tif ({negate(m[2])})", exit_line] + [x[1:] for x in body[i + 2:end - 1]]
                         + tail)
        for exit_lines in ([exit_line], ["\t{", exit_line, "\t}"]):
            rest = i + 1 + len(exit_lines)
            if body[i + 1:rest] == exit_lines and rest < end:
                found.append(body[:i] + [f"\tif ({negate(m[2])})", "\t{"]
                             + ["\t" + x if x else x for x in body[rest:end]] + ["\t}"] + tail)
    return rng.choice(found) if found else None


def if_to_switch(body, rng):
    """An if/else-if chain that tests one operand against a constant in each if becomes a switch with a case for each
    test and a default for a last else, or the other way. When a local only holds the operand for the chain, as a
    decompiler shows a switch's temporary, the switch can also test what the local held and drop it. At /Od a switch
    stores its operand in a temporary first, and its tests compare that one by one."""
    found = []
    for i, line in enumerate(body):
        chain = if_chain(body, i)
        if chain and not any(re.fullmatch(r"\t*break;", x) for _, block in chain.cases for x in block):
            t, x = chain.tabs, chain.operand
            found.append(body[:i] + switch_lines(t, x, chain.cases) + body[chain.last + 1:])
            held = re.fullmatch(rf"{t}{re.escape(x)} = (.+);", body[i - 1]) if i else None
            declared = [j for j, b in enumerate(body) if re.fullmatch(rf"\t+[\w ]+ \**{re.escape(x)};", b)]
            uses = {j for j, b in enumerate(body) if re.search(rf"\b{re.escape(x)}\b", b)}
            if held and declared and declared[0] < i - 1 and uses == {declared[0], i - 1, *chain.tests}:
                d = declared[0]
                between = body[d + 1:i - 1]
                if d == 0 and between[:1] == [""]:  # the local was the only declaration: drop the blank line after it
                    between = between[1:]
                found.append(body[:d] + between + switch_lines(t, held[1], chain.cases) + body[chain.last + 1:])
        m = SWITCH_LINE.match(line)
        if m and opens_block(body, i, m[1]):
            t = m[1]
            end = block_end(body, i + 1, t)
            cases = switch_cases(body[i + 2:end], t) if end is not None else None
            if cases:
                found.append(body[:i] + chain_lines(t, m[2], cases) + body[end + 1:])
    return rng.choice(found) if found else None


Chain = collections.namedtuple("Chain", "tabs operand cases tests last")


def if_chain(body, i):
    """The if/else-if chain that starts at line I and tests one operand against a constant in each if, as a Chain:
    CASES are (constant, block lines) with None for a last else, TESTS the lines of the ifs, LAST the closing line.
    None when line I starts no such chain, or the chain goes on with an else that tests something else."""
    m = IF_CONSTANT.match(body[i])
    if not m or not opens_block(body, i, m[1]):
        return None
    t, x, constant, at, cases = m[1], m[2], m[3], i, []
    while True:
        end = block_end(body, at + 1, t)
        if end is None:
            return None
        cases.append((constant, body[at + 2:end]))
        tests = [i] + [j for j in range(i + 1, end) if body[j].startswith(t + "else if (")]
        after = body[end + 1] if end + 1 < len(body) else ""
        if after == t + "else" and opens_block(body, end + 1, t):
            last = block_end(body, end + 2, t)
            return None if last is None else Chain(t, x, cases + [(None, body[end + 3:last])], tests, last)
        more = re.fullmatch(rf"{t}else if \({re.escape(x)} == ({CONSTANT})\)", after)
        if not more or not opens_block(body, end + 1, t):
            return None if after.startswith(t + "else") else Chain(t, x, cases, tests, end)
        constant, at = more[1], end + 1


def switch_lines(t, operand, cases):
    lines = [f"{t}switch ({operand})", t + "{"]
    for constant, block in cases:
        lines += [t + "default:" if constant is None else f"{t}case {constant}:", *block, t + "\tbreak;"]
    return lines + [t + "}"]


def switch_cases(inner, t):
    """The (constant, lines) cases of a switch's body, with None for a default, when each case ends in a break,
    holds no other break of the switch and the default comes last; else None."""
    starts = [j for j, x in enumerate(inner) if re.match(rf"{t}(?:case |default:)", x)]
    if not starts or starts[0] != 0:
        return None
    cases = []
    for k, start in enumerate(starts):
        lines = inner[start + 1:starts[k + 1] if k + 1 < len(starts) else len(inner)]
        label = re.fullmatch(rf"{t}case ({CONSTANT}):", inner[start])
        default = inner[start] == t + "default:" and k + 1 == len(starts)
        if not (label or default) or lines[-1:] != [t + "\tbreak;"] or t + "\tbreak;" in lines[:-1]:
            return None
        cases.append((label[1] if label else None, lines[:-1]))
    return cases if cases[0][0] is not None else None


def chain_lines(t, operand, cases):
    lines = []
    for n, (constant, block) in enumerate(cases):
        test = t + "else" if constant is None else f"{t}{'else ' if n else ''}if ({operand} == {constant})"
        lines += [test, t + "{", *block, t + "}"]
    return lines


def drop_arguments(body, rng):
    found = [(i, m, args) for i, line in enumerate(body) if STATEMENT.match(line)
             for m in [CALL_STATEMENT.match(line)] if m for args in [split_arguments(m[3])] if args]
    if not found:
        return None
    i, m, args = rng.choice(found)
    kept = args[:rng.choice(range(len(args)))]
    return body[:i] + [f"{m[1]}((void (*)()){m[2]})({', '.join(kept)});"] + body[i + 1:]


def flip_ternary(body, rng):
    """`c ? a : b` becomes `!c ? b : a`: the compiler tests the condition the way it is written."""
    found = []
    for i, line in enumerate(body):
        spans = [(start + 1, end) for start, end in bracket_pairs(line)]
        m = TERNARY_STATEMENT.match(line)
        if m:
            spans.append((m.end(1), len(line) - 1))
        found += [(i, start, end, parts) for start, end in spans for parts in [split_ternary(line[start:end])] if parts]
    if not found:
        return None
    i, start, end, (condition, first, second) = rng.choice(found)
    line = body[i]
    return body[:i] + [f"{line[:start]}{negate(condition)} ? {second} : {first}{line[end:]}"] + body[i + 1:]


def rename_local(body, rng):
    """A placeholder local takes the SLOT_NAMES name of another hash value, which moves it to another stack slot."""
    found = dict.fromkeys(m[1] for line in body if "static " not in line for m in [DECLARATION.match(line)]
                          if m and PLACEHOLDER.fullmatch(m[1]))
    used = names("\n".join(body))
    free = [name for name in SLOT_NAMES if name not in used]
    if not found or not free:
        return None
    old, new = rng.choice(list(found)), rng.choice(free)
    return [re.sub(rf"(?<!\.)(?<!->)\b{old}\b", new, line) for line in body]


CHANGES = [swap_statements, flip_comparison, swap_operands, change_zero_test, change_increment, change_assignment,
           change_signedness, change_cast, invert_if, split_if, join_if, for_to_while, while_to_for, inline_copy,
           early_return, if_to_switch, drop_arguments, flip_ternary, inline_temp, if_to_ternary, ternary_to_if,
           else_tail, drop_else, nest_return]
GATED = [(rename_local, SLOT_DIFF)]  # each change only when the diff shows its sign
# Changes that alter what the code does, each only when the diff shows its sign. A try one of them makes counts
# only when it matches exactly: then the original does the same.
GUESSES = [(fall_through, JMP_DIFF), (change_comparison, COMPARE_DIFF)]


def indent(line):
    return line[:len(line) - len(line.lstrip("\t"))]


def starts_statement(body, i):
    return i == 0 or body[i - 1].rstrip().endswith((";", "{", "}", ":"))


def names(statement):
    return set(re.findall(r"[A-Za-z_]\w*", statement))


def target(statement):
    """The part of a statement that it stores to: left of its assignment, or all of it."""
    m = ASSIGNED.match(statement)
    return m[1] if m else statement


def writes(statement):
    """The variable a statement assigns, declares or steps with ++ or --: the last name of its target."""
    if not ASSIGNED.match(statement) and not re.search(r"\+\+|--", statement):
        return set()
    found = re.findall(r"[A-Za-z_]\w*", target(statement))
    return set(found[-1:])


def independent(a, b):
    """Whether A and B can trade places: neither uses the variable the other writes, and neither stores
    through a pointer or calls a function while the other one calls or touches memory."""
    if writes(a) & names(b) or writes(b) & names(a):
        return False
    for one, other in ((a, b), (b, a)):
        if (CALL.search(one) or MEMORY.search(target(one))) and (CALL.search(other) or MEMORY.search(other)):
            return False
    return True


def assigned(name, lines):
    """Whether LINES assign NAME, step it with ++ or --, or take its address."""
    pattern = rf"\b{name}\s*(?:[-+*/%&|^]|<<|>>)?=(?!=)|\b{name}\s*(?:\+\+|--)|(?:\+\+|--|&)\s*{name}\b"
    return any(re.search(pattern, line) for line in lines)


def local_declaration(lines, name):
    """The index in LINES of the line that declares NAME as a local that is not static, or None."""
    return next((i for i, line in enumerate(lines) for m in [DECLARATION.match(line)]
                 if m and m[1] == name and "static " not in line), None)


def reads(name, line):
    """The places in LINE that read the variable NAME: each use but a field of that name and the left side of
    `NAME = ...`."""
    return list(re.finditer(rf"(?<!\.)(?<!->)\b{name}\b(?!\s*=(?!=))", line))


def address_taken(name, lines):
    return any(re.search(rf"(?<![&\w)\]])&\s*{name}\b", line) for line in lines)


def calls_take(line, place):
    """Whether each call in LINE has PLACE inside its brackets, so that it runs after what is at PLACE."""
    closing = dict(bracket_pairs(line))
    return all(m.end() - 1 < place < closing.get(m.end() - 1, -1) for m in CALL.finditer(line))


def dead_after(name, lines):
    """Whether LINES, which come after a store to NAME, never read that value: each read comes after a new
    `NAME = ...` whose block is still open, and there is no `++` or `--` of NAME without one."""
    covered = None  # the indent of the store that hides the old value, while its block is open
    for line in lines:
        depth = len(indent(line))
        if covered is not None and depth < covered:
            covered = None
        stepped = re.search(rf"\b{name}\s*(?:\+\+|--)|(?:\+\+|--)\s*{name}\b", line)
        if re.match(rf"\t+{name} = ", line) and not reads(name, line) and not stepped:
            covered = depth if covered is None else min(covered, depth)
        elif (reads(name, line) or stepped) and covered is None:
            return False
    return True


def in_loop(body, i):
    """Whether line I of BODY is inside a for, while or do: the header of a block around it is one."""
    depth = len(indent(body[i]))
    for line in reversed(body[:i]):
        if len(indent(line)) < depth and line.strip() != "{":
            if re.match(r"\t*(?:for|while|do)\b", line):
                return True
            depth = len(indent(line))
    return False


def whole_operand(line, start, end):
    """Whether LINE[START:END] is a whole argument, a whole right side or a whole returned value, so that what
    goes there needs no brackets."""
    before, after = line[:start].rstrip(), line[end:].lstrip()
    opened = before.endswith(("(", ",")) or re.search(r"(?<![=!<>])=$|\breturn$", before)
    return bool(opened) and after.startswith((")", ",", ";"))


def split_condition(condition):
    """CONDITION cut at each && and || outside brackets: the parts, with the operators between them."""
    parts, depth, start = [], 0, 0
    for i, char in enumerate(condition):
        depth += (char == "(") - (char == ")")
        if depth == 0 and condition.startswith((" && ", " || "), i):
            parts += [condition[start:i], condition[i:i + 4]]
            start = i + 4
    return parts + [condition[start:]]


def comparison_forms(part):
    """The other ways to write PART when it is one comparison of <, <=, > or >=, maybe inside `!( )`: each of the
    four operators, with and without the `!( )`, on the sides in either order. None when PART is something else."""
    inner = part[2:-1] if part.startswith("!(") and (1, len(part) - 1) in bracket_pairs(part) else part
    sides = split_comparison(inner)
    if sides is None:
        return []
    left, _, right = sides
    plain = [f"{a} {o} {b}" for a, b in [(left, right), (right, left)] for o in RELATIONAL]
    return [form for form in plain + [f"!({form})" for form in plain] if form != part]


def split_comparison(text):
    """(left, operator, right) when TEXT is one comparison of <, <=, > or >= outside brackets, with nothing there
    that binds less tightly; else None."""
    flat = outside_brackets(text)
    found = list(re.finditer(r" (<=|>=|<|>) ", flat))
    if len(found) != 1 or re.search(r"\?|[^=!<>]=[^=]|==|!=| & | \| | \^ |,", flat):
        return None
    m = found[0]
    return text[:m.start()], m[1], text[m.end():]


def outside_brackets(text):
    """TEXT with each character inside round or square brackets replaced by _, so a search sees only the top."""
    out, depth = [], 0
    for char in text:
        depth -= char in ")]"
        out.append(char if depth == 0 else "_")
        depth += char in "(["
    return "".join(out)


def split_arguments(text):
    """TEXT, the inside of a call's brackets, cut at each comma outside brackets. None when a bracket
    closes the call early, as in `f(a) + g(b)`."""
    parts, depth, start = [], 0, 0
    for i, char in enumerate(text):
        depth += (char == "(") - (char == ")")
        if depth < 0:
            return None
        if depth == 0 and char == ",":
            parts.append(text[start:i].strip())
            start = i + 1
    return parts + [text[start:].strip()]


def bracket_pairs(line):
    """The (open, close) indexes of each pair of round brackets in LINE."""
    pairs, opened = [], []
    for i, char in enumerate(line):
        if char == "(":
            opened.append(i)
        elif char == ")" and opened:
            pairs.append((opened.pop(), i))
    return pairs


def split_ternary(text):
    """TEXT as (condition, first, second) when it is one `c ? a : b` outside brackets, else None."""
    marks, depth = [], 0
    for i, char in enumerate(text):
        depth += (char == "(") - (char == ")")
        if depth == 0 and text.startswith((" ? ", " : "), i):
            marks.append(i)
    if len(marks) != 2 or text[marks[0] + 1] != "?" or text[marks[1] + 1] != ":":
        return None
    return text[:marks[0]], text[marks[0] + 3:marks[1]], text[marks[1] + 3:]


def zero_test(part):
    """PART written the other way: `x == 0` as `!x`, `x != 0` as `x`, and back. None for other parts."""
    m = re.fullmatch(rf"({OPERAND}) (==|!=) 0", part)
    if m:
        return ("!" if m[2] == "==" else "") + m[1]
    m = re.fullmatch(rf"!({OPERAND})", part)
    if m:
        return f"{m[1]} == 0"
    return f"{part} != 0" if re.fullmatch(OPERAND, part) else None


def bracketed(condition):
    return f"({condition})" if " || " in condition or "?" in condition else condition


def has_continue(lines):
    return any(re.search(r"\bcontinue\b", line) for line in lines)


def first_match(patterns, line):
    return next((m for m in (re.match(p, line) for p in patterns) if m), None)


def replace_match(body, rng, pattern, rewrite):
    found = [(i, m) for i, line in enumerate(body) for m in pattern.finditer(line)]
    if not found:
        return None
    i, m = rng.choice(found)
    return body[:i] + [body[i][:m.start()] + rewrite(m) + body[i][m.end():]] + body[i + 1:]


def opens_block(body, i, tabs):
    return body[i + 1:i + 2] == [tabs + "{"]


def block_end(body, open_line, tabs):
    """The line that closes the block opened at OPEN_LINE: the first one that is TABS and "}"."""
    return next((j for j in range(open_line + 1, len(body)) if body[j] == tabs + "}"), None)


def negate(condition):
    m = re.fullmatch(rf"({OPERAND}) (==|!=|<=|>=|<|>) ({OPERAND})", condition)
    if m:
        return f"{m[1]} {NEGATE[m[2]]} {m[3]}"
    m = re.fullmatch(rf"!({OPERAND})", condition)
    if m:
        return m[1]
    return "!" + condition if re.fullmatch(OPERAND, condition) else f"!({condition})"


class EveryOption:
    """Stands in for random.Random in a change. Run the change again while next() is true: the runs make each
    sequence of choices the change can make once."""

    def __init__(self):
        self.path, self.depth = [], 0  # [option taken, options] for each choice() of a run

    def choice(self, options):
        if self.depth == len(self.path):
            self.path.append([0, len(options)])
        taken = self.path[self.depth][0]
        self.depth += 1
        return options[taken]

    def next(self):
        self.depth = 0
        while self.path and self.path[-1][0] + 1 == self.path[-1][1]:
            self.path.pop()
        if self.path:
            self.path[-1][0] += 1
        return bool(self.path)


def neighbors(body, changes):
    """Every body that one of CHANGES makes from BODY."""
    found = []
    for change in changes:
        options = EveryOption()
        while True:
            new = change(body, options)
            if new is not None:
                found.append(new)
            if not options.next():
                break
    return found


def mutate(body, rng, changes):
    """BODY changed by one to three of CHANGES, or None when none applies."""
    changed = None
    for _ in range(rng.choice([1, 1, 1, 2, 2, 3])):
        for change in rng.sample(changes, len(changes)):
            new = change(changed or body, rng)
            if new is not None:
                changed = new
                break
    return changed


# Building, scoring and the search.


def score(address):
    """The function's Score in the last build, and reccmp's diff."""
    out, _ = runner.reccmp("--target", project.game_config().target, "--verbose", hex(address), "--no-color",
                           cwd=project.BUILD)
    if re.search(r" 100% match\.", out):
        return Score(100.0, True, 0, 0), out
    changed = llm.DIFF_LINE.findall(out)
    if " 100% effective match" in out:
        return Score(100.0, False, len(changed), structural_lines(changed)), out
    m = re.search(r"is only (\d+(?:\.\d+)?)% similar", out)
    if m is None:
        sys.exit(f"reccmp gave no score for {hex(address)}:\n{out[-2000:]}")
    return Score(float(m[1]), False, len(changed), structural_lines(changed)), out


def structural_lines(changed):
    """The lines of CHANGED, the (sign, text) of each changed line of a reccmp diff, whose mnemonic the other side
    lacks: an instruction too many or too few. The other changed lines differ only in their operands, such as a
    register or a stack slot."""
    removed, added = collections.Counter(), collections.Counter()
    for sign, text in changed:
        words = text.split()
        (removed if sign == "-" else added)[words[0] if words else ""] += 1
    return sum((removed - added).values()) + sum((added - removed).values())


def rank(result):
    return result.percent, result.exact, -result.lines


def rank_by_class(result):
    """Like rank, but at the same percent the try with fewer structural lines wins, even with more changed lines."""
    return result.percent, result.exact, -result.structural, -result.lines


def describe(result):
    if result.exact:
        return "100% match"
    kind = "effective match" if result.percent >= 100 else "similar"
    return f"{result.percent:.2f}% {kind}, {result.lines} differing lines"


def try_function(path, lines, span, function, crlf, address):
    """Build the file with FUNCTION in SPAN and score it: (Score, diff), or None when it does not build."""
    llm.write_source(path, "\n".join(lines[:span[0]] + function + lines[span[1] + 1:]) + "\n", crlf)
    worked, _ = osutil.caught(check.build)
    return score(address) if worked else None


def fresh_change(body, seen, rng, changes):
    """A change of BODY not tried before, or None when 50 draws find none."""
    for _ in range(50):
        new = mutate(body, rng, changes)
        if new is not None and "\n".join(new) not in seen:
            seen.add("\n".join(new))
            return new
    return None


def shuffled_neighbors(body, changes, guesses, rng, guessed):
    """BODY's single changes of CHANGES and GUESSES, in a random order. The ones only a guess makes go into GUESSED."""
    found = neighbors(body, changes)
    safe = {"\n".join(new) for new in found}
    risky = [new for new in neighbors(body, guesses) if "\n".join(new) not in safe]
    guessed.difference_update(safe)
    guessed.update("\n".join(new) for new in risky)
    found += risky
    rng.shuffle(found)
    return found


def unseen(bodies, seen):
    """The last of BODIES not tried before, taken off the list, or None when none is left."""
    while bodies:
        new = bodies.pop()
        if "\n".join(new) not in seen:
            seen.add("\n".join(new))
            return new
    return None


def search(build_and_score, start, body, tries, minutes, rng, changes, guesses, rank_key):
    """Climb from BODY with CHANGES: (best Score, best body, tries made). Every other try is the next of the best
    body's single changes, in a random order, so that a fix one change away is always found; the others change the
    current body at random. A new best's changes go before the old best's untried ones, which stay, and a try that
    scores the same as the best adds its changes after all the others. After 40 tries with no new best it goes back
    to the best. GUESSES, changes that alter what the code does, only go in single changes, and a try that only
    they make counts only when it matches exactly."""
    best = current = (start, body)
    seen = {"\n".join(body)}
    guessed = set()
    sweep = shuffled_neighbors(body, changes, guesses, rng, guessed)
    deadline = time.time() + minutes * 60 if minutes else None
    tried = stale = 0
    while tried < tries and not best[0].exact and (deadline is None or time.time() < deadline):
        new = unseen(sweep, seen) if tried % 2 == 0 else None
        new = new or fresh_change(current[1], seen, rng, changes) or unseen(sweep, seen)
        if new is None:
            print("no new change to try")
            break
        tried += 1
        stale += 1
        result = build_and_score(new)
        if result is not None and "\n".join(new) in guessed and not result[0].exact:
            result = None
        if result is not None and rank_key(result[0]) > rank_key(best[0]):
            print(f"try {tried}: {describe(result[0])}", flush=True)
            best = current = (result[0], new)
            sweep += shuffled_neighbors(new, changes, guesses, rng, guessed)  # unseen() takes from the end
            stale = 0
        elif result is not None and rank_key(result[0]) >= rank_key(current[0]):
            current = (result[0], new)
            if rank_key(result[0]) == rank_key(best[0]):
                sweep[:0] = shuffled_neighbors(new, changes, guesses, rng, guessed)
        if stale and stale % 40 == 0:
            current = best
    return best[0], best[1], tried


def permute(path, address, tries, minutes, seed, rank_key):
    """Search for a better shape of the function at ADDRESS in PATH. 0 when it reaches 100%."""
    original = path.read_bytes()
    source, crlf = llm.read_source(path)
    lines = source.rstrip("\n").split("\n")
    span = llm.definition_span(lines, address)
    if span is None or "{" not in lines[span[0]:span[1]]:
        sys.exit(f"{path} has no definition at {hex(address)} with its opening brace on a line of its own")
    opening = lines.index("{", span[0])
    head, body = lines[span[0]:opening + 1], lines[opening + 1:span[1]]

    def build_and_score(new_body):
        return try_function(path, lines, span, head + new_body + ["}"], crlf, address)

    kept = False
    try:
        start = build_and_score(body)
        if start is None:
            sys.exit(f"{path} does not build")
        print(f"start: {describe(start[0])}", flush=True)
        if start[0].exact:
            return 0
        if llm.names_only(start[1]):
            print("Only the names of globals or functions differ: fix the declarations, a new shape cannot help.")
            return 1
        changes = CHANGES + [change for change, diff in GATED if diff.search(start[1])]
        guesses = [change for change, diff in GUESSES if diff.search(start[1])]
        best, best_body, tried = search(build_and_score, start[0], body, tries, minutes, random.Random(seed), changes,
                                        guesses, rank_key)
        OUT.mkdir(parents=True, exist_ok=True)
        (OUT / f"{address:08x}.c").write_text("\n".join(head + best_body + ["}"]) + "\n", encoding="utf-8")
        if best.percent > start[0].percent:
            final = build_and_score(best_body)
            kept = final is not None and final[0].percent > start[0].percent
        print(f"{tried} tries: {describe(start[0])} -> {describe(best)}; "
              + (f"written to {path}" if kept else f"{path} unchanged, best try in {OUT}"))
    finally:
        if not kept:
            path.write_bytes(original)
    return 0 if best.exact else 1
