#include "decls.h"
#include <windows.h>
void __stdcall FUN_00929140(int *param_1);
void FUN_009288d0(void *param_1);

// FUNCTION: SADX 0x00928840
void __fastcall FUN_00928840(int *param_1)
{
	if (*(int *)*param_1 != 0)
	{
		CloseHandle(*(HANDLE *)*param_1);
		*(int *)*param_1 = 0;
	}
	if (*param_1 != 0)
	{
		operator delete((void *)*param_1);
	}
}

// STUB: SADX 0x00928870
void __fastcall FUN_00928870(int *param_1, int param_2, int param_3)
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

// STUB: SADX 0x00928900
void __fastcall FUN_00928900(int *param_1)
{
}

// STUB: SADX 0x00928940
void FUN_00928940(void *param_1)
{
}

// STUB: SADX 0x00928950
void __fastcall FUN_00928950(int *param_1, int param_2, double param_3)
{
}

// STUB: SADX 0x00928980
int __fastcall FUN_00928980(int param_1, int param_2)
{
	return (int)0;
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

// FUNCTION: SADX 0x00928a70
char __fastcall FUN_00928a70(void *param_1)
{
	return *(char *)((char *)param_1 + 0x44);
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

// STUB: SADX 0x00928bf0
float __fastcall FUN_00928bf0(void *param_1)
{
	return (float)0;
}

// STUB: SADX 0x00928c70
void FUN_00928c70(int param_1)
{
}

// STUB: SADX 0x00928cd0
void FUN_00928cd0(int param_1)
{
}

// STUB: SADX 0x00928d30
void __fastcall FUN_00928d30(int *param_1)
{
}

// STUB: SADX 0x00929020
int FUN_00929020(int param_1, int param_2)
{
	return (int)0;
}

// STUB: SADX 0x00929140
void __stdcall FUN_00929140(int *param_1)
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

// FUNCTION: SADX 0x009297a0
void __fastcall FUN_009297a0(int *param_1)
{
	int var1 = *param_1;
	if (var1 != 0)
	{
		operator delete((void *)var1);
	}
}
