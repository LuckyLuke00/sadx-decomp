#include "decls.h"
void FUN_005d3b80(struct task *param_1);
extern struct NJS_TEXLIST texlist_e102_beam;
struct task;
struct taskwk;
extern int DAT_05b9d838;
extern struct NJS_ARGB DAT_02671d74;

// STUB: SADX 0x005d2d60
long FUN_005d2d60(struct task *tp, struct taskwk *tw, int param_3)
{
	return (long)0;
}

// FUNCTION: SADX 0x005d3470
void E102BeamDisplay(struct task *tp)
{
	struct taskwk *local_8g;
	int local_cg;
	local_8g = tp->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	___njSetConstantMaterial(&DAT_02671d74);
	___njColorBlendingMode(0, 0xa);
	___njColorBlendingMode(1, 0xa);
	njPushMatrix(0);
	local_cg = (local_8g->wtimer & 0x200) != 0;
	njTranslateV(0, &local_8g->pos);
	___njSetTexture(&texlist_e102_beam);
	late_DrawSprite3D(&sprite_e102_beam, local_cg, 0x30, 4);
	ResetMaterial();
	njPopMatrix(1);
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
}

// STUB: SADX 0x005d3530
void E102BeamDestruct(struct task *tp)
{
}

// FUNCTION: SADX 0x005d35b0
void E102BeamAto(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	switch (local_8->mode)
	{
		case 0:
			local_8->counter.f = 1.0;
			tp->disp = E102BeamAtoDisplay;
			local_8->mode = 1;
		case 1:
			local_8->counter.f -= 0.10000000149011612;
			if (local_8->counter.f <= 0.0)
			{
				DestroyTask(tp);
				return;
			}
	}
	E102BeamAtoDisplay(tp);
}

#pragma optimize("", off)
// STUB: SADX 0x005d3630
void E102BeamAtoDisplay(struct task *tp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x005d37c0
int calcE102ShotDir(struct taskwk *twp, struct taskwk *cwp)
{
	return (int)0;
}

// FUNCTION: SADX 0x005d3950
void SetE102BeamNoHorming(struct task *tp, struct NJS_POINT3 *vec)
{
	tp->twp->mode = 2;
	tp->twp->value.l = 0;
	if (vec != (struct NJS_POINT3 *)0)
	{
		tp->mwp->spd = *vec;
	}
}

// STUB: SADX 0x005d3990
void E102FireEffect(struct task *tp, struct playerwk *pwp, struct E102WK *ewk)
{
}

// FUNCTION: SADX 0x005d3b00
void FUN_005d3b00(struct task *param_1)
{
	struct taskwk *local_8;

	local_8 = param_1->twp;
	switch (local_8->mode)
	{
		case 0:
			local_8->counter.f = 2.0;
			local_8->mode = 1;
		case 1:
			local_8->counter.f -= 0.5;
			if (local_8->counter.f <= 0.0)
			{
				DestroyTask(param_1);
				return;
			}
	}
	FUN_005d3b80(param_1);
}

// STUB: SADX 0x005d3c40
void E102BeamRing(struct task *tp)
{
}
