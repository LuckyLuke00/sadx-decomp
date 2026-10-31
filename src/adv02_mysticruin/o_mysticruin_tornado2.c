#include "decls.h"
static void Tornado2Displayer(struct task *tp);
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

// FUNCTION: SADX 0x006b0a90
void ObjectMysticRuinTornado2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if ((char)DAT_05b9d744 == 2)
	{
		if (var1->mode == 0)
		{
			tp->disp = Tornado2Displayer;
			var1->mode = 1;
		}
		Tornado2Displayer(tp);
	}
}
