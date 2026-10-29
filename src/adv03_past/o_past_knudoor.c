#include "decls.h"
extern struct obj *DAT_060eeaa4;

// FUNCTION: SADX 0x006c0760
void KnucklesDoorDisplayer(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	ds_DrawObjectClip(*(struct obj **)((char *)DAT_060eeaa4 + 0x38), 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x006c07c0
void ObjectPastKnucklesDoor(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		return;
	}
	if (var1->mode == 0)
	{
		tp->disp = KnucklesDoorDisplayer;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		var1->mode = 1;
	}
	KnucklesDoorDisplayer(tp);
}
