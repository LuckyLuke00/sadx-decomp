#include "decls.h"
extern struct task *DAT_060ccb94;

// FUNCTION: SADX 0x007dd4c0
void amyeggrob_cons(struct task *tp)
{
	tp->twp->counter.f = 0.0f;
	tp->twp->value.f = 1.0f;
	tp->twp->timer.l = 0;
	SetEventWork(tp->twp);
	tp->exec = amyeggrob_exec;
	tp->disp = amyeggrob_draw;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x007dd510
struct task *set_amy()
{
	struct task *var1;
	var1 = CreateElementalTask(2, 3, amyeggrob_cons);
	if (var1 != 0)
	{
		DAT_060ccb94 = var1;
	}
	return var1;
}
