#include "decls.h"

// STUB: SADX 0x00858420
void Wait(struct task *tp)
{
}

// FUNCTION: SADX 0x00858500
void ObjectWater(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->scl.y = 1.0;
	tp->exec = Wait;
	var1->scl.z = 0.0;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
