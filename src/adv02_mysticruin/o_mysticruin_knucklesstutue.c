#include "decls.h"

// FUNCTION: SADX 0x006b5950
void KnucklesStutueDisplayer(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	FUN_004a88c0(*(NJS_ACTION **)((char *)DAT_060eeaac + 0x20), var1->value.f);
	njPopMatrix(1);
}
