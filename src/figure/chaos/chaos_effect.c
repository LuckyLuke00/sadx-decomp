#include "decls.h"
extern float DAT_060df57c;
extern float DAT_060df554;
extern float DAT_060df6fc;
extern int DAT_060df558;
extern struct taskwk *DAT_060df740[256];
extern char DAT_060df580[1];
extern float DAT_060df6f8;

// STUB: SADX 0x008c46c0
void setDrop(struct taskwk *twp, int num, float size, float yofs)
{
}

// STUB: SADX 0x008c4ad0
void SetEffectPunchTameParticle(struct NJS_POINT3 *pos, int num)
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
		*(float *)&local_cg->counter = 0.0f;
		*(float *)&local_cg->scl.x = DAT_060df6f8;
		local_cg->timer.ptr = pos;
	}
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

// STUB: SADX 0x008c5030
void ChaosUnderLight2(struct NJS_POINT3 *pos, float yofs)
{
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

// FUNCTION: SADX 0x008c5700
void dispEffectChaos0AttackB_init(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	local_8->counter.f = 0.0f;
	local_8->scl.x = DAT_060df6fc;
	tp->exec = dispEffectChaos0AttackB;
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
