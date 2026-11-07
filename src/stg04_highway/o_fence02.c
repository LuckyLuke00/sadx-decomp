#include "decls.h"

// GLOBAL: SADX 0x03e71868
static struct CCL_INFO object_c_info[1];

// FUNCTION: SADX 0x0081ec10
void ObjectFence02(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.ptr = object_fence02_fen02_fen02;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, object_c_info, 1, 4);
		SET_COLLI_RANGE(var1->cwp, 15.52f);
	}
	ObjectCCollision(tp);
}
