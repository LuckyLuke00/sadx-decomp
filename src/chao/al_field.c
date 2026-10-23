#include "decls.h"

// STUB: SADX 0x004516c0
void AL_FieldExecutor(struct task *tp)
{
}

// STUB: SADX 0x004516f0
void AL_FieldDisplayer(struct task *tp)
{
}

// FUNCTION: SADX 0x00451790
void AL_ChildFieldDestructor(struct task *tp)
{
	if (tp->ptp != NULL)
	{
		*(int *)((char *)tp->ptp->twp + 0x50) = 0;
	}
}

// FUNCTION: SADX 0x004517b0
void FUN_004517b0(struct task *param_1, int param_2)
{
	int *var1 = (int *)(*(int **)((char *)param_1 + 0x20));
	if (param_2 > 0)
	{
		*(char *)((char *)var1 + 1) = 1;
		*(short *)((char *)var1 + 6) = (short)param_2;
	}
	else
	{
		*(char *)((char *)var1 + 1) = 0;
	}
}

// STUB: SADX 0x004517d0
struct task *AL_AllFieldCreateTT(unsigned long kind, struct NJS_POINT3 *pPos, float radius, long WaitTime, long ActiveTime)
{
	return (struct task *)0;
}

// STUB: SADX 0x00451850
struct task *AL_ChildFieldCreateT(struct task *pParentTask, unsigned long kind, struct NJS_POINT3 *pPos, float radius, long time)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x004518d0
struct task *AL_AllFieldCreateT(unsigned long kind, struct NJS_POINT3 *pPos, float radius, long time)
{
	return AL_AllFieldCreateTT(kind, pPos, radius, 0, time);
}
