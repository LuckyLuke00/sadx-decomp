#include "decls.h"
struct CL_ObjInfo;
struct CL_Poly;
struct CL_PolyInfo;
struct CL_PolyInfo *FUN_004fbd10(struct CL_ObjInfo *param_1, struct CL_Poly *param_2);
extern "C" double atan2(double v, double u);
extern void *DAT_05bb5620;
extern void *DAT_05bb00d8;
float njInnerProduct(struct NJS_POINT3 *param_1, struct NJS_POINT3 *param_2);
extern void FUN_004f6ef0(void);
extern void FUN_004f8070(void *param_1);
void FUN_004f76a0(void *param_1);
extern int DAT_05cb5620;
extern int DAT_05cb5624;
extern int DAT_05cb562c;
void FUN_004f6f20(void *param_1, int param_2);
void FUN_004f6f70(void *param_1, int param_2);

// STUB: SADX 0x004f6e40
long CL_ColPolListInit()
{
	return (long)0;
}

// FUNCTION: SADX 0x004f6ef0
void FUN_004f6ef0(void)
{
	FUN_004f6f20(&DAT_05bb5620, 0x4000);
	FUN_004f6f70(&DAT_05bb00d8, 0x100);
}

#pragma optimize("", off)
// STUB: SADX 0x004f6f20
void FUN_004f6f20(void *param_1, int param_2)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x004f6f70
void FUN_004f6f70(void *param_1, int param_2)
{
	int *local_8;

	DAT_05cb5624 = (int)param_1;
	local_8 = (int *)param_1 + 0x10;
	for (; param_2 > 1; param_2 = param_2 - 1, param_1 = (void *)((int)param_1 + 0x40), local_8 = local_8 + 0x10)
	{
		*(int *)param_1 = (int)local_8;
	}
	*(int *)param_1 = 0;
	DAT_05cb5620 = 0;
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

// STUB: SADX 0x004f7740
int FUN_004f7740(int *param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x004f7830
struct obj *CL_SeekObjectTree(struct obj *obp, unsigned long ulattr, struct CL_ObjInfo *oip)
{
	struct obj *local_8;

	njPushMatrix(0);
	njTranslateV(0, (struct NJS_POINT3 *)((char *)obp + 8));
	if (*(int *)((char *)obp + 0x1c) != 0)
	{
		njRotateZ(0, *(unsigned short *)((char *)obp + 0x1c));
	}
	if (*(int *)((char *)obp + 0x18) != 0)
	{
		njRotateY(0, *(unsigned short *)((char *)obp + 0x18));
	}
	if (*(int *)((char *)obp + 0x14) != 0)
	{
		njRotateX(0, *(unsigned short *)((char *)obp + 0x14));
	}
	njScaleV(0, (struct NJS_POINT3 *)((char *)obp + 0x20));
	local_8 = obp->child;
	while (local_8 != 0)
	{
		local_8 = CL_SeekObjectTree(local_8, ulattr, oip);
	}
	if (CL_ListUpPolygonsInObject(obp, ulattr, oip) == 0)
	{
		njPopMatrix(1);
		return 0;
	}
	njPopMatrix(1);
	return obp->sibling;
}

// STUB: SADX 0x004f8010
void FUN_004f8010(float param_1)
{
}

// STUB: SADX 0x004f8070
void FUN_004f8070(void *param_1)
{
}

// STUB: SADX 0x004f80e0
int FUN_004f80e0(int *param_1)
{
	return (int)0;
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

// STUB: SADX 0x004fafe0
long CL_ColPolCFPolygon(struct zxsdwstr *zss, float rad)
{
	return (long)0;
}

// STUB: SADX 0x004fb150
void FUN_004fb150(float *param_1, float *param_2, float *param_3, float *param_4)
{
}

// FUNCTION: SADX 0x004fb430
float GetInnerProduct(struct NJS_POINT3 *p0, struct NJS_POINT3 *p1, struct NJS_POINT3 *p2)
{
	struct NJS_POINT3 v0;
	struct NJS_POINT3 v1;

	v0.x = p1->x - p0->x;
	v0.y = p1->y - p0->y;
	v0.z = p1->z - p0->z;
	v1.x = p2->x - p0->x;
	v1.y = p2->y - p0->y;
	v1.z = p2->z - p0->z;
	return njInnerProduct(&v0, &v1);
}

// FUNCTION: SADX 0x004fba70
void FUN_004fba70(float *param_1, float *param_2, float *param_3)
{
	param_3[0] = param_1[1] * param_2[2] - param_1[2] * param_2[1];
	param_3[1] = param_1[2] * param_2[0] - param_1[0] * param_2[2];
	param_3[2] = param_1[0] * param_2[1] - param_1[1] * param_2[0];
}

// FUNCTION: SADX 0x004fbad0
void GetAngleZXV(const struct NJS_POINT3 *vec, long *ang_x, long *ang_z)
{
	*ang_z = -(long)(atan2(vec->x, vec->y) * 65536.0 / 6.283184);
	*ang_x = (long)(atan2(vec->z, njSqrt(vec->x * vec->x + vec->y * vec->y)) * 65536.0 / 6.283184);
	return;
}

// STUB: SADX 0x004fbb70
int FUN_004fbb70(int *param_1)
{
	return (int)0;
}

// STUB: SADX 0x004fbd10
struct CL_PolyInfo *FUN_004fbd10(struct CL_ObjInfo *obj, struct CL_Poly *poly)
{
	return (struct CL_PolyInfo *)0;
}

// STUB: SADX 0x004fcd10
void RemoveObjInfo(struct obj *pObject)
{
}
