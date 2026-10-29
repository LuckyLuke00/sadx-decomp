#include "decls.h"

// FUNCTION: SADX 0x00703e40
void dispChaos7Panel(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	SetRegularTexture();
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x18) + 0x8000 != 0)
	{
		njRotateY(NULL, (unsigned short)(*(short *)((char *)var1 + 0x18) + -0x8000));
	}
	FUN_004a88c0((NJS_ACTION *)var1->counter.ptr, var1->timer.f);
	njPopMatrix(1);
}
