#include "decls.h"

// GLOBAL: SADX 0x0480b9b8
static struct CCL_INFO object_c_info[2];

// FUNCTION: SADX 0x00877fc0
void ObjectCasinoTsdoor(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		struct taskwk *var1 = tp->twp;
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, &object_c_info[0], 2, 4);
		}
		tp->disp = ObjectCasinoTsdoorDraw;
		tp->exec = ObjectCasinoTsdoorExec;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		var1->wtimer = 0;
		var1->mode = 0;
	}
}
