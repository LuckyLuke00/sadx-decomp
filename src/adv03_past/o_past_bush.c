#include "decls.h"

// FUNCTION: SADX 0x006c03c0
void ShidaDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 30.0f))
	{
		struct NJS_ACTION *var2 = *(struct NJS_ACTION **)((char *)DAT_060eea54 + 0x2c);
		SetObjectTexture();
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		njRotateZXY(0, var1->ang.x, var1->ang.y, var1->ang.z);
		if (var1->flag & 0x200)
		{
			late_ActionClipEx(var2, var1->value.f, 0, 1.0f);
		}
		else
		{
			late_DrawObjectClipEx(var2->object, 0, 1.0f);
		}
		late_DrawShadowObject(*(struct obj **)((char *)DAT_060eeaa4 + 0x3c), 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x006c0480
void SotetsuDisplayer(struct task *tp)
{
	struct taskwk *var1;
	struct NJS_ACTION *var2;
	struct obj *var3;

	var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 30.0f))
	{
		var2 = *(struct NJS_ACTION **)((char *)DAT_060eea54 + 0x30);
		SetObjectTexture();
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		njRotateZXY(0, var1->ang.x, var1->ang.y, var1->ang.z);
		if (var1->flag & 0x200)
		{
			late_ActionClipEx(var2, var1->value.f, 1, 1.0f);
		}
		else
		{
			var3 = var2->object;
			late_DrawObjectClipEx(var3, 1, 1.0f);
		}
		late_DrawShadowObject(*(struct obj **)((char *)DAT_060eeaa4 + 0x3c), 1.0f);
		njPopMatrix(1);
	}
}
