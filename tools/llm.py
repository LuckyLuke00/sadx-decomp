"""Let a language model decompile functions, with the build's score as its feedback.

  python tools/llm.py init [--url URL] [--key-env VAR] [--model NAME] [--start "COMMAND"]
      find the chat server, see what it takes and write llm.json
  python tools/llm.py solve FILE 0x00401000 [0x...]
      the loop for each function, in this checkout: the best attempt stays in FILE
  python tools/llm.py bench [--set SET.tsv | --ladder N]
      solve matched functions again, each from a start without it, then put the files back
  python tools/llm.py report [--tag T]
      the summary of each results file, or of T's

Any server with an OpenAI-style /chat/completions works: llama.cpp, Ollama, LM Studio,
vLLM or a hosted API. docs/FRAMEWORK.md, section "LLM agents", says how to set one up.
tools/llmclient.py says what llm.json holds.

solve and bench take --prompt NAME (the system prompt tools/prompts/NAME.txt, plus
data/llm-hints.txt when the game has one), --tries N, --seed S (try N asks with seed
S+N), --structs (the first prompt lists the members of the structs the dossier names,
and a build error about a missing member lists the members of that struct), --accesses
(each dossier adds how the whole exe reads and writes each global it names), --facts (each
dossier adds what the assembly hides: calling convention, pointer globals, structs without
members), --top-k K,
--top-p P and --min-p M (sent with every request, else the server picks), --tree-wins
(a try that fails on a declaration the tree has in another way is built once more without
the model's declaration of that name), --think-max N (the run ends when it would think after
N thinking tries, or after a thinking try that repeated), --max-repeats N (the run ends after
N tries that repeated an earlier try), --give-up (the run ends after
GIVE_UP_STALE tries without a new best, or after STUCK_TRIES when the best is below
GIVE_UP_BELOW%), --stop-below P (the run ends after STOP_AFTER tries when the best is below P%,
or when nothing built), --try-tokens N,N,... (the reply limit of each try in turn, the last one for
the tries after it; a thinking try keeps its own), --stale-built-only (a try that does not build
does not count toward STUCK_TRIES, nor toward --give-up) and --tag T (default: the prompt's name). Every command
takes --config PATH.
Results go to build/llm/T/: results.tsv with a row per function and transcripts/ADDRESS.jsonl
with every exchange.

bench solves each function of its set from the same start: the function's file with the
function and the file's unmatched functions as stubs, without the declarations only they
used. Then it puts the file and the generated files back. Git must hold each file as it
is, staged or committed, to restore it after a hard kill. Matched means 100% in
docs/progress/summary.json. It saves the set
as build/llm/T/set.tsv and runs that one again for T. A new tag without --set gets
--ladder N: N matched functions of each size bucket, spread over the exe.

The loop: the first prompt holds the function's dossier and up to EXAMPLES matched
functions of the same code group, its own file first, then the nearest in size. Each
attempt goes into the file as it was before the function, and `check.py decls` and
`check.py fn` score it. Then the model sees its best attempt so far with that attempt's
diff, and one line on its latest try when that was another. When the instructions differ
only in the names of globals or functions, the feedback lists the exe's name next to the
model's for each one. An attempt it already sent
is not built again, and the temperature rises until it sends something new. Nor is a try with a word
that tricks.forbidden finds, such as inline assembly: it can never match. A try that does not
build gets repairs, each built once more and kept when it fixes its error: the exe's or the
runtime's spelling of a name, calls and variables through the model's type where the tree declares
them another way, the runtime's declarations, declarations from earlier tries, `(char *)` on a
pointer to a type of unknown size, casts on pointer conversions that C accepts (up to CAST_ROUNDS
rounds) and no `static` on a function that nothing calls. The note to the model names each one.
After STUCK_TRIES tries without a new best, the tries think until the best moves again.
When the file already holds the function, that code is the first best: a solve only
replaces it with a try that scores higher.
"""

import argparse
import collections
import csv
import functools
import json
import re
import subprocess
import sys
import time
from pathlib import Path

import cfix
import check
import ci
import declgen
import llmclient
import names
import osutil
import progress
import project
import scoring
import tricks

ROOT = project.ROOT
PROMPTS = ROOT / "tools" / "prompts"  # NAME.txt: the system prompt that --prompt NAME picks
HINTS = ROOT / "data" / "llm-hints.txt"  # the game's own facts, added to the system prompt when present
CONFIG = ROOT / "llm.json"
OUT = project.BUILD / "llm"
SERVER_LOG = OUT / "server.log"
BUCKETS = (("<=32", 32), ("33-64", 64), ("65-128", 128), ("129-256", 256), ("257-512", 512), (">512", float("inf")))
LADDER = 5  # functions per size bucket
FEEDBACK_LINES = 150
ERROR_LINES = 40
STUCK_TRIES = 3  # tries without a new best before the model thinks
GIVE_UP_STALE, GIVE_UP_BELOW = 4, 60  # --give-up ends a run at this many stale tries, or at STUCK_TRIES below this %
STOP_AFTER = 2  # --stop-below looks at the best after this many tries
TEMPERATURE_STEP, TEMPERATURE_MAX = 0.3, 1.2  # added after each repeated attempt
EXAMPLES = 2
CAST_ROUNDS = 3  # builds of a try with casts added on the pointer conversions the compiler refused
OFF, ON = '#pragma optimize("", off)', '#pragma optimize("", on)'  # around a static STUB that its own file calls
STRUCT_LINES = 120  # member lines in the first prompt's Structs section
STRUCT_DEPTH = 2  # levels of member types below the types the dossier names
STRUCTS_RULE = ("The Structs section lists members with their offsets: "
                "use the member names, not casts, when an offset matches.")
RESULT_FIELDS = ["file", "address", "size", "tries", "best", "wall_s", "prompt_tokens", "completion_tokens", "model",
                 "think_tries", "repeats"]
SET_FIELDS = ["file", "address", "size", "name"]
BLOCK = re.compile(r"```[a-zA-Z+]*[ \t]*\n(.*?)```", re.S)
NOT_BUILT = "Failed to find function symbol"  # reccmp: the build holds no code for the function
CALL_CLASH = re.compile(r"error C26(?:60|64): '(\w+)'")  # a call that the callee's declaration rejects
# A name the code uses without its declaration, or a runtime function declared by hand and so mangled as C++.
UNDECLARED = re.compile(r"error C(?:3861|2065): '(\w+)'|unresolved external symbol \"[^\"(]*?(\w+)\(")
ALIAS = re.compile(r"^decls: ((?:FUN|DAT)_[0-9a-f]{8}) has the name (\w+): use that$", re.M)
UNRESOLVED_VARIABLE = re.compile(r'unresolved external symbol "[^"]*?(\w+)" \(\?')  # a variable: its type has no "("
SHORT_GLOBAL = re.compile(r"DAT_([0-9a-f]{1,7})$")  # a global's name with a digit of its address missing
PROMPT_GLOBAL = re.compile(r"DAT_([0-9a-f]{8})|\b0x([0-9a-f]{6,8})\b")  # a global in the dossier, or in its assembly
# Names that the model puts in place of the runtime's, and the runtime's name.
MATH_NAMES = "sqrt sin cos tan asin acos atan atan2 exp log log10 pow fmod".split()
MEMORY_NAMES = "memset memcpy memmove strlen strcpy".split()
RUNTIME_SYNONYMS = {
    **{f"{name}f": name for name in MATH_NAMES + ["fabs", "floor", "ceil"]},
    **{f"_CI{name}": name for name in MATH_NAMES},
    **{f"{prefix}{name}": name for prefix in ("__", "__builtin_") for name in MEMORY_NAMES},
}
# Ghidra's type names, and the C type.
GHIDRA_TYPES = {"uint": "unsigned int", "ushort": "unsigned short", "ulong": "unsigned long", "byte": "unsigned char",
                "uchar": "unsigned char", "undefined1": "unsigned char", "undefined2": "unsigned short",
                "undefined4": "unsigned int"}
FTOL_NAMES = ("_ftol2_sse", "_ftol2", "__ftol2_sse", "__ftol2", "_ftol")  # the compiler's float to int helpers
FTOL_CALL = re.compile(r"(?<![\w.>])(?:" + "|".join(FTOL_NAMES) + r")\s*\(")
# Runtime functions with C linkage, as a C build sees them. A C++ header would also declare overloads such as
# floor(float), which change the code of the file's other functions.
CRT_PROTOTYPES = {
    "memset": "void *memset(void *dst, int value, unsigned int size)",
    "memcpy": "void *memcpy(void *dst, const void *src, unsigned int size)",
    "memmove": "void *memmove(void *dst, const void *src, unsigned int size)",
    "memcmp": "int memcmp(const void *a, const void *b, unsigned int size)",
    "memchr": "void *memchr(const void *s, int c, unsigned int size)",
    "strcpy": "char *strcpy(char *dst, const char *src)",
    "strncpy": "char *strncpy(char *dst, const char *src, unsigned int size)",
    "strcat": "char *strcat(char *dst, const char *src)",
    "strcmp": "int strcmp(const char *a, const char *b)",
    "strncmp": "int strncmp(const char *a, const char *b, unsigned int size)",
    "strlen": "unsigned int strlen(const char *s)",
    "strchr": "char *strchr(const char *s, int c)",
    "strrchr": "char *strrchr(const char *s, int c)",
    "strstr": "char *strstr(const char *s, const char *part)",
    "rand": "int rand(void)",
    "srand": "void srand(unsigned int seed)",
    "abs": "int abs(int x)",
    "labs": "long labs(long x)",
    "atoi": "int atoi(const char *s)",
    "atol": "long atol(const char *s)",
    "atof": "double atof(const char *s)",
    "malloc": "void *malloc(unsigned int size)",
    "calloc": "void *calloc(unsigned int count, unsigned int size)",
    "realloc": "void *realloc(void *p, unsigned int size)",
    "free": "void free(void *p)",
    "qsort": ("void qsort(void *base, unsigned int count, unsigned int size, "
              "int (*compare)(const void *, const void *))"),
    **{name: f"double {name}(double x)"
       for name in "sqrt sin cos tan asin acos atan fabs floor ceil exp log log10".split()},
    "atan2": "double atan2(double y, double x)",
    "pow": "double pow(double x, double y)",
    "fmod": "double fmod(double x, double y)",
    "printf": "int printf(const char *format, ...)",
    "sprintf": "int sprintf(char *dst, const char *format, ...)",
    "_snprintf": "int _snprintf(char *dst, unsigned int size, const char *format, ...)",
    "vsprintf": "int vsprintf(char *dst, const char *format, char *args)",
    "_vsnprintf": "int _vsnprintf(char *dst, unsigned int size, const char *format, char *args)",
    "sscanf": "int sscanf(const char *s, const char *format, ...)",
}
# The runtime names that need their header: macros, and functions that take a FILE.
CRT_HEADERS = {"stdarg.h": "va_start va_arg va_end", "stdio.h": "fprintf fopen fclose fread fwrite fseek ftell"}
CRT_HEADER = {name: header for header, functions in CRT_HEADERS.items() for name in functions.split()}
# C2440 or C2664 on a conversion: file, line, what is converted ('=' or a callee's name), parameter, from, to
CONVERSION = re.compile(r"^(.+?)\((\d+)\) : error C(?:2440|2664): '([^']*)' : cannot convert "
                        r"(?:(?:parameter|argument) (\d+) )?from '([^']*)' to '([^']*)'$")
CONVERTED = {"=", "initializing", "return"}  # what C2440 can name when one expression is converted
ERROR_AT = re.compile(r"^(.+?)\((\d+)\) : error ")
CAST_BROKEN = re.compile(r"error C(?:2059|2143|2061|2146|2065):")  # what a cast the compiler cannot parse causes
SCORE = re.compile(r"^(0x[0-9a-f]{8}) \S.*?: (?:(\d+(?:\.\d+)?)% match|(stub))", re.M)
DECLARED = re.compile(r"^(?:prototype:|locals:|  \w+ 0x[0-9a-f]{8} ).*", re.M)  # a dossier's typed lines
TAG = re.compile(r"\b(?:struct|union|enum)\s+(\w+)")
OFFSET = re.compile(r"static_assert\(offsetof\(\w+, (\w+)\) == (0x[0-9a-f]+)")
MISSING_MEMBER = re.compile(r"C2039: '\w+' : is not a member of '(\w+)'")
DIFF_LINE = re.compile(r"^(?:0x[0-9a-f]+)?\s*: ([-+])(.*)$", re.M)  # a changed line of reccmp's diff: sign, text
SOURCE_LINE = re.compile(r"\s+\([^()\s]+:\d+\)$")  # such as "	(ef_flash.c:128)" after a line of our build
# decls lines that say the tree declares a name in another way: name, then the tree's way(s)
CLASH_CONTEXT = re.compile(r"^decls: (\w+): (.+) in the context tree\. Declare it that way too\.$")
CLASH_TREE = re.compile(r"^decls: (\w+): the tree declares it `([^`]*)`, a file here declares it `([^`]*)`")
CLASH_WAYS = re.compile(r"^decls: (\w+): sources declare it in \d+ ways: (.+)$")
SYMBOL = re.compile(r"[^\s,\[\]]+(?:\[[^\]]*\])*(?:\+0x[0-9a-f]+)? \([A-Z]+\)")  # a name reccmp put in, with its kind
Best = collections.namedtuple("Best", "percent reply note text")  # text: the source file with that attempt in it
Build = collections.namedtuple("Build", "decls func source percent output")  # source: the file that holds the code
# file, line and the type without its `*` of an error on a pointer to a type of unknown size
UNKNOWN_SIZE = re.compile(r"^(.+?)\((\d+)\) : error C2036: '([^']*?)\s*\*' : unknown size", re.M)
ERROR_CODE = re.compile(r"\berror (C\d+)")
BYTE_STEPS = 40  # rewrites per line in byte_arith, a stop for a loop that cannot happen
OFFSET_LINES = 3  # lines that the note on byte offsets shows
TASK_LEAD = "Now your function. "  # between the examples and the function's own task in the first prompt
Conversion = collections.namedtuple("Conversion", "path line name param source target")  # param: None for a C2440


def hexa(address):
    return f"0x{address:08x}"


def bucket(size):
    return next(name for name, top in BUCKETS if size <= top)


@functools.cache
def marker() -> re.Pattern:
    """The line above a definition: FUNCTION or STUB."""
    return re.compile(rf"//\s*(?:FUNCTION|STUB):\s*{project.game_config().target}\s+(0x[0-9a-fA-F]+)")


def function_line(address):
    return f"// FUNCTION: {project.game_config().target} {hexa(address)}"


def annotation_address(line):
    m = marker().match(line)
    return int(m.group(1), 16) if m else None


def definition_span(lines, address):
    """(first, last) line index of the definition at ADDRESS, or None when it has none or no closing line."""
    start = next((i for i, line in enumerate(lines) if annotation_address(line) == address), None)
    end = None if start is None else names.definition_end(lines, start)
    return None if end is None else (start, end)


def wrap_stub(func, sig):
    """FUNC, a definition's lines with the signature SIG, between OFF and ON when it is a static STUB: the compiler
    keeps a call to a function that is compiled without optimization, as it does for a function of another file. Any
    other FUNC as it is."""
    if re.match(r"static\b", sig) and func[0].startswith("// STUB"):
        return [OFF, *func, ON]
    return func


def definition_block(lines, address):
    """definition_span, widened over the OFF and ON lines around the definition: the lines to cut or replace."""
    span = definition_span(lines, address)
    if span is None:
        return None
    first, last = span
    if first and lines[first - 1] == OFF and last + 1 < len(lines) and lines[last + 1] == ON:
        return first - 1, last + 1
    return span


def unclosed_definitions(lines):
    """The indexes of the FUNCTION and STUB annotations in LINES whose definition has no lone "}" line before the
    next such annotation. apply_function takes the first one after an annotation as the definition's end: with none,
    it stops; past the next annotation, it replaces the next definition too."""
    starts = [i for i, line in enumerate(lines) if annotation_address(line) is not None]
    unclosed = []
    for start, after in zip(starts, starts[1:] + [len(lines)]):
        end = names.definition_end(lines, start)
        if end is None or end > after:
            unclosed.append(start)
    return unclosed


def signature_index(func):
    """Index in FUNC, a definition's lines from its annotation on, of the signature: the first line after the
    annotation that is not blank or a `//` comment, as names.parse_annotations reads it."""
    return next(i for i, line in enumerate(func) if i > 0 and line.strip() and not line.lstrip().startswith("//"))


def defined_name(text, address):
    """The name of TEXT's definition at ADDRESS, or None when it has none."""
    lines = text.split("\n")
    span = definition_span(lines, address)
    return None if span is None else names.declared_name(next(line for line in lines[span[0] + 1:] if line.strip()))


def first_function_line(lines):
    """Index of the first annotated line: the top-of-file declarations end there."""
    return next((i for i, line in enumerate(lines) if annotation_address(line) is not None), len(lines))


def parse_reply(reply, address, name=None):
    """(declarations, function lines) from the first fenced block that holds the function's annotation, else from
    the first that defines NAME, with the annotation put above the definition. Declarations between the annotation
    and the signature join the others: the file's tools take the first statement after an annotation as its
    signature."""
    blocks = [[line.rstrip() for line in m.group(1).split("\n")] for m in BLOCK.finditer(reply.replace("\r\n", "\n"))]
    for lines in blocks + [annotated_definition(lines, address, name) for lines in blocks if name]:
        span = definition_span(lines, address)
        if span is not None:
            func = lines[span[0]:span[1] + 1]
            sig = next(i for i, line in enumerate(func) if i and line and not line.endswith(";") and line[:2] != "//")
            inner = [i for i in range(1, sig) if func[i].endswith(";")]
            decls = [d for d in lines[:span[0]] if d and not d.startswith("//")] + [func[i] for i in inner]
            return decls, [line for i, line in enumerate(func) if i not in inner]
    return None


def annotated_definition(lines, address, name):
    """LINES with the annotation of ADDRESS above the first unindented definition of NAME, or LINES as they are."""
    at = next((i for i, line in enumerate(lines) if line[:1].strip() and "(" in line and not line.endswith(";")
               and names.declared_name(line) == name), None)
    return lines if at is None else lines[:at] + [function_line(address)] + lines[at:]


def apply_function(text, address, decls, func):
    """TEXT with the function in address order (replacing its old definition) and the new declarations after the includes."""
    lines = text.split("\n")
    if lines[-1] == "":
        lines.pop()
    sig = names.parse_annotations("\n".join(func))[0][2]
    func = wrap_stub(func, sig)
    annotated = [(i, annotation_address(line)) for i, line in enumerate(lines) if annotation_address(line) is not None]
    same = next((i for i, a in annotated if a == address), None)
    later = next((i for i, a in annotated if a > address), None)
    if same is not None:
        block = definition_block(lines, address)
        if block is None:
            sys.exit(f"the definition at {hexa(address)} has no closing brace line")
        lines[block[0]:block[1] + 1] = func
    elif later is not None:
        if lines[later - 1] == OFF:
            later -= 1  # a wrapped STUB starts at its OFF line
        lines[later:later] = func + [""]
    else:
        if lines:
            lines.append("")
        lines += func
    if re.match(r"static\b", sig):
        decls = decls + [sig + ";"]  # callers above it need a prototype, and decls never declares a static function
    includes = [i for i, line in enumerate(lines[:first_function_line(lines)]) if line.startswith("#include")]
    seen = {line.strip() for line in lines}
    new = [d for d in dict.fromkeys(decls) if d.strip() not in seen]
    at = includes[-1] + 1 if includes else 0
    lines[at:at] = new
    return "\n".join(lines) + "\n"


@functools.cache
def table_names(tables):
    """address: name of each function in TABLES' functions.tsv, or None without tables."""
    if not tables:
        return None
    return {int(r["address"], 16): r["name"] for r in names.table_rows(Path(tables) / "functions.tsv")}


@functools.cache
def shared_names(tables):
    """The function names that several functions in TABLES have, or None without tables."""
    if table_names(tables) is None:
        return None
    counts = collections.Counter(table_names(tables).values())
    return {name for name, n in counts.items() if n > 1}


def without_static(func, shared):
    """FUNC's lines without `static` before its signature, or None when its signature has none or its name may be
    in SHARED (None: unknown). A function without `static` clashes with any other function of its name."""
    at = signature_index(func)
    if not re.match(r"static\s", func[at]):
        return None
    signature = re.sub(r"^static\s+", "", func[at])
    if shared is None or names.declared_name(signature) in shared:
        return None
    return func[:at] + [signature] + func[at + 1:]


def stub_functions(text, addresses):
    """TEXT with the definitions at ADDRESSES as stubs, and without the top-of-file declarations only they used."""
    lines = text.split("\n")
    for address in addresses:
        block = definition_block(lines, address)
        if block is not None:
            sig = names.parse_annotations("\n".join(lines[block[0]:block[1] + 1]))[0][2]
            stub = [f"// STUB: {project.game_config().target} {hexa(address)}", sig, declgen.stub_body(sig)]
            stub = "\n".join(stub).split("\n")
            lines[block[0]:block[1] + 1] = wrap_stub(stub, sig)
    top = first_function_line(lines)
    declared = [names.declared_name(line[:-1]) if i < top and line.endswith(";") else None for i, line in enumerate(lines)]
    used = collections.Counter()
    for line, name in zip(lines, declared):
        used.update(set(re.findall(r"\w+", line)) - {name})
    return "\n".join(line for line, name in zip(lines, declared) if name is None or used[name])


def read_source(path):
    """The file's text with LF line ends, and whether the file has CRLF ones."""
    if not path.exists():
        return '#include "decls.h"\n', False
    text = path.read_bytes().decode("utf-8")
    return text.replace("\r\n", "\n"), "\r\n" in text


def write_source(path, text, crlf):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes((text.replace("\n", "\r\n") if crlf else text).encode("utf-8"))


def snapshot(paths):
    """The bytes of each of PATHS that exists, for restore."""
    return {p: p.read_bytes() for p in paths if p.exists()}


def restore(saved):
    for p, data in saved.items():
        p.write_bytes(data)


def generated_files():
    return [ROOT / rel for rel in names.GENERATED]


def run_check(*args):
    """(output, exit code) of tools/check.py with ARGS."""
    out = subprocess.run([sys.executable, str(ROOT / "tools" / "check.py"), *args], cwd=ROOT, capture_output=True,
                         text=True, errors="replace")
    return out.stdout + out.stderr, out.returncode


def folder_flags(config, *keys):
    """--tables T and the like, for the folders llm.json sets."""
    return [arg for key in keys if config[key] for arg in (f"--{key}", config[key])]


def tree_roots(config):
    """This tree, then the context tree when llm.json sets one."""
    return [ROOT, *([Path(config["context"])] if config["context"] else [])]


def decls(config):
    """(output, exit code) of check.py decls with the folders llm.json sets."""
    return run_check("decls", *folder_flags(config, "tables", "context"))


def score(config, address):
    """(percent, or None when nothing built or decls failed, the output of decls and the scoring)."""
    declared, failed = decls(config)
    text, _ = run_check("fn", hexa(address))
    scores = {int(m.group(1), 16): 0.0 if m.group(3) else float(m.group(2)) for m in SCORE.finditer(text)}
    return (None if failed else scores.get(address)), declared + text


def dossier(config, address, *flags):
    return run_check("dossier", hexa(address), *flags, *folder_flags(config, "tables", "drafts", "context"))[0].strip()


def tree_warnings(config):
    """The decls lines of the tree before the first try, when decls passes: they are not about the function."""
    text, failed = decls(config)
    return set() if failed else {line for line in text.splitlines() if line.startswith("decls:")}


def tool_lines(text, known):
    """The scoring output without decls' summary line of the functions it declared and the KNOWN decls lines."""
    return [line for line in text.splitlines()
            if not (line.startswith("decls:") and ("functions (" in line or line in known))]


def build_errors(text, known):
    """The lines that say why decls or the build failed."""
    lines = tool_lines(text, known)
    errors = [line for line in lines if " error " in line or "fatal" in line or line.startswith("decls:")]
    shown = (errors or lines[-ERROR_LINES:])[:ERROR_LINES]
    if any(NOT_BUILT in line for line in lines):
        shown.append("If the function is `static`, drop the `static`: the compiler leaves out a static function "
                     "that nothing in the build calls, so there is nothing to score.")
    return shown


def error_count(text, known):
    """How many compiler errors the build output TEXT holds."""
    return sum(" error " in line for line in tool_lines(text, known))


def tree_conflicts(decls, lines):
    """(DECLS without the model's declarations that decls' LINES say clash with the tree, name: the tree's ways)."""
    mine = {}
    for d in decls:
        for name, decl in line_declarations(d):
            mine.setdefault(name, set()).add(decl)
    gone = {}
    for line in lines:
        m = CLASH_CONTEXT.match(line)
        if m and m.group(1) in mine:
            gone[m.group(1)] = re.findall(r"declares it `([^`]*)`", m.group(2))
        m = CLASH_TREE.match(line)
        if m and m.group(3) in mine.get(m.group(1), ()):
            gone[m.group(1)] = [m.group(2)]
        m = CLASH_WAYS.match(line)
        if m:
            ways = m.group(2).split(" | ")
            theirs = [w for w in ways if w not in mine.get(m.group(1), ())]
            if theirs and len(theirs) < len(ways):
                gone[m.group(1)] = theirs
    return without_declarations(decls, gone), gone


def line_declarations(line):
    """(name, declaration) of each declaration that LINE holds whole: a declaration over two lines has none."""
    funcs, vars_ = names.local_declarations(line)
    return funcs + vars_


def cast_calls(func, decls, clashed):
    """FUNC's lines with each call to a name in CLASHED made through a pointer of the type DECLS give it, such as
    `((void (*)(int, int))f)(a, b)`. The call then builds whatever the tree declares, and compiles to the same code."""
    types = {name: re.sub(rf"\b{name}\s*\(", "(*)(", re.sub(r"^(extern|static)\s+", "", decl), count=1)
             for d in decls for name, decl in line_declarations(d) if name in clashed}
    at = signature_index(func)
    body = func[at + 1:]
    for name, pointer in types.items():
        call = re.compile(rf"(?<![\w.>&]){name}\s*\(")
        body = [call.sub(f"(({pointer}){name})(", line) for line in body]
    return func[:at + 1] + body


def one_edit_apart(a, b):
    """Whether A and B are equal or differ by one character changed, added or left out."""
    if abs(len(a) - len(b)) > 1:
        return False
    if len(a) == len(b):
        return sum(x != y for x, y in zip(a, b)) <= 1
    short, longer = sorted((a, b), key=len)
    return any(longer[:i] + longer[i + 1:] == short for i in range(len(longer)))


def short_globals(flagged, prompt):
    """name: DAT_ name of an address in PROMPT, for each flagged DAT_ name that has fewer than 8 digits and an address
    to match: the digits with zeros in front, else the only address one edit apart."""
    known = {(a or b).rjust(8, "0") for a, b in PROMPT_GLOBAL.findall(prompt)}
    fixes = {}
    for name in flagged:
        m = SHORT_GLOBAL.match(name)
        if m:
            padded = m.group(1).rjust(8, "0")
            near = [a for a in known if one_edit_apart(a, m.group(1)) or one_edit_apart(a, padded)]
            pick = padded if padded in known else near[0] if len(near) == 1 else None
            if pick:
                fixes[name] = f"DAT_{pick}"
    return fixes


def ftol_casts(line):
    """LINE with each call of a float to int helper, such as `_ftol2_sse(x)`, as the cast `((long)(x))`."""
    out, at = "", 0
    while True:
        m = FTOL_CALL.search(line, at)
        if not m:
            return out + line[at:]
        close = cfix.bracket_end(line, m.end() - 1)
        if close is None:  # the call goes on over the next line
            return out + line[at:]
        out += f"{line[at:m.start()]}((long)({line[m.end():close]}))"
        at = close + 1


def with_renames(decls, func, text, prompt):
    """(DECLS and FUNC with the names that the build output TEXT flags written another way, the renames as old: new),
    or (DECLS, FUNC, {}) when there is none. The names: a function or global that decls says the tables name, a global
    with a digit of its address missing (the address is in PROMPT), a runtime function or Ghidra type under another
    name, and the compiler's float to int helpers (new: a cast)."""
    flagged = undeclared(text) | set(UNRESOLVED_VARIABLE.findall(text))
    renames = dict(ALIAS.findall(text))
    renames.update(short_globals(flagged, prompt))
    renames.update({name: RUNTIME_SYNONYMS[name] for name in flagged & RUNTIME_SYNONYMS.keys()})
    renames.update({name: GHIDRA_TYPES[name] for name in flagged & GHIDRA_TYPES.keys()})
    used = set(re.findall(r"\w+", "\n".join(decls + func)))
    renames = {old: new for old, new in renames.items() if old in used}
    ftol = flagged & set(FTOL_NAMES) & used
    if not renames and not ftol:
        return decls, func, {}
    if renames:
        pattern = re.compile(r"(?<![\w.])(?<!->)(" + "|".join(map(re.escape, renames)) + r")\b")
        decls = [pattern.sub(lambda m: renames[m.group(1)], d) for d in decls]
        func = [pattern.sub(lambda m: renames[m.group(1)], line) for line in func]
    if ftol:
        decls = without_declarations(decls, ftol)
        func = [ftol_casts(line) for line in func]
    return list(dict.fromkeys(decls)), func, {**renames, **{name: "(long)" for name in sorted(ftol)}}


def cast_globals(func, decls, dropped):
    """(FUNC's lines with each use of a variable in DROPPED made through a pointer of the type DECLS give it, such as
    `(*(unsigned char *(*))&v)`, the names changed). The code then builds whatever the tree declares, and compiles to
    the same code."""
    pointers = {name: re.sub(rf"\b{name}\b", "(*)", decl, count=1)
                for d in decls for name, decl in names.local_declarations(d)[1] if name in dropped}
    at = signature_index(func)
    body, changed = func[at + 1:], set()
    for name, pointer in pointers.items():
        use = re.compile(rf"(?<![\w.])(?<!->){name}\b(?!\s*\()")
        for i, line in enumerate(body):
            body[i], count = use.subn(f"(*({pointer})&{name})", line)
            if count:
                changed.add(name)
    return func[:at + 1] + body, sorted(changed)


def runtime_line(name):
    """The line that declares the runtime function or macro NAME."""
    return f"#include <{CRT_HEADER[name]}>" if name in CRT_HEADER else f'extern "C" {CRT_PROTOTYPES[name]};'


def undeclared(text):
    """The names that the build output TEXT says have no declaration."""
    return {name for pair in UNDECLARED.findall(text) for name in pair if name}


def with_runtime(decls, text):
    """(DECLS with a declaration of each runtime function that the build output TEXT says has none, and without the
    model's own declarations of those, the lines added), or (DECLS, []) when there is none."""
    missing = undeclared(text) & (CRT_HEADER.keys() | CRT_PROTOTYPES.keys())
    lines = sorted({runtime_line(name) for name in missing})
    if not lines:
        return decls, []
    return without_declarations(decls, missing) + lines, lines


def with_earlier(decls, text, earlier):
    """(DECLS with EARLIER's line for each name that the build output TEXT says has no declaration, the lines added),
    or (DECLS, []) when there is none. EARLIER maps a name to the line an earlier try declared it with."""
    declared = {name for d in decls for name, _ in line_declarations(d)}
    lines = sorted({earlier[name] for name in undeclared(text) - declared if name in earlier})
    return (decls + lines, lines) if lines else (decls, [])


def without_declarations(decls, dropped):
    """DECLS without the lines that declare a name in DROPPED, such as a --tree-wins try's "dropped" names."""
    return [d for d in decls if not any(name in dropped for name, _ in line_declarations(d))]


def declared_scope(func, decls, attempt, wanted, headers):
    """{name: Pointee} of the declarations in FUNC (its parameters and locals), DECLS, the top of the file's lines
    ATTEMPT and the generated globals headers, the first one that has a name wins. The headers only for WANTED names."""
    scope = {}

    def add(statement):
        declared = cfix.declared_type(statement)
        if declared:
            scope.setdefault(*declared)

    span = names.parameter_span(func[signature_index(func)])
    for parameter in span[2] if span else ():
        add(parameter)
    for line in func[1:] + decls + attempt[:first_function_line(attempt)]:
        add(line)
    wanted = wanted - scope.keys()
    pattern = re.compile(rf"^extern ([^\n]*\b(?:{'|'.join(map(re.escape, wanted))})\b[^\n]*);$", re.M)
    for path in headers if wanted else ():
        for m in pattern.finditer(path.read_text(encoding="utf-8") if path.exists() else ""):
            add(m.group(1))
    return scope


def byte_arith(func, decls, attempt, path, address, text, types, headers):
    """(FUNC with `(char *)` on each pointer to a type of unknown size that the C2036 lines of PATH in TEXT name, the
    lines it changed), or (FUNC, []) when none changes. ATTEMPT is the text of PATH that TEXT is the build of, HEADERS
    the files that declare globals. Such a pointer cannot add an offset, so the model meant bytes, which is what the
    cast says."""
    lines = attempt.split("\n")
    span = definition_span(lines, address)
    if span is None or lines[span[0]:span[1] + 1] != func:
        return func, []
    flagged = collections.defaultdict(dict)  # index in func: {type name: the type as the compiler wrote it}
    for where, number, kind in UNKNOWN_SIZE.findall(text):
        at = int(number) - 1 - span[0]
        if Path(where).resolve() == path.resolve() and 0 <= at < len(func):
            flagged[at][cfix.plain_type(kind)] = kind
    wanted = set(re.findall(r"[A-Za-z_]\w*", " ".join(func[i] for i in flagged)))
    scope = declared_scope(func, decls, lines, wanted, headers)
    fixed, changed = list(func), []
    for i, spellings in flagged.items():
        for _ in range(BYTE_STEPS):
            line = cfix.next_byte_fix(fixed[i], spellings, scope, types)
            if line is None:
                break
            fixed[i] = line
        if fixed[i] != func[i]:
            changed.append(fixed[i].strip())
    return fixed, changed


def fewer_unknown_sizes(before, after):
    """Whether the build output AFTER has fewer C2036 lines than BEFORE and no error code that BEFORE lacks."""
    return (len(UNKNOWN_SIZE.findall(after)) < len(UNKNOWN_SIZE.findall(before))
            and set(ERROR_CODE.findall(after)) <= set(ERROR_CODE.findall(before)))


def conversions(text):
    """The Conversion of each C2440 and C2664 line in the build output TEXT, once each."""
    found = (CONVERSION.match(line.strip()) for line in text.splitlines())
    return list(dict.fromkeys(Conversion(m[1], int(m[2]), m[3], int(m[4]) if m[4] else None, m[5], m[6])
                              for m in found if m))


def pointer_conversion(conversion):
    """Whether CONVERSION is from a pointer to a pointer or an integer, or from an integer to a pointer, so that a cast
    to its target type is the conversion that C makes without one. An array counts as a pointer to convert from."""
    if (conversion.param is None and conversion.name not in CONVERTED) or "<" in conversion.target:
        return False
    return (cfix.type_kind(conversion.source), cfix.type_kind(conversion.target)) in {
        ("pointer", "pointer"), ("array", "pointer"), ("pointer", "integer"), ("array", "integer"),
        ("integer", "pointer")}


def add_casts(func, attempt, text, path, address, kinds, refused=()):
    """(FUNC with a cast on each pointer conversion that the build output TEXT of the file text ATTEMPT refuses in
    the function's own lines under PATH, the Conversions that got a cast). A spot that is not clear gets none, and
    neither does a Conversion in REFUSED. KINDS is the kind of each tag in the tree, for tagged."""
    lines = attempt.split("\n")
    span = definition_span(lines, address)
    first = signature_index(func)
    continued = cfix.continued_lines(func)
    cast, applied = list(func), []
    for conversion in conversions(text) if span else []:
        i = conversion.line - 1 - span[0]
        if (not pointer_conversion(conversion) or conversion in refused
                or Path(conversion.path).resolve() != path.resolve()
                or not first < i < len(func) or i in continued or lines[conversion.line - 1] != func[i]):
            continue
        line = cfix.cast_line(cast[i], conversion, kinds)
        if line is not None:
            cast[i] = line
            applied.append(conversion)
    return cast, applied


def cast_failed(applied, text, retry_text):
    """The Conversions of APPLIED whose cast did not fix its error. RETRY_TEXT is the build with the casts, TEXT the
    build that refused the Conversions. The cast failed when the error is still there, or when its line has a syntax
    error that TEXT did not have, such as a cast to a name the compiler does not know. Another error that the first
    one hid is not the cast's fault."""
    def errors_at(output, conversion):
        return {line for line in output.splitlines()
                if (m := ERROR_AT.match(line)) and (m[1], int(m[2])) == (conversion.path, conversion.line)}

    def failed(conversion):
        before, after = errors_at(text, conversion), errors_at(retry_text, conversion)
        cast = {line for line in before if conversion in conversions(line)}
        return bool(after & cast) or any(CAST_BROKEN.search(line) for line in after - before)

    return [c for c in applied if failed(c)]


def cast_round(rebuild, decls, func, attempt, text, path, address, kinds, refused):
    """(the file text, percent, build output and function lines) of one build of FUNC with casts on the pointer
    conversions that the build output TEXT of the file text ATTEMPT refuses, or None when no cast fixes its error.
    A cast that fails goes into REFUSED and the round is built once more without it, so that one wrong spot does not
    cost the right casts. REBUILD is solve_function's."""
    for _ in range(2):
        cast, applied = add_casts(func, attempt, text, path, address, kinds, refused)
        if not applied:
            return None
        rebuilt, percent, retry_text = rebuild(decls, cast)
        failed = cast_failed(applied, text, retry_text)
        if not failed:
            return rebuilt, percent, retry_text, cast
        refused.update(failed)
    return None


def cast_pointers(rebuild, decls, func, attempt, text, path, address, kinds):
    """(the file text, percent, build output and function lines) after up to CAST_ROUNDS rounds of cast_round, each
    on the build of the round before."""
    percent, refused = None, set()
    for _ in range(CAST_ROUNDS):
        done = cast_round(rebuild, decls, func, attempt, text, path, address, kinds, refused)
        if done is None:
            break
        attempt, percent, text, func = done
    return attempt, percent, text, func


def load_types(config):
    return names.Types(Path(config["tables"]) / "types.h" if config["tables"] else ROOT / names.TYPES_H)


def render_type(types, name):
    """(the type's block as C with a /* +0xN */ comment on each member that has an offset, its member line count)."""
    offsets = dict(OFFSET.findall(types.blocks[name]))
    lines = types.blocks[name].splitlines()
    start, end = next(i for i, line in enumerate(lines) if line.endswith("{")), lines.index("};")
    for i in range(start + 1, end):
        offset = re.match(r" {4}\S.*;$", lines[i]) and offsets.get(names.declared_name(lines[i].strip()[:-1]))
        if offset:
            lines[i] += f"  /* +{offset} */"
    return "\n".join(lines[:end + 1]), end - start - 1


def member_types(types, name):
    """The defined types that the members of NAME mention, in order."""
    found = TAG.findall(types.blocks[name].split("};", 1)[0])
    return [t for t in dict.fromkeys(found) if t != name and t in types.blocks]


def struct_section(types, dossier_text):
    """The Structs section: the types that the dossier's prototype, locals and names used lines mention, then their
    member types down to STRUCT_DEPTH, until STRUCT_LINES member lines are shown. "" when the dossier names no
    defined type."""
    level = [t for t in dict.fromkeys(TAG.findall("\n".join(DECLARED.findall(dossier_text)))) if t in types.blocks]
    seen, shown, left, count = set(level), [], 0, 0
    for _ in range(STRUCT_DEPTH + 1):
        below = []
        for name in level:
            text, members = render_type(types, name)
            if count + members > STRUCT_LINES:
                left += 1
                continue
            shown.append(text)
            count += members
            below += [t for t in member_types(types, name) if t not in seen]
            seen.update(below)
        level = below
    if not shown:
        return ""
    more = f"{left} more types do not fit and are left out.\n" if left else ""
    return "Structs (a `/* +0xN */` comment is the member's offset):\n```cpp\n" + "\n\n".join(shown) + "\n```\n" + more


def missing_members(types, errors):
    """The members of each type that a C2039 error in ERRORS names, once per type. "" when there is none."""
    if types is None:
        return ""
    found = [t for t in dict.fromkeys(MISSING_MEMBER.findall("\n".join(errors))) if t in types.blocks]
    if not found:
        return ""
    return ("\nThe compiler named these types; these are all their members (`/* +0xN */` is the offset):\n```cpp\n"
            + "\n\n".join(render_type(types, t)[0] for t in found) + "\n```")


def masked(line):
    """A diff line without the source line reccmp adds to ours, and with each name it put in replaced by SYMBOL."""
    return SYMBOL.sub("SYMBOL", SOURCE_LINE.sub("", line)).strip()


def names_only(diff):
    """Whether the instructions that differ are the same apart from the names of globals and functions. A line that
    is on both sides as it is moved, so the order differs too."""
    sides = {"-": [], "+": []}
    for sign, text in DIFF_LINE.findall(diff):
        sides[sign].append(SOURCE_LINE.sub("", text).strip())
    moved = set(sides["-"]) & set(sides["+"])
    return (bool(sides["-"]) and not moved
            and sorted(map(masked, sides["-"])) == sorted(map(masked, sides["+"])))


def name_pairs(diff):
    """(the exe's name, ours) for each name that differs between a changed line of the exe and the same line in our
    build, once each. Lines that are the same apart from names pair up in order."""
    ours = [text for sign, text in DIFF_LINE.findall(diff) if sign == "+"]
    pairs = []
    for sign, text in DIFF_LINE.findall(diff):
        twin = next((o for o in ours if masked(o) == masked(text)), None) if sign == "-" else None
        if twin is None:
            continue
        ours.remove(twin)
        pairs += [(exe, own) for exe, own in zip(SYMBOL.findall(text), SYMBOL.findall(twin)) if exe != own]
    return list(dict.fromkeys(pairs))


def names_note(diff):
    """The names to change when the instructions differ only in names, else ""."""
    if not names_only(diff):
        return ""
    rows = [f"- the exe has `{exe.rsplit(' (', 1)[0]}` where yours has `{own.rsplit(' (', 1)[0]}`"
            for exe, own in name_pairs(diff)]
    return ("Only names differ: each instruction is the exe's apart from them. The score names an address after the "
            "nearest global at or below it, so one address can have two names. Use the exe's name in each place. "
            "A `[0][5]` or `+8` after a name is the fixed part of the address: keep your own index.\n"
            + "\n".join(rows) + "\n")


def feedback(percent, text, address, known, types=None):
    if percent is None:
        errors = build_errors(text, known)
        return ("Nothing was scored: decls or the compiler failed. They said:\n```\n"
                + "\n".join(errors) + "\n```" + missing_members(types, errors) + "\n"
                f"Fix the function (all of it) and reply with one cpp block again, with the `{function_line(address)}` line.")
    lines = tool_lines(text, known)
    return (f"Score {percent:.2f}%. The scoring tool printed (`decls:` lines are declaration problems: fix them first; "
            "`-` is the exe, `+` is your build):\n```\n" + "\n".join(lines[:FEEDBACK_LINES]) + "\n```\n"
            + names_note(text)
            + "Reply with one cpp block again: the declarations and the whole function with the changes.")


def matched_functions():
    """address: name of each function that docs/progress/summary.json counts as matched: at 100% in plain C."""
    summary = json.loads(progress.SUMMARY_JSON.read_text(encoding="utf-8"))
    return {int(f["address"], 16): f["name"] for f in summary["functions"]
            if scoring.is_matched(f) and not f["library"]}


def definitions(roots):
    """address: (root, file) of each FUNCTION definition. The first root that has one wins."""
    found = {}
    for root in roots:
        for rel, text in names.read_sources(root).items():
            for kind, address, _ in names.parse_annotations(text):
                if kind == "FUNCTION":
                    found.setdefault(address, (root, rel))
    return found


def matched_source(path, address):
    """The C of the definition at ADDRESS in PATH, or None when it has none."""
    lines = path.read_text(encoding="utf-8").split("\n")
    span = definition_span(lines, address)
    return None if span is None else "\n".join(lines[span[0]:span[1] + 1])


def examples(config, file, address, count, extra=()):
    """Up to COUNT matched functions of the same code group, its own file first, then the nearest in size."""
    sizes = {f["address"]: f["size"] for f in progress.load_functions()}
    groups = progress.load_codegen_groups()
    group = progress.codegen_group(groups, address)
    where = definitions(tree_roots(config))
    done = matched_functions()
    pool = sorted((a for a in done if a != address and a in where and progress.codegen_group(groups, a) == group),
                  key=lambda a: (where[a][1] != file, abs(sizes.get(a, 0) - sizes[address]), a))
    shown = []
    for a in pool:
        if len(shown) == count:
            break
        root, rel = where[a]
        source = matched_source(root / rel, a)
        if source is None:
            continue
        shown.append(f"Example: {done[a]}, which matches 100%. Its dossier:\n```\n{dossier(config, a, *extra)}\n```\n"
                     f"Its C:\n```cpp\n{source}\n```")
    return shown


def first_prompt(config, file, address, types=None, count=EXAMPLES, extra=()):
    facts = dossier(config, address, '--c', '--callers', *extra)
    structs = "" if types is None else struct_section(types, facts)
    task = (f"Function {hexa(address)}, to go in {file}. Dossier:\n```\n{facts}\n```\n{structs}"
            f"Write the function. Reply with one cpp block with the `{function_line(address)}` line.")
    shown = examples(config, file, address, count, extra)
    return "\n\n".join(shown + [TASK_LEAD + task]) if shown else task


def attempt_key(parsed):
    """An attempt with its whitespace folded, so a resend with other spacing counts as the same."""
    decls, func = parsed
    return " ".join(" ".join(decls + func).split())


def next_turn(best, improved, reply, note, latest):
    """The model's best attempt and that attempt's feedback, plus a line on the latest try when it was another."""
    if best is None or improved:
        return [{"role": "assistant", "content": reply}, {"role": "user", "content": note}]
    return [{"role": "assistant", "content": best.reply},
            {"role": "user", "content": f"{best.note}\n\nYour latest try {latest}. The reply above is your best so far "
                                        f"({best.percent:.2f}%): start again from it and change something else."}]


def file_best(config, text, address, known, types):
    """The function's definition in the file as a Best, when it has one that builds, else None."""
    lines = text.split("\n")
    span = definition_span(lines, address)
    if span is None or lines[span[0]].lstrip().startswith("// STUB"):
        return None
    percent, output = score(config, address)
    if percent is None:
        return None
    code = "\n".join(lines[span[0]:span[1] + 1])
    return Best(percent, f"```cpp\n{code}\n```", feedback(percent, output, address, known, types), text)


def thinks(stale, config):
    """Whether a try thinks: after STUCK_TRIES tries without a new best, when the server can."""
    return stale >= STUCK_TRIES and bool(config["think_on"])


def reply_limit(args, config, tries):
    """The max_tokens of the try after TRIES tries: its --try-tokens value, the last one for the tries after the list,
    else the config's."""
    if not args.try_tokens:
        return config["max_tokens"]
    return args.try_tokens[min(tries, len(args.try_tokens) - 1)]


class Repairs:
    """What the repairs of one try changed. A repair that did not run or was not kept leaves its field empty."""

    def __init__(self):
        self.renamed = {}  # old name: new name
        self.dropped = {}  # name: the ways the tree declares it
        self.casts = []  # the callees that the code calls through a cast
        self.gcasts = []  # the globals that the code uses through a cast
        self.runtime = []  # the declarations of runtime functions that the code got
        self.carried = []  # the declarations that the code got back from earlier tries
        self.offsets = []  # the lines that got `(char *)` for a byte offset
        self.pointer_casts = []  # {"before": line, "after": line} for each line that got a cast
        self.unstatic = False  # whether the function lost its `static`

    def tree_ways(self):
        """name: the tree's declarations of it, as the model reads them."""
        return {name: " or ".join(f"`{way}`" for way in ways) for name, ways in self.dropped.items()}

    def note(self):
        """What the code got, told to the model in front of the build's feedback."""
        note = "".join(f"Your declaration of {name} was dropped: the tree declares it as {ways}.\n"
                       for name, ways in self.tree_ways().items())
        if self.casts:
            note += f"Your calls to {', '.join(self.casts)} were made through a cast to your declaration's type.\n"
        if self.gcasts:
            note += f"Your uses of {', '.join(self.gcasts)} were made through a cast to your declaration's type.\n"
        if self.runtime:
            note += (f"Your code got {', '.join(f'`{line}`' for line in self.runtime)} for the runtime functions "
                     "it calls, in place of your own declarations of them.\n")
        if self.carried:
            note += (f"Your code got {', '.join(f'`{line}`' for line in self.carried)} back from your earlier tries: "
                     "it uses those names without declaring them.\n")
        if self.renamed:
            note += ("Your code got these names changed: "
                     + ", ".join(f"`{old}` to `{new}`" for old, new in self.renamed.items()) + ".\n")
        if self.offsets:
            note += ("A pointer to a type of unknown size cannot add an offset, so `(char *)` was put on it to "
                     "count bytes, as in " + ", ".join(f"`{line}`" for line in self.offsets[:OFFSET_LINES]) + ".\n")
        if self.pointer_casts:
            note += ("The compiler refused pointer conversions, so these lines got a cast (it compiles to "
                     "the same code as C's implicit conversion):\n"
                     + "".join(f"- `{c['before']}` became `{c['after']}`\n" for c in self.pointer_casts))
        if self.unstatic:
            note += ("Your `static` was dropped: nothing in the build calls the function, so the compiler "
                     "left it out.\n")
        return note

    def latest(self, outcome):
        """The line on the latest try: what its code got, then OUTCOME. next_turn shows only this line when the try
        is no new best."""
        prefixes = []
        if self.dropped:
            prefixes.append("was built without your declaration of "
                            + ", ".join(f"{name} (the tree declares it as {ways})"
                                        for name, ways in self.tree_ways().items()) + " and ")
        if self.casts:
            prefixes.append(f"was built with casts on the calls to {', '.join(self.casts)} and ")
        if self.runtime:
            prefixes.append(f"was built with {', '.join(f'`{line}`' for line in self.runtime)} and ")
        if self.carried:
            prefixes.append(f"was built with your earlier {', '.join(f'`{line}`' for line in self.carried)} and ")
        if self.offsets:
            prefixes.append(f"was built with `(char *)` on the pointers of {len(self.offsets)} byte offsets and ")
        if self.gcasts:
            prefixes.append(f"was built with casts on the uses of {', '.join(self.gcasts)} and ")
        if self.renamed:
            swaps = ", ".join(f"{old} to {new}" for old, new in self.renamed.items())
            prefixes.append(f"was built with these names changed: {swaps}, and ")
        if self.unstatic:
            prefixes.append("was built without `static` and ")
        if self.pointer_casts:
            prefixes.append("was built with casts on the pointer conversions and ")
        return "".join(prefixes) + outcome

    def trim(self):
        """What the code got, as the console line shows it."""
        trim = f" (without its declaration of {', '.join(self.dropped)})" if self.dropped else ""
        trim += " (without static)" if self.unstatic else ""
        trim += f" (casts on {', '.join(self.casts)})" if self.casts else ""
        trim += f" (pointer casts on {len(self.pointer_casts)} lines)" if self.pointer_casts else ""
        trim += f" (casts on uses of {', '.join(self.gcasts)})" if self.gcasts else ""
        trim += f" (with {' '.join(self.runtime)})" if self.runtime else ""
        trim += f" (with earlier {' '.join(self.carried)})" if self.carried else ""
        trim += f" (renamed {' '.join(self.renamed)})" if self.renamed else ""
        trim += f" (byte offsets on {len(self.offsets)} lines)" if self.offsets else ""
        return trim

    def logged(self):
        """The repairs that changed something, under the transcript's keys."""
        repairs = {"dropped": self.dropped, "unstatic": self.unstatic, "casts": self.casts,
                   "pointer_casts": self.pointer_casts, "gcasts": self.gcasts, "runtime": self.runtime,
                   "carried": self.carried, "renamed": self.renamed, "bytes": self.offsets}
        return {key: value for key, value in repairs.items() if value}


class Bench:
    """One function's builds for the repairs. Each repair_ method builds the try again with one repair when the
    build output asks for it, and returns (the build to go on with, what the repair changed). A repair that does
    not help gives back the build it got and an empty change. A try that builds gets no repair."""

    def __init__(self, rebuild, config, path, address, known, tree_wins, types, declared_before):
        self.rebuild = rebuild  # (decls, func) -> (the file with them, its percent or None, the build output)
        self.config, self.path, self.address, self.known = config, path, address, known
        self.tree_wins, self.types = tree_wins, types
        self.declared_before = declared_before  # name: the line an earlier try declared it with

    def build(self, decls, func):
        return Build(decls, func, *self.rebuild(decls, func))

    def repair(self, build, task):
        """Each repair in turn, from the try's first BUILD. TASK is the first prompt's task, which names addresses.
        Returns (the model's code with its names fixed, that code without the declarations that the tree wins over,
        the last build, the Repairs)."""
        repairs = Repairs()
        model, repairs.renamed = self.repair_names(build, task)
        trimmed, repairs.dropped = self.repair_clashes(model)
        build, repairs.casts = self.repair_calls(trimmed, model.decls, repairs.dropped)
        build, repairs.gcasts = self.repair_globals(build, model.decls, repairs.dropped)
        build, repairs.runtime = self.repair_runtime(build)
        build, repairs.carried = self.repair_earlier(build)
        build, repairs.offsets = self.repair_offsets(build)
        build, repairs.pointer_casts = self.repair_pointers(build)
        build, repairs.unstatic = self.repair_static(build)
        return model, trimmed, build, repairs

    def repair_names(self, build, task):
        """A name that the exe or the runtime writes another way gets that way. Kept when the build no longer names
        the old one."""
        if build.percent is not None:
            return build, {}
        decls, func, changes = with_renames(build.decls, build.func, build.output, task)
        if not changes:
            return build, {}
        retry = self.build(decls, func)
        if any(re.search(rf"\b{re.escape(old)}\b", retry.output) for old in changes):
            return build, {}
        return retry, changes

    def repair_clashes(self, build):
        """With the tree_wins option, the model's declarations that clash with the tree go. Kept for the names whose
        clash is gone: else the clash was not the model's declaration."""
        if not self.tree_wins or build.percent is not None:
            return build, {}
        kept, gone = tree_conflicts(build.decls, tool_lines(build.output, self.known))
        if not gone:
            return build, {}
        retry = self.build(kept, build.func)
        left = tool_lines(retry.output, self.known)
        dropped = {name: ways for name, ways in gone.items()
                   if not any(line.startswith(f"decls: {name}: ") for line in left)}
        return (retry, dropped) if dropped else (build, {})

    def repair_calls(self, build, decls, dropped):
        """A call to a DROPPED callee that the tree declares another way goes through a cast to the type that the
        model's DECLS give it. Kept when that clash is gone, even when another error remains."""
        if build.percent is not None:
            return build, []
        clashed = {name for name in CALL_CLASH.findall(build.output) if name in dropped}
        if not clashed:
            return build, []
        retry = self.build(build.decls, cast_calls(build.func, decls, clashed))
        if clashed & set(CALL_CLASH.findall(retry.output)):
            return build, []
        return retry, sorted(clashed)

    def repair_globals(self, build, decls, dropped):
        """A use of a DROPPED variable that the tree declares another way goes through a cast to the type that the
        model's DECLS give it. Kept when the try then builds or has fewer errors."""
        if build.percent is not None or not dropped:
            return build, []
        func, changed = cast_globals(build.func, decls, dropped)
        if not changed:
            return build, []
        retry = self.build(build.decls, func)
        if retry.percent is None and error_count(retry.output, self.known) >= error_count(build.output, self.known):
            return build, []
        return retry, changed

    def repair_runtime(self, build):
        """A runtime function that the code calls undeclared gets its declaration. Kept when none is missing."""
        if build.percent is not None:
            return build, []
        decls, wanted = with_runtime(build.decls, build.output)
        if not wanted:
            return build, []
        retry = self.build(decls, build.func)
        if with_runtime(decls, retry.output)[1]:
            return build, []
        return retry, wanted

    def repair_earlier(self, build):
        """A name that the code uses undeclared gets the line that an earlier try declared it with. Kept when no
        such name is left."""
        if build.percent is not None:
            return build, []
        decls, added = with_earlier(build.decls, build.output, self.declared_before)
        if not added:
            return build, []
        retry = self.build(decls, build.func)
        if with_earlier(build.decls, retry.output, self.declared_before)[1]:
            return build, []
        return retry, added

    def repair_offsets(self, build):
        """A pointer to a type of unknown size gets `(char *)`, so that its offsets count bytes. Kept when fewer of
        those errors are left, even when another error remains."""
        if build.percent is not None or not UNKNOWN_SIZE.search(build.output):
            return build, []
        headers = [root / names.GLOBALS_H for root in tree_roots(self.config)]
        func, changed = byte_arith(build.func, build.decls, build.source, self.path, self.address, build.output,
                                   self.types, headers)
        if not changed:
            return build, []
        retry = self.build(build.decls, func)
        if not fewer_unknown_sizes(build.output, retry.output):
            return build, []
        return retry, changed

    def repair_pointers(self, build):
        """A pointer conversion that the compiler refuses gets a cast, in rounds that keep the casts that help."""
        if build.percent is not None or not any(map(pointer_conversion, conversions(build.output))):
            return build, []
        source, percent, output, func = cast_pointers(self.rebuild, build.decls, build.func, build.source,
                                                      build.output, self.path, self.address, self.types.kind)
        changes = [{"before": was.strip(), "after": now.strip()} for was, now in zip(build.func, func) if was != now]
        return Build(build.decls, func, source, percent, output), changes

    def repair_static(self, build):
        """`static` goes when the build holds no code for the function: the compiler leaves out a static function
        that nothing in the build calls. Kept when the try then builds."""
        if build.percent is not None or NOT_BUILT not in build.output:
            return build, False
        func = without_static(build.func, shared_names(self.config["tables"]))
        if func is None:
            return build, False
        retry = self.build(build.decls, func)
        if retry.percent is None:
            return build, False
        return retry, True


def solve_function(args, file, address, transcript):
    """Run the loop for one function. Returns tries, best, wall_s, prompt_tokens, completion_tokens, think_tries, repeats."""
    config = args.settings
    started = time.time()
    path = ROOT / file
    before, crlf = read_source(path)
    name = defined_name(before, address) or (table_names(config["tables"]) or {}).get(address)
    # decls forgets a name once no file uses it, so each decls run starts from these files.
    generated = snapshot(generated_files())
    known = tree_warnings(config)
    restore(generated)

    def rebuild(decls, func):
        """(the file with DECLS and FUNC in place of the function, its percent or None, the build output)."""
        text = apply_function(before, address, decls, func)
        write_source(path, text, crlf)
        restore(generated)
        return text, *score(config, address)

    types = load_types(config) if args.structs else None
    repair_types = types or load_types(config)  # the byte offset and pointer cast repairs read layouts either way
    extra = (('--accesses',) if args.accesses else ()) + (('--facts',) if args.facts else ())
    count = EXAMPLES
    first = first_prompt(config, file, address, types, count, extra)
    base = [{"role": "system", "content": args.system}, {"role": "user", "content": first}]
    best = file_best(config, before, address, known, types)  # the code already in the file is the floor
    restore(generated)
    messages, seen = base, {}  # seen: key -> (try, note)
    declared_before = {}  # name: the line an earlier try declared it with; a later try often leaves the line out
    bench = Bench(rebuild, config, path, address, known, args.tree_wins, repair_types, declared_before)
    stale, temperature, totals = 0, config["temperature"], collections.Counter()
    transcript.parent.mkdir(parents=True, exist_ok=True)
    with open(transcript, "w", encoding="utf-8") as log:
        log.write(json.dumps({"prompt": first}) + "\n")
        if best is not None:
            log.write(json.dumps({"file_best": best.percent}) + "\n")
            print(f"{hexa(address)}: the file's code scores {best.percent:.2f}%", flush=True)
        tries = 0  # the tries that got a reply
        while tries < args.tries and not (best and best.percent == 100):  # a restored try can match already
            thinking = thinks(stale, config)
            asked = time.time()
            seed = None if args.seed is None else args.seed + tries + 1
            try:
                reply = llmclient.chat({**config, "max_tokens": reply_limit(args, config, tries)}, messages,
                                       temperature, thinking, seed)
            except llmclient.ServerError as e:
                if e.status != 400 or "context" not in str(e).lower():
                    raise
                # Too long for the server: drop the history, else an example, else give up on the function. The
                # shorter chat is the same try again.
                if messages is not base:
                    messages = base
                elif count > 0:
                    count -= 1
                    first = first_prompt(config, file, address, types, count, extra)
                    messages = base = [base[0], {"role": "user", "content": first}]
                    log.write(json.dumps({"prompt": first}) + "\n")
                else:
                    print(f"{hexa(address)} try {tries + 1}: even the first prompt is too long for the server",
                          flush=True)
                    break
                print(f"{hexa(address)} try {tries + 1}: too long for the server, retrying shorter", flush=True)
                continue
            tries += 1
            totals["prompt_tokens"] += reply.usage["prompt_tokens"]
            totals["completion_tokens"] += reply.usage["completion_tokens"]
            totals["think_tries"] += thinking
            parsed = parse_reply(reply.text, address, name)
            percent, repeat, repairs = None, None, Repairs()
            shown = reply.text  # the reply as the model sees it again
            if parsed is None:
                result = latest = "had no function in the reply"
                note = (f"Your reply had no fenced cpp block with the `{function_line(address)}` line and a function "
                        "that ends with a line holding only `}`. Reply with one cpp block.")
            elif attempt_key(parsed) in seen:
                repeat, earlier = seen[attempt_key(parsed)]
                result = latest = f"repeated try {repeat}"
                note = f"That is the same code as your try {repeat}, which got this answer:\n\n{earlier}"
            elif cheats := tricks.forbidden(parsed[0] + parsed[1]):  # no build, so it can never match
                result = latest = "used " + ", ".join(f"`{word}`" for word in dict.fromkeys(cheats)) + ", not allowed"
                note = ("Inline assembly, `__emit`, `__declspec(naked)`, `#pragma` and `__pragma` are not allowed. "
                        "Write the function in C.")
                seen[attempt_key(parsed)] = (tries, note)
            else:
                model, trimmed, build, repairs = bench.repair(bench.build(*parsed), first.rpartition(TASK_LEAD)[2])
                attempt, percent = build.source, build.percent
                if repairs.renamed:
                    shown = "```cpp\n" + "\n".join(model.decls + [""] + model.func) + "\n```"
                note = repairs.note() + feedback(percent, build.output, address, known, types)
                seen[attempt_key(parsed)] = (tries, note)
                for code in (model, trimmed, build):  # the repaired code counts as this try too
                    seen[attempt_key((code.decls, code.func))] = (tries, note)
                declared_before.update({name: d for d in model.decls for name, _ in line_declarations(d)
                                        if name not in repairs.dropped})
                result = "build failed" if percent is None else f"{percent:.2f}%"
                if percent is None:
                    errors = build_errors(build.output, known)[:10]
                    latest = repairs.latest("did not build:\n```\n" + "\n".join(errors) + "\n```"
                                            + missing_members(types, errors))
                else:
                    latest = repairs.latest(f"scored {percent:.2f}%")
            improved = percent is not None and (best is None or percent > best.percent)
            if improved:
                best = Best(percent, shown, note, attempt)
            failed_build = parsed is not None and repeat is None and percent is None
            stale = 0 if improved else stale + (0 if args.stale_built_only and failed_build else 1)
            totals["repeats"] += repeat is not None
            temperature = (round(min(temperature + TEMPERATURE_STEP, TEMPERATURE_MAX), 2) if repeat is not None
                           else config["temperature"])
            log.write(json.dumps({"try": tries, "thinking": thinking, "result": result,
                                  "seconds": round(time.time() - asked, 1), "usage": reply.usage,
                                  "finish": reply.finish, "reasoning": reply.reasoning, "reply": reply.text,
                                  "note": note, **repairs.logged()}) + "\n")
            log.flush()
            cut = " (the reply hit max_tokens)" if reply.finish == "length" else ""
            print(f"{hexa(address)} try {tries}{' (thinking)' if thinking else ''}: {result}{repairs.trim()}{cut}",
                  flush=True)
            if percent == 100:
                break
            if args.max_repeats is not None and totals["repeats"] >= args.max_repeats:
                break
            best_percent = best.percent if best else 0.0
            if args.give_up and (stale >= GIVE_UP_STALE or (stale >= STUCK_TRIES and best_percent < GIVE_UP_BELOW)):
                break
            if args.stop_below is not None and tries >= STOP_AFTER and best_percent < args.stop_below:
                break
            if args.think_max is not None and thinks(stale, config) and (totals["think_tries"] >= args.think_max
                                                                         or (thinking and repeat is not None)):
                break
            messages = base + next_turn(best, improved, shown, note, latest)
    write_source(path, best.text if best else before, crlf)
    restore(generated)
    decls(config)
    return {"tries": tries, "best": best.percent if best else 0.0, "wall_s": time.time() - started, **totals}


def log_result(path, file, address, size, result, model):
    new = not path.exists()
    with open(path, "a", encoding="utf-8", newline="") as out:
        writer = csv.writer(out, delimiter="\t")
        if new:
            writer.writerow(RESULT_FIELDS)
        writer.writerow([file, hexa(address), size, result["tries"], f"{result['best']:.2f}",
                         f"{result['wall_s']:.1f}", result["prompt_tokens"], result["completion_tokens"], model,
                         result["think_tries"], result["repeats"]])


def solve_and_log(args, file, address, size):
    folder = OUT / args.tag
    results = folder / "results.tsv"
    if results.exists() and results.read_text(encoding="utf-8").splitlines()[0].split("\t") != RESULT_FIELDS:
        sys.exit(f"{results} has other columns than {RESULT_FIELDS}: log to another tag")
    result = solve_function(args, file, address, folder / "transcripts" / f"{address:08x}.jsonl")
    log_result(results, file, address, size, result, args.settings["model"])
    print(f"{hexa(address)}: best {result['best']:.2f}% in {result['tries']} tries "
          f"({result['think_tries']} thinking), {result['wall_s']:.0f}s", flush=True)


def solve(args):
    file = (ROOT / args.file).resolve().relative_to(ROOT.resolve()).as_posix()
    sizes = {f["address"]: f["size"] for f in progress.load_functions()}
    unknown = [hexa(a) for a in args.addresses if a not in sizes]
    if unknown:
        sys.exit(f"not a function in data/functions.csv: {' '.join(unknown)}")
    llmclient.ensure_server(args.settings, SERVER_LOG)
    for address in sorted(args.addresses):
        solve_and_log(args, file, address, sizes[address])
    return 0


def ladder(per_bucket):
    """PER_BUCKET matched functions of each size bucket, spread evenly over the bucket in address order."""
    sizes = {f["address"]: f["size"] for f in progress.load_functions()}
    where = definitions([ROOT])
    done = matched_functions()
    pool = sorted(a for a in done if a in where and a in sizes)
    chosen = []
    for name, _ in BUCKETS:
        in_bucket = [a for a in pool if bucket(sizes[a]) == name]
        count = min(per_bucket, len(in_bucket))
        chosen += [in_bucket[i * len(in_bucket) // count] for i in range(count)]
    return [{"file": where[a][1], "address": hexa(a), "size": str(sizes[a]), "name": done[a]} for a in chosen]


def write_set(path, rows):
    path.parent.mkdir(parents=True, exist_ok=True)
    with open(path, "w", encoding="utf-8", newline="") as out:
        writer = csv.DictWriter(out, SET_FIELDS, delimiter="\t", extrasaction="ignore")
        writer.writeheader()
        writer.writerows(rows)


def bench(args):
    folder = OUT / args.tag
    saved_set = folder / "set.tsv"
    if args.set:
        rows, source = names.table_rows(args.set), args.set
    elif saved_set.exists():
        rows, source = names.table_rows(saved_set), saved_set
    else:
        rows, source = ladder(args.ladder), f"--ladder {args.ladder}"
    files = sorted({r["file"] for r in rows})
    # The second column of a status line is what git does not hold: an unstaged change or an untracked file.
    dirty = [line for line in ci.git("status", "--porcelain", "--", *files).splitlines() if line[1] != " "]
    if dirty:
        sys.exit("bench puts each file back from a copy, and git restores it after a hard kill, "
                 "so stage (git add) or commit these first:\n" + "\n".join(dirty))
    if not args.set or Path(args.set).resolve() != saved_set.resolve():
        write_set(saved_set, rows)
    print(f"bench: {len(rows)} functions from {source}, tag {args.tag}", flush=True)
    llmclient.ensure_server(args.settings, SERVER_LOG)
    results = folder / "results.tsv"
    done = {int(r["address"], 16) for r in names.table_rows(results)} if results.exists() else set()
    matched = matched_functions()
    for row in rows:
        address = int(row["address"], 16)
        if address in done:
            continue
        path = ROOT / row["file"]
        saved = snapshot([path, *generated_files()])
        try:
            text, crlf = read_source(path)
            unmatched = [a for kind, a, _ in names.parse_annotations(text) if kind == "FUNCTION" and a not in matched]
            write_source(path, stub_functions(text, [address, *unmatched]), crlf)
            solve_and_log(args, row["file"], address, row["size"])
        finally:
            restore(saved)
    return report(args.tag)


def report(tag):
    tags = [tag] if tag else sorted(p.name for p in OUT.glob("*") if (p / "results.tsv").exists())
    if not tags or not (OUT / tags[0] / "results.tsv").exists():
        sys.exit("no results yet")
    for t in tags:
        rows = list({r["address"]: r for r in names.table_rows(OUT / t / "results.tsv")}.values())
        best = [float(r["best"]) for r in rows]
        tokens = sum(int(r["prompt_tokens"]) + int(r["completion_tokens"]) for r in rows)
        print(f"{t}: functions tried {len(rows)}, matched at 100% {sum(1 for b in best if b == 100)}, "
              f"mean best score {sum(best) / len(rows):.2f}%, mean tries {sum(int(r['tries']) for r in rows) / len(rows):.2f}, "
              f"total tokens {tokens}, wall time {sum(float(r['wall_s']) for r in rows):.0f}s, "
              f"thinking tries {sum(int(r['think_tries']) for r in rows)}, repeats {sum(int(r['repeats']) for r in rows)}")
    return 0


def system_prompt(name):
    game = project.game_config()
    text = (PROMPTS / f"{name}.txt").read_text(encoding="utf-8").strip()
    text = text.replace("{target}", game.target).replace("{exe}", game.filename)
    if HINTS.exists():
        text += "\n\n" + HINTS.read_text(encoding="utf-8").strip()
    return text


def parse_args():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    common = argparse.ArgumentParser(add_help=False)
    common.add_argument("--config", type=Path, default=CONFIG, help="the config file (default: llm.json)")
    runs = argparse.ArgumentParser(add_help=False, parents=[common])
    runs.add_argument("--prompt", default="v2", choices=sorted(p.stem for p in PROMPTS.glob("*.txt")))
    runs.add_argument("--tries", type=osutil.positive_int, default=10)
    runs.add_argument("--seed", type=int, help="try N asks with seed S+N, so a rerun repeats")
    runs.add_argument("--structs", action="store_true", help="show the members of the structs the dossier names")
    runs.add_argument("--accesses", action="store_true", help="show how the whole exe reads and writes each global")
    runs.add_argument("--facts", action="store_true",
                      help="add what the assembly hides to each dossier: calling convention, pointer globals, "
                           "structs without members")
    for sampler, kind in (("--top-k", int), ("--top-p", float), ("--min-p", float)):
        runs.add_argument(sampler, type=kind, help="sent with every request (default: the server's own)")
    runs.add_argument("--tree-wins", action="store_true",
                      help="build a try once more without the declarations that clash with the tree")
    runs.add_argument("--think-max", type=int, help="end a run when it would think after N thinking tries")
    runs.add_argument("--max-repeats", type=int, help="end a run after N tries that repeated an earlier try")
    runs.add_argument("--give-up", action="store_true", help="end a run that stopped getting better")
    runs.add_argument("--stop-below", type=float, metavar="P",
                      help=f"end a run after {STOP_AFTER} tries when the best is below P%% or nothing built")
    runs.add_argument("--try-tokens", type=osutil.positive_ints, metavar="N,N,...",
                      help="the reply limit of each try in turn, the last one for the tries after it")
    runs.add_argument("--stale-built-only", action="store_true",
                      help="a try that does not build does not count toward thinking")
    runs.add_argument("--tag", help="results go to build/llm/TAG (default: the prompt's name)")
    commands = parser.add_subparsers(dest="command", required=True)
    init = commands.add_parser("init", parents=[common])
    init.add_argument("--url", help="the URL before /chat/completions, such as http://127.0.0.1:8080/v1")
    init.add_argument("--key-env", help="the environment variable that holds the API key")
    init.add_argument("--model", help="the model name, when the server lists several")
    init.add_argument("--start", help="the command that starts the server, when nothing answers")
    solve_command = commands.add_parser("solve", parents=[runs])
    solve_command.add_argument("file", help="the source file, such as src/main.c")
    solve_command.add_argument("addresses", nargs="+", type=lambda value: int(value, 16), help="e.g. 0x00401000")
    bench_command = commands.add_parser("bench", parents=[runs])
    bench_command.set_defaults(seed=1)
    chosen = bench_command.add_mutually_exclusive_group()
    chosen.add_argument("--set", type=Path, help="a tab-separated file with file, address and size columns")
    chosen.add_argument("--ladder", type=int, default=LADDER, help="matched functions per size bucket")
    commands.add_parser("report").add_argument("--tag")
    return parser.parse_args()


def main():
    args = parse_args()
    if args.command == "report":
        return report(args.tag)
    if args.command == "init":
        return llmclient.init(args.config, args.url, args.key_env, args.model, args.start, SERVER_LOG)
    args.settings = llmclient.load(args.config)
    samplers = {"top_k": args.top_k, "top_p": args.top_p, "min_p": args.min_p}
    args.settings["extra_body"] = {**args.settings["extra_body"], **{k: v for k, v in samplers.items() if v is not None}}
    args.tag = args.tag or args.prompt
    args.system = system_prompt(args.prompt)  # once, so an edit mid-run changes nothing
    if args.structs:
        args.system += "\n\n" + STRUCTS_RULE
    if args.seed is not None and not args.settings["seed"]:
        print(f"{args.config} says the server does not repeat a reply for a seed: this run will not repeat.")
    try:
        return solve(args) if args.command == "solve" else bench(args)
    except llmclient.ServerError as e:
        sys.exit(str(e))


if __name__ == "__main__":
    check.rerun_in_venv(__file__)
    sys.exit(main())
