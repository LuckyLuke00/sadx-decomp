"""Tests of the names in tools/dossier.py: the size of a global, the element and member at an offset into it, the
notes on memory operands, the Ghidra draft's names and the names that several globals share.

run() returns the failures as "<helper> gives <found> for <input>, not <wanted>".
"""

import tempfile
from pathlib import Path

import dossier
import facttests
import names

WORK = ("struct work {\n    float speed;\n    float pos;\n};\n"
        'static_assert(sizeof(work) == 0x8, "sizeof work");\n'
        'static_assert(offsetof(work, speed) == 0x0, "work::speed");\n'
        'static_assert(offsetof(work, pos) == 0x4, "work::pos");\n')
TABLE = dossier.Global(0x500000, 0x50, "DAT_00500000", "struct work DAT_00500000[10]")


def types_of(text: str) -> names.Types:
    with tempfile.TemporaryDirectory() as folder:
        path = Path(folder) / "types.h"
        path.write_text(text, encoding="utf-8")
        return names.Types(path)


def check_global_size() -> list[str]:
    """A definition's size counts decimal and hex array lengths. An unknown length or type gives 0."""
    types = types_of(WORK)
    cases = [("char DAT_x[0x400]", 0x400), ("int DAT_x[10]", 40), ("struct work DAT_x[2][3]", 48),
             ("int DAT_x[]", 0), ("struct task DAT_x", 0)]
    return [f"global_size gives {found} for {definition!r}, not {wanted}" for definition, wanted in cases
            if (found := dossier.global_size(definition, "DAT_x", types)) != wanted]


def check_member_path() -> list[str]:
    """The element and member at an offset into a global, with the rest past the member's start. An array of
    unknown length still has its elements. A scalar or a struct with no layout has none."""
    types = types_of(WORK)
    cases = [(TABLE, 0xc, "DAT_00500000[1].pos"), (TABLE, 0xe, "DAT_00500000[1].pos+0x2"),
             (dossier.Global(0x500000, 0, "DAT_00500000", "struct work DAT_00500000[]"), 0x10,
              "DAT_00500000[2].speed"),
             (dossier.Global(0x500000, 40, "DAT_00500000", "int DAT_00500000[10]"), 8, "DAT_00500000[2]"),
             (dossier.Global(0x500000, 4, "DAT_00500000", "int DAT_00500000"), 2, None),
             (dossier.Global(0x500000, 8, "DAT_00500000", "struct task DAT_00500000"), 4, None)]
    return [f"member_path gives {found} for {g.decl} at +0x{offset:x}, not {wanted}" for g, offset, wanted in cases
            if (found := dossier.member_path(g, offset, types)) != wanted]


class CodeImage(facttests.FakeImage):
    """The fake image with code at 0x401000."""

    def __init__(self, code: bytes):
        self.bytes = {**self.bytes, 0x401000: code}


def check_operand_notes() -> list[str]:
    """A memory operand with a base register and a data address gets a note, as one with no base register does:
    the element and member it falls in. One with a small displacement gets none."""
    # mov eax, [esi + 0x50000c]; mov ecx, [0x50000c]; mov eax, [esi + 4]
    code = bytes.fromhex("8b860c005000" "8b0d0c005000" "8b4604")
    image = CodeImage(code)
    namer = dossier.Namer(image, {}, {}, {}, [TABLE])
    lines = dossier.disassemble(image, namer, 0x401000, len(code), types_of(WORK))
    notes = [line.split(" ; ")[1] if " ; " in line else None for line in lines]
    wanted = ["DAT_00500000[1].pos", "DAT_00500000[1].pos", None]
    failures = [] if notes == wanted else [f"disassemble notes {notes}, not {wanted}"]
    if 0x500000 not in namer.used:
        failures.append("disassemble lists no names used for a [reg + disp] operand")
    return failures


def check_draft_names() -> list[str]:
    """In Ghidra's draft, an address inside a known global becomes its element and member, and one past a member's
    start keeps Ghidra's name with a comment that names the holder."""
    draft = "DAT_00500000[0].speed = DAT_0050000c;\nDAT_0050000e = 0;\nDAT_00600000 = 1;\n"
    wanted = ("DAT_00500000[0].speed = DAT_00500000[1].pos;\nDAT_0050000e /* DAT_00500000+0xe */ = 0;\n"
              "DAT_00600000 = 1;")
    namer = dossier.Namer(facttests.FakeImage(), {}, {}, {}, [TABLE])
    with tempfile.TemporaryDirectory() as folder:
        (Path(folder) / "00401000.c").write_text(draft, encoding="utf-8")
        found = dossier.ghidra_c(0x401000, Path(folder), {}, namer, types_of(WORK))
    return [] if found == wanted else [f"ghidra_c gives {found!r}, not {wanted!r}"]


def check_shared_names() -> list[str]:
    """A name that two rows of the globals table share stays DAT_ for both. A name of one row stays."""
    header = "address\tname\tdecl\tbase\tdims\tsize\tobject\n"
    rows = ["0x00501000\tobj_c_info\tint {}\tint\t\t4\to_x.obj", "0x00502000\tobj_c_info\tint {}\tint\t\t4\to_y.obj",
            "0x00503000\tSpeed\tfloat {}\tfloat\t\t4\to_x.obj"]
    with tempfile.TemporaryDirectory() as folder:
        (Path(folder) / "globals.tsv").write_text(header + "\n".join(rows) + "\n", encoding="utf-8")
        found = [g.name for g in dossier.known_globals(Path(folder), {}, names.Previous({}, {}, {}), types_of(""))]
    wanted = ["DAT_00501000", "DAT_00502000", "Speed"]
    return [] if found == wanted else [f"known_globals names {found}, not {wanted}"]


def run() -> list[str]:
    """Every check of this module, in order."""
    checks = [check_global_size, check_member_path, check_operand_notes, check_draft_names, check_shared_names]
    return [failure for check in checks for failure in check()]
