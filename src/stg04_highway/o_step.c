#include "decls.h"
void FUN_004a88c0(NJS_ACTION *param_1, float param_2);
extern struct obj object_tai_dai_tai_dai_tai_dai[];

// FUNCTION: SADX 0x00821230
void destStep(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (var1->counter.ptr != 0)
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	}
	FreeTask(tp);
}

// FUNCTION: SADX 0x00821260
void dispStep(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(0, var1->ang.y);
	}
	___dsDrawObject(*(struct obj **)((char *)var1 + 8));
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00821580
void ObjectStep4Tails(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (FUN_004c39c0(tp) != 0)
	{
		njPrintC(0x110010, "> NOT USE");
		njPrintC(0x110011, "> ROTATION");
		njPrintC(0x110012, "> NOT USE");
		njPrintC(0x110013, "> NOT USE");
		njPrintC(0x110014, "> NOT USE");
		njPrintC(0x110015, "> NOT USE");
	}
	var1->timer.ptr = &object_tai_dai_tai_dai_tai_dai;
	ObjectGCollision(tp);
}

// FUNCTION: SADX 0x00821610
void dispFlyingStepSub(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(0, var1->ang.y);
	}
	FUN_004a88c0((NJS_ACTION *)var1->value.ptr, var1->timer.f);
	njPopMatrix(1);
}
