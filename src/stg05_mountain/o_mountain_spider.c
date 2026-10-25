#include "decls.h"
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);
extern struct NJS_TEXLIST texlist_obj_mountain;

// FUNCTION: SADX 0x0082fac0
void DrawMtnSpiderA(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	float var2 = var1->scl.x;
	if (dsCheckViewV(&var1->pos, 10.0f))
	{
		___njSetTexture(&texlist_obj_mountain);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(0, *(unsigned short *)((char *)var1 + 0x1c));
		}
		if (var1->ang.x != 0)
		{
			njRotateX(0, var1->ang.x);
		}
		FUN_0067d2d0(0, var2, var2, var2);
		___dsAction((struct NJS_ACTION *)(*(int *)((char *)var1 + 8)), var1->timer.f, var2);
		njPopMatrix(1);
		if (var1->value.ptr != 0)
		{
			___njDrawLine3D((struct NJS_POINT3COL *)var1->value.ptr, 1, 0x40);
		}
	}
}

// STUB: SADX 0x0082fb90
void DstrMtnSpiderA(struct task *p_task)
{
}

// FUNCTION: SADX 0x0082fd90
void DrawMtnSpiderB(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	float var2 = var1->scl.x;
	if (dsCheckViewV(&var1->pos, 10.0f))
	{
		___njSetTexture(&texlist_obj_mountain);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(0, *(unsigned short *)((char *)var1 + 0x1c));
		}
		if (var1->ang.x != 0)
		{
			njRotateX(0, var1->ang.x);
		}
		if (var1->ang.y != 0)
		{
			njRotateY(0, var1->ang.y);
		}
		FUN_0067d2d0(0, var2, var2, var2);
		___dsAction((struct NJS_ACTION *)(*(int *)((char *)var1 + 8)), var1->timer.f, var2);
		njPopMatrix(1);
	}
}
