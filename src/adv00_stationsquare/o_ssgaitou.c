#include "decls.h"
static void Disp(struct task *tp);
extern struct NJS_SPRITE sprite_lamp;
extern int DAT_05b9d838;

#pragma optimize("", off)
// STUB: SADX 0x0068b0b0
static void Disp(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0068b1e0
void LampDisp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 0xa);
	SetMaterial(0.7f, 0.8f, 0.8f, 0.8f);
	sprite_lamp.p.x = var1->pos.x;
	sprite_lamp.p.y = var1->pos.y + 39.0f;
	sprite_lamp.p.z = var1->pos.z;
	saSetSpriteZOffset(-3.0f);
	saDrawSprite3D(&sprite_lamp, 0, 0x32);
	ResetMaterial();
	Disp(tp);
}
