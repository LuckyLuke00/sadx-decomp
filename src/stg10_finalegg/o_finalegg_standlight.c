#include "decls.h"
void standlight_exec(struct task *task_p);
void standlight_draw(struct task *task_p);

#pragma optimize("", off)
// STUB: SADX 0x00894310
void standlight_draw(struct task *task_p)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008943d0
void standlight_exec(struct task *task_p)
{
	struct taskwk *var1 = task_p->twp;
	if (FUN_004c39c0(task_p) != 0)
	{
		njPrintC(0x110013, "<-MODEL Ang.(DEG)");
		*(int *)((char *)var1 + 0x8) = (int)((*(float *)((char *)var1 + 0x2c) * 65536.0) / 360.0);
	}
	EntryColliList(var1);
	standlight_draw(task_p);
}

// STUB: SADX 0x00894430
void ObjectFinalEggStandlight(struct task *task_p)
{
}
