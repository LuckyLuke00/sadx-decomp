#include "decls.h"

// FUNCTION: SADX 0x006b0ac0
void LadderDestructor(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	Free(var1->value.ptr);
	Free(var1->timer.ptr);
	FreeTaskC(tp);
}

// FUNCTION: SADX 0x006b0af0
void LadderDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	int var2;

	SetObjectTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y - 60.0, var1->pos.z);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	for (var2 = 3; var2 != 0; var2--)
	{
		___dsDrawModel(*(struct NJS_MODEL **)((char *)*(void **)((char *)DAT_060eea9c + 0x14c) + 4));
		FUN_0067d830(0, 0.0f, 99.0f, 0.0f);
	}
	njPopMatrix(1);
}
