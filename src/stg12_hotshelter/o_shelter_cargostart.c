#include "decls.h"

// FUNCTION: SADX 0x008add30
void Destructor(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckPadReadMode() == 0)
	{
		PadReadOn();
	}
	struct obj *var2 = (struct obj *)var1->counter.ptr;
	if (var2 != 0)
	{
		WithdrawCollisionEntry(tp, var2);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	}
}

// STUB: SADX 0x008ae000
void ObjShelterCargostart(struct task *tp)
{
}
