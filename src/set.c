#include "decls.h"
void SetStatusEntry();
void ProcessStatusTable1P();
void ProcessStatusTable2P();
extern int DAT_05cc8664;
extern char DAT_05cc8669;
extern long boolCheckRangeIn;
extern int DAT_05ccc67c;
void InitStatusTable();
void SwitchStatusTable(struct taskwk *pTaskWork);
void DestroyTask(struct task *tp);
extern short DAT_05cc866c;
extern short DAT_05cc867a[256];
void FUN_00550f60(int param_1);
void FUN_00550170(char *param_1);
void FUN_00550280(void);
extern char DAT_05cc8668;
extern int DAT_05cd2948;
extern int DAT_05ccc678;

// FUNCTION: SADX 0x005500d0
void SetObject(struct task *pTask)
{
	struct taskwk *local_8g;

	local_8g = pTask->twp;
	switch (local_8g->mode)
	{
		case 0:
			DAT_05cc8664 = 0;
			DAT_05cc8669 = 0;
			DAT_05cc8668 = 0;
			boolCheckRangeIn = 1;
			DAT_05ccc678 = 0;
			InitStatusTable();
			local_8g->mode = 1;
			DAT_05ccc67c = 0;
			break;
		case 1:
			FUN_00550280();
			FUN_00550170((char *)local_8g);
			break;
		case 2:
			SwitchStatusTable(local_8g);
			break;
	}
}

// FUNCTION: SADX 0x00550170
void FUN_00550170(char *param_1)
{
	if (DAT_05ccc678 != 0)
	{
		*param_1 = 2;
		param_1[1] = 0;
		DAT_05ccc678 = 0;
	}
}

#pragma optimize("", off)
// STUB: SADX 0x005501a0
void InitStatusTable()
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00550280
void FUN_00550280(void)
{
	if (DAT_05baf368[1] == 0 || CheckEditMode() != 0 || *(unsigned char *)((char *)DAT_05baf368[1] + 9) == 2)
	{
		ProcessStatusTable1P();
	}
	else
	{
		ProcessStatusTable2P();
	}
	DAT_05ccc67c = 1;
}

// STUB: SADX 0x005506a0
long CheckRangeP2XYZRP(float *pf, float rx0, float ry0, float rz0, float R, float *pf2)
{
	return (long)0;
}

// STUB: SADX 0x00550c10
int FUN_00550c10(float *fPos, float fX, float fY, float fZ, float fRangeSq)
{
	return (int)0;
}

#pragma optimize("", off)
// STUB: SADX 0x00550cc0
void SwitchStatusTable(struct taskwk *pTaskWork)
{
}
#pragma optimize("", on)

// STUB: SADX 0x00550d90
void FUN_00550d90(void)
{
}

// STUB: SADX 0x00550e00
void SetStatusEntry()
{
}

// FUNCTION: SADX 0x00550f60
void FUN_00550f60(int param_1)
{
	int local_8;
	for (local_8 = 0; local_8 < DAT_05cc866c; local_8++)
	{
		if ((*(short *)((char *)DAT_05cc867a + local_8 * 16) & 0x4000) == 0)
		{
			*(short *)((char *)DAT_05cc867a + local_8 * 16) &= 0xffff7fe9;
			if ((*(short *)((char *)DAT_05cc867a + local_8 * 16) & 1) != 0)
			{
				(*(struct task **)((char *)DAT_05cc867a + 2 + local_8 * 16))->exec = DestroyTask;
			}
		}
	}
}

// STUB: SADX 0x00550ff0
void ReleaseStatusEntry()
{
}

// STUB: SADX 0x00551150
void ReviveSetObject()
{
}

// FUNCTION: SADX 0x00551200
void AddSetStage(short ssGap)
{
	if (ChkGameMode() == 0)
		return;
	boolCheckRangeIn = 0;
	DAT_05ccc678 = 1;
	DAT_05cc8668 += ssGap;
}

// FUNCTION: SADX 0x00551240
long CheckRange(struct task *pTask)
{
	if (pTask->ocp != NULL)
	{
		return CheckRangeWithR(pTask, pTask->ocp->unionStatus.fRangeOut);
	}
	else
	{
		return CheckRangeWithR(pTask, 168100.0f);
	}
}

// STUB: SADX 0x00551290
long CheckRangeWithR(struct task *pTask, float fRange)
{
	return (long)0;
}

// FUNCTION: SADX 0x00551340
long CheckRangeOut(struct task *pTask)
{
	if (pTask->ocp != NULL)
	{
		return CheckRangeOutWithR(pTask, pTask->ocp->unionStatus.fRangeOut);
	}
	else
	{
		return CheckRangeOutWithR(pTask, 168100.0f);
	}
}

// FUNCTION: SADX 0x00551390
long CheckRangeOut_L(struct task *pTask)
{
	float local_8 = 168100.0;

	if ((pTask->ocp != 0) && (pTask->ocp->unionStatus.fRangeOut > local_8))
	{
		local_8 = pTask->ocp->unionStatus.fRangeOut;
	}
	return CheckRangeOutWithR(pTask, local_8);
}

// STUB: SADX 0x005513e0
long CheckRangeOutWithR(struct task *tp, float fRange)
{
	return (long)0;
}

// FUNCTION: SADX 0x00551530
void FUN_00551530(int param_1)
{
	*(short *)(*(int *)(param_1 + 0x1c) + 2) = *(short *)(*(int *)(param_1 + 0x1c) + 2) | 4;
}

// FUNCTION: SADX 0x00551550
void SetNoRevive(struct task *pTask)
{
	pTask->ocp->ssCondition |= 0x10;
}

// FUNCTION: SADX 0x00551590
void SetContinue(struct task *pTask)
{
	pTask->ocp->ssCondition |= 0x4000;
}

// FUNCTION: SADX 0x005515b0
void Dead(struct task *pTask)
{
	pTask->ocp->ssCondition &= ~0x8000;
	pTask->ocp->ssCondition &= ~0x1;
}

// FUNCTION: SADX 0x005515f0
void DeadOut(struct task *pTask)
{
	pTask->ocp->ssCondition &= ~0x8000;
	pTask->ocp->ssCondition &= ~0x1;
	pTask->exec = DestroyTask;
}

// FUNCTION: SADX 0x00551630
void SetUserFlag(struct task *tp, signed char flag)
{
	if (tp->ocp != NULL)
	{
		tp->ocp->scUserFlag = flag;
	}
}

// FUNCTION: SADX 0x00551650
signed char GetUserFlag(struct task *tp)
{
	if (tp->ocp != 0)
	{
		return tp->ocp->scUserFlag;
	}
	return 0;
}

// FUNCTION: SADX 0x00551670
void SetObjEditTable(void *pTable)
{
	*(int *)((char *)&DAT_05cd2948 + (int)DAT_05cc8668 * 4) = (int)pTable;
	DAT_05ccc678 = 1;
}
