#include "decls.h"
void FUN_005dbda0(int param_1);
extern char DAT_05edd13e;

// FUNCTION: SADX 0x005db6d0
struct bosswk *BInitialize(struct taskwk *twp, unsigned int size)
{
	struct bosswk *local_8;

	local_8 = (struct bosswk *)CAlloc(1, size);
	if (local_8 != 0)
	{
		local_8->mtnmode = 0;
		local_8->jvmode = 0;
	}
	twp->flag |= 1;
	DAT_05edd13e = 0;
	return local_8;
}

// FUNCTION: SADX 0x005dbd40
void FUN_005dbd40(int param_1, int param_2)
{
	*(unsigned short *)(param_1 + 8) = *(unsigned char *)(*(int *)(param_1 + 0x2c) + param_2 * 0x10 + 6);
	*(unsigned short *)(param_1 + 0xa) = *(unsigned short *)(param_1 + 8);
	*(short *)(param_1 + 4) = *(char *)(*(int *)(param_1 + 0x2c) + *(unsigned short *)(param_1 + 0xa) * 0x10 + 5);
	FUN_005dbda0(param_1);
}

// STUB: SADX 0x005dbda0
void FUN_005dbda0(int param_1)
{
}

// STUB: SADX 0x005dbe10
void FUN_005dbe10(struct taskwk *param_1, struct bosswk *param_2)
{
}

// STUB: SADX 0x005dcde0
void BTerminateInterpolateMotion(struct taskwk *twp, struct bosswk *bwp)
{
}
