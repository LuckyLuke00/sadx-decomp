#include "decls.h"
static void ObjectDisplay(struct task *tp);

// GLOBAL: SADX 0x02225868
static struct CCL_INFO ccinfo[2];

static void ObjectMain(struct task *tp);
static void ObjectALGardenDoor(struct task *tp);

// FUNCTION: SADX 0x004772f0
static void ObjectDisplay(struct task *tp)
{
	struct taskwk *var1;

	if (DAT_05b9d838 == 0)
	{
		var1 = tp->twp;
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		___njSetTexture(&texlist_Garden00SSObj);
		FUN_004a7cb0((struct obj *)&object_stch_elegate_waku_waku, (struct NJS_MOTION *)&motion_stch_elegate_waku, var1->counter.f);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x00477500
static void ObjectMain(struct task *tp)
{
}

// FUNCTION: SADX 0x00477540
static void ObjectALGardenDoor(struct task *tp)
{
	CCL_Init(tp, ccinfo, 2, 4);
	tp->exec = ObjectMain;
	tp->disp = ObjectDisplay;
	tp->dest = ExplosionRockDestructor;
}

// FUNCTION: SADX 0x00477570
struct task *AloG00ElegateWakuCreate(struct task *parent_tp)
{
	struct task *var1;
	struct taskwk *var2;

	var1 = CreateChildTask(2, ObjectALGardenDoor, parent_tp);
	if (var1 != 0)
	{
		var2 = var1->twp;
		var2->pos.x = 0.0f;
		var2->pos.y = 0.0f;
		var2->pos.z = 157.0f;
	}
	return var1;
}
