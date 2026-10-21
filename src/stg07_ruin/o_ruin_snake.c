#include "decls.h"

// STUB: SADX 0x00858f50
void End(struct task *tp)
{
}

// FUNCTION: SADX 0x008590d0
void EndC(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (var1->btimer == 0)
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->value.ptr);
		ReleaseMobileLandObject((struct obj *)var1->value.ptr);
		NpcMilesSetStandByFlag(0);
	}
}
