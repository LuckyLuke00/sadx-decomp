#include "decls.h"
static void TaskBossExec(struct task *tp);
static void TaskBossDisp(struct task *tp);

// STUB: SADX 0x006c5c90
long Egm2WeakPointZeroCheck(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x006c5ce0
void Egm2PodPlayerSearch(struct task *tp)
{
}

// STUB: SADX 0x006c5de0
void Egm2ShadowDraw(struct task *tp)
{
}

#pragma optimize("", off)
// STUB: SADX 0x006c6400
static void TaskBossDisp(struct task *tp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x006c65c0
static void TaskBossExec(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006c66f0
void setBoss_egm2()
{
	struct task *var1 = CreateElementalTask(3, 1, TaskBossExec);
	if (var1 != 0)
	{
		var1->exec = TaskBossExec;
		var1->disp = TaskBossDisp;
	}
}
