#include "decls.h"
extern struct task *DAT_060ccb48;
void FreeTask(struct task *tp);

// STUB: SADX 0x007dbfd0
void FUN_007dbfd0(int param_1)
{
}

// FUNCTION: SADX 0x007dc010
void FUN_007dc010(void)
{
	if (DAT_060ccb48 != NULL)
	{
		FreeTask(DAT_060ccb48);
	}
}

// FUNCTION: SADX 0x007dc030
void FUN_007dc030(void)
{
	struct taskwk *var1 = DAT_060ccb48->twp;
	var1->timer.l = 0;
	var1->mode = 1;
}
