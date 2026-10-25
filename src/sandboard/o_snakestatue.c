#include "decls.h"
extern struct ActionParam DAT_00a0a978;
extern struct TaskInfo ObjectTaskInfo;
// GLOBAL: SADX 0x00a0a958
static struct TaskInfo ObjectTaskInfo;
extern struct ActionParam DAT_00a0a970;

// FUNCTION: SADX 0x007e76a0
void ObjectSnakeStatue(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_00a0a970);
}

// FUNCTION: SADX 0x007e76c0
void ObjectRock(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_00a0a970.action_p);
}

// FUNCTION: SADX 0x007e76e0
void ObjectRockyHead(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_00a0a978);
}

// STUB: SADX 0x007e7700
void initObject(struct task *task_p, const struct ActionParam *param_p)
{
}
