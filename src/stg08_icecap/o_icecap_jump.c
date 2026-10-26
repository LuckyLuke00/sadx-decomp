#include "decls.h"

// FUNCTION: SADX 0x00867130
void ObjectIcecapJump(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	var1->id = 9;
	var1->timer.ptr = object_jpdai_all1_jpdai01_jpdai01;
	ObjectGCollision(tp);
}
