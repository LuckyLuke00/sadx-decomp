#include "decls.h"
extern int DAT_060d1344;

// FUNCTION: SADX 0x00857320
void End(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
	ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	FreeTaskC(tp);
	DAT_060d1344 = 0;
}
