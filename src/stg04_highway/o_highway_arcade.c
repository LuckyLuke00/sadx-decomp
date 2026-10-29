#include "decls.h"

// FUNCTION: SADX 0x00821e60
void ArcadeDisplayer(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	late_DrawObject((struct obj *)var1->counter.ptr, 1);
	njPopMatrix(1);
}
