#include "decls.h"
#include <stdlib.h>
void FUN_005d7240(struct task *param_1);
extern struct NJS_SPRITE sprite_tsuchi_kake;
extern struct NJS_SPRITE sprite_rader;
extern struct NJS_TEXLIST texlist_knu_eff;
extern int DAT_05b9d838;
extern unsigned long DAT_05edcbb4;
extern unsigned long DAT_05edcbb0;
void FreeTask(struct task *tp);
struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
void KnuEffectChargeScl(struct task *tp);
void dispKnuEffectChargeScl(struct task *tp);
extern unsigned long DAT_05edc4d0;

// STUB: SADX 0x005d6db0
void EffectKnuPunch(struct task *tp)
{
}

// STUB: SADX 0x005d6e50
void dispEffectKnuPunch(struct task *tp)
{
}

// STUB: SADX 0x005d6f60
void EffectKnuHadoken(struct task *tp)
{
}

// FUNCTION: SADX 0x005d7070
void dispEffectKnuHadoken(struct task *tp)
{
	struct taskwk *local_cg;
	float local_8g;

	local_cg = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		local_8g = local_cg->counter.f * 0.800000011920929f;
		SetMaterial(local_8g, 1.0f, 1.0f, 1.0f);
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 10);
		___njSetTexture(&texlist_knu_eff);
		njPushMatrix(0);
		njTranslateV(0, &local_cg->pos);
		___njDrawSprite3D(&sprite_k_hadoken, 0, 0x32);
		njPopMatrix(1);
		ResetMaterial();
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 6);
	}
}

// STUB: SADX 0x005d7140
void FUN_005d7140(struct NJS_POINT3 *pos)
{
}

// STUB: SADX 0x005d7240
void FUN_005d7240(struct task *tp)
{
}

// FUNCTION: SADX 0x005d7410
void dispEffectSpray(struct task *tp)
{
	struct taskwk *local_8g;
	int local_10;
	float local_cj;

	local_8g = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		local_10 = 0x1e - local_8g->wtimer;
		local_cj = (float)local_10 / 30.0f;
		SetMaterial(local_cj, 1.0f, 1.0f, 1.0f);
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 10);
		___njSetTexture(&texlist_knu_eff);
		njPushMatrix(0);
		njTranslateV(0, &local_8g->pos);
		___njDrawSprite3D(&sprite_k_kira, 0, 0x32);
		njPopMatrix(1);
		ResetMaterial();
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 6);
	}
}

// STUB: SADX 0x005d74f0
void KnuEffectClod(struct task *tp)
{
}

// STUB: SADX 0x005d76a0
void dispKnuEffectClod(struct task *tp)
{
}

// FUNCTION: SADX 0x005d7800
void KnuEffectDisplayRadar(struct NJS_POINT3 *pos, long patnmb, float scale, float alpha)
{
	float local_8;

	if (DAT_05b9d838 != 0)
	{
		return;
	}
	SetMaterial(alpha, 1.0f, 1.0f, 1.0f);
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	sprite_rader.p.x = pos->x - 30.0f;
	sprite_rader.p.y = pos->y;
	sprite_rader.sx = scale;
	sprite_rader.sy = scale;
	___njSetTexture(&texlist_knu_eff);
	local_8 = scale * 0.009999999776482582f + -2.0f;
	if (local_8 >= -3.0f && local_8 < 12048.0f)
	{
		local_8 = local_8 + 22048.0f;
	}
	late_DrawSprite2D(&sprite_rader, patnmb, local_8, 0x22, 4);
	ResetMaterial();
}

// STUB: SADX 0x005d78f0
void KnuEffectPutTsuchiKakera(struct NJS_POINT3 *pos, struct NJS_POINT3 *spd)
{
}

// STUB: SADX 0x005d7a80
void KnuEffectTsuchiKakeraMove(struct task *tp)
{
}

// FUNCTION: SADX 0x005d7b60
void dispKnuEffectTsuchiKakeraMove(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 6);
		___njSetTexture(&texlist_knu_eff);
		njPushMatrix(0);
		njTranslateV(0, &local_8->pos);
		if (*(int *)((char *)local_8 + 0x14) != 0)
		{
			njRotateX(0, *(unsigned short *)((char *)local_8 + 0x14));
		}
		if (*(int *)((char *)local_8 + 0x1c) != 0)
		{
			njRotateZ(0, *(unsigned short *)((char *)local_8 + 0x1c));
		}
		___njDrawSprite3D(&sprite_tsuchi_kake, 0, 0x20);
		njPopMatrix(1);
	}
}

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

// STUB: SADX 0x005d7ed0
void KnuEffectPutChargeUp(float rate)
{
}

// FUNCTION: SADX 0x005d8000
void dispKnuEffectChargeUpStay(struct task *tp)
{
	struct taskwk *local_8g = tp->twp;

	KnuEffectDrawTsubu(&local_8g->pos, (1.0f - local_8g->timer.f) * local_8g->value.f);
}

// FUNCTION: SADX 0x005d8040
void KnuEffectDrawTsubu(struct NJS_POINT3 *pos, float alp)
{
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	___njSetTexture(&texlist_knu_eff);
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 10);
	SetMaterial(alp, 1.0f, 1.0f, 1.0f);
	njPushMatrix(0);
	njTranslateV(0, pos);
	late_DrawSprite3D(&sprite_k_charge, 0, 0x32, 0);
	njPopMatrix(1);
	ResetMaterial();
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
}

// STUB: SADX 0x005d80f0
void KnuEffectChargeUp(struct task *tp)
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

// STUB: SADX 0x005d82c0
void KnuEffectComboFire(struct task *tp)
{
}

// FUNCTION: SADX 0x005d8560
void KnuEffectPutCharge0()
{
	struct task *local_8 = CreateElementalTask(2, 6, KnuEffectChargeScl);
	if (local_8)
	{
		struct taskwk *local_c = local_8->twp;
		local_c->scl.x = 0.055555556f;
		local_c->scl.y = 6.0f;
		local_c->scl.z = 1.2f;
		local_c->value.f = 0.0f;
		*(float *)((char *)local_c + 8) = -1.0f;
		local_8->disp = dispKnuEffectChargeScl;
	}
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
