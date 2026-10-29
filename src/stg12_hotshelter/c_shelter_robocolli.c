#include "decls.h"
extern struct obj object_no_name_cuuube01_cuuube01[];

// GLOBAL: SADX 0x04ad7ed4
static struct CCL_INFO cinfo_appear[1] =
{
	{0, 3, 0x70, 0xe0, 0x380000, {0.0f, 10.0f, 0.0f}, 5.0f, 10.0f, 2.0f, 0.0f, 0, 0, 0}
};

// FUNCTION: SADX 0x008ac3f0
static void DrawBoxColli(struct taskwk *twp)
{
	float local_8 = twp->scl.x * 0.2f;
	float local_c = twp->scl.y * 0.2f;
	float local_10 = twp->scl.z * 0.2f;

	njPushMatrix(0);
	FUN_0067d830(0, twp->pos.x, twp->pos.y + twp->scl.y, twp->pos.z);
	if (twp->ang.y)
	{
		njRotateY(0, (Uint16)twp->ang.y);
	}
	FUN_0067d2d0(0, local_8, local_c, local_10);
	SetMaterial(0.05f, 0.05f, 0.0f, 0.0f);
	___dsDrawObject(object_no_name_cuuube01_cuuube01);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008ac4b0
void ColliShelterSwitch(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct CCL_INFO *var2;

	if (DAT_05ccde90)
	{
		DrawBoxColli(var1);
		DebPrintf(0x110010, "-> SWITCH ID");
		DebPrintf(0x110011, "-> ROTATE Y");
		DebPrintf(0x110012, "-> NO USE");
		DebPrintf(0x110013, "-> SIZE X");
		DebPrintf(0x110014, "-> SIZE Y");
		DebPrintf(0x110015, "-> SIZE Z");
		return;
	}
	if (CheckRangeOut(tp))
	{
		return;
	}
	switch (var1->mode)
	{
	case 0:
		var1->btimer = var1->ang.x;
		var1->ang.x = 0;
		var1->ang.z = 0;
		CCL_Init(tp, cinfo_appear, 1, 4);
		var2 = var1->cwp->info;
		var2->center.y = var1->scl.y;
		var2->a = var1->scl.x;
		var2->b = var1->scl.y;
		var2->c = var1->scl.z;
		var1->mode = 1;
		break;
	case 1:
		if (var1->cwp->flag & 1)
		{
			FUN_0058b860(var1->btimer, 1);
			FreeTask(tp);
			return;
		}
		break;
	}
	EntryColliList(var1);
}
