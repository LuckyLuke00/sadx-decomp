#include "decls.h"
static void Disp(struct task *tp);
static void Normal(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x008822e0
static void Disp(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008823d0
static void Normal(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.f = var1->counter.f + 0.10000000149011612;
	if (var1->counter.f >= 15.0)
	{
		var1->counter.f = 0.0;
	}
	Disp(tp);
}

// FUNCTION: SADX 0x00882410
void ObjectIdea(struct task *tp)
{
	tp->twp->counter.f = 0.0f;
	DAT_060dbcb0 &= 0xffffdfff;
	DAT_048093da = 1;
	tp->exec = Normal;
	tp->disp = Disp;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
}
