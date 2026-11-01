#include "decls.h"
extern struct NJS_MODEL *rotate_model[10];
extern void TornadeInUpObject(struct task *tp);

// STUB: SADX 0x00806270
void RotateObj(struct task *tp)
{
}

// FUNCTION: SADX 0x00806440
void TornadeInUpObject(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	switch (var1->mode)
	{
	case 0:
		var1->mode = 1;
		{
			int var2 = 0;
			while (var2 < 10)
			{
				struct task *var3 = CreateChildTask(2, RotateObj, tp);
				*(struct NJS_MODEL **)((char *)var3->twp + 0x10) = rotate_model[var2];
				var3->twp->pos.y = var1->pos.y;
				var2++;
			}
		}
		SetFreeCameraMode(1);
		break;
	case 1:
		var1->wtimer++;
		if (var1->wtimer < 0x96)
		{
			LoopTaskC(tp);
		}
		else
		{
			FreeTaskC(tp);
			FreeTask(tp);
		}
		break;
	}
}

// STUB: SADX 0x008064d0
void ObjectWindySetInEff(struct task *tp)
{
}
