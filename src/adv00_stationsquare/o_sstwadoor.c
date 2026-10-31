#include "decls.h"

// GLOBAL: SADX 0x026de888
static struct CCL_INFO ccinfo[2];

static void ObjectMain(struct task *tp);
static void ObjectDisplay(struct task *tp);

// FUNCTION: SADX 0x0068f360
static void ObjectDisplay(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (*(int *)((char *)var1 + 0x18))
	{
		njRotateY(0, *(unsigned short *)((char *)var1 + 0x18));
	}
	ds_ActionClip(action_sssikake_twadoor, var1->counter.f, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x0068f5d0
static void ObjectMain(struct task *tp)
{
}

// FUNCTION: SADX 0x0068f640
void ObjectSSTwadoor(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		CCL_Init(tp, ccinfo, 2, 4);
		tp->exec = ObjectMain;
		tp->disp = ObjectDisplay;
	}
}
