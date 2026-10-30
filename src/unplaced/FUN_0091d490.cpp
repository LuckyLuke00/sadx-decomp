#include "decls.h"
#include "../advertise.h"
extern int DAT_00a5dd7c;

// STUB: SADX 0x0091d490
char FUN_0091d490(char *param_1)
{
	return (char)0;
}

// STUB: SADX 0x0091d4a0
int FUN_0091d4a0(int param_1)
{
	return (int)0;
}

// STUB: SADX 0x0091d4b0
int FUN_0091d4b0(int param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x0091d4c0
int __fastcall FUN_0091d4c0(int param_1)
{
	return *(int *)(param_1 + 0x50) * *(int *)(param_1 + 0x4c);
}

// STUB: SADX 0x0091d4d0
void FUN_0091d4d0(void *param_1)
{
}

// FUNCTION: SADX 0x0091d510
int __fastcall FUN_0091d510(int param_1)
{
	return *(int *)(param_1 + 0xc) != 0;
}

// STUB: SADX 0x0091d520
void __fastcall FUN_0091d520(int param_1)
{
}

// STUB: SADX 0x0091d5a0
int FUN_0091d5a0(int param_1)
{
	return (int)0;
}

// STUB: SADX 0x0091d5b0
int FUN_0091d5b0(int param_1)
{
	return (int)0;
}

// STUB: SADX 0x0091d5c0
int FUN_0091d5c0(int param_1)
{
	return (int)0;
}

// STUB: SADX 0x0091d5d0
int FUN_0091d5d0(int param_1)
{
	return (int)0;
}

// STUB: SADX 0x0091d5e0
int FUN_0091d5e0(int param_1)
{
	return (int)0;
}

// STUB: SADX 0x0091d5f0
int FUN_0091d5f0(int param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x0091d600
int __fastcall FUN_0091d600(int param_1)
{
	int var1 = 0;
	if (*(int **)(param_1 + 0x84) != 0)
	{
		var1 = (*(int (__thiscall **)(int))(*(int *)*(int **)(param_1 + 0x84) + 4))((int)*(int **)(param_1 + 0x84));
	}
	if (*(int **)(param_1 + 0x88) != 0)
	{
		var1 += (*(int (__thiscall **)(int))(*(int *)*(int **)(param_1 + 0x88) + 4))((int)*(int **)(param_1 + 0x88));
	}
	if (*(int **)(param_1 + 0x8c) != 0)
	{
		return var1 + (*(int (__thiscall **)(int))(*(int *)*(int **)(param_1 + 0x8c) + 4))((int)*(int **)(param_1 + 0x8c));
	}
	return var1;
}

// STUB: SADX 0x0091d660
int __fastcall FUN_0091d660(int param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x0091d7e0
void __fastcall FUN_0091d7e0(int *param_1)
{
	*param_1 = (int)&DAT_00a5dd7c;
	((Magic::RenderCore::Resource*)param_1)->Magic::RenderCore::Resource::~Resource();
}
