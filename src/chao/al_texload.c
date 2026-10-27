#include "decls.h"

// STUB: SADX 0x00442460
void AL_LoadTex(char *filename, struct NJS_TEXLIST *pTexlist, unsigned short lev)
{
}

#pragma optimize("", off)
// STUB: SADX 0x004424c0
void AL_ReleaseTex(unsigned short lev)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00442520
void FUN_00442520()
{
	int var1;
	for (var1 = 0; var1 < 4; var1++)
		AL_ReleaseTex((unsigned short)var1);
}

// STUB: SADX 0x00442540
void AL_InitTexLoad()
{
}
