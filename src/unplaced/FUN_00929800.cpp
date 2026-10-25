#include "decls.h"
#include <windows.h>
#include <string>
struct FUN_0092a020_0;
struct FUN_00929fe0_t;

// STUB: SADX 0x00929870
int FUN_00929870(void *param_1)
{
	return (int)0;
}

// STUB: SADX 0x009298a0
int FUN_009298a0(void *param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x00929900
void FUN_00929900(char *param_1)
{
	if (*(int *)(param_1 + 0x10) != 0)
	{
		if (*(unsigned int *)(param_1 + 0x14) >= 0x10)
			param_1 = *(char **)param_1;
		SetCurrentDirectoryA(param_1);
	}
}

// STUB: SADX 0x00929920
void FUN_00929920(char *param_1)
{
}

// STUB: SADX 0x00929940
void __fastcall FUN_00929940(int param_1)
{
}

// STUB: SADX 0x009299d0
std::string * FUN_009299d0(std::string *param_1)
{
	return (std::string *)0;
}

// STUB: SADX 0x00929a50
std::string * FUN_00929a50(std::string *param_1)
{
	return (std::string *)0;
}

// STUB: SADX 0x00929ab0
void __fastcall FUN_00929ab0(void *param_1)
{
}

// FUNCTION: SADX 0x00929f20
void FUN_00929f20(int param_1)
{
	Sleep(param_1);
}

// STUB: SADX 0x00929f30
void FUN_00929f30(void *param_1)
{
}

// STUB: SADX 0x00929f50
void FUN_00929f50(int *param_1)
{
}

// FUNCTION: SADX 0x00929fe0
void __stdcall FUN_00929fe0(FUN_00929fe0_t *param_1)
{
	int var1 = (int)(*(int **)((char *)param_1 + 0xc));
	if (var1 != 0)
	{
		(*(void (__stdcall **)(int))(*(int *)var1 + 8))(var1);
	}
	*(int **)((char *)param_1 + 0xc) = 0;
	int var2 = (int)(*(int **)((char *)param_1 + 0x50));
	if (var2 != 0)
	{
		(*(void (__stdcall **)(int))(*(int *)var2 + 8))(var2);
	}
	*(int **)((char *)param_1 + 0x50) = 0;
}

// FUNCTION: SADX 0x0092a020
void __stdcall FUN_0092a020(struct FUN_0092a020_0 *param_1)
{
	int var1 = *(int *)((char *)param_1 + 0xc);
	if (var1 != 0)
	{
		(*(void (__stdcall **)(int))(*(int *)var1 + 8))(var1);
	}
	int var2 = *(int *)((char *)param_1 + 0x50);
	*(int *)((char *)param_1 + 0xc) = 0;
	if (var2 != 0)
	{
		(*(void (__stdcall **)(int))(*(int *)var2 + 8))(var2);
	}
	*(int *)((char *)param_1 + 0x50) = 0;
}

// FUNCTION: SADX 0x0092a060
void __stdcall FUN_0092a060(int param_1)
{
	int var1 = (int)(*(int **)(param_1 + 0xc));
	if (var1 != 0)
	{
		(*(void (__stdcall **)(int))(*(int *)var1 + 8))(var1);
	}
	*(int **)(param_1 + 0xc) = 0;
}

// FUNCTION: SADX 0x0092a0b0
void __stdcall FUN_0092a0b0(int param_1)
{
	int var1 = (int)(*(int **)(param_1 + 0xc));
	if (var1 != 0)
	{
		(*(void (__stdcall **)(int))(*(int *)var1 + 8))(var1);
	}
	*(int **)(param_1 + 0xc) = 0;
}

// STUB: SADX 0x0092a0e0
int __fastcall FUN_0092a0e0(struct FUN_0092a0e0_0 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
	return (int)0;
}

// STUB: SADX 0x0092a1c0
void __stdcall FUN_0092a1c0(int param_1)
{
}

// FUNCTION: SADX 0x0092a1e0
void __stdcall FUN_0092a1e0(int param_1)
{
	int var1 = (int)(*(int **)(param_1 + 0xc));
	if (var1 != 0)
	{
		(*(void (__stdcall **)(int))(*(int *)var1 + 8))(var1);
	}
	*(int **)(param_1 + 0xc) = 0;
}

// FUNCTION: SADX 0x0092a2c0
void __stdcall FUN_0092a2c0(int param_1)
{
	int var1 = (int)(*(int **)(param_1 + 0x14));
	if (var1 != 0)
	{
		(*(void (__stdcall **)(int))(*(int *)var1 + 8))(var1);
	}
	*(int **)(param_1 + 0x14) = 0;
}

// STUB: SADX 0x0092a3b0
int __stdcall FUN_0092a3b0(int param_1, int param_2, int param_3, int param_4)
{
	return (int)0;
}

// STUB: SADX 0x0092a3d0
int __stdcall FUN_0092a3d0(int param_1, int param_2, int param_3, int param_4, int param_5)
{
	return (int)0;
}

// STUB: SADX 0x0092a420
int __stdcall FUN_0092a420(int param_1, int param_2, int param_3, int param_4, int param_5)
{
	return (int)0;
}

// STUB: SADX 0x0092a710
void __fastcall FUN_0092a710(void *param_1, int param_2)
{
}
