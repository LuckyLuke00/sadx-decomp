#include "decls.h"
extern int DAT_05cd2978;
extern struct NJS_ACTION action_f_f0023_frog[1];
extern unsigned short DAT_05cd296c;
void FUN_00595f80(int param_1, int param_2);

// STUB: SADX 0x00595dd0
void setDirKaeru(struct task *tp)
{
}

// STUB: SADX 0x00595e40
void setDirKaeru2(struct task *tp)
{
}

// FUNCTION: SADX 0x00595f80
void FUN_00595f80(int param_1, int param_2)
{
	int iVar1;

	iVar1 = *(int *)(param_1 + 0x20);
	if (*(int *)(iVar1 + 8) != param_2)
	{
		*(int *)(iVar1 + 8) = param_2;
		*(float *)(iVar1 + 0xc) = 0.0f;
	}
}

// STUB: SADX 0x00595fb0
long chkAngLimit(struct task *tp, struct NJS_POINT3 *next_pos)
{
	return (long)0;
}

// STUB: SADX 0x00596120
void setDirKaeru3(struct task *tp)
{
}

// FUNCTION: SADX 0x00596760
void setCatchingKaeru(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	*(int *)((char *)local_8 + 0x18) = 0;
	*(int *)((char *)local_8 + 0x14) = 0;
	*(int *)((char *)local_8 + 0x1c) = 0x4000;
	DAT_05cd296c |= 0x400;
	FUN_00595f80((int)tp, (int)&action_f_f0023_frog);
}

// STUB: SADX 0x005967c0
void moveCatchingKaeru(struct task *tp)
{
}

// STUB: SADX 0x00596b30
long chkDistanceLure(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x00597500
void motionBigKaeru(struct task *tp)
{
}

// STUB: SADX 0x005977c0
void moveFishingKaeru(struct task *tp)
{
}

// FUNCTION: SADX 0x005979c0
void setKaeruFree(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	local_8->mode = 1;
	if (tp->mwp->height > 1.0f)
	{
		tp->mwp->height -= 1.0f;
	}
	DAT_05cd2978 = 0;
	FUN_00595f80((int)tp, (int)&action_f_f0021_frog);
}
