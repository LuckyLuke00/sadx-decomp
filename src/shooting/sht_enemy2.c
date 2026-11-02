#include "decls.h"

#pragma optimize("", off)
// STUB: SADX 0x007ecac0
void DirectionToPlayer(struct taskwk *twp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x007ecbc0
void Zako2GunDraw(struct task *tp)
{
}
#pragma optimize("", on)

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
