#include "decls.h"

// GLOBAL: SADX 0x04ad7b68
static struct CCL_INFO ColliInfo[2];

static void ExecATask(struct task *tp);
static void DispATask(struct task *tp);

// FUNCTION: SADX 0x008aac00
static void DispATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	float var2;

	var2 = var1->counter.f;
	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	FUN_0067d830(0, 0.0f, 0.0f, var2);
	late_DrawObjectClipEx((struct obj *)&object_gt_bgatecente_bgate02, 0, 1.0f);
	var2 = var2 * -2.0;
	FUN_0067d830(0, 0.0f, 0.0f, var2);
	late_DrawObjectClipEx((struct obj *)&object_gt_bgatecente_bgate01, 0, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x008aacd0
static void ExecATask(struct task *tp)
{
}

// FUNCTION: SADX 0x008aaf20
void ObjShelterGate1(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 250000.0f) == 0)
	{
		var1->counter.f = 0.0f;
		var1->timer.f = njCos(var1->ang.y) * -1.0;
		var1->value.f = njSin(var1->ang.y);
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, &ColliInfo[0], 2, 4);
		}
		var1->mode = 1;
		tp->exec = ExecATask;
		tp->disp = DispATask;
		tp->dest = (void (*)(struct task *))FUN_007d21b0;
	}
}
