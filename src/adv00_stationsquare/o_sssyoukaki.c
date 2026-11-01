#include "decls.h"

// GLOBAL: SADX 0x026ddf8c
static struct CCL_INFO ccinfo[1];

static void ObjectDisplay(struct task *tp);
static void ObjectMain(struct task *tp);

// FUNCTION: SADX 0x0068b350
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
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	ds_DrawModelClip(model_ssobj_syoukaki_syoukaki, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0068b3c0
static void ObjectMain(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (FUN_004c39c0(tp) != 0)
	{
		ObjectDisplay(tp);
		return;
	}
	if (CheckRangeOut(tp) == 0)
	{
		ObjectDisplay(tp);
		EntryColliList(var1);
	}
}

// FUNCTION: SADX 0x0068b400
void ObjectSSSyoukaki(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		CCL_Init(tp, ccinfo, 1, 4);
		tp->exec = ObjectMain;
		tp->disp = ObjectDisplay;
	}
}
