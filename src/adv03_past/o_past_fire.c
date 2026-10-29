#include "decls.h"
extern float DAT_05b3df40;
static void DispPastChaosFire(struct task *tp);
extern long DAT_060b97f0;

// FUNCTION: SADX 0x006bf800
static void DispPastChaosFire(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	___njFogDisable();
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 0xa);
	___njSetConstantMaterial((struct NJS_ARGB *)&material_bigfire);
	sprite_bigfire.p = var1->pos;
	sprite_bigfire.sx = var1->scl.x;
	sprite_bigfire.sy = var1->scl.y;
	DAT_05b3df40 = -10.0f;
	late_DrawSprite3D(&sprite_bigfire, DAT_060b97f0, 0x3a, 4);
	DAT_05b3df40 = 0.0f;
	ResetMaterial();
	___njFogEnable();
}

// FUNCTION: SADX 0x006bf890
void ObjectPastChaosFire(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		tp->disp = DispPastChaosFire;
		switch (var1->mode)
		{
		case 0:
			var1->mode = 1;
			break;
		case 1:
			var1->value.f += 0.5;
			DAT_060b97f0 = (long)var1->value.f;
			if (DAT_060b97f0 >= 0x10)
			{
				DAT_060b97f0 = 0;
				var1->value.f = 0.0;
			}
			DispPastChaosFire(tp);
			return;
		}
	}
}
