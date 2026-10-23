#include "decls.h"

// FUNCTION: SADX 0x00815f00
void destTPGoRoundManager(struct task *tp)
{
	struct taskwk *var1;
	int var2;

	FreeTaskC(tp);
	dsStop_num(0x43);
	var1 = tp->twp;
	var2 = FUN_004c39c0(tp);
	if ((var2 == 0) && (var1->counter.ptr != 0))
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	}
	FreeTask(tp);
}
