#include "decls.h"

// FUNCTION: SADX 0x00703e40
void dispChaos7Panel(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	SetRegularTexture();
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
	if (var1->ang.y + 0x8000 != 0)
	{
		njRotateY(NULL, (unsigned short)((short)var1->ang.y + -0x8000));
	}
	FUN_004a88c0((NJS_ACTION *)var1->counter.ptr, var1->timer.f);
	njPopMatrix(1);
}
