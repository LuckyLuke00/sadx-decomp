#include "decls.h"
extern struct CCL_INFO WarpColliInfo[4];
void FUN_007d21b0(...);

// FUNCTION: SADX 0x0069ee20
void EffectWarp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->scl.x = 1.0;
	var1->scl.y = 0.0;
	var1->ang.x = 0;
	var1->scl.z = 0.0;
	*(int *)((char *)var1 + 0x1c) = 0;
	tp->exec = EffectWarpExecutor;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	tp->disp = EffectWarpDisplayer;
}

// FUNCTION: SADX 0x0069f040
void ObjectECEggWarp(struct task *tp)
{
	if (FUN_004c39c0(tp) == 0)
	{
		CCL_Init(tp, WarpColliInfo, 4, 4);
	}
	tp->exec = ObjectChaoWarpExecutor;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	tp->disp = ObjectChaoWarpDisplayer;
}
