#include "decls.h"

// GLOBAL: SADX 0x03a0c878
static struct CCL_INFO object_c_info[4];

// FUNCTION: SADX 0x007fee90
void ObjectBeachFenceC(struct task *tp)
{
	tp->twp->counter.ptr = object_seaobj_tesuric_tesuric;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, &object_c_info[2], 1, 4);
	}
	ObjectCCollision_L(tp);
}

// FUNCTION: SADX 0x007feed0
void ObjectBeachFenceD(struct task *tp)
{
	tp->twp->counter.ptr = object_seaobj_tesurie_tesurie;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, &object_c_info[3], 1, 4);
	}
	ObjectCCollision_L(tp);
}
