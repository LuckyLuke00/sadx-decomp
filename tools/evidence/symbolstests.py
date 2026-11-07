"""Unit tests for symbols.py: reading the neutral symbol files, the rows they give, the lvalue check and the
one-enumerator flag.

Run on its own: .venv/Scripts/python.exe -I tools/evidence/symbolstests.py
run() calls every check and returns the failures. All names are made up.
"""

import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

import covers  # noqa: E402
import profiles  # noqa: E402
import symbols  # noqa: E402
from symbols import Constant, SymbolsError  # noqa: E402

CPP, C = profiles.get("msvc-vc10-x86-cpp"), profiles.get("msvc-vc10-x86-c")
PROTOTYPES = ("address,name,slot,type\n"
              "0x00401000,xxSetMode,0,void\n"
              "0x00401000,xxSetMode,1,int\n"
              "0x00401000,xxSetMode,2,enum XX_MODE\n"
              "0x00402000,xxGetMode,0,enum XX_MODE\n"
              "0x00403000,xxPrint,0,int\n"
              "0x00403000,xxPrint,1,const char *\n"
              "0x00403000,xxPrint,2,...\n"
              "0x00404000,xxModes,0,enum XX_MODE *\n"
              "0x00404000,xxModes,1,enum XX_MODE &\n")
ENUMS = ("enum,name,value\n"
         "enum XX_MODE,XX_MODE_OFF,0\n"
         "enum XX_MODE,XX_MODE_ON,1\n"
         "enum XX_MODE,XX_MODE_AUTO,0x2\n")
SCOPES = ("address,scope,name,value\n"
          "0x00401000,enum STEP,STEP_INIT,0\n"
          "0x00401000,enum STEP,STEP_RUN,1\n"
          "0x00401000,enum STEP,STEP_EXIT,2\n"
          "0x00401000,enum KIND,KIND_A,1\n")


def load(files: dict):
    with tempfile.TemporaryDirectory() as folder:
        for name, text in files.items():
            (Path(folder) / name).write_text(text, encoding="utf-8", newline="")
        try:
            return symbols.load(Path(folder))
        except SymbolsError as error:
            return str(error)


def good() -> symbols.Symbols:
    return load({symbols.PROTOTYPES: PROTOTYPES, symbols.ENUMS: ENUMS, symbols.SCOPES: SCOPES})


def check_load() -> list[str]:
    failures = []
    if load({}) is not None:
        failures.append("no symbol files must give None")
    found = good()
    if isinstance(found, str):
        return failures + [f"good files failed: {found}"]
    if found.prototypes["0x00401000"] != ["void", "int", "enum XX_MODE"]:
        failures.append(f"prototype {found.prototypes['0x00401000']}")
    if found.enums["enum XX_MODE"] != [("XX_MODE_OFF", 0), ("XX_MODE_ON", 1), ("XX_MODE_AUTO", 2)]:
        failures.append(f"enum {found.enums['enum XX_MODE']}")
    if found.scopes["0x00401000"][3] != Constant("enum KIND", "KIND_A", 1):
        failures.append(f"scope {found.scopes['0x00401000']}")
    only = load({symbols.ENUMS: ENUMS})
    if isinstance(only, str) or only.prototypes or only.scopes or len(only.enums) != 1:
        failures.append(f"one file alone gives {only!r}")
    header = "address,name,slot,type\n"
    cases = (
        ({symbols.PROTOTYPES: "address,name,type\n"}, "the columns must be address,name,slot,type"),
        ({symbols.PROTOTYPES: header + "0x401000,f,0\n"}, ":2: the row needs 4 values"),
        ({symbols.PROTOTYPES: header + "0x401000,f,0,int,extra\n"}, ":2: the row needs 4 values"),
        ({symbols.PROTOTYPES: header + "zz,f,0,int\n"}, ":2: address 'zz' is not a hex number"),
        ({symbols.PROTOTYPES: header + "0x401000,f,one,int\n"}, ":2: slot 'one' is not a number from 0"),
        ({symbols.PROTOTYPES: header + "0x401000,f,0,\n"}, ":2: the name and the type must not be empty"),
        ({symbols.PROTOTYPES: header + "0x401000,f,0,int\n0x401000,f,0,int\n"}, ":3: 0x401000 slot 0 is also at"),
        ({symbols.PROTOTYPES: header + "0x401000,f,0,int\n0x401000,f,2,int\n"}, "0x401000 has no slot 1"),
        ({symbols.PROTOTYPES: header + "0x401000,f,0,int\n0x401000,f,1,...\n0x401000,f,2,int\n"},
         ":3: ... must be the last parameter"),
        ({symbols.PROTOTYPES: header + "0x401000,f,0,...\n"}, ":2: ... must be the last parameter"),
        ({symbols.ENUMS: "enum,name,value\nXX_MODE,XX_A,0\n"}, ":2: enum 'XX_MODE' must be spelled enum NAME"),
        ({symbols.ENUMS: "enum,name,value\nenum X,XX A,0\n"}, ":2: name 'XX A' is not an identifier"),
        ({symbols.ENUMS: "enum,name,value\nenum X,XX_A,zero\n"}, ":2: value 'zero' is not an integer"),
        ({symbols.ENUMS: "enum,name,value\nenum X,XX_A,0\nenum X,XX_A,1\n"}, ":3: enum X XX_A is also at"),
        ({symbols.SCOPES: "address,scope,name,value\n0x1,,A,0\n"}, ":2: the scope must not be empty"),
        ({symbols.SCOPES: "address,scope,name,value\n0x1,enum S,A,0\n0x1,enum S,A,1\n"},
         ":3: A of enum S is also at"),
    )
    for files, wanted in cases:
        got = load(files)
        if not isinstance(got, str) or wanted not in got:
            failures.append(f"symbol error {got!r}, want {wanted!r}")
    return failures


def check_rows() -> list[str]:
    failures = []
    found = good()
    rows = found.call_rows("0x00401000", "xxSetMode")
    if list(rows) != [2] or rows[2].groups != ("enum XX_MODE",) or rows[2].status != symbols.REFERENCE_PROTOTYPE:
        failures.append(f"call rows {rows}")
    if found.call_rows("0x00409000", "xxNone") != {}:
        failures.append("a function with no prototype must give no call rows")
    returned = found.return_row("0x00402000", "xxGetMode")
    if returned is None or (returned.callee, returned.slot, returned.groups) != ("xxGetMode", 0, ("enum XX_MODE",)):
        failures.append(f"return row {returned}")
    if found.return_row("0x00401000", "xxSetMode") is not None:
        failures.append("a void return must give no return row")
    if found.call_rows("0x00404000", "xxModes") != {} or found.return_row("0x00404000", "xxModes") is not None:
        failures.append("a pointer or reference to an enum must give no row")
    for spelled, wanted in (("enum XX_MODE", True), ("enum XX_MODE *", False), ("enum XX_MODE &", False),
                            ("enum XX_MODE [4]", False), ("enum XX_MODE (*)(int)", False), ("int", False)):
        if symbols.enum_slot(spelled) != wanted:
            failures.append(f"enum_slot({spelled!r}) is not {wanted}")
    if found.parameters("0x00403000") != (("const char *",), True):
        failures.append(f"variadic parameters {found.parameters('0x00403000')}")
    if found.parameters("0x00401000") != (("int", "enum XX_MODE"), False):
        failures.append(f"parameters {found.parameters('0x00401000')}")
    wide = found.scope_row("0x00401000")
    narrow = found.scope_row("0x00401000", ("enum STEP",))
    if wide.groups != ("enum KIND", "enum STEP") or narrow.groups != ("enum STEP",):
        failures.append(f"scope rows {wide.groups} {narrow.groups}")
    if found.scope_row("0x00402000") is not None:
        failures.append("a function with no scope constants must give no scope row")
    names = [(name.name, name.value, name.origins) for name in found.names(wide)]
    if names != [("STEP_INIT", 0, ("reference",)), ("STEP_RUN", 1, ("reference",)), ("STEP_EXIT", 2, ("reference",)),
                 ("KIND_A", 1, ("reference",))]:
        failures.append(f"scope names {names}")
    if [name.name for name in found.names(narrow)] != ["STEP_INIT", "STEP_RUN", "STEP_EXIT"]:
        failures.append(f"narrow scope names {found.names(narrow)}")
    if [name.name for name in found.names(rows[2])] != ["XX_MODE_OFF", "XX_MODE_ON", "XX_MODE_AUTO"]:
        failures.append(f"enum names {found.names(rows[2])}")
    if not found.check(rows[2]).passed or not found.check(wide).passed:
        failures.append("checked rows must pass")
    if load({symbols.PROTOTYPES: PROTOTYPES}).check(rows[2]) != symbols.argmap.Check(False, symbols.NO_ENUM):
        failures.append("an enum with no enums.csv rows must fail its check")
    return failures


def check_lvalues() -> list[str]:
    failures = []
    constants = good().scopes["0x00401000"]
    three = [("step", 0), ("step", 1), ("step", 2), ("step", 1)]
    if symbols.lvalue_check(three, constants, 3) != {"step": ("enum STEP",)}:
        failures.append(f"three values give {symbols.lvalue_check(three, constants, 3)}")
    two = [("step", 0), ("step", 1), ("step", 1)]
    if symbols.lvalue_check(two, constants, 3) != {}:
        failures.append("two distinct values must not pass at 3")
    if symbols.lvalue_check(two, constants, 2) != {"step": ("enum STEP",)}:
        failures.append(f"two values at 2 give {symbols.lvalue_check(two, constants, 2)}")
    stray = three + [("step", 7)]
    if symbols.lvalue_check(stray, constants, 3) != {}:
        failures.append("a value of no constant must fail the check")
    both = [("kind", 1)]
    if symbols.lvalue_check(both, constants, 1) != {"kind": ("enum KIND", "enum STEP")}:
        failures.append(f"a value of two scopes gives {symbols.lvalue_check(both, constants, 1)}")
    return failures


def search(*aliases: str) -> covers.Search:
    node = covers.Node(tuple(covers.Name(name, 1, False, ("reference",)) for name in aliases), 1)
    return covers.Search([covers.Candidate((node,), False)])


def check_one_enumerator() -> list[str]:
    failures = []
    row = good().call_rows("0x00401000", "xxSetMode")[2]
    scope = good().scope_row("0x00401000")
    if not symbols.one_enumerator(search("XX_MODE_ON"), row, CPP):
        failures.append("one enumerator under C++ must give the flag")
    if symbols.one_enumerator(search("XX_MODE_ON", "XX_MODE_YES"), row, CPP):
        failures.append("two enumerators of one value must not give the flag")
    if symbols.one_enumerator(search("XX_MODE_ON"), row, C):
        failures.append("a C profile must not give the flag")
    if symbols.one_enumerator(search("STEP_RUN"), scope, CPP):
        failures.append("a scope row must not give the flag")
    incomplete = search("XX_MODE_ON")
    incomplete.incomplete = True
    if symbols.one_enumerator(incomplete, row, CPP) or symbols.one_enumerator(covers.Search(), row, CPP):
        failures.append("an incomplete or empty search must not give the flag")
    return failures


def run() -> list[str]:
    failures = []
    for check in (check_load, check_rows, check_lvalues, check_one_enumerator):
        failures += check()
    return failures


if __name__ == "__main__":
    found = run()
    for failure in found:
        print(failure)
    if not found:
        print("symbolstests: all passed")
    sys.exit(1 if found else 0)
