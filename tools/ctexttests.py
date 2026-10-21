"""Checks for the C text scanners in tools/cfix.py and for line_declarations in tools/llm.py: they read one line or
one function of C by brackets and commas, and must not count a bracket, comma or = inside a string, a character or
a comment."""

import cfix
import llm

Pointee = cfix.Pointee


def check_blank_literals() -> list[str]:
    """Each string, character and comment becomes filler of the same length: `_` for a string or character, blanks for
    a comment. Text outside them stays. A quote or comment mark inside another literal does not start a new one, and
    an escaped quote does not end a string."""
    cases = [("", ""),
             ("f(a, b);", "f(a, b);"),
             ('f("a,)", 1);', 'f(_____, 1);'),
             ("f(')', 2);", "f(___, 2);"),
             ("x = 1; // (a, b", "x = 1; " + " " * 8),
             ("x = 1; /* ) */ y = 2;", "x = 1;         y = 2;"),
             ('s = "a \\" ) b";', "s = " + "_" * 10 + ";"),
             ('s = "// no"; // yes', 's = _______;       '),
             ("c = '\\''; d = 1;", "c = ____; d = 1;"),
             ('f("(", ")", \'(\');', "f(___, ___, ___);")]
    failures = []
    for line, wanted in cases:
        found = cfix.blank_literals(line)
        if found != wanted:
            failures.append(f"blank_literals gives {found!r} for {line!r}, not {wanted!r}")
    return failures


def check_bracket_end() -> list[str]:
    """The index of the bracket that closes the one at START. Round and square brackets nest. None when the bracket
    never closes, or when START is past the last character."""
    cases = [("f(a)", 1, 3),
             ("f(g(a), h(b)) + 1", 1, 12),
             ("f(g(a), h(b))", 3, 5),
             ("a[i + (j)] = 1;", 1, 9),
             ("f((a)", 1, None),
             ("f(a, g(b)", 1, None),
             ("f(a", 1, None),
             ("f(", 1, None),
             ("f()", 1, 2),
             ("", 0, None)]
    failures = []
    for line, start, wanted in cases:
        found = cfix.bracket_end(line, start)
        if found != wanted:
            failures.append(f"bracket_end gives {found} for {line!r} at {start}, not {wanted}")
    return failures


def check_bracket_start() -> list[str]:
    """The index of the bracket that the one at CLOSE closes. Round and square brackets nest. None when no bracket
    opens it."""
    cases = [("f(a)", 3, 1),
             ("f(g(a), h(b))", 12, 1),
             ("f(g(a), h(b))", 5, 3),
             ("a[i + (j)] = 1;", 9, 1),
             ("a)", 1, None),
             ("f(a))", 4, None),
             ("f(a)) + (b)", 4, None),
             (")", 0, None),
             ("()", 1, 0)]
    failures = []
    for line, close, wanted in cases:
        found = cfix.bracket_start(line, close)
        if found != wanted:
            failures.append(f"bracket_start gives {found} for {line!r} at {close}, not {wanted}")
    return failures


def check_group_at_end() -> list[str]:
    """The group in parentheses that the text ends with, as (index of its `(`, the text inside). The group is the
    last one when the text holds several. None when the text does not end with `)`, or when that `)` closes nothing."""
    cases = [("f(a, (b))", (1, "a, (b)")),
             ("(x)", (0, "x")),
             ("f(a)(b)", (4, "b")),
             ("()", (0, "")),
             ("(int *)", (0, "int *")),
             ("a", None),
             ("", None),
             ("f(a) + 1", None),
             ("a[1]", None),
             ("a)", None),
             ("f(a))", None)]
    failures = []
    for text, wanted in cases:
        found = cfix.group_at_end(text)
        if found != wanted:
            failures.append(f"group_at_end gives {found} for {text!r}, not {wanted}")
    return failures


def check_expression_end() -> list[str]:
    """The index where the expression that starts at START ends: a `,` or `;` outside brackets, or the bracket that
    closes the one around it. A comma inside brackets or braces does not end it. None when the line ends first."""
    cases = [("a, b", 0, 1),
             ("a; b", 0, 1),
             ("f(a, b), c", 0, 7),
             ("a[i, j], b", 0, 7),
             ("{1, 2}, 3", 0, 6),
             ("f(a, b)", 2, 3),
             ("a + b)", 2, 5),
             ("f(a + g(b))", 2, 10),
             ("f(a, g(b), c)", 7, 8),
             ("a ] b", 0, 2),
             ("a + b", 0, None),
             ("(a, b)", 0, None),
             ("f(a, ", 4, None),
             ("a, b", 4, None),
             ("", 0, None),
             ("f(____, 1)", 2, 6)]
    failures = []
    for blanked, start, wanted in cases:
        found = cfix.expression_end(blanked, start)
        if found != wanted:
            failures.append(f"expression_end gives {found} for {blanked!r} from {start}, not {wanted}")
    return failures


def check_trimmed() -> list[str]:
    """START and END moved in over the blanks at both ends. Nothing changes when there is none. A range of nothing
    gives an empty range: START equals END."""
    cases = [("  ab  ", 0, 6, (2, 4)),
             ("x =  a + b ;", 3, 11, (5, 10)),
             ("ab", 0, 2, (0, 2)),
             ("a b", 0, 3, (0, 3)),
             ("\ta\t", 0, 3, (1, 2)),
             ("  ab  ", 1, 5, (2, 4)),
             ("ab", 1, 1, (1, 1)),
             ("", 0, 0, (0, 0))]
    failures = []
    for blanked, start, end, wanted in cases:
        found = cfix.trimmed(blanked, start, end)
        if found != wanted:
            failures.append(f"trimmed gives {found} for {blanked!r} from {start} to {end}, not {wanted}")
    return failures


def check_value_span() -> list[str]:
    """The span of the one expression that a C2440 on NAME converts: after the one = (NAME is '=' or 'initializing'),
    or after the one return, up to the `;` or `,`, without blanks. None when the line holds more than one = or return,
    when there is none (== <= += do not count), when the expression has no end in the line, or when it is a brace
    list or empty."""
    cases = [("x = 5;", "=", (4, 5)),
             ("int x =  a + b ;", "initializing", (9, 14)),
             ("return x + 1;", "return", (7, 12)),
             ("return (a, b);", "return", (7, 13)),
             ("x = a, b;", "=", (4, 5)),
             ("x = (a, b);", "=", (4, 10)),
             ("x = y == z;", "=", (4, 10)),
             ("x = y <= z;", "=", (4, 10)),
             ("x = _____;", "=", (4, 9)),
             ("int a = 1, b = 2;", "initializing", None),
             ("x = y = z;", "=", None),
             ("return a; return b;", "return", None),
             ("x += 1;", "=", None),
             ("x == 1;", "=", None),
             ("x = f(a,", "=", None),
             ("x = a +", "=", None),
             ("return x", "return", None),
             ("int a[2] = {1, 2};", "initializing", None),
             ("return;", "return", None),
             ("", "=", None)]
    failures = []
    for blanked, name, wanted in cases:
        found = cfix.value_span(blanked, name)
        if found != wanted:
            failures.append(f"value_span gives {found} for {blanked!r} on {name}, not {wanted}")
    return failures


def check_argument_spans() -> list[str]:
    """The span of each argument of the call whose bracket opens just before START, without blanks. A comma inside
    a nested call does not split. The spans stop at the bracket that closes the call. None when the call goes on in
    the next line, or a `;` ends an argument."""
    cases = [("f(a, b)", 2, [(2, 3), (5, 6)]),
             ("f( a ,  b )", 2, [(3, 4), (8, 9)]),
             ("f(g(a, b), c[1, 2], d)", 2, [(2, 9), (11, 18), (20, 21)]),
             ("f(a)(b)", 2, [(2, 3)]),
             ("x = f(a, b) + 1;", 6, [(6, 7), (9, 10)]),
             ("f(____, 1)", 2, [(2, 6), (8, 9)]),
             ("f(a, b", 2, None),
             ("f(a,", 2, None),
             ("f(a; b)", 2, None),
             ("f(a, g(b)", 2, None)]
    failures = []
    for blanked, start, wanted in cases:
        found = cfix.argument_spans(blanked, start)
        if found != wanted:
            failures.append(f"argument_spans gives {found} for {blanked!r} from {start}, not {wanted}")
    return failures


def check_argument_span() -> list[str]:
    """The span of argument PARAM (from 1) of the one call to NAME. None when the line calls NAME more than once or
    not at all (a longer name or a name inside a string does not count), when PARAM is past the last argument, when
    that argument is empty, or when the call goes on in the next line."""
    cases = [("Foo(a, b)", "Foo", 1, (4, 5)),
             ("Foo(a, b)", "Foo", 2, (7, 8)),
             ("Foo (a, b)", "Foo", 2, (8, 9)),
             ("x = Foo(g(a, b), c);", "Foo", 2, (17, 18)),
             ("x = Foo(g(a, b), c);", "Foo", 1, (8, 15)),
             ("Bar(Foo(a), b)", "Bar", 2, (12, 13)),
             ("xFoo(a); Foo(b);", "Foo", 1, (13, 14)),
             ("Foo(a, b)", "Foo", 3, None),
             ("Foo()", "Foo", 1, None),
             ("Foo(a,, b)", "Foo", 2, None),
             ("Foo(a); Foo(b);", "Foo", 1, None),
             ("Foo(Foo(a))", "Foo", 1, None),
             ("FooBar(a)", "Foo", 1, None),
             ("Bar(a)", "Foo", 1, None),
             ("Foo(a,", "Foo", 2, None),
             ("Foo", "Foo", 1, None),
             ("f(_____, Foo(a))", "Foo", 1, (13, 14))]
    failures = []
    for blanked, name, param, wanted in cases:
        found = cfix.argument_span(blanked, name, param)
        if found != wanted:
            failures.append(f"argument_span gives {found} for {blanked!r} on {name} {param}, not {wanted}")
    return failures


def check_continued_lines() -> list[str]:
    """The indexes of the lines that continue a statement from the line before, or from an open bracket. A line that
    ends with `;`, `{`, `}`, `:` or `)` ends a statement, so does `else` or `do`. A bracket, `;` or operator inside a
    string, a character or a comment does not count. A blank line, a comment line and a # line change nothing."""
    cases = [(["void Foo()", "{", "int a;", "a = 1;", "}"], set()),
             (["x = foo(a,", "b);", "y = 2;"], {1}),
             (["x = foo(a,", "b,", "c);"], {1, 2}),
             (["f(a,", "g(b)", ", c);", "h();"], {1, 2}),
             (["x = a +", "b;", "y = 1;"], {1}),
             (["if (a)", "b = 1;"], set()),
             (["else", "a = 1;", "do", "b = 2;"], set()),
             (["case 1:", "a = 1;"], set()),
             (["x = a +", "", "b;"], {2}),
             (["x = a +", "// note (", "b;"], {2}),
             (["x = a +", "#if 0", "b;"], {2}),
             (['puts("(");', "x = 1;"], set()),
             (["f(')');", "x = 1;"], set()),
             (["x = 1; // (", "y = 2;"], set()),
             (["x = 1; /* + */", "y = 2;"], set()),
             (["x = a; // +", "y = 2;"], set()),
             (["x = a /* ; */", "+ b;"], {1}),
             (["a[i,", "j] = 1;"], {1}),
             (["a[g(1)", "+ 2] = 3;"], {1}),
             (["for (i = 0;", "i < n;", "i++)", "m++;"], {1, 2}),
             ([], set())]
    failures = []
    for func, wanted in cases:
        found = cfix.continued_lines(func)
        if found != wanted:
            failures.append(f"continued_lines gives {sorted(found)} for {func}, not {sorted(wanted)}")
    return failures


def check_is_cast() -> list[str]:
    """The text between parentheses is a type when it is a pointer type (a name and `*`s), or a name that starts with
    a C type word. A bare name is an expression. Any other text is none."""
    cases = [("int", True),
             ("unsigned char", True),
             ("struct Bar", True),
             ("const Foo", True),
             ("Foo *", True),
             ("Foo*", True),
             ("Foo **", True),
             ("const Foo *", True),
             ("unsigned int *", True),
             (" int ", True),
             ("Foo", False),
             ("Foo Bar", False),
             ("a + b", False),
             ("x*y", False),
             ("*p", False),
             ("1", False),
             ("f(x)", False),
             ("", False)]
    failures = []
    for group, wanted in cases:
        found = cfix.is_cast(group)
        if found != wanted:
            failures.append(f"is_cast gives {found} for {group!r}, not {wanted}")
    return failures


def check_plain_type() -> list[str]:
    """The type name without `const`, `volatile`, `struct`, `union`, `enum` and `*`. Other words stay, and a word that
    only starts with one of those does not go."""
    cases = [("const struct Foo *", "Foo"),
             ("volatile int", "int"),
             ("enum Bar", "Bar"),
             ("union Baz const *", "Baz"),
             ("Foo **", "Foo"),
             ("unsigned char", "unsigned char"),
             ("constant_pad", "constant_pad"),
             ("structure", "structure"),
             ("struct", ""),
             ("", "")]
    failures = []
    for text, wanted in cases:
        found = cfix.plain_type(text)
        if found != wanted:
            failures.append(f"plain_type gives {found!r} for {text!r}, not {wanted!r}")
    return failures


def check_declared_type() -> list[str]:
    """(name, Pointee(type name, pointer levels, array dimensions)) of the declaration that the statement starts with,
    without extern, static, const, struct and the like. None when it starts with return, else, goto, case, delete, new
    or typedef, or with no declaration, such as an assignment or a call."""
    cases = [("int x;", ("x", Pointee("int", 0, 0))),
             ("    unsigned char *p = q;", ("p", Pointee("unsigned char", 1, 0))),
             ("const struct Foo **pp;", ("pp", Pointee("Foo", 2, 0))),
             ("struct Foo work;", ("work", Pointee("Foo", 0, 0))),
             ("int pad[4][2];", ("pad", Pointee("int", 0, 2))),
             ("Foo *tab[3];", ("tab", Pointee("Foo", 1, 1))),
             ("static int n = 0;", ("n", Pointee("int", 0, 0))),
             ("extern short DAT_00501000;", ("DAT_00501000", Pointee("short", 0, 0))),
             ("int *const p;", ("p", Pointee("int", 1, 0))),
             ("int a, b;", ("a", Pointee("int", 0, 0))),
             ("int x", ("x", Pointee("int", 0, 0))),
             ("Foo *task)", ("task", Pointee("Foo", 1, 0))),
             ("return x;", None),
             ("else x;", None),
             ("goto done;", None),
             ("typedef int T;", None),
             ("x = 5;", None),
             ("FUN_00401000(a);", None),
             ("void Run(int a)", None),
             ("", None)]
    failures = []
    for statement, wanted in cases:
        found = cfix.declared_type(statement)
        if found != wanted:
            failures.append(f"declared_type gives {found} for {statement!r}, not {wanted}")
    return failures


def check_line_declarations() -> list[str]:
    """(name, declaration) of each declaration that the line holds whole, a function with its parameter names left out.
    A declaration over two lines, a static function, a call, a comment and an empty line have none."""
    cases = [("int Bar(int a);", [("Bar", "int Bar(int)")]),
             ("void Foo(struct Bar *b, int c);", [("Foo", "void Foo(struct Bar *, int)")]),
             ("int Foo(void);", [("Foo", "int Foo(void)")]),
             ("extern int DAT_00501000[3];", [("DAT_00501000", "int DAT_00501000[3]")]),
             ("extern int work;", [("work", "int work")]),
             ("void Run(int a,", []),
             ("int\n", []),
             ("static int Foo(int);", []),
             ("Foo(a);", []),
             ("// int Bar(int);", []),
             ("", [])]
    failures = []
    for line, wanted in cases:
        found = llm.line_declarations(line)
        if found != wanted:
            failures.append(f"line_declarations gives {found} for {line!r}, not {wanted}")
    return failures


def check_cast_text() -> list[str]:
    """EXPRESSION cast to TARGET: `(TARGET)expression`, with the expression in brackets when it is more than one
    operand. A name, a number, a member, an index, a call with flat arguments and a prefix operator on one are one
    operand. A sum, a product, a condition and a call after an operator are more."""
    cases = [("a", "int *", "(int *)a"),
             ("1.5", "float", "(float)1.5"),
             ("task->work", "Foo *", "(Foo *)task->work"),
             ("work.pad", "short", "(short)work.pad"),
             ("pad[i + 1]", "char", "(char)pad[i + 1]"),
             ("Run(a, b)", "Foo *", "(Foo *)Run(a, b)"),
             ("&work", "void *", "(void *)&work"),
             ("*p", "int", "(int)*p"),
             ("-a", "int", "(int)-a"),
             ("a + b", "int *", "(int *)(a + b)"),
             ("a * b", "int", "(int)(a * b)"),
             ("a ? b : c", "int", "(int)(a ? b : c)"),
             ("pad[i] + 1", "char", "(char)(pad[i] + 1)"),
             ("a, b", "int", "(int)(a, b)")]
    failures = []
    for expression, target, wanted in cases:
        found = cfix.cast_text(expression, target)
        if found != wanted:
            failures.append(f"cast_text gives {found!r} for {expression!r} to {target!r}, not {wanted!r}")
    return failures


def check_tagged() -> list[str]:
    """The type name with struct, union or enum before each tag that KINDS holds, also inside a pointer or a function
    pointer type. A tag that already has a keyword before it, a word that is no tag, and a word that only contains a
    tag stay as they are."""
    kinds = {"Foo": "struct", "Bar": "union", "Baz": "enum"}
    cases = [("Foo *", "struct Foo *"),
             ("const Bar", "const union Bar"),
             ("void (*)(Foo *, Baz)", "void (*)(struct Foo *, enum Baz)"),
             ("Foo, Foo", "struct Foo, struct Foo"),
             ("struct Foo *", "struct Foo *"),
             ("union Bar", "union Bar"),
             ("enum Baz", "enum Baz"),
             ("unsigned int", "unsigned int"),
             ("FooBar *", "FooBar *"),
             ("Foo2", "Foo2"),
             ("", "")]
    failures = []
    for name, wanted in cases:
        found = cfix.tagged(name, kinds)
        if found != wanted:
            failures.append(f"tagged gives {found!r} for {name!r}, not {wanted!r}")
    if cfix.tagged("Foo *", {}) != "Foo *":
        failures.append(f"tagged gives {cfix.tagged('Foo *', {})!r} for 'Foo *' with no kinds, not 'Foo *'")
    return failures


def run() -> list[str]:
    """Every check of this module, in order."""
    failures = []
    for check in (check_blank_literals, check_bracket_end, check_bracket_start, check_group_at_end,
                  check_expression_end, check_trimmed, check_value_span, check_argument_spans, check_argument_span,
                  check_continued_lines, check_is_cast, check_plain_type, check_declared_type,
                  check_line_declarations, check_cast_text, check_tagged):
        failures += check()
    return failures
