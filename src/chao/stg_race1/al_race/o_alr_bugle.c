#include "decls.h"

// GLOBAL: SADX 0x00962f54
static struct TaskInfo ObjectTaskInfo;

extern struct ActionParam DAT_00962f6c;

// FUNCTION: SADX 0x00493380
void ObjectAlrBugle(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_00962f6c);
}
