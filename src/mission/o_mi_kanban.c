#include "decls.h"
static void Exec(struct task *tp);
static void Disp(struct task *tp);

// STUB: SADX 0x0049c290
static void Disp(struct task *tp)
{
}

// STUB: SADX 0x0049c320
static void Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x0049c420
void ObjectMiKanban(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	if (IsMissionAppear(tp))
	{
		var1->ang.x = 0;
		var1->ang.z = 0;
		var1->mode = 0;
		tp->exec = Exec;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		tp->disp = Disp;
	}
}
