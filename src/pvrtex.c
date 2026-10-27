#include "decls.h"
extern int DAT_05cd25fc;
extern float DAT_05cd259c;
extern float DAT_05cd25a0;
extern float DAT_05cd258c;
extern int DAT_0629c724;
unsigned long FUN_005750b0(float *param_1);
unsigned long FUN_004951c0(unsigned long param_1, unsigned long param_2);
extern unsigned long DAT_05cd25f4;
extern long DAT_05cd25a4[20];
extern int DAT_05cd2588;
extern long DAT_05cd25f8;

// FUNCTION: SADX 0x00573e60
void ghInitPvrTexture()
{
	int local_8;
	for (local_8 = 0; local_8 < 4; local_8++)
	{
		*(int *)((char *)DAT_05cd25a4 + local_8 * 0x18) = 0xffffffff;
	}
	DAT_05cd259c = 0.0f;
	DAT_05cd25a0 = 0.0f;
	*(float *)((char *)DAT_05cd25a4 + 0x10) = 0.0f;
	*(float *)((char *)DAT_05cd25a4 + 0x14) = 1.0f;
	*(float *)((char *)DAT_05cd25a4 + 0x28) = 1.0f;
	*(float *)((char *)DAT_05cd25a4 + 0x2c) = 0.0f;
	*(float *)((char *)DAT_05cd25a4 + 0x40) = 1.0f;
	*(float *)((char *)DAT_05cd25a4 + 0x44) = 1.0f;
	DAT_05cd25f8 = 0xffffffff;
	DAT_05cd25a4[19] = 0;
	DAT_05cd25fc = 1;
	DAT_05cd25f4 = 0;
	DAT_05cd258c = 1.0f;
	DAT_05cd2588 = 0;
}

// FUNCTION: SADX 0x00573f10
long FUN_00573f10()
{
	return DAT_05cd25f8;
}

// STUB: SADX 0x00573f20
void ghSetPvrTexMaterial(unsigned long color)
{
}

// FUNCTION: SADX 0x00573f90
void ghSetPvrTexVertexColor(unsigned long c0, unsigned long c1, unsigned long c2, unsigned long c3)
{
	c0 = FUN_004951c0(c0, DAT_05cd25f8);
	c1 = FUN_004951c0(c1, DAT_05cd25f8);
	c2 = FUN_004951c0(c2, DAT_05cd25f8);
	c3 = FUN_004951c0(c3, DAT_05cd25f8);
	DAT_05cd25a4[0] = c0;
	DAT_05cd25a4[6] = c1;
	DAT_05cd25a4[12] = c2;
	DAT_05cd25a4[18] = c3;
	if ((c0 & c1 & c2 & c3 & 0xff000000) == 0xff000000)
	{
		DAT_05cd25a4[19] = 0;
	}
	else
	{
		DAT_05cd25a4[19] = 1;
	}
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

// STUB: SADX 0x005740a0
void ghSetPvrTexBaseColor(unsigned long color)
{
}

// STUB: SADX 0x00574e40
void ghSetPvrTexUV(int flipflag)
{
}

// FUNCTION: SADX 0x00574f80
void ghDefaultBlendingMode()
{
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
}

// STUB: SADX 0x00574fa0
unsigned long ghGetColor2Color(long mode, unsigned long sc, unsigned long dc, float rate)
{
	return (unsigned long)0;
}

// STUB: SADX 0x00575050
void FUN_00575050(int param_1, float *param_2)
{
}

// STUB: SADX 0x005750b0
unsigned long FUN_005750b0(float *param_1)
{
	return (unsigned long)0;
}

// FUNCTION: SADX 0x00575150
void ghGetPvrTextureSize(struct NJS_TEXLIST *texlist, int index, int *w, int *h)
{
	int local_8g;
	int local_cg;
	if (texlist == 0)
	{
		texlist = (struct NJS_TEXLIST *)DAT_0629c724;
	}
	local_8g = texlist->textures[index].texaddr;
	local_cg = local_8g + 0x18;
	if (w != 0)
	{
		*w = *(int *)(local_cg + 0xc);
	}
	if (h != 0)
	{
		*h = *(int *)(local_cg + 0x10);
	}
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

// STUB: SADX 0x00575210
void ghFade(float rate)
{
}

// STUB: SADX 0x00575360
void ghAdvertiseCamera(struct task *tp)
{
}

// STUB: SADX 0x00575760
void DrawTitleBack(float x, float y, float z, float w, float h)
{
}
