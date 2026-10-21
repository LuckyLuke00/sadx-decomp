#include "decls.h"
extern struct task *DAT_05edd9b0;

// FUNCTION: SADX 0x00602340
void FreeAdvaMiniGameSelTask()
{
	if (DAT_05edd9b0)
	{
		DestroyTask(DAT_05edd9b0);
	}
}
