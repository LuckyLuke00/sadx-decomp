#include "decls.h"
static void execRound(struct task *task_p);
static void initRound(struct task *task_p, const void *param_p);
extern struct TaskInfo DAT_00a0a360;

// FUNCTION: SADX 0x007e6e60
static void initRound(struct task *task_p, const void *param_p)
{
	task_p->mwp->work.b[0] = 0;
}

// FUNCTION: SADX 0x007e6e70
void FUN_007e6e70(void)
{
	SetInputP(0, 0x2c);
	switch (GetPlayerNumber())
	{
	case 2:
		CreateElementalTask(3, 2, MilesSnowBoard);
		break;
	case 0:
		CreateElementalTask(3, 2, SonicSnowBoard);
		break;
	}
}

// STUB: SADX 0x007e6f50
static void execRound(struct task *task_p)
{
}

// FUNCTION: SADX 0x007e6fd0
void Rd_SandBoard(struct task *task_p)
{
	MirenInitTask(task_p, &DAT_00a0a360, 0);
}

// GLOBAL: SADX 0x00a0a360
struct TaskInfo DAT_00a0a360 = {1, 2, (void (*)(struct task *, void *))initRound, execRound, 0, 0};
