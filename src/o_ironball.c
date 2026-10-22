#include "decls.h"

// FUNCTION: SADX 0x008bd160
void FUN_008bd160(struct task *param_1)
{
	struct taskwk *local_8;

	local_8 = param_1->twp;
	if (local_8->counter.ptr != 0)
	{
		WithdrawCollisionEntry(param_1, (struct obj *)local_8->counter.ptr);
		ReleaseMobileLandObject((struct obj *)local_8->counter.ptr);
	}
	FreeTaskC(param_1);
}

// STUB: SADX 0x008be060
int FUN_008be060(struct task *param_1)
{
	return (int)0;
}
