#include "decls.h"
extern struct task *DAT_060cca74;

// FUNCTION: SADX 0x007da6b0
void FUN_007da6b0()
{
	if (DAT_060cca74)
	{
		FreeTask(DAT_060cca74);
		DAT_060cca74 = 0;
	}
}
