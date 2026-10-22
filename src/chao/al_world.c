#include "decls.h"
extern float DAT_05ade380[16];
extern float DAT_05aea9f0[16];
extern int DAT_05aeaa34;
void njInvertMatrix(float *param_1);
extern unsigned short DAT_05aeaa30;
extern int DAT_05ade3c0[0x100];

// FUNCTION: SADX 0x0043da50
long ALW_CountEntry(unsigned short category)
{
	return DAT_05ade3c0[category];
}

// FUNCTION: SADX 0x0043da60
long ALW_HeldOn(struct al_entry_work *pEntry)
{
	if (pEntry != NULL)
	{
		pEntry->flag |= 2;
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x0043da80
long ALW_HeldOff(struct al_entry_work *pEntry)
{
	if (pEntry != 0)
	{
		pEntry->flag &= 0xfffd;
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x0043daa0
long ALW_IsHeld(struct task *tp)
{
	if (tp->fwp != 0)
	{
		if (*(unsigned char *)((char *)tp->fwp + 6) & 2)
		{
			return 1;
		}
	}
	return 0;
}

// FUNCTION: SADX 0x0043dac0
long ALW_SetHeldOffset(struct task *tp, float offset)
{
	if (tp->fwp != 0)
	{
		*(float *)((char *)tp->fwp + 0x2c) = offset;
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x0043dae0
long ALW_SetHeldRadius(struct task *tp, float radius)
{
	if (tp->fwp != 0)
	{
		*(float *)((char *)tp->fwp + 0x28) = radius;
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x0043db00
long ALW_LockOn(struct task *pMyTask, struct task *pTargetTask)
{
	struct forcewk *var1;
	struct forcewk *var2;
	var1 = pMyTask->fwp;
	var2 = pTargetTask->fwp;
	if ((var1 != 0) && (var2 != 0))
	{
		*(int **)((char *)var1 + 0x44) = (int *)var2;
		return 1;
	}
	return 0;
}

// STUB: SADX 0x0043db30
struct task *ALW_GetLockOnTask(struct task *pMyTask)
{
	return (struct task *)0;
}

// STUB: SADX 0x0043db50
float ALW_CalcDistFromLockOn(struct task *pMyTask)
{
	return (float)0;
}

// STUB: SADX 0x0043db70
long ALW_AttentionOn(struct task *tp1, struct task *tp2)
{
	return (long)0;
}

// FUNCTION: SADX 0x0043dbc0
long ALW_AttentionOff(struct task *tp)
{
	struct forcewk *var1 = tp->fwp;
	if (var1)
	{
		*(short *)((char *)var1 + 6) = 0;
		*(int *)((char *)var1 + 0x40) = 0;
		*(int *)((char *)var1 + 0xc) = -1;
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x0043dbf0
struct al_entry_work *ALW_IsAttention(struct task *tp)
{
	struct al_entry_work *var1 = (struct al_entry_work *)tp->fwp;
	if (var1)
		return var1->pCommu;
	return 0;
}

// STUB: SADX 0x0043dc10
long ALW_IsSheAttentionOtherOne(struct task *pMyTask, struct task *pHerTask)
{
	return (long)0;
}

// FUNCTION: SADX 0x0043dc40
long ALW_CommunicationOn(struct task *tp1, struct task *tp2)
{
	struct forcewk *var1;
	struct forcewk *var2;

	var1 = tp1->fwp;
	var2 = tp2->fwp;
	if (var1 == NULL || var2 == NULL)
	{
		return 0;
	}
	*(void **)((char *)var1 + 0x40) = var2;
	*(void **)((char *)var2 + 0x40) = var1;
	*(unsigned int *)((char *)var1 + 0xc) = (unsigned int)DAT_05aeaa30;
	*(unsigned int *)((char *)var2 + 0xc) = (unsigned int)DAT_05aeaa30;
	DAT_05aeaa30++;
	if (DAT_05aeaa30 >= 0x100)
	{
		DAT_05aeaa30 = 0;
	}
	return 1;
}

// STUB: SADX 0x0043dca0
long ALW_CommunicationOff(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x0043dcf0
struct al_entry_work *ALW_IsCommunication(struct task *tp)
{
	return (struct al_entry_work *)0;
}

// STUB: SADX 0x0043dd10
struct al_entry_work *ALW_IsCommunicationEx(struct task *tp, unsigned short category)
{
	return (struct al_entry_work *)0;
}

// FUNCTION: SADX 0x0043dd40
short ALW_RecieveCommand(struct task *tp)
{
	struct forcewk *var1 = tp->fwp;
	short var2 = 0;
	if (var1)
	{
		var2 = *(short *)((char *)var1 + 0x34);
		*(short *)((char *)var1 + 0x34) = 0;
	}
	return var2;
}

// STUB: SADX 0x0043dd60
long ALW_SendCommand(struct task *tp, short command)
{
	return (long)0;
}

// STUB: SADX 0x0043de30
long ALW_CancelEntry(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x0043de70
long ALW_GetCategory(struct task *tp)
{
	if (tp->fwp != 0)
	{
		return *(unsigned short *)tp->fwp;
	}
	return -1;
}

// STUB: SADX 0x0043de90
void ALW_Control(struct task *tp)
{
}

// FUNCTION: SADX 0x0043def0
void ALW_Displayer(struct task *tp)
{
	njGetMatrix(DAT_05ade380);
	njGetMatrix(DAT_05aea9f0);
	njInvertMatrix(DAT_05aea9f0);
	DAT_05aeaa34 = 0;
}

// FUNCTION: SADX 0x0043df20
void ALW_Destructor(struct task *tp)
{
	DAT_05ade3c0[0xb] = 0;
	ALW_ClearEntry();
}

// STUB: SADX 0x0043df30
long ALW_Create()
{
	return (long)0;
}

// STUB: SADX 0x0043df90
long ALW_TurnToLockOn(struct task *pMyTask, long RotSpd)
{
	return (long)0;
}

// FUNCTION: SADX 0x0043dfb0
long ALW_Entry(unsigned short category, struct task *tp, unsigned short kind)
{
	return ALW_Entry2(category, tp, kind, NULL);
}
