#include "decls.h"
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);

// FUNCTION: SADX 0x0082f850
void Object_Mountain_Futa_Display(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 20.0f))
	{
		___njSetTexture(&texlist_obj_mountain);
		njPushMatrix(0);
		FUN_0067d830(0, var1->pos.x, var1->pos.y, var1->pos.z);
		if (var1->ang.y)
		{
			njRotateY(0, var1->ang.y);
		}
		ds_DrawModelClip(*(struct NJS_MODEL **)((char *)var1->counter.ptr + 4), 1.0f);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x0082fa30
void Object_Mountain_Futa(struct task *tp)
{
}
