#include "decls.h"
extern struct NJS_TEXLIST texlist_muteki[8];
extern struct NJS_MODEL DAT_05a7989c;
extern struct NJS_TEXLIST texlist_barrier_cup[2];
extern struct NJS_MODEL DAT_05a6401c;
extern struct NJS_TEXLIST texlist_muteki_sphere[1];
extern struct NJS_MODEL DAT_05a79e44;
extern int DAT_05b9d838;

// FUNCTION: SADX 0x005b4c50
void EffectThunderBarrier(struct task *tp)
{
	dsPlay_oneshot(6, 0, 0, 0);
	tp->dest = (void (*)(struct task *))FUN_005b5aa0;
	tp->exec = TBarrier;
	TBarrier(tp);
}

// STUB: SADX 0x005b4db0
void FUN_005b4db0(struct obj *obj, struct csts *cstsp)
{
}

// STUB: SADX 0x005b4eb0
void ThunderB(struct task *tp)
{
}

// STUB: SADX 0x005b5280
void ef_barrier_DrawModel(struct NJS_MODEL *mdl)
{
}

// FUNCTION: SADX 0x005b5300
void EffectBarrier(struct task *tp)
{
	dsPlay_oneshot(6, 0, 0, 0);
	tp->dest = (void (*)(struct task *))FUN_005b5aa0;
	tp->exec = NBarrier;
	NBarrier(tp);
}

// STUB: SADX 0x005b5340
void NBarrier(struct task *tp)
{
}

// FUNCTION: SADX 0x005b5430
void NormalB(struct task *tp)
{
	struct taskwk *local_cg;
	struct taskwk *local_8g;

	local_cg = tp->twp;
	local_8g = tp->ptp->twp;
	if (local_cg->btimer >= 0x1e)
	{
		FreeTask(tp);
	}
	else
	{
		local_cg->pos = local_8g->pos;
		local_cg->scl.x = *(float *)((char *)local_8g + 0x30) * 0.2f;
		NBarrierDisp(tp);
		local_cg->btimer++;
	}
}

// FUNCTION: SADX 0x005b54c0
void NBarrierDisp(struct task *tp)
{
	int local_cg;
	struct taskwk *local_8g;

	local_8g = tp->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	njPushMatrix(0);
	local_cg = local_8g->btimer >> 1;
	___njSetTexture(&texlist_barrier_cup[local_cg]);
	njTranslateV(0, &local_8g->pos);
	if (local_8g->ang.y != 0)
	{
		njRotateY(0, (unsigned short)local_8g->ang.y);
	}
	if (local_8g->ang.x != 0)
	{
		njRotateX(0, (unsigned short)local_8g->ang.x);
	}
	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	FUN_0067d2d0(0, local_8g->scl.x, local_8g->scl.x, local_8g->scl.x);
	ef_barrier_DrawModel(&DAT_05a6401c);
	njPopMatrix(1);
	ResetMaterial();
}

// FUNCTION: SADX 0x005b55c0
void EffectMuteki(struct task *tp)
{
	tp->dest = (void (*)(struct task *))FUN_005b5aa0;
	tp->exec = MutekiDisp;
	tp->exec = Muteki;
	Muteki(tp);
}

// FUNCTION: SADX 0x005b55f0
void MutekiDisp(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	njPushMatrix(0);
	___njSetTexture(&texlist_muteki_sphere[0]);
	njTranslateV(0, &local_8->pos);
	if (local_8->ang.y != 0)
	{
		njRotateY(0, (unsigned short)local_8->ang.y);
	}
	if (local_8->ang.x != 0)
	{
		njRotateX(0, (unsigned short)local_8->ang.x);
	}
	FUN_0067d2d0(0, local_8->scl.x, local_8->scl.x, local_8->scl.x);
	ef_barrier_DrawModel(&DAT_05a79e44);
	njPopMatrix(1);
}

// STUB: SADX 0x005b56b0
void Muteki(struct task *tp)
{
}

// FUNCTION: SADX 0x005b5830
void CMuteki(struct task *tp)
{
	struct taskwk *local_cg;
	struct taskwk *local_8g;
	local_cg = tp->twp;
	local_8g = tp->ptp->twp;
	if (local_cg->btimer >= 0x20)
	{
		FreeTask(tp);
		return;
	}
	local_cg->pos = local_8g->pos;
	local_cg->scl.x = *(float *)((char *)local_8g + 0x30) * 0.20000000298023224f;
	CMutekiDisp(tp);
	local_cg->btimer++;
}

// FUNCTION: SADX 0x005b58c0
void CMutekiDisp(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	{
		int local_c;

		njPushMatrix(0);
		local_c = (local_8->btimer >> 1) & 7;
		___njSetTexture(&texlist_muteki[local_c]);
		njTranslateV(0, &local_8->pos);
		if (local_8->ang.y != 0)
		{
			njRotateY(0, local_8->ang.y);
		}
		if (local_8->ang.x != 0)
		{
			njRotateX(0, local_8->ang.x);
		}
		FUN_0067d2d0(0, local_8->scl.x, local_8->scl.x, local_8->scl.x);
		ef_barrier_DrawModel(&DAT_05a7989c);
		njPopMatrix(1);
	}
}
