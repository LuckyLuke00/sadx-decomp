#include "decls.h"
struct taskwk *FUN_007430b0(struct task *param_1);
extern struct task *DAT_060cb770;

// STUB: SADX 0x007430b0
struct taskwk *FUN_007430b0(struct task *param_1)
{
	return (struct taskwk *)0;
}

// STUB: SADX 0x00743120
void FUN_00743120()
{
}

// FUNCTION: SADX 0x00743180
void FUN_00743180()
{
	if (DAT_060cb770)
	{
		FreeTask(DAT_060cb770);
		DAT_060cb770 = 0;
	}
}
