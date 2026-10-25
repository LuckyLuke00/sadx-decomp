#include "decls.h"
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);

// FUNCTION: SADX 0x008355e0
void DrawBonehead(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (dsCheckViewV(&var1->pos, 20.0f))
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
		FUN_0067d2d0(0, var1->scl.x + 1.0f, var1->scl.x + 1.0f, var1->scl.x + 1.0f);
		ds_DrawModelClip((struct NJS_MODEL *)&model_haka1a_gaikotu_gaikotu, var1->scl.x + 1.0f);
		njPopMatrix(1);
	}
}
