#include "decls.h"
extern int DAT_060eeac8;
extern struct obj *DAT_060eea9c;

// FUNCTION: SADX 0x006b0a20
void Tornado2Displayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	___njSetTexture(*(struct NJS_TEXLIST **)((char *)DAT_060eeac8 + 0xc));
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	___dsDrawObject(*(struct obj **)((char *)DAT_060eea9c + 0x20));
	njPopMatrix(1);
}

// STUB: SADX 0x006b0a90
void ObjectMysticRuinTornado2(struct task *tp)
{
}
