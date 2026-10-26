#include "decls.h"

// STUB: SADX 0x006abfb0
void DispAllStones(struct TMyWork *MyWork)
{
}

// STUB: SADX 0x006ac0f0
int CheckOpenState()
{
	return (int)0;
}

// FUNCTION: SADX 0x006ac750
void DesertATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
	ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	Free(var1->value.ptr);
}
