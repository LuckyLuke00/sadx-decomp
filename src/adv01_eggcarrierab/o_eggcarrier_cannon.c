#include "decls.h"

// STUB: SADX 0x0069bdf0
void Term(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;
	Free(local_8->value.ptr);
	struct taskwk *local_4 = (struct taskwk *)local_8->timer.ptr;
	if (local_4 != NULL)
	{
		FUN_0069bd30((struct task *)(*(int *)&local_4->scl.x));
		FUN_0069bd30((struct task *)(*(int *)&local_4->scl.y));
		Free(local_4);
	}
	FUN_004c39c0(tp);
}
