#include "decls.h"

// FUNCTION: SADX 0x006e6640
void ObjectPatoExit(struct task *tp)
{
	struct colliwk *var1;

	var1 = (struct colliwk *)tp->twp->counter.ptr;
	if (var1)
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1);
		ReleaseMobileLandObject((struct obj *)var1);
	}
}
