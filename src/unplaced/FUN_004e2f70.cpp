#include "decls.h"

// FUNCTION: SADX 0x004e2f70
void FUN_004e2f70(int param_1, int param_2)
{
	if (param_2 != 0)
	{
		*(float *)(param_2 + 0x40) = 0.0f;
		*(float *)(param_2 + 0x3c) = 0.0f;
		*(float *)(param_2 + 0x38) = 0.0f;
	}
	if (param_1 != 0)
	{
		*(float *)(param_1 + 0xc) = 0.0f;
		*(float *)(param_1 + 8) = 0.0f;
		*(float *)(param_1 + 4) = 0.0f;
	}
}
