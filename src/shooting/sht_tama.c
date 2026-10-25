#include "decls.h"
extern int DAT_05b9d838;
extern struct obj object_stef_s_pshot_s_pshot[1];

// FUNCTION: SADX 0x007ef700
void TamaDraw2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (var1->wtimer >= 0xb4)
	{
		return;
	}
	if (DAT_05b9d838)
	{
		return;
	}
	___njFogDisable();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	njRotateXYZ(0, var1->ang.x, var1->ang.y, var1->ang.z);
	FUN_0067d2d0(0, 1.0, 1.0, -1.0);
	___njSetTexture(&texlist_shooting0);
	late_DrawObjectEx((struct obj *)&object_stef_s_pshot_s_pshot, 4);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x007ef7b0
void TamaDead(struct task *tp)
{
	tp->awp = NULL;
}

// STUB: SADX 0x007efc60
void FUN_007efc60(struct task *tp)
{
}
