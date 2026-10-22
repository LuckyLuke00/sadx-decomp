#include "decls.h"

// FUNCTION: SADX 0x00694d30
void FUN_00694d30(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	ds_DrawObjectClip((struct obj *)var1->counter.ptr, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x00694e20
void ObjectECBook1(struct task *tp)
{
}

// STUB: SADX 0x00694e40
void ObjectECBook2(struct task *tp)
{
}

// STUB: SADX 0x00694e60
void ObjectECBook3(struct task *tp)
{
}
