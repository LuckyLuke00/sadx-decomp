"""Decode one function of the exe into the instructions that a path from its entry reaches.

groups.py reads every game function with it, and floattells.py uses its number(). It
follows the paths from the entry, so it never decodes jump tables or padding.

Needs capstone, so it runs in .venv.
"""

import re
import struct
from typing import NamedTuple

import capstone

import pe

# The registers that can carry an argument, as bits. esp and ebp never do.
EAX, ECX, EDX, EBX, ESI, EDI = 1, 2, 4, 8, 16, 32
ALL_REGISTERS = EAX | ECX | EDX | EBX | ESI | EDI
CALL_CHANGES = EAX | ECX | EDX  # a call may change these
REGISTER = {name: bit for bit, names in ((EAX, "eax ax al ah"), (ECX, "ecx cx cl ch"), (EDX, "edx dx dl dh"),
                                         (EBX, "ebx bx bl bh"), (ESI, "esi si"), (EDI, "edi di"))
            for name in names.split()}

STOPS = ("ret", "int3", "ud2", "hlt")
SWITCH = re.compile(r"\[(?:\w+ \+ )?\w+\*4 \+ (0x[0-9a-f]+)\]")  # jmp dword ptr [eax*4 + table]
SLOT = re.compile(r"dword ptr \[(0x[0-9a-f]+)\]")


class Instruction(NamedTuple):
    address: int
    size: int
    mnemonic: str
    operands: str
    reads: int  # register bits
    writes: int
    target: int | None  # where a direct call or jump goes
    callee: str | None  # the name of what a call or a jump out of the function goes to


class Function(NamedTuple):
    address: int
    size: int
    row: int  # its index in data/codegen-groups.csv
    code: list[Instruction]  # what a path from the entry reaches, in address order
    successors: dict[int, list[int]]  # the instructions that can run next, inside the function


def changes(instruction: Instruction) -> int:
    """The registers an instruction may change. A call may change eax, ecx and edx."""
    return instruction.writes | (CALL_CHANGES if instruction.mnemonic == "call" else 0)


class Decoder:
    """Decodes the functions of one image."""

    def __init__(self, image: pe.Image, names: dict[int, str]):
        self.image = image
        self.names = names  # the library function at each address, from src/library.csv
        self.disassembler = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        self.disassembler.detail = True

    def function(self, start: int, size: int, row: int) -> Function:
        span = range(start, start + size)
        code = self.image.read(start, size)
        decoded = {}  # address: capstone instruction, decoded straight on from the entry and each branch target
        instructions, successors = {}, {}
        pending = [start]
        while pending:
            address = pending.pop()
            if address in instructions or address not in span:
                continue
            if address not in decoded:
                self.decode_from(decoded, code[address - start:], address)
            if address not in decoded:
                continue  # bytes that don't decode
            instruction = self.simplify(decoded[address], span)
            instructions[address] = instruction
            successors[address] = [following for following in self.flow(instruction, span) if following in span]
            pending.extend(successors[address])
        return Function(start, size, row, [instructions[address] for address in sorted(instructions)], successors)

    def decode_from(self, decoded: dict, code: bytes, address: int) -> None:
        """Add the instructions of code, which starts at address, up to one that is already decoded."""
        for instruction in self.disassembler.disasm(code, address):
            if instruction.address in decoded:
                return
            decoded[instruction.address] = instruction

    def simplify(self, instruction, span: range) -> Instruction:
        """Keep what the analysis needs, with the registers read and written."""
        mnemonic, operands = instruction.mnemonic, instruction.op_str
        target = number(operands) if mnemonic == "call" or mnemonic.startswith(("j", "loop")) else None
        callee = None
        if target is not None and target not in span:
            callee = self.names.get(target) or f"fn_{target:x}"
        elif mnemonic in ("call", "jmp") and (slot := SLOT.fullmatch(operands)):
            callee = f"imp_{self.image.import_slots.get(int(slot.group(1), 16), '?')}"
        reads, writes = registers(instruction)
        return Instruction(instruction.address, instruction.size, mnemonic, operands, reads, writes, target, callee)

    def flow(self, instruction: Instruction, span: range) -> list[int]:
        """The addresses that can run after an instruction."""
        mnemonic, after = instruction.mnemonic, instruction.address + instruction.size
        if mnemonic in STOPS:
            return []
        if mnemonic == "jmp":
            if table := SWITCH.search(instruction.operands):
                return self.switch_targets(int(table.group(1), 16), span)
            return [instruction.target] if instruction.target is not None else []
        if mnemonic.startswith(("j", "loop")):
            return [instruction.target, after]
        return [after]

    def switch_targets(self, table: int, span: range) -> list[int]:
        """A switch's jump table: dwords that point into the function."""
        targets = []
        while len(entry := self.image.read(table + 4 * len(targets), 4)) == 4:
            target = struct.unpack("<I", entry)[0]
            if target not in span:
                break
            targets.append(target)
        return targets


def registers(instruction) -> tuple[int, int]:
    """The register bits an instruction reads and writes. An idiom that sets a register
    without using its old value reads nothing, such as xor eax, eax or or eax, -1. A push
    reads nothing: it saves a register or reserves stack space."""
    mnemonic, operands = instruction.mnemonic, instruction.op_str
    if mnemonic.startswith("nop") or mnemonic == "pushal" or mnemonic == "push" and operands in REGISTER:
        return 0, 0
    read_ids, write_ids = instruction.regs_access()
    reads = sum({REGISTER.get(instruction.reg_name(register), 0) for register in read_ids})
    writes = sum({REGISTER.get(instruction.reg_name(register), 0) for register in write_ids})
    parts = operands.split(", ")
    if len(parts) == 2 and parts[0] in REGISTER:
        destination, source = parts
        if does_nothing(mnemonic, destination, source):
            return 0, 0
        if ignores_old_value(mnemonic, destination, source):
            return 0, writes
    return reads, writes


def does_nothing(mnemonic: str, destination: str, source: str) -> bool:
    """Whether a two-operand instruction leaves its destination register as it was."""
    return destination == source and mnemonic in ("mov", "xchg") or mnemonic == "lea" and source == f"[{destination}]"


def ignores_old_value(mnemonic: str, destination: str, source: str) -> bool:
    """Whether a two-operand instruction sets its destination register to a value that
    does not depend on the old one: xor eax, eax, or an and or or with an immediate."""
    if destination == source and mnemonic in ("xor", "sub", "sbb"):
        return True
    if (value := number(source)) is None:
        return False
    ones = (1 << register_width(destination)) - 1
    value &= ones
    return mnemonic == "or" and value == ones or mnemonic == "and" and value == 0


def has_frame(code: list[Instruction]) -> bool:
    """Whether code starts with push ebp; mov ebp, esp, after a mov edi, edi for hot patching."""
    start = [(i.mnemonic, i.operands) for i in code[:3] if (i.mnemonic, i.operands) != ("mov", "edi, edi")]
    return start[:2] == [("push", "ebp"), ("mov", "ebp, esp")]


def register_width(name: str) -> int:
    return 32 if len(name) == 3 else 8 if name[1] in "lh" else 16


def number(text: str) -> int | None:
    """An immediate or address as capstone prints it: hex, or decimal below 10."""
    return int(text, 0) if text.startswith("0x") or text.isdigit() else None
