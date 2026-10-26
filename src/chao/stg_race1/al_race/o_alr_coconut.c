#include "decls.h"
extern struct TaskInfo DAT_009c8b18;
extern struct ActionParam DAT_009c8b34;

// FUNCTION: SADX 0x00717790
void ObjectAlrCoconut(struct task *task_p)
{
	MirenInitTask(task_p, &DAT_009c8b18, &DAT_009c8b34);
}

// STUB: SADX 0x007177b0
void initObject(struct task *task_p, const struct ActionParam *param_p)
{
}
