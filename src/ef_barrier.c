#include "decls.h"

// FUNCTION: SADX 0x005b4c50
void EffectThunderBarrier(struct task *tp)
{
	dsPlay_oneshot(6, 0, 0, 0);
	tp->dest = (void (*)(struct task *))FUN_005b5aa0;
	tp->exec = TBarrier;
	TBarrier(tp);
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

// FUNCTION: SADX 0x005b55c0
void EffectMuteki(struct task *tp)
{
	tp->dest = (void (*)(struct task *))FUN_005b5aa0;
	tp->exec = MutekiDisp;
	tp->exec = Muteki;
	Muteki(tp);
}
