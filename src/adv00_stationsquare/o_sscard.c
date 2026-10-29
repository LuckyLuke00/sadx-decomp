#include "decls.h"

// FUNCTION: SADX 0x0068c8d0
void dispSSCard(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	SetObjectTexture();
	ds_ActionClip((struct NJS_ACTION *)var1->counter.ptr, var1->timer.f, 1.0f);
	njPopMatrix(1);
}
