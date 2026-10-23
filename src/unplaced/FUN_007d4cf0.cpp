#include "decls.h"

// FUNCTION: SADX 0x007d4cf0
void FUN_007d4cf0(int param_1, float param_2, float param_3, float param_4)
{
	int local_0;
	local_0 = *(int *)(param_1 + 0x20);
	*(float *)(local_0 + 0x20) = param_2;
	*(float *)(local_0 + 0x24) = param_3;
	*(float *)(local_0 + 0x28) = param_4;
}

// FUNCTION: SADX 0x007d4d10
void FUN_007d4d10(struct task *param_1, float param_2)
{
	*(float *)((char *)param_1->twp + 0x34) = param_2;
}
