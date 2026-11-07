"""The local configuration of the evidence tool: evidence/config.json, hand-owned.

{
  "schema": 2,
  "sources": {"root": "src", "suffixes": [".c", ".cpp"], "encoding": "utf-8", "annotation": "<regex>"},
  "target": <header set>,
  "references": [<header set>, ...],
  "origins": {"<origin>": ["<folder>", ...], ...},
  "backups": "<folder>",
  "kept": ["config.json", "argmap.csv", ...],
  "thresholds": {"<name>": <number>, ...},
  "samples": {"<sample tree>": {"folders": ["<folder>", ...], "reference": "<reference set>", "encoding": "<codec>"}},
  "manuals": [{"path": "<file>", "reference": "<reference set>", "encoding": "<codec>"}, ...],
  "placeholders": {"<macro>": "no-code" | "code", ...}
}

A header set is {"name", "profile", "search_path", "predefines", "known_undefined", "umbrellas", "encoding"}: one
closure per umbrella, read under the named compiler profile. The target set is the game's own build; the reference
sets are other header sources, such as a vendor SDK.

- Paths are relative to the repository root, or absolute. An umbrella is a file path when that file exists, else a
  name to find on the search path.
- The annotation regex has the groups kind and address. It is matched against each // comment of the game source.
- An origin names the folders whose headers it covers. A name's origin is the origin of the deepest folder that holds
  its definition; a predefined macro has the origin "predefined".
- "kept" lists the hand-owned files, relative to evidence/, that each backup holds.
- "thresholds" overrides entries of THRESHOLDS; an unknown entry is an error.
- "samples" names the sample trees, such as vendor sample code. The named reference set's headers and profile
  evaluate a tree's calls; the encoding decodes its files. Optional.
- "manuals" lists text dumps of vendor manuals, each read for the functions of its reference set. Optional.
- "placeholders" lists the game's placeholder macros: "no-code" for one that expands to no code, such as a guessed
  assert, "code" for one that stands for code the decomp could not name yet. Each use is a placeholder site. Optional.

Standard library only.
"""

import codecs
import hashlib
import json
import os
import re
from dataclasses import dataclass, field
from pathlib import Path

import cheaders
import profiles
import remap

SCHEMA = 2
RULES_VERSION = 6  # raised by hand for a deliberate change of meaning; part of every fingerprint
FILE = "config.json"
CODE = Path(__file__).resolve().parent  # the tool's sources: their hash is part of every fingerprint
KEYS = {"schema", "sources", "target", "references", "origins", "backups", "kept", "thresholds", "samples", "manuals",
        "placeholders"}
SET_KEYS = {"name", "profile", "search_path", "predefines", "known_undefined", "umbrellas", "encoding"}
SOURCE_KEYS = {"root", "suffixes", "encoding", "annotation"}
SAMPLE_KEYS = {"folders", "reference", "encoding"}
MANUAL_KEYS = {"path", "reference", "encoding"}
PLACEHOLDER_KINDS = ("code", "no-code")
PREDEFINED = "predefined"

# The one table of numbers that change what the tool reports. Each entry is a public default; config.json may
# override it. Every number that ranks or caps evidence belongs here.
THRESHOLDS = {
    "cover_budget": 128,  # lookups and composite walk visits per cover search
    "branch_cap": cheaders.Config.branch_cap,  # alternatives one macro name keeps
    "remap_exact": remap.Scores.exact,  # alignment scores of the three pair kinds
    "remap_rewrite": remap.Scores.rewrite,
    "remap_target": remap.Scores.target,
    "gate_brake": 0.30,  # unresolved plus unevaluated over coverage sites that stops the run at the gate
    "shingle_size": 5,  # tokens per shingle when sample files are compared for lineage
    "lineage_cut": 0.5,  # the Jaccard similarity at which two sample files share a lineage (complete linkage)
    "lineage_min_shingles": 50,  # a file with fewer shingles shares a lineage only by its relative path
    "spell_a_clusters": 5,  # spelling A: lineage clusters that pass the value, this alias's share, the literal share
    "spell_a_share": 0.9,
    "spell_a_literal": 0.1,
    "spell_b_clusters": 3,  # spelling B: the same three numbers
    "spell_b_share": 0.5,
    "spell_b_literal": 0.3,
    "spell_combo": 2,  # spelling A of a combination of names: clusters that spell that exact combination
    "composite_terms": 4,  # the most names in a composite cover, with one multi-bit name at least
    "yield_floor": 20,  # a module whose yield probe finds fewer sites stays out, with the count in gate.md
    "scope_min_values": 3,  # the lvalue check: distinct values one lvalue takes, all constants of one scope
    "pair_min_sites": 3,  # the kill switch of a paired function: compared slots whose value both builds know,
    "pair_min_rate": 0.5,  # and the share of them with the same value
}


class ConfigError(Exception):
    """config.json is missing or malformed."""


@dataclass(frozen=True)
class HeaderSet:
    name: str
    config: cheaders.Config
    umbrellas: tuple


@dataclass(frozen=True)
class Sources:
    root: Path
    suffixes: tuple
    encoding: str
    annotation: re.Pattern


@dataclass(frozen=True)
class SampleTree:
    name: str
    folders: tuple  # Path records
    reference: str  # the reference set that evaluates the tree's calls
    encoding: str


@dataclass(frozen=True)
class Manual:
    path: Path
    reference: str  # the reference set whose functions the manual describes
    encoding: str


@dataclass(frozen=True)
class Config:
    root: Path  # the repository
    folder: Path  # evidence/
    sources: Sources
    target: HeaderSet
    references: tuple  # HeaderSet records
    origins: tuple  # (canonical folder, origin name), deepest folder first
    backups: Path
    kept: tuple
    thresholds: dict
    samples: tuple = ()  # SampleTree records
    manuals: tuple = ()  # Manual records
    placeholders: dict = field(default_factory=dict)  # placeholder macro: "no-code" or "code"

    def origin(self, file: str) -> str:
        """The origin of the header FILE, "" when no origin folder holds it."""
        if file == "<predefined>":
            return PREDEFINED
        path = cheaders.canonical(file)
        return next((name for folder, name in self.origins if path.startswith(folder + os.sep)), "")

    def scores(self) -> remap.Scores:
        return remap.Scores(self.thresholds["remap_exact"], self.thresholds["remap_rewrite"],
                            self.thresholds["remap_target"])

    def reference(self, name: str) -> HeaderSet:
        return next(item for item in self.references if item.name == name)

    def fingerprint(self) -> str:
        """The configuration hash: every header set in order, the sample trees, the manuals, the placeholder macros,
        the threshold table, RULES_VERSION, the schema and the hash of the tool's sources (tests excluded). Canonical JSON, so equal
        settings give equal hashes."""
        sets = [{"name": item.name, "profile": [item.config.profile.name, item.config.profile.version],
                 "search_path": list(item.config.search_path), "predefines": item.config.predefines,
                 "known_undefined": sorted(item.config.known_undefined), "branch_cap": item.config.branch_cap,
                 "encoding": item.config.encoding, "umbrellas": list(item.umbrellas)}
                for item in (self.target, *self.references)]
        samples = [[tree.name, [str(folder) for folder in tree.folders], tree.reference, tree.encoding]
                   for tree in self.samples]
        manuals = [[str(manual.path), manual.reference, manual.encoding] for manual in self.manuals]
        code = hashlib.sha256()
        for path in sorted(CODE.glob("*.py")):
            if not path.stem.endswith("tests"):
                code.update(path.name.encode("utf-8") + b"\0" + path.read_bytes() + b"\0")
        data = {"schema": SCHEMA, "rules": RULES_VERSION, "sets": sets, "samples": samples, "manuals": manuals,
                "placeholders": self.placeholders, "thresholds": self.thresholds, "code": code.hexdigest()}
        return hashlib.sha256(json.dumps(data, sort_keys=True).encode("utf-8")).hexdigest()


def load(root: Path, folder: Path) -> Config:
    path = folder / FILE
    if not path.is_file():
        raise ConfigError(f"missing hand-owned file {path}")
    try:
        data = json.loads(path.read_text(encoding="utf-8"))
    except (UnicodeDecodeError, json.JSONDecodeError) as error:
        raise ConfigError(f"{path}: {error}") from error
    _keys(data, KEYS, {"schema", "sources", "target", "backups", "kept"}, str(path))
    if data["schema"] != SCHEMA:
        raise ConfigError(f"{path}: schema {data['schema']}, this tool reads schema {SCHEMA}")
    thresholds = dict(THRESHOLDS)
    for name, number in data.get("thresholds", {}).items():
        if name not in THRESHOLDS:
            raise ConfigError(f"{path}: unknown threshold {name!r}; known: {', '.join(sorted(THRESHOLDS))}")
        thresholds[name] = number
    origins = sorted(((cheaders.canonical(str(_path(root, item))), name)
                      for name, items in data.get("origins", {}).items() for item in items),
                     key=lambda entry: -len(entry[0]))
    references = tuple(_header_set(root, item, thresholds, f"{path}: references[{index}]")
                       for index, item in enumerate(data.get("references", [])))
    names = {item.name for item in references}
    samples = tuple(_sample(root, name, item, names, f"{path}: samples.{name}")
                    for name, item in data.get("samples", {}).items())
    manuals = tuple(_manual(root, item, names, f"{path}: manuals[{index}]")
                    for index, item in enumerate(data.get("manuals", [])))
    placeholders = _placeholders(data.get("placeholders", {}), f"{path}: placeholders")
    return Config(root, folder, _sources(root, data["sources"], f"{path}: sources"),
                  _header_set(root, data["target"], thresholds, f"{path}: target"), references,
                  tuple(origins), _path(root, data["backups"]), tuple(data["kept"]), thresholds, samples, manuals,
                  placeholders)


def _placeholders(data, where: str) -> dict:
    if not isinstance(data, dict):
        raise ConfigError(f"{where}: not an object")
    for macro, kind in data.items():
        if kind not in PLACEHOLDER_KINDS:
            raise ConfigError(f"{where}.{macro}: unknown kind {kind!r}; known: {', '.join(PLACEHOLDER_KINDS)}")
    return dict(data)


def _sample(root: Path, name: str, data, references: set, where: str) -> SampleTree:
    _check_reading(data, SAMPLE_KEYS, references, where)
    return SampleTree(name, tuple(_path(root, folder) for folder in data["folders"]), data["reference"],
                      data["encoding"])


def _manual(root: Path, data, references: set, where: str) -> Manual:
    _check_reading(data, MANUAL_KEYS, references, where)
    return Manual(_path(root, data["path"]), data["reference"], data["encoding"])


def _check_reading(data, allowed: set, references: set, where: str):
    """Checks the keys, the reference set and the encoding of one sample tree or manual entry."""
    _keys(data, allowed, allowed, where)
    if data["reference"] not in references:
        raise ConfigError(f"{where}: unknown reference set {data['reference']!r}")
    try:
        codecs.lookup(data["encoding"])
    except LookupError as error:
        raise ConfigError(f"{where}: unknown encoding {data['encoding']!r}") from error


def _keys(data, allowed: set, required: set, where: str):
    if not isinstance(data, dict):
        raise ConfigError(f"{where}: not an object")
    unknown, missing = set(data) - allowed, required - set(data)
    if unknown:
        raise ConfigError(f"{where}: unknown keys {', '.join(sorted(unknown))}")
    if missing:
        raise ConfigError(f"{where}: missing keys {', '.join(sorted(missing))}")


def _path(root: Path, text: str) -> Path:
    path = Path(text)
    return path if path.is_absolute() else root / path


def _sources(root: Path, data, where: str) -> Sources:
    _keys(data, SOURCE_KEYS, SOURCE_KEYS, where)
    try:
        annotation = re.compile(data["annotation"])
    except re.error as error:
        raise ConfigError(f"{where}: annotation: {error}") from error
    if not {"kind", "address"} <= set(annotation.groupindex):
        raise ConfigError(f"{where}: the annotation regex needs the groups kind and address")
    return Sources(_path(root, data["root"]), tuple(data["suffixes"]), data["encoding"], annotation)


def _header_set(root: Path, data, thresholds: dict, where: str) -> HeaderSet:
    _keys(data, SET_KEYS, {"name", "profile", "search_path", "umbrellas"}, where)
    if data["profile"] not in profiles.PROFILES:
        raise ConfigError(f"{where}: unknown profile {data['profile']!r}; known: {', '.join(sorted(profiles.PROFILES))}")
    config = cheaders.Config(profiles.PROFILES[data["profile"]],
                             tuple(str(_path(root, item)) for item in data["search_path"]),
                             dict(data.get("predefines", {})), frozenset(data.get("known_undefined", [])),
                             thresholds["branch_cap"], data.get("encoding", "utf-8"))
    umbrellas = tuple(str(_path(root, item)) if _path(root, item).is_file() else item for item in data["umbrellas"])
    return HeaderSet(data["name"], config, umbrellas)
