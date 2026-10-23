#include "decls.h"
extern struct task *DAT_060cba14;

// FUNCTION: SADX 0x00771e90
void FUN_00771e90(struct task *param_1)
{
	struct task *var1;
	struct task *var2;
	struct taskwk *var3;
	struct taskwk *var4;
	struct taskwk *var5;
	var1 = FUN_0056b1f0(3);
	var3 = var1->twp;
	var2 = FUN_0056b1f0(0);
	var4 = var2->twp;
	var5 = param_1->twp;
	var4->pos.x = var5->pos.x + var3->pos.x;
	var4->pos.y = var5->pos.y + var3->pos.y;
	var4->pos.z = var5->pos.z + var3->pos.z;
	*(int *)((char *)var4 + 0x18) = *(int *)((char *)var5 + 0x18) + *(int *)((char *)var3 + 0x18);
}

// STUB: SADX 0x00771ee0
void FUN_00771ee0()
{
}

// FUNCTION: SADX 0x00771f30
void FUN_00771f30()
{
	if (DAT_060cba14)
	{
		FreeTask(DAT_060cba14);
		DAT_060cba14 = 0;
	}
}
