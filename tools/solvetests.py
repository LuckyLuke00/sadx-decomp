"""Tests of the try loop in tools/llm.py: solve_function against a fake server, and the --tries, --try-tokens,
--prefix-feedback and --refuse-fakematch flags, with the kinds that tools/fakematch.py finds.

solve_function gets fakes for the file, the dossier and the builds. The fake server refuses a chat as too long for
its context when the case's rule says so, else replies with no code, so no try builds. run() returns the failures as
"<case> gives <found>, not <wanted>".
"""

import argparse
import contextlib
import io
import json
import os
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import NamedTuple
from unittest import mock

import fakematch
import llm
import llmclient

ADDRESS = 0x00401000
FILE = "src/foo.c"
SEED = 5
MAX_TOKENS = 1500
TOO_LONG = "http://127.0.0.1:8080/v1/chat/completions answered 400: the request exceeds the available context size"
DIFF = ("---\n+++\n@@ -0x401000,4 +0x405900,4 @@\n"  # reccmp's diff: two instructions match, then one differs
        "0x401000 : sub esp, 0x10 \t(foo.c:31)\n"
        "0x401003 : push ebx\n"
        "0x401004 : -mov ebx, ecx\n"
        "         : +mov ebx, dword ptr [esi + 0x2c]\n"
        "0x401006 : ret\n\n"
        "0x00401000 foo: 80.00% match. Diff above (- original, + ours).")
IMAGE = range(0x400000, 0x800000)  # the fake exe's sections


class Run(NamedTuple):
    seeds: list[int]  # the seed of each ask
    replies: int  # the asks that got a reply
    tries: int  # the tries that solve_function returns
    logged: list[int]  # the try numbers in its transcript
    limits: list[int]  # the max_tokens of each ask
    results: list[str]  # the result of each try in its transcript
    lasts: list[str]  # the last message of each ask
    best: float  # the best that solve_function returns
    kept: str  # the text that the file got last
    entries: list[dict]  # every line of its transcript
    live: list  # every line of its live file: the last try's header, its reply's pieces, then its result


def never_too_long(messages) -> bool:
    return False


def solved(tries, too_long, reply="no code", **flags) -> Run:
    """A run of TRIES against a server that refuses the chats for which TOO_LONG is true, else answers REPLY, or
    with a list of replies the next one, and its last one after the list. FLAGS override the run's other flags, such
    as stop_below=70."""
    asks, kept = [], []
    replies = [reply] if isinstance(reply, str) else reply

    def chat(config, messages, temperature, thinking, seed, on_text):
        refused = too_long(messages)
        asks.append((seed, refused, config["max_tokens"], messages[-1]["content"]))
        if refused:
            raise llmclient.ServerError(TOO_LONG, 400)
        answered = sum(not ask[1] for ask in asks)
        text = replies[min(answered, len(replies)) - 1]
        on_text("content", text)
        return llmclient.Reply(text, "", {"prompt_tokens": 1, "completion_tokens": 1}, "stop")

    def first_prompt(config, file, address, types, count, extra, similar, recipe):
        return f"{count} examples" + llm.recipe_section(recipe)

    fakes = {"read_source": lambda path: ('#include "decls.h"\n', False),
             "write_source": lambda path, text, crlf: kept.append(text), "snapshot": lambda paths: {},
             "tree_warnings": lambda config: set(), "load_types": lambda config: None, "first_prompt": first_prompt,
             "file_best": lambda *args: None, "decls": lambda config: ("", 0), "exe_contains": lambda: IMAGE.__contains__,
             "exe_literal": lambda: lambda address, width: None}
    settings = {"tables": None, "context": None, "temperature": 0.2, "think_on": None, "max_tokens": MAX_TOKENS}
    options = dict(settings=settings, system="", tries=tries, seed=SEED, structs=False, accesses=False, facts=False,
                   idioms=False, tree_wins=False, stale_built_only=False, max_repeats=None, give_up=False,
                   stop_below=None, try_tokens=None, think_max=None, similar_examples=False,
                   prefix_feedback=False, refuse_fakematch=False, recipes=None)
    args = argparse.Namespace(**{**options, **flags})
    with (tempfile.TemporaryDirectory() as folder, mock.patch.multiple(llm, **fakes),
          mock.patch.object(llmclient, "chat", chat), contextlib.redirect_stdout(io.StringIO())):
        transcript, live = Path(folder) / "transcript.jsonl", Path(folder) / "live.jsonl"
        with mock.patch.object(llm, "LIVE", live):
            result = llm.solve_function(args, FILE, ADDRESS, transcript)
        logged = [json.loads(line) for line in transcript.read_text(encoding="utf-8").splitlines()]
        shown = [json.loads(line) for line in live.read_text(encoding="utf-8").splitlines()] if live.exists() else []
    return Run([ask[0] for ask in asks], sum(not ask[1] for ask in asks), result["tries"],
               [entry["try"] for entry in logged if "try" in entry], [ask[2] for ask in asks],
               [entry["result"] for entry in logged if "try" in entry], [ask[3] for ask in asks], result["best"],
               kept[-1], logged, shown)


def check_too_long() -> list[str]:
    """A chat too long for the server is asked again shorter with the same seed, as the same try: first without the
    history, then with one example fewer. A run gives up when even the first prompt without examples is too long,
    and then it made no try."""
    full = f"{llm.EXAMPLES} examples"
    cases = [("a first prompt too long", 2, lambda messages: messages[1]["content"] == full,
              ([SEED + 1, SEED + 1, SEED + 2], 2, 2, [1, 2])),
             ("a history too long", 3, lambda messages: len(messages) > 2,
              ([SEED + 1, SEED + 2, SEED + 2, SEED + 3, SEED + 3], 3, 3, [1, 2, 3])),
             ("every prompt too long", 2, lambda messages: True, ([SEED + 1] * (llm.EXAMPLES + 1), 0, 0, []))]
    failures = []
    for case, tries, too_long, wanted in cases:
        found = solved(tries, too_long)[:4]
        if found != wanted:
            failures.append(f"{case} gives {found}, not {wanted}")
    return failures


def check_stop_below() -> list[str]:
    """--stop-below P ends a run after STOP_AFTER tries when the best is below P%. Here no try builds, so the best
    is 0%: P 70 stops it, P 0 does not, and a run of fewer tries ends as before."""
    cases = [("--stop-below 70", 3, {"stop_below": 70.0}, llm.STOP_AFTER), ("no --stop-below", 3, {}, 3),
             ("--stop-below 0", 3, {"stop_below": 0.0}, 3), ("--stop-below 70 --tries 1", 1, {"stop_below": 70.0}, 1)]
    failures = []
    for case, tries, flags, wanted in cases:
        found = solved(tries, never_too_long, **flags).tries
        if found != wanted:
            failures.append(f"{case} gives {found} tries, not {wanted}")
    return failures


def check_try_tokens() -> list[str]:
    """--try-tokens sets each try's max_tokens in turn, and its last value holds for the tries after it. A chat too
    long for the server is the same try again, so it keeps that try's limit. Without the flag every try gets the
    config's max_tokens."""
    full = f"{llm.EXAMPLES} examples"
    cases = [("--try-tokens 600,1000", 3, never_too_long, {"try_tokens": [600, 1000]}, [600, 1000, 1000]),
             ("--try-tokens 600,1000 and a first prompt too long", 2, lambda messages: messages[1]["content"] == full,
              {"try_tokens": [600, 1000]}, [600, 600, 1000]),
             ("no --try-tokens", 2, never_too_long, {}, [MAX_TOKENS, MAX_TOKENS])]
    failures = []
    for case, tries, too_long, flags, wanted in cases:
        found = solved(tries, too_long, **flags).limits
        if found != wanted:
            failures.append(f"{case} gives the limits {found}, not {wanted}")
    return failures


def check_forbidden_reply() -> list[str]:
    """A reply with inline assembly or a pragma gets no build, so it can never match. Its try names the word, and the
    next prompt says that it is not allowed. The same reply again is a repeat of that try."""
    failures = []
    for word, line in [("__asm", "\t__asm nop"), ("#pragma", '#pragma optimize("", off)')]:
        reply = f"```cpp\n{llm.function_line(ADDRESS)}\nvoid Foo(void)\n{{\n{line}\n}}\n```"
        builds = []
        with mock.patch.object(llm.Bench, "build", lambda self, *args: builds.append(args)):
            run = solved(2, never_too_long, reply)
        found = (run.results, len(builds), "are not allowed" in run.lasts[-1])
        wanted = ([f"used `{word}`, not allowed", "repeated try 1"], 0, True)
        if found != wanted:
            failures.append(f"a reply with {word} gives {found}, not {wanted}")
    return failures


def parsed(argv, name):
    """The flag NAME that llm.py gets from the arguments ARGV, or argparse's exit code when it refuses them."""
    with mock.patch.object(sys, "argv", ["llm.py", *argv]), contextlib.redirect_stderr(io.StringIO()):
        try:
            return getattr(llm.parse_args(), name)
        except SystemExit as error:
            return f"exit {error.code}"


def check_tries_flag() -> list[str]:
    """--tries takes 1 or more. Less stops at argparse's error, before a run that would make no try. --try-tokens
    takes a comma-separated list of the same."""
    cases = [("--tries 1", ["solve", "--tries", "1", FILE, "0x00401000"], "tries", 1),
             ("--tries 0", ["solve", "--tries", "0", FILE, "0x00401000"], "tries", "exit 2"),
             ("bench --tries -1", ["bench", "--tries", "-1"], "tries", "exit 2"),
             ("--try-tokens 600,1000", ["bench", "--try-tokens", "600,1000"], "try_tokens", [600, 1000]),
             ("--try-tokens 600,0", ["bench", "--try-tokens", "600,0"], "try_tokens", "exit 2")]
    failures = []
    for case, argv, name, wanted in cases:
        found = parsed(argv, name)
        if found != wanted:
            failures.append(f"{case} gives {found!r}, not {wanted!r}")
    return failures


def check_prefix_feedback() -> list[str]:
    """--prefix-feedback adds how many instructions match from the function's start to the first difference: the
    diff's unmarked lines before the first marked one. It adds nothing when the diff's first hunk starts after the
    function's start, since the diff leaves out the lines before it, nor when no line differs. Without the flag the
    feedback has no such line."""
    note = "The first 2 instructions match; the first difference is instruction 3.\n"
    plain = llm.feedback(80.0, DIFF, ADDRESS, set())
    later = DIFF.replace("@@ -0x401000", "@@ -0x401030")
    first = DIFF.replace("0x401000 : sub esp, 0x10 \t(foo.c:31)\n0x401003 : push ebx\n", "")
    same = "---\n+++\n@@ -0x401000,1 +0x405900,1 @@\n0x401000 : ret\n"
    reply = f"```cpp\n{llm.function_line(ADDRESS)}\nvoid Foo(void)\n{{\n}}\n```"
    with mock.patch.object(llm.Bench, "build", lambda self, decls, func: llm.Build(decls, func, "", 80.0, DIFF)):
        asked = {flag: solved(2, never_too_long, reply, prefix_feedback=flag).lasts[-1] for flag in (True, False)}
    cases = [("the flag on", llm.feedback(80.0, DIFF, ADDRESS, set(), None, True),
              plain.replace("Reply with", note + "Reply with")),
             ("the flag off", "instructions match" in plain, False),
             ("a first hunk after the function's start", llm.feedback(80.0, later, ADDRESS, set(), None, True),
              llm.feedback(80.0, later, ADDRESS, set())),
             ("a difference in the first instruction", "The first 0 instructions match; the first difference is "
              "instruction 1.\n" in llm.feedback(80.0, first, ADDRESS, set(), None, True), True),
             ("no line that differs", llm.feedback(100.0, same, ADDRESS, set(), None, True),
              llm.feedback(100.0, same, ADDRESS, set())),
             ("the flag on in a run", note in asked[True], True),
             ("the flag off in a run", note in asked[False], False),
             ("--prefix-feedback", parsed(["solve", "--prefix-feedback", FILE, "0x00401000"], "prefix_feedback"), True),
             ("no --prefix-feedback", parsed(["solve", FILE, "0x00401000"], "prefix_feedback"), False)]
    return [f"{case} gives {found!r}, not {wanted!r}" for case, found, wanted in cases if found != wanted]


def check_recipes() -> list[str]:
    """--recipes DIR puts the plan in DIR/ADDRESS/recipe.md into the first prompt, after its lead line. A function
    with no plan file gets the prompt without one."""
    with tempfile.TemporaryDirectory() as folder:
        plans = Path(folder)
        no_plan = solved(1, never_too_long, recipes=plans).lasts[0]
        (plans / llm.hexa(ADDRESS)).mkdir()
        (plans / llm.hexa(ADDRESS) / "recipe.md").write_text("1. The loop counts down.\n", encoding="utf-8")
        with_plan = solved(1, never_too_long, recipes=plans).lasts[0]
    wanted = f"{llm.EXAMPLES} examples{llm.RECIPE_LEAD}\n1. The loop counts down.\n\n"
    failures = []
    if with_plan != wanted:
        failures.append(f"the first prompt with a plan is {with_plan!r}, not {wanted!r}")
    if no_plan != f"{llm.EXAMPLES} examples":
        failures.append(f"the first prompt without a plan file is {no_plan!r}")
    return failures


def cpp(*body) -> str:
    """A reply with the function `int Foo(void)` whose body is the lines BODY."""
    return "\n".join(["```cpp", llm.function_line(ADDRESS), "int Foo(void)", "{", *body, "}", "```"])


def check_refuse_fakematch() -> list[str]:
    """--refuse-fakematch: a 100% try with a fakematch line does not end the run. Its note names the line, and the
    run asks again. A later clean 100% ends the run and stays in the file. When none comes, the file keeps the first
    refused try and the run's best is 100. A refused match counts as 100 for --stop-below. Without the flag the
    first 100% ends the run."""
    dirty, other, clean = (cpp("\treturn *(int *)0x00500000;"), cpp("\treturn *(int *)0x00500004;"),
                           cpp("\treturn Bar;"))
    code = "\n".join(llm.parse_reply(dirty, ADDRESS)[1])

    def build(self, decls, func):
        return llm.Build(decls, func, "\n".join(func), 100.0, "")

    with mock.patch.object(llm.Bench, "build", build):
        off = solved(3, never_too_long, dirty)
        refused = solved(3, never_too_long, [dirty, other], refuse_fakematch=True)
        then_clean = solved(3, never_too_long, [dirty, clean], refuse_fakematch=True)
        stop_below = solved(3, never_too_long, ["no code", dirty, other], refuse_fakematch=True, stop_below=70.0)
    note = "`return *(int *)0x00500000;` (raw_address)"
    cases = [("the flag off", (off.tries, off.kept), (1, code)),
             ("every try refused", (refused.tries, refused.results, refused.best, refused.kept),
              (3, ["100.00%", "100.00%", "repeated try 2"], 100.0, code)),
             ("the refused lines in the transcript", [e.get("refused") for e in refused.entries if "try" in e][:2],
              [[["raw_address", "return *(int *)0x00500000;"]], [["raw_address", "return *(int *)0x00500004;"]]]),
             ("the next prompt", [note in last for last in refused.lasts[1:2]], [True]),
             ("the kept refused try", {"kept_refused": True} in refused.entries, True),
             ("a clean try after a refused one", (then_clean.tries, then_clean.kept.strip().split("\n")[-2]),
              (2, "\treturn Bar;")),
             ("no kept refused try after a clean one", {"kept_refused": True} in then_clean.entries, False),
             ("--stop-below 70", stop_below.tries, 3),
             ("--refuse-fakematch", parsed(["solve", "--refuse-fakematch", FILE, "0x00401000"], "refuse_fakematch"),
              True),
             ("no --refuse-fakematch", parsed(["solve", FILE, "0x00401000"], "refuse_fakematch"), False)]
    return [f"{case} gives {found!r}, not {wanted!r}" for case, found, wanted in cases if found != wanted]


def check_fakematch_kinds() -> list[str]:
    """fakematch.found finds each kind on its line, and not on a plain line like it."""
    cases = [("raw_address", ["\treturn *(int *)0x00500000;"], "return *(int *)0x00500000;",
              ["\treturn *(int *)0x00900000;"]),
             ("index_game", ["\treturn *(&p[1] - 1);"], "return *(&p[1] - 1);", ["\treturn p[0] & 1;"]),
             ("neighbor_address", ["\treturn *(&p + 1);"], "return *(&p + 1);", ["\treturn *(p + 1);"]),
             ("neighbor_address", ["\treturn (&x)[1];"], "return (&x)[1];", ["\treturn (x & 1) + 1;"]),
             ("neighbor_address", ["\tp = &x - 0x2;"], "p = &x - 0x2;", ["\tp = &x;"]),
             ("address_pun", ["\treturn *(int *)&x;"], "return *(int *)&x;", ["\treturn *p;"]),
             ("address_pun", ["\treturn (*(int (*)[1])&x)[0];"], "return (*(int (*)[1])&x)[0];", ["\treturn p[0];"]),
             ("cast_call", ["\t((void (*)(int))Foo)(x);"], "((void (*)(int))Foo)(x);", ["\tFoo(p, x);"]),
             ("cast_call", ["\t(*(void (*)(int))Foo)(x);"], "(*(void (*)(int))Foo)(x);", ["\t(*Foo)(p, x);"]),
             ("cast_call", ["\t((Bar)Foo)(x);"], "((Bar)Foo)(x);", ["\t(*(void (*)(int))p->f)(x);"]),
             ("cast_call", ["\treinterpret_cast<void (__cdecl *)(int)>(&Foo)(x);"],
              "reinterpret_cast<void (__cdecl *)(int)>(&Foo)(x);", ["\treinterpret_cast<int *>(p)[0] = x;"]),
             ("address_pun", ["\treinterpret_cast<int *>(&x)[0] = 1;"], "reinterpret_cast<int *>(&x)[0] = 1;",
              ["\treinterpret_cast<int *>(p)[0] = 1;"]),
             ("cast_call", ["\t((void (*)(int))(Foo))(x);"], "((void (*)(int))(Foo))(x);", ["\t((Foo))(p, x);"]),
             ("constant_test", ["\tif (0) x = 1;"], "if (0) x = 1;", ["\twhile (1) x++;"]),
             ("empty_statement", ["\twhile (Bar(x)) ;"], "while (Bar(x)) ;",
              ["\tdo", "\t{", "\t\tx--;", "\t}", "\twhile (x);"]),
             ("empty_block", ["\tif (x)", "\t{", "\t}", "\telse", "\t\tx = 1;"], "{",
              ["\tif (x)", "\t{", "\t\tx = 1;", "\t}"]),
             ("unused_local", ["\tint y;", "\treturn x;"], "y", ["\tint y = x;", "\treturn y;"]),
             ("unused_local", ["\tint *y = p->y;", "\treturn x;"], "y", ["\tint *y = p->y;", "\treturn *y;"]),
             ("address_number", ["\tFoo((int)&DAT_04000002, x);"], "Foo((int)&DAT_04000002, x);",
              ["\tFoo((int)&DAT_0400000c, x);"])]
    failures = []
    for kind, hit, line, plain in cases:
        for body, wanted in ((hit, [(kind, line)]), (plain, [])):
            func = [llm.function_line(ADDRESS), "int Foo(int *p, int x)", "{", *body, "}"]
            found = fakematch.found(func, 1, IMAGE.__contains__)
            if found != wanted:
                failures.append(f"{kind}: {body} gives {found}, not {wanted}")
    return failures


def check_refusal_names() -> list[str]:
    """The refusal of a raw address names the symbol there, and a global that holds it with the offset."""
    symbols = [(0x008a5ce0, "FUN_008a5ce0", None), (0x05cda1d0, "DAT_05cda1d0", 16)]
    cases = [("tp->exec = (void (*)(struct task *))0x8a5ce0;", "0x8a5ce0 is `FUN_008a5ce0`"),
             ("p = (char *)0x5cda1d8;", "0x5cda1d8 is `DAT_05cda1d0 + 0x8`"),
             ("p = (char *)0x5cda1e0;", "use the global or function at that address by its name")]
    failures = []
    for line, wanted in cases:
        note = llm.refusal([("raw_address", line)], lambda a: llm.symbol_at(symbols, a))
        if wanted not in note or (wanted.startswith("use") and " is `" in note):
            failures.append(f"the refusal of {line!r} is {note!r}, without {wanted!r}")
    return failures


def check_constant_globals() -> list[str]:
    """A float or double DAT_ that the reply declares where the exe holds a literal in read-only data is refused, and
    the refusal names the literal. Another type, an array, a named global or an address with no literal is not."""
    literals = {(0x0095cbf8, 4): "0.5f", (0x00956608, 8): "2.0"}

    def literal_at(address, width):
        return literals.get((address, width))

    decls = ["extern float DAT_0095cbf8;", "extern const double DAT_00956608;", "extern int DAT_0095cbf8;",
             "extern float DAT_0095cbf8[2];", "extern float Scale;", "extern float DAT_00a00000;"]
    found = fakematch.constant_globals(decls, literal_at)
    wanted = [("constant_global", "extern float DAT_0095cbf8;"), ("constant_global", "extern const double DAT_00956608;")]
    failures = [] if found == wanted else [f"constant_globals gives {found}, not {wanted}"]
    note = llm.refusal(found[:1], literal_at=literal_at)
    if "write `0.5f` in its place" not in note:
        failures.append(f"the refusal of a constant global is {note!r}, without its literal")
    return failures


def check_annotation_below_signature() -> list[str]:
    """A reply with the annotation between the signature and the body parses as if the annotation were above it."""
    below = "\n".join(["```cpp", "int Foo(void)", llm.function_line(ADDRESS), "{", "\treturn 1;", "}", "```"])
    found = llm.parse_reply(below, ADDRESS)
    wanted = ([], [llm.function_line(ADDRESS), "int Foo(void)", "{", "\treturn 1;", "}"])
    return [] if found == wanted else [f"an annotation below the signature gives {found}, not {wanted}"]


def check_live() -> list[str]:
    """The live file holds the last try: its header, the reply as the client handed it over, then its result."""
    live = solved(2, never_too_long).live
    wanted = [["content", "no code"], {"result": "had no function in the reply"}]
    if not live or live[0].get("try") != 2 or live[0].get("address") != llm.hexa(ADDRESS) or live[1:] != wanted:
        return [f"the live file of 2 tries is {live}, not try 2's header and then {wanted}"]
    return []


def check_live_ends() -> list[str]:
    """A try that ends without a reply closes the live file too, so the page does not wait for its result."""
    def fails(messages):
        raise llmclient.ServerError("boom", 500)

    ended = []
    with mock.patch.object(llm, "end_live", ended.append):
        solved(1, lambda messages: True)
        try:
            solved(1, fails)
        except llmclient.ServerError:
            pass
    wanted = ["even the first prompt is too long for the server", "the server failed: boom"]
    return [] if ended == wanted else [f"the tries without a reply end the live file with {ended}, not {wanted}"]


def sse(*events) -> list[bytes]:
    """Server-sent events as the lines a response gives: a str is a raw line, a dict is a data line."""
    lines = []
    for event in events:
        lines += [(event if isinstance(event, str) else "data: " + json.dumps(event)).encode("utf-8") + b"\n", b"\n"]
    return lines


def check_stream_events() -> list[str]:
    """events joins a stream's pieces into the answer parse reads, hands each piece to on_text as it comes, and
    turns an error event into a ServerError with its code, so a full context is asked again."""
    def delta(**fields):
        return {"choices": [{"delta": fields, "finish_reason": None}]}

    stream = sse(": a comment", delta(reasoning_content="Hm."), delta(content="```cpp\n"), delta(content="}\n```"),
                 {"choices": [{"delta": {}, "finish_reason": "stop"}]},
                 {"choices": [], "usage": {"prompt_tokens": 7, "completion_tokens": 3}}, "data: [DONE]")
    pieces = []
    reply = llmclient.parse(llmclient.events(stream, lambda kind, text: pieces.append((kind, text)), 60))
    failures = []
    wanted = llmclient.Reply("```cpp\n}\n```", "Hm.", {"prompt_tokens": 7, "completion_tokens": 3}, "stop")
    if reply != wanted:
        failures.append(f"the stream gives {reply}, not {wanted}")
    if pieces != [("reasoning", "Hm."), ("content", "```cpp\n"), ("content", "}\n```")]:
        failures.append(f"on_text got {pieces}")
    full = {"code": 500, "message": "Context size has been exceeded."}
    for case, line in (("an error event", "error: " + json.dumps(full)), ("an error in a data line", {"error": full})):
        try:
            llmclient.events(sse(delta(content="x"), line), None, 60)
            failures.append(f"{case} gives no ServerError")
        except llmclient.ServerError as e:
            if e.status != 500 or llmclient.CONTEXT_FULL not in str(e):
                failures.append(f"{case} gives status {e.status} and {e}")
    try:
        llmclient.events(sse(delta(content="int f(){")), None, 60)
        failures.append("a stream that the server closes before its end gives no ServerError")
    except llmclient.ServerError:
        pass
    return failures


def check_full_context_restart() -> list[str]:
    """chat asks again after a full context or a failed draft, and first hands on_text ("restart", ""), so the live
    file starts again."""
    draft_failed = ('{"error":{"code":500,"message":"got exception: speculative batch index 4 is not inside the current '
                    'sub-batch [0, 4)","type":"server_error"}}')
    failures = []
    for error in (llmclient.CONTEXT_FULL, draft_failed):
        answers = [llmclient.ServerError(f"the server failed during the reply: {error}", 500),
                   {"choices": [{"message": {"content": "x"}, "finish_reason": "stop"}]}]

        def call(config, path, body=None, timeout=None, read=None):
            answer = answers.pop(0)
            if isinstance(answer, Exception):
                raise answer
            return answer

        pieces = []
        with (mock.patch.object(llmclient, "call", call),
              mock.patch.object(llmclient.time, "sleep", lambda seconds: None)):
            reply = llmclient.chat(llmclient.DEFAULTS, [], 0.0, False, None,
                                   lambda kind, text: pieces.append((kind, text)))
        if pieces != [("restart", "")] or reply.text != "x":
            failures.append(f"{error} gives the pieces {pieces} and the reply {reply.text!r}, not a restart and 'x'")
    return failures


def check_shared_context() -> list[str]:
    """With shared_context, a request starts after the requests that waited longer, once its prompt and max_tokens fit
    beside the running ones or none runs. chat waits until then, holds its room while the reply runs and frees it
    after. A request of a process that ended holds nothing."""
    failures = []
    requests = {"a": {"pid": 1, "tokens": 20000, "since": 0, "running": True},
                "b": {"pid": 1, "tokens": 30000, "since": 1, "running": False},
                "c": {"pid": 1, "tokens": 2000, "since": 2, "running": False}}
    if llmclient.may_start(requests, "c", 32768):
        failures.append("c starts before b, which waited longer")
    if llmclient.may_start(requests, "b", 32768):
        failures.append("b starts although 20000 and 30000 do not fit in 32768")
    del requests["a"]
    if not llmclient.may_start(requests, "b", 32768):
        failures.append("b waits although nothing runs")
    if not llmclient.may_start({"d": {"pid": 1, "tokens": 40000, "since": 0, "running": False}}, "d", 32768):
        failures.append("a request bigger than the shared context does not start alone")

    ended = subprocess.Popen([sys.executable, "-c", "pass"])
    ended.wait()
    with tempfile.TemporaryDirectory() as folder:
        ledger = Path(folder) / "ledger.json"
        holder = {"pid": os.getpid(), "tokens": 900, "since": 0, "running": True}
        ledger.write_text(json.dumps({"other": holder, "ended": {**holder, "pid": ended.pid}}), encoding="utf-8")
        held, waits = [], []

        def call(config, path, body=None, timeout=None, read=None):
            if path == "/apply-template":
                return {"prompt": "p"}
            if path == "/tokenize":
                return {"tokens": [0] * 100}
            held.append(json.loads(ledger.read_text(encoding="utf-8")))
            return {"choices": [{"message": {"content": "x"}, "finish_reason": "stop"}]}

        def sleep(seconds):
            waits.append(seconds)
            if len(waits) > 3:
                raise RuntimeError("still waiting")
            with llmclient.ledger(ledger) as noted:
                noted.pop("other", None)

        config = {**llmclient.DEFAULTS, "shared_context": 1000, "max_tokens": 200}
        with (mock.patch.object(llmclient, "call", call), mock.patch.object(llmclient, "ledger_path", lambda c: ledger),
              mock.patch.object(llmclient.time, "sleep", sleep)):
            try:
                llmclient.chat(config, [], 0.0, False, None)
            except RuntimeError as e:
                failures.append(f"chat {e} after the room freed up: does a request of an ended process hold room?")
        mine = [r for noted in held for r in noted.values()]
        if len(waits) != 1 or len(mine) != 1 or mine[0]["tokens"] != 300 or not mine[0]["running"]:
            failures.append(f"chat waits {len(waits)} times (not 1) and holds {mine} during the reply, not 300 tokens")
        if json.loads(ledger.read_text(encoding="utf-8")):
            failures.append(f"chat leaves {ledger.read_text(encoding='utf-8')} in the shared file")
    return failures


def run() -> list[str]:
    """Every check of this module, in order."""
    failures = []
    for check in (check_too_long, check_stop_below, check_try_tokens, check_forbidden_reply, check_tries_flag,
                  check_prefix_feedback, check_recipes, check_refuse_fakematch, check_fakematch_kinds, check_refusal_names,
                  check_constant_globals, check_annotation_below_signature, check_live,
                  check_live_ends, check_stream_events, check_full_context_restart, check_shared_context):
        failures += check()
    return failures
