"""Unit tests for the changes in tools/permute.py: what each one makes of a body, and where it must not apply.

The fixtures are synthetic function bodies, one line per statement and tabs as in the tree. Nothing builds.
"""

import permute


def made(change, body):
    """Every body that CHANGE makes from BODY, each as one string."""
    return ["\n".join(new) for new in permute.neighbors(body, [change])]


def lines(text):
    return text.strip("\n").split("\n")


def expect(name, change, body, wanted):
    """A failure unless CHANGE makes exactly the bodies WANTED from BODY."""
    found = made(change, lines(body))
    wanted = ["\n".join(lines(w)) for w in wanted]
    if sorted(found) == sorted(wanted):
        return []
    return [f"{name}: {change.__name__} makes\n" + "\n--\n".join(found) + "\ninstead of\n" + "\n--\n".join(wanted)]


def check_inline_temp():
    """A temp read once by the next line goes into it; the declaration stays while a later store and read use
    it, and goes when nothing else does. Brackets only where the place is not a whole operand."""
    failures = expect("two uses", permute.inline_temp, """
\tfloat t;
\tt = p->x * p->x + p->z * p->z;
\tr = njSqrt(t);
\tif (q)
\t{
\t\tt = q->x * q->x;
\t\tr = njSqrt(t);
\t}
""", ["""
\tfloat t;
\tr = njSqrt(p->x * p->x + p->z * p->z);
\tif (q)
\t{
\t\tt = q->x * q->x;
\t\tr = njSqrt(t);
\t}
""", """
\tfloat t;
\tt = p->x * p->x + p->z * p->z;
\tr = njSqrt(t);
\tif (q)
\t{
\t\tr = njSqrt(q->x * q->x);
\t}
"""])
    failures += expect("brackets", permute.inline_temp, """
\tint t;
\tt = a + b;
\tx = t * 2;
""", ["""
\tx = (a + b) * 2;
"""])
    return failures


def check_inline_temp_refuses():
    """No inline where the value is read again, read before in a loop, or read after a store whose block has
    closed, where a call on the line runs before the read, or where the address of the temp is taken."""
    refused = {
        "read again": "\tint t;\n\tt = a + b;\n\tf(t);\n\tg(t);",
        "read before in a loop": "\tint t;\n\twhile (c)\n\t{\n\t\tg(t);\n\t\tt = a + b;\n\t\tf(t);\n\t}",
        "read by the loop": "\tint t;\n\tdo\n\t{\n\t\tt = a + b;\n\t\tf(t);\n\t} while (t);",
        "closed store": "\tint t;\n\tt = a + b;\n\tf(t);\n\tif (c)\n\t{\n\t\tt = 1;\n\t}\n\tg(t);",
        "call first": "\tint t;\n\tt = a + b;\n\tx = h() + t;",
        "address": "\tint t;\n\tt = a + b;\n\tf(t);\n\tg(&t);",
        "parameter": "\tt = a + b;\n\tf(t);",
    }
    return [f"inline_temp changes the case '{name}'" for name, body in refused.items()
            if made(permute.inline_temp, lines(body))]


def check_inline_temp_covered():
    """A store in the same block before the next read hides the old value, so the inline goes ahead."""
    return expect("covered", permute.inline_temp, """
\tint t;
\tt = a + b;
\tf(t);
\tt = 2;
\tg(t);
""", ["""
\tint t;
\tf(a + b);
\tt = 2;
\tg(t);
""", """
\tint t;
\tt = a + b;
\tf(t);
\tg(2);
"""])


def check_invert_else_if():
    """An else-if with an else swaps its two blocks and negates its condition; the first if stays."""
    body = """
\tif (x > 1)
\t{
\t\ta();
\t}
\telse if (x < 2)
\t{
\t\tb();
\t}
\telse
\t{
\t\tc();
\t}
"""
    wanted = """
\tif (x > 1)
\t{
\t\ta();
\t}
\telse if (x >= 2)
\t{
\t\tc();
\t}
\telse
\t{
\t\tb();
\t}
"""
    found = made(permute.invert_if, lines(body))
    if "\n".join(lines(wanted)) in found:
        return []
    return ["invert_if gives no swapped else-if:\n" + "\n--\n".join(found)]


def check_ternary():
    """An if/else that stores one of two values to one place, or returns one of two, becomes a ternary, and back."""
    stores = "\tif (a < b)\n\t{\n\t\tx = 1;\n\t}\n\telse\n\t{\n\t\tx = y;\n\t}"
    returns = "\tif (c)\n\t{\n\t\treturn p->a;\n\t}\n\telse\n\t{\n\t\treturn 0;\n\t}"
    failures = expect("stores", permute.if_to_ternary, stores, ["\tx = a < b ? 1 : y;"])
    failures += expect("returns", permute.if_to_ternary, returns, ["\treturn c ? p->a : 0;"])
    failures += expect("two places", permute.if_to_ternary, stores.replace("x = y", "z = y"), [])
    failures += expect("back", permute.ternary_to_if, "\tx = a < b ? 1 : y;", [stores])
    return failures


def check_else_tail():
    """An if block that ends in a jump takes the rest of its block as an else, or the next if as an else-if, and
    drop_else takes them away again."""
    plain = "\tif (!p)\n\t{\n\t\treturn;\n\t}\n\tf();\n\tg();"
    wrapped = "\tif (!p)\n\t{\n\t\treturn;\n\t}\n\telse\n\t{\n\t\tf();\n\t\tg();\n\t}"
    chain = "\tif (a)\n\t{\n\t\treturn 1;\n\t}\n\tif (b)\n\t{\n\t\tf();\n\t}\n\treturn 0;"
    in_loop = "\twhile (c)\n\t{\n\t\tif (a)\n\t\t{\n\t\t\tbreak;\n\t\t}\n\t\tf();\n\t}\n\tg();"
    failures = expect("rest", permute.else_tail, plain, [wrapped])
    failures += expect("else-if", permute.else_tail, chain, [
        "\tif (a)\n\t{\n\t\treturn 1;\n\t}\n\telse if (b)\n\t{\n\t\tf();\n\t}\n\treturn 0;",
        "\tif (a)\n\t{\n\t\treturn 1;\n\t}\n\telse\n\t{\n\t\tif (b)\n\t\t{\n\t\t\tf();\n\t\t}\n\t\treturn 0;\n\t}"])
    failures += expect("loop", permute.else_tail, in_loop, [
        "\twhile (c)\n\t{\n\t\tif (a)\n\t\t{\n\t\t\tbreak;\n\t\t}\n\t\telse\n\t\t{\n\t\t\tf();\n\t\t}\n\t}\n\tg();"])
    failures += expect("back", permute.drop_else, wrapped, [plain])
    failures += expect("back from else-if", permute.drop_else,
                       "\tif (a)\n\t{\n\t\treturn 1;\n\t}\n\telse if (b)\n\t{\n\t\tf();\n\t}", [
                           "\tif (a)\n\t{\n\t\treturn 1;\n\t}\n\tif (b)\n\t{\n\t\tf();\n\t}"])
    return failures


def check_else_tail_refuses():
    """No else where the block can reach its end, where it has one already, where the rest holds a label or a local
    of its own, and no drop where the else declares a local that would move out of its block."""
    refused = {
        "no jump": (permute.else_tail, "\tif (a)\n\t{\n\t\tf();\n\t}\n\tg();"),
        "jump deeper": (permute.else_tail, "\tif (a)\n\t{\n\t\tif (b)\n\t\t{\n\t\t\treturn;\n\t\t}\n\t}\n\tg();"),
        "has an else": (permute.else_tail, "\tif (a)\n\t{\n\t\treturn;\n\t}\n\telse\n\t{\n\t\tf();\n\t}"),
        "label": (permute.else_tail, "\tif (a)\n\t{\n\t\treturn;\n\t}\n\tf();\n\tdone:\n\tg();"),
        "local": (permute.else_tail, "\tif (a)\n\t{\n\t\treturn;\n\t}\n\tint x = f();\n\tg(x);"),
        "drop a local": (permute.drop_else,
                         "\tif (a)\n\t{\n\t\treturn;\n\t}\n\telse\n\t{\n\t\tint x = f();\n\t\tg(x);\n\t}"),
        "drop with no jump": (permute.drop_else, "\tif (a)\n\t{\n\t\tf();\n\t}\n\telse\n\t{\n\t\tg();\n\t}"),
    }
    return [f"{change.__name__} changes the case '{name}'" for name, (change, body) in refused.items()
            if made(change, lines(body))]


def check_fall_through():
    """A break before a case goes, a case that runs on gets one, and labels or jumps in a row are left alone."""
    body = "\tswitch (m)\n\t{\n\t\tcase 0:\n\t\t\tf();\n\t\t\tbreak;\n\t\tcase 1:\n\t\tcase 2:\n" \
           "\t\t\tg();\n\t\t\treturn;\n\t\tdefault:\n\t\t\th();\n\t}"
    return expect("cases", permute.fall_through, body, [body.replace("\t\t\tbreak;\n", "")])


def check_change_comparison():
    """Each comparison in a condition gets the other operators, with and without `!( )`, on the sides in either
    order; a part that is not one comparison at the top gets nothing. The gate fires on a changed compare mask, or
    on a changed jump right after one, and not on an unchanged pair."""
    product = "(s + 60.0f) * (s + 60.0f)"
    found = made(permute.change_comparison, [f"\tif (d <= {product})"])
    plain = [f"{a} {o} {b}" for a, b in [("d", product), (product, "d")] for o in ["<", "<=", ">", ">="]]
    wanted = {f"\tif ({form})" for form in plain + [f"!({form})" for form in plain]} - {f"\tif (d <= {product})"}
    failures = [] if set(found) == wanted and len(found) == 15 else [f"change_comparison makes {found}"]
    found = made(permute.change_comparison, ["\twhile (!(a < b) && c > 1.0f)"])
    if len(found) != 30 or "\twhile (a >= b && c > 1.0f)" not in found or "\twhile (!(a < b) && 1.0f < c)" not in found:
        failures.append(f"change_comparison makes {found} for two parts")
    for body in ["\tif (a & b < c)", "\tif (a == b)", "\tif (a < b < c)", "\tif (f(a < b))", "\tx = a < b;"]:
        if made(permute.change_comparison, [body]):
            failures.append(f"change_comparison changes {body!r}")
    shown = {"mask": "0x5945f6 : fnstsw ax\n0x5945f8 : -test ah, 0x41\n         : +test ah, 5\n",
             "jump": "0x5945f8 : test ah, 0x41 \t(a.c:3)\n0x5945fb : -jne 0x16\n         : +jp 0x16\n"}
    failures += [f"COMPARE_DIFF misses the {name}" for name, diff in shown.items()
                 if not permute.COMPARE_DIFF.search(diff)]
    if permute.COMPARE_DIFF.search("0x5945f8 : test ah, 0x41\n0x5945fb : jne 0x16\n0x5945fd : -mov eax, 1\n"):
        failures.append("COMPARE_DIFF fires on an unchanged compare")
    return failures


def check_nest_return():
    """An early jump, braced or not, puts the rest of its block under the negated condition when the rest ends in a
    jump; not when the rest can run off its end, or holds a label."""
    rest = "\tg();\n\treturn x;"
    nested = "\tif (p != 0)\n\t{\n\t\tg();\n\t\treturn x;\n\t}\n\treturn 0;"
    failures = expect("braced", permute.nest_return, "\tif (p == 0)\n\t{\n\t\treturn 0;\n\t}\n" + rest, [nested])
    failures += expect("braceless", permute.nest_return, "\tif (p == 0)\n\t\treturn 0;\n" + rest, [nested])
    failures += expect("in a loop", permute.nest_return,
                       "\twhile (c)\n\t{\n\t\tif (a)\n\t\t{\n\t\t\tcontinue;\n\t\t}\n\t\tf();\n\t\tbreak;\n\t}",
                       ["\twhile (c)\n\t{\n\t\tif (!a)\n\t\t{\n\t\t\tf();\n\t\t\tbreak;\n\t\t}\n\t\tcontinue;\n\t}"])
    for name, body in {"runs off": "\tif (a)\n\t{\n\t\treturn;\n\t}\n\tf();",
                       "label": "\tif (a)\n\t{\n\t\treturn 0;\n\t}\n\tdone:\n\treturn 1;"}.items():
        if made(permute.nest_return, lines(body)):
            failures.append(f"nest_return changes the case '{name}'")
    return failures


def step(before, after):
    """A change that turns the one-line body BEFORE into AFTER, and finds no place in any other body."""
    def change(body, rng):
        return [after] if body == [before] else None
    change.__name__ = f"{before}_to_{after}"
    return change


def climb(changes, scores, seeds=range(20), guesses=()):
    """For each seed, the body that search() ends on from the body S, with CHANGES and GUESSES, where SCORES gives
    each body's percent and 100 is an exact match."""
    import random
    ends = []
    for seed in seeds:
        def build_and_score(new):
            return permute.Score(scores[new[0]], scores[new[0]] == 100, 0, 0), ""
        best = permute.search(build_and_score, build_and_score(["S"])[0], ["S"], 50, None, random.Random(seed),
                              changes, list(guesses), lambda s: s.percent)
        ends.append(best[1][0])
    return ends


def check_search():
    """A better change first does not hide a fix one change from the start, and a change that alone scores the same
    leads on to a fix one change after it, for every seed. A guess counts only as an exact match, unless a change
    makes the same body too."""
    import contextlib
    import io
    with contextlib.redirect_stdout(io.StringIO()):
        ends = {"B": climb([step("S", "A"), step("S", "B"), step("A", "A2")], {"S": 90, "A": 95, "A2": 80, "B": 100}),
                "X": climb([step("S", "T"), step("S", "W"), step("T", "X")], {"S": 90, "T": 90, "W": 80, "X": 100}),
                "A": climb([step("S", "A")], {"S": 90, "A": 95, "G": 97}, guesses=[step("S", "G")]),
                "G": climb([step("S", "A")], {"S": 90, "A": 95, "G": 100}, guesses=[step("S", "G")]),
                "C": climb([step("S", "C")], {"S": 90, "C": 95}, guesses=[step("S", "C")])}
    return [f"search ends on {found} instead of {wanted} every time" for wanted, found in ends.items()
            if set(found) != {wanted}]


def run():
    return [failure for check in (check_inline_temp, check_inline_temp_refuses, check_inline_temp_covered,
                                  check_invert_else_if, check_ternary, check_else_tail, check_else_tail_refuses,
                                  check_nest_return, check_fall_through, check_change_comparison, check_search)
            for failure in check()]


if __name__ == "__main__":
    print("\n\n".join(run()) or "permutetests: all pass")
