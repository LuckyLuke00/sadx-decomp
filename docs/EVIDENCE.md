# The evidence tool

`tools/evidence/` lists the spots in the game source that may hide an original name:

- a bare number that may stand for a name from a header or from the symbol dump of a reference build, such as `xxPush(0)` for `xxPush(NULL)` or `p->flags = 0x10` for a flag name;
- a literal that may be a macro;
- a placeholder macro that stands for code with no name yet, such as a guessed assert.

Each spot gets a stable id, its candidate names, its evidence and its counterevidence, and a tier. A tier is a review priority. It is not a probability, and it is not permission to rename. The tool changes no source file. A name goes into the tree only after a person confirms it.

The tool is generic. A game plugs in its own headers, sample code and other material through a local folder that git ignores. Standard library only.

## Setup

1. Make the folder `evidence/` at the repo root. The framework `.gitignore` ignores it.
2. Write the hand-owned files in it: `config.json`, `argmap.csv`, `expected-names.csv` and `denylist.txt`, and optionally `fieldmap.csv` and `probes.csv` (see [Files](#files)). If a reference build has a program database, run `pdbimport` on it to write the [symbol files](#symbol-files) in it. For another kind of symbol dump, let a local adapter write them. If other builds of the game have functions paired with the game's, let a local adapter write their [reference call files](#reference-call-files) in it.
3. Run `audit`. It must pass before you publish anything.
4. If an earlier inventory exists, run `import-baseline PATH` once.
5. Run `run`.
6. Read `confidence.md`. Record each review with `decide`.

A missing hand-owned file stops the run with an error that names it. A run writes only into `evidence/` and the backup folder.

## Commands

Run each command with the venv Python and `-I`:

```bash
.venv/Scripts/python.exe -I tools/evidence/evidence.py run
```

| Command | What it does | Exit code |
| --- | --- | --- |
| `audit` | Checks that no deny-listed word is in what git would publish: the paths and contents of tracked files, untracked files that git does not ignore, and staged versions. It also checks that git ignores `evidence/` and tracks nothing in it. It does not read history or ignored files. Each hit prints `file:line:entry` | 1 on a hit or a fault |
| `run` | The whole run, in order: the inventory of call, field, reference symbol and placeholder sites, the reference calls, the sample corpus, the manuals and the spelling tiers, the ids and the ledger, the baseline diff when a baseline exists, the tiers and the eligibility, the audit and the gate report. It prints the generation, the brake of each kind and the out-of-date outputs | 1 on a fault or when a brake fires |
| `import-baseline PATH` | Copies an earlier `inventory.csv` in as `evidence/baseline-inventory.csv`. Once only | 1 if the file is malformed or a baseline exists |
| `decide ID confirm\|reject\|reopen [--candidate NAME] [--note TEXT]` | Appends one review decision to `notes.csv`. `confirm` and `reject` take the top candidate, unless `--candidate` names another candidate of the row, or a candidate written with other aliases of its names (any order of the terms, the same `~`). `reopen` takes no candidate. The next run reads the decision into the ledger. A gone or ambiguous id gives a warning | 1 on an unknown id, a wrong candidate, a row with no candidate, no ledger yet, or a malformed file |
| `pdbimport FILE [--map MAP.csv]` | Reads a program database and writes the three [symbol files](#symbol-files) into `evidence/`, over any that exist. See [Program database reader](#program-database-reader). It prints what it wrote and what it left out | 1 on a malformed file or map, or on a version or record that the reader does not support |

`tools/evidence/probe.py` makes the compiler fixtures. It is not part of a run. It needs the repo's toolchain in `.toolchain`:

- `probe.py fixtures` compiles the probe cases in C and C++ mode and writes `tools/evidence/probe/vc10-c.json` and `vc10-cpp.json`.
- `probe.py differential [--count N] [--seed S] [--language c|cpp]` compares the evaluator with `cl.exe` on seeded random expressions. It prints each disagreement and writes nothing.

## Tests

Each module has its own test script beside it, `<module>tests.py`. Each script runs on its own and exits 1 on a failure:

```bash
.venv/Scripts/python.exe -I tools/evidence/configtests.py
```

To run all of them:

```bash
for test in tools/evidence/*tests.py; do .venv/Scripts/python.exe -I "$test" || echo "FAILED: $test"; done
```

The tests use made-up names. They write only to temp folders, and they need no `evidence/` folder and no `cl.exe`. `audittests.py` and `pipelinetests.py` need git, because they make a temp repository. `pdbimporttests.py` builds its program databases from bytes. It also reads `build/SELFTEST.pdb` when the self-test target was built, and says that it skips that check when not.

## Files

### Hand-owned

| File | What it holds |
| --- | --- |
| `config.json` | The configuration: the game source, the header sets, the origins, the backups, the thresholds, the sample trees and the placeholder macros |
| `argmap.csv` | Which argument of which callee takes names from which groups |
| `fieldmap.csv` | Optional. Which member of which struct takes names from which groups |
| `probes.csv` | Optional. The yield probes of the modules that a run does not build |
| `expected-names.csv` | Per umbrella header, the names that must resolve. A smoke test for the header reader |
| `denylist.txt` | The words that must not appear in public files |
| `baseline-inventory.csv` | An earlier inventory, after `import-baseline` |
| `notes.csv` | The review decisions per site id, written by `decide` |

### Symbol files

Optional. `pdbimport` or a local adapter writes them from the symbol dump of a reference build: another build of the game, with its own names. A run reads the ones that exist. See [Symbol file schemas](#symbol-file-schemas).

| File | What it holds |
| --- | --- |
| `prototypes.csv` | The return type and the parameter types of the game's functions, as the reference build spells them |
| `enums.csv` | The enumerators of the enums that `prototypes.csv` names |
| `scope-constants.csv` | The enum constants declared inside each function |

### Reference call files

Optional. A local adapter writes two files per reference build NAME: another build of the game, such as a port, whose functions are paired with the game's. A run reads every pair of files that exists. One file without its partner stops the run. See [Reference call file schemas](#reference-call-file-schemas) and [Reference calls](#reference-calls).

| File | What it holds |
| --- | --- |
| `pairs-NAME.csv` | The game function and the reference function of each pair |
| `refcalls-NAME.csv` | The calls of each paired reference function, in order, with their argument values |

### Generated

| File | What it holds |
| --- | --- |
| `high-water.txt` | The number of the highest site id ever minted. It only grows |
| `state/CURRENT` | One line: the number of the live generation |
| `state/<n>/sites.csv` | Generation n's live sites with their ids |
| `state/<n>/ledger.csv` | Generation n's ledger: one row per id ever seen |
| `state/<n>/manifest.json` | The schema, the generation, the high-water mark and the SHA-256 of each file in the folder |
| `inventory.csv` | Every mapped call argument and mapped field spot, in coverage or not, every reference symbol site and every placeholder use |
| `argmap-proposed.csv` | Callees that a vendor header declares and `argmap.csv` does not map, with their literal arguments and what the sample trees pass at that slot |
| `confidence.csv` | One row per coverage site, in review order |
| `candidates.csv` | Every candidate of every coverage site, ranked |
| `confidence.md` | The eligibility rule, the meaning tiers, the spelling of the top candidates, the eligibility per callee, the rollup by target, slot and value, the reference names list, the placeholder list and the baseline diff causes |
| `ledger-changes.md` | What the last run changed in the ledger |
| `gate.md` | The gate report |
| `diagnostics/baseline-diff.csv` | The baseline diff, while a baseline exists |
| `diagnostics/sample-calls.csv` | Every call to a wanted callee in the sample trees, with its value, spelling key and lineage |

The state is one unit. A run writes a new generation folder in full, raises the high-water mark, then replaces `state/CURRENT` in one rename. A run stopped before the rename leaves the old generation live, and the next run deletes the partial folder. A read checks every hash in the manifest, so a hand edit or a torn write fails with a clear error. After a commit, only the live and the previous generation stay.

The other outputs are written after the commit. The first line of each names the generation that wrote it. A file from another generation is out of date, and `run` names it.

### Backups

Each run makes a snapshot in the `backups` folder of `config.json`. A snapshot holds the live state files, the hand-owned files that `kept` lists and `notes.csv` when it exists, because no run can make them again. A run whose files hash the same as the latest snapshot makes none. The newest 10 snapshots stay. `state.restore()` puts a snapshot back as a new generation. It never lowers the high-water mark, so a restored state never reuses an id. No command calls it yet.

## Schemas

A file with a version line fails on any other version.

### `config.json`, schema 2

```text
{
  "schema": 2,
  "sources": {"root": "src", "suffixes": [".c", ".cpp"], "encoding": "utf-8", "annotation": "<regex>"},
  "target": <header set>,
  "references": [<header set>, ...],
  "origins": {"<origin>": ["<folder>", ...], ...},
  "backups": "<folder>",
  "kept": ["config.json", "argmap.csv", ...],
  "thresholds": {"<name>": <number>, ...},
  "samples": {"<sample tree>": {"folders": ["<folder>", ...], "reference": "<reference set>", "encoding": "<codec>"}},
  "manuals": [{"path": "<file>", "reference": "<reference set>", "encoding": "<codec>"}, ...],
  "placeholders": {"<macro>": "no-code" | "code", ...}
}
```

- `schema`, `sources`, `target`, `backups` and `kept` are required. An unknown key is an error.
- The `annotation` regex needs the groups `kind` and `address`. It is matched against each `//` comment of the game source and names each function by its address.
- A header set is `{"name", "profile", "search_path", "predefines", "known_undefined", "umbrellas", "encoding"}`. `name`, `profile`, `search_path` and `umbrellas` are required. Each umbrella gives one closure, read under the named profile. The `target` set is the game's own build. A `references` set is another header source, such as a vendor SDK.
- `known_undefined` lists the names that count as 0 in `#if`. Any other name that is not defined makes the condition unresolved, never 0.
- An umbrella is a file path when that file exists, else a name to find on the search path.
- An origin names the folders whose headers it covers. A name's origin is the origin of the deepest folder that holds its definition.
- Paths are relative to the repo root, or absolute.
- `thresholds` overrides entries of the threshold table below. An unknown entry is an error.
- `samples` is optional. It names the sample trees, such as vendor sample code. All three keys are required. The headers and the profile of the named `references` set evaluate the tree's calls. `encoding` is a Python codec name that decodes the tree's files.
- `manuals` is optional. Each entry is a text dump of a vendor manual. It is read for the functions of the named `references` set. All three keys are required.
- `placeholders` is optional. It lists the game's placeholder macros: `no-code` for a macro that expands to no code, such as a guessed assert, and `code` for a macro that stands for code the decomp could not name yet. Each use is a placeholder site.

The configuration hash covers every header set in order, the sample trees, the manuals, the placeholder macros, the threshold table, `RULES_VERSION`, the schema and the hash of the tool's `.py` sources (tests excluded). It is part of every ledger fingerprint. So a change to any tool source updates `last_checked` on every ledger row.

### Thresholds

These are the code defaults, in `config.THRESHOLDS`. `configtests.py` checks that this table equals them.

<!-- thresholds -->
| Name | Default | What it sets |
| --- | --- | --- |
| `cover_budget` | 128 | Lookups and composite walk visits per cover search |
| `branch_cap` | 8 | Alternatives that one macro name keeps. A name with more is unresolved |
| `remap_exact` | 10 | Alignment score of an exact pair |
| `remap_rewrite` | 3 | Alignment score of a rewrite pair |
| `remap_target` | 3 | Alignment score of a target pair |
| `gate_brake` | 0.30 | Share of unresolved plus unevaluated coverage sites that fires the brake |
| `shingle_size` | 5 | Tokens per shingle when sample files are compared for lineage |
| `lineage_cut` | 0.5 | Jaccard similarity at which two sample files share a lineage (complete linkage) |
| `lineage_min_shingles` | 50 | A file with fewer shingles shares a lineage only with files that have its relative path |
| `spell_a_clusters` | 5 | Spelling A: the lineage clusters that pass the value, at least |
| `spell_a_share` | 0.9 | Spelling A: this alias's share of the named weight, at least |
| `spell_a_literal` | 0.1 | Spelling A: the literal share of all clusters, at most |
| `spell_b_clusters` | 3 | Spelling B: the lineage clusters that pass the value, at least |
| `spell_b_share` | 0.5 | Spelling B: this alias's share of the named weight, at least |
| `spell_b_literal` | 0.3 | Spelling B: the literal share of all clusters, at most |
| `spell_combo` | 2 | Spelling A of a combination of names: the clusters that spell that exact combination, at least |
| `composite_terms` | 4 | The most names in a composite cover, with one multi-bit name at least |
| `yield_floor` | 20 | A module whose yield probe finds fewer sites stays out, with the count in gate.md |
| `scope_min_values` | 3 | The lvalue check: the distinct values that one lvalue takes in a function, all constants of one scope, at least |
| `pair_min_sites` | 3 | The kill switch of a paired function: the compared slots whose value both builds know, at least |
| `pair_min_rate` | 0.5 | The kill switch of a paired function: the share of those slots with the same value, at least |
<!-- /thresholds -->

### Compiler profiles

A profile is a named, versioned object for one compiler, target and language. It gives the type sizes, the literal typing, what folding does at the edges, the `#if` width, the compiler's own predefines, the boolean type names and the tokens that header reading drops. A case with no rule gives "unsupported". The evaluator never guesses.

| Profile | Version | Provenance |
| --- | --- | --- |
| `msvc-vc10-x86-cpp` | 1 | The VC10 probe, C++ mode (`probe/vc10-cpp.json`) |
| `msvc-vc10-x86-c` | 1 | The VC10 probe, C mode (`probe/vc10-c.json`) |
| `shc-c` | 1 | Not probed and not checked against the compiler manual |

The target profile evaluates every value at a target site, also when the name comes from a vendor header. A reference profile evaluates the `#if` lines of its reference headers.

### `argmap.csv`

No version line: the columns are the schema. `callee,slot,mode,groups,status,header,spelled_type,origins,note`.

- `callee`, `slot`: the function and its 1-based argument index. One row per pair.
- `mode`: `value` (one name), `flags` (one name, or single-bit names or'ed together) or `and-mask` (also `~` of them).
- `groups`: space-separated. An entry that ends with `_` is a name prefix. Any other entry is one name.
- `status`: `header prototype` when the slot type comes from a vendor header, else `unverified`.
- `header`: the vendor header that declares the callee.
- `spelled_type`: the slot's parameter type as that header spells it, before typedefs unroll.
- `origins`: space-separated origins whose names the slot accepts. Empty means the origin of the header.
- `note`: free text.

The prototype check reads the callee's prototype from the row's header. The slot's spelled type must equal the row's, with spacing normalized. A failed check or an `unverified` row gives tier B at best. A row in `argmap-proposed.csv` gives nothing until a person copies it into `argmap.csv`.

### `fieldmap.csv`

Optional. No version line: the columns are the schema. `type,member,mode,groups,status,header,spelled_type,origins,note`.

- `type`, `member`: the struct or union as the headers name it, such as `struct xxobj` or a typedef name, and one of its members. Two rows that name one member fail.
- `mode`, `groups`, `origins`, `note`: as in `argmap.csv`. The spot's operator sets the mode: `&=` masks, `|=` and `&` take flags, and `=`, `==` and `!=` keep the row's mode. Empty `origins` means the origin of the header that defines the type's body, as the game reaches it.
- `status`: `header declaration` when the member type comes from a vendor header, else `unverified`.
- `header`: the vendor header that defines the type's body.
- `spelled_type`: the member's type as that header spells it, before typedefs unroll.

The member check reads the type's body from the row's header. Every closure that defines the body there must give the same members, the body must hold the member, and the member's spelled type must equal the row's. A failed check or an `unverified` row gives tier B at best. A row whose type has no body in the target headers gives a warning and no sites.

### `probes.csv`

Optional. No version line. `module,sites,floor,verdict,date,method,note`: one row per yield probe of a module that a run does not build. `sites` is what the probe counted, `floor` is the `yield_floor` it was held against, and `method` says what it counted. A probe is a one-off count, so a run does not repeat it. `gate.md` shows the rows under "Skipped modules".

### Symbol file schemas

No version line: the columns are the schema. A run checks every row on load. A malformed row stops the run with the file and the line.

- `prototypes.csv`: `address,name,slot,type`. One row per return (slot 0) and per parameter (slot 1 and up) of a function.
  - `address`: the function's address, a hex number spelled as the owner annotations spell it. The run lowercases it.
  - `name`: the function's name in the reference build.
  - `type`: the type as the dump spells it: `enum NAME` for an enum, `...` for a variadic tail, which must be the last slot. Only a bare `enum NAME` is an enum slot: a pointer, reference, array or function type that holds an enum, such as `enum NAME *`, is not.
  - Each function needs each slot from 0 to its last, once.
- `enums.csv`: `enum,name,value`. The enumerators of the enums that `prototypes.csv` names, each enum spelled `enum NAME` as there. A name is an identifier, once per enum. A value is an integer, decimal or hex with `0x`.
- `scope-constants.csv`: `address,scope,name,value`. The enum constants declared inside a function. `scope` names the enum of each constant, unique within the function: two enums of one name in one function need two scope names. Names and values as in `enums.csv`.

### Reference call file schemas

A run checks every row on load. A malformed row stops the run with the file and the line. Addresses are hex with `0x`, in lowercase.

- `pairs-NAME.csv`: no version line. `target,reference`: the address of a game function and of its paired reference function. An address on more than one row drops all of its rows, so only 1:1 pairs count.
- `refcalls-NAME.csv`, schema 1. The first line is `# evidence-refcalls schema=1 floats=in-order` or `floats=apart`, then the columns `owner,order,callee,values`. One row per call in a reference function.
  - `owner`: the reference function's address.
  - `order`: the call's place in its function, 1 to n with no gap and no duplicate.
  - `callee`: a reference address, a name, or `?` when it is not known.
  - `values`: the arguments, separated by spaces. Each is `?` when not known, an integer (decimal or `0x` hex, with an optional `-`) with an optional width `:8`, `:16`, `:32` or `:64`, or a float with a `.` or an exponent.
  - `floats=apart` says that the build passes floats in registers of their own, so a decompiled call that holds a float need not keep the source order of its arguments.

### `expected-names.csv`

No version line. `set,umbrella,name`: the header set's name, the umbrella, and a name that must resolve in that closure. The gate report lists each name that does not resolve.

### `denylist.txt`

One entry per line. Blank lines and lines that start with `#` are skipped. Matches ignore case. `word: ENTRY` matches ENTRY only as a whole word. `substring: ENTRY` matches it anywhere. With no prefix, an entry of 4 or more characters is a substring and a shorter one is a word. An empty deny-list is a fault.

### `sites.csv`, schema 1

The line `# evidence-sites schema=1`, then a CSV header and one row per live site, each owner's sites in order. Columns: `id,owner,ordinal,kind,target,slot,expression,value,file,line,column,context`.

- `id`: `S` plus 6 digits. Minted once above the high-water mark, never reused.
- `owner`: the function's annotation address, else `file:name`, or `file#name` at file scope.
- `ordinal`: the site's place in its owner, from 1. For reading only.
- `kind`, `target`, `slot`, `expression`: the payload. `kind` is `call`, `field`, `variable`, `case`, `return` or `placeholder`.
  - A call site: `target` is the callee's address when one annotated definition has its name, else its spelling. `slot` is the argument index, such as `2`. For a call nested in another call's argument, each outer callee comes first with its argument index: `outer#1/2`, where `outer` is the outer callee's address or spelling.
  - A field site: `target` is the type id and the member, such as `struct xxobj.flags`, or `?.flags` when only the member name types the spot. `slot` is the operator, such as `|=`. A scope site of a field spot has the same form.
  - A variable site: `target` is the variable, `slot` the operator (`=`, `==` or `!=`).
  - A case site: `target` is the switch expression as written, `slot` is `case`.
  - A return site: `target` is the owner, `slot` is `return`.
  - A placeholder site: `target` is the macro. `slot`, `expression` and `value` are empty.
  - `expression` is the argument or the value with outer parentheses dropped and each integer literal written as its value with the suffix of its type (`0x80000000` becomes `2147483648u`).
- `value`: the converted value. Not identity.
- `file`, `line`, `column`: where the site is. Not identity.
- `context`: a hash of the statement that holds the site and the statement before it. It only ranks suggestions.

### `ledger.csv`, schema 2

The line `# evidence-ledger schema=2`, then a CSV header and one row per id ever seen, in id order. No row is ever deleted. Columns: `id,kind,status,spelling,candidates,tier,spelling_tier,evidence,counter,fingerprint,first_seen,last_checked,file,line`.

- `kind`: `placeholder` for a placeholder site, else `value`. A placeholder row has the tier `placeholder` and no candidates.
- `status`: for a live site with no decision, `open` or `applied`. `applied` means every value-giving leaf of the expression is a header name. For a live site with a decision in `notes.csv`: `confirmed`, `rejected`, or `stale` when the row's review hash changed since the decision. After `reopen`, the site is `open` or `applied` again. After a remap, an id that is not live is `gone` or `ambiguous`. A row whose id is not live keeps its last status.
- `spelling`: the argument, the value or the placeholder use as written.
- `candidates`: every candidate, ranked, with `; ` between them. The first is the top candidate.
- `tier`: the meaning tier of the top candidate. `spelling_tier`: its spelling tier (see [Spelling](#spelling)).
- `evidence`: the argmap row and its prototype check (for a field site, the fieldmap row and its member check; for a reference symbol site, the row's status, its groups and the symbol check), the top candidate's origins and its spelling. For a placeholder site: the macro's kind, its note and the hash of its definition. `counter`: the counterevidence.
- `fingerprint`: a hash of the inputs that feed the row: the names its argmap row takes with their values and origins, the argmap row, the prototype, the expression and its value, the evidence, the spellings of the candidates and the configuration hash. Canonical JSON.
- `first_seen`: the date the ledger first held the id. `last_checked`: the date its fingerprint last changed.
- `file`, `line`: where the site was last seen.

### `notes.csv`, schema 1

Written by `decide`. Each decision adds one row, and the latest row per id wins. `decide` writes the whole file again, in one atomic write.

The line `# evidence-notes schema=1`, then a CSV header and one row per decision. Columns: `id,decision,candidate,hash,fingerprint,time,note`.

- `decision`: `confirm`, `reject` or `reopen`. `confirm` gives the status `confirmed`, `reject` gives `rejected`, and `reopen` sets the row back to `open` or `applied`.
- `candidate`: the candidate the decision is about: the top candidate, or the one that `--candidate` names, as written. A candidate written with other aliases of its names keeps that spelling here. Empty for `reopen`.
- `hash`: the review hash: the SHA-256 of the row's candidates, its meaning tier and its spelling tier at decision time.
- `fingerprint`: the row's ledger fingerprint at decision time.
- `time`: the UTC time, ISO 8601.
- `note`: free text.

A decided row whose review hash changed is stale. It comes back into review, and `ledger-changes.md` shows the old decision next to the candidate and tiers now. A fingerprint change that keeps the candidates and both tiers updates `last_checked` only, so it never makes a decision stale. A decision whose id is gone or ambiguous is orphaned. `ledger-changes.md` lists it, and `decide` warns on it.

### Generated outputs

A CSV output starts with `# <kind> generation=N`. A Markdown output starts with `# <title>, generation N`.

| File | Kind | Columns |
| --- | --- | --- |
| `inventory.csv` | `evidence-inventory` | `id,kind,file,line,column,owner,target,slot,callee,argument,expression,status,cause,detail,value,type,state,mode,row,check,flags,candidates,incomplete` |
| `argmap-proposed.csv` | `argmap-proposed` | `callee,slot,sites,values,header,spelled_type,sample_clusters,sample_spellings` |
| `confidence.csv` | `evidence-confidence` | `id,eligible,meaning,spelling,sites,target,slot,callee,argument,value,status,top,reason,counter,origins,samples,decision,flags,file,line,list` |
| `candidates.csv` | `evidence-candidates` | `id,rank,name,meaning,spelling,origins,aliases` |
| `diagnostics/baseline-diff.csv` | `evidence-baseline-diff` | `side,cause,file,line,callee,arg,old_literal,old_value,new_expression,new_value,old_candidates,new_candidates,id` |
| `diagnostics/sample-calls.csv` | `evidence-sample-calls` | `tree,file,line,callee,slot,argument,status,cause,value,key,kind,node,lineage` |

In `candidates.csv`, `aliases` holds the terms of the candidate in the order of `name`, separated by spaces. Each term is its aliases, joined by `=`. `decide` reads it to accept a candidate written with other aliases, so it needs the `candidates.csv` of the live generation.

`baseline-inventory.csv` keeps the columns of the first scanner: `file,line,callee,arg,literal,value,candidates`.

In `argmap-proposed.csv`, `sample_clusters` is the number of lineages with an evaluated call at the slot, and `sample_spellings` gives the named spellings there, each with its lineages, most first (at most 5). Both stay empty when no sample tree reads the slot. In `confidence.csv`, `eligible` is `yes`, `no` or `no sample`, `samples` is the top candidate's spelling text, `decision` is the latest decision in `notes.csv`, and `list` is the review list of the row: `review`, `reference` or `placeholder`.

## Coverage

These spots can be sites:

- A call argument is in coverage when its callee has an `argmap.csv` row and the argument is a constant expression: literals, arithmetic and bit operators, `?:`, casts, and identifiers that are not known variables or functions.
- A field spot is a write (`=`, `|=`, `&=`) or a compare (`==`, `!=`, `&`) of a member after `.` or `->` in a function body, also inside a call argument. The member and its base must be the whole left operand. `x.f = x.f | K` counts as `x.f |= K`. A field spot is in coverage when its member has a `fieldmap.csv` row and its value is a constant expression.
- Each use of a placeholder macro that `config.json` lists is a placeholder site.
- With the [symbol files](#symbol-files), the reference symbol sites:
  - a call argument whose callee has no `argmap.csv` row, when the callee's reference prototype gives the argument an enum type;
  - a `return` with a value, in a function whose reference return type is an enum;
  - the scope sites, in a function with scope constants: a field spot with no `fieldmap.csv` row and an operator `=`, `==` or `!=`, a known variable written or compared with these operators (a local's initializer counts as `=`), and a case label.

Coverage is syntactic, so unresolved and unevaluated sites are part of it. Only coverage sites get ids.

```text
call arguments and field spots in the game source
├── out of coverage (counted, not graded)
│   ├── unmapped calls, and field spots whose member has no fieldmap row
│   ├── function-like macro callees
│   ├── field spots whose base has no known type, and bitfields
│   ├── nonconstant values: a variable or function, ., ->, [], unary * or &
│   └── unsupported files: a file with #if lines
└── coverage sites
    ├── resolved: the value evaluates
    │   ├── A, A*, B, C: from the top candidate
    │   ├── incomplete with cover: the budget ran out after a cover was found
    │   └── no candidate
    ├── unresolved: an unknown identifier, an unresolved #if, a missing include, a truncated branch
    └── unevaluated: a function-like macro, sizeof of an expression, a comma, wrong arity, another unsupported step
```

Variables, case labels and returns that are no reference symbol site are out of coverage and not counted. `gate.md` counts the case labels all the same, and the raw-offset accesses such as `*(T *)((char *)p + 8)`, which are never sites. Its section "Reference symbols" gives the rows of each symbol file, the reference symbol sites per kind and their flags.

Each split in `gate.md` sums to its total. The brake works per kind: it counts unresolved plus unevaluated over the coverage sites of one kind. The first run of a kind is its baseline. Over `gate_brake`, the run exits 1: fix the model before building on it. The brake is a process limit, not a measured value. Never raise the budget to make A appear.

## Tiers

Each coverage site has two tiers: the meaning tier of its top candidate (does the name fit the slot and the value) and its spelling tier (does the vendor write that name there, see [Spelling](#spelling)). This table gives the meaning tiers.

| Tier | Meaning |
| --- | --- |
| A | A `header prototype` argmap row that passed the prototype check, a `header declaration` fieldmap row that passed the member check, an enum slot or return of a reference prototype whose enum `enums.csv` holds, or a scope site that passes the lvalue check; a value that evaluates with every step supported, a complete search and no candidate name in an unresolved branch |
| A* | A with counterevidence. Shown apart, never eligible |
| B | As A, from an `unverified` row, a row whose prototype or member check failed, a field site that only its member name types, or a scope site that does not pass the lvalue check (`scope value only`) |
| C | A candidate name whose definition sits in an unresolved branch or has several alternatives |
| incomplete with cover | The budget ran out after a cover was found |
| unevaluated, unresolved, no candidate | From the site's status |
| placeholder | A placeholder site. It has no candidates and its own list in `confidence.md` |

Counterevidence: another closure or profile gives a candidate's name another value; a name with no accepted origin; the target closures disagree on a name of the expression; a target prototype spells the slot otherwise; a body in the fieldmap row's header gives the member another type than the target headers do; the paired function of a reference build passes another value at the slot (`value differs across builds`, see [Reference calls](#reference-calls)). Two member types differ when their kind, width or sign differ, so a typedef of the same type is no counterevidence.

A site is eligible for review when its meaning tier is A, its top candidate's spelling tier is A or B, and its status is `open` or `stale`. Eligible is not confirmed: a name goes into the tree only after a person confirms it. A site whose slot no sample tree reads can never get sample support, so it is not eligible by construction (`no sample` in `confidence.csv`). The sample corpus reads call slots only, so every field site is `no sample`. A placeholder site is never eligible. A comes from `argmap.csv` header-prototype rows, `fieldmap.csv` header-declaration rows and the reference symbols only, so a thin A list is expected. `confidence.md` says so at the top.

One enumerator: under a C++ profile, a plain integer converts to an enum type only through a cast. So where the game source has a literal with no cast at an enum slot or return of a reference prototype, the original had an enumerator there, or a cast. A site whose top candidate is one enumerator alone gets the flag `one enumerator`. With meaning A and status `open` or `stale`, it is eligible without a spelling tier.

Scope constants are the enum constants that a function declares, such as the steps of a state machine. A scope site takes every scope constant of its function as a candidate, meaning B at best. The lvalue check: an lvalue that takes `scope_min_values` or more distinct literal values in its function, each of them the value of a constant of one scope, passes. Its sites take the constants of that scope only, get the flag `lvalue check` and can reach meaning A. The lvalue is a field spot's base and member, a variable, or a case label's switch expression, keyed by its tokens as written with outer parentheses dropped.

Names from a reference build can never get sample support, so they have a list of their own. A site goes on the reference list when its top candidate has the origin `reference`, its meaning tier is A and its status is `open` or `stale`.

The review order: the review list, then the reference list, then the placeholder list. In the reference list, the sites with the flag `one enumerator` come first, then those with the flag `lvalue check`. After that, each list puts eligible sites first, then the meaning tier in the order of the table, then the spelling tier (A, B, C, none), then the number of sites with the same target, slot and value (high first), then the id.

Type gates: `NULL` only at a pointer slot. `TRUE`, `FALSE`, `true` and `false` only at a boolean slot: its spelled type is in the profile's boolean list, or its type is `bool`. A slot that only unrolls to an integer is not boolean. Other names only at a slot of their own kind. A variadic argument gets no candidates. A 0 gets a candidate only from a name whose value is 0.

The cover search, in rank order: at an `and-mask` slot only, the covers of the inverse (`~NAME`, then the composites, then the split of 2 to 4 single-bit names); then one name with the value; then, at a `flags` or `and-mask` slot, the composites and the split. A composite covers the value with 2 to `composite_terms` names whose bits do not overlap, one of them a multi-bit name (such as a mask) at least. Composites rank by the number of names, then by the names, lowest bit first. The split takes one single-bit name per set bit, so it ranks after every composite of the same value. Each lookup and each visit of the composite walk costs one step of `cover_budget`.

## Spelling

The spelling tier tells how the vendor's sample code writes a candidate at the same call slot. Spelling in the game source is not evidence.

- The sample corpus reads each sample tree of `config.json`. A file is a node, by SHA-256, so exact copies count once. The directive lines drop, and every `#if` branch stays. Each argument to a wanted callee is evaluated with the tree's own header set and profile. `diagnostics/sample-calls.csv` lists each observation.
- A tree is left out for a slot when its headers do not declare the callee, define it as a function-like macro, or give it another arity or another spelled slot type. `gate.md` lists these.
- Lineage: the tool compares two sample files by the Jaccard index of their shingles (runs of `shingle_size` tokens). Complete linkage at `lineage_cut` groups the files into lineages. A file with fewer than `lineage_min_shingles` shingles joins only the files with its relative path. `gate.md` shows the similarity histograms of same-path and other-path pairs, so that the cut can sit in the valley between them.
- A key is one way to write a candidate: each name by one of its aliases, joined with `|`, with an optional `~`. `A | B` and `B | A` are one key.
- For a key, the clusters are the lineages that pass the key's value at the slot. Each tree gives the value with its own headers. A lineage weighs 1, split evenly over its distinct spellings. A spelling with names and literals counts as literal. The share is the key's weight over all named weight. The literal share is the literal weight over the clusters.

| Tier | Rule |
| --- | --- |
| A | At least `spell_a_clusters` clusters, a share of at least `spell_a_share` and a literal share of at most `spell_a_literal`. A combination of names also needs `spell_combo` lineages that write that combination |
| B | At least `spell_b_clusters` clusters, a share of at least `spell_b_share` and a literal share of at most `spell_b_literal` |
| C | Some lineage writes the key, or the callee's section in a manual names each name of the key |
| none | Anything else |

A candidate's spelling is its best key. The weights are exact fractions, so a share at a threshold meets it. The thresholds are never lowered to make A appear.

Manuals: the reader splits a manual dump at each `FORMAT` marker into function sections. Index lines (a name and a run of dots) drop. A section stays only when its head names a function of the manual's reference set. `gate.md` shows the markers, the index entries and the sections that stay.

## Reference calls

With the [reference call files](#reference-call-files), a run compares the calls of each paired function with the reference build's calls:

1. The game calls and the reference calls align on the callee only, so one differing argument never blocks the alignment. A callee called once on each side anchors the alignment. A reference callee address maps to the game through the 1:1 pairs of its build. A callee that does not map never aligns. A game callee is its role id: the address of its annotated definition, else its spelling, so a reference callee name aligns only with a game callee that has no annotated definition. Only the pairs that every optimal alignment makes count.
2. Two aligned calls compare their arguments slot by slot, when both have the same number of arguments. On a `floats=apart` build, a call with a float on either side does not compare. A game value compares after its conversion to the parameter type. An integer compares at the narrower width of the two sides, and a float slot compares the bit pattern of an integer.
3. The kill switch: a paired function gives evidence only with at least `pair_min_sites` compared slots whose value both builds know, and with the same value in at least `pair_min_rate` of them. Otherwise the alignment or the pair is likely wrong.
4. A coverage call site in a live function whose slot compares gets the build's value. The same value is evidence ("same value in build NAME"). Another value is counterevidence: the site gets the flag `value differs across builds`, and meaning A becomes A*. A literal whose value differs across builds may stand for a macro. A `?` value counts for nothing.
5. A build that gives fewer than `yield_floor` sites a value gives no evidence at all.

The values of each build go into the site's fingerprint, so a new reference value updates the ledger row. `gate.md` has a section "Reference calls": per build the pairs, the paired functions by what became of them, the slots of the live functions, the coverage sites by the reference value and the verdict, then the sites with the flag `value differs across builds`.

## Program database reader

`pdbimport FILE` reads a program database (a `.pdb` file) and writes the three [symbol files](#symbol-files). [tools/evidence/pdbimport.py](../tools/evidence/pdbimport.py) was written from these public descriptions of the format:

- the PDB pages of the LLVM project: [MSF](https://llvm.org/docs/PDB/MsfFile.html), [info stream](https://llvm.org/docs/PDB/PdbStream.html), [TPI stream](https://llvm.org/docs/PDB/TpiStream.html), [DBI stream](https://llvm.org/docs/PDB/DbiStream.html), [module stream](https://llvm.org/docs/PDB/ModiStream.html), [type records](https://llvm.org/docs/PDB/CodeViewTypes.html) and [symbol records](https://llvm.org/docs/PDB/CodeViewSymbols.html);
- `include/cvinfo.h` in [microsoft/microsoft-pdb](https://github.com/microsoft/microsoft-pdb/blob/master/include/cvinfo.h): the record kinds and their fields;
- `PDB/msf/msf.cpp` in the [same repository](https://github.com/microsoft/microsoft-pdb/blob/master/PDB/msf/msf.cpp): a block map of more than one block, in a large file;
- the [PE format](https://learn.microsoft.com/windows/win32/debug/pe-format): the section headers.

It reads:

- every top-level procedure of every module, with its function type: one `prototypes.csv` row per return and parameter;
- the enum constants anywhere inside a procedure, also in nested blocks: the `scope-constants.csv` rows. A constant inside an inline site belongs to the inlined function, so it does not count. The scope is `enum NAME`, then `enum NAME #2` and on for other enums of that name in the same function;
- the enumerators of each enum that a prototype slot names: the `enums.csv` rows.

A procedure's address is its RVA: the virtual address of its section plus its offset. The map turns an RVA into a game address. `--map MAP.csv` has the columns `reference,target`: hex addresses, with or without `0x`. `reference` is an RVA in the program database, and `target` is the game address. Each reference and each target is on one row only. Without a map, the files keep the RVAs.

How it spells a type:

- A simple type by its C name, such as `unsigned long`, and a class, struct, union or enum by its tag and name, such as `struct Vec3`. It spells no typedef names, so a `DWORD` parameter is `unsigned long`.
- `const` and `volatile` before the type (`const int`), but after the mark of a pointer (`char *const`).
- The marks `*`, `&` and `&&`, and `NAME::*` for a member pointer. A pointer to an array or a function puts its mark in parentheses: `float (*)[16]`, `void (*)(int)`.
- An array with its element count, `[?]` when the element size is not known.
- A slot whose type is an enum, also under `const`, as `enum NAME`.
- A type that the reader does not know as `<leaf 0xNNNN>` or `<simple 0xNNNN>`, so that it shows in the file.

It leaves out these, and prints how many:

- a procedure outside every section, or with no function type;
- an RVA that the map does not hold;
- an address with several different procedures: code that the linker folded into one, so the name is not sure;
- a constant of an enum type that is no enumerator of its enum, or whose enum has no single definition;
- an enum with several different definitions, or with none: it gives no `enums.csv` rows.

It stops with an error that names the stream and the offset on a malformed file, and on what it does not support:

- an info stream version other than VC70 (20000404), a TPI version other than V80 (20040203), a DBI version other than V70 (19990903), and a module signature other than C13 (4);
- an address map (OMAP): the file of a binary that a tool rewrote after the link;
- a procedure that keeps its type in the IPI stream (`S_GPROC32_ID`, `S_LPROC32_ID`).

It does not spell calling conventions, `__restrict` or `__unaligned`. A member function's type is spelled like a plain function, with no class and no `this`.

## Site ids

A site's identity is its owner and its payload: kind, target, slot path and expression. Per owner, a scored global alignment pairs the last run's sites with this run's, in order. A pair is exact, a rewrite (same slot and value, another expression) or a target change (same slot and expression, another callee). A second pass pairs a site whose callee and expression both changed, when it is the only one of its owner with that slot and value.

A pairing is kept only when every optimal alignment makes it. Otherwise the old id becomes `ambiguous`, the new site gets a fresh id, and `ledger-changes.md` lists the suggested match. An old id with no pair becomes `gone`. An edit at one site never moves another site's id. [tools/evidence/remap.py](../tools/evidence/remap.py) has the rules.

## Limits

- Only coverage sites get candidates. Unmapped calls and nonconstant and unsupported sites are counted, not graded. So are field spots with no fieldmap row, an untyped base or a bitfield member, and case labels and raw-offset accesses.
- A literal return is a spot only in a function whose reference return type is an enum. Call arguments and returns are never scope sites.
- Reference names and prototypes come from another build of the game. A name, a type or a value can differ in the target build. An enum type from a reference prototype converts as `int`.
- `pdbimport` reads only the versions and records that [Program database reader](#program-database-reader) names. Its type spellings have no typedef names, so a slot type resolves in the target headers only when the headers spell it the same way.
- Reference calls are only as good as the pairs and the decompiler that wrote them. The game side takes calls through a named callee only: an indirect call, a call through `.`, `->` or `::`, a function-like macro and a placeholder are not calls there, so the adapter must skip indirect calls too. Both sides must list calls in the order of their callee's position in the text, outer call first. A decompiler that moves an inner call into a temporary lists it before its outer call, so one of the two may not align. A call whose callee has no prototype in the game compares its values with no conversion to a parameter type.
- On a `floats=apart` build, a call with a float on either side gives no evidence. A value that differs across builds is a lead, not proof of a macro: a port can change a constant on purpose.
- The lvalue check keys an lvalue by its tokens as written, so `p->x` and `(*p).x` are two lvalues. It counts the values of writes, compares and case labels alike, before they convert to the lvalue's type.
- A field spot needs the member on the left: `3 == p->f` is not a spot, and `(x & K) == K` gives only the `&` spot.
- A field spot's base types through the declaration subset. When it does not, the member name alone types the spot only when every body with that member has a fieldmap row, the rows take the same names and the member has one spelling. Such a site is B at best.
- The sample corpus reads call slots only, so a field site gets no spelling tier.
- A no-code placeholder leaves nothing in the binary, so nothing can check it.
- Host Python is not the target machine. The tool claims only what the profiles model, each with its provenance.
- There is no full preprocessor and no C++ parser. Include order is modelled only inside the umbrella closures. Unresolved conditions never count as 0.
- The game source is not preprocessed. A file with `#if` lines is unsupported as a whole. A local that shares its name with a header constant is caught only by the declaration subset. The target closures act as one, so a name can resolve in a file that does not include its header. Such a site gets the flag "include", nothing more.
- A header included twice under different macro state (X-macro style) is not modelled.
- Swapping two sites in one owner keeps one id at most.
- The expansion rules are for Release builds only.
- Vendor values may differ in the game's port of the library.
- Sample code shows the vendor's habits, not the game team's.
- The sample corpus keeps every `#if` branch, so a call in a dead branch counts too.
- Lineage is a similarity measure. A copy that the vendor changed past `lineage_cut` counts as a lineage of its own.
- Types from the game source are not evidence. A comes from `argmap.csv` and `fieldmap.csv` rows and the reference symbols only.
- Splits, merges, extracted helpers and moves of a function with no annotation give gone and new ids. So does a callee and expression change when the owner holds another site with the same slot and value. An insert or delete among adjacent identical sites makes them ambiguous. Ids are local to `evidence/`.
- `sizeof` of an expression is unevaluated. An object-like macro that expands to a call is unsupported.
- `audit` checks the working tree and the index, not history.
- Tiers are review priority. A threshold change changes tiers, not evidence.
