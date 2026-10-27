#include "decls.h"

// FUNCTION: SADX 0x00878120
void ObjectCasinoSlotArmDraw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 62510.0f))
	{
		return;
	}
	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture2(0xc);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	if (var1->counter.f == 0.0f)
	{
		ds_DrawObjectClip(object_cas_obj_slot_arm_slot_arm, 1.0f);
	}
	else
	{
		ds_ActionClip(action_cas_obj_slot_arm, var1->counter.f, 1.0f);
	}
	njPopMatrix(1);
}

// STUB: SADX 0x00878340
void ObjectCasinoSlotArm(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 62510.0f) == 0)
	{
		struct taskwk *var1 = tp->twp;

		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, (struct CCL_INFO *)0x0480ba20, 1, 4);
		}
		tp->disp = ObjectCasinoSlotArmDraw;
		tp->exec = ObjectCasinoSlotArmExec;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		var1->counter.f = 0.0f;
		var1->wtimer = 0;
	}
}
