#include "decls.h"

// FUNCTION: SADX 0x005c5ae0
void FUN_005c5ae0(struct task *param_1)
{
	struct taskwk *local_8 = param_1->twp;
	local_8->scl.x = local_8->scl.x - 0.44999998807907104;
	if (local_8->scl.x < 0.0)
	{
		local_8->scl.x = 0.0;
		local_8->mode = 0;
		local_8->wtimer = 0;
	}
	AirLiftDraw(param_1);
}
