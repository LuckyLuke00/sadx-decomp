#include "decls.h"
extern struct task *DAT_060cca28;

// FUNCTION: SADX 0x007d95a0
void E101Factory_Delete()
{
	if (DAT_060cca28)
	{
		FreeTask(DAT_060cca28);
		DAT_060cca28 = 0;
	}
}
