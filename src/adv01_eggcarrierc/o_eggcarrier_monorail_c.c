#include "decls.h"
extern int DAT_05b9d838;
void late_DrawObjectClipEx(struct obj *, int, float);

// STUB: SADX 0x006a2520
void MonorailAnimater(struct task *tp)
{
}

// FUNCTION: SADX 0x006a2880
void MonorailCarDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	if (tp->ptp->twp->mode == 2)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	njRotateXYZ(0, var1->ang.x, var1->ang.y, var1->ang.z);
	late_DrawObjectClipEx((struct obj *)var1->timer.ptr, 0, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x006a2a80
void MonorailDestructor(struct task *tp)
{
	FreeTaskC(tp);
	if (tp->mwp != NULL)
	{
		if (tp->mwp->ang_spd.x != 0)
		{
			Free((void *)tp->mwp->ang_spd.x);
		}
		Free(tp->mwp);
		tp->mwp = NULL;
	}
}
