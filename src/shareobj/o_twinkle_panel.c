#include "decls.h"

// FUNCTION: SADX 0x008d54c0
void ObjectTPPanel(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	if (CheckRangeOutWithR(tp, 9060100.0f) != 0)
		return;
	if (((DAT_05b9d724 << 8) | DAT_05b9d744) != 0x300)
	{
		if ((((DAT_05b9d724 << 8) | DAT_05b9d744) & 0xff00) != 0x2300)
			return;
	}
	if (CheckEditMode() != 0)
	{
		local_8->counter.ptr = &object_tpobj_paneru_paneru[0];
		local_8->scl.x = 0.0;
		dispTPPanel(tp);
		return;
	}
	switch (local_8->mode)
	{
		case 0:
			local_8->mode = 1;
			local_8->counter.ptr = &object_tpobj_paneru_paneru[0];
			tp->dest = FUN_0049e8b0;
			tp->disp = dispTPPanel;
			break;
		case 1:
			local_8->value.l += 0x100;
			local_8->scl.x = njSin(local_8->value.l);
			if (local_8->scl.x < -0.8f)
				local_8->scl.x = -0.8f;
			dispTPPanel(tp);
			break;
	}
}
