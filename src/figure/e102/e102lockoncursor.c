#include "decls.h"
extern struct NJS_SPRITE DAT_026792ec;
extern int DAT_05b9d838;
void DispMultiDigitDisplay(struct task *tp);
void FUN_005e5770(struct task *param_1);

// STUB: SADX 0x005e5440
void E102LockOnCursor_dest(struct task *tp)
{
}

// FUNCTION: SADX 0x005e54f0
void DispMultiDigit(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;

	if (DAT_05b9d838 != 0)
	{
		return;
	}
	switch (local_8->mode)
	{
	case 0:
		tp->disp = DispMultiDigitDisplay;
		local_8->mode = 1;
		break;
	}
	DispMultiDigitDisplay(tp);
}

// FUNCTION: SADX 0x005e5540
void DispMultiDigitDisplay(struct task *tp)
{
	struct taskwk *local_8g;
	int local_cg;

	local_8g = tp->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	njPushMatrix(0);
	njTranslateV(0, (struct NJS_POINT3 *)(local_8g->timer.ptr));
	if (DAT_05b42a7c->ang.y != 0)
	{
		njRotateY(0, (unsigned short)((short)DAT_05b42a7c->ang.y));
	}
	if (DAT_05b42a7c->ang.x + 0x8000 != 0)
	{
		njRotateX(0, (unsigned short)((DAT_05b42a7c->ang.x + 0x8000)));
	}
	if (slEventBossName != -1)
	{
		FUN_0067d830(0, 0.0f, -5.0f, -10.0f);
	}
	else
	{
		FUN_0067d830(0, 0.0f, 0.0f, -10.0f);
	}
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	___njDrawSprite3D(&DAT_026792ec, 0xc, 0x22);
	FUN_0067d830(0, 8.0f, 0.0f, 0.0f);
	if (local_8g->value.b[0] >= 10)
	{
		local_cg = local_8g->value.b[0] / 10;
		___njDrawSprite3D(&DAT_026792ec, local_cg, 0x22);
		FUN_0067d830(0, 8.0f, 0.0f, 0.0f);
	}
	local_cg = local_8g->value.b[0] % 10;
	___njDrawSprite3D(&DAT_026792ec, local_cg, 0x22);
	SetMaterial(0.0f, 0.0f, 0.0f, 0.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x005e5720
int FUN_005e5720(int param_1)
{
	if (param_1 == 0)
	{
		return 0;
	}
	int local_8;
	local_8 = *(int *)(param_1 + 0x2c);
	return *(int *)(local_8 + 0x14);
}

// FUNCTION: SADX 0x005e5750
struct task *GetE102LockCsTaskPointer(struct task *beam_tp)
{
	if (beam_tp == NULL)
		return NULL;
	return (struct task *)beam_tp->twp->value.ptr;
}

// STUB: SADX 0x005e5770
void FUN_005e5770(struct task *param_1)
{
}

// FUNCTION: SADX 0x005e5860
void E102LockOnCursor_dis(struct task *tp)
{
	struct taskwk *local_cg;
	struct anywk *local_8g;
	local_cg = tp->twp;
	local_8g = tp->awp;
	if (local_cg->timer.l >= 0x3c)
	{
		FreeTask(tp);
	}
	else
	{
		local_cg->timer.l += 1;
		*(int *)((char *)local_8g + 0x24) += 0x200;
		*(int *)((char *)local_8g + 0x28) += 0x300;
		tp->disp = E102LockOnCursor_dis_Disp;
		E102LockOnCursor_dis_Disp(tp);
	}
}

// FUNCTION: SADX 0x005e5bb0
void E102KillCursorOnly(struct task *tp)
{
	struct motionwk *local_8;

	if (tp == NULL)
	{
		return;
	}
	local_8 = tp->mwp;
	if (local_8 == NULL)
	{
		return;
	}
	if (*(void **)((char *)local_8 + 0x40) == NULL)
	{
		return;
	}
	if (*(void **)((char *)*(void **)((char *)local_8 + 0x40) + 0x20) != NULL)
	{
		*(short *)((char *)*(void **)((char *)*(void **)((char *)local_8 + 0x40) + 0x20) + 4) |= 0x100;
	}
	FUN_005e5770(tp);
}
