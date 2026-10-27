#include "decls.h"
extern int DAT_05edcca0;
extern struct NJS_SPRITE DAT_05edcc80;
extern struct NJS_TEXANIM DAT_02675d70;

// FUNCTION: SADX 0x005db5f0
float FUN_005db5f0(float param_1, float param_2, float param_3, int param_4)
{
	float local_8;

	if ((DAT_05edcca0 & 1) == 0)
	{
		DAT_05edcca0 = DAT_05edcca0 | 1;
		DAT_05edcc80.sx = 1.0f * ScreenRaitoX;
		DAT_05edcc80.sy = 1.0f * ScreenRaitoY;
		DAT_05edcc80.ang = 0;
		DAT_05edcc80.tlist = &texlist_con_regular;
		DAT_05edcc80.tanim = &DAT_02675d70;
	}
	DAT_05edcc80.p.x = param_1 * ScreenRaitoX;
	DAT_05edcc80.p.y = param_2 * ScreenRaitoY;
	local_8 = param_3;
	if (local_8 >= -3.0f && local_8 < 12048.0f)
	{
		local_8 = local_8 + 22048.0f;
	}
	late_DrawSprite2D(&DAT_05edcc80, param_4, local_8, 0x20, 4);
	return 16.0f;
}
