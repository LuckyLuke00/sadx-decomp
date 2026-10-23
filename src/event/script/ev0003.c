#include "decls.h"
extern struct task *DAT_060cbf58;

// STUB: SADX 0x007cd3f0
void tornado_disp(struct task *tp)
{
}

// STUB: SADX 0x007cd770
void tornado_cons(struct task *tp)
{
}

// FUNCTION: SADX 0x007cd7b0
void FUN_007cd7b0()
{
	DAT_060cbf58 = CreateElementalTask(2, 5, tornado_cons);
}

// FUNCTION: SADX 0x007cd7d0
void FUN_007cd7d0()
{
	if (DAT_060cbf58)
	{
		FreeTask(DAT_060cbf58);
		DAT_060cbf58 = 0;
	}
}
