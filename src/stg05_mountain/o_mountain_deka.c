#include "decls.h"

// FUNCTION: SADX 0x0082d340
void Object_Mountain_Deka_Display(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->timer.ptr = &object_taoreiwam_clkiri_iwa0a_iwa0a;

	if (dsCheckViewV(&var1->pos, 1500.0f))
	{
		float var2 = var1->scl.z;

		if (var2 >= 59.0f)
		{
			var2 = 59.0f;
		}
		___njSetTexture(&texlist_obj_mountain);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y)
		{
			njRotateY(0, var1->ang.y);
		}
		FUN_0067d2d0(0, 0.1f, 0.1f, 0.1f);
		dsScaleLight(0.1f);
		___dsAction(action_taoreiwam_dai, var2 * 2.0f, 0.1f);
		dsReScaleLight();
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x0082d530
void GCInit_DownDeka(struct task *tp)
{
	struct obj *var1;
	struct taskwk *var2;

	var2 = tp->twp;
	var1 = GetMobileLandObject();
	var2->counter.ptr = var1;
	var1->scl[0] = 0.1f;
	var1->scl[1] = 0.1f;
	var1->evalflags = 0x10;
	var1->scl[2] = 0.1f;
	var1->ang[0] = var2->ang.x;
	var1->ang[1] = var2->ang.y;
	var1->ang[2] = var2->ang.z;
	var1->pos[0] = var2->pos.x;
	var1->pos[1] = var2->pos.y + 60.0;
	var1->pos[2] = var2->pos.z;
	var1->model = *(struct NJS_MODEL **)((char *)var2->timer.ptr + 4);
	var1->child = *(struct obj **)((char *)var2->timer.ptr + 0x2c);
	var1->sibling = *(struct obj **)((char *)var2->timer.ptr + 0x30);
	RegisterCollisionEntry(0x8000000, tp, var1);
}
