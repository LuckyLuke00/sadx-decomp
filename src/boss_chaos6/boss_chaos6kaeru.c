#include "decls.h"
void setDirC6Kaeru2(struct task *tp);
extern unsigned short DAT_05cd296c;
extern unsigned char DAT_060c32ab;

// FUNCTION: SADX 0x006fa6d0
void FUN_006fa6d0(int param_1)
{
	int iVar1;

	iVar1 = *(int *)(param_1 + 0x20);
	*(short *)(iVar1 + 0x10) = *(short *)(iVar1 + 0x10) - 1;
	if (*(short *)(iVar1 + 0x10) <= 0)
	{
		*(int *)(iVar1 + 0x18) = *(int *)(iVar1 + 0x18) + 0xb6;
		*(short *)(iVar1 + 0x10) = 3;
	}
}

// STUB: SADX 0x006fa700
void setDirC6Kaeru2(struct task *tp)
{
}

// FUNCTION: SADX 0x006faab0
void setCatchingC6Kaeru(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	var1->ang.y = 0;
	var1->ang.x = 0;
	var1->ang.z = 0x4000;
	DAT_05cd296c |= 0x400;
	var1 = tp->twp;
	if (var1->counter.ptr != action_f_f0023_frog)
	{
		var1->timer.f = 0.0f;
		var1->counter.ptr = action_f_f0023_frog;
		var1->timer.f = 0.0f;
	}
	SetFinishAction();
	DAT_060c32ab = 1;
}
