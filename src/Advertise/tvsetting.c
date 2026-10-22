#include "decls.h"
void FUN_005fd510(int param_1, int param_2);
void FUN_005fd320(struct task *param_1);
void FUN_005fd760(struct task *param_1);
extern struct task *DAT_05edd9a0;

// FUNCTION: SADX 0x005fd240
struct task *FUN_005fd240(struct ModeSelPrmType *param_1)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, FUN_005fd320);
	DAT_05edd9a0 = local_8g;
	if (DAT_05edd9a0)
	{
		local_cg = CAlloc(1, 0x38);
		local_8g->awp = (struct anywk *)local_cg;
		((void (*)(struct task *, struct ModeSelPrmType *))SetAdvaTvSettingTask)(local_8g, param_1);
		local_8g->exec = FUN_005fd320;
		local_8g->disp = FUN_005fd760;
	}
	return local_8g;
}

// STUB: SADX 0x005fd2b0
struct task *SetAdvaTvSettingTask(struct ModeSelPrmType *prmp)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x005fd300
void FUN_005fd300(struct anywk *param_1)
{
	*(unsigned char *)((char *)param_1 + 0x34) = 0;
	*(int *)((char *)param_1 + 0x18) = 0;
	*(unsigned char *)((char *)param_1 + 0x29) = 0;
}

// FUNCTION: SADX 0x005fd4c0
void FUN_005fd4c0(struct anywk *param_1)
{
	AvaLoadTexForEachMode(ADVA_MODE_TVSETTING);
	FUN_005fd300(param_1);
}

// FUNCTION: SADX 0x005fd4e0
void FUN_005fd4e0(int param_1)
{
	if (*(char *)(param_1 + 0x34) != 0)
	{
		FUN_005fd510(*(char *)(param_1 + 0x34), 1);
	}
}
