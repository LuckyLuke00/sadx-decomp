#include "decls.h"

// STUB: SADX 0x006e6570
void ObjectPatoRegular(struct task *tp)
{
}

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

// STUB: SADX 0x006e6670
void ObjectChaos0Pato(struct task *tp)
{
}
