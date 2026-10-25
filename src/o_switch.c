#include "decls.h"
void FUN_0058b860(int param_1, int param_2);
extern unsigned char DAT_05cd290c[48];
void FUN_0058b160(struct task *);

// FUNCTION: SADX 0x0058b140
void FUN_0058b140(struct task *param_1)
{
	FUN_0058b160(param_1);
}

// FUNCTION: SADX 0x0058b160
void FUN_0058b160(struct task *param_1)
{
	struct obj *local_8;
	local_8 = (struct obj *)param_1->twp->value.l;
	WithdrawCollisionEntry(param_1, local_8);
	ReleaseMobileLandObject(local_8);
}

// STUB: SADX 0x0058b400
void FUN_0058b400(int param_1)
{
}

// STUB: SADX 0x0058b470
void FUN_0058b470(int param_1)
{
}

// FUNCTION: SADX 0x0058b530
void FUN_0058b530(int param_1, int param_2)
{
	if (param_2 != 0)
	{
		*(char *)(param_1 + 1) = 1;
		*(char *)(param_1 + 9) = 0xff;
	}
	else
	{
		*(char *)(param_1 + 1) = 0;
	}
}

// FUNCTION: SADX 0x0058b560
void FUN_0058b560(char *param_1)
{
	if (*(char *)(param_1 + 1) == 0)
	{
		if (*(unsigned char *)(param_1 + 9) >= 0x32)
			*(unsigned char *)(param_1 + 9) = *(unsigned char *)(param_1 + 9) - 0x1e;
		else
			*(unsigned char *)(param_1 + 9) = 0x14;
	}
}

// FUNCTION: SADX 0x0058b5a0
void FUN_0058b5a0(int param_1, int param_2)
{
	if (param_2 != 0)
	{
		if (GetSwitchOnOff(*(short *)((char *)*(int *)((char *)param_1 + 0x20) + 0xe)) == 0)
			dsPlay_oneshot(0xd, 0, 0, 0);
		FUN_0058b860(*(short *)((char *)*(int *)((char *)param_1 + 0x20) + 0xe), 1);
	}
	else
	{
		if (GetSwitchOnOff(*(short *)((char *)*(int *)((char *)param_1 + 0x20) + 0xe)) != 0)
			dsPlay_oneshot(0xd, 0, 0, 0);
		FUN_0058b860(*(short *)((char *)*(int *)((char *)param_1 + 0x20) + 0xe), 0);
	}
}

// FUNCTION: SADX 0x0058b630
void FUN_0058b630(struct task *param_1)
{
	GetSwitchOnOff(*(short *)((char *)param_1->twp + 0xe));
}

// FUNCTION: SADX 0x0058b650
int FUN_0058b650(int param_1)
{
	if (*(unsigned char *)(*(int *)(param_1 + 0x20) + 3) != 0)
		return 1;
	else
		return 0;
}

// STUB: SADX 0x0058b670
void ExecRidingTime(struct task *tp)
{
}

// FUNCTION: SADX 0x0058b8b0
int GetSwitchOnOff(unsigned int ID)
{
	if ((DAT_05cd290c[ID] & 1) != 0)
		return 1;
	else
		return 0;
}

// FUNCTION: SADX 0x0058b8d0
int FUN_0058b8d0(int param_1)
{
	if ((DAT_05cd290c[param_1] & 2) != 0)
		return 1;
	else
		return 0;
}

// FUNCTION: SADX 0x0058b8f0
void ClearAllSwitches()
{
	int local_8;
	for (local_8 = 0; local_8 < 0x30; local_8 = local_8 + 1)
	{
		DAT_05cd290c[local_8] = 0;
	}
}
