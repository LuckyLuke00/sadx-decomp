#include "decls.h"

// FUNCTION: SADX 0x00703890
void destChaos7Building(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (var1->counter.ptr != 0)
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	}
	FreeTaskC(tp);
	FreeTask(tp);
}

// FUNCTION: SADX 0x007038d0
void dispChaos7Building(struct task *tp)
{
	struct taskwk *var1;
	float *var2;

	var1 = tp->twp;
	SetObjectTexture();
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
	ds_DrawObjectClip((struct obj *)var1->timer.ptr, 1.0f);
	njPopMatrix(1);
	ResetMaterial();
	LoadControl3D();
}

// FUNCTION: SADX 0x00703de0
void ObjectChaos7GrayBld(struct task *tp)
{
	tp->twp->btimer = 0;
	execChaos7Building(tp);
}

// FUNCTION: SADX 0x00703e00
void ObjectChaos7BrownBld(struct task *tp)
{
	tp->twp->btimer = 1;
	execChaos7Building(tp);
}

// FUNCTION: SADX 0x00703e20
void ObjectChaos7RedBld(struct task *tp)
{
	tp->twp->btimer = 2;
	execChaos7Building(tp);
}
