#include "decls.h"

// STUB: SADX 0x007e6040
void ObjectCartDial(struct task *task_p)
{
}

// STUB: SADX 0x007e6060
void initObject(struct task *task_p, const struct ActionParam *param_p)
{
}

// STUB: SADX 0x007e6080
void FUN_007e6080(char param_1)
{
}

// FUNCTION: SADX 0x007e6240
void execObject(struct task *task_p)
{
	struct motionwk *var1;

	if (CheckRangeOut(task_p) == 0)
	{
		var1 = task_p->mwp;
		var1->work.b[0] = CartRaceGetDialState();
		dispObject(task_p);
	}
}
