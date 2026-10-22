#include "decls.h"

// FUNCTION: SADX 0x006d5950
void UkisimaExit(struct task *tp)
{
	struct anywk *var1 = tp->awp;

	if (var1->work.ptr[1] != 0)
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->work.ptr[1]);
		ReleaseMobileLandObject((struct obj *)var1->work.ptr[1]);
		var1->work.ptr[1] = 0;
	}
}

// STUB: SADX 0x006d5c40
void UkisimaBreak(float x, float z)
{
}
