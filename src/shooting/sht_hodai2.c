#include "decls.h"
struct task;

// FUNCTION: SADX 0x007f1b00
void HodaiDisp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	njRotateXYZ(0, (long *)(*(long *)&var1->ang.x), (long *)(*(long *)&var1->ang.y), (long *)(*(long *)&var1->ang.z));
	___njSetTexture(&texlist_shooting0);
	late_DrawObjectClipEx((struct obj *)&object_edv_f_futa_f_futa, 4, 1.0);
	njPopMatrix(1);
}

// STUB: SADX 0x007f1be0
void FUN_007f1be0(struct task *cTask)
{
}

// FUNCTION: SADX 0x007f1c40
void HodaiTamaDraw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
	njRotateXYZ(0, (long *)(*(long *)&var1->ang.x), (long *)(*(long *)&var1->ang.y), (long *)(*(long *)&var1->ang.z));
	FUN_0067d2d0(0, 1.0, 1.0, -1.0);
	___njSetTexture(&texlist_shooting0);
	late_ActionEx((struct NJS_ACTION *)&action_tekkyu_s_tekkyu, var1->counter.f, 4, 1.0);
	njPopMatrix(1);
}
