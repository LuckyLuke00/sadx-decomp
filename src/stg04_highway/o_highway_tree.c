#include "decls.h"

// FUNCTION: SADX 0x0081eab0
void ObjectHighwayGreen(struct task *tp)
{
	tp->twp->counter.ptr = object_green_g_belt_g_belt;
	ObjectNormal(tp);
}

// FUNCTION: SADX 0x0081ebf0
void ObjectHighwayGreenE(struct task *tp)
{
	tp->twp->counter.ptr = object_green_g_belt_a_g_belt_a;
	ObjectNormal(tp);
}
