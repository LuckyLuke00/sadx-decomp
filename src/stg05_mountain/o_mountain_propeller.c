#include "decls.h"

// FUNCTION: SADX 0x008319e0
void ObjectMountainPropellerExit(struct task *tp)
{
	if (FUN_004c39c0(tp) == 0)
	{
		WithdrawCollisionEntry(tp, (struct obj *)tp->twp->counter.ptr);
		ReleaseMobileLandObject((struct obj *)tp->twp->counter.ptr);
	}
}
