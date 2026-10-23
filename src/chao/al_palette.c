#include "decls.h"

// FUNCTION: SADX 0x00437b50
void AL_PaletteInit(struct task *tp)
{
	*(void **)((char *)tp->twp + 0x684) = syMalloc(0x60);
}

// FUNCTION: SADX 0x00437b70
void AL_PaletteFree(struct task *tp)
{
	syFree(*(void **)((char *)tp->twp + 0x684));
}

// STUB: SADX 0x00437b90
void alpalSetBank(struct task *tp, int cno)
{
}
