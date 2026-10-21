#include "decls.h"

// FUNCTION: SADX 0x00808e10
void ObjectWindyBigFloot(struct task *tp)
{
	tp->twp->timer.ptr = object_windobj_bigfloot_bigfloot;
	ObjectGCollision(tp);
}
