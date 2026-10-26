#include "decls.h"
static void ev_e101_cons(struct task *tp);

// STUB: SADX 0x007da990
void ev_e101_exec(struct task *tp)
{
}

// FUNCTION: SADX 0x007daa90
static void ev_e101_cons(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.f = 0.0f;
	var1->value.l = 0;
	tp->exec = ev_e101_exec;
	tp->disp = ev_e101_draw;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x007daac0
struct task *ev_e101()
{
	struct task *var1;

	var1 = CreateElementalTask(2, 3, ev_e101_cons);
	if (var1 != NULL)
	{
		SetEventWork(var1->twp);
	}
	return var1;
}
