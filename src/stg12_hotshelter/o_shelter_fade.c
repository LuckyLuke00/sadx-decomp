#include "decls.h"

// FUNCTION: SADX 0x008b5890
void ObjShelterFade(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.f = 0.0f;
	var1->mode = 0;
	tp->exec = (void (*)(struct task *))0x8b57a0;
	tp->disp = (void (*)(struct task *))0x8b56e0;
}
