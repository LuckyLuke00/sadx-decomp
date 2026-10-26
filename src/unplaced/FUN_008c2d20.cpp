#include "decls.h"
#include <new>
int FUN_008c3590(int param_1, int *param_2, int param_3);
void FUN_008c3260(int param_1, int *param_2, int *param_3);
void FUN_008c4130(char *param_1);
void FUN_008c41a0(char *param_1);
void FUN_008c3850(int param_1, int *param_2, int *param_3);
void FUN_008c3450(int param_1, int *param_2, int *param_3);
void FUN_008c3770(int param_1, int *param_2, int *param_3);
int * FUN_008c3650(int param_1, int *param_2, int param_3);
int * FUN_008c36e0(int param_1, int *param_2, int param_3);

// STUB: SADX 0x008c2d20
void FUN_008c2d20(int param_1, int param_2)
{
}

// STUB: SADX 0x008c3260
void FUN_008c3260(int param_1, int *param_2, int *param_3)
{
}

// STUB: SADX 0x008c33a0
void FUN_008c33a0(int param_1, int param_2)
{
}

// STUB: SADX 0x008c3450
void FUN_008c3450(int param_1, int *param_2, int *param_3)
{
}

// FUNCTION: SADX 0x008c3550
int * FUN_008c3550(int param_1, int *param_2, int param_3)
{
	while (param_3 > 0)
	{
		if (*param_2 != 0)
		{
			*param_2 = param_1 + *param_2;
		}
		param_3 -= 2;
		param_2 += 2;
	}
	return param_2;
}

// STUB: SADX 0x008c3590
int FUN_008c3590(int param_1, int *param_2, int param_3)
{
	return (int)0;
}

// STUB: SADX 0x008c3650
int * FUN_008c3650(int param_1, int *param_2, int param_3)
{
	return (int *)0;
}

// STUB: SADX 0x008c36e0
int * FUN_008c36e0(int param_1, int *param_2, int param_3)
{
	return (int *)0;
}

// FUNCTION: SADX 0x008c3770
void FUN_008c3770(int param_1, int *param_2, int *param_3)
{
	int *local_8;
	local_8 = param_2;
	while (local_8 < param_3)
	{
		if (*local_8 != 0)
		{
			*local_8 = param_1 + 8 + *local_8;
		}
		local_8 = local_8 + 3;
	}
}

// STUB: SADX 0x008c37b0
void FUN_008c37b0(int *param_1, int *param_2)
{
}

// FUNCTION: SADX 0x008c3850
void FUN_008c3850(int param_1, int *param_2, int *param_3)
{
	int *local_8;
	local_8 = param_2;
	while (local_8 < param_3)
	{
		if (local_8[1] != 0)
		{
			local_8[1] = param_1 + local_8[1];
		}
		local_8 = local_8 + 2;
	}
}

// STUB: SADX 0x008c4080
int * __fastcall FUN_008c4080(int *param_1)
{
	return (int *)0;
}

// STUB: SADX 0x008c4130
void FUN_008c4130(char *param_1)
{
}

// STUB: SADX 0x008c41a0
void FUN_008c41a0(char *param_1)
{
}

// STUB: SADX 0x008c4210
void *FUN_008c4210(int param_1)
{
	return (void *)0;
}

// STUB: SADX 0x008c4330
void __fastcall FUN_008c4330(void *param_1)
{
}

// FUNCTION: SADX 0x008c43d0
void __fastcall FUN_008c43d0(void *param_1)
{
	delete *(void **)((char *)param_1 + 4);
}
