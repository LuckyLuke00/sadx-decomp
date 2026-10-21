#include "decls.h"
void FUN_00550f60(int param_1);
void FUN_00550170(char *param_1);
void FUN_00550280(void);
extern char DAT_05cc8668;
extern int DAT_05cd2948;
extern int DAT_05ccc678;

// STUB: SADX 0x005500d0
void SetObject(struct task *pTask)
{
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

// STUB: SADX 0x005501a0
void InitStatusTable()
{
}

// STUB: SADX 0x00550280
void FUN_00550280(void)
{
}

// STUB: SADX 0x00550c10
int FUN_00550c10(float *fPos, float fX, float fY, float fZ, float fRangeSq)
{
	return (int)0;
}

// STUB: SADX 0x00550cc0
void SwitchStatusTable(struct taskwk *pTaskWork)
{
}

// STUB: SADX 0x00550d90
void FUN_00550d90(void)
{
}

// STUB: SADX 0x00550f60
void FUN_00550f60(int param_1)
{
}

// STUB: SADX 0x00551150
void ReviveSetObject()
{
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

// STUB: SADX 0x00551390
long CheckRangeOut_L(struct task *pTask)
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

// STUB: SADX 0x005515b0
void Dead(struct task *pTask)
{
}

// STUB: SADX 0x005515f0
void DeadOut(struct task *pTask)
{
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
