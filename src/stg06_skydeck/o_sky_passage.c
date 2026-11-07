#include "decls.h"
extern int DAT_05b9d838;

// FUNCTION: SADX 0x00841530
void dispSkyPassageWMotion(struct task *tp)
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
		ds_ActionClip((struct NJS_ACTION *)((int)var1->counter.l), var1->timer.f, 1.0);
		njPopMatrix(1);
		if (FUN_004c39c0(tp) == 0)
		{
			float var2 = var1->timer.f + 1.0;
			var1->timer.f = var2;
			struct NJS_MOTION *var3 = *(struct NJS_MOTION **)((char *)(var1->counter.ptr) + 4);
			if ((float)(unsigned int)var3->nbFrame <= var2)
			{
				var1->timer.f = 0.0f;
			}
		}
	}
}
