#include "decls.h"
extern struct task *DAT_060cba34;

// STUB: SADX 0x007738f0
void FUN_007738f0(struct task *param_1)
{
}

// FUNCTION: SADX 0x007739c0
void FUN_007739c0()
{
	if (DAT_060cba34)
	{
		FreeTask(DAT_060cba34);
		DAT_060cba34 = 0;
	}
}
