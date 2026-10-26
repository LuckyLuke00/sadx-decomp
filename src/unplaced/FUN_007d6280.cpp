#include "decls.h"
extern struct task *DAT_060cc57c;

// FUNCTION: SADX 0x007d6280
void FUN_007d6280(float param_1, float param_2, float param_3, long param_4, long param_5, long param_6)
{
	struct task *var1;
	struct taskwk *var2;

	var1 = CreateElementalTask(2, 5, eggmoble_init);
	if (var1)
	{
		var2 = var1->twp;
		var2->pos.x = param_1;
		var2->ang.x = param_4;
		var2->pos.y = param_2;
		var2->ang.y = param_5;
		var2->pos.z = param_3;
		var2->ang.z = param_6;
		var2->scl.x = 1.0f;
		DAT_060cc57c = var1;
		var2->scl.y = 1.0f;
		var2->scl.z = 1.0f;
	}
}

// FUNCTION: SADX 0x007d62e0
void FUN_007d62e0()
{
	if (DAT_060cc57c)
	{
		FreeTask(DAT_060cc57c);
		DAT_060cc57c = 0;
	}
}
