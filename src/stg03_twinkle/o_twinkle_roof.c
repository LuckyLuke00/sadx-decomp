#include "decls.h"

// FUNCTION: SADX 0x00815380
void destTPRoof(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	int var2;

	var2 = FUN_004c39c0(tp);
	if ((var2 == 0) && (var1->counter.ptr != 0))
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	}
	FreeTask(tp);
}
