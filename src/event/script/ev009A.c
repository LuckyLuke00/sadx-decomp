#include "decls.h"
extern struct task *DAT_060cb8d4;
extern struct task *DAT_060cb8d0;

// STUB: SADX 0x00758c60
void light_cons(struct task *tp)
{
}

// FUNCTION: SADX 0x00758d00
void FUN_00758d00()
{
	DAT_060cb8d0 = CreateElementalTask(0, 1, light_cons);
}

// FUNCTION: SADX 0x00758d20
void FUN_00758d20()
{
	if (DAT_060cb8d0)
	{
		DestroyTask(DAT_060cb8d0);
		DAT_060cb8d0 = 0;
	}
}

// FUNCTION: SADX 0x00758d40
void FUN_00758d40()
{
	if (DAT_060cb8d4)
	{
		FreeTask(DAT_060cb8d4);
	}
}
