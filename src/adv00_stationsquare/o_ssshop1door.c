#include "decls.h"

// GLOBAL: SADX 0x026debf0
static struct CCL_INFO ccinfo[2];

static void ObjectMain(struct task *tp);
static void ObjectDisplay(struct task *tp);

// FUNCTION: SADX 0x006903c0
static void ObjectDisplay(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	ds_ActionClip(action_sssikake_shop1door, var1->counter.f, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x00690730
static void ObjectMain(struct task *tp)
{
}

// FUNCTION: SADX 0x006907f0
void ObjectSSShop1door(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		CCL_Init(tp, ccinfo, 2, 4);
		var1->counter.f = 1.0f;
		tp->exec = ObjectMain;
		tp->disp = ObjectDisplay;
	}
}
