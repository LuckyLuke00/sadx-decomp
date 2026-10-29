#include "decls.h"
extern int DAT_05b9d838;

// FUNCTION: SADX 0x00841530
void dispSkyPassageWMotion(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		njPushMatrix(NULL);
		njTranslateV((float *)0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		SetObjectTexture();
		ds_ActionClip((struct NJS_ACTION *)(*(int *)((char *)var1 + 8)), *(float *)((char *)var1 + 0xc), 1.0);
		njPopMatrix(1);
		if (FUN_004c39c0(tp) == 0)
		{
			float var2 = *(float *)((char *)var1 + 0xc) + 1.0;
			*(float *)((char *)var1 + 0xc) = var2;
			struct NJS_MOTION *var3 = *(struct NJS_MOTION **)((char *)(*(void **)((char *)var1 + 8)) + 4);
			if ((float)(unsigned int)var3->nbFrame <= var2)
			{
				*(float *)((char *)var1 + 0xc) = 0.0f;
			}
		}
	}
}
