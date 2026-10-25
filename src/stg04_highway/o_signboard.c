#include "decls.h"

// FUNCTION: SADX 0x00822d00
void dispSignboard(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	ModelTurnWhite(var1, 8);
	if (*(int *)((char *)var1 + 0x10) == 0)
	{
		SetObjectTexture();
	}
	else
	{
		___njSetTexture((struct NJS_TEXLIST *)*(int *)((char *)var1 + 0x10));
	}
	njPushMatrix((float *)0);
	njTranslateV((float *)0, &var1->pos);
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX((float *)0, (unsigned short)*(short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY((float *)0, (unsigned short)*(short *)((char *)var1 + 0x18));
	}
	late_DrawModel((struct NJS_MODEL *)*(int *)(*(int *)((char *)var1 + 8) + 4), 4);
	njPopMatrix(1);
	ResetMaterial();
}
