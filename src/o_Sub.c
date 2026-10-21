#include "decls.h"
#include <stdlib.h>
extern struct obj object_Arrow_Y;
extern struct obj object_Arrow_Z;
extern int DAT_05b9d838;
extern struct obj object_sphere01;

// FUNCTION: SADX 0x0056e500
void DispVectorXYV(struct NJS_POINT3 *bp, struct NJS_POINT3 *vec)
{
	long ang[3];
	float local_18;

	if (DAT_05b9d838 != 0)
		return;
	local_18 = njSqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	GetAngleXYV(vec, &ang[0], &ang[1]);
	njPushMatrix(0);
	njTranslateV(0, bp);
	if (ang[0] != 0)
		njRotateX(0, (unsigned short)ang[0]);
	if (ang[1] != 0)
		njRotateY(0, (unsigned short)ang[1]);
	FUN_0067d2d0(0, 1.0f, 1.0f, local_18);
	___dsDrawObject(&object_Arrow_Z);
	njPopMatrix(1);
}

// STUB: SADX 0x0056e600
void GetAngleXYV(const struct NJS_POINT3 *vec, long *ang_x, long *ang_y)
{
}

// FUNCTION: SADX 0x0056e6a0
void DispVectorZXV(struct NJS_POINT3 *bp, struct NJS_POINT3 *vec)
{
	long ang[3];
	float local_18;

	if (DAT_05b9d838 != 0)
		return;
	local_18 = njSqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	GetAngleZXV(vec, &ang[0], &ang[2]);
	njPushMatrix(0);
	njTranslateV(0, bp);
	if (ang[2] != 0)
		njRotateZ(0, (unsigned short)ang[2]);
	if (ang[0] != 0)
		njRotateX(0, ang[0]);
	FUN_0067d2d0(0, 1.0f, local_18, 1.0f);
	___dsDrawObject(&object_Arrow_Y);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0056e7a0
void DispSphere(struct NJS_POINT3 *bp, float scale)
{
	if (DAT_05b9d838 != 0)
		return;
	scale = scale * 0.1f;
	njPushMatrix(0);
	njTranslateV(0, bp);
	FUN_0067d2d0(0, scale, scale, scale);
	___dsDrawObject(&object_sphere01);
	njPopMatrix(1);
}

// STUB: SADX 0x0056e810
long ChkItemInPercent(float *tbl)
{
	return (long)0;
}

// STUB: SADX 0x0056e890
long MakePopUpItem(struct taskwk *twp, long kind)
{
	return (long)0;
}

// FUNCTION: SADX 0x0056e990
struct obj *EntryMobileLandCollsion(struct task *tp, struct NJS_MODEL *model)
{
	struct obj *local_cg;
	struct taskwk *local_8g;

	local_8g = tp->twp;
	local_cg = GetMobileLandObject();
	if (local_cg != 0)
	{
		local_cg->evalflags = 0x10;
		local_cg->scl[0] = 1.0f;
		local_cg->scl[1] = 1.0f;
		local_cg->scl[2] = 1.0f;
		local_cg->pos[0] = local_8g->pos.x;
		local_cg->pos[1] = local_8g->pos.y;
		local_cg->pos[2] = local_8g->pos.z;
		local_cg->ang[0] = local_8g->ang.x;
		local_cg->ang[1] = local_8g->ang.y;
		local_cg->ang[2] = local_8g->ang.z;
		local_cg->model = model;
		local_cg->child = 0;
		local_cg->sibling = 0;
		RegisterCollisionEntry(0, tp, local_cg);
		return local_cg;
	}
	local_8g->btimer = local_8g->btimer | 2;
	return 0;
}

// STUB: SADX 0x0056ea70
void SetMobileLandCollsionData(struct taskwk *twp, struct obj *op)
{
}

// STUB: SADX 0x0056eb30
void CharColliOn(struct taskwk *twp)
{
}

// STUB: SADX 0x0056eb90
void CharColliOff(struct taskwk *twp)
{
}

// STUB: SADX 0x0056ebf0
void LoopAnimation(struct NJS_ACTION *anm, float *fnum, float anm_speed)
{
}

// STUB: SADX 0x0056ec80
long csnDistPlayer(struct NJS_POINT3 *my_pos, float rad)
{
	return (long)0;
}

// STUB: SADX 0x0056ee90
long ChkParabolaEnd(struct sParabola *para)
{
	return (long)0;
}
