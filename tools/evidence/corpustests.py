"""Unit tests for corpus.py: sample calls per tree, left-out slots, spelling keys, lineage and the sample columns of
the proposals. Each check builds a fixture repository in a temp folder, with two sample trees whose header sets
differ.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/corpustests.py
run() calls every check and returns the failures. All names are made up, apart from generic toolchain words.
"""

import json
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import argmap  # noqa: E402
import config  # noqa: E402
import corpus  # noqa: E402
import ctokens  # noqa: E402
import inventory  # noqa: E402
import profiles  # noqa: E402

TARGET_H = """\
#ifndef XX_VENDOR_H
#define XX_VENDOR_H
#define NULL 0
#define XXF_A 0x1
#define XXF_B 0x2
#define XXV_TOP 7
typedef struct XX_T XX_T;
void xxPush(XX_T *m);
void xxFlags(unsigned int flags);
void xxMode(int mode, int other);
void xxGone(int value);
void xxMacro(int value);
void xxWide(int value);
void xxTyped(int value);
#endif
"""

OLD_H = (TARGET_H.replace("#define NULL 0", "#define NULL ((void *)0)").replace("XXV_TOP 7", "XXV_TOP 5")
         .replace("void xxGone(int value);\n", "").replace("void xxMacro(int value);", "#define xxMacro(a) ((a) + 1)")
         .replace("void xxWide(int value);", "void xxWide(int value, int extra);")
         .replace("void xxTyped(int value);", "void xxTyped(long value);"))

SOURCE = """\
#include "vendor.h"

void caller(void)
{
    xxPush(NULL);
    xxFlags(XXF_A);
    xxMode(1, 2);
    xxGone(1);
    xxMacro(1);
    xxWide(1);
    xxTyped(1);
}
"""

ARGMAP = """\
callee,slot,mode,groups,status,header,spelled_type,origins,note
xxPush,1,value,NULL,header prototype,vendor.h,XX_T *,,
xxFlags,1,flags,XXF_,header prototype,vendor.h,unsigned int,,
xxMode,1,value,XXV_,header prototype,vendor.h,int,,
"""


def filler(seed: str, count: int) -> str:
    """COUNT statements of five tokens whose names hold SEED, so that two seeds share no shingle."""
    return "".join(f"int xx_{seed}_{index} = {index};\n" for index in range(count))


MAIN = """\
#include <vendor.h>
#if XX_OLD
void f(void) { xxFlags(XXF_B | XXF_A); }
#else
void f(void) { xxFlags(XXF_A|XXF_B); }
#endif
void g(XX_T *m)
{
    xxPush(NULL);
    xxPush((void *)0);
    s.xxPush(0);
    xxMode(XXV_TOP, 0);
    xxMode(1);
#if XX_OLD
    xxMode(1,
#else
    xxMode(2,
#endif
        0);
    xxFlags(~(XXF_B | XXF_A));
    xxFlags(~XXF_A | XXF_B);
    xxFlags(XXF_A | 0x4);
    xxFlags((XXF_A));
    xxGone(1);
    xxMacro(1);
    xxWide(1);
    xxTyped(1);
}
""" + filler("main", 30)

REWRITE = "void r(void)\n{\n    xxPush(NULL);\n}\n"

FILES = {
    "inc/vendor.h": TARGET_H,
    "old/inc/vendor.h": OLD_H,
    "new/inc/vendor.h": TARGET_H,
    "src/a.c": SOURCE,
    "old/samples/a/main.c": MAIN,
    "new/samples/a/main.c": MAIN,
    "old/samples/c/rewrite.c": REWRITE + filler("old", 30),
    "new/samples/c/rewrite.c": REWRITE + filler("new", 30),
    "old/samples/d/tiny.c": "void t(void) { xxPush(NULL); }\n",
    "new/samples/d/TINY.C": "void t(void) { xxPush(NULL); xxPush(NULL); }\n",
    "new/samples/e/tiny2.c": "void u(void) { xxPush(NULL); }\n",
    "old/samples/g/tri.c": 'void v(void) { xxPush(NULL); }\nchar *s = "??/";\n',
    "old/samples/h/data.c": 'char d[] = "??/";\n',
    "old/samples/h/notes.txt": "xxPush(NULL);\n",
}

CONFIG = {
    "schema": 2,
    "sources": {"root": "src", "suffixes": [".c"], "encoding": "utf-8",
                "annotation": r"//\s*(?P<kind>FUNCTION):\s*XX\s+(?P<address>0x[0-9a-fA-F]+)\s*$"},
    "target": {"name": "game", "profile": "msvc-vc10-x86-cpp", "search_path": ["inc"], "umbrellas": ["vendor.h"]},
    "references": [
        {"name": "old", "profile": "shc-c", "search_path": ["old/inc"], "umbrellas": ["vendor.h"],
         "encoding": "latin-1"},
        {"name": "new", "profile": "shc-c", "search_path": ["new/inc"], "umbrellas": ["vendor.h"],
         "encoding": "latin-1"}],
    "origins": {"vendor": ["inc"]},
    "backups": "backups",
    "kept": ["config.json", "argmap.csv"],
    "samples": {"old": {"folders": ["old/samples"], "reference": "old", "encoding": "cp932"},
                "new": {"folders": ["new/samples"], "reference": "new", "encoding": "cp932"}},
}


def read_fixture(folder: str) -> corpus.Corpus:
    root = Path(folder)
    for name, text in FILES.items():
        (root / name).parent.mkdir(parents=True, exist_ok=True)
        (root / name).write_text(text, encoding="utf-8")
    (root / "old/samples/f").mkdir(parents=True)
    (root / "old/samples/f/bad.c").write_bytes(b"void b(void) { xxPush(NULL); } /* \x81\x20 */\n")
    (root / "evidence").mkdir()
    (root / "evidence" / "config.json").write_text(json.dumps(CONFIG), encoding="utf-8")
    (root / "evidence" / "argmap.csv").write_text(ARGMAP, encoding="utf-8")
    loaded = config.load(root, root / "evidence")
    found = inventory.build(loaded, argmap.read_argmap(root / "evidence" / "argmap.csv"))
    return corpus.read(loaded, found)


def describe(item: corpus.Observation) -> tuple:
    return (item.file, item.callee, item.key, item.kind, item.result.status, item.value)


def check_observations() -> list[str]:
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        read = read_fixture(folder)
    old = [describe(item) for item in read.observations if item.tree == "old" and item.file == "a/main.c"]
    wanted = [
        ("a/main.c", "xxFlags", "XXF_A | XXF_B", "named", "ok", 3),
        ("a/main.c", "xxFlags", "XXF_A | XXF_B", "named", "ok", 3),
        ("a/main.c", "xxPush", "NULL", "named", "ok", 0),
        ("a/main.c", "xxPush", "( void * ) 0", "literal", "ok", 0),
        ("a/main.c", "xxMode", "XXV_TOP", "named", "ok", 5),
        ("a/main.c", "xxMode", "1", "", "unsupported", None),
        ("a/main.c", "xxMode", "2", "literal", "ok", 2),
        ("a/main.c", "xxFlags", "~(XXF_A | XXF_B)", "named", "ok", 0xFFFFFFFC),
        ("a/main.c", "xxFlags", "~ XXF_A | XXF_B", "named", "ok", 0xFFFFFFFE),
        ("a/main.c", "xxFlags", "XXF_A | 4", "mixed", "ok", 5),
        ("a/main.c", "xxFlags", "XXF_A", "named", "ok", 1),
    ]
    if old != wanted:
        failures.append(f"old tree, every branch kept, member calls and branch joins dropped: got {old}")
    new = {(item.callee, item.value) for item in read.observations if item.tree == "new" and item.file == "a/main.c"}
    if ("xxMode", 7) not in new or ("xxMode", 5) in new:
        failures.append(f"each tree evaluates under its own headers: got {sorted(new, key=str)}")
    if not {("xxGone", 1), ("xxMacro", 1), ("xxWide", 1), ("xxTyped", 1)} <= new:
        failures.append("the new tree reads the slots the old tree leaves out")
    arity = next(item for item in read.observations if item.result.status == "unsupported")
    if arity.result.cause != "arity":
        failures.append(f"a call whose argument count does not fit: {arity.result}")
    return failures


def check_left_out() -> list[str]:
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        read = read_fixture(folder)
    wanted = {("xxGone", 1): "no prototype", ("xxMacro", 1): "function-like macro", ("xxWide", 1): "arity differs",
              ("xxTyped", 1): "slot type differs"}
    if read.trees["old"].left_out != wanted:
        failures.append(f"left out of the old tree: got {read.trees['old'].left_out}")
    if read.trees["new"].left_out:
        failures.append(f"nothing left out of the new tree: got {read.trees['new'].left_out}")
    if any(item.callee in ("xxGone", "xxMacro", "xxWide", "xxTyped") for item in read.observations
           if item.tree == "old"):
        failures.append("a left-out slot gives no observation")
    return failures


def check_files() -> list[str]:
    """A decode failure and a tokenizer failure are listed; a file with no wanted callee is never tokenized; only
    source suffixes count, case ignored."""
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        read = read_fixture(folder)
    old, new = read.trees["old"], read.trees["new"]
    reasons = sorted((file, reason.split(":")[0]) for file, reason in old.failures)
    if reasons != [("f/bad.c", "does not decode as cp932"), ("g/tri.c", "trigraph")]:
        failures.append(f"failures: got {old.failures}")
    if (old.files, new.files) != (6, 4):
        failures.append(f"files with a source suffix: got {old.files} and {new.files}")
    if not any(item.file == "d/TINY.C" for item in read.observations):
        failures.append("an upper-case suffix counts")
    nodes = {item.node for item in read.observations if item.file == "a/main.c"}
    trees = {item.tree for item in read.observations if item.file == "a/main.c"}
    if len(nodes) != 1 or trees != {"old", "new"}:
        failures.append(f"an exact copy in two trees is one node read in each: {len(nodes)} nodes, trees {trees}")
    return failures


def check_lineage() -> list[str]:
    """Exact copies are one node; a same-path rewrite splits; sparse files join only on a shared path."""
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        read = read_fixture(folder)
    by_file = {}
    for item in read.observations:
        if item.callee == "xxPush" and item.value == 0:
            by_file[item.tree, item.file] = item.node
    lineages = read.lineage(set(by_file.values()))
    groups = [sorted({file for (tree, file), node in by_file.items() if node in cluster}) for cluster in lineages]
    if len(lineages) != 5:
        failures.append(f"five lineages: got {groups}")
    tiny = {by_file["old", "d/tiny.c"], by_file["new", "d/TINY.C"]}
    if not any(tiny <= cluster for cluster in lineages):
        failures.append("two sparse files on one path, case ignored, are one lineage")
    if any(by_file["new", "e/tiny2.c"] in cluster and len(cluster) > 1 for cluster in lineages):
        failures.append("a sparse file on its own path is alone")
    rewrites = {by_file["old", "c/rewrite.c"], by_file["new", "c/rewrite.c"]}
    if any(rewrites <= cluster for cluster in lineages):
        failures.append("a same-path rewrite splits")
    same, other = read.histograms()
    if same[0] != 1 or sum(same) != 1 or sum(other) != 2:
        failures.append(f"histograms of the dense pairs: got {same} and {other}")
    return failures


def check_spelling_keys() -> list[str]:
    profile = profiles.PROFILES["shc-c"]
    cases = {
        "B | A": ("A | B", ("A", "B"), False),
        "((A))": ("A", ("A",), False),
        "~(B | A)": ("~(A | B)", ("A", "B"), True),
        "(~(A))": ("~A", ("A",), True),
        "~A | B": ("~ A | B", (), False),
        "~(A) | B": ("~ ( A ) | B", (), False),
        "A | 0x4": ("A | 4", (), False),
        "(void *)0": ("( void * ) 0", (), False),
        "0x10u": ("16u", (), False),
    }
    got = {text: corpus.spelling_key(ctokens.tokens_of(text), profile) for text in cases}
    return [] if got == cases else [f"spelling keys: got {got}"]


def check_sample_calls() -> list[str]:
    with tempfile.TemporaryDirectory() as folder:
        read = read_fixture(folder)
    lines = corpus.sample_calls_text(read, 3).splitlines()
    failures = []
    if lines[0] != "# evidence-sample-calls generation=3" or lines[1] != ",".join(corpus.SAMPLE_CALL_COLUMNS):
        failures.append(f"sample-calls header: got {lines[:2]}")
    if len(lines) != 2 + len(read.observations):
        failures.append("one row per observation")
    tiny = [line.split(",") for line in lines if "/tiny.c," in line.lower()]
    if len({row[-1] for row in tiny}) != 1 or not tiny[0][-1]:
        failures.append(f"one lineage label for one lineage: got {tiny}")
    return failures


def check_proposals() -> list[str]:
    """The lineages at the slot and the named spellings with their lineages; a literal-only slot has no spelling; a
    slot that no tree reads keeps both columns empty."""
    with tempfile.TemporaryDirectory() as folder:
        read = read_fixture(folder)
    rows = [("xxPush", 1, 9, "0", "vendor.h", "XX_T *", "", ""), ("xxGone", 1, 1, "1", "vendor.h", "int", "", ""),
            ("xxNone", 1, 1, "1", "vendor.h", "int", "", "")]
    wanted = [("xxPush", 1, 9, "0", "vendor.h", "XX_T *", 5, "NULL 5"), ("xxGone", 1, 1, "1", "vendor.h", "int", 1, ""),
              ("xxNone", 1, 1, "1", "vendor.h", "int", "", "")]
    got = corpus.sampled_proposals(read, rows)
    failures = [] if got == wanted else [f"proposals: got {got}"]
    flags = corpus.sampled_proposals(read, [("xxFlags", 1, 1, "3", "vendor.h", "unsigned int", "", "")])[0]
    if flags[-2:] != (1, "XXF_A 1; XXF_A | XXF_B 1; ~ XXF_A | XXF_B 1; ~(XXF_A | XXF_B) 1"):
        failures.append(f"named spellings only, by lineages then text: got {flags[-2:]}")
    return failures


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_observations, check_left_out, check_files, check_lineage, check_spelling_keys,
                  check_sample_calls, check_proposals):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    print("\n".join(found) or "corpustests: all passed")
    sys.exit(1 if found else 0)
