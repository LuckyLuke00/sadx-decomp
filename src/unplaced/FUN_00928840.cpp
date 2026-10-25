#include "decls.h"
#include <windows.h>
void FUN_009288d0(void *param_1);

// STUB: SADX 0x00928840
void FUN_00928840(int *param_1)
{
}

// FUNCTION: SADX 0x009288c0
void __fastcall FUN_009288c0(void *param_1)
{
	LeaveCriticalSection((LPCRITICAL_SECTION)*(void **)param_1);
}

// STUB: SADX 0x009288d0
void FUN_009288d0(void *param_1)
{
}

// FUNCTION: SADX 0x009288e0
void __fastcall FUN_009288e0(int *param_1)
{
	int var1 = *param_1;
	if (var1 != 0)
	{
		DeleteCriticalSection((LPCRITICAL_SECTION)var1);
		operator delete((void *)var1);
	}
}

// STUB: SADX 0x00928940
void FUN_00928940(void *param_1)
{
}

// FUNCTION: SADX 0x009289b0
int __fastcall FUN_009289b0(int param_1)
{
	return (*(int *)(param_1 + 0x50) - *(int *)(param_1 + 0x4c)) >> 2;
}

// FUNCTION: SADX 0x009289c0
void __fastcall FUN_009289c0(struct S *param_1, int param_2, double param_3)
{
	*(byte *)((char *)param_1 + 0x44) = 1;
	*(double *)((char *)param_1 + 0x60) = param_3;
}

// STUB: SADX 0x009289e0
int __fastcall FUN_009289e0(struct FUN_009289e0_struct *param_1)
{
	return (int)0;
}

// STUB: SADX 0x00928a20
float __fastcall FUN_00928a20(int param_1)
{
	return (float)0;
}

// FUNCTION: SADX 0x00928a60
double __fastcall FUN_00928a60(void *param_1)
{
	return *(double *)((char *)param_1 + 0x80);
}

// STUB: SADX 0x00928af0
void __fastcall FUN_00928af0(struct S *param_1)
{
}

// STUB: SADX 0x00928bc0
double __fastcall FUN_00928bc0(struct S *param_1)
{
	return (double)0;
}

// STUB: SADX 0x00928c70
void FUN_00928c70(int param_1)
{
}

// STUB: SADX 0x00928cd0
void FUN_00928cd0(int param_1)
{
}

// STUB: SADX 0x00929210
void __fastcall FUN_00929210(struct S *param_1)
{
}

// STUB: SADX 0x009292e0
void __fastcall FUN_009292e0(char *param_1, char *param_2, int param_3, char *param_4)
{
}
