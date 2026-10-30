"""Tests of tools/varfiles.py: which variable of our build a GLOBAL annotation pairs with.

run() returns the failures as "<helper> gives <found> for <input>, not <wanted>". Each check builds a small reccmp
database by hand.
"""

from pathlib import Path
from types import SimpleNamespace

from reccmp.compare.db import EntityDb
from reccmp.compare.match_msvc import match_variables
from reccmp.cvdump.parser import ModuleEntry, SizeRefEntry
from reccmp.types import EntityType, ImageId

import varfiles
from foldtests import failure

SOURCES = "D:/game/"  # the source folder
OBJECTS = "D:/game/build/CMakeFiles/game.dir/"  # where CMake builds the objects of SOURCES
SECTION = 0x403000  # where the one section of FakeImage starts


class FakeImage:
    """Our image, with one section at SECTION."""

    def get_abs_addr(self, section: int, offset: int) -> int:
        return SECTION + offset


def check_object_source() -> list[str]:
    """An object file that CMake built gives its source, a library's gives None."""
    cases = {"D:\\game\\build\\CMakeFiles\\game.dir\\src\\stage\\o_door.c.obj": "src/stage/o_door.c",
             OBJECTS + "src/globals.cpp.obj": "src/globals.cpp",
             "C:\\crt\\mt_obj\\fopen.obj": None}
    failures = []
    for obj, wanted in cases.items():
        found = varfiles.object_source(obj)
        if found != wanted:
            failures.append(failure("object_source", found, obj, wanted))
    return failures


def check_mark_objects() -> list[str]:
    """A variable gets the source of the object that holds it. A library's variable, one outside every object and a
    function get none."""
    parser = SimpleNamespace(
        modules=[ModuleEntry(1, "", OBJECTS + "src/a.c.obj"), ModuleEntry(2, "", OBJECTS + "src/b.c.obj"),
                 ModuleEntry(3, "LIBCMT.lib", "C:/crt/fopen.obj")],
        sizerefs=[SizeRefEntry(1, 3, 0x100, 0x20), SizeRefEntry(2, 3, 0x120, 0x10), SizeRefEntry(3, 3, 0x200, 8)])
    db = EntityDb()
    db.bulk_insert(ImageId.RECOMP, [(SECTION + 0x104, {"type": EntityType.DATA, "name": "door_info"}),
                                    (SECTION + 0x124, {"name": "door_info"}),
                                    (SECTION + 0x204, {"type": EntityType.DATA, "name": "_iob"}),
                                    (SECTION + 0x300, {"type": EntityType.DATA, "name": "late"}),
                                    (SECTION + 0x100, {"type": EntityType.FUNCTION, "name": "DoorMain"})])
    varfiles.mark_objects(db, parser, FakeImage())
    found = {entity.recomp_addr: entity.get("object_source") for entity in db.all(ImageId.RECOMP)
             if entity.get("object_source")}
    wanted = {SECTION + 0x104: "src/a.c", SECTION + 0x124: "src/b.c"}
    given = "two objects, a library, a gap and a function"
    return [] if found == wanted else [failure("mark_objects", found, given, wanted)]


def check_mark_files() -> list[str]:
    """An annotation's entity gets its file."""
    db = EntityDb()
    db.bulk_insert(ImageId.ORIG, [(0x800100, {"type": EntityType.DATA, "name": "door_info"})])
    variables = [SimpleNamespace(offset=0x800100, filename=Path(SOURCES + "src/a.c"))]
    varfiles.mark_files(db, variables)
    found = db.get(ImageId.ORIG, 0x800100).get("annotation_file")
    wanted = SOURCES + "src/a.c"
    return [] if found == wanted else [failure("mark_files", found, variables, wanted)]


def pairs(annotations: list[tuple[int, str]], variables: list[tuple[int, str]]) -> dict[int, int]:
    """The pairs, game address: our address, that match_own_files() and then reccmp's pass make of ANNOTATIONS, (game
    address, file), and VARIABLES, (our address, source), all of one name."""
    db = EntityDb()
    db.bulk_insert(ImageId.ORIG, [(address, {"type": EntityType.DATA, "name": "info",
                                             "annotation_file": SOURCES + file}) for address, file in annotations])
    db.bulk_insert(ImageId.RECOMP, [(address, {"type": EntityType.DATA, "name": "info", "object_source": source})
                                    for address, source in variables])
    varfiles.match_own_files(db)
    match_variables(db)
    return {match.orig_addr: match.recomp_addr for match in db.get_matches()}


def check_match_own_files() -> list[str]:
    """Each annotation pairs with its own file's variable, though the files' address order crosses. An annotation
    whose file has no variable of the name, or a file with two variables or two annotations of it, pairs by name."""
    cases = {
        "crossed files": ([(0x800100, "src/b.c"), (0x800200, "src/a.c")],
                          [(0x403104, "src/a.c"), (0x403124, "src/b.c")],
                          {0x800100: 0x403124, 0x800200: 0x403104}),
        "a header's annotation": ([(0x800100, "src/info.h")],
                                  [(0x403104, "src/a.c")],
                                  {0x800100: 0x403104}),
        "two variables in a file": ([(0x800100, "src/b.c"), (0x800200, "src/a.c")],
                                    [(0x403104, "src/a.c"), (0x403124, "src/a.c")],
                                    {0x800100: 0x403104, 0x800200: 0x403124}),
        "two annotations in a file": ([(0x800100, "src/a.c"), (0x800200, "src/a.c")],
                                      [(0x403104, "src/b.c"), (0x403124, "src/a.c")],
                                      {0x800100: 0x403104, 0x800200: 0x403124}),
    }
    failures = []
    for case, (annotations, variables, wanted) in cases.items():
        found = pairs(annotations, variables)
        if found != wanted:
            failures.append(failure("match_own_files", found, case, wanted))
    return failures


def run() -> list[str]:
    """Every check of the own-file pairing, in order: the failures of all."""
    failures = []
    for check in (check_object_source, check_mark_objects, check_mark_files, check_match_own_files):
        failures += check()
    return failures
