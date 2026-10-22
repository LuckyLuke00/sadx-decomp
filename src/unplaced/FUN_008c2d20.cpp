#include "decls.h"

// FUNCTION: SADX 0x008c3550
int * FUN_008c3550(int param_1, int *param_2, int param_3)
{
	while (param_3 > 0)
	{
		if (*param_2 != 0)
		{
			*param_2 = param_1 + *param_2;
		}
		param_3 -= 2;
		param_2 += 2;
	}
	return param_2;
}

// FUNCTION: SADX 0x008c3770
void FUN_008c3770(int param_1, int *param_2, int *param_3)
{
	int *local_8;
	local_8 = param_2;
	while (local_8 < param_3)
	{
		if (*local_8 != 0)
		{
			*local_8 = param_1 + 8 + *local_8;
		}
		local_8 = local_8 + 3;
	}
}
