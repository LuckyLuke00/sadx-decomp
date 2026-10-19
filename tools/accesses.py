"""How the whole exe reads and writes its globals: `check.py access`, and the dossier's --accesses lines.

One pass over every function in data/functions.csv records each memory operand and each immediate that points
into a data section. A record has the access size, whether a float instruction uses it, whether it reads or
writes, and its form: `direct`, indexed by a scaled register (`[reg*4]`), offset from a register (`[reg+]`), or
the address itself taken (`address`). The size and kind of the reads are evidence for a global's type.
build/accesses.tsv caches the pass until data/functions.csv changes. Needs capstone, so it runs in .venv.
"""

import bisect
import collections
import csv
from typing import NamedTuple

import capstone

import pe
import progress
import project

CACHE = project.BUILD / "accesses.tsv"
FIELDS = ["target", "size", "value", "form", "reads", "writes", "functions"]
EXECUTE = 0x20000000  # IMAGE_SCN_MEM_EXECUTE
# x87 instructions whose memory operand is an integer or a control block: every other x87 operand is a float.
X87_NOT_FLOAT = {"fild", "fist", "fistp", "fisttp", "ficom", "ficomp", "fiadd", "fisub", "fisubr", "fimul", "fidiv",
                 "fidivr", "fbld", "fbstp", "fldcw", "fnstcw", "fstcw", "fnstsw", "fstsw", "fldenv", "fnstenv",
                 "fstenv", "frstor", "fnsave", "fsave", "fxsave", "fxrstor"}
SSE_FLOAT = ("ss", "sd", "ps", "pd")  # suffixes of SSE instructions on floats


class Access(NamedTuple):
    target: int
    size: int  # bytes, 0 for a taken address
    value: str  # "float" or "int"
    form: str
    reads: int
    writes: int
    functions: list[int]


def value_kind(mnemonic: str) -> str:
    if mnemonic.startswith("f"):
        return "int" if mnemonic in X87_NOT_FLOAT else "float"
    if mnemonic.endswith(SSE_FLOAT) and not mnemonic.startswith(("cvtsi", "cvtpi", "movs", "cmps")):
        return "float"
    return "int"


def data_ranges(image: pe.Image) -> list[tuple[int, int]]:
    return sorted((start, start + size) for start, size, section in image.sections if not section.flags & EXECUTE)


def in_data(ranges: list[tuple[int, int]], address: int) -> bool:
    i = bisect.bisect_right(ranges, (address, float("inf"))) - 1
    return i >= 0 and ranges[i][0] <= address < ranges[i][1]


def operand_access(ins, op) -> tuple[int, int, str, str, int, int] | None:
    """(target, size, value, form, reads, writes) of one operand, or None when it holds no address."""
    if op.type == capstone.x86.X86_OP_IMM:
        return op.imm & 0xFFFFFFFF, 0, "int", "address", 0, 0
    if op.type != capstone.x86.X86_OP_MEM or not op.mem.disp:
        return None
    target = op.mem.disp & 0xFFFFFFFF
    if ins.mnemonic == "lea":
        return (target, 0, "int", "address", 0, 0) if not op.mem.base and not op.mem.index else None
    if op.mem.base:
        form = "[reg+]"
    elif op.mem.index:
        form = f"[reg*{op.mem.scale}]"
    else:
        form = "direct"
    return (target, op.size, value_kind(ins.mnemonic), form, int(bool(op.access & capstone.CS_AC_READ)),
            int(bool(op.access & capstone.CS_AC_WRITE)))


def function_accesses(md: capstone.Cs, code: bytes, start: int):
    """Each operand access in one function, data or not."""
    for ins in md.disasm(code, start):
        if ins.group(capstone.CS_GRP_CALL) or ins.group(capstone.CS_GRP_JUMP):
            continue  # their targets are code, and an indirect call reads a function pointer slot
        for op in ins.operands:
            found = operand_access(ins, op)
            if found is not None:
                yield found


def scan(image: pe.Image, sizes: dict[int, int]) -> list[Access]:
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    ranges = data_ranges(image)
    counts = collections.defaultdict(lambda: [0, 0, set()])
    for start, size in sizes.items():
        for found in function_accesses(md, image.read(start, size), start):
            if not in_data(ranges, found[0]):
                continue
            entry = counts[found[:4]]
            entry[0] += found[4]
            entry[1] += found[5]
            entry[2].add(start)
    return [Access(*key, reads, writes, sorted(functions)) for key, (reads, writes, functions) in sorted(counts.items())]


def write_cache(rows: list[Access]) -> None:
    CACHE.parent.mkdir(parents=True, exist_ok=True)
    with open(CACHE, "w", encoding="utf-8", newline="\n") as f:
        writer = csv.writer(f, delimiter="\t", lineterminator="\n")
        writer.writerow(FIELDS)
        for r in rows:
            writer.writerow([f"0x{r.target:08x}", r.size, r.value, r.form, r.reads, r.writes,
                             " ".join(f"0x{a:08x}" for a in r.functions)])


def load(image: pe.Image) -> list[Access]:
    """Every access in the exe, sorted by target. The cache is rebuilt when data/functions.csv is newer."""
    if not CACHE.exists() or CACHE.stat().st_mtime < progress.FUNCTIONS_CSV.stat().st_mtime:
        write_cache(scan(image, {f["address"]: f["size"] for f in progress.load_functions()}))
    with open(CACHE, encoding="utf-8", newline="") as f:
        return [Access(int(r["target"], 16), int(r["size"]), r["value"], r["form"], int(r["reads"]),
                       int(r["writes"]), [int(a, 16) for a in r["functions"].split()])
                for r in csv.DictReader(f, delimiter="\t")]


def within(rows: list[Access], start: int, size: int) -> list[Access]:
    """The accesses to the bytes start .. start+size-1 (at least the first byte)."""
    first = bisect.bisect_left(rows, start, key=lambda r: r.target)
    last = bisect.bisect_left(rows, start + max(size, 1), key=lambda r: r.target)
    return rows[first:last]


def describe(r: Access, start: int) -> str:
    if r.form == "address":
        return f"+0x{r.target - start:x} address taken in {len(r.functions)} function{'' if len(r.functions) == 1 else 's'}"
    form = "" if r.form == "direct" else f" via {r.form}"
    uses = ", ".join(f"{word} {n}" for word, n in (("read", r.reads), ("written", r.writes)) if n)
    return f"+0x{r.target - start:x} {r.size}-byte {r.value}{form}: {uses or 'used'}"


def summary(rows: list[Access], start: int, size: int, limit: int) -> str:
    """One line: the most used groups of accesses to a global, by offset."""
    found = within(rows, start, size)
    if not found:
        return "no instruction reads or writes it by address"
    shown = sorted(sorted(found, key=lambda r: -(r.reads + r.writes + len(r.functions)))[:limit],
                   key=lambda r: (r.target, r.form))
    more = f"; and {len(found) - limit} more" if len(found) > limit else ""
    return "; ".join(describe(r, start) for r in shown) + more


def show(game, addresses: list[int], size: int) -> int:
    rows = load(pe.Image(game))
    for address in addresses:
        found = within(rows, address, size)
        print(f"== 0x{address:08x} .. 0x{address + max(size, 1) - 1:08x}: {len(found)} kinds of access")
        for r in found:
            listed = " ".join(f"0x{a:08x}" for a in r.functions[:12])
            extra = f" and {len(r.functions) - 12} more" if len(r.functions) > 12 else ""
            print(f"  {describe(r, address)}  in {listed}{extra}")
    return 0
