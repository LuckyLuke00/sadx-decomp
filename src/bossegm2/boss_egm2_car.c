#include "decls.h"
extern const struct Egm2CarData egm2_car_data[64];

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

// FUNCTION: SADX 0x006cbbe0
void Dsp_car_broken(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	struct anywk *var2 = pTask->awp;

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
	if (var1->ang.x)
	{
		njRotateX(0, var1->ang.x);
	}
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ(0, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	MirenEffSaveState();
	MirenEffChangeAlpha(*(float *)((char *)var2 + 0x1c));
	late_DrawObjectClip(egm2_car_data[*(unsigned char *)((char *)var2 + 0x18)].obj, 1, 1.0f);
	njPopMatrix(1);
	MirenEffLoadState();
}
