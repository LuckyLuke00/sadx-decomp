#include "decls.h"
extern struct task *DAT_060ccdc4;

// FUNCTION: SADX 0x007ddaa0
void DeleteEggmoble1()
{
	if (DAT_060ccdc4)
	{
		FreeTask(DAT_060ccdc4);
		DAT_060ccdc4 = 0;
	}
}
