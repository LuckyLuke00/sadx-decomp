#!/usr/bin/env python3
"""Write the progress as an objdiff report, which decomp.dev and decomp.fun read.

  python tools/objdiffreport.py [--out PATH]

The format is version 2 of objdiff-core's protos/report.proto, as JSON: the
proto's field names, and 64-bit numbers as strings, as objdiff writes them. Each
source file under src is a unit with the game functions it annotates. The game
functions no source file has yet form one more unit for each area. The areas are
the categories. Data counts only in the report's own measures, because
summary.json does not tie a global to a file. Reads the same committed files as
pages.py and writes PATH (default report.json). On GitHub Actions it also sets
the step output `target` to the target name. Run as a script it reruns itself
in .venv, as the areas need its packages.
"""

import argparse
import collections
import json
import os
from pathlib import Path

import pages
import progress
import scoring

REPORT_VERSION = 2  # objdiff-core's REPORT_VERSION
NOT_STARTED = "not-started"  # the folder of the units that hold an area's functions with no source file


def percent(part: float, whole: float) -> float:
    return 100 * scoring.ratio(part, whole)


def measures(site: pages.Site, addresses: list[int], data: tuple[int, int] = (0, 0)) -> dict:
    """objdiff's measures for the game functions at ADDRESSES and the DATA share (matched, all) in bytes. The fuzzy
    share weighs each function's score by its size."""
    code = site.area_code(addresses)
    fuzzy = sum(site.sizes[address] * scoring.score(site.entries[address])
                for address in addresses if address in site.entries)
    matched = sum(1 for address in addresses if site.is_matched(address))
    return {"fuzzy_match_percent": percent(fuzzy, code.game),
            "total_code": str(code.game), "matched_code": str(code.matched),
            "matched_code_percent": percent(code.matched, code.game),
            "total_data": str(data[1]), "matched_data": str(data[0]), "matched_data_percent": percent(*data),
            "total_functions": len(addresses), "matched_functions": matched,
            "matched_functions_percent": percent(matched, len(addresses))}


def function_item(site: pages.Site, address: int) -> dict:
    entry = site.entries.get(address)
    return {"name": entry["name"] if entry else f"FUN_{address:08x}", "size": str(site.sizes[address]),
            "fuzzy_match_percent": 100 * scoring.score(entry) if entry else 0.0,
            "metadata": {"virtual_address": str(address)}}


def unit_members(site: pages.Site) -> dict[str, list[int]]:
    """The game functions of each unit, by unit name: the first source file that annotates a function, else its
    area's unit in NOT_STARTED."""
    found = collections.defaultdict(list)
    for address in sorted(site.game):
        files = site.sources.get(address)
        found[files[0] if files else f"{NOT_STARTED}/{site.area_of[address]}"].append(address)
    return dict(sorted(found.items()))


def unit(site: pages.Site, name: str, addresses: list[int]) -> dict:
    metadata = {"progress_categories": sorted({site.area_of[address] for address in addresses})}
    if name.startswith(f"{NOT_STARTED}/"):
        metadata["auto_generated"] = True
    else:
        metadata["source_path"] = name
    return {"name": name, "measures": measures(site, addresses),
            "functions": [function_item(site, address) for address in addresses], "metadata": metadata}


def report(site: pages.Site) -> dict:
    units = [unit(site, name, addresses) for name, addresses in unit_members(site).items()]
    overall = measures(site, sorted(site.game), scoring.data_share(site.summary))
    overall["total_units"] = len(units)
    categories = [{"id": area, "name": site.area_title(area), "measures": measures(site, addresses)}
                  for area, addresses in site.areas().items()]
    return {"measures": overall, "units": units, "version": REPORT_VERSION, "categories": categories}


def main() -> None:
    parser = argparse.ArgumentParser(description="Write the progress as an objdiff report.")
    parser.add_argument("--out", type=Path, default=progress.ROOT / "report.json",
                        help="output file (default: report.json)")
    out = parser.parse_args().out
    site = pages.Site()
    out.write_text(json.dumps(report(site), indent=1) + "\n", encoding="utf-8", newline="\n")
    print(f"Wrote {out}")
    path = os.environ.get("GITHUB_OUTPUT")
    if path:  # CI names the artifact <target>_report, the name decomp.dev and decomp.fun look for
        with open(path, "a", encoding="utf-8") as outputs:
            outputs.write(f"target={site.summary['target']}\n")


if __name__ == "__main__":
    import check  # here, not at the top: only the script run needs it

    check.rerun_in_venv(__file__)
    main()
