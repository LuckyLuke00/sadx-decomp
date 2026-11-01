#include "decls.h"

// GLOBAL: SADX 0x03e715f8
static struct CCL_INFO object_c_info[4];

// FUNCTION: SADX 0x0081e650
void ObjectHighwayGate(struct task *tp)
{
	tp->twp->counter.ptr = object_gate_gate00_gate00;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, &object_c_info[1], 3, 4);
	}
	ObjectCCollision(tp);
}

// FUNCTION: SADX 0x0081e690
void ObjectHighwayFence(struct task *tp)
{
	tp->twp->counter.ptr = object_fence00_fen01_fen01;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, &object_c_info[0], 1, 4);
	}
	ObjectCCollision(tp);
}
