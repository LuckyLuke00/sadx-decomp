#include "decls.h"
extern struct task *DAT_060cc95c;

// FUNCTION: SADX 0x007d8d80
void deleteBoot()
{
	if (DAT_060cc95c)
	{
		FreeTask(DAT_060cc95c);
		DAT_060cc95c = 0;
	}
}
