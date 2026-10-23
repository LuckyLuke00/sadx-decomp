#include "decls.h"

// FUNCTION: SADX 0x00863190
void Normal1(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	float var2 = var1->timer.f;
	struct NJS_POINT3 *var3 = &var1->scl;

	if (CheckRangeOut(pTask))
	{
		return;
	}
	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	njScaleV(0, var3);
	___dsAction(action_obj_m_kusa_a, var2, FUN_004a1e90((float *)var3));
	njPopMatrix(1);
	var2 += 1.0;
	if (var2 >= 29.0)
	{
		var2 = 0.0;
	}
	var1->timer.f = var2;
}

// STUB: SADX 0x00863250
void Normal2(struct task *pTask)
{
}

// FUNCTION: SADX 0x00863310
void ObjectMizukusaA(struct task *pTask)
{
	pTask->exec = Normal1;
	pTask->disp = Normal1;
	pTask->twp->mode = 0;
	pTask->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x00863330
void ObjectMizukusaB(struct task *pTask)
{
	pTask->exec = Normal2;
	pTask->disp = Normal2;
	pTask->twp->mode = 1;
	pTask->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
