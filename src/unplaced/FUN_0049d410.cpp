#include "decls.h"

// FUNCTION: SADX 0x0049d410
int FUN_0049d410(int param_1, int param_2)
{
	int index = param_2 / 8;
	int bit = 1 << (param_2 % 8);

	if (*(char *)(param_1 + index + 0x240) & bit)
	{
		return 1;
	}
	return 0;
}
