#include "decls.h"
extern struct task *DAT_060cceb0;

// STUB: SADX 0x007e0400
void ptrmiles_exec(struct task *tp)
{
}

// FUNCTION: SADX 0x007e0470
void ptrmiles_cons(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->counter.f = 0.5f;
	var1->timer.f = 0.0f;
	var1->value.l = 0;
	var1->scl.x = 0.0f;
	var1->scl.y = 0.0f;
	var1->scl.z = 0.0f;
	EV_SetMode(tp, 0);
	tp->exec = ptrmiles_exec;
	tp->disp = ptrmiles_draw;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// STUB: SADX 0x007e04c0
struct task *miles_with_ptr()
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x007e04f0
void miles_motchg(long num, float spd)
{
	struct task *var1;

	var1 = DAT_060cceb0;
	if (var1 != 0)
	{
		var1->twp->value.l = num;
		var1->twp->timer.f = 0.0f;
		var1->twp->counter.f = spd;
	}
}
