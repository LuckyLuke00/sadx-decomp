#include "decls.h"

// FUNCTION: SADX 0x008895d0
void FUN_008895d0(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	if (var1->counter.ptr != 0)
	{
		WithdrawCollisionEntry(param_1, (struct obj *)var1->counter.ptr);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
		var1->counter.ptr = 0;
	}
}
