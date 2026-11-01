#include "decls.h"
extern struct NJS_ACTION *DAT_060eeacc;

// FUNCTION: SADX 0x00698440
void FUN_00698440(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	SetObjectTexture();
	ds_ActionClip(*(struct NJS_ACTION **)((char *)DAT_060eeacc + 8), var1->value.f, 1.0f);
	njPopMatrix(1);
}
