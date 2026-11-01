#include "decls.h"

// GLOBAL: SADX 0x03e714a8
static struct CCL_INFO object_c_info[1];

// FUNCTION: SADX 0x0081d410
void ObjectHighwayRaftA(struct task *tp)
{
	tp->twp->timer.ptr = object_asi1_asi_a_asi_a;
	ObjectGCollision(tp);
}

// FUNCTION: SADX 0x0081d430
void ObjectHighwayRaftC(struct task *tp)
{
	tp->twp->timer.ptr = object_asi_asi_3_asi_3;
	ObjectGCollision(tp);
}

// FUNCTION: SADX 0x0081d450
void ObjectHighwayTunagi(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	*(struct obj **)((char *)var1 + 8) = object_ss_tunagidai_tunagidai;

	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, object_c_info, 1, 4);
		SET_COLLI_RANGE(var1->cwp, 14.0f);
	}
	ObjectCCollision_L(tp);
}

// FUNCTION: SADX 0x0081d4b0
void ObjectHighwayHeliPLight(struct task *tp)
{
	tp->twp->counter.ptr = object_hwobj_portlght_portlght;
	ObjectCCollision_setNWZ(tp);
	ObjectNormal(tp);
}
