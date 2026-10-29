#include "decls.h"
static void ExecATask(struct task *tp);
extern int DAT_05b3e05c;
extern unsigned char *DAT_05b37314;
extern char *KindMes[5];
void FUN_0058ac40(struct task *param_1);
void FUN_0058acd0(struct task *param_1);
void FUN_0058afb0(struct task *param_1);
void FUN_0058b190(struct task *param_1);
void FUN_0058b210(struct task *param_1);
void FUN_0058b270(struct task *param_1);
void FUN_0058b4e0(struct task *param_1);
void FUN_0058b190(struct task *param_1);
void FUN_0058b210(struct task *param_1);
void FUN_0058b270(struct task *param_1);
void FUN_0058b4e0(struct task *param_1);
void FUN_0058b560(char *param_1);
void ExecRidingTime(struct task *tp);
long EntryColliList(struct taskwk *twp);
long CheckCollisionP(struct NJS_POINT3 *vp, float d);
void FUN_0058b190(struct task *param_1);
void FUN_0058b210(struct task *param_1);
void FUN_0058b270(struct task *param_1);
void FUN_0058b4e0(struct task *param_1);
void FUN_0058b860(int param_1, int param_2);
extern unsigned char DAT_05cd290c[48];
void FUN_0058b160(struct task *);

// FUNCTION: SADX 0x0058aab0
void ObjectSwitch(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	if (DAT_05b3e05c == 0xa)
	{
		if (IsMissionStatus(tp->ocp) != 0)
		{
			if (*(unsigned char *)((char *)*(int *)((char *)tp->ocp + 0x10) + 1) != (*(unsigned char *)(DAT_05b37314 + *(unsigned char *)(*(int *)((char *)tp->ocp + 0x10))) & 1))
			{
				DestroyTask(tp);
				return;
			}
		}
	}
	if (FUN_004c39c0(tp) != 0)
	{
		switch (local_8->mode)
		{
		case 0:
			FUN_0058ac40(tp);
			break;
		case 1:
			FUN_0058b160(tp);
			FUN_0058acd0(tp);
			FUN_0058afb0(tp);
			break;
		}
		DebPrintf(0x110010, "<- ANGLE X");
		DebPrintf(0x110011, "<- ANGLE Y");
		DebPrintf(0x110012, "<- ANGLE Z");
		DebPrintf(0x110013, "<- KIND:%s", KindMes[local_8->timer.w[0]]);
		DebPrintf(0x110014, "<- ID");
		if (local_8->timer.w[0] == 2)
		{
			DebPrintf(0x110015, "<- TIMER");
		}
	}
	else
	{
		switch (local_8->mode)
		{
		case 0:
			FUN_0058ac40(tp);
			break;
		case 1:
			FUN_0058afb0(tp);
			ExecATask(tp);
			break;
		}
	}
}

// FUNCTION: SADX 0x0058aeb0
static void ExecATask(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (FUN_004c39c0(tp) == 0)
	{
		switch (local_8->timer.w[0])
		{
		case 0:
			FUN_0058b190(tp);
			break;
		case 1:
			FUN_0058b210(tp);
			break;
		case 2:
			FUN_0058b270(tp);
			break;
		case 3:
			FUN_0058b4e0(tp);
			break;
		default:
			FUN_0058b190(tp);
			break;
		}
		ExecRidingTime(tp);
		FUN_0058b560((char *)local_8);
	}
	if (CheckCollisionP(&local_8->pos, 70.0f))
	{
		local_8->flag |= 0x100;
	}
	else
	{
		local_8->flag &= ~0x100;
	}
	EntryColliList(local_8);
}

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

// FUNCTION: SADX 0x0058b210
void FUN_0058b210(struct task *param_1)
{
	struct taskwk *local_8;

	local_8 = param_1->twp;
	if (FUN_0058b650((int)param_1) != 0)
	{
		FUN_0058b5a0((int)param_1, 1);
		FUN_0058b530((int)local_8, 1);
	}
	else
	{
		FUN_0058b5a0((int)param_1, 0);
		FUN_0058b530((int)local_8, 0);
	}
}

// STUB: SADX 0x0058b400
void FUN_0058b400(int param_1)
{
}

// FUNCTION: SADX 0x0058b470
void FUN_0058b470(int param_1)
{
	int local_8;

	local_8 = *(unsigned short *)(param_1 + 6) - 0x28;
	if (local_8 > 0)
	{
		if (*(char *)(param_1 + 1) != 0)
			*(short *)(param_1 + 0xa) = (short)((int)(local_8 * 0.05999999865889549) + 1);
		else
			*(short *)(param_1 + 0xa) = (short)((int)(local_8 * 0.03999999910593033) + 1);
	}
	else
		*(short *)(param_1 + 0xa) = 1;
}

#pragma optimize("", off)
// STUB: SADX 0x0058b4e0
void FUN_0058b4e0(struct task *param_1)
{
}
#pragma optimize("", on)

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
