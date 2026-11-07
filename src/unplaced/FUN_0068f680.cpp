#include "decls.h"
extern struct NJS_ACTION action_sssikake_uradoor[1];

// FUNCTION: SADX 0x0068f680
void FUN_0068f680(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, (struct NJS_POINT3 *)((char *)var1 + 0x20));
	if (var1->ang.y)
	{
		njRotateY(0, (unsigned short)var1->ang.y);
	}
	ds_ActionClip(action_sssikake_uradoor, var1->counter.f, 1.0f);
	njPopMatrix(1);
}
