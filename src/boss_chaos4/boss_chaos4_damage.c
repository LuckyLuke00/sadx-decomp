#include "decls.h"
extern int DAT_05b9d838;
extern float DAT_05b3df40;
extern struct NJS_TEXLIST texlist_chaos4_common;
extern struct obj object_chaos4ball_s;
void MirenEffSaveState();
void MirenEffLoadState();
void MirenEffChangeAlpha(float alpha);
float njSin(int);
float njCos(int);
void njPushMatrix(float *);
void njTranslateV(float *, struct NJS_POINT3 *);
void FUN_0067d2d0(float *, float, float, float);
float FUN_004a1e90(float *);
void late_DrawObjectClip(struct obj *, int, float);
void njPopMatrix(int);
void ___njSetTexture(struct NJS_TEXLIST *);

// FUNCTION: SADX 0x006f25b0
void Dsp_damage_ball(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;
	struct anywk *var2 = pTask->awp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_chaos4_common);
	MirenEffSaveState();
	MirenEffChangeAlpha(0.5f);
	var1->scl.z = njSin(var2->work.ul[3]) * 0.5 + 2.0;
	var1->scl.x = var1->scl.z;
	var1->scl.y = njCos(var2->work.ul[3]) * 0.5 + 2.0;
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	FUN_0067d2d0(0, var1->scl.x, var1->scl.y, var1->scl.z);
	DAT_05b3df40 = 100.0f;
	late_DrawObjectClip(&object_chaos4ball_s, 0, FUN_004a1e90(&var1->scl.x));
	DAT_05b3df40 = 0.0f;
	njPopMatrix(1);
	MirenEffLoadState();
}

// STUB: SADX 0x006f2a60
void damage_ballSet(struct NJS_POINT3 *base_pos)
{
}
