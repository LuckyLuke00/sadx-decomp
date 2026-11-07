#include "decls.h"

// GLOBAL: SADX 0x03e71bec
static struct CCL_INFO object_c_info[1];

// FUNCTION: SADX 0x008209c0
void ObjectHighwaySign1(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->counter.ptr = object_ss_sign1_sign1;

	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, object_c_info, 1, 4);
		SET_COLLI_RANGE(var1->cwp, 21.0f);
	}
	ObjectCCollision_setWZ(tp);
	ObjectCCollision(tp);
}
