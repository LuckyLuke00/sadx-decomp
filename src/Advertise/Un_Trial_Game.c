#include "decls.h"
static void title_menu_disp(struct task *tp);
void FUN_005f3540(struct task *);
extern struct task *DAT_05edd89c;
void FUN_005f4610(float);

// FUNCTION: SADX 0x005f3480
struct task *SetAdvaTrialGameTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, FUN_005f3540);
	DAT_05edd89c = local_8g;
	if (DAT_05edd89c != 0)
	{
		local_cg = CAlloc(1, 0x28);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005f22c0(local_8g, prmp);
		local_8g->exec = FUN_005f3540;
		local_8g->disp = title_menu_disp;
	}
	return local_8g;
}

// STUB: SADX 0x005f3b60
static void title_menu_disp(struct task *tp)
{
}

// FUNCTION: SADX 0x005f45f0
void FUN_005f45f0(struct task *param_1)
{
	FUN_005f4610(*(float *)((char *)param_1 + 0x10));
}
