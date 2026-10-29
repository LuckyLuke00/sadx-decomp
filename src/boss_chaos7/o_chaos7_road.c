#include "decls.h"

// FUNCTION: SADX 0x00702c90
void dispChaos7Road(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	SetObjectTexture();
	njPushMatrix(NULL);
	njTranslateV((float *)0, &var1->pos);
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
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
