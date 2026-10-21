#include "decls.h"
extern struct task *DAT_060cbf58;

// FUNCTION: SADX 0x007cd7d0
void FUN_007cd7d0()
{
	if (DAT_060cbf58)
	{
		FreeTask(DAT_060cbf58);
		DAT_060cbf58 = 0;
	}
}
