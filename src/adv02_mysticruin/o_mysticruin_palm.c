#include "decls.h"
extern float DAT_05b3df40;
extern struct obj *DAT_060eea9c;
extern int DAT_05b9d838;

// FUNCTION: SADX 0x006b2d50
void PalmDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	njRotateZXY(0, var1->ang.x, var1->ang.y, var1->ang.z);
	DAT_05b3df40 = -37952.0f;
	late_DrawObjectClipEx((struct obj *)(*(int **)((char *)DAT_060eea9c + 0x16c)), 1, 1.0);
	DAT_05b3df40 = 0.0f;
	njPopMatrix(1);
}

// FUNCTION: SADX 0x006b2dd0
void ObjectMysticRuinPalm(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		if (var1->mode == 0)
		{
			tp->disp = PalmDisplayer;
			var1->mode = 1;
		}
		PalmDisplayer(tp);
	}
}
