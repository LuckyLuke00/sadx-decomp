#include "decls.h"
static void Disp(struct task *tp);

// FUNCTION: SADX 0x0068c690
static void Disp(struct task *tp)
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
	ds_DrawObjectClip(object_ssobj_shop2_kaseki_shop2_kaseki, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0068c700
void ObjectSSShop2kaseki(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->ang.x = 0;
	*(long *)((char *)var1 + 0x1c) = 0;
	tp->exec = Disp;
	tp->disp = Disp;
}
