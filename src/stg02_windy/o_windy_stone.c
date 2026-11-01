#include "decls.h"

// GLOBAL: SADX 0x03b75998
static struct CCL_INFO object_c_info[2];

// FUNCTION: SADX 0x008092c0
void ObjectWindyIshiA(struct task *tp)
{
	tp->twp->counter.ptr = object_wvobj_sekichu_a_sekichu_a;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, &object_c_info[0], 1, 4);
	}
	ObjectCCollision(tp);
}

// FUNCTION: SADX 0x00809300
void ObjectWindyIshiB(struct task *tp)
{
	tp->twp->counter.ptr = object_wvobj_sekichu_b_sekichu_b;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, &object_c_info[1], 1, 4);
	}
	ObjectCCollision(tp);
}
