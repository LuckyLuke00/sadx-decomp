#include "decls.h"

// GLOBAL: SADX 0x03e71c50
static struct CCL_INFO object_c_info[2];

// FUNCTION: SADX 0x00820dd0
void ObjectBench(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	*(struct obj **)((char *)var1 + 8) = object_obj_bench_bench_bench;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, object_c_info, 2, 4);
		SET_COLLI_RANGE(var1->cwp, 20.0f);
	}
	ObjectCCollision(tp);
}
