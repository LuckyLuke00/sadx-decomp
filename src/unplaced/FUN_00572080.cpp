#include "decls.h"

// FUNCTION: SADX 0x00572080
void FUN_00572080(float *param_1, float *param_2)
{
	*param_1 = *param_2;
	*(float *)((char *)param_1 + 4) = *(float *)((char *)param_2 + 4);
	*(float *)((char *)param_1 + 8) = *(float *)((char *)param_2 + 8);
}

// FUNCTION: SADX 0x005720b0
void FUN_005720b0(int *param_1, int *param_2)
{
	*param_1 = *param_2;
	*(int *)((char *)param_1 + 4) = *(int *)((char *)param_2 + 4);
	*(int *)((char *)param_1 + 8) = *(int *)((char *)param_2 + 8);
}

// FUNCTION: SADX 0x005720e0
void FUN_005720e0(struct obj *param_1, float param_2)
{
	*(float *)param_1 = param_2;
	*(float *)((char *)param_1 + 4) = param_2;
	*(float *)((char *)param_1 + 8) = param_2;
}

// FUNCTION: SADX 0x00572100
void FUN_00572100(struct NJS_TEXLIST *param_1)
{
	if (param_1 == 0)
	{
		SetObjectTexture();
	}
	else
	{
		___njSetTexture(param_1);
	}
}

// STUB: SADX 0x00572120
void FUN_00572120(char *param_1, char *param_2, int param_3)
{
}
