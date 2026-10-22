#include "decls.h"

// STUB: SADX 0x008d88b0
void FUN_008d88b0(struct taskwk *twp, struct enemywk *ewp)
{
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
