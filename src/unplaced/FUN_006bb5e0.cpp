#include "decls.h"
extern int DAT_060eeac8;
extern int DAT_060eeaac;
void late_ActionMesh(NJS_ACTION *action, float frame, int flgs);

// FUNCTION: SADX 0x006bb800
void FUN_006bb800(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	if (CheckCollisionP(&var1->pos, 500.0f))
	{
		___njSetTexture(*(struct NJS_TEXLIST **)((char *)DAT_060eeac8 + 0x54));
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y)
		{
			njRotateY(0, (Uint16)var1->ang.y);
		}
		late_ActionMesh(*(NJS_ACTION **)((char *)DAT_060eeaac + 0x3c), *(float *)((char *)var1 + 0x10), 1);
		njPopMatrix(1);
	}
}
