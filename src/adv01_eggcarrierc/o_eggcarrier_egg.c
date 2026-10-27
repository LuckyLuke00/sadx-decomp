#include "decls.h"
extern struct NJS_TEXLIST *DAT_060eeaa0;
extern struct obj *DAT_060eea98;

// FUNCTION: SADX 0x0069e980
void EggDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct task *var2 = GetPlayerTaskPointer(0);
	if (var2->exec != 0 && DAT_05b9d838 == 0)
	{
		___njSetTexture(*(struct NJS_TEXLIST **)((char *)DAT_060eeaa0 + 0xc));
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y)
		{
			njRotateY(0, var1->ang.y);
		}
		ds_DrawObjectClip(*(struct obj **)((char *)DAT_060eea98 + 0x58), 1.0f);
		njPopMatrix(1);
	}
}
