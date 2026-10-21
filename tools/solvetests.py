"""Tests of the try loop in tools/llm.py: solve_function against a fake server, and the --tries flag.

solve_function gets fakes for the file, the dossier and the builds. The fake server refuses a chat as too long for
its context when the case's rule says so, else replies with no code, so no try builds. run() returns the failures as
"<case> gives <found>, not <wanted>".
"""

import argparse
import contextlib
import io
import json
import sys
import tempfile
from pathlib import Path
from unittest import mock

import llm
import llmclient

ADDRESS = 0x00401000
FILE = "src/foo.c"
SEED = 5
TOO_LONG = "http://127.0.0.1:8080/v1/chat/completions answered 400: the request exceeds the available context size"


def solved(tries, too_long):
    """(the seed of each ask, the asks that got a reply, the tries that solve_function returns, the try numbers in
    its transcript) for a run of TRIES against a server that refuses the chats for which TOO_LONG is true."""
    asks = []

    def chat(config, messages, temperature, thinking, seed):
        refused = too_long(messages)
        asks.append((seed, refused))
        if refused:
            raise llmclient.ServerError(TOO_LONG, 400)
        return llmclient.Reply("no code", "", {"prompt_tokens": 1, "completion_tokens": 1}, "stop")

    def first_prompt(config, file, address, types, count, extra):
        return f"{count} examples"

    fakes = {"read_source": lambda path: ('#include "decls.h"\n', False), "write_source": lambda path, text, crlf: None,
             "snapshot": lambda paths: {}, "tree_warnings": lambda config: set(), "load_types": lambda config: None,
             "first_prompt": first_prompt, "file_best": lambda *args: None, "decls": lambda config: ("", 0)}
    settings = {"tables": None, "context": None, "temperature": 0.2, "think_on": None}
    args = argparse.Namespace(settings=settings, system="", tries=tries, seed=SEED, structs=False, accesses=False,
                              facts=False, tree_wins=False, stale_built_only=False, max_repeats=None, give_up=False,
                              think_max=None)
    with (tempfile.TemporaryDirectory() as folder, mock.patch.multiple(llm, **fakes),
          mock.patch.object(llmclient, "chat", chat), contextlib.redirect_stdout(io.StringIO())):
        transcript = Path(folder) / "transcript.jsonl"
        result = llm.solve_function(args, FILE, ADDRESS, transcript)
        logged = [json.loads(line) for line in transcript.read_text(encoding="utf-8").splitlines()]
    return ([seed for seed, _ in asks], sum(not refused for _, refused in asks), result["tries"],
            [entry["try"] for entry in logged if "try" in entry])


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
        found = solved(tries, too_long)
        if found != wanted:
            failures.append(f"{case} gives {found}, not {wanted}")
    return failures


def parsed_tries(argv):
    """The --tries that llm.py gets from the arguments ARGV, or argparse's exit code when it refuses them."""
    with mock.patch.object(sys, "argv", ["llm.py", *argv]), contextlib.redirect_stderr(io.StringIO()):
        try:
            return llm.parse_args().tries
        except SystemExit as error:
            return f"exit {error.code}"


def check_tries_flag() -> list[str]:
    """--tries takes 1 or more. Less stops at argparse's error, before a run that would make no try."""
    cases = [("--tries 1", ["solve", "--tries", "1", FILE, "0x00401000"], 1),
             ("--tries 0", ["solve", "--tries", "0", FILE, "0x00401000"], "exit 2"),
             ("bench --tries -1", ["bench", "--tries", "-1"], "exit 2")]
    failures = []
    for case, argv, wanted in cases:
        found = parsed_tries(argv)
        if found != wanted:
            failures.append(f"{case} gives {found!r}, not {wanted!r}")
    return failures


def run() -> list[str]:
    """Every check of this module, in order."""
    failures = []
    for check in (check_too_long, check_tries_flag):
        failures += check()
    return failures
