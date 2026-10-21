#include "decls.h"
extern struct task *DAT_060cbb9c;

// FUNCTION: SADX 0x00791270
void FUN_00791270()
{
	if (DAT_060cbb9c)
	{
		FreeTask(DAT_060cbb9c);
		DAT_060cbb9c = 0;
	}
}
