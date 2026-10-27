#include "decls.h"
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);

// FUNCTION: SADX 0x008362c0
void Mountain_Honoo_Fire(struct task *tp, struct NJS_POINT3 tmpp, struct NJS_POINT3 tmpv, float f)
{
	struct taskwk *local_8 = tp->twp;
	struct NJS_POINT3 local_14;
	struct NJS_POINT3 local_20;
	njPushMatrix(_nj_unit_matrix_);
	njTranslateV(0, &local_8->pos);
	if (local_8->ang.y)
	{
		njRotateY(0, local_8->ang.y);
	}
	FUN_0067d2d0(0, local_8->scl.x, local_8->scl.x, local_8->scl.x);
	njCalcPoint(0, &tmpp, &local_14);
	njCalcVector(0, &tmpv, &local_20);
	njPopMatrix(1);
	CreateFire(&local_14, &local_20, f);
}

// FUNCTION: SADX 0x008363b0
void o_mountain_honoo_Display(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 100.0f))
	{
		___njSetTexture(&texlist_obj_mountain);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y)
		{
			njRotateY(0, var1->ang.y);
		}
		FUN_0067d2d0(0, var1->scl.x, var1->scl.x, var1->scl.x);
		dsScaleLight(var1->scl.x);
		ds_ActionClip((struct NJS_ACTION *)var1->counter.ptr, (float)var1->wtimer, var1->scl.x);
		dsReScaleLight();
		njPopMatrix(1);
	}
}
