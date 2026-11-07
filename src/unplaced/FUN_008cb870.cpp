#include "decls.h"
extern struct task *DAT_060dfeb0;

// STUB: SADX 0x008cb870
void FUN_008cb870(int param_1, int *param_2, int *param_3)
{
}

// FUNCTION: SADX 0x008cb8d0
int FUN_008cb8d0(void)
{
	struct task *local_8;
	local_8 = DAT_060dfeb0;
	if (local_8 != NULL)
	{
		*(char *)((int *)local_8->twp) = 8;
	}
	return (int)local_8;
}
