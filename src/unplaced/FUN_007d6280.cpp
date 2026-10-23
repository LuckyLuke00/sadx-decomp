#include "decls.h"
extern struct task *DAT_060cc57c;

// STUB: SADX 0x007d6280
void FUN_007d6280(float param_1, float param_2, float param_3, long param_4, long param_5, long param_6)
{
}

// FUNCTION: SADX 0x007d62e0
void FUN_007d62e0()
{
	if (DAT_060cc57c)
	{
		FreeTask(DAT_060cc57c);
		DAT_060cc57c = 0;
	}
}
