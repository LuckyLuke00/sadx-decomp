#include "decls.h"
extern struct task *DAT_060cbb9c;

// STUB: SADX 0x007911a0
void FUN_007911a0(struct task *param_1)
{
}

// STUB: SADX 0x00791210
void FUN_00791210()
{
}

// FUNCTION: SADX 0x00791270
void FUN_00791270()
{
	if (DAT_060cbb9c)
	{
		FreeTask(DAT_060cbb9c);
		DAT_060cbb9c = 0;
	}
}
