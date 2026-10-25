#include "decls.h"
struct IniFile;

// STUB: SADX 0x00408df0
void FUN_00408df0(struct IniFile *param_1, int param_2)
{
}

// STUB: SADX 0x00408e30
void __fastcall FUN_00408e30(void *param_1, int param_2, int param_3)
{
}

// STUB: SADX 0x00409350
void FUN_00409350(void *param_1)
{
}

// FUNCTION: SADX 0x00409750
void __fastcall FUN_00409750(int *param_1, int param_2, int param_3)
{
	int iVar1;
	int *piVar2;

	iVar1 = *param_1;
	*param_1 = *(int *)(iVar1 + 8);
	if (*(char *)(*(int *)(iVar1 + 8) + 0x45) == '\0')
	{
		*(int **)(*(int *)(iVar1 + 8) + 4) = param_1;
	}
	*(int *)(iVar1 + 4) = param_1[1];
	if (param_1 == *(int **)(*(int *)(param_3 + 4) + 4))
	{
		*(int *)(*(int *)(param_3 + 4) + 4) = iVar1;
		*(int **)(iVar1 + 8) = param_1;
		param_1[1] = iVar1;
		return;
	}
	piVar2 = (int *)param_1[1];
	if (param_1 == (int *)piVar2[2])
	{
		piVar2[2] = iVar1;
		*(int **)(iVar1 + 8) = param_1;
		param_1[1] = iVar1;
		return;
	}
	*piVar2 = iVar1;
	*(int **)(iVar1 + 8) = param_1;
	param_1[1] = iVar1;
}

// STUB: SADX 0x00409cb0
void __fastcall FUN_00409cb0(void *param_1)
{
}

// STUB: SADX 0x00409ed0
int __fastcall FUN_00409ed0(int *param_1, int param_2)
{
	return (int)0;
}

// STUB: SADX 0x00409f20
int __fastcall FUN_00409f20(int param_1)
{
	return (int)0;
}

// STUB: SADX 0x0040a280
void __fastcall FUN_0040a280(void *param_1, int param_2, int param_3)
{
}
