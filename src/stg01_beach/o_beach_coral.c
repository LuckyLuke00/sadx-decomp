#include "decls.h"

// FUNCTION: SADX 0x007fedd0
void ObjectBeachCoralA(struct task *tp)
{
	tp->twp->counter.ptr = object_seaobj_sanngo00_sanngo00;
	ObjectScaleNormal(tp);
}

// FUNCTION: SADX 0x007fedf0
void ObjectBeachCoralB(struct task *tp)
{
	tp->twp->counter.ptr = object_seaobj_sanngo01_sanngo01;
	ObjectScaleNormal(tp);
}
