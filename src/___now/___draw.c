#include "decls.h"
#include <math.h>
extern float DAT_05b3df0c[3];
extern float DAT_05b3df10[3];
extern float DAT_05b3df14[3];
extern int DAT_05b39eb8[9];
extern float DAT_05b39dc0[9];
extern int DAT_05b39db8;
extern void *DAT_05b39e78[];
extern void *DAT_05b39e08[];
extern void *DAT_05b3dee4[];
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);
void FUN_0067d830(int param_1, float param_2, float param_3, float param_4);
extern int DAT_05b39e90;
extern int DAT_05b39e94;
extern int DAT_05b39e98;
extern int DAT_05b39ea4;
extern void (*DAT_05b3df00)(struct obj *obj);
extern void (*DAT_05b39e68)(struct obj *obj);
extern void (*DAT_05b39dbc)(struct obj *obj);
extern float DAT_05b3df44;
void FUN_004a3890();
extern LATE_FAR_Z_T DAT_05b39e18;
void ___OutputDebugString(char *, ...);
int isTextureNG(struct NJS_TEXLIST *tl, int numChk);
void FUN_004a27c0();
void FUN_004a2960();
extern int DAT_05b39df4;
void njRotateXYZ(long param_1, long *param_2, long *param_3, long *param_4);
void njRotateZXY(long param_1, long *param_2, long *param_3, long *param_4);
void FUN_00422560(int param_1);
void late_DrawObjectClip(struct obj *obj, int flgs, float clipScl);
int isTextureNG(NJS_TEXLIST *tl, int numChk);
extern int DAT_05b3dee0;
extern int DAT_05b3ded4;
extern int DAT_05b3ded8;
extern int DAT_05b3df48;
extern "C" void *memset(void *dest, int c, unsigned int count);
extern unsigned char DAT_05b3df53;
extern float DAT_05b3df38;
void late_DrawModelClip(struct NJS_MODEL *, int, float);
int isTextureNG(struct NJS_TEXLIST *, int);
extern int DAT_05b3df40;
extern int DAT_05b39e2c;
extern int DAT_05cd4078;
void FUN_00598720(int param_1);
static int isTextureNG(struct NJS_TEXLIST *tl, int numChk);
extern NJS_ARGB DAT_05b3df28;
extern float DAT_05b3df3c;

void njSetPerspective(long param_1);
void njSetConstantMaterial(NJS_ARGB *param_1);

extern long DAT_06298c64;
extern long DAT_05b39e6c;
extern NJS_ARGB DAT_05b39de4;
extern NJS_TEXLIST *DAT_05b3ded0;
extern int DAT_05b39eb4;
extern unsigned char DAT_05b39e10;
extern unsigned char DAT_05b3e065;
extern int DAT_05b9d838;

// FUNCTION: SADX 0x004a0220
void ___njSetPerspective(long a)
{
	if (DAT_06298c64 != a)
	{
		njSetPerspective(a);
	}
	DAT_05b39e6c = a;
	DAT_06298c64 = a;
}

// FUNCTION: SADX 0x004a0250
long ds_GetPerspective()
{
	return DAT_05b39e6c;
}

// FUNCTION: SADX 0x004a0260
void ___njSetBackColor(unsigned long c0, unsigned long c1, unsigned long c2)
{
	c0 |= 0xff000000;
	c1 |= 0xff000000;
	c2 |= 0xff000000;
	njSetBackColor(c0, c1, c2);
}

// FUNCTION: SADX 0x004a02a0
void ___njReleaseTextureAll()
{
	njReleaseTextureAll();
	late_execCancel();
	MSG_CloseRequestCls();
}

// FUNCTION: SADX 0x004a02c0
void ___njSetConstantMaterial(NJS_ARGB *argb)
{
	DAT_05b39de4 = *argb;
	if (DAT_05b39de4.a > 1.0)
	{
		DAT_05b39de4.a = 1.0;
	}
	else if (DAT_05b39de4.a < -1.0)
	{
		DAT_05b39de4.a = -1.0;
	}
	if (DAT_05b39de4.r > 1.0)
	{
		DAT_05b39de4.r = 1.0;
	}
	else if (DAT_05b39de4.r < -1.0)
	{
		DAT_05b39de4.r = -1.0;
	}
	if (DAT_05b39de4.g > 1.0)
	{
		DAT_05b39de4.g = 1.0;
	}
	else if (DAT_05b39de4.g < -1.0)
	{
		DAT_05b39de4.g = -1.0;
	}
	if (DAT_05b39de4.b > 1.0)
	{
		DAT_05b39de4.b = 1.0;
	}
	else if (DAT_05b39de4.b < -1.0)
	{
		DAT_05b39de4.b = -1.0;
	}
	njSetConstantMaterial(&DAT_05b39de4);
}

// FUNCTION: SADX 0x004a03f0
void ___njSetTexture(NJS_TEXLIST *texlist)
{
	long local_8;

	DAT_05b3ded0 = texlist;
	DAT_05b39eb4 = 0;
	local_8 = njSetTexture(texlist);
}

// FUNCTION: SADX 0x004a0420
void ___njSetTextureNum(int num)
{
	DAT_05b39eb4 = num;
	if (DAT_05b3ded0 != 0)
	{
		njSetTextureNum(num);
	}
}

// FUNCTION: SADX 0x004a0450
int ___dsSetTexture()
{
	njSetTexture(DAT_05b3ded0);
	return DAT_05b39eb4;
}

// FUNCTION: SADX 0x004a0470
void ___njColorBlendingMode(int tgt, int mode)
{
	if (tgt == 0)
	{
		DAT_05b39e10 = (DAT_05b39e10 & ~0xf) | (mode & 0xf);
	}
	else if (tgt == 1)
	{
		DAT_05b39e10 = (DAT_05b39e10 & 0xf) | ((mode & 0xf) << 4);
	}
	njColorBlendingMode(tgt, mode);
}

// FUNCTION: SADX 0x004a04d0
void ___njDrawTexture(struct NJS_TEXTURE_VTX *v, int num, int ind, int tf)
{
	int local_8;

	local_8 = DAT_05b3e065;
	if (DAT_05b9d838)
	{
		return;
	}
	if (local_8)
	{
		___njFogDisable();
	}
	njDrawTexture(v, num, ind, tf);
	if (local_8)
	{
		___njFogEnable();
	}
}

// FUNCTION: SADX 0x004a0620
int FUN_004a0620(int param_1)
{
	unsigned int local_ci;
	unsigned int local_8g;
	int local_10;

	local_ci = *(unsigned int *)(*(int *)(param_1 + 0x10) + 0x10);
	local_10 = 0;
	if (local_ci & 0x100000)
	{
		local_10 = 1;
	}
	local_8g = local_ci & 0xfc000000;
	if (local_8g == 0x84000000 || local_8g == 0x24000000 || local_8g == 0x30000000)
	{
		local_10 = ((local_ci & 0x2000000) != 0) + 1;
	}
	return local_10;
}

// FUNCTION: SADX 0x004a0690
void late_ReleaseTexture(NJS_TEXLIST *tl)
{
	int local_8g;
	int local_cj;
	int local_10;

	if (isTextureNG(tl, 0))
	{
		return;
	}
	njReleaseTexture(tl);
}

// FUNCTION: SADX 0x004a06c0
static int isTextureNG(struct NJS_TEXLIST *tl, int numChk)
{
	struct NJS_TEXLIST *local_8g;
	unsigned int local_cj;
	int *local_10;

	local_8g = tl;
	if (local_8g == NULL)
	{
		return 1;
	}
	local_10 = *(int **)tl;
	if (*(int *)((char *)tl + 4) == 0)
	{
		return 1;
	}
	for (local_cj = 0; local_cj < (unsigned int)*(int *)((char *)tl + 4); local_cj++)
	{
		if (*(int *)((char *)local_10 + local_cj * 12 + 8) == 0)
		{
			return 1;
		}
	}
	if (**(int **)tl == -1)
	{
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x004a0740
int dsCheckView(float x, float y, float z, float radius)
{
	struct NJS_POINT3 ft;
	ft.x = x;
	ft.y = y;
	ft.z = z;
	return dsCheckViewV(&ft, radius);
}

// FUNCTION: SADX 0x004a0920
void FUN_004a0920(struct obj *param_1)
{
	___dsDrawObject(param_1);
}

// FUNCTION: SADX 0x004a0940
void FUN_004a0940(struct NJS_MODEL *param_1)
{
	___dsDrawModel(param_1);
}

// FUNCTION: SADX 0x004a0960
void FUN_004a0960(struct obj *param_1, struct NJS_MOTION *param_2, float param_3)
{
	FUN_004a7cb0(param_1, param_2, param_3);
}

// FUNCTION: SADX 0x004a0980
void FUN_004a0980(const struct obj *param_1, const struct NJS_MOTION *param_2, const struct NJS_MOTION *param_3, float param_4)
{
	___dsDrawShapeMotion(param_1, param_2, param_3, param_4);
}

// FUNCTION: SADX 0x004a0a10
void njEasyDrawObject(struct obj *obj)
{
	njSetConstantMaterial(&DAT_05b3df28);
	FUN_004a0920(obj);
	njSetConstantMaterial(&DAT_05b39de4);
}

// FUNCTION: SADX 0x004a0a40
void njEasyDrawShapeMotion(const struct obj *object, const struct NJS_MOTION *motion, const struct NJS_MOTION *shape, float frame)
{
	njSetConstantMaterial(&DAT_05b3df28);
	FUN_004a0980(object, motion, shape, frame);
	njSetConstantMaterial(&DAT_05b39de4);
}

// FUNCTION: SADX 0x004a0a80
int FUN_004a0a80(struct NJS_MODEL *param_1)
{
	FUN_004a0940(param_1);
	return 0;
}

// FUNCTION: SADX 0x004a0aa0
void FUN_004a0aa0(struct obj *param_1, struct NJS_MOTION *param_2, float param_3)
{
	FUN_004a0960(param_1, param_2, param_3);
}

// FUNCTION: SADX 0x004a0ac0
void ___SAnjSimpleDrawObject(struct obj *obj)
{
	FUN_004a0920(obj);
}

// FUNCTION: SADX 0x004a1f70
void dsDrawModel_S(struct NJS_MODEL *m)
{
	if (*(float *)((char *)m + 0x24) >= 900.0f)
	{
		ds_DrawModelClip(m, 1.0f);
	}
	else
	{
		late_DrawModelClipEx(m, 0, 1.0f);
	}
}

// FUNCTION: SADX 0x004a1fb0
void dsOpenDraw_S()
{
	do
	{
		if (DAT_05cd4078 != 0)
		{
			FUN_00598720(0);
		}
	}
	while (0);
}

// FUNCTION: SADX 0x004a1fd0
void ___njDrawSprite3D(struct NJS_SPRITE *sp, int n, unsigned long atr)
{
	int local_8;

	local_8 = (atr & 0x20) ? 4 : 1;
	late_DrawSprite3D(sp, n, atr, local_8);
}

// FUNCTION: SADX 0x004a2010
void ___njDrawLine3D(struct NJS_POINT3COL *p, int n, unsigned long atr)
{
	int local_10s;
	int local_14h;
	int local_8g;
	int local_18;
	int local_cj;
	int local_1c;

	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if ((atr & 0x80000000) != 0)
	{
		if (isTextureNG(DAT_05b3ded0, 0) != 0)
		{
			return;
		}
		if (isTextureNG(DAT_05b3ded0, 1) != 0)
		{
			return;
		}
	}
	njDrawLine3D(p, n, atr);
}

// FUNCTION: SADX 0x004a2080
void ___njDrawTriangle3D(struct NJS_POINT3COL *p, int n, unsigned long atr)
{
	int local_8g;
	int local_10m;
	int local_18;
	int local_14;
	int local_1c;
	int local_cj;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if ((atr & 0x80000000) != 0)
	{
		if (isTextureNG(DAT_05b3ded0, 0) != 0)
		{
			return;
		}
		if (isTextureNG(DAT_05b3ded0, 1) != 0)
		{
			return;
		}
	}
	njDrawTriangle3D(p, n, atr);
}

// FUNCTION: SADX 0x004a20f0
void ___njDrawPolygon2D(struct NJS_POINT2COL *p, int n, float pri, unsigned long atr)
{
	int local_14h;
	int local_8g;
	int local_1c;
	int local_18;
	int local_10m;
	int local_cj;

	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if ((atr & 0x80000000) != 0)
	{
		if (isTextureNG(DAT_05b3ded0, 0) != 0)
		{
			return;
		}
		if (isTextureNG(DAT_05b3ded0, 1) != 0)
		{
			return;
		}
	}
	do
	{
		FUN_00422560(7);
		njSetZUpdateMode(0);
	} while (0);
	___SAnjDrawPolygon2D(p, n, pri, atr);
	njSetZUpdateMode(1);
	npSetZCompare();
}

// FUNCTION: SADX 0x004a2180
void ___njDrawPolygon3D(struct NJS_POINT3COL *p, int n, unsigned long atr)
{
	char local_1c[0x14];
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if ((atr & 0x80000000) != 0)
	{
		if (isTextureNG(DAT_05b3ded0, 0) != 0)
		{
			return;
		}
		if (isTextureNG(DAT_05b3ded0, 1) != 0)
		{
			return;
		}
	}
	njDrawPolygon3D(p, n, atr);
}

// FUNCTION: SADX 0x004a2660
void saSetSpriteZOffset(float zoffset)
{
	DAT_05b3df3c = zoffset;
}

// FUNCTION: SADX 0x004a2670
void saDrawSprite3D(struct NJS_SPRITE *r4_sp, int r5_n, unsigned long r6_attr)
{
	if (DAT_05b9d838)
		return;
	DAT_05b3df38 = DAT_05b3df3c;
	late_DrawSprite3D(r4_sp, r5_n, r6_attr, 0);
	DAT_05b3df38 = 0.0f;
}

// FUNCTION: SADX 0x004a26b0
void late_init()
{
	if (DAT_05b3dee0 != 0)
	{
		syFree((void *)DAT_05b3dee0);
	}
	DAT_05b3ded8 = 0x88000;
	DAT_05b3dee0 = (int)syMalloc(0x88000);
	DAT_05b39df4 = DAT_05b3dee0 + 0x88000;
	FUN_004a2960();
	FUN_004a27c0();
}

// FUNCTION: SADX 0x004a2710
void *late_alloca(unsigned int sz)
{
	int local_8;

	local_8 = 0;
	sz = (sz + 0x1f) & 0xffffffe0;
	if (DAT_05b3ded4 + sz <= DAT_05b39df4)
	{
		local_8 = DAT_05b3ded4;
		DAT_05b3ded4 = DAT_05b3ded4 + sz;
	}
	else
	{
		if (DAT_05b3df48 == 0)
		{
			___OutputDebugString("late_alloca() : not enough memory!\n");
			DAT_05b3df48 = 1;
		}
	}
	return (void *)local_8;
}

// FUNCTION: SADX 0x004a2780
void FUN_004a2780(int param_1)
{
	param_1 = param_1 + 0x1f & 0xffffffe0;
	if ((unsigned)(DAT_05b3ded4 - param_1) >= (unsigned)DAT_05b3dee0)
	{
		DAT_05b3ded4 = DAT_05b3ded4 - param_1;
	}
	else
	{
		DAT_05b3ded4 = DAT_05b3dee0;
	}
}

// FUNCTION: SADX 0x004a2800
void FUN_004a2800(void)
{
	DAT_05b3ded4 = (DAT_05b3dee0 + 0x1f) & 0xffffffe0;
	memset((void *)DAT_05b3dee0, 0, DAT_05b3ded8);
	DAT_05b3df48 = 0;
}

// FUNCTION: SADX 0x004a2840
void late_DrawShadowObject(struct obj *obj, float clipScl)
{
	float local_8;
	local_8 = *(float *)&DAT_05b3df40;
	*(float *)&DAT_05b3df40 = -27952.0f;
	late_DrawObjectClip(obj, 6, clipScl);
	*(float *)&DAT_05b3df40 = local_8;
}

// FUNCTION: SADX 0x004a2880
void late_DrawShadowModel(struct NJS_MODEL *mdl, float clipScl)
{
	float local_8;
	local_8 = *(float *)&DAT_05b3df40;
	*(float *)&DAT_05b3df40 = -27952.0;
	late_DrawModelClip(mdl, 6, clipScl);
	*(float *)&DAT_05b3df40 = local_8;
}

// FUNCTION: SADX 0x004a28c0
void late_reset_far_z()
{
	*(int *)&DAT_05b39e18 = *(int *)&late_far_z_dflt;
	*(int *)((char *)&DAT_05b39e18 + 4) = *(int *)((char *)&late_far_z_dflt + 4);
	*(int *)((char *)&DAT_05b39e18 + 8) = *(int *)((char *)&late_far_z_dflt + 8);
}

// FUNCTION: SADX 0x004a28f0
void late_set_far_z(float nor, float ex, float mesh)
{
	if (nor >= 0.0f)
	{
		nor = -3000.0f;
	}
	if (ex >= 0.0f)
	{
		ex = -1200.0f;
	}
	if (mesh >= 0.0f)
	{
		mesh = -1200.0f;
	}
	*(float *)&DAT_05b39e18 = nor;
	*(float *)((char *)&DAT_05b39e18 + 4) = ex;
	*(float *)((char *)&DAT_05b39e18 + 8) = mesh;
}

// FUNCTION: SADX 0x004a29c0
void FUN_004a29c0(void)
{
	npSetZCompare();
	njSetZUpdateMode(1);
	gjGXSetBlendMode(1);
	lig_resetGjPaletteNo(0);
	FUN_004a3890();
	late_reset_far_z();
	njSetConstantMaterial(&DAT_05b39de4);
	DAT_05b39e2c = 0;
}

// FUNCTION: SADX 0x004a2a10
void late_execCancel()
{
	DAT_05b39e2c = 2;
}

// FUNCTION: SADX 0x004a2a20
void late_execCancelNoErase()
{
	DAT_05b39e2c = 1;
}

// FUNCTION: SADX 0x004a3890
void FUN_004a3890()
{
	char *local_8;
	for (local_8 = (char *)late_zentry; local_8 != (char *)late_zentry + 0x4000; local_8 += 8)
	{
		*(int *)local_8 = (int)local_8;
		*(int *)(local_8 + 4) = (int)local_8;
	}
}

// FUNCTION: SADX 0x004a4000
void nlateBegin(int flgs)
{
	NJS_ARGB *local_8;

	if ((flgs & 1) == 0)
	{
		do
		{
			FUN_00422560(3);
			njSetZUpdateMode(0);
		} while (0);
	}
	if ((flgs & 0x10) != 0)
	{
		do
		{
			FUN_00422560(7);
			njSetZUpdateMode(0);
		} while (0);
	}
	if ((flgs & 2) != 0)
	{
		local_8 = &DAT_05b3df28;
	}
	else
	{
		local_8 = &DAT_05b39de4;
	}
	njSetConstantMaterial(local_8);
}

// FUNCTION: SADX 0x004a47d0
void late_DrawObjectClip(struct obj *obj, int flgs, float clipScl)
{
	int local_8g;
	int local_cj;
	int local_10;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if (isTextureNG(DAT_05b3ded0, 0) != 0)
	{
		return;
	}
	lateDrawObject(obj, flgs, clipScl);
}

// FUNCTION: SADX 0x004a4820
void late_DrawObject(struct obj *obj, int flgs)
{
	float local_10;
	int local_ci;
	int local_8g;
	if (DAT_05b9d838)
	{
		return;
	}
	if (isTextureNG(DAT_05b3ded0, 0))
	{
		return;
	}
	lateDrawObject(obj, flgs, DAT_05b3df44);
}

// FUNCTION: SADX 0x004a51f0
void late_DrawObjectClipEx(struct obj *obj, int flgs, float clipScl)
{
	int local_8g;
	int local_cj;
	int local_10;
	if (DAT_05b9d838 != 0)
		return;
	if (isTextureNG(DAT_05b3ded0, 0) != 0)
		return;
	DrawObjectClipEx(obj, flgs, clipScl);
}

// FUNCTION: SADX 0x004a5240
void late_DrawObjectEx(struct obj *obj, int flgs)
{
	int local_10;
	int local_ci;
	int local_8g;
	if (DAT_05b9d838)
	{
		return;
	}
	if (isTextureNG(DAT_05b3ded0, 0))
	{
		return;
	}
	DrawObjectClipEx(obj, flgs, DAT_05b3df44);
}

// FUNCTION: SADX 0x004a5c80
void FUN_004a5c80(struct obj *param_1, int param_2)
{
	int local_10;
	int local_ci;
	int local_8g;
	if (DAT_05b9d838)
	{
		return;
	}
	if (isTextureNG(DAT_05b3ded0, 0))
	{
		return;
	}
	DrawObjectMS(param_1, param_2, DAT_05b3df44);
}

// FUNCTION: SADX 0x004a5cd0
void late_DrawObjectClipMS(struct obj *obj, int flgs, float clipScl)
{
	int local_8g;
	int local_cj;
	int local_10;
	if (DAT_05b9d838 != 0)
		return;
	if (isTextureNG(DAT_05b3ded0, 0) != 0)
		return;
	DrawObjectMS(obj, flgs, clipScl);
}

// FUNCTION: SADX 0x004a6900
float FUN_004a6900(void *param_1, float *param_2)
{
	float local_8 = *(float *)((char *)param_1 + 8) * *param_2 + *(float *)((char *)param_1 + 0x18) * param_2[1] + *(float *)((char *)param_1 + 0x28) * param_2[2] + *(float *)((char *)param_1 + 0x38);
	return -local_8;
}

// FUNCTION: SADX 0x004a6940
void late_DrawObjectMesh(struct obj *obj, int flgs)
{
	int local_8g;
	int local_cj;
	int local_10;
	if (DAT_05b9d838)
	{
		return;
	}
	if (isTextureNG(DAT_05b3ded0, 0))
	{
		return;
	}
	DrawObjectClipMesh(obj, flgs, DAT_05b3df44);
}

// FUNCTION: SADX 0x004a6990
void late_DrawObjectClipMesh(struct obj *obj, int flgs, float clipScl)
{
	int local_8g;
	int local_cj;
	int local_10;
	if (DAT_05b9d838 != 0)
		return;
	if (isTextureNG(DAT_05b3ded0, 0) != 0)
		return;
	DrawObjectClipMesh(obj, flgs, clipScl);
}

// FUNCTION: SADX 0x004a7800
void CHAOS_SetMeshMode(int sw)
{
	DAT_05b3df53 = sw;
}

// FUNCTION: SADX 0x004a7ac0
void njMotionData0(struct obj *obj)
{
	(*DAT_05b3df00)(obj);
	(*DAT_05b39e68)(obj);
	(*DAT_05b39dbc)(obj);
}

// FUNCTION: SADX 0x004a7af0
void njMotionData1(struct obj *obj)
{
	int local_8;

	local_8 = DAT_05b39e90;
	DAT_05b39e94 = local_8;
	DAT_05b39e98 = local_8 + 4;
	DAT_05b39ea4 = 0;
	(*DAT_05b3df00)(obj);
	(*DAT_05b39e68)(obj);
	(*DAT_05b39dbc)(obj);
	local_8 += 8;
	DAT_05b39e90 = local_8;
}

// FUNCTION: SADX 0x004a7b60
void njMotionData2(struct obj *obj)
{
	int local_8;

	local_8 = DAT_05b39e90;
	DAT_05b39e94 = local_8;
	DAT_05b39e98 = local_8 + 8;
	DAT_05b39ea4 = 0;
	DAT_05b3df00(obj);
	DAT_05b39e68(obj);
	DAT_05b39dbc(obj);
	local_8 += 0x10;
	DAT_05b39e90 = local_8;
}

// FUNCTION: SADX 0x004a7bd0
void njMotionData3(struct obj *obj)
{
	int iVar1;
	iVar1 = DAT_05b39e90;
	DAT_05b39e94 = iVar1;
	DAT_05b39e98 = iVar1 + 0xc;
	DAT_05b39ea4 = 0;
	DAT_05b3df00(obj);
	DAT_05b39e68(obj);
	DAT_05b39dbc(obj);
	iVar1 += 0x18;
	DAT_05b39e90 = iVar1;
	return;
}

// FUNCTION: SADX 0x004a7c40
void njMotionData4(struct obj *obj)
{
	int iVar1;

	iVar1 = DAT_05b39e90;
	DAT_05b39e94 = iVar1;
	DAT_05b39e98 = iVar1 + 0x10;
	DAT_05b39ea4 = 0;
	DAT_05b3df00(obj);
	DAT_05b39e68(obj);
	DAT_05b39dbc(obj);
	iVar1 = iVar1 + 0x20;
	DAT_05b39e90 = iVar1;
}

// FUNCTION: SADX 0x004a8740
void MotionObjTranslate(struct obj *obj)
{
	FUN_0067d830(0, obj->pos[0], obj->pos[1], obj->pos[2]);
}

// FUNCTION: SADX 0x004a8770
void MotionObjRotateXYZ(struct obj *obj)
{
	njRotateXYZ(0, (long *)obj->ang[0], (long *)obj->ang[1], (long *)obj->ang[2]);
}

// FUNCTION: SADX 0x004a87a0
void MotionObjRotateZXY(struct obj *obj)
{
	njRotateZXY(0, (long *)obj->ang[0], (long *)obj->ang[1], (long *)obj->ang[2]);
}

// FUNCTION: SADX 0x004a87d0
void MotionObjScale(struct obj *obj)
{
	FUN_0067d2d0(0, obj->scl[0], obj->scl[1], obj->scl[2]);
}

// FUNCTION: SADX 0x004a8800
void FUN_004a8800(struct obj *param_1, struct NJS_MOTION *param_2, float param_3, float param_4)
{
	DrawMotion(param_1, param_2, param_3, 0, param_4, ___DrawModel);
}

// FUNCTION: SADX 0x004a8830
void late_DrawMotionClip(struct obj *object, struct NJS_MOTION *motion, float frame, int flgs, float clipScl)
{
	DrawMotion(object, motion, frame, flgs, clipScl, lateDrawModel);
}

// FUNCTION: SADX 0x004a8860
void late_DrawMotionClipEx(struct obj *object, struct NJS_MOTION *motion, float frame, int flgs, float clipScl)
{
	DrawMotion(object, motion, frame, flgs, clipScl, DrawModelEx);
}

// FUNCTION: SADX 0x004a8890
void late_DrawMotionClipMesh(struct obj *object, struct NJS_MOTION *motion, float frame, int flgs, float clipScl)
{
	DrawMotion(object, motion, frame, flgs, clipScl, DrawModelMesh);
}

// FUNCTION: SADX 0x004a88c0
void FUN_004a88c0(NJS_ACTION *param_1, float param_2)
{
	float local_8g;
	float local_14h;
	float local_1ci;
	float local_18;
	float local_20;
	float local_cj;
	float local_10m;

	DrawAction(param_1, param_2, 0, 0.0f, ___DrawModel);
}

// FUNCTION: SADX 0x004a89c0
void ___dsAction(struct NJS_ACTION *param_1, float param_2, float param_3)
{
	int local_8g;
	int local_14h;
	int local_1ci;
	int local_18;
	int local_20;
	int local_cj;
	int local_10m;
	DrawAction(param_1, param_2, 0, param_3, ___DrawModel);
}

// FUNCTION: SADX 0x004a89f0
void FUN_004a89f0(NJS_ACTION *param_1, float param_2, int param_3)
{
	float local_8g;
	float local_14h;
	int local_1ci;
	int local_18;
	int local_20;
	int local_cj;
	int local_10m;

	DrawAction(param_1, param_2, param_3, 0.0, lateDrawModel);
}

// FUNCTION: SADX 0x004a8a20
void late_Action(NJS_ACTION *param_1, float param_2, int param_3, float param_4)
{
	int local_8g;
	int local_14h;
	int local_1ci;
	int local_18;
	int local_20;
	int local_cj;
	int local_10m;
	DrawAction(param_1, param_2, param_3, param_4, lateDrawModel);
}

// FUNCTION: SADX 0x004a8a50
void FUN_004a8a50(NJS_ACTION *param_1, float param_2, int param_3)
{
	int local_8g;
	int local_14h;
	int local_1ci;
	int local_18;
	int local_20;
	int local_cj;
	int local_10m;

	DrawAction(param_1, param_2, param_3, 0.0f, DrawModelEx);
}

// FUNCTION: SADX 0x004a8ab0
void late_ActionMS(NJS_ACTION *action, float frame, int flgs)
{
	float local_10s;
	int local_8g;
	int local_14h;
	int local_1ci;
	int local_18;
	int local_20;
	int local_cj;
	DrawAction(action, frame, flgs, 0.0f, DrawModelMS);
}

// FUNCTION: SADX 0x004a8ae0
void FUN_004a8ae0(NJS_ACTION *param_1, float param_2, int param_3, float param_4)
{
	int local_8g;
	int local_14h;
	int local_1ci;
	int local_18;
	int local_20;
	int local_cj;
	int local_10m;

	DrawAction(param_1, param_2, param_3, param_4, DrawModelMS);
}

// FUNCTION: SADX 0x004a8b10
void FUN_004a8b10(NJS_ACTION *param_1, float param_2, int param_3)
{
	float local_8g;
	float local_14h;
	float local_1ci;
	float local_18;
	float local_20;
	int local_cj;
	int local_10m;

	DrawAction(param_1, param_2, param_3, 0.0, DrawModelMesh);
}

// FUNCTION: SADX 0x004a8e90
void FUN_004a8e90(float *param_1, float *param_2, float *param_3, float param_4)
{
	*param_3 = (1.0 - param_4) * *param_1 + *param_2 * param_4;
	param_3[1] = (1.0 - param_4) * param_1[1] + param_2[1] * param_4;
	param_3[2] = (1.0 - param_4) * param_1[2] + param_2[2] * param_4;
}

// FUNCTION: SADX 0x004a99c0
void ___dsDrawShapeMotion(const struct obj *object, const struct NJS_MOTION *motion, const struct NJS_MOTION *shape, float frame)
{
	DrawShapeMotion((struct obj *)object, (struct NJS_MOTION *)motion, (struct NJS_MOTION *)shape, frame, 0, 0.0f, (void *)&___DrawModel);
}

// FUNCTION: SADX 0x004a99f0
void late_DrawShapeMotion(struct obj *object, struct NJS_MOTION *motion, struct NJS_MOTION *shape, float frame, int flgs)
{
	DrawShapeMotion(object, motion, shape, frame, flgs, 0.0, lateDrawModel);
}

// FUNCTION: SADX 0x004a9a20
void late_DrawShapeMotionEx(struct obj *object, struct NJS_MOTION *motion, struct NJS_MOTION *shape, float frame, int flgs)
{
	DrawShapeMotion(object, motion, shape, frame, flgs, 0.0f, DrawModelEx);
}

// FUNCTION: SADX 0x004a9a50
void FUN_004a9a50(struct obj *param_1, struct NJS_MOTION *param_2, struct NJS_MOTION *param_3, float param_4, int param_5)
{
	DrawShapeMotion(param_1, param_2, param_3, param_4, param_5, 0.0f, DrawModelMS);
}

// FUNCTION: SADX 0x004a9a80
void late_DrawShapeMotionMesh(struct obj *object, struct NJS_MOTION *motion, struct NJS_MOTION *shape, float frame, int flgs)
{
	DrawShapeMotion(object, motion, shape, frame, flgs, 0.0f, DrawModelMesh);
}

// FUNCTION: SADX 0x004a9ab0
void MotLnkData0(struct obj *obj)
{
	(*(void (*)(struct obj *))DAT_05b39e78[DAT_05b39db8])(obj);
	(*(void (*)(struct obj *))DAT_05b39e08[DAT_05b39db8])(obj);
	(*(void (*)(struct obj *))DAT_05b3dee4[DAT_05b39db8])(obj);
}

// FUNCTION: SADX 0x004a9dc0
void ___dsDrawMotionLink(struct obj *object, struct NJS_MOTION_LINK *motionlink, float frame)
{
	DrawMotionLink(object, motionlink, frame, 0, 0.0f, ___DrawModel);
}

// FUNCTION: SADX 0x004aa720
void FUN_004aa720(float *param_1)
{
	DAT_05b39dc0[DAT_05b39db8 * 3] = param_1[2];
	DAT_05b39dc0[DAT_05b39db8 * 3 + 1] = param_1[3];
	DAT_05b39dc0[DAT_05b39db8 * 3 + 2] = param_1[4];
}

// FUNCTION: SADX 0x004aa770
void FUN_004aa770(struct NJS_POINT3 *param_1)
{
	DAT_05b39eb8[DAT_05b39db8 * 3] = *(int *)((char *)param_1 + 0x14);
	DAT_05b39eb8[DAT_05b39db8 * 3 + 1] = *(int *)((char *)param_1 + 0x18);
	DAT_05b39eb8[DAT_05b39db8 * 3 + 2] = *(int *)((char *)param_1 + 0x1c);
}

// FUNCTION: SADX 0x004aa7c0
void FUN_004aa7c0(float *param_1)
{
	DAT_05b3df0c[DAT_05b39db8 * 3] = param_1[8];
	DAT_05b3df10[DAT_05b39db8 * 3] = param_1[9];
	DAT_05b3df14[DAT_05b39db8 * 3] = param_1[10];
}

// FUNCTION: SADX 0x004aac20
void late_DrawMotionLinkEx(struct obj *object, struct NJS_MOTION_LINK *motionlink, float frame, int flgs)
{
	DrawMotionLink(object, motionlink, frame, flgs, 0.0f, DrawModelEx);
}

// FUNCTION: SADX 0x004aac50
void ___dsActionLink(NJS_ACTION_LINK *actionlink, float frame)
{
	ActionLink(actionlink, frame, 0, 0.0f, ___DrawModel);
}

// FUNCTION: SADX 0x004aaff0
void late_ActionLink(NJS_ACTION_LINK *actionlink, float frame, int flgs)
{
	ActionLink(actionlink, frame, flgs, 0.0, lateDrawModel);
}

// FUNCTION: SADX 0x004ab020
void late_ActionLinkEx(NJS_ACTION_LINK *actionlink, float frame, int flgs)
{
	ActionLink(actionlink, frame, flgs, 0.0f, DrawModelEx);
}

// FUNCTION: SADX 0x004ab050
void late_ActionLinkMesh(NJS_ACTION_LINK *actionlink, float frame, int flgs)
{
	ActionLink(actionlink, frame, flgs, 0.0f, DrawModelMesh);
}
