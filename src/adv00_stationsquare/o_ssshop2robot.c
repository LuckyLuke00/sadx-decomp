#include "decls.h"
static void Disp(struct task *tp);

// FUNCTION: SADX 0x0068c580
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp) != 0)
	{
		return;
	}
	if (DAT_05b9d838 != 0)
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
	ds_DrawObjectClip(object_ssobj_shop2robot_shop2robot, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0068c5f0
void ObjectSSShop2robot(struct task *tp)
{
	tp->twp->mode = 0;
	tp->exec = Disp;
	tp->disp = Disp;
}
