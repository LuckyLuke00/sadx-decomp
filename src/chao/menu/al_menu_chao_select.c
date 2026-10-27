#include "decls.h"
extern int DAT_060c6130;
extern int DAT_060c6134;

// FUNCTION: SADX 0x00712650
void ChaoSelectMenuManagerDestructor(struct task *tp)
{
	if (DAT_060c6130)
	{
		Free((void *)DAT_060c6130);
		DAT_060c6130 = 0;
	}
}

// FUNCTION: SADX 0x00712670
void FUN_00712670(int param_1)
{
	DAT_060c6134 = param_1;
}

// FUNCTION: SADX 0x00712680
enum EMenuStatus AL_GetChaoSelectMenuStatus()
{
	return (enum EMenuStatus)DAT_060c6134;
}

// FUNCTION: SADX 0x00712690
long AL_ChaoMenuIsEnd()
{
	if (DAT_060c6130 != 0)
	{
		return *(long *)((char *)DAT_060c6130 + 0x10);
	}
	return 0;
}

// FUNCTION: SADX 0x007126a0
void FUN_007126a0()
{
	if (DAT_060c6130 != 0)
	{
		*(int *)((char *)DAT_060c6130 + 0x10) = 1;
	}
}

// FUNCTION: SADX 0x007126c0
void AL_ChaoMenuSetBusy()
{
	if (DAT_060c6130 != 0)
	{
		*(int *)((char *)DAT_060c6130 + 0x14) = 1;
	}
}

// FUNCTION: SADX 0x007126e0
void FUN_007126e0()
{
	if (DAT_060c6130 != 0)
	{
		*(int *)((char *)DAT_060c6130 + 0x14) = 0;
	}
}

// FUNCTION: SADX 0x00712700
int FUN_00712700()
{
	if (DAT_060c6130 != 0)
	{
		return *(int *)((char *)DAT_060c6130 + 0x14);
	}
	return 0;
}

// FUNCTION: SADX 0x00712710
long AL_ChaoSelectMenuIsFocusedModoru()
{
	if ((*(int *)((char *)DAT_060c6130 + 0x2c) >= 2) && (*(int *)((char *)DAT_060c6130 + 0x28) < 4))
	{
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x00712730
long AL_ChaoSelectMenuIsFocusedKettei()
{
	if ((*(int *)((char *)DAT_060c6130 + 0x2c) >= 2) && (*(int *)((char *)DAT_060c6130 + 0x28) >= 4))
	{
		return 1;
	}
	return 0;
}
