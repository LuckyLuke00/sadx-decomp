#include "decls.h"
extern struct task *DAT_05edd9bc;

// FUNCTION: SADX 0x00606340
void FUN_00606340(void)
{
	if (DAT_05edd9bc)
	{
		DestroyTask(DAT_05edd9bc);
	}
}
