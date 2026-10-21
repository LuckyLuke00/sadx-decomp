#include "decls.h"
static void title_menu_disp(struct task *tp);
extern struct task *DAT_05edd870;
void FUN_005f2090(float);

// FUNCTION: SADX 0x005f1030
struct task *SetAdvaAchivementTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 4, trial_game_exec);
	DAT_05edd870 = local_8g;
	if (DAT_05edd870 != 0)
	{
		local_cg = CAlloc(1, 0x28);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_005f22c0(local_8g, prmp);
		local_8g->exec = trial_game_exec;
		local_8g->disp = title_menu_disp;
	}
	return local_8g;
}

// STUB: SADX 0x005f1600
static void title_menu_disp(struct task *tp)
{
}

// FUNCTION: SADX 0x005f2070
void FUN_005f2070(struct task *param_1)
{
	FUN_005f2090(*(float *)((char *)param_1 + 0x10));
}
