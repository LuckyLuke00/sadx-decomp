#include "decls.h"

// FUNCTION: SADX 0x00825d40
void dispElevator(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	___dsDrawModel(*(struct NJS_MODEL **)((char *)var1->counter.ptr + 4));
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00825da0
void exitElevator(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	int var2;

	var2 = FUN_004c39c0(tp);
	if ((var2 == 0) && (var1->counter.ptr != 0))
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	}
	FreeTaskC(tp);
}

// FUNCTION: SADX 0x00825e10
void dispEvStep(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct _OBJ_EDITENTRY *var2 = (struct _OBJ_EDITENTRY *)(var1->timer.l);
	struct NJS_MODEL *var3 = (struct NJS_MODEL *)(*(int *)((char *)var2 + 0x2c));
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	___dsDrawModel(*(struct NJS_MODEL **)((char *)var2 + 4));
	njPushMatrix(0);
	if (var1->wtimer != 0)
	{
		njRotateZ(0, var1->wtimer);
	}
	___dsDrawModel((struct NJS_MODEL *)(*(int *)((char *)var3 + 4)));
	njPopMatrix(1);
	njPushMatrix(0);
	var3 = (struct NJS_MODEL *)(*(int *)((char *)var3 + 0x30));
	if (var1->wtimer != 0)
	{
		njRotateZ(0, var1->wtimer);
	}
	___dsDrawModel((struct NJS_MODEL *)(*(int *)((char *)var3 + 4)));
	njPopMatrix(2);
}
