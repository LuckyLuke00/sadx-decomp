#include "decls.h"
extern struct TaskInfo RdTaskInfo;

// FUNCTION: SADX 0x007e43a0
void Rd_MiniCart(struct task *task_p)
{
	MirenInitTask(task_p, &RdTaskInfo, 0);
}

// FUNCTION: SADX 0x007e4450
void deadRound(struct task *tp)
{
	ResetMleriRangeRad();
}

// FUNCTION: SADX 0x007e4460
void initRound(struct task *task_p, const void *param_p)
{
	struct task *var1;
	*(char *)task_p->mwp = 0;
	var1 = CreateElementalTask(2, 0, mc_bgmcontrol);
	var1->twp->mode = 0x19;
	var1->twp->wtimer = 0xa;
	InitSnatchPlayerInfo();
	SetMleriRangeRad(2000.0f);
	InitStartDushCheck();
	execRound(task_p);
}

// STUB: SADX 0x007f2e70
void mc_bgmcontrol(struct task *tp)
{
}
