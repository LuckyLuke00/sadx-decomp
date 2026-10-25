"""Unit tests for the type search in tools/retype.py: the edits on text and the verdict on the scores.

The fixtures are synthetic lines and scores. Nothing builds.
"""

import retype

S = "DAT_00800000"  # the symbol a candidate retypes
TASK = "struct taskwk *"


def exits(step) -> bool:
    """Whether STEP stops the run."""
    try:
        step()
    except SystemExit:
        return True
    return False


def check_replace() -> list[str]:
    """A replace edit needs its count: another count stops the run, before anything is written."""
    failures = []
    if retype.replace_text("a b a", "a", "c", 2, "f.c") != "c b c":
        failures.append("replace_text does not replace both")
    if not exits(lambda: retype.replace_text("a b a", "a", "c", 1, "f.c")):
        failures.append("replace_text goes on with a wrong count")
    if not exits(lambda: retype.apply_edits({"f.c": "int x;\n"}, [{"kind": "extern", "symbol": S, "decl": f"int {S}"}])):
        failures.append("an extern edit that finds no line does not stop the run")
    return failures


def check_externs() -> list[str]:
    """Only the column-0 extern lines of the symbol change. Another symbol, an indented line and a prototype stay."""
    text = "\n".join([f"extern short *{S};", f"extern short *{S}0;", f"    extern short *{S};", f"void f(short *{S});",
                      f"extern char {S}[4];"])
    wanted = "\n".join([f"extern {TASK}{S};", f"extern short *{S}0;", f"    extern short *{S};",
                        f"void f(short *{S});", f"extern {TASK}{S};"])
    found, count = retype.retype_externs(text, S, f"{TASK}{S}")
    return [] if (found, count) == (wanted, 2) else [f"retype_externs gives {count} lines:\n{found}"]


def check_uncast() -> list[str]:
    """A cast to the new type goes, with the parentheses it leaves when they are not a call's. A cast to another
    type stays, and so does one on a member, whose type is another."""
    cases = [
        ("a read", f"x = *(int *)&{S};", "int", f"x = {S};"),
        ("a read in a call", f"f(*(int *)&{S});", "int", f"f({S});"),
        ("a pointer to a pointer", f"Set((*(struct taskwk *(*))&{S}));", TASK, f"Set({S});"),
        ("a member through it", f"if ((*(struct taskwk *(*))&{S})->pos.y >= y)", TASK, f"if ({S}->pos.y >= y)"),
        ("a conversion", f"((struct taskwk *){S})->pos.x = 0;", TASK, f"{S}->pos.x = 0;"),
        ("an element", f"x = *(int *)&{S}[4];", "int", f"x = {S}[4];"),
        ("another type", f"x = *(char *)&{S};", "int", f"x = *(char *)&{S};"),
        ("a member", f"x = *(int *)&{S}.y;", "int", f"x = *(int *)&{S}.y;"),
        ("another symbol", f"x = (int){S}0;", "int", f"x = (int){S}0;"),
    ]
    failures = []
    for case, line, ctype, wanted in cases:
        found = retype.uncast(line, S, ctype)
        if found != wanted:
            failures.append(f"uncast of {case} gives {found!r}, not {wanted!r}")
    found = retype.count_casts(f"x = *(int *)&{S} + (char){S} + {S}; // (int){S}", S)
    if found != 2:
        failures.append(f"count_casts finds {found} casts, not 2")
    return failures


def result(name, scores, error=None, puns=0, other_fakes=0, casts=0):
    return retype.Result(name, error, scores, puns, other_fakes, casts, 0.0)


def check_winner() -> list[str]:
    """A survivor builds, drops no function and leaves no address_pun line in the watched functions, nor a new fake
    line of another kind. One survivor wins; of several, the preferred one, else the only one with the fewest casts
    left; else nothing wins."""
    base = result("baseline", {1: 1.0, 2: 0.5}, puns=2, other_fakes=1, casts=3)
    good = result("good", {1: 1.0, 2: 0.6}, other_fakes=1)
    same = result("same", {1: 1.0, 2: 0.5}, casts=1)
    cases = [
        ("one survivor", [good, result("worse", {1: 0.9, 2: 1.0}), result("broken", {}, error="error C2440"),
                          result("puns", {1: 1.0, 2: 0.5}, puns=1), result("fakes", {1: 1.0, 2: 0.5}, other_fakes=2),
                          result("lost", {1: 1.0})], None, "good"),
        ("the preferred survivor", [good, same], "same", "same"),
        ("the fewest casts", [good, same], None, "good"),
        ("a tie", [good, same._replace(casts=0)], None, None),
        ("no survivor", [result("puns", {1: 1.0, 2: 0.5}, puns=1)], None, None),
    ]
    failures = []
    for case, results, prefer, wanted in cases:
        found, why = retype.winner(base, results, prefer)
        if found != wanted:
            failures.append(f"winner of {case} is {found} ({why}), not {wanted}")
    return failures


def run() -> list[str]:
    """Run every check and give all the failures."""
    failures = []
    for check in (check_replace, check_externs, check_uncast, check_winner):
        failures += check()
    return failures
