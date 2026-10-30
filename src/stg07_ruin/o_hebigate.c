#include "decls.h"
static void Normal(struct task *tp);
static void Disp(struct task *tp);

// FUNCTION: SADX 0x00856320
static void Disp(struct task *tp)
{
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, (struct NJS_POINT3 *)((char *)tp->twp + 0x20));
	FUN_004a88c0((struct NJS_ACTION *)&action_hebigate_hebikuchi, *(float *)((char *)tp->twp + 0xc));
	njPopMatrix(1);
}

#pragma optimize("", off)
// STUB: SADX 0x00856370
static void Normal(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x008564c0
void ObjectHebigate(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct obj *var2 = SetModelCollision(&object_hebi_clhebigate_clhebigate[0], tp, 1);

	var1->counter.ptr = var2;
	var2->scl[0] = 1.0f;
	var2->scl[1] = 1.0f;
	var2->scl[2] = 1.0f;
	var1->value.l = 0;
	var1->timer.f = 99.0f;
	tp->dest = MonorailCarDestructor;
	tp->exec = Normal;
	tp->disp = Disp;
}
