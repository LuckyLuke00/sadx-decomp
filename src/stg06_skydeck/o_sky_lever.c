#include "decls.h"
extern int DAT_060d0acc;
extern int DAT_060d0ad0;

// FUNCTION: SADX 0x0083e500
void dispSkyLever(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (var1->ang.z != 0)
	{
		njRotateZ(NULL, (unsigned short)(short)var1->ang.z);
	}
	if (var1->ang.x != 0)
	{
		njRotateX(NULL, (unsigned short)var1->ang.x);
	}
	if (var1->ang.y != 0)
	{
		njRotateY(NULL, (unsigned short)var1->ang.y);
	}
	SetObjectTexture();
	ds_DrawModelClip((struct NJS_MODEL *)*(void **)((char *)var1->counter.ptr + 4), 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0083e590
void exitSkyLever(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (var1->counter.ptr)
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
		if (tp->ptp)
		{
			DAT_060d0acc = tp->twp->ang.x;
			DAT_060d0ad0 = tp->twp->ang.z;
		}
	}
}

// FUNCTION: SADX 0x0083e5e0
void FUN_0083e5e0(struct task *param_1)
{
	FreeTaskC(param_1);
	struct taskwk *var1 = param_1->twp;
	if (var1->counter.ptr)
	{
		WithdrawCollisionEntry(param_1, (struct obj *)var1->counter.ptr);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
		if (param_1->ptp)
		{
			DAT_060d0acc = param_1->twp->ang.x;
			DAT_060d0ad0 = param_1->twp->ang.z;
		}
	}
}
