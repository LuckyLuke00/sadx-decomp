#include "decls.h"
extern struct ActionParam DAT_00a09e7c;

// GLOBAL: SADX 0x00a09e64
static struct TaskInfo ObjectTaskInfo;

// FUNCTION: SADX 0x007e5700
void ObjectCartPreviousZone(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_00a09e7c);
}

// FUNCTION: SADX 0x007e5720
void ObjectCartNextZone(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, (void *)((char *)&DAT_00a09e7c + 1));
}
