#include "decls.h"
extern float DAT_05b39e9c;
extern int DAT_05b39ea0;
extern int DAT_05b39eac;
#include <math.h>
extern int DAT_05b3df54;
extern int DAT_05b3df5c;
void FUN_004a2800();
void FUN_004a29c0();
void FUN_005b5aa0(...);
void FUN_004a0960(struct obj *param_1, struct NJS_MOTION *param_2, float param_3);
void FUN_004a0940(struct NJS_MODEL *param_1);
static float CHAOS7_MsZofsFnc(struct LATE_MDL_RQ *mrq, const struct NJS_MODEL *m, float z);
extern "C" void *memcpy(void *param_1, const void *param_2, unsigned int param_3);
extern void *DAT_05b3dedc;
extern int DAT_05b3df24;
extern float DAT_05b39eb0;
static int isTextureNG(struct NJS_TEXLIST *tl, int numChk);
extern float DAT_05b3df44;
void njDrawPolygon3D(NJS_POINT3COL *param_1, Int param_2, Uint32 param_3);
void motion_init_param(struct NJS_MOTION *motion, float frame);
void njSetZUpdateMode(long param_1);
void njSetZUpdateMode(long param_1);
void late_DrawObject(struct obj *obj, int flgs);
void ___DrawObject(struct obj *obj);
extern void (*DAT_05b39df8)(struct obj *obj);
void set_motion_func(struct obj *object);
extern unsigned short DAT_05b39e84;
extern unsigned short DAT_05b39e14;
void nlateBegin(int flgs);
void njSetZUpdateMode(long param_1);
int dsCheckViewV(struct NJS_POINT3 *ft, float radius);
void dsPushPopMotion(struct obj *obj);
extern struct NJS_TEXLIST *DAT_05b3ded0;
void njSetZUpdateMode(long param_1);
extern void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
void *late_setOdr(int sz, int odr, int no, int flgs);
void npSetZCompare();
void njSetZUpdateMode(long param_1);
void *late_alloca(unsigned int sz);
struct LATE_PO2D_RQ;
extern void *late_alloca(unsigned int sz);
extern struct LATE_FAR_Z_T late_far_z_dflt;
extern unsigned char DAT_05b3df51;
void FUN_004a5c80(struct obj *param_1, int param_2);
extern int DAT_05b3df64;
extern void *DAT_05b3df04;
extern int DAT_05b3df4c;
extern unsigned char DAT_05b3df52;
extern int DAT_05b3df68;
extern float DAT_05b3df0c[3];
extern float DAT_05b3df10[3];
extern float DAT_05b3df14[3];
extern int DAT_05b39eb8[9];
extern float DAT_05b39dc0[9];
extern int DAT_05b39db8;
extern void (*DAT_05b39e78[2])(struct obj *);
extern void (*DAT_05b39e08[2])(struct obj *);
extern void (*DAT_05b3dee4[2])(struct obj *);
extern char DAT_05b39e30[2][0x1c];
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
extern int DAT_05b39e90;
extern int DAT_05b39e94;
extern int DAT_05b39e98;
extern int DAT_05b39ea4;
extern void (*DAT_05b3df00)(struct obj *obj);
extern void (*DAT_05b39e68)(struct obj *obj);
extern void (*DAT_05b39dbc)(struct obj *obj);
void FUN_004a3890();
extern struct LATE_FAR_Z_T late_far_z_chaos;
extern struct LATE_FAR_Z_T late_far_z_chaos0;
extern struct LATE_FAR_Z_T late_far_z_chaos7;
extern LATE_FAR_Z_T DAT_05b39e18;
void ___OutputDebugString(char *, ...);
void late_DrawSprite2D(struct NJS_SPRITE *sp, int n, float pri, unsigned long atr, int flgs);
int isTextureNG(struct NJS_TEXLIST *tl, int numChk);
void FUN_004a27c0();
void FUN_004a2960();
extern int DAT_05b39df4;
void late_DrawObjectClip(struct obj *obj, int flgs, float clipScl);
int isTextureNG(NJS_TEXLIST *tl, int numChk);
extern int DAT_05b3dee0;
extern int DAT_05b3ded4;
extern int DAT_05b3ded8;
extern int DAT_05b3df48;
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);
extern unsigned char DAT_05b3df53;
extern float DAT_05b3df38;
void late_DrawModelClip(struct NJS_MODEL *, int, float);
int isTextureNG(struct NJS_TEXLIST *, int);
long dsSimpleDrawModel(struct NJS_MODEL *);
extern unsigned char DAT_02608e24;
extern float DAT_05b3df40;
extern float DAT_05a922f8;
extern float DAT_05a922fc;
extern float DAT_0629c6e0;
extern float DAT_0629c6ec;
extern float DAT_0629c6f0;
extern int DAT_05b39e2c;
extern int DAT_05cd4078;
int isTextureNG(struct NJS_TEXLIST *tl, int numChk);
extern NJS_ARGB DAT_05b3df28;
extern float DAT_05b3df3c;

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

// DIFF: frame: the original frame has 12 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a0690
void late_ReleaseTexture(NJS_TEXLIST *tl)
{
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
	if ((int)tl->nbTexture == 0)
	{
		return 1;
	}
	for (local_cj = 0; local_cj < (unsigned int)(int)tl->nbTexture; local_cj++)
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

// FUNCTION: SADX 0x004a0790
int dsCheckViewV(NJS_POINT3 *ft, float radius)
{
	float local_20k;
	float local_24;
	NJS_POINT3 fv;
	float local_ci;
	float local_8g;

	if (DAT_05b9d838 != 0)
	{
		return 0;
	}
	radius = radius * 1.2f;
	njCalcPoint(0, ft, &fv);
	if (clipZ_far > -fv.z + radius)
	{
		return 0;
	}
	if (-fv.z - radius > clipZ_near)
	{
		return 0;
	}
	local_20k = -fv.z - radius;
	local_24 = -1.0f / local_20k;
	local_ci = (fv.x + radius) * (DAT_05a922f8 * DAT_0629c6e0) * local_24 + DAT_0629c6ec;
	if (local_ci < 0.0f)
	{
		return 0;
	}
	local_ci = (fv.x - radius) * (DAT_05a922f8 * DAT_0629c6e0) * local_24 + DAT_0629c6ec;
	if (local_ci > ScreenRaitoX * 640.0f)
	{
		return 0;
	}
	local_8g = (fv.y - radius) * (-DAT_0629c6e0 * DAT_05a922fc) * local_24 + DAT_0629c6f0;
	if (local_8g < 0.0f)
	{
		return 0;
	}
	local_8g = (fv.y + radius) * (-DAT_0629c6e0 * DAT_05a922fc) * local_24 + DAT_0629c6f0;
	if (local_8g > ScreenRaitoY * 480.0f)
	{
		return 0;
	}
	return 1;
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

// FUNCTION: SADX 0x004a09a0
int FUN_004a09a0(struct NJS_MODEL *param_1)
{
	njSetConstantMaterial(&DAT_05b3df28);
	FUN_004a0940(param_1);
	njSetConstantMaterial(&DAT_05b39de4);
	return 0;
}

// FUNCTION: SADX 0x004a09d0
void FUN_004a09d0(struct obj *param_1, struct NJS_MOTION *param_2, float param_3)
{
	njSetConstantMaterial(&DAT_05b3df28);
	FUN_004a0960(param_1, param_2, param_3);
	njSetConstantMaterial(&DAT_05b39de4);
}

// FUNCTION: SADX 0x004a0a10
void njEasyDrawObject(NJS_OBJECT *obj)
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

// STUB: SADX 0x004a0ae0
void ___dsDrawModel(NJS_MODEL *model)
{
}

// STUB: SADX 0x004a0c10
void ___dsDrawObject(struct obj *obj)
{
}

// FUNCTION: SADX 0x004a0d10
void ___DrawObject(struct obj *obj)
{
	unsigned long local_8;

	while (obj != (struct obj *)0)
	{
		local_8 = obj->evalflags;
		switch (local_8 & 7)
		{
		case 0:
			njPushMatrixEx();
			njTranslateEx((NJS_VECTOR *)obj->pos);
			if (local_8 & 0x20)
			{
				njRotateZXY(0, obj->ang[0], obj->ang[1], obj->ang[2]);
			}
			else
			{
				njRotateXYZ(0, obj->ang[0], obj->ang[1], obj->ang[2]);
			}
			njScaleEx((NJS_VECTOR *)obj->scl);
			if ((local_8 & 8) == 0)
			{
				unsigned long local_c = (unsigned long)obj->model;
				if ((local_c < 0x100000) == 0)
				{
					if ((signed char)DAT_02608e24 != 0 && DAT_05cd4078 <= 0)
					{
						dsSimpleDrawModel((NJS_MODEL *)local_c);
					}
					else
					{
						njDrawModel((NJS_MODEL *)local_c);
					}
				}
			}
			if ((local_8 & 0x10) == 0)
			{
				___DrawObject(obj->child);
			}
			njPopMatrixEx();
			break;
		case 1:
			njPushMatrixEx();
			if (local_8 & 0x20)
			{
				njRotateZXY(0, obj->ang[0], obj->ang[1], obj->ang[2]);
			}
			else
			{
				njRotateXYZ(0, obj->ang[0], obj->ang[1], obj->ang[2]);
			}
			njScaleEx((NJS_VECTOR *)obj->scl);
			if ((local_8 & 8) == 0)
			{
				unsigned long local_10 = (unsigned long)obj->model;
				if ((local_10 < 0x100000) == 0)
				{
					if ((signed char)DAT_02608e24 != 0 && DAT_05cd4078 <= 0)
					{
						dsSimpleDrawModel((NJS_MODEL *)local_10);
					}
					else
					{
						njDrawModel((NJS_MODEL *)local_10);
					}
				}
			}
			if ((local_8 & 0x10) == 0)
			{
				___DrawObject(obj->child);
			}
			njPopMatrixEx();
			break;
		case 2:
			njPushMatrixEx();
			njTranslateEx((NJS_VECTOR *)obj->pos);
			njScaleEx((NJS_VECTOR *)obj->scl);
			if ((local_8 & 8) == 0)
			{
				unsigned long local_14 = (unsigned long)obj->model;
				if ((local_14 < 0x100000) == 0)
				{
					if ((signed char)DAT_02608e24 != 0 && DAT_05cd4078 <= 0)
					{
						dsSimpleDrawModel((NJS_MODEL *)local_14);
					}
					else
					{
						njDrawModel((NJS_MODEL *)local_14);
					}
				}
			}
			if ((local_8 & 0x10) == 0)
			{
				___DrawObject(obj->child);
			}
			njPopMatrixEx();
			break;
		case 3:
			njPushMatrixEx();
			njScaleEx((NJS_VECTOR *)obj->scl);
			if ((local_8 & 8) == 0)
			{
				unsigned long local_18 = (unsigned long)obj->model;
				if ((local_18 < 0x100000) == 0)
				{
					if ((signed char)DAT_02608e24 != 0 && DAT_05cd4078 <= 0)
					{
						dsSimpleDrawModel((NJS_MODEL *)local_18);
					}
					else
					{
						njDrawModel((NJS_MODEL *)local_18);
					}
				}
			}
			if ((local_8 & 0x10) == 0)
			{
				___DrawObject(obj->child);
			}
			njPopMatrixEx();
			break;
		case 4:
			njPushMatrixEx();
			njTranslateEx((NJS_VECTOR *)obj->pos);
			if (local_8 & 0x20)
			{
				njRotateZXY(0, obj->ang[0], obj->ang[1], obj->ang[2]);
			}
			else
			{
				njRotateXYZ(0, obj->ang[0], obj->ang[1], obj->ang[2]);
			}
			if ((local_8 & 8) == 0)
			{
				unsigned long local_1c = (unsigned long)obj->model;
				if ((local_1c < 0x100000) == 0)
				{
					if ((signed char)DAT_02608e24 != 0 && DAT_05cd4078 <= 0)
					{
						dsSimpleDrawModel((NJS_MODEL *)local_1c);
					}
					else
					{
						njDrawModel((NJS_MODEL *)local_1c);
					}
				}
			}
			if ((local_8 & 0x10) == 0)
			{
				___DrawObject(obj->child);
			}
			njPopMatrixEx();
			break;
		case 5:
			njPushMatrixEx();
			if (local_8 & 0x20)
			{
				njRotateZXY(0, obj->ang[0], obj->ang[1], obj->ang[2]);
			}
			else
			{
				njRotateXYZ(0, obj->ang[0], obj->ang[1], obj->ang[2]);
			}
			if ((local_8 & 8) == 0)
			{
				unsigned long local_20 = (unsigned long)obj->model;
				if ((local_20 < 0x100000) == 0)
				{
					if ((signed char)DAT_02608e24 != 0 && DAT_05cd4078 <= 0)
					{
						dsSimpleDrawModel((NJS_MODEL *)local_20);
					}
					else
					{
						njDrawModel((NJS_MODEL *)local_20);
					}
				}
			}
			if ((local_8 & 0x10) == 0)
			{
				___DrawObject(obj->child);
			}
			njPopMatrixEx();
			break;
		case 6:
			njPushMatrixEx();
			njTranslateEx((NJS_VECTOR *)obj->pos);
			if ((local_8 & 8) == 0)
			{
				unsigned long local_24 = (unsigned long)obj->model;
				if ((local_24 < 0x100000) == 0)
				{
					if ((signed char)DAT_02608e24 != 0 && DAT_05cd4078 <= 0)
					{
						dsSimpleDrawModel((NJS_MODEL *)local_24);
					}
					else
					{
						njDrawModel((NJS_MODEL *)local_24);
					}
				}
			}
			if ((local_8 & 0x10) == 0)
			{
				___DrawObject(obj->child);
			}
			njPopMatrixEx();
			break;
		default:
			if ((local_8 & 8) == 0)
			{
				unsigned long local_28 = (unsigned long)obj->model;
				if ((local_28 < 0x100000) == 0)
				{
					if ((signed char)DAT_02608e24 != 0 && DAT_05cd4078 <= 0)
					{
						dsSimpleDrawModel((NJS_MODEL *)local_28);
					}
					else
					{
						njDrawModel((NJS_MODEL *)local_28);
					}
				}
			}
			if ((local_8 & 0x10) == 0)
			{
				___DrawObject(obj->child);
			}
			break;
		}
		obj = obj->sibling;
	}
}

// STUB: SADX 0x004a1290
void ds_DrawModelClip(NJS_MODEL *mdl, float clipScl)
{
}

// STUB: SADX 0x004a1420
void ds_DrawObjectClip(struct obj *obj, float clipScl)
{
}

// FUNCTION: SADX 0x004a1e90
float FUN_004a1e90(float *param_1)
{
	float local_cg = fabsf(param_1[0]);
	float local_8g = fabsf(param_1[1]);
	float local_10g = fabsf(param_1[2]);

	local_cg = local_cg > local_8g ? (local_cg > local_10g ? local_cg : local_10g) : (local_8g > local_10g ? local_8g : local_10g);
	return local_cg;
}

// FUNCTION: SADX 0x004a1f70
void dsDrawModel_S(struct NJS_MODEL *m)
{
	if (m->r >= 900.0f)
	{
		ds_DrawModelClip(m, 1.0f);
	}
	else
	{
		late_DrawModelClipEx(m, 0, 1.0f);
	}
}

// STUB: SADX 0x004a1fb0
void dsOpenDraw_S()
{
}

// FUNCTION: SADX 0x004a1fd0
void ___njDrawSprite3D(struct NJS_SPRITE *sp, int n, unsigned long atr)
{
	int local_8;

	local_8 = (atr & 0x20) ? 4 : 1;
	late_DrawSprite3D(sp, n, atr, local_8);
}

// DIFF: frame: the original frame has 24 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a2010
void ___njDrawLine3D(struct NJS_POINT3COL *p, int n, unsigned long atr)
{
	if (DAT_05b9d838 != 0)
		return;
	if (atr & 0x80000000)
	{
		if (isTextureNG(DAT_05b3ded0, 0) != 0)
			return;
		if (isTextureNG(DAT_05b3ded0, 1) != 0)
			return;
	}
	njDrawLine3D(p, n, atr);
}

// DIFF: frame: the original frame has 24 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a2080
void ___njDrawTriangle3D(struct NJS_POINT3COL *p, int n, unsigned long atr)
{
	if (DAT_05b9d838 != 0)
		return;
	if (atr & 0x80000000)
	{
		if (isTextureNG(DAT_05b3ded0, 0) != 0)
			return;
		if (isTextureNG(DAT_05b3ded0, 1) != 0)
			return;
	}
	njDrawTriangle3D(p, n, atr);
}

// STUB: SADX 0x004a20f0
void ___njDrawPolygon2D(struct NJS_POINT2COL *p, int n, float pri, unsigned long atr)
{
}

// DIFF: frame: the original frame has 24 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a2180
void ___njDrawPolygon3D(struct NJS_POINT3COL *p, int n, unsigned long atr)
{
	if (DAT_05b9d838 != 0)
		return;
	if ((0x80000000 & atr) != 0)
	{
		if (isTextureNG(DAT_05b3ded0, 0) != 0)
			return;
		if (isTextureNG(DAT_05b3ded0, 1) != 0)
			return;
	}
	njDrawPolygon3D(p, n, atr);
}

// STUB: SADX 0x004a21f0
void dsDrawSprite2D(NJS_SPRITE *sp, int n, float pri, unsigned long atr)
{
}

// STUB: SADX 0x004a2320
void dsDrawSprite3D(NJS_SPRITE *sp, int n, unsigned long atr)
{
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

// FUNCTION: SADX 0x004a27c0
void FUN_004a27c0()
{
	FUN_004a2800();
	ResetMaterial();
	FUN_004a29c0();
	FUN_005b5aa0();
	DAT_05b9d838 = 0;
	DAT_05b3df54 = 0;
	DAT_05b3df5c = 0;
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
	local_8 = DAT_05b3df40;
	DAT_05b3df40 = -27952.0f;
	late_DrawObjectClip(obj, 6, clipScl);
	DAT_05b3df40 = local_8;
}

// FUNCTION: SADX 0x004a2880
void late_DrawShadowModel(struct NJS_MODEL *mdl, float clipScl)
{
	float local_8;
	local_8 = DAT_05b3df40;
	DAT_05b3df40 = -27952.0;
	late_DrawModelClip(mdl, 6, clipScl);
	DAT_05b3df40 = local_8;
}

// FUNCTION: SADX 0x004a28c0
void late_reset_far_z()
{
	DAT_05b39e18 = late_far_z_dflt;
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
	DAT_05b39e18.nor = nor;
	(&DAT_05b39e18)->ex = ex;
	(&DAT_05b39e18)->mesh = mesh;
}

// FUNCTION: SADX 0x004a2960
void FUN_004a2960()
{
	if (((void)0, 0) == 7)
	{
		late_far_z_chaos = late_far_z_chaos7;
	}
	else
	{
		late_far_z_chaos = late_far_z_chaos0;
	}
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

// FUNCTION: SADX 0x004a38d0
static void *late_addZEntry(float z, struct LATE_LNK *a, int md)
{
	int local_ci;
	int local_8g;
	char *local_18;
	char *local_14;
	char *local_10;

	local_8g = 0;
	*(float *)((char *)a + 4) = z;
	local_ci = (int)(z + 2048.0 + DAT_05b3df40);
	if ((*(unsigned char *)((char *)a + 8) & 0x10) == 0)
		local_ci += 8;
	if (local_ci > 0x7fe)
	{
		*(float *)((char *)a + 4) = z + DAT_05b3df40;
		if (md == 1 && local_ci >= 10000)
		{
			local_ci = 0x7ff;
			local_8g = 1;
		}
		else
			local_ci = 0x7fe;
	}
	else if (local_ci < 5)
	{
		*(float *)((char *)a + 4) = z + DAT_05b3df40;
		if (local_ci > -7952)
			local_ci = 4;
		else if (local_ci > -17952)
			local_ci = 3;
		else if (local_ci > -27952)
			local_ci = 2;
		else if (local_ci > -37952)
			local_ci = 1;
		else
			local_ci = 0;
		local_8g = 1;
		md = local_8g;
	}
	local_10 = (char *)late_zentry + local_ci * 8;
	for (local_18 = local_10, local_14 = *(char **)local_10; local_14 != local_10;
		local_18 = local_14, local_14 = *(char **)local_14)
	{
		if (*(float *)((char *)a + 4) < *(float *)(local_14 + 4))
		{
			*(char **)a = local_14;
			*(struct LATE_LNK **)local_18 = a;
			break;
		}
	}
	if (local_14 == local_10)
	{
		*(char **)a = local_10;
		*(struct LATE_LNK **)local_18 = a;
		*(struct LATE_LNK **)(local_10 + 4) = a;
	}
	return a;
}

// FUNCTION: SADX 0x004a3a50
static void *late_setOdr(int sz, int odr, int no, int flgs)
{
	int local_8g;
	void *local_cg;
	NJS_ARGB *local_10g;

	if (DAT_05b39e2c != 0)
		return 0;
	if (flgs & 8)
		return 0;
	local_cg = late_alloca(sz);
	if (local_cg == 0)
		return 0;
	*(unsigned char *)((char *)local_cg + 8) = DAT_05b3e065 << 5 | (flgs & 1) << 4 | odr;
	*(unsigned short *)((char *)local_cg + 0xa) = no;
	*(NJS_TEXLIST **)((char *)local_cg + 0xc) = DAT_05b3ded0;
	*(unsigned char *)((char *)local_cg + 9) = DAT_05b39e10;
	*(int *)((char *)local_cg + 0x20) = DAT_0629c6c8;
	*(int *)((char *)local_cg + 0x24) = DAT_0629c540;
	*(int *)((char *)local_cg + 0x28) = DAT_0629c6c4;
	local_10g = (flgs & 2) ? &DAT_05b3df28 : &DAT_05b39de4;
	*(NJS_ARGB *)((char *)local_cg + 0x10) = *local_10g;
	local_8g = DAT_05cd4078;
	if (flgs & 4)
		*(unsigned short *)((char *)local_cg + 0xa) |= 0x8000;
	*(unsigned char *)((char *)local_cg + 8) |= local_8g << 6;
	return local_cg;
}

// STUB: SADX 0x004a3b80
int late_setPo2D(struct LATE_PO2D_RQ *s, struct NJS_POINT2COL *p, int n, float pri, unsigned long atr)
{
	return (int)0;
}

// FUNCTION: SADX 0x004a3cf0
static float nlateBegin2D(int flgs, float pri)
{
	if (pri >= 10000.0 || (flgs & 0x10))
	{
		UNKNOWN_ZUPDATE_MACRO(7, 0);
	}
	else if ((flgs & 1) == 0)
	{
		UNKNOWN_ZUPDATE_MACRO(3, 0);
	}
	else
	{
		UNKNOWN_ZUPDATE_MACRO(3, 1);
	}
	njSetConstantMaterial((flgs & 2) ? &DAT_05b3df28 : &DAT_05b39de4);
	if (pri > -1.0)
		pri = -1.0f;
	return pri;
}

// STUB: SADX 0x004a3db0
void late_DrawLine3D(struct NJS_POINT3COL *p, int n, unsigned long atr, int flgs)
{
}

// FUNCTION: SADX 0x004a3ea0
int late_setPo3D(struct LATE_PO3D_RQ *s, struct NJS_POINT3COL *p, int n, unsigned long atr)
{
	int local_8;

	*(unsigned long *)((char *)s + 0x80) = atr;
	*(int *)((char *)s + 0x84) = DAT_05b39eb4;
	*(struct NJS_POINT3COL *)((char *)s + 0x30) = *p;
	if (p->p != 0)
	{
		*(int *)((char *)s + 0x30) = (int)late_alloca(n * 0xc);
		if (*(int *)((char *)s + 0x30) == 0)
		{
			return 0;
		}
		memcpy(*(void **)((char *)s + 0x30), p->p, n * 0xc);
	}
	if (p->col != 0)
	{
		*(int *)((char *)s + 0x34) = (int)late_alloca(n * 4);
		if (*(int *)((char *)s + 0x34) == 0)
		{
			return 0;
		}
		for (local_8 = 0; local_8 < n; local_8++)
		{
			((int *)(*(int *)((char *)s + 0x34)))[local_8] = ((int *)p->col)[local_8];
		}
	}
	if (p->tex != 0)
	{
		*(int *)((char *)s + 0x38) = (int)late_alloca(n * 4);
		if (*(int *)((char *)s + 0x38) == 0)
		{
			return 0;
		}
		memcpy(*(void **)((char *)s + 0x38), p->tex, n * 4);
	}
	if ((atr & 0x80000000) == 0)
	{
		*(int *)((char *)s + 0xc) = 0;
	}
	njGetMatrix((NJS_MATRIX *)((char *)s + 0x40));
	return 1;
}

// FUNCTION: SADX 0x004a4000
static void nlateBegin(int flgs)
{
	if ((flgs & 1) == 0)
	{
		UNKNOWN_ZUPDATE_MACRO(3, 0);
	}
	if (flgs & 0x10)
	{
		UNKNOWN_ZUPDATE_MACRO(7, 0);
	}
	njSetConstantMaterial((flgs & 2) ? &DAT_05b3df28 : &DAT_05b39de4);
}

// STUB: SADX 0x004a4070
void late_DrawTriangle3D(struct NJS_POINT3COL *p, int n, unsigned long atr, int flgs)
{
}

// STUB: SADX 0x004a4160
void late_DrawBoxFill2D(float x, float y, float x2, float y2, float pri, unsigned long argb, int flgs)
{
}

// STUB: SADX 0x004a43c0
void late_DrawPolygon3D(struct NJS_POINT3COL *p, int n, unsigned long atr, int flgs)
{
}

// DIFF: frame: the original frame has 48 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a44b0
void late_DrawSprite2D(NJS_SPRITE *sp, int n, float pri, unsigned long atr, int flgs)
{
	void *local_8g;

	if (DAT_05b9d838 != 0)
		return;
	if ((unsigned int)sp < 0x100000)
		return;
	if (isTextureNG(sp->tlist, 1) != 0)
		return;
	if (pri >= -2.0 && pri < 10000.0)
		pri += 12048.0;
	local_8g = late_setOdr(0x98, 2, n, flgs);
	if (local_8g != 0)
	{
		*(float *)((char *)local_8g + 0x54) = pri;
		*(unsigned long *)((char *)local_8g + 0x50) = atr;
		*(NJS_SPRITE *)((char *)local_8g + 0x30) = *sp;
		njGetMatrix((NJS_MATRIX *)((char *)local_8g + 0x58));
		late_addZEntry(pri, (struct LATE_LNK *)local_8g, 1);
	}
	else
	{
		pri = nlateBegin2D(flgs, pri);
		njDrawSprite2D(sp, n, pri, atr);
		npSetZCompare();
		njSetZUpdateMode(1);
		ResetMaterial();
	}
}

// DIFF: frame: the original frame has 44 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a45e0
void late_DrawSprite3D(NJS_SPRITE *sp, int n, unsigned long atr, int flgs)
{
	float local_ci;
	void *local_8g;

	if (DAT_05b9d838 != 0)
		return;
	if ((unsigned int)sp < 0x100000)
		return;
	if (isTextureNG(sp->tlist, 1) != 0)
		return;
	local_8g = late_setOdr(0x98, 3, n, flgs);
	if (local_8g != 0)
	{
		*(unsigned long *)((char *)local_8g + 0x50) = atr;
		*(NJS_SPRITE *)((char *)local_8g + 0x30) = *sp;
		njGetMatrix((NJS_MATRIX *)((char *)local_8g + 0x58));
		local_ci = sp->p.x * *(float *)((char *)local_8g + 0x60) + sp->p.y * *(float *)((char *)local_8g + 0x70)
			+ sp->p.z * *(float *)((char *)local_8g + 0x80) + *(float *)((char *)local_8g + 0x90);
		local_ci = -local_ci;
		late_addZEntry(local_ci + DAT_05b3df38, (struct LATE_LNK *)local_8g, 0);
	}
	else
	{
		nlateBegin(flgs);
		njDrawSprite3D(sp, n, atr);
		npSetZCompare();
		njSetZUpdateMode(1);
		ResetMaterial();
	}
}

// STUB: SADX 0x004a4710
void late_SetFunc(void (*fnc)(void *), void *arg, float zprio, int flgs)
{
}

// DIFF: frame: the original frame has 12 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a47d0
void late_DrawObjectClip(struct obj *obj, int flgs, float clipScl)
{
	if (DAT_05b9d838 != 0)
		return;
	if (isTextureNG(DAT_05b3ded0, 0) != 0)
		return;
	lateDrawObject(obj, flgs, clipScl);
}

// DIFF: frame: the original frame has 12 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a4820
void late_DrawObject(struct obj *obj, int flgs)
{
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if (isTextureNG(DAT_05b3ded0, 0) != 0)
	{
		return;
	}
	lateDrawObject(obj, flgs, DAT_05b3df44);
}

// STUB: SADX 0x004a4ff0
void late_DrawModelClip(struct NJS_MODEL *mdl, int flgs, float clipScl)
{
}

// DIFF: frame: the original frame has 12 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a5080
void late_DrawModel(struct NJS_MODEL *mdl, int flgs)
{
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if (isTextureNG(DAT_05b3ded0, 0) != 0)
	{
		return;
	}
	if (mdl != 0)
	{
		if (DAT_05b3df44 == 0.0f || mdl->r == 0.0f || dsCheckViewV(&mdl->center, mdl->r * DAT_05b3df44) != 0)
		{
			lateDrawModel(mdl, flgs);
		}
	}
}

// DIFF: frame: the original frame has 12 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a51f0
void late_DrawObjectClipEx(struct obj *obj, int flgs, float clipScl)
{
	if (DAT_05b9d838 != 0)
		return;
	if (isTextureNG(DAT_05b3ded0, 0) != 0)
		return;
	DrawObjectClipEx(obj, flgs, clipScl);
}

// DIFF: frame: the original frame has 12 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a5240
void late_DrawObjectEx(struct obj *obj, int flgs)
{
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if (isTextureNG(DAT_05b3ded0, 0) != 0)
	{
		return;
	}
	DrawObjectClipEx(obj, flgs, DAT_05b3df44);
}

// STUB: SADX 0x004a5a10
void late_DrawModelEx(struct NJS_MODEL *mdl, int flgs)
{
}

// STUB: SADX 0x004a5aa0
void late_DrawModelClipEx(struct NJS_MODEL *mdl, int flgs, float clipScl)
{
}

// DIFF: frame: the original frame has 12 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a5c80
void FUN_004a5c80(struct obj *param_1, int param_2)
{
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if (isTextureNG(DAT_05b3ded0, 0) != 0)
	{
		return;
	}
	DrawObjectMS(param_1, param_2, DAT_05b3df44);
}

// DIFF: frame: the original frame has 12 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a5cd0
void late_DrawObjectClipMS(struct obj *obj, int flgs, float clipScl)
{
	if (DAT_05b9d838 != 0)
		return;
	if (isTextureNG(DAT_05b3ded0, 0) != 0)
		return;
	DrawObjectMS(obj, flgs, clipScl);
}

// STUB: SADX 0x004a64a0
void late_DrawModelMS(struct NJS_MODEL *mdl, int flgs)
{
}

// STUB: SADX 0x004a6530
void late_DrawModelClipMS(struct NJS_MODEL *mdl, int flgs, float clipScl)
{
}

// FUNCTION: SADX 0x004a6900
float FUN_004a6900(void *param_1, float *param_2)
{
	float local_8 = *(float *)((char *)param_1 + 8) * *param_2 + *(float *)((char *)param_1 + 0x18) * param_2[1] + *(float *)((char *)param_1 + 0x28) * param_2[2] + *(float *)((char *)param_1 + 0x38);
	return -local_8;
}

// DIFF: frame: the original frame has 12 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a6940
void late_DrawObjectMesh(struct obj *obj, int flgs)
{
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if (isTextureNG(DAT_05b3ded0, 0) != 0)
	{
		return;
	}
	DrawObjectClipMesh(obj, flgs, DAT_05b3df44);
}

// DIFF: frame: the original frame has 12 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a6990
void late_DrawObjectClipMesh(struct obj *obj, int flgs, float clipScl)
{
	if (DAT_05b9d838 != 0)
		return;
	if (isTextureNG(DAT_05b3ded0, 0) != 0)
		return;
	DrawObjectClipMesh(obj, flgs, clipScl);
}

// STUB: SADX 0x004a7160
void late_DrawModelMesh(struct NJS_MODEL *mdl, int flgs)
{
}

// STUB: SADX 0x004a71f0
void late_DrawModelClipMesh(struct NJS_MODEL *mdl, int flgs, float clipScl)
{
}

// FUNCTION: SADX 0x004a7620
void CHAOS_SetChaosNo(int no)
{

	DAT_05b3df51 = no;
	if (no == 7)
	{
		late_far_z_chaos = late_far_z_chaos7;
	}
	else
	{
		late_far_z_chaos = late_far_z_chaos0;
	}
	DAT_05b3df04 = 0;
	DAT_05b3df4c = 0;
	DAT_05b3df52 = 0;
	DAT_05b3df68 = 0;
	DAT_05b3df53 = 0;
	switch (no)
	{
	case 4:
		DAT_05b3df4c = 1;
		DAT_05b3df52 = 1;
		DAT_05b3df68 = 1;
		break;
	case 7:
		DAT_05b3df4c = 1;
		DAT_05b3df04 = (void *)CHAOS7_MsZofsFnc;
		break;
	}
}

// FUNCTION: SADX 0x004a76f0
float CHAOS7_MsZofsFnc(struct LATE_MDL_RQ *mrq, const struct NJS_MODEL *m, float z)
{
	switch (m->mats[0].attr_texId & 0xffff)
	{
		case 0:
			*(unsigned char *)((char *)mrq + 8) |= 0x10;
			return z + 10.0f;
		case 1:
			*(unsigned char *)((char *)mrq + 8) |= 0x10;
			return z - 300.0f;
		case 6:
		case 7:
			*(unsigned char *)((char *)mrq + 8) |= 0x10;
			return z - 200.0f;
	}
	if (m == model_c7_kihon_chaos7_c7_ago_u2_in || m == model_c7_kihon_chaos7_c7_ago_u1_in || m == model_c7_kihon_chaos7_c7_ago_t_in || m == model_c7_kihon_chaos7_c7_ago_u1 || m == model_c7_kihon_chaos7_c7_eye || m == model_c7_kihon_chaos7_c7_ago_t || m == model_c7_kihon_chaos7_c7_head_in || m == model_c7_kihon_chaos7_c7_head)
	{
		*(unsigned char *)((char *)mrq + 8) |= 0x10;
	}
	return z;
}

// FUNCTION: SADX 0x004a7800
void CHAOS_SetMeshMode(int sw)
{
	DAT_05b3df53 = sw;
}

// FUNCTION: SADX 0x004a7810
void CHAOS_DrawModel(struct NJS_MODEL *m)
{
	DAT_05b3df64 = (int)DAT_05b3df04;
	DAT_05b39e18 = late_far_z_chaos;
	if ((char)DAT_05b3df52 != 0)
	{
		DAT_05b3df40 = -7952.0f;
	}
	if ((char)DAT_05b3df53 != 0)
	{
		late_DrawModelMesh(m, DAT_05b3df68 | 0x8000);
	}
	else
	{
		late_DrawModelMS(m, DAT_05b3df68);
	}
	if (DAT_05b3df4c != 0)
	{
		DAT_05b3df40 = 0.0f;
	}
	DAT_05b39e18 = late_far_z_dflt;
	DAT_05b3df64 = 0;
}

// FUNCTION: SADX 0x004a78d0
void CHAOS_DrawObject(struct obj *o)
{
	DAT_05b3df64 = (int)DAT_05b3df04;
	DAT_05b39e18 = late_far_z_chaos;
	if ((char)DAT_05b3df52 != 0)
	{
		DAT_05b3df40 = -7952.0f;
	}
	FUN_004a5c80(o, DAT_05b3df68);
	if (DAT_05b3df4c != 0)
	{
		DAT_05b3df40 = 0.0f;
	}
	DAT_05b39e18 = late_far_z_dflt;
	DAT_05b3df64 = 0;
}

// FUNCTION: SADX 0x004a7970
void CHAOS_Action(struct NJS_ACTION *a, float fr)
{
	DAT_05b3df64 = (int)DAT_05b3df04;
	DAT_05b39e18 = late_far_z_chaos;
	if ((char)DAT_05b3df52 != 0)
	{
		DAT_05b3df40 = -7952.0f;
	}
	late_ActionMS(a, fr, DAT_05b3df68);
	if (DAT_05b3df4c != 0)
	{
		DAT_05b3df40 = 0.0f;
	}
	DAT_05b39e18 = late_far_z_dflt;
	DAT_05b3df64 = 0;
}

// FUNCTION: SADX 0x004a7a10
void CHAOS_DrawShapeMotion(struct obj *o, struct NJS_MOTION *m, struct NJS_MOTION *shp, float fr)
{
	DAT_05b3df64 = (int)DAT_05b3df04;
	DAT_05b39e18 = late_far_z_chaos;
	if ((char)DAT_05b3df52 != 0)
	{
		DAT_05b3df40 = -7952.0f;
	}
	FUN_004a9a50(o, m, shp, fr, DAT_05b3df68);
	if (DAT_05b3df4c != 0)
	{
		DAT_05b3df40 = 0.0f;
	}
	DAT_05b39e18 = late_far_z_dflt;
	DAT_05b3df64 = 0;
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

// FUNCTION: SADX 0x004a7cb0
void FUN_004a7cb0(struct obj *param_1, struct NJS_MOTION *param_2, float param_3)
{
	DrawMotion(param_1, param_2, param_3, 0, 0, ___DrawModel);
}

// FUNCTION: SADX 0x004a7ce0
void ___DrawModel(struct NJS_MODEL *model)
{
	if (((unsigned long)model < 0x100000) == 0)
	{
		if ((signed char)DAT_02608e24 != 0 && DAT_05cd4078 <= 0)
		{
			dsSimpleDrawModel(model);
		}
		else
		{
			njDrawModel(model);
		}
	}
}

// DIFF: frame: the original frame has 20 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a7d20
void DrawMotion(struct obj *object, struct NJS_MOTION *motion, float frame, int flgs, float clpScl, void *drwMdlFnc)
{
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if ((unsigned long)object < 0x100000 || (unsigned long)motion < 0x100000)
	{
		return;
	}
	if (isTextureNG(DAT_05b3ded0, 0) != 0)
	{
		return;
	}
	DAT_05b3dedc = drwMdlFnc;
	DAT_05b3df24 = flgs;
	DAT_05b39eb0 = 0.0f;
	motion_init_param(motion, frame);
	set_motion_func(object);
	dsPushPopMotion(object);
	DAT_05b39eb0 = 0.0f;
}

// STUB: SADX 0x004a7db0
void dsPushPopMotion(struct obj *obj)
{
}

// FUNCTION: SADX 0x004a7f60
void motion_init_param(struct NJS_MOTION *motion, float frame)
{
	float local_8g;
	unsigned long local_cg;

	local_8g = frame;
	if (motion != 0)
	{
		local_cg = motion->nbFrame;
		local_8g -= (float)((unsigned long)frame / local_cg * local_cg);
		DAT_05b39e84 = motion->inp_fn & ~0xc0;
		DAT_05b39e14 = motion->type;
		DAT_05b39e90 = (int)motion->mdata;
		DAT_05b39ea0 = (int)motion->nbFrame;
	}
	else
	{
		DAT_05b39e84 = 0;
		DAT_05b39e14 = 0;
	}
	DAT_05b39e9c = local_8g;
	DAT_05b39ea4 = 0;
	DAT_05b39eac = 0;
}

// FUNCTION: SADX 0x004a8020
void set_motion_func(struct obj *object)
{
	DAT_05b39df8 = motion_data_func_table[DAT_05b39e84];
	if ((DAT_05b39e14 & 1) != 0)
	{
		DAT_05b3df00 = MotionIntTranslate;
	}
	else
	{
		DAT_05b3df00 = MotionObjTranslate;
	}
	if ((DAT_05b39e14 & 2) != 0)
	{
		if ((object->evalflags & 0x20) != 0)
		{
			DAT_05b39e68 = MotionIntRotateZXY;
		}
		else
		{
			DAT_05b39e68 = MotionIntRotateXYZ;
		}
	}
	else
	{
		if ((object->evalflags & 0x20) != 0)
		{
			DAT_05b39e68 = MotionObjRotateZXY;
		}
		else
		{
			DAT_05b39e68 = MotionObjRotateXYZ;
		}
	}
	if ((DAT_05b39e14 & 4) != 0)
	{
		DAT_05b39dbc = MotionIntScale;
	}
	else
	{
		DAT_05b39dbc = MotionObjScale;
	}
}

// STUB: SADX 0x004a80d0
void MotionIntTranslate(struct obj *obj)
{
}

// STUB: SADX 0x004a8200
void LinearMotionF(struct NJS_MKEY_F *key, unsigned long keyno, unsigned long n, float *dst)
{
}

// STUB: SADX 0x004a8410
void MotionIntRotateXYZ(struct obj *obj)
{
}

// STUB: SADX 0x004a8530
void LinearMotionA(struct NJS_MKEY_A *key, unsigned long keyno, unsigned long n, long *dst)
{
}

// STUB: SADX 0x004a8620
void MotionIntRotateZXY(struct obj *obj)
{
}

// FUNCTION: SADX 0x004a8740
void MotionObjTranslate(struct obj *obj)
{
	FUN_0067d830(0, obj->pos[0], obj->pos[1], obj->pos[2]);
}

// FUNCTION: SADX 0x004a8770
void MotionObjRotateXYZ(struct obj *obj)
{
	njRotateXYZ(0, obj->ang[0], obj->ang[1], obj->ang[2]);
}

// FUNCTION: SADX 0x004a87a0
void MotionObjRotateZXY(struct obj *obj)
{
	njRotateZXY(0, obj->ang[0], obj->ang[1], obj->ang[2]);
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

// DIFF: frame: the original frame has 28 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a88c0
void FUN_004a88c0(NJS_ACTION *param_1, float param_2)
{
	DrawAction(param_1, param_2, 0, 0.0, ___DrawModel);
}

// STUB: SADX 0x004a88f0
void DrawAction(struct NJS_ACTION *action, float frame, int flgs, float clpScl, void *drwMdlFnc)
{
}

// DIFF: frame: the original frame has 28 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a89c0
void ds_ActionClip(NJS_ACTION *action, float frame, float clipScl)
{
	DrawAction(action, frame, 0, clipScl, (void *)___DrawModel);
}

// DIFF: frame: the original frame has 28 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a89f0
void late_Action(NJS_ACTION *action, float frame, int flgs)
{
	DrawAction(action, frame, flgs, 0.0, (void *)lateDrawModel);
}

// DIFF: frame: the original frame has 28 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a8a20
void late_ActionClip(NJS_ACTION *action, float frame, int flgs, float clipScl)
{
	DrawAction(action, frame, flgs, clipScl, (void *)lateDrawModel);
}

// DIFF: frame: the original frame has 28 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a8a50
void late_ActionEx(NJS_ACTION *action, float frame, int flgs)
{
	DrawAction(action, frame, flgs, 0.0f, (void *)DrawModelEx);
}

// DIFF: frame: the original frame has 28 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a8a80
void late_ActionClipEx(NJS_ACTION *action, float frame, int flgs, float clipScl)
{
	DrawAction(action, frame, flgs, clipScl, (void *)DrawModelEx);
}

// DIFF: frame: the original frame has 28 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a8ab0
void late_ActionMS(NJS_ACTION *action, float frame, int flgs)
{
	DrawAction(action, frame, flgs, 0.0, (void *)DrawModelMS);
}

// DIFF: frame: the original frame has 28 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a8ae0
void late_ActionClipMS(NJS_ACTION *action, float frame, int flgs, float clipScl)
{
	DrawAction(action, frame, flgs, clipScl, (void *)DrawModelMS);
}

// DIFF: frame: the original frame has 28 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a8b10
void late_ActionMesh(NJS_ACTION *action, float frame, int flgs)
{
	DrawAction(action, frame, flgs, 0.0, (void *)DrawModelMesh);
}

// DIFF: frame: the original frame has 28 more bytes; their source is unknown.
// FUNCTION: SADX 0x004a8b40
void late_ActionClipMesh(NJS_ACTION *action, float frame, int flgs, float clipScl)
{
	DrawAction(action, frame, flgs, clipScl, (void *)DrawModelMesh);
}

// STUB: SADX 0x004a8b70
void njShapeData0(struct obj *obj)
{
}

// STUB: SADX 0x004a8de0
float GetKeyframeData(const struct NJS_MKEY_P *key, unsigned long keyno, unsigned long n, float **dst1, float **dst2)
{
	return (float)0;
}

// FUNCTION: SADX 0x004a8e90
void FUN_004a8e90(float *param_1, float *param_2, float *param_3, float param_4)
{
	*param_3 = (1.0 - param_4) * *param_1 + *param_2 * param_4;
	param_3[1] = (1.0 - param_4) * param_1[1] + param_2[1] * param_4;
	param_3[2] = (1.0 - param_4) * param_1[2] + param_2[2] * param_4;
}

// STUB: SADX 0x004a8ef0
void njShapeData1n(struct obj *obj)
{
}

// FUNCTION: SADX 0x004a90c0
void InterpolatesNormal(const float *srca, const float *srcb, float *dst, float t)
{
	float local_8g;
	float local_cg;

	dst[0] = (1.0f - t) * srca[0] + srcb[0] * t;
	dst[1] = (1.0f - t) * srca[1] + srcb[1] * t;
	dst[2] = (1.0f - t) * srca[2] + srcb[2] * t;
	local_8g = dst[0] * dst[0] + dst[1] * dst[1] + dst[2] * dst[2];
	if (local_8g > 1e-5f)
	{
		local_cg = 1.0f / sqrtf(local_8g);
		dst[0] = dst[0] * local_cg;
		dst[1] = dst[1] * local_cg;
		dst[2] = dst[2] * local_cg;
	}
	else
	{
		dst[0] = 0.0f;
		dst[1] = 0.0f;
		dst[2] = 1.0f;
	}
}

// STUB: SADX 0x004a9660
void DrawShapeMotion(struct obj *object, struct NJS_MOTION *motion, struct NJS_MOTION *shape, float frame, int flgs, float clpScl, void *drawModel)
{
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
	DAT_05b39e78[DAT_05b39db8](obj);
	DAT_05b39e08[DAT_05b39db8](obj);
	DAT_05b3dee4[DAT_05b39db8](obj);
}

// FUNCTION: SADX 0x004a9b00
void MotLnkData1(struct obj *obj)
{
	int local_8;
	local_8 = *(int *)DAT_05b39e30[DAT_05b39db8];
	*(int *)(DAT_05b39e30[DAT_05b39db8] + 0x14) = local_8;
	*(int *)(DAT_05b39e30[DAT_05b39db8] + 0x18) = local_8 + 4;
	*(int *)(DAT_05b39e30[DAT_05b39db8] + 8) = 0;
	DAT_05b39e78[DAT_05b39db8](obj);
	DAT_05b39e08[DAT_05b39db8](obj);
	DAT_05b3dee4[DAT_05b39db8](obj);
	local_8 += 8;
	*(int *)DAT_05b39e30[DAT_05b39db8] = local_8;
}

// FUNCTION: SADX 0x004a9bb0
void MotLnkData2(struct obj *obj)
{
	int local_8;
	local_8 = *(int *)DAT_05b39e30[DAT_05b39db8];
	*(int *)(DAT_05b39e30[DAT_05b39db8] + 0x14) = local_8;
	*(int *)(DAT_05b39e30[DAT_05b39db8] + 0x18) = local_8 + 8;
	*(int *)(DAT_05b39e30[DAT_05b39db8] + 8) = 0;
	DAT_05b39e78[DAT_05b39db8](obj);
	DAT_05b39e08[DAT_05b39db8](obj);
	DAT_05b3dee4[DAT_05b39db8](obj);
	local_8 = local_8 + 0x10;
	*(int *)DAT_05b39e30[DAT_05b39db8] = local_8;
}

// FUNCTION: SADX 0x004a9c60
void MotLnkData3(struct obj *obj)
{
	int local_8;
	local_8 = *(int *)DAT_05b39e30[DAT_05b39db8];
	*(int *)(DAT_05b39e30[DAT_05b39db8] + 0x14) = local_8;
	*(int *)(DAT_05b39e30[DAT_05b39db8] + 0x18) = local_8 + 0xc;
	*(int *)(DAT_05b39e30[DAT_05b39db8] + 8) = 0;
	DAT_05b39e78[DAT_05b39db8](obj);
	DAT_05b39e08[DAT_05b39db8](obj);
	DAT_05b3dee4[DAT_05b39db8](obj);
	local_8 += 0x18;
	*(int *)DAT_05b39e30[DAT_05b39db8] = local_8;
}

// FUNCTION: SADX 0x004a9d10
void MotLnkData4(struct obj *obj)
{
	int local_8;

	local_8 = *(int *)DAT_05b39e30[DAT_05b39db8];
	*(int *)(DAT_05b39e30[DAT_05b39db8] + 0x14) = local_8;
	*(int *)(DAT_05b39e30[DAT_05b39db8] + 0x18) = local_8 + 0x10;
	*(int *)(DAT_05b39e30[DAT_05b39db8] + 8) = 0;
	DAT_05b39e78[DAT_05b39db8](obj);
	DAT_05b39e08[DAT_05b39db8](obj);
	DAT_05b3dee4[DAT_05b39db8](obj);
	local_8 = local_8 + 0x20;
	*(int *)DAT_05b39e30[DAT_05b39db8] = local_8;
}

// FUNCTION: SADX 0x004a9dc0
void ___dsDrawMotionLink(struct obj *object, struct NJS_MOTION_LINK *motionlink, float frame)
{
	DrawMotionLink(object, motionlink, frame, 0, 0.0f, ___DrawModel);
}

// STUB: SADX 0x004aa160
void FUN_004aa160(int param_1)
{
}

// STUB: SADX 0x004aa2b0
void FUN_004aa2b0(int param_1, int param_2, unsigned int param_3, float *param_4)
{
}

// STUB: SADX 0x004aa390
void FUN_004aa390(void *param_1)
{
}

// STUB: SADX 0x004aa630
void FUN_004aa630(int *param_1, int *param_2, int param_3, int param_4, int *param_5)
{
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
