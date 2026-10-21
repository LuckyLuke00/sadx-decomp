#include "decls.h"
int FUN_007d5120();
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

// FUNCTION: SADX 0x007d5140
int FUN_007d5140()
{
	return FUN_007d5120();
}
