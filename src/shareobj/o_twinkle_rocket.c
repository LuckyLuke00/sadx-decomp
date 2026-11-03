#include "decls.h"

// FUNCTION: SADX 0x008d2b10
void ObjectTPRocket(struct task *tp)
{
	struct taskwk *local_8g;
	struct anywk *local_cg;
	local_8g = tp->twp;
	local_cg = tp->awp;
	CheckRangeOutWithR(tp, 1020100.0f);
	if (((DAT_05b9d724 << 8) | DAT_05b9d744) != 0x300)
	{
		if ((((DAT_05b9d724 << 8) | DAT_05b9d744) & 0xff00) != 0x2300)
			return;
	}
	switch (local_8g->mode)
	{
	case 0:
		local_8g->mode = 1;
		tp->disp = dispTPRocket;
		tp->dest = FUN_0049e8b0;
		local_cg->work.sl[2] = 0x20;
		local_8g->scl.y = 0.2f;
	case 1:
		local_cg->work.sl[0] -= 0x200;
		local_cg->work.sl[1] += local_cg->work.sl[2];
		if (local_cg->work.sl[1] > 0x800 || local_cg->work.sl[1] < -0x800)
			local_cg->work.sl[2] = -local_cg->work.sl[2];
		local_8g->scl.x += local_8g->scl.y;
		if (local_8g->scl.x > 20.0 || local_8g->scl.x < -20.0)
			local_8g->scl.y = -local_8g->scl.y;
		dispTPRocket(tp);
		break;
	}
}
