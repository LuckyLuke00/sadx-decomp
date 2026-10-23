#include "decls.h"
static void ev_e104_exec(struct task *tp);

// STUB: SADX 0x007d9dd0
static void ev_e104_exec(struct task *tp)
{
}

// FUNCTION: SADX 0x007d9ec0
void ev_e104_cons(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.f = 0.0f;
	var1->value.l = 0;
	tp->exec = ev_e104_exec;
	tp->disp = ev_e104_draw;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x007d9ef0
struct task *ev_e104()
{
	struct task *var1;

	var1 = CreateElementalTask(2, 3, ev_e104_cons);
	if (var1 != NULL)
	{
		SetEventWork(var1->twp);
	}
	return var1;
}
