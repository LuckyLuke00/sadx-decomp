#include "decls.h"

// FUNCTION: SADX 0x0044a350
long ALBHV_OsanpoThrown(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (*(short *)((char *)var1 + 0x1c6) == 0)
	{
		AL_SetMotionLink(tp, 0);
		*(short *)((char *)var1 + 0x1c6) += 1;
		var1 = tp->twp;
		*(int *)((char *)var1 + 0xb0) &= 0xfffffff7;
	}
	return 0;
}

// FUNCTION: SADX 0x0044a430
long AL_GetBehavior(struct task *param_1)
{
	return *(long *)((char *)param_1->twp + 0x450 + *(long *)((char *)param_1->twp + 0x44c) * 4);
}

// FUNCTION: SADX 0x0044a450
void FUN_0044a450(int param_1)
{
	*(int *)(param_1 + 2) = 0;
	*(int *)(param_1 + 0xc) = 0;
	*(int *)(param_1 + 0x10) = 0;
	*(int *)(param_1 + 0x14) = 0xe10;
	*(int *)(param_1 + 0x18) = 0;
}

// STUB: SADX 0x0044a530
void FUN_0044a530(int param_1, int param_2, int param_3)
{
}

// STUB: SADX 0x0044a570
int FUN_0044a570(int param_1)
{
	return (int)0;
}

// STUB: SADX 0x0044a5c0
void AL_ReturnBehavior(struct task *tp)
{
}

// FUNCTION: SADX 0x0044a620
void AL_BehaviorSetFreeWork(struct task *tp, long info)
{
	*(long *)((char *)tp->twp + 0x430) = info;
}

// FUNCTION: SADX 0x0044a640
long AL_BehaviorGetFreeWork(struct task *tp)
{
	return *(long *)((char *)tp->twp + 0x430);
}

// FUNCTION: SADX 0x0044a740
void AL_SetBehavior(struct task *tp, long (*Func)(struct task *))
{
	AL_SetBehaviorWithTimer(tp, Func, -1);
}

// STUB: SADX 0x0044a760
void AL_SetNextBehavior(struct task *tp, long (*Func)(struct task *))
{
}

// STUB: SADX 0x0044a960
long ALBHV_OdekakeEject(struct task *tp)
{
	return (long)0;
}
