#include "decls.h"

// FUNCTION: SADX 0x0083fb10
void ObjectSkydeck_crane_Draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 400.0f))
	{
		___njSetTexture(&texlist_obj_skydeck);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y)
		{
			njRotateY(0, var1->ang.y);
		}
		ds_DrawObjectClip(object_skymain_kr_skymain_kr, 1.0f);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x0083fd10
void ObjectSkydeck_crane_hang_Draw(struct task *tp)
{
}
