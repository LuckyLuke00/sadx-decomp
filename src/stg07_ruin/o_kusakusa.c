#include "decls.h"

// FUNCTION: SADX 0x00855c20
void ObjectGakekusa(struct task *tp)
{
	tp->twp->counter.ptr = object_los_nc_gakeshoku_nc_gakeshoku;
	ObjectNormal(tp);
}
