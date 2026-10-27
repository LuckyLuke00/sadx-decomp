#include "decls.h"
void FUN_007ecd30(struct task *param_1);
void FUN_007ecd30(struct task *param_1);

// FUNCTION: SADX 0x007ed6d0
void sht_Zako3Gun(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct task *var2 = tp->ptp;
	struct taskwk *var3 = var2->twp;

	switch (var1->mode)
	{
	case 0:
		var1->pos.x = 0.0f;
		var1->pos.y = 0.0f;
		var1->pos.z = 0.0f;
		var1->ang.x = 0;
		var1->ang.y = 0;
		var1->ang.z = 0;
		var1->timer.w[0] = 0;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		var1->mode = 1;
		break;
	case 1:
		if (var3->mode == 1)
		{
			var1->pos = var3->pos;
			DirectionToPlayer(var1);
			if (FrameIn(var3) != 0)
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
		DestroyTask(tp);
		return;
	}
	LoopTaskC(tp);
}
