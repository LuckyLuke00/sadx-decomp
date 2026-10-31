#include "decls.h"
static void FExec(struct task *tp);
extern struct task *DAT_05edd778;
extern int DAT_060ce75c;
void FUN_007f2150(void);

// FUNCTION: SADX 0x005e8510
struct task *SetAdvaPutiTask(struct ModeSelPrmType *prmp)
{
	DAT_05edd778 = CreateElementalTask(0, 4, FExec);
	return DAT_05edd778;
}

// STUB: SADX 0x005e8530
static void FExec(struct task *tp)
{
}

// FUNCTION: SADX 0x005e86e0
void FUN_005e86e0(void *param_1)
{
	syFree(*(void **)((char *)param_1 + 4));
	*(void **)((char *)param_1 + 4) = 0;
}

// FUNCTION: SADX 0x005e8700
void FUN_005e8700(struct AlrReal *param_1)
{
	GameGearLoop();
}

// FUNCTION: SADX 0x005e8710
void FDest(struct task *tp)
{
	struct anywk *local_8;

	local_8 = tp->awp;
	if (local_8->work.ul[1] != 0)
	{
		FUN_005e86e0(local_8);
	}
	Free(local_8);
	tp->awp = 0;
	if (DAT_060ce75c != 0)
	{
		FUN_007f2150();
	}
	return;
}

// FUNCTION: SADX 0x005e8760
void FreeAdvaPutiTask()
{
	FreeTask(DAT_05edd778);
}
