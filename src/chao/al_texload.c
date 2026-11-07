#include "decls.h"
extern struct NJS_TEXNAME DAT_05b07030[];
extern struct NJS_TEXNAME DAT_05b06830[1];

// STUB: SADX 0x00442460
void AL_LoadTex(char *filename, struct NJS_TEXLIST *pTexlist, unsigned short lev)
{
}

// FUNCTION: SADX 0x004424c0
void AL_ReleaseTex(unsigned short lev)
{
	struct NJS_TEXNAME *var1;
	struct NJS_TEXNAME *var2;
	int var3;
	var1 = (struct NJS_TEXNAME *)((char *)&DAT_05b06830[0] + (lev << 0xb));
	var2 = (struct NJS_TEXNAME *)((char *)&DAT_05b07030[0] + (lev << 0xb));
	var3 = var1->attr;
	while (var3 != 0 && var1 < var2)
	{
		late_ReleaseTexture((struct NJS_TEXLIST *)var1->attr);
		___OutputDebugString("Release TEXLIST_%s\n", var1->filename);
		var1->attr = 0;
		var1->filename = 0;
		var1 = (struct NJS_TEXNAME *)((char *)var1 + 8);
		var3 = var1->attr;
	}
}

// FUNCTION: SADX 0x00442520
void FUN_00442520()
{
	int var1;
	for (var1 = 0; var1 < 4; var1++)
		AL_ReleaseTex((unsigned short)var1);
}

// FUNCTION: SADX 0x00442540
void AL_InitTexLoad()
{
	void *var1;
	int var2;

	var1 = &DAT_05b06830[0];
	do
	{
		var2 = 0x100;
		do
		{
			*(int *)((char *)var1 + 4) = 0;
			*(int *)var1 = 0;
			var1 = (char *)var1 + 8;
			var2 = var2 - 1;
		} while (var2 != 0);
	} while ((int)var1 < (int)&DAT_05b08830);
}
