#include "decls.h"
void cNormal2(struct task *ctp);

// FUNCTION: SADX 0x00882ef0
void Disp1(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture2(0x22);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	njPushMatrix(0);
	FUN_0067d830(0, -9.8377f, 0.0f, -2.053f);
	njRotateY(0, 0x6c1);
	late_DrawModel((struct NJS_MODEL *)var1->counter.ptr, 9);
	njPopMatrix(1);
	njPushMatrix(0);
	FUN_0067d830(0, 9.2365f, 0.0f, 3.961f);
	njRotateY(0, 0xe05b);
	late_DrawModel((struct NJS_MODEL *)var1->timer.ptr, 9);
	njPopMatrix(1);
	njRotateY(0, 0xf38f);
	late_DrawModel((struct NJS_MODEL *)var1->value.ptr, 9);
	njPopMatrix(1);
}

// STUB: SADX 0x00883050
void cNormal2(struct task *ctp)
{
}

// STUB: SADX 0x008831a0
void ObjectNeon(struct task *tp)
{
}
