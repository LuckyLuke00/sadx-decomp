#include "decls.h"

// GLOBAL: SADX 0x03e71898
static struct CCL_INFO object_c_info[1];

// FUNCTION: SADX 0x0081ec70
void ObjectCurbCurb(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->counter.ptr = object_curb_curb01_curb01;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, object_c_info, 1, 4);
		SET_COLLI_RANGE(var1->cwp, 10.0f);
	}
	ObjectCCollision(tp);
}
