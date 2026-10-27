#include "decls.h"

// FUNCTION: SADX 0x006c1190
void DisplayPalm(struct task *tp)
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
	if (var1->flag & 0x200)
	{
		late_ActionClipEx((struct NJS_ACTION *)(*(struct obj **)((char *)DAT_060eea54 + 0x28)), var1->value.f, 1, 1.0f);
	}
	else
	{
		late_DrawObjectClipEx(*(struct obj **)((char *)DAT_060eeaa4 + 0x24), 1, 1.0f);
	}
	njPopMatrix(1);
}
