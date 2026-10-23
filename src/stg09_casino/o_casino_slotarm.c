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
		___dsAction(action_cas_obj_slot_arm, var1->counter.f, 1.0f);
	}
	njPopMatrix(1);
}
