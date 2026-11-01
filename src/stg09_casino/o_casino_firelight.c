#include "decls.h"

// GLOBAL: SADX 0x0480bc98
static struct CCL_INFO object_c_info[1];

// FUNCTION: SADX 0x00878c90
void ObjectCasinoFirelight(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		tp->exec = ObjectCasinoFirelightExec;
		tp->dest = (void (*)(struct task *))FUN_007d21b0;
		tp->twp->wtimer = 0;
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, &object_c_info[0], 1, 4);
		}
	}
}
