#include "decls.h"
static void Disp(struct task *tp);

// FUNCTION: SADX 0x0068c4f0
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp))
	{
		return;
	}
	if (DAT_05b9d838)
	{
		return;
	}
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	SetObjectTexture();
	ds_DrawObjectClip((struct obj *)&object_ssobj_shop2frame_shop2frame, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0068c560
void ObjectSSShop2frame(struct task *tp)
{
	tp->twp->mode = 0;
	tp->exec = Disp;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
