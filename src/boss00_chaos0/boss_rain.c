#include "decls.h"
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

// STUB: SADX 0x006e2ac0
void DisplayDrop(struct task *tp)
{
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
