#include "decls.h"

// FUNCTION: SADX 0x0043a2c0
void SetMotionLink(struct MOTION_CTRL *pMtnCtrl, long MtnNum)
{
	long var1;
	long var2;

	var1 = MtnNum * 8;
	var2 = *(int *)((char *)pMtnCtrl + 0x48);
	var2 += (var1 - MtnNum) * 4;
	*(int *)((char *)pMtnCtrl + 8) = MtnNum;
	if (*(int *)((char *)var2 + 0xc) < 0)
	{
		*(float *)((char *)pMtnCtrl + 0x10) = 0.06666667f;
	}
	else
	{
		*(float *)((char *)pMtnCtrl + 0x10) = 1.0f / (float)(int)*(int *)((char *)var2 + 0xc);
	}
	*(float *)((char *)pMtnCtrl + 0x14) = 0.0f;
	*(short *)((char *)pMtnCtrl + 0x30) = *(short *)((char *)var2 + 4);
	*(float *)((char *)pMtnCtrl + 0x34) = *(float *)((char *)var2 + 0x10);
	*(float *)((char *)pMtnCtrl + 0x38) = *(float *)((char *)var2 + 0x10);
	*(float *)((char *)pMtnCtrl + 0x3c) = *(float *)((char *)var2 + 0x14);
	*(float *)((char *)pMtnCtrl + 0x40) = *(float *)((char *)var2 + 0x18);
	*(int *)((char *)pMtnCtrl + 0x44) = *(int *)((char *)var2);
	*(short *)((char *)pMtnCtrl) = 2;
}

// STUB: SADX 0x0043a3b0
void SetMotionLinkStep(struct MOTION_CTRL *pMtnCtrl, long MtnNum, unsigned short step)
{
}

// STUB: SADX 0x0043a4d0
void FUN_0043a4d0(void *param_1, int param_2)
{
}

// STUB: SADX 0x0043a530
void FUN_0043a530(int param_1, int param_2)
{
}

// FUNCTION: SADX 0x0043a600
void FUN_0043a600(float *param_1, float param_2)
{
	*(float *)((char *)param_1 + 0xc) = param_2;
}

// FUNCTION: SADX 0x0043a610
long IsMotionEnd(struct MOTION_CTRL *pMtnCtrl)
{
	return *(unsigned char *)((char *)pMtnCtrl + 0x0) & 1;
}

// FUNCTION: SADX 0x0043a620
long IsMotionStop(struct MOTION_CTRL *pMtnCtrl)
{
	return (*(unsigned char *)pMtnCtrl >> 3) & 1;
}

// FUNCTION: SADX 0x0043a750
float FUN_0043a750(void *param_1)
{
	return *(float *)((char *)param_1 + 0x1c);
}

// FUNCTION: SADX 0x0043a760
int FUN_0043a760(int param_1)
{
	return *(int *)(param_1 + 4);
}

// STUB: SADX 0x0043a770
unsigned short FUN_0043a770(void *param_1)
{
	return (unsigned short)0;
}

// STUB: SADX 0x0043a780
void MotionInit(struct MOTION_CTRL *pMtnCtrl, struct MOTION_TABLE *pTable)
{
}
