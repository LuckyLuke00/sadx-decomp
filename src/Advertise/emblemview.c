#include "decls.h"
void FUN_005ff9b0(struct anywk *param_1);
void FUN_005ff970(struct anywk *param_1);
void FUN_005ff920(struct task *param_1, struct ModeSelPrmType *param_2);
extern struct task *DAT_05edd9ac;

// STUB: SADX 0x005ff8b0
struct task *SetAdvaEmblemViewTask(struct ModeSelPrmType *prmp)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x005ff920
void FUN_005ff920(struct task *param_1, struct ModeSelPrmType *param_2)
{
	struct anywk *local_8;

	local_8 = param_1->awp;
	*(void **)((char *)local_8 + 4) = *(void **)param_2;
	*(void **)((char *)local_8 + 8) = *(void **)((char *)param_2 + 4);
	*(float *)((char *)local_8 + 0xc) = 5800.0f;
	*(int *)((char *)local_8 + 0) = 0;
	FUN_005ff970(local_8);
}

// FUNCTION: SADX 0x005ff970
void FUN_005ff970(struct anywk *param_1)
{
	FUN_005ff9b0(param_1);
	*(int *)((char *)param_1 + 0x18) = 0;
	*(int *)((char *)param_1 + 0x34) = 0;
	*(float *)((char *)param_1 + 0x2c) = 1.0f;
	*(unsigned char *)((char *)param_1 + 0x39) = 0xff;
}

// STUB: SADX 0x005ff9b0
void FUN_005ff9b0(struct anywk *param_1)
{
}

// FUNCTION: SADX 0x005ffba0
void FUN_005ffba0(struct anywk *param_1)
{
	AvaLoadTexForEachMode(ADVA_MODE_EMBLEMVIEW);
	SetAdvaModeBGM((enum AvaBgmEnum)4);
	FUN_005ff970(param_1);
	*(unsigned char *)((char *)param_1 + 0x3a) = 0;
	*(float *)((char *)param_1 + 0x30) = 0.0f;
	*(unsigned char *)((char *)param_1 + 0x3b) = 0;
}

// FUNCTION: SADX 0x00600aa0
void FreeAdvaEmblemViewTask()
{
	if (DAT_05edd9ac)
	{
		DestroyTask(DAT_05edd9ac);
	}
}
