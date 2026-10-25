#include "decls.h"
static void ObjectDisplay(struct task *tp);
static void ObjectMain(struct task *tp);
extern struct CCL_INFO ccinfo[];
extern int DAT_05b9d838;
extern struct NJS_TEXLIST texlist_Garden00SSObj;
extern struct obj object_stch_racegate_waku_waku[1];
extern struct NJS_MOTION motion_stch_racegate_waku[1];

// FUNCTION: SADX 0x00477000
static void ObjectDisplay(struct task *tp)
{
	struct taskwk *var1;

	if (DAT_05b9d838 == 0)
	{
		var1 = tp->twp;
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		___njSetTexture(&texlist_Garden00SSObj);
		FUN_004a7cb0((struct obj *)&object_stch_racegate_waku_waku, (struct NJS_MOTION *)&motion_stch_racegate_waku, var1->counter.f);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x00477210
static void ObjectMain(struct task *tp)
{
}

// FUNCTION: SADX 0x00477250
void ObjectALGardenDoor(struct task *tp)
{
	CCL_Init(tp, (struct CCL_INFO *)&ccinfo, 2, 4);
	tp->exec = ObjectMain;
	tp->disp = ObjectDisplay;
	tp->dest = ExplosionRockDestructor;
}

// STUB: SADX 0x00477280
struct task *AloG00RacegateWakuCreate(struct task *parent_tp)
{
	return (struct task *)0;
}
