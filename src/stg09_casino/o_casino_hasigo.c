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
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(NULL, *(unsigned short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		FUN_0067d2d0((float *)0, var1->scl.x, 1.0f, 1.0f);
		ds_DrawObjectClip((struct obj *)&object_cas_hashgo_hashgo, var1->scl.x > 1.0f ? var1->scl.x : 1.0f);
		njPopMatrix(1);
	}
}
