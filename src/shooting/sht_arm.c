#include "decls.h"

// FUNCTION: SADX 0x007f0970
void ArmDisp(struct task *tp)
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
	njRotateXYZ(0, var1->ang.x, var1->ang.y, var1->ang.z);
	___njSetTexture(&texlist_shooting0);
	ds_ActionClip((struct NJS_ACTION *)&action_edv_f_arm, var1->counter.f, 1.0f);
	njPopMatrix(1);
}
