#include "decls.h"
extern struct task *DAT_060cc4c8;

// FUNCTION: SADX 0x007d5620
void FUN_007d5620(int param_1)
{
	struct task *var1;
	struct taskwk *var2;
	void *var3;

	if (DAT_060cc4c8 == 0)
		return;
	var1 = DAT_060cc4c8;
	var2 = var1->twp;
	var3 = *(void **)((char *)var2 + 0x10);
	*(float *)((char *)DAT_05edd128 + 0x20) = *(float *)var3;
	*(float *)((char *)DAT_05edd128 + 0x24) = *(float *)((char *)var3 + 4);
	*(float *)((char *)DAT_05edd128 + 0x28) = *(float *)((char *)var3 + 8);
	*(int *)((char *)DAT_05edd128 + 0x14) = *(int *)((char *)var3 + 0xc);
	*(int *)((char *)DAT_05edd128 + 0x18) = *(int *)((char *)var3 + 0x10);
	*(int *)((char *)DAT_05edd128 + 0x1c) = *(int *)((char *)var3 + 0x14);
	DestroyTask(var1);
	DAT_060cc4c8 = 0;
	if (param_1 != 0)
		EvChaosExit();
}
