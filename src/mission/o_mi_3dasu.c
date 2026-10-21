#include "decls.h"

extern struct obj object_mi_3dasu_fat_d[];
extern struct NJS_TEXLIST texlist_mi_3dasu;
extern struct obj DAT_05a862dc;
extern struct CCL_INFO cinfo_mannequin[];

// FUNCTION: SADX 0x0049a770
static void Disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (GetPlayerTaskPointer(0)->exec)
	{
		njPushMatrix(0);
		___njSetTexture(&texlist_mi_3dasu);
		FUN_0067d830(0, var1->pos.x, (float)(var1->pos.y + var1->value.f), var1->pos.z);
		if (var1->ang.y)
		{
			njRotateY(0, (unsigned short)var1->ang.y);
		}
		___dsDrawObject(object_mi_3dasu_fat_d);
		if (var1->flag & 1)
		{
			SetRegularTexture();
			FUN_0067d830(0, 0.0f, (float)(0.10000000149011612 - var1->value.f), 0.0f);
			late_DrawShadowObject(&DAT_05a862dc, 1.0f);
		}
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x0049a840
static void Destructor(struct task *tp)
{
	struct colliwk *var1 = tp->twp->cwp;
	struct taskwk *var2 = (struct taskwk *)DAT_05baf368;
	if (var2)
	{
		for (long var3 = 0; var3 < var1->nbHit; var3++)
		{
			if (var1->hit_info[var3].hit_twp == var2)
			{
				var2->flag &= ~0x800;
				*(signed char *)DAT_05baf368 = 1;
				*(long *)(*(char **)DAT_05ba3328[0] + 0x68) = 0;
				return;
			}
		}
	}
}

// FUNCTION: SADX 0x0049a8a0
static void Exec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct motionwk *var2 = tp->mwp;
	struct NJS_POINT3 local_10;
	if (CheckRangeOut(tp))
	{
		FreeTask(tp);
	}
	if (!EV_CheckCansel())
	{
		if (!IsMissionDispFlag(tp))
		{
			DestroyTask(tp);
			return;
		}
		switch (var1->mode)
		{
		case 0:
			CCL_Init(tp, cinfo_mannequin, 3, 4);
			ObjectMovableInitialize(var1, var2, 4);
			var1->flag |= 2;
			tp->disp = Disp;
			var1->value.f = 8.0f;
			var1->mode = 1;
			break;
		case 1:
			local_10.x = var1->pos.x;
			local_10.y = var1->pos.y;
			local_10.z = var1->pos.z;
			ObjectMovableSRegularExecute(tp);
			if (var1->flag & 1)
			{
				var1->pos.x = local_10.x;
				var1->pos.y = local_10.y;
				var1->pos.z = local_10.z;
			}
			if (var1->flag & 0x1000)
			{
				var1->wtimer = 0;
				var1->mode = 2;
			}
			else if (!(var1->flag & 1))
			{
				if (++var1->wtimer >= 600)
				{
					tp->exec = DestroyTask;
				}
			}
			break;
		case 2:
			var1->ang.y = -((struct taskwk *)DAT_05baf368)->ang.y;
			ObjectMovableSRegularExecute(tp);
			if (!(var1->flag & 0x1000))
			{
				var1->mode = 1;
			}
			break;
		}
		var1->ang.x = 0;
		var1->ang.z = 0;
		Disp(tp);
	}
}

// FUNCTION: SADX 0x0049a9f0
void ObjectMi3Dasu(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (IsMissionAppear(tp))
	{
		var1->wtimer = 0;
		tp->exec = Exec;
		tp->dest = Destructor;
		tp->disp = Disp;
	}
}
