"""The copies of a static function that the game's link folded, for reccmp.

Two source files can each define the same static function. The game's link kept
one copy and sent the other file's calls to it, where its objects were compiled
with /Gy: each function is then a COMDAT, and /OPT:ICF folds identical
COMDATs. With two copies it keeps the later object's. Our link keeps both
(/OPT:NOICF), so the other file's calls go to our second copy. reccmp numbers functions that share a
name, so such a call shows as UVScroll(2) where the game's shows UVScroll(1),
and the caller can't match.

alias_folds() names such a copy after the copy the game kept. A copy qualifies
when it is static, matches no function of the game, and is the same code as
exactly one function that does and shares its name. Same code is
the same size, the same instructions and the same targets, where an address
inside each function counts as its offset from the start. A call to a copy that
folds counts as a call to the copy it folds into, so a chain of copies folds
too. Only the name changes, so a call to the copy scores as a call to the kept
one, as in the game.

install() makes each Compare made after it run alias_folds() on our image at
the end of reccmp's analysis.

Needs reccmp, so it runs in .venv.
"""

from reccmp.compare import core
from reccmp.compare.asm.parse import ParseAsm
from reccmp.types import EntityType, ImageId


def alias_folds(db, image) -> dict[int, int]:
    """Name each fold copy in our IMAGE after the copy the game kept. Returns {copy: kept copy}, our addresses."""
    functions = [entity for entity in db.all(ImageId.RECOMP)
                 if entity.entity_type == EntityType.FUNCTION and entity.name and entity.size(ImageId.RECOMP)]
    matched = {}
    for entity in functions:
        if entity.matched:
            matched.setdefault(entity.name, []).append(entity)
    copies = [(entity, [kept for kept in matched.get(entity.name, [])
                        if kept.size(ImageId.RECOMP) == entity.size(ImageId.RECOMP)])
              for entity in functions if not entity.matched and entity.get("symbol") is None]
    folds, kept_copies = {}, {}
    changed = True
    while changed:
        changed = False
        for copy, candidates in copies:
            if copy.recomp_addr in folds or not candidates:
                continue
            mine = code(image, copy, folds)
            same = [kept for kept in candidates if code(image, kept, folds) == mine]
            if len(same) == 1:
                folds[copy.recomp_addr] = same[0].recomp_addr
                kept_copies[copy.recomp_addr] = same[0]
                changed = True
    with db.batch() as batch:
        for address, kept in kept_copies.items():
            batch.set(ImageId.RECOMP, address, computed_name=kept.best_name())
    return folds


def code(image, function, folds: dict[int, int]) -> list[str]:
    """FUNCTION's instructions as reccmp shows them, with each address written the same way in every copy: an
    address inside FUNCTION as its offset from the start, a fold copy as the copy it folds into, any other address as
    itself."""
    start = function.recomp_addr
    size = function.size(ImageId.RECOMP)

    def address(value: int, exact: bool = False, indirect: bool = False) -> str:
        if start <= value < start + size:
            return f"<start+{value - start:#x}>"
        return hex(folds.get(value, value))

    parser = ParseAsm(addr_test=lambda value: True, name_lookup=address)
    return [text for _, text in parser.parse_asm(image.read(start, size), start)]


def install() -> None:
    """Run alias_folds() on our image after reccmp's last step of analysis, in each Compare made from now on.
    Installing it again changes nothing."""
    last_step = core.complete_partial_strings
    if getattr(last_step, "folds", False):
        return

    def then_alias_folds(db, image_id, binfile, encoding):
        last_step(db, image_id, binfile, encoding)
        if image_id == ImageId.RECOMP:
            alias_folds(db, binfile)

    then_alias_folds.folds = True
    core.complete_partial_strings = then_alias_folds
