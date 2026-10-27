#include "decls.h"

extern int DAT_060cc790[1];

// FUNCTION: SADX 0x007d72d0
void FUN_007d72d0(short param_1)
{
	if (DAT_060cc790[param_1] != 0)
	{
		DestroyTask((struct task *)DAT_060cc790[param_1]);
		DAT_060cc790[param_1] = 0;
	}
}
