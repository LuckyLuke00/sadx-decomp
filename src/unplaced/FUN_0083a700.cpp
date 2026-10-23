#include "decls.h"

// STUB: SADX 0x0083a700
void FUN_0083a700(struct task *param_1)
{
}

// FUNCTION: SADX 0x0083a790
void FUN_0083a790(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;
	if (var1->counter.ptr != 0)
	{
		WithdrawCollisionEntry(param_1, (struct obj *)var1->counter.ptr);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
		var1->counter.ptr = 0;
	}
	var1 = param_1->twp;
	Free(var1->value.ptr);
	var1->value.ptr = 0;
	Free(var1->timer.ptr);
	var1->timer.ptr = 0;
	FreeTaskC(param_1);
}
