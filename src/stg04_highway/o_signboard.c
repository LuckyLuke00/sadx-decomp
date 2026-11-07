#include "decls.h"

// FUNCTION: SADX 0x00822d00
void dispSignboard(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	ModelTurnWhite(var1, 8);
	if (var1->value.l == 0)
	{
		SetObjectTexture();
	}
	else
	{
		___njSetTexture((struct NJS_TEXLIST *)var1->value.l);
	}
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (var1->ang.z != 0)
	{
		njRotateZ(NULL, (unsigned short)(short)var1->ang.z);
	}
	if (var1->ang.x != 0)
	{
		njRotateX(NULL, (unsigned short)(short)var1->ang.x);
	}
	if (var1->ang.y != 0)
	{
		njRotateY(NULL, (unsigned short)(short)var1->ang.y);
	}
	late_DrawModel((struct NJS_MODEL *)*(int *)((int)var1->counter.l + 4), 4);
	njPopMatrix(1);
	ResetMaterial();
}
