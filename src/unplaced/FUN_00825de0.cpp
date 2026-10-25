#include "decls.h"

// FUNCTION: SADX 0x00825de0
void FUN_00825de0(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;
	struct obj *var2 = (struct obj *)var1->counter.ptr;
	if (var2 != 0)
	{
		WithdrawCollisionEntry(param_1, var2);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	}
}
