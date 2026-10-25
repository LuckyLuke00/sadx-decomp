#include "decls.h"
struct task;
struct taskwk;

// FUNCTION: SADX 0x008e1b50
void FUN_008e1b50(struct task *param_1)
{
	struct taskwk *local_8;
	local_8 = param_1->twp;
	if (CheckCollisionP(&local_8->pos, 14.0f * (1.0f + *(float *)((char *)local_8 + 0x2c))) == 1)
	{
		SetFinishAction();
		local_8->mode = 5;
	}
}
