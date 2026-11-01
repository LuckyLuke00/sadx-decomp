#include "decls.h"

// FUNCTION: SADX 0x004502f0
void FUN_004502f0(int *param_1, int param_2)
{
	if (param_1 != 0)
	{
		int *var1 = (int *)*(int *)((char *)param_1 + 4);
		if (var1 != 0)
		{
			int *var2 = (int *)*(int *)((char *)var1 + 4);
			if (var2 != 0)
			{
				*(int *)((char *)var2 + 4) = param_2;
			}
		}
	}
}
