#include "decls.h"
extern struct task *DAT_05edd9b4;

// FUNCTION: SADX 0x00602360
struct task *SetAdvaExplainTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 3, FUN_00602430);
	DAT_05edd9b4 = local_8g;
	if (DAT_05edd9b4 != 0)
	{
		local_cg = CAlloc(1, 0x20);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_006023d0(local_8g, prmp);
		local_8g->exec = FUN_00602430;
		local_8g->disp = FUN_006026b0;
	}
	return local_8g;
}
