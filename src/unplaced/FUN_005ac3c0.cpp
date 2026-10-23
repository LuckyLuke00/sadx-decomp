#include "decls.h"

// FUNCTION: SADX 0x005ac3c0
void FUN_005ac3c0(struct task *param_1)
{
	struct taskwk *local_8;

	local_8 = param_1->twp;
	if (local_8->counter.l != 0)
	{
		Free(local_8->counter.ptr);
		local_8->counter.l = 0;
	}
}

// STUB: SADX 0x005ac490
int FUN_005ac490(int param_1)
{
	return (int)0;
}

// STUB: SADX 0x005ac4e0
int FUN_005ac4e0(int param_1)
{
	return (int)0;
}

// STUB: SADX 0x005ac7d0
void FUN_005ac7d0(unsigned char param_1, float *param_2)
{
}

// STUB: SADX 0x005ac8b0
void FUN_005ac8b0(struct NJS_POINT3 *param_1)
{
}
