#include "decls.h"
void FUN_005f3310(float);
void FUN_005f2320(struct task *);
extern struct task *DAT_05edd888;
void FUN_005f2850(struct task *);

// FUNCTION: SADX 0x005f2250
struct task *FUN_005f2250(struct ModeSelPrmType *param_1)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, FUN_005f2320);
	DAT_05edd888 = local_8g;
	if (DAT_05edd888 != 0)
	{
		local_cg = CAlloc(1, 0x28);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005f22c0(local_8g, param_1);
		local_8g->exec = FUN_005f2320;
		local_8g->disp = FUN_005f2850;
	}
	return local_8g;
}

// FUNCTION: SADX 0x005f32f0
void FUN_005f32f0(struct task *param_1)
{
	FUN_005f3310(*(float *)((char *)param_1 + 0x10));
}
