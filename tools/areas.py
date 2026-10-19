"""Sort the game's functions into areas, such as a stage, a character or the menus: `check.py areas`.

data/areas.yml holds the game's rules. A function in a source file under src/ takes the area of the file's path,
by the `tree` lines: that area is exact. For every other function, `check.py areas` guesses an area from the exe
alone and writes the guess to data/areas.csv, with its evidence. A function with neither is not sorted yet.

The guess, in this order:
1. Seeds. The stage object lists and stage tables, the other function tables, class names, source paths and
   strings each name the area of some functions. A function that two of them place in different areas gets
   no seed.
2. Code groups. A row of data/codegen-groups.csv is one compile. When GROUP_VOTES seeds lie in a group and all
   agree, the group's other functions take that area. A group is a lower layer of an area when (1) no seed in
   it is of another area, (2) many groups call it, and (3) most of its calls into other groups go to groups
   of that area.
3. Callers. A function whose callers all have one area takes that area, with limits for the `shared` areas.
4. Runs. The linker keeps an area's code together, so a function between two seeds of one area takes it.

Each step's docstring has its limits. Needs capstone, so it runs in .venv.
"""

import collections
import csv
import re
import struct
import sys
from collections.abc import Iterator
from pathlib import Path

import accesses
import codegen
import datafiles
import dossier
import pe
import progress
import project

ROOT = project.ROOT
RULES = ROOT / "data" / "areas.yml"
AREAS_CSV = ROOT / "data" / "areas.csv"
UNPLACED = "src/unplaced/"  # functions whose file is not known yet
UNSORTED = "unsorted"
Edges = dict[int, dict[int, set[str]]]  # function -> {caller: kinds of reference}

MAX_STRING = 64  # bytes read for a string, NUL included: a longer string reads as empty
MIN_TEXT = 3  # characters a string needs to name an area
STRING_HOPS = 2  # pointer hops from the data a function uses to a string that names its area
STRUCT_WORDS = 16  # words of a record searched for pointers on each hop
TABLE_LINKS = 64  # the most function pointers a data table may link to the code that reads it
MIN_TABLE = 2  # the fewest function pointers in a row that make a table
GROUP_VOTES = 5  # seeds a code group needs, all of one area, before the whole group takes that area
LAYER_EDGES = 20  # calls a seedless group must make to other groups before it can count as a library's layer
LAYER_SHARE = 0.9  # share of those calls that must go to groups of one area
LAYER_CALLERS = 5  # other groups that must call it, so it is a layer under them and not a leaf
SPREAD_NEAR = 0x1000  # a function takes a shared area from its callers only when one of them is this close
API_CALLERS = 8  # direct callers, all of one area, that make a function that area's own API from any group
DIVERSE_AREAS = 3  # areas calling one function that make it shared code
ZONE_WINDOW = 5  # functions on each side searched for shared code
ZONE_DIVERSE = 2  # shared-code functions in that window that make a zone the callers rule may not enter
OUTLIER_WINDOW = 25  # seeds on each side searched for a seed of the same area
VETO_AREAS = 2  # other areas calling a function that stop the runs rule from labelling it
SHARED_GAP = 16  # the longest gap the runs rule closes between two seeds of a shared area, about two files


class Data:
    """The words and strings of the exe's data sections, by address."""

    def __init__(self, image: pe.Image):
        self.image = image
        self.words = {}  # section start -> (end, the section's words)
        for start, _, section in image.sections:
            if section.flags & pe.CODE or section.name == ".rsrc":  # resources hold no pointers the code follows
                continue
            raw = image.contents(section)
            self.words[start] = (start + len(raw) // 4 * 4, struct.unpack_from(f"<{len(raw) // 4}I", raw))
        self.low = min(self.words)
        self.high = max(end for end, _ in self.words.values())

    def in_data_span(self, address: int) -> bool:
        """True from the lowest data section to the end of the highest, gaps between them included."""
        return self.low <= address < self.high

    def dwords(self, address: int, count: int) -> tuple[int, ...]:
        for start, (end, words) in self.words.items():
            if start <= address < end and address % 4 == 0:
                index = (address - start) // 4
                return words[index:index + count]
        return ()

    def terminated(self, address: int) -> bytes:
        """The bytes at the address up to the NUL, or b"" if no NUL lies within MAX_STRING bytes."""
        raw = self.image.read(address, MAX_STRING)
        end = raw.find(b"\0")
        return raw[:end] if end >= 0 else b""

    def c_string(self, address: int) -> str:
        """The string at the address, or "" if it is empty or MAX_STRING bytes or longer."""
        return self.terminated(address).decode("ascii", "replace")

    def printable_string(self, address: int) -> str:
        """The string at the address, or "" if it has fewer than MIN_TEXT characters, holds a byte outside
        ASCII text, or is MAX_STRING bytes or longer."""
        raw = self.terminated(address)
        if len(raw) < MIN_TEXT or not all(32 <= c < 127 for c in raw):
            return ""
        return raw.decode("ascii")


def tree_areas(rules: dict) -> dict[int, tuple[str, str]]:
    """address -> (area, file) for the FUNCTION, TEMPLATE and SYNTHETIC annotations under src/, except in
    src/unplaced/. Stops at a file that no tree line matches."""
    lines = [(re.compile(pattern), area) for pattern, area in rules["tree"]]
    found = {}
    for path in sorted((ROOT / "src").rglob("*")):
        source = path.relative_to(ROOT).as_posix()
        if path.suffix not in (".c", ".cpp") or source.startswith(UNPLACED):
            continue
        addresses = codegen.function_marker().findall(codegen.read_source(path))
        if not addresses:
            continue
        area = next((area for pattern, area in lines if pattern.search(source)), None)
        if area is None:
            sys.exit(f"{source}: no tree line in {RULES.relative_to(ROOT).as_posix()} matches it. "
                     "Add one for its folder.")
        for address in addresses:
            found[int(address, 16)] = (area, source)
    return found


def object_lists(data: Data, game: set[int], lists: dict) -> list[tuple[int, str, int]]:
    """(stage, name, function) for each entry of each stage's object lists that is a game function."""
    entries = []
    words = lists["entry"] // 4
    for slot, header in enumerate(data.dwords(lists["address"], lists["stages"] * lists["acts"])):
        pair = data.dwords(header, 2)
        if len(pair) < 2:
            continue
        count, first = pair
        listed = data.dwords(first, count * words)
        for i in range(0, len(listed), words):
            function, name = listed[i + lists["code"] // 4], listed[i + lists["name"] // 4]
            if function in game:
                entries.append((slot // lists["acts"], data.c_string(name), function))
    return entries


def data_uses(image: pe.Image, game: set[int]) -> dict[int, set[int]]:
    """function -> the data addresses it reads, writes or takes."""
    uses = collections.defaultdict(set)
    for access in accesses.load(image):
        for function in access.functions:
            if function in game:
                uses[function].add(access.target)
    return uses


def strings_used(data: Data, targets: set[int]) -> set[str]:
    """The printable strings within STRING_HOPS pointer hops of the data a function uses."""
    found, seen, frontier = set(), set(), list(targets)
    for _ in range(STRING_HOPS + 1):
        following = []
        for p in frontier:
            if p in seen or not data.in_data_span(p):
                continue
            seen.add(p)
            text = data.printable_string(p)
            if text:
                found.add(text)
                continue
            following += [w for w in data.dwords(p, STRUCT_WORDS) if data.in_data_span(w)]
        frontier = following
    return found


def function_run(data: Data, game: set[int], address: int) -> list[int]:
    """The game functions in the words from the address, up to the first word that is not one."""
    run = []
    for w in data.dwords(address, TABLE_LINKS + 1):
        if w not in game:
            break
        run.append(w)
    return run


def table_links(data: Data, game: set[int], uses: dict[int, set[int]]) -> dict[int, set[int]]:
    """function -> the functions in a pointer table it uses, when the table holds MIN_TABLE to TABLE_LINKS."""
    links = {}
    for function, targets in uses.items():
        linked = set()
        for target in targets:
            run = function_run(data, game, target)
            if MIN_TABLE <= len(run) <= TABLE_LINKS:
                linked.update(run)
        if linked:
            links[function] = linked
    return links


def table_entries(data: Data, table: dict) -> list[int]:
    """The functions in a table: every stride bytes, the word itself, or with hops 1 the first word of the
    record it points to."""
    step = table["stride"] // 4
    entries = list(data.dwords(table["address"], table["entries"] * step)[::step])
    for _ in range(table.get("hops", 0)):
        entries = [(data.dwords(w, 1) or (0,))[0] for w in entries]
    return entries


def object_list_seeds(data: Data, game: set[int], rules: dict) -> Iterator[tuple[int, str, str]]:
    """(function, area, why) for each game function in a stage's object lists."""
    stages = rules["stages"]
    lists = rules["object_lists"]
    stages_of = collections.defaultdict(set)
    names = collections.defaultdict(set)
    for stage, name, function in object_lists(data, game, lists):
        if stage in stages:
            stages_of[function].add(stages[stage])
            names[function].add(name.strip())
    for function, areas in stages_of.items():
        named = [(line, name) for line in rules["object_names"]
                 for name in sorted(names[function]) if re.search(line["name"], name)]
        if named:
            line, name = named[0]
            if len(areas) < line.get("stages", 1):
                continue
            area = line["area"]
        else:
            name = min(names[function])
            area = next(iter(areas)) if len(areas) == 1 else lists["several"]
        yield function, area, f"object list {name!r}"


def stage_table_seeds(data: Data, rules: dict) -> Iterator[tuple[int, str, str]]:
    """(function, area, why) for each function in a table with one entry per stage."""
    stages = rules["stages"]
    for table in rules["stage_tables"]:
        for stage, function in enumerate(data.dwords(table, max(stages) + 1)):
            if stage in stages:
                yield function, stages[stage], f"stage table 0x{table:08x}[{stage}]"


def table_seeds(data: Data, rules: dict) -> Iterator[tuple[int, str, str]]:
    """(function, area, why) for each function in the other function tables."""
    for table in rules["tables"]:
        areas = table["areas"]
        for i, function in enumerate(table_entries(data, table)):
            yield function, areas[i] if len(areas) > 1 else areas[0], table["what"]


def class_seeds(rules: dict) -> Iterator[tuple[int, str, str]]:
    """(function, area, why) for the methods and users of each class whose name a rule matches."""
    for row in progress.read_csv(datafiles.CLASSES_CSV):
        for area, pattern in rules["classes"]:
            if re.search(pattern, row["class"]):
                for function in (row["methods"] + " " + row["users"]).split():
                    yield int(function, 16), area, f"class {row['class']}"


def path_seeds(rules: dict) -> Iterator[tuple[int, str, str]]:
    """(function, area, why) for each function whose source path a rule matches."""
    for row in progress.read_csv(datafiles.SOURCE_FILES_CSV):
        for area, pattern in rules["sources"]:
            if re.search(pattern, row["file"]):
                yield int(row["function"], 16), area, f"path {row['file']}"


def string_seeds(data: Data, uses: dict[int, set[int]], rules: dict) -> Iterator[tuple[int, str, str]]:
    """(function, area, why) for each function that uses a string a rule matches."""
    strings = [(area, re.compile(pattern)) for area, pattern in rules["strings"]]
    for function, targets in uses.items():
        for text in sorted(strings_used(data, targets)):
            for area, regex in strings:
                if regex.search(text):
                    yield function, area, f"string {text!r}"


def seeds(data: Data, game: set[int], uses: dict[int, set[int]], rules: dict) -> dict[int, tuple[str, str]]:
    """function -> (area, why). A function two rules disagree on gets no seed."""
    claims = collections.defaultdict(dict)  # function -> area -> why
    for source in (object_list_seeds(data, game, rules), stage_table_seeds(data, rules),
                   table_seeds(data, rules), class_seeds(rules), path_seeds(rules),
                   string_seeds(data, uses, rules)):
        for function, area, why in source:
            if function in game:
                claims[function].setdefault(area, why)
    return {f: next(iter(c.items())) for f, c in claims.items() if len(c) == 1}


def typed_edges(game: set[int], callers: dict[int, list[tuple[int, str]]], links: dict[int, set[int]]) -> Edges:
    """function -> {caller: kinds}: the game functions that call it, jump to it, take its address ("ref") or
    read it from a table ("table")."""
    edges = collections.defaultdict(lambda: collections.defaultdict(set))
    for target, listed in callers.items():
        for caller, kind in listed:
            if target in game and caller in game and caller != target:
                edges[target][caller].add(kind)
    for reader, table in links.items():
        for entry in table - {reader}:
            edges[entry][reader].add("table")
    return edges


def seed_areas_by_group(group_of: dict[int, int], found: dict) -> dict[int, collections.Counter]:
    """code group -> its seeds' areas, each with the number of seeds."""
    seed_areas = collections.defaultdict(collections.Counter)
    for a, (area, _) in found.items():
        seed_areas[group_of[a]][area] += 1
    return seed_areas


def group_votes(seed_areas: dict[int, collections.Counter]) -> dict[int, tuple[str, str]]:
    """A code group is one compile. When GROUP_VOTES or more seeds lie in it and all agree, the group is that
    area's own code, so its other functions take the area."""
    won = {g: next(iter(c)) for g, c in seed_areas.items() if len(c) == 1 and sum(c.values()) >= GROUP_VOTES}
    return {g: (area, f"code group 0x{g:08x}: all {sum(seed_areas[g].values())} seeds in it say {area}")
            for g, area in won.items()}


def group_calls(group_of: dict[int, int], edges: Edges) -> tuple[dict, dict]:
    """(group -> {group it calls: edges}, group -> the groups that call it), for calls between groups."""
    calls = collections.defaultdict(collections.Counter)
    called_by = collections.defaultdict(set)
    for target, callers in edges.items():
        for caller in callers:
            if group_of[caller] != group_of[target]:
                calls[group_of[caller]][group_of[target]] += 1
                called_by[group_of[target]].add(group_of[caller])
    return calls, called_by


def layer_area(g: int, calls: dict, called_by: dict, labels: dict[int, str],
               seed_areas: dict[int, collections.Counter]) -> tuple[str, int] | None:
    """(area, calls into it) when group g is a lower layer of that area, else None."""
    total = sum(calls[g].values())
    votes = collections.Counter()
    for target, n in calls[g].items():
        if target in labels:
            votes[labels[target]] += n
    if total < LAYER_EDGES or not votes or len(called_by[g]) < LAYER_CALLERS:
        return None
    area, n = votes.most_common(1)[0]
    if n / total >= LAYER_SHARE and set(seed_areas[g]) <= {area}:
        return area, n
    return None


def library_layers(group_of: dict[int, int], edges: Edges, seed_areas: dict[int, collections.Counter],
                   won: dict) -> dict[int, tuple[str, str]]:
    """A group is a lower layer of an area when (1) no seed in it is of another area, (2) at least
    LAYER_CALLERS other groups call it, (3) it makes at least LAYER_EDGES calls into other groups, and
    (4) at least LAYER_SHARE of those calls go to groups of that area. The groups in `won` count as labelled."""
    calls, called_by = group_calls(group_of, edges)
    labels = {g: area for g, (area, _) in won.items()}
    layers = {}
    groups = sorted(set(group_of.values()))
    changed = True
    while changed:
        changed = False
        for g in groups:
            if g in labels:
                continue
            layer = layer_area(g, calls, called_by, labels, seed_areas)
            if layer:
                area, n = layer
                labels[g] = area
                layers[g] = (area, f"code group 0x{g:08x}: {n} of its {sum(calls[g].values())} calls go into "
                                   f"{area}, and {len(called_by[g])} groups call it")
                changed = True
    return layers


def shared_zone(order: list[int], edges: Edges, labels: dict[int, str]) -> set[int]:
    """Functions near code that DIVERSE_AREAS different areas call. Such code is shared, so one caller's area
    says nothing about it."""
    diverse = [len({labels[c] for c in edges[a] if c in labels}) >= DIVERSE_AREAS for a in order]
    zone = set()
    for i, a in enumerate(order):
        if sum(diverse[max(0, i - ZONE_WINDOW):i + ZONE_WINDOW + 1]) >= ZONE_DIVERSE:
            zone.add(a)
    return zone


def spread(labels: dict[int, str], edges: Edges, group_of: dict[int, int], zone: set[int],
           rules: dict) -> tuple[dict[int, str], dict[int, str]]:
    """Until nothing changes, a function whose callers all have one area takes that area, in two cases:
    - It has API_CALLERS or more direct callers. The callers may lie in any group.
    - (1) It lies outside the shared zone, (2) its callers are all in its code group, and (3) for a shared area,
      a caller sits within SPREAD_NEAR or calls it directly and the area is a `direct` area."""
    labels = dict(labels)
    why = {}
    changed = True
    while changed:
        changed = False
        for function, callers in edges.items():
            if function in labels:
                continue
            areas = {labels.get(c) for c in callers}
            if len(areas) != 1 or None in areas:
                continue
            area = next(iter(areas))
            direct_callers = [c for c, kinds in callers.items() if kinds & {"call", "jmp"}]
            if len(direct_callers) >= API_CALLERS:
                labels[function] = area
                why[function] = f"called directly by {len(direct_callers)} {area} functions"
                changed = True
                continue
            crosses_groups = any(group_of[c] != group_of[function] for c in callers)
            if function in zone or crosses_groups:
                continue
            near = min(abs(c - function) for c in callers) < SPREAD_NEAR
            reached_directly = bool(direct_callers) and area in rules["direct"]
            allowed = near or reached_directly
            if area in rules["shared"] and not allowed:
                continue
            labels[function] = area
            why[function] = "only called from " + area
            changed = True
    return labels, why


def run_ends(order: list[int], labels: dict[int, str], shared: set[str]) -> list[int]:
    """The labelled functions that can end a run. An outlier ends no run. A label is an outlier when (1) its area
    is not shared, (2) no label within OUTLIER_WINDOW labels on either side has its area, and (3) the labels just
    before and after it have one other area."""
    labelled = [a for a in order if a in labels]
    ends = []
    for i, a in enumerate(labelled):
        area = labels[a]
        near = labelled[max(0, i - OUTLIER_WINDOW):i] + labelled[i + 1:i + 1 + OUTLIER_WINDOW]
        lone = area not in shared and not any(labels[b] == area for b in near)
        between_others = 0 < i < len(labelled) - 1 and labels[labelled[i - 1]] == labels[labelled[i + 1]] != area
        if not (lone and between_others):
            ends.append(a)
    return ends


def runs(order: list[int], group_of: dict[int, int], edges: Edges, labels: dict[int, str],
         rules: dict) -> dict[int, tuple[str, str]]:
    """Link order keeps an area's code in runs. A function takes an area when (1) it lies between two ends of
    that area from run_ends, (2) both ends are in one code group, and (3) fewer than VETO_AREAS other areas
    call it. A shared area's code can sit inside another area's run, so for a shared area the gap may hold at
    most SHARED_GAP functions."""
    shared = set(rules["shared"])
    ends = run_ends(order, labels, shared)
    position = {a: i for i, a in enumerate(order)}
    found = {}
    for left, right in zip(ends, ends[1:]):
        area = labels[left]
        if labels[right] != area or group_of[left] != group_of[right]:
            continue
        if area in shared and position[right] - position[left] - 1 > SHARED_GAP:
            continue
        for a in order[position[left] + 1:position[right]]:
            if a in labels:
                continue
            others = {labels[c] for c in edges[a] if c in labels and labels[c] != area}
            if len(others) < VETO_AREAS:
                found[a] = (area, f"between {area} functions 0x{left:08x} and 0x{right:08x}")
    return found


def guess(image: pe.Image, rules: dict) -> tuple[list[int], dict[int, tuple[str, str]]]:
    """The game functions in address order, and (area, why) for each one the exe places."""
    functions = progress.load_functions()
    groups = progress.load_codegen_groups()
    game = progress.game_addresses(functions, groups)
    order = sorted(game)
    group_of = {a: progress.codegen_group(groups, a)["start"] for a in order}
    data = Data(image)
    uses = data_uses(image, game)
    found = seeds(data, game, uses, rules)
    callers = dossier.read_callers(image, {f["address"]: f["size"] for f in functions})
    edges = typed_edges(game, callers, table_links(data, game, uses))
    seed_areas = seed_areas_by_group(group_of, found)
    won = group_votes(seed_areas)
    won.update(library_layers(group_of, edges, seed_areas, won))
    for a in order:
        if a not in found and group_of[a] in won:
            found[a] = won[group_of[a]]
    labels = {a: area for a, (area, _) in found.items()}
    labels, why = spread(labels, edges, group_of, shared_zone(order, edges, labels), rules)
    found.update({a: (labels[a], w) for a, w in why.items()})
    found.update(runs(order, group_of, edges, labels, rules))
    return order, found


def check_rules(rules: dict) -> None:
    """Exit when `shared` or `direct` names an area the `map` list lacks, or a `tables` entry has neither one
    area nor one area per entry."""
    where = RULES.relative_to(ROOT).as_posix()
    named = {area for entry in rules["map"] for area in entry["areas"]}
    for key in ("shared", "direct"):
        unknown = sorted(set(rules[key]) - named)
        if unknown:
            sys.exit(f"{where}: the `{key}` list names {', '.join(unknown)}, which the `map` list does not.")
    for table in rules["tables"]:
        if len(table["areas"]) not in (1, table["entries"]):
            sys.exit(f"{where}: the `tables` entry {table['what']!r} has {len(table['areas'])} areas for "
                     f"{table['entries']} entries. Give one area, or one per entry.")


def report(order: list[int], found: dict[int, tuple[str, str]], tree: dict[int, tuple[str, str]]) -> None:
    """Print how the tree and the guess sort the game's functions, and each file whose tree line the guess
    disputes."""
    in_tree = sum(a in tree for a in order)
    guessed = sum(a in found and a not in tree for a in order)
    unsorted = len(order) - in_tree - guessed
    print(f"     {AREAS_CSV.relative_to(ROOT).as_posix()}: the exe places {len(found)} of {len(order)} game functions")
    print(f"     {in_tree} sorted by their file, {guessed} by the guess, {unsorted} not sorted yet")
    files = collections.defaultdict(collections.Counter)  # file -> what the guess says of its functions
    for a, (area, source) in tree.items():
        if a in found:
            files[(source, area)][found[a][0]] += 1
    for (source, area), said in sorted(files.items()):
        most, n = said.most_common(1)[0]
        if most != area:
            print(f"note {source} is {area} by its tree line, but the guess says {most} for {n} of its functions")


def write(game: Path) -> int:
    """Write the exe's guess to data/areas.csv, and print how the tree and the guess sort the game's functions."""
    if not RULES.exists():
        sys.exit(f"{RULES.relative_to(ROOT).as_posix()} is missing: it holds the game's area rules.")
    rules = project.read_yml(RULES)
    check_rules(rules)
    tree = tree_areas(rules)
    order, found = guess(pe.Image(game), rules)
    with AREAS_CSV.open("w", encoding="utf-8", newline="") as out:
        writer = csv.writer(out, lineterminator="\n")
        writer.writerow(["address", "area", "why"])
        for a in order:
            area, why = found.get(a, (UNSORTED, ""))
            writer.writerow([f"0x{a:08x}", area, why])
    report(order, found, tree)
    return 0
