#include "decls.h"
void FUN_0044a450(int param_1);

// FUNCTION: SADX 0x0044a350
long ALBHV_OsanpoThrown(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (*(short *)((char *)var1 + 0x1c6) == 0)
	{
		AL_SetMotionLink(tp, 0);
		*(short *)((char *)var1 + 0x1c6) += 1;
		var1 = tp->twp;
		*(int *)((char *)var1 + 0xb0) &= 0xfffffff7;
	}
	return 0;
}

// FUNCTION: SADX 0x0044a430
long AL_GetBehavior(struct task *param_1)
{
	return *(long *)((char *)param_1->twp + 0x450 + *(long *)((char *)param_1->twp + 0x44c) * 4);
}

// FUNCTION: SADX 0x0044a450
void FUN_0044a450(int param_1)
{
	*(int *)(param_1 + 2) = 0;
	*(int *)(param_1 + 0xc) = 0;
	*(int *)(param_1 + 0x10) = 0;
	*(int *)(param_1 + 0x14) = 0xe10;
	*(int *)(param_1 + 0x18) = 0;
}

// FUNCTION: SADX 0x0044a530
void FUN_0044a530(int param_1, int param_2, int param_3)
{
	struct task *var2 = (struct task *)param_1;
	struct taskwk *var1 = var2->twp;
	if (*(int *)((char *)var1 + 0x448) < 0xf)
	{
		*(int *)((char *)var1 + 0x450 + *(int *)((char *)var1 + 0x448) * 4) = param_2;
		*(int *)((char *)var1 + 0x490 + *(int *)((char *)var1 + 0x448) * 4) = param_3;
		*(int *)((char *)var1 + 0x448) += 1;
	}
}

// FUNCTION: SADX 0x0044a570
int FUN_0044a570(int param_1)
{
	int iVar1;
	int iVar2;
	int iVar3;

	iVar1 = *(int *)((char *)param_1 + 0x20);
	iVar2 = iVar1 + 0x1c4;
	FUN_0044a450(iVar2);
	iVar3 = *(int *)((char *)iVar2 + 0x288);
	iVar1 = *(int *)((char *)iVar2 + iVar3 * 4 + 0x28c);
	*(int *)((char *)iVar2 + 0x284) -= 1;
	*(int *)((char *)iVar2 + 0x280) = iVar1;
	iVar3 += 1;
	*(int *)((char *)iVar2 + 0x288) = iVar3;
	return *(int *)((char *)iVar2 + iVar3 * 4 + 0x28c) != 0;
}

// STUB: SADX 0x0044a5c0
void AL_ReturnBehavior(struct task *tp)
{
}

// FUNCTION: SADX 0x0044a620
void AL_BehaviorSetFreeWork(struct task *tp, long info)
{
	*(long *)((char *)tp->twp + 0x430) = info;
}

// FUNCTION: SADX 0x0044a640
long AL_BehaviorGetFreeWork(struct task *tp)
{
	return *(long *)((char *)tp->twp + 0x430);
}

// FUNCTION: SADX 0x0044a650
void AL_BehaviorCheckInterrupt(struct task *tp)
{
	long (*var3)(struct task *);
	int var1;
	int var2;

	var1 = 0;
	var3 = (long (__cdecl *)(struct task *))AL_GetBehavior(tp);
	var2 = 0;
	if (var3 == ALBHV_Mayu || var3 == ALBHV_Dead)
	{
		return;
	}
	if (AL_CheckWater(tp) != 0)
	{
		var1 = 1;
	}
	else
	{
		if (var3 == ALBHV_Sleep || var3 == ALBHV_SitSleep)
		{
			goto lab_0x44a6e2;
		}
		if (AL_CheckWhistle(tp) != 0)
		{
			var1 = 1;
		}
		if (AL_CheckObakeHead(tp) != 0)
		{
			var1 = 1;
		}
		if (AL_CheckFruit(tp) != 0)
		{
			var1 = 1;
		}
		if (AL_CheckMinimal(tp) != 0)
		{
			var1 = 1;
		}
	}
lab_0x44a6e2:
	if (AL_CheckDakko(tp) != 0)
	{
		var2 = 1;
		var1 = 1;
	}
	else
	{
		if (AL_CheckNade(tp) != 0)
		{
			var1 = 1;
		}
	}
	if (AL_CheckDamage(tp) != 0)
	{
		var2 = 0;
	}
	else
	{
		if (var1 == 0)
		{
			return;
		}
	}
	ALW_AttentionOff(tp);
	ALW_CommunicationOff(tp);
	if (var2 == 0)
	{
		AL_CloseParameterFukidasi(tp);
	}
}

// FUNCTION: SADX 0x0044a740
void AL_SetBehavior(struct task *tp, long (*Func)(struct task *))
{
	AL_SetBehaviorWithTimer(tp, Func, -1);
}

// FUNCTION: SADX 0x0044a760
void AL_SetNextBehavior(struct task *tp, long (*Func)(struct task *))
{
	FUN_0044a530((int)tp, (int)Func, -1);
}

// STUB: SADX 0x0044a780
void AL_BehaviorInit(struct task *tp)
{
}

// FUNCTION: SADX 0x0044a960
long ALBHV_OdekakeEject(struct task *tp)
{
	struct taskwk *var1;
	long var2;

	var1 = tp->twp;
	if (*(short *)((char *)var1 + 0x1c6) == 0)
	{
		AL_SetMotionLink(tp, 0);
		*(short *)((char *)var1 + 0x1c6) += 1;
		*(int *)((char *)tp->twp + 0xb0) &= 0xfffffff7;
	}
	var2 = *(int *)((char *)var1 + 0x1d0);
	*(int *)((char *)var1 + 0x1d0) = var2 + 1;
	if (var2 > 0x3c)
	{
		*(int *)((char *)tp->twp + 0xb0) |= 8;
		AL_SetBehavior(tp, ALBHV_Think);
		return 1;
	}
	return 0;
}
