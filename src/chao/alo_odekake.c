#include "decls.h"
static struct CCL_INFO colli_info[9];
extern int DAT_060cae28;
extern int DAT_060cae24;

// FUNCTION: SADX 0x007149a0
void ALO_OdekakeMachineDestructor(struct task *tp)
{
	DAT_060cae24 = 0;

	if (tp->awp != 0)
	{
		syFree(tp->awp);
		tp->awp = 0;
	}
}

// FUNCTION: SADX 0x00714b50
void ALO_OdekakeMachine(struct task *tp)
{
	struct anywk *var1;

	CCL_Init(tp, colli_info, 9, 4);
	tp->awp = (struct anywk *)syCalloc(1, 0x30);
	tp->exec = ALO_OdekakeMachineExecutor;
	tp->dest = ALO_OdekakeMachineDestructor;
	tp->disp = ALO_OdekakeMachineDisplayerNeut;
	DAT_060cae24 = (int)tp;
	DAT_060cae28 = 0;
	var1 = tp->awp;
	var1->work.f[3] = -0.49f;
	var1->work.ul[0] = 1;
}

// FUNCTION: SADX 0x00714bb0
void ALO_OdekakeMachineCreate(struct NJS_POINT3 *pPos, long angy)
{
	struct task *var1 = CreateElementalTask(2, 2, ALO_OdekakeMachine);
	struct taskwk *var2 = var1->twp;
	var2->pos = *pPos;
	var2->ang.y = angy;
}
