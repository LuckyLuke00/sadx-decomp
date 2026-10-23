#include "decls.h"

// FUNCTION: SADX 0x007dd9b0
void FUN_007dd9b0(float param_1, float param_2, float param_3, long param_4, long param_5, long param_6)
{
	struct task *var1;
	var1 = CreateElementalTask(3, 3, mghand_exec);
	if (var1 != 0)
	{
		var1->twp->pos.x = param_1;
		var1->twp->pos.y = param_2;
		var1->twp->pos.z = param_3;
		var1->twp->ang.x = param_4;
		var1->twp->ang.y = param_5;
		var1->twp->ang.z = param_6;
		var1->twp->wtimer = 0;
		var1->twp->counter.l = 0;
		var1->mwp->ang_spd.x = 0x20;
		var1->mwp->ang_spd.y = 0x200;
		var1->disp = mghand_draw;
		var1->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	}
}
