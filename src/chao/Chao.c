#include "decls.h"

// FUNCTION: SADX 0x0044bd10
void ChaoDestructor(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	late_exec();
	AL_ShapeExit(tp);
	FUN_007d21b0(tp);
	ALW_CancelEntry(tp);
	FreeTaskC(tp);
	if (*(int *)((char *)var1 + 0x68) != 0)
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
	if (tp->mwp != 0)
	{
		syFree(tp->mwp);
		tp->mwp = 0;
	}
}

// FUNCTION: SADX 0x0044bdb0
void KillChao(struct task *tp)
{
	AL_ClearChaoParam((struct CHAO_PARAM_GC *)(*(int **)((char *)tp->twp + 0x6c)));
	FreeTask(tp);
}
