#include "decls.h"
void FUN_006bc4a0(int param_1, int param_2);

// STUB: SADX 0x006bc4a0
void FUN_006bc4a0(int param_1, int param_2)
{
}

// FUNCTION: SADX 0x006bc660
long LoadMapPAST(unsigned short act)
{
	switch (act)
	{
		case 0:
			texLoadTexturePvmFile("map_past_s", &texlist_mapPAST);
			break;
		case 1:
			texLoadTexturePvmFile("map_past_e", &texlist_mapPAST);
			break;
		default:
			return 0;
	}
	FUN_004b6460(&texlist_mapPAST, "mapPAST");
	return 1;
}

// FUNCTION: SADX 0x006bc840
void DestroyMapPAST(unsigned short act)
{
	FUN_004b6520((int)&texlist_mapPAST);
	late_ReleaseTexture(&texlist_mapPAST);
}

// STUB: SADX 0x006bc860
void FUN_006bc860(struct task *param_1)
{
}

// STUB: SADX 0x006bc910
void AnimAct2Waters(struct task *tp)
{
}

// STUB: SADX 0x006bc960
void AnimAct3Waters(struct task *tp)
{
}

// STUB: SADX 0x006bca20
void Bg_Past(struct task *tp)
{
}
