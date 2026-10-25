#include "decls.h"
static void ObjectMain(struct task *tp);
static void ObjectDisplay(struct task *tp);
extern int DAT_05b9d838;
extern struct obj object_sssikake_pole_pole[];

// FUNCTION: SADX 0x00690c80
static void ObjectDisplay(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	ds_DrawObjectClip((struct obj *)&object_sssikake_pole_pole, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00690cd0
static void ObjectMain(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp) == 0)
	{
		if (FUN_004c39c0(tp) != 0)
		{
			ObjectDisplay(tp);
			return;
		}
		ObjectDisplay(tp);
		EntryColliList(var1);
	}
}

// STUB: SADX 0x00690d10
void ObjectSSPole(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		CCL_Init(tp, (struct CCL_INFO *)0x26ded40, 1, 4);
		tp->exec = ObjectMain;
		tp->disp = ObjectDisplay;
	}
}
