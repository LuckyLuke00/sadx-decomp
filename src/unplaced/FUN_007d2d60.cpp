#include "decls.h"
extern struct task *DAT_060cc140;
void FreeTask(struct task *tp);

// FUNCTION: SADX 0x007d2d60
void FUN_007d2d60(void)
{
	if (DAT_060cc140 != NULL)
	{
		FreeTask(DAT_060cc140);
	}
}
