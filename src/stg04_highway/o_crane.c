#include "decls.h"

// FUNCTION: SADX 0x00824960
void dispCrane(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	late_DrawModelClipMesh(*(struct NJS_MODEL **)((char *)var1->counter.ptr + 4), 1, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008249d0
void exitCraneManager(struct task *tp)
{
	struct taskwk *var1;
	int var2;

	FreeTaskC(tp);
	var1 = tp->twp;
	var2 = FUN_004c39c0(tp);
	if ((var2 == 0) && (var1->counter.ptr != 0))
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	}
}

// FUNCTION: SADX 0x00824a10
void dispCage(struct task *tp)
{
	struct taskwk *var1;
	float *var2;

	var1 = tp->twp;
	SaveControl3D();
	njControl3D(0x10);
	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	var2 = (float *)0;
	njPushMatrix((NJS_MATRIX *)var2);
	njTranslateV(var2, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY((NJS_MATRIX *)var2, (unsigned short)var1->ang.y);
	}
	SetObjectTexture();
	FUN_0067d830(var2, 0.0f, 0.0f, -30.0f);
	late_ActionClipMesh((struct NJS_ACTION *)var1->timer.ptr, *(float *)((char *)var1 + 0x2c), 0, 1.0f);
	njPopMatrix(1);
	ResetMaterial();
	LoadControl3D();
}
