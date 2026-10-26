#include "decls.h"
extern struct NJS_TEXLIST texlist_fountain[8];
extern int DAT_05b9d838;
float FUN_004a1e90(float *param_1);
void late_DrawObjectClipMesh(struct obj *obj, int flgs, float clipScl);

// FUNCTION: SADX 0x00825350
void calcPushUp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct anywk *var2 = tp->awp;
	struct NJS_POINT3 p;
	p.x = 0.0f;
	p.y = 6.0f;
	p.z = -6.0f;
	if (var1->scl.x != 0.0f || var1->scl.y != 0.0f || var1->scl.z != 0.0f)
	{
		p.x = var1->scl.x;
		p.y = var1->scl.y;
		p.z = var1->scl.z;
	}
	njPushMatrix(_nj_unit_matrix_);
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ(0, *(unsigned short *)((char *)var1 + 0x1c));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX(0, *(unsigned short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY(0, *(unsigned short *)((char *)var1 + 0x18));
	}
	njCalcPoint(0, &p, (struct NJS_POINT3 *)var2);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00825700
void dispStream(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_fountain[tp->ptp->twp->btimer]);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	njScaleV(0, &var1->scl);
	late_DrawObjectClipMesh((struct obj *)var1->counter.l, 0, FUN_004a1e90((float *)&var1->scl));
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00825800
void dispRibon(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_fountain[tp->ptp->twp->btimer]);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY(0, *(unsigned short *)((char *)var1 + 0x18));
	}
	njScaleV(0, &var1->scl);
	late_DrawObjectClipMesh((struct obj *)var1->counter.l, 0, FUN_004a1e90((float *)&var1->scl));
	njPopMatrix(1);
}
