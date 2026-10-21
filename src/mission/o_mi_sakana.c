#include "decls.h"

// STUB: SADX 0x0049b8b0
void motionSakana(struct task *tp)
{
}

// STUB: SADX 0x0049b910
void FUN_0049b910(struct task *tp)
{
}

// STUB: SADX 0x0049b990
void FUN_0049b990(struct obj *objp)
{
}

// STUB: SADX 0x0049baf0
void sakana_exit(struct task *tp)
{
}

// FUNCTION: SADX 0x0049bb20
void sakanaGeneraterExit(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (var1->value.ptr != 0)
	{
		DestroyTask((struct task *)var1->value.ptr);
		return;
	}
}

// STUB: SADX 0x0049c020
void sakanaInitialize(struct task *tp)
{
}

// STUB: SADX 0x0049c0a0
struct task *setSakana(struct task *tp)
{
	return (struct task *)0;
}
