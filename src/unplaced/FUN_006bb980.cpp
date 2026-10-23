#include "decls.h"
extern int DAT_060eeaac;
extern int DAT_060eeac8;
void FUN_004a8b10(NJS_ACTION *param_1, float param_2, int param_3);

// FUNCTION: SADX 0x006bbbd0
void FUN_006bbbd0(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	if (CheckCollisionP(&var1->pos, 500.0f))
	{
		___njSetTexture(*(struct NJS_TEXLIST **)((char *)DAT_060eeac8 + 0x54));
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y)
		{
			njRotateY(0, var1->ang.y);
		}
		FUN_004a8b10(*(NJS_ACTION **)((char *)DAT_060eeaac + 0x40), *(float *)((char *)var1 + 0x10), 1);
		njPopMatrix(1);
	}
}
