"""The tells of one function that docs/PORTING.md section 6 lists: how it starts, how it
handles its stack and exceptions, and which string literals and floats it uses.

groups.py counts them for each code group. A tell is a fact about the code that only some
compiler flags can make. The float tells are in floattells.py.

Needs capstone, so it runs in .venv.
"""

import re
import sys
from typing import NamedTuple

import capstone

import floattells
import pe
import x86

IMMEDIATE = re.compile(r"eax, (0x[0-9a-f]+|\d+)")
ESP_READ = re.compile(r"\[esp(?: \+ (0x[0-9a-f]+|\d+))?\]")
CHKSTK = ("__chkstk", "__alloca_probe")  # mov eax, size; call __chkstk reserves size bytes of stack


def security_cookie(image: pe.Image, names: dict[int, str]) -> int | None:
    """The address of ___security_cookie, which __security_check_cookie compares ecx with."""
    check = next((address for address, name in names.items() if name == "@__security_check_cookie@4"), None)
    if check is None:
        return None
    disassembler = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    _, _, mnemonic, operands = next(disassembler.disasm_lite(image.read(check, 6), check))
    found = x86.SLOT.fullmatch(operands.removeprefix("ecx, "))
    if mnemonic != "cmp" or not found:
        sys.exit(f"0x{check:08x} __security_check_cookie does not start with cmp ecx, [___security_cookie].")
    return int(found.group(1), 16)


class StringFinder:
    """String literals in read-only data: text of 4 or more printable characters after a zero byte."""

    def __init__(self, image: pe.Image):
        self.image = image
        self.ranges = [(start, start + length) for start, length, section in image.sections
                       if not section.flags & (pe.CODE | pe.WRITABLE)]

    def at(self, address: int) -> bytes | None:
        if not any(start < address < end for start, end in self.ranges) or self.image.read(address - 1, 1) != b"\0":
            return None
        text = self.image.read(address, 4096).split(b"\0")[0]
        return text if len(text) >= 4 and all(32 <= c < 127 or c in (9, 10, 13) for c in text) else None

    def used_by(self, code: list[x86.Instruction]) -> set[tuple[bytes, int]]:
        """(text, address) of each string literal that the code uses: one text can sit at two addresses."""
        addresses = {int(value, 16) for instruction in code for value in re.findall(r"0x[0-9a-f]+", instruction.operands)}
        return {(text, address) for address in addresses if (text := self.at(address)) is not None}


class Tells(NamedTuple):
    address: int
    aligned: bool
    frame: bool  # push ebp; mov ebp, esp at the start
    eh: bool  # an exception frame: mov eax, fs:[0]
    cookie: bool  # loads ___security_cookie
    and_esp: bool  # aligns its stack, which keeps a frame under /Oy
    argument_without_frame: bool  # uses an argument through esp
    slot_reread: bool  # loads one frame slot into two registers with two movs in a row: /Od
    push_pop: bool  # push of a constant and pop into a register: /O1
    strings: set[tuple[bytes, int]]  # (text, address) of each string literal it uses: one text can sit at two
    floats: floattells.Floats

    @property
    def bare_frame(self) -> bool:
        return self.frame and not self.eh and not self.and_esp

    @property
    def eh_without_cookie(self) -> bool:
        return self.eh and not self.cookie

    @staticmethod
    def of(function: x86.Function, cookie: int | None, strings: StringFinder) -> "Tells":
        code = function.code
        frame = x86.has_frame(code)
        depths = stack_depths(function)
        return Tells(
            address=function.address, aligned=function.address % 16 == 0, frame=frame,
            eh=any(i.mnemonic == "mov" and i.operands == "eax, dword ptr fs:[0]" for i in code),
            cookie=cookie is not None and any(f"[0x{cookie:x}]" in i.operands for i in code),
            and_esp=any(i.mnemonic == "and" and i.operands.startswith("esp, 0xfffff") for i in code),
            argument_without_frame=not frame and uses_argument(code, depths), slot_reread=slot_reread(code),
            push_pop=push_pop(code), strings=strings.used_by(code), floats=floattells.float_tells(code, depths))


def stack_depths(function: x86.Function) -> dict[int, int]:
    """The bytes pushed since the entry, before each instruction, along the paths from the entry.
    A call counts as popping nothing. After a call to a function that pops its own arguments
    the count runs high, so a use of an argument there goes unseen."""
    by_address = {instruction.address: instruction for instruction in function.code}
    reserved = {second.address: int(first.operands[5:], 0) for first, second in pairs(function.code)
                if second.callee in CHKSTK and first.mnemonic == "mov" and IMMEDIATE.fullmatch(first.operands)}
    depths = {function.address: 0} if function.address in by_address else {}
    pending = list(depths)
    while pending:
        address = pending.pop()
        instruction = by_address[address]
        after = depths[address] + stack_change(instruction.mnemonic, instruction.operands) + reserved.get(address, 0)
        # dict.fromkeys: a branch to the next instruction lists it twice.
        reached = [following for following in dict.fromkeys(function.successors[address])
                   if following in by_address and following not in depths]
        depths.update(dict.fromkeys(reached, after))
        pending.extend(reached)
    return depths


def uses_argument(code: list[x86.Instruction], depths: dict[int, int]) -> bool:
    """Whether code without a frame reads or writes [esp+x] past what it pushed: an argument."""
    for instruction in code:
        found = ESP_READ.search(instruction.operands)
        if found and instruction.mnemonic != "lea" and int(found.group(1) or "0", 0) >= depths[instruction.address] + 4:
            return True
    return False


def stack_change(mnemonic: str, operands: str) -> int:
    if mnemonic == "push":
        return 4
    if mnemonic == "pop":
        return -4
    if mnemonic in ("sub", "add") and operands.startswith("esp, "):
        try:
            return int(operands[5:], 0) * (1 if mnemonic == "sub" else -1)
        except ValueError:
            return 0  # sub esp, eax
    return 0


def pairs(code: list[x86.Instruction]):
    """Each instruction and the one that directly follows it."""
    return ((first, second) for first, second in zip(code, code[1:]) if first.address + first.size == second.address)


def slot_reread(code: list[x86.Instruction]) -> bool:
    def load(instruction: x86.Instruction) -> str | None:
        parts = instruction.operands.split(", ")
        if instruction.mnemonic == "mov" and len(parts) == 2 and parts[0] != "ebp" and parts[1].startswith("dword ptr [ebp"):
            return parts[1]
        return None

    return any(load(first) is not None and load(first) == load(second) for first, second in pairs(code))


def push_pop(code: list[x86.Instruction]) -> bool:
    return any(first.mnemonic == "push" and (first.operands.startswith(("0x", "-")) or first.operands.isdigit())
               and second.mnemonic == "pop" for first, second in pairs(code))
