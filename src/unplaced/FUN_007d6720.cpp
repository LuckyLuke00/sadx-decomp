#include "decls.h"

// FUNCTION: SADX 0x007d6720
void FUN_007d6720(int param_1, float param_2, float param_3, float param_4)
{
	if (param_1 != 0)
	{
		if (*(char *)*(int *)(param_1 + 0x20) == 0)
		{
			*(float *)(*(int *)(param_1 + 0x24) + 4) = param_2;
			*(int *)(*(int *)(param_1 + 0x24)) = (int)param_3;
			*(float *)(*(int *)(param_1 + 0x24) + 0xc) = param_4;
		}
	}
}
