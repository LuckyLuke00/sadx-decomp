#include "decls.h"
extern struct NJS_ARGB DAT_0286df48;
extern struct NJS_SPRITE DAT_060df55c;
extern struct task *DAT_060bd48c;

// FUNCTION: SADX 0x006e2a80
void DisplayRain(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	___njDrawLine3D(&rain_p3col, 1, 0);
	njPopMatrix(1);
	ResetMaterial();
}

// FUNCTION: SADX 0x006e2ac0
void DisplayDrop(struct task *tp)
{
	struct taskwk *var1;
	float var2;

	var1 = tp->twp;
	DAT_0286df48.a = var1->counter.f;
	___njSetConstantMaterial(&DAT_0286df48);
	___njSetTexture(&texlist_chaos_effect);
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	var2 = var1->counter.f * 0.25;
	njRotateX(0, 0x4000);
	FUN_0067d2d0(0, var2, var2, var2);
	___njDrawSprite3D(&DAT_060df55c, 0, 0x22);
	njPopMatrix(1);
	ResetMaterial();
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
}

// FUNCTION: SADX 0x006e2d70
void ctrlRainEffect(struct task *tp)
{
	int var1;

	var1 = 0;
	if (rain_param.num <= 0)
	{
		return;
	}
	do
	{
		CreateElementalTask(2, 3, RainEffect);
		var1++;
	}
	while (var1 < rain_param.num);
}

// FUNCTION: SADX 0x006e2da0
void setRainEffect()
{
	DAT_060bd48c = CreateElementalTask(2, 2, ctrlRainEffect);
}
