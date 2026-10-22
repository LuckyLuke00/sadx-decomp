#include "decls.h"
extern unsigned long DAT_05edcbb4;
extern unsigned long DAT_05edcbb0;
void FreeTask(struct task *tp);
struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
void KnuEffectChargeScl(struct task *tp);
void dispKnuEffectChargeScl(struct task *tp);
extern unsigned long DAT_05edc4d0;

// FUNCTION: SADX 0x005d7c10
void KnuEffectPutRingSpring(struct NJS_POINT3 *pos)
{
	struct task *local_8;

	local_8 = CreateElementalTask(2, 6, KnuEffectRingSpring);
	if (local_8 != NULL)
	{
		local_8->twp->pos = *pos;
	}
}

// STUB: SADX 0x005d8000
void dispKnuEffectChargeUpStay(struct task *tp)
{
}

// FUNCTION: SADX 0x005d8240
void KnuEffectChargeUpStay(struct task *tp)
{
	struct taskwk *local_8g = tp->twp;
	float local_cg = local_8g->timer.f + 0.1666666716337204f;

	local_8g->timer.f = local_cg;
	if (local_cg >= 1.0f)
	{
		FreeTask(tp);
	}
	else
	{
		KnuEffectDrawTsubu(&local_8g->pos, (1.0f - local_8g->timer.f) * local_8g->value.f);
	}
}

// STUB: SADX 0x005d8560
void KnuEffectPutCharge0()
{
}

// STUB: SADX 0x005d85d0
void KnuEffectChargeScl(struct task *tp)
{
}

// FUNCTION: SADX 0x005d8760
void KnuEffectPutCharge1()
{
	struct task *local_8 = CreateElementalTask(2, 6, KnuEffectChargeScl);
	if (local_8)
	{
		struct taskwk *local_c = local_8->twp;
		local_c->scl.x = 0.041666668f;
		local_c->scl.y = 0.6f;
		local_c->scl.z = 4.5f;
		local_c->value.f = 0.0f;
		*(float *)((char *)local_c + 8) = -1.0f;
		local_8->disp = dispKnuEffectChargeScl;
	}
}

// FUNCTION: SADX 0x005d87d0
void KnuEffectHormTubeReset()
{
	DAT_05edc4d0 = 0;
}

// FUNCTION: SADX 0x005d87e0
void FUN_005d87e0(int param_1, int param_2, int param_3)
{
	if ((DAT_05edcbb4 & 1) == 0)
	{
		DAT_05edcbb4 = DAT_05edcbb4 | 1;
		DAT_05edcbb0 = param_3;
	}
}
