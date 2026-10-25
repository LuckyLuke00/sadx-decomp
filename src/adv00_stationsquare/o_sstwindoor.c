#include "decls.h"
static void ObjectClose(struct task *tp);
extern struct NJS_ACTION action_sssikake_twindoor[];

// FUNCTION: SADX 0x0068fa50
void FUN_0068fa50(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	___dsAction(action_sssikake_twindoor, *(float *)((char *)var1 + 8), 1.0f);
	njPopMatrix(1);
}

#pragma optimize("", off)
// STUB: SADX 0x0068fb40
static void ObjectClose(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0068fbd0
void ObjectWait(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp))
	{
		return;
	}
	FUN_0068fa50(tp);
	if (!var1->btimer)
	{
		if (CheckCollisionP(&var1->pos, 15.0f))
		{
			return;
		}
		tp->exec = ObjectClose;
		dsPlay_oneshot(0x212, 0, 0, 0);
	}
	else
	{
		var1->btimer--;
	}
}
