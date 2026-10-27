#include "decls.h"
void FUN_008c1fb0(int param_1);

// FUNCTION: SADX 0x008c1f20
void FUN_008c1f20(struct task *param_1, short *param_2)
{
	struct motionwk *local_8;
	local_8 = param_1->mwp;
	local_8->work.w[0] = 0;
	local_8->work.w[1] = param_2[0];
	*(int *)((char *)local_8 + 4) = *(int *)(param_2 + 2);
	*(int *)((char *)local_8 + 8) = *(int *)(param_2 + 4);
}

// FUNCTION: SADX 0x008c1f60
void FUN_008c1f60(int param_1)
{
	struct motionwk *local_8;
	local_8 = *(struct motionwk **)((char *)param_1 + 0x24);
	FUN_008c1fb0(param_1);
	local_8->work.w[0]++;
	if (local_8->work.w[0] >= local_8->work.w[1])
	{
		local_8->work.w[0] = 0;
	}
}

// STUB: SADX 0x008c1fb0
void FUN_008c1fb0(int param_1)
{
}

// FUNCTION: SADX 0x008c2030
void FUN_008c2030(int param_1)
{
	if (*(int *)param_1 != 0)
	{
		njRotateX(0, *(short *)param_1);
	}
}
