#include "decls.h"
void FUN_00422560(int param_1);
static void Exec(struct task *tp);
static void Disp(struct task *tp);

// FUNCTION: SADX 0x0049c290
static void Disp(struct task *tp)
{
	struct taskwk *var2 = tp->twp;
	unsigned char *var3 = *(unsigned char **)((char *)tp->ocp + 0x10);
	___njSetTexture(&texlist_kariobj);
	FUN_00422560(3);
	njPushMatrix(0);
	matlist_mi_kanban_ita3[0].attr_texId = (unsigned long)((int)var3[8] % 5) + 7;
	njTranslateV(0, &var2->pos);
	if (var2->ang.y != 0)
	{
		njRotateY(0, (unsigned short)var2->ang.y);
	}
	njScaleV(0, &var2->scl);
	___dsDrawObject((struct obj *)&object_mi_kanban_ita);
	njPopMatrix(1);
	npSetZCompare();
}

// FUNCTION: SADX 0x0049c320
static void Exec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct NJS_POINT3 pos;
	if (!CheckRangeOut(tp))
	{
		if (!IsMissionDispFlag(tp))
		{
			DestroyTask(tp);
			return;
		}
		switch (var1->mode)
		{
		case 0:
			if (isRangeMission((struct NJS_POINT3 *)((char *)DAT_05baf368[0] + 0x20), &var1->pos, 1600.0f))
			{
				pos.x = var1->pos.x;
				pos.y = var1->pos.y + 5.0;
				pos.z = var1->pos.z;
				SetLookingPointP(0, &pos);
				var1->mode = 1;
			}
			break;
		case 1:
			if (!isRangeMission((struct NJS_POINT3 *)((char *)DAT_05baf368[0] + 0x20), &var1->pos, 1640.0f))
			{
				CancelLookingAtP(0);
				var1->mode = 0;
			}
			break;
		}
		Disp(tp);
	}
}

// FUNCTION: SADX 0x0049c420
void ObjectMiKanban(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	if (IsMissionAppear(tp))
	{
		var1->ang.x = 0;
		var1->ang.z = 0;
		var1->mode = 0;
		tp->exec = Exec;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		tp->disp = Disp;
	}
}
