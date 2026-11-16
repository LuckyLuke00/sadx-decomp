#include "decls.h"
extern struct obj object_stair_gunpod_gunpod[];

// FUNCTION: SADX 0x007ec8c0
int __fastcall Zako2Move(struct taskwk *twp)
{
	int var1 = twp->value.b[2] * 16 + DAT_060cd3a8;
	int var2 = *(int *)(var1 + 4);
	int var3 = *(int *)*(int *)(var1 + 8);
	twp->pos.x = *(float *)((char *)var2 + (DAT_060ce418 - var3) * 12);
	twp->pos.y = *(float *)((char *)var2 + (DAT_060ce418 - var3) * 12 + 4);
	twp->pos.z = *(float *)((char *)var2 + (DAT_060ce418 - var3) * 12 + 8);
	return 1;
}

#pragma optimize("", off)
// STUB: SADX 0x007ecac0
void DirectionToPlayer(struct taskwk *twp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x007ecbc0
void Zako2GunDraw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct taskwk *var2 = tp->ptp->twp;
	if (DAT_05b9d838 == 0)
	{
		___njFogDisable();
		njPushMatrix(NULL);
		FUN_0067d830(NULL, var2->pos.x, var2->pos.y, var2->pos.z);
		njRotateXYZ(NULL, var2->ang.x, var2->ang.y, var2->ang.z);
		FUN_0067d2d0(NULL, 2.0f, 2.0f, 2.0f);
		FUN_0067d830(NULL, 0.0f, -5.014568f, -1.932182f);
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (Uint16)var1->ang.y);
		}
		___njSetTexture(&texlist_shooting0);
		late_DrawObjectEx(&object_stair_gunpod_gunpod[0], 4);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x007ecca0
void Zako2GunDead(struct task *tp)
{
	tp->twp->mode = 5;
}

// FUNCTION: SADX 0x007ecf40
void sht_Zako2Gun(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct taskwk *var2 = tp->ptp->twp;

	switch (var1->mode)
	{
	case 0:
		var1->ang.x = 0;
		var1->ang.y = 0;
		var1->ang.z = 0;
		var1->timer.w[0] = 0;
		tp->dest = Zako2GunDead;
		tp->disp = Zako2GunDraw;
		var1->mode = 1;
		break;
	case 1:
		if (var2->mode == 1)
		{
			var1->pos = var2->pos;
			DirectionToPlayer(var1);
			Zako2GunDraw(tp);
			if (FrameIn(var2))
			{
				if (var1->timer.w[0] == 0)
				{
					CreateChildTask(2, FUN_007ecd30, tp);
					var1->timer.w[0] = 0x1e;
				}
				else
				{
					var1->timer.w[0]--;
				}
			}
		}
		break;
	case 5:
		FreeTask(tp);
		break;
	}
	LoopTaskC(tp);
}
