#include "decls.h"

// STUB: SADX 0x00609ad0
void FUN_00609ad0(struct task *param_1, struct enemywk *param_2)
{
}

// FUNCTION: SADX 0x00609b40
void FUN_00609b40(int param_1)
{
	float local_8;

	local_8 = *(float *)(param_1 + 0x30) - 1.0f;
	*(float *)(param_1 + 0x34) = (-*(float *)(param_1 + 0x34) * 0.12f - local_8 * 0.32f) + *(float *)(param_1 + 0x34);
	*(float *)(param_1 + 0x30) = *(float *)(param_1 + 0x30) + *(float *)(param_1 + 0x34);
	*(float *)(param_1 + 0x2c) = 2.0f - *(float *)(param_1 + 0x30);
}

// FUNCTION: SADX 0x0060a0c0
void FUN_0060a0c0(struct taskwk *param_1, struct enemywk *param_2)
{
	int local_8;

	param_1->flag &= 0xfffffeff;
	local_8 = *(int *)((char *)param_1 + 0x18);
	*(int *)((char *)param_1 + 0x18) = *(int *)((char *)param_2 + 0x1b0);
	if (EnemySearchPlayer(param_1, param_2) == 1)
	{
		param_1->flag |= 0x100;
	}
	*(int *)((char *)param_1 + 0x18) = local_8;
}

// STUB: SADX 0x0060a360
void FUN_0060a360(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x0060a7c0
void FUN_0060a7c0(char *param_1)
{
}
