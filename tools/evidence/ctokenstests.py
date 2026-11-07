"""Unit tests for ctokens.py, the shared lexer of the evidence tools.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/ctokenstests.py
run() calls every check and returns the failures. All names are made up.
"""

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import ctokens  # noqa: E402
from ctokens import Unsupported  # noqa: E402


def texts(text: str) -> list[str]:
    return [token.text for token in ctokens.tokens_of(text)]


def check_strings_and_comments() -> list[str]:
    failures = []
    tokens, comments = ctokens.tokenize('f("/*", 1); // say "hi"\n/* it\'s */ g();')
    if [token.text for token in tokens] != ["f", "(", '"/*"', ",", "1", ")", ";", "g", "(", ")", ";"]:
        failures.append(f"comment opener in a string: got {[token.text for token in tokens]}")
    if [comment.text for comment in comments] != ['// say "hi"', "/* it's */"]:
        failures.append(f"quotes in comments: got {[comment.text for comment in comments]}")
    if texts(r"'\\' '\'' '/' L'A'") != [r"'\\'", r"'\''", "'/'", "L'A'"]:
        failures.append(f"character constants: got {texts(chr(39))}")
    return failures


def check_lines_and_columns() -> list[str]:
    failures = []
    tokens, _ = ctokens.tokenize("﻿a\r\n\tbc  d\r\n")
    got = [(token.text, token.line, token.column, token.bol) for token in tokens]
    if got != [("a", 1, 1, True), ("bc", 2, 2, True), ("d", 2, 6, False)]:
        failures.append(f"BOM, CRLF and columns: got {got}")
    tokens, _ = ctokens.tokenize("x = 1 + \\\n  2;\ny")
    got = [(token.text, token.line, token.column, token.bol) for token in tokens]
    if got[4:] != [("2", 2, 3, False), (";", 2, 4, False), ("y", 3, 1, True)]:
        failures.append(f"a spliced line keeps its written line and column: got {got}")
    tokens, comments = ctokens.tokenize("// note \\\nstill note\nz")
    if [token.text for token in tokens] != ["z"] or tokens[0].line != 3:
        failures.append(f"a backslash-newline continues a // comment: got {tokens}")
    if [(comment.line, comment.end_line) for comment in comments] != [(1, 2)]:
        failures.append(f"a continued comment spans its lines: got {comments}")
    return failures


def check_unsupported() -> list[str]:
    failures = []
    for text, reason in (("a ??/\nb", "trigraph"), ("a /* open", "unterminated block comment")):
        try:
            ctokens.tokenize(text)
            failures.append(f"{text!r}: expected Unsupported")
        except Unsupported as error:
            if str(error) != reason:
                failures.append(f"{text!r}: got reason {error}")
    if texts("#error don't") != ["#", "error", "don", "'", "t"]:
        failures.append(f"a lone quote is one token: got {texts(chr(39))}")
    return failures


def check_drop_words() -> list[str]:
    tokens = ctokens.tokens_of("__declspec(dllimport) int __cdecl f(_In_ int a, _In_reads_(n) int *b, __int64 c);")
    kept = ctokens.spelling(ctokens.drop_words(tokens, {"__declspec", "__cdecl"}, ("_In_",)))
    if kept != "int f ( int a , int * b , __int64 c ) ;":
        return [f"drop_words: got {kept}"]
    return []


def check_unwrapped() -> list[str]:
    cases = {"( ( a ) )": "a", "( a ) | ( b )": "( a ) | ( b )", "( a | b )": "a | b", "()": "", "a": "a"}
    got = {text: " ".join(ctokens.unwrapped(text.replace("()", "( )").split())) for text in cases}
    return [] if got == cases else [f"unwrapped: got {got}"]


def check_drop_directives() -> list[str]:
    """Directive lines go, every branch stays, and the callback sees each directive."""
    failures = []
    tokens = ctokens.tokens_of("#if XX_A\nf(1);\n#else\nf(2);\n#endif\n# define XX_B 1\ng();\n")
    seen = []
    kept = ctokens.spelling(ctokens.drop_directives(tokens, lambda words, line: seen.append((words[0].text, line))))
    if kept != "f ( 1 ) ; f ( 2 ) ; g ( ) ;":
        failures.append(f"drop_directives keeps every branch: got {kept}")
    if seen != [("if", 1), ("else", 3), ("endif", 5), ("define", 6)]:
        failures.append(f"drop_directives callback: got {seen}")
    if ctokens.spelling(ctokens.drop_directives(tokens)) != kept:
        failures.append("drop_directives with no callback")
    return failures


def calls_of(text: str) -> list[tuple]:
    """(callee, outer, argument spellings) of each call in TEXT, with any identifier as a callee."""
    tokens = ctokens.tokens_of(text)
    found = ctokens.find_calls(tokens, lambda index: tokens[index].kind == "id")
    return [(tokens[call.position].text, call.outer, [ctokens.spelling(argument) for argument in call.arguments(tokens)])
            for call in found]


def check_find_calls() -> list[str]:
    failures = []
    cases = {
        "f(a, g(b, c), (d, e)[1, 2], {x, y});": [
            ("f", (), ["a", "g ( b , c )", "( d , e ) [ 1 , 2 ]", "{ x , y }"]),
            ("g", (("f", 2),), ["b", "c"])],
        "f();": [("f", (), [])],
        ") f(1); g(2, h(3);": [("f", (), ["1"]), ("h", (("g", 2),), ["3"])],
        "a(b(c(1)));": [("a", (), ["b ( c ( 1 ) )"]), ("b", (("a", 1),), ["c ( 1 )"]),
                        ("c", (("a", 1), ("b", 1)), ["1"])],
    }
    for text, wanted in cases.items():
        if calls_of(text) != wanted:
            failures.append(f"find_calls {text!r}: got {calls_of(text)}")
    tokens = ctokens.tokens_of("x.f(1); g(2); h(3);")
    found = ctokens.find_calls(tokens, lambda index: tokens[index].kind == "id" and tokens[index - 1].text != ".",
                               tokens.index(next(token for token in tokens if token.text == "g")) - 1, len(tokens) - 4)
    if [tokens[call.position].text for call in found] != ["g"]:
        failures.append("find_calls: the callee filter and the bounds")
    return failures


def fields_of(text: str) -> list[tuple]:
    """(base, member, operator, value) of each field spot in TEXT, with any identifier but a keyword as a callee."""
    tokens = ctokens.tokens_of(text)
    keywords = {"if", "while", "return", "sizeof"}
    found = ctokens.find_fields(tokens, lambda index: tokens[index].kind == "id" and tokens[index].text not in keywords)
    return [(ctokens.spelling(tokens[spot.base:spot.member - 1]), tokens[spot.member].text, spot.operator,
             ctokens.spelling(tokens[spot.value:spot.end])) for spot in found]


def check_find_fields() -> list[str]:
    """Writes and compares through . and ->, the x.f = x.f | K fold, C precedence on both sides, the bounds, and the
    forms that are no field spot."""
    cases = {
        "p->f = 3;": [("p", "f", "=", "3")],
        "s.f |= 0x8;": [("s", "f", "|=", "0x8")],
        "a[0].f &= ~8;": [("a [ 0 ]", "f", "&=", "~ 8")],
        "(*p).f = 1;": [("( * p )", "f", "=", "1")],
        "p->a.f = 2;": [("p -> a", "f", "=", "2")],
        "get(x)->f = 4;": [("get ( x )", "f", "=", "4")],
        "((T *)q)->f = 5;": [("( ( T * ) q )", "f", "=", "5")],
        "if (p->f == 3 && q) g();": [("p", "f", "==", "3")],
        "if (p->f & 8) g();": [("p", "f", "&", "8")],
        "x = p->f != 0;": [("p", "f", "!=", "0")],
        "g(p->f == 1, 2);": [("p", "f", "==", "1")],
        "p->f = p->f | 8 | 16;": [("p", "f", "|=", "8 | 16")],
        "p->f = p->f & 0xf7;": [("p", "f", "&=", "0xf7")],
        "p->f = p->f & 8 | 16;": [("p", "f", "=", "p -> f & 8 | 16"), ("p", "f", "&", "8")],
        "p->f = c ? 1 : 2;": [("p", "f", "=", "c ? 1 : 2")],
        "y = p->f == 1 ? a : b;": [("p", "f", "==", "1")],
        "return (p)->f == 0;": [("( p )", "f", "==", "0")],
        "a = p->f = 3;": [("p", "f", "=", "3")],
        "p->f = 1, q->g = 2;": [("p", "f", "=", "1"), ("q", "g", "=", "2")],
        "if (x) p->f = 3;": [("p", "f", "=", "3")],
    }
    rejected = ("*p->f = 3;", "a + p->f == 3;", "(int)p->f == 3;", "&p->f == q;", "!p->f == 0;", "p->f[2] = 3;",
                "x & p->f & 8;", "{ .f = 3 }", "p->f -= 1;", "p->f;")
    failures = [f"find_fields {text!r}: got {fields_of(text)}" for text, wanted in cases.items()
                if fields_of(text) != wanted]
    failures += [f"find_fields {text!r} is no spot: got {fields_of(text)}" for text in rejected if fields_of(text)]
    tokens = ctokens.tokens_of("p->f = 1; q->g = 2; r->h = 3;")
    if [tokens[spot.member].text for spot in ctokens.find_fields(tokens, lambda index: False, 5, 11)] != ["g"]:
        failures.append("find_fields: the bounds")
    return failures


def values_of(text: str) -> list[tuple]:
    """(kind, lvalue, operator, value) of each value spot in TEXT, with any identifier but a keyword as a name."""
    tokens = ctokens.tokens_of(text)
    keywords = {"if", "while", "return", "switch", "case", "int", "else", "do", "sizeof"}
    found = ctokens.find_values(tokens, lambda index: tokens[index].kind == "id" and tokens[index].text not in keywords)
    return [(spot.kind, ctokens.spelling(tokens[spot.lvalue[0]:spot.lvalue[1]]) if spot.lvalue else "", spot.operator,
             ctokens.spelling(tokens[spot.value:spot.end])) for spot in found]


def check_find_values() -> list[str]:
    """Plain variables before =, == and !=, case labels with the innermost braced switch, returns with a value, the
    bounds, and the forms that are no value spot."""
    variable, case, ret = ctokens.VARIABLE, ctokens.CASE, ctokens.RETURN
    cases = {
        "mode = 3;": [(variable, "mode", "=", "3")],
        "if (mode == 1 && x) g();": [(variable, "mode", "==", "1")],
        "while (mode != -2) g();": [(variable, "mode", "!=", "- 2")],
        "for (i = 0; i < 3; ++i) g();": [(variable, "i", "=", "0")],
        "a = b = 1;": [(variable, "a", "=", "b = 1"), (variable, "b", "=", "1")],
        "g(mode == 4, 2);": [(variable, "mode", "==", "4")],
        "else mode = 5;": [(variable, "mode", "=", "5")],
        "int a, b = 6;": [(variable, "b", "=", "6")],
        "return mode == 1 ? 2 : 3;": [(ret, "", "return", "mode == 1 ? 2 : 3"), (variable, "mode", "==", "1")],
        "return -1;": [(ret, "", "return", "- 1")],
        "switch (p->m) { case 1: case A | B: break; }": [(case, "p -> m", "case", "1"),
                                                        (case, "p -> m", "case", "A | B")],
        "switch (a) { case 1: switch (b) { case 2: break; } case 3: break; }": [
            (case, "a", "case", "1"), (case, "b", "case", "2"), (case, "a", "case", "3")],
        "switch (a) { case c ? 1 : 2: break; }": [(case, "a", "case", "c ? 1 : 2")],
    }
    rejected = ("int x = 1;", "*p = 3;", "a + b == 3;", "&x == q;", "!x == 0;", "p->x = 3;", "x[2] = 3;",
                "x += 1;", "return;", "case 1:", "switch (a) case 1: break;", "A::x = 1;", "(int)x == 3;")
    failures = [f"find_values {text!r}: got {values_of(text)}" for text, wanted in cases.items()
                if values_of(text) != wanted]
    failures += [f"find_values {text!r} is no spot: got {values_of(text)}" for text in rejected if values_of(text)]
    tokens = ctokens.tokens_of("a = 1; b = 2; c = 3;")
    if [tokens[spot.position].text for spot in ctokens.find_values(tokens, lambda index: True, 3, 8)] != ["b"]:
        failures.append("find_values: the bounds")
    return failures


def check_raw_offsets() -> list[str]:
    """A unary * on a pointer cast of a group that adds or subtracts; no product, and no cast of a plain name."""
    tokens = ctokens.tokens_of("*(Sint32 *)((char *)p + 8) = 3; y = *(Uint8 *)(p - 4); x = a * (b + 1); "
                               "*(int *)p = 3;")
    count = ctokens.raw_offsets(tokens, -1, len(tokens))
    return [] if count == 2 else [f"raw_offsets: got {count}"]


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_strings_and_comments, check_lines_and_columns, check_unsupported, check_drop_words,
                  check_unwrapped, check_drop_directives, check_find_calls, check_find_fields, check_find_values,
                  check_raw_offsets):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    print("\n".join(found) or "ctokenstests: all passed")
    sys.exit(1 if found else 0)
