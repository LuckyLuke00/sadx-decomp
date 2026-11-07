#include "decls.h"

// FUNCTION: SADX 0x00702aa0
void destChaos7Float(struct task *tp)
{
	FreeTask(tp);
}

// FUNCTION: SADX 0x00702ab0
void dispChaos7Float(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	SetObjectTexture();
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (var1->ang.z != 0)
	{
		njRotateZ(NULL, (unsigned short)(short)var1->ang.z);
	}
	if (var1->ang.y != 0)
	{
		njRotateY(NULL, (unsigned short)var1->ang.y);
	}
	ds_DrawObjectClip((struct obj *)var1->counter.ptr, 1.0f);
	njPopMatrix(1);
}
