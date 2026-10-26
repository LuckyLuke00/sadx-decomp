#include "decls.h"
extern struct CCL_INFO cci_fence[];
extern struct obj object_ya_fence_body_body[];

// FUNCTION: SADX 0x00820d90
void ObjectFence(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, cci_fence, 1, 4);
	}
	*(struct obj **)((char *)var1 + 8) = object_ya_fence_body_body;
	ObjectCCollision(tp);
}
