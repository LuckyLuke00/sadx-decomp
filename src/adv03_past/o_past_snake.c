#include "decls.h"
extern struct obj *DAT_060eeaa4;

// FUNCTION: SADX 0x006c0fa0
void DisplaySnake(struct task *tp)
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
	ds_DrawObjectClip(*(struct obj **)((char *)DAT_060eeaa4 + 0x20), 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x006c1010
void ObjectPastSnake(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		if (var1->mode == 0)
		{
			tp->disp = DisplaySnake;
			var1->mode = 1;
		}
		DisplaySnake(tp);
	}
}
