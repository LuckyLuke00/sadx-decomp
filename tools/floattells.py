"""The float tells of one function: code that only some compiler flags make.

groups.py counts them for each code group. They cover SSE and x87 instructions, calls into
the runtime's math functions, and a model of the x87 stack (X87Model) that finds the stores
which /arch:SSE2 would not make.

Needs capstone through x86.py, so it runs in .venv.
"""

import collections
import re
from typing import NamedTuple

import x86

LOAD_CONSTANTS = ("fld1", "fldz", "fldpi", "fldl2e", "fldl2t", "fldlg2", "fldln2")
COMPARES = ("fcom", "fcomp", "fcompp", "fucom", "fucomp", "fucompp", "ftst",
            "fcomi", "fcompi", "fucomi", "fucompi", "fcomip", "fucomip")
UNARY = ("fchs", "fabs", "fsqrt", "frndint", "fsin", "fcos", "f2xm1", "fscale", "fprem", "fprem1", "fxtract", "fptan")
COMBINES = ("fpatan", "fyl2x", "fyl2xp1")


class Floats(NamedTuple):
    x87: bool  # uses x87 float code
    x87_tells: list[str]  # x87 code that no /arch:SSE2 test build made, by kind
    xmm: bool
    sse: bool  # code that only /arch:SSE or /arch:SSE2 makes
    sse2: bool  # code that only /arch:SSE2 makes
    fast: bool  # float code that only /fp:fast makes, or intrinsics


# SSE instructions, and whether they count only with an xmm operand (movq also moves MMX registers).
SSE = dict.fromkeys(("cvttss2si cvttsd2si comiss comisd ucomiss ucomisd fcomi fcomip fcompi fucomi fucomip fucompi "
                     "cvtps2pd cvtpd2ps cvtss2sd cvtsd2ss cvtdq2ps cvtdq2pd cvtsi2ss cvtsi2sd "
                     "addsd subsd mulsd divsd sqrtsd addss subss mulss divss sqrtss minss maxss minsd maxsd").split(), False)
SSE |= dict.fromkeys(("movss movsd movq movd movdqa movdqu movups movlpd movhpd movlps movhps punpckldq "
                      "xorps xorpd andps andpd andnps andnpd orps orpd pxor movaps movapd "
                      "cmpltsd cmpnlesd cmpltss cmpnless unpcklps shufps").split(), True)
SSE1 = set("comiss ucomiss cvttss2si cvtsi2ss movss xorps movaps fcompi fcomi fucompi".split())  # /arch:SSE makes these too
FAST = set("addss subss mulss divss fsqrt fsin fcos".split())

# Runtime functions, by their names in src/library.csv.
LIBM_REGISTER = {"__CIsin": 1, "__CIcos": 1, "__CItan": 1, "__CIatan": 1, "__CIasin": 1, "__CIacos": 1, "__CIlog": 1,
                 "__CIlog10": 1, "__CIexp": 1, "__CIsqrt": 1, "__CIatan2": 2, "__CIpow": 2, "__CIfmod": 2}  # x87 arguments
LIBM_STACK = {f"{prefix}{name}" for prefix in ("", "_") for name in
              "floor ceil fmod modf frexp ldexp pow exp log log10 sin cos tan atan atan2 asin acos sqrt fabs sinh cosh tanh hypot".split()}
FTOL = {"__ftol2_sse", "__ftol2_sse_excpt"}
FTOL64 = "__ftol2"
X87_CONTROL = {"fnstcw", "fldcw", "fwait", "fnclex", "fninit", "fnstsw", "fstcw", "fnstenv", "fldenv", "ffree"}

MEMORY = re.compile(r"(byte|word|dword|qword|tbyte|xmmword) ptr (?:[a-z]s:)?\[([^\]]*)\]")
BASE = re.compile(r"\b(eax|ebx|ecx|edx|esi|edi|ebp|esp)\b")
ST = re.compile(r"st\((\d)\)")
TERM = re.compile(r"([+-]?)\s*(0x[0-9a-f]+|\d+)(?!\w*\*)")
ARITHMETIC = re.compile(r"f(i?)(add|sub|subr|mul|div|divr)(p?)$")


def memory_operand(operands: str):
    """(size, registers, constant offset, text inside the brackets) of the first memory operand, or None.
    The offset is None for an indexed operand."""
    found = MEMORY.search(operands)
    if not found:
        return None
    size, inner = found.groups()
    offset = None if "*" in inner else sum((-1 if sign == "-" else 1) * int(value, 0) for sign, value in TERM.findall(inner))
    return size, BASE.findall(inner), offset, inner


def on_stack(key) -> bool:
    return key[0] in ("stack", "frame")


def is_x87(mnemonic: str) -> bool:
    return mnemonic.startswith("f") and mnemonic not in X87_CONTROL


def float_tells(code: list[x86.Instruction], depths: dict[int, int]) -> Floats:
    """The float tells of one function. code: its instructions in address order.
    depths: the bytes pushed since the entry, before each instruction, by address.

    The x87 side follows where each x87 stack value came from:
      memory  a load from memory, a constant, or a dword fild, with no call result in it
      call    a call result, or anything computed from one; also an unknown value, as after a label
      int64   a qword fild, which /arch:SSE2 also keeps on x87
    Storing a memory value is a tell, unless /arch:SSE2 makes the store too: the value is
    returned, it is later combined with a call result or passed to a libm call, or it is a plain
    copy between two places addressed through registers.
    """
    tells = []
    xmm = x87 = sse = sse2 = fast = False
    labels = set()
    for instruction in code:
        mnemonic, operands = instruction.mnemonic, instruction.operands
        xmm |= "xmm" in operands
        if mnemonic in SSE and (not SSE[mnemonic] or "xmm" in operands):
            sse = True
            sse2 |= mnemonic not in SSE1
        fast |= mnemonic in FAST
        if mnemonic == "fnstsw":
            tells.append("fnstsw")
        x87 |= is_x87(mnemonic)
        if mnemonic.startswith("j") and not instruction.callee and (target := x86.number(operands)) is not None:
            labels.add(target)
    if x87:
        tells += X87Model(code, depths, labels).tells()
    return Floats(x87, tells, xmm, sse, sse2, fast)


class X87Value(NamedTuple):
    """A value on the x87 stack and where it came from: see float_tells()."""
    kind: str
    computed: bool = False
    constant: bool = False
    source: str = "register"
    slots: frozenset = frozenset()
    size: str | None = None
    inlined: bool = False


class Operation(NamedTuple):
    """One x87 instruction with its operands read."""
    index: int
    mnemonic: str
    memory: tuple | None  # its memory operand: see memory_operand()
    key: tuple | None  # the place that operand names: see X87Model.key()
    registers: list[int]  # the n of each st(n) operand


class X87Model:
    """Runs the x87 stack of one function and lists the stores that /arch:SSE2 never makes."""

    def __init__(self, code: list[x86.Instruction], depths: dict[int, int], labels: set[int]):
        self.code, self.depths, self.labels = code, depths, labels
        self.index = {instruction.address: i for i, instruction in enumerate(code)}
        self.frame = x86.has_frame(code)
        self.returned = set()  # places whose reloaded value is the return value
        self.stack = []
        self.spilled = {}  # stack slot: the value stored there
        self.slot_stores = collections.defaultdict(list)  # stack slot: the values stored there
        self.merged = set()  # stack slots whose value was combined with a call result or passed to libm
        self.outgoing = []  # (stack slot, value) stored since the last call: arguments
        self.found = []

    def tells(self) -> list[str]:
        self.find_returned()
        for i in range(len(self.code)):
            self.step(i)
        grown = True
        while grown:
            grown = self.merge_feeders()
        for key, values in self.slot_stores.items():
            if not (key in self.returned or key in self.merged):
                self.found += ["x87_store_inline" if value.inlined else "x87_store_stack" for value in values]
        return self.found

    def merge_feeders(self) -> bool:
        """A stack slot that feeds a returned or merged slot is ambiguous too. Whether this pass merged more."""
        before = len(self.merged)
        for key, values in self.slot_stores.items():
            if key in self.returned or key in self.merged:
                self.merged.update(*(value.slots for value in values))
        return len(self.merged) > before

    def key(self, i: int):
        """Which memory the float operand of instruction i names, or None without one.
        Stack slots are counted from the entry esp, so pushes don't change them."""
        operand = memory_operand(self.code[i].operands)
        if operand is None:
            return None
        _, bases, offset, inner = operand
        if not bases:
            return "global", inner.strip()
        if bases == ["esp"] and offset is not None:
            return "stack", offset - self.depths[self.code[i].address]
        if self.frame and bases == ["ebp"] and offset is not None:
            return "frame", offset
        return "register", inner.strip()

    def reaches_ret(self, i: int) -> bool:
        """From instruction i on, does the x87 top reach a ret without being stored or passed on?"""
        for _ in range(80):
            if i >= len(self.code):
                return False
            mnemonic, operands, callee = self.code[i].mnemonic, self.code[i].operands, self.code[i].callee
            if mnemonic == "ret":
                return True
            if mnemonic == "jmp" and callee:
                return callee in LIBM_REGISTER
            if mnemonic == "call" and callee not in LIBM_REGISTER and callee not in LIBM_STACK:
                return False
            if mnemonic in ("fst", "fstp", "fist", "fistp") and memory_operand(operands):
                return self.key(i) in self.returned and mnemonic.startswith("fst")
            # A jump inside the function goes to its target, which may be unknown (the end of the code).
            i = self.index.get(x86.number(operands), len(self.code)) if mnemonic == "jmp" else i + 1
        return False

    def find_returned(self) -> None:
        loads = [i for i, instruction in enumerate(self.code)
                 if instruction.mnemonic == "fld" and memory_operand(instruction.operands)]
        while True:
            before = len(self.returned)
            for i in loads:
                self.mark_returned(i)
            if len(self.returned) == before:
                return

    def mark_returned(self, i: int) -> None:
        """If the fld at i loads a value that reaches a ret, the place it loads from holds the return value."""
        key = self.key(i)
        if key not in self.returned and self.reaches_ret(i + 1):
            self.returned.add(key)

    def top(self) -> X87Value:
        return self.stack[-1] if self.stack else X87Value("call", computed=True)

    def pop(self, count: int = 1) -> list[X87Value]:
        return [self.stack.pop() for _ in range(count) if self.stack]

    def combine(self, values: list[X87Value], extra_slots=()) -> X87Value:
        kinds = {value.kind for value in values}
        kind = "call" if "call" in kinds else "int64" if "int64" in kinds else "memory"
        slots = frozenset(extra_slots).union(*(value.slots for value in values))
        if kind == "call":
            self.merged |= slots
        return X87Value(kind, computed=True, slots=slots)

    def store(self, op: Operation, value: X87Value) -> None:
        key = op.key
        if value.kind != "memory":
            if on_stack(key):
                self.spilled[key] = value
            return
        if value.size and value.size != op.memory[0]:
            value = value._replace(computed=True)  # float to double: not a plain copy
        if on_stack(key):
            self.spilled[key] = value
            self.slot_stores[key].append(value)
            self.outgoing.append((key, value))
        elif key in self.returned or op.mnemonic == "fst" and self.reaches_ret(op.index + 1):
            pass  # a returned value
        elif not value.computed and not value.constant and value.source == "register" and key[0] == "register":
            pass  # a copy between two places addressed through registers
        else:
            self.found.append("x87_store_inline" if value.inlined else "x87_store")

    def call(self, callee: str) -> None:
        """A call or jump to a named function."""
        if callee in FTOL or callee == FTOL64:
            self.convert_to_integer(callee)
        elif callee in LIBM_REGISTER:
            self.call_with_register_arguments(callee)
        else:
            self.stack.clear()
            if callee in LIBM_STACK:
                self.call_with_stack_arguments(callee)
            self.outgoing.clear()

    def convert_to_integer(self, callee: str) -> None:
        if callee in FTOL and self.top().kind == "memory":
            self.found.append("ftol")
        self.pop()

    def call_with_register_arguments(self, callee: str) -> None:
        arguments = self.pop(LIBM_REGISTER[callee])
        if callee == "__CIsqrt" and arguments and arguments[0].kind == "memory":
            # /arch:SSE2 inlines sqrt as sqrtsd unless the result is returned or combined with a call result
            self.stack.append(X87Value("memory", computed=True, slots=arguments[0].slots, inlined=True))
            return
        for argument in arguments:
            self.merged |= argument.slots
        self.stack.append(X87Value("call", computed=True))

    def call_with_stack_arguments(self, callee: str) -> None:
        if (callee.lstrip("_") in ("floor", "ceil") and self.outgoing
                and all(value.kind == "memory" for _, value in self.outgoing)):
            # /arch:SSE2 inlines floor of a memory value, and moves ceil's argument through xmm0
            self.stack.append(X87Value("memory", computed=True, inlined=True,
                                       slots=frozenset(key for key, _ in self.outgoing)))
        else:
            self.merged.update(key for key, _ in self.outgoing)

    def step(self, i: int) -> None:
        address, mnemonic, callee = self.code[i].address, self.code[i].mnemonic, self.code[i].callee
        if address in self.labels:
            self.stack.clear()
        if mnemonic == "ret":
            if self.stack:
                self.merged |= self.stack[-1].slots  # what a returned value came from is x87 under /arch:SSE2 too
            self.stack.clear()
        elif mnemonic in ("call", "jmp"):
            if callee:
                self.call(callee)
            else:
                self.outgoing.clear()
            if mnemonic == "jmp" or not callee:
                self.stack.clear()
        elif is_x87(mnemonic):
            self.execute(i)

    def execute(self, i: int) -> None:
        """Run one x87 instruction on the stack."""
        mnemonic, operands = self.code[i].mnemonic, self.code[i].operands
        op = Operation(i, mnemonic, memory_operand(operands), self.key(i), [int(x) for x in ST.findall(operands)])
        if mnemonic == "fld":
            self.load(op)
        elif mnemonic in LOAD_CONSTANTS:
            self.stack.append(X87Value("memory", constant=True))
        elif mnemonic == "fild":
            qword = op.memory and op.memory[0] == "qword"
            self.stack.append(X87Value("int64") if qword else X87Value("memory", computed=True, source="int"))
        elif mnemonic in ("fst", "fstp"):
            self.store_top(op)
        elif mnemonic in ("fist", "fistp"):
            self.store_integer(op)
        else:
            self.compute(op)

    def load(self, op: Operation) -> None:
        if op.memory and op.key in self.spilled:
            spilled = self.spilled[op.key]
            self.stack.append(spilled._replace(slots=spilled.slots | {op.key}))
        elif op.memory:
            source = "global" if op.key[0] == "global" else "stack" if on_stack(op.key) else "register"
            slots = frozenset([op.key]) if on_stack(op.key) else frozenset()
            self.stack.append(X87Value("memory", source=source, slots=slots, size=op.memory[0]))
        elif op.registers:
            n = op.registers[0]
            self.stack.append(self.stack[-1 - n] if len(self.stack) > n else X87Value("call", computed=True))

    def store_top(self, op: Operation) -> None:
        if op.memory:
            self.store(op, self.top())
        elif op.registers and op.registers[0] > 0 and len(self.stack) > op.registers[0]:
            self.stack[-1 - op.registers[0]] = self.top()
        if op.mnemonic == "fstp":
            self.pop()

    def store_integer(self, op: Operation) -> None:
        if not (op.memory and op.memory[0] == "qword") and self.top().kind == "memory":
            self.found.append("fistp32")
        if op.mnemonic == "fistp":
            self.pop()

    def compute(self, op: Operation) -> None:
        mnemonic, stack = op.mnemonic, self.stack
        if mnemonic in COMPARES:
            self.pop(2 if mnemonic.endswith("pp") else 1 if mnemonic.endswith(("p", "pi", "ip")) else 0)
        elif mnemonic == "fxch":
            n = op.registers[0] if op.registers else 1
            if len(stack) > n:
                stack[-1], stack[-1 - n] = stack[-1 - n], stack[-1]
        elif mnemonic in UNARY:
            stack[-1:] = [self.top()._replace(computed=True)]
            if mnemonic == "fptan":
                stack.append(X87Value("memory", constant=True))
        elif mnemonic in COMBINES:
            if len(stack) >= 2:
                stack.append(self.combine(self.pop(2)))
        elif ARITHMETIC.match(mnemonic):
            if op.memory:
                self.arithmetic_with_memory(op)
            else:
                self.arithmetic_between_registers(op)

    def arithmetic_with_memory(self, op: Operation) -> None:
        other = self.spilled.get(op.key)
        result = self.combine([self.top()] + ([other] if other is not None else []), (op.key,) if on_stack(op.key) else ())
        if result.kind == "call" and on_stack(op.key):
            self.merged.add(op.key)
        self.stack[-1:] = [result]

    def arithmetic_between_registers(self, op: Operation) -> None:
        stack = self.stack
        positions = [0] + [n for n in op.registers if n != 0]
        result = self.combine([stack[-1 - n] if len(stack) > n else X87Value("call", computed=True) for n in positions])
        for n in positions:
            if len(stack) > n:
                stack[-1 - n] = result
        if op.mnemonic.endswith("p"):
            self.pop()
