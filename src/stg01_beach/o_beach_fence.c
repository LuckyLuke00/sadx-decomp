#include "decls.h"
extern struct CCL_INFO DAT_03a0c908[];
extern struct CCL_INFO DAT_03a0c8d8;

// FUNCTION: SADX 0x007fee90
void ObjectBeachFenceC(struct task *tp)
{
	tp->twp->counter.ptr = object_seaobj_tesuric_tesuric;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, &DAT_03a0c8d8, 1, 4);
	}
	ObjectCCollision_L(tp);
}

// FUNCTION: SADX 0x007feed0
void ObjectBeachFenceD(struct task *tp)
{
	tp->twp->counter.ptr = object_seaobj_tesurie_tesurie;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, DAT_03a0c908, 1, 4);
	}
	ObjectCCollision_L(tp);
}
