#include "decls.h"

// FUNCTION: SADX 0x004ccc20
void FUN_004ccc20(int param_1, int param_2)
{
	int local_8;
	local_8 = 0;
	if (param_2 != 0)
	{
		*(int *)((char *)param_2 + local_8 * 4) = param_1;
	}
	FUN_004ccc60(param_2, &local_8);
}
