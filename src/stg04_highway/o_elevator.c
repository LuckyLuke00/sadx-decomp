#include "decls.h"

// FUNCTION: SADX 0x00825d40
void dispElevator(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(0, var1->ang.y);
	}
	___dsDrawModel(*(struct NJS_MODEL **)((char *)var1->counter.ptr + 4));
	njPopMatrix(1);
}

// STUB: SADX 0x00825e10
void dispEvStep(struct task *tp)
{
}
