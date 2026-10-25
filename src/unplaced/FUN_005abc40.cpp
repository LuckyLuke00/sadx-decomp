#include "decls.h"
void FUN_005abd00(int param_1);
void FUN_005abd40(int param_1);

// STUB: SADX 0x005abc40
void FUN_005abc40(int param_1)
{
}

// STUB: SADX 0x005abca0
void FUN_005abca0(int param_1)
{
}

// STUB: SADX 0x005abd00
void FUN_005abd00(int param_1)
{
}

// FUNCTION: SADX 0x005abd40
void FUN_005abd40(int param_1)
{
	struct taskwk *local_8;

	local_8 = ((struct task *)param_1)->twp;
	if (local_8->counter.l != 0)
	{
		FUN_005ac1a0((struct task *)param_1);
	}
}
