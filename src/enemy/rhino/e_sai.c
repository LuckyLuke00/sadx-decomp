#include "decls.h"
void FUN_008d88b0(struct taskwk *param_1, struct enemywk *param_2);
extern struct NJS_MATERIAL matlist_rhino_jet[1];

// FUNCTION: SADX 0x008d8580
void FUN_008d8580(int param_1, char *param_2)
{
	matlist_rhino_jet[0].attr_texId = (int)((unsigned char)(*(char *)(param_1 + 3)) % 3);
	matlist_rhino_jet[0].diffuse.argb.b = (char)((char)*param_2 + 3);
}

// FUNCTION: SADX 0x008d8710
void FUN_008d8710(struct taskwk *param_1, struct enemywk *param_2)
{
	EnemyCheckGroundCollision(param_1, param_2);
}

// FUNCTION: SADX 0x008d8800
void FUN_008d8800(int param_1, int param_2, int param_3)
{
	if (*(int *)(param_2 + 0xc) != 0)
	{
		Free(*(void **)(param_2 + 0xc));
	}
	if (*(int *)(param_2 + 0x10) != 0)
	{
		Free(*(void **)(param_2 + 0x10));
	}
	((void (*)(int, int, int))FUN_005b5aa0)(param_1, param_2, param_3);
}

// FUNCTION: SADX 0x008d8850
void SaiNormal(struct taskwk *twp, struct enemywk *ewp)
{
	SaiCatAnimation(twp, ewp);
	SaiMove(twp, ewp);
	FUN_008d8710(twp, ewp);
	FUN_008d88b0(twp, ewp);
	SaiDraw(twp, ewp);
}
