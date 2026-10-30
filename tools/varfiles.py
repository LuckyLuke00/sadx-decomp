"""The variable of its own source file for each GLOBAL annotation, for reccmp.

reccmp pairs a GLOBAL annotation with a variable of our build by its name alone,
first come first served in address order. Several source files can each have a
variable of one name: a static each, or the definition that a generated file
adds for an extern. Where our link puts them in another order than the game's,
the pairs cross, and a function that reads such a variable can't match. In SADX,
o_stoper.c's annotation of object_c_info got globals.cpp's object_c_info, so
ObjectStoperL scored 97.56% on code that matches.

match_own_files() first pairs each annotation with the variable of its name in
the object file built from the annotation's file. Only a pair that is the one
choice on both sides counts: a file with two variables of the name, or two
annotations of it, stays with reccmp's pass, which pairs the rest by name as
before.

install() makes each Compare made after it mark what match_own_files() needs,
and run it before reccmp's pass. mark_objects() gives each variable of our
build the source of its object file, from the section contributions and module
list of our PDB. mark_files() gives each annotation its file.

Needs reccmp, so it runs in .venv.
"""

from pathlib import Path

from reccmp.compare import core
from reccmp.parser import DecompCodebase
from reccmp.types import EntityType, ImageId

import pe

CMAKE_FOLDER = "CMakeFiles"  # CMake builds each object in CMakeFiles/<target>.dir, at its source's path


class ModulesCvdump(core.Cvdump):
    """reccmp's Cvdump, which also reads the module list: section contributions name their object file by number."""

    def run(self):
        self.modules()
        return super().run()


def object_source(obj: str) -> str | None:
    """The path of the source file that CMake built the object file OBJ from, relative to the source folder. None for
    an object file that CMake did not build, such as a library's."""
    parts = obj.replace("\\", "/").split("/")
    if CMAKE_FOLDER not in parts:
        return None
    return "/".join(parts[parts.index(CMAKE_FOLDER) + 2:]).removesuffix(".obj")


def is_variable(entity) -> bool:
    """Whether reccmp's variable pass takes ENTITY of our build: it has a name, and no type or the data type."""
    return bool(entity.get("name")) and (not entity.get("type") or entity.get("type") == EntityType.DATA)


def is_annotation(entity) -> bool:
    """Whether reccmp's variable pass takes ENTITY of the game: a variable with a name, not a function's static."""
    return entity.get("type") == EntityType.DATA and bool(entity.get("name")) and not entity.get("static_var")


def mark_objects(db, parser, image) -> None:
    """Give each variable of our build in DB the source of the object file that holds it, as object_source, from the
    section contributions and modules that PARSER read. IMAGE is our image."""
    sources = {module.id: object_source(module.obj) for module in parser.modules}
    spans = sorted((image.get_abs_addr(ref.section, ref.offset), ref.size, ref.module) for ref in parser.sizerefs)
    ranges = [(start, start + size) for start, size, _ in spans]
    with db.batch() as batch:
        for entity in db.all(ImageId.RECOMP):
            if not is_variable(entity):
                continue
            index = pe.range_index(ranges, entity.recomp_addr)
            source = None if index is None else sources[spans[index][2]]
            if source:
                batch.set(ImageId.RECOMP, entity.recomp_addr, object_source=source)


def mark_files(db, variables) -> None:
    """Give the game's entity in DB of each of VARIABLES, GLOBAL annotations that reccmp parsed, its file as
    annotation_file."""
    with db.batch() as batch:
        for variable in variables:
            batch.set(ImageId.ORIG, variable.offset, annotation_file=Path(variable.filename).as_posix())


def match_own_files(db) -> None:
    """Pair each unmatched GLOBAL annotation in DB with the one unmatched variable of its name whose object file was
    built from the annotation's file, where no other annotation of that file and name has it."""
    sources = {}
    for entity in db.unmatched(ImageId.RECOMP):
        source = entity.get("object_source")
        if source and is_variable(entity):
            sources.setdefault(entity.get("name"), []).append((source, entity.recomp_addr))
    claims = {}
    for entity in db.unmatched(ImageId.ORIG):
        file = entity.get("annotation_file")
        if not file or not is_annotation(entity):
            continue
        own = [address for source, address in sources.get(entity.get("name"), []) if file.endswith("/" + source)]
        if len(own) == 1:
            claims.setdefault(own[0], []).append(entity.orig_addr)
    with db.batch() as batch:
        for address, annotations in claims.items():
            if len(annotations) == 1:
                batch.match(annotations[0], address)


def install() -> None:
    """Mark what match_own_files() needs and run it before reccmp's variable pass, in each Compare made from now on.
    Installing it again changes nothing."""
    by_name = core.match_variables
    if getattr(by_name, "varfiles", False):
        return
    load_cvdump, load_markers = core.load_cvdump, core.load_markers

    def then_mark_objects(cvdump_analysis, db, recomp_bin):
        load_cvdump(cvdump_analysis, db, recomp_bin)
        mark_objects(db, cvdump_analysis.parser, recomp_bin)

    def then_mark_files(code_files, lines_db, orig_bin, target_id, db, encoding, project_aliases, report):
        load_markers(code_files, lines_db, orig_bin, target_id, db, encoding, project_aliases, report)
        codebase = DecompCodebase(code_files, target_id, aliases=project_aliases)
        codebase.prune_invalid_addrs(orig_bin.is_valid_vaddr)  # as load_markers does: the annotations it kept
        codebase.prune_reused_addrs()
        mark_files(db, codebase.iter_variables())

    def own_files_then_by_name(db, report):
        match_own_files(db)
        by_name(db, report)

    own_files_then_by_name.varfiles = True
    core.Cvdump = ModulesCvdump
    core.load_cvdump = then_mark_objects
    core.load_markers = then_mark_files
    core.match_variables = own_files_then_by_name
