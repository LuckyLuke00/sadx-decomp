#include "decls.h"
void FUN_00602430(struct task *param_1);
void FUN_006026b0(struct task *param_1);
extern struct task *DAT_05edd9b4;

// FUNCTION: SADX 0x00602360
struct task *FUN_00602360(struct ModeSelPrmType *param_1)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 3, FUN_00602430);
	DAT_05edd9b4 = local_8g;
	if (DAT_05edd9b4)
	{
		local_cg = CAlloc(1, 0x20);
		local_8g->awp = (struct anywk *)local_cg;
		((void (*)(struct task *, struct ModeSelPrmType *))SetAdvaExplainTask)(local_8g, param_1);
		local_8g->exec = FUN_00602430;
		local_8g->disp = FUN_006026b0;
	}
	return local_8g;
}
