#include "decls.h"
extern struct ActionParam DAT_009c8ad8;

// GLOBAL: SADX 0x009c8ab8
static struct TaskInfo ObjectTaskInfo;

extern struct ActionParam DAT_009c8ad0;

// FUNCTION: SADX 0x00717450
void ObjectAlrStartMark(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_009c8ad0);
}

// FUNCTION: SADX 0x00717470
void ObjectAlrSmallScreen(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_009c8ad0.action_p);
}

// FUNCTION: SADX 0x00717490
void ObjectAlrIslet(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_009c8ad8);
}
