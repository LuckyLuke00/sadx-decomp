#include "decls.h"
extern struct task *DAT_05edd9ac;

// FUNCTION: SADX 0x00600aa0
void FreeAdvaEmblemViewTask()
{
	if (DAT_05edd9ac)
	{
		DestroyTask(DAT_05edd9ac);
	}
}
