#include "decls.h"

// FUNCTION: SADX 0x00817390
void dispCatapult(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	___dsAction((struct NJS_ACTION *)var1->timer.ptr, var1->scl.y, 1.0f);
	njPopMatrix(1);
}
