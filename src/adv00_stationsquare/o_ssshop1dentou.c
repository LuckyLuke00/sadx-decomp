#include "decls.h"

// GLOBAL: SADX 0x026de4d8
static struct NJS_SPRITE sprite_lamp;

// FUNCTION: SADX 0x0068d1d0
void dispSSShop1Dentou(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	___njSetTexture((struct NJS_TEXLIST *)var1->value.ptr);
	ds_DrawObjectClip((struct obj *)var1->counter.ptr, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0068d240
void dispSSShop1Lamp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 0xa);
	SetMaterial(0.7f, 0.8f, 0.65f, 0.3f);
	sprite_lamp.p.x = var1->pos.x;
	sprite_lamp.p.y = var1->pos.y - 2.2f;
	sprite_lamp.p.z = var1->pos.z;
	saSetSpriteZOffset(-3.0f);
	saDrawSprite3D(&sprite_lamp, 0, 0x32);
	ResetMaterial();
	SaveConstantAttr();
	OnConstantAttr(0, 0x2000000);
	dispSSShop1Dentou(tp);
	LoadConstantAttr();
}

// STUB: SADX 0x0068d300
void ObjectSSShop1Dentou(struct task *tp)
{
}
