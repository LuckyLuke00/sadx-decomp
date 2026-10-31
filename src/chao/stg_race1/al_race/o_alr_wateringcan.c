#include "decls.h"

// GLOBAL: SADX 0x00962f28
static struct TaskInfo ObjectTaskInfo;

extern struct ActionParam DAT_00962f40;

// FUNCTION: SADX 0x00493310
void ObjectAlrWateringCan(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_00962f40);
}
