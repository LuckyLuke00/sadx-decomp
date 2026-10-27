#include "decls.h"
extern struct obj *DAT_060eeaa4;
extern struct NJS_ACTION *DAT_060eea54;

// FUNCTION: SADX 0x006c0de0
void DisplayTree(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	if (var1->value.f <= 0.01f)
	{
		late_DrawObjectClipEx(*(struct obj **)((char *)DAT_060eeaa4 + 0x2c), 1, 1.0f);
	}
	else
	{
		late_ActionClipEx((struct NJS_ACTION *)(*(struct obj **)((char *)DAT_060eea54 + 0x20)), var1->value.f, 1, 1.0f);
	}
	njPopMatrix(1);
}
