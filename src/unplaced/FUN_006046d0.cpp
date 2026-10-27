#include "decls.h"
struct task *FUN_00604760(struct task *param_1, struct ModeSelPrmType *param_2);
extern struct task *DAT_05edd9b8;

// FUNCTION: SADX 0x006046d0
void FUN_006046d0(void)
{
	if (DAT_05edd9b8)
	{
		DestroyTask(DAT_05edd9b8);
	}
}

// FUNCTION: SADX 0x006046f0
struct task *SetAdvaSndTestTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 3, snd_test_exec);
	DAT_05edd9bc = local_8g;
	if (DAT_05edd9bc != 0)
	{
		local_cg = CAlloc(1, 0x48);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_00604760(local_8g, prmp);
		local_8g->exec = snd_test_exec;
		local_8g->disp = snd_test_disp;
	}
	return local_8g;
}
