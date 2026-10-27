#include "decls.h"
extern int DAT_060eeaac;
extern int DAT_060eeac8;

// FUNCTION: SADX 0x006b9050
void FUN_006b9050(struct NJS_TEXLIST *param_1)
{
	struct task *var2 = (struct task *)param_1;
	struct taskwk *var1;
	var1 = var2->twp;
	___njSetTexture((struct NJS_TEXLIST *)*(int **)((char *)DAT_060eeac8 + 0x54));
	njPushMatrix(0);
	njTranslateV(0, (struct NJS_POINT3 *)((char *)var1 + 0x20));
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY(0, *(unsigned short *)((char *)var1 + 0x18));
	}
	FUN_004a88c0((NJS_ACTION *)*(int *)((char *)DAT_060eeaac + 0x84), *(float *)((char *)var1 + 8));
	njPopMatrix(1);
}
