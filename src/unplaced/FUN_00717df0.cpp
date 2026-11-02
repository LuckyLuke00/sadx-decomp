#include "decls.h"
extern char DAT_060cb334;

// FUNCTION: SADX 0x00717df0
int FUN_00717df0()
{
	return DAT_060cb334;
}

// FUNCTION: SADX 0x00717e00
void FUN_00717e00(int param_1)
{
	dsStop_id(*((int *)(*(int *)(param_1 + 0x20) + 0x10)));
}

// FUNCTION: SADX 0x00717e20
void FUN_00717e20(int param_1)
{
	struct task *var1;
	struct taskwk *var2;
	int var3;
	int var4;

	var1 = (struct task *)param_1;
	var2 = (struct taskwk *)(*(int *)((char *)var1 + 0x20));
	var3 = *(int *)((char *)var2 + 0x10);
	if (*(int *)((char *)var2 + 0x1c) > 0)
	{
		var4 = ((*(int *)((char *)var2 + 0x1c) - 1) * *(int *)((char *)var2 + 0x14) + *(int *)((char *)var2 + 0x18)) / *(int *)((char *)var2 + 0x1c);
		dsVolume_id(var3, var4);
		*(int *)((char *)var2 + 0x1c) = *(int *)((char *)var2 + 0x1c) - 1;
		*(int *)((char *)var2 + 0x14) = var4;
	}
	if (*(int *)((char *)var2 + 0x28) > 0)
	{
		var4 = ((*(int *)((char *)var2 + 0x28) - 1) * *(int *)((char *)var2 + 0x20) + *(int *)((char *)var2 + 0x24)) / *(int *)((char *)var2 + 0x28);
		dsPan_id(var3, var4);
		*(int *)((char *)var2 + 0x28) = *(int *)((char *)var2 + 0x28) - 1;
		*(int *)((char *)var2 + 0x20) = var4;
	}
	if (*(int *)((char *)var2 + 0x34) > 0)
	{
		var4 = ((*(int *)((char *)var2 + 0x34) - 1) * *(int *)((char *)var2 + 0x2c) + *(int *)((char *)var2 + 0x30)) / *(int *)((char *)var2 + 0x34);
		dsPitch_id(var3, var4);
		*(int *)((char *)var2 + 0x34) = *(int *)((char *)var2 + 0x34) - 1;
		*(int *)((char *)var2 + 0x2c) = var4;
	}
}

// FUNCTION: SADX 0x00717eb0
struct task *FUN_00717eb0(int param_1, int param_2)
{
	struct task *var1;
	struct taskwk *var2;

	var1 = CreateElementalTask(2, 5, NULL);
	if (var1 != NULL)
	{
		dsPlay_timer(param_1, (int)var1, 1, 0, param_2);
		var1->exec = (void (__cdecl *)(struct task *))FUN_00717e20;
		var1->dest = (void (__cdecl *)(struct task *))FUN_00717e00;
		var2 = var1->twp;
		*(int *)((char *)var2 + 0x10) = (int)var1;
		*(int *)((char *)var2 + 0x14) = 0;
		*(int *)((char *)var2 + 0x18) = 0;
		*(int *)((char *)var2 + 0x1c) = 0;
		*(int *)((char *)var2 + 0x20) = 0;
		*(int *)((char *)var2 + 0x24) = 0;
		*(int *)((char *)var2 + 0x28) = 0;
		*(int *)((char *)var2 + 0x2c) = 0;
		*(int *)((char *)var2 + 0x30) = 0;
		*(int *)((char *)var2 + 0x34) = 0;
	}
	return var1;
}
