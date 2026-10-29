#include "decls.h"
extern int DAT_060dd07c;
extern struct obj object_no_name_cuuube01_cuuube01[];
extern struct CCL_INFO cinfo_root[];
extern "C" int rand(void);

// FUNCTION: SADX 0x00890a50
void DoorDestructor(struct task *tp)
{
	dsStop_id((int)tp->twp);
}

// FUNCTION: SADX 0x00890b20
void FUN_00890b20(void)
{
	SetPositionP(0, 2033.0f, 5239.0f, -2330.0f);
	DAT_05baf368[0]->ang.y = 0x4000;
}

// FUNCTION: SADX 0x00890b60
void FEGG_ResetAmysFakeRoot()
{
	int var1;
	float var2;

	var1 = rand();
	var2 = (float)var1 * 3.0517578125e-05f;
	var1 = (long)(var2 * 5.0f);
	DAT_060dd07c = var1;
}

// FUNCTION: SADX 0x00890c10
void ColliFinalEggFakeRoot(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05ccde90)
	{
		if (DAT_05b9d838)
		{
			return;
		}
		njPushMatrix(0);
		FUN_0067d830(0, var1->pos.x, var1->pos.y + 30.0, var1->pos.z);
		if (var1->ang.y)
		{
			njRotateY(0, (Uint16)var1->ang.y);
		}
		FUN_0067d2d0(0, 6.0f, 6.0f, 2.0f);
		SetMaterial(0.05f, 1.0f, 0.0f, 0.0f);
		ds_DrawObjectClip(object_no_name_cuuube01_cuuube01, FUN_00500c70(6.0f, 6.0f, 2.0f));
		njPopMatrix(1);
		njPrintC(0xa001f, "SCL X -> UNIT ID(1 - 5)");
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
		CCL_Init(tp, cinfo_root, 1, 4);
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		var1->mode = 1;
		break;
	case 1:
		if (DAT_060dd07c == var1->btimer && (var1->cwp->flag & 1))
		{
			FUN_00890b20();
			DeadOut(tp);
		}
		break;
	}
	EntryColliList(var1);
}
