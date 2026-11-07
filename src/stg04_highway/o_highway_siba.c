#include "decls.h"

// GLOBAL: SADX 0x03e71778
static struct CCL_INFO object_c_info[2];

// FUNCTION: SADX 0x0081ea10
void ObjectHighwaySiba1(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->counter.ptr = object_obj_siba1_siba1;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, object_c_info, 1, 4);
		SET_COLLI_RANGE(var1->cwp, 29.0f);
	}
	ObjectCCollision(tp);
}

// FUNCTION: SADX 0x0081ea70
void ObjectHighwaySiba2(struct task *tp)
{
	tp->twp->counter.ptr = object_obj_siba2_siba2;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, &object_c_info[1], 1, 4);
	}
	ObjectCCollision(tp);
}
