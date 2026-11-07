#include "decls.h"

// GLOBAL: SADX 0x045dace8
static struct CCL_INFO object_c_info[1];

extern struct obj object_obj_hako_obj_hako[];

// FUNCTION: SADX 0x00866e90
void ObjectHako(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	CCL_Init(tp, object_c_info, 1, 4);
	var1->counter.ptr = object_obj_hako_obj_hako;
	ObjectCCollision(tp);
}
