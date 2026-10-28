#include "decls.h"

// FUNCTION: SADX 0x004772f0
void ObjectDisplay(struct task *tp)
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

// STUB: SADX 0x00477570
struct task *AloG00ElegateWakuCreate(struct task *parent_tp)
{
	return (struct task *)0;
}
