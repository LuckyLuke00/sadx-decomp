#include "decls.h"
void FUN_005fcd60(float);
extern struct task *DAT_05edd990;

// FUNCTION: SADX 0x005fcd40
void FUN_005fcd40(struct task *param_1)
{
	FUN_005fcd60(*(float *)((char *)param_1 + 0x10));
}

// FUNCTION: SADX 0x005fd0e0
void FUN_005fd0e0(void)
{
	if (DAT_05edd990)
	{
		DestroyTask(DAT_05edd990);
	}
}

// FUNCTION: SADX 0x005fd100
void FUN_005fd100(void)
{
	*(int *)((char *)DAT_05edd990->awp + 4) = 5;
}
