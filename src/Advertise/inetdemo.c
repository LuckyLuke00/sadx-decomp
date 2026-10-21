#include "decls.h"
extern struct task *DAT_05edd9a4;

// FUNCTION: SADX 0x005ff890
void FreeAdvaInetDemoTask()
{
	if (DAT_05edd9a4)
	{
		DestroyTask(DAT_05edd9a4);
	}
}
