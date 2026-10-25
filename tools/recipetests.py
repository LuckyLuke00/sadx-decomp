"""Checks for tools/recipes.py: which recipes count as a plan without code, and which try of an llm.py transcript
counts as the local model's win."""

import json
import tempfile
from pathlib import Path

import project
import recipes

TARGET = project.game_config().target
PLAN = "1. Load the second argument and test it.\n2. Return early when it is zero.\n"


def check_recipe_problems() -> list[str]:
    """A plan of short numbered steps passes. A code block, a line with `;`, `{` or `}`, no step and too many steps
    each fail it."""
    many = "".join(f"{i}. Step {i}.\n" for i in range(1, recipes.MAX_STEPS + 2))
    cases = [("a plain plan", PLAN, 0), ("a code block", PLAN + "```\nreturn\n```\n", 1),
             ("a code line", PLAN + "3. Write x = 1; there.\n", 1), ("a brace", PLAN + "3. Open a { here.\n", 1),
             ("no step", "Load it and return.\n", 1), ("too many steps", many, 1)]
    return [f"recipe_problems finds {len(recipes.recipe_problems(text))} problems in {name}, not {wanted}"
            for name, text, wanted in cases if len(recipes.recipe_problems(text)) != wanted]


def reply(*body):
    lines = [f"// FUNCTION: {TARGET} 0x00401000", "void FUN_00401000(void)", "{", *body, "}"]
    return "```cpp\n" + "\n".join(lines) + "\n```"


def check_winning_reply() -> list[str]:
    """The first try at 100% wins, with its block. A try below 100%, a repeat and a win with a trick word don't."""
    records = [{"prompt": "p"}, {"try": 1, "result": "80.00%", "reply": reply()},
               {"try": 2, "result": "repeat of try 1", "reply": reply()},
               {"try": 3, "result": "100.00%", "reply": reply("\t__asm nop")},
               {"try": 4, "result": "100.00%", "reply": reply()}, {"try": 5, "result": "100.00%", "reply": "none"}]
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder) / "00401000.jsonl"
        path.write_text("".join(json.dumps(record) + "\n" for record in records), encoding="utf-8")
        won = recipes.winning_reply(path, 0x401000)
    if won != (reply(), 4):
        return [f"winning_reply gives {won}, not try 4 and its block"]
    return []


def run() -> list[str]:
    """Every check of this module, in order."""
    failures = []
    for check in (check_recipe_problems, check_winning_reply):
        failures += check()
    return failures
