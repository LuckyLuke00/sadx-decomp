#include "decls.h"
extern unsigned long DAT_05cd25f4;
extern long DAT_05cd25a4[24];
extern int DAT_05cd2588;
extern long DAT_05cd25f8;

// FUNCTION: SADX 0x00573f10
long FUN_00573f10()
{
	return DAT_05cd25f8;
}

// STUB: SADX 0x00573f20
void ghSetPvrTexMaterial(unsigned long color)
{
}

// FUNCTION: SADX 0x00574040
long FUN_00574040(long *param_1)
{
	long local_8;
	if (param_1 != 0)
	{
		param_1[0] = DAT_05cd25a4[0];
		local_8 = DAT_05cd25a4[0];
		param_1[1] = DAT_05cd25a4[6];
		param_1[2] = DAT_05cd25a4[12];
		param_1[3] = DAT_05cd25a4[18];
	}
	else
	{
		local_8 = DAT_05cd25a4[0];
	}
	return local_8;
}

// FUNCTION: SADX 0x00574f80
void ghDefaultBlendingMode()
{
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
}

// STUB: SADX 0x00575050
void FUN_00575050(int param_1, float *param_2)
{
}

// STUB: SADX 0x00575150
void ghGetPvrTextureSize(struct NJS_TEXLIST *texlist, int index, int *w, int *h)
{
}

// STUB: SADX 0x005751b0
unsigned long ghGetPvrTexGlobalIndex(struct NJS_TEXLIST *texlist, int index)
{
	return (unsigned long)0;
}

// FUNCTION: SADX 0x005751e0
void ghSetFadeColor(unsigned long color)
{
	DAT_05cd25f4 = color | 0xff000000;
}

// FUNCTION: SADX 0x00575200
void ghSetFadeFlag(int flag)
{
	DAT_05cd2588 = flag;
}
