#include "decls.h"
extern struct TaskInfo ObjectTaskInfo;
extern struct ActionParam DAT_00a09fb0;
static void execObject(struct task *task_p);
static void initObject(struct task *task_p, void *param_p);
static void dispObject(struct task *task_p);

// FUNCTION: SADX 0x007e6040
void ObjectCartDial(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_00a09fb0);
}

#pragma optimize("", off)
// STUB: SADX 0x007e6060
static void initObject(struct task *param_1, void *param_2)
{
}
#pragma optimize("", on)

// STUB: SADX 0x007e6080
void FUN_007e6080(char param_1)
{
}

#pragma optimize("", off)
// STUB: SADX 0x007e60f0
static void dispObject(struct task *task_p)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x007e6240
static void execObject(struct task *task_p)
{
	struct motionwk *var1;

	if (CheckRangeOut(task_p) == 0)
	{
		var1 = task_p->mwp;
		var1->work.b[0] = CartRaceGetDialState();
		dispObject(task_p);
	}
}

// GLOBAL: SADX 0x00a09f20
static struct TaskInfo ObjectTaskInfo = {8, 2, initObject, execObject, dispObject, 0};
