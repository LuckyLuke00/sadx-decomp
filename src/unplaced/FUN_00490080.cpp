#include "decls.h"

// FUNCTION: SADX 0x00490080
int FUN_00490080(int param_1)
{
	int var1 = 0;
	if (param_1 != 0)
	{
		int param_2 = *(int *)(param_1 + 0x9c);
		if (param_2 != 0)
		{
			if (*(int *)(param_2 + 0x18) == (int)FUN_007d21b0)
			{
				var1 = *(int *)(param_2 + 0x20);
			}
		}
	}
	return var1;
}

// STUB: SADX 0x004900b0
int FUN_004900b0(int param_1)
{
	return (int)0;
}
