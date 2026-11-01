#include "decls.h"
extern int DAT_05edcc7c;
extern struct NJS_SPRITE DAT_05edcc5c;
extern struct NJS_SPRITE DAT_05edcc3c;
extern struct NJS_TEXANIM DAT_00997a5c;
extern struct NJS_TEXANIM DAT_00997a48;

// FUNCTION: SADX 0x005db370
void MirenScoreDisplayScoreTitle()
{
	float local_cg;
	float local_8g;

	if ((DAT_05edcc7c & 1) == 0)
	{
		DAT_05edcc7c = DAT_05edcc7c | 1;
		DAT_05edcc5c.p.x = 43.0f * ScreenRaitoX;
		DAT_05edcc5c.p.y = 30.0f * ScreenRaitoY;
		DAT_05edcc5c.p.z = 0.0f;
		DAT_05edcc5c.sx = 1.0f * ScreenRaitoX;
		DAT_05edcc5c.sy = 1.0f * ScreenRaitoY;
		DAT_05edcc5c.ang = 0;
		DAT_05edcc5c.tlist = &texlist_board_score;
		DAT_05edcc5c.tanim = &DAT_00997a5c;
	}
	if ((DAT_05edcc7c & 2) == 0)
	{
		DAT_05edcc7c = DAT_05edcc7c | 2;
		DAT_05edcc3c.p.x = 51.0f * ScreenRaitoX;
		DAT_05edcc3c.p.y = 62.0f * ScreenRaitoY;
		DAT_05edcc3c.p.z = 0.0f;
		DAT_05edcc3c.sx = 1.0f * ScreenRaitoX;
		DAT_05edcc3c.sy = 1.0f * ScreenRaitoY;
		DAT_05edcc3c.ang = 0;
		DAT_05edcc3c.tlist = &texlist_con_regular;
		DAT_05edcc3c.tanim = &DAT_00997a48;
	}
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	local_8g = -1.501f;
	if (local_8g >= -3.0f && local_8g < 12048.0f)
	{
		local_8g = local_8g + 22048.0f;
	}
	late_DrawSprite2D(&DAT_05edcc5c, 0, local_8g, 0x20, 4);
	local_cg = -1.5f;
	if (local_cg >= -3.0f && local_cg < 12048.0f)
	{
		local_cg = local_cg + 22048.0f;
	}
	late_DrawSprite2D(&DAT_05edcc3c, 0, local_cg, 0x20, 4);
}
