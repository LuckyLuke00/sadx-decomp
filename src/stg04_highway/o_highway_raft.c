#include "decls.h"

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
