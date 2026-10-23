#include "decls.h"

// FUNCTION: SADX 0x008a5d90
void ObjShelterBluelight(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.f = 0.0f;
	tp->exec = (void (*)(struct task *))0x8a5ce0;
	tp->disp = (void (*)(struct task *))0x8a5c70;
}
