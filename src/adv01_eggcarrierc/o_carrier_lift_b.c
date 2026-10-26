#include "decls.h"
extern struct obj *DAT_060eea98;

// FUNCTION: SADX 0x0069f2c0
void LiftBDraw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	ds_DrawObjectClip(*(struct obj **)((char *)DAT_060eea98 + 0x10), 1.0f);
	njPopMatrix(1);
}
