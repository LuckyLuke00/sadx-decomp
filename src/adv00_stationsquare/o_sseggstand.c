#include "decls.h"

// FUNCTION: SADX 0x0068e1b0
void ObjectMainOn(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (FUN_004c39c0(tp) == 0)
	{
		EntryColliList(var1);
	}
	ObjectDisplayOn(tp);
}
