#include "decls.h"

// FUNCTION: SADX 0x00875a80
void Display(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture2(0xc);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.z != 0)
		{
			njRotateZ(NULL, (unsigned short)var1->ang.z);
		}
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		FUN_0067d2d0((float *)0, var1->scl.x, 1.0f, 1.0f);
		ds_DrawObjectClip((struct obj *)&object_cas_hashgo_hashgo, var1->scl.x > 1.0f ? var1->scl.x : 1.0f);
		njPopMatrix(1);
	}
}
