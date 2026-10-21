"""Tests of the byte-offset repair in tools/llm.py and tools/cfix.py: the helpers that put `(char *)` on a pointer to
a type of unknown size (error C2036) so that `+`, `-` and `[]` on it count bytes.

run() returns the failures as "<helper> gives <found> for <input>, not <wanted>". The types headers and globals
headers that the helpers read are written in a throwaway folder inside each check.
"""

import tempfile
from pathlib import Path

import cfix
import llm
import names
import project

P = cfix.Pointee
TARGET = project.game_config().target

# Foo holds every shape of member. Bar points back to Foo. Un is a top-level union. Anon has an anonymous union, which
# closes with `} ;`: a closing `};` would end the struct for struct_members.
TYPES_TEXT = """struct Foo {
    int a;
    struct Bar *next;
    struct Bar link;
    struct Bar list[4];
    float grid[2][3];
    union {
        int i;
        struct Bar b;
    } work;
    struct {
        short s;
    } inner[2];
    char name[8];
};
static_assert(sizeof(Foo) == 0x40, "sizeof Foo");

struct Bar {
    int x;
    struct Foo *owner;
};

union Un {
    int w;
    float f;
};

struct Anon {
    int first;
    union {
        int u1;
        float u2;
    } ;
    int last;
};
"""
INT = P("int", 0, 0)
FOO_PTR = P("Foo", 1, 0)
BAR_PTR = P("Bar", 1, 0)
# the names that a function under repair can use
SCOPE = {"tp": FOO_PTR, "bp": BAR_PTR, "pp": P("Foo", 2, 0), "g": P("Foo", 0, 0), "arr": P("Bar", 0, 3), "n": INT}
SPELLINGS = {"Foo": "struct Foo", "Bar": "struct Bar"}


def fixture_types(folder: str) -> names.Types:
    """The types header TYPES_TEXT, written in FOLDER and read by names.Types."""
    path = Path(folder) / "types.h"
    path.write_text(TYPES_TEXT, encoding="utf-8")
    return names.Types(path)


def failure(helper: str, found, given, wanted) -> str:
    return f"{helper} gives {found!r} for {given!r}, not {wanted!r}"


def check_operand_ends() -> list[str]:
    """binary_operand says whether the text before an operator ends in an operand: a name, a number, a call, an index
    or a group. A cast, an operator, a comma, a keyword and nothing do not. opens_call says whether a `(` after the
    text starts a call's arguments: after a name, a call, an index or a group, but not after a keyword such as `if`
    or after a cast."""
    binary = [("a", True), ("  a  ", True), ("_x1", True), ("a[1]", True), ("f(x)", True), ("(a)", True),
              ("(Foo)", True), ("x)", True), ("", False), ("   ", False), ("a +", False), ("a,", False),
              ("return", False), ("return ", False), ("(int)", False), ("(char *)", False),
              ("(unsigned char)", False), ("x = (struct Foo *)", False)]
    calls = [("f", True), ("  g  ", True), ("a->f", True), ("endif", True), ("(a)", True), ("a[0]", True),
             ("f(x)", True), ("", False), ("x + ", False), ("(int *)", False), ("(struct Foo *)", False)]
    calls += [(word, False) for word in ("if", "while", "for", "switch", "return", "else", "case")]
    failures = []
    for text, wanted in binary:
        found = cfix.binary_operand(text)
        if found is not wanted:
            failures.append(failure("binary_operand", found, text, wanted))
    for text, wanted in calls:
        found = cfix.opens_call(text)
        if found is not wanted:
            failures.append(failure("opens_call", found, text, wanted))
    return failures


def check_binary_sign() -> list[str]:
    """binary_sign says whether the `+` or `-` at an index adds or subtracts. It does not in `++`, `--`, `+=`, `-=`
    and `->`, and not as a sign: at the start, after an operator, an opening bracket, a cast or `return`. It does
    after a name, an index, a group and a `*` operand."""
    cases = [("a + b", 2, True), ("a - b", 2, True), ("a[1] - 1", 5, True), ("*p - 1", 3, True), ("(x)-1", 3, True),
             ("a++", 1, False), ("a++", 2, False), ("a--", 1, False), ("a += 1", 2, False), ("a -= 1", 2, False),
             ("a->b", 2, False), ("-a", 0, False), ("x = -a", 4, False), ("f(-a)", 2, False),
             ("(int)-a", 5, False), ("(char)+x", 6, False), ("return -a", 7, False), ("a - -b", 4, False),
             ("a - -b", 2, True)]
    failures = []
    for line, i, wanted in cases:
        found = cfix.binary_sign(line, i)
        if found is not wanted:
            failures.append(failure("binary_sign", found, (line, i), wanted))
    return failures


def check_operand_start() -> list[str]:
    """operand_start finds where the operand that ends at an index starts: a name, call, index or member chain, a group
    or a number. With PREFIX it takes the unary `*`, `&` and `!` and the casts in front of it, but not a `*` that is
    a product, and not after `return`. It gives None when the text before the end is not an operand."""
    # (the text before ` + 1`, prefix, the operand that ends there)
    cases = [("x = p", True, "p"), ("x = a->b", True, "a->b"), ("x = a.b[2]", True, "a.b[2]"),
             ("x = a[1]->b[2]", True, "a[1]->b[2]"), ("x = f(x, y)", True, "f(x, y)"),
             ("x = f(a)[2]", True, "f(a)[2]"), ("x = g(1)(2)", True, "g(1)(2)"), ("x = (a + b)", True, "(a + b)"),
             ("x = (a + b)->c", True, "(a + b)->c"), ("x = *p", True, "*p"), ("x = *p", False, "p"),
             ("x * *p", True, "*p"), ("x = &a.b", True, "&a.b"), ("x = !p", True, "!p"),
             ("x = (int *)p", True, "(int *)p"), ("x = (int *)p", False, "p"),
             ("x + (int *)p", True, "(int *)p"), ("return *p", True, "*p"),
             ("x =", True, None), ("x = a->", True, None), ("x = a[", True, None), ("x = a++", True, None)]
    failures = []
    for before, prefix, wanted in cases:
        line = before + " + 1"
        start = cfix.operand_start(line, len(before), prefix)
        found = None if start is None else line[start:len(before)]
        if found != wanted:
            failures.append(failure("operand_start", found, (line, len(before), prefix), wanted))
    return failures


def check_chain_end() -> list[str]:
    """chain_end gives the index where the `+` and `-` terms that go on from the first `+` end: at the first `)`,
    `]`, `,` or `;` outside brackets, or at an operator that binds weaker than `+` (comparisons, shifts, `&`, `|`,
    `?`, `=` and the like). A product, a call with commas inside, a `->` and a sign stay in. Trailing blanks do not
    count, and the end of the line ends it too."""
    cases = [("x = p + 4;", "x = p + 4"), ("x = p + 4", "x = p + 4"), ("x = p + 4   ", "x = p + 4"),
             ("x = p + 4 ;", "x = p + 4"), ("f(p + 4, 5)", "f(p + 4"), ("f(p + 4)", "f(p + 4"),
             ("a[p + 4]", "a[p + 4"), ("x = p + 4 - 2 + q;", "x = p + 4 - 2 + q"),
             ("x = p + f(a, b) - 1;", "x = p + f(a, b) - 1"), ("x = p + a[1, 2] + 3;", "x = p + a[1, 2] + 3"),
             ("x = p + a->b + 3;", "x = p + a->b + 3"), ("x = p + a * 2 / 3;", "x = p + a * 2 / 3"),
             ("x = p + -4;", "x = p + -4"), ("x = p + 4 == q;", "x = p + 4"), ("x = p + q != r;", "x = p + q"),
             ("x = p + 4 < q;", "x = p + 4"), ("x = p + 4 >> 1;", "x = p + 4"), ("x = p + 4 & m;", "x = p + 4"),
             ("if (p + 4 && q)", "if (p + 4"), ("x = p + 4 ? a : b;", "x = p + 4"), ("x = {p + 4};", "x = {p + 4")]
    failures = []
    for line, wanted in cases:
        i = line.index("+")
        found = line[:cfix.chain_end(line, i)]
        if found != wanted:
            failures.append(failure("chain_end", found, (line, i), wanted))
    return failures


def check_under_cast() -> list[str]:
    """under_cast says whether the text from START to END is all that a cast `(type)(...)` holds: the cast's group
    must open right before START and close right after END. A call, a plain group, text in front of START inside
    the group, text behind END inside it, or an unclosed group is not a cast."""
    cases = [("x = (int *)(p + 4);", True), ("x = (int)(p + 4);", True), ("x = (struct Foo *)(p + 4);", True),
             ("x = (int *) ( p + 4 );", True), ("x = (int *)(p + 4) + 1;", True), ("x = ((int *)(p + 4));", True),
             ("x = (p + 4);", False), ("x = f(p + 4);", False), ("x = (int *)(p + 4 + 1);", False),
             ("x = (int *)(q + p + 4);", False), ("x = (int *)(p + 4;", False), ("p + 4", False)]
    failures = []
    for line, wanted in cases:
        start = line.index("p + 4")
        found = cfix.under_cast(line, start, start + len("p + 4"))
        if found is not wanted:
            failures.append(failure("under_cast", found, (line, start, start + 5), wanted))
    return failures


def check_unknown_size_pattern() -> list[str]:
    """UNKNOWN_SIZE finds the C2036 lines of a build and captures (file, line, type without its `*`). The file may
    hold spaces and parentheses, as in `Program Files (x86)`. Other error codes and warnings do not match."""
    line = "x.c(12) : error C2036: 'struct Foo *' : unknown size"
    spaced = "D:\\Program Files (x86)\\x.c"
    cases = [(line, [("x.c", "12", "struct Foo")]),
             ("cl\r\n" + line + "\r\ny.c(3) : error C2036: 'struct Bar *' : unknown size\r\n",
              [("x.c", "12", "struct Foo"), ("y.c", "3", "struct Bar")]),
             (line.replace("x.c", spaced), [(spaced, "12", "struct Foo")]),
             (line.replace("struct Foo", "const struct Foo"), [("x.c", "12", "const struct Foo")]),
             (line.replace("Foo *", "Foo  *"), [("x.c", "12", "struct Foo")]),
             (line.replace("Foo *", "Foo **"), [("x.c", "12", "struct Foo *")]),
             (line.replace("C2036", "C2037"), []), (line.replace("error", "warning"), []),
             (line.replace(" : unknown size", " : bad"), []), ("", [])]
    failures = []
    for text, wanted in cases:
        found = llm.UNKNOWN_SIZE.findall(text)
        if found != wanted:
            failures.append(failure("UNKNOWN_SIZE.findall", found, text, wanted))
    return failures


def check_struct_members() -> list[str]:
    """struct_members gives {owner: {member: Pointee}} for a struct or union: the owner is its name, or NAME.#N for the
    Nth union or struct inside it, and a member of such a type has that owner as the name of its type. Pointers
    count stars, arrays count dimensions, and the static_assert after the block is no member. An anonymous union
    gives its members to the struct around it."""
    foo = {"Foo": {"a": INT, "next": BAR_PTR, "link": P("Bar", 0, 0), "list": P("Bar", 0, 1), "grid": P("float", 0, 2),
                   "work": P("Foo.#1", 0, 0), "inner": P("Foo.#2", 0, 1), "name": P("char", 0, 1)},
           "Foo.#1": {"i": INT, "b": P("Bar", 0, 0)}, "Foo.#2": {"s": P("short", 0, 0)}}
    cases = [("Foo", foo), ("Bar", {"Bar": {"x": INT, "owner": FOO_PTR}}),
             ("Un", {"Un": {"w": INT, "f": P("float", 0, 0)}}),
             ("Anon", {"Anon": {"first": INT, "u1": INT, "u2": P("float", 0, 0), "last": INT},
                       "Anon.#1": {"u1": INT, "u2": P("float", 0, 0)}})]
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        types = fixture_types(folder)
        for name, wanted in cases:
            found = cfix.struct_members(types, name)
            if found != wanted:
                failures.append(failure("struct_members", found, name, wanted))
    return failures


def check_member_type() -> list[str]:
    """member_type gives the Pointee of a member. The owner is a struct pointer for `->` and a struct for `.`; a
    pointer to pointer, an array, the wrong access, a name that is no struct and a member that does not exist give
    None. A union or struct inside a struct is an owner too."""
    cases = [(FOO_PTR, "a", True, INT), (P("Foo", 0, 0), "a", False, INT), (P("Foo", 0, 0), "next", False, BAR_PTR),
             (P("Foo.#1", 0, 0), "i", False, INT), (P("Un", 0, 0), "w", False, INT),
             (FOO_PTR, "a", False, None), (P("Foo", 0, 0), "a", True, None), (P("Foo", 2, 0), "a", True, None),
             (P("Foo", 1, 1), "a", True, None), (FOO_PTR, "zz", True, None), (P("Foo.#9", 0, 0), "i", False, None),
             (P("Zed", 1, 0), "a", True, None), (P("int", 1, 0), "a", True, None)]
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        types = fixture_types(folder)
        for owner, member, arrow, wanted in cases:
            found = cfix.member_type(types, owner, member, arrow)
            if found != wanted:
                failures.append(failure("member_type", found, (owner, member, arrow), wanted))
    return failures


def check_element_type() -> list[str]:
    """element_type gives what an index or a `*` reaches: an array loses a dimension first, else a pointer loses a
    star. A plain value gives None."""
    cases = [(P("Foo", 2, 0), P("Foo", 1, 0)), (P("Foo", 1, 0), P("Foo", 0, 0)), (P("Foo", 1, 2), P("Foo", 1, 1)),
             (P("Foo", 0, 1), P("Foo", 0, 0)), (P("Foo", 0, 0), None)]
    failures = []
    for found_type, wanted in cases:
        found = cfix.element_type(found_type)
        if found != wanted:
            failures.append(failure("element_type", found, found_type, wanted))
    return failures


def check_follow() -> list[str]:
    """follow walks the index and member steps in REST from a Pointee. No steps give the Pointee itself. A step that
    does not apply, an unclosed index, an unknown member, a missing member name and any other text give None, and
    so does None in front. Blanks around a step do not matter."""
    foo, bar = P("Foo", 0, 0), P("Bar", 0, 0)
    cases = [(FOO_PTR, "", FOO_PTR), (FOO_PTR, "   ", FOO_PTR), (FOO_PTR, "->a", INT), (foo, ".a", INT),
             (FOO_PTR, "->next->owner", FOO_PTR), (FOO_PTR, "->list[1].x", INT), (FOO_PTR, "->list[1]", bar),
             (FOO_PTR, "->grid[1][2]", P("float", 0, 0)), (FOO_PTR, "->grid[a[1]]", P("float", 0, 1)),
             (FOO_PTR, " -> list [ 1 ] . x ", INT), (FOO_PTR, "[2].a", INT), (FOO_PTR, "->work.b.owner", FOO_PTR),
             (None, "->a", None), (FOO_PTR, ".a", None), (foo, "->a", None), (FOO_PTR, "->zz", None),
             (FOO_PTR, "->", None), (FOO_PTR, "->list[1", None), (FOO_PTR, "->list[1]->x", None),
             (FOO_PTR, "+ 1", None), (FOO_PTR, "->a[0]", None), (FOO_PTR, "->a.b", None)]
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        types = fixture_types(folder)
        for start, rest, wanted in cases:
            found = cfix.follow(start, rest, types)
            if found != wanted:
                failures.append(failure("follow", found, (start, rest), wanted))
    return failures


def check_expression_type() -> list[str]:
    """expression_type gives the Pointee of a cast, or of a name in SCOPE with `*`, `&`, `[]`, `.` and `->` steps, also
    in groups. A cast gives its own type, without `const`, `struct` and the like. It gives None for any other
    expression (a sum), for a name that SCOPE lacks, for a step that does not apply, for the address of an array and
    for unbalanced brackets."""
    foo, bar, cast = P("Foo", 0, 0), P("Bar", 0, 0), P("Foo", 1, 0)
    cases = [("tp", FOO_PTR), ("  tp  ", FOO_PTR), ("tp->next", BAR_PTR), ("tp -> next [ 2 ]", bar),
             ("tp->next->owner", FOO_PTR), ("tp->link.x", INT), ("tp->list[1].x", INT),
             ("tp->list", P("Bar", 0, 1)), ("tp->grid[1]", P("float", 0, 1)), ("tp->work.b.owner", FOO_PTR),
             ("tp->inner[0].s", P("short", 0, 0)), ("tp->name[1]", P("char", 0, 0)), ("tp[0].a", INT),
             ("*tp", foo), ("**pp", foo), ("*tp->list", bar), ("&g", cast),
             ("&tp->link", BAR_PTR), ("&&n", P("int", 2, 0)),
             ("arr[1]", P("Bar", 0, 2)), ("&arr[1][2][0]", BAR_PTR), ("(*pp)->next", BAR_PTR), ("((tp))->a", INT),
             ("(Foo *)q", cast), ("(struct Foo *)q", cast), ("(const Foo *)tp", cast),
             ("(unsigned char *)tp", P("unsigned char", 1, 0)), ("(int)n", INT), ("(Bar *)tp->next", BAR_PTR),
             ("((Bar *)tp->next)->owner", FOO_PTR),
             ("tp + 1", None), ("(tp + 1)", None), ("nope", None), ("", None), ("tp->zz", None), ("tp->", None),
             ("tp.a", None), ("g->a", None), ("n[0]", None), ("**tp", None), ("tp->list[1]->x", None),
             ("tp->grid[1][2][3]", None), ("&tp->list", None), ("&arr[1]", None), ("tp[1", None), ("(tp", None),
             ("(", None), ("*", None), ("&", None)]
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        types = fixture_types(folder)
        for text, wanted in cases:
            found = cfix.expression_type(text, SCOPE, types)
            if found != wanted:
                failures.append(failure("expression_type", found, text, wanted))
    return failures


def check_pointer_kind() -> list[str]:
    """pointer_kind gives the spelling of the type that an operand points to, when the operand is one pointer to a
    type in SPELLINGS. A value, an array, a pointer to pointer, a type that SPELLINGS lacks and an operand with no
    type give None."""
    only_bar = {"Bar": "struct Bar"}
    cases = [("tp", SPELLINGS, "struct Foo"), ("tp->next", SPELLINGS, "struct Bar"), ("&g", SPELLINGS, "struct Foo"),
             ("(Foo *)q", SPELLINGS, "struct Foo"), ("tp", {"Foo": "const struct Foo"}, "const struct Foo"),
             ("tp", only_bar, None), ("tp->link", SPELLINGS, None), ("tp->list", SPELLINGS, None),
             ("pp", SPELLINGS, None), ("g", SPELLINGS, None), ("n", SPELLINGS, None), ("nope", SPELLINGS, None)]
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        types = fixture_types(folder)
        for operand, spellings, wanted in cases:
            found = cfix.pointer_kind(operand, spellings, SCOPE, types)
            if found != wanted:
                failures.append(failure("pointer_kind", found, (operand, spellings), wanted))
    return failures


def check_next_byte_fix() -> list[str]:
    """next_byte_fix puts `(char *)` on the first pointer to a type in SPELLINGS that a `+`, `-` or `[]` uses, and gives
    None when there is none. Under a cast, the offset keeps its type: `*(int *)(p + 4)` becomes
    `*(int *)((char *)p + 4)`. Otherwise the sum is cast back to the type as the compiler spelled it. The sum goes
    on to the first `)`, `]`, `,` or weaker operator. An operand that starts with `*` or `&`, or is a cast, gets
    parentheses. An index casts the pointer alone, but not when a member follows. A pointer to pointer, an array, a
    value, `++`, a sum in front of a `*` operand and a type outside SPELLINGS stay."""
    only_foo = {"Foo": "struct Foo"}
    cases = [("g = (struct task *)(tp + 4);", SPELLINGS, "g = (struct task *)((char *)tp + 4);"),
             ("x = tp + 4;", SPELLINGS, "x = (struct Foo *)((char *)tp + 4);"),
             ("x = tp - 4;", SPELLINGS, "x = (struct Foo *)((char *)tp - 4);"),
             ("x=tp-4;", SPELLINGS, "x=(struct Foo *)((char *)tp-4);"),
             ("x = tp + 4;", {"Foo": "const struct Foo"}, "x = (const struct Foo *)((char *)tp + 4);"),
             ("x = *(int *)(tp + 4);", SPELLINGS, "x = *(int *)((char *)tp + 4);"),
             ("x = (int)(tp + 4);", SPELLINGS, "x = (int)((char *)tp + 4);"),
             ("x = tp->next + 1;", SPELLINGS, "x = (struct Bar *)((char *)tp->next + 1);"),
             ("x = tp[2];", SPELLINGS, "x = ((char *)tp)[2];"),
             ("x = &tp[1];", SPELLINGS, "x = &((char *)tp)[1];"),
             ("x = tp[bp + 1];", SPELLINGS, "x = ((char *)tp)[bp + 1];"),
             ("x = *pp + 1;", SPELLINGS, "x = (struct Foo *)((char *)(*pp) + 1);"),
             ("return *pp + 1;", SPELLINGS, "return (struct Foo *)((char *)(*pp) + 1);"),
             ("x = &g + 1;", SPELLINGS, "x = (struct Foo *)((char *)(&g) + 1);"),
             ("x = (Foo *)q + 1;", SPELLINGS, "x = (struct Foo *)((char *)((Foo *)q) + 1);"),
             ("foo(tp + 4, 5);", SPELLINGS, "foo((struct Foo *)((char *)tp + 4), 5);"),
             ("x = tp + n * 2 - 1;", SPELLINGS, "x = (struct Foo *)((char *)tp + n * 2 - 1);"),
             ("x = tp + 4 < y;", SPELLINGS, "x = (struct Foo *)((char *)tp + 4) < y;"),
             ("x = s[tp + 1];", SPELLINGS, "x = s[(struct Foo *)((char *)tp + 1)];"),
             ("x = a ? tp + 1 : tp + 2;", SPELLINGS, "x = a ? (struct Foo *)((char *)tp + 1) : tp + 2;"),
             ("x = tp[1] + tp[2];", SPELLINGS, "x = ((char *)tp)[1] + tp[2];"),
             ("x = *(int *)(tp + 4) + *(int *)(tp + 8);", SPELLINGS,
              "x = *(int *)((char *)tp + 4) + *(int *)(tp + 8);"),
             ("x = tp->next + 1;", only_foo, None), ("x = tp[2].a;", SPELLINGS, None),
             ("x = tp->next[1].x;", SPELLINGS, None), ("x = tp->a + 1;", SPELLINGS, None),
             ("x = tp++;", SPELLINGS, None), ("x = n + 1;", SPELLINGS, None), ("x = (char *)tp + 4;", SPELLINGS, None),
             ("x = pp + 1;", SPELLINGS, None), ("x = arr + 1;", SPELLINGS, None), ("x = -tp;", SPELLINGS, None),
             ("x = nope + 1;", SPELLINGS, None), ("", SPELLINGS, None)]
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        types = fixture_types(folder)
        for line, spellings, wanted in cases:
            found = cfix.next_byte_fix(line, spellings, SCOPE, types)
            if found != wanted:
                failures.append(failure("next_byte_fix", found, (line, spellings), wanted))
    return failures


def check_declared_scope() -> list[str]:
    """declared_scope gives {name: Pointee} of the parameters and locals of FUNC, of DECLS, and of the top of the file
    ATTEMPT, which ends at its first annotation. The first declaration of a name wins, in that order. The signature
    is the first line after the annotation that is no blank and no comment. The globals headers give a name only when
    it is WANTED: the first header that declares it wins, and a header that does not exist is skipped."""
    annotation = f"// FUNCTION: {TARGET} 0x00401000"
    run = [annotation, "void Run(struct Foo *tp, int n)", "{", "\tstruct Foo *loc;", "\tg = tp;", "}"]
    commented = [annotation, "// a note", "", "void Run(struct Foo *tp, struct Bar b[2])", "{", "}"]
    other = [f"// FUNCTION: {TARGET} 0x00402000", "void Other(void)", "{", "}", "extern int after;"]
    shadows = ["extern struct Bar *tp;", "extern struct Bar *loc;", "extern struct Bar *dd;"]
    a_header = ("extern struct Foo *DAT_00501000;\nextern int DAT_00501004;\n"
                "extern struct Bar DAT_00501008[2];\nint not_extern;\n")
    b_header = "extern struct Bar *DAT_00501000;\n"
    base = {"tp": FOO_PTR, "n": INT, "loc": FOO_PTR}
    # (case, FUNC, DECLS, ATTEMPT, WANTED, header files in order, the scope)
    cases = [("parameters and locals", run, [], [], set(), [], base),
             ("declarations of DECLS and of the top of ATTEMPT", run, ["extern int extra;"],
              ["extern int top;", *run, "", *other], set(), [], base | {"extra": INT, "top": INT}),
             ("the first declaration of a name wins", run, shadows, ["extern int dd;", "extern int tt;", *run],
              set(), [], base | {"dd": P("Bar", 1, 0), "tt": INT}),
             ("a comment and a blank line before the signature", commented, [], [], set(), [],
              {"tp": FOO_PTR, "b": P("Bar", 0, 1)}),
             ("a global that is wanted", run, [], [], {"DAT_00501000"}, ["a.h"], base | {"DAT_00501000": FOO_PTR}),
             ("a global array that is wanted", run, [], [], {"DAT_00501008"}, ["a.h"],
              base | {"DAT_00501008": P("Bar", 0, 1)}),
             ("no global that is not wanted", run, [], [], set(), ["a.h"], base),
             ("a wanted name that no header declares", run, [], [], {"DAT_00509999", "not_extern"}, ["a.h"], base),
             ("the first header wins and a missing one is skipped", run, [], [], {"DAT_00501000"},
              ["none.h", "b.h", "a.h"], base | {"DAT_00501000": BAR_PTR})]
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        (Path(folder) / "a.h").write_text(a_header, encoding="utf-8")
        (Path(folder) / "b.h").write_text(b_header, encoding="utf-8")
        for case, func, decls, attempt, wanted_names, files, scope in cases:
            found = llm.declared_scope(func, decls, attempt, wanted_names, [Path(folder) / name for name in files])
            if found != scope:
                failures.append(failure("declared_scope", found, case, scope))
    return failures


def c2036(path, index: int, top: int, kind: str = "struct Foo", code: str = "C2036") -> str:
    """A build line for the function line INDEX of a file with TOP lines in front of it."""
    return f"{path}({top + index + 1}) : error {code}: '{kind} *' : unknown size\n"


def check_byte_arith() -> list[str]:
    """byte_arith puts `(char *)` on the pointers of the C2036 lines of PATH, its own file, and gives (the new FUNC, the
    changed lines, stripped). A C2036 line of another file with a line number inside the function changes nothing,
    and neither does a line outside the function, another error code, a type that is not the one named, a line with
    no sum on a pointer of that type, or no error. A global pointer takes its type from the headers. It repeats until
    a line has no more such sum. When FUNC is not the definition at ADDRESS in ATTEMPT, it gives (FUNC, [])."""
    annotation = f"// FUNCTION: {TARGET} 0x00401000"
    func = [annotation, "void Run(struct Foo *tp, int n)", "{", "\tstruct Foo *loc;", "\tg = (struct task *)(tp + 4);",
            "\tx = *(int *)(loc + 8);", "\ty = n + 1;", "\tz = DAT_00501000 + 4;", "\tw = tp[1] + tp[2];", "}"]
    top = ["extern int top;", ""]
    tail = ["", f"// FUNCTION: {TARGET} 0x00402000", "void Other(void)", "{", "}", ""]
    attempt = "\n".join(top + func + tail)
    first, second, third, fourth, fifth = 4, 5, 6, 7, 8
    fixed = {first: "\tg = (struct task *)((char *)tp + 4);", second: "\tx = *(int *)((char *)loc + 8);",
             fourth: "\tz = (struct Foo *)((char *)DAT_00501000 + 4);",
             fifth: "\tw = ((char *)tp)[1] + ((char *)tp)[2];"}
    # (case, the build lines as (file, function line, type, code), the function lines that change)
    cases = [("a C2036 line of its own file", [("own", first, "struct Foo", "C2036")], [first]),
             ("the same file spelled with slashes", [("slashes", first, "struct Foo", "C2036")], [first]),
             ("a C2036 line of another file at that line number", [("other", first, "struct Foo", "C2036")], []),
             ("lines of its own file and of another", [("other", first, "struct Foo", "C2036"),
                                                       ("own", second, "struct Foo", "C2036")], [second]),
             ("a global from the headers", [("own", fourth, "struct Foo", "C2036")], [fourth]),
             ("two sums on one line", [("own", fifth, "struct Foo", "C2036")], [fifth]),
             ("two lines", [("own", first, "struct Foo", "C2036"), ("own", second, "struct Foo", "C2036")],
              [first, second]),
             ("a type with a const spelling", [("own", first, "const struct Foo", "C2036")], [first]),
             ("a line with no pointer sum", [("own", third, "struct Foo", "C2036")], []),
             ("another type", [("own", second, "struct Bar", "C2036")], []),
             ("another error code", [("own", first, "struct Foo", "C2037")], []),
             ("a line before the function", [("own", -1, "struct Foo", "C2036")], []),
             ("a line behind the function", [("own", len(func), "struct Foo", "C2036")], []),
             ("no error", [], [])]
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        types = fixture_types(folder)
        headers = [Path(folder) / "globals.h"]
        headers[0].write_text("extern struct Foo *DAT_00501000;\n", encoding="utf-8")
        path, other = Path(folder) / "x.c", Path(folder) / "y.c"
        spelled = {"own": str(path), "other": str(other), "slashes": str(path).replace("\\", "/")}
        for case, errors, changed_at in cases:
            text = "".join(c2036(spelled[file], index, len(top), kind, code) for file, index, kind, code in errors)
            wanted = ([fixed[i] if i in changed_at else line for i, line in enumerate(func)],
                      sorted(fixed[i].strip() for i in changed_at))
            found = llm.byte_arith(func, [], attempt, path, 0x401000, text, types, headers)
            found = (found[0], sorted(found[1]))
            if found != wanted:
                failures.append(failure("byte_arith", found, case, wanted))
        text = c2036(path, first, len(top))
        changed_func = func[:-1] + ["\t// a different last line", "}"]
        unusable = [("a FUNC that is not the definition in ATTEMPT", changed_func, attempt, 0x401000),
                    ("an ADDRESS with no definition", func, attempt, 0x403000),
                    ("a definition with no closing line", func[:-1], "\n".join(top + func[:-1]), 0x401000)]
        for case, given, source, address in unusable:
            found = llm.byte_arith(given, [], source, path, address, text, types, headers)
            if found != (given, []):
                failures.append(failure("byte_arith", found, case, (given, [])))
    return failures


def check_fewer_unknown_sizes() -> list[str]:
    """fewer_unknown_sizes says whether the build output AFTER has fewer C2036 lines than BEFORE and no error code that
    BEFORE lacks. The same number or more is not fewer, and a new code makes it fail even when all C2036 lines
    are gone. A code that BEFORE had may stay or go."""
    def unknown(count: int) -> str:
        return "".join(f"x.c({n + 1}) : error C2036: 'struct Foo *' : unknown size\n" for n in range(count))

    def error(code: str) -> str:
        return f"x.c(9) : error {code}: something\n"

    cases = [("fewer C2036 lines", unknown(2), unknown(1), True), ("no C2036 line left", unknown(1), "", True),
             ("the same number", unknown(1), unknown(1), False), ("more", unknown(1), unknown(2), False),
             ("none before and after", "", "", False),
             ("fewer and a new code", unknown(2), unknown(1) + error("C2059"), False),
             ("none left and a new code", unknown(1), error("C2059"), False),
             ("fewer and an old code stays", unknown(2) + error("C2440"), unknown(1) + error("C2440"), True),
             ("fewer and an old code goes", unknown(1) + error("C2440"), "", True)]
    failures = []
    for case, before, after, wanted in cases:
        found = llm.fewer_unknown_sizes(before, after)
        if found is not wanted:
            failures.append(failure("fewer_unknown_sizes", found, case, wanted))
    return failures


def run() -> list[str]:
    """Every check of the byte-offset repair, in order: the failures of all."""
    failures = []
    for check in (check_operand_ends, check_binary_sign, check_operand_start, check_chain_end, check_under_cast,
                  check_unknown_size_pattern, check_struct_members, check_member_type, check_element_type,
                  check_follow, check_expression_type, check_pointer_kind, check_next_byte_fix,
                  check_declared_scope, check_byte_arith, check_fewer_unknown_sizes):
        failures += check()
    return failures
