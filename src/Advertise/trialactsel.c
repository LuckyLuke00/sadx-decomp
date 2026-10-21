#include "decls.h"
extern struct task *DAT_05edd9c0;

// FUNCTION: SADX 0x00607bc0
void FreeAdvaTrialActSelTask()
{
	if (DAT_05edd9c0)
	{
		DestroyTask(DAT_05edd9c0);
	}
}
