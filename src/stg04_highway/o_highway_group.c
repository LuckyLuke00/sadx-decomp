#include "decls.h"
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

// STUB: SADX 0x0081cac0
void ObjectForCurbCurb(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 2250000.0f) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			tp->disp = DrawForCurb;
			CCL_Init(tp, (struct CCL_INFO *)0x3e71448, 1, 4);
			SET_COLLI_RANGE(var1->cwp, 10.0f);
			var1->mode = 1;
			break;
		case 1:
			DrawForCurb(tp);
			EntryColliList(var1);
			return;
		}
	}
}

// STUB: SADX 0x0081d180
void ObjectHighwayGroupFF(struct task *tp)
{
}

// STUB: SADX 0x0081d210
void ObjectHighwayGroupGreenA(struct task *tp)
{
}

// STUB: SADX 0x0081d240
void ObjectHighwayGroupGreenB(struct task *tp)
{
}
