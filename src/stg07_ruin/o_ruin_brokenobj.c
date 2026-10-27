#include "decls.h"
static void ColliOnly(struct task *tp);
static void Exec(struct task *tp);
static void Disp(struct task *tp);
void FUN_00850d10(struct task *param_1);
extern struct CCL_INFO c_info01[2];

#pragma optimize("", off)
// STUB: SADX 0x00850c00
static void Disp(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00850df0
static void ColliOnly(struct task *tp)
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

#pragma optimize("", off)
// STUB: SADX 0x00851090
static void Exec(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008511d0
void ObjectRuinBrokenObj(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	EnemyInitialize(tp, var1);
	var1->counter.f = 0.0f;
	var1->mode = 1;
	var1->wtimer = 0;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, (struct CCL_INFO *)&c_info01, 1, 2);
	}
	CreateChildTask(2, ColliOnly, tp);
	tp->exec = Exec;
	tp->disp = Disp;
	tp->dest = FUN_00850d10;
}
