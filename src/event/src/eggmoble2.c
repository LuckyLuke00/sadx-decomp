#include "decls.h"
extern struct task *DAT_060ccdc8;

// FUNCTION: SADX 0x007de9d0
void EV_deleggmoble2()
{
	if (DAT_060ccdc8)
	{
		FreeTask(DAT_060ccdc8);
		DAT_060ccdc8 = 0;
	}
}
