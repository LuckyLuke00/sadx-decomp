#include "decls.h"

// FUNCTION: SADX 0x008078d0
void ObjectWindyStoneBridge(struct task *tp)
{
	tp->twp->timer.ptr = object_windobj_isibasi_isibasi;
	ObjectGCollision(tp);
}
