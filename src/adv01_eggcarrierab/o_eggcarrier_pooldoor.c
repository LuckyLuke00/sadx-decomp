#include "decls.h"
extern unsigned char DAT_05bafc0d;
extern struct NJS_MODEL **DAT_060f4ad4;

// FUNCTION: SADX 0x006960f0
static void ExecATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	int var2;

	EntryColliList(var1);
	var2 = GetPlayerNumber() == 3 ? DAT_05bafc0d : 0;
	if (var2)
	{
		var1->cwp->info->center.z = 20.0f;
	}
	else
	{
		var1->cwp->info->center.z = 0.0f;
	}
}

// FUNCTION: SADX 0x00696130
static void DispATask(struct task *tp)
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
		njRotateY(0, var1->ang.y);
	}
	FUN_0067d830(0, 0.0f, 0.0f, var1->cwp->info->center.z);
	ds_DrawModelClip(DAT_060f4ad4[7], 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x006961c0
static void InitATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	tp->disp = DispATask;
	tp->dest = (void (*)(struct task *))FUN_007d21b0;
	CCL_Init(tp, ColliInfo, 1, 4);
	var1->mode = 1;
}

// FUNCTION: SADX 0x006961f0
void ObjectECPoolDoor(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 1000000.0f) == 0)
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
				ExecATask(tp);
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
				ExecATask(tp);
				break;
			}
		}
	}
}
