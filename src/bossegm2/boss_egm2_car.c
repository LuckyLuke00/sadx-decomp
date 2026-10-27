#include "decls.h"
extern "C" double fabs(double param_1);
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

// FUNCTION: SADX 0x006cbca0
void Exe_car_broken(struct task *pTask)
{
	struct taskwk *var1;
	struct anywk *var2;
	float var3;
	var1 = pTask->twp;
	var2 = pTask->awp;
	var1->pos.x += var2->work.f[0];
	var1->pos.y += var2->work.f[1];
	var1->pos.z += var2->work.f[2];
	var2->work.f[1] -= 0.027222221717238426f;
	if (var1->pos.y < 0.0f)
	{
		var1->pos.y = 0.0f;
		var3 = fabs(var2->work.f[1]);
		var2->work.f[1] = var3 * 0.800000011920929f;
	}
	var1->ang.x += *(int *)((char *)var2 + 0xc);
	var1->ang.y += *(int *)((char *)var2 + 0x10);
	var1->ang.z += *(int *)((char *)var2 + 0x14);
	var2->work.f[7] -= 0.007000000216066837f;
	if (var2->work.f[7] < -1.0f)
	{
		FreeTask(pTask);
	}
	Dsp_car_broken(pTask);
}
