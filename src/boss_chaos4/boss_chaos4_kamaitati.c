#include "decls.h"

// FUNCTION: SADX 0x006f3b30
void Dsp_Chaos4KamaTame(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_chaos4_kama);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	CHAOS_Action((struct NJS_ACTION *)&action_c4_tailattame01, var1->value.f);
	CHAOS_Action((struct NJS_ACTION *)&action_c4_tailattame02, var1->value.f);
	njPopMatrix(1);
}
