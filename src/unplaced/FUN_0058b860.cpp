#include "decls.h"

// FUNCTION: SADX 0x0058b860
void FUN_0058b860(int param_1, int param_2)
{
	if (param_2 != 0)
	{
		*(unsigned char *)(param_1 + 0x5cd290c) |= 1;
	}
	else
	{
		*(unsigned char *)(param_1 + 0x5cd290c) &= 0xfffffffe;
	}
	*(unsigned char *)(param_1 + 0x5cd290c) |= 2;
}
