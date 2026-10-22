#include "decls.h"
extern struct NJS_ACTION action_sssikake_kartdoor[1];

// FUNCTION: SADX 0x006908a0
void FUN_006908a0(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	SetObjectTexture();
	___dsAction((struct NJS_ACTION *)&action_sssikake_kartdoor, *(float *)((char *)var1 + 8), 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x00690910
void ObjectColliSet(struct taskwk *twp)
{
}
