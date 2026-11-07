#include "decls.h"
extern int DAT_05b9d838;

// FUNCTION: SADX 0x00842d60
void dispTPFoothold(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.z != 0)
		{
			njRotateZ(NULL, (unsigned short)(short)var1->ang.z);
		}
		if (var1->ang.x != 0)
		{
			njRotateX(NULL, (unsigned short)var1->ang.x);
		}
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		SetObjectTexture();
		ds_DrawObjectClip((struct obj *)var1->timer.ptr, 1.0f);
		njPopMatrix(1);
	}
}
