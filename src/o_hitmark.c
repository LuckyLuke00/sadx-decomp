#include "decls.h"
static void objDisplay(struct task *tp);
extern long o_hit_spd1;

// FUNCTION: SADX 0x0060ea20
void Object_HitMark(struct task *tp)
{
	tp->exec = objNormal;
	tp->disp = objDisplay;
}

#pragma optimize("", off)
// STUB: SADX 0x0060ea40
static void objDisplay(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0060eca0
void objNormal(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	local_8->counter.l += o_hit_spd1;
	objDisplay(tp);
}
