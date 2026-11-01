#include "decls.h"
#include <new>

// STUB: SADX 0x0040ad40
void __fastcall FUN_0040ad40(void **param_1, int param_2)
{
}

// FUNCTION: SADX 0x0040ad80
char __stdcall FUN_0040ad80(char param_1)
{
	return 0;
}

// FUNCTION: SADX 0x0040ad90
void __stdcall FUN_0040ad90(int param_1, int param_2)
{
}

// STUB: SADX 0x0040ada0
void __stdcall FUN_0040ada0(float *param_1)
{
}

// STUB: SADX 0x0040adc0
void __stdcall FUN_0040adc0(float *param_1, float *param_2)
{
}

// FUNCTION: SADX 0x0040ade0
char __stdcall FUN_0040ade0(int param_1, int param_2)
{
	return 0;
}

// FUNCTION: SADX 0x0040adf0
char FUN_0040adf0()
{
	return 0;
}

// FUNCTION: SADX 0x0040ae00
bool FUN_0040ae00()
{
	return true;
}

// STUB: SADX 0x0040ae10
void __stdcall FUN_0040ae10(int *param_1)
{
}

// STUB: SADX 0x0040af10
void * __fastcall FUN_0040af10(unsigned int param_1)
{
	return (void *)0;
}

// STUB: SADX 0x0040af70
char __fastcall FUN_0040af70(char *param_1, char param_2)
{
	return (char)0;
}

// FUNCTION: SADX 0x0040af90
unsigned char __fastcall FUN_0040af90(int param_1)
{
	return *(unsigned char *)(param_1 + 0xc);
}

#pragma optimize("", off)
// STUB: SADX 0x0040afa0
int FUN_0040afa0(char *param_1, char *param_2)
{
	return (int)0;
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0040b010
int FUN_0040b010(const void *param_1, const void *param_2)
{
	return FUN_0040afa0((char *)param_1, (char *)param_2);
}

// STUB: SADX 0x0040b020
void * __fastcall FUN_0040b020(void *param_1, int param_2)
{
	return (void *)0;
}

// STUB: SADX 0x0040b050
void __stdcall FUN_0040b050(int *param_1)
{
}

// FUNCTION: SADX 0x0040b180
void __fastcall FUN_0040b180(int param_1, int param_2, int param_3)
{
	int iVar1;
	int iVar2;
	int iVar3;
	int iVar4;

	iVar1 = *(int *)(param_1 + 8);
	iVar2 = *(int *)iVar1;
	*(int *)(param_1 + 8) = iVar2;
	iVar3 = *(int *)iVar1;
	if (*(char *)(iVar3 + 0x15) == 0)
	{
		*(int *)(iVar3 + 4) = param_1;
	}
	*(int *)(iVar1 + 4) = *(int *)(param_1 + 4);
	iVar4 = *(int *)(param_3 + 4);
	iVar2 = *(int *)(iVar4 + 4);
	if (param_1 == iVar2)
	{
		*(int *)(iVar4 + 4) = iVar1;
		*(int *)iVar1 = param_1;
		*(int *)(param_1 + 4) = iVar1;
		return;
	}
	iVar2 = *(int *)(param_1 + 4);
	iVar4 = *(int *)iVar2;
	if (param_1 == iVar4)
	{
		*(int *)iVar2 = iVar1;
		*(int *)iVar1 = param_1;
		*(int *)(param_1 + 4) = iVar1;
		return;
	}
	*(int *)(iVar2 + 8) = iVar1;
	*(int *)iVar1 = param_1;
	*(int *)(param_1 + 4) = iVar1;
}

// STUB: SADX 0x0040b1e0
void __fastcall FUN_0040b1e0(int *param_1)
{
}

// STUB: SADX 0x0040b1f0
void __fastcall FUN_0040b1f0(void *param_1, int param_2)
{
}

// STUB: SADX 0x0040b3a0
void FUN_0040b3a0(void *param_1)
{
}
