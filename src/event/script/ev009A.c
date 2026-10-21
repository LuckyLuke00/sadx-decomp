#include "decls.h"
extern struct task *DAT_060cb8d0;

// FUNCTION: SADX 0x00758d20
void FUN_00758d20()
{
	if (DAT_060cb8d0)
	{
		DestroyTask(DAT_060cb8d0);
		DAT_060cb8d0 = 0;
	}
}
