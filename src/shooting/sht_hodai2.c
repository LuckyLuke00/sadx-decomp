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
	njRotateXYZ(0, var1->ang.x, var1->ang.y, var1->ang.z);
	___njSetTexture(&texlist_shooting0);
	late_DrawObjectClipEx((struct obj *)&object_edv_f_futa_f_futa, 4, 1.0);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x007f1be0
void FUN_007f1be0(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;
	struct NJS_POINT3 local_14;

	local_14.x = 0.0f;
	local_14.y = 6.0f;
	local_14.z = 0.0f;
	var1->timer.w[0]++;
	if ((var1->timer.w[0] & 3) == 0)
	{
		CreateSmoke(&var1->pos, &local_14, 9.0f);
	}
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
	njRotateXYZ(0, var1->ang.x, var1->ang.y, var1->ang.z);
	FUN_0067d2d0(0, 1.0, 1.0, -1.0);
	___njSetTexture(&texlist_shooting0);
	late_ActionEx((struct NJS_ACTION *)&action_tekkyu_s_tekkyu, var1->counter.f, 4, 1.0);
	njPopMatrix(1);
}
