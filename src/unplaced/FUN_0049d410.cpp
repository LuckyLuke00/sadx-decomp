#include "decls.h"

// FUNCTION: SADX 0x0049d410
int FUN_0049d410(int param_1, int param_2)
{
	int local_8g = param_2 / 8;
	int local_cg = 1 << (param_2 % 8);

	if (*(char *)(param_1 + local_8g + 0x240) & local_cg)
	{
		return 1;
	}
	return 0;
}
