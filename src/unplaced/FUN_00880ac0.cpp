#include "decls.h"
void FUN_00880ac0(struct task *param_1);
struct task;
extern struct NJS_SPRITE DAT_060dc468;

// FUNCTION: SADX 0x00880ac0
void FUN_00880ac0(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_bigstar);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (DAT_05b42a7c->ang.y)
	{
		njRotateY(0, DAT_05b42a7c->ang.y);
	}
	FUN_0067d2d0(0, var1->scl.x, var1->scl.x, var1->scl.x);
	___njDrawSprite3D(&DAT_060dc468, var1->btimer, 0x20);
	njPopMatrix(1);
}

// STUB: SADX 0x00880b50
void FUN_00880b50(struct task *tp)
{
}
