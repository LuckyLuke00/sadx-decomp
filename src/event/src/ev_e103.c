#include "decls.h"

// FUNCTION: SADX 0x007da140
void ev_e103_cons(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.f = 0.0f;
	var1->value.l = 0;
	tp->exec = ev_e103_exec;
	tp->disp = ev_e103_draw;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x007da170
struct task *ev_e103()
{
	struct task *var1;

	var1 = CreateElementalTask(2, 3, ev_e103_cons);
	if (var1 != NULL)
	{
		SetEventWork(var1->twp);
	}
	return var1;
}
