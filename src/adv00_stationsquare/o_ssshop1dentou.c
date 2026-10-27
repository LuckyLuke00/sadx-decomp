#include "decls.h"

// FUNCTION: SADX 0x0068d1d0
void dispSSShop1Dentou(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	___njSetTexture((struct NJS_TEXLIST *)var1->value.ptr);
	ds_DrawObjectClip((struct obj *)var1->counter.ptr, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x0068d300
void ObjectSSShop1Dentou(struct task *tp)
{
}
