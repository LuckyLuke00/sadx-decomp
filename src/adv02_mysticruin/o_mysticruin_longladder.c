#include "decls.h"

// FUNCTION: SADX 0x006b0ac0
void LadderDestructor(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	Free(var1->value.ptr);
	Free(var1->timer.ptr);
	FreeTaskC(tp);
}
