#include "decls.h"
extern struct task *DAT_060cbb94;

// FUNCTION: SADX 0x0078db30
void FUN_0078db30()
{
	if (DAT_060cbb94)
	{
		FreeTask(DAT_060cbb94);
		DAT_060cbb94 = 0;
	}
}
