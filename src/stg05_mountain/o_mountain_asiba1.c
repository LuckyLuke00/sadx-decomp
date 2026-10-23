#include "decls.h"

// FUNCTION: SADX 0x008629d0
void Die(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (var1->counter.ptr != 0)
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	}

	Free(var1->value.ptr);
}
