#include "decls.h"
void ObjectReleaseBox(struct task *task_p);
void DispSphere(struct NJS_POINT3 *bp, float scale);

// FUNCTION: SADX 0x00891110
static void FUN_00891110(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;
	if (CheckCollisionP(&var1->pos, (var1->scl.x + 1.0) * 14.0) == 1)
	{
		SetFinishAction();
		var1->mode = 5;
	}
}

// FUNCTION: SADX 0x00891150
void ObjectFinalEggRelease(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct task *var2;
	if (CheckRangeOut(tp))
	{
		return;
	}
	switch (var1->mode)
	{
	case 0:
		var1->mode = 2;
		tp->disp = 0;
		break;
	case 2:
		if (SeqCheckFlag(0xaf))
		{
			var1->mode = 3;
			return;
		}
		if (!FUN_004c39c0(tp))
		{
			FUN_00891110(tp);
		}
		if (FUN_004c39c0(tp))
		{
			njPrintC(0x110013, "<- SCALE");
			DispSphere(&tp->twp->pos, (tp->twp->scl.x + 1.0) * 14.0);
		}
		break;
	case 3:
		var2 = CreateElementalTask(2, 2, ObjectReleaseBox);
		var2->twp->pos.x = var1->pos.x;
		var2->twp->pos.y = var1->pos.y;
		var2->twp->pos.z = var1->pos.z;
		var1->mode = 4;
		break;
	}
}
