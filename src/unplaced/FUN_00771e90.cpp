#include "decls.h"
extern struct task *DAT_060cba14;

// FUNCTION: SADX 0x00771f30
void FUN_00771f30()
{
	if (DAT_060cba14)
	{
		FreeTask(DAT_060cba14);
		DAT_060cba14 = 0;
	}
}
