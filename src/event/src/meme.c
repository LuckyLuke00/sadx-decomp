#include "decls.h"
extern struct task *DAT_060ccb08;

// FUNCTION: SADX 0x007db720
void MemeDelete()
{
	if (DAT_060ccb08)
	{
		FreeTask(DAT_060ccb08);
		DAT_060ccb08 = 0;
	}
}
