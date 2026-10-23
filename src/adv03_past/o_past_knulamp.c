#include "decls.h"

// FUNCTION: SADX 0x006bfb10
void LampDisplayer(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	sprite_panlight.p.x = var1->pos.x;
	sprite_panlight.p.y = var1->pos.y + 12.5;
	sprite_panlight.p.z = var1->pos.z;
	material_panlight.r = var1->scl.x;
	material_panlight.g = var1->scl.y;
	material_panlight.b = var1->scl.z;
	___njFogDisable();
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 0xa);
	___njSetConstantMaterial(&material_panlight);
	saSetSpriteZOffset(-10.0f);
	saDrawSprite3D(&sprite_panlight, 0, 0x32);
	ResetMaterial();
	___njFogEnable();
	SetObjectTexture();
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(NULL, (unsigned short)var1->ang.y);
	}
	ds_DrawObjectClip(*(struct obj **)((char *)DAT_060eeaa4 + 0x10), 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x006bfc00
void ObjectPastKnucklesLamp(struct task *tp)
{
}
