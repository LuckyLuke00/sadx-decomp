#include "decls.h"
extern int DAT_05b9d838;

// FUNCTION: SADX 0x008bbba0
void NomalObject(struct task *tp)
{
	void (*local_8)(struct task *);
	local_8 = tp->disp;
	local_8(tp);
	CheckRangeOut(tp);
}

// FUNCTION: SADX 0x008bbfc0
void FUN_008bbfc0(struct task *param_1)
{
	long local_8;
	local_8 = ChkItemInPercent(CmnKusaRanItemTbl);
	if (local_8 == 0)
	{
		return;
	}
	MakePopUpItem((struct taskwk *)param_1, local_8);
}

// FUNCTION: SADX 0x008bbff0
void DrawCmnKusa(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if (dsCheckViewV(&local_8->pos, 10.0f) == 0)
	{
		return;
	}
	___njSetTexture((struct NJS_TEXLIST *)local_8->value.ptr);
	njPushMatrix(0);
	njTranslateV(0, &local_8->pos);
	if (local_8->ang.z != 0)
		njRotateZ(0, *(unsigned short *)&local_8->ang.z);
	if (local_8->ang.x != 0)
		njRotateX(0, local_8->ang.x);
	if (local_8->ang.y != 0)
		njRotateY(0, local_8->ang.y);
	late_DrawObjectMesh((struct obj *)local_8->counter.ptr, 0);
	njPopMatrix(1);
}
