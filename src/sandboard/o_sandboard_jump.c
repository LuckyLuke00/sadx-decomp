#include "decls.h"
extern struct obj object_sunabo_sb_jpdai_sb_jpdai[1];

// FUNCTION: SADX 0x007e7680
void ObjectSandBoardJump(struct task *task_p)
{
	struct taskwk *var1;
	var1 = task_p->twp;
	*(unsigned char *)((char *)var1 + 2) = 9;
	var1->timer.ptr = object_sunabo_sb_jpdai_sb_jpdai;
	ObjectGCollision(task_p);
}
