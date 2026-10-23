#include "decls.h"
extern struct task *DAT_060cbf64;

// FUNCTION: SADX 0x007ce580
void FUN_007ce580()
{
	if (DAT_060cbf64)
	{
		FreeTask(DAT_060cbf64);
		DAT_060cbf64 = 0;
	}
}

// STUB: SADX 0x007ce5a0
void FUN_007ce5a0(float param_1, float param_2, float param_3, int param_4)
{
}

// STUB: SADX 0x007ce600
void FUN_007ce600(int param_1)
{
}
