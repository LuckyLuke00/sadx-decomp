#include "decls.h"

// FUNCTION: SADX 0x008d88b0
void FUN_008d88b0(struct taskwk *param_1, struct enemywk *param_2)
{
	if (EnemyCheckDamage(param_1, param_2) != 0)
	{
		param_1->mode = 7;
		param_1->counter.b[0] = 0;
		param_1->counter.b[1] = 1;
		*(float *)((char *)param_1 + 0x34) = 0.35f;
	}
}

// FUNCTION: SADX 0x008d88f0
void FUN_008d88f0(struct task *param_1, struct taskwk *param_2, int param_3)
{
	if (CheckRangeOut(param_1) != 0)
	{
		FUN_008d8800((int)param_1, (int)param_2, param_3);
	}
	else
	{
		EntryColliList(param_2);
	}
}
