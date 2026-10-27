#include "decls.h"
extern int DAT_05cd2968;

// STUB: SADX 0x0049b3e0
void FUN_0049b3e0(struct NJS_MODEL *model)
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

// STUB: SADX 0x0049b9f0
void sakana_disp(struct task *tp)
{
}

// FUNCTION: SADX 0x0049baf0
void sakana_exit(struct task *tp)
{
	if (tp->awp)
	{
		struct task *var1 = *(struct task **)((char *)tp->awp + 8);
		if (var1 && var1->twp)
		{
			*(int *)((char *)var1->twp + 0x10) = 0;
		}
		DAT_05cd2968--;
	}
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

// FUNCTION: SADX 0x0049c270
void ObjectMiSakana(struct task *tp)
{
	if (IsMissionAppear(tp))
	{
		MiSakanaGenerater(tp);
	}
}
