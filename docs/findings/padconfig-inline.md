# padconfig: one inline choice differs from the game

Status: **open**. Written 2026-11-12. Read this before any new work on `padconfig`.

Newest result (2026-11-14, sixth part, near the end): the tree's inline candidate list of `padconfig` is
wrong by two functions. With the right list the stock `<list>` gives the game's bytes, when `padconfig`'s
own source has about 490 nodes fewer. The sections before the sixth part assume the wrong list.

Tree state since the eighth part (2026-11-14): the right list is in `src/`. `padconfig` now has 66 candidates,
a frame of 0x9cc and a score of 81.48% (before: 82.63%). The byte counts and the frame in "The difference"
below describe the tree before that fix.

## The difference

- `padconfig` (0x0057d490, `src/advertise.c`) compiles to 22020 bytes with a frame of 0x9e4.
- The game has 22072 bytes with a frame of 0x9f8.
- The game inlines one more `std::string` constructor: the one of the default-case `ReadFile` call. Our build
  keeps it as a call, because the function's node count is past the cap of 35000 at that call.

[PORTING.md](../PORTING.md#traps) explains the node count, the cap and the budget.

## What is proven

1. **The stock compiler gives the game's bytes.** VS2010 SP1 `c2.dll` needs no patch and no other build.
2. **One small constructor decides.** `_List_unchecked_const_iterator(node, list)` has 41 nodes with the stock
   `<list>`. Its body is one call, `this->_Adopt(_Plist);` (line 42), and `_Adopt` is empty. Three lines of
   `padconfig` use it: `DAT_05cd2820 = DAT_05cd2828.begin();`.
3. **Without that call the function equals the game.** A copy of `<list>` without line 42 gives a constructor of
   24 nodes. `padconfig` then has 22072 bytes and 0 differences, and all 22 annotated functions of the file
   equal the game. With the stock header 21 of 22 do.
4. **Why it decides.** With the stock header each use costs the budget 41 and the count 179. Without the call it
   costs the count 24 and the budget nothing. The count at the default-case constructor is then 34579, under
   the cap.
5. **Nothing else in the tree changes.** `<list>` reaches 5 tree files. Only the code of `padconfig` differs
   between the two headers.

## What is ruled out

| Cause | Why not |
| --- | --- |
| Another compiler build | The stock compiler gives the bytes (item 1). |
| The RTM headers | `padconfig` has 22020 bytes and frame 0x9e4, as with SP1. |
| `_SECURE_SCL`, `_ITERATOR_DEBUG_LEVEL` | No effect on the choice. |
| Flags `-GF`, `-GR-`, `-Gy`, `-Ob2`, `-Ot`, `-Oy` | 22020 bytes and frame 0x9e4, as stock. |
| Flags `-Os`, `-Oi` | Other code (21366 and 22008 bytes). |
| No debug info | 22072 bytes but 10351 differences, frame 0x9e4. |
| `/GL` | The `-GL` build is further from the game than the normal build (sixth part, item 1). |
| Headers with no `_Adopt` call at all | The game keeps the vector iterator constructor as a function (0x004bab50), and 0x004ba3f0 calls it twice. A callee of 40 nodes or fewer is never refused, so that constructor has over 40 nodes in the game. |
| A smaller `list::clear` | The game's copy (0x005fb840, 129 bytes) equals ours. |
| A compiler rule "a refused callee costs nothing the next time" | It fits the numbers of `padconfig`. `InitStaff2` rejects it. |
| Source rewrites | 44 source forms, 165 body rewrites with equal bytes and 80 declaration variants all miss. |
| Other releases | The 2004 PC release has no such code. The September 2014 Steam exe has the same bytes. The console releases use other compilers. |

## A form that forces the match, and why the tree does not have it

This block, placed before the declaration of `DAT_05cd2820`, gives 22072 bytes and 0 differences with the stock
headers (tested in a scratch copy, 22 of 22 functions equal):

```cpp
template<> inline std::_List_unchecked_const_iterator<std::_List_val<LBOnData, std::allocator<LBOnData> >, std::_Iterator_base0>::_List_unchecked_const_iterator(
    _Nodeptr _Pnode, const std::_List_val<LBOnData, std::allocator<LBOnData> > *_Plist)
    : _Ptr(_Pnode)
{
}
```

Do not apply it. Decision of 2026-11-12:

- It is a fake match. No game programmer specializes a library constructor, so it copies the result and not
  the source.
- A 100% score would hide an open question.
- `DrawLBOn` uses the same list. It matches with the stock header (row 1 below), so it does not need the
  block.

The same holds for any other form that only moves the compiler's counters.

## The open question

What gave the game's build a cheaper list iterator constructor? Three guesses, best first:

1. The build setup gave the compiler other text for that constructor. No known VS2010 header set has it. The
   vector constructor in the same file is stock (last result below).
2. The three `begin()` lines look different in the original source. No tested form gives the same bytes.
3. The compiler had one other rule. `InitStaff2` speaks against it.

A related pattern: the tree's source forms lack nodes in two functions. With them `InitStaff2` needs 26 to 33
`MAYBE_ASSERT()` lines, and `InitLBOn` (0x00582b10) needs 10 to 13. The next section gives the cause: other
plain source forms carry those nodes.

## Result of 2026-11-12: the source form carries nodes

The lead is `InitStaff` (0x005ebea0, row 6 below). Tests are scratch compiles with the stock headers.

1. **Equal code, other weight.** `n = n + 1` has 2 nodes more than `n++`, `++n` and `n += 1`. The code is the same.
2. **`InitStaff`.** With `n++` on its 29 insert lines it has 5745 bytes (game 5756): the last `std::wstring`
   destructor stays a call. It equals the game with 1 to 38 `MAYBE_ASSERT()` lines (40 fails), and with no such
   line when the 29 lines say `n = n + 1`.
3. **`InitStaff2`.** The same holds: with `n = n + 1` on its 29 insert lines and no `MAYBE_ASSERT()` line it
   equals the game (6937 bytes, frame 0x91c). So the 29 placeholder lines stand for 58 nodes of plain source.
4. **`padconfig` has too many nodes, not too few.** The tree writes `x = x + 1` 15 times and `x = x - 1` 7
   times. Its conditions say `(x != 0)` and `(x == 0)`. With `x++`, `(x)` and `(!x)` the count drops, and the
   compiler inlines the default-case constructor. The instruction sequence then equals the game: 5074
   instructions, no block differs.
5. **Best form so far.** The form is `x++` (15 lines), `(x)` and `(!x)`, with `x = x - 1` kept. The frame is
   0x9f8 as in the game, and 14 bytes differ. They are the offsets of temporaries in 7 instructions. The
   places: after 3 calls on the object 0x0629c344, after the 3 `begin()` lines, and in the default-case
   constructor. The form has no header change and no specialization.
6. **The window.** From the lightest form (all four rewrites), 5 to 7 `MAYBE_ASSERT()` lines give the same 14
   bytes. 0 to 4 lines give 231 bytes and frame 0x9f0. 8 to 14 lines give frame 0x9f4.
7. **More forms on the insert lines.** `n = 1 + n` and `(void)n++` weigh the same as `n = n + 1` and fit both
   functions. `++n`, `n += 1` and an `(int)` cast on the index do not fit `InitStaff2`.
8. **A hidden conversion carries a node too.** `InitLB` (0x005f4ee0, row 5 below) has the game's instructions
   but frame 0x314 (game 0x324). It equals the game with 9 to 13 `MAYBE_ASSERT()` lines. It also equals the
   game with no such line when `Texture::Load` must convert both getter results. The test types for the two
   `SOCFileStream` getters are `char*` and `unsigned int`. One changed getter alone gives frame 0x318.
   `InitLB` has 11 `Load` calls, so 2 conversions per call are 22 nodes. `InitLBOn` has 13 `Load` calls. With
   the test types it equals the game with no line, and 1 line fails.
9. **The helper's prototype closes `InitStaff2`.** `InitStaff2` has 4 `Load` calls and 1 call to
   `FUN_004b23e0` with the two getter results. With the test getter types alone it needs 21 to 28 lines (20
   and 29 fail). So `n = n + 1` on 29 lines is 2 nodes too heavy. When `FUN_004b23e0` takes `char*` and
   `unsigned int` too, the window is 22 to 29 lines (21 and 30 fail). Then `n = n + 1` on the 29 lines and no
   `MAYBE_ASSERT()` line equals the game. The test adds a second declaration of the helper with these types,
   so only the call in `InitStaff2` changes.
10. **One set of forms fits four functions.** The set: getters that return `char*` and `unsigned int`, a
    helper that takes them, and `n = n + 1` on the insert lines. `InitStaff`, `InitStaff2`, `InitLB` and
    `InitLBOn` then equal the game with no `MAYBE_ASSERT()` line. The types are test types. Each type pair
    that `Load` must convert and the helper takes as is has the same weight. `padconfig` gets heavier with
    them (9 getter pairs): frame 0x9d4 with the tree source, 0x9f4 with the light forms. By the count it then
    needs 4 to 8 nodes less (not tested). No known source form gives that.
11. **That set is in the tree.** Both getters score 100%. `InitStaff2` scores 100% with no `MAYBE_ASSERT()`
    line. `FUN_004b23e0` stays at 94.12%. `InitLB` has the game's bytes and scores 99.83%: its one difference
    is the name of the folded `clear` copy (row 7 below). `padconfig` scored 81.62% with the old forms (before:
    81.85%). With `x++`, `x--`, `(x)` and `(!x)` it scores 82.63%, and its frame is 0x9f4 (game 0x9f8). The
    tree has those forms.
12. **The folded `clear` copy has a second folded call inside.** The scorer now folds an instance of a
    template into the matched instance of that template with the same code (`tools/folds.py`). That does not
    close `InitLB`. The game's `clear` (0x005fb840) calls 0x005b5aa0 where ours calls its own `_Dest_val`
    instance. 0x005b5aa0 is a 5-byte empty function. `padconfig` calls it too, by another name and with 4
    arguments. So the game's link folded functions of other names into it. The tree has many empty
    functions with that code at their own addresses, so the code alone does not say which ones folded. The
    scorer knows one name per address. `clear` scores 97.96% for that reason.

Open: the 14 bytes. The node count alone does not close them, so one more source form or the constructor
question above is still in play. `scratch tools: padtest.py, shape_diff.py, objcmp.py` in the local research
folder.

## Functions that can show the cause

Rank is value for the question first, cost second. The counts come from the game's code, not from source, so a
function can turn out neutral. The first order of work is 2, then 4, then 1. The results table below has the
state.

| # | Address | Tree state | Bytes | In the game's code | Tests |
| --- | --- | --- | --- | --- | --- |
| 1 | 0x005837c0 | `DrawLBOn`, 100% | 16200 | list 0x05cd2828: 6 uses; iterator 0x05cd2820: 14 uses; 2 `clear` calls | the cheap constructor on the same list type |
| 2 | 0x005fa460 | 82.70% | 2016 | 3 `clear` calls on a second list, 0x05edd970 | how the compiler charges a refused `clear` |
| 3 | 0x005f5a70 | `DrawLB`, 99.96% | 17904 | second list: 5 uses; 2 `clear` calls | whether a list in another file behaves the same |
| 4 | 0x004ba3f0 | not in `src/` | 1411 | 2 calls to the vector constructor 0x004bab50 | the vector side, by a compile |
| 5 | 0x005f4ee0 | `InitLB`, 99.83% | 2644 | second list: 1 use; 1 `clear` call | the missing-nodes pattern (twin of `InitLBOn`) |
| 6 | 0x005ebea0 | `InitStaff`, 100% | 5756 | 1 call to 0x004bab50 | the vector side; the missing-nodes pattern (twin of `InitStaff2`) |
| 7 | 0x005f5940 | 98.55% | 235 | second list: 4 uses; 1 `clear` call | needed for row 2 only |
| 8 | 0x00582b10 | `InitLBOn`, 100% | 3084 | list 1 use, iterator 1 use | done as a test: it fits both headers |
| 9 | 0x005f1320 | `achivement_exec`, 83.33% | 736 | object 0x0629c344: 5 uses; 3 calls to 0x00424b40 | the source form of the call chain behind 3 of the 7 instructions |
| 10 | 0x005f37e0 | 79.68% | 884 | object 0x0629c344: 5 uses; 3 calls to 0x00424b40 | as row 9 |
| 11 | 0x005f25a0 | 76.73% | 684 | object 0x0629c344: 3 uses; 2 calls to 0x00424b40 | as row 9 |
| 12 | 0x0059fc10 | `TitleNewWakeProcedure`, 100% | 357 | object 0x0629c344: 1 use | the getter alone |
| 13 | 0x0059fdb0 | 97.56% | 693 | object 0x0629c344 | the getter alone |

How to read a result:

- **Row 1.** Build it with the stock header and with the header without line 42. If only the second gives the
  game's bytes, the cheap constructor holds for this list. If only the stock one does, it falls.
- **Row 2.** The game refuses `clear` (183 nodes) three times in a small function, so the budget is tight there.
  If the stock rules give the game's bytes, the "free refusal" rule loses ground. If not, the cause moves to
  the compiler.
- **Row 3.** As row 1. A match only without line 42 says the cause covers every list, not one file.
- **Row 4.** If plain source with the stock `<vector>` gives the two constructor calls, the difference sits in
  the list code alone.
- **Rows 5 and 6.** Count the `MAYBE_ASSERT()` lines each needs. More cases with one line per load or insert
  point at a macro in the original source.

Add each result to this file.

### Results per row (2026-11-12)

| # | Result | Verdict |
| --- | --- | --- |
| 1 | `DrawLBOn` is written. It equals the game's bytes (16200, frame 0x3b8) with the stock header and with the header without line 42. It is in the tree at 100%. 3 locals have a start value and no later use. The function builds with `/Od`, so each start value is a store in the game's code. The checker no longer counts such a local as `unused_local`. | Neutral: it fits both headers. |
| 2 | 82.70% with `memcpy` for the `SAVE_DATA` copy (the type has no layout). A scratch test with a 0x580-byte layout and a struct assignment leaves 52 bytes: one 4-byte frame slot that no code uses. 40 `MAYBE_ASSERT()` lines change nothing. The header without line 42 changes nothing. One unused 4-byte local leaves 2 bytes (54 name and type variants, none exact). The tree has the `memcpy` form. | Neutral: the slot is not an inline effect. |
| 3 | `DrawLB` is in the tree at 99.96% with the game's bytes (17904, frame 0x4b8). The two `clear` calls go to the folded copy 0x005fb840, as in row 7. It equals the game with the stock header, without line 42, and with the 8-entry and 9-entry lines (2026-11-14). | Neutral: it fits every header. |
| 4 | 62.30%. It needs an engine class of 0x20 bytes with two vectors that the tree does not have. The game calls 0x004bab50 for `begin()` and for `end()`. Parked. Row 6 and `InitStaff2` answer the vector question (see the last result below). | Not needed now. |
| 5 | `InitLB`: see items 8, 10 and 12 above. In the tree at 99.83% with the game's bytes. The getter types are a choice between equal fits. | The missing nodes are plain source. |
| 6 | `InitStaff` is in the tree at 100% with `n = n + 1` and no `MAYBE_ASSERT()` line. | The missing nodes are plain source. |
| 7 | The bytes equal the game (235, frame 0xa4). The score is 98.55%. `clear` (0x005fb840) is one folded copy for two list types, and the scorer knows one name per address (item 12). In the tree. | Needed for row 2 only. |
| 8 | `InitLBOn` is in the tree at 100% with no `MAYBE_ASSERT()` line. Its `begin()` line is `DAT_05cd2820 = DAT_05cd2828.begin();`, as in `padconfig`. | The `begin()` form and the conversion form hold. |
| 9, 10, 11 | See "Result of 2026-11-14" below. | The chain form of `padconfig` is the game's form. |
| 12, 13 | Both frames equal the game (0x14 and 0x44). The extra `xor edx, edx` lines are gone: the callees are methods now (item 5 below). Row 12 scores 100%. Row 13 scores 97.56%: the lines left read an address inside `DAT_05b3e320`, and the scorer names it in another way. | Neutral. |

### Result of 2026-11-14: the call chain is not the cause

Rows 9 to 11 are three small functions with the chain of `padconfig` (13 getter calls in total).

1. **The plain chain form gives the game's slots.** The form is `FUN_00405f00()->FUN_00424b40()->...` in one
   statement. The game stores the 13 getter results at `ebp-0x24`, `-0x30`, `-0x3c`, `-0x48`, `-0x54`. Our build
   stores each one exactly 4 bytes higher. The step of 0xc is the same.
2. **One 4-byte slot is missing in each function.** The frames are 0x64, 0x64 and 0x48 (game 0x68, 0x68 and
   0x4c). The game has the slot at the top of the frame, between the first `char` local and the security
   cookie. No code uses it. 0x005fa460 (row 2) has the same slot. The four functions are siblings.
3. **Test on 0x005f25a0.** With one unused 4-byte local and a struct copy for the 0x580-byte save data, the
   frame is 0x4c and all getter and controller slots equal the game (93.13%, scratch only). The local lands at
   the bottom of the frame, not at the game's place. The tree has no such local.
4. **A named pointer for the first getter result scores higher and is wrong.** It gives 80.19%, 79.92% and
   77.24%, but it moves that result to `ebp-0x14`, out of the row of 0xc steps. The tree has the plain form.
5. **Five callees are methods.** The tree had them as `__fastcall` functions with an unused second argument.
   The game's callers load the object in `ecx` and write no `xor edx, edx`. The callees read `ecx` and end
   with `ret` or `ret 4`. They are members now: `SOCInput::FUN_00424910`, `FUN_00424950`, `FUN_00424a70`,
   `FUN_00424a80` and `SOCRender::FUN_00419d00`. `FUN_00424a70` and `FUN_00424a80` return `int`: the callers
   push `eax` with no sign extension. Four score 100%. `FUN_00424910` is a stub.
6. **A call with a result that no code reads is an `if` with an empty body.** Rows 9 and 11 hold the line
   `...->FUN_00431d10(7)` or `...->FUN_00431c60(7)`. As a plain statement, each later instruction takes the
   next register of the game's order, so all of them differ. 12 forms are tested in row 9. `if (call) { }`
   and `if (call);` give the game's registers and no extra code. The other 10 do not: plain, `(void)`, `!`,
   `== true`, `!= 0`, `(int)`, `(bool)`, a ternary, `&& 0` and a comma. Row 10 has no such line and no such
   shift.
7. **The same two rows have a `break` in the first block and a second `break` at the end of `case 1`.** The
   game's first block jumps to the end of the `switch` and has no jump over an `else`. The case ends with two
   jumps to the same place, and no label points at the second one. 7 placements are tested in row 9. One
   gives the game's instructions: `break;` at the end of the first block, a new `if` in place of `else if`,
   and `break;` after the closing brace of the case. `return;` in place of the first `break;` gives the same
   code in the two placements tested with it, so the source word is a choice. Row 10 has the plain `else if` form and one `break`.
8. **What is left in rows 9 to 11.** No instruction differs in row 9 once the numbers are blanked: only the
   4-byte slot of item 2 is left. Rows 10 and 11 also have the save-data copy (`rep movsd` in the game,
   `memcpy` in the tree, as row 2).
9. **The empty `if` does not belong in `padconfig`.** Line 1787 has a call of this kind
   (`...->FUN_00432100(30000,30000,500.0)`). With the empty `if` the score goes from 82.63% to 85.09%. That
   gain is false. The game's registers at that call differ before the `if` can act. The shift starts at the
   default-case constructor (line 1112), which the game inlines and our build calls. The `if` only moves
   later code back by chance. A byte compare shows the same: 10282 bytes differ with the `if`, 10316 without
   it, and the frame stays 0x9f4 (game 0x9f8). The tree keeps the plain statement.

So the 14 bytes of `padconfig` do not come from the source form of the chain. The slots after a getter call
follow from what the compiler reserves before them.

Side facts:

- The game keeps one copy of the compiler header's `swprintf` (0x005f5a30, 55 bytes). A `LIBRARY` note in
  `src/header-functions.h` with the line `// swprintf` names it. The tree has no such note yet: the first
  function that calls `swprintf` adds it. `tools/declgen.py` then writes no prototype and no stub for a use by
  name.
- The bytes `xor reg, reg; jne` back to itself occur 12 times in 5 functions: 0x004ba3f0 (6), 0x00577bc0 (3),
  0x004b5e70, 0x004ba9c0, 0x00588ea0. An empty `do { } while (0)` gives these bytes. The source text behind
  them is not known.

### Result of 2026-11-14: the limit is 40 nodes, and the heavier source forms fit

Tests are scratch compiles of `src/advertise.c` copies with a byte compare (`padtest.py`). The tree is not
changed.

1. **The count at the deciding call.** A trace of the stock compiler on the tree gives 34868 before the
   default-case constructor and 35004 inside it. The cap is 35000. The compiler then refuses `_Tidy`,
   `assign` and the constructor itself.
2. **16 source variants, two headers.** The four rewrites of item 11 above go back to the old form in groups:
   `x = x + 1` (15 lines), `x = x - 1` (7 lines), `(x != 0)` (10 lines), `(x == 0)` (11 lines). The getter
   types stay.
   - With the stock header no variant equals the game. The frames are 0x9d4 to 0x9f4.
   - With `<list>` without line 42, six variants give 0 differences: the two condition groups alone, each of
     them with `x = x + 1`, and those three with `x = x - 1` added. The tree's light forms give frame 0xa04.
     All four old forms give 235 differences and frame 0x9f0.
3. **The limit is exactly 40 nodes.** Line 42 is replaced by a line with no code and a chosen weight (a comma
   list of `_Plist`). With 1, 2, 4 and 8 entries `padconfig` equals the game. The trace gives 40 nodes for 8
   entries. With 9 entries (42 nodes) and more it does not. The stock constructor has 41.
4. **The `_Adopt` call itself must be absent.** `this->_Adopt(0);` gives a constructor of 40 nodes that keeps
   the call. No source weight fits it: in steps of 2 nodes the frame goes from 0x9fc to 0x9f4 and skips 0x9f8.
   `_Adopt(_Plist);` and a cast on the argument change nothing.
5. **The other functions do not care.** `InitStaff2`, `InitLBOn`, `DrawLBOn` and `InitLB` equal the game with
   the stock header, without line 42, and with the 40-node line.

So the game's build saw a list iterator constructor of 40 nodes or fewer with no `_Adopt` step, and
`padconfig` is the only function that shows it. The light forms in the tree fit the stock header best, but
they cannot reach the game's bytes with any header tested. The heavier forms can, and they are the forms of
`InitStaff` and `InitStaff2`. The bytes do not choose between the six variants.

### Result of 2026-11-14, second part: the vector constructor is stock, and what is left

Tests are scratch compiles and read-only traces. The scripts are in `build/witness/` (local). The tree is not
changed, except for `DrawLB` (row 3).

1. **The vector constructor has its `_Adopt` call, in the same file as `padconfig`.** `<vector>` line 46 is
   the twin of `<list>` line 42. A copy of `<vector>` without it gives:
   - `InitStaff2` (0x00577e40, `src/advertise.c`): 49 differences, frame 0x92c (game 0x91c). Stock: 0.
   - `InitStaff` (0x005ebea0, `src/Advertise/Option_sub.c`): 3437 differences. Stock: 0.

   So no setting that drops `_Adopt` for the whole file or the whole build fits. Only the list constructor is
   cheaper, and only `padconfig` shows it.
2. **The game has no list code that calls a constructor out of line.** 0x004bab50 is the 24-byte two-argument
   iterator constructor. Two functions call it: 0x004ba3f0 (2 calls, a vector of 0x4c-byte elements) and
   `InitStaff` (1 call, `begin() + 426` on a vector). An explicit instantiation of `list`, `vector` and their
   iterator classes gives the same bytes for `begin`, `end` and the constructors with both `<list>` texts. So
   a copy that is not inlined cannot show the header text.
3. **The tree's light forms are not the game's forms, with either header.** With the stock header six of the
   16 variants give the game's stack offsets at the two getter results, the `atanf` result and the three
   `begin()` temporaries: the two condition groups alone, each with `x = x + 1`, and those three with
   `x = x - 1`. They are the six variants of item 2 above. The size of `padconfig` alone is then 10883 to
   10904 nodes. The tree has 10835, and its offsets sit 4 bytes off. Without line 42 the tree's forms give
   10366 differences (frame 0xa04).
4. **`GetSubject` is defined in its class.** Defined below the class, it is no inline candidate. `padconfig`
   then gets the game's instructions with the stock header (233 differing bytes, frame 0x9f4). But the game's
   frame holds the 8 bytes per getter that only a refused inline attempt reserves.
5. **The count in numbers** (variant with both condition groups). With the stock header one `begin()` costs
   the count 323: 53 for `begin`, 17 for `_Nextnode`, 37 + 37 + 41 for the three constructors, 15 for
   `_Adopt`, and 41 added again at each of the three levels above the 41-node constructor. Without line 42 it
   costs 168. With the 8-entry line it costs 184, and with `this->_Adopt(0);` 199. The count at the
   default-case constructor is 35032 with the stock header and 34556 without line 42.
6. **The game's own inline code cannot carry the gap.** Before the deciding call it adds 488 to the count:
   `GetSubject` 284, the two getters 38, `AngleUniform` 85, the `SOCIniFile` constructor and destructor 81.
   The gap is about 400. Four other `GetSubject` bodies (`!`, `NULL`, `0 ==`, a ternary) change nothing.
7. **A lighter refused `clear` does not give the game's frame.** `clear` without lines 1103 to 1105 saves 324.
   All six variants then give the game's instructions, with 219 differences and frame 0x9f0.
8. **More inline candidates late in the function do not fit.** An inline wrapper around one or both
   `GetTextSize` calls, with each of the 16 variants: no variant equals the game. With one wrapper the best
   is 235 differences and frame 0x9ec: the early offsets are 8 bytes high and the late region is 20 bytes
   short.
9. **The header switch in `advertise.h` plays no part.** The block that sets `_HAS_CPP0X`, `_HAS_TR1` and
   `_HAS_TR1_IMPORTS` to 0 around `<vector>`, `<list>` and `<map>` was tested in three forms: `_HAS_CPP0X`
   alone, `_HAS_CPP0X` for `<string>` too, and no block. `padconfig` has the same differences in each.
10. **A compiler without the re-added amounts does not fit either.** The re-added amounts are 5041 of the
    35032. Without them the count is 29991 at the deciding call, far under the cap. The later string
    constructors would then inline too, and the game calls them. This is a calculation on the trace, not a
    run. The third part below has the run.

What is left, with no order of likelihood:

- The game's build had other text for the list constructor alone. Its `<vector>` is stock (item 1). The fifth
  part below shows a second text that fits, and finds no build setting that gives either text.
- The game's compiler revision counts this one case in another way. The five hotfix builds after .404 are not
  obtainable. The third part below tests changed counting rules in real compiles: none fits.
- A source form of the three `begin()` lines that nobody has thought of. Every form tested changes the bytes.
- Added 2026-11-14: the candidate list was wrong. The sixth part below replaces this list with one open
  part, the own node count.

### Result of 2026-11-14, third part: changed counting rules do not give the game's bytes

Tests are real compiles with the stock compiler. A Frida script changes the inline counting in the compiler's
memory only. No toolchain file changes. This is a diagnosis and never a build step. The script is
`build/witness/c2/rule.py` (local). The source is the variant with both condition groups, and the header is
stock. "Others" are the 23 other annotated functions of `src/advertise.c`.

The stock rules: the count starts at the function's own size and the budget is two times that size. A callee
over 40 nodes is refused when it is over the budget that is left. Every callee is refused when the count is
over 35000. A callee over 40 nodes is charged to the count and the budget. After a nested level the nodes of
that level are added again one level up. A refusal for size takes them off again.

| Changed rule | `padconfig` | Others |
| --- | --- | --- |
| None (control) | 10351 differences, frame 0x9e4 | equal |
| None, `<list>` without line 42 (control) | 0 differences | |
| No second add to the count, no refund to the count | 10383, frame 0xad8 | equal |
| No second add to the count, refund kept | 10557, frame 0xb88 | equal |
| No second charge to the budget, no refund to the budget | 10606, frame 0x9dc | `InitStaff2` 54, `InitLBOn` 47 |
| The two rows above this one together | 10364, frame 0xa9c | `InitStaff2` and `InitLBOn` differ |
| Refusal limit 41, charge limit 40 | 10351, no change | |
| Charge limit 41, 42 or 43 (refusal limit 40 or the same) | 217, frame 0x9f4 | `InitStaff2` 49, 49, 43 |
| Charge limit 44 | 237, frame 0x9ec | `InitStaff2` 74, `InitLBOn` 47 |
| Both limits 48, 49, 53, 58 or 64 | over 10000 | |
| Both limits 39 | 10351 | `InitStaff2` 4423 |
| Both limits 36 or 32 | over 10000 | `InitStaff2` over 4000 |
| No second add, no refund, cap 30350 to 30470 | 225, frame 0xa00 | |
| The same with cap 30500 or 30530 | over 10000 | |
| Each refusal sets the count back in full | 10557, frame 0xb88 | |
| The same with caps 15400 to 16300, step 25 | no match, lowest 9547 | |
| Each refusal keeps only the callee's own size, caps 19782 to 20682, step 25 | no match, lowest 236 | |

1. **No tested rule gives the game's bytes.** The game's frame is 0x9f8. The closest runs have 217 to 239
   differences, and each of them misses the frame.
2. **A change on the budget side breaks other functions.** `InitStaff2` and `InitLBOn` equal the game with
   the stock rules. They differ with each changed limit and with each changed budget rule.
3. **A change on the count side shows only in `padconfig`.** It is the only function that reaches the cap. So
   other functions cannot contradict such a change, and they cannot support it either. A set of changes that
   is fitted to `padconfig` alone proves nothing.
4. **The order of the functions cannot move.** Explicit instantiations of the list iterator classes and of
   `begin` give the stock bytes (10351, frame 0x9e4). The compiler still handles them after `padconfig`.
5. **No callee has the force flag.** The stock trace shows no callee that skips the limits.
6. **The game's three list calls in `padconfig` are `clear`.** All three go to 0x005fb840. `begin()` is
   inline at each site. This agrees with the compile and adds nothing.

So the second explanation above has no support left. It is not refuted: a revision could differ in a way
that no tested rule covers.

### Result of 2026-11-14, fourth part: one `<list>` text in every VS2010 copy at hand

A search of all local drives finds one VS2010 `<list>` text only. The SP1 `VC\include\list`, the RTM
`VC\include\list` and the RTM `VC\crt\src\list` (both from the Windows SDK 7.1 ISO) have the same SHA-1. So no
header at hand gives the cheaper constructor.

One other text of that library generation was tested later, an April 2010 pre-release text. Its `<list>`
differs from the stock one by a warning pragma and the indent of `#if` lines only. The iterator constructor is
the same, and `padconfig` gets the stock bytes (10351 differences, frame 0x9e4). The full header set of that
text does not compile with the SP1 compiler. So the header explanation has no candidate left. It is not
refuted: a project-local copy of `<list>` would leave no trace.

### Result of 2026-11-14, fifth part: one uncharged constructor gives the game's bytes, and no setting gives that

Tests are scratch compiles with header copies and source variants in `build/witness/` (local). The tree and the
toolchain are not changed. A `__forceinline` in a header copy is a diagnosis here, not a proposed source form.

1. **The stock `<list>` text gives the game's bytes when one iterator constructor is not counted.** c2 does not
   count a callee that has symbol flag 0x2000 (rule 8 of the long record). The keyword `__forceinline` sets
   that flag. Header copies with the keyword, the `_Adopt` call kept, variant with both condition groups:

   | `__forceinline` on | `padconfig` | Cost of one `begin()` |
   |---|---|---|
   | nothing (stock) | 10351 differences, frame 0x9e4 | 323 |
   | `_List_unchecked_const_iterator(_Nodeptr, const _Mylist *)` | 0 differences, frame 0x9f8 | 159 |
   | `_List_const_iterator(_Nodeptr, const _Mylist *)` | 0 differences, frame 0x9f8 | 163 |
   | both of these | 10353 differences, frame 0x9f8 | not logged |
   | these two and `_List_iterator(_Nodeptr, const _Mylist *)` | 10354 differences, frame 0x9fc | not logged |
   | all three and `begin()` | 10355 differences, frame 0xa00 | not logged |
   | `_List_iterator(_Nodeptr, const _Mylist *)` only | 217 differences, frame 0x9f4 | not logged |
   | `begin()` only | 219 differences, frame 0x9f0 | not logged |

   With each of the two forms that fit, all 24 annotated functions of `src/advertise.c` equal the game.
   So "the `_Adopt` call is absent" was too narrow. The game needs a `begin()` cost in a window: 159, 163, 168
   (no line 42) and 184 (8-entry line) fit, 199 does not.
2. **Only the keyword sets the flag.** In the stock compile no inline candidate has it. A trace of two test
   files shows the flag for `__forceinline` on a function, for `inline` under `#define inline __forceinline`,
   and for `__forceinline` on a declaration in the class. It shows no flag for: `inline`, `__inline`,
   `_inline`, a definition in the class, `static`, `extern`, a friend, a lambda, a local class, an unnamed
   namespace, `extern "C"`, a template, an explicit specialization, an explicit instantiation, a `dllimport`
   or `dllexport` class, a calling convention, `virtual`, `throw()`, the `__declspec` forms `noinline`,
   `nothrow`, `noalias`, `restrict`, `deprecated` and `property`, and the pragmas `inline_depth`,
   `inline_recursion`, `auto_inline`, `optimize`, `runtime_checks`, `check_stack`, `strict_gs_check` and
   `pack`. c2.dll has no instruction that sets the bit, so the front end supplies it.
3. **A define of `inline` does not reach the constructors.** They are defined in their class without the word
   `inline`. `-Dinline=__forceinline` for the whole file gives 4662 differences and frame 0xa14.
   `-D__inline=__forceinline` changes nothing. The define placed around one standard header only (`<math.h>`,
   `<new>`, `<windows.h>`, `<string>`, `<vector>`, `<list>`, `<map>`, the three containers, the four library
   headers, all seven) gives 10351 differences each, with frame 0x9e4 or 0x9e8.
4. **The game's own inline functions do not have the flag.** `__forceinline` on the input getter
   (0x00405f00) gives frame 0x9f8 but 3335 differences: a flagged callee ignores the count limit, so the two
   calls of that getter late in `padconfig` inline, and the game has calls there. On `GetSubject` it gives 12173
   differences. On the `SOCIniFile` constructor, the destructor or both it gives 10351 differences and frame
   0x9e8. No combination of the four fits. A flagged callee fits only when it is never a candidate of its own
   after the count passes the limit. The list constructors are such callees: they sit inside `begin()`.
5. **The debug-info form plays no part.** Without `-Z7`, with `-Zi` and with `-Zd` the result is the stock one
   (10351 differences, frame 0x9e4). `-ZI` does not combine with `/Ob1`.
6. **No callee has two sizes in one compile.** The trace of all inline candidates of the file shows one size
   per function.

So two texts of the list iterator constructors give the game's bytes: one without the `_Adopt` call and one
with `__forceinline`. Both differ from every `<list>` copy at hand, and no compiler option, define or pragma
tested here gives either. The cause is still not known.

### Result of 2026-11-14, sixth part: the candidate list was wrong, and the stock `<list>` then fits

Tests are real compiles with the stock compiler and the stock `<list>`. The Frida script
`build/witness/c2/rule.py` (local) reads the compiler's memory, and its rule `own=D` changes the own node
count of `padconfig` by D before the inliner reads it. That rule stands for a lighter source. It is a
diagnosis and never a build step.

1. **Link-time code generation is not the cause.** In one DLL test rig the normal build gives 22020 bytes
   and frame 0x9e4, as the tree does. With stack offsets blanked it differs from the game in 68 places, the
   first at instruction 1283. The `-GL` build differs in 99 places, the first at instruction 426 (other
   exception state numbers). An optimized first `-GL` module makes it worse (frame 0x9d8).
2. **`SOCRender::FUN_00419cf0` is not an inline function.** `FUN_00501ce0` (472 bytes, group F) calls it, and
   so do `FUN_004c5390` (4 calls) and `FUN_004c9e40`. A callee of 40 nodes or fewer is never refused under
   the cap, and this setter has 21 nodes. The tree defines it in the class. That gives `padconfig` 6 inline
   candidates too many, all after the deciding constructor.
3. **`FUN_00582ad0` is `floorf` of `<math.h>`.** Its body is `(float)floor((double)x)`. Its only caller in the
   game is `padconfig` (3 calls, all after the deciding constructor), and it sits right after `padconfig`.
   The next function, 0x00582af0, is the out-of-line copy of the inline `~SOCIniFile`. So the game places
   the inline copies of this file right after `padconfig`. `atanf` on the stick line is the same kind of
   function. The tree defines `FUN_00582ad0` as a plain function, so 3 candidates are missing.
4. **The candidate count is 66, not 69.** The compiler divides the budget by the number of candidates left,
   and it counts every candidate, also those after the cap. So the count changes every share.
5. **With 66 candidates the stock header gives the game's bytes, when the own count is 10332 to 10352.**
   Source: the variant with both condition groups, with `floorf(...)` at the three calls, and a header copy
   that only declares the setter. The compiler sees 66 candidates, with `_floorf` at numbers 55, 56 and 64.
   The variant has 10883 own nodes and gives 10606 differences, frame 0x9c4. With `own=-551` to `own=-531`
   `padconfig` has 0 differences and frame 0x9f8, and all 24 annotated functions of the file equal the
   game. `own=-555` gives frame 0x9fc and `own=-527` gives frame 0x9f0. The tree's `padconfig` has 10835
   nodes, so it is 483 to 503 nodes too heavy.
6. **No other candidate count fits.** Scans of the own count, step 4, with stand-in late candidates:

   | Candidates | Best result |
   | --- | --- |
   | 63 | 18 differences, frame 0x9f8, at own -904 to -888 |
   | 65 | no match in -791 to -558 |
   | 66 | 0 differences at own -551 to -531 |
   | 67 | no match in -423 to -178 |
   | 68 | 14 differences, frame 0x9f8, at own -245 to -240 (step 1) |
   | 69 | 14 differences, frame 0x9f8, at own -56 to -52 (step 1) |
   | 70 | no match in +70 to +230 |

   The 14 differences are stack offsets: one string helper inside the string constructor at number 17 is
   refused and the game inlines it, and number 41 differs too. The local emulator scan `scan_fewer.py` of
   2026-11-11 found the same single answer (3 candidates fewer, own count 10331 to 10355). It was set aside
   then, because nothing was known that removes candidates.
7. **What pins the own count.** The window edges are both at candidate 17, a string constructor: its share
   of the budget decides which string helpers inline inside it. The budget is twice the own count. A cap
   scan shows that a lower count with an unchanged budget does not fit (own unchanged, cap 35440 to 35640;
   own -270, cap 35170 to 35370: no match).
8. **Compile options do not change the own count.** Without `-Z7`, with `-Zi`, without `/GS`, with `-MD` and
   without `/DNDEBUG` it stays 10883.
9. **`InitLBOn` confirms our node counting.** It has 1589 own nodes and 28 candidates, and it equals the
   game only with an own count change of -7 to +1. So the tree's forms (braces, plain conditions) count
   right there. `DrawLBOn` equals the game at every own count from -600 to +600, so it shows nothing.
10. **Source forms that carry nodes and make no code** (price list, test functions, `/Od`):

    | Form | Nodes |
    | --- | --- |
    | A brace block `{ }` | 2 |
    | `!= 0` or `== 0` in a condition, against the plain test | 2 (3 on a `bool` call) |
    | `default: break;` | 2 |
    | A second `break;` after `break` or `return` | 1 |
    | `(int)` or `(float)` on a `double` value where the conversion is implicit anyway | 1 |
    | `(long)` on a value that goes to an `int` | 1 |
    | `(void)` on a call | 2 |
    | Two nested `if` against one `if` with `&&` | 7 |
    | The return type of a call, the call convention, line layout | 0 |

    The variant's `padconfig` has 191 brace blocks (68 hold one statement and need no braces, 14 are bare),
    55 `!= 0`, 18 `== 0`, 93 `(int)`, 11 `(long)` and 11 `(float)`. All of these together carry about 440
    nodes. The tuple list of `padconfig` has 550 scope pairs (`InitLBOn` 49, `DrawLBOn` 124): an `if` makes
    two scopes of its own, an `else`, a loop and each brace block one.
11. **Hidden candidates between the early sites do not fit with our own count.** Empty inline calls placed
    before the stick line: one such call gives 2 differing bytes at own -372 to -358, and one or two calls
    with 0 to 4 more late candidates give no match.

So the count of 66 has two supports that do not depend on each other, and it is the one count that gives
the game's bytes. The open part is the own node count: the game's `padconfig` source has about 490 nodes
fewer than the tree's, in forms that make no code. Which forms is not known. The two list constructor
texts of the fifth part fit only with the wrong count of 69.

### Result of 2026-11-14, seventh part: the plainest source is still 125 to 145 nodes too heavy

Local tools: `build/witness/hunt/noc.py` finds no-code edits in `padconfig`, and `greedy.py` keeps each edit
that leaves the game's bytes. The test compile sets the own count to 10342 (rule `ownabs=10342`, a diagnosis),
so "equal" means: this source text makes the game's code when the count is right.

1. **Edits that keep the bytes**, from the 10883-node variant of the sixth part:

   | Edit | Sites | Nodes saved |
   | --- | --- | --- |
   | Braces around one statement dropped | 65 | 130 |
   | `!= 0` dropped in a condition | 53 of 54 | 109 |
   | Cast dropped together with its parentheses, and parentheses under a hidden conversion | about 100 | 100 |
   | `== 0` written as `!x` | 15 | 34 |
   | Bare block without a declaration dropped | 8 | 16 |
   | `a = a - b` written as `a -= b` | 4 | 10 |
   | Two nested `if` written as one `&&` | 1 | 7 |

   All together: 10477 own nodes, 0 differences. The game needs 10332 to 10352.
2. **Edits that change the code**, so the game does not have them: `b = a = 0;` for two assignments (22 sites,
   all fail), the `break;` after `return 1;` dropped, `(GetFreeCamera() != 0) + 11` without `!= 0`.
3. **Price list, added.** Parentheses cost nothing, except 1 node where a hidden conversion sits right outside
   them. A dropped cast with its parentheses kept saves nothing. A declaration without a start value costs
   nothing. A cast to the same type costs 1. `int` against `long` costs 1 per mix, and so does signed against
   unsigned and an `enum` against an `int`. A member access costs 2 per level.
4. **Hidden integer conversions are not the rest.** With every `long` read as `int` the count of `padconfig`
   stays 10883. With every `unsigned` read as `signed` it is 10876.
5. **Other front-end builds count the same.** The RTM `c1xx.dll` and the `.400` hotfix `c1xx.dll`, each with
   the stock `c2.dll`, give 10883 for `padconfig`, 1589 for `InitLBOn`, 2954 for `InitStaff2`.
6. **A count-only change does not replace the rest.** The plain source with a cap of 35070 to 35245 gives 16
   differences and the right frame, and no exact match from 35000 to 35400 (step 5). The budget must drop
   too, and only the own count lowers both.

So about 135 nodes are still not explained. Every no-code form found so far is used up. Either the game's
source has a lighter form that is not in the price list, or one more input of the inliner is still wrong in
the tree (a callee size or the candidate list), with a pair of errors that cancel in the count of 66.

### Result of 2026-11-14, eighth part: the right list is in the tree; two more readings are ruled out

1. **The candidate fix is in `src/`.**
   - `SOCRender::FUN_00419cf0` is declared in the class and defined in `src/unplaced/SOCRender.cpp`.
   - `FUN_0041a7d0` moved to that file. The game stores the field there without a call. That code group is
     `/O2`, which inlines a small function of the same file without the `inline` keyword. So the setter is a
     plain member, and the three `/Od /Ob1` callers of the sixth part call it. All 16 annotated functions of
     the two files are at 100%.
   - The three calls in `padconfig` are `floorf(...)`. The definition of `FUN_00582ad0` is gone, and
     `src/header-functions.h` has a `LIBRARY` note for 0x00582ad0. It scores 100%.
   - `padconfig` now has 66 candidates, 10835 own nodes, 10600 differing bytes and a frame of 0x9cc. Its
     score drops from 82.63% to 81.48%. With the own count set to 10342 (rule `ownabs`, a diagnosis) the
     tree's file gives 0 differences and frame 0x9f8. So the tree's text makes the game's code, and only the
     weight of its no-code forms is wrong.
2. **The budget must drop, the count may stay.** Plain source of the seventh part (10477 nodes), with the
   budget of the game (rule `own=-135`) and a moved cap: every cap from 34840 to 35020 (step 20) gives the
   game's bytes. Cap 34820 gives 217 differences, cap 35040 gives 10304. In terms of the plain source: the
   budget must be 250 to 290 lower, and the running node count may be 155 lower to 25 higher.
3. **What that rules out.** Every inline event adds its nodes to the count and takes the same number from the
   budget. Item 2 allows 25 more in the count at most. So a larger callee or one more inlined callee can
   stand for about 60 of the 135 nodes at most, and at least 75 nodes must leave `padconfig`'s own source.
   This is arithmetic on the measured windows, not a compile test.
4. **One hidden empty inline call does not fit at any place.** The plain source with `hid();` at 12 places,
   own count 10300 to 10576, step 6 (the last five places: 10330 to 10570):

   | Place of the call | Best result |
   | --- | --- |
   | Before candidate 1 | 0 differences at 10336 to 10354: the window does not move |
   | Between candidates 22 and 35 (7 places) | 2 differences, frame 0x9f8, at 10516 to 10528 |
   | Between candidates 36 and 42 (3 places) | 219 differences |
   | Before candidate 43 | 219 differences |

   The 2 differing bytes are one stack offset: the string constructor at number 35 gets another inline tree.

So the open part is unchanged in size and smaller in kind: about 135 nodes, of which at least 75 are plain
source weight in `padconfig`. No form in the price list is left to remove.

### Result of 2026-11-14, ninth part: more readings ruled out, 33 nodes found

All counts are for the plain source of the seventh part (10477 own nodes). "Equal" means 0 differing bytes
and frame 0x9f8.

1. **Front-end options do not change the count.** It stays 10477 with `/EHa`, `/Zc:forScope-`, `/fp:except`,
   `/fp:fast`, `/fp:strict`, `/GF`, `/GL`, `/GR-`, `/Gy`, `/J`, `/Ob2`, `/Oi`, `/openmp`, `/RTC1`, `/vmg`, `/W4`
   and `/Ze`. The file does not compile with `/Zc:wchar_t-`, `/Za` and `/Zp1`.
2. **One more late candidate does not fit.** With `GetFreeCamera` as an inline function (67 candidates), no
   own count from 10420 to 10580 (step 4) is equal:

   | Own count | Differences | Frame |
   | --- | --- | --- |
   | 10420 to 10444 | 10316 | 0x9f4 |
   | 10447 to 10512 | 231 | 0x9fc |
   | 10516 to 10524 | 217 | 0x9f4 |
   | 10528 to 10540 | 219 | 0x9f0 |
   | 10544 to 10580 | 239 | 0x9e8 |

   So the count of 66 stands.
3. **Small inline functions without arguments do not carry the rest.** Test: statements of the first cases
   moved into `void` functions without parameters, defined before `padconfig`.
   - A function of 20, 24 or 31 nodes is inlined. With the own count set to 10342 the code is equal.
   - A function of 43 or 54 nodes is refused, and so is one with three calls. The call stays in the code.
   - An inlined function of `s` nodes takes `s - 16` from the own count and adds 16 to the running count.
     The running count may rise by 25 at most (eighth part, item 2). So such functions can stand for 24 of
     the missing nodes at most, unless other nodes leave the source too.
4. **A `delete` line weighs 32 or 24 nodes.** `delete p` weighs 32 nodes when the class of `p` has a base
   class with virtual functions, and 24 when the class itself is the root. The code is the same.
   `padconfig` has 13 such lines for texture pointers. Nine of these pointers (0x05cd2710 to 0x05cd2730) are
   read only by `padconfig`, and no code in the game writes an object to them. Test: these nine as pointers
   to the base class `Resource` give 10405 own nodes and 14 differing bytes with the stock compiler (frame
   0x9f8), and equal code with the count set to 10342. The form is not adopted: the function that
   `padconfig` calls before each `delete` takes a texture pointer (item 5).
5. **Type fixes that remove conversions without code.** Own count change, each measured alone:

   | Fix | `padconfig` | `InitLBOn` |
   | --- | --- | --- |
   | `FUN_0041c2d0` takes `Texture*`, not `void*` | -13 | not measured |
   | `DAT_05ab39ac` is a `SOCRender*`, so the six casts go | -6 | not measured |
   | The three name arrays at 0x02606b1c hold `const char*` | -6 | not measured |
   | `FUN_004b23e0` takes `Texture**` first | -3 | 0 |
   | `FUN_004b5e70` takes a pointer, so the three `(int)` casts go | -3 | not measured |
   | The empty placeholder call in one `if` is an empty statement | -2 | not measured |
   | `Texture::Load` takes `(char*, int, unsigned int, ...)` | -18 | -26: ruled out, the window of `InitLBOn` is -7 to +1 |

   The first six give 33 nodes: 10444. They are not in the tree yet.
6. **Our prototypes are not the cause.** The prototypes of all other functions that `padconfig` calls were
   checked again. No other parameter type differs.

So 91 to 113 nodes are still not explained (window 10331 to 10353). Ruled out in this part: compiler options,
a 67th candidate, hidden inline functions without arguments, and the `Load` signature.

### Result of 2026-11-14, tenth part: the six fixes together, a second control, five more readings ruled out

1. **The six type fixes together give 10444 own nodes.** Source: the plain source with the six fixes of the
   ninth part, and header copies with the same types. The stock compiler gives 233 differing bytes and frame
   0x9fc. With the own count set to 10342 (rule `ownabs`, a diagnosis) the code is equal. The other 23
   annotated functions of the file equal the game, `InitLBOn` stays at 1589 nodes and `InitStaff2` at 2954.
2. **`InitStaff2` is a second control.** It has 2954 own nodes and equals the game only with an own count
   change of -14 to +1 (-15 gives 4429 differences, +2 gives 43). Every header change must keep both
   controls inside their windows.
3. **The stream buffer getter does not return `void*`.** That type removes 9 conversions in `padconfig`
   (10435). It also removes 13 in `InitLBOn` (1576) and 5 in `InitStaff2`. `InitLBOn` then has 47 differing
   bytes and frame 0x3ac against 0x3b0. So each `Load(stream.getter(), ...)` call carries one conversion in
   the game's source.
4. **A helper for the blend mode pair does not fit.** `padconfig` sets the two blend modes at 8 places with
   the same two calls. Test: one inline function with both calls. The own count is then 10339, inside the
   window, but the code has 13869 differing bytes and frame 0x9dc. Seven of the 8 places come after the cap,
   where the compiler refuses every candidate. The game has both calls inline at all 8 places. For the same
   reason no inline helper can sit after the sixth `ReadFile` block.
5. **The `delete` weight stays 32.** In the game the constructor of `Texture` stores one vtable, and its
   destructor at 0x00922bf0 ends with a call to 0x009211b0, which stores a second vtable (0x00a5cfc0). So
   the base class has virtual functions, and the lighter form of the ninth part (item 4) is not the game's.
6. **Statement forms, added to the price list.** Two statements joined with a comma weigh the same as two
   statements. `if (c) { f(); }` weighs 25 and `if (c) f();` weighs 23. An `if` makes two scope pairs, a
   `for` without braces one.
7. **Nothing is left in the forms that make no code.** Of the 502 conversions in `padconfig`, 117 make no
   code: 44 pointer conversions at `object.method()` calls (4 of them at `FUN_0040b010`), 21 at string
   temporaries, 26 from an array to a pointer, 7 between pointer types, 11 from `unsigned` to `int` and 8 at
   the casts to the menu `enum`. `InitLBOn` has the same object calls and string literals, and its count is
   right. The 14 parenthesis nodes all group arithmetic. One nested `if` pair is left, and its outer `if`
   has an `else`.

So 91 to 113 nodes are still not explained. Ruled out in this part: the `void*` buffer getter, a blend mode
helper, any inline helper after the cap, a lighter `delete`, and the comma form.

### Result of 2026-11-15: the six type fixes are in the tree

The six fixes of the ninth part are applied to the sources, and `check.py decls` wrote the shared
declarations again.

- `FUN_0041c2d0` takes `Magic::RenderCore::Texture*`.
- `DAT_05ab39ac` is a `SOCRender*`. The casts at its method calls are gone in all files.
- The three name arrays at 0x02606b1c, 0x02606b34 and 0x02606b4c hold `const char*`.
- `FUN_004b23e0` and `FUN_004b5e70` take `Magic::RenderCore::Texture**` as first parameter. The second
  parameter of `FUN_004b23e0` stays `char*`, which gives the same count as the `void*` form of the test.
- `UNKNOWN_NO_CODE()` expands to nothing, so its use is an empty statement.

Result: `padconfig` has 10802 own nodes in the tree (10835 before). Its score stays 81.48%, because the
tree keeps its other forms. `InitLBOn` has 1589 nodes and `InitStaff2` 2953, both inside their windows. All
138 functions of the 13 files that the change touches keep their scores.

### Result of 2026-11-15, second part: `DisplayPauseMenu` is a control with `switch`, float and draw code

1. **Two more controls of the load kind, two functions that pin nothing.** `InitLB` (1364 own nodes) equals
   the game with an own count change of -4 to +4, and not with -8 or +8. `InitStaff` (2324) equals the game
   with -30 to +15, and not with -60 or +30. `DrawLB` and `DrawLBOn` equal the game at every tested count, so
   they pin nothing. Until this part no matched function tested the forms of `switch`, float and draw code.
2. **No other near match shows the budget symptom.** `FUN_004b23e0` (460 own nodes) has frame 0xa4 against
   0xa0 at every own count change from -300 to +40. Its gap has another cause.
3. **The count does not depend on the place in the file.** A copy of `padconfig` before or after it also
   counts 10444.
4. **`DisplayPauseMenu` (0x0057ae90) and `GetPauseMenuActive` (0x0057ad20) are in the tree at 100%.**
   `FUN_0057aa00` takes three arguments, as its one call pushes three. `DisplayPauseMenu` has 7568 bytes and
   frame 0x770. It holds 20 texture loads, six `switch` statements, float assignments with `? :`, a `do`
   loop, seven `DrawTexture` calls with float arguments, and calls to `SetMaterial` and
   `printPauseTexture`. The compiler sees 40 candidates: 20 string constructors, all refused, and 20 string
   destructors, all inline. The game has the same 40 choices.
5. **Its frame depends on its own count.** The refused constructors leave frame space that no code uses:
   800 bytes in the game. The tree's function has 3614 own nodes.

   | Own count | Result |
   | --- | --- |
   | 3609 | frame 0x76c |
   | 3610 to 3614 | equal to the game |
   | 3615 | frame 0x76c |
   | 3654 | frame 0x778 |
   | 3665 | frame 0x778 |
   | 3666 to 3689 | equal to the game |
   | 3690 | frame 0x77c |

   Scan: every count from 3486 to 3742 in steps of 4 or less. So a function can have more than one window.
6. **The window picks the short zero tests.** With `if (x == 0)` at the 19 load guards and `if (x != 0)` at
   the draw guard the count is 3654, and the frame is 8 bytes too large. Each short form (`if (!x)`,
   `if (x)`) saves 2 nodes. All 20 give 3614, the top of the lower window. Only the 19 give 3616, only the
   one gives 3652: both fail. The upper window needs 12 to 35 nodes more than the long forms, and no known
   form supplies them. The plain `padconfig` uses the same short forms.
7. **Forms that the code or the frame fixes.**
   - The six draw locals sit below the stream objects in the frame. So they are in a block of their own,
     after the loads.
   - One `DrawTexture` call has `0.0 * x` as first argument: the game loads the zero (`fldz`) and multiplies
     on the stack (`fmulp`). The six other calls have `x * 0.0`, which gives one `fmul` with a memory
     operand. `0.0f * x` and `0 * x` give the same code as `0.0 * x`.
   - A local's name decides its place inside its scope, so the placeholder names carry a suffix where needed.
8. **Price list, added.** A cast of a constant to an `enum` costs nothing against a named enumerator. A
   `(int)` or `(long)` cast with parentheses on a float expression at a call argument costs 1 against the
   hidden conversion (27 against 26 nodes). The same cast on a plain variable costs nothing, and so does
   `(long)(a == b)`.
9. **What this means for `padconfig`.** `DisplayPauseMenu` is written in the plain forms and has at most 4
   nodes too many and none too few, if the lower window is the game's. So these forms are priced right:
   `switch` with `case` and `break`, `? :`, float assignments, `-=` and `+=` on floats, the `do` loop,
   `DrawTexture` with float arguments, `SetMaterial`, `printPauseTexture`, the casts to the menu `enum`, and
   the load block inside a `switch`. They do not hold the 91 to 113 nodes.
10. **Forms that still no control tests.** The plain `padconfig` has them, `DisplayPauseMenu` and the load
    controls have none or almost none: `&&` and `||` (22 lines), `++` and `--` (38 lines), `else` (38 lines
    against 3), bit tests with `&` (20 lines against 1), array elements (30 lines), `for` loops (18 against 1
    in `InitStaff2`), `printMenu2` calls with a compare as argument (16), `floorf` (3). The next control
    must have these forms.

Local tools for this part: `build/witness/hunt/picknames.py` (names for a wanted frame order),
`frameuse.py`, `objfn.py`, `zform.py`, and `build/witness/apply/one.sh` for the scans.

### Result of 2026-11-15, third part: the menu `exec` family pins nothing; `MDHeaderOpen` is not a control yet

1. **The unused 4-byte frame slot of rows 2, 9, 10 and 11 has a source.** `title_menu_sub_exec` (0x004c0970)
   fills a 3-byte array and passes it to `AdvaOpenDialogCsrLet`. The four other `exec` functions have the same
   slot at the same place and never use it. A scratch copy with an unused 3-byte array (or an unused `int`)
   of a name that sorts there gives each of them the game's frame. An unused local gets a frame slot at
   `/Od`, at the place its name gives it. The tree does not have this local: the checker counts an unused
   local as a forced match.
2. **The save-data copy is a struct assignment.** The game copies 0x580 bytes with `rep movsd`. A `memcpy`
   call cannot give that. A scratch copy with a 0x580-byte struct type and an assignment gives the game's
   instructions. The tree keeps `memcpy`, because the type has no layout yet.
3. **`title_menu_exec` (0x004c06f0) and `title_menu_sub_exec` are in the tree**, at 74.22% and 88.82%. The
   first differs only in the read of the loop counter 0x05b9d848: the game copies it to a temp before the
   `fild`, which is the code of a `volatile int`. The tree declares it `int`, because the checker counts a
   `volatile` global as a forced match. `file_sel_exec` (0x004b6d90) has the same two reads. The second
   differs only in the two save-data copies of item 2.
4. **With items 1 and 2, three more functions equal the game in scratch**: 0x005f25a0, 0x005f37e0 and
   `title_menu_sub_lb_exec` (0x005fa460, 2016 of 2016 bytes). The compare of the first two blanks addresses.
5. **`title_menu_sub_lb_exec` pins nothing.** It equals the game at every own count change from -800 to
   +800 (16 steps). So its three refused `clear` calls do not depend on its size, and the forms it holds
   (`&&`, `++`, `else`, array elements) stay untested.
6. **`MDHeaderOpen` (0x0059ce70) was the next candidate**: two loops, `++`, array elements, a `new`, eight
   `delete`s and one string temporary. Result so far, in scratch only:
   - The game's function has no exception frame. Of the 73 `/Od /Ob1` callers of kept library copies, it is
     the only one with a string object and no frame. A build without `/EHsc` gives the game's frame size
     (0xe8); the stock build gives 0xec plus the exception record.
   - The best form has 1440 of 1461 bytes. The game copies the result of the `new` through one more slot.
     A named pointer in between gives 1461 bytes and a frame 4 bytes too large. The stock build with
     exceptions has that extra copy, but also the state stores that the game lacks.
   - The implicit conversion to `std::string` leaves 32 unused frame bytes, the explicit `std::string(x)`
     leaves 28, as the game has. The explicit form pushes the arguments in another order than the game.
   - No tested setting gives both: `/EHs-`, `/EHc-`, `/EHa`, `_HAS_EXCEPTIONS=0`, a `throw()` constructor.
   The tree builds every file with `/EHsc` and has no per-file switch, so the function is not in the tree.
7. **What this means for `padconfig`.** No new control came out of this part. The forms of item 10 of the
   second part are still untested. Candidates left with string objects and these forms: 0x004b38e0,
   0x004abe70, 0x004b0aa0, 0x004c67f0.

Local tools for this part, in `build/witness/slot/`: `sib.sh` (added local plus struct copy), `sweep.sh`
(own count scan), `forms.py` (rough counts of source forms in the game's code), `ehscan.py`, `mdl.sh`.

### Result of 2026-11-15, fourth part: the three forms of the third part are in the tree

1. **The loop counter 0x05b9d848 is `volatile int`.** Every function that uses it keeps or gains its score.
   `title_menu_exec` goes from 74.22% to 100%. `file_sel_exec` goes from 77.37% to 100%; it also needs the
   float cast on the product, `(float)(n * 0.05)`.
2. **The save block has a layout.** `SAVE_DATA` is 0x580 bytes. The 12 globals that lay inside the block at
   0x05ccca18 are now its fields. Three of them were arrays read one element early, such as
   `M_bestScore[stg - 1]`. The copy is a struct assignment. All 241 functions of the touched files keep their
   scores, and `title_menu_sub_exec` goes from 88.82% to 100%.
3. **The three copies of `title_menu_sub_exec` declare the unused 3-byte array.** 0x005f37e0 is at 100%.
   0x005f25a0 has the game's bytes; it still counts as a trick, because it holds an `if` with an empty body.
   `title_menu_sub_lb_exec` has the game's bytes at 99.37%; the rest is the name of the folded `clear`.
4. **`data/proven-forms.csv` holds the evidence** for the `volatile` global and for the three unused locals.
   `tools/tricks.py` and `tools/fakematch.py` read it: a form with a row is no trick.
5. **Not done:** a build without `/EHsc` for `MDHeaderOpen`. The best form still misses 21 bytes, so the
   switch proves nothing yet.
6. **`padconfig` does not change.** These functions pin no inline decision.

### Result of 2026-11-15, fifth part: the main loop holds source that makes no code

The main loop 0x004abe70 is the first of four controls. It is in `src/main.c` at 94.97%.

1. **One `if` with an empty body is in the game's source.** It sits after the frame rate statement. It makes
   no code, but the compiler takes one register for its condition. So the three bit tests after it use the
   next register in the game. With that `if`, a scratch build has the game's 2478 bytes, and only 27 bytes
   differ: all are frame offsets.
2. **What such forms cost at `/Od`:**

   | Form                                                      | Code | Register step | Own nodes       |
   | --------------------------------------------------------- | ---- | ------------- | --------------- |
   | `if (c) { }` with a constant, a byte global or a folded const local | none | one | +9          |
   | `if (dwordGlobal) { }`, `__noop(...)`, `0 && (...)`       | none | none          | not measured    |
   | `MAYBE_ASSERT()`                                          | none | none          | +2              |
   | call of an empty inline function, 3 computed arguments    | none | none          | +8, one site    |
   | `if (0) { real code }`                                    | `xor`, `je` | one    | not measured    |

   The empty inline call can also grow the frame (+8 bytes seen).
3. **The frame gives the hidden node count.** Own count of the visible code plus the empty `if`: 1327. The
   frame is the game's (0x1e8, 0 byte differences) at +16, +24 and +48 to +88 nodes. It is 0x1dc from -40 to
   +8, and 0x1f0 at +32, +40 and +96 to +112. So the game's function holds about 16 to 31, or 48 to 95, more
   nodes of source that makes no code. The scan steps by 8.
4. **Three constants are stored and never read:** 45, 16 and 356. Together with the frame rate value, this
   fits a display of the frame rate that the build compiles out. The condition and the body are unknown.
5. **The tree holds it as a placeholder.** `if (UNKNOWN_CONDITION) { UNKNOWN_NO_CODE(); }` stands for the
   test. `UNKNOWN_CONDITION` is a new placeholder in `src/include/decls.h`. The function is at 94.97% with it
   (86.22% without); the rest is the frame of item 3.
6. **Global types fixed on the way,** each from how the exe reads the global: the two file tables at
   0x05b3e308 and 0x05b3e320 have 6 entries (the release loops run 0 to 5, and the next global starts 24
   bytes on); the words behind them are globals of their own; 0x05cc3631 is `unsigned char` (read with
   `movzx`). No score drops.
7. **Meaning for `padconfig`:** source that makes no code can only raise the own count. `padconfig` needs
   91 to 113 nodes less, so this does not close its gap. It shows that such source exists in this code base,
   and it gives the cost of each form.

Local tools for this part, in `build/witness/slot/`: `reg.sh` (build one variant and list the register lines),
`nd.py` (line by line compare), `ed/` (the variants).

### Result of 2026-11-15, sixth part: `LoadGameDDS` is 39 to 41 nodes short, and what each form costs

`LoadGameDDS` (0x004b0aa0) is the second control. It is in `src/unplaced/LoadGameDDS.cpp` at 93.77%, in its
plain form: 14 file loads with `Load`, 6 calls of `FUN_004b23e0`, two `switch` blocks on the language.

1. **The plain form has the game's code and a smaller frame.** 3708 of 3708 bytes; 55 bytes differ, all frame
   offsets. The frame is 0x42c, the game's is 0x458. The own count is 1916.
2. **The frame is the game's only at +39, +40 and +41 nodes.** Scan from -80 to +280 in steps of 8, and each
   count from 33 to 47. So the game's source of this function holds 39 to 41 nodes that make no code. A window
   between two coarse steps above +47 is not ruled out.
3. **Costs of forms that make no code, measured in this function:**

   | Form                                                        | Own nodes     |
   | ----------------------------------------------------------- | ------------- |
   | implicit conversion of an argument (`char *` to `void *`, `unsigned` to `int`) | +1 each |
   | conversion of a constant argument (`1` to `bool`, `0` to a pointer) | 0      |
   | `p == 0` in place of `!p`                                   | +2 each       |
   | `(void)` cast on a call whose result is dropped             | +2 each       |
   | `MAYBE_ASSERT()`                                            | +2 each       |
   | `new T()` in place of `new T`                               | 0             |
   | call of a base class method on a derived object             | +7 each       |

4. **One form fits by count: 2 nodes at each of the 20 calls.** 20 `MAYBE_ASSERT()` lines, one after each
   `Load` and each `FUN_004b23e0` call, give the game's bytes (own count 1956). 14 lines give 1944 and do
   not fit. The place of the lines is not proven: only the count is.
5. **A `(void)` cast on every `Load` call in the tree is ruled out.** It breaks `InitStaff2`, `DisplayPauseMenu`,
   `InitLBOn` and `InitLB` (each frame grows by 8 or 12 bytes). So the extra nodes are not part of every
   `Load` call. They belong to this function.
6. **The getter and `Load` types hold.** With exact argument types the count is 1888, 28 lower. The four
   functions of item 5 match with the present types, so their conversions are real.
7. **The function has a static that nothing reads:** `static int DAT_05b422ec = DAT_05b3ebbc;`. `padconfig` has
   statics that hold a time stamp. This fits code that measures or reports the loads and that the build
   compiles out.
8. **The other two controls have the game's code as scratch drafts.** 0x004c67f0 (3524 bytes) and 0x004b38e0
   (8676 bytes): no instruction is missing, extra or on another register. Slots of locals are still in
   another order. They are not in the tree yet.
9. **Meaning for `padconfig`:** two functions now show source that makes no code (about 16 to 31 nodes in the
   main loop, 39 to 41 here). Both need more nodes, `padconfig` needs less. What can lower a count is in the
   table: an argument type that is wrong in the tree costs 1 node per call, and `== 0` costs 2 more than `!`.

Local tools for this part, in `build/witness/ctl/`: `BRIEF.md` (the brief for a draft), `one.sh` (own count
and compare of one variant), `rep.py` (make a variant), `voidload.py`, and one folder per control.

### Result of 2026-11-15, seventh part: the forms that the tree's `padconfig` still holds

A count of the source forms that carry nodes and make no code, per function, as the tree has them now:

| Function           | Lines | `!= 0` | `== 0` | `if (x)` | `if (!x)` | `(int)` | `(long)` | `(float)` | `x = x +` | `++` `--` |
| ------------------ | ----- | ------ | ------ | -------- | --------- | ------- | -------- | --------- | --------- | --------- |
| `padconfig`        | 1557  | 43     | 4      | 10       | 12        | 90      | 11       | 11        | 4         | 38        |
| `DisplayPauseMenu` | 380   | 0      | 0      | 1        | 19        | 0       | 0        | 0         | 0         | 1         |
| `InitLBOn`         | 97    | 0      | 1      | 0        | 0         | 0       | 0        | 0         | 0         | 0         |
| `InitLB`           | 89    | 0      | 1      | 0        | 0         | 0       | 0        | 0         | 0         | 0         |
| `InitStaff2`       | 124   | 1      | 3      | 0        | 1         | 0       | 0        | 1         | 30        | 0         |
| `InitStaff`        | 76    | 0      | 0      | 0        | 1         | 0       | 0        | 0         | 30        | 0         |
| `LoadGameDDS`      | 137   | 0      | 0      | 0        | 5         | 0       | 0        | 0         | 0         | 0         |

1. **These forms are the ones of the seventh part of 2026-11-14.** Its plainest source drops them and is still
   too heavy. So the count gives no new saving. The 91 to 113 nodes stay open.
2. **No matched control holds `(int)`, `(long)` or `!= 0` in number.** `DrawLB` and `DrawLBOn` hold 260 and
   more `(int)` casts, but they equal the game at every own count. So no control pins the price of a cast.
3. **`x = x + 1` is a form of the game's source.** `InitStaff` and `InitStaff2` hold 30 such lines each and
   are inside their windows.
4. **Three calls of a base class method.** `padconfig` calls `FUN_0092b1b0`, a method of `IniFile`, on a
   `SOCIniFile` local three times. Such a call costs 7 nodes more than a call of a method of the object's own
   class. So these calls hold 21 nodes at most. No control has this call, so the price is not tested there.

Local tool for this part: `build/witness/ctl/formcount.py`.

## The full record

The long record, the traces and the scripts are local research files and not in this repo:
`work/research/inline-1103/fable-1111.md` (sections 1, 8 and 9) and the folder `fable-1111/` next to it. From
the repo root:

```
.venv/Scripts/python.exe -I work/research/inline-1103/fable-1111/refs.py data 0x05cd2828 0x05cd2820 0x05edd970
.venv/Scripts/python.exe -I work/research/inline-1103/fable-1111/refs.py calls 0x005fb840 0x004bab50
.venv/Scripts/python.exe -I work/research/inline-1103/fable-1111/intree.py plain spec
```
