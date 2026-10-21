#include "decls.h"
extern struct task *DAT_05edd9b4;

// FUNCTION: SADX 0x00602710
void FUN_00602710(void)
{
	if (DAT_05edd9b4)
	{
		DestroyTask(DAT_05edd9b4);
	}
}
