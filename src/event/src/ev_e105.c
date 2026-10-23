#include "decls.h"
static void ev_e105_exec(struct task *tp);

// STUB: SADX 0x007d9b50
static void ev_e105_exec(struct task *tp)
{
}

// FUNCTION: SADX 0x007d9c40
void ev_e105_cons(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.f = 0.0f;
	var1->value.l = 0;
	SetEventWork(var1);
	tp->exec = ev_e105_exec;
	tp->disp = ev_e105_draw;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x007d9c80
struct task *ev_e105()
{
	return CreateElementalTask(2, 3, ev_e105_cons);
}
