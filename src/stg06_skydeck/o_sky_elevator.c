#include "decls.h"

// FUNCTION: SADX 0x00842940
void dispSkyEV(struct task *tp)
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
	late_DrawObjectClipEx((struct obj *)var1->timer.ptr, 1, 1.0f);
	njPopMatrix(1);
}
