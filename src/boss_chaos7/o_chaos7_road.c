#include "decls.h"

// FUNCTION: SADX 0x00702c90
void dispChaos7Road(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	SetObjectTexture();
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (var1->ang.z != 0)
	{
		njRotateZ(NULL, (unsigned short)(short)var1->ang.z);
	}
	if (var1->ang.x != 0)
	{
		njRotateX(NULL, (unsigned short)var1->ang.x);
	}
	if (var1->ang.y != 0)
	{
		njRotateY(NULL, (unsigned short)var1->ang.y);
	}
	ds_DrawObjectClip((struct obj *)var1->timer.ptr, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00702d20
void destChaos7Road(struct task *tp)
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
	FreeTask(tp);
}

// FUNCTION: SADX 0x00702f20
void ObjectChaos7Road0(struct task *tp)
{
	tp->twp->btimer = 0;
	execChaos7Road(tp);
}

// FUNCTION: SADX 0x00702f40
void ObjectChaos7Road1(struct task *tp)
{
	tp->twp->btimer = 1;
	execChaos7Road(tp);
}

// FUNCTION: SADX 0x00702f60
void ObjectChaos7Road2(struct task *tp)
{
	tp->twp->btimer = 2;
	execChaos7Road(tp);
}

// FUNCTION: SADX 0x00702f80
void ObjectChaos7Road3(struct task *tp)
{
	tp->twp->btimer = 3;
	execChaos7Road(tp);
}

// FUNCTION: SADX 0x00702fa0
void ObjectChaos7Road4(struct task *tp)
{
	tp->twp->btimer = 4;
	execChaos7Road(tp);
}
