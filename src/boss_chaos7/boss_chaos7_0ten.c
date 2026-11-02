#include "decls.h"
void DisplayTenT(struct task *tp);
extern struct NJS_SPRITE sprite_c7tt;

// FUNCTION: SADX 0x00704820
void DisplayTenT(struct task *tp)
{
	struct NJS_ARGB argb;
	struct taskwk *var1;

	var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		argb.a = 1.0f;
		argb.b = 1.0f;
		argb.g = 1.0f;
		argb.r = 1.0f;
		___njSetConstantMaterial(&argb);
		___njColorBlendingMode(0, 0xa);
		___njColorBlendingMode(1, 0xa);
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		sprite_c7tt.sy = var1->scl.x * var1->scl.y;
		sprite_c7tt.sx = sprite_c7tt.sy;
		late_DrawSprite3D(&sprite_c7tt, 0, 0x30, 4);
		njPopMatrix(1);
	}
}
