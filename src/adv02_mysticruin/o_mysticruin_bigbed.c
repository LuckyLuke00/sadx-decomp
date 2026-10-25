#include "decls.h"
extern struct obj *DAT_060eea9c;

// FUNCTION: SADX 0x006b3550
void BedDisplayer(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(0, var1->ang.y);
	}
	ds_DrawObjectClip(*(struct obj **)((char *)DAT_060eea9c + 0x188), 1.0f);
	njPopMatrix(1);
}
