#include "decls.h"

// FUNCTION: SADX 0x0069bdf0
void Term(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	void *var2 = var1->value.ptr;
	Free(var2);
	struct task *var3 = (struct task *)var1->timer.ptr;
	if (var3 != 0)
	{
		FUN_0069bd30((struct task *)var3->awp);
		FUN_0069bd30((struct task *)var3->thp);
		Free(var3);
	}
	FUN_004c39c0(tp);
}

// STUB: SADX 0x0069c370
void CollisionAttackBox(struct task *tp)
{
}
