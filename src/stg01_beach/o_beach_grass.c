#include "decls.h"

// FUNCTION: SADX 0x007fed50
void ObjectBeachGrassA(struct task *tp)
{
	tp->twp->counter.ptr = object_seaobj_kusa4a_kusa4a;
	ObjectNormal(tp);
}

// FUNCTION: SADX 0x007fed70
void ObjectBeachGrassB(struct task *tp)
{
	tp->twp->counter.ptr = object_seaobj_kusa4b_kusa4b;
	ObjectScaleNormal(tp);
}

// FUNCTION: SADX 0x007fedb0
void ObjectBeachGrassD(struct task *tp)
{
	tp->twp->counter.ptr = object_seaobj_kusa3_kusa3;
	ObjectNormal(tp);
}
