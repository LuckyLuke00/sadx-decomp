#include "decls.h"

// GLOBAL: SADX 0x0480c5f8
static struct CCL_INFO object_c_info[2];

// FUNCTION: SADX 0x0087d9a0
void ObjectCasinoSrdoor(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		struct taskwk *var1 = tp->twp;
		if (FUN_004c39c0(tp) == 0)
		{
			var1->ang.x = 0;
			*(long *)((char *)var1 + 0x1c) = 0;
			CCL_Init(tp, &object_c_info[0], 2, 4);
		}
		tp->disp = ObjectCasinoSrdoorDraw;
		tp->exec = ObjectCasinoSrdoorExec;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		var1->wtimer = 0;
		var1->mode = 0;
	}
}
