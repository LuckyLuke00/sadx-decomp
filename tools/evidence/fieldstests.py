"""Unit tests for fields.py: reading fieldmap.csv, the member check and the typing of field spot bases.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/fieldstests.py
run() calls every check and returns the failures. All names are made up.
"""

import os
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import argmap  # noqa: E402
import cheaders  # noqa: E402
import cparse  # noqa: E402
import fields  # noqa: E402
import profiles  # noqa: E402
from argmap import ArgmapError  # noqa: E402
from cheaders import Member  # noqa: E402

CPP = profiles.get("msvc-vc10-x86-cpp")
HEADER = ",".join(fields.COLUMNS)
GOOD = (f"{HEADER}\n"
        "struct  xxobj,flags,flags,XXE_,header declaration,xx.h,Uint32,,eval flags\n"
        "XX_HOLDER,count,value,XXC_ XX_NONE,unverified,,,vendor,\n")

TOP_H = """\
typedef unsigned int Uint32;
typedef struct xxobj {
    Uint32 flags;
    struct xxobj *child, *sibling;
    Uint32 bits : 4;
    float pos[3];
} XX_OBJECT;
typedef struct {
    XX_OBJECT *table[2];
    int count;
} XX_HOLDER, *XX_PHOLDER;
XX_OBJECT *xxGet(int index);
extern XX_HOLDER g_holder;
"""

SOURCE = """\
typedef XX_PHOLDER MY_HOLDER;
void f(XX_OBJECT *op, XX_OBJECT objs[4], void *raw)
{
    XX_PHOLDER ph;
    op->flags = 1;
    op->child->sibling->flags |= 2;
    (*op).flags = 3;
    objs[1].flags = 4;
    xxGet(1)->flags = 5;
    ((XX_OBJECT *)raw)->flags = 6;
    ph->count = 7;
    g_holder.table[0]->flags = 8;
    unknown->flags = 9;
    op->bits = 1;
    ((MY_HOLDER)raw)->count = 2;
    (*op).child->flags = 3;
    xxNothing(1)->flags = 4;
}
void g(XX_HOLDER *g_holder)
{
    g_holder->count = 1;
}
"""

OBJECT = ("struct xxobj", "Uint32")
SPOT_TYPES = [OBJECT, OBJECT, OBJECT, OBJECT, OBJECT, OBJECT, ("XX_HOLDER", "int"), OBJECT, None,
              ("struct xxobj", "Uint32 : 4"), ("XX_HOLDER", "int"), OBJECT, None, ("XX_HOLDER", "int")]


def read(text: str | None):
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder) / fields.FIELDMAP
        if text is not None:
            path.write_text(text, encoding="utf-8")
        try:
            return fields.read_fieldmap(path)
        except ArgmapError as error:
            return str(error)


def closure(header: str) -> cheaders.Closure:
    with tempfile.TemporaryDirectory() as folder:
        path = os.path.join(folder, "top.h")
        with open(path, "w", encoding="utf-8", newline="") as handle:
            handle.write(header)
        return cheaders.read(path, cheaders.Config(CPP))


def check_read() -> list[str]:
    failures = []
    if read(None) != []:
        failures.append(f"a missing fieldmap gives {read(None)!r}")
    rows = read(GOOD)
    if isinstance(rows, str):
        return failures + [f"good fieldmap failed: {rows}"]
    flags, count = rows
    got = (flags.callee, flags.slot, flags.mode, flags.groups, flags.status, flags.header, flags.spelled_type,
           flags.line)
    if got != ("struct xxobj.flags", 0, "flags", ("XXE_",), "header declaration", "xx.h", "Uint32", 2):
        failures.append(f"row {flags}")
    if (count.callee, count.status, count.origins, fields.type_and_member(flags)) != (
            "XX_HOLDER.count", "unverified", ("vendor",), ("struct xxobj", "flags")):
        failures.append(f"row {count}")
    cases = (
        ("type,member\n", "the columns must be"),
        (GOOD + "struct xxobj,flags,value,A,unverified,,,,\n", "struct xxobj.flags is also on line 2"),
        (f"{HEADER}\nXX_T,,value,A,unverified,,,,\n", "needs a type and a member"),
        (f"{HEADER}\nXX_T,m,value,A,header declaration,,int,,\n", "needs a header"),
        (f"{HEADER}\nXX_T,m,value,A,header prototype,xx.h,int,,\n", "status 'header prototype'"),
    )
    for text, wanted in cases:
        got = read(text)
        if not isinstance(got, str) or wanted not in got:
            failures.append(f"fieldmap error {got!r}, want {wanted!r}")
    return failures


def check_member() -> list[str]:
    failures = []
    flags, count = read(GOOD)
    body = (Member("flags", "Uint32"), Member("child", "struct xxobj *"))
    cases = (
        (count, [("xx.h", body)], "unverified row"),
        (flags, [("other.h", body)], "no body of struct xxobj in xx.h"),
        (flags, [("sdk/xx.h", body), ("XX.H", body[:1])], "xx.h defines struct xxobj in different ways"),
        (flags, [("xx.h", body[1:])], "xx.h's struct xxobj has no member flags"),
        (flags, [("xx.h", (Member("flags", "int"),))], "xx.h spells flags 'int', the row says 'Uint32'"),
        (flags, [("sdk/xx.h", body), ("other.h", ())], ""),
    )
    for row, bodies, wanted in cases:
        got = fields.check_member(row, bodies)
        if (got.passed, got.reason) != (wanted == "", wanted):
            failures.append(f"member check of {row.callee} in {bodies}: got {got}, want {wanted!r}")
    return failures


def check_rows() -> list[str]:
    """Rows key on the type id that their type spelling names in the closures; a row whose type has no body warns,
    and two rows that name one member fail."""
    failures = []
    found = closure(TOP_H)
    text = (f"{HEADER}\nXX_OBJECT,flags,flags,XXE_,unverified,,,,\nXX_PHOLDER,count,value,XXC_,unverified,,,,\n"
            "Uint32,flags,value,XXC_,unverified,,,,\n")
    keyed, warnings = fields.index_rows(read(text), [found])
    if sorted(keyed) != [("struct xxobj", "flags")] or len(warnings) != 2:
        failures.append(f"index: got {sorted(keyed)}, {warnings}")
    elif "XX_PHOLDER" not in warnings[0] or "has no struct or union body" not in warnings[0]:
        failures.append(f"index warning: got {warnings[0]!r}")
    twice = f"{HEADER}\nXX_OBJECT,flags,flags,XXE_,unverified,,,,\nstruct xxobj,flags,flags,XXE_,unverified,,,,\n"
    try:
        fields.index_rows(read(twice), [found])
        failures.append("two rows for one member did not fail")
    except ArgmapError as error:
        if "lines 2 and 3" not in str(error):
            failures.append(f"two rows: got {error}")
    owners = fields.member_owners([found, closure(TOP_H.replace("Uint32 flags;", "int flags;"))])
    if owners["count"] != {"XX_HOLDER": "int"} or owners["flags"] != {"struct xxobj": None}:
        failures.append(f"member owners: got {owners['count']}, {owners['flags']}")
    for operator, mode in (("&=", "and-mask"), ("|=", "flags"), ("&", "flags"), ("=", "value"), ("!=", "value")):
        if fields.operator_row(read(GOOD)[1], operator).mode != mode:
            failures.append(f"operator {operator} gives mode {fields.operator_row(read(GOOD)[1], operator).mode}")
    return failures


def check_types() -> list[str]:
    """The base of each spot types through locals, file names, closure variables and functions, casts, *, [ ], .
    and ->; a closure name that two closures declare in different ways does not type."""
    failures = []
    found = closure(TOP_H)
    source = cparse.parse(SOURCE, "a.c", CPP, type_names=frozenset(found.type_names))
    got = []
    for spot in source.spots:
        scope = fields.Scope([found], source, source.owners[spot.owner].names)
        got.append(scope.member(fields.base_type(spot.base, scope), spot.arrow, spot.member))
    if got != SPOT_TYPES:
        failures.append(f"spot types: got {got}")
    scope = fields.Scope([found], source, {})
    cases = (("XX_OBJECT * const", "XX_OBJECT"), ("int [ 2 ] [ 3 ]", "int [ 3 ]"), ("XX_PHOLDER", "XX_HOLDER"),
             ("MY_HOLDER", "XX_HOLDER"), ("int ( * ) [ 3 ]", None), ("int", None), ("XX_HOLDER", None), (None, None))
    for spelling, wanted in cases:
        if scope.dereferenced(spelling) != wanted:
            failures.append(f"dereferenced {spelling!r}: got {scope.dereferenced(spelling)!r}, want {wanted!r}")
    cases = (("XX_OBJECT", "struct xxobj"), ("const XX_OBJECT", "struct xxobj"), ("xxobj", "struct xxobj"),
             ("struct xxobj", "struct xxobj"), ("XX_HOLDER", "XX_HOLDER"), ("Uint32", None), ("XX_PHOLDER", None))
    for spelling, wanted in cases:
        if scope.body(spelling) != wanted:
            failures.append(f"body {spelling!r}: got {scope.body(spelling)!r}, want {wanted!r}")
    named = [(len(fields.named_bodies([found], name, header)), header) for name, header in
             (("XX_OBJECT", "top.h"), ("XX_HOLDER", "TOP.H"), ("XX_OBJECT", "other.h"), ("Uint32", "top.h"))]
    if named != [(1, "top.h"), (1, "TOP.H"), (0, "other.h"), (0, "top.h")]:
        failures.append(f"named bodies: got {named}")
    elif fields.named_bodies([found], "XX_OBJECT", "top.h")[0][1][1][0] != Member("flags", "Uint32"):
        failures.append(f"named body members: got {fields.named_bodies([found], 'XX_OBJECT', 'top.h')}")
    other = closure(TOP_H.replace("extern XX_HOLDER g_holder;", "extern int g_holder;"))
    split = fields.Scope([found, other], source, {})
    if split.name_type("g_holder") is not None or split.members("struct xxobj") is None:
        failures.append(f"two closures: got {split.name_type('g_holder')!r}, {split.members('struct xxobj')}")
    return failures


def run() -> list[str]:
    failures = []
    for check in (check_read, check_member, check_rows, check_types):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    for failure in found:
        print(failure)
    if not found:
        print("fieldstests: all passed")
    sys.exit(1 if found else 0)
