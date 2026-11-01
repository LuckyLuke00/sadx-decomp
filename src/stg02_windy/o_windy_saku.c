#include "decls.h"

// GLOBAL: SADX 0x03b75b80
static struct CCL_INFO object_c_info[2];

// FUNCTION: SADX 0x00809f50
void ObjectWindySakuA(struct task *tp)
{
	tp->twp->counter.ptr = object_windobj_saku_a_saku_a;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, &object_c_info[0], 1, 4);
	}
	ObjectCCollision(tp);
}

// FUNCTION: SADX 0x00809f90
void ObjectWindySakuB(struct task *tp)
{
	tp->twp->counter.ptr = object_windobj_saku_b_saku_b;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, &object_c_info[1], 1, 4);
	}
	ObjectCCollision(tp);
}
