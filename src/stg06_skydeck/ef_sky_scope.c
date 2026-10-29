#include "decls.h"
extern int DAT_05b9d838;
void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
float FUN_004a1e90(float *param_1);
void ds_DrawObjectClip(struct obj *obj, float clipScl);
long SetObjectTexture();

// FUNCTION: SADX 0x0083e370
void dispSkyScope(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y + 0.5, var1->pos.z);
	if ((var1->btimer & 2) && var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	if (var1->btimer & 4)
	{
		njScaleV(0, &var1->scl);
		SetObjectTexture();
		ds_DrawObjectClip((struct obj *)var1->counter.ptr, FUN_004a1e90((float *)&var1->scl));
	}
	else
	{
		SetObjectTexture();
		ds_DrawObjectClip((struct obj *)var1->counter.ptr, 1.0f);
	}
	njPopMatrix(1);
}
