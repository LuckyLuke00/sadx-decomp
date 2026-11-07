"""The evidence tool: bare numbers that may be standard names, literals that may be macros, and the evidence for and
against each. Its local state and outputs live in evidence/ at the repository root, which git must ignore.

Run with the venv python and -I: .venv/Scripts/python.exe -I tools/evidence/evidence.py <command>

Commands:
  audit             check that no deny-listed word is in what git would publish (tools/evidence/audit.py)
  run               the inventory with its ids and ledger, the baseline diff when a baseline exists, the meaning
                    tiers, the audit and the gate report (tools/evidence/pipeline.py); exit 1 when the brake fires
  import-baseline   copy an earlier inventory in as evidence/baseline-inventory.csv, once (tools/evidence/baseline.py)
  decide            decide <id> confirm|reject|reopen [--candidate NAME] [--note TEXT]: append a review decision to
                    evidence/notes.csv (tools/evidence/decisions.py); the next run reads it into the ledger
  pdbimport         pdbimport FILE [--map MAP.csv]: write prototypes.csv, enums.csv and scope-constants.csv into
                    evidence/ from a program database (tools/evidence/pdbimport.py)

Standard library only.
"""

import argparse
import datetime
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
FOLDER = ROOT / "evidence"
ARGMAP = "argmap.csv"
sys.path.insert(0, str(HERE))


def run_command() -> int:
    import argmap
    import audit
    import baseline
    import cheaders
    import config
    import decisions
    import gate
    import inventory
    import ledger
    import pairs
    import pipeline
    import state
    import symbols
    try:
        loaded = config.load(ROOT, FOLDER)
        rows = argmap.read_argmap(FOLDER / ARGMAP)
        stops, generation, notes = pipeline.run(loaded, rows, datetime.date.today().isoformat())
    except (gate.GateError, audit.AuditError, baseline.BaselineError, cheaders.HeaderError, config.ConfigError,
            argmap.ArgmapError, decisions.DecisionError, inventory.InventoryError, ledger.LedgerError,
            pairs.PairsError, state.StateError, symbols.SymbolsError) as error:
        print(f"evidence run: {error}", file=sys.stderr)
        return 1
    print("\n".join(notes + [f"generation {generation}, {FOLDER / gate.GATE}"]
                    + [f"brake {stop.kind}: {stop.stopped} of {stop.coverage} ({stop.share:.1%}), "
                       + ("FIRED" if stop.fired else "not fired") for stop in stops if stop.coverage]))
    return 1 if any(stop.fired for stop in stops) else 0


def import_command(source: Path) -> int:
    import baseline
    try:
        print(f"imported {baseline.import_baseline(source, FOLDER)}")
    except baseline.BaselineError as error:
        print(f"evidence import-baseline: {error}", file=sys.stderr)
        return 1
    return 0


def decide_command(site_id: str, decision: str, candidate: str, note: str) -> int:
    import decisions
    import ledger
    import score
    import state
    try:
        live = state.read_state(FOLDER)
        if live is None or ledger.LEDGER not in live.files:
            raise decisions.DecisionError("no ledger yet: run the tool first")
        rows = ledger.parse_ledger(live.files[ledger.LEDGER])
        aliases = score.read_aliases(FOLDER, live.generation, site_id)
        time = datetime.datetime.now(datetime.timezone.utc).isoformat(timespec="seconds")
        made, warnings = decisions.decide(FOLDER, rows, site_id, decision, candidate, note, time, aliases)
    except (decisions.DecisionError, ledger.LedgerError, state.StateError) as error:
        print(f"evidence decide: {error}", file=sys.stderr)
        return 1
    for warning in warnings:
        print(f"warning: {warning}", file=sys.stderr)
    print(f"{made.id}: {decisions.describe(made)}")
    return 0


def pdbimport_command(source: Path, mapping: Path | None) -> int:
    import pdbimport
    try:
        counts = pdbimport.import_file(source, mapping, FOLDER)
    except pdbimport.PdbError as error:
        print(f"evidence pdbimport: {error}", file=sys.stderr)
        return 1
    print(pdbimport.describe(counts))
    return 0


def main() -> int:
    import decisions
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    commands = parser.add_subparsers(dest="command", required=True)
    commands.add_parser("audit", help="check that no deny-listed word is in what git would publish")
    commands.add_parser("run", help="run the whole tool and write the reports in evidence/")
    copy = commands.add_parser("import-baseline", help="copy an earlier inventory in, once")
    copy.add_argument("source", type=Path, help="the earlier inventory.csv")
    decide = commands.add_parser("decide", help="append a review decision for one site id to evidence/notes.csv")
    decide.add_argument("id", help="the site id, such as S000123")
    decide.add_argument("decision", choices=decisions.DECISIONS)
    decide.add_argument("--candidate", default="", help="another candidate of the row than the top one, or a "
                        "candidate written with other aliases of its names")
    decide.add_argument("--note", default="", help="free text")
    reader = commands.add_parser("pdbimport", help="write the neutral symbol files from a program database")
    reader.add_argument("source", type=Path, help="the program database (.pdb)")
    reader.add_argument("--map", type=Path, default=None, help="reference,target address map (hex); without it the "
                        "files keep the reference addresses")
    args = parser.parse_args()
    if args.command == "audit":
        import audit
        return audit.main(ROOT)
    if args.command == "run":
        return run_command()
    if args.command == "decide":
        return decide_command(args.id, args.decision, args.candidate, args.note)
    if args.command == "pdbimport":
        return pdbimport_command(args.source, args.map)
    return import_command(args.source)


if __name__ == "__main__":
    sys.exit(main())
