#include "decls.h"
extern void FUN_004f8070(void *param_1);
void FUN_004f76a0(void *param_1);
extern int DAT_05cb5620;
extern int DAT_05cb5624;
extern int DAT_05cb562c;
void FUN_004f6f20(void *param_1, int param_2);
void FUN_004f6f70(void *param_1, int param_2);

// FUNCTION: SADX 0x004f6ef0
void FUN_004f6ef0(void)
{
	FUN_004f6f20((void *)0x5bb5620, 0x4000);
	FUN_004f6f70((void *)0x5bb00d8, 0x100);
}

// STUB: SADX 0x004f6f20
void FUN_004f6f20(void *param_1, int param_2)
{
}

// STUB: SADX 0x004f6f70
void FUN_004f6f70(void *param_1, int param_2)
{
}

// FUNCTION: SADX 0x004f6fd0
void CL_ColPolListUpModeSetAll()
{
	DAT_05cb562c = 1;
}

// FUNCTION: SADX 0x004f75d0
int * FUN_004f75d0(void)
{
	int *local_8g;
	int *local_cg;

	local_8g = (int *)DAT_05cb5624;
	local_cg = (int *)*local_8g;
	if (local_cg == 0)
	{
		return 0;
	}
	DAT_05cb5624 = (int)local_cg;
	local_cg = (int *)DAT_05cb5620;
	*local_8g = (int)local_cg;
	if (*local_8g != 0)
	{
		local_cg[1] = (int)local_8g;
	}
	DAT_05cb5620 = (int)local_8g;
	local_8g[1] = ~(int)&DAT_05cb5620;
	return local_8g;
}

// STUB: SADX 0x004f7640
void FUN_004f7640(void *param_1)
{
}

// FUNCTION: SADX 0x004f76a0
void FUN_004f76a0(void *param_1)
{
	int iVar1;
	int iVar2;
	int iVar3;

	iVar1 = *(int *)param_1;
	iVar2 = *(int *)((char *)param_1 + 4);
	if (iVar1 != 0)
	{
		*(int *)((char *)iVar1 + 4) = iVar2;
	}
	if ((iVar2 & 1) != 0)
	{
		iVar3 = ~iVar2;
		*(int *)iVar3 = iVar1;
	}
	else
	{
		*(int *)iVar2 = iVar1;
	}
	*(int *)param_1 = DAT_05cb5624;
	DAT_05cb5624 = (int)param_1;
}

// STUB: SADX 0x004f7700
void FUN_004f7700(void)
{
}

// STUB: SADX 0x004f8010
void FUN_004f8010(float param_1)
{
}

// STUB: SADX 0x004f8070
void FUN_004f8070(void *param_1)
{
}

// FUNCTION: SADX 0x004f89d0
float FUN_004f89d0(float *param_1, float *param_2)
{
	float local_8g;
	float local_cj;
	float local_10;

	local_8g = *param_1 - *param_2;
	param_2 = param_2 + 1;
	param_1 = param_1 + 1;
	local_cj = *param_1 - *param_2;
	param_2 = param_2 + 1;
	param_1 = param_1 + 1;
	local_10 = *param_1 - *param_2;
	return local_8g * local_8g + local_cj * local_cj + local_10 * local_10;
}

// STUB: SADX 0x004fcd10
void RemoveObjInfo(struct obj *pObject)
{
}
