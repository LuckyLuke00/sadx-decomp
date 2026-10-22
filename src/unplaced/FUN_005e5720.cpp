#include "decls.h"

// FUNCTION: SADX 0x005e5720
int FUN_005e5720(int param_1)
{
	if (param_1 == 0)
	{
		return 0;
	}
	int local_8;
	local_8 = *(int *)(param_1 + 0x2c);
	return *(int *)(local_8 + 0x14);
}
