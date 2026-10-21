#include "decls.h"
extern struct task *DAT_060cb770;

// FUNCTION: SADX 0x00743180
void FUN_00743180()
{
	if (DAT_060cb770)
	{
		FreeTask(DAT_060cb770);
		DAT_060cb770 = 0;
	}
}
