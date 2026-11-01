#include "decls.h"

// GLOBAL: SADX 0x009c8a8c
static struct TaskInfo ObjectTaskInfo;

extern struct ActionParam DAT_009c8aa4;

// FUNCTION: SADX 0x007172c0
void ObjectAlrCheerChao(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_009c8aa4);
}
