#include "decls.h"
extern struct task *DAT_060cc134;

// FUNCTION: SADX 0x007d2c50
void FUN_007d2c50()
{
	if (DAT_060cc134)
	{
		FreeTask(DAT_060cc134);
		DAT_060cc134 = 0;
	}
}
