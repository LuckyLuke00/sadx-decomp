#include "decls.h"
extern struct task *DAT_060cc57c;

// FUNCTION: SADX 0x007d62e0
void FUN_007d62e0()
{
	if (DAT_060cc57c)
	{
		FreeTask(DAT_060cc57c);
		DAT_060cc57c = 0;
	}
}
