#include "decls.h"
void FUN_0067e510(float *param_1, float param_2, float param_3, float param_4);
void setParticleDispTask(struct taskwk *twp);
extern struct NJS_TEXLIST texlist_chaos_effect;
void DestroyTask(struct task *tp);
extern struct taskwk *DAT_060df330[0x80];
extern struct NJS_SPRITE DAT_060df534;
extern struct NJS_SPRITE DAT_060df6d8;
extern struct NJS_SPRITE DAT_060df700;
extern struct NJS_SPRITE DAT_060df720;
extern struct NJS_SPRITE DAT_060df55c;
extern int DAT_060df530;
extern float DAT_060df57c;
extern float DAT_060df554;
extern float DAT_060df6fc;
extern int DAT_060df558;
extern struct taskwk *DAT_060df740[256];
extern char DAT_060df580[1];
extern float DAT_060df6f8;

// FUNCTION: SADX 0x008c4400
void LoadEffectTexture()
{
	initSpriteSub(&DAT_060df534, &texlist_chaos_effect, &anim_c0_attack_a[0]);
	initSpriteSub(&DAT_060df6d8, &texlist_chaos_effect, &anim_c0_attack_b[0]);
	initSpriteSub(&DAT_060df700, &texlist_chaos_effect, &anim_c0_attack_c[0]);
	initSpriteSub(&DAT_060df720, &texlist_chaos_effect, &anim_c0_drop[0]);
	initSpriteSub(&DAT_060df55c, &texlist_chaos_effect, &anim_c0_ato[0]);
	DAT_060df558 = 0;
	DAT_060df530 = 0;
	DAT_060df6f8 = 1.3f;
	DAT_060df6fc = 1.3f;
	DAT_060df57c = 1.0f;
	DAT_060df554 = 0.2f;
}

// STUB: SADX 0x008c44c0
void dispEffectChaosTracks(struct task *tp)
{
}

// STUB: SADX 0x008c46c0
void setDrop(struct taskwk *twp, int num, float size, float yofs)
{
}

// STUB: SADX 0x008c4ad0
void SetEffectPunchTameParticle(struct NJS_POINT3 *pos, int num)
{
}

// STUB: SADX 0x008c4b40
void dispEffectChaos0LightParticle_tame_init(struct task *tp)
{
}

// STUB: SADX 0x008c4d00
void dispEffectChaos0LightParticle_tame(struct task *tp)
{
}

// FUNCTION: SADX 0x008c4d80
void SetEffectPunchTame(struct NJS_POINT3 *pos)
{
	struct task *local_8g;
	struct taskwk *local_cg;
	local_8g = CreateElementalTask(2, 5, dispEffectChaos0AttackA);
	if (local_8g != NULL)
	{
		local_cg = local_8g->twp;
		local_cg->counter.f = 0.0f;
		local_cg->scl.x = DAT_060df6f8;
		local_cg->timer.ptr = pos;
	}
}

// STUB: SADX 0x008c4dd0
void dispEffectChaos0AttackA(struct task *tp)
{
}

// FUNCTION: SADX 0x008c4fb0
void ChaosUnderLightInit(float radius)
{
	le_CreateLight(2, 4);
	le_SetLightColor(2, 0.0f, 1.0f, 1.0f);
	le_SetLightIntensity(2, 0.5f, 1.0f, 1.0f);
}

// FUNCTION: SADX 0x008c5000
void ChaosUnderLight(struct taskwk *twp)
{
	njUnitLightMatrix((struct NJS_LIGHT *)DAT_060df580);
	njTranslateLightV((struct NJS_LIGHT *)DAT_060df580, &twp->pos);
}

// FUNCTION: SADX 0x008c5030
void ChaosUnderLight2(struct NJS_POINT3 *pos, float yofs)
{
	njUnitLightMatrix((struct NJS_LIGHT *)&DAT_060df580);
	FUN_0067e510((float *)&DAT_060df580, pos->x, pos->y + yofs, pos->z);
}

// FUNCTION: SADX 0x008c5080
void ChaosUnderLightDelete(struct task *tp)
{
	le_DeleteLight(2);
}

// FUNCTION: SADX 0x008c5090
void SetChaosShakeBrain(struct obj *obj, struct task *tp)
{
	struct task *local_8;
	local_8 = CreateElementalTask(2, 2, ChaosShakeBrain);
	if (local_8 != NULL)
	{
		local_8->twp->timer.l = (long)obj;
		obj->evalflags &= 0xfffffffb;
	}
}

// STUB: SADX 0x008c50d0
void ChaosShakeBrain(struct task *tp)
{
}

// FUNCTION: SADX 0x008c5160
void setParticleDispTask(struct taskwk *twp)
{
	if (DAT_060df558 < 0x100)
	{
		if (DAT_060df558 == 0)
		{
			CreateElementalTask(0, 6, drawEffectChaos0LightParticle);
		}
		DAT_060df740[DAT_060df558] = twp;
		DAT_060df558 = DAT_060df558 + 1;
	}
}

// STUB: SADX 0x008c53d0
void SetEffectPunch(struct NJS_POINT3 *pos, struct NJS_POINT3 *pos_old, int num)
{
}

// STUB: SADX 0x008c5520
void dispEffectChaos0LightParticle(struct task *tp)
{
}

// FUNCTION: SADX 0x008c5700
void dispEffectChaos0AttackB_init(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	local_8->counter.f = 0.0f;
	local_8->scl.x = DAT_060df6fc;
	tp->exec = dispEffectChaos0AttackB;
}

// FUNCTION: SADX 0x008c5730
void dispEffectChaos0AttackB(struct task *tp)
{
	struct taskwk *local_8g;
	float local_cg;
	local_8g = tp->twp;
	local_cg = local_8g->counter.f + 1.25f;
	local_8g->counter.f = local_cg;
	if (local_cg >= 10.0f)
	{
		DestroyTask(tp);
	}
	else
	{
		if (DAT_060df530 < 0x80)
		{
			if (DAT_060df530 == 0)
			{
				CreateElementalTask(0, 6, drawEffectChaos0EffectB);
			}
			DAT_060df330[DAT_060df530] = local_8g;
			DAT_060df530 = DAT_060df530 + 1;
		}
	}
}

// STUB: SADX 0x008c57c0
void drawEffectChaos0EffectB(struct task *tp)
{
}

// STUB: SADX 0x008c5960
void SetObjectAlpha(struct obj **list, float a)
{
}

// FUNCTION: SADX 0x008c5a10
struct task *SetChangeAlpha(struct task *tp, struct obj **list, float a0, float a1, int time)
{
	struct task *local_8g;
	struct anywk *local_cg;
	local_8g = CreateChildTask(0, ChangeAlphaTask, tp);
	if (local_8g != NULL)
	{
		local_8g->awp = (struct anywk *)CAlloc(1, 0x14);
		local_cg = local_8g->awp;
		local_cg->work.ptr[0] = list;
		local_cg->work.f[1] = a0;
		local_cg->work.f[2] = a1;
		local_cg->work.f[3] = (a1 - a0) / (float)time;
		local_cg->work.ul[4] = time;
		SetObjectAlpha(list, a0);
	}
	return local_8g;
}

// FUNCTION: SADX 0x008c5aa0
void ChangeAlphaTask(struct task *tp)
{
	struct anywk *local_8;
	local_8 = tp->awp;
	local_8->work.f[1] = local_8->work.f[1] + local_8->work.f[3];
	local_8->work.ul[4] = local_8->work.ul[4] - 1;
	if (local_8->work.ul[4] == 0)
	{
		local_8->work.f[1] = local_8->work.f[2];
		tp->exec = DestroyTask;
	}
	SetObjectAlpha((struct obj **)local_8->work.ptr[0], local_8->work.f[1]);
}

// FUNCTION: SADX 0x008c5b10
void SetChaosEffectParam(float sa, float sb, float sc, float add)
{
	if (sa > 0.0f)
	{
		DAT_060df6f8 = sa;
	}
	if (sb > 0.0f)
	{
		DAT_060df6fc = sb;
	}
	if (sc > 0.0f)
	{
		DAT_060df57c = sc;
	}
	if (add > 0.0f)
	{
		DAT_060df554 = add;
	}
}
