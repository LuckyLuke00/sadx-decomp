#include "decls.h"
extern int DAT_05b9d838;
extern struct taskwk *DAT_05b42a7c;
extern struct obj object_wvobj_watage_watage;
extern struct obj object_wvobj_flower_b_flower_b[];
extern struct obj object_wvobj_flower_a_flower_a[1];

// FUNCTION: SADX 0x008067b0
void ObjectWatageDisplay(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct taskwk *var2 = tp->ptp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var2->scl.x + var1->pos.x, var2->scl.y + var1->pos.y, var2->scl.z + var1->pos.z);
	if (DAT_05b42a7c->ang.y)
	{
		njRotateY(0, (Uint16)DAT_05b42a7c->ang.y);
	}
	late_DrawObjectClip(&object_wvobj_watage_watage, 1, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00806d30
void ObjectWindyFlowerA(struct task *tp)
{
	*(void **)((char *)tp->twp + 8) = object_wvobj_flower_a_flower_a;
	ObjectNormal(tp);
	ObjectCCollision_setWZ(tp);
}

// FUNCTION: SADX 0x00806d50
void ObjectWindyFlowerB(struct task *tp)
{
	tp->twp->counter.ptr = object_wvobj_flower_b_flower_b;
	ObjectNormal(tp);
	ObjectCCollision_setWZ(tp);
}

// FUNCTION: SADX 0x008071c0
void ObjectWindyPopo(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			tp->disp = PopoDisplay;
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			var1->mode = 1;
			break;
		case 1:
			PopoDisplay(tp);
			return;
		}
	}
}
