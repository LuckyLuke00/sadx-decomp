"""Unit tests for config.py: loading evidence/config.json, its faults, origins and the threshold table. Each check
works in a temp folder.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/configtests.py
run() calls every check and returns the failures. All names are made up.
"""

import copy
import json
import os
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import cheaders  # noqa: E402
import config  # noqa: E402
import remap  # noqa: E402

DATA = {
    "schema": 2,
    "sources": {"root": "src", "suffixes": [".c"], "encoding": "utf-8",
                "annotation": r"//\s*(?P<kind>FUNCTION):\s*XX\s+(?P<address>0x[0-9a-f]+)\s*$"},
    "target": {"name": "game", "profile": "msvc-vc10-x86-cpp", "search_path": ["inc"],
               "predefines": {"XX_ON": "1"}, "known_undefined": ["XX_OFF"], "umbrellas": ["src/own.h", "vendor.h"]},
    "references": [{"name": "other", "profile": "shc-c", "search_path": ["ref"], "umbrellas": ["vendor.h"],
                    "encoding": "latin-1"}],
    "origins": {"vendor": ["inc"], "deep": ["inc/deep"], "game": ["src"]},
    "backups": "backups",
    "kept": ["config.json"],
    "thresholds": {"cover_budget": 7},
    "samples": {"old": {"folders": ["ref", "D:/xx/abs"], "reference": "other", "encoding": "cp932"}},
    "manuals": [{"path": "ref/manual.txt", "reference": "other", "encoding": "latin-1"}],
    "placeholders": {"XX_ASSERT": "no-code", "XX_GUESS": "code"},
}


def loaded(data: dict, folder: str) -> config.Config:
    root = Path(folder)
    for name in ("src", "inc/deep", "ref", "evidence"):
        (root / name).mkdir(parents=True, exist_ok=True)
    (root / "src" / "own.h").write_text("", encoding="utf-8")
    (root / "evidence" / config.FILE).write_text(json.dumps(data), encoding="utf-8")
    return config.load(root, root / "evidence")


def fault(data, folder: str) -> str:
    """The ConfigError text that loading DATA raises, or "" when it raises none. DATA None writes no file."""
    try:
        if data is None:
            config.load(Path(folder), Path(folder) / "evidence")
        else:
            loaded(data, folder)
    except config.ConfigError as error:
        return str(error)
    return ""


def check_load() -> list[str]:
    failures = []
    with tempfile.TemporaryDirectory() as folder:
        found = loaded(DATA, folder)
        root = Path(folder)
        target = found.target
        if (target.name, target.config.profile.name, target.config.predefines) != ("game", "msvc-vc10-x86-cpp",
                                                                                 {"XX_ON": "1"}):
            failures.append(f"target {target}")
        if target.config.search_path != (str(root / "inc"),) or target.config.known_undefined != {"XX_OFF"}:
            failures.append(f"target paths {target.config.search_path} {target.config.known_undefined}")
        if target.umbrellas != (str(root / "src/own.h"), "vendor.h"):
            failures.append(f"umbrellas: a file path when the file exists, else a name: {target.umbrellas}")
        [reference] = found.references
        if (reference.name, reference.config.profile.name, reference.config.encoding) != ("other", "shc-c",
                                                                                         "latin-1"):
            failures.append(f"reference {reference}")
        if (found.sources.root, found.sources.suffixes) != (root / "src", (".c",)):
            failures.append(f"sources {found.sources}")
        if found.thresholds["cover_budget"] != 7 or found.thresholds["gate_brake"] != config.THRESHOLDS["gate_brake"]:
            failures.append(f"thresholds {found.thresholds}")
        if found.scores() != remap.Scores():
            failures.append(f"scores {found.scores()}")
        if found.samples != (config.SampleTree("old", (root / "ref", Path("D:/xx/abs")), "other", "cp932"),):
            failures.append(f"samples {found.samples}")
        if found.manuals != (config.Manual(root / "ref/manual.txt", "other", "latin-1"),):
            failures.append(f"manuals {found.manuals}")
        if found.placeholders != {"XX_ASSERT": "no-code", "XX_GUESS": "code"}:
            failures.append(f"placeholders {found.placeholders}")
        if found.reference("other") is not reference:
            failures.append("reference() finds a reference set by name")
        if found.backups != root / "backups" or found.kept != ("config.json",):
            failures.append(f"backups {found.backups} {found.kept}")
        for file, wanted in ((root / "inc/deep/a.h", "deep"), (root / "inc/a.h", "vendor"), (root / "src/b.h", "game"),
                             (root / "elsewhere/c.h", ""), ("<predefined>", config.PREDEFINED)):
            if found.origin(str(file)) != wanted:
                failures.append(f"origin of {file}: {found.origin(str(file))!r}, wanted {wanted!r}")
        if found.origin(str(root / "INC" / "x.h").replace("/", os.sep)) != "vendor":
            failures.append("origin: case and separators do not matter")
    return failures


def check_faults() -> list[str]:
    failures = []

    def changed(edit) -> dict:
        data = copy.deepcopy(DATA)
        edit(data)
        return data

    cases = (
        (None, "missing hand-owned file"),
        (changed(lambda data: data.update(extra=1)), "unknown keys extra"),
        (changed(lambda data: data.pop("kept")), "missing keys kept"),
        (changed(lambda data: data.update(schema=1)), "schema 1"),
        (changed(lambda data: data["thresholds"].update(xx_budget=1)), "unknown threshold 'xx_budget'"),
        (changed(lambda data: data["target"].update(profile="xx")), "unknown profile 'xx'"),
        (changed(lambda data: data["target"].pop("umbrellas")), "target: missing keys umbrellas"),
        (changed(lambda data: data["references"][0].update(extra=1)), "references[0]: unknown keys extra"),
        (changed(lambda data: data["sources"].update(annotation="//(?P<kind>X)")), "the groups kind and address"),
        (changed(lambda data: data["sources"].update(annotation="(")), "annotation:"),
        (changed(lambda data: data["samples"]["old"].update(reference="game")),
         "samples.old: unknown reference set 'game'"),
        (changed(lambda data: data["samples"]["old"].update(encoding="xx-codec")),
         "samples.old: unknown encoding 'xx-codec'"),
        (changed(lambda data: data["samples"]["old"].pop("encoding")), "samples.old: missing keys encoding"),
        (changed(lambda data: data["manuals"][0].update(extra=1)), "manuals[0]: unknown keys extra"),
        (changed(lambda data: data["placeholders"].update(XX_ASSERT="maybe")),
         "placeholders.XX_ASSERT: unknown kind 'maybe'; known: code, no-code"),
        (changed(lambda data: data.update(placeholders=["XX_ASSERT"])), "placeholders: not an object"),
    )
    for data, wanted in cases:
        with tempfile.TemporaryDirectory() as folder:
            found = fault(data, folder)
        if wanted not in found:
            failures.append(f"fault {wanted!r}: got {found!r}")
    with tempfile.TemporaryDirectory() as folder:
        loaded(DATA, folder)
        (Path(folder) / "evidence" / config.FILE).write_text("{", encoding="utf-8")
        if "config.json" not in fault(None, folder):
            failures.append("a JSON error names the file")
    return failures


def check_defaults() -> list[str]:
    """The threshold table takes its defaults from the modules that use them."""
    failures = []
    wanted = {"branch_cap": cheaders.Config.branch_cap, "remap_exact": remap.Scores.exact,
              "remap_rewrite": remap.Scores.rewrite, "remap_target": remap.Scores.target}
    for name, value in wanted.items():
        if config.THRESHOLDS[name] != value:
            failures.append(f"threshold {name} {config.THRESHOLDS[name]}, the module default is {value}")
    with tempfile.TemporaryDirectory() as folder:
        data = copy.deepcopy(DATA)
        data.pop("thresholds")
        if loaded(data, folder).thresholds != config.THRESHOLDS:
            failures.append("no overlay uses the defaults")
    return failures


def check_docs() -> list[str]:
    """The threshold table in docs/EVIDENCE.md equals the code defaults."""
    text = (Path(__file__).resolve().parents[2] / "docs" / "EVIDENCE.md").read_text(encoding="utf-8")
    block = text.split("<!-- thresholds -->", 1)[1].split("<!-- /thresholds -->", 1)[0]
    documented = {}
    for line in block.splitlines()[3:]:
        name, default = (cell.strip() for cell in line.split("|")[1:3])
        documented[name.strip("`")] = float(default) if "." in default else int(default)
    if documented != config.THRESHOLDS:
        return [f"docs/EVIDENCE.md thresholds {documented}, the code defaults are {config.THRESHOLDS}"]
    return []


def check_fingerprint() -> list[str]:
    """Equal settings give equal hashes; each setting that changes evaluation changes the hash."""
    failures = []

    def changed(edit) -> dict:
        data = copy.deepcopy(DATA)
        edit(data)
        return data

    with tempfile.TemporaryDirectory() as folder:
        base = loaded(DATA, folder).fingerprint()
        if loaded(copy.deepcopy(DATA), folder).fingerprint() != base:
            failures.append("equal settings give equal fingerprints")
        cases = {
            "an overlay": changed(lambda data: data["thresholds"].update(cover_budget=8)),
            "a predefine": changed(lambda data: data["target"]["predefines"].update(XX_ON="2")),
            "the include path order": changed(lambda data: data["target"].update(search_path=["ref", "inc"])),
            "the umbrella order": changed(lambda data: data["target"].update(umbrellas=["vendor.h", "src/own.h"])),
            "the known-undefined list": changed(lambda data: data["target"].update(known_undefined=[])),
            "a reference set": changed(lambda data: data["references"][0].update(profile="msvc-vc10-x86-c")),
            "a sample encoding": changed(lambda data: data["samples"]["old"].update(encoding="latin-1")),
            "a sample folder": changed(lambda data: data["samples"]["old"].update(folders=["ref"])),
            "a manual": changed(lambda data: data.pop("manuals")),
            "a placeholder kind": changed(lambda data: data["placeholders"].update(XX_GUESS="no-code")),
        }
        for label, data in cases.items():
            if loaded(data, folder).fingerprint() == base:
                failures.append(f"{label} changes the fingerprint")
    return failures


def run() -> list[str]:
    """Every check, in order. Returns the failures."""
    failures = []
    for check in (check_load, check_faults, check_defaults, check_docs, check_fingerprint):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    print("\n".join(found) or "configtests: all passed")
    sys.exit(1 if found else 0)
