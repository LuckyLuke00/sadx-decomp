#include "decls.h"
void late_ReleaseTexture(struct NJS_TEXLIST *tl);
extern struct TEX_PVMTABLE *ListofPlayersPvmList[9];
extern char DAT_05cc3554[9];
void PvrLoadtexture(struct NJS_TEXLIST *texlist);
long FUN_00423e50(const char *param_1, struct NJS_TEXLIST *param_2);
extern struct NJS_TEXLIST *DAT_05cc3540[5];
extern struct NJS_TEXLIST *DAT_05cc25b0[1];

#pragma optimize("", off)
// STUB: SADX 0x005019e0
void PvrLoadtexture(struct NJS_TEXLIST *texlist)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00501b40
void LoadPlayersTexture(long pno)
{
	struct TEX_PVMTABLE *local_8;

	local_8 = ListofPlayersPvmList[pno];
	if (local_8 != 0)
	{
		if (DAT_05cc3554[pno] == 0)
		{
			while (local_8->ptexlist != 0)
			{
				if (local_8->pname == 0)
				{
					PvrLoadtexture(local_8->ptexlist);
				}
				else
				{
					texLoadTexturePvmFile(local_8->pname, local_8->ptexlist);
				}
				local_8 = (struct TEX_PVMTABLE *)((char *)local_8 + 8);
			}
			if (pno == 5)
			{
				ERobCtrlInit();
			}
		}
		DAT_05cc3554[pno]++;
	}
}

// FUNCTION: SADX 0x00501bd0
void ReleasePlayersTexture(long pno)
{
	struct TEX_PVMTABLE *local_8 = ListofPlayersPvmList[pno];
	if (!local_8)
	{
		return;
	}
	else
	{
		if (DAT_05cc3554[pno] == 1)
		{
			while (local_8->ptexlist)
			{
				if (local_8->ptexlist->textures->texaddr)
				{
					late_ReleaseTexture(local_8->ptexlist);
				}
				local_8++;
			}
		}
		if (0 < DAT_05cc3554[pno])
		{
			DAT_05cc3554[pno]--;
		}
	}
}

// FUNCTION: SADX 0x00501c60
void ReleaseAllPlayersTexture()
{
	int local_8g;
	struct TEX_PVMTABLE *local_cg;

	for (local_8g = 0; local_8g < 9; local_8g++)
	{
		local_cg = ListofPlayersPvmList[local_8g];
		if (local_cg == 0)
		{
			continue;
		}
		else
		{
			if (DAT_05cc3554[local_8g] > 0)
			{
				while (0 != local_cg->ptexlist)
				{
					late_ReleaseTexture(local_cg->ptexlist);
					local_cg = (struct TEX_PVMTABLE *)((char *)local_cg + 8);
				}
			}
			DAT_05cc3554[local_8g] = 0;
		}
	}
}

// STUB: SADX 0x00501ce0
void LoadTextureForEachGameMode(long gamemode)
{
}

// STUB: SADX 0x00502210
long SetRegularTexture()
{
	return (long)0;
}

// FUNCTION: SADX 0x00502240
long CheckObjectTexture()
{
	if (DAT_05cc3540[1] != 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// STUB: SADX 0x00502260
long SetObjectTexture()
{
	return (long)0;
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

#pragma optimize("", off)
// STUB: SADX 0x00502980
void texLoadTexturePvmFile(char *fname, struct NJS_TEXLIST *ptlo)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00502a90
long LoadPvmMEM2(const char *filename, struct NJS_TEXLIST *texlist)
{
	___OutputDebugString("LoadPvmMEM2 - %s\n", filename);
	return FUN_00423e50(filename, texlist);
}
