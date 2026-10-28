#include "decls.h"
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
				var1->counter.f = *(float *)((char *)var1 + 0x2c) + var1->counter.f;
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

// STUB: SADX 0x00808490
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
			CCL_Init(tp, (struct CCL_INFO *)0x3b75508, 2, 4);
			break;
		case 1:
			var1->counter.f = *(float *)((char *)var1 + 0x2c) + var1->counter.f;
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

// STUB: SADX 0x00808520
void ObjectWindySakuC(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->value.ptr = (void *)0x3b32804;
	CCL_Init(tp, (struct CCL_INFO *)0x3b75568, 1, 4);
	var1->timer.b[0] = 1;
	tp->exec = Exec;
	tp->disp = Draw;
}

// STUB: SADX 0x00808560
void ObjectWindyHaneA(struct task *tp)
{
}

// STUB: SADX 0x008085a0
void ObjectWindyHaneB(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->value.ptr = (void *)0x3b43ea8;
	CCL_Init(tp, (struct CCL_INFO *)0x3b75598, 1, 4);
	var1->timer.b[0] = 1;
	tp->exec = Exec;
	tp->disp = Draw;
}

// STUB: SADX 0x008085e0
void ObjectWindyBigFlootB(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->value.ptr = (void *)0x3b4a048;
	CCL_Init(tp, (struct CCL_INFO *)0x3b75628, 1, 4);
	var1->timer.b[0] = 1;
	tp->exec = Exec;
	tp->disp = Draw;
}
