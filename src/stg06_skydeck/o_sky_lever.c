#include "decls.h"
extern int DAT_060d0acc;
extern int DAT_060d0ad0;

// FUNCTION: SADX 0x0083e500
void dispSkyLever(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
	}
	SetObjectTexture();
	ds_DrawModelClip((struct NJS_MODEL *)*(void **)((char *)*(void **)((char *)var1 + 8) + 4), 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0083e590
void exitSkyLever(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (*(void **)((char *)var1 + 8))
	{
		WithdrawCollisionEntry(tp, (struct obj *)*(void **)((char *)var1 + 8));
		ReleaseMobileLandObject((struct obj *)*(void **)((char *)var1 + 8));
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
	if (*(void **)((char *)var1 + 8))
	{
		WithdrawCollisionEntry(param_1, (struct obj *)*(void **)((char *)var1 + 8));
		ReleaseMobileLandObject((struct obj *)*(void **)((char *)var1 + 8));
		if (param_1->ptp)
		{
			DAT_060d0acc = param_1->twp->ang.x;
			DAT_060d0ad0 = param_1->twp->ang.z;
		}
	}
}
