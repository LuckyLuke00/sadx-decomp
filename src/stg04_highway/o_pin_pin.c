#include "decls.h"

// GLOBAL: SADX 0x03e71a48
static struct CCL_INFO object_c_info[3];

// FUNCTION: SADX 0x0081f5f0
void ObjectPinPin(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->counter.ptr = object_pin_pin_pin;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, object_c_info, 3, 4);
		SET_COLLI_RANGE(var1->cwp, 7.3f);
	}
	ObjectCCollision(tp);
}
