#include "decls.h"

// FUNCTION: SADX 0x00406700
void __fastcall FUN_00406700(int *param_1, int param_2, int param_3)
{
	int iVar1;
	int *piVar2;

	iVar1 = param_1[2];
	param_1[2] = *(int *)iVar1;
	if (*(char *)(*(int *)iVar1 + 0x2d) == '\0')
	{
		*(int *)(*(int *)iVar1 + 4) = (int)param_1;
	}
	*(int *)(iVar1 + 4) = param_1[1];
	if (param_1 == *(int **)(*(int *)(param_3 + 4) + 4))
	{
		*(int *)(*(int *)(param_3 + 4) + 4) = iVar1;
		*(int **)iVar1 = (int *)((int)param_1);
		param_1[1] = iVar1;
		return;
	}
	piVar2 = (int *)param_1[1];
	if (param_1 == (int *)*piVar2)
	{
		*piVar2 = iVar1;
		*(int **)iVar1 = (int *)((int)param_1);
		param_1[1] = iVar1;
		return;
	}
	piVar2[2] = iVar1;
	*(int **)iVar1 = (int *)((int)param_1);
	param_1[1] = iVar1;
}

// STUB: SADX 0x00406760
void __fastcall FUN_00406760(int *param_1, int param_2)
{
}
