#include "decls.h"
struct task;
struct taskwk;

// FUNCTION: SADX 0x008e1ab0
void FUN_008e1ab0(struct task *param_1)
{
	struct taskwk *local_18;
	struct NJS_POINT3 local_14;

	local_18 = param_1->twp;
	local_14.x = local_18->scl.x + 1.0f;
	njPushMatrix(0);
	FUN_0067d830(0, local_18->pos.x, local_18->pos.y, local_18->pos.z);
	FUN_0067d2d0(0, local_14.x, local_14.x, local_14.x);
	___dsDrawObject(&object_sphere01);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008e1b50
void FUN_008e1b50(struct task *param_1)
{
	struct taskwk *local_8;
	local_8 = param_1->twp;
	if (CheckCollisionP(&local_8->pos, 14.0f * (1.0f + local_8->scl.x)) == 1)
	{
		SetFinishAction();
		local_8->mode = 5;
	}
}
