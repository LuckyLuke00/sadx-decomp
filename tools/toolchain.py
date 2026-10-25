"""The portable VC++ 2010 SP1 toolchain that builds the decomp.

check.py calls ensure() before every build. The first time, it downloads the
Windows SDK 7.1 ISO and the VC++ 2010 SP1 compiler update from Microsoft
(722 MB) and checks their SHA-256. It unpacks them with Windows' own tools
(tar.exe, a read-only mount of the ISO and `msiexec /a`) and copies the files
the build uses into one folder. Nothing is installed and nothing downloaded is
run. Standard library only.
"""

import os
import shutil
import subprocess
import sys
import tempfile
import urllib.request
from pathlib import Path
from typing import NamedTuple

import osutil

CL_VERSION = "16.00.40219.01"
LINK_VERSION = "10.00.40219.01"
# What the build uses, and what cl.exe and link.exe need to start.
FILES = ["bin/cl.exe", "bin/link.exe", "bin/msvcr100.dll", "bin/msvcp100.dll", "bin/mspdb100.dll", "bin/RC.Exe",
         "bin/mt.exe", "include/stdio.h", "lib/libcmt.lib", "sdk/include/windows.h", "sdk/lib/kernel32.lib"]


class Download(NamedTuple):
    url: str
    size: int
    sha256: str

    @property
    def name(self) -> str:
        return self.url.rsplit("/", 1)[1]


SDK_ISO = Download(
    "https://download.microsoft.com/download/F/1/0/F10113F5-B750-4969-A255-274341AC6BCE/GRMSDK_EN_DVD.iso",
    594_841_600, "27cb38f76095c0acb9b558109f8693b39cbceb796856c15bd575f9e9d0b316c3")
COMPILER_UPDATE = Download(
    "https://download.microsoft.com/download/7/5/0/75040801-126C-4591-BCE4-4CD1FD1499AA/VC-Compiler-KB2519277.exe",
    126_890_440, "46497a249dac03f8a6d6b4f4a737546246752ca751ae16c34127a1d784232645")
DOWNLOADS = (COMPILER_UPDATE, SDK_ISO)

# The ISO folders that hold the SDK MSIs, and each MSI with the folder msiexec unpacks it into.
SDK_FOLDERS = ["Setup/WinSDKBuild", "Setup/WinSDKWin32Tools", "Setup/WinSDKTools", "Setup/vc_stdx86"]
MSIS = [
    ("kb/vc_stdx86.msi", "vc"),
    ("iso/Setup/vc_stdx86/vc_stdx86.msi", "vcrtm"),
    ("iso/Setup/WinSDKBuild/WinSDKBuild_x86.msi", "sdk"),
    ("iso/Setup/WinSDKWin32Tools/WinSDKWin32Tools_x86.msi", "rc"),
    ("iso/Setup/WinSDKTools/WinSDKTools_x86.msi", "mt"),
]
# Windows' own bsdtar reads CAB files. Git for Windows puts GNU tar, which can't, first on PATH.
TAR = Path(os.environ["SystemRoot"], "System32", "tar.exe")
# Downloads stay here until the toolchain is complete, so a failed run does not download again.
# The path must stay short: msiexec failed with error 1304 under a long one.
WORK = Path(tempfile.gettempdir(), "decomp-toolchain")


def ensure(dest: Path) -> None:
    """Make dest a complete toolchain, downloading it if it is not one yet."""
    if problem(dest) is None:
        return
    total = sum(item.size for item in DOWNLOADS)
    print(f"Setting up the VC++ 2010 SP1 compiler in {dest}: a {total / 1e6:.0f} MB download from Microsoft, once.")
    WORK.mkdir(parents=True, exist_ok=True)
    for item in DOWNLOADS:
        fetch(item)
    unpack()
    # The layout is built next to dest and renamed into place, so dest is only ever complete or absent.
    partial = dest.with_name(dest.name + ".partial")
    osutil.remove(partial)
    copy_layout(partial)
    reason = problem(partial)
    if reason:
        sys.exit(f"{partial}: {reason}")
    osutil.remove(dest)
    partial.rename(dest)
    osutil.remove(WORK)
    print(f"cl.exe {CL_VERSION} and link.exe {LINK_VERSION} are ready in {dest}.")


def problem(dest: Path) -> str | None:
    """Why dest is not a complete toolchain, or None when its files are there, cl.exe and link.exe run, and
    <intrin.h> compiles (an older layout's does not: see copy_layout)."""
    for name in FILES:
        if not dest.joinpath(name).exists():
            return f"missing {name}"
    for exe, version in (("cl.exe", CL_VERSION), ("link.exe", LINK_VERSION)):
        if version not in banner(dest, exe):
            return f"{exe} does not report version {version}"
    with tempfile.TemporaryDirectory() as folder:
        source = Path(folder, "intrin.cpp")
        source.write_text("#include <intrin.h>\n", encoding="ascii")
        result = subprocess.run([str(dest / "bin" / "cl.exe"), "/nologo", "/Zs", str(source)], capture_output=True,
                                text=True, env=env(dest))
    if result.returncode:
        return "<intrin.h> does not compile: " + (result.stdout + result.stderr).strip().splitlines()[-1]
    return None


def banner(dest: Path, exe: str) -> str:
    result = subprocess.run([str(dest / "bin" / exe)], capture_output=True, text=True, env=env(dest))
    return result.stdout + result.stderr


def env(dest: Path, *extra_path: Path) -> dict[str, str]:
    """The environment that runs the toolchain in dest: PATH, INCLUDE and LIB point into its layout."""
    return dict(os.environ,
                PATH=os.pathsep.join([str(dest / "bin"), *map(str, extra_path), os.environ["PATH"]]),
                INCLUDE=os.pathsep.join([str(dest / "include"), str(dest / "sdk" / "include")]),
                LIB=os.pathsep.join([str(dest / "lib"), str(dest / "sdk" / "lib")]))


# Download and unpack


def fetch(item: Download) -> None:
    target = WORK / item.name
    if target.exists() and wrong_file(target, item) is None:
        return
    print(f"Downloading {item.name} ({item.size / 1e6:.0f} MB).")
    partial = target.with_name(target.name + ".part")
    try:
        with urllib.request.urlopen(item.url, timeout=60) as response, partial.open("wb") as out:
            shutil.copyfileobj(response, out, 1 << 20)
    except OSError as error:
        sys.exit(f"Download failed: {item.url}: {error}")
    reason = wrong_file(partial, item)
    if reason:
        sys.exit(f"{item.name} is not the file this project pins: {reason}")
    partial.replace(target)


def wrong_file(path: Path, item: Download) -> str | None:
    """Why path is not the pinned file, or None when its size and SHA-256 match."""
    size = path.stat().st_size
    if size != item.size:
        return f"{size} bytes, expected {item.size}"
    digest = osutil.sha256(path)
    if digest != item.sha256:
        return f"SHA-256 {digest}, expected {item.sha256}"
    return None


def unpack() -> None:
    """tar reads the update's .exe as an archive, so its installer never runs."""
    for folder in ["kb", "iso", *(target for _, target in MSIS)]:
        osutil.remove(WORK / folder)
    (WORK / "kb").mkdir()
    osutil.run([TAR, "-xf", WORK / COMPILER_UPDATE.name, "-C", WORK / "kb"])
    copy_from_iso(WORK / SDK_ISO.name, WORK / "iso", SDK_FOLDERS)
    for msi, target in MSIS:
        osutil.run(["msiexec", "/a", WORK / msi, "/qn", f"TARGETDIR={WORK / target}"])


def copy_from_iso(iso: Path, dest: Path, folders: list[str]) -> None:
    """Windows mounts the SDK ISO, read-only and with no drive letter, and the folders are copied from it."""
    image = "-ImagePath '" + str(iso).replace("'", "''") + "'"
    dismount = f"Dismount-DiskImage {image} | Out-Null"
    osutil.powershell(f"Mount-DiskImage {image} -NoDriveLetter -Access ReadOnly | Out-Null")
    # Once it is mounted, every step that can fail runs inside the try, so the ISO is always dismounted.
    try:
        volume = osutil.powershell(f"(Get-DiskImage {image} | Get-Volume).Path").strip()
        if not volume:
            sys.exit(f"Windows mounted {iso} but reported no volume for it. Run again.")
        for folder in folders:
            osutil.copy_tree(Path(volume) / folder, dest / folder)
    except BaseException:
        # Keep the first error. A failed dismount now only prints a line, so it can't replace that error.
        if subprocess.run([*osutil.POWERSHELL, dismount], capture_output=True).returncode != 0:
            print(f"Also: {iso} is still mounted. Run `Dismount-DiskImage {image}` in PowerShell.",
                  file=sys.stderr)
        raise
    osutil.powershell(dismount)


# Layout


def copy_layout(dest: Path) -> None:
    """The folder layout that env() points PATH, INCLUDE and LIB at."""
    vs = WORK / "vc" / "Program Files" / "Microsoft Visual Studio 10.0"
    sdk = Path("Program Files", "Microsoft SDKs", "Windows", "v7.1")
    osutil.copy_tree(vs / "VC" / "include", dest / "include")
    # The update's intrin.h includes ammintrin.h, which the update does not ship. The SDK's own intrin.h differs
    # only in that include, so <vector> and <string> compile with it.
    osutil.copy_files(WORK / "vcrtm" / vs.relative_to(WORK / "vc") / "VC" / "include", dest / "include", ["intrin.h"])
    osutil.copy_tree(WORK / "sdk" / sdk / "Include", dest / "sdk" / "include")
    osutil.copy_files(vs / "VC" / "lib", dest / "lib")
    osutil.copy_files(WORK / "sdk" / sdk / "Lib", dest / "sdk" / "lib")
    osutil.copy_files(vs / "VC" / "bin", dest / "bin")
    osutil.copy_files(vs / "VC" / "bin" / "1033", dest / "bin" / "1033")
    osutil.copy_files(vs / "Common7" / "IDE", dest / "bin",
                      ["mspdb100.dll", "mspdbsrv.exe", "mspdbcore.dll", "msobj100.dll"])
    osutil.copy_files(WORK / "vc" / "Win" / "System", dest / "bin", ["msvcr100.dll", "msvcp100.dll"])
    osutil.copy_files(WORK / "rc" / sdk / "Bin", dest / "bin", ["RC.Exe", "RcDll.Dll"])
    osutil.copy_files(WORK / "mt" / sdk / "Bin", dest / "bin", ["mt.exe"])
