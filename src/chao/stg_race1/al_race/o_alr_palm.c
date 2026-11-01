#include "decls.h"

// GLOBAL: SADX 0x009c8b50
static struct TaskInfo ObjectTaskInfo;

extern struct ActionParam DAT_009c8b68;

// FUNCTION: SADX 0x00717940
void ObjectAlrPalm(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_009c8b68);
}
