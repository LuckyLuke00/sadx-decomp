#include "decls.h"
void FUN_007d4790(struct task *param_1);

// STUB: SADX 0x007d4720
void EVAlifeMotionCallBack(struct obj *obj)
{
}

// FUNCTION: SADX 0x007d49f0
void EV_Alife_cons(struct task *tp)
{
	tp->twp->counter.l = 2;
	tp->exec = EV_Alife_exec;
	tp->disp = EV_Alife_draw;
	tp->dest = FUN_007d4790;
}

// FUNCTION: SADX 0x007d4a20
struct task *EV_Alife()
{
	struct task *var1;

	var1 = CreateElementalTask(2, 3, EV_Alife_cons);
	if (var1 != NULL)
	{
		SetEventWork(var1->twp);
	}
	return var1;
}
