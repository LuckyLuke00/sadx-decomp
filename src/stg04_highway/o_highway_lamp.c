#include "decls.h"

// GLOBAL: SADX 0x03e71ad8
static struct CCL_INFO object_c_info[1];

// FUNCTION: SADX 0x0081f800
void ObjectHighwayLamp01(struct task *tp)
{
	tp->twp->counter.ptr = object_lmp_lmpb_lmpb;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, &object_c_info[0], 1, 4);
	}
	ObjectCCollision_setNWZ(tp);
	ObjectCCollision_L(tp);
}

// FUNCTION: SADX 0x0081f840
void ObjectHighwayLamp02(struct task *tp)
{
	tp->twp->counter.ptr = object_lmpc_lmpc_lmpc;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, (struct CCL_INFO *)&object_c_info, 1, 4);
	}
	ObjectCCollision_setNWZ(tp);
	ObjectCCollision_L(tp);
}
