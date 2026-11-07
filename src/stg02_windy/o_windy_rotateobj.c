#include "decls.h"

// GLOBAL: SADX 0x03b75508
static struct CCL_INFO object_c_info[7];

extern struct CCL_INFO DAT_03b755c8[1];
extern struct CCL_INFO DAT_03b75628[];
extern struct obj object_windobj_bigflootb_bigflootb[];
extern struct CCL_INFO DAT_03b75598[];
extern struct CCL_INFO DAT_03b75568[];
extern struct obj object_windobj_saku_c_saku_c[];
static void Draw(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x00807f30
static void Draw(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00808400
static void Exec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 1000000.0f) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			var1->mode = 1;
			break;
		case 1:
			if (dsCheckViewV(&var1->pos, 200.0f))
			{
				var1->counter.f = var1->scl.x + var1->counter.f;
				if (FUN_004c39c0(tp))
				{
					njPrintC(0x110013, "<- ROTATE_SPEED");
				}
				Draw(tp);
				EntryColliList(var1);
				return;
			}
			break;
		}
	}
}

// FUNCTION: SADX 0x00808490
void ObjectWindyHasiEnd(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 2250000.0f) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			var1->mode = 1;
			tp->disp = DrawHasiEnd;
			CCL_Init(tp, object_c_info, 2, 4);
			break;
		case 1:
			var1->counter.f = var1->scl.x + var1->counter.f;
			if (FUN_004c39c0(tp))
			{
				njPrintC(0x110013, "<- ROTATE_SPEED");
			}
			DrawHasiEnd(tp);
			EntryColliList(var1);
			return;
		}
	}
}

// FUNCTION: SADX 0x00808520
void ObjectWindySakuC(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->value.ptr = &object_windobj_saku_c_saku_c;
	CCL_Init(tp, (struct CCL_INFO *)&DAT_03b75568, 1, 4);
	var1->timer.b[0] = 1;
	tp->exec = Exec;
	tp->disp = Draw;
}

// FUNCTION: SADX 0x00808560
void ObjectWindyHaneA(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->value.ptr = &object_windobj_haneobj_a_haneobj_a;
	CCL_Init(tp, DAT_03b755c8, 2, 4);
	var1->timer.b[0] = 2;
	tp->exec = Exec;
	tp->disp = Draw;
}

// FUNCTION: SADX 0x008085a0
void ObjectWindyHaneB(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->value.ptr = &object_windobj_haneobj_b_haneobj_b;
	CCL_Init(tp, DAT_03b75598, 1, 4);
	var1->timer.b[0] = 1;
	tp->exec = Exec;
	tp->disp = Draw;
}

// FUNCTION: SADX 0x008085e0
void ObjectWindyBigFlootB(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->value.ptr = &object_windobj_bigflootb_bigflootb;
	CCL_Init(tp, DAT_03b75628, 1, 4);
	var1->timer.b[0] = 1;
	tp->exec = Exec;
	tp->disp = Draw;
}
