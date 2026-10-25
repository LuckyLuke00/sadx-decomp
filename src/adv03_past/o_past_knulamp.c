#include "decls.h"
extern "C" int rand(void);

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

// FUNCTION: SADX 0x006bfc00
void ObjectPastKnucklesLamp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			tp->disp = LampDisplayer;
			var1->mode = 1;
			break;
		case 1:
			{
				int var2 = rand();
				float var3 = (float)var2 * 3.0517578125e-05f;
				var3 = var3 * 0.20000000298023224f;
				var1->scl.x = var3 + 0.800000011920929f;
				var3 = var3 + 0.10000000149011612f;
				var1->scl.y = var3;
				var1->scl.z = var3;
				LampDisplayer(tp);
				return;
			}
		}
		LampDisplayer(tp);
	}
}
