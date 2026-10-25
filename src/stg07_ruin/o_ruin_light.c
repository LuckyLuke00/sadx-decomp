#include "decls.h"

// FUNCTION: SADX 0x00853c00
void ObjectRuinLight(struct task *tp)
{
	tp->twp->counter.ptr = object_lwobj_komorebi2_komorebi2;
	ObjectCCollision_setNWZ(tp);
	ObjectScaleNormal(tp);
}
