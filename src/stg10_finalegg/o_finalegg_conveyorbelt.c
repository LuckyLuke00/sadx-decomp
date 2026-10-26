#include "decls.h"
void SideTaskExec(struct task *tp);

// FUNCTION: SADX 0x0089ddc0
void SideTaskExec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckCollisionP(&var1->pos, tp->ptp->twp->scl.z * 128.0f + 20.0f) == 1)
	{
		var1->flag |= 0x100;
		return;
	}
	var1->flag &= 0xfeff;
}

// STUB: SADX 0x0089de40
void SideTask(struct task *tp)
{
}
