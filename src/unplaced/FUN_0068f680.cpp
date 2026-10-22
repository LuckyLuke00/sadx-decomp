#include "decls.h"
extern struct NJS_ACTION action_sssikake_uradoor[1];

// FUNCTION: SADX 0x0068f680
void FUN_0068f680(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, (struct NJS_POINT3 *)((char *)var1 + 0x20));
	if (*(int *)((char *)var1 + 0x18))
	{
		njRotateY(0, *(unsigned short *)((char *)var1 + 0x18));
	}
	___dsAction(action_sssikake_uradoor, *(float *)((char *)var1 + 8), 1.0f);
	njPopMatrix(1);
}
