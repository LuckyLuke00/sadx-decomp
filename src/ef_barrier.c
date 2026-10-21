#include "decls.h"
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

// STUB: SADX 0x005b5430
void NormalB(struct task *tp)
{
}

// STUB: SADX 0x005b54c0
void NBarrierDisp(struct task *tp)
{
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

// STUB: SADX 0x005b5830
void CMuteki(struct task *tp)
{
}

// STUB: SADX 0x005b58c0
void CMutekiDisp(struct task *tp)
{
}
