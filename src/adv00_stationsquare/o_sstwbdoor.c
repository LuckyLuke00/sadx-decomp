#include "decls.h"

// GLOBAL: SADX 0x026de828
static struct CCL_INFO ccinfo[2];

static void ObjectMain(struct task *tp);
static void ObjectDisplay(struct task *tp);

// FUNCTION: SADX 0x0068f040
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
	ds_ActionClip(action_sssikake_twbdoor, var1->counter.f, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x0068f2b0
static void ObjectMain(struct task *tp)
{
}

// FUNCTION: SADX 0x0068f320
void ObjectSSTwbdoor(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		CCL_Init(tp, ccinfo, 2, 4);
		tp->exec = ObjectMain;
		tp->disp = ObjectDisplay;
	}
}
