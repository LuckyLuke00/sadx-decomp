#include "decls.h"
extern struct task *DAT_060cc4ac;
extern struct task *DAT_060cc4a8;

// STUB: SADX 0x007d5320
void FUN_007d5320()
{
}

// FUNCTION: SADX 0x007d5340
void FUN_007d5340()
{
	if (DAT_060cc4a8)
	{
		FreeTask(DAT_060cc4a8);
		DAT_060cc4a8 = 0;
	}
}

// FUNCTION: SADX 0x007d5360
void FUN_007d5360()
{
	if (DAT_060cc4ac)
	{
		FreeTask(DAT_060cc4ac);
		DAT_060cc4ac = 0;
	}
}
