#include "decls.h"

// FUNCTION: SADX 0x00821d00
void FUN_00821d00(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;
	___njSetTexture((struct NJS_TEXLIST *)(var1->value.ptr));
	njPushMatrix((float *)0);
	njTranslateV((float *)0, &var1->pos);
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX((float *)0, *(unsigned short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY((float *)0, *(unsigned short *)((char *)var1 + 0x18));
	}
	___dsDrawModel((struct NJS_MODEL *)*(int *)(*(int *)((char *)var1 + 8) + 4));
	njPopMatrix(1);
}
