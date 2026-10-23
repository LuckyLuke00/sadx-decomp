#include "decls.h"

// FUNCTION: SADX 0x007edc80
void TornadeDisp(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	njPushMatrix(NULL);
	FUN_0067d830(NULL, 0.0f, 0.0f, 4001.0f);
	___njSetTexture(&texlist_shooting0);
	FUN_0067d2d0(NULL, 0.5f, 0.5f, 0.5f);
	FUN_004a88c0((struct NJS_ACTION *)&action_shot_bf_s_bodya, 0.0f);
	late_ActionEx((struct NJS_ACTION *)&action_shot_s_ecfire, var1->counter.f, 4, 1.0f);
	njPopMatrix(1);
	njPushMatrix(NULL);
	FUN_0067d830(NULL, 0.0f, 0.0f, 0.0f);
	___njSetTexture(&texlist_shooting2);
	___dsSetPalette(2);
	FUN_004a8b10((struct NJS_ACTION *)&action_tr2henkei_tr2_tf_event_s_tr2rt, var1->counter.f, 4);
	___dsSetPalette(0);
	njPopMatrix(1);
}
