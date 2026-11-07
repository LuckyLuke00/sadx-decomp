#include "decls.h"
extern struct NJS_SPRITE sprite_plight;
extern struct NJS_ARGB DAT_060b866c;

// FUNCTION: SADX 0x0069e820
void GreenBlinkDisplayer(struct task *tp)
{
	struct taskwk *var1;
	struct NJS_POINT3 *var2;
	int var3;

	var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		sprite_plight.sy = var1->scl.x;
		sprite_plight.sx = sprite_plight.sy;
		var2 = (struct NJS_POINT3 *)var1->counter.ptr;
		DAT_060b866c.a = var1->value.f;
		DAT_060b866c.r = 1.0f;
		DAT_060b866c.g = 1.0f;
		DAT_060b866c.b = 1.0f;
		___njFogDisable();
		saSetSpriteZOffset(-20.0f);
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 0xa);
		___njSetConstantMaterial(&DAT_060b866c);
		var3 = 0;
		while (var3 < (short)var1->timer.w[0])
		{
			sprite_plight.p = *var2;
			var2++;
			saDrawSprite3D(&sprite_plight, 0, 0x32);
			var3++;
		}
		ResetMaterial();
		___njFogEnable();
	}
}
