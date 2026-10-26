#include "decls.h"
void __fastcall FUN_0090cc20(int param_1);

// FUNCTION: SADX 0x0090b3b0
void __fastcall FUN_0090b3b0(void *param_1)
{
	*(int *)((char *)param_1 + 0x18) = 0;
	*(int *)((char *)param_1 + 0x2c) = 0;
	*(int *)((char *)param_1 + 0x20) = 0;
	*(int *)((char *)param_1 + 0x24) = 0;
	*(int *)((char *)param_1 + 0x28) = 0;
	*(int *)((char *)param_1 + 0x8060) = 0;
	*(char *)((char *)param_1 + 0x8058) = 0;
}

// FUNCTION: SADX 0x0090b3d0
int __fastcall FUN_0090b3d0(int param_1)
{
	Z80_Reset(*(unsigned char **)(param_1 + 0x48));
	if (*(int *)(param_1 + 0x28) != 0)
	{
		FUN_0090cc20(*(int *)(param_1 + 0x40));
	}
	return 1;
}

// STUB: SADX 0x0090b540
void __fastcall FUN_0090b540(void *param_1, int param_2)
{
}

// FUNCTION: SADX 0x0090b560
void __fastcall FUN_0090b560(void *param_1, void *param_2, int param_3)
{
	*(int *)((char *)*(int *)((char *)param_1 + 0x40) + 0x196a4) = param_3;
}

// FUNCTION: SADX 0x0090b5b0
int __fastcall FUN_0090b5b0(void *param_1)
{
	return *(int *)((char *)param_1 + 0x44);
}
