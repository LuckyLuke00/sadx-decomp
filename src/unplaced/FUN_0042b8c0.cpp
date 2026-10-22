#include "decls.h"
extern void *DAT_01c6ed3c[16];

// FUNCTION: SADX 0x0042b8c0
void *FUN_0042b8c0(int param_1)
{
	if ((unsigned int)(param_1 - 1) <= 8)
	{
		return DAT_01c6ed3c[param_1 * 2];
	}
	return 0;
}
