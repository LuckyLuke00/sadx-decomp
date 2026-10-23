#include "decls.h"
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

// FUNCTION: SADX 0x00714bb0
void ALO_OdekakeMachineCreate(struct NJS_POINT3 *pPos, long angy)
{
	struct task *var1 = CreateElementalTask(2, 2, ALO_OdekakeMachine);
	struct taskwk *var2 = var1->twp;
	var2->pos = *pPos;
	var2->ang.y = angy;
}
