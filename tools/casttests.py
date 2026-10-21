"""Unit tests for the pointer-conversion casts of tools/llm.py and tools/cfix.py.

The helpers read the build output (C2440 and C2664 lines), find the spot that a cast belongs to, add the cast, and
undo the casts that did not help. The fixtures are synthetic: one file, src/foo.c, with one function at 0x00401000.
"""

from pathlib import Path

import cfix
import llm

PATH_TEXT = "src/foo.c"
PATH = Path(PATH_TEXT)
ADDRESS = 0x00401000
SIGNATURE = "void work(char *p, int *q)"
PLAIN = ("int *", "char *")  # the types of a pointer conversion: from, to
SYNTAX = "error C2143: syntax error : missing ')' before '*'"


def refusal(line, name, param, source, target, path=PATH_TEXT):
    """The build output line for a conversion that the compiler refuses."""
    if param is None:
        return f"{path}({line}) : error C2440: '{name}' : cannot convert from '{source}' to '{target}'"
    return f"{path}({line}) : error C2664: '{name}' : cannot convert parameter {param} from '{source}' to '{target}'"


def function_of(body, signature=SIGNATURE):
    """The lines of a definition at ADDRESS, from its annotation to its closing brace."""
    return [llm.function_line(ADDRESS), signature, "{", *body, "}"]


def refusals_of(lines, spots, path=PATH_TEXT):
    """The build output for SPOTS, tuples of (line text, name, param, from, to), in the file with LINES."""
    return "\n".join(refusal(lines.index(spot[0]) + 1, *spot[1:], path=path) for spot in spots)


def check_conversions() -> list[str]:
    """Each C2440 and C2664 line of the build output gives one Conversion, once, in the order of first sight. A line
    of another error, a warning or no text gives none. The path is whatever stands before the line number."""
    c2440 = refusal(7, "=", None, *PLAIN)
    c2664 = refusal(9, "Run", 2, *PLAIN)
    other = ["src/foo.c(7) : warning C4047: '=' : 'char *' differs in levels of indirection from 'int'",
             "src/foo.c(8) : error C2065: 'x' : undeclared identifier"]
    conv = llm.Conversion
    cases = [
        ("a C2440", c2440, [conv(PATH_TEXT, 7, "=", None, *PLAIN)]),
        ("a C2664", c2664, [conv(PATH_TEXT, 9, "Run", 2, *PLAIN)]),
        ("a C2664 that says argument", "src/foo.c(9) : error C2664: 'Run' : cannot convert argument 1 from 'int' to "
         "'char *'", [conv(PATH_TEXT, 9, "Run", 1, "int", "char *")]),
        ("a C2440 that names initializing", refusal(7, "initializing", None, *PLAIN),
         [conv(PATH_TEXT, 7, "initializing", None, *PLAIN)]),
        ("lines that repeat", "\n".join([c2440, c2664, c2440, c2664]),
         [conv(PATH_TEXT, 7, "=", None, *PLAIN), conv(PATH_TEXT, 9, "Run", 2, *PLAIN)]),
        ("one error at two lines", c2440 + "\n" + refusal(8, "=", None, *PLAIN),
         [conv(PATH_TEXT, 7, "=", None, *PLAIN), conv(PATH_TEXT, 8, "=", None, *PLAIN)]),
        ("two parameters of one call", c2664 + "\n" + refusal(9, "Run", 1, *PLAIN),
         [conv(PATH_TEXT, 9, "Run", 2, *PLAIN), conv(PATH_TEXT, 9, "Run", 1, *PLAIN)]),
        ("other errors and a warning", "\n".join(other[:1] + [c2664] + other[1:]),
         [conv(PATH_TEXT, 9, "Run", 2, *PLAIN)]),
        ("an indented line with a drive in its path", "    " + refusal(12, "=", None, *PLAIN, path="D:\\work\\foo.c"),
         [conv("D:\\work\\foo.c", 12, "=", None, *PLAIN)]),
        ("lines with CRLF", c2440 + "\r\n" + c2664 + "\r\n", [conv(PATH_TEXT, 7, "=", None, *PLAIN),
                                                              conv(PATH_TEXT, 9, "Run", 2, *PLAIN)]),
        ("no text", "", []),
    ]
    failures = []
    for case, text, wanted in cases:
        found = llm.conversions(text)
        if found != wanted:
            failures.append(f"conversions gives {found} for {case}, not {wanted}")
    return failures


def check_type_kind() -> list[str]:
    """A type as the compiler prints it is a pointer when it has a `*`, an array when it ends in `[n]`, an integer when
    it is one of the integer scalars once const and volatile are gone, and other for the rest. bool, float and double
    are other, and so are a reference and a member pointer: a C cast would not make that conversion."""
    cases = [
        ("char *", "pointer"), ("const char *", "pointer"), ("char *const", "pointer"), ("struct Foo *", "pointer"),
        ("int **", "pointer"), ("int (__cdecl *)(int)", "pointer"), ("volatile int *", "pointer"),
        ("int [4]", "array"), ("char[16]", "array"), ("const int [2]", "array"), ("int []", "array"),
        ("long long", "integer"), ("unsigned int", "integer"), ("unsigned long long", "integer"),
        ("signed char", "integer"), ("unsigned __int64", "integer"), ("const int", "integer"),
        ("volatile unsigned short", "integer"),
        ("bool", "other"), ("float", "other"), ("double", "other"), ("const double", "other"), ("void", "other"),
        ("struct Foo", "other"), ("int &", "other"), ("int *&", "other"), ("const Foo &", "other"),
        ("int Foo::*", "other"), ("int (Foo::*)(int)", "other"), ("", "other"),
    ]
    failures = []
    for name, wanted in cases:
        found = cfix.type_kind(name)
        if found != wanted:
            failures.append(f"type_kind gives {found!r} for {name!r}, not {wanted!r}")
    return failures


def check_pointer_conversion() -> list[str]:
    """A conversion needs a cast when it goes from a pointer or an array to a pointer or an integer, or from an
    integer to a pointer. A C2440 counts only when it names one converted expression: =, initializing or return. A
    C++ template in the target is no conversion for a C cast. Struct, float, bool, array and reference targets, and
    integer to integer, are none."""
    cases = [
        ("a pointer assigned to a pointer", "=", None, "int *", "char *", True),
        ("a pointer used to initialize a pointer", "initializing", None, "int *", "char *", True),
        ("a pointer returned as a pointer", "return", None, "int *", "char *", True),
        ("a pointer passed as a pointer", "Run", 2, "int *", "char *", True),
        ("a pointer to an integer", "=", None, "int *", "int", True),
        ("an integer to a pointer", "=", None, "int", "char *", True),
        ("an array to a pointer", "=", None, "int [4]", "int *", True),
        ("an array to an integer", "=", None, "char [4]", "int", True),
        ("a C2440 of an unnamed kind", "type cast", None, "int *", "char *", False),
        ("a template target", "=", None, "int *", "Foo<int> *", False),
        ("a template target in a call", "Run", 1, "int *", "Foo<int> *", False),
        ("an integer to an integer", "=", None, "int", "short", False),
        ("a pointer to a float", "=", None, "int *", "float", False),
        ("an integer to a bool", "=", None, "int", "bool", False),
        ("a pointer to a struct", "=", None, "Foo *", "Foo", False),
        ("a struct to a pointer", "=", None, "Foo", "Foo *", False),
        ("a pointer to an array", "=", None, "int *", "int [4]", False),
        ("an array to an array", "=", None, "int [4]", "char [4]", False),
        ("a pointer to a reference", "Run", 1, "int *", "int &", False),
        ("a pointer to a member pointer", "=", None, "int *", "int Foo::*", False),
    ]
    failures = []
    for case, name, param, source, target, wanted in cases:
        found = llm.pointer_conversion(llm.Conversion(PATH_TEXT, 1, name, param, source, target))
        if found != wanted:
            failures.append(f"pointer_conversion gives {found} for {case}, not {wanted}")
    return failures


def check_cast_line() -> list[str]:
    """cast_line puts the cast in front of the one expression that the Conversion names: the value after the one `=`
    or `return` of a C2440, or argument PARAM of the one call to the callee of a C2664. The cast gets brackets
    around anything that is more than one operand, and the tag before a struct, union or enum name of the target
    that the tree has. A bracket, comma, `=` or the callee's name in a string, a character or a comment does not
    count. The result is None when the spot is more than one place: two `=`, two calls, a missing or empty argument,
    or an expression that goes on in the next line."""
    foo = {"Foo": "struct"}
    cases = [
        ("an assignment", "\tp = q;", "=", None, "char *", {}, "\tp = (char *)q;"),
        ("an initializer", "\tchar *p = q;", "initializing", None, "char *", {}, "\tchar *p = (char *)q;"),
        ("a return", "\treturn q;", "return", None, "char *", {}, "\treturn (char *)q;"),
        ("a return after an if", "\tif (a) return q;", "return", None, "char *", {}, "\tif (a) return (char *)q;"),
        ("a return in front of a comment", "\treturn q; // return", "return", None, "char *", {},
         "\treturn (char *)q; // return"),
        ("a sum", "\tp = q + 1;", "=", None, "char *", {}, "\tp = (char *)(q + 1);"),
        ("a condition", "\treturn a ? q : r;", "return", None, "char *", {}, "\treturn (char *)(a ? q : r);"),
        ("an address of a member", "\tp = &r->next[2];", "=", None, "char *", {}, "\tp = (char *)&r->next[2];"),
        ("a call", "\tp = Bar(a, b);", "=", None, "char *", {}, "\tp = (char *)Bar(a, b);"),
        ("blanks around the value", "\tp =   q  ;", "=", None, "char *", {}, "\tp =   (char *)q  ;"),
        ("a comparison before the assignment", "\tif (a == b) p = q;", "=", None, "char *", {},
         "\tif (a == b) p = (char *)q;"),
        ("a value that a bracket closes", "\twhile ((p = Bar(q)) != 0)", "=", None, "char *", {},
         "\twhile ((p = (char *)Bar(q)) != 0)"),
        ("a = in a string and a comment", '\tp = Bar(";", q); // x = y', "=", None, "char *", {},
         '\tp = (char *)Bar(";", q); // x = y'),
        ("a compound assignment", "\tp += q;", "=", None, "char *", {}, None),
        ("two assignments", "\ta = p = q;", "=", None, "char *", {}, None),
        ("two declarators", "\tchar *p = q, *r = s;", "initializing", None, "char *", {}, None),
        ("a value that goes on", "\tp = Bar(a,", "=", None, "char *", {}, None),
        ("a sum that goes on", "\tp = q +", "=", None, "char *", {}, None),
        ("no value", "\tp =;", "=", None, "char *", {}, None),
        ("a brace initializer", "\tchar *p[] = { q, r };", "initializing", None, "char *", {}, None),
        ("the first argument", "\tRun(a, b);", "Run", 1, "char *", {}, "\tRun((char *)a, b);"),
        ("a middle argument", "\tRun(a, b, c);", "Run", 2, "char *", {}, "\tRun(a, (char *)b, c);"),
        ("the last argument", "\tRun(a, b, c);", "Run", 3, "char *", {}, "\tRun(a, b, (char *)c);"),
        ("a call as the first argument", "\tRun(Bar(a, b), c);", "Run", 1, "char *", {},
         "\tRun((char *)Bar(a, b), c);"),
        ("an argument after a call", "\tRun(Bar(a, b), c);", "Run", 2, "char *", {}, "\tRun(Bar(a, b), (char *)c);"),
        ("a sum as an argument", "\tRun(a, b + 1);", "Run", 2, "char *", {}, "\tRun(a, (char *)(b + 1));"),
        ("a space before the bracket", "\tRun (a, b);", "Run", 2, "char *", {}, "\tRun (a, (char *)b);"),
        ("the callee's name in a string", '\tRun("Run(", b);', "Run", 2, "char *", {}, '\tRun("Run(", (char *)b);'),
        ("two calls of the callee", "\tRun(a, Run(b, c));", "Run", 2, "char *", {}, None),
        ("the callee's name inside another name", "\tmyRun(a, b);", "Run", 2, "char *", {}, None),
        ("a missing argument", "\tRun(a);", "Run", 2, "char *", {}, None),
        ("a call without arguments", "\tRun();", "Run", 1, "char *", {}, None),
        ("an empty argument", "\tRun(a, , c);", "Run", 2, "char *", {}, None),
        ("a call that goes on", "\tRun(a,", "Run", 2, "char *", {}, None),
        ("a call that is not closed", "\tRun(a, b", "Run", 2, "char *", {}, None),
        ("a tag of the tree", "\tp = q;", "=", None, "Foo *", foo, "\tp = (struct Foo *)q;"),
        ("a tag in a const type", "\tp = q;", "=", None, "const Foo **", foo, "\tp = (const struct Foo **)q;"),
        ("a tag that is already there", "\tp = q;", "=", None, "struct Foo *", foo, "\tp = (struct Foo *)q;"),
        ("a name that the tree lacks", "\tp = q;", "=", None, "Bar *", foo, "\tp = (Bar *)q;"),
        ("blanks around the target", "\tp = q;", "=", None, " Foo * ", foo, "\tp = (struct Foo *)q;"),
    ]
    failures = []
    for case, line, name, param, target, kinds, wanted in cases:
        found = cfix.cast_line(line, llm.Conversion(PATH_TEXT, 1, name, param, "int *", target), kinds)
        if found != wanted:
            failures.append(f"cast_line gives {found!r} for {case}, not {wanted!r}")
    return failures


def casting(body, spots, head=(), tail=(), signature=SIGNATURE, edit=None, address=ADDRESS, refused=(), kinds=None,
            path=PATH_TEXT):
    """(the function lines given, add_casts' lines, add_casts' Conversions) for a function with BODY in a file with
    HEAD above it and TAIL below it, whose build refused SPOTS. EDIT maps a line to the text that the function lines
    have in place of it. REFUSED holds the indexes of the Conversions that the call refuses to cast."""
    func = function_of(body, signature)
    lines = [*head, *func, *tail]
    text = refusals_of(lines, spots, path)
    given = [(edit or {}).get(line, line) for line in func]
    skipped = {llm.conversions(text)[i] for i in refused}
    cast, applied = llm.add_casts(given, "\n".join(lines), text, PATH, address, kinds or {}, skipped)
    return given, cast, applied


def check_add_casts() -> list[str]:
    """add_casts casts each pointer conversion that the build refused in the function's own lines of the file, and
    returns those Conversions. It leaves a conversion alone when: it is no pointer conversion, its spot is in
    another file, in the signature or in another function, its line continues a statement from the line before, the
    line changed since the build, the Conversion is in REFUSED, or cast_line finds no single spot. A definition that
    the file lacks gives the lines back."""
    p_q, run_q = "\tp = q;", "\tRun(1, q);"
    spot_p, spot_run = (p_q, "=", None, *PLAIN), (run_q, "Run", 2, *PLAIN)
    cast_p, cast_run = "\tp = (char *)q;", "\tRun(1, (char *)q);"
    other_above = [llm.function_line(0x00400000), "void task(void)", "{", "\tt = u;", "}", ""]
    other_below = ["", llm.function_line(0x00402000), "void pad(void)", "{", "\tr = s;", "}"]
    continued = ["\tif (a &&", "\t    (p = q))", "\t\tx = 0;", "\tBar(a,", "\t    Run(1, q));", p_q]
    # (case, body, spots, options, the body wanted, the number of Conversions wanted)
    cases = [
        ("two refused conversions", [p_q, run_q], [spot_p, spot_run], {}, [cast_p, cast_run], 2),
        ("a conversion in another file", [p_q, run_q], [spot_p, spot_run], {"path": "src/other.c"}, [p_q, run_q], 0),
        ("the file spelt another way", [p_q], [spot_p], {"path": "src/./foo.c"}, [cast_p], 1),
        ("a conversion of an integer to an integer", [p_q], [(p_q, "=", None, "int", "short")], {}, [p_q], 0),
        ("a Conversion in REFUSED", [p_q, run_q], [spot_p, spot_run], {"refused": [0]}, [p_q, cast_run], 1),
        ("lines that continue a statement", continued, [(continued[1], "=", None, *PLAIN),
                                                        (continued[4], "Run", 2, *PLAIN), (p_q, "=", None, *PLAIN)],
         {}, continued[:5] + [cast_p], 1),
        ("a line in another function above", [p_q], [spot_p, ("\tt = u;", "=", None, *PLAIN)],
         {"head": other_above}, [cast_p], 1),
        ("a line in another function below", [p_q], [spot_p, ("\tr = s;", "=", None, *PLAIN)],
         {"tail": other_below}, [cast_p], 1),
        ("a line in the signature", [p_q], [spot_p, ("void work(char *p = q)", "=", None, *PLAIN)],
         {"signature": "void work(char *p = q)"}, [cast_p], 1),
        ("a line that changed since the build", [p_q], [spot_p], {"edit": {p_q: cast_p}}, [cast_p], 0),
        ("a spot that is not one place", ["\ta = p = q;", p_q], [("\ta = p = q;", "=", None, *PLAIN), spot_p], {},
         ["\ta = p = q;", cast_p], 1),
        ("two conversions of one line", ["\tRun(p, q);"], [("\tRun(p, q);", "Run", 1, "char *", "int *"),
                                                           ("\tRun(p, q);", "Run", 2, *PLAIN)],
         {}, ["\tRun((int *)p, (char *)q);"], 2),
        ("a tag of the tree", [p_q], [(p_q, "=", None, "int *", "Foo *")], {"kinds": {"Foo": "struct"}},
         ["\tp = (struct Foo *)q;"], 1),
        ("a definition that the file lacks", [p_q], [spot_p], {"address": 0x00403000}, [p_q], 0),
        ("no build output", [p_q], [], {}, [p_q], 0),
    ]
    failures = []
    for case, body, spots, options, wanted_body, wanted_count in cases:
        given, cast, applied = casting(body, spots, **options)
        wanted = [*given[:3], *wanted_body, given[-1]]
        if cast != wanted or len(applied) != wanted_count:
            failures.append(f"add_casts gives {cast[3:-1]} and {len(applied)} Conversions for {case}, "
                            f"not {wanted_body} and {wanted_count}")
    return failures


def check_cast_failed() -> list[str]:
    """A cast failed when its error is still in the build with the casts, or when its line has a syntax error that the
    first build did not have, such as a cast to a name that the compiler does not know. Another error that the first
    one hid, an error on another line or in another file, or a syntax error that was there before, is not the
    cast's fault. The result keeps the order of APPLIED."""
    c7 = llm.Conversion(PATH_TEXT, 7, "Run", 2, *PLAIN)
    c9 = llm.Conversion(PATH_TEXT, 9, "Run", 2, *PLAIN)
    c7_first = llm.Conversion(PATH_TEXT, 7, "Run", 1, "char *", "int *")
    e7, e9 = refusal(7, "Run", 2, *PLAIN), refusal(9, "Run", 2, *PLAIN)
    e7_first = refusal(7, "Run", 1, "char *", "int *")
    syntax = f"{PATH_TEXT}(7) : {SYNTAX}"
    cases = [
        ("an error that stays", [c7], e7, e7, [c7]),
        ("an error that is gone", [c7], e7, "", []),
        ("an error on another line", [c7], e7, "src/foo.c(20) : error C2065: 'x' : undeclared identifier", []),
        ("a new syntax error on the line", [c7], e7, syntax, [c7]),
        ("a new undeclared name on the line", [c7], e7, "src/foo.c(7) : error C2065: 'Foo' : undeclared identifier",
         [c7]),
        ("an error that the first one hid", [c7], e7,
         "src/foo.c(7) : error C2664: 'Bar' : cannot convert parameter 1 from 'long' to 'char'", []),
        ("a syntax error that was there before", [c7], e7 + "\n" + syntax, syntax, []),
        ("a syntax error on another line", [c7], e7, f"{PATH_TEXT}(8) : {SYNTAX}", []),
        ("a syntax error in another file", [c7], e7, f"src/other.c(7) : {SYNTAX}", []),
        ("one of two that stays", [c7, c9], e7 + "\n" + e9, e9, [c9]),
        ("two that stay", [c9, c7], e7 + "\n" + e9, e9 + "\n" + e7, [c9, c7]),
        ("two parameters of one line, one stays", [c7, c7_first], e7 + "\n" + e7_first, e7_first, [c7_first]),
        ("nothing applied", [], e7, e7, []),
    ]
    failures = []
    for case, applied, text, retry, wanted in cases:
        found = llm.cast_failed(applied, text, retry)
        if found != wanted:
            failures.append(f"cast_failed gives {found} for {case}, not {wanted}")
    return failures


def fake_rebuild(results):
    """(a stand-in for solve_function's rebuild that gives each of RESULTS in turn, the list of its calls)."""
    calls = []

    def rebuild(decls, func):
        calls.append((decls, list(func)))
        return results[len(calls) - 1] if len(calls) <= len(results) else ("", None, "")

    return rebuild, calls


def check_cast_round() -> list[str]:
    """cast_round builds once with all the casts and gives the build back when no cast failed. A cast that failed goes
    into REFUSED and the round builds once more without it, so the right casts stay. A second round of failures, or
    nothing left to cast, gives None. A Conversion that REFUSED holds gets no cast."""
    body = ["\tp = q;", "\tRun(1, q);"]
    func = function_of(body)
    attempt = "\n".join(func)
    error_a, error_b = (refusal(func.index(line) + 1, name, param, *PLAIN) for line, name, param in
                        ((body[0], "=", None), (body[1], "Run", 2)))
    both = error_a + "\n" + error_b
    conv_a, conv_b = llm.conversions(both)
    syntax_b = f"{PATH_TEXT}({conv_b.line}) : {SYNTAX}"
    int_to_short = refusal(conv_a.line, "=", None, "int", "short")
    plain_a, plain_b = body
    cast_a, cast_b = "\tp = (char *)q;", "\tRun(1, (char *)q);"
    decls = ["extern int Foo;"]
    # (case, build output, REFUSED before, the builds, the result wanted, the casts of each build, REFUSED after)
    cases = [
        ("no pointer conversion", int_to_short, [], [], None, [], []),
        ("casts that fix their errors", both, [], [("built", 100.0, "")], ("built", 100.0, "", [cast_a, cast_b]),
         [[cast_a, cast_b]], []),
        ("one cast that fails", both, [], [("one", None, error_a), ("two", 88.0, "")],
         ("two", 88.0, "", [plain_a, cast_b]), [[cast_a, cast_b], [plain_a, cast_b]], [conv_a]),
        ("a second build that fails too", both, [], [("one", None, error_a), ("two", None, syntax_b)], None,
         [[cast_a, cast_b], [plain_a, cast_b]], [conv_a, conv_b]),
        ("casts that all fail", both, [], [("one", None, both)], None, [[cast_a, cast_b]], [conv_a, conv_b]),
        ("a Conversion refused before", both, [conv_a], [("one", 100.0, "")], ("one", 100.0, "", [plain_a, cast_b]),
         [[plain_a, cast_b]], [conv_a]),
        ("only refused Conversions", both, [conv_a, conv_b], [], None, [], [conv_a, conv_b]),
    ]
    failures = []
    for case, text, refused_before, builds, wanted_result, wanted_calls, refused_after in cases:
        rebuild, calls = fake_rebuild(builds)
        refused = set(refused_before)
        found = llm.cast_round(rebuild, decls, func, attempt, text, PATH, ADDRESS, {}, refused)
        wanted = None if wanted_result is None else (*wanted_result[:3], [*func[:3], *wanted_result[3], func[-1]])
        found_calls = [cast[3:-1] if given == decls else None for given, cast in calls]
        if found != wanted or found_calls != wanted_calls or refused != set(refused_after):
            failures.append(f"cast_round gives {found}, builds of {found_calls} and {len(refused)} refused for {case}, "
                            f"not {wanted}, {wanted_calls} and {len(refused_after)}")
    return failures


def check_cast_pointers() -> list[str]:
    """cast_pointers runs cast_round again on each build it keeps, up to CAST_ROUNDS times, and gives the last kept
    build. It stops when a round gives None. A Conversion that failed in one round stays refused in the next. When
    no round keeps a build, the arguments come back and the percent is None."""
    def chain(count, done):
        """The body of COUNT assignments of which the first DONE have a cast."""
        return [f"\tp{i} = " + ("(char *)" if i < done else "") + f"q{i};" for i in range(count)]

    def error(count, index):
        return refusal(function_of(chain(count, 0)).index(chain(count, 0)[index]) + 1, "=", None, *PLAIN)

    def built(body, percent, output):
        return "\n".join(function_of(body)), percent, output

    rounds = llm.CAST_ROUNDS
    plain = chain(rounds + 1, 0)
    one = chain(1, 0)
    three = ["\tpa = qa;", "\tpb = qb;", "\tpc = qc;"]
    cast_a, cast_b, cast_c = "\tpa = (char *)qa;", "\tpb = (char *)qb;", "\tpc = (char *)qc;"
    lines_three = function_of(three)
    error_b, error_c = (refusal(lines_three.index(line) + 1, "=", None, *PLAIN) for line in three[1:])
    error_a = refusal(lines_three.index(three[0]) + 1, "=", None, *PLAIN)
    short = refusal(2, "=", None, "int", "short")
    # (case, body, build output, the builds as (casts, percent, output), the casts of the result, its percent, output)
    cases = [
        ("no pointer conversion", one, short, [], one, None, short),
        ("two rounds that end clean", chain(2, 0), error(2, 0),
         [(chain(2, 1), None, error(2, 1)), (chain(2, 2), 95.5, "")], chain(2, 2), 95.5, ""),
        ("more rounds than CAST_ROUNDS", plain, error(rounds + 1, 0),
         [(chain(rounds + 1, k), None, error(rounds + 1, k)) for k in range(1, rounds + 1)],
         chain(rounds + 1, rounds), None, error(rounds + 1, rounds)),
        ("a cast that never helps", one, error(1, 0), [(chain(1, 1), None, error(1, 0))], one, None, error(1, 0)),
        ("a refused Conversion in the rounds after", three, error_a + "\n" + error_b,
         [([cast_a, cast_b, three[2]], None, error_b), ([cast_a, three[1], three[2]], None, error_b + "\n" + error_c),
          ([cast_a, three[1], cast_c], None, error_b)],
         [cast_a, three[1], cast_c], None, error_b),
    ]
    failures = []
    for case, body, text, builds, wanted_body, wanted_percent, wanted_output in cases:
        func = function_of(body)
        rebuild, calls = fake_rebuild([built(*item) for item in builds])
        found = llm.cast_pointers(rebuild, ["extern int Foo;"], func, "\n".join(func), text, PATH, ADDRESS, {})
        wanted_func = function_of(wanted_body)
        wanted = ("\n".join(wanted_func), wanted_percent, wanted_output, wanted_func)
        wanted_calls = [function_of(casts) for casts, _, _ in builds]
        if found != wanted or [cast for _, cast in calls] != wanted_calls:
            failures.append(f"cast_pointers gives {found[1:3]}, {len(calls)} builds and the lines {found[3][3:-1]} for "
                            f"{case}, not {wanted[1:3]}, {len(builds)} builds and the lines {wanted_body}")
    return failures


def run() -> list[str]:
    """Run every check and give all the failures."""
    failures = []
    for check in (check_conversions, check_type_kind, check_pointer_conversion, check_cast_line, check_add_casts,
                  check_cast_failed, check_cast_round, check_cast_pointers):
        failures += check()
    return failures
