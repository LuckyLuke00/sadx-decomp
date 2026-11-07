"""Unit tests for inventory.py: sites, values, candidates, flags, proposals, and the files of a commit (ledger.commit).
Each check builds a fixture repository in a temp folder.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/inventorytests.py
run() calls every check and returns the failures. All names are made up, apart from generic toolchain words.
"""

import json
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import argmap  # noqa: E402
import config  # noqa: E402
import ctokens  # noqa: E402
import fields  # noqa: E402
import inventory  # noqa: E402
import ledger  # noqa: E402
import profiles  # noqa: E402
import state  # noqa: E402
import symbols  # noqa: E402

CPP = profiles.PROFILES["msvc-vc10-x86-cpp"]

VENDOR = """\
#ifndef XX_VENDOR_H
#define XX_VENDOR_H
#define NULL 0
#define XXF_NONE 0
#define XXF_A 0x1
#define XXF_B 0x2
#define XXF_C 0x4
#define XXM_ONE 1
#define xxMacro(a) ((a) + 1)
#define XX_ASSERT() ((void)0)
#define XX_GUESS(a, b) xxMode(a, b)
typedef struct XX_T XX_T;
void xxPush(XX_T *m);
void xxFlags(unsigned int flags);
void xxMode(int mode, int other);
int xxCount(unsigned int flags);
void xxUnmapped(int value);
#endif
"""

A_C = """\
#include "vendor.h"

// FUNCTION: XX 0x00401000
void caller(XX_T *m, int local)
{
    xxPush(0);
    xxPush(NULL);
    xxPush(m);
    xxFlags(XXF_A | 0x4);
    xxFlags(3);
    xxFlags((0x0));
    xxMode(1, local);
    xxMode(1);
    xxMode(XX_UNKNOWN, 0);
    xxUnmapped(5);
    xxMacro(2);
    xxUnmapped(xxCount(XXF_A));
}
"""

FILES = {
    "inc/vendor.h": VENDOR,
    "src/a.c": A_C,
    "src/b.c": "#if XX_ON\nint xx;\n#endif\n",
    "src/c.c": "void other(void)\n{\n    xxFlags(XXF_B);\n}\n",
}

ARGMAP = """\
callee,slot,mode,groups,status,header,spelled_type,origins,note
xxPush,1,value,NULL,header prototype,vendor.h,XX_T *,,
xxFlags,1,flags,XXF_,header prototype,vendor.h,unsigned int,,
xxMode,1,value,XXM_,header prototype,vendor.h,int,,
xxCount,1,flags,XXF_,header prototype,vendor.h,int,,
xxMacro,1,value,XXM_,unverified,,,,
"""

CONFIG = {
    "schema": 2,
    "sources": {"root": "src", "suffixes": [".c"], "encoding": "utf-8",
                "annotation": r"//\s*(?P<kind>FUNCTION):\s*XX\s+(?P<address>0x[0-9a-fA-F]+)\s*$"},
    "target": {"name": "game", "profile": "msvc-vc10-x86-cpp", "search_path": ["inc"], "umbrellas": ["vendor.h"]},
    "origins": {"vendor": ["inc"]},
    "backups": "backups",
    "kept": ["config.json", "argmap.csv"],
}


def repository(folder: str, files: dict = FILES, settings: dict = CONFIG) -> tuple:
    """The fixture repository in FOLDER, with config.json SETTINGS: (loaded config, argmap rows)."""
    root = Path(folder)
    for name, text in files.items():
        (root / name).parent.mkdir(parents=True, exist_ok=True)
        (root / name).write_text(text, encoding="utf-8")
    (root / "evidence").mkdir(exist_ok=True)
    (root / "evidence" / "config.json").write_text(json.dumps(settings), encoding="utf-8")
    (root / "evidence" / "argmap.csv").write_text(ARGMAP, encoding="utf-8")
    loaded = config.load(root, root / "evidence")
    return loaded, argmap.read_argmap(root / "evidence" / "argmap.csv")


def committed(loaded, rows, today: str = "2026-01-01") -> tuple:
    """A run up to its commit, with no sample corpus: inventory.build, then ledger.commit. Returns (the inventory, the
    commit)."""
    found = inventory.build(loaded, rows)
    return found, ledger.commit(loaded, found, today)


def describe(record: inventory.Record) -> tuple:
    result = record.result
    top = record.search.candidates[0].text if record.search and record.search.candidates else ""
    return (record.callee, record.slot, record.expression, result.status, result.cause, record.value, record.state,
            top, tuple(record.flags))


def check_sites() -> list[str]:
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        found = inventory.build(*repository(folder))
    wanted = [
        ("xxPush", "1", "0", "ok", "", "0", "open", "NULL", ()),
        ("xxPush", "1", "NULL", "ok", "", "0", "applied", "NULL", ()),
        ("xxPush", "1", "m", "nonconstant", "variable", "", "open", "", ()),
        ("xxFlags", "1", "XXF_A | 4", "ok", "", "5", "open", "XXF_A | XXF_C", ("partial",)),
        ("xxFlags", "1", "3", "ok", "", "3", "open", "XXF_A | XXF_B", ()),
        ("xxFlags", "1", "0", "ok", "", "0", "open", "XXF_NONE", ()),
        ("xxMode", "1", "1", "ok", "", "1", "open", "XXM_ONE", ()),
        ("xxMode", "1", "1", "unsupported", "arity", "", "open", "", ()),
        ("xxMode", "1", "XX_UNKNOWN", "unresolved", "unknown identifier", "", "open", "", ()),
        ("xxCount", "xxUnmapped#1/1", "XXF_A", "ok", "", "1", "applied", "XXF_A", ()),
        ("xxFlags", "1", "XXF_B", "ok", "", "2", "applied", "XXF_B", ("include",)),
    ]
    got = [describe(record) for record in found.records]
    if got != wanted:
        failures += [f"site {index}: {item}" for index, item in enumerate(got) if index >= len(wanted)
                     or item != wanted[index]]
        failures += [f"missing site {item}" for item in wanted[len(got):]]
    if [record.owner for record in found.records[:2]] != ["0x00401000"] * 2 or found.records[-1].owner != "src/c.c:other":
        failures.append(f"owners {[record.owner for record in found.records]}")
    if found.unsupported_files != [("src/b.c", "#if")] and [file for file, _ in found.unsupported_files] != ["src/b.c"]:
        failures.append(f"unsupported files {found.unsupported_files}")
    if found.macro_calls != 1:
        failures.append(f"a function-like macro callee is no site: {found.macro_calls}")
    if found.proposed != [("xxUnmapped", 1, 1, "5", "vendor.h", "int", "", "")]:
        failures.append(f"proposals {found.proposed}")
    if any(record.check.reason for record in found.records if record.callee in ("xxPush", "xxFlags", "xxMode")):
        failures.append(f"checks {[(record.callee, record.check.reason) for record in found.records]}")
    count = next(record for record in found.records if record.callee == "xxCount")
    if not count.check.reason.startswith("vendor.h spells argument 1 'unsigned int'"):
        failures.append(f"a spelled type that differs fails the check: {count.check}")
    if len({record.context for record in found.records[:3]}) != 3 or len(found.records[0].context) != 16:
        failures.append(f"contexts {[record.context for record in found.records[:3]]}")
    return failures


D_C = """\
#include "vendor.h"

// FUNCTION: XX 0x00402000
void guarded(int value)
{
    XX_ASSERT();
    XX_ASSERT(value < 16);
    XX_GUESS(1, 2);
}
"""


def check_placeholders() -> list[str]:
    """Each use of a listed placeholder macro is a placeholder site: in coverage, open, with no value. Its prototype
    text holds the hash of the macro's definition, and a literal inside a no-code macro gets a flag."""
    failures = []
    settings = dict(CONFIG, placeholders={"XX_ASSERT": "no-code", "XX_GUESS": "code"})
    files = dict(FILES, **{"src/d.c": D_C})
    with tempfile.TemporaryDirectory() as folder:
        found = inventory.build(*repository(folder, files, settings))
        plain = inventory.build(*repository(folder, files))
        changed = dict(files, **{"inc/vendor.h": VENDOR.replace("((void)0)", "((void)1)")})
        redefined = inventory.build(*repository(folder, changed, settings))
    held = [record for record in found.records if record.kind == inventory.PLACEHOLDER]
    got = [(record.target, record.slot, record.argument, record.expression, record.row.note, record.covered,
            record.state, record.value, tuple(record.flags)) for record in held]
    wanted = [("XX_ASSERT", "", "XX_ASSERT()", "", "no-code", True, "open", "", ()),
              ("XX_ASSERT", "", "XX_ASSERT(value < 16)", "value < 16", "no-code", True, "open", "",
               ("literal inside a no-code macro",)),
              ("XX_GUESS", "", "XX_GUESS(1, 2)", "1 , 2", "code", True, "open", "", ())]
    if got != wanted:
        failures.append(f"placeholder sites {got}")
    if found.unmapped != plain.unmapped - 3:
        failures.append(f"a placeholder use is no unmapped call: {found.unmapped} against {plain.unmapped}")
    if any(record.kind == inventory.PLACEHOLDER for record in plain.records):
        failures.append("only listed macros are placeholders")
    if len(held) == 3 and (not held[0].prototype.startswith("definition ") or held[0].prototype == held[2].prototype):
        failures.append(f"prototype texts {[record.prototype for record in held]}")
    moved = [record.prototype for record in redefined.records if record.kind == inventory.PLACEHOLDER]
    if len(held) == 3 and (moved[0] == held[0].prototype or moved[2] != held[2].prototype):
        failures.append("a changed definition changes its sites' prototype text, and only theirs")
    if {record.kind for record in found.records if record.callee == "xxFlags"} != {inventory.CALL}:
        failures.append("a mapped argument is a call site")
    return failures


FIELD_TYPES = """\
#define XXE_HIDE 0x8
#define XXE_SKIP 0x10
typedef struct xxobj {
    unsigned int flags;
    struct xxobj *child;
    unsigned int bits : 2;
} XX_OBJ;
typedef struct xxcnk {
    unsigned int flags;
} XX_CNK;
"""

E_C = """\
#include "vendor.h"

// FUNCTION: XX 0x00403000
void walk(XX_OBJ *op, XX_CNK *cp, void *raw)
{
    op->flags = XXE_HIDE;
    op->flags |= 0x10;
    op->flags &= ~0x8;
    xxFlags(op->flags & 0x18);
    op->child = 0;
    op->bits = 1;
    cp->flags = 8;
    ((XX_OBJ *)raw)->flags = 8;
    unknown->flags = 0x10;
    op->other = 1;
    switch (op->flags) {
    case 1:
        break;
    }
    *(int *)((char *)raw + 4) = 0;
}
"""

FIELDMAP = """\
type,member,mode,groups,status,header,spelled_type,origins,note
XX_OBJ,flags,flags,XXE_,header declaration,vendor.h,unsigned int,,
struct xxcnk,flags,flags,XXE_,unverified,,,,
XX_OBJ,child,value,NULL,header declaration,vendor.h,struct xxobj *,,
XX_NONE_T,flags,flags,XXE_,unverified,,,,
"""
FIELD_FILES = dict(FILES, **{"inc/vendor.h": VENDOR.replace("#endif\n", FIELD_TYPES + "#endif\n"), "src/e.c": E_C})


def fielded(folder: str, files: dict, fieldmap: str, settings: dict = CONFIG) -> inventory.Inventory:
    loaded, rows = repository(folder, files, settings)
    (Path(folder) / "evidence" / fields.FIELDMAP).write_text(fieldmap, encoding="utf-8")
    return inventory.build(loaded, rows)


def check_fields() -> list[str]:
    """A spot of a mapped member is a field site: its target is the type id and the member, its slot the operator,
    its value converted to the member type, and the operator sets the mode. A base that does not type falls back on
    the member name. Bitfields, unmapped members, case labels and raw offsets are counted. A body in the row's header
    that types the member otherwise is counterevidence."""
    failures = []
    files = FIELD_FILES
    with tempfile.TemporaryDirectory() as folder:
        found = fielded(folder, files, FIELDMAP)
    held = [record for record in found.records if record.kind == inventory.FIELD]
    obj = ("struct xxobj.flags", "XX_OBJ.flags")
    wanted = [
        (*obj, "=", "XXE_HIDE", "ok", "", "8", "applied", "XXE_HIDE", ()),
        (*obj, "|=", "16", "ok", "", "16", "open", "XXE_SKIP", ()),
        (*obj, "&=", "~ 8", "ok", "", "4294967287", "open", "~XXE_HIDE", ()),
        (*obj, "&", "24", "ok", "", "24", "open", "XXE_HIDE | XXE_SKIP", ()),
        ("struct xxobj.child", "XX_OBJ.child", "=", "0", "ok", "", "0", "open", "NULL", ()),
        ("struct xxcnk.flags", "struct xxcnk.flags", "=", "8", "ok", "", "8", "open", "XXE_HIDE", ()),
        (*obj, "=", "8", "ok", "", "8", "open", "XXE_HIDE", ()),
        ("?.flags", "struct xxcnk.flags", "=", "16", "ok", "", "16", "open", "XXE_SKIP",
         (inventory.MEMBER_NAME_ONLY,)),
    ]
    got = [(record.target, *describe(record)) for record in held]
    if got != wanted:
        failures += [f"field site {index}: {item}" for index, item in enumerate(got) if index >= len(wanted)
                     or item != wanted[index]]
        failures += [f"missing field site {item}" for item in wanted[len(got):]]
    counts = {"spots": 10, "unmapped": 1, "bitfields": 1, "case labels": 1, "raw offsets": 1}
    if dict(found.field_counts) != counts:
        failures.append(f"field counts {dict(found.field_counts)}")
    checks = {record.callee: record.check.reason for record in held}
    if checks != {"XX_OBJ.flags": "", "XX_OBJ.child": "", "struct xxcnk.flags": "unverified row"}:
        failures.append(f"member checks {checks}")
    first = ("member unsigned int", ("vendor",), "0x00403000")
    if held and (held[0].prototype, held[0].accepted, held[0].owner) != first:
        failures.append(f"first field site {held[0].prototype!r}, {held[0].accepted}, {held[0].owner}")
    if len(found.field_rows) != 4 or not any("type XX_NONE_T has no struct or union body" in warning
                                             for warning in found.warnings):
        failures.append(f"fieldmap rows {len(found.field_rows)}, warnings {found.warnings}")

    sdk = "typedef struct xxobj {\n    int flags;\n} XX_OBJ;\n"
    settings = dict(CONFIG, references=[{"name": "sdk", "profile": "shc-c", "search_path": ["ref"],
                                         "umbrellas": ["sdk.h"], "encoding": "latin-1"}])
    row = FIELDMAP.split("\n")[0] + "\nXX_OBJ,flags,flags,XXE_,header declaration,sdk.h,int,,\n"
    with tempfile.TemporaryDirectory() as folder:
        other = fielded(folder, dict(files, **{"ref/sdk.h": sdk}), row, settings)
    marked = {(record.check.reason, tuple(record.flags)) for record in other.records if record.kind == inventory.FIELD
              and record.callee == "XX_OBJ.flags"}
    if marked != {("", ("target member differs",))}:
        failures.append(f"a reference body that types the member otherwise: {marked}")
    return failures


G_C = """\
#include "vendor.h"

// FUNCTION: XX 0x00404000
void xxGame(int unused, int mode)
{
}

// FUNCTION: XX 0x00405000
int xxGetMode(void)
{
    return 1;
}

// FUNCTION: XX 0x00406000
void stepper(int step, XX_OBJ *op)
{
    int mode = 0;
    xxGame(0, 2);
    step = 0;
    step = 1;
    if (step == 2) {
    }
    switch (step) {
    case 1:
        break;
    }
    op->flags = 1;
    op->flags |= 2;
    mode = 7;
}

void plain(int step)
{
    step = 1;
    return;
}
"""

REFERENCE_FILES = {
    "prototypes.csv": ("address,name,slot,type\n"
                       "0x00404000,xxGame,0,void\n0x00404000,xxGame,1,int\n0x00404000,xxGame,2,enum XX_MODE\n"
                       "0x00405000,xxGetMode,0,enum XX_MODE\n"),
    "enums.csv": ("enum,name,value\n"
                  "enum XX_MODE,XX_MODE_OFF,0\nenum XX_MODE,XX_MODE_ON,1\nenum XX_MODE,XX_MODE_AUTO,2\n"),
    "scope-constants.csv": ("address,scope,name,value\n"
                            "0x00406000,enum STEP,STEP_INIT,0\n0x00406000,enum STEP,STEP_RUN,1\n"
                            "0x00406000,enum STEP,STEP_EXIT,2\n0x00406000,enum KIND,KIND_A,1\n"),
}
SYMBOL_FILES = dict(FIELD_FILES, **{"src/g.c": G_C})


def referenced(folder: str, files: dict = SYMBOL_FILES, symbol_files: dict = REFERENCE_FILES) -> tuple:
    """The fixture repository in FOLDER with SYMBOL_FILES in its evidence folder: (loaded config, argmap rows)."""
    loaded, rows = repository(folder, files)
    for name, text in symbol_files.items():
        (Path(folder) / "evidence" / name).write_text(text, encoding="utf-8")
    return loaded, rows


def check_symbols() -> list[str]:
    """With reference symbols: an enum slot of a game callee is a call site, a return in a function whose reference
    return type is an enum is a return site, and in a function with scope constants the variable writes and compares,
    the case labels and the unmapped field spots are scope sites. The lvalue check narrows a lvalue's names to the
    scope it passes for. Call arguments are no scope sites, and a function with no scope constants gives none."""
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        loaded, rows = referenced(folder)
        found = inventory.build(loaded, rows)
        _, made = committed(loaded, rows)
    held = [record for record in found.records if record.file == "src/g.c"]
    lvalue, one = symbols.LVALUE_CHECK, symbols.ONE_ENUMERATOR
    wanted = [
        ("variable", "mode", "=", "0", "STEP_INIT", ("enum KIND", "enum STEP"), ()),
        ("call", "0x00404000", "2", "2", "XX_MODE_AUTO", ("enum XX_MODE",), (one,)),
        ("variable", "step", "=", "0", "STEP_INIT", ("enum STEP",), (lvalue,)),
        ("variable", "step", "=", "1", "STEP_RUN", ("enum STEP",), (lvalue,)),
        ("variable", "step", "==", "2", "STEP_EXIT", ("enum STEP",), (lvalue,)),
        ("case", "step", "case", "1", "STEP_RUN", ("enum STEP",), (lvalue,)),
        ("field", "struct xxobj.flags", "=", "1", "KIND_A", ("enum KIND", "enum STEP"), ()),
        ("variable", "mode", "=", "7", "", ("enum KIND", "enum STEP"), ()),
        ("return", "0x00405000", "return", "1", "XX_MODE_ON", ("enum XX_MODE",), (one,)),
    ]
    got = [(record.kind, record.target, record.slot, record.value,
            record.search.candidates[0].text if record.search and record.search.candidates else "",
            record.row.groups, tuple(record.flags)) for record in held]
    if sorted(got) != sorted(wanted):
        failures += [f"symbol site {item}" for item in got if item not in wanted]
        failures += [f"missing symbol site {item}" for item in wanted if item not in got]
    first = next((record for record in held if record.kind == inventory.CALL), None)
    if first is None or (first.prototype, first.accepted, first.check.passed) != ("reference: (int, enum XX_MODE)",
                                                                                  (symbols.REFERENCE,), True):
        failures.append(f"reference call site {first and (first.prototype, first.accepted, first.check)}")
    if any(proposal[0] == "xxGame" for proposal in found.proposed):
        failures.append("a callee with a reference prototype is no proposal")
    if found.field_counts["scope sites"] != 1:
        failures.append(f"scope field sites {found.field_counts['scope sites']}")
    if found.symbols is None or not made.generation:
        failures.append("the inventory keeps the symbols, and a commit takes the new kinds")
    disputed = dict(REFERENCE_FILES, **{"enums.csv": "enum,name,value\nenum XX_MODE,XXM_ONE,2\n"})
    with tempfile.TemporaryDirectory() as folder:
        other = inventory.build(*referenced(folder, symbol_files=disputed))
    pools = [record.pool for record in other.records if record.kind == inventory.CALL and record.target == "0x00404000"]
    if not pools or pools[0].disputed != {"XXM_ONE": "target headers give 1"}:
        failures.append(f"a reference name that the target headers define otherwise: {pools and pools[0].disputed}")
    return failures


def check_normalized() -> list[str]:
    failures = []
    for text, wanted in (("(0x0)", "0"), ("0", "0"), ("0u", "0u"), ("0x80000000", "2147483648u"),
                         ("2147483648", "2147483648ul"), ("(void *)0", "( void * ) 0"), ("(A) | (B)", "( A ) | ( B )"),
                         ("1.5f", "1.5f"), ("'A'", "'A'")):
        got = inventory.normalized(ctokens.tokens_of(text), CPP)
        if got != wanted:
            failures.append(f"normalized {text!r}: {got!r}, wanted {wanted!r}")
    return failures


def check_run() -> list[str]:
    """Two commits keep the ids; a rewrite with the same value keeps its id; the outputs carry the generation."""
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        loaded, rows = repository(folder)
        first, made = committed(loaded, rows)
        ids = [record.id for record in first.records if record.covered]
        if made.generation != 1 or len(set(ids)) != len(ids) or not all(ids):
            failures.append(f"first run: generation {made.generation}, ids {ids}")
        if any(record.id for record in first.records if not record.covered):
            failures.append("a nonconstant site gets no id")
        second, made = committed(loaded, rows)
        if made.generation != 2 or [record.id for record in second.records if record.covered] != ids:
            failures.append(f"second run: generation {made.generation}, ids moved")
        edited = dict(FILES, **{"src/a.c": A_C.replace("xxFlags(3);", "xxFlags(XXF_A | XXF_B);")})
        loaded, rows = repository(folder, edited)
        third, _ = committed(loaded, rows)
        if [record.id for record in third.records if record.covered] != ids:
            failures.append("a rewrite with the same value keeps its id")
        folder_path = Path(folder) / "evidence"
        header = (folder_path / inventory.INVENTORY).read_text(encoding="utf-8").split("\n")[:2]
        if header != ["# evidence-inventory generation=3", ",".join(inventory.COLUMNS)]:
            failures.append(f"inventory.csv header {header}")
        if not (folder_path / inventory.PROPOSED).read_text(encoding="utf-8").startswith("# argmap-proposed generation=3"):
            failures.append("argmap-proposed.csv header")
        live = state.read_state(folder_path)
        if len(state.parse_sites(live.files[state.SITES])) != len(ids):
            failures.append("sites.csv holds the coverage sites")
        if not any((Path(folder) / "backups").iterdir()):
            failures.append("a run makes a backup")
    return failures


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_sites, check_placeholders, check_fields, check_symbols, check_normalized, check_run):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    print("\n".join(found) or "inventorytests: all passed")
    sys.exit(1 if found else 0)
