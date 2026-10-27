#include "decls.h"
void FUN_0090b5e0(int param_1, int param_2, int param_3, int param_4, int param_5);

// STUB: SADX 0x0090a010
void __fastcall FUN_0090a010(void *param_1, void *param_2)
{
}

// FUNCTION: SADX 0x0090a090
void __fastcall FUN_0090a090(int param_1, int param_2, int param_3)
{
	int var1;

	var1 = *(int *)(param_1 + param_3 * 4 + 0x1c);
	if (var1 != 0)
	{
		FUN_00909e30(var1);
	}
}

// FUNCTION: SADX 0x0090a0b0
void __fastcall FUN_0090a0b0(int param_1, int param_2, int param_3)
{
	int var1;

	var1 = *(int *)(param_1 + param_3 * 4 + 0x1c);
	if (var1 != 0)
	{
		FUN_00909e50(var1);
	}
}

// FUNCTION: SADX 0x0090a0d0
void __fastcall FUN_0090a0d0(int param_1)
{
	int var1;
	int var2;

	var1 = *(int *)(param_1 + 0x1c);
	if (var1 == 0)
	{
		return;
	}
	var2 = *(int *)(param_1 + 0x20);
	if (var2 == 0)
	{
		return;
	}
	var1 = *(int *)(var1 + 0x28);
	var2 = *(int *)(var2 + 0x28);
	FUN_0090b5e0(*(int *)(var1 + 0x38), *(int *)(var2 + 0x38), *(int *)(var1 + 4), *(int *)(var2 + 4), *(int *)(var1 + 0x20));
}
