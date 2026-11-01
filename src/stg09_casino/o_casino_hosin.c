#include "decls.h"

// GLOBAL: SADX 0x0480a26c
static struct CCL_INFO object_c_info[1];

// FUNCTION: SADX 0x0086e280
void ObjectCasinoHosin(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		tp->exec = ExecHosin;
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, &object_c_info[0], 1, 4);
			var1->cwp->info->a = var1->scl.x + 5.0f;
			CalcColliRange(var1->cwp);
		}
		var1->wtimer = 0;
	}
}
