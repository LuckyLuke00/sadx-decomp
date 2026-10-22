#include "decls.h"
extern struct obj *DAT_060eeaa4;

// FUNCTION: SADX 0x006c0d10
void DisplayWell(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y != 0)
		njRotateY(0, (unsigned short)var1->ang.y);
	SetObjectTexture();
	ds_DrawObjectClip(*(struct obj **)((char *)DAT_060eeaa4 + 0x34), 1.0f);
	ds_DrawObjectClip(*(struct obj **)((char *)DAT_060eeaa4 + 0x48), 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x006c0d90
void ObjectPastWell(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (!CheckRangeOut(tp))
	{
		if (var1->mode == 0)
		{
			CCL_Init(tp, cinfo_well, 1, 4);
			tp->disp = DisplayWell;
			var1->mode = 1;
		}
		DisplayWell(tp);
		EntryColliList(var1);
	}
}
