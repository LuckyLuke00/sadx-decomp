#include "decls.h"
extern struct task *DAT_060cc340;

// FUNCTION: SADX 0x007d4f70
void deleteScanLine()
{
	if (DAT_060cc340)
	{
		FreeTask(DAT_060cc340);
		DAT_060cc340 = 0;
	}
}
