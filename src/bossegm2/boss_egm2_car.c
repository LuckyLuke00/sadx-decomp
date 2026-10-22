#include "decls.h"

// FUNCTION: SADX 0x006cbb70
void Dsp_car(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_egm2_car);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	ds_DrawObjectClip(object_sssikake_ccar_before_ccar_before, 1.0f);
	njPopMatrix(1);
}
