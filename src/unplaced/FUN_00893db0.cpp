#include "decls.h"
extern struct obj object_hsgo_hasigo_hasigo[1];

// FUNCTION: SADX 0x00893db0
void FUN_00893db0(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;
	int var2;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.x)
	{
		njRotateX(0, (unsigned short)var1->ang.x);
	}
	var2 = var1->ang.y + 0x8000;
	if (var2)
	{
		njRotateY(0, (unsigned short)(var1->ang.y + 0x8000));
	}
	ds_DrawModelClip(object_hsgo_hasigo_hasigo[0].model, 1.0f);
	njPopMatrix(1);
}
