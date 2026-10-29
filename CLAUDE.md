@docs/CLAUDE-GENERIC.md

# SADX: this game's facts

Matching decompilation of 2014 Steam `Sonic Adventure DX.exe` (32-bit, VC++ 2010 SP1). reccmp target `SADX`, so annotations read `// FUNCTION: SADX 0x00401000`. README.md: version, progress. docs/STYLE.md: naming, file layout, language.

- Ghidra opens this 90 MB exe slowly. Keep one REA session open.
- Unplaced functions go in `.cpp` files (docs/STYLE.md section 4).
- Rich header shows 121 objects built with whole-program optimization (`/GL`), but not which ones or their language. Register-argument calls between code groups show some when no fold explains them, noted in `data/codegen-groups.csv` for groups A, B1, B2, B3, L. `/GL` stays off until a function proves it needs it.
