#include "decls.h"

// FUNCTION: SADX 0x0045bb30
void AL_EggDestructor(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	ALW_CancelEntry(tp);
	if (*(int *)((char *)var1 + 0x68) != 0 && *(int *)((char *)var1 + 0x6c) != 0)
	{
		syFree(*(void **)((char *)var1 + 0x6c));
		*(int *)((char *)var1 + 0x6c) = 0;
	}
	if (tp->twp != 0)
	{
		if (tp->twp->cwp != 0)
		{
			FUN_004da910((int)tp->twp);
		}
		syFree(tp->twp);
		tp->twp = 0;
	}
	if (tp->awp != 0)
	{
		syFree(tp->awp);
		tp->awp = 0;
	}
	if (tp->mwp != 0)
	{
		syFree(tp->mwp);
		tp->mwp = 0;
	}
}
