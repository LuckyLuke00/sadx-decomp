#include "decls.h"

// FUNCTION: SADX 0x007f1350
void KiraiDisp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	if (StageEventCheck())
	{
		return;
	}
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	___njSetTexture(&texlist_shooting0);
	FUN_0067d2d0(0, 2.0f, 2.0f, 2.0f);
	late_ActionEx((struct NJS_ACTION *)&action_stene_s_kibody, var1->counter.f, 0, 2.0f);
	njPopMatrix(1);
}
