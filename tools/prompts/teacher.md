# Recipe brief: {address}

You are the teacher. Match function {address} in {file} to 100%, then write the plan you followed, so a smaller
model can follow it. Your checkout is {root}. Work only there.

## Rules

1. Solve from this brief, the target's assembly and the checkout's own files only. Never read another checkout,
   another clone of this repository, its build folders, or any local table or symbol file outside {root}/src and
   {root}/data that the brief doesn't name.
2. Edit only {file}, and in it only the function at {address}. Leave every other source as it is: the check fails
   when another source changed.
3. Plain C or C++ only. No `__asm`, no `#pragma` that changes the code, no `volatile`, no `__declspec(naked)`, no
   macro that hides one of these. The check fails a function that matches through a trick.
4. Score a try from {root}: `python tools/recipes.py score {address}`. It builds the file and prints the percent and
   the diff. Stop at 100%.
5. When it reaches 100%, write {folder}/recipe.md: the plan, as 1 to 12 short numbered steps. Each step says what the
   assembly shows and what that means for the C, in words. No code: no code block and no line with `;`, `{` or `}`.
   Name a type, a field, a global or a call when the step needs it. Say the step that was hard to find, such as an
   order of statements, a cast, a signed type or a loop form the compiler keeps.
6. Then run `python tools/recipes.py check {folder}` from {root}. It passes only with the score at 100%, no trick, no
   other source changed and a plan without code. Fix what it reports.
7. If you can't reach 100%, stop and say the best percent and what blocks it. Don't write recipe.md.

End with one line: the check's result, the best percent, and the tries you scored.
