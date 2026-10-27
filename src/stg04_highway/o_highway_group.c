#include "decls.h"
static void Exec(struct task *tp);
static void DrawForCurb(struct task *tp);

// FUNCTION: SADX 0x0081ca40
static void DrawForCurb(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	SetObjectTexture();
	njPushMatrix((float *)0);
	njTranslateV((float *)0, &var1->pos);
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX((float *)0, *(unsigned short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY((float *)0, *(unsigned short *)((char *)var1 + 0x18));
	}
	___dsDrawObject(&object_curb_curb01_curb01[0]);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0081cac0
void ObjectForCurbCurb(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 2250000.0f) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			tp->disp = DrawForCurb;
			CCL_Init(tp, &object_cu_info[0], 1, 4);
			SET_COLLI_RANGE(var1->cwp, 10.0f);
			var1->mode = 1;
			break;
		case 1:
			DrawForCurb(tp);
			EntryColliList(var1);
			break;
		}
	}
}

#pragma optimize("", off)
// STUB: SADX 0x0081cc10
static void Exec(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0081d0c0
void ObjectHighwayGroupFence(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.l = 0x81e690;
	var1->value.l = 2;
	tp->dest = ExplosionRockDestructor;
	tp->exec = Exec;
}

// FUNCTION: SADX 0x0081d0f0
void ObjectHighwayGroupCurb(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.l = (long)ObjectForCurbCurb;
	var1->value.l = 2;
	tp->dest = ExplosionRockDestructor;
	tp->exec = Exec;
}

// FUNCTION: SADX 0x0081d120
void ObjectHighwayGroupFence02(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.l = 0x81ec10;
	var1->value.l = 2;
	tp->dest = ExplosionRockDestructor;
	tp->exec = Exec;
}

// FUNCTION: SADX 0x0081d150
void ObjectHighwayGroupPinpin(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.l = 0x81f5f0;
	var1->value.l = 2;
	tp->dest = ExplosionRockDestructor;
	tp->exec = Exec;
}

// FUNCTION: SADX 0x0081d180
void ObjectHighwayGroupFF(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.l = (long)ObjectFence;
	var1->value.l = 2;
	tp->dest = ExplosionRockDestructor;
	tp->exec = Exec;
}

// FUNCTION: SADX 0x0081d1b0
void ObjectHighwayGroupRaftA(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.l = (long)ObjectHighwayForRaftA;
	var1->value.l = 6;
	tp->dest = ExplosionRockDestructor;
	tp->exec = Exec;
}

// FUNCTION: SADX 0x0081d1e0
void ObjectHighwayGroupRaftC(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.l = (long)ObjectHighwayRaftC;
	var1->value.l = 6;
	tp->dest = ExplosionRockDestructor;
	tp->exec = Exec;
}

// FUNCTION: SADX 0x0081d210
void ObjectHighwayGroupGreenA(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.l = 0x81ead0;
	var1->value.l = 2;
	tp->dest = ExplosionRockDestructor;
	tp->exec = Exec;
}

// FUNCTION: SADX 0x0081d240
void ObjectHighwayGroupGreenB(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.l = (long)ObjectHighwayGreenB;
	var1->value.l = 2;
	tp->dest = ExplosionRockDestructor;
	tp->exec = Exec;
}

// FUNCTION: SADX 0x0081d270
void ObjectHighwayGroupGreenD(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.l = 0x81eb90;
	var1->value.l = 2;
	tp->dest = ExplosionRockDestructor;
	tp->exec = Exec;
}

// FUNCTION: SADX 0x0081d2a0
void ObjectHighwayGroupClight(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.l = 0x81fbe0;
	var1->value.l = 2;
	tp->dest = ExplosionRockDestructor;
	tp->exec = Exec;
}
