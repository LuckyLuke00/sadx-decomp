#include "decls.h"
extern struct task *DAT_05edd9a0;

// FUNCTION: SADX 0x005fdd20
void FUN_005fdd20(void)
{
	if (DAT_05edd9a0)
	{
		DestroyTask(DAT_05edd9a0);
	}
}
