#include "decls.h"
void FUN_00617200(int param_1);

// FUNCTION: SADX 0x006171b0
void FUN_006171b0(int param_1)
{
	float local_8;
	local_8 = *(float *)(*(int *)(param_1 + 0x20) + 0x30) + -0.10000000149011612;
	*(float *)(*(int *)(param_1 + 0x20) + 0x30) = local_8;
	if (local_8 < -3.0)
	{
		*(float *)(*(int *)(param_1 + 0x20) + 0x30) = -3.0;
	}
}

// STUB: SADX 0x00617200
void FUN_00617200(int param_1)
{
}
