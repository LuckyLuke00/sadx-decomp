#include "decls.h"
extern int DAT_05b9d838;
extern struct obj object_ssobj_shop2boxfuta_shop2boxfuta[];
static void Disp(struct task *tp);

// FUNCTION: SADX 0x0068bb20
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp) == 0 && DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y)
		{
			njRotateY(0, var1->ang.y);
		}
		ds_DrawObjectClip(object_ssobj_shop2boxfuta_shop2boxfuta, 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x0068bb90
void ObjectSSShop2boxfuta(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->ang.x = 0;
	*(long *)((char *)var1 + 0x1c) = 0;
	var1->mode = 0;
	tp->exec = Disp;
	tp->disp = Disp;
}
