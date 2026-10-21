#include "decls.h"

// FUNCTION: SADX 0x006868b0
void FUN_006868b0(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	ds_DrawObjectClip(object_sikake_powerbox_powerbox, 1.0f);
	njPopMatrix(1);
}
