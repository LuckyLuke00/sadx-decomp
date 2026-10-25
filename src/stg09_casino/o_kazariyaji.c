#include "decls.h"

// STUB: SADX 0x008807d0
void ObjectKazariYaji(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->mode = 0;
	var1->btimer = 0;
	tp->exec = (void (__cdecl *)(struct task *))0x880790;
	tp->disp = (void (__cdecl *)(struct task *))0x8806c0;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
