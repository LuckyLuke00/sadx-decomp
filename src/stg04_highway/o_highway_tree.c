#include "decls.h"

// GLOBAL: SADX 0x03e717d8
static struct CCL_INFO object_c_info[3];

// FUNCTION: SADX 0x0081eab0
void ObjectHighwayGreen(struct task *tp)
{
	tp->twp->counter.ptr = object_green_g_belt_g_belt;
	ObjectNormal(tp);
}

// FUNCTION: SADX 0x0081ead0
void ObjectHighwayGreenA(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->counter.ptr = object_st_green_basin_a_basin_a;

	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, object_c_info, 1, 4);
		SET_COLLI_RANGE(var1->cwp, 8.0f);
	}
	ObjectCCollision(tp);
}

// FUNCTION: SADX 0x0081eb30
void ObjectHighwayGreenB(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	*(struct obj **)((char *)var1 + 8) = object_st_green_basin_b_basin_b;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, &object_c_info[1], 1, 4);
		SET_COLLI_RANGE(var1->cwp, 8.0f);
	}
	ObjectCCollision(tp);
}

// FUNCTION: SADX 0x0081eb90
void ObjectHighwayGreenD(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	*(struct obj **)((char *)var1 + 8) = object_st_green_basin_d_basin_d;
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, &object_c_info[2], 1, 4);
		SET_COLLI_RANGE(var1->cwp, 8.0f);
	}
	ObjectCCollision(tp);
}

// FUNCTION: SADX 0x0081ebf0
void ObjectHighwayGreenE(struct task *tp)
{
	tp->twp->counter.ptr = object_green_g_belt_a_g_belt_a;
	ObjectNormal(tp);
}
