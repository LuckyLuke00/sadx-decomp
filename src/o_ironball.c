#include "decls.h"
extern "C" double fabs(double param_1);

// GLOBAL: SADX 0x04c2e808
static struct CCL_INFO object_c_info[2];

extern struct obj DAT_05a7ecc0;
extern int DAT_05b9d838;

// FUNCTION: SADX 0x008bc9f0
void ObjectIronBallCheckFlag(struct taskwk *twp)
{
	int local_8g;
	int local_cj;
	float local_10m;
	float local_14;
	twp->smode = 0;
	twp->timer.f = twp->pos.y;
	if (twp->scl.x > 50.0)
		twp->scl.x = 50.0f;
	if (twp->scl.x < -5.0)
		twp->scl.x = -5.0f;
	twp->ang.y &= 0xffff;
	if (twp->ang.y <= 0x7fff && twp->ang.y > 0x1000)
		twp->ang.y = 0x1000;
	if (twp->ang.y >= 0x8000 && twp->ang.y < 0xf000)
		twp->ang.y = 0xf000;
	local_8g = (int)twp->scl.z;
	local_cj = local_8g % 1000;
	local_10m = (float)local_cj;
	local_14 = fabs(local_10m);
	local_8g = (int)local_14;
	if (local_8g >= 100)
		twp->smode |= 4;
	local_8g %= 100;
	if (local_8g >= 10)
	{
		if (local_8g >= 90)
			twp->smode |= 0x10;
		else
			twp->smode |= 2;
	}
	local_8g %= 10;
	if (local_8g >= 1)
		twp->smode |= 1;
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
		njRotateX(0, (Uint16)local_8->ang.x);
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

// FUNCTION: SADX 0x008bd640
void ChildIronRing(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	local_8->counter.ptr = &DAT_05a7ecc0;
	if (FUN_004c39c0(tp) == 0)
		CCL_Init(tp, &object_c_info[1], 1, 4);
	tp->dest = (void (__cdecl *)(struct task *))FUN_008be060;
	tp->exec = ChildIronRingRegular;
	tp->disp = ChildIronRingDisplayer;
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
