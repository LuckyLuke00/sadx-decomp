#include "decls.h"
void FUN_004da910(int param_1);

// FUNCTION: SADX 0x0046ccf0
void AL_MinimalDestructor(struct task *tp)
{
	tp->awp = 0;
	ALW_CancelEntry(tp);
	if (tp->twp != 0)
	{
		if (tp->twp->cwp != 0)
		{
			FUN_004da910((int)tp->twp);
		}
		syFree(tp->twp);
		tp->twp = 0;
	}
	if (tp->mwp != 0)
	{
		syFree(tp->mwp);
		tp->mwp = 0;
	}
}

// STUB: SADX 0x0046cdf0
void FUN_0046cdf0(struct MOTION_TABLE *tp, int var1)
{
}

// FUNCTION: SADX 0x0046d1c0
void AL_CreateMinimalCreateManager()
{
	struct task *var1 = CreateElementalTask(2, 2, AL_MinimalCreateManagerExecutor);
	if (var1 != 0)
	{
		var1->twp->ang.x = 0;
	}
}

// STUB: SADX 0x0046d1e0
void AL_MinimalInit()
{
}

// STUB: SADX 0x0046d210
void AL_MinimalExit()
{
}
