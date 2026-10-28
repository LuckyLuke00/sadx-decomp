#include "decls.h"
struct NJS_POINT3;
int FUN_005ac4e0(int param_1);

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

// STUB: SADX 0x005ac400
void *FUN_005ac400(int param_1)
{
	return (void *)0;
}

// FUNCTION: SADX 0x005ac490
int FUN_005ac490(int param_1)
{
	int local_8g;
	int local_cj;
	int local_10;

	local_8g = *(int *)(param_1 + 0xc);
	local_cj = 0;
	local_10 = *(unsigned short *)(param_1 + 0x14);
	do
	{
		local_cj = FUN_005ac4e0(local_8g) + local_cj;
		local_8g = local_8g + 0x1c;
		local_10 = local_10 - 1;
	} while (local_10 != 0);
	return local_cj;
}

// STUB: SADX 0x005ac4e0
int FUN_005ac4e0(int param_1)
{
	return (int)0;
}

// STUB: SADX 0x005ac540
void FUN_005ac540(int param_1, int param_2, int param_3, int param_4)
{
}

// STUB: SADX 0x005ac7d0
void FUN_005ac7d0(unsigned char param_1, float *param_2)
{
}

// STUB: SADX 0x005ac8b0
void FUN_005ac8b0(struct NJS_POINT3 *param_1)
{
}
