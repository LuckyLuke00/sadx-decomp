#include "decls.h"

// GLOBAL: SADX 0x03feb7c0
static struct CCL_INFO object_c_info[2];

// FUNCTION: SADX 0x00835100
void ObjectMountainChair(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.ptr = object_denkiisu1a_denki_isu_denki_isu;
	var1->value.ptr = &texlist_obj_mountain;
	CCL_Init(tp, &object_c_info[1], 1, 4);
	ObjectCCollision(tp);
}
