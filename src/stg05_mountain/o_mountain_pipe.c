#include "decls.h"

// FUNCTION: SADX 0x00834760
void ObjectMountainPipeI(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->counter.ptr = (void *)0x3f5d4ec;
	var1->value.ptr = (void *)0x3f42728;
	if (var1->mode == 0)
	{
		CCL_Init(tp, (struct CCL_INFO *)0x3feb688, 1, 4);
	}
	CheckCollisionScale(var1);
	ObjectScaleCCollision(tp);
}
