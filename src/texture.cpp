#include "decls.h"
void PvrLoadtexture(struct NJS_TEXLIST *texlist);
long FUN_00423e50(const char *param_1, struct NJS_TEXLIST *param_2);
extern struct NJS_TEXLIST *DAT_05cc3540[5];
extern struct NJS_TEXLIST *DAT_05cc25b0[1];

// STUB: SADX 0x005019e0
void PvrLoadtexture(struct NJS_TEXLIST *texlist)
{
}

// STUB: SADX 0x00501b40
void LoadPlayersTexture(long pno)
{
}

// STUB: SADX 0x00501bd0
void ReleasePlayersTexture(long pno)
{
}

// STUB: SADX 0x00501ce0
void LoadTextureForEachGameMode(long gamemode)
{
}

// FUNCTION: SADX 0x00502290
void ReleaseTexture()
{
	int local_8;

	for (local_8 = 1; local_8 < 5; local_8++)
	{
		if (DAT_05cc3540[local_8] == 0)
		{
			continue;
		}
		if (*(unsigned long *)((char *)DAT_05cc3540[local_8]->textures + 8) != 0)
		{
			late_ReleaseTexture(DAT_05cc3540[local_8]);
		}
		DAT_05cc3540[local_8] = 0;
	}
	local_8 = 0;
	while (DAT_05cc25b0[local_8] != 0)
	{
		late_ReleaseTexture(DAT_05cc25b0[local_8]);
		DAT_05cc25b0[local_8] = 0;
	}
	late_execCancel();
}

// STUB: SADX 0x00502330
long LoadPvmT(unsigned short stgact)
{
	return (long)0;
}

// STUB: SADX 0x005023f0
long ReleasePvmT(unsigned short stgact)
{
	return (long)0;
}

// FUNCTION: SADX 0x00502a90
long LoadPvmMEM2(const char *filename, struct NJS_TEXLIST *texlist)
{
	___OutputDebugString("LoadPvmMEM2 - %s\n", filename);
	return FUN_00423e50(filename, texlist);
}
