#include "decls.h"
extern int DAT_05b9d838;

// STUB: SADX 0x008bc9f0
void ObjectIronBallCheckFlag(struct taskwk *twp)
{
}

// FUNCTION: SADX 0x008bcb60
void ObjectIronBallDisplay(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (DAT_05b9d838 != 0)
		return;
	SaveConstantAttr();
	OffConstantAttr(0, 0x80000);
	SetRegularTexture();
	njPushMatrix(0);
	njTranslateV(0, &local_8->pos);
	if (local_8->ang.z != 0)
		njRotateZ(0, (unsigned short)local_8->ang.z);
	if (local_8->ang.x != 0)
		njRotateX(0, local_8->ang.x);
	ds_DrawModelClip(*(struct NJS_MODEL **)((char *)local_8->counter.ptr + 4), 1.0f);
	njPopMatrix(1);
	LoadConstantAttr();
}

// FUNCTION: SADX 0x008bd160
void FUN_008bd160(struct task *param_1)
{
	struct taskwk *local_8;

	local_8 = param_1->twp;
	if (local_8->counter.ptr != 0)
	{
		WithdrawCollisionEntry(param_1, (struct obj *)local_8->counter.ptr);
		ReleaseMobileLandObject((struct obj *)local_8->counter.ptr);
	}
	FreeTaskC(param_1);
}

// STUB: SADX 0x008bd2a0
void ChildIronBallDisplayer(struct task *tp)
{
}

// STUB: SADX 0x008bd6a0
void ChildIronRingDisplayer(struct task *tp)
{
}

// STUB: SADX 0x008bd7d0
void ChildIronRingRegular(struct task *tp)
{
}

// STUB: SADX 0x008bdf40
void ObjectIronBallJGDisplayer(struct task *tp)
{
}

// STUB: SADX 0x008be060
int FUN_008be060(struct task *param_1)
{
	return (int)0;
}

// STUB: SADX 0x008be080
void ObjectIronBallJG_Tobi(struct task *tp)
{
}
