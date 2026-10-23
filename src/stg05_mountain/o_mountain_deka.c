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
