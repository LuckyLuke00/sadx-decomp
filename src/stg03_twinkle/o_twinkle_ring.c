#include "decls.h"
extern struct NJS_MODEL DAT_05a7b20c;

// FUNCTION: SADX 0x00813e10
void dispTPRing(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	if (var1->btimer < 0x32)
	{
		if (var1->scl.y != -1000000.0f)
		{
			StaticShadow(var1, var1->scl.y);
		}
	}
	SaveConstantAttr();
	OffConstantAttr(0, 0x80000);
	SetRegularTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	ds_DrawModelClip(&DAT_05a7b20c, 1.0f);
	njPopMatrix(1);
	LoadConstantAttr();
}
