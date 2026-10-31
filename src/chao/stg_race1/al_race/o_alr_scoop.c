#include "decls.h"

// GLOBAL: SADX 0x00962f80
static struct TaskInfo ObjectTaskInfo;

extern struct ActionParam DAT_00962f98;

// FUNCTION: SADX 0x00493410
void ObjectAlrScoop(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_00962f98);
}
