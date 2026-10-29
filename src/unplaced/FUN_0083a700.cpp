#include "decls.h"

// FUNCTION: SADX 0x0083a700
void FUN_0083a700(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;
	struct obj *var2 = *(struct obj **)((char *)com_objtbl + (var1->smode << 4));
	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_obj_skydeck);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		___dsDrawObject(var2);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x0083a790
void FUN_0083a790(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;
	if (var1->counter.ptr != 0)
	{
		WithdrawCollisionEntry(param_1, (struct obj *)var1->counter.ptr);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
		var1->counter.ptr = 0;
	}
	var1 = param_1->twp;
	Free(var1->value.ptr);
	var1->value.ptr = 0;
	Free(var1->timer.ptr);
	var1->timer.ptr = 0;
	FreeTaskC(param_1);
}
