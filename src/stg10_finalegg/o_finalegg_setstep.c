#include "decls.h"
static void DispATask(struct task *tp);

// GLOBAL: SADX 0x048a6440
static struct CCL_INFO ColliInfo[1];

static void InitATask(struct task *tp);
extern bool DAT_060dd27c;

// FUNCTION: SADX 0x0089f230
static void DispATask(struct task *tp)
{
	struct taskwk *var1;
	bool var2;

	if (DAT_060dd27c)
	{
		return;
	}
	var1 = tp->twp;
	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	var2 = (var1->pos.x > 2082.0f) && (var1->pos.x < 2084.0f) && (var1->pos.y > 197.0f) && (var1->pos.y < 199.0f) && (var1->pos.z > -1344.0f) && (var1->pos.z < -1342.0f);
	if (var2)
	{
		var1->pos.y = 198.1f;
	}
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	ds_DrawModelClip(model_setasiba_lv1_lv1, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0089f310
static void InitATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	tp->disp = DispATask;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
	CCL_Init(tp, (struct CCL_INFO *)ColliInfo, 1, 4);
	var1->mode = 1;
}

// FUNCTION: SADX 0x0089f340
void ObjectFinalEggSetStep(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 250000.0f) == 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			switch (var1->mode)
			{
			case 0:
				InitATask(tp);
				break;
			case 1:
				DispATask(tp);
				EntryColliList(tp->twp);
				break;
			}
		}
		else
		{
			switch (var1->mode)
			{
			case 0:
				InitATask(tp);
				break;
			case 1:
				DebPrintf(0x110010, "-> ROTATE X");
				DebPrintf(0x110011, "-> ROTATE Y");
				DebPrintf(0x110012, "-> ROTATE Z");
				DispATask(tp);
				EntryColliList(tp->twp);
				break;
			}
		}
	}
}
