#include "decls.h"
static void Disp(struct task *tp);
extern struct obj object_seaobj_parasol03_parasol03[];
extern int DAT_05b9d838;

// FUNCTION: SADX 0x007f9270
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
	late_DrawObjectClipEx(object_seaobj_parasol03_parasol03, 1, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x007f92e0
void Exec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut_L(tp) == 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			EntryColliList(var1);
		}
		Disp(tp);
	}
}

// STUB: SADX 0x007f9320
void ObjectBeachKasa(struct task *tp)
{
}
