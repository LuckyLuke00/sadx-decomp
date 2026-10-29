#include "decls.h"
extern struct obj object_no_name_cuuube01_cuuube01[];
void FinalEggSetAppearZERO(long no);

// GLOBAL: SADX 0x048a58c0
static struct CCL_INFO cinfo_appear[1] =
{
	{ 0, 3, 0x70, 0xe0, 0x380000, { 0.0f, 10.0f, 0.0f }, 5.0f, 10.0f, 2.0f, 0.0f, 0, 0, 0 }
};

// FUNCTION: SADX 0x008933d0
static void DrawBoxColli(struct taskwk *twp)
{
	float local_c = twp->scl.x * 0.20000000298023224;
	float local_10 = twp->scl.y * 0.20000000298023224;
	float local_14 = twp->scl.z * 0.20000000298023224;
	if (DAT_05b9d838)
	{
		return;
	}
	njPushMatrix(0);
	FUN_0067d830(0, twp->pos.x, twp->pos.y + twp->scl.y, twp->pos.z);
	if (twp->ang.y)
	{
		njRotateY(0, twp->ang.y);
	}
	FUN_0067d2d0(0, local_c, local_10, local_14);
	SetMaterial(0.05f, 0.05f, 0.0f, 0.0f);
	ds_DrawObjectClip(object_no_name_cuuube01_cuuube01, FUN_00500c70(local_c, local_10, local_14));
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008934d0
void ColliFinalEggAppearZERO(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct CCL_INFO *var2;
	if (DAT_05ccde90)
	{
		DrawBoxColli(var1);
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
			FinalEggSetAppearZERO(var1->btimer);
			FreeTask(tp);
			return;
		}
		break;
	}
	EntryColliList(var1);
}

// FUNCTION: SADX 0x00893580
void ColliFinalEggKillZERO(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct CCL_INFO *var2;
	if (DAT_05ccde90)
	{
		DrawBoxColli(var1);
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
			ERobKill();
			FreeTask(tp);
			return;
		}
		break;
	}
	EntryColliList(var1);
}
