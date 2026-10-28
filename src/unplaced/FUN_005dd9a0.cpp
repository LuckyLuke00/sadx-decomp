#include "decls.h"

// FUNCTION: SADX 0x005dd9a0
void FUN_005dd9a0(void *param_1)
{
	*(float *)((char *)param_1 + 0x34) = *(float *)((char *)param_1 + 0x34) + 0.10999999940395355;
	if (5.0 <= *(float *)((char *)param_1 + 0x34))
	{
		*(char *)param_1 = 2;
		*(float *)((char *)param_1 + 0x34) = 1.0;
	}
}

// FUNCTION: SADX 0x005ddbf0
void FUN_005ddbf0(struct task *param_1)
{
	struct taskwk *local_8;

	local_8 = param_1->twp;
	if (param_1->ocp != 0)
	{
		if (FUN_00551570((int)param_1) != 0)
		{
			local_8->mode = local_8->mode;
		}
		else
		{
			FUN_00551530((int)param_1);
			FUN_005de120(local_8);
		}
	}
	else
	{
		FUN_005de120(local_8);
	}
	FUN_005e5770(param_1);
	FUN_004da910((int)local_8);
	CCL_Init(param_1, itembox_colli_info1, 2, 4);
	local_8->mode = 4;
}

// STUB: SADX 0x005ddc80
void FUN_005ddc80(struct task *param_1)
{
}

// STUB: SADX 0x005ddea0
void FUN_005ddea0(struct task *param_1)
{
}
