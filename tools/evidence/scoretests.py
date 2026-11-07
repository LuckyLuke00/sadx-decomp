"""Unit tests for score.py: each tier and each kind of counterevidence on hand-built sites, the counts, the
eligibility and the review order, and the tiers and outputs of a fixture repository.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/scoretests.py
run() calls every check and returns the failures. All names are made up, apart from generic toolchain words.
"""

import sys
import tempfile
from dataclasses import replace
from pathlib import Path
from types import SimpleNamespace

sys.path.insert(0, str(Path(__file__).parent))

import csv
import io

import argmap  # noqa: E402
import ceval  # noqa: E402
import covers  # noqa: E402
import decisions  # noqa: E402
import fields  # noqa: E402
import inventory  # noqa: E402
import inventorytests  # noqa: E402
import score  # noqa: E402
import spelling  # noqa: E402
import symbols  # noqa: E402

ROW = argmap.Row("xxFlags", 1, "flags", ("XXF_",), argmap.HEADER_PROTOTYPE, "vendor.h", "unsigned int", (), "", 2)
PASS = argmap.Check(True, "")
OK = ceval.Result(ceval.OK, 3, inventorytests.CPP.int_type("int"), literal=True)
FIELD_ROW = replace(ROW, callee="XX_OBJ.flags", slot=0, status=fields.HEADER_DECLARATION)


def site(names=("XXF_A", "XXF_B"), origins=("vendor",), uncertain=(), disputed=None, flags=(), row=ROW,
         check=PASS, accepted=(), result=OK, incomplete=False) -> inventory.Record:
    """A site whose one candidate splits into NAMES, each a node of its own."""
    terms = tuple(covers.Node((covers.Name(name, 1 << index, False, origins),), 1 << index)
                  for index, name in enumerate(names))
    search = covers.Search([covers.Candidate(terms, False)] if names else [], incomplete)
    pool = inventory.Pool([alias for node in terms for alias in node.aliases], set(uncertain), dict(disputed or {}),
                          None)
    return inventory.Record("src/a.c", 1, 1, "0x1", "xxFlags", "1", "xxFlags", "3", "3", result, row, check, "",
                            list(flags), search, pool, None, accepted, id="S000001")


def check_tiers() -> list[str]:
    unverified = replace(ROW, status=argmap.UNVERIFIED, header="", spelled_type="")
    cases = [
        ("A", site(), score.A, ()),
        ("A disputed", site(disputed={"XXF_B": "shc-c gives 4"}), score.A_STAR, ("XXF_B: shc-c gives 4",)),
        ("A origin", site(accepted=("crt",)), score.A_STAR,
         ("XXF_A: origin vendor not accepted", "XXF_B: origin vendor not accepted")),
        ("A accepted", site(accepted=("crt", "vendor")), score.A, ()),
        ("A disagree", site(flags=("closures disagree", "include")), score.A_STAR, ("closures disagree",)),
        ("A prototype", site(flags=("target prototype differs",)), score.A_STAR, ("target prototype differs",)),
        ("B unverified", site(row=unverified), score.B, ()),
        ("B check", site(check=argmap.Check(False, "vendor.h spells argument 1 'int'")), score.B, ()),
        ("B with counter", site(row=unverified, accepted=("crt",)), score.B,
         ("XXF_A: origin vendor not accepted", "XXF_B: origin vendor not accepted")),
        ("C", site(uncertain=("XXF_B",)), score.C, ()),
        ("incomplete", site(incomplete=True), score.INCOMPLETE, ()),
        ("no candidate", site(names=()), score.NO_CANDIDATE, ()),
        ("incomplete, no cover", site(names=(), incomplete=True), score.NO_CANDIDATE, ()),
        ("unresolved", site(result=ceval.failure(ceval.UNRESOLVED, "unknown identifier", "XX_X")), score.UNRESOLVED,
         ()),
        ("unevaluated", site(result=ceval.failure(ceval.UNSUPPORTED, "arity")), score.UNEVALUATED, ()),
        ("placeholder", replace(site(), kind=inventory.PLACEHOLDER), score.PLACEHOLDER, ()),
    ]
    failures = []
    for label, record, tier, counter in cases:
        got = score.grade_site(record)
        if (got.tier, got.counter) != (tier, counter):
            failures.append(f"{label}: {got.tier} {got.counter}, wanted {tier} {counter}")
    reasons = [score.grade_site(record).reason for record in (cases[6][1], cases[7][1], cases[0][1])]
    if reasons != [score.UNVERIFIED_ROW, score.CHECK_FAILED, ""]:
        failures.append(f"B reasons {reasons}")
    if score.grade_site(site(origins=("vendor", "crt"))).origins != ("crt", "vendor"):
        failures.append("the origins of a candidate are sorted and unique")
    return failures


def field_site(row=FIELD_ROW, **changes) -> inventory.Record:
    """A field site of ROW; CHANGES as site() takes them."""
    return replace(site(row=row, **changes), kind=inventory.FIELD)


def check_fields() -> list[str]:
    """A field site of a header-declaration row whose member check passed is A; a target member of another type is
    counterevidence; an unverified row, a failed member check and a member name only give B, each with its reason."""
    failures = []
    for label, record, tier, counter, reason in (
            ("A", field_site(), score.A, (), ""),
            ("member differs", field_site(flags=("target member differs",)), score.A_STAR,
             ("target member differs",), ""),
            ("unverified", field_site(replace(FIELD_ROW, status=argmap.UNVERIFIED)), score.B, (), score.UNVERIFIED_ROW),
            ("check", field_site(check=argmap.Check(False, "xx.h's XX_OBJ has no member flags")), score.B, (),
             score.MEMBER_CHECK_FAILED),
            ("name only", field_site(flags=(inventory.MEMBER_NAME_ONLY,)), score.B, (), inventory.MEMBER_NAME_ONLY)):
        got = score.grade_site(record)
        if (got.tier, got.counter, got.reason) != (tier, counter, reason):
            failures.append(f"field {label}: {got}, wanted {tier} {counter} {reason!r}")
    return failures


def check_counts() -> list[str]:
    unverified = replace(ROW, status=argmap.UNVERIFIED)
    nonconstant = ceval.failure(ceval.NONCONSTANT, "variable", "m")
    records = [site(), site(origins=("crt",)), site(row=unverified), site(result=nonconstant), site(names=())]
    got = score.tier_counts(records)
    wanted = {"A": 2, "A vendor": 1, "A crt": 1, "B": 1, "B unverified row": 1, "no candidate": 1}
    return [] if got == wanted else [f"counts {dict(got)}, wanted {wanted}"]


def check_eligibility() -> list[str]:
    """Eligible: a sampled site, meaning A, top spelling A or B, status open or stale. A site that no sample tree reads
    is not eligible by construction. Eligible sites come first in review order."""
    spelled = {tier: (spelling.Spelling(tier, "XXF_A | XXF_B"),) for tier in spelling.ORDER}
    unverified = replace(ROW, status=argmap.UNVERIFIED)
    cases = [
        ("A, spelling A, open", replace(site(), sampled=True, spellings=spelled["A"]), inventory.OPEN, score.YES),
        ("spelling B", replace(site(), sampled=True, spellings=spelled["B"]), inventory.OPEN, score.YES),
        ("stale", replace(site(), sampled=True, spellings=spelled["A"]), decisions.STALE, score.YES),
        ("spelling C", replace(site(), sampled=True, spellings=spelled["C"]), inventory.OPEN, score.NO),
        ("no spelling", replace(site(), sampled=True), inventory.OPEN, score.NO),
        ("meaning B", replace(site(row=unverified), sampled=True, spellings=spelled["A"]), inventory.OPEN, score.NO),
        ("applied", replace(site(), sampled=True, spellings=spelled["A"]), inventory.APPLIED, score.NO),
        ("confirmed", replace(site(), sampled=True, spellings=spelled["A"]), decisions.CONFIRMED, score.NO),
        ("not sampled", replace(site(), spellings=spelled["A"]), inventory.OPEN, score.NO_SAMPLE),
        ("placeholder", replace(site(), kind=inventory.PLACEHOLDER), inventory.OPEN, score.NO),
    ]
    failures = []
    for label, record, status, wanted in cases:
        got = score.eligibility(record, score.grade_site(record), spelling.top_of(record.spellings), status)
        if got != wanted:
            failures.append(f"eligibility {label}: {got}, wanted {wanted}")
    later = replace(site(), sampled=True, spellings=spelled["A"], id="S000002")
    rows = {key: SimpleNamespace(status=inventory.OPEN) for key in ("S000001", "S000002")}
    ranked = score.review_order([site(), later], rows)
    if [(item.record.id, item.eligible) for item in ranked] != [("S000002", score.YES), ("S000001", score.NO_SAMPLE)]:
        failures.append(f"eligible sites come first: {[(item.record.id, item.eligible) for item in ranked]}")
    return failures


ENUM_ROW = argmap.Row("xxGame", 2, "value", ("enum XX_MODE",), symbols.REFERENCE_PROTOTYPE, "", "enum XX_MODE",
                      (symbols.REFERENCE,), symbols.PROTOTYPES, 0)
SCOPE_ROW = replace(ENUM_ROW, callee="stepper", slot=0, groups=("enum STEP",), status=symbols.REFERENCE_SCOPE,
                    spelled_type="", note="")


def reference_site(row=ENUM_ROW, flags=(), **changes) -> inventory.Record:
    """A site of a reference-symbol ROW whose one candidate is one name of reference origin; CHANGES as replace()
    takes them."""
    record = site(names=("XX_MODE_ON",), origins=(symbols.REFERENCE,), row=row, flags=flags,
                  accepted=(symbols.REFERENCE,))
    return replace(record, **changes)


def check_references() -> list[str]:
    """A reference enum row gives A; a scope row gives A only with the lvalue check, else B. A one-enumerator site of
    meaning A is eligible without spelling while it is open or stale. Open or stale sites of meaning A with a
    reference origin go on the reference list: one enumerator first, then the lvalue check, then site count, then
    id."""
    failures = []
    for label, record, tier, reason in (
            ("enum", reference_site(), score.A, ""),
            ("scope", reference_site(SCOPE_ROW), score.B, score.SCOPE_ONLY),
            ("scope with the lvalue check", reference_site(SCOPE_ROW, (symbols.LVALUE_CHECK,)), score.A, "")):
        got = score.grade_site(record)
        if (got.tier, got.reason) != (tier, reason):
            failures.append(f"reference {label}: {got}, wanted {tier} {reason!r}")
    one = reference_site(flags=(symbols.ONE_ENUMERATOR,))
    eligible = [score.eligibility(one, score.grade_site(one), spelling.top_of(()), status)
                for status in (inventory.OPEN, decisions.STALE, inventory.APPLIED)]
    if eligible != [score.YES, score.YES, score.NO_SAMPLE]:
        failures.append(f"one-enumerator eligibility {eligible}")
    lists = [score.review_list(record, score.grade_site(record), status) for record, status in (
        (one, inventory.OPEN), (one, inventory.APPLIED), (reference_site(SCOPE_ROW), inventory.OPEN),
        (site(), inventory.OPEN))]
    if lists != [score.REFERENCE_LIST, score.REVIEW_LIST, score.REVIEW_LIST, score.REVIEW_LIST]:
        failures.append(f"lists {lists}")
    records = [reference_site(id="S000001", target="xxLone"),
               reference_site(SCOPE_ROW, (symbols.LVALUE_CHECK,), id="S000002"),
               reference_site(flags=(symbols.ONE_ENUMERATOR,), id="S000003"),
               reference_site(id="S000004"), reference_site(id="S000005"), replace(site(), id="S000006")]
    rows = {record.id: SimpleNamespace(status=inventory.OPEN) for record in records}
    ranked = score.review_order(records, rows)
    order = [(item.record.id, item.review_list) for item in ranked]
    wanted = [("S000006", score.REVIEW_LIST)] + [(f"S00000{number}", score.REFERENCE_LIST) for number in (3, 2, 4, 5, 1)]
    if order != wanted:
        failures.append(f"reference order {order}")
    text = score.summary_text(records, ranked, 1, None)
    if "## Reference names\n\n- sites: 5; one enumerator 1; lvalue check 1\n" not in text:
        failures.append(f"confidence.md lists the reference names\n{text}")
    return failures


def check_fixture() -> list[str]:
    """Through the inventory: NULL at a header-prototype pointer slot is A; a failed check is B."""
    with tempfile.TemporaryDirectory() as folder:
        found = inventory.build(*inventorytests.repository(folder))
    got = [(record.callee, record.expression, score.grade_site(record).tier) for record in found.records
           if record.covered]
    wanted = [("xxPush", "0", "A"), ("xxPush", "NULL", "A"), ("xxFlags", "XXF_A | 4", "A"), ("xxFlags", "3", "A"),
              ("xxFlags", "0", "A"), ("xxMode", "1", "A"), ("xxMode", "1", "unevaluated"),
              ("xxMode", "XX_UNKNOWN", "unresolved"), ("xxCount", "XXF_A", "B"), ("xxFlags", "XXF_B", "A")]
    return [] if got == wanted else [f"fixture tiers {got}"]


def check_fixture_origins() -> list[str]:
    """The row's origins are the origins of its names: they never hide its header's prototype. The default is the
    origin of the header that declares the callee."""
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        loaded, _ = inventorytests.repository(folder)
        text = inventorytests.ARGMAP.replace("vendor.h,XX_T *,,", "vendor.h,XX_T *,other,")
        (loaded.folder / "argmap.csv").write_text(text, encoding="utf-8")
        found = inventory.build(loaded, argmap.read_argmap(loaded.folder / "argmap.csv"))
    push = next(record for record in found.records if record.callee == "xxPush")
    flags = next(record for record in found.records if record.callee == "xxFlags")
    if not push.check.passed or push.accepted != ("other",):
        failures.append(f"a row with origins keeps its prototype: {push.check}, {push.accepted}")
    if score.grade_site(push).counter != ("NULL: origin vendor not accepted",):
        failures.append(f"a name of another origin is counterevidence: {score.grade_site(push)}")
    if flags.accepted != ("vendor",):
        failures.append(f"the default accepted origin is the header's: {flags.accepted}")
    return failures


def check_outputs() -> list[str]:
    """confidence.csv, candidates.csv and confidence.md: review order, the phase-1 note, the rollup."""
    failures = []
    with tempfile.TemporaryDirectory() as temp:
        loaded, rows = inventorytests.repository(temp)
        found, made = inventorytests.committed(loaded, rows)
        score.write(loaded.folder, found.records, made.generation, None, made.rows, made.decided)
        confidence = (loaded.folder / score.CONFIDENCE).read_text(encoding="utf-8").split("\n")
        candidates = (loaded.folder / score.CANDIDATES).read_text(encoding="utf-8").split("\n")
        text = (loaded.folder / score.CONFIDENCE_MD).read_text(encoding="utf-8")
        score.write(loaded.folder, found.records, made.generation, [], made.rows, made.decided)
        with_diff = (loaded.folder / score.CONFIDENCE_MD).read_text(encoding="utf-8")
    if confidence[:2] != ["# evidence-confidence generation=1", ",".join(score.CONFIDENCE_COLUMNS)]:
        failures.append(f"confidence.csv header {confidence[:2]}")
    table = [line.split(",") for line in confidence[2:] if line]
    got = [(fields[2], fields[4], fields[7], fields[8]) for fields in table]
    wanted = [("A", "2", "xxPush", "0"), ("A", "2", "xxPush", "NULL"), ("A", "1", "xxFlags", "XXF_A | 0x4"),
              ("A", "1", "xxFlags", "3"), ("A", "1", "xxFlags", "( 0x0 )"), ("A", "1", "xxMode", "1"),
              ("A", "1", "xxFlags", "XXF_B"), ("B", "1", "xxCount", "XXF_A"), ("unevaluated", "1", "xxMode", "1"),
              ("unresolved", "1", "xxMode", "XX_UNKNOWN")]
    if got != wanted:
        failures.append(f"review order {got}")
    if any((fields[1], fields[3], fields[15]) != (score.NO_SAMPLE, spelling.NONE, "") for fields in table):
        failures.append("with no sample tree, no site is sampled and no site has a spelling")
    if candidates[0] != "# evidence-candidates generation=1" or "1,XXF_A | XXF_B,A,none,vendor,XXF_A XXF_B" not in (
            "\n".join(candidates)):
        failures.append(f"candidates.csv {candidates[:4]}")
    if not text.startswith("# Confidence, generation 1\n\n" + score.NOTE + "\n"):
        failures.append("confidence.md opens with the phase-1 note")
    for line in ("- A: 7\n  - vendor: 7\n", "- B: 1\n  - prototype check failed: 1\n  - origins vendor: 1\n",
                 "- call: yes 0, no 0, no sample 10\n", "| xxPush | 1 | 0 | 2 | A 2 | none | NULL |",
                 "| xxMode | 1 | expression XX_UNKNOWN | 1 | unresolved 1 | none |  |"):
        if line not in text:
            failures.append(f"confidence.md lacks {line!r}\n{text}")
    if "## Baseline diff causes" in text or "## Baseline diff causes" not in with_diff:
        failures.append("the baseline section comes only with a baseline diff")
    return failures


def check_aliases() -> list[str]:
    """The aliases column joins the aliases of each term; read_aliases gives a site's candidates back as alias groups,
    and fails on a candidates.csv of another generation."""
    failures = []
    names = (covers.Name("XXF_A", 1, False), covers.Name("XXF_AA", 1, False))
    candidate = covers.Candidate((covers.Node(names, 1), covers.Node((covers.Name("XXF_B", 2, False),), 2)), False)
    if score.alias_column(candidate) != "XXF_A=XXF_AA XXF_B":
        failures.append(f"alias column {score.alias_column(candidate)!r}")
    with tempfile.TemporaryDirectory() as temp:
        loaded, rows = inventorytests.repository(temp)
        found, made = inventorytests.committed(loaded, rows)
        score.write(loaded.folder, found.records, made.generation, None, made.rows, made.decided)
        data = (loaded.folder / score.CANDIDATES).read_text(encoding="utf-8").split("\n", 1)[1]
        site_id = next(fields["id"] for fields in csv.DictReader(io.StringIO(data))
                       if fields["name"] == "XXF_A | XXF_B")
        got = score.read_aliases(loaded.folder, made.generation, site_id)
        if got != {"XXF_A | XXF_B": (("XXF_A",), ("XXF_B",))}:
            failures.append(f"read_aliases {got}")
        try:
            score.read_aliases(loaded.folder, made.generation + 1, site_id)
            failures.append("no fault for a candidates.csv of another generation")
        except decisions.DecisionError as error:
            if "run the tool first" not in str(error):
                failures.append(f"fault {error}")
    return failures


def check_placeholders() -> list[str]:
    """Placeholder sites: their own list, last in review order, kept out of the review tables, with a table per macro
    in confidence.md."""
    failures = []
    settings = dict(inventorytests.CONFIG, placeholders={"XX_ASSERT": "no-code", "XX_GUESS": "code"})
    files = dict(inventorytests.FILES, **{"src/d.c": inventorytests.D_C})
    with tempfile.TemporaryDirectory() as temp:
        loaded, rows = inventorytests.repository(temp, files, settings)
        found, made = inventorytests.committed(loaded, rows)
        score.write(loaded.folder, found.records, made.generation, None, made.rows, made.decided)
        data = (loaded.folder / score.CONFIDENCE).read_text(encoding="utf-8").split("\n", 1)[1]
        text = (loaded.folder / score.CONFIDENCE_MD).read_text(encoding="utf-8")
    table = list(csv.DictReader(io.StringIO(data)))
    lists = [(fields["list"], fields["meaning"], fields["eligible"]) for fields in table]
    wanted = [(score.REVIEW_LIST, fields["meaning"], fields["eligible"]) for fields in table[:10]]
    wanted += [(score.PLACEHOLDER_LIST, score.PLACEHOLDER, score.NO)] * 3
    if lists != wanted:
        failures.append(f"lists in review order {lists}")
    for line in ("- placeholder: 3\n", "- call: yes 0, no 0, no sample 10\n", "## Placeholders\n",
                 "| XX_ASSERT | no-code | 2 | open 2 | literal inside a no-code macro 1 |",
                 "| XX_GUESS | code | 1 | open 1 |  |"):
        if line not in text:
            failures.append(f"confidence.md lacks {line!r}\n{text}")
    if "| XX_ASSERT |  |" in text:
        failures.append("the rollup by target leaves placeholders out")
    return failures


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_tiers, check_fields, check_counts, check_eligibility, check_references, check_fixture,
                  check_fixture_origins, check_outputs, check_aliases, check_placeholders):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    print("\n".join(found) or "scoretests: all passed")
    sys.exit(1 if found else 0)
