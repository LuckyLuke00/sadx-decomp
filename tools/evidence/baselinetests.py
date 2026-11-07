"""Unit tests for baseline.py: each cause on a seeded old row, the new-only rows, the file faults and the run. Each
check builds a fixture repository in a temp folder.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/baselinetests.py
run() calls every check and returns the failures. All names are made up, apart from generic toolchain words.
"""

import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import argmap  # noqa: E402
import baseline  # noqa: E402
import inventory  # noqa: E402
import inventorytests  # noqa: E402

VENDOR = """\
#ifndef XX_VENDOR_H
#define XX_VENDOR_H
#define NULL 0
#define TRUE 1
#define XXF_A 0x1
#define XXF_B 0x2
#define XXF_AB 0x3
#define XXM_ONE 1
#if 0
#define XXM_TWO 2
#else
#define XXM_TWO 3
#endif
#define xxMacro(a) ((a) + 1)
typedef struct XX_T XX_T;
void xxPush(XX_T *m);
void xxFlags(unsigned int flags);
void xxMode(int mode, int other);
void xxZ(long on);
#endif
"""

A_C = """\
#include "vendor.h"

void caller(XX_T *m)
{
    xxPush(0);
    xxPush(NULL);
    xxPush(m);
    xxFlags(-1);
    xxMode((short)0x18000, 0);
    xxMode(2, 0);
    xxZ(1);
    xxFlags(3);
    xxMode(1, 0);
    xxMacro(2);
    __xxPush(0);
    const char *s = "xxMode(1, 2)";
    const char *u = "a//b"; xxMode(1, 0);
    xxFlags(1 + 2);
    xxMode(1, 1); xxMode(1, 1);
}
"""

FILES = {
    "inc/vendor.h": VENDOR,
    "src/a.c": A_C,
    "src/b.c": "#if XX_ON\n#endif\nvoid g(void)\n{\n    xxMode(1, 0);\n}\n",
    "src/local.h": "xxMode(1, 0);\n",
}

ARGMAP = """\
callee,slot,mode,groups,status,header,spelled_type,origins,note
xxPush,1,value,NULL,header prototype,vendor.h,XX_T *,,
xxFlags,1,flags,XXF_,header prototype,vendor.h,unsigned int,,
xxMode,1,value,XXM_,header prototype,vendor.h,int,,
xxMacro,1,value,XXM_,unverified,,,,
xxZ,1,value,TRUE,unverified,,,,
"""

# The old rows, one per cause, with the faults of the first scanner seeded in.
OLD = """\
file,line,callee,arg,literal,value,candidates
a.c,5,xxPush,1,0,0,NULL (vendor.h)
a.c,8,xxFlags,1,-1,-1,
a.c,9,xxMode,1,(short)0x18000,98304,
a.c,10,xxMode,1,2,2,XXM_TWO (vendor.h)
a.c,11,xxZ,1,1,1,TRUE (vendor.h)
a.c,12,xxFlags,1,3,3,XXF_A | XXF_B (bit flags)
a.c,13,xxMode,1,1,1,
a.c,14,xxMacro,1,2,2,
a.c,15,__xxPush,1,0,0,NULL (vendor.h)
a.c,16,xxMode,1,1,1,XXM_ONE (vendor.h)
a.c,19,xxMode,1,1,1,XXM_ONE (vendor.h)
a.c,4,xxMode,1,1,1,
b.c,5,xxMode,1,1,1,XXM_ONE (vendor.h)
local.h,1,xxMode,1,1,1,XXM_ONE (vendor.h)
"""

WANTED = {
    ("old", baseline.SAME, "src/a.c", 5),
    ("old", baseline.CONVERTED, "src/a.c", 8),
    ("old", baseline.CAST, "src/a.c", 9),
    ("old", baseline.DEFINITION, "src/a.c", 10),
    ("old", baseline.TYPE_GATE, "src/a.c", 11),
    ("old", baseline.RANK, "src/a.c", 12),
    ("old", baseline.SEARCH, "src/a.c", 13),
    ("old", baseline.MACRO, "src/a.c", 14),
    ("old", baseline.STRIPPED, "src/a.c", 15),
    ("old", baseline.IN_STRING, "src/a.c", 16),
    ("old", baseline.SAME, "src/a.c", 19),
    ("old", baseline.UNEXPLAINED, "src/a.c", 4),
    ("old", baseline.UNSUPPORTED_FILE, "src/b.c", 5),
    ("old", baseline.NOT_READ, "src/local.h", 1),
    ("new", baseline.NAMES, "src/a.c", 6),
    ("new", baseline.NONCONSTANT, "src/a.c", 7),
    ("new", baseline.COMMENT_CUT, "src/a.c", 17),
    ("new", baseline.NOT_PLAIN, "src/a.c", 18),
    ("new", baseline.NOT_IN_BASELINE, "src/a.c", 19),
}


def repository(folder: str) -> tuple:
    """The fixture repository in FOLDER with the baseline in place: (loaded config, argmap rows)."""
    loaded, _ = inventorytests.repository(folder, FILES)
    (loaded.folder / "argmap.csv").write_text(ARGMAP, encoding="utf-8")
    (loaded.folder / baseline.BASELINE).write_text(OLD, encoding="utf-8")
    return loaded, argmap.read_argmap(loaded.folder / "argmap.csv")


def where(entry: baseline.Entry) -> tuple:
    found = entry.old or entry.new
    return entry.side, entry.cause, found.file, found.line


def check_causes() -> list[str]:
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        loaded, rows = repository(folder)
        old = baseline.read_baseline(loaded.folder / baseline.BASELINE, baseline.prefix(loaded))
        entries = baseline.diff(inventory.build(loaded, rows), old, loaded, rows)
    got = [where(entry) for entry in entries]
    failures += [f"cause {item}" for item in sorted(set(got) - WANTED)]
    failures += [f"missing cause {item}" for item in sorted(WANTED - set(got))]
    if len(got) != len(set(got)):
        failures.append(f"each row has one cause: {sorted(got)}")
    twin = [entry.new for entry in entries if entry.new and entry.new.line == 19]
    if [record.column for record in twin] != [5, 19]:
        failures.append(f"rows with one key pair in order: columns {[record.column for record in twin]}")
    if baseline.unexplained(entries) != 1 or baseline.summary(entries)[-1] != "unexplained old rows: 1":
        failures.append(f"summary {baseline.summary(entries)}")
    text = baseline.format_diff(entries, 4).split("\n")
    if text[:2] != ["# evidence-baseline-diff generation=4", ",".join(baseline.DIFF_COLUMNS)] or len(text) != 22:
        failures.append(f"diff file {text[:2]}, {len(text)} lines")
    return failures


def check_faults() -> list[str]:
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        root = Path(folder)
        for name, text, wanted in (("columns.csv", "file,line,callee\n", "the columns must be"),
                                   ("line.csv", OLD.replace("a.c,5,", "a.c,five,"), "line.csv:2"),
                                   ("value.csv", OLD.replace(",98304,", ",0x18000,"), "value.csv:4")):
            (root / name).write_text(text, encoding="utf-8")
            try:
                baseline.read_baseline(root / name, "")
                failures.append(f"{name} reads")
            except baseline.BaselineError as error:
                if wanted not in str(error):
                    failures.append(f"{name}: {error}")
        try:
            baseline.read_baseline(root / "none.csv", "")
            failures.append("a missing baseline reads")
        except baseline.BaselineError as error:
            if "none.csv" not in str(error):
                failures.append(f"missing baseline: {error}")
        (root / "evidence").mkdir()
        (root / "old.csv").write_text(OLD, encoding="utf-8")
        copy = baseline.import_baseline(root / "old.csv", root / "evidence")
        if copy.read_text(encoding="utf-8") != OLD:
            failures.append("the import copies the file")
        try:
            baseline.import_baseline(root / "old.csv", root / "evidence")
            failures.append("a second import overwrites the baseline")
        except baseline.BaselineError:
            pass
    return failures


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_causes, check_faults):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    print("\n".join(found) or "baselinetests: all passed")
    sys.exit(1 if found else 0)
