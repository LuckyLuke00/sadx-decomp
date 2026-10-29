#include "decls.h"

// FUNCTION: SADX 0x00702ab0
void dispChaos7Float(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	SetObjectTexture();
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
	}
	ds_DrawObjectClip((struct obj *)var1->counter.ptr, 1.0f);
	njPopMatrix(1);
}
