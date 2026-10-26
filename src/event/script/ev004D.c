#include "decls.h"
extern struct task *DAT_060cbb94;

// STUB: SADX 0x0078da40
void gattai_exec(struct task *tp)
{
}

// FUNCTION: SADX 0x0078da80
void FUN_0078da80(struct task *param_1)
{
	struct task *var1;
	struct task *var2;
	struct taskwk *var3;
	struct taskwk *var4;
	struct taskwk *var5;
	var1 = FUN_0056b1f0(0);
	var3 = var1->twp;
	var2 = FUN_0056b1f0(2);
	var4 = var2->twp;
	var5 = param_1->twp;
	var4->pos.x = var5->pos.x + var3->pos.x + 0.0;
	var4->pos.y = var5->pos.y + var3->pos.y - 2.0;
	var4->pos.z = var5->pos.z + var3->pos.z - 3.5;
	*(int *)((char *)var4 + 0x18) = *(int *)((char *)var5 + 0x18) + *(int *)((char *)var3 + 0x18);
}

// STUB: SADX 0x0078dae0
void FUN_0078dae0()
{
}

// FUNCTION: SADX 0x0078db30
void FUN_0078db30()
{
	if (DAT_060cbb94)
	{
		FreeTask(DAT_060cbb94);
		DAT_060cbb94 = 0;
	}
}
