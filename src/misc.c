#include "decls.h"
extern float DAT_05b9d860;
void njGetMatrix(float *param_1);
void njSetMatrix(float *param_1, float *param_2);
struct obj *scanObjectSub(float **mbp, struct obj *obj, float *m);
extern int DAT_0629c6c8;
extern int DAT_05b9e064;
extern int DAT_0629c540;
extern int DAT_0629c6c4;
extern int DAT_05b9e060;
extern int DAT_05b9e068;
extern "C" double floor(double param_1);

// FUNCTION: SADX 0x004cb9c0
long AdjustAngle(long ang0, long ang1, long dang)
{
	short local_8;
	ang0 &= 0xffff;
	ang1 &= 0xffff;
	local_8 = (short)(ang1 - ang0);
	if (local_8 <= dang && local_8 >= -dang)
	{
		return ang1;
	}
	if (local_8 & 0x8000)
	{
		local_8 = (short)(ang0 - dang);
	}
	else
	{
		local_8 = (short)(ang0 + dang);
	}
	return local_8 & 0xffff;
}

// FUNCTION: SADX 0x004cba30
long SubAngle(long ang0, long ang1)
{
	ang0 &= 0xffff;
	ang1 &= 0xffff;
	short local_8 = (short)(ang1 - ang0);
	return (long)local_8;
}

// FUNCTION: SADX 0x004cba60
long DiffAngle(long ang0, long ang1)
{
	ang0 &= 0xffff;
	ang1 &= 0xffff;
	short local_8 = (short)(ang1 - ang0);
	if (local_8 < 0)
	{
		local_8 = -local_8;
	}
	return local_8 & 0xffff;
}

// FUNCTION: SADX 0x004cbab0
long CreateNinjaAngle(long ang0, long ang1)
{
	long local_8;

	local_8 = SubAngle(ang0, ang1);
	if (local_8 > 0)
	{
		local_8 = ang1;
		while (ang0 > local_8)
		{
			local_8 += 0x10000;
		}
	}
	else if (local_8 < 0)
	{
		local_8 = ang1;
		while (ang0 < local_8)
		{
			local_8 -= 0x10000;
		}
	}
	else
	{
		local_8 = ang0;
	}
	return local_8;
}

// FUNCTION: SADX 0x004cbd30
void InterpolateModel(struct NJS_MODEL *op, struct NJS_MODEL *np, struct NJS_MODEL *dp, float rate)
{
	long local_14;
	struct NJS_POINT3 *local_ci;
	struct NJS_POINT3 *local_10;
	struct NJS_POINT3 *local_8g;
	local_14 = op->nbPoint;
	local_ci = op->points;
	local_10 = np->points;
	local_8g = dp->points;
	InterpolatePointAsSin(local_ci, local_10, local_8g, rate, local_14);
	CalculatePlaneNormals(dp);
	CalculatePointNormals(dp);
}

// STUB: SADX 0x004cbe70
void InterpolatePointAsSin(struct NJS_POINT3 *opp, struct NJS_POINT3 *npp, struct NJS_POINT3 *dpp, float ang, unsigned long nbPoint)
{
}

// FUNCTION: SADX 0x004ccaf0
long SearchTheObjectTreeForTheObject(struct obj *pobj, struct obj *obj)
{
	long num = 0;
	struct obj *local_cg = pobj;
	local_cg = SearchTheObjectForTheObject(local_cg, obj, &num);
	if (local_cg == 0)
	{
		return -1;
	}
	else
	{
		return num;
	}
}

// STUB: SADX 0x004ccb30
struct obj *SearchTheObjectForTheObject(struct obj *pobj, struct obj *obj, long *pnum)
{
	return (struct obj *)0;
}

// FUNCTION: SADX 0x004ccbd0
float GetFloatMod(float dividend, float divisor)
{
	float local_8g;
	float local_cj;
	if (divisor == 0.0f)
	{
		return 0.0f;
	}
	local_8g = (float)floor(dividend / divisor);
	local_cj = dividend - local_8g * divisor;
	return local_cj;
}

// STUB: SADX 0x004ccc60
int FUN_004ccc60(int param_1, int *param_2)
{
	return (int)0;
}

// FUNCTION: SADX 0x004cce50
void SaveConstantAttr()
{
	DAT_05b9e068 = DAT_0629c540;
	DAT_05b9e060 = DAT_0629c6c4;
}

// FUNCTION: SADX 0x004cce70
void LoadConstantAttr()
{
	DAT_0629c540 = DAT_05b9e068;
	DAT_0629c6c4 = DAT_05b9e060 | 0x800000;
}

// FUNCTION: SADX 0x004ccea0
void OnConstantAttr(unsigned long soc_and, unsigned long soc_or)
{
	DAT_0629c540 = DAT_0629c540 | soc_and;
	DAT_0629c6c4 = soc_or | 0x800000 | DAT_0629c6c4;
}

// FUNCTION: SADX 0x004cced0
void OffConstantAttr(unsigned long soc_and, unsigned long soc_or)
{
	DAT_0629c540 &= ~(int)soc_and;
	DAT_0629c6c4 &= ~(int)soc_or;
}

// FUNCTION: SADX 0x004ccf00
void SaveControl3D()
{
	DAT_05b9e064 = DAT_0629c6c8;
}

// FUNCTION: SADX 0x004ccf10
void LoadControl3D()
{
	DAT_0629c6c8 = DAT_05b9e064;
}

// FUNCTION: SADX 0x004ccf20
void OnControl3D(unsigned long flag)
{
	DAT_0629c6c8 |= flag;
}

// FUNCTION: SADX 0x004ccf40
void OffControl3D(unsigned long flag)
{
	DAT_0629c6c8 &= ~(int)flag;
}

// FUNCTION: SADX 0x004ccf60
long MSetPosition(struct NJS_POINT3 *p, struct NJS_POINT3 *v, struct Angle3 *a, float r)
{
	return MSetPositionWIgnoreAttribute(p, v, a, 0, r) != 0;
}

// FUNCTION: SADX 0x004ccf90
long MSetPositionIgnoreAttribute(struct NJS_POINT3 *p, struct NJS_POINT3 *v, struct Angle3 *a, long attrmask, float r)
{
	return (MSetPositionWIgnoreAttribute(p, v, a, attrmask, r) != 0);
}

// FUNCTION: SADX 0x004cd480
void setObjFlags(struct obj **obj, unsigned long flag)
{
	while (*obj != 0)
	{
		(*obj)->evalflags |= flag;
		obj++;
	}
}

// FUNCTION: SADX 0x004cd4b0
void clrObjFlags(struct obj **obj, unsigned long flag)
{
	while (*obj != 0)
	{
		(*obj)->evalflags &= ~flag;
		obj++;
	}
}

// FUNCTION: SADX 0x004cd600
float *getObjectMatrix(float *mat, struct obj *obj, int num)
{
	float tmp[16];
	float *mbp;

	if (mat == 0)
	{
		njGetMatrix(tmp);
	}
	else
	{
		njSetMatrix(tmp, mat);
	}
	mbp = &DAT_05b9d860;
	scanObjectSub(&mbp, obj, tmp);
	return (float *)((char *)&DAT_05b9d860 + num * 64);
}

// FUNCTION: SADX 0x004cd670
void getObjectMatrixBuf(float *mat, int num)
{
	njSetMatrix(mat, (float *)((char *)&DAT_05b9d860 + num * 64));
}

// FUNCTION: SADX 0x004cd690
void initSpriteSub(struct NJS_SPRITE *sp, const struct NJS_TEXLIST *list, const struct NJS_TEXANIM *anim)
{
	sp->tlist = (struct NJS_TEXLIST *)list;
	sp->tanim = (struct NJS_TEXANIM *)anim;
	sp->ang = 0;
	sp->sx = 1.0f;
	sp->sy = 1.0f;
	sp->p.x = 0.0f;
	sp->p.y = 0.0f;
	sp->p.z = 0.0f;
}

// FUNCTION: SADX 0x004cdab0
char *FUN_004cdab0(char *param_1, unsigned int param_2)
{
	do
	{
		param_1--;
		*param_1 = (char)((param_2 % 10) + 0x30);
		param_2 = param_2 / 10;
	}
	while (param_2 != 0);
	return param_1;
}

// FUNCTION: SADX 0x004cdaf0
char *FUN_004cdaf0(char *param_1, unsigned int param_2)
{
	int local_8;
	do
	{
		local_8 = param_2 & 0xf;
		param_1--;
		*param_1 = (local_8 < 10 ? 0x30 : 0x57) + local_8;
		param_2 >>= 4;
	}
	while (param_2 != 0);
	return param_1;
}

// FUNCTION: SADX 0x004cdb40
char *FUN_004cdb40(char *param_1, unsigned int param_2)
{
	int local_8;
	do
	{
		local_8 = param_2 & 0xf;
		param_1--;
		*param_1 = (local_8 < 10 ? 0x30 : 0x37) + local_8;
		param_2 >>= 4;
	}
	while (param_2 != 0);
	return param_1;
}

// FUNCTION: SADX 0x004cdb90
int SPrintf(char *s, const char *format, ...)
{
	char *args;
	int local_cg;
	args = (char *)&format + 4;
	local_cg = VSPrintf(s, format, args);
	args = (char *)0;
	return local_cg;
}

// FUNCTION: SADX 0x004cdbd0
float AdjustFloat(float f0, float f1, float df)
{
	float local_8;

	if (f0 > f1)
	{
		local_8 = f0 - df;
		if (local_8 < f1)
		{
			local_8 = f1;
		}
	}
	else if (f0 < f1)
	{
		local_8 = f0 + df;
		if (local_8 > f1)
		{
			local_8 = f1;
		}
	}
	else
	{
		local_8 = f0;
	}
	return local_8;
}
