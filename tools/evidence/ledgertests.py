"""Unit tests for ledger.py: the file format, and the ledger that commit() makes across runs: dates, statuses,
remaps, tier and candidate moves, gone and ambiguous rows, the first run over a state with no ledger, and the review
decisions (confirmed, stale, reopened, orphaned). Each check works in a temp folder, on the inventorytests fixture.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/ledgertests.py
run() calls every check and returns the failures. All names are made up.
"""

import sys
import tempfile
from dataclasses import replace
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import decisions  # noqa: E402
import fields  # noqa: E402
import inventory  # noqa: E402
import inventorytests  # noqa: E402
import ledger  # noqa: E402
import state  # noqa: E402

DAYS = ("2026-01-01", "2026-01-02", "2026-01-03", "2026-01-04")
TIME = "2026-01-01T00:00:00+00:00"


def live_ledger(folder: Path) -> dict:
    return ledger.parse_ledger(state.read_state(folder).files[ledger.LEDGER])


def changes_text(folder: Path) -> str:
    return (folder / ledger.CHANGES).read_text(encoding="utf-8")


def site_id(found: inventory.Inventory, callee: str, argument: str) -> str:
    """The id of the one site of CALLEE whose argument, without spaces, is ARGUMENT."""
    [record] = [record for record in found.records
                if record.callee == callee and "".join(record.argument.split()) == argument]
    return record.id


def edited(old: str, new: str) -> dict:
    """The fixture files with OLD replaced by NEW in src/a.c."""
    return dict(inventorytests.FILES, **{"src/a.c": inventorytests.A_C.replace(old, new)})


def check_format() -> list[str]:
    failures = []
    row = ledger.Row("S000001", ledger.VALUE, "open", "a, b", "XX_A; XX_B", "A", "C", "argmap header prototype", "",
                     "f00", DAYS[0], DAYS[1], "src/a.c", 4)
    rows = {"S000010": replace(row, id="S000010"), "S000001": row}
    data = ledger.format_ledger(rows)
    if ledger.parse_ledger(data) != rows:
        failures.append("the ledger round-trips")
    if data.decode("utf-8").split("\n")[2].split(",")[0] != "S000001":
        failures.append("the rows are in id order")
    lines = data.decode("utf-8").split("\n")
    for broken, wanted in ((b"id,kind\n", "not a ledger file"),
                           (data.replace(b"schema=2", b"schema=1"), "ledger schema 1"),
                           ("\n".join([lines[0], "id,kind"] + lines[2:]).encode("utf-8"), "the ledger columns")):
        try:
            ledger.parse_ledger(broken)
            failures.append(f"no error for {wanted!r}")
        except ledger.LedgerError as error:
            if wanted not in str(error):
                failures.append(f"error {error!r}, wanted {wanted!r}")
    return failures


def check_runs() -> list[str]:
    """Four runs over one folder: unchanged, then edited sources, then an edited header and argmap row."""
    failures = []
    with tempfile.TemporaryDirectory() as temp:
        folder = Path(temp) / "evidence"
        loaded, rows = inventorytests.repository(temp)
        first, _ = inventorytests.committed(loaded, rows, DAYS[0])
        covered = [record for record in first.records if record.covered]
        found = live_ledger(folder)
        if sorted(found) != sorted(record.id for record in covered):
            failures.append("first run: one ledger row per coverage site")
        if any((row.first_seen, row.last_checked) != (DAYS[0], DAYS[0]) for row in found.values()):
            failures.append("first run: both dates are today")
        if any(found[record.id].status != record.state for record in covered):
            failures.append("first run: the status is the site's state")
        if f"- {ledger.NEW}: {len(covered)}\n" not in changes_text(folder):
            failures.append(f"first run: every id is new\n{changes_text(folder)}")
        before = state.read_state(folder).files[ledger.LEDGER]

        inventorytests.committed(loaded, rows, DAYS[1])
        if state.read_state(folder).files[ledger.LEDGER] != before:
            failures.append("an unchanged run leaves the ledger as it was, dates included")
        text = changes_text(folder)
        if any(f"- {kind}: 0" not in text for kind in ledger.CHANGE_ORDER) or "## " in text:
            failures.append(f"an unchanged run has no changes\n{text}")

        rewritten, deleted = site_id(first, "xxFlags", "3"), site_id(first, "xxPush", "0")
        twin, other = site_id(first, "xxFlags", "(0x0)"), site_id(first, "xxFlags", "XXF_B")
        files = edited("xxFlags(3);", "xxFlags(XXF_A | XXF_B);")
        files["src/a.c"] = files["src/a.c"].replace("    xxPush(0);\n", "").replace(
            "    xxFlags((0x0));\n", "    xxFlags((0x0));\n    xxFlags(0);\n")
        loaded, rows = inventorytests.repository(temp, files)
        third, _ = inventorytests.committed(loaded, rows, DAYS[2])
        found, text = live_ledger(folder), changes_text(folder)
        if site_id(third, "xxFlags", "XXF_A|XXF_B") != rewritten:
            failures.append("a rewrite with the same value keeps its id")
        row = found[rewritten]
        if (row.status, row.spelling, row.first_seen, row.last_checked) != ("applied", "XXF_A | XXF_B", DAYS[0],
                                                                            DAYS[2]):
            failures.append(f"the rewritten row: {row}")
        if f"- {rewritten} src/a.c:" not in text.split(f"## {ledger.REMAPPED}")[-1]:
            failures.append(f"the rewrite is listed as a remap\n{text}")
        if found[deleted].status != ledger.GONE or f"- {deleted} " not in text.split(f"## {ledger.GONE}")[-1]:
            failures.append(f"a deleted site's row stays, gone\n{text}")
        if found[twin].status != ledger.AMBIGUOUS or "suggested: S" not in text.split(f"## {ledger.AMBIGUOUS}")[-1]:
            failures.append(f"a twin inserted next to its twin makes the old row ambiguous, with suggestions\n{text}")
        if found[other].last_checked != DAYS[0]:
            failures.append("an untouched row keeps its last-checked date")
        ids = {record.id for record in first.records + third.records if record.covered}
        if set(found) != ids:
            failures.append("no row is ever deleted")

        files["inc/vendor.h"] = files["inc/vendor.h"].replace("#define XXF_C 0x4\n",
                                                              "#define XXF_C 0x4\n#define XXF_AB 0x3\n")
        loaded, rows = inventorytests.repository(temp, files)
        (folder / "argmap.csv").write_text(inventorytests.ARGMAP.replace(
            "xxFlags,1,flags,XXF_,header prototype", "xxFlags,1,flags,XXF_,unverified"), encoding="utf-8")
        rows = inventorytests.argmap.read_argmap(folder / "argmap.csv")
        inventorytests.committed(loaded, rows, DAYS[3])
        found, text = live_ledger(folder), changes_text(folder)
        tiers = text.split(f"## {ledger.TIER}")[-1].split("## ")[0]
        if f"- {rewritten} " not in tiers or ": meaning A to B" not in tiers:
            failures.append(f"an argmap row marked unverified moves its tiers\n{text}")
        if f"- {rewritten} src/a.c:" not in text.split(f"## {ledger.CANDIDATES}")[-1] or "added XXF_AB" not in text:
            failures.append(f"a new exact name is an added candidate\n{text}")
        if not found[rewritten].candidates.startswith("XXF_AB; "):
            failures.append(f"the exact name ranks first: {found[rewritten].candidates}")
        counted = site_id(third, "xxCount", "XXF_A")
        if found[counted].last_checked != DAYS[3] or f"- {ledger.RECHECKED}: 0" in text:
            failures.append(f"a row whose group gained a name is rechecked\n{text}")
        if found[site_id(third, "xxPush", "NULL")].last_checked != DAYS[0]:
            failures.append("a row of another group keeps its last-checked date")
    return failures


def check_placeholders() -> list[str]:
    """A placeholder site is a placeholder row whose evidence names its kind and definition; a second run keeps its
    id. A call site is a value row."""
    failures = []
    settings = dict(inventorytests.CONFIG, placeholders={"XX_ASSERT": "no-code", "XX_GUESS": "code"})
    files = dict(inventorytests.FILES, **{"src/d.c": inventorytests.D_C})
    with tempfile.TemporaryDirectory() as temp:
        loaded, rows = inventorytests.repository(temp, files, settings)
        first, _ = inventorytests.committed(loaded, rows, DAYS[0])
        second, _ = inventorytests.committed(loaded, rows, DAYS[1])
        found = live_ledger(Path(temp) / "evidence")
    held = [record.id for record in first.records if record.kind == inventory.PLACEHOLDER]
    if len(held) != 3 or {found[key].kind for key in held} != {ledger.PLACEHOLDER}:
        failures.append(f"placeholder rows {[(key, found[key].kind) for key in held]}")
        return failures
    text = found[held[0]].evidence
    if not text.startswith("placeholder no-code: the binary cannot tell this apart from no statement; definition "):
        failures.append(f"placeholder evidence {text!r}")
    if [record.id for record in second.records if record.kind == inventory.PLACEHOLDER] != held:
        failures.append("a second run keeps the placeholder ids")
    calls = {found[record.id].kind for record in first.records if record.kind == inventory.CALL and record.covered}
    if calls != {ledger.VALUE}:
        failures.append(f"call sites are value rows: {calls}")
    return failures


def check_fields() -> list[str]:
    """A field site is a value row whose evidence names its fieldmap row and its member check; a second run keeps its
    id."""
    failures = []
    with tempfile.TemporaryDirectory() as temp:
        loaded, rows = inventorytests.repository(temp, inventorytests.FIELD_FILES)
        (Path(temp) / "evidence" / fields.FIELDMAP).write_text(inventorytests.FIELDMAP, encoding="utf-8")
        first, _ = inventorytests.committed(loaded, rows, DAYS[0])
        second, _ = inventorytests.committed(loaded, rows, DAYS[1])
        found = live_ledger(Path(temp) / "evidence")
    held = {record.callee: record.id for record in first.records if record.kind == inventory.FIELD and record.covered}
    if {found[key].kind for key in held.values()} != {ledger.VALUE}:
        failures.append(f"field rows {[(key, found[key].kind) for key in held.values()]}")
    for callee, wanted in (("XX_OBJ.flags", "fieldmap header declaration vendor.h; member check passed; origins vendor"),
                           ("struct xxcnk.flags", "fieldmap unverified; member check failed: unverified row")):
        if not found[held[callee]].evidence.startswith(wanted):
            failures.append(f"{callee} evidence {found[held[callee]].evidence!r}")
    if [record.id for record in second.records if record.kind == inventory.FIELD and record.covered] != [
            record.id for record in first.records if record.kind == inventory.FIELD and record.covered]:
        failures.append("a second run keeps the field ids")
    return failures


def check_transition() -> list[str]:
    """A live state from before the ledger: every kept id is added, and a gone id gets a row from its old site."""
    failures = []
    with tempfile.TemporaryDirectory() as temp:
        folder = Path(temp) / "evidence"
        loaded, rows = inventorytests.repository(temp)
        first, _ = inventorytests.committed(loaded, rows, DAYS[0])
        live = state.read_state(folder)
        state.commit(folder, {state.SITES: live.files[state.SITES]}, live.high_water)
        deleted = site_id(first, "xxPush", "0")
        loaded, rows = inventorytests.repository(temp, edited("    xxPush(0);\n", ""))
        second, _ = inventorytests.committed(loaded, rows, DAYS[1])
        found, text = live_ledger(folder), changes_text(folder)
        kept = sum(1 for record in second.records if record.covered)
        if f"- {ledger.ADDED}: {kept}\n" not in text or f"- {ledger.NEW}: 0\n" not in text:
            failures.append(f"every kept id is added to the ledger\n{text}")
        if f"## {ledger.ADDED}" in text:
            failures.append("added rows are counted, not listed")
        row = found.get(deleted)
        if row is None or (row.status, row.spelling, row.first_seen, row.file) != (ledger.GONE, "0", DAYS[1],
                                                                                    "src/a.c"):
            failures.append(f"a gone id with no ledger row gets one from its old site: {row}")
    return failures


def check_decisions() -> list[str]:
    """One decision through three runs: confirmed, stale after a tier move, open again after reopen. A rejected site
    that is deleted is orphaned, decide warns on it, an id that was never minted fails, and the backup keeps
    notes.csv."""
    failures = []
    with tempfile.TemporaryDirectory() as temp:
        folder = Path(temp) / "evidence"
        loaded, rows = inventorytests.repository(temp)
        first, made = inventorytests.committed(loaded, rows, DAYS[0])
        flags, pushed = site_id(first, "xxFlags", "3"), site_id(first, "xxPush", "0")
        decision, warnings = decisions.decide(folder, made.rows, flags, decisions.CONFIRM, "", "", TIME, {})
        if decision.candidate != "XXF_A | XXF_B" or warnings:
            failures.append(f"confirm takes the top candidate: {decision}, {warnings}")
        _, made = inventorytests.committed(loaded, rows, DAYS[1])
        if made.rows[flags].status != decisions.CONFIRMED or flags not in made.decided:
            failures.append(f"a confirmed row: {made.rows[flags]}")

        (folder / "argmap.csv").write_text(inventorytests.ARGMAP.replace(
            "xxFlags,1,flags,XXF_,header prototype", "xxFlags,1,flags,XXF_,unverified"), encoding="utf-8")
        _, made = inventorytests.committed(loaded, inventorytests.argmap.read_argmap(folder / "argmap.csv"), DAYS[2])
        text = changes_text(folder)
        stale = text.split(f"## {ledger.STALE_DECISION}")[-1].split("## ")[0]
        if made.rows[flags].status != decisions.STALE or f"- {flags} src/a.c:" not in stale or (
                f"3: confirm XXF_A | XXF_B at {TIME}, now XXF_A | XXF_B (meaning B, spelling none)") not in stale:
            failures.append(f"a tier move makes the decision stale, and the old decision stays visible\n{text}")

        decisions.decide(folder, made.rows, flags, decisions.REOPEN, "", "", TIME, {})
        decisions.decide(folder, made.rows, pushed, decisions.REJECT, "", "wrong group", TIME, {})
        loaded, rows = inventorytests.repository(temp, edited("    xxPush(0);\n", ""))
        _, made = inventorytests.committed(loaded, rows, DAYS[3])
        text = changes_text(folder)
        if made.rows[flags].status != inventory.OPEN:
            failures.append(f"reopen opens the row again: {made.rows[flags].status}")
        if made.rows[pushed].status != ledger.GONE or (
                f"- {pushed} gone: reject NULL at {TIME}: wrong group") not in text.split(f"## {ledger.ORPHANED}")[-1]:
            failures.append(f"a decision on a gone site is orphaned\n{text}")
        _, warnings = decisions.decide(folder, made.rows, pushed, decisions.REOPEN, "", "", TIME, {})
        if warnings != [f"{pushed} is gone: the decision is orphaned"]:
            failures.append(f"decide warns on a gone id: {warnings}")
        try:
            decisions.decide(folder, made.rows, "S999999", decisions.CONFIRM, "", "", TIME, {})
            failures.append("an id that was never minted fails")
        except decisions.DecisionError as error:
            if "no such id" not in str(error):
                failures.append(f"an unknown id: {error}")
        if not (max((Path(temp) / "backups").iterdir()) / decisions.NOTES).is_file():
            failures.append("the backup keeps notes.csv")
    return failures


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_format, check_runs, check_placeholders, check_fields, check_transition, check_decisions):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    print("\n".join(found) or "ledgertests: all passed")
    sys.exit(1 if found else 0)
