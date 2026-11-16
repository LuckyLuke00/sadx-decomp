#include "decls.h"

// FUNCTION: SADX 0x0081f2b0
void Exit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct obj *var2 = (struct obj *)var1->counter.ptr;

	ReleaseMobileLandObject(var2);
	WithdrawCollisionEntry(tp, var2);
}
