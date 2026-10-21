"""Write the shared declarations from the names the source files use: `check.py decls`.

Scans the hand-written files under src for the function, global and struct names
they use, then writes:

  src/include/types.h       struct and enum definitions they need
  src/include/functions.h   a declaration for each function they call or define
  src/include/globals.h     an extern for each global they use
  src/unplaced/stubs.cpp    a STUB for each called function that has no source yet
  src/unplaced/globals.cpp  a GLOBAL definition for each used global that no file defines

A signature comes from the function's definition, else from the --context tree,
else from a declaration in a source file, else from the --tables folder, else from
the files this command wrote before. So a name stays known while a file uses it. The
context tree is another checkout: its files give signatures and globals, but their
uses do not count. A name several functions share means the one from the using
file's own file, else the global overloads. Runtime library names are left to the
library's headers.

A tables folder holds tab-separated files with a header row, for names the tree
does not know yet. Other columns are ignored.
  functions.tsv  address, name, proto, scope (G global, L static), file (the source file it belongs in),
                 note (a line `check.py dossier` prints), locals (local declarations,
                 `; `-separated, which `check.py dossier` prints; optional), object (the object file
                 the function is in; optional)
  globals.tsv    address, name, decl ({} where the name goes), base, dims (comma-separated, ? when unknown), size,
                 object (the object file the global is in; optional)
  types.h        struct, union and enum definitions, a blank line between blocks, with sizeof static_asserts

A global name that several addresses share, such as one static in each object, means the address in an object that
the using file defines functions of.

Prints a line for each problem it finds. Returns 1 when a used name has no
declaration it can make, when functions.h would declare a function whose name
another function in the tree also has, unless both are global overloads,
when globals.h would declare one name for two globals, or when a global lies
inside another global's span (the span comes from the types the tree knows)
and the last layout, the context's with --context, did not have that pair
already. A pair it had before is a problem line only. With --context, the
functions that the context's files define count as declared in functions.h when
their name occurs a second time in the tree and the context together, as they
will in the context once these files are in it.
Standard library only.
"""

import collections
import csv
import re
from pathlib import Path

import names
import progress
import project

ROOT = project.ROOT
HEADER = "// Generated from the names the source files use. Do not edit: change the sources instead.\n"
EMPTY_ROW = {"name": "", "proto": "", "scope": "", "file": ""}
POINTER_TO = re.compile(r"\b(?:struct|union)\s+(\w+)\s*\*+\s*(\w+)")  # the pointed-to type and the pointer's name
CALL_ARGUMENTS = r"\((?:[^()]|\([^()]*\))*\)"  # with one level of nested parentheses, as in `f(g(x))`
# `p->x`, `p[i].x`: p's type needs its layout. `f(a)->x`: f's return type does. Only the name is consumed, so a
# name in the arguments counts too.
MEMBER_STEP = r"(?:->|\[[^\]]*\]\s*(?:\.|->))"  # `->`, or an index and then `.` or `->`
REACHED_THROUGH = re.compile(rf"(\w+)(?=\s*(?:{CALL_ARGUMENTS}\s*)?{MEMBER_STEP})")
RETURNS_POINTER_TO = re.compile(r"(?:const\s+)?(?:struct|union)\s+(\w+)\s*\*")  # a signature's pointed-to return type


def load_tables(library: set[str], tables: Path | None) -> tuple[dict, dict, dict, dict, dict]:
    """Functions and globals by address and by name, and the addresses of each global name that several share. Every
    function starts with its address name, and the tables' rows replace those they give."""
    funcs = {}
    fnames = collections.defaultdict(list)  # name: addresses, several for overloads and same-named statics
    with open(progress.FUNCTIONS_CSV, encoding="utf-8", newline="") as f:
        for r in csv.DictReader(f):
            a = int(r["address"], 16)
            funcs[a] = dict(EMPTY_ROW, name=f"FUN_{a:08x}")
    if tables is None:
        return funcs, dict(fnames), {}, {}, {}
    for r in names.table_rows(tables / "functions.tsv"):
        a = int(r["address"], 16)
        funcs[a] = r
        if not r["name"].startswith(("FUN_", "?")) and "::" not in r["name"] and r["name"] not in library:
            fnames[r["name"]].append(a)
    fnames = dict(fnames)
    glob = {}
    gnames = collections.defaultdict(list)
    for r in names.table_rows(tables / "globals.tsv"):
        a = int(r["address"], 16)
        glob[a] = r
        gnames[r["name"]].append(a)
    usable = {n: a for n, a in gnames.items() if len(n) > 2 and n not in fnames}
    gname = {n: a[0] for n, a in usable.items() if len(a) == 1}
    shared = {n: a for n, a in usable.items() if len(a) > 1}
    return funcs, fnames, glob, gname, shared


class Types(names.Types):
    def closure(self, wanted):
        out, todo = set(), [n for n in wanted if n in self.blocks]
        while todo:
            n = todo.pop()
            if n in out:
                continue
            out.add(n)
            todo.extend(d for d in self.deps[n] if d in self.blocks and d not in out)
        return out

    def pointees(self, defined, reached):
        """The types with a layout that pointer members of the DEFINED types point to, for members named in REACHED."""
        return {u for n in defined for u, member in POINTER_TO.findall(self.blocks[n])
                if member in reached and u in self.blocks}

    def write(self, defined, forward):
        lines = [HEADER, "#pragma once", "#pragma warning(disable: 4480)", "#include <stddef.h>", ""]
        fwd = sorted((n for n in forward | defined if self.kind.get(n, "struct") != "enum"), key=str.lower)
        for n in fwd:
            lines.append(f"{self.kind.get(n, 'struct')} {n};")
        lines.append("")
        for n in self.order:
            if n in defined:
                lines.append(self.blocks[n])
                lines.append("")
        return "\n".join(lines)


def stub_body(sig: str) -> str:
    ret = sig.split("(")[0]
    name = names.declared_name(sig) or ""
    ret = ret[: ret.rfind(name)].strip() if name else ret
    ret = re.sub(r"\b(extern|static|inline|__inline|__cdecl|__stdcall|__fastcall|__thiscall)\b", "", ret)
    ret = " ".join(ret.split())
    if ret == "void" or ret.endswith("void") and "*" not in ret:
        return "{\n}"
    if re.match(r"(const\s+)?(struct|union)\b", ret) and "*" not in ret:
        return f"{{\n\t{ret} r = {{}};\n\treturn r;\n}}"
    return f"{{\n\treturn ({ret})0;\n}}"


def extern_of(definition: str) -> str:
    """The extern a definition needs in globals.h: an array's size is left to the definition."""
    return "extern " + re.sub(r"\[\s*\w+\s*\]", "[]", definition, count=1) if "[" in definition else "extern " + definition


def write(context: Path | None, tables: Path | None) -> int:
    target = project.game_config().target
    library = {row.name for row in project.library_rows() if row.kind == "library"}
    funcs, fnames, glob, gnames, shared_globals = load_tables(library, tables)
    types = Types(tables / "types.h" if tables else ROOT / names.TYPES_H)
    before = names.previous(ROOT)
    sources = names.read_sources(ROOT)
    context_sources = names.context_sources(context, sources)
    problems = []
    fatal = []  # problems the build cannot get past

    defined_funcs = {}  # address: (file, signature, static, stub)
    defined_globals = {}  # address: (file, definition)
    tokens = set()
    counts = collections.Counter()
    local_funcs = collections.defaultdict(set)
    local_vars = collections.defaultdict(set)
    own_decls = set()  # (name, declaration) pairs from this tree's files, not the context's
    file_tokens = {}
    for rel, text in sources.items():
        for kind, address, sig in names.parse_annotations(text):
            if kind in names.FUNCTION_KINDS:
                if address in defined_funcs:
                    problems.append(f"{rel}: 0x{address:08x} is also annotated in {defined_funcs[address][0]}")
                defined_funcs[address] = (rel, sig, bool(re.match(r"static\b", sig)), kind == "STUB")
            elif kind == "GLOBAL":
                if address in defined_globals:
                    problems.append(f"{rel}: GLOBAL 0x{address:08x} is also defined in {defined_globals[address][0]}")
                defined_globals[address] = (rel, sig)
        found = re.findall(r"[A-Za-z_]\w*", names.strip_code(text))
        file_tokens[rel] = set(found)
        tokens |= set(found)
        counts.update(found)
        lf, lv = names.local_declarations(text)
        for name, decl in lf:
            local_funcs[name].add(decl)
            own_decls.add((name, decl))
        for name, decl in lv:
            local_vars[name].add(decl)
            own_decls.add((name, decl))
    # The context's definitions and declarations: signatures and types only.
    context_funcs, context_globals = {}, {}
    context_decls = {}  # (name, declaration): the context file that declares it
    context_counts = collections.Counter()
    for rel, text in context_sources.items():
        context_counts.update(re.findall(r"[A-Za-z_]\w*", names.strip_code(text)))
        for kind, address, sig in names.parse_annotations(text):
            if kind in names.FUNCTION_KINDS:
                context_funcs[address] = (rel, sig, bool(re.match(r"static\b", sig)), kind == "STUB")
            elif kind == "GLOBAL":
                context_globals[address] = (rel, sig)
        lf, lv = names.local_declarations(text)
        for name, decl in lf + lv:
            context_decls.setdefault((name, decl), rel)
        for name, decl in lf:
            local_funcs[name].add(decl)
        for name, decl in lv:
            local_vars[name].add(decl)

    def report_conflict(name, options):
        """A name declared in several ways, where one of them is this tree's own. A way that only a context
        file uses is fatal: the context's file never builds here, so a score here would not hold there."""
        ways = {}  # declaration_key: the declarations that read the same
        for o in options:
            ways.setdefault(names.declaration_key(o), []).append(o)
        if len(ways) < 2 or not any((name, o) in own_decls for o in options):
            return
        theirs = [f"{context_decls[(name, same[0])]} declares it `{same[0]}`" for same in ways.values()
                  if not any((name, o) in own_decls for o in same)]
        if theirs:
            fatal.append(f"{name}: {', '.join(theirs)} in the context tree. Declare it that way too.")
        else:
            shown = " | ".join(same[0] for same in ways.values())
            problems.append(f"{name}: sources declare it in {len(ways)} ways: {shown}")

    # A definition or an earlier stub names a function the table only knows by address, such as WinMain.
    stubs_before = {a: ("", sig, False, True) for a, sig in before.stubs.items()}
    for a, d in list(context_funcs.items()) + list(defined_funcs.items()) + list(stubs_before.items()):
        dname = names.declared_name(d[1])
        if a in funcs and funcs[a]["name"].startswith("FUN_") and dname and not dname.startswith("FUN_"):
            funcs[a] = dict(funcs[a], name=dname)
            fnames.setdefault(dname, []).append(a)
        if tables is None and a in funcs and not funcs[a]["scope"]:
            funcs[a] = dict(funcs[a], scope="L" if d[2] else "G", file=d[0])
    if tables is None:
        gnames = global_names(defined_globals, context_globals, before, fnames)
    # A file's home: its own path and the original files of the functions it defines.
    home = collections.defaultdict(set)
    for a, d in defined_funcs.items():
        if a in funcs:
            home[d[0]].add(funcs[a]["file"])

    def meaning(name, rel):
        """The functions a name in rel means: the ones rel defines, else the one from its own file, else the global
        overloads. A folded copy of another file's function makes that file a home of rel, but rel's own definitions
        still win, as in C."""
        options = fnames[name]
        if len(options) == 1:
            return options
        here = [a for a in options if a in defined_funcs and defined_funcs[a][0] == rel]
        if here:
            return here
        own = [a for a in options if funcs[a]["file"] == rel or funcs[a]["file"] in home[rel]]
        return own or [a for a in options if funcs[a]["scope"] == "G"]

    # Functions: every canonical or address name that a source uses, besides its own definition.
    used_funcs = set()
    users = collections.defaultdict(set)  # address: the files that use it by name
    for rel, found in file_tokens.items():
        for tok in found & fnames.keys():
            for a in meaning(tok, rel):
                users[a].add(rel)
                if a not in defined_funcs or counts[tok] > 1:
                    used_funcs.add(a)
    for tok in tokens:
        if re.fullmatch(r"FUN_[0-9a-f]{8}", tok):
            a = int(tok[4:], 16)
            if a in funcs and (a not in defined_funcs or counts[tok] > 1):
                used_funcs.add(a)
                if funcs[a]["name"] != tok:
                    problems.append(f"{tok} has the name {funcs[a]['name']}: use that")
    decls, stubs = {}, {}
    for a in sorted(used_funcs):
        row = funcs[a]
        name = row["name"]
        d = defined_funcs.get(a)
        if d and (d[2] or "::" in (names.declared_name(d[1]) or "")):
            others = sorted(users[a] - {d[0]})
            if d[2] and others:
                problems.append(f"{name} is static in {d[0]} but {', '.join(others)} use it: drop the static")
            continue  # static or a method: its file declares it
        c = context_funcs.get(a)
        chosen_locally = False
        if d:
            sig = d[1]
        elif c and not c[2] and "::" not in (names.declared_name(c[1]) or ""):
            sig = c[1]
        elif local_funcs.get(name):
            options = sorted(local_funcs[name])
            report_conflict(name, options)
            sig = options[0]
            chosen_locally = True
        elif row["proto"]:
            sig = row["proto"].rstrip(";")
        elif a in before.stubs:
            sig = before.stubs[a]
        else:
            fatal.append(f"{name} (0x{a:08x}): no known prototype. Declare it at the top of the file that calls it.")
            continue
        if names.declared_name(sig) != name:
            fatal.append(f"0x{a:08x}: its signature `{sig}` does not declare {name}")
            continue
        if not chosen_locally:  # report_conflict covered the local choice
            for own in sorted(o for o in local_funcs.get(name, ()) if (name, o) in own_decls):
                if names.declaration_key(own) != names.declaration_key(sig):
                    problems.append(f"{name}: the tree declares it `{sig}`, a file here declares it `{own}`. "
                                    "Remove that declaration: a second signature is a C++ overload that never links.")
        decls[a] = sig
        if d is None:
            stubs[a] = sig
    # functions.h declares each function for every file, so only global overloads may share a name. In the context,
    # the same holds for the functions its files define, once a name occurs a second time there with these files.
    declared = {funcs[a]["name"] for a in decls}
    for a, d in context_funcs.items():
        name = funcs[a]["name"] if a in funcs else ""
        if not d[2] and "::" not in (names.declared_name(d[1]) or "") and counts[name] + context_counts[name] > 1:
            declared.add(name)
    for name in sorted(declared & fnames.keys()):
        group = [a for a in fnames[name] if a in decls or a in defined_funcs or a in context_funcs]
        if len(group) > 1 and any(funcs[a]["scope"] != "G" for a in group):
            where = ", ".join(f"0x{a:08x} ({funcs[a]['file']})" for a in group)
            fatal.append(f"{name}: {where} share the name. Make each one static in its own file, "
                         f"with a STUB annotation until it is ported.")

    # Globals: every canonical or address name that a source uses.
    global_name = {a: n for n, a in gnames.items()}
    used_globals = set()
    for tok in tokens:
        if tok in gnames:
            used_globals.add(gnames[tok])
        elif re.fullmatch(r"DAT_[0-9a-f]{8}", tok):
            a = int(tok[4:], 16)
            if a in glob:
                problems.append(f"{tok} has the name {glob[a]['name']}: use that")
            used_globals.add(a)
    # A name that several addresses share is one static in each object: a file means the one in an object it defines
    # functions of.
    objects = collections.defaultdict(set)
    for a, d in defined_funcs.items():
        if a in funcs and funcs[a].get("object"):
            objects[d[0]].add(funcs[a]["object"])
    for rel, found in file_tokens.items():
        for tok in found & shared_globals.keys():
            here = [a for a in shared_globals[tok] if glob[a].get("object") in objects[rel]]
            if len(here) == 1:
                used_globals.add(here[0])
    externs, gdefs = {}, {}
    unsized = set()  # globals that stubs give one element, though their size is unknown
    for a in sorted(used_globals | set(defined_globals)):
        row = glob.get(a)
        name = row["name"] if row else global_name.get(a, f"DAT_{a:08x}")
        d = defined_globals.get(a)
        if d:
            if re.match(r"static\b", d[1]):
                continue
            externs[a] = extern_of(d[1].split("=")[0].strip())
            continue
        c = context_globals.get(a)
        if c and not re.match(r"static\b", c[1]):
            decl = c[1].split("=")[0].strip()
            externs[a] = extern_of(decl)
            gdefs[a] = (decl, "const" in decl.split(name)[0])
            continue
        if local_vars.get(name):
            options = sorted(local_vars[name])
            report_conflict(name, options)
            decl = options[0]
            externs[a] = "extern " + decl
            m = re.search(r"\[\s*\]", decl)
            definition = decl
            if m:
                definition = decl[:m.start()] + "[1]" + decl[m.end():]
                unsized.add(a)
                problems.append(f"{name}: no file defines it, so stubs give it one element; define it with its real size")
            gdefs[a] = (definition, "const" in decl.split(name)[0])
            continue
        if row is None:
            if a in before.globals and name in before.externs:
                externs[a] = before.externs[name]
                gdefs[a] = (before.globals[a], "const" in before.globals[a].split(name)[0])
            else:
                fatal.append(f"{name}: no known type. Declare it `extern <type> {name};` at the top of the file that uses it.")
            continue
        dims = row["dims"].split(",") if row["dims"] else []
        ext = row["decl"].replace("{}", name)
        if dims and dims[0] in ("?", "0", ""):
            ext = re.sub(r"\[[\w?]*\]", "[]", ext, count=1)
        externs[a] = "extern " + ext
        definition = row["decl"].replace("{}", name)
        if dims and dims[0] in ("?", "0", ""):
            elem = names.element_size(row["base"], types)
            inner = 1
            for x in dims[1:]:
                inner *= int(x) if x.isdigit() else 1
            count = int(row["size"]) // (elem * inner) if elem and row["size"] else 1
            definition = re.sub(r"\[[\w?]*\]", f"[{max(count, 1)}]", definition, count=1)
        gdefs[a] = (definition, row["base"].startswith("const"))
    # globals.h declares each global for every file, so a name serves one address.
    addresses_of = collections.defaultdict(list)
    for a, ext in externs.items():
        addresses_of[names.declared_name(ext)].append(a)
    for name, addresses in sorted(addresses_of.items()):
        if len(addresses) > 1:
            where = ", ".join(f"0x{a:08x}" for a in addresses)
            fatal.append(f"{name}: {where} share the name. Define each one static in its own file, "
                         f"with a GLOBAL annotation.")

    # A global inside another global splits it. The globals that only the context's files use count too: they are in
    # the layout of the whole tree. A clash that the last layout (the context's, else this tree's) already had is old.
    layout = {a: externs[a][len("extern "):] if a in unsized else
              gdefs[a][0] if a in gdefs else defined_globals[a][1].split("=")[0].strip() for a in externs}
    last_layout = names.previous(context).globals if context_sources else before.globals
    for tok in context_counts:
        a = gnames.get(tok) or (int(tok[4:], 16) if re.fullmatch(r"DAT_[0-9a-f]{8}", tok) else None)
        if a is None or a in layout:
            continue
        name = glob[a]["name"] if a in glob else global_name.get(a, tok)
        if context_globals.get(a) and not re.match(r"static\b", context_globals[a][1]):
            layout[a] = context_globals[a][1].split("=")[0].strip()
        elif local_vars.get(name):
            layout[a] = sorted(local_vars[name])[0]
        elif a in last_layout:
            layout[a] = last_layout[a]
    new, old, unknown = nested_globals(layout, set(externs), last_layout, types)
    fatal.extend(new)
    problems.extend(old)
    if unknown:
        problems.append(f"{len(unknown)} globals have no known size, so none is checked for a global inside it: "
                        + ", ".join(unknown[:5]) + (", ..." if len(unknown) > 5 else ""))

    # Types: full definitions for struct names the hand-written code uses; forward
    # declarations for those only signatures name.
    used_types = {t for t in tokens if t in types.blocks}
    for a, (definition, _) in gdefs.items():
        m = re.match(r"(?:const\s+)?(?:struct|union)\s+(\w+)\s+[^*]*$", definition.split("=")[0])
        if m:
            used_types.add(m.group(1))
            if m.group(1) not in types.blocks:
                gname = names.declared_name(definition)
                size = glob[a]["size"] if a in glob and glob[a]["size"] else "N"
                fatal.append(f"{gname}: no file gives the layout of {m.group(1)}, so it cannot be defined. Declare it "
                             f"`extern char {gname}[{size}];` at the top of the file that uses it and reach its fields "
                             "through casts.")
    # A pointer the code reaches through, such as `tp->awp->work`, needs its type's layout even when the code never
    # names that type: for globals and for members of the types defined so far, until no more turn up.
    reached = set()
    for text in sources.values():
        reached |= set(REACHED_THROUGH.findall(names.strip_code(text)))
    used_types |= {u for ext in externs.values() for u, n in POINTER_TO.findall(ext) if n in reached and u in types.blocks}
    for sig in decls.values():
        returned = RETURNS_POINTER_TO.match(sig)
        if returned and names.declared_name(sig) in reached and returned.group(1) in types.blocks:
            used_types.add(returned.group(1))
    defined_types = types.closure(used_types)
    more = types.pointees(defined_types, reached) - defined_types
    while more:
        defined_types |= types.closure(more)
        more = types.pointees(defined_types, reached) - defined_types
    forward = set()
    for sig in list(decls.values()) + list(externs.values()):
        forward |= set(n for n in re.findall(r"\b(?:struct|union)\s+(\w+)", sig))
        used_enums = set(n for n in re.findall(r"\benum\s+(\w+)", sig))
        defined_types |= types.closure(used_enums)
    for n in list(defined_types):
        forward |= set(re.findall(r"\b(?:struct|union)\s+(\w+)\s*\*", types.blocks[n]))

    # Write.
    out = {}
    out[names.TYPES_H] = types.write(defined_types, forward)
    flines = [HEADER, "#pragma once", ""]
    for a, sig in sorted(decls.items()):
        flines.append(f"{sig};")
    out[names.FUNCTIONS_H] = "\n".join(flines) + "\n"
    glines = [HEADER, "#pragma once", ""]
    for a, ext in sorted(externs.items()):
        glines.append(f"{ext};")
    out[names.GLOBALS_H] = "\n".join(glines) + "\n"
    slines = [HEADER, '#include "decls.h"', ""]
    for a, sig in sorted(stubs.items()):
        slines += [f"// STUB: {target} 0x{a:08x}", sig, stub_body(sig), ""]
    out[names.STUBS_CPP] = "\n".join(slines)
    dlines = [HEADER, '#include "decls.h"', ""]
    for a, (definition, const) in sorted(gdefs.items()):
        init = " = {}" if const and "[" in definition else (" = 0" if const else "")
        dlines += [f"// GLOBAL: {target} 0x{a:08x}", f"{definition}{init};", ""]
    out[names.GLOBALS_CPP] = "\n".join(dlines)
    for rel, text in out.items():
        path = ROOT / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        old = path.read_text(encoding="utf-8") if path.exists() else None
        if old != text:
            path.write_text(text, encoding="utf-8", newline="\n")
    for p in problems + fatal:
        print("decls:", p)
    print(f"decls: {len(decls)} functions ({len(stubs)} stubs), {len(externs)} globals "
          f"({len(gdefs)} generated), {len(defined_types)} types")
    return 1 if fatal else 0


def declared_size(decl: str, types: Types) -> int | None:
    """The bytes that a global's declaration takes, or None when its type or an array length is unknown."""
    name = names.declared_name(decl)
    tail_start = list(re.finditer(rf"\b{re.escape(name)}\b", decl))[-1].end()
    size = names.element_size(decl[:tail_start - len(name)].strip(), types)
    for length in re.findall(r"\[\s*([^\]]*?)\s*\]", decl[tail_start:]):
        if size is None or not re.fullmatch(r"\d+|0x[0-9a-f]+", length):
            return None
        size *= int(length, 0)
    return size


def type_of(decl: str) -> str:
    """The declaration without its name, such as `struct NJS_ARGB` or `int[4]`."""
    name = names.declared_name(decl)
    return re.sub(r"\s+(?=\[)", "", re.sub(rf"\b{re.escape(name)}\b", "", decl, count=1)).strip()


def nested_globals(declarations: dict[int, str], own: set[int], last: dict[int, str],
                   types: Types) -> tuple[list[str], list[str], list[str]]:
    """(a line for each new global that lies inside another global, a line for each global that holds others as in
    LAST, the names of the globals whose size is unknown). Only a pair with a global in OWN counts. DECLARATIONS and
    LAST: address: declaration. The generated layout gives every global its own object, so a global inside another
    one splits it and moves the fields behind it."""
    sizes = {a: declared_size(d, types) for a, d in declarations.items()}
    new, held = [], collections.defaultdict(list)
    holder = None  # (end, address) of the global that reaches farthest among the lower addresses
    for a in sorted(declarations):
        if holder and a < holder[0] and (a in own or holder[1] in own):
            h = holder[1]
            if all(x in last and declared_size(last[x], types) == sizes[x] for x in (a, h)):
                held[h].append(a)
            else:
                new.append(f"{names.declared_name(declarations[a])}: inside {names.declared_name(declarations[h])} "
                           f"({type_of(declarations[h])}) at +{a - h}. Remove that declaration and reach it "
                           f"through {names.declared_name(declarations[h])}.")
        if sizes[a] is not None and (not holder or a + sizes[a] > holder[0]):
            holder = (a + sizes[a], a)
    old = [f"{names.declared_name(declarations[h])} ({type_of(declarations[h])}) holds {len(inside)} other globals, "
           "as in the last layout: " + ", ".join(f"{names.declared_name(declarations[a])} at +{a - h}"
                                                 for a in inside[:3]) + (", ..." if len(inside) > 3 else "")
           for h, inside in held.items()]
    return new, old, [names.declared_name(declarations[a]) for a in sorted(sizes) if sizes[a] is None]


def global_names(defined: dict, context: dict, before: names.Previous, fnames: dict) -> dict[str, int]:
    """name: address of each global the tree, the context or the last run defines, if the name is unique."""
    found = collections.defaultdict(set)
    for a, (_, definition) in list(context.items()) + list(defined.items()):
        found[names.declared_name(definition)].add(a)
    for a, definition in before.globals.items():
        found[names.declared_name(definition)].add(a)
    return {n: next(iter(a)) for n, a in found.items() if n and len(a) == 1 and len(n) > 2 and n not in fnames}
