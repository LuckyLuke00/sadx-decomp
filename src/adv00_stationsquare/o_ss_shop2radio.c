#include "decls.h"
static void Disp(struct task *tp);

// FUNCTION: SADX 0x0068c610
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
		njRotateY(0, (Uint16)var1->ang.y);
	}
	ds_DrawObjectClip(object_ssobj_shop2_radio_shop2_radio, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0068c680
void ObjectSSShop2radio(struct task *tp)
{
	tp->exec = Disp;
	tp->disp = Disp;
}
