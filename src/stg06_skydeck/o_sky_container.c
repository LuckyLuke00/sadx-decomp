#include "decls.h"

// FUNCTION: SADX 0x008445e0
void dispSkyContainer(struct task *tp)
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
		njRotateY(0, (Uint16)var1->ang.y);
	}
	SetObjectTexture();
	ds_DrawObjectClip((struct obj *)var1->timer.ptr, 1.0f);
	njPopMatrix(1);
}
