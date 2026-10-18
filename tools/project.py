"""Where the repo's files are, and which game it targets, for check.py.

The paths of the build, the game's target in reccmp-project.yml, and the search for the
original exe: the configured path first, then any Steam library.
Needs ruamel only when it reads a yml file, so the system Python can still load it.
"""

import csv
import functools
import re
import subprocess
import sys
import winreg
from pathlib import Path
from typing import NamedTuple

import library
import osutil
import progress
import toolchain

ROOT = progress.ROOT
VENV = ROOT / ".venv"
VENV_SCRIPTS = VENV / "Scripts"
VENV_PYTHON = VENV_SCRIPTS / "python.exe"
REQUIREMENTS = ROOT / "requirements.txt"
TOOLCHAIN = ROOT / ".toolchain"
BUILD = ROOT / "build"

PROJECT_YML = ROOT / "reccmp-project.yml"
USER_YML = ROOT / "reccmp-user.yml"
LIBRARY_CSV = ROOT / "src" / "library.csv"  # the data source of the game target
OUR_GAME = BUILD / "game.exe"  # the game target in CMakeLists.txt


class Game(NamedTuple):
    target: str  # the reccmp target, and the module name in every annotation
    filename: str
    sha256: str


@functools.cache
def game_config() -> Game:
    """The game: the one target in reccmp-project.yml."""
    targets = read_yml(PROJECT_YML)["targets"]
    if len(targets) != 1:
        sys.exit(f"{PROJECT_YML.name} must have exactly one target, the game. It has: {', '.join(targets)}")
    [(target, entry)] = targets.items()
    if not re.fullmatch(r"[A-Z0-9]+", target):
        sys.exit(f"{PROJECT_YML.name}: rename target {target} to capitals and digits only. "
                 "reccmp's annotation lint accepts nothing else.")
    if entry.get("marker_aliases"):
        sys.exit(f"{PROJECT_YML.name}: remove marker_aliases. Annotations name the target, {target}: "
                 "check.py picks each file's flags from those alone.")
    return Game(target, entry["filename"], entry["hash"]["sha256"])


def find_game_hint() -> str:
    return f'Run: python tools/check.py setup --game "<path to {game_config().filename}>"'


def run(command: list, cwd: Path = ROOT) -> subprocess.CompletedProcess:
    return osutil.run(command, cwd=cwd, env=toolchain.env(TOOLCHAIN, VENV_SCRIPTS))


def read_yml(path: Path):
    # ruamel is only in .venv. The system Python imports this module to create .venv, so the import waits.
    from ruamel.yaml import YAML

    return YAML(typ="safe").load(path)


def library_rows() -> list[library.Row]:
    """The rows of src/library.csv. A new game has none until `check.py library` writes it."""
    if not LIBRARY_CSV.exists():
        return []
    lines = [line for line in LIBRARY_CSV.read_text(encoding="utf-8").splitlines()
             if line.strip() and not line.lstrip().startswith("#")]
    return [library.Row(int(row["address"], 16), row["name"], row["symbol"], row["type"])
            for row in csv.DictReader(lines, delimiter="|")]


def configured_game() -> Path | None:
    """The game path in reccmp-user.yml, if it has one."""
    users = read_yml(USER_YML) if USER_YML.exists() else None
    path = (users or {}).get("targets", {}).get(game_config().target, {}).get("path")
    return Path(path) if path else None


def steam_libraries() -> list[Path]:
    """Steam's own folder and the libraries in its libraryfolders.vdf. Empty without Steam."""
    try:
        with winreg.OpenKey(winreg.HKEY_CURRENT_USER, r"Software\Valve\Steam") as key:
            steam = Path(winreg.QueryValueEx(key, "SteamPath")[0])
    except OSError:
        return []
    libraries = [steam]
    folders = steam / "steamapps" / "libraryfolders.vdf"
    if folders.exists():
        # Lines like: "path"    "D:\\SteamLibrary"
        found = re.findall(r'"path"\s+"([^"]+)"', folders.read_text(encoding="utf-8", errors="replace"))
        libraries += [Path(path.replace("\\\\", "\\")) for path in found]
    return libraries


def game_in_library(steam_library: Path, wanted: Game) -> Path | None:
    """The game in one Steam library, or None."""
    common = steam_library / "steamapps" / "common"
    for folder in sorted(common.iterdir()) if common.is_dir() else []:
        candidate = folder / wanted.filename
        if candidate.is_file() and osutil.sha256(candidate) == wanted.sha256:
            return candidate
    return None


def steam_game() -> Path | None:
    """The game in any Steam library on this machine, or None. The pinned SHA-256 picks it out."""
    for steam_library in steam_libraries():
        found = game_in_library(steam_library, game_config())
        if found is not None:
            return found
    return None


def require_game(given: Path | None = None) -> Path:
    """The original exe: the given one, the configured one if it is still there, or the one in a Steam library."""
    game = given
    if game is None:
        configured = configured_game()
        game = configured if configured and configured.is_file() else steam_game()
    if game is None:
        sys.exit(f"{game_config().filename} with the SHA-256 in {PROJECT_YML.name} is in no Steam library. "
                 f"{find_game_hint()}")
    if not game.is_file():
        sys.exit(f"{game} is not a file. {find_game_hint()}")
    if osutil.sha256(game) != game_config().sha256:
        sys.exit(f"{game} is another build than the one in {PROJECT_YML.name}: its SHA-256 differs. "
                 "README.md names the build this project targets.")
    return game
