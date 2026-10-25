#include "decls.h"
extern struct CCL_INFO c_info01[2];

// FUNCTION: SADX 0x00850df0
void ColliOnly(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	switch (var1->mode)
	{
	case 0:
		var1->mode = 1;
		CCL_Init(tp, &c_info01[1], 1, 4);
		break;
	case 1:
		EntryColliList(var1);
		break;
	}
}

// STUB: SADX 0x008511d0
void ObjectRuinBrokenObj(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	EnemyInitialize(tp, var1);
	var1->counter.f = 0.0f;
	var1->mode = 1;
	var1->wtimer = 0;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, c_info01, 1, 2);
	}
	CreateChildTask(2, ColliOnly, tp);
	tp->exec = (void (*)(struct task *))0x851090;
	tp->disp = (void (*)(struct task *))0x850c00;
	tp->dest = (void (*)(struct task *))0x850d10;
}
