#include "decls.h"
extern struct task *DAT_060cca6c;

// FUNCTION: SADX 0x007da5a0
void frog_delete()
{
	if (DAT_060cca6c)
	{
		FreeTask(DAT_060cca6c);
		DAT_060cca6c = 0;
	}
}
