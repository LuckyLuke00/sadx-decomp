#include "decls.h"
static void ObjectMain(struct task *tp);
static void ObjectDisplay(struct task *tp);

// GLOBAL: SADX 0x0286e0dc
static struct CCL_INFO ccinfo[1];

extern void *DAT_060eea80;

// FUNCTION: SADX 0x006e5c60
static void ObjectDisplay(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	ds_DrawObjectClip((struct obj *)*(void **)((char *)DAT_060eea80 + 0x11c), 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x006e5cb0
static void ObjectMain(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		if (FUN_004c39c0(tp) != 0)
		{
			ObjectDisplay(tp);
			return;
		}
		ObjectDisplay(tp);
		EntryColliList(tp->twp);
	}
}

// FUNCTION: SADX 0x006e5cf0
void ObjectC0Pole(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		CCL_Init(tp, ccinfo, 1, 4);
		tp->exec = ObjectMain;
		tp->disp = ObjectDisplay;
	}
}
