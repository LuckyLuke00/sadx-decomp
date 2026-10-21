#include "decls.h"
extern struct task *DAT_060cbf64;

// FUNCTION: SADX 0x007ce580
void FUN_007ce580()
{
	if (DAT_060cbf64)
	{
		FreeTask(DAT_060cbf64);
		DAT_060cbf64 = 0;
	}
}
