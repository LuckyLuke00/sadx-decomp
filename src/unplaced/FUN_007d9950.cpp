#include "decls.h"

// FUNCTION: SADX 0x007d9950
void FUN_007d9950(struct task *param_1)
{
	if (param_1)
	{
		FreeTask(param_1);
	}
}

// FUNCTION: SADX 0x007d9970
void FUN_007d9970(struct task *param_1, int param_2)
{
	param_1->twp->mode = param_2;
	param_1->mwp->spd.x = 0.0f;
	param_1->mwp->spd.z = 0.0f;
}
