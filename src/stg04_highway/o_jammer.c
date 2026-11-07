#include "decls.h"

// FUNCTION: SADX 0x00821d00
void FUN_00821d00(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;
	___njSetTexture((struct NJS_TEXLIST *)(var1->value.ptr));
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (var1->ang.z != 0)
	{
		njRotateZ(NULL, (unsigned short)(short)var1->ang.z);
	}
	if (var1->ang.x != 0)
	{
		njRotateX(NULL, (unsigned short)var1->ang.x);
	}
	if (var1->ang.y != 0)
	{
		njRotateY(NULL, (unsigned short)var1->ang.y);
	}
	___dsDrawModel((struct NJS_MODEL *)*(int *)((int)var1->counter.l + 4));
	njPopMatrix(1);
}
